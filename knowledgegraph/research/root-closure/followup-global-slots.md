# Follow-up global-slot investigation

## Scope

Static-only follow-up for Phase-0 Root Closure. Binary: `SPORE/SporeBin/SporeApp.exe` 3.1.0.22, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`, `x86:LE:32:windows`.

No Wine, runtime trace, source edit, `SPORE/` edit, historical artifact edit, or Phase-0 interface edit was made. The only outputs are this report and `followup-global-slots.json`.

Inputs were read-only `objdump`/`llvm-readobj`, committed canonical xrefs, committed Ghidra function/structure/SDK/decompiler exports, and committed decomp-gap projections.

## Findings

1. **`DAT_0167eae0` is a `cGameNounManager*`, not a generic owner/context pointer.** `0x00b3d300` returns it; `0x00bff408..0x00bff428` moves the return directly into ECX and calls `0x00b21340`, the high-confidence `cGameNounManager::GetData` implementation. That body uses `this+0x98` (`mNounMap`) and `this+0x78` (`mNouns`). The same pointee contract is exposed by noun helpers and the `this+0x74` `mpPlayer` read.
2. **`0x00b3d2a0` is not canonical `cStarManager::Get`.** It returns `DAT_0167eae4`, an alternate `cStarManager`-compatible slot used at `mEmpires +0x150` and `mpRelationshipManager +0x204`. The SDK-declared canonical getter is `0x00b3d3a0`, returning the different slot `DAT_0167eb0c`.
3. **The four globals form two alternate/canonical pairs.** Aliasing is possible but not proven:

   | domain | alternate | canonical |
   |---|---|---|
   | noun manager | `DAT_0167eae0` / `0x00b3d300` | `DAT_0167eb60` / `0x00b3d400` |
   | star manager | `DAT_0167eae4` / `0x00b3d2a0` | `DAT_0167eb0c` / `0x00b3d3a0` |

4. **No direct static writer was found.** Full executable disassembly contains only five direct reads: `eae0` once, `eae4` twice, `eb0c` once, and `eb60` once. All are loads. The slots lie in the writable zero-fill tail of `.data`: no on-disk pointer initializer or matching relocation was found. This does not prove immutability; indirect/bulk publication remains unresolved.
5. **`0x00b3d2c0` is not a getter or initializer.** It selects among state-dependent results, including `[DAT_0167eae4+0x204]`, `SpacePlayerData+0x0c`, and zero.
6. **The committed “`cStarManager::Get` fan-in 0” is an analysis gap.** Raw disassembly finds an unowned 14-byte thunk at `0x00b5ca50` that calls `0x00b3d3a0` and dispatches its returned object's vtable. `functions.tsv` has no function at `0x00b5ca50`, and the committed xref TSV has no corresponding row.

## Direct global-reference inventory

| global | direct static references | direct writes |
|---|---|---|
| `0x0167eae0` | `0x00b3d300: mov eax, ds:0x167eae0` | none found |
| `0x0167eae4` | `0x00b3d2a0: mov eax, ds:0x167eae4`; `0x00b3d2f0: mov ecx, ds:0x167eae4` | none found |
| `0x0167eb0c` | `0x00b3d3a0: mov eax, ds:0x167eb0c` | none found |
| `0x0167eb60` | `0x00b3d400: mov eax, ds:0x167eb60` | none found |

`.data` begins at VA `0x0150c000`, has virtual size `0x212764`, and raw size `0x0c4c00`. The four slots are beyond raw contents but within the writable virtual extent. The image therefore supplies no static pointer initializer for them.

## Decoded contracts

### `0x00b3d300` — alternate noun-manager accessor

```text
mov eax, DAT_0167eae0
ret
```

High-information proof:

```text
0x00bff408 call 0x00b3d300
...
0x00bff426 mov ecx,eax
0x00bff428 call 0x00b21340
```

`0x00b21340` starts with `mov esi,ecx`, searches `[esi+0x98]`, and walks `[esi+0x78]`. Those match SDK `cGameNounManager::mNounMap` and `mNouns`. The committed root-closure graph also records 232 distinct common direct callers of `0x00b3d300` and `0x00b21340`.

This supersedes the earlier generic “shared context/owner” interpretation. The safe interpretation is:

> `0x00b3d300` returns an alternate global `cGameNounManager*` slot.

Whether that pointer is always identical to `DAT_0167eb60` remains unresolved.

### `0x00b3d2a0` — alternate star-manager accessor

```text
mov eax, DAT_0167eae4
ret
```

The returned object is consumed as a manager receiver:

- `0x00ba9370` searches `this+0x150` and compares with map end storage at `this+0x154`, matching `cStarManager::mEmpires`.
- `0x00b3d2f0` loads `DAT_0167eae4` directly into ECX and tail-jumps to `0x00c4f030`.
- `0x00c4f030` returns `[ECX+0x204]`, matching `cStarManager::mpRelationshipManager`.
- `0x01021300` uses this accessor on empire-cache miss/mismatch, then performs AddRef/store/Release replacement on `SpacePlayerData+0x1c`.

The safe interpretation is:

> `0x00b3d2a0` is a high-fan-in alternate `cStarManager*` access path, not the SDK-declared canonical getter.

The canonical getter remains `0x00b3d3a0 -> DAT_0167eb0c`.

### `0x00b3d2c0` — state-selected bridge

The 59-byte function:

1. calls `0x00b5b800` to obtain forwarded state;
2. compares selected state constants;
3. may jump to `0x010212f0`, which reads `SpacePlayerData+0x0c`;
4. may load `DAT_0167eae4` into ECX and tail-jump to `0x00c4f030`, returning relationship-manager `+0x204`;
5. otherwise returns zero.

It directly consumes the alternate star-manager slot but does not return that manager and does not initialize it.

### Canonical getters

- `0x00b3d3a0`: SDK/decompiler name `Simulator::cStarManager::Get`; returns `DAT_0167eb0c`.
- `0x00b3d400`: SDK/decompiler name `Simulator::cGameNounManager::Get`; returns `DAT_0167eb60`.

Both are six-byte borrowed global loaders with no validation, refresh, AddRef, lock, or write.

## Aliasing evidence

### Noun pair

Committed xrefs show 11 distinct functions that directly call both `0x00b3d300` and `0x00b3d400`:

```text
00ae9f50 00aebe90 00b33350 00b335d0 00cd3bf0 00d0e170
00d100b0 00d38150 00ef10c0 00fe5a20 01007430
```

`0x00aebe90` is especially informative:

```text
0x00aec5b6 -> 0x00b3d300 -> noun/current-empire helper
0x00aece60 -> 0x00b3d300 -> 0x00f67d90 -> this+0x74
0x00aece75 -> 0x00b3d400 -> canonical cGameNounManager
```

The function co-uses both slots but does not compare the returned pointers. Co-call and field compatibility do not prove equality.

### Star pair

The committed xref export records zero callers of `0x00b3d3a0`, so it cannot produce a meaningful alternate/canonical common-caller set. Raw disassembly supplies the missing executable evidence:

```text
0x00b5ca50 call 0x00b3d3a0
0x00b5ca55 mov edx,[eax]
0x00b5ca57 mov ecx,eax
0x00b5ca59 mov eax,[edx+0x28]
0x00b5ca5c jmp eax
```

This is a virtual dispatch on the canonical star-manager object. It still supplies no writer, equality check, or lifecycle evidence.

The safest alias model is:

```text
alternate global pointer slot  ==?  canonical global pointer slot
```

Possible outcomes—same pointer, phase-specific distinct pointers, or unresolved indirect publication—must remain open.

## Selected-window findings

### `0x00ba9370`

- ECX is the manager receiver; the ID is one stack argument.
- ID `-1` returns zero.
- The helper searches `this+0x150` through `0x00e5c780`.
- It compares the returned iterator with `this+0x154`.
- Non-end results return node payload at `+0x14`.
- It has no exact-key equality check and does not mutate the map.

Keep the operation described as lower-bound/ceiling projection, not exact find or insertion.

### `0x01021300`

```text
id = SpacePlayerData+0x18
cached = SpacePlayerData+0x1c
if id == -1: return 0
if cached && cached->0x84 == id: return cached
empire = DAT_0167eae4 lookup through 0x00ba9370
AddRef(empire)
SpacePlayerData+0x1c = empire
Release(old)
return empire
```

This is established cache mutation. It is not publication or teardown of any of the four manager slots.

### `0x00bff2d0`

Contains the decisive alternate noun-manager chain `0x00b3d300 -> 0x00b21340`, plus `0x00b25f40`, `0x00b25fb0`, `0x00b25c30`, and `0x00f67d90` calls on the same noun-manager contract. This is stronger than generic context/fan-in inference.

### `0x00cfbc10`

Contains the complementary domains:

```text
0x00cfc49b -> 0x00b3d2a0 -> 0x00ba9370
0x00cfbe33..0x00cfbed5 -> 0x00b3d300 -> noun/player helpers
0x00cfbfbd -> 0x00b3d300 -> 0x00b21340
```

The star/empire and noun/player roots are separate manager contracts even in one consumer.

### `0x010225d0`

SDK-named `Simulator::SpaceTeleportTo` uses:

- `0x00b3d300 -> 0x00f67d90 -> [cGameNounManager+0x74]` to reach `mpPlayer`/player state;
- `0x00b3d2a0 -> 0x00bb59b0` for a separate star/space operation.

The two manager returns are not compared or substituted.

## Lifecycle result

Established:

- All four getters are raw borrowed global-word loaders.
- No direct slot writer, static pointer initializer, or matching relocation was found.
- `0x01021300` mutates only the current-empire cache.
- `0x00b21340` mutates manager-owned noun-map records.
- `0x00b3d2c0` and `0x00b5ca50` are consumers, not initializers.

Unresolved:

- first writer and last teardown for each slot;
- whether alternate/canonical pairs are published together;
- simultaneous-alias or phase-distinct-object behavior;
- nullability, publication ordering, and reference ownership;
- indirect consumers of the canonical getters;
- any thread-safety or teardown guarantees.

Absence of a direct writer must not be converted into an immutability claim.

## Decomp-gap correction

The committed function table contains:

```text
00b5c9d0 ... size 94 ... ends before 00b5ca2e
00b5ca60 ... next committed function
```

It has no function at `0x00b5ca50`, even though executable bytes and the canonical getter call exist there. The xref exporter consequently misses that call. The committed fan-in value zero for `0x00b3d3a0` remains a valid description of the committed projection, but not of the binary.

The noun SDK address contradiction also remains:

- SDK XML names `GetData` at `0x00b212d0`.
- The called, high-confidence implementation is the separate 202-byte function at `0x00b21340`.
- Exact SDK-entry identity remains unresolved; implementation mechanics at `0x00b21340` are strong.

## Unresolved results

1. Whether `DAT_0167eae0` and `DAT_0167eb60` are always equal, phase-distinct, or sometimes distinct instances.
2. Whether `DAT_0167eae4` and `DAT_0167eb0c` are always equal, phase-distinct, or sometimes distinct instances.
3. The exact direct or indirect writer for every slot.
4. The alias publication and teardown order for each pair.
5. The owner and caller path of unowned `0x00b5ca50`, plus indirect users of `0x00b3d3a0`.
6. Exact relationship between SDK `0x00b212d0` and implementation `0x00b21340`.
7. Nullability, concurrency, and AddRef/Release ownership of the global manager slots.

## Evidence

Primary committed evidence:

- `knowledgegraph/research/root-closure/track-a-service-identity.{json,md}`
- `knowledgegraph/research/root-closure/track-d-noun-registry.{json,md}`
- `knowledgegraph/research/root-closure/cross-root-relationships.{json,md}`
- `knowledgegraph/triage/xrefs-2540f2ca.tsv`
- `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json`
- `knowledgegraph/triage/reconstruction-readiness-f0e310e0.json`
- `.spore-analysis/ghidra-exports/functions.tsv`
- `.spore-analysis/ghidra-exports/sdk_functions.tsv`
- `.spore-analysis/ghidra-exports/structs_fields.tsv`
- `.spore-analysis/ghidra-exports/spore_sdk.xml`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cStarManager__Get.c`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cGameNounManager__Get.c`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cGameNounManager__GetData.c`
- `knowledgegraph/research/decomp-gap/sim-core-{00,04,07}.json`
- `knowledgegraph/research/global-campaign-2026/track-j-dependency-graph.json`

Supplemental read-only checks used `objdump -d/-h/-p/-x/-r/-s`, `llvm-readobj --sections`, and `sha256sum` on the existing binary.
