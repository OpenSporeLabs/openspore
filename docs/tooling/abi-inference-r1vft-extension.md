# `R1-VFT`: the callee-pop receiver form

Status: shipped 2026-09-29. Rule id `R1-VFT`, in
`tools/reconstruction_tooling/abi_infer.py::_vftable_dispatch_receiver` and the
receiver block of `_infer_rules`. Test plan in
`tests/test_abi_inference.py::R1VftReceiverRuleTest` and
`::R1VftFalsifierTest`. Corpus groups in `tests/vftable_corpus.py`.

## The question this answers

`V1-VFT` fires on a sound vftable slot in the **caller**-cleanup shape and
rests the register receiver on that shape: nothing is popped and no stack word
is read as an argument, so the receiver is in a register, and of
`__thiscall`/`__fastcall` only ECX carries one.

The **callee**-pop shape was left out, and the previous session refused it as a
block with a single assertion — *sound membership plus callee cleanup must
change nothing at all* — over thirteen corpus targets. That assertion was two
claims wearing one name, and the second was wrong.

## The two shapes, and what separates them

A callee-popping vftable slot has two possible receivers:

* a **COM / `__stdcall` interface member** takes its receiver from the **first
  callee-popped stack word**. `0x01053e00` is the real shape: `SUB ESP,0x18` +
  `PUSH ESI` is 28 bytes, so `MOV ESI,dword ptr [ESP + 0x20]` is
  `entry_ESP+0x4`, and the body dereferences it.
* a **plain member that happens to pop its own arguments** receives `this` in
  **ECX** like every other member.

Membership alone cannot tell them apart: it is the same fact in both. Nor can
"the body reads ECX" alone, because a `__fastcall` first argument also arrives in
ECX. `0x00e51010` is that case and must stay out — its body is
`MOV ECX,dword ptr [ESP + 0x4]` … `PUSH ECX` … `MOV ECX,dword ptr
[0x016b3c0c]`: ECX loaded *from* the first popped word and forwarded as an
ordinary argument, incoming ECX never read.

Note that the engine's own `ecx_read_without_deref` reason does **not** make
that distinction. That reason is raised whenever ECX is read *anywhere*, and a
load *into* ECX counts. A rule keyed on the reason alone would have called
`0x00e51010` a register receiver.

## The rule

`R1-VFT` claims a **receiver register**, and nothing else. Every precondition:

| # | precondition | what it refuses |
|---|--------------|----------------|
| P1 | a *sound* membership (`vftable_memberships` has dropped every entry that cannot state `VFTABLE_BASIS`) | the record is byte-identical to the unarmed one |
| P2 | `receiver.reason == "ecx_read_without_deref"` | the three sibling reasons — `ecx_reassigned_before_deref`, `ecx_address_taken_without_memory_access`, `ecx_used_as_counter` — are different unknowns and stay unknown |
| P3 | at least one ECX read at an index **strictly below** `ecx_first_write` (`_incoming_ecx_reads`) | `0x00e51010`, `0x00e5c0f0`, `0x00e7d660` |
| P4 | `cleanup.side == "callee"` | the caller-cleanup shape, which is `V1-VFT`'s; one receiver fact gets one rule |

On the strength of those, `receiver.present` becomes `true`, `register` becomes
`"ECX"`, `provenance` becomes `"vftable_slot_dispatch"`, and confidence is
**`INFERRED`** — never higher, because the rule observes exactly one fact about
the receiver (which register) and its middle step is the same compiler-model step
`C8-E`/`C8` already make for EDX, which the module caps for the same reason:
assembly and intrinsic wrappers exist, and only external corroboration raises it.

`offsets` stays empty. The body never dereferenced the receiver, so the record
states *where* the receiver is and not *what it points into*.

## What it does not claim

The rule names **no convention**. That is the ordinary `C6B` arm, reading this
function's own `ret imm` and the receiver register this rule established. It
names no class (a slot is not a class; `0x00b1e4d0` is a member of 443 sound
tables), no vtable identity, no receiver type, no field, no layout. Every claim
is in `R1VftReceiverRuleTest::test_no_convention_class_or_layout_is_stated_by_the_rule`.

## The falsifiers

Sixteen mutations, in `R1VftFalsifierTest`, each paired with a *firing* control
so a negative is a real negative. The load-bearing ones:

| falsifier | mechanism |
|-----------|-----------|
| unrelated ECX writes | the def/use relation, not the reason code: `0x00e51010`'s shape stays refused, and a one-line move of the read makes it fire |
| ECX as a normal integer argument | same case, stated directly |
| stack-word receivers (COM form) | `0x01053e00` in miniature and in full; a membership *forced* on it is still refused |
| weak / malformed / absent membership | P1; the record is byte-identical to the unarmed one |
| caller-cleanup shape | P4; the claim stays `V1-VFT`'s and its `vftable_slot` marker is untouched |
| no callee pop | P4; a body with no `RET` never reaches the rule |
| the three sibling R0 reasons | P2 |
| incoming EDX (the C8-E collision) | the receiver claim stands, the convention does not, both readings stay |
| contradictory `ret` immediates | `cleanup.side == "CONFLICT"` is not `"callee"`, so the claim is withheld too |
| a membership for a different function | not transferable; a refused body stays refused whatever the slot |
| adjustor arithmetic alone | no membership, no claim — the mission's candidate direction, as a control |
| tail jumps and thunks | a thunk's receiver belongs to the target; `present` stays not-`True`, `register` stays `None` |
| register reuse around the call | P3, as a pair |
| a dispatcher is not a member | negative 5's shape, unchanged |
| the guard is load-bearing | by replacement: with `_incoming_ecx_reads` loosened, the three real targets the guard keeps out **fire**, and go back to refused when it is restored |

## The differential

687 inputs — 611 evidence-pack listings, 40 committed vftable captures, 24
fixture bodies, 12 live captures — with the real sound memberships recomputed
off the image. **32 records change: 22 distinct targets plus the 10 fixture
captures of 10 of them. Nothing else moves.** In particular `0x01053e00`,
`0x00e51010`, `0x00e5c0f0`, `0x00e7d660`, every caller-cleanup `V1-VFT` record,
every `T1-FWD` thunk, and fixtures 03/06/20 are byte-identical.

The 22 targets: `0052e640` `0052e650` `005774f0` `0057d6f0` `005a2050`
`005c5ee0` `005c8bc0` `00642210` `0067dc80` `0067e6b0` `0093b610` `00957510`
`0095f960` `00a85840` `00a98400` `00abf790` `00b267d0` `00c2e640` `00e310c0`
`00e5cac0` `00f968b0` `00f9fef0`.

## Independent corroboration, one witness per shape

Not one of the ten corpus targets that reached the queue relies on the rule, and
that is what makes overturning the earlier blanket refusal safe rather than lucky:

* `0x0052e650` — `0x0055c633` is `SUB ECX,0x8` immediately before the `CALL`: an
  adjustor, a pointer operation on `this`.
* `0x00e5cac0` — `0x007fbd90` is `ADD ECX,0xc` immediately before the `CALL`;
  the body forwards `this + 0xc`.
* `0x0057d6f0` — three this-adjusting thunks at `0x0057a5a0/b0/c0`
  (`SUB ECX,0x10/0x14/0x4; JMP`), and **no** direct call into it anywhere in the
  image.
* `0x00642210` — two `JMP` entries, `0x00642160` and `0x00642170`, each preceded
  by a `SUB ECX` adjustor.
* `0x0067dc80` — one `JMP` entry at `0x0067db00`, `SUB ECX,0x4`.
* `0x0052e640` — two direct call sites push three words and load ECX from the
  caller's own incoming ECX; the callee pops 12.
* `0x00a85840`, `0x00a98400` — the body adjusts the receiver itself:
  `LEA ECX,[ESI + 0x24]` (resp. `0x18`) with `ESI = MOV ESI,ECX`, then
  `CALL 0x00537dc0`.
* `0x00f9fef0` — `TEST EDI,EDI; JZ` then `LEA EBX,[EDI + 0x4]`: null-tested and
  then offset.
* `0x0067e6b0` — byte-identical in shape to `0x0067dc80`, which has a witness.

## The corpus split

`tests/vftable_corpus.py`'s `refused` group is split, because it always was two
groups:

* `dispatch_receiver` (10) — sound callee-pop slots whose body reads its incoming
  ECX. `R1-VFT` resolves these.
* `stack_receiver` (3) — `0x01053e00`, plus `0x00fa5040` and `0x006a2e20` as
  controls. The armed record is still **byte-identical** to the unarmed one, and
  the byte-identity assertion is still made.

`R1VftRuleTest::test_the_stack_receiver_shape_stays_byte_identical` is
re-scoped, not weakened: the same assertion, over a group every member of which
would be a real error to upgrade.

## What this did not do

`_apply_caller_corroboration` was investigated first and **rejected**, on
measurement rather than on taste:

* its `call_sites` input is not wired into the production pipeline at all —
  `evidence._derived_abi` calls `analyze(...)` without it, so the existing
  cleanup corroboration never fires either;
* of the twelve targets the ceiling blocked, **seven have no direct `CALL`
  entry at all** and two more are reachable only through `JMP` thunks, so
  caller-side evidence is structurally impossible for them, not merely weak;
* a `SUB ECX,imm` dominating a `CALL` exists for only five of the twelve, three
  of them through `JMP` thunks whose argument area belongs to a further-out
  caller;
* an adjustor alone is not a receiver: a caller may adjust an integer
  `__fastcall` first argument by a constant too. Pinned as falsifier 10.

The direction that the machine evidence actually supports is the one shipped, and
it needs no caller fragments at all.
