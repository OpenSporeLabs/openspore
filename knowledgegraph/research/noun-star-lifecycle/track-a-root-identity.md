# Track A — Noun/Star Root Identity Report

**Scope:** `00b3d300` / `DAT_0167eae0` and `00b3d2a0` / `DAT_0167eae4`, with the named/canonical comparators `00b3d400` / `DAT_0167eb60` and `00b3d3a0` / `DAT_0167eb0c`.

**Binary:** `SPORE/SporeBin/SporeApp.exe` 3.1.0.22, x86-LE 32-bit, image base `0x00400000`, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`.

**Research mode:** static/read-only. No Wine, runtime trace, differential run, Ghidra mutation, direct filesystem SPORE modification, shared JSON edit, executable edit, or implementation work was performed. Runtime observations are segregated below and are explicitly not claims about these roots.

## Executive answer

1. `00b3d300` returns the raw 32-bit value stored at `DAT_0167eae0`. It has no arguments, no callee, no allocation, no AddRef/Release, no validation, no lock, and no write. Its selected consumers use the result as a `cGameNounManager`-compatible receiver: `00bff408 -> 00b3d300`, `00bff426: mov ecx,eax`, and `00bff428 -> 00b21340`; `00b21340` reads the manager-shaped `mNounMap +0x98`, sentinel `+0x9c`, and `mNouns +0x78` fields. The precise pointee class, owner, publication, and equality with the canonical noun slot remain unresolved.

2. `00b3d2a0` returns the raw 32-bit value stored at `DAT_0167eae4`. Its selected consumers use the result as a `cStarManager`-compatible receiver: `00ba9370` reads the empire map at `+0x150` and end/sentinel at `+0x154`; `00b3d2c0` directly loads `DAT_0167eae4` into ECX and `00c4f030` reads `+0x204`, matching the SDK `mpRelationshipManager` field. It is not the named `Simulator::cStarManager::Get` accessor; that getter is `00b3d3a0 -> DAT_0167eb0c`.

3. The noun and star roots are distinct **services/paths**, and each noun/star alternate/canonical pair occupies distinct **physical storage**. Physical aliasing is rejected. Value aliasing is not established: `DAT_0167eae0 == DAT_0167eb60` and `DAT_0167eae4 == DAT_0167eb0c` remain open at every lifecycle point. No common publisher, equality check, replacement path, or root clear was recovered in the bounded static surface.

4. Manager construction, noun materialization/destruction, star map operations, star database replacement, and `SpacePlayerData` cache teardown are real static lifecycle surfaces, but none is joined to a root-slot publication or unpublication operation. The root pointer is therefore a borrowed raw observation, not a proven stable object identity or lifetime handle.

**Overall confidence:** high for the accessor mechanics, backing addresses, direct field compatibility, physical separation, and direct null behavior; medium for exact alternate pointee class; low/unresolved for ownership, publication, value equality, liveness, rebind order, and teardown identity. The root-closure synthesis correctly classifies `00b3d300` as `SUPPORTED` with alias/lifecycle open and `00b3d2a0` as `SUPPORTED` with alias/lifecycle open (`docs/analysis/simulator-root-closure.md:131-145`; `knowledgegraph/research/root-closure-f0e310e0.json:112-218`).

## Evidence and provenance

### Binary and static artifacts

- `docs/analysis/simulator-root-closure.md:1-18` fixes the static-only evidence boundary and identifies `00b3d300` and `00b3d2a0` as alternate manager-pointer accessors; `:20-28` preserves the alias/lifecycle and receiver ambiguities; `:90-92` identifies `00b3d300` as the highest-impact unresolved root.
- `knowledgegraph/research/root-closure-f0e310e0.json:49-60` records the unresolved pair-equality and lifecycle questions; `:93-97` defines the smallest separating experiment; `:112-166` and `:169-218` contain the machine-readable per-root contracts.
- `docs/analysis/simulator-shared-state-interface.md:1-15` states that the closure has no runtime trace; `:36-64` is the older conservative interface for both roots; `:94-129` keeps input, space, and manager roots separate; `:203-224` records the global slots as four-byte values.
- `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json:27-39` fixes the 11-root order; `:122-180` records the global forwarding helper; `:284-479` records the global slots and cGameNounManager/cStarManager layout projections. Its `runtime_evidence` is false at `:10-25`.
- `knowledgegraph/research/root-closure/followup-global-slots.md:11-35` reports the direct noun/star compatibility, four-slot table, no direct writer, and image-time zero-fill; `:39-100` gives the accessor bodies and canonical getters; `:102-143` gives the common-caller and raw canonical-thunk evidence; `:147-172` gives lookup/cache mechanics; `:199-245` gives the lifecycle negative result and remaining unknowns.
- `knowledgegraph/research/root-closure/track-a-service-identity.md:7-21` is the prior static adjudication; `:52-84` records receiver invariants and lifecycle negative; `:23-50` records representative call chains.
- `knowledgegraph/research/root-closure/cross-root-relationships.md:1-27` separates the shared Simulator substrate from the individual roots; `:37-53` gives the mechanical root metrics; `:178-190` gives the initialization/teardown negative and the proposed separating trace.
- `knowledgegraph/triage/xrefs-2540f2ca.tsv:96284-96289` contains the `00b3d300`/`00b3d400` co-call rows, including `00aebe90`; `:103660-103665` contains setup-body rows, including `00b60d80`; `:98973-99006` contains noun materialization/destruction xrefs; `:99085-99116` contains manager teardown and staged destroy xrefs. These are static reference rows, not runtime traces.

### Fresh read-only Ghidra queries

The following were queried against the already-open `SporeApp.exe` program without mutation:

- `00b3d300`: `MOV EAX,[0x0167eae0]; RET`.
- `00b3d2a0`: `MOV EAX,[0x0167eae4]; RET`.
- `00b3d400`: `MOV EAX,[0x0167eb60]; RET`, decompiled return type `cGameNounManager *`.
- `00b3d3a0`: `MOV EAX,[0x0167eb0c]; RET`, decompiled return type `cStarManager *`.
- Ghidra xrefs to `DAT_0167eae0`, `DAT_0167eb60`, `DAT_0167eae4`, and `DAT_0167eb0c` returned only the corresponding direct reads; `DAT_0167eae4` additionally has the direct read in `00b3d2c0`. The canonical star getter has one raw code xref at the unowned thunk `00b5ca50`; Ghidra’s named-function caller query returns zero because that thunk is not a named function.
- Byte-pattern searches returned only `E0 EA 67 01 @ 00b3d301`, `60 EB 67 01 @ 00b3d401`, `E4 EA 67 01 @ 00b3d2a1/00b3d2f2`, and `0C EB 67 01 @ 00b3d3a1`. This is a bounded executable-literal negative, not proof that computed, bulk, loader, external, or runtime publication is absent.
- Memory inspection of `0x0167eac0..0x0167eb1f` returned zero bytes. The root slots lie in the writable zero-fill tail of `.data`; this is image/layout evidence only, not runtime null evidence. The same boundary is stated in `followup-global-slots.md:22-35` and `blocker-a-primary.md:77-86`.
- Ghidra `cGameNounManager` layout: size `0x11c`; vptrs at `+0x00/+0x04/+0x08`, `mpAvatar +0x54`, `mpPlayerTribe +0x70`, `mpPlayer +0x74`, `mNouns +0x78`, `mNounMap +0x98`, `mObjects +0x10c`. Ghidra `cStarManager` layout: size `0x22c`; `mEmpires +0x150`, map end/sentinel `+0x154`, and `mpRelationshipManager +0x204`.

## Direct contracts

### `00b3d300` — alternate noun-manager-compatible root

**Mechanics and storage.** The body is exactly:

```text
00b3d300  mov eax, [DAT_0167eae0]
00b3d305  ret
```

The root returns a borrowed raw 4-byte value. It does not accept arguments, call a service locator, validate the result, AddRef/Release, allocate, lock, or mutate the slot. The Ghidra and JSON records agree on 1,097 direct callers, 1,941 canonical call edges, and 252 gameplay callers (`followup-global-slots.md:39-61`; `track-a-service-identity.json:55-93`).

**Why the return is noun-manager-compatible.** The high-information consumer is the `00bff2d0` window. The committed exact call-chain artifact records:

```text
00bff408  call 00b3d300
00bff426  mov ecx, eax
00bff428  call 00b21340
```

`00b21340` uses the receiver as the noun map owner: `this+0x98` is passed to the lower-bound helper, `this+0x9c` is the map end/sentinel, and `this+0x78` is walked as the noun list. Its returned value is a borrowed `tGameDataVectorT<cGameData>*` payload selected from the map, not a new interface object. The precise Ghidra `00b21340` body and callback shape are in `followup-global-slots.md:132-141` and `blocker-a-primary.md:130-152`; the SDK callback and field vocabulary is in `~/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/SubSystem/GameNounManager.h:62-114` and `:130-152`.

**Returned identity.** The strongest static classification is “alternate raw `cGameNounManager*` / noun-manager-compatible receiver.” The exact class identity is not promoted to a proof because:

- `00b3d400` is the named `Simulator::cGameNounManager::Get` accessor and returns the different `DAT_0167eb60`; Ghidra’s function prototype is `cGameNounManager *`, but the SDK function name is not proof that `00b3d300` is the same function or the same slot.
- The binary has no MSVC RTTI. Type archaeology explicitly treats SDK names, vtable candidates, and shared layouts as structural evidence, not a unique C++ hierarchy (`docs/analysis/type-archaeology.md:23-33`, `:60-70`, `:289-356`; `knowledgegraph/research/types/11-vtable-archaeology.md:1-23`).
- The local SDK calls `cGameNounManager` a singleton, but the binary exposes two noun storage words. The SDK wording is corroborating vocabulary only (`GameNounManager.h:62-74`; `blocker-a-primary.md:51-64`).

### `00b3d2a0` — alternate star-manager-compatible root

**Mechanics and storage.** The body is exactly:

```text
00b3d2a0  mov eax, [DAT_0167eae4]
00b3d2a5  ret
```

The root returns a borrowed raw 4-byte value. It is not the registry lookup and it is not the named canonical getter. It has no arguments, callee, allocation, validation, AddRef/Release, lock, or write. The prior static JSON records 314 direct callers, 510 canonical xref rows, and 101 gameplay callers (`track-a-service-identity.json:96-137`; `followup-global-slots.md:63-81`).

**Why the return is star-manager-compatible.** The selected consumer chain is independent of the accessor name:

- `00ba9370` takes the returned object as its manager receiver. Ghidra decompilation returns null for ID `-1`, calls the generic lower-bound helper with the map beginning at `this+0x150`, compares the result with `this+0x154`, and returns the node payload at `+0x14`. The SDK defines `EmpiresMap` and places `mEmpires` at `+0x150` (`StarManager.h:100-155`, `:270-331`).
- `00b3d2f0` is a direct read of `DAT_0167eae4` into ECX followed by a tail jump to `00c4f030`; `00c4f030` is exactly `MOV EAX,[ECX+0x204]; RET`. The SDK places `mpRelationshipManager` at `+0x204` (`StarManager.h:293-320`).
- The canonical `Simulator::cStarManager::Get` is `00b3d3a0 -> DAT_0167eb0c`, not `00b3d2a0 -> DAT_0167eae4` (`followup-global-slots.md:95-100`; `track-a-service-identity.md:15-21`).

The safe static identity is therefore “alternate raw `cStarManager*` or a layout-compatible manager pointer.” The exact owner, publication, and whether it is a phase-specific instance remain unresolved.

## Backing globals and physical storage

| Accessor | Global | Physical shape | Direct read sites | Direct store/clear found | Static status |
|---|---|---|---|---|---|
| `00b3d300` | `DAT_0167eae0` | 4-byte word at `0x0167eae0` | `00b3d300` | none in bounded scan | alternate noun path; alias/lifecycle open |
| `00b3d400` | `DAT_0167eb60` | 4-byte word at `0x0167eb60` | `00b3d400` | none in bounded scan | named canonical noun path |
| `00b3d2a0` | `DAT_0167eae4` | 4-byte word at `0x0167eae4` | `00b3d2a0`, `00b3d2c0` | none in bounded scan | alternate star path; alias/lifecycle open |
| `00b3d3a0` | `DAT_0167eb0c` | 4-byte word at `0x0167eb0c` | `00b3d3a0` | none in bounded scan | named canonical star path |

The four words are distinct. That rejects **physical aliasing**, not **value equality**. `docs/analysis/simulator-root-closure.md:20-28`, `followup-global-slots.md:15-35`, `blocker-a-primary.md:70-100`, and `blocker-a-adversarial.md:39-72` all preserve this distinction.

The image-time zero bytes do not establish that the roots are null in a running process. The architecture evidence policy explicitly rejects zero image bytes as runtime null proof (`knowledgegraph/research/architecture-resolution.json:62-74`; `blocker-a-primary.md:77-86`).

## Aliasing, distinctness, and path relationships

### Noun pair: `DAT_0167eae0` versus `DAT_0167eb60`

**Established distinct path.** `00b3d300` reads `DAT_0167eae0`; `00b3d400` reads `DAT_0167eb60`. The word locations are distinct and direct byte-pattern searches find no common store or equality operation. `00b3d300` is therefore not the same physical storage as the canonical getter.

**Co-use is not equality.** Eleven functions directly call both noun accessors. `00aebe90` uses the alternate for the noun/player/game-data path and later calls the canonical noun getter, but does not compare the returned pointers (`followup-global-slots.md:104-121`; `xrefs-2540f2ca.tsv:96575-96589`). This proves two active access paths, not a shared pointer value.

**High fan-in is not ownership.** The alternate noun accessor has 1,097 direct callers versus 43 for the canonical accessor. This asymmetry may indicate an operational path and a compatibility/legacy path, but it does not prove that either root is stale, live, canonical, or owner-authoritative. The same warning is recorded in `track-a-service-identity.md:52-57` and `blocker-a-primary.md:100-100`.

### Star pair: `DAT_0167eae4` versus `DAT_0167eb0c`

The same physical/value distinction applies. The committed xref export has no named canonical-star caller, but raw executable disassembly contains a 14-byte thunk at `00b5ca50` that calls `00b3d3a0`, loads the returned vtable, and dispatches slot `+0x28` (`followup-global-slots.md:123-143`). This is a concrete canonical consumer, so sparse committed fan-in cannot prove that `DAT_0167eb0c` is dead. The exact owner and caller lifecycle of `00b5ca50` remain unresolved.

### Cross-domain distinctness

The noun and star roots are not interchangeable services. A representative multi-domain consumer uses `00b3d300` for the noun/current-player context and `00b3d2a0` for a separate star/space operation (`followup-global-slots.md:174-197`; `track-a-service-identity.md:39-50`). `00b3d350` is a third, independently named `cGameInputManager*` accessor over `DAT_0167eaf8`, not an alias of either target root (`docs/analysis/simulator-shared-state-interface.md:81-94`; `knowledgegraph/research/root-closure-f0e310e0.json:280-318`).

The shared `Simulator::sSpacePlayerData` container is an authoritative backing structure for player, context, and empire-cache fields, not proof that the manager slots, input state, and space state share one object (`docs/analysis/simulator-root-closure.md:94-129`; `cross-root-relationships.md:73-108`).

## Initialization and publication

### Root publication: unresolved

No direct root writer was found in the pinned executable surface. The root regions are in writable `.data` beyond the raw initialized image bytes, and the only exact address patterns are the accessor/read sites. The prior reports therefore classify the result as a **bounded negative**, not “no publisher exists” (`followup-global-slots.md:22-35`; `blocker-a-primary.md:79-100`; `blocker-a-adversarial.md:62-76`).

A fresh Ghidra query found `00b60d80` as a caller of `00b3d2a0` at `00b634ab`. The surrounding instructions are:

```text
00b634a0  jz 00b634ab
00b634ab  call 00b3d2a0
00b634b0  mov ecx, eax
00b634b2  call 00c2e4e0
```

This is evidence that a large setup/composition body consumes the alternate star accessor during a control-flow path. It is **not** evidence that `00b3d2a0` initializes `DAT_0167eae4`, because the call result is passed onward and no target-word store or equality operation is shown. The canonical xref row is `xrefs-2540f2ca.tsv:103866`.

The noun manager construction surface is `00b232b0`: it writes three interface vptrs and initializes refcount/mode/list/map/object fields. Its direct caller and vtable xrefs identify a manager construction/teardown family, but there is no join from that object to `DAT_0167eae0` or `DAT_0167eb60` (`blocker-a-primary.md:102-115`; Ghidra `FUN_00b232b0` result in this pass). The static SDK names `cGameNounManager::CreateInstance` and `DestroyInstance`, but the binary body boundary is at `00b20c60` / `00b225d0` rather than the SDK anchors (`GameNounManager.h:62-86`; `blocker-a-primary.md:117-128`).

### Manager-local materialization is not root publication

`00b20c60` creates a noun through a factory, inserts a node into the manager’s `mObjects`/`mNouns` structures, assigns an object identifier, and invalidates the noun cache through `00b201a0`. `00b225d0` stages destruction, releases a temporary reference, unlinks/cleans the object, and invalidates the noun cache. These paths support manager-owned live noun materialization, but no root-global store or clear appears in them (`blocker-a-primary.md:117-165`; `xrefs-2540f2ca.tsv:98973-99006`).

The SDK and local data model explicitly separate live noun registry/cache state from persistence. `cGameNounManager` is runtime reconstruction state; a live noun or its manager pointer is not a durable save identity (`docs/analysis/gameplay-data-model.md:252-267`, `:294-330`; `docs/analysis/serialization-model.md:335-360`).

### Star setup and persistence surfaces

`00ba9370` and `01021300` establish a manager-local star/empire cache path, not manager-root publication:

```text
current player ID = sSpacePlayerData+0x18
cached pointer     = sSpacePlayerData+0x1c
on hit             = compare cached cEmpire+0x84
on miss            = 00b3d2a0 -> 00ba9370
                     AddRef(new); store; Release(old)
```

The lower-bound result can be a greater successor because the wrapper checks only the map end, not the returned key. `01021300` does not perform a post-lookup ID equality check on the miss path (`followup-global-slots.md:158-172`; `00ba9370` and `01021300` Ghidra decompilation in this pass; `docs/analysis/simulator-shared-state-interface.md:143-156`, `:188-201`).

`00bb4ba0` is a bounded `stars.db.tmp` write and `stars.db` replacement path. It serializes star/space state and then calls the replacement helper, but it does not publish or clear `DAT_0167eae4` or `DAT_0167eb0c` (`blocker-a-primary.md:217-228`; `docs/analysis/serialization-model.md:274-299`, `:397-410`).

## Teardown and identity stability

### Manager/object teardown is recovered; root unpublication is not

`00b22440` resets the noun manager’s vtables, releases vector/list/map state, clears selected fields, and restores base vtables. It is a manager teardown surface, not proof of a root-slot clear or final service release (`blocker-a-primary.md:154-165`, `:378-390`; fresh Ghidra decompilation of `FUN_00b22440`).

For star/empire state, `00bad7a0` releases an intrusive map payload selected by the lower-bound path and erases the map node. It does not clear `sSpacePlayerData+0x1c`. `01022460` separately clears active planet, active star, and cached empire, resets the player ID, and releases those fields; it does not clear either star root. The map erase and player-cache invalidation are therefore separate lifecycle levels (`00bad7a0` and `01022460` Ghidra decompilation; `blocker-a-primary.md:185-202`; `architecture-resolution.md:73-80`).

App mode teardown is also a separate state-machine surface: `SetActiveModeAt` validates the index and the transition helper performs old `OnExit`, active-index write, exit announcement, new `OnEnter`, and enter announcement (`docs/analysis/gameplay-state-machines.md:81-120`; `knowledgegraph/research/state-machines/ui-gameplay.json:1-34`). This is static control/data-flow evidence for a mode lifecycle, not a root-slot publisher or runtime ordering observation. The semantic blueprint keeps App mode, Simulator strategy, input, SpaceContext, scenario, and Cell axes separate (`docs/analysis/semantic-blueprint.md:943-955`).

### Stability contract

The roots provide a snapshot of the current global word at accessor time, not a stable identity handle:

- no root-side AddRef or ownership transfer;
- no null check or failure sentinel;
- no generation/epoch field;
- no validation that a previously returned pointer remains live;
- no direct root rebind/clear path recovered.

A caller retaining a returned raw pointer across a potential manager teardown or allocator reuse has no static guarantee. Even if a later read returns the same numeric address, that is not proof of the same object. The adversarial review correctly requires pointer values plus a lifetime/generation marker before treating equality as object identity (`blocker-a-adversarial.md:74-79`, `:186-203`).

## Null and failure behavior

### Root accessors

Neither `00b3d300` nor `00b3d2a0` has a null guard or special failure return. Each returns the raw word, including zero if the slot is zero at the time of the read. Image-time zero is not runtime null evidence.

### Noun materialization path

`00b21340` assumes a usable manager receiver: it computes `receiver+0x9c`, passes the map at `receiver+0x98` to the lower-bound helper, and reads/walks manager list state. A null or already-invalid alternate noun pointer is not converted to a safe null result by the root or wrapper. Allocation, insertion, callback, and partial-materialization failure behavior is not fully closed; the callback path can allocate a record and the map helper can insert separately, but the complete ownership/failure join is unresolved (`followup-global-slots.md:130-141`; `blocker-a-primary.md:130-152`, `:364-374`).

The noun path uses four callback pointers plus noun ID, not “five callbacks.” The older five-callback wording is superseded by the direct ABI/SDK alignment (`architecture-resolution.md:45-63`; `blocker-a-adversarial.md:130-149`).

### Star lookup/cache path

`00ba9370` has two explicit null results: ID `-1` returns null and a lower-bound end iterator returns null. It does not check a null manager receiver before using `this+0x150/+0x154`. Missing exact membership is not a failure sentinel: an absent ID below a greater successor can return that successor. `01021300` returns null for player ID `-1`, but on a cache miss it directly consumes the manager returned by `00b3d2a0`, stores a possibly null lookup result, and releases the old cache. Its `SpacePlayerData` pointer and manager root are not protected by a universal null guard (`00ba9370` and `01021300` Ghidra decompilation; `followup-global-slots.md:147-172`).

### Other non-target receiver exception

`00bff2d0` is not evidence that `00b1fdb0` is globally a noun-root accessor. In the exceptional `00bff2d0:00bff3ad-00bff3b4` window, `01002bd0` supplies `DAT_016dc0fc` before `00b1fdb0`; this separate receiver has its own lifecycle and is rejected as either noun root (`architecture-resolution.md:45-61`; `root-closure-f0e310e0.json:54-60`, `:136-166`). It reinforces that receiver provenance must be tracked per call path.

## Competing hypotheses

### H1 — one shared owner; alternate and canonical values always equal

**Prediction:** a common publisher writes both noun words and both star words; publication/rebind/teardown is paired; no null, stale, unequal, or allocator-reuse window exists; consumers through either path observe the same owner-local state.

**Evidence for:** SDK singleton wording; both accessors return manager-shaped pointers; noun and star fields are compatible with the same class families; some consumers use alternate and canonical paths in one body.

**Evidence against:** four physical words; no direct common publisher, equality check, or teardown store; canonical and alternate callers are asymmetric; the canonical star getter has a concrete but unowned raw thunk; no runtime equality observation exists.

**Assessment:** unresolved. This hypothesis cannot be selected from names or co-call topology. `architecture-resolution.json:76-100` and `:103-128`; `blocker-a-adversarial.md:203-293`.

### H2 — phase-specific or independently rebound managers

**Prediction:** a transition produces an unequal or one-sided null/stale window; alternate and canonical consumers observe different map/list/cache state; rebind or teardown order differs by root.

**Evidence for:** distinct writable words; alternate/canonical fan-in asymmetry; current-player cache explicitly uses the alternate star slot; noun and star objects have their own construction, materialization, and teardown surfaces.

**Evidence against:** no concrete writer, equality operation, runtime trace, or observed unequal window was recovered. The zero-fill image and no-writer scan are not a phase model.

**Assessment:** unresolved and architecture-relevant. A phase-specific result would require explicit epoch/rebind and cache rules, but those rules are a clean-room hypothesis, not a recovered original lifecycle. `blocker-a-primary.md:257-321`.

### H3 — one accessor is stale/legacy or compatibility-only

**Prediction:** the alternate tracks the active manager while the canonical remains old/null, or vice versa; canonical consumers see stale manager-local state; teardown of the active root does not affect the other.

**Evidence for:** 1,097 versus 43 noun callers and 314 versus a sparse/unowned canonical-star thunk; the alternate star slot is used by the current-player cache path.

**Evidence against:** canonical noun callers exist; the raw canonical-star thunk dispatches through the returned vtable; no liveness or stale-object observation exists.

**Assessment:** unresolved. Low fan-in cannot prove deadness or stale storage. `followup-global-slots.md:123-143`; `blocker-a-primary.md:291-305`.

### H4 — opaque computed/bulk/external publication

**Prediction:** a computed store, table/relocation path, bulk-copy helper, service registration helper, loader, or external component writes the root words without a literal address reference; publication may be equal or unequal.

**Evidence for:** the slots are writable `.data` locations beyond raw initialized image contents; the negative scan covers only direct literal references; a large setup body consumes the alternate accessor.

**Evidence against:** no concrete computed target, table base, bulk-copy source/destination, or external publication join has been recovered. Opaque publication is possible, not proven or proven leading.

**Assessment:** unresolved. The adversarial review explicitly rejects promoting “no direct writer” into either immutability or a particular opaque publisher (`blocker-a-adversarial.md:47-76`).

### H5 — manager-local lifecycle is mistaken for root lifecycle

**Prediction:** noun create/destroy, star map erase, `stars.db` replacement, or `SpacePlayerData` teardown clears a root word or destroys the object returned by a root.

**Evidence for:** each manager has direct construction, object, map, database, or teardown bodies; the stars database path is explicitly bounded and may look like persistence of manager state.

**Evidence against:** inspected manager/object/cache teardown bodies do not target `DAT_0167eae0`, `DAT_0167eb60`, `DAT_0167eae4`, or `DAT_0167eb0c`; live noun registry and star database layers are separate from root-slot storage. The data model and serialization model explicitly distinguish runtime registries, persistent records, and raw root pointers (`gameplay-data-model.md:294-374`; `serialization-model.md:335-380`).

**Assessment:** rejected as a root-publication/lifecycle claim; retained as evidence of owner-local object lifecycle only.

## Runtime evidence — separate

**No positive runtime evidence exists for `00b3d300`, `00b3d2a0`, `DAT_0167eae0`, `DAT_0167eb60`, or their pointee lifetime.** The closure artifact sets `runtime_evidence=false` and explicitly says no OBSERVED or VERIFIED claim is made (`docs/analysis/simulator-root-closure.md:1-3`; `root-closure-f0e310e0.json:7-12`, `:27-35`).

Repository runtime material about application startup or `IAppSystem` access is not evidence for these roots. No synchronized capture of all four words, vtable pointers, object generations, manager map/list sizes, noun create/destroy events, empire cache refresh, or teardown was performed. Therefore the following remain static hypotheses rather than runtime facts:

- whether the two noun words are equal;
- whether the two star words are equal;
- whether either pair has a one-sided null or rebind window;
- whether allocator reuse can create a false numeric equality;
- first writer, replacement order, and final unpublication order;
- whether a root remains borrowed after manager teardown;
- exact runtime failure behavior when a slot is null.

The smallest positive observation remains a synchronized read-only trace around a naturally reachable mode transition, noun/star construction, noun create/destroy, empire erase/cache refresh, and teardown. One equal snapshot cannot prove H1; one unequal snapshot with the corresponding object lifetime can reject unconditional H1. The required matrix is already specified in `blocker-a-primary.md:332-344` and `blocker-a-adversarial.md:268-279`.

## Conclusion

**Resolved with high confidence:** `00b3d300` is a no-argument raw borrowed global-word accessor over `DAT_0167eae0`; its selected receiver contract is `cGameNounManager`-compatible. `00b3d2a0` is a no-argument raw borrowed global-word accessor over `DAT_0167eae4`; its selected receiver contract is `cStarManager`-compatible. Noun and star are separate service paths. The four target words are physically distinct.

**Unresolved with high consequence:** alternate/canonical value equality, root publication and replacement, exact owner/lifetime, nullability guarantees, rebind/phase identity, and root teardown order. The correct compatibility-safe characterization is four separate opaque observation ports with no implicit equality or fallback. That is a clean-room safety boundary, not a claim that the original has four owners or four recovered lifecycle mechanisms (`docs/analysis/architecture-blockers.md:73-89`; `docs/analysis/semantic-blueprint.md:961-979`).

The highest-impact contradiction remains `00b3d300` / `DAT_0167eae0` versus `DAT_0167eb60`: the alternate noun slot is the dominant operational path and is directly used as a noun-manager receiver, but the binary does not prove that it is the canonical `cGameNounManager::Get` slot or the same object. The star pair has a parallel but independently lower-impact unresolved publication/equality relation. No claim of singleton identity, phase stability, or durable pointer identity is justified until a publisher/lifecycle trace or equivalent static dataflow is recovered.

## Authoritative source index

- Root closure: `docs/analysis/simulator-root-closure.md`; `knowledgegraph/research/root-closure-f0e310e0.json`.
- Shared-state interface: `docs/analysis/simulator-shared-state-interface.md`; `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json`.
- Direct root follow-up: `knowledgegraph/research/root-closure/followup-global-slots.md`; `track-a-service-identity.md/.json`; `cross-root-relationships.md/.json`.
- Architecture resolution and blocker: `docs/analysis/architecture-resolution.md`; `knowledgegraph/research/architecture-resolution.json`; `docs/analysis/architecture-blockers.md`; `knowledgegraph/research/architecture-blockers/blocker-a-primary.md`; `blocker-a-adversarial.md`.
- Semantic blueprint: `docs/analysis/semantic-blueprint.md`.
- Gameplay and persistence: `docs/analysis/gameplay-data-model.md`; `docs/analysis/serialization-model.md`; `knowledgegraph/research/data-model/10-serialization.json`.
- State machines: `docs/analysis/gameplay-state-machines.md`; `knowledgegraph/research/gameplay-state-machines.json`; `knowledgegraph/research/state-machines/ui-gameplay.json`; `temporal-semantics.json`.
- Type/vtable archaeology: `docs/analysis/type-archaeology.md`; `knowledgegraph/research/types/11-vtable-archaeology.md`; `12-field-archaeology.md`.
- SDK corroboration: `~/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/SubSystem/GameNounManager.h`; `StarManager.h`; `SpacePlayerData.h`; `~/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/cGameData.h`; `cStar.h`; `cStarRecord.h`; `NounClassFactories.h`.
