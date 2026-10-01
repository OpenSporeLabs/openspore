# ABI capability extension — vftable slot membership and tail-call forwarding

Status: PROPOSAL, approved for implementation on the evidence recorded below.
Author: orchestrator, 2026-09-28. Supersedes nothing; extends
`docs/tooling/abi-inference-spec.md` with two rules, `V1` and `T1`.

Nothing in this document weakens an existing check. Both rules are **additional
disjuncts** placed where the engine currently emits `ABI_UNKNOWN`: they can only
turn an abstention into a positive claim, never turn a positive claim into a
weaker or different one, and they are inert unless the machine produces the
evidence they require.

---

## 1. The current rule, and why it is correct

`C10` (`abi_infer.py:2284-2306`) fires when no stack-argument read resolves, no
positive receiver evidence exists, and EDX is not read as an incoming base:

> C10 — CONV-NONE. *Conclusion:* `calling_convention = null`, `confidence =
> UNKNOWN`. *Why:* such a function is byte-identical under all four conventions.

**This is correct and must not be weakened.** The four x86-32 conventions differ
only in which register carries an argument and who pops the stack. A body with no
`ret N`, no `[ESP+k]` operand and no ECX read emits the same bytes under all four.
The conventional *name* is a property of the call site and the class, not of that
function. Emitting `__cdecl` here would be exactly the fabrication the engine
exists to prevent.

The consequence is that 33 of the 35 current frontier targets cannot reach a
static PASS, because the `ABI` dimension is `WARN` while the derived record
abstains. **The ceiling is real. It is also not the whole story**, because for a
subset of these targets the answer is recoverable from evidence the engine is
simply never shown.

---

## 2. Observed evidence

### 2.1 The engine has no input describing the function's own address

`analyze(disassembly, *, call_sites, ghidra_calling_convention,
ghidra_parameter_count, persisted_abi, image_base)` (`abi_infer.py:2844`). The
address is an **output** (`record["target"]["va"]`), never an input. `state
.vtable_loads` describes dispatches the function *performs*, and `D1` explicitly
refuses to call the offset a vtable fact:

> `vtable_offset` is a **candidate first slot** only. It is never called a
> vtable address and never promoted to `OBSERVED` vtable evidence.

`cross_validate` (`abi_infer.py:2674-2681`) already accepts external claims but
its documented precedence forbids them from *setting* `calling_convention`,
`sret.present` or `receiver.present`, or from promoting an abstention. A new
evidence class therefore needs a **new input and a new rule**, not a wider
`cross_validate`.

### 2.2 The frontier's 10 `no_discriminator` targets are vftable slots

Of the 35 frontier targets, 10 carry `no_discriminator: no stack-argument read and
no positive receiver evidence`. All 10 are the value of a dword inside a
maximal run of ≥2 `.text` pointers in `.rdata`/`.data`.

### 2.3 A sound vftable predicate exists, and it is stricter than the current one

The existing signal — `index["records"][va]["vtables"]`, from
`.spore-analysis/ghidra-exports/vtables.json` via `tools/triage/classify.py` — is
a **heuristic** and is badly contaminated. Measured on the real image:

* `0x00b1e4d0` (`XOR AL,AL; RET`) appears at **330 slot positions**, in 296
  vptr-backed tables. It genuinely is a virtual member of ~296 classes; ICF
  collapse means no rule can attribute it to one.
* `1,224 / 6,232` (19.6%) of code-referenced function-pointer runs are **not**
  vtables — they are callback/handler tables registered by initializers such as
  `FUN_0133ba60`.
* For `0x01053e00`, **all five** index-claimed vtables are unsound: `0x00c6a960`
  is not even in `.rdata` (it lies in `.text`), and the four `0x0149b8xx`/`0x0149ba30`
  entries are interior slot addresses of a 520-slot dispatch table, not table
  bases.
* This binary has **zero RTTI**: scanning all 870,231 `.rdata`/`.data` dwords
  yields **0** MSVC `RTTICompleteObjectLocator` records. Any rule leaning on a
  COL/RTTI slot is unsatisfiable here and was discarded.

**The sound predicate `P(T)`** (verified by an independent image scan;
`/tmp/opencode/abi2/vscan.py` reproduces these counts):

> **`P(T)` — `T` is a vptr-backed vftable base iff**
> 1. `T` lies in `.rdata`/`.data` and is the **base of a maximal run** of ≥2
>    consecutive dwords each holding a `.text` address; **and**
> 2. some code instruction is `MOV dword ptr [R + d], T` where `R` is a
>    general-purpose register **other than ESP or EBP**, the destination is **not
>    an absolute address**, and `0 ≤ d ≤ 0x40`; **and**
> 3. no other `T'` satisfying (2) lies in `(T, T+4i]` — the slot index is
>    well-founded.

Measured: 7,238 code-pointer runs, 6,911 vptr-shaped stores, 2,839 vptr-stored
bases, **1,007 tables satisfy `P`**. Clause 2's two exclusions are load-bearing:
`MOV [ESP+0x10],0x13eb428` (`0x009feb54`) and `MOV [EBP-0x2c],0x13eb428`
(`0x00404036`) are frame-local callback tables.

### 2.4 The falsifier: a vftable slot whose receiver is NOT in ECX

`0x01053e00` is a **frontier target** and its machine body is unambiguous:

```
01053e00: SUB ESP,0x18
01053e03: PUSH ESI
01053e04: MOV ESI,dword ptr [ESP + 0x20]      ; = entry_ESP+0x4
...
01053ecf: POP ESI
01053ed0: ADD ESP,0x18
01053ed3: RET 0x8
```

`SUB ESP,0x18` + `PUSH ESI` = 28 bytes, so `[ESP+0x20]` is `entry_ESP+0x4`: the
receiver is the **first callee-popped stack argument**, and the callee pops 8.
ECX carries the receiver of each *inner* virtual, not of this function. This is
the COM/`__stdcall` interface shape.

Consequence: **"vftable slot ⇒ `__thiscall`" is FALSE.** Membership alone would
have asserted a wrong ABI. This is the single most important finding in the
investigation, and it is why rule `V1` carries a cleanup guard.

---

## 3. Proposed rules

### V1 — vftable slot membership, register-receiver form

*Placed in `_infer_rules` between the `C9` arm and the `else` (`abi_infer.py:2274-2284`).*

**Precondition (all required):**
1. `P(T)` holds for some table `T`, and `dword[T + 4i] == target_va` for some
   `i ≥ 0` — the function is a slot of a vptr-backed vftable;
2. the derived cleanup is **`side == "caller"`** — the terminal is a bare `RET`
   (or `RET 0`), so the callee pops nothing;
3. `not keys` — no entry-relative stack-argument slot was resolved;
4. `receiver["present"] is not True` — no listing-derived positive receiver;
5. `not edx_incoming_deref` — no `__fastcall` reading.

**Conclusion:** `calling_convention = "__thiscall"`, `confidence = INFERRED`,
receiver `register = "ECX"`, `stack_arguments.total_bytes = 0`.

**Why it cannot be wrong.** Clause 1 makes the function a **non-static virtual
member function** — a virtual function is never `static`, so it has a receiver
and therefore a class. Clause 2 plus clause 3 mean the receiver is **not** in the
callee-popped stack area: the callee pops nothing, and no stack word is read as an
argument. On x86-32 MSVC the only remaining place a receiver can arrive is a
register, and of `__thiscall`/`__fastcall` only ECX carries it — clause 5 removes
`__fastcall`. There is no third possibility; the argument is a disjunction over an
exhaustive set, not a preference.

**Why clause 2 is load-bearing, not decorative.** On the current frontier, **12
targets satisfy clause 1 but fail clause 2** — sound vftable membership with
`cleanup.side == "callee"`: `0x0067dc80` (`App::IMessageManager::Get`),
`0x0067e6b0`, `0x0052e640`, `0x0052e650`, `0x0057d6f0`, `0x00642210`,
`0x00a85840`, `0x00a98400`, `0x00e5cac0`, `0x00f9fef0`, `0x00fa5040`,
`0x006a2e20`. Membership alone would have asserted `__thiscall` on all twelve.
`0x01053e00` is excluded by clause 1 *and* clause 2 independently.

**Recorded, not claimed.** `inferences[]` gains one `V1` entry citing the table
address, the slot index and the cleanup evidence. The record gains a
`receiver.provenance = "vftable_slot"` field so a reader can tell a listing-derived
receiver from a membership-derived one. **Class identity is never inferred** —
`0x00b1e4d0` in 296 tables yields "virtual member of some class", never a name.

### T1 — tail-call forwarding

*Placed before the `tail_call.present → force UNKNOWN` override (`abi_infer.py:2314-2318`).*

**Precondition (all required):** `S1` exactly one exit and no `RET` anywhere;
`S2` that exit is a **direct** `JMP imm32` to a static target; `S3` the target is
**not** inside the thunk's own body and is a **function entry**; `S4`
`esp_delta == 0` and not `after_frame_setup`; `S5` the target's own record yields
a concrete `calling_convention`; `S6` the thunk's observed argument area is
**compatible** with the target's (both 0, or equal); `S7` the target lies in
`.text` and is not an IAT/import pointer.

**Conclusion:** forward the target's `calling_convention` and `cleanup` at
confidence **capped by the target's own**, and record the hop as a cited
inference naming both VAs. The receiver's **adjustor delta** (the 8
`SUB ECX,imm ; JMP` thunks) is emitted as a distinct `receiver.adjustor_delta`
field; the receiver's *identity* is never copied.

Termination is a VA-keyed `visited` set plus a depth cap. All 17 direct chains in
this binary terminate at depth 2, but the engine's `tail_call.target` is
`state.transfer_out[-1]` and is provably wrong for `0x00847a90` and `0x01053be0`,
so termination must be enforced rather than assumed.

**S6 is load-bearing.** `0x007e6100` → `0x007e6135` is the one real false positive
of a naive rule: a `strcmp`-shaped loop whose `JMP` skips into its *own* body
(Ghidra splits it into two functions). It is caught independently by `S3` (the
target is not an entry — `getFunctionContaining` says `0x007e6130`), `S4`
(`esp_delta = 4`, an unmatched `PUSH ESI`) and `S6` (4 bytes of arguments against
the target's 20). A naive forward would have claimed "0 stack args, caller
cleanup" for a function with two cdecl stack words.

**`S2`/`S7` exclude a demonstrated impossibility.** `0x00847a40`
(`App::Canvas::func10h`) is a **vftable slot at `0x141ca98`** — so it must be
`__thiscall` — and tail-jumps to **`KERNEL32!SetThreadExecutionState`** on one arm
and `USER32!SetActiveWindow` on the other, both `__stdcall` callee-pop 4. The
receiver and argument conventions genuinely differ and no sound rule forwards
them.

---

## 4. What becomes provable, and what stays UNKNOWN

**Newly provable:** `__thiscall` with the receiver in ECX for a vftable slot in
register-receiver form (V1); and a thunk's convention and cleanup when it is a
single ESP-neutral static hop to a resolved target (T1).

**Explicitly still UNKNOWN, and why:**
* **51 residue targets** (global singleton getters, e.g. `0x00b3d300`
  `MOV EAX,[0x0167eae0]; RET`). Not in any function-pointer table. A `__thiscall`
  member compiling `return g_ptr;` emits these exact bytes, and caller-side
  evidence was measured and **falsified in both directions**: ECX is written
  before **80.2%** of their 8,971 direct call sites, and `0x00b3d300` — which is
  provably receiver-free — has ECX set 16 bytes before a call at `0x00b2960a`,
  consumed by an intervening vtable dispatch. There is no machine-only
  discriminator.
* **The 12 callee-cleanup vftable slots.** Membership proves a class; the cleanup
  form proves the receiver is *either* in ECX (a `__stdcall` class member) *or* in
  the popped area (a COM interface method). Distinguishing them needs
  "the first popped word is read as a pointer base", which is a **separate** rule
  with its own failure modes and is **not** proposed here.
* **Class identity**, for any target. Membership yields "some class".
* **A `__cdecl` free function** is never promoted by these rules; neither V1 nor
  T1 can reach it.

---

## 5. Why the change cannot create a false PASS

1. **Additive placement.** Both rules sit in the `elif` chain *before* the `else`
   that currently emits `C10`. With the evidence absent — the default — the arm is
   false, the `else` is reached, and every existing record is **byte-identical**.
2. **Inert by default.** The new input is keyword-only and defaults to empty. No
   test call site shifts; `analyze`'s existing parameters are already keyword-only.
3. **The engine may not be lied to.** Membership arrives as a new input, never
   smuggled through `cross_validate`, whose precedence already forbids setting a
   convention. `context.py:133-137` keeps a `DERIVED` ABI from ever making a
   document "complete".
4. **The falsifier is excluded twice.** `0x01053e00` fails `P` (all five of its
   index-claimed vtables are unsound) *and* fails the cleanup guard.
5. **Two independent guards on V1.** Membership alone misfires on 12 of 35
   frontier targets; the cleanup clause removes all of them. Both were measured,
   not assumed.
6. **No cross-validation abuse.** T1's confidence is capped by the target's own;
   V1 emits `INFERRED`, never `SUPPORTED`, so no later consumer can read it as
   stronger than an inference.

---

## 6. Affected goldens and expected corpus impact

* **No existing golden changes.** All 27 hermetic goldens and 12 live captures
  call `analyze` without the new input, so every expected value is unchanged. The
  new rules are covered by new fixtures.
* `cross_validate` at `abi_infer.py:2723` currently records a `disagrees` conflict
  when `inferred is None` — treating an **abstention** as disagreement, mirroring
  the Ghidra arm the docstring already exempts ("Ghidra silence is not
  agreement"). This opens a false conflict on `0x005a2320` and would do so on all
  25 `no_terminal_ret` targets. It is a **defect**, fixed on its own terms, and
  fixed by extending the same principle to abstention.
* **Expected impact, measured on the current frontier of 35:**
  * `V1` fires on **9**: `0x00980510`, `0x00b1e4d0`, `0x00b7e380`, `0x00b1fbf0`,
    `0x0051e340`, `0x0051e380`, `0x006e64f0`, `0x007f30d0`, `0x00fa0d50`.
  * `T1` fully resolves **1**: `0x0096ff70` (→ `__thiscall`, one 4-byte stack word,
    callee pops 4; independently corroborated because the target writes
    `0x1442584` into `[ESI+0xc]` and that vftable contains `0x0096ff70` at slot
    +3). `0x00980480` gains `cleanup = {callee, 4, OBSERVED}` but its target
    `0x00980330` still abstains, so its **convention stays UNKNOWN** — the
    cleanup gain is real, the convention is not claimed.
  * `V1` corpus-wide (all 610 packs) is measured in Phase 4 and recorded in the
    revalidation report, not predicted here.
* **Two targets become immediately promotable.** `0x00980510` and `0x00b1fbf0`
  are already reconstructed and are blocked **solely** by `ABI=WARN`;
  `EVIDENCE COVERAGE=WARN` does not block, because `validate.py:1470` excludes
  `COVERAGE_CHECK` from the `structural` set and the aggregate at
  `validate.py:1511-1521` reads FAIL/UNKNOWN/NOT_AVAILABLE/WARN from `structural`
  only. Resolving ABI moves both to static PASS.

---

## 6a. Implementation outcome — orchestrator rulings

Implemented and verified (full suite `1628 tests … OK`, 107 of them new). The
following items in §§2–6 were contradicted by the implementation. Rulings, so
nothing above is left standing as if it were true:

* **R1 — clause 3 (D4) direction. The implementation's reading is correct; the
  proposal's literal wording was wrong.** Read as "no other vptr-stored address
  inside `T`'s own run", clause 3 rejects 290 of 1007 candidates and yields 717,
  contradicting §2.3's own 1007 — and it is incoherent, because a vftable stored
  by several constructors is ordinary multiple inheritance. Implemented as the
  proposal's *stated purpose* — "a candidate may not be a slot of another
  candidate" — which is provably vacuous under clause 1 and is a harmless
  tightening. §2.3's number stands; clause 3's wording does not.
* **R2 — the §2.3 measurements were an artifact of the reference scan, not of
  the predicate.** The reference mapped one contiguous *file* blob across
  sections, running 1.3 MB past `.data` and sweeping most of `.rsrc` into the data
  range, and it read the `MOV` immediate at a fixed offset so every store
  carrying a displacement was dropped — making `0 ≤ d ≤ 0x40` dead code (all 6911
  of its stores have `d == 0`). Hand-decoded proof that the dropped stores are
  real: `0x00980c0d` is `C7 41 0C 14 43 44 01` = `MOV [ECX+0xC], 0x01444314`.
  Correctly mapped, the image yields **6232 code-pointer runs, 12601 vptr stores,
  4168 vptr bases, 1494 sound tables** — a strict **superset** of the reference
  set, so no target §2.2 relied on was lost. The §2.3 table is superseded.
* **R3 — rule ids.** `V1` and `T1` are already the spec's VARIADIC-SUSPICION and
  TAIL-CALL rules and are emitted today, so the new rules are `V1-VFT` and
  `T1-FWD`, registered through the same engine-local mechanism as `C6B`/`C8-E`.
  `infer_rule` now also *refuses an unregistered id*, mirroring `abstain`.
* **R4 — V1's confidence.** The proposal said V1 must emit `INFERRED` and "never
  `SUPPORTED`". V1 does emit `INFERRED`; observed records reach `SUPPORTED` only
  through the pre-existing `_bump` path, when the persisted oracle independently
  *agrees* (`cross_validation.persisted == "agrees"`), and `_bump` is hard-capped
  at `SUPPORTED`. That is corroboration, not assertion, and it is the engine's
  documented behaviour. No change made.
* **R5 — "two targets become immediately promotable" was wrong.**
  `0x00980510` is blocked solely by `ABI=WARN` and does become immediately
  promotable. `0x00b1fbf0` remains `WARN` after V1 because its source span names
  no convention, so the check now fails on the last arm instead of the confidence
  arm. Separately, **8 of the 9 frontier V1 targets are `NOT_AVAILABLE` with
  "target source span is not deterministically available"** — they are
  unreconstructed, so no dimension can move for them until a worker produces a
  source that names the convention. Those 8 are the *reconstruction* frontier
  this extension opens, not promotion-ready work.
* **R6 — the firing set is corpus-wide, not 9.** Measured over all 610 packs:
  **20 `V1-VFT` firings and 13 `T1-FWD` firings**; 11 targets move ABI
  `WARN → PASS`; 8 targets additionally move `FIELDS/OFFSETS`
  `NOT_AVAILABLE → PASS` (a consequence of `receiver.register = "ECX"`). No FAIL
  created, no PASS lost, 573 of 606 records byte-identical and the 33 that differ
  do so **only** by one of the two new rule ids.
* **R7 — `0x00847a40`'s sound table base is `0x0141ca70`**, not the `0x0141ca98`
  quoted in §4; that is an interior slot ten dwords in, which is the same
  contamination §2.3 documents for `0x01053e00`, now measured a second time. The
  target is still refused, by S2.
* **R8 — `0x006a2e20` was already `__thiscall`** before any membership existed
  (R1 + C6B: it reads its receiver through ECX and pops 8), so it was never a
  "membership alone gets it wrong" case. V1 refuses it on two independent counts.
* **R9 — no new evidence category.** Membership rides in `abi_derived`'s
  provenance. A new category would enter `validate.py`'s static denominator and
  move `EVIDENCE COVERAGE` for all 610 packs, and membership is not an
  independent oracle — it is a fact about the same image the listing came from.
* **R10 — open, for a future proposal:** the 12 callee-cleanup sound-slot targets
  need "the first callee-popped word is read as a pointer base" to separate a
  `__stdcall` class member from a COM interface method. That is a distinct rule
  with distinct failure modes (`0x00a85840` and `0x00a98400` pop 8 without
  reading the first word) and is deliberately **not** shipped here.

## 7. Rejected alternatives, and why

* **Caller-side ECX liveness.** Falsified by measurement, both directions (§4).
* **Identity getter (`MOV EAX,ECX; RET`).** Sound in principle — MSVC treats
  incoming ECX as dead under cdecl/stdcall, so consuming it as a value can only
  be ABI-defined — but **zero** occurrences in this bucket across 16.5 MB of
  `.text`. It buys one frontier target (`0x00e5cac0`, `MOV EAX,ECX; RET 0x4`) in a
  *different* bucket. Deferred: sound, but not this proposal's payload, and its
  generalised `LEA r32,[ECX+d]; RET` form has a known landmine (the engine does
  not record LEA destinations as defines, so a naive guard passes on
  `0x0104c4f0`).
* **RTTI/COL-based membership.** Unsatisfiable — this binary has zero RTTI.
* **Trusting `vtables.json` / `index.json` membership.** Measured precision under
  45%, with phantom entries; `0x01053e00` is a live counterexample.
* **Forwarding tail calls without `S3`/`S4`/`S6`.** `0x007e6100` demonstrates the
  false positive.
