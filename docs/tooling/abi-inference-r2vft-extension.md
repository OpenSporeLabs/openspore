# `R2-VFT`: the address-taken receiver form

Status: shipped 2026-09-30. Rule id `R2-VFT`, in
`tools/reconstruction_tooling/abi_infer.py::_vftable_address_receiver` with
`_ecx_def_indices`, `_ecx_rooted_accesses`, `_incoming_member_leas` and
`_incoming_ecx_null_test`, and the receiver block of `_infer_rules`. Test plan in
`tests/test_abi_inference.py::R2VftReceiverRuleTest` and
`::R2VftFalsifierTest`. Corpus group in `tests/vftable_corpus.py`.

## The question this answers

`R1-VFT` resolves a sound callee-pop vftable slot whose body **reads** its
incoming ECX before writing it. It does not care what the body does with the
value, and that is its strength: it cannot distinguish `MOV ESI,ECX` from
`MOV EAX,[ECX+4]`. It has a matching weakness. A body that never *touches memory*
through the receiver at all — that copies nothing, dereferences nothing, and only
computes the **address** of something inside it — satisfies `R1-VFT`'s
`ecx_read_without_deref` guard only by accident of instruction choice. It does not
satisfy it, in fact: the engine's own `receiver.reason` for such a body is
`ecx_address_taken_without_memory_access`, which `R1-VFT` refuses as a *different*
unknown.

`0x009817c0` is the real shape:

```
009817c0  MOV EAX,dword ptr [ESP + 0x4]
009817c4  CMP EAX,0xeec58382
009817c9  JZ  0x009817e5
009817cb  CMP EAX,0xeef3af8c
009817d0  JZ  0x009817db
009817d2  MOV dword ptr [ESP + 0x4],EAX
009817d6  JMP 0x00951240            ; unhandled hashes: tail-delegate
009817db  TEST ECX,ECX
009817dd  JZ  0x009817ef
009817df  LEA EAX,[ECX + 0xc]
009817e2  RET 0x4
009817e5  TEST ECX,ECX
009817e7  JZ  0x009817ef
009817e9  LEA EAX,[ECX + 0x4]
009817ec  RET 0x4
009817ef  XOR EAX,EAX
009817f1  RET 0x4
```

Two LEAs, no dereference of ECX anywhere, ECX never written, callee pops 4. The
same sound membership, the same callee pop, the same incoming ECX, used as the
same thing — and a different reason code, so a different refusal.

So the two rules are separated by an **instruction**, not by a distinction between
two kinds of receiver. That is the point of the evidence.

## The proof obligation, and why the guard is enough

The load-bearing step is a fact about the x86-32 MSVC calling convention, not a
compiler heuristic. Enumerate the register parameters:

| convention | ECX on entry | who cleans |
|---|---|---|
| `__cdecl` | undefined | caller |
| `__stdcall` | undefined | **callee** |
| `__clrcall` | undefined | **callee** |
| `__thiscall` | **`this`** | caller (or callee under `/Gz`) |
| `__fastcall` | first argument | caller |
| `__vectorcall` (x86) | first argument | caller |

Now intersect with the cleanup. **An `__fastcall` callee never pops, and neither
does a `__cdecl` or `__clrcall` callee.** So for a body whose terminal `ret imm`
pops its own arguments, the only convention under which ECX is *defined on entry*
is the one callee-popping convention that has a register parameter at all — a
`__thiscall` that pops — and in it ECX is `this`. A body that reads an undefined
register is not a body a compiler emits.

The COM / `__stdcall` interface member, the shape that would otherwise take its
receiver off the stack, has no register parameter and therefore never reads its
incoming ECX. `0x01053e00` is the real shape of that and is still refused, and
the falsifier battery re-asserts it in miniature and in full, with a membership
forced on.

The residual risk is hand-written assembly and intrinsic wrappers. That is why
the rule is capped at `INFERRED` for the same reason `R1-VFT` and `C8` are: only
external corroboration raises it.

## Independent corroboration, from inside the binary

Not one of the five targets the rule resolves rests on it.

* **`0x00950eb0`** — the function three of them **tail-call into** — is a member
  of 17 sound tables, pops 4, and its body is `MOV EAX,ECX; MOV ECX,[ESP + 0x4];
  ...; TEST EAX,EAX; JZ; ADD EAX,0x4; RET 0x4`. `R1-VFT` **already resolves it**
  to `__thiscall` with `receiver.register == "ECX"`, on nothing but a copy. The
  machine fact this rule claims for the three bodies that tail-call into it is
  therefore already asserted by the shipped engine, for their own delegate. That
  is the sharpest evidence available and it is not a source declaration.
  Asserted in
  `test_the_delegate_of_every_witness_is_already_certified_thiscall`.
* **`0x00e3a400`** — the same hash-dispatch family at full size, with no sound
  vftable membership at all — dereferences ECX at offsets `0x310/0x324/0x328/
  0x32c` and adjusts it by `0x2c0`, and the engine already resolves it to
  `__thiscall` at `SUPPORTED` by plain `R1` + `C6B`. The siblings are refused
  only because their bodies offset `this` rather than dereference it.
* **`0x00969ac0`** — the constructor of the class whose table `0x009817c0` is a
  slot of — is `MOV ESI,ECX` ... `MOV dword ptr [ESI + 0xc],0x01441a2c`, so the
  table this rule names is installed into an object whose address arrived in
  ECX.
* The persisted Ghidra SDK decompilation of
  `UTFWin::ScrollbarDrawable::SetImage` is a member function. That is
  corroboration and it is deliberately **not** part of the argument: the rule
  reads no source, no name, no triage label, and no existing inferred receiver
  fact. The gate test is
  `test_the_membership_is_the_only_thing_that_moved_each_one`.

## The rule

`R2-VFT` claims a **receiver register**, and nothing else. Stated on positive
dataflow, not on `receiver.reason` — and that is not a style preference, it is
forced: `_receiver_evidence` ranks its unknowns in a fixed order (dereference,
then address-taken, then counter, then any read), so a body that both offsets
ECX and uses it as a `REP` count reports the *address-taken* reason and a rule
keyed on the reason would admit it. Pinned by
`test_11_a_rep_string_op_makes_ecx_a_counter`.

| # | precondition | what it refuses |
|---|--------------|----------------|
| V1 | a *sound* membership (`vftable_memberships` has dropped every entry that cannot state `VFTABLE_BASIS`) | the record is byte-identical to the unarmed one |
| V2 | `cleanup.side == "callee"` | the caller-cleanup shape (`V1-VFT`'s), a body with no terminal `RET`, a `ret 0x3` non-dword pop, and a *conflicting* cleanup — a conflict is not `"callee"` |
| V3 | `receiver_evidence.present is None` | one receiver fact gets one rule: an incoming dereference is `R1`'s, an `R-ALIAS` dereference is `R1`'s, and a post-write dereference is `ecx_reassigned_before_deref` |
| V4 | no memory access rooted at ECX at all, **including the indexed forms** `_record_ecx_access` skips (`MOV EAX,[ECX + ECX*4 + 0x8]`) | the dereference class, stated over a complete list |
| V5 | `state.ecx_rep` is false | a repeat count is an ordinary integer |
| V6 | ≥1 **incoming member `LEA`** | everything below |

### V6, the address-taking, exactly

A site qualifies when **all** of these hold, and it is derived from the parsed
instruction stream, not from `state.ecx_addr_taken`:

* `LEA r32, [ECX + k]` — base register **ECX**, **index register absent**;
* the rendered operand names `ECX` **exactly once**. `[ECX + ECX + 0x4]` is a
  sum, and the parser reports it exactly as it reports `[ECX + 0x4]`: base `ECX`,
  no index, displacement 4. The count is taken on the operand's own text because
  the two are not otherwise distinguishable;
* the **destination is not ECX** — `LEA ECX,[ECX + 0x8]` is a `this` adjustor,
  a *write*;
* `0 <= k`, `k % 4 == 0`, `k <= 0x7fc` (`MAX_MEMBER_DISPLACEMENT`). A negative
  displacement is a pre-adjustment, a non-multiple of four cannot be the offset
  of any scalar in a 32-bit object, and the cap bounds the claim to an
  object-sized address rather than a mask. **This is a narrowing, not the
  load-bearing step**, and it is labelled as one;
* **no ECX definition at or before the site** (`_ecx_def_indices`).

The last condition is the def/use relation, and the rule states its own rather
than reading `state.ecx_first_write`, because three classes of definition never
reach that field and each is a false positive for a rule keyed on "the incoming
ECX":

| missed definition | why it is a definition |
|---|---|
| `LEA ECX,[ECX+0x8]` | `STORE_MNEM` has no `LEA`, so an adjustor written as a `LEA` records nothing and becomes indistinguishable from a member address |
| `XCHG r,ECX` | `_is_store` is only true for operand 0, so an exchange's second operand defines nothing |
| `CALL` | ECX is volatile in x86-32, so a read after a call reads the callee's leftover, and there is no register operand to record it against |

A tail `JMP` is **not** a definition: it passes ECX through. Each of the three
has a falsifier, and the call one is a falsifier the previous session's
extraction would have admitted.

On the strength of that, `receiver.present` becomes `true`, `register` becomes
`"ECX"`, `provenance` becomes `"vftable_slot_address"` — a third string, so the
three derivations can never be confused with one another — and confidence is
**`INFERRED`**, never higher.

### `TEST ECX,ECX` is corroboration, not a precondition

`_incoming_ecx_null_test` reports whether the body null-tests the *incoming* ECX
and branches on it, and the rule **neither requires nor refuses on it**. A
compiler may omit a null guard where the caller guarantees a non-null `this`
(`__assume`), so "the body null-tests `this`" is not a property the ABI
guarantees, and requiring it would fit the rule to the fixtures rather than to the
machine. It is reported because it is decisive evidence *when present*: a
`TEST ECX,ECX` followed by a conditional branch guards against exactly the
failure a null receiver produces, and no integer-argument reading of the same
body explains one. `test_2_a_null_test_alone_is_not_a_receiver` asserts both
directions: the rule fires with the test removed, and a test with no
address-taking is the receiver-*absent* reading.

### What it does not claim

No convention (that is the ordinary `C6B` arm, read off this function's own
`ret imm`). No class, no vtable identity, no receiver type, no field, no layout.
In particular the `LEA` displacements — `0x4` and `0xc` on the witness — are
**not** published as `receiver.offsets`, which means displacements the body
actually dereferenced through the receiver; this body dereferenced nothing, so
they stay empty. The displacements appear only inside the rule's own `value`, as
`member_lea_sites` and `member_lea_displacements`, next to
`incoming_member_leas` and `incoming_ecx_null_test`.

## A guard that was written, measured and rejected

"A register loaded from the first popped stack word is never dereferenced" is the
obvious seventh guard, and it is **not** in the table. It is not a soundness
requirement — the register-parameter argument above already excludes the COM
reading without it — and it refuses a real shape: a `__thiscall` that takes a
pointer argument on the stack and dereferences it. `test_16_a_stack_pointer_
argument_is_not_a_second_receiver` pins the decision so it cannot be re-added as
an unexamined conservatism.

The other rejections are named rather than silently absent:

* **multi-arm control flow** is *allowed*, and the witness is three arms. The
  engine's model is a linear walk, so "incoming" is decided by listing order: a
  body whose write textually precedes the address-taking is refused even when the
  two are on different arms. That is a conservative refusal, stated in
  `test_19`, and it is a decision rather than an accident.
* **indirect dispatch** is *allowed* when the address is computed from the
  incoming ECX and no memory is touched *through* it
  (`LEA EAX,[ECX + 0x4]; MOV EDX,[EAX]; CALL EDX`). The register-parameter
  argument is unchanged, and the rule must claim nothing about the table at
  `[EAX]` — asserted in `test_20`.
* **an `R1-VFT` collision** (a callee-popping body that also reads its incoming
  EDX) is the C8-E collision: the receiver claim stands and the *convention* is
  withheld with `ecx_and_edx_indistinguishable`. Same shape as `R1-VFT`, pinned
  in `test_21`.

## The falsifiers

`R2VftFalsifierTest` is twenty-eight mutations, each paired with a *firing*
control so a negative is a real negative. The battery was written **before** the
engine change: with the rule absent, every negative already passed and every
positive failed, which is the signature of a battery that is actually
load-bearing.

| falsifier | mechanism |
|-----------|-----------|
| ECX as an integer argument loaded from the first popped word | the def/use relation: the write precedes the site |
| a null test with no address-taking | the receiver-*absent* reading (R2), not R2-VFT |
| ECX from a frame local / an immediate / a register / a `pop` | same |
| scaled, indexed and summed address arithmetic | base, index and the single-naming count |
| negative, unaligned, and past-the-cap displacements | the member-displacement narrowing |
| an ECX write before the site, in eight forms | the def/use relation, ordering-sensitive |
| a call before the site | ECX is volatile: `_ecx_def_indices` |
| register reuse, `XCHG`, an adjustor written as a `LEA` | the same three definition classes |
| caller cleanup; no `RET`; `ret 0x3`; conflicting `ret`s | V2, and one receiver fact gets one rule |
| a `REP` string op anywhere in the body | V5, read positively and **not** off the reason code |
| incoming deref, `R-ALIAS` deref, post-write deref | V3 — `R1` owns the first two, the third is a named ceiling |
| a membership that cannot state its basis; ten malformed shapes; no membership | V1, and malformed input is byte-identical to no input |
| membership for a slot that does not exist; a membership borrowed across functions | V1 plus the evidence layer's own memberships are asserted to be the image's |
| the COM / `__stdcall` stack receiver, miniature and real, with memberships forced | the register-parameter argument |
| a stack *pointer argument* alongside the receiver | allowed, deliberately: `test_16` |
| an adjustor alone; a thunk | a write is not a read; a thunk's receiver is the target's |
| multi-arm, three-arm, and the reordered arm | linear-walk honesty |
| indirect dispatch through a computed address; through a member of the receiver | allowed, and claims nothing about the table |
| the incoming-EDX collision | the convention is withheld, the receiver is not |
| the address-taking instruction deleted, or its base changed | V6's existence |
| every guard replaced by a stand-in | `test_24`: three mutations, and the negatives each guard exists for then fire |

`R2VftReceiverRuleTest::test_the_whole_committed_corpus_moves_exactly_the_new_
group` re-derives the whole boundary: every other committed capture, with its
real sound memberships, must produce exactly the record it produced before the
rule existed.

## The differential

**703 inputs** — 607 evidence-pack listings, 48 committed vftable captures, 29
fixture bodies, 12 live captures and 7 tail-forward pairs — with the real sound
memberships recomputed off the image. Against the pre-change engine: **689
unchanged, 13 changed, 0 errored**, plus 1 input that did not exist before.

The 13 are the six new corpus captures and exactly seven records:

* `0x00841540` — `ABI_UNKNOWN` → `ABI_INFERRED`, no convention → `__thiscall`.
* `0x009646d0`, `0x009672d0`, `0x00980330`, `0x009804e0`, `0x009817c0` — no
  convention → `__thiscall`, and three receiver abstentions
  (`receiver_not_determinable`, `ecx_address_taken_without_memory_access`,
  `receiver_undetermined_blocks_convention`) all retired. Their *verdict* stays
  `ABI_UNKNOWN` because each transfers out of the listing to a hash delegate, so
  `T2` stands: the receiver claim and the tail-transfer claim are separate facts
  and this rule only makes the first one.
* `hop:0x00980480` — `T1-FWD` moves from forwarding the *cleanup* at `OBSERVED`
  to forwarding the *convention* at `INFERRED`, because its tail target
  `0x00980330` now has one. Its `cleanup` block is byte-identical: the same
  `callee`/4/`OBSERVED`/`forwarded_from_tail_target`, and its `receiver` is
  still `present: false`, because a thunk's receiver is the target's.

Nothing else moves. In particular `0x01053e00`, `0x00e51010`, `0x00e5c0f0`,
`0x00e7d660`, `0x00fa5040`, `0x006a2e20`, every caller-cleanup `V1-VFT` record
and every `T1-FWD` thunk is byte-identical, and the seven committed
`tests/expected/abi` fixture goldens do not move at all — this rule adds no
observation kind, so no record's `observations` list changes.

## The reach, measured

Not the corpus the suite regresses against: **every queue function the image
proves is a slot of a vptr-backed vftable** — 223 of them — disassembled live
and run through the shipped engine with its real memberships.

| rule | targets |
|------|---------|
| `R2-VFT` | **5** |
| `R1-VFT` | 23 |
| `R1` | 152 |
| undetermined | 17 |
| receiver absent | 26 |

The five are `0x00841540`, `0x009646d0`, `0x009672d0`, `0x009804e0`,
`0x009817c0`, and all five move from *no convention at all* to `__thiscall`. That
is the rule's whole reach in the reconstruction universe: it is exhausted, and
the campaign below is what it was worth.

`0x00980330` is not a queue target — it is only a tail target — and it is the
one that makes the reach worth more than its face: see the next section.

## What the campaign promoted

Five targets, in three waves, all from this rule and the machinery it feeds.

| target | how | before |
|--------|-----|--------|
| `0x009817c0` | `R2-VFT` directly | `ABI` WARN, receiver undetermined |
| `0x00980480` | `R2-VFT` on its tail target `0x00980330`, then `T1-FWD` | no convention; the hop's convention abstained |
| `0x007d9410` | `T1-FWD` on `0x007d9bb0` (an `R1-VFT` body: slot 2 of a sound table, pops 4, `MOV ESI,ECX`) after a **live** re-collection | no convention; the pack predated the hop target's listing |
| `0x009672d0` | `R2-VFT` directly | `validation_warn` |
| `0x009804e0` | `R2-VFT` directly | `validation_warn` |

`0x007d9410` is worth naming separately because it is **not** R2-VFT's doing: its
own body is `SUB ECX,0x4; JMP`, an adjustor thunk, and its blocker was a stale
evidence pack. Re-collecting it live let the pipeline resolve its hop target from
the bridge, and the shipped `R1-VFT` then did the rest. It was found by applying
the same stale-pack check the `0x00980480` unlock had already taught, and it is
reported as a separate cause rather than folded into the rule's tally.

`0x009646d0` is already reconstructed under `PKG-UTFWIN-LAYOUT-WAVE6`; its ABI
record improved under it and no second package was created.

## What this did not do

`0x007d9410` and `0x00980480` were on the list of *genuine ABI ceilings*, and
both were resolved. Neither was resolved by laundering: no confidence was
raised, no verdict was asserted that the evidence does not carry, and no ceiling
was redefined. `0x00980480`'s convention arrives through `T1-FWD`, the
already-shipped forwarding rule, from a hop target whose receiver this rule
established from the same machine facts it establishes everywhere else. The
ceiling was real; it was the *hop target* that was unresolved, and it is
resolved now.

The remaining ceilings are untouched and remain ceilings. `0x01053db0` and
`0x01053e00` are `ecx_reassigned_before_deref` with **no** sound membership, so no
vftable rule can reach them. `0x00e7b6c0` and `0x00e7d2c0` have no sound
membership either. `0x00e3a400` has none and already reads `__thiscall` at
`SUPPORTED`; it is blocked by the integrator-owned null index identity and a
non-function-entry xref record. `0x00fa5040` is a COM / `__stdcall` stack
receiver behind an untrusted frame pointer (`C11`, `esp_alignment_unknown`).
`0x01053be0` and `0x00f96840` are listings with no terminal `RET`, so the path
that returns was never observed. `0x00f9fef0` reads `__thiscall` already and is
blocked by `GLOBALS`, return semantics and unfinished model tests.
