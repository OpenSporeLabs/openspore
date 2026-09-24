# Follow-up 03 — noun/star root publication and lifecycle

## Result

**Classification:** `UNRESOLVED_BUT_SAFE`

Static observation cannot close pointer equality or root publication for either noun or star slots. The four targets are distinct four-byte words, and the direct/computed/table searches did not identify a writer. The safe architecture is four separate opaque root ports with explicit publication and teardown boundaries; do not merge slots or route the `DAT_016dc0fc` receiver through them.

## Scope and constraints

Explicit Ghidra program: `SporeApp.exe`, `x86:LE:32:windows`, image base `0x00400000`.

No Ghidra program mutation, runtime experiment, source implementation, `SPORE/` access, `spore.db` query, or historical edit was performed. The four target words are zero in the loaded image, which does not establish runtime liveness.

## Direct accessors and root words

| Root | Direct readers | Writers found | Accessor contract |
|---|---|---:|---|
| `DAT_0167eae0` | `0x00b3d300: mov eax,[0x0167eae0]; ret` | 0 | raw borrowed load |
| `DAT_0167eb60` | `0x00b3d400: mov eax,[0x0167eb60]; ret` | 0 | raw borrowed `cGameNounManager::Get` load |
| `DAT_0167eae4` | `0x00b3d2a0: mov eax,[0x0167eae4]; ret`; `0x00b3d2c0: mov ecx,[0x0167eae4]; jmp 0x00c4f030` | 0 | raw alternate load; `0x00b3d2c0` is a state-selected relationship bridge |
| `DAT_0167eb0c` | `0x00b3d3a0: mov eax,[0x0167eb0c]; ret` | 0 | raw borrowed `cStarManager::Get` load |

The four accessors perform no validation, allocation, `AddRef`, `Release`, locking, or ownership transfer. The noun-compatible alternate `0x00b3d300` is used by `0x00bff2d0` as the receiver for the noun-data path, so it is not merely a generic context locator.

## Direct, literal, computed, and table search

- Direct Ghidra xrefs found exactly five target read sites and zero direct target writes or equality operands.
- Exact four-byte literal scans found each root address only in its accessor instruction(s): `0x00b3d301`, `0x00b3d401`, `0x00b3d2a1/0x00b3d2f2`, and `0x00b3d3a1`.
- No exact data occurrence was found for the four accessor entry addresses.
- A data reference at `0x0146286c` points to `0x00b5ca50`, a thunk that calls `0x00b3d3a0` and dispatches through a returned object's vtable. It is a getter consumer, not a root writer.
- A bounded read-only P-code scan resolved zero concrete arithmetic addresses and zero P-code `STORE`s to any of the four roots. This does not cover opaque pointer-derived addresses, external calls, loader/runtime writes, unresolved code, or opaque bulk memory operations.
- The arithmetic base candidate `0x0167ea80` was rejected as a manager table: its users read/write float fields through `0x00b3cf40` and the `0x00b3ce80/0x00b3cec0/0x00b3cf00` selectors, not the root-word offsets.

## Pair/equality separator

A co-call scan found 11 functions calling both noun accessors: `0x00ae9f50`, `0x00aebe90`, `0x00b33350`, `0x00b335d0`, `0x00cd3bf0`, `0x00d0e170`, `0x00d100b0`, `0x00d38150`, `0x00ef10c0`, `0x00fe5a20`, and `0x01007430`. Their accessor results are used in separate noun/data, mode, receiver, or lifecycle paths. For example, `0x00cd3bf0` retains the canonical result while the alternate is used in another path; `0x00b335d0` has separate mode branches. No cross-accessor pointer comparison was recovered.

No function co-calls `0x00b3d2a0` and `0x00b3d3a0`. Co-call topology and shared domain use are not equality evidence.

## Receiver chain

`0x01002bd0` is exactly:

```text
mov eax,[0x016dc0fc]
ret
```

In `0x00bff2d0`:

```text
0x00bff3ad call 0x01002bd0
0x00bff3b2 mov ecx,eax
0x00bff3b4 call 0x00b1fdb0
```

`DAT_016dc0fc` has its own direct publication and teardown:

- `0x010066e0` stores the constructed parent at `0x010067f0`.
- `0x01006880` clears it at `0x010068c4` after releasing the child at parent+`0x30`.
- `0x00fda750` stores the constructed child at parent+`0x15c`.
- The receiver's `+0x54` result is therefore a separate parent/context field, not either noun root.

This rejects the hypothesis that `DAT_016dc0fc` is a common publisher for the noun/star roots. It does not close indirect publication of the four target words.

## Constructor and teardown observations

The inspected star-manager lifecycle is field/service oriented:

- `0x00b60d80` constructs/registers the manager.
- `0x00bae490` initializes manager fields including `mEmpires +0x150` and relationship state `+0x204`.
- `0x00bb6a30` initializes the relationship manager.
- `0x00bb7250` tears down manager state and clears/releases `+0x204`.
- `0x00babe70` releases manager-owned maps and fields.

The inspected noun lifecycle is record/map oriented:

- `0x00b21410` unlinks a noun map node, releases the payload, frees the node, and clears a matching owner field.
- `0x00b25fe0` performs noun-related cleanup and traversal.

None has a direct xref to any of the four target words. This is evidence against those inspected paths publishing/unpublishing the roots, not proof that no opaque service-registration or phase publisher exists.

## Aliasing and shared storage

- Physical storage aliasing is rejected: the targets are four distinct four-byte words.
- Value aliasing is unresolved: an unobserved common publisher could place the same manager pointer in multiple words.
- Noun data is receiver-owned (`mNouns +0x78`, `mNounMap +0x98` in the `0x00b21340` path).
- Star empire data is manager-owned (`mEmpires +0x150`); relationship state is field-owned (`+0x204`).
- No indirection table, proxy, shared map root, access-time `AddRef`, or direct alias store was found for the target words.
- The `0x00b5ca50` thunk is a table consumer of the canonical star getter, not an aliasing/publication mechanism.

## Hypotheses and status

| ID | Hypothesis | Status |
|---|---|---|
| H1 | Noun slots always point to the same manager | unresolved, unsupported as fact |
| H2 | Star slots always point to the same manager | unresolved, unsupported as fact |
| H3 | A common computed/table/bulk publisher fills one or more roots | plausible generic mechanism, not identified |
| H4 | Slots are phase-specific, rebound, or distinct instances | plausible, unproven |
| H5 | One slot is obsolete/unpublished while the other is live | plausible liveness alternative, unproven |
| H6 | `DAT_016dc0fc` is a common noun/star publisher | rejected |
| H7 | The four words share storage or a handle/proxy | physical aliasing rejected; value aliasing unresolved |
| H8 | Inspected manager constructors/destructors directly publish all roots | not supported for inspected paths; global absence not proven |
| H9 | `0x00b3d300` is a noun-manager-compatible alternate accessor | supported with alias limit |

## Exact lower bound

The smallest defensible slot-level lower bound is:

- **4 unresolved publication states**, one for each root word.
- **4 unresolved unpublication/teardown states**, one for each root word.
- **2 unresolved value-equality relations**, noun pair and star pair.

A single opaque function could service multiple publication or teardown obligations, so the number of concrete writer functions is not bounded by this count. The exact count is the number of unresolved slot contracts, not the number of undiscovered call paths.

The safe interim boundary is therefore: keep four separate opaque roots, preserve manager-owned noun/star storage, and expose publication/replacement/unpublication as explicit lifecycle events. It is unsafe to assume a singleton, shared noun/star storage, exact receiver provenance, or absence of indirect writers.

## References

- `0x00b3d300`, `0x00b3d400`, `0x00b3d2a0`, `0x00b3d2c0`, `0x00b3d3a0`
- `0x00b5ca50`, data reference `0x0146286c`
- `0x00bff2d0:0x00bff3ad-0x00bff3b4`
- `0x01002bd0`, `0x010066e0`, `0x01006880`, `0x00fda750`
- `0x00b21410`, `0x00b25fe0`
- `0x00b60d80`, `0x00bae490`, `0x00bb6a30`, `0x00bb7250`, `0x00babe70`
- `0x0167ea80`, `0x00b3cf40`, `0x00b3ce80`, `0x00b3cec0`, `0x00b3cf00`
