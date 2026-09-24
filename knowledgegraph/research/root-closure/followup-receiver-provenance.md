# Follow-up receiver provenance

## Scope and method

Phase-0 Root Closure follow-up for `00b1fdb0` and `00b25fb0`, using the requested windows:

`00d2e380`, `00d2e4a0`, `00d2e580`, `00d2e720`, `00d2e8a0`, `00d39360`, `00aebe90`, `00bdde70`, `00d06270`, `00bf9820`, `00bff2d0`, `00cfbc10`.

Evidence is committed static material plus read-only `objdump -d -Mintel` disassembly of `SPORE/SporeBin/SporeApp.exe`. The connected Ghidra bridge had no open program; no Ghidra mutation or live decompilation was used. No Wine, runtime, source, `SPORE/`, historical, or Phase-0 interface edit was made.

Binary: `SporeApp.exe` 3.1.0.22, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`; analysis snapshot `f0e310e0`; canonical xrefs `2540f2ca`.

## Executive conclusions

- `00b1fdb0` is still a raw receiver-field read: `mov eax,[ecx+0x54]; ret`.
- The selected call sites do not show a direct `00b3d400 -> DAT_0167eb60 -> ECX -> 00b1fdb0` chain.
- `00b3d300` is the dominant selected receiver source. Ten of eleven selected `00b1fdb0` calls and all fourteen selected `00b25fb0` calls use `00b3d300`'s `DAT_0167eae0` return.
- The one exception is `00bff2d0:00bff3b4`, where `ECX` comes from the return of `01002bd0`; that receiver remains unresolved.
- `00b3d400` is a committed `cGameNounManager::Get` accessor for `DAT_0167eb60`, but its selected use in `00aebe90` is a separate branch and is not the receiver of either target family.
- `00b1fd50` supplies a strong direct `owner+0x54` replacement writer: AddRef new, store, Release old. It is evidence for probable `cGameNounManager::mpAvatar`, but it is not the committed SDK `SetAvatar` address `00b1fca0`, which is adjudicated dead.

## Receiver classification

| window | target | selected callsite(s) | last ECX source | classification |
|---|---|---|---|---|
| `00d2e380` | `00b1fdb0` | `00d2e399` | `00b3d300@00d2e392 -> DAT_0167eae0` | context |
| `00d2e4a0` | `00b1fdb0` | `00d2e4c1` | `00b3d300@00d2e4ba -> DAT_0167eae0` | context |
| `00d2e580` | `00b1fdb0` | `00d2e58b` | `00b3d300@00d2e584 -> DAT_0167eae0` | context |
| `00d2e720` | `00b1fdb0` | `00d2e751` | `00b3d300@00d2e74a -> DAT_0167eae0` | context |
| `00d2e8a0` | `00b1fdb0` | `00d2e93e` | `00b3d300@00d2e937 -> DAT_0167eae0` | context |
| `00d39360` | `00b1fdb0` | `00d393cf`, `00d39459`, `00d394e3`, `00d39509`, `00d395cc` | each preceded by `00b3d300 -> mov ecx,eax` | context |
| `00bff2d0` | `00b1fdb0` | `00bff3b4` | `01002bd0@00bff3ad -> mov ecx,eax` | unresolved |
| `00aebe90` | `00b25fb0` | `00aec5bd` | `00b3d300@00aec5b6 -> DAT_0167eae0` | context |
| `00bdde70` | `00b25fb0` | `00bde22f` | `00b3d300@00bde228 -> DAT_0167eae0` | context |
| `00bf9820` | `00b25fb0` | `00bf985d` | `00b3d300@00bf9856 -> DAT_0167eae0` | context |
| `00bff2d0` | `00b25fb0` | `00bff3f0`, `00bff500`, `00bff576`, `00bff5ad`, `00bff5d7`, `00bff60e` | each preceded by `00b3d300 -> mov ecx,eax` | context |
| `00cfbc10` | `00b25fb0` | `00cfc39c`, `00cfc3f7`, `00cfc446`, `00cfc797` | each preceded by `00b3d300 -> mov ecx,eax` | context |
| `00d06270` | `00b25fb0` | `00d06298` | `00b3d300@00d06291 -> DAT_0167eae0` | context |

`context` means the selected dataflow reaches a shared context/owner candidate, not that the candidate is proven to be `cGameNounManager`.

## Root mechanics

### `00b1fdb0`

```text
00b1fdb0: mov eax,DWORD PTR [ecx+0x54]
00b1fdb3: ret
```

The function itself does not call a manager getter, read `DAT_0167eb60`, allocate, lock, AddRef, or Release. The result remains a borrowed raw 32-bit value. The existing creature-layout evidence still supports the returned value being an avatar/current-creature pointer.

### `00b25fb0`

```text
push ecx
push esi
mov esi,ecx
call 01021300
...
mov ecx,esi
call 00b25f40
```

`ESI` preserves the incoming context. `00b25fb0` does not call `00b3d400`; its noun-registry path is `00b25f40 -> 00b21340`. On a null empire it returns the caller stack fallback, as already established in Track E.

## Manager getters and globals

| getter | body/global | selected use | target relation |
|---|---|---|---|
| `00b3d300` | `mov eax,ds:0x167eae0; ret` | dominant source for both target families | shared context/owner candidate |
| `00b3d2a0` | `mov eax,ds:0x167eae4; ret` | `00aebe90`, `00cfbc10`; used by `00ba9370` and `00ba6dc0` | separate cStarManager-compatible registry owner candidate |
| `00b3d400` | `mov eax,ds:0x167eb60; ret` | `00aebe90:00aece75 -> 00e14c10` | named noun-manager getter, not a target receiver in the selected calls |
| `00b3d3a0` | `mov eax,ds:0x167eb0c; ret` | no selected target-window call found | SDK-named alternate cStarManager accessor; alias unresolved |
| `00b3d350` | `mov eax,ds:0x167eaf8; ret` | `00bf9820`, `00bff2d0`, `00cfbc10` | separate `cGameInputManager` state |
| `00b3d3e0` | `mov eax,ds:0x167eb24; ret` | `00bff2d0`, `00cfbc10` | unnamed raw global getter; no target role shown |
| `00b3d380` | `mov eax,ds:0x167eb04; ret` | `00aebe90`, `00cfbc10` | unnamed raw global getter; no target role shown |
| `00b3d490` | `mov eax,ds:0x167eb40; ret` | `00aebe90` | result stored locally; no target role shown |

The whole executable disassembly reference scan found only one direct reference to `DAT_0167eb60`:

```text
00b3d400: mov eax,ds:0x167eb60
```

No direct executable store to `DAT_0167eb60` was found. This does not establish initialization or teardown; it only establishes the absence of a direct static writer in the scanned image.

## `owner+0x54` write and avatar lifetime

The strongest direct writer found is `00b1fd50`:

```text
00b1fd50: push ebx
00b1fd51: mov ebx,ecx
00b1fd53: mov eax,DWORD PTR [ebx+0x54]
...
00b1fd66: mov esi,DWORD PTR [esp+0x10]
...
00b1fd83: mov eax,DWORD PTR [esi]
00b1fd85: mov edx,DWORD PTR [eax]
00b1fd87: mov ecx,esi
00b1fd89: call edx
00b1fd8b: mov DWORD PTR [ebx+0x54],esi
...
00b1fd92: mov eax,DWORD PTR [edi]
00b1fd94: mov edx,DWORD PTR [eax+4]
00b1fd97: mov ecx,edi
00b1fd99: call edx
```

Mechanics:

1. Save the incoming owner in `EBX`.
2. Load the old value at `owner+0x54`.
3. Load the new value from the caller stack argument.
4. Call virtual slot `+0x00` on a non-null new value.
5. Store the new raw address at `owner+0x54`.
6. Call virtual slot `+0x04` on a non-null old value.

Committed static callers show the same context source before this writer:

- `00c09af0 -> 00b3d300 -> 00c09af5: mov ecx,eax -> 00c09af7: call 00b1fd50`.
- `00ef1244 -> 00b3d300 -> 00ef1249: mov ecx,eax -> 00ef124b: call 00b1fd50`.

This is strong `mpAvatar` replacement/lifetime evidence because the SDK declares `cGameNounManager::mpAvatar` at `+0x54` as an `intrusive_ptr<cCreatureAnimal>`, and the writer performs reference-managed replacement.

The SDK address `00b1fca0` for `SetAvatar` is not a function and has no xrefs in the committed boundary repair. Do not mechanically merge `00b1fca0` with `00b1fd50`; classify `00b1fd50` as the direct writer with probable `mpAvatar` identity, not as a confirmed exact SDK function entry.

A broad scan found many unrelated stores at object offset `+0x54`, including initialization-looking stores. They were not counted as `cGameNounManager::mpAvatar` because no selected target dataflow or matching owner layout classified their receivers.

## Remaining gaps

1. Resolve whether `DAT_0167eae0` aliases, wraps, or differs from `DAT_0167eb60` and `DAT_0167eb0c`.
2. Resolve `01002bd0` in `00bff2d0` and classify the sole non-`00b3d300` `00b1fdb0` receiver.
3. Adjudicate `00b1fd50` against the dead SDK `00b1fca0` address and bind it formally to the noun-manager owner if possible.
4. Find the initialization, replacement, and teardown path for `DAT_0167eb60`; no direct writer to that global was found.
5. Keep `DAT_0167eae0` as context/owner-candidate in Phase-0; do not promote it to `cGameNounManager` solely from target co-call frequency.

## Evidence boundary

Committed root-closure tracks and triage/xref exports supplied the prior static contracts. Read-only disassembly supplied the exact `ECX` definitions and the `00b1fd50` store. No runtime, Wine, source, `SPORE/`, historical, or Phase-0 interface edit was made.
