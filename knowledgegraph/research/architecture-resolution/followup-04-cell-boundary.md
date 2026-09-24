# Follow-up 04 — Cell lifecycle boundary observation

**Status:** `BOUNDED_SUPPORTED`  
**Program:** `SporeApp.exe` 3.1.0.22, explicit read-only Ghidra observation  
**Scope:** `cCellGFX` / `mGFXObjectIndex` detach and rebuild, `cCellGame+0x411c`, `cCellObjectData+0x108`, despawn, stage reload, `OnExit`, `Dispose`, and `cCellSerializableData` classification.

## Verdict

A **static in-place per-cell GFX association seam exists**, but no single straight-line invocation was proven to detach and rebuild the association while retaining the same cell. The same `cCellObjectData`/pool identity is retained across the separate detach and rebuild branches. Despawn and stage reload are identity-destructive.

```text
FUN_00e7c8c0
  -> FUN_00e78c00
       -> FUN_00e66010       detach existing GFX record
       or
       -> FUN_00e6d8f0       allocate and attach a new GFX record
            -> FUN_00e5ce90  initialize reciprocal cell association
```

The two calls in `FUN_00e78c00` are mutually exclusive: detach occurs when `cCellObjectData+0x248` is present; rebuild occurs when the field is zero. Therefore the recovered result is **same identity across separate operations**, not a proven atomic detach→rebuild transaction.

`FUN_00e780a0` is different: it detaches the GFX association but always releases the input `cCellObjectData` pool object. `FUN_00e7fd00` clears the avatar index, drains the old cell pool, detaches each GFX association, releases each old cell, and then performs setup/population work. Neither retains the old cell identity.

## Structure ownership

| Location | Recovered owner | Classification | Boundary |
|---|---|---|---|
| `cCellGame+0x411c` | `cCellGame.mAvatarCellIndex` | Simulation identity | Avatar/player Cell pool index; not a GFX pointer |
| `cCellObjectData+0x00` | `mObjectPoolIndex` | Simulation identity | Same object returned by the cell pool |
| `cCellObjectData+0xfc` | `mModelKey` (`ResourceKey`) | Persistent content identity | Model/content key, separate from GFX |
| `cCellObjectData+0x108` | `mCellResource` (`cCellDataReference<cCellCellResource>*`) | Content-reference boundary | Runtime reference to Cell resource |
| `cCellObjectData+0x244` | `mHealthPoints` | Gameplay state | Simulation-owned health |
| `cCellObjectData+0x248` | `mGFXObjectIndex` | Presentation association | Replaceable GFX pool index |
| `cCellObjectData+0x358` | `mScale` | Gameplay/stage state | Simulation/stage state |
| `cCellObjectData+0x35c` | `mpQuery` | Simulation state | Query ownership, not presentation |
| `cCellGFX+0x168` | `mCellGFXObjects` | Presentation pool | Per-cell GFX records |
| `cCellGame+0x5190` | `mpSerializableData` | Cross-boundary persistence candidate | Mode-specific serializable state |
| `cCellUI` | `mRollovers` and UI/layout state | Presentation/UI | Separate service owner |

`cCellDataReference_` is 16 bytes: instance ID, serializer pointer, resolved resource pointer, and a counter. Its `Create` helper deduplicates by instance ID plus serializer context. The Cell object's `+0x108` is therefore a runtime resource-reference boundary, not a GFX handle and not a raw Cell content record.

`cCellSerializableData` is a 236-byte serializable/refcount object. Its constructor allocates `0xec` bytes and installs serializable vtables. It is distinct from the live `cCellObjectData` pool and from Cell content records.

## Positive detach/rebuild seam

### Detach: `FUN_00e66010` — `0x00e66010`

The implicit EAX input is a `cCellObjectData` pool index; disassembly uses the `cCellGame` cell pool at `sCellGame+0x1c`.

1. Resolve the existing cell from the cell pool.
2. Read `cCellObjectData+0x248`.
3. Resolve that index through `cCellGFX.mCellGFXObjects` at `sCellGFX+0x168`.
4. Write zero to `cCellObjectData+0x248`.
5. Clean the GFX record with `FUN_00e65ad0`.
6. Release the GFX record pool entry.

The helper does **not** release the `cCellObjectData` pool entry. Its direct callers are `FUN_00e780a0`, `FUN_00e78c00`, and `FUN_00e7fd00`.

### Rebuild: `FUN_00e6d8f0` — `0x00e6d8f0`

1. Resolve the existing `cCellObjectData` from its cell pool index.
2. Allocate a new GFX record with `FUN_00b72160`.
3. Write the new GFX pool index to `puVar3[0x92]`, which is `cCellObjectData+0x248`.
4. Call `FUN_00e5ce90` with the new GFX index and the existing cell's `mObjectPoolIndex`.
5. `FUN_00e5ce90` writes the cell index into the new GFX record at its reciprocal `+0x0c` field.
6. Replay idle animation on the same `cCellObjectData`.

`FUN_00e6d8f0` has one direct caller: `FUN_00e78c00`, and that call is reached when the existing cell's `+0x248` is zero.

### Caller seam: `FUN_00e7c8c0` / `FUN_00e78c00`

`FUN_00e7c8c0` iterates the cell pool and passes each live `cCellObjectData*` to `FUN_00e78c00`. The positive branches do not release that cell. `FUN_00e78c00` therefore provides a bounded per-cell presentation refresh seam:

- Existing `+0x248`: detach the GFX record and keep the cell object.
- Missing `+0x248`: attach a new GFX record to the same cell object.

This is a static path, not a runtime trace. The evidence does not prove that all absent-GFX cases take the rebuild branch, nor that the detach and rebuild occur in one invocation.

## Despawn and replacement: `FUN_00e780a0`

`FUN_00e780a0` receives a cell pool index and performs these operations:

1. Resolve the cell.
2. If the index equals `sCellGame+0x411c`, clear the avatar index to zero.
3. Remove query/linked state and release related query handles.
4. If `+0x248` is nonzero, detach the GFX record through `FUN_00e66010`.
5. In scale-replacement mode, call `FUN_00e67890` and possibly `FUN_00e771d0`. These paths use the old cell's `+0x108` resource reference and `+0xfc` model key for effect/child/replacement work.
6. Call `FUN_00b72260(param_1)`, releasing the input `cCellObjectData` pool object.

The function has 27 xrefs from 23 callers, including death, interaction, population, and setup/rebuild paths. Its GFX detach is in place only as an intermediate operation; the old cell identity is not retained after return.

## Stage reload: `FUN_00e7fd00`

`FUN_00e7fd00` is the opposite boundary:

- Clears `sCellGame+0x51d8` and `sCellGame+0x411c`.
- Drains transient interaction records through `FUN_00e7e130`.
- Iterates old cell pool entries.
- Clears a matching avatar index.
- Detaches each nonzero `+0x248` association through `FUN_00e66010`.
- Releases each old cell with `FUN_00b72260`.
- Drains GFX/effect/UI state, resets world/scale/setup state, and performs later population/setup work.

Its callers include the frame reload branch at `0x00e806b0`, `cCellGame::Initialize`, `FUN_00e80660`, and `FUN_00e809a0`. No old `cCellObjectData`/pool identity survives this drain. Reload is a runtime rebuild, not a same-cell visual refresh.

## Mode exit and dispose

### `OnExit` — `0x00e7fc00`

`OnExit`:

- Restores display/background globals.
- Drains transient interaction records.
- Calls `FUN_00e64a00`, which drains `cCellGFX` preloaded/visual records, world/layer/model/effect services, shadow/light state, and UI state.
- Calls `FUN_00e82d40` for additional service cleanup.

The direct `OnExit` body does not rewrite `cCellGame+0x411c`, `cCellObjectData+0x108`, or `cCellObjectData+0x248`, and does not directly release the cell pool. It is a mode/presentation cleanup boundary, not proof that either the cell pool or its identity survives.

### `Dispose` — `0x00e81f30`

`Dispose` performs deeper service-owner release:

- `FUN_00e63f90` for `cCellGame`.
- `FUN_00e64090` for `cCellGFX`.
- `FUN_00e61b00` for `cCellUI`.

`FUN_00e64090` releases GFX world/layer/model/effect/preload handles and GFX object-pool storage. `FUN_00e61b00` releases UI layout/rollover state. `FUN_00e63f90` performs generic cCellGame service/pool/refcount cleanup. Dispose is therefore distinct from OnExit and distinct from per-cell GFX reattachment.

## Content and serialization classification

### `mModelKey` and `mCellResource`

`CreateCellObject` calls `GetModelKeyForCellResource` and writes the returned `ResourceKey` at `+0xfc`; it stores the `cCellDataReference<cCellCellResource>*` at `+0x108`. `GetModelKeyForCellResource` resolves through the reference before selecting a model key. `FUN_00e6d8f0`, `FUN_00e67890`, and `FUN_00e771d0` consume `+0x108` for resource/effect/child/replacement work.

The GFX detach path changes `+0x248`; it does not clear `+0xfc` or `+0x108`. Recovered classification:

- `mModelKey`: persistent content identity.
- `mCellResource`: runtime content-reference boundary.
- Resolved resource pointer inside `cCellDataReference_`: runtime resource state.
- Neither is the GFX association.

### `cCellSerializableData`

`FUN_00e61550` allocates a 236-byte object and installs serializable/refcount vtables. `cCellGame::Initialize` allocates or adopts the object at `cCellGame+0x5190`. `FUN_00e63d10` swaps a newly allocated object into the global serializable-data slot and copies state through `FUN_00e627a0`; `FUN_00e819b0` can perform a similar in-memory handoff before Cell initialization.

This is an explicit **mode-specific serializable-state/save candidate**, separate from:

- live `cCellObjectData` gameplay state;
- `cCellGFX`/GFX handles;
- `cCellUI` state;
- Cell content records.

No disk transaction, complete field coverage, migration policy, or automatic save on `OnExit` is claimed.

## Hypotheses and exact predictions

### H1 — In-place per-cell GFX association seam

**Claim:** A `cCellObjectData` pool identity can survive a GFX detach and later reattach.

**Predictions:**

1. Detach clears `+0x248` without releasing the input cell pool entry.
2. Rebuild receives an existing cell and writes a newly allocated GFX index to `+0x248`.
3. The caller continues using the same cell object after rebuild.

**Result:** `SUPPORTED_WITH_BRANCH_LIMIT` — `FUN_00e66010` and `FUN_00e6d8f0` satisfy the field/pool predictions; branches are separate.

### H2 — One atomic detach→rebuild function

**Claim:** One recovered function unconditionally performs detach and rebuild on the same cell.

**Predictions:**

1. The same function calls `FUN_00e66010` and then `FUN_00e6d8f0`.
2. The cell remains valid between both calls.
3. No despawn branch intervenes.

**Result:** `NOT_PROVEN` — the direct xrefs show separate branches and separate callers.

### H3 — `FUN_00e780a0` releases the old cell

**Claim:** `FUN_00e780a0` is despawn/transition, not presentation-only refresh.

**Predictions:**

1. Matching `cCellGame+0x411c` is cleared.
2. `+0x248` is detached before pool release.
3. `FUN_00b72260(param_1)` follows the optional replacement/child work.

**Result:** `SUPPORTED` — all three direct observations hold.

### H4 — Reload discards old pool identity

**Claim:** `FUN_00e7fd00` rebuilds runtime state from drained pools.

**Predictions:**

1. `+0x411c` is cleared at reload entry.
2. Old cells have GFX detached and then are released.
3. World/UI/setup work follows the drain.

**Result:** `SUPPORTED` — the body performs all three operations in that order.

### H5 — Content identity is independent of GFX

**Claim:** `mModelKey` and `mCellResource` are content/resource fields, not presentation handles.

**Predictions:**

1. Create populates `+0xfc` and `+0x108`.
2. GFX detach/rebuild changes `+0x248` without clearing `+0xfc` or `+0x108`.
3. Effect/child/replacement helpers resolve through `+0x108`.

**Result:** `SUPPORTED` — direct create, detach, rebuild, effect, and child/replacement paths agree.

### H6 — Mode teardown is separate from save

**Claim:** `OnExit` and `Dispose` are service/mode cleanup boundaries; `cCellSerializableData` is a separate save candidate.

**Predictions:**

1. OnExit drains transient/presentation state without serializing the cell pool.
2. Dispose releases `cCellGame`, `cCellGFX`, and `cCellUI` separately.
3. `cCellSerializableData` has its own 236-byte allocation, vtables, and `+0x5190` owner.
4. No disk transaction is inferred from teardown.

**Result:** `SUPPORTED_AS_BOUNDED_SAVE_CANDIDATE` — the direct teardown and handoff paths are separate; save bytes remain unresolved.

## Modern design invariant versus recovered original behavior

### Modern design invariant — normative, not an original claim

- Use a stable simulation `CellId`/pool index independent of presentation.
- Treat `mGFXObjectIndex` as optional and replaceable.
- Keep model/content keys and resource references separate from resolved runtime resources and GFX/UI handles.
- Keep gameplay state authoritative in simulation and rendered pose/effects downstream.
- Model create, gameplay mutation, presentation detach, presentation rebuild, despawn, reload, `OnExit`, and `Dispose` as distinct transitions.
- Use `cCellSerializableData` as a separate mode-state DTO/candidate; do not treat live pool, GFX, UI, or world handles as save-surviving.

### Recovered original behavior — static observation

- The original uses pool indices and reciprocal GFX association fields.
- The original has a per-cell detach path and a per-cell new-GFX attachment path using the same Cell object across separate calls.
- The original's `FUN_00e780a0` and `FUN_00e7fd00` release old Cell objects rather than preserving them.
- The original's `OnExit` and `Dispose` coordinate separate GFX, UI, and CellGame service owners.
- The original's `cCellSerializableData` is a mode-specific in-memory state candidate; this pass does not establish a complete save transaction.

## Bound

The negative result is not “no in-place GFX operation”: the binary does contain one. The bound is narrower: the observed in-place detach and rebuild are **conditional, separate operations**, while the common despawn/reload helpers do not retain the old Cell identity. No positive original-process trace, complete GFX record structure, hidden virtual retirement order, or complete save transaction is claimed.

## Ghidra citations

- `0x00e74a20` — `CreateCellObject`
- `0x00e65640` — `GetModelKeyForCellResource`
- `0x00e66010` — per-cell GFX detach
- `0x00e6d8f0` — per-cell GFX rebuild
- `0x00e5ce90` — reciprocal GFX record initialization
- `0x00e78c00` — detach/rebuild branch seam
- `0x00e7c8c0` — per-cell pool iteration
- `0x00e780a0` — despawn and pool release
- `0x00e7fd00` — stage reload/drain
- `0x00e7fc00` — `OnExit`
- `0x00e81f30` — `Dispose`
- `0x00e63f90` — `cCellGame` teardown
- `0x00e64090` — `cCellGFX` teardown
- `0x00e61b00` — `cCellUI` teardown
- `0x00e5dba0` — stage-level `cCellGFX::Initialize`
- `0x00e61550`, `0x00e61630`, `0x00e63d10` — serializable allocation/handoff
- `0x00e806b0` — reload branch
- `0x00e819b0` — GFX/UI/Cell initialization and serializable handoff
- `0x00e82420` — `cCellDataReference_::Create`
- Structures: `cCellObjectData`, `cCellGame`, `cCellGFX`, `cCellUI`, `cCellDataReference_`, `cCellSerializableData`
