# Blocker B — Adversarial critique

**Reviewed artifacts:**

- `knowledgegraph/research/architecture-blockers/blocker-b-primary.md`
- `knowledgegraph/research/architecture-resolution/track-06-forwarded-state.md`
- `knowledgegraph/research/architecture-resolution/track-06-forwarded-state.json`
- `knowledgegraph/research/architecture-resolution/followup-02-forwarded-state.md`
- `knowledgegraph/research/architecture-resolution/followup-02-forwarded-state.json`
- `knowledgegraph/research/semantic-blueprint.json`
- `knowledgegraph/research/types/20-synthesis-blueprint.md`

**Method:** adversarial read-only cross-check, including read-only Ghidra spot checks of the target, accessor, field writers, constructor/allocation path, destructor family, mode normalizer, and canonical accessor. No source, `SPORE/`, Ghidra project, or canonical SQLite KG state was modified.

## Adversarial verdict

The forwarding mechanics and scalar mode-like use are well supported. The primary report nevertheless promotes identity, authority, first-writer order, and lifecycle beyond the evidence graph it actually establishes.

The decisive omission is an identity join. The report proves facts about a `GameModeManager`-shaped constructor family and facts about the object currently returned by `FUN_00b3d320`, but it never proves that the allocation constructed at `0x00b1d870` is the value published in `DAT_0167eaec`. That missing join invalidates the high-confidence receiver-class and target-pointee lifecycle claims, while leaving the mode-word interpretation useful but non-authoritative.

## 1. The two evidence islands are not joined

### Island A: a `GameModeManager`-shaped object family exists

Read-only evidence supports this chain:

1. `FUN_00b60d80` allocates a `0x9c` object at `0x00b61d72`.
2. It invokes `0x00b1d870` on that allocation at `0x00b61d80`.
3. `0x00b1d870` installs vtable `0x0145d7f0`, initializes `+0x20` and `+0x24` to `-1`, and clears the remaining derived fields.
4. The allocation is stored in the calling object's `+0x2c` field and inserted into a vector owned by that calling object.
5. The corresponding destructor family exists at `0x00b1d970`/`0x00b1dc40`.

This is strong evidence for one SDK-layout-compatible `cGameModeManager` construction family. The vtable data itself carries a `GameModeManager` name string, further strengthening that family's identity.

### Island B: `DAT_0167eaec` supplies a pointer whose `+0x20` word has mode semantics

This chain is also strong:

1. `FUN_00b3d320` returns the raw word in `DAT_0167eaec`.
2. `0x00b5b800` null-checks that word and reads `[word+0x20]`.
3. `0x00b289ac` writes `kLoadGameMode` to `[FUN_00b3d320()+0x20]`.
4. `0x00b5f056` writes the normalized destination/current mode to `[FUN_00b3d320()+0x20]` in the sole caller of `0x00b5f040`.
5. Scalar comparison consumers use the returned value as a mode discriminator.

The two direct field writers are immediate continuations of the exact accessor result, so they are genuine **pointee-field writers for the accessor's current result**. They are not evidence about an arbitrary object merely because another constructor happens to use offset `+0x20`.

### Missing bridge

Nothing in the recovered evidence establishes either:

- `DAT_0167eaec == allocation-base-from-0x00b1d870`; or
- `*[DAT_0167eaec] == 0x0145d7f0` at runtime.

The report states the distinction correctly in places, then collapses it in the executive claim. In particular, `blocker-b-primary.md:22` calls the receiver “strongly `cGameModeManager`-compatible,” while `blocker-b-primary.md:25`, `blocker-b-primary.md:108`, and `blocker-b-primary.md:225-227` acknowledge that construction/publication and canonical identity are unresolved.

**Adversarial classification:** `cGameModeManager` identity is high-confidence for the constructor family, but only candidate-compatible for the `DAT_0167eaec` pointee. “Strongly compatible receiver” is not justified at high confidence.

## 2. Global-slot writers versus pointee-field writers

| Address | Storage classified | What it proves | What it does not prove |
|---|---|---|---|
| `0x00b1d896` | Pointee field of the object constructed by `0x00b1d870` | Constructor-family initialization of `+0x20` to `-1` | That this object is ever published in `DAT_0167eaec`; that it is the first writer of the target pointee |
| `0x00b289ac` | Pointee field of the immediate result of `FUN_00b3d320` | The accessor's current pointee receives `kLoadGameMode` | Constructor provenance, canonical-slot equality, or lifetime safety |
| `0x00b5f056` | Pointee field of the immediate result of `FUN_00b3d320` | The accessor's current pointee receives the normalized destination/current mode | That the pointee is fresh, canonical, or uniquely owned |
| `0x0167eaec` | Global receiver slot | One direct read at `0x00b3d320`; no recovered direct writer | No computed, bulk, copy, or runtime publication |

This distinction also adjudicates the prior reports:

- Their **global-slot** negative remains valid: no direct writer to `DAT_0167eaec` was recovered (`followup-02-forwarded-state.md:18-31`; `track-06-forwarded-state.json:738-765`).
- Their broader “no `+0x20` writer” wording was too strong after `0x00b289ac` and `0x00b5f056` were found.
- Correcting the field-writer negative does **not** correct or supersede the global-slot negative.
- The constructor at `0x00b1d870` belongs in a third category: a structurally matching family initializer, not yet a target-slot writer.

The primary report notices the category distinction at `blocker-b-primary.md:121-141`, but later uses the constructor as the “first recovered field writer” for the target and as support for target-pointee construction.

## 3. Contradictions and overclaims

### C1 — High-confidence receiver identity contradicts unresolved publication

`blocker-b-primary.md:22` and `blocker-b-primary.md:330` assign high confidence to receiver class/layout, but `blocker-b-primary.md:25` and `blocker-b-primary.md:217-227` state that the slot-to-constructor path and canonical identity are unresolved. A constructor-shaped family is not a class identity for an unjoined pointee.

**Required downgrade:** “a `cGameModeManager`-compatible construction family exists; the target pointee is structurally and semantically compatible, but exact object identity is unconfirmed.”

### C2 — “Pointee construction/destruction” is a family-to-target category error

`blocker-b-primary.md:217-218` says pointee construction and destruction are supported. What is supported is construction and destruction of the `0x9c` object family allocated by `0x00b60d80`. No recovered instruction publishes that allocation into `DAT_0167eaec`, and no recovered instruction connects its destruction to clearing the slot.

The semantic synthesis blueprint explicitly warns that a manager, pool, factory, or accessor does not prove exclusive ownership (`types/20-synthesis-blueprint.md:48-55`) and that lifecycle stages are not complete without sequence evidence (`types/20-synthesis-blueprint.md:87-92`). The primary report's wording exceeds that contract.

### C3 — The constructor is not shown to be the first target field writer

`blocker-b-primary.md:121-127` correctly says its store is to an allocated pointee, not the global slot, but `blocker-b-primary.md:332` records it as the “first field initializer” without qualifying the object identity. It is first only in the constructor family's own lifecycle.

A target-field first writer remains unresolved because the target pointer's construction/publication chain is unresolved.

### C4 — “Earliest static mode writer” is not a first-writer criterion

`blocker-b-primary.md:141` and `blocker-b-primary.md:333` nominate `0x00b28990` because it is the earliest recovered non-initializing store **by address**. Address order is not execution order. More importantly, `0x00b60d80` is called from `0x00b63510` at `0x00b6364d`, and the mode commit at `0x00b5f040` follows at `0x00b63664` on the successful lazy-initialization path. If the constructed family is the target pointee, `0x00b5f040` is the immediate post-construction non-sentinel writer in that path; `0x00b28990` is a later special load-mode path.

Even without that conditional, neither address can be called the target's first writer before target publication is known.

### C5 — “Active mode ID” overstates authority and freshness

The direct stores make “mode-domain scalar” high-confidence. They do not establish that every non-null access to `DAT_0167eaec` returns the authoritative, fresh active mode. The report itself leaves semantic freshness unresolved (`blocker-b-primary.md:219-221`, `blocker-b-primary.md:334-336`).

A stale mirror, duplicate state object, or temporarily unpublished replacement can satisfy all cited writer and consumer facts while making “the active game-mode ID” false as an architectural authority claim.

**Safe formulation:** `+0x20` is a mode-ID-compatible scalar state word, apparently updated on mode transitions; whether it is always the canonical active value is unresolved.

### C6 — The `-1` result conflates two distinct origins

The exact root semantics are:

- zero global word -> synthesize `0xffffffff` before reading a pointee;
- nonzero global word -> return raw `[pointee+0x20]`, with no normalization in the root.

The constructor-family field initializer and the event normalizer can also place `-1` in a field. Therefore `0xffffffff` is a wire result with at least two possible proven origins: absent receiver and invalid/unset mode state. The root does not distinguish them.

`blocker-b-primary.md:24`, `blocker-b-primary.md:203`, and `blocker-b-primary.md:331` collapse these into one “no usable active mode/invalid normalized mode” meaning. The SDK helper cited by the report also does not normalize a non-null manager's field; it returns the field value. SDK corroboration therefore does not justify treating the two origins as semantically identical.

### C7 — “Refcounted” is not established for the manager object

`blocker-b-primary.md:215` says the constructor/destructor pair establishes a “refcounted/managed” family. The destructor releases contained objects and `0x00b1dc40` optionally frees the outer allocation, but no shared reference count for the manager object itself is shown. The local owner field/vector prove retention, not whether ownership is unique, shared, intrusive-refcounted, or merely lifecycle-managed.

**Safe formulation:** a managed object family with owner-container retention and teardown; outer-object sharing semantics remain unknown.

### C8 — “Borrowed during the read” does not establish lifetime safety

The root performs no ownership operation, so “no ownership transfer” is sound. However, the null test and field load are separate memory accesses with no lock or pin. If another thread can replace or destroy the pointee, the root has no statically demonstrated lifetime guarantee across them.

The primary correctly avoids exposing the pointer, but its “borrowed service object for the duration of the read” wording at `blocker-b-primary.md:207-211` can be read as a stronger guarantee than the evidence provides. It means “non-owning access shape,” not “concurrency-safe lifetime.”

### C9 — “Two manager access ports” is premature

`blocker-b-primary.md:227` recommends two manager access ports, although the object in `DAT_0167eaec` is not bound to the `cGameModeManager` family. The evidence supports two distinct raw pointer words/accessors, one SDK-named canonical getter and one unnamed getter.

They may contain the same pointer, different instances of the same class, different classes with shared layout, or one stale and one live object. Distinct storage addresses prove only that the slots are not storage aliases.

### C10 — The final typed API exceeds the demonstrated boundary

`blocker-b-primary.md:338-346` freezes `read_active_game_mode_id() -> uint32_t` and describes the result as a `cGameModeManager` receiver field. The semantic blueprint's interim boundary was narrower: borrowed opaque `uint32`, absent source `-1`, no ownership transfer (`semantic-blueprint.json:61-92`).

The new evidence justifies a named mode-domain adapter, but not authoritative active-state semantics or receiver-class typing. `uint32_t forwarded_mode_word()` or an explicitly non-authoritative `ForwardedModeId` is safer.

## 4. Aliasing conclusions

The primary report properly keeps aliasing unresolved, but its supporting language should be tightened:

- `DAT_0167eaec` and `DAT_0167eb2c` are distinct storage words; neither is a direct alias of the other.
- Pointer equality has not been observed.
- Different writers have not been bound to either slot.
- Absence of a common direct writer does not disprove value aliasing, because publication may be computed, bulk, copied, or runtime-populated.
- The same pointer in both slots would still not prove identical lifetime, ownership, or freshness semantics.
- The `cGameModeManager::Get` name on `0x00b3d420` is SDK/Ghidra naming plus a one-read body, not runtime confirmation that the other slot is an alternate publication of the same singleton.

The safe conclusion is only: **do not merge the slots or port identities yet**.

## 5. Smallest decisive observation

The smallest comprehensive observation is one naturally reachable, read-only **allocation-to-slot-to-field identity chain**:

1. At `0x00b1d870`, record allocation base `A` and vtable `0x0145d7f0`.
2. At the first non-zero return of `0x00b3d320`, record pointee `P` and the canonical return `C` at the same timestamp.
3. Record `P == A`, `P == C`, `*[P] == 0x0145d7f0`, and the first write to `[P+0x20]` after construction.
4. Continue only to the first replacement/clear/teardown of `P` or `DAT_0167eaec` if lifetime is part of the same trace.

This single bounded chain decides the central alternatives:

- `P == A` with the matching vtable binds the constructor family to the target pointee;
- `P != A` falsifies the receiver-class identity claim for the investigated instance;
- `P == C` establishes pointer aliasing, while `P != C` establishes observed separation only for that interval;
- the first recorded field mutation identifies first-writer order for that object;
- replacement/clear/teardown closes the lifetime claim.

A transition snapshot without teardown cannot decide lifetime. If no natural teardown is reachable, class/aliasing/first-write may be closed for one interval, but lifetime must remain open.

## 6. What can safely proceed

Safe now:

- Preserve the exact raw mechanics: read the global word; return `-1` when zero; otherwise copy `[word+0x20]` by value.
- Model the result as a non-owning, non-authoritative mode discriminator or `ForwardedModeId` adapter.
- Use the directly observed mode constants and normalizer behavior inside that adapter.
- Keep `DAT_0167eaec` and `DAT_0167eb2c` as separate ports with explicit `freshness_unknown` and `canonicality_unknown` states.
- Build mode-routing state-machine scaffolding around scalar comparisons without exposing the receiver.
- Plan the read-only identity trace above.

Not safe yet:

- Cast or expose the receiver as `cGameModeManager*`.
- Call the value the canonical active mode.
- Merge the alternate and canonical ports.
- Promise unique/shared/refcounted ownership or thread-safe pointee lifetime.
- Claim constructor or teardown of the target pointee.
- Claim a first writer or first mode transition.
- Treat `-1` as a single semantic state without documenting both possible origins.
- Persist, serialize, or replay the value as authoritative mode state.

## Bottom line

The primary report correctly supersedes the prior reports' overly broad “no `+0x20` writer” wording, but it must not use that correction to imply receiver identity or lifecycle closure. The durable result is a mode-domain scalar read-through with two unjoined ownership/identity axes: a structurally plausible `cGameModeManager` family, and an unpublished raw slot whose current pointee is written with mode values. The allocation-to-slot identity join—not another caller comparison or another SDK layout match—is the decisive missing observation.
