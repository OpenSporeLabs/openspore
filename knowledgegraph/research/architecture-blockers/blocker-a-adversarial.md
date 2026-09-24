# Blocker A Adversarial Critique — Noun/star publication lifecycle

**Review target:** `knowledgegraph/research/architecture-blockers/blocker-a-primary.md`

**Review mode:** read-only adversarial review of the primary report and prior local architecture reports. No source, `SPORE/`, Ghidra project, or canonical SQLite KG was modified. No original-process runtime observation was performed.

## Executive verdict

The primary report correctly preserves the central blocker: the four physical root words are distinct, but their runtime publishers, value equality, liveness, rebind order, and teardown order are not established. It also correctly preserves the bounded lower-bound behavior of the inspected noun and empire paths.

The report is nevertheless too quick to turn physical separation and a few manager-field observations into an architectural story. The biggest overclaims are:

1. **Storage is not ownership.** Four distinct words establish four addressable slots, not four owners, four lifetimes, or four independently managed services.
2. **The noun/star manager labels are partly provisional.** The strongest evidence establishes compatible receiver layouts, not complete class identity or root publication.
3. **Lower-bound lookup has destructive consequences.** “Invalidate the matching entry” and “erase the matching object” are not safe descriptions unless exact-key membership is separately proven; the inspected helpers can select a successor.
4. **Materialization is not root publication.** Factory creation, list insertion, noun-map materialization, and cache invalidation do not establish how any root slot receives a manager.
5. **The proposed four-port boundary is conditionally safe only.** It is safe as a compatibility-excluded, opaque observation seam. It is not safe if the ports imply four owners, four recovered lifecycle mechanisms, or independent manager instances.
6. **The “smallest decisive observation” is not one trace.** One unequal or root-changing observation can reject unconditional equality, but only a complete transition/teardown matrix can establish a positive always-equal or teardown-order model.

The report should therefore remain classified as an open compatibility blocker, while its implementation decision should be narrowed to: **a bounded clean-room semantic replacement may proceed with opaque root observations and explicit host-side rebind policy; original root identity, publication, and teardown compatibility remains blocked.**

## 1. Claim-by-claim challenge

| Primary claim | What is actually supported | Adversarial correction |
|---|---|---|
| Four distinct four-byte words | Direct image/layout observation and distinct accessor reads | This rejects physical aliasing only. It does not prove four owners, four lifetimes, four publications, or four distinct manager objects. |
| No publisher recovered | No direct literal writer in the bounded scans | This is a negative result, not evidence for a particular publisher. Computed, data-table, helper-argument, external, loader, and unresolved-code paths remain open. |
| Four root ports are the safe boundary | A conservative uncertainty-preserving interface is possible | Ports are an implementation policy, not a recovered architecture. They must not assert four owners or route a consumer from one port to another as a fallback. |
| Noun and star managers are the owners below the roots | Receiver layouts and selected field access are compatible with those manager types | Manager compatibility is not publication ownership. The root may contain a borrowed pointer, a phase object, a proxy, or a value published by a service layer not recovered here. |
| Noun materialization is manager-owned | Factory call, intrusive-list insertion, noun-map rebuild, and reference-managed paths are visible | This proves a bounded create/register/materialize sequence. It does not prove that the noun manager is the sole owner, that the root slot points to it, or that the object survives teardown. |
| Noun invalidation marks the matching vector | `needsUpdate` is written through a lower-bound lookup and type/cast filtering | The report must say “lower-bound-selected vector/record.” Without a key postcondition, “matching” is an overclaim. |
| Noun erase removes the matching object | A map-erase path is present | The map helper is lower-bound based; the report does not establish an exact key check. A successor can be selected under the same missing-key condition. |
| Star empire erase is direct and cache invalidation is independent | A map eraser releases its selected payload; player cache clearing is a separate body | This is a strong static separation, but the eraser itself is not membership-safe without an exact-key or pre-membership invariant. |
| Manager teardown is direct | A manager teardown/cleanup body is present | This does not establish global unpublication, final root clear order, cross-root release order, or whether a service owner keeps the manager alive after the body returns. |
| `cStar` and `cStarRecord` have distinct identities | Different types/storage and a typed pointer link are supported | Physical type separation is supported. Logical cardinality and identity are not: a live star noun may represent the same logical star as its record. The report itself also says they “share semantic star identity.” |
| Raw root pointers are not serialized | No root write was found in the inspected persistence paths | The defensible claim is that raw pointer persistence is **not authorized or evidenced** for the replacement. Static absence does not prove the original never serializes or restores a root value. |
| One bounded trace is the smallest decisive observation | A trace can expose unequal values and root changes | It is the smallest decisive observation for rejecting H1, not for proving H1 or closing teardown. A complete positive model needs the required transition matrix. |

## 2. Publisher and root storage

### What survives

The strongest claim here is the physical one. The four target words are distinct storage locations, each is read by a direct accessor, and the reported image-time bytes are zero. The absence of a direct store in the bounded disassembly/xref scans is also real evidence that the publishers are not simple literal writes in the analyzed surface.

The primary report is right to reject physical aliasing and right to reject fan-in as ownership proof. The high fan-in of `0x00b3d300` and `0x00b3d2a0` shows use, not publication priority or authority. The sparse canonical accessors do not show that the canonical slots are dead.

### What is overclaimed

The report calls the static publication gap an unresolved issue but then describes opaque publication as the “leading explanation” (`blocker-a-primary.md:307-321`). That is not established. The only support is that the direct scans are negative and the slots are in a writable `.data` region. That makes an opaque path possible, not more likely than phase-specific, stale, loader-initialized, or even always-equal publication.

The words “root storage word” and “publisher” also need stricter definitions:

- A **slot** is an address whose value is read by an accessor.
- A **publisher** is a concrete operation that writes, rebinds, clears, or initializes that slot.
- A **service registration** is a manager construction or registration event.
- A **manager owner** is an object that retains and releases the pointee.

The report has direct evidence for the first category and partial evidence for the second and third. It has not connected the four slots to a fourth category.

The proposed `publish`, `replace`, and `unpublish` operations should be labeled **clean-room lifecycle hooks**, not binary operations. The report itself notes that the inspected manager constructors and destructors do not write the root words. Calling the hooks “explicit lifecycle events” is safe only if the implementation makes that distinction visible.

### Smallest decisive static observation

The smallest useful static continuation is not another accessor scan. It is a complete dataflow from every concrete manager construction/registration result into any of the four words, including:

- direct stores through aliases of the four addresses;
- `memcpy`/bulk-copy helpers whose source or destination is derived from those addresses;
- table or relocation initializers;
- service-registration helpers that receive a manager pointer and publish it indirectly;
- loader or external boundary calls that can write the writable `.data` region.

If that produces a concrete store or clear, the publisher, value source, and likely owner chain become decidable. If it does not, static analysis has reached its stated limit; it must not upgrade “no writer found” into “no writer exists.”

### Smallest decisive runtime observation

One naturally reachable mode transition with simultaneous read-only captures of all four words immediately before and after the transition is enough to reject unconditional equality if it shows a non-null unequal pair, a one-sided null, or a rebind. It is not enough to prove that the slots are always equal. A single equal snapshot is likewise not enough.

The trace must also record the manager object address and a generation or lifetime marker. Comparing the four words without knowing whether the pointee was destroyed and a new object was allocated can mistake allocator reuse for value equality.

## 3. Storage, ownership, and lifetime

The primary report correctly distinguishes raw borrowed accessors from manager-owned fields. The getters perform no AddRef, Release, validation, allocation, or lock. That supports a borrowed-pointer contract at the accessor boundary. It does not establish the lifetime of the pointee after the getter returns.

The report also uses “manager-owned” in several places where the evidence is narrower:

- `cGameNounManager` has intrusive lists/maps and a factory path. This supports registry/list ownership mechanics.
- `cStarManager` has selected map/vector/field ownership mechanics. This supports selected runtime ownership mechanics.
- Neither fact proves that a root slot owns the manager, that the root is the manager’s lifetime authority, or that a service composition layer does not retain it elsewhere.

The noun report in `knowledgegraph/research/root-closure/followup-receiver-provenance.md:13-20,67-87,131-137` is more conservative than the primary report about `0x00b3d300`: it calls the receiver a shared context/owner candidate in some places and explicitly says not to promote it to `cGameNounManager` solely from co-call frequency. The primary report’s “noun-manager-compatible” wording is acceptable only as a compatibility claim. Its table labels such as “raw noun-port candidate” must not silently become “noun owner.”

The star report has the same issue. `0x00b3d2a0` is strongly `cStarManager`-compatible because its result is consumed through `mEmpires +0x150` and relationship-manager `+0x204`, but that does not establish that `DAT_0167eae4` and `DAT_0167eb0c` point to the same manager or that either root owns the manager.

The distinction is important for the proposed interface:

```text
root slot != manager owner
manager object != lifetime authority
borrowed pointer != retained reference
field owner != root publisher
```

The primary report preserves these distinctions in its conclusion, but not consistently in its stronger “manager-owned” language.

## 4. Lookup semantics

The lower-bound correction is one of the report’s strongest results. `0x00e5c780` is used as an ordered lower-bound helper, and the noun and empire wrappers do not perform a returned-key equality check. The report is right to reject exact-find and to require callers needing exactness to add an identity postcondition.

The implication must be carried through every operation:

- Noun materialization can select a successor record and rebuild its payload using the requested noun ID.
- Noun invalidation can mark a successor vector when the requested key is absent.
- Empire lookup can return a successor empire.
- Current-player cache refresh can retain and return that successor.
- The empire eraser can select and remove a successor unless membership is guaranteed by the caller or a key check is added.

The report applies the exactness warning to lookup and cache, but uses “matching” in the invalidation and erase sections (`blocker-a-primary.md:143-165,185-202`). That wording should be replaced with “lower-bound-selected” unless the exact-key invariant is independently established.

There is a second limitation: map comparator behavior is only demonstrated for the observed map/helper pairing. The report should not generalize the lower-bound behavior to every noun, political-ID, or future map without preserving the comparator and key-width assumptions. “Unsigned” and “lower-bound” are bounded observations, not universal map semantics.

The safe clean-room rule is precise:

```text
lookup_by_key_or_ceiling(...)
exact_lookup(...) = lookup(...) + key/identity postcondition
```

A future exact lookup may be implemented as a deliberate clean-room choice, but it must not be described as the original binary’s behavior.

## 5. Noun materialization and cache invalidation

The factory and list-insertion path is useful. The primary report correctly avoids calling the noun manager a persistence format and correctly distinguishes live object materialization from save state.

The claim is still too broad in two places:

1. “Manager-owned materialization into the live noun list” is supported as a list/registry relationship, not as a complete ownership proof. The report itself notes no universal noun hierarchy and no RTTI-backed type closure.
2. “The five callback arguments” is contradicted by the later correction to four callback pointers plus a noun ID. The primary report carries both formulations in nearby sections (`blocker-a-primary.md:130-141`). The final implementation contract must use one ABI description only: four callbacks plus noun ID.

`0x00b21340` has an additional ownership gap that the primary mentions only indirectly. The create callback allocates a record, while the map helper can allocate a separate map node. The visible path does not prove that the callback result and map node are the same allocation or that insertion failure cleans up the create result. A clean-room noun factory can choose its own ownership model, but the report should not describe the binary path as a closed create/insert ownership chain.

`0x00b201a0` is a direct invalidation bridge, but its result is not necessarily an exact-key invalidation. It should be represented as:

```text
lower_bound(noun_id)
mark selected vector dirty
apply observed type/cast filter to other vectors
```

Any claim of exact cache invalidation requires a runtime key matrix or a proven membership invariant.

The report also does not establish locking, reentrancy, allocation failure behavior, exception behavior, or whether a failed callback leaves `needsUpdate` set or partially materialized. Those omissions do not prevent a bounded clean-room implementation, but they do prevent claiming compatibility with the original cache lifecycle.

## 6. Star lookup, materialization, and erase

The empire lookup correction is strong. `0x00ba9370` does not AddRef, Release, insert, or compare the returned key. The current-player cache is independently reference-managed and identity-checking only on its hit path. The report correctly rejects exact-result cache semantics and guaranteed erase-time cache clearing.

The report should carry the same lower-bound warning into erase more visibly. `0x00bad7a0` uses lower-bound selection and releases the selected map payload. If the requested political ID is absent and a greater key exists, a successor can be removed. The static body may rely on a caller invariant that the key is currently present, but that invariant is not established by the report. “Empire map erase is direct” is safe; “erase the requested empire” is not.

The separate `SpacePlayerData+0x1c` cache clear is a real negative against a guaranteed single invalidation chain. It also means the clean-room boundary must keep the following distinct:

- manager selection;
- manager-owned empire map;
- player-owned empire cache;
- cache reference ownership;
- current-player identity generation.

A single “invalidate star port” operation could accidentally hide or incorrectly couple these. If the implementation exposes one, it must document whether it invalidates the manager map, the player cache, a root observation, or all three.

The report’s statement that a cache-owned reference can keep an erased empire alive is plausible from the independent AddRef/Release path, but it is not a runtime observation. It should remain a static lifetime consequence with “can”/“may,” not a claim that the original actually reaches the stale-cache case in normal play.

## 7. Materialization, persistence, and noun/star aliasing

The physical distinction between live `cStar` and `cStarRecord` is well supported by type/layout evidence: `cStar` is a game-data noun and has a record pointer, while `cStarRecord` is a separate record type. The report is right not to serialize raw root addresses and right not to equate a manager root with a database.

The statement “live star noun, persistent star record, live planet, and empire record are distinct identities” is too strong. The evidence establishes distinct storage and typed links, not identity cardinality or lifecycle equivalence. A live star noun can be a runtime view of the same logical star represented by a `cStarRecord`. The primary report itself says the two “share semantic star identity” (`blocker-a-primary.md:204-213`) and then uses “distinct identities” in the final classification (`blocker-a-primary.md:378-390`). The safer formulation is:

```text
distinct physical representations and typed links;
logical identity and association cardinality remain unresolved.
```

The same caution applies to the noun registry. The manager may own the live object’s intrusive list entry and cache vector, while the noun’s owner pointer, factory, political identity, and persistence object follow separate rules. “Owned noun” is too strong unless the report specifies which ownership relation is meant.

Persistence evidence is bounded in the right direction. The star database replacement and runtime registry reconstruction distinction are useful. However, “no root-global write was found” supports “root serialization is not evidenced,” not “raw root serialization is proven absent.” The clean-room decision may reject host-pointer persistence as unsafe and nonportable; that is a design decision, not a recovered negative about the original binary.

## 8. Teardown and unpublication

The primary report correctly says manager teardown is visible but root unpublication is not. It also correctly refuses to infer cross-root teardown order from manager field cleanup.

The remaining issue is terminology. `FUN_00b22440` or equivalent manager cleanup is evidence of a manager teardown surface. It is not automatically:

- final service teardown;
- last root read;
- root clear;
- root release;
- destruction of the object returned by the root getter;
- a guarantee that no later code uses a borrowed manager.

Likewise, noun object destruction, noun-manager teardown, star-manager teardown, and root unpublication are four different lifecycle levels. The report sometimes places them in one state graph (`blocker-a-primary.md:232-255`) and sometimes separates them. The graph should label each edge by ownership level and mark root edges unknown rather than drawing a generic “manager teardown” endpoint.

A safe clean-room implementation should represent root observations with an epoch/generation token. A consumer that retains a borrowed root view must be invalidated when the host rebinds or unpublishes that view, even though the original binary’s exact unpublication mechanism is unknown. This is a replacement safety mechanism, not a claim about the original.

## 9. Four-port boundary: safe conditionally, unsafe as currently overread

### What is safe

A four-port boundary can proceed if it means only this:

```text
four separately addressable, opaque root observations
```

Each port should have:

- no implicit equality with another port;
- no implicit fallback to another port;
- no raw manager pointer in the public semantic interface;
- an explicit host-side publication/rebind/clear event;
- an observation generation or epoch;
- a borrowed-result lifetime rule;
- a compatibility status that remains unresolved.

This is outcome-independent. It remains valid whether the two noun words are always equal, always distinct, phase-rebound, temporarily null, or populated by an opaque publisher.

### What is unsafe

The proposal becomes unsafe if any of the following is implied:

1. **Four ports means four owners.** The evidence proves four words, not four owner objects.
2. **Alternate/canonical means a known priority.** The labels come from accessor naming and call distribution, not publication authority.
3. **`replace` means the original manager field replacement.** The observed replacement paths are object fields and caches, not the root words.
4. **`invalidate` means all manager caches are invalidated.** Noun vector invalidation and star map/cache invalidation are separate and differently scoped.
5. **`unpublish` means the original clears the slot.** No root clear path is recovered.
6. **A null root can be replaced by the other port.** That would collapse the unresolved phase/liveness boundary.
7. **Port values can be compared by address as durable identity.** The binary has no established durable identity for root pointers, and persistence reports reject raw pointer restoration.
8. **Four ports can be exposed to original plugins or vtables.** This would require the unresolved original ABI and is outside the clean-room boundary.

The clean-room decision should therefore be phrased as: **proceed with a compatibility-excluded, opaque four-slot observation boundary; do not implement original manager ownership or lifecycle emulation yet.**

The implementation should add negative tests for all unresolved states, not only the equal-manager happy path:

- both ports equal;
- noun ports unequal;
- star ports unequal;
- one port null while the other is live;
- rebind while a borrowed view is retained;
- rebind to an allocator-reused address with a new generation;
- noun cache invalidation after a missing-key lower-bound lookup;
- empire map erase while the player cache still points at the old object;
- manager teardown with no root clear yet;
- root clear with a manager still retained by another owner;
- restore/reconstruction producing new runtime object addresses.

## 10. Contradictory or stale local reports

These are not all fatal contradictions, but the primary report should surface them instead of flattening them into one settled account.

| Local report | Conflict or qualification | Effect on Blocker A |
|---|---|---|
| `root-closure/followup-global-slots.md:13-20,39-81` | Calls `DAT_0167eae0` and `DAT_0167eae4` manager-compatible and calls the second star accessor canonical, while `followup-receiver-provenance.md:13-20,131-137` keeps some receiver identity as a context/owner candidate and warns against promotion from co-call frequency. | Use “compatible layout” and “named accessor path”; do not call either root an owner. |
| `root-closure/followup-noun-boundary.md:7-13,15-52` | Claims raw control flow resolves `0x00b212d0` as a split continuation and identifies `0x00b21340` as the actual GetData implementation. The primary report instead leaves the SDK address/body identity unresolved. | The address identity is statically more resolved than the primary suggests, even though runtime/publication questions remain open. |
| `simulator-shared-state-interface.md:126-141,203-220` | Treats the noun path as mechanics with exact SDK function identity unresolved and preserves “unknown/approximation” vocabulary. | The primary should retain the mechanism/type distinction instead of repeatedly naming `cGameNounManager` as if the class were closed. |
| `root-closure/followup-global-slots.md:222-245` vs. `architecture-resolution/track-02-star.md:53-67` | One report says the committed xref projection has zero canonical star callers; the other incorporates raw disassembly of the unowned thunk. | The raw thunk should be included as a bounded static correction, while its caller/liveness remains unresolved. |
| `architecture-resolution/track-01-noun.md:57-78` vs. `simulator-shared-state-interface.md:126-141` | The former corrects the callback count to four plus noun ID; the latter retains an older five-argument description in places. | The final ABI contract must use four callbacks plus noun ID and mark the old wording superseded. |
| `blocker-c-primary.md:390-401` | Blocker C permits a clean-room persistence seam but blocks original restore/mode compatibility. | Blocker A must not turn the clean-room “can proceed” decision into permission to reproduce original root publication or persistence behavior. |
| `architecture-decisions.md:101-112,132-138,170` | Root identity/liveness is explicitly conditional on compatibility requirements. | The safe four-port decision is conditional, not a completed architecture decision for original compatibility. |

## 11. Minimum evidence needed before reopening the blocker

The following observations would materially change the decision:

1. **One concrete root writer or clear** for any of the four words, including a computed, bulk, table, or helper-argument path.
2. **One natural unequal/null/rebind window** for either noun or star pair.
3. **One natural teardown sequence** showing root clear/replacement and manager release order.
4. **One missing-ID successor case** for noun materialization and empire lookup, followed by erase and cache refresh, to confirm the static lower-bound consequences.
5. **One save/load round trip** if original persistence compatibility is required; static database replacement alone cannot establish root publication or restore identity.
6. **One concrete service-registration vtable instance** binding the noun or star manager object to a publisher, if root ownership is required.

Until those observations exist, the correct posture is not “four unknown publishers.” It is: **four physically distinct slots, four opaque observation contracts, at least two unresolved value relations, four unresolved root-lifecycle relations, and no recovered cross-root teardown order.**

## Final classification

- **Publisher:** unresolved; the direct negative is bounded and does not select an opaque mechanism as the leading explanation.
- **Storage:** four distinct four-byte slots are supported; four owners or lifetimes are not.
- **Lookup:** lower-bound/ceiling behavior is supported for the inspected noun and empire paths; exact-key behavior is not.
- **Materialization:** factory/list/map materialization is bounded; root publication and full ownership are unresolved.
- **Invalidation:** noun dirty-vector behavior is direct but lower-bound-selected; scope and failure behavior are incomplete. Star map and player-cache invalidation are separate.
- **Erase:** map erase is direct, but exact membership is not proven; successor removal remains possible.
- **Teardown:** manager/object cleanup bodies are direct; root unpublication and cross-root teardown order are not.
- **Ownership/lifetime:** selected manager fields and intrusive references are supported; root publication ownership, retained root lifetime, and post-teardown borrow rules are not.
- **Noun/star aliasing:** physical noun/star root aliasing is rejected; value aliasing and phase identity are open. Physical `cStar`/`cStarRecord` aliasing is rejected, but logical identity/cardinality is not closed.
- **Persistence:** star database replacement and runtime registry reconstruction are bounded; root serialization remains unevidenced and raw host-pointer persistence is unsafe for the replacement.
- **Implementation:** the four-port boundary can proceed only as a compatibility-excluded opaque observation seam with explicit host-side rebind/generation policy. It must not be described as four recovered owners or four original lifecycle operations.

**Bottom line:** the primary report should preserve its open-status conclusion, downgrade several “matching/owned/canonical” phrasings, and explicitly condition the four-port decision on non-compatibility. The boundary is safe as a conservative replacement seam, not as an original root/liveness model.
