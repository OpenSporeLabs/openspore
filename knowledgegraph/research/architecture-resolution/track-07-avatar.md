# Track 7 — Avatar Owner / Lifetime

## Resolution

**Status: `RESOLVED_SUPPORTED_WITH_LIMIT`; classification: `cross_boundary`; conflict record: `preferred_claim_with_limit`.**

`0x00b1fdb0` is only `return *(uint32_t *)(ECX + 0x54)`. It is **not** a universally typed avatar getter:

- `0x00b3d300` is a raw noun-manager-compatible root port returning `DAT_0167eae0`. When its result is a live cGameNounManager-layout receiver, `+0x54` is `cGameNounManager::mpAvatar`, an `intrusive_ptr<cCreatureAnimal>`, and the accessor returns a **borrowed raw current-creature pointer**.
- At the exceptional `0x00bff2d0` path, `0x01002bd0` returns separately published `DAT_016dc0fc`, a cSimulatorSpaceGame-shaped parent/context. Its `+0x54` is `mpHighLODPlanetSim`, not `mpAvatar`.

The semantic type is receiver-dependent. Follow-up-03 leaves `DAT_0167eae0` and `DAT_0167eb60` as physically distinct words with unresolved publication, liveness, teardown, and value equality; the noun-layout field contract is conditional on a live receiver, not a proof of a published singleton.

## Native contract versus modern recommendation

**Native/local evidence:**

- `0x00b1fd50` performs old/new `+0xb58` bit `0x200` updates, then AddRef-new → store-new → Release-old when addresses differ.
- `0x00b1fdb0` performs no AddRef/Release and returns the raw field.
- `0x00c099e0` installs a creature on the noun-layout path; `0x00ef10c0` clears the slot before destroying the old object.
- `0x00b3d300` and `0x00b3d400` are separate raw root ports. Co-call topology does not prove equality.

**Modern replacement guidance:** a stable gameplay `EntityId` may be useful in a future architecture, but no stable EntityId field or native ABI is claimed here. Keep noun-root ports, object references, Cell pool indices, presentation handles, and save candidates as separate domains until their contracts are proven.

## Ownership and lifetime

For a live cGameNounManager-layout receiver, `0x00b1fd50` closes the local retention contract:

1. Clear bit `0x200` on old `+0xb58`.
2. Set bit `0x200` on new `+0xb58`.
3. If addresses differ: call new vtable `+0x00` (AddRef), store at owner `+0x54`, then call old vtable `+0x04` (Release).
4. Equal addresses skip reference/store churn; null is a valid stored value.

The current word is nullable, replaceable, and has no observed generation or durable-ID semantics. The exact owner multiplicity across noun lists, parent collections, and external references remains open.

## Publication uncertainty

Follow-up-03 found:

- `DAT_0167eae0` and `DAT_0167eb60` are distinct four-byte words.
- Their accessors perform raw loads only.
- Five direct root reads, zero direct writers, zero bounded computed stores, and no cross-accessor equality were recovered.
- The eleven noun co-call functions use the ports in separate paths; this is not aliasing evidence.
- `DAT_016dc0fc/0x01002bd0` has its own constructor/teardown publication and is not either noun root.

Therefore this report freezes the **conditional local noun-layout contract**, not root publication, liveness, teardown, or value equality. Runtime is required for those root-level questions and for save restoration timing; it was not performed.

## Smallest separator

```text
0x00bff3ad call 0x01002bd0
0x01002bd0 mov eax,[0x016dc0fc]; ret
0x00bff3b2 mov ecx,eax
0x00bff3b4 call 0x00b1fdb0
```

- `0x010066e0` publishes `DAT_016dc0fc`; `0x01006880` clears it.
- `cSimulatorSpaceGame+0x54 = intrusive_ptr<cSimPlanetHighLOD> mpHighLODPlanetSim`.
- The high-LOD value is compared with the inherited EBX sentinel in this hidden-register window; it is not dereferenced as a creature.
- `0x00b3d300` supplies a noun-layout receiver used by `0x00b20c60`/`0x00b21340` at noun fields, but that does not close either root's publication state.

## Field corrections and layout

- `result vtable + 0xd8` is `cCreatureBase::GetCurrentBrainLevel`; it is not a result-object field.
- `result + 0x55c` is rejected. `0x00d2e720` discards the `0x00b1fdb0` return and reads `+0x55c` on the `cSpeciesProfile*` returned by `0x004df420 -> 0x004df550`.
- The selected cSpeciesProfile runtime size is `0xA18`; the imported `0xEEC` Ghidra projection is superseded/quarantined by conflict adjudication. The `+0x55c` field meaning remains unknown. If a local Ghidra type still reports `0xEEC`, it is stale metadata and must not override the `0xA18` allocation/constructor evidence.
- `cCreatureBase+0xb54` is the separate `intrusive_ptr<AnimatedCreature>` presentation association.
- `cCellGame+0x411c` is a Cell-local `cObjectPoolIndex`, not the noun-layout avatar pointer.

## Ownership matrix

| Concept | Classification | Owner/lifetime |
|---|---|---|
| `DAT_0167eae0` via `0x00b3d300` | `simulation` | Noun-manager-compatible port when published/live; publication unresolved |
| `DAT_0167eb60` via `0x00b3d400` | `cross_boundary` | Separate named noun-root port; publication/equality unresolved |
| Conditional noun-layout `+0x54` | `simulation` | Retained current `cCreatureAnimal`; replaced/cleared by local writer |
| `0x00b1fdb0` result | `cross_boundary` | Borrowed raw receiver+`0x54`; semantic type is receiver-dependent |
| `cCreatureBase/cCreatureAnimal` | `simulation` | Intrusive object graph; current slot is one owner |
| `cGameNounManager` lists / parent collections | `cross_boundary` | Additional runtime retention and noun ownership |
| `cCreatureBase+0xb54` AnimatedCreature | `presentation` | Detachable/rebuildable association; exact detach order deferred |
| Model key / model-world handles | `cross_boundary` | Content identity plus runtime graphics handles |
| `cCellGame+0x411c` avatar index | `simulation` | 4096-slot Cell-local pool identity |
| Cell GFX/UI/world/effect handles | `presentation` | Rebuilt/released independently of gameplay identity |
| `cSimulatorSpaceGame+0x54` | `simulation` | `mpHighLODPlanetSim`, never an avatar fallback |
| `cCreatureGameData` | `cross_boundary` | Progression state; save handoff unresolved |
| `cCellSerializableData` | `cross_boundary` | Separate Cell save candidate |
| Serialized noun/cGameData records | `persistent_content` | Serialization eligibility/restore candidates; raw pointer emission unresolved |

## Nine adversarial steps

| Step | Result |
|---|---|
| Receiver-type separation | Universal avatar claim falsified by the separately published cSimulatorSpaceGame-shaped receiver. |
| Pointer vs handle | Direct vtable/nested dereferences and virtual refcount reject ID/index/union. |
| Owner vs borrower | Conditional noun-layout slot retains one current reference; accessor returns borrowed. |
| Gameplay vs presentation | Conditional noun-layout result is gameplay state; AnimatedCreature/GFX are separate. |
| Current pointer vs stable identity | Raw selection is mutable/null/replaceable; no native stable EntityId is claimed. |
| Replacement/despawn | Slot replacement, object destruction, Cell despawn, and rebuild are distinct. |
| Pool/index separation | Conditional noun reference and Cell avatar pool index are different identities. |
| Presentation/save boundary | Native layers and serializable eligibility are separate; exact save field emission is unresolved. |
| Architecture dependence | Offset coincidence is rejected; local instruction sequences are decisive, root publication remains open. |

The full hypotheses, predictions, evidence, same-session correlation notes, field/layout adjudications, dependent decisions, freeze/defer lists, blockers, and citations are in `track-07-avatar.json`.

## Freeze / defer

Freeze the raw `+0x54` accessor, conditional noun-layout refcount mechanics, receiver-dependent typing, vtable `+0xd8`, rejected root-result `+0x55c`, `0xA18` cSpeciesProfile runtime-size selection, and separation of gameplay/presentation/Cell identity.

Defer root publication/equality/liveness/teardown, exact `0x00b1fd50` symbol identity, complete owner multiplicity, presentation detach timing, save field coverage, and positive runtime/save traces. Any stable gameplay EntityId is deferred modern architecture guidance, not native evidence.

## Sources

- `knowledgegraph/research/architecture-resolution/followup-03-root-publication.{md,json}`
- Read-only Ghidra `SporeApp.exe`: `0x00b1fdb0`, `0x00b1fd50`, `0x00b3d300`, `0x00b3d400`, `0x00b20c60`, `0x00b21340`, `0x00c099e0`, `0x00ef10c0`, `0x00bff2d0`, `0x01002bd0`, `0x010066e0`, `0x01006880`, `0x00d2e380`, `0x00d2e4a0`, `0x00d2e580`, `0x00d2e720`, `0x00d2e8a0`, `0x00d39360`, `0x004df420`, `0x004df550`.
- `knowledgegraph/research/conflict-adjudication.json:4337-4375,10227-10355`
- `knowledgegraph/research/root-closure/track-c-opaque-owner.{md,json}`
- `knowledgegraph/research/root-closure/followup-receiver-provenance.{md,json}`
- `knowledgegraph/research/root-closure/followup-noun-boundary.{md,json}`
- `knowledgegraph/research/data-model/04-creature-data.json`
- `knowledgegraph/research/data-model/09-save-load-persistence.json`
- `knowledgegraph/research/data-model/17-persistence-synthesis.json`
- `knowledgegraph/research/state-machines/cell-stage.json`
- `knowledgegraph/research/architecture-resolution/track-08-cell-lifecycle.{md,json}`

No runtime, implementation, source change, historical-artifact change, Ghidra mutation, `SPORE/` access, or `spore.db` access was performed.

