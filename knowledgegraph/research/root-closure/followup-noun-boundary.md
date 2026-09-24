# Follow-up noun boundary — Phase-0 Root Closure

## Scope

Static-only investigation of `0x00b21340`, the SDK address `0x00b212d0`, `0x00ba8420`, `0x00b25f40`, callbacks `0x00b21080`/`0x00d3d420`/`0x00b236c0`/`0x00b1e500`, central consumer `0x00bfbbf0`, and the `0x00b25fb0` receiver question. Pinned binary: `SPORE/SporeBin/SporeApp.exe` 3.1.0.22, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`. No runtime, Wine, source, `SPORE/`, historical artifact, or Phase-0 interface edits.

## Executive findings

1. **`0x00b21340` is the actual `Simulator::cGameNounManager::GetData` implementation.** `0x00b212d0` is not a second implementation: raw control flow reaches it by `jmp` from the real `0x00b211e0` body. The committed `0x00b211e0 -> 0x00b212d0` xref is a split-function intra-function jump misclassified as a call.
2. **`0x00b21340` uses lower-bound, not exact-find.** It calls `0x00e5c780`, compares only against the map end sentinel, and never checks the returned node key. A missing noun with a greater successor can select/rebuild the successor record using the requested noun ID.
3. **The four requested callbacks are now mechanically identified.** `0x00b21080` creates a 0x18-byte noun-vector record; `0x00d3d420` releases vector elements; `0x00b236c0` casts to `Simulator::cCivilization` and appends one owned intrusive pointer; `0x00b1e500` compares `cGameData::GetNounID` with the requested noun ID.
4. **`0x00b25f40` is a kCivilization-by-political-ID lookup**, not the SDK `GetPlayerCivilization` entry. It uses the kCivilization callback set and returns the first matching `cGameData`/`cCivilization`-compatible pointer.
5. **`0x00b25fb0` has no caller stack fallback.** Its null-empire path returns the saved incoming `ECX`; it ends with plain `ret`. The selected receiver chains are `0x00b3d300 -> 0x00b25fb0`, not `0x00b3d400 -> 0x00b25fb0`.

## SDK boundary: `0x00b212d0` vs `0x00b21340`

Committed exports disagree:

- `functions.tsv` records a 98-byte function at `0x00b212d0` and a separate 202-byte `FUN_00b21340`.
- `sdk_functions.tsv` labels `0x00b212d0` `Simulator::cGameNounManager::GetData`.
- The committed SDK decompilation at `0x00b212d0` is boundary-contaminated and recursively calls its own SDK-named body.

Raw bytes resolve the boundary:

```text
0x00b211e0  real function entry
...
0x00b212c7  je 0x00b212eb
0x00b212cb  jmp 0x00b212d0
...
0x00b212d0  continuation block labeled GetData by the SDK import
...
0x00b2132f  ret 8
```

The real `0x00b211e0` body walks `mNouns` at `+0x78` and `mObjects` at `+0x10c`, calls `cGameData` vtable `+0x20` (`GetNounID`), and shares the `0x00b2132f` epilogue. It is an unresolved noun-map maintenance/update function, not the five-argument GetData ABI.

`0x00b21340` has the independent contract:

```text
ECX = cGameNounManager-layout receiver
+0x04 create callback
+0x08 clear callback
+0x0c add callback
+0x10 filter callback
+0x14 uint32 nounID
return record pointer
ret 0x14
```

Safe label: `Simulator::cGameNounManager::GetData [implementation 0x00b21340; SDK address 0x00b212d0 is a split continuation]`.

## `0x00b21340` ordering and semantics

The exact static sequence is:

1. Lower-bound `this+0x98` (`mNounMap`) with `nounID` through `0x00e5c780`.
2. Compare the result only with `this+0x9c` (map end).
3. On end only: call the create callback, then `0x00ba8420`.
4. On a non-end result: load `node+0x14` as the record; no key equality check.
5. If `record+0x00` (`needsUpdate`) is nonzero, call the clear callback.
6. Walk `this+0x78` (`mNouns`) and call filter `(cGameData*, nounID)`.
7. Call add `(record*, cGameData*)` for accepted elements.
8. Clear `needsUpdate` and return the record.

The lower-bound/successor issue is material: if the requested key is absent but a greater key exists, the function does not insert. It can use the successor payload, and if stale, rebuild that payload with the requested noun ID. This is static behavior, not a runtime claim.

The returned record and its elements are borrowed at this boundary. `0x00b21340` performs no `AddRef` or `Release`. The sampled noun consumers also dereference a null record without a guard.

## `0x00ba8420`

This is best classified as a generic map insertion/`try_emplace`-style helper on the noun path, not as a noun-specific constructor:

- ECX is a map receiver.
- It searches by the supplied key pointer and uses `0x009215c0`/`0x00ba83a0` for tree insertion/rebalance.
- `0x00ba83a0` calls `0x00f473a0` for a 0x18-byte allocation and `0x009216a0` for linkage.
- Existing equal key: output iterator is written and inserted byte is `0`.
- Insertion path: output iterator is written and inserted byte is `1`.

`0x00b21340` ignores the output/inserted byte. The exact relationship between the create callback result and the object allocated inside `0x00ba8420` is not closed: the visible call arguments do not pass the create result into `0x00ba8420`. Do not collapse the two allocations into one ownership claim without a typed dataflow proof.

Duplicate handling is visible, but allocator failure, exception behavior, tree repair after failure, and the exact map template are unresolved.

## Callback thunks

| address | exact role | static behavior | ownership/failure |
|---|---|---|---|
| `0x00b21080` | create | Allocates 0x18 bytes through `0x00f473a0`; sets `needsUpdate=1` and begin/end/capacity to zero | Returns null on visible allocation-null path; no record release |
| `0x00d3d420` | clear | Reads begin/end and calls `0x00e25bd0`; releases each non-null element through vtable `+0x04`, then sets end back to begin | Releases vector elements, not the record; skips null elements |
| `0x00b236c0` | add | Calls `cGameData` vtable `+0x0c` with type token `0x901f1362`, SDK `Simulator::cCivilization`; AddRefs, appends, then Releases the temporary | One vector-owned intrusive reference for a successful cast; null input/cast is not an error return |
| `0x00b1e500` | filter | Calls vtable `+0x20` (`GetNounID`) and compares to the supplied noun ID | Read-only; no null-element guard |

`0x00b25f40` pushes the callbacks in reverse ABI order:

```text
create  0x00b21080
clear   0x00d3d420
add     0x00b236c0
filter  0x00b1e500
nounID  0x018c816a = GameNounIDs::kCivilization
```

It then scans the returned vector, calls `cGameData::GetPoliticalID` at vtable `+0x4c`, and returns the first matching raw pointer or null. It has no null record/element guard and no ownership transfer.

`0x00b25ca0` uses the same kCivilization callback set but returns `GetData()+0x04`, exposing the vector begin pointer.

## `0x00b25f40` and `0x00b25fb0`

`0x00b25f40` is a one-argument, caller-cleaned `ret 4` function:

```text
ECX noun-manager-layout context
stack +0x04 = political ID
```

It is not the SDK `GetPlayerCivilization` implementation. The SDK address `0x00b25f90` is an adjudicated tail alias inside `0x00b25f40`; the bytes there are the no-match epilogue.

`0x00b25fb0` is a separate no-argument bridge:

```text
push ecx
push esi
call 0x01021300
if empire != 0:
    read empire+0x84
    call 0x00b25f40(politicalID) with saved ECX
else:
    read saved ECX from [ESP+4] after the two pushes
restore and ret
```

The null path therefore returns the original `ECX` context value, not a caller-supplied stack word. The normal path is high-confidence kCivilization/cCivilization-compatible, but exact assignment to the SDK method remains medium because the null path returns a context-shaped value and the SDK address is contaminated.

### `ECX` provenance

The selected static evidence supports:

```text
0x00b3d300 -> mov ecx,eax -> 0x00b25fb0
```

Examples:

- `0x00bfbc21` `0x00b3d300`; `0x00bfbc28` `0x00b25fb0`.
- `0x00aec5b6` `0x00b3d300`; `0x00aec5bd` `0x00b25fb0`; later `0x00aece75` `0x00b3d400`.
- `0x00d0e706` `0x00b3d300`; `0x00d0e70d` `0x00b25fb0`; later `0x00d0e75b`/766 `0x00b3d400`.
- `0x00d100e0` `0x00b3d300`; `0x00d100e7` `0x00b25fb0`; later `0x00d10393`/39e `0x00b3d400`.

The committed metrics report all 100 distinct `0x00b25fb0` callers co-call `0x00b3d300`. Only three callers co-call `0x00b3d400`, and in each sampled body the getter call is separate from the `0x00b25fb0` receiver propagation. No `0x00b3d400 -> 0x00b25fb0` chain was found. Whether `DAT_0167eae0` and `DAT_0167eb60` alias remains unresolved.

## Central consumer `0x00bfbbf0`

`0x00bfbbf0` is a 1,928-byte unnamed function with one committed direct caller (`0x00ae6240`). It has ECX receiver/no explicit stack arguments and a plain return; exact SDK method identity is unresolved.

Static high-information paths:

```text
0x00bfbc21 0x00b3d300
0x00bfbc28 0x00b25fb0

0x00bfbd26 0x00b3d300
0x00bfbd2d 0x00b25ca0
0x00bfbd3d 0x00b3d300
0x00bfbd58 0x00b21340(
             create 0x00cd7d10,
             clear  0x00d3d420,
             add    0x00acdff0,
             filter 0x00b1e500,
             nounID 0x018c43e8 = kCity)
```

It then reads the kCivilization begin/end vector and the kCity vector, calls `cGameData::GetPoliticalID` on elements, and performs city/civilization/relationship operations. It repeatedly calls `0x00b3d300` before `0x00b25fb0` and directly calls `0x00b3d2c0` for relationship-manager-compatible state.

The central body does not visibly AddRef/Release the noun records in the inspected window. It demonstrates that the callbacks are selected by noun/category: the central kCity path uses `0x00cd7d10` and `0x00acdff0`, not the kCivilization `0x00b21080`/`0x00b236c0` pair.

## Preserved contradictions and unresolved limits

- The SDK address `0x00b212d0` is now explained as a split continuation, but the exported function record and SDK decompilation remain contaminated and are not edited.
- The real containing function `0x00b211e0` has noun/list/map maintenance mechanics but no exact SDK method name.
- `0x00b21340` lower-bound successor behavior is exact static behavior; whether the game relies on a key invariant that prevents harmful successor aliasing is not established.
- The create-result versus `0x00ba8420`-allocation ownership relation is unresolved.
- Allocation failure, exception, map erase, full invalidation, locking, and reentrancy remain unresolved.
- `0x00b25fb0` is mechanically the ECX bridge; exact SDK `GetPlayerCivilization` identity and the no-empire context return remain bounded ambiguities.
- `0x00bfbbf0` is statically a city/civilization orchestration consumer, but its exact SDK identity is unknown.

## Evidence paths

- `.spore-analysis/ghidra-exports/functions.tsv`
- `.spore-analysis/ghidra-exports/spore_sdk.xml`
- `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cGameNounManager__GetData.c`
- `knowledgegraph/triage/xrefs-2540f2ca.tsv`
- `knowledgegraph/triage/xrefs-2540f2ca.summary.json`
- `knowledgegraph/research/decomp-gap/sim-core-02.json`
- `knowledgegraph/research/decomp-gap/hold-infrastructure.json`
- `knowledgegraph/research/root-closure/track-d-noun-registry.json`
- `knowledgegraph/research/root-closure/track-e-empire-chain.json`
- `knowledgegraph/research/root-closure/cross-root-relationships.json`
- Read-only disassembly of `SPORE/SporeBin/SporeApp.exe` over the bounded ranges recorded in the JSON artifact.
