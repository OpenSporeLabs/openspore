# ABI inference engine — specification

Pure, deterministic x86-32 ABI-fact inference over Ghidra disassembly text for
`SporeApp.exe` (MSVC, `x86:LE:32:windows`, image base `0x00400000`).

Target module: `tools/reconstruction_tooling/abi_inference.py`
Target consumer: `tools/reconstruction_tooling/evidence.py` (new evidence
category), surfaced to `context.py` (`06_abi`) and `validate.py` (check `ABI`).

## 0. Scope, and what the engine is forbidden to do

The engine answers **one** question: *given only the instruction stream of one
function, what can be established about how it is called and how it returns?*

It is a pure function. No file system, no Ghidra, no network, no clock, no
randomness, no globals mutated across calls. Input is disassembly text (plus
optional caller fragments and optional external claims); output is a JSON-shaped
dict. Same input bytes ⇒ byte-identical output, always.

The engine **never** produces a C++ type, a parameter name, a class name, a
field name, or a prototype string. It produces:

* calling convention **names** (`__cdecl`, `__thiscall`, `__stdcall`,
  `__fastcall`) or `null`,
* a **register** for the receiver,
* an **argument slot table** (entry-relative offsets, ordinals, widths),
* a **cleanup side and byte count**,
* a **return register** and a **value class**,
* a **candidate** (never a conclusion) for a hidden struct-return pointer,
* offset and entropy bounds for layout reasoning,
* an explicit list of reasons it declined to conclude.

`ABI_UNKNOWN` with a populated `abstained_because` list is a **successful**
result. It is the expected result for a large fraction of this binary, and the
fixture set asserts it explicitly.

### 0.1 Empirical baseline this design is calibrated against

Measured over all 58,757 functions of `SporeApp.exe` in the current Ghidra
project. These numbers are the reason the design is as conservative as it is:

| Fact | Count | Consequence for the design |
|---|---|---|
| Ghidra `getCallingConventionName()` == `unknown` | 58,691 / 58,757 (99.89%) | Ghidra is not an oracle. Cross-validation is almost always a no-op. |
| Ghidra `getParameterCount()` == 0 | 58,280 (99.1%) | Ghidra contributes nothing about arguments. |
| Ghidra names a real convention | `__cdecl` 30, `__stdcall` 28, `__thiscall` 7, `__fastcall` 1 | `SUPPORTED`-by-agreement will be rare. Say so, do not fake it. |
| `ret` with an immediate | 31,152 instructions | `ret N` is the cleanup oracle. |
| functions with **no** `ret` | 4,806 (8.2%) | Must abstain, not guess. |
| functions with >1 `ret` instruction | 13,375 | Multiple exits are normal. |
| functions whose `ret` immediates **disagree** | **0** | MSVC normalises per function. A disagreement means hand-written asm, tail-merging, or a bad listing — all hard abstentions. |
| ECX used as a memory base | 25,349 | Receiver detection is the highest-value signal. |
| … of those, ECX **never spilled** to a local | 13,954 (55%) | The dominant MSVC idiom is the *spill*; receiver detection must handle direct, spill, and alias forms. |
| last instruction is a `jmp` | 5,335 (9.1%) | Tail calls are common ⇒ thunks need a first-class shape. |
| `push ebp` without `mov ebp,esp` | 11,995 | Frame pointer is not guaranteed; ESP-based argument resolution is mandatory. |
| `lea esp,[ebp-N]` | 2,282 | A third frame-teardown idiom. |
| `and esp,0xfffffff0` | 1,375 | **Poisons ESP-relative resolution** unless a frame pointer exists. |
| `FS:`/`GS:` segment operands | 1,888 | SEH/cookie frames. Must be classified, and must *not* be read as variadic evidence. |

## 1. Input contract

```python
analyze(
    disassembly,                 # see 1.1
    *,
    call_sites=(),              # tuple of caller fragments, see 1.3 (default: empty)
    ghidra_calling_convention=None,   # str | None
    ghidra_parameter_count=None,      # int | None
    persisted_abi=None,              # dict | None (record["abi"])
    image_base=0x00400000,           # int; used only for the address-like-immediate test
) -> dict
```

All keyword arguments are optional and every default preserves a conservative
verdict. `image_base` participates in determinism, so it is part of the
function's identity: a different base can produce a different record, and the
record echoes the value it used.

### 1.1 Accepted disassembly shapes

The real REST endpoint (`/disassemble_function`, consumed today by
`evidence.py::_live_disassembly`) returns **no bytes column**:

```json
{"instructions": [{"address": "0040ccb0", "instruction": "PUSH EBP"},
                  {"address": "0040ccb1", "instruction": "MOV EBP,ESP"}],
 "count": 2}
```

`normalize_listing` accepts, in this order:

1. `list[{"address": str|int, "instruction": str}]` — the primary shape.
2. `dict` with an `"instructions"` list (value of shape 1); `"count"` ignored
   after being cross-checked against `len(instructions)`.
3. `list[str]` — raw listing lines (shape 4, one element per line).
4. `str` — a raw CodeBrowser listing, with or without an address column and
   with or without a raw-bytes column.
5. `None` / `""` / `[]` — an **empty listing**, which is a legal, tested input
   (§5 F19) that yields `ABI_UNKNOWN` with `empty_listing`.

Anything else raises `ValueError`. Silently coercing an unrecognised shape is
forbidden.

### 1.2 Text-listing line grammar (shape 4)

Applied left to right, greedily, per line:

```
line      := WS* [ address WS+ ] [ bytes WS+ ] mnemonic-text
address   := "0x" HEX+          |  HEX{6,8}          ; bare address needs >= 6 digits
bytes     := ( HEX{2} WS+ ){1,15}                     ; one or more byte groups
mnemonic-text := <one or more tokens, no comment>
```

Comment stripping happens first: cut at the first `;` or `//`, then `rstrip()`.

Column reliance and degradation, exactly:

| Column | Relied on? | If missing | If present but malformed |
|---|---|---|---|
| address | optional | `va = None`; `index` (listing position) remains the provenance key. Every record carries `"address_available": false` and no address-based citations are emitted — citations fall back to `index`. | A first token of 1–5 hex digits is **not** an address (it is a byte group or a mnemonic), so `55` is never mistaken for an address. This is what makes shape 4-without-address unambiguous. |
| raw bytes | ignored for semantics | n/a | A `bytes` match is only consumed if non-empty text remains after it. `00401230  00 00 00 00` (data, no mnemonic) therefore yields a `DATA_BYTE` observation and no instruction, instead of a garbage mnemonic `00`. |

Ordering hazard, resolved: after an address, `55` (2 hex digits) cannot be an
address (needs 6+), so it is consumed as a byte group. `00401230` is 8 digits so
it is an address. No ambiguity is reachable in this address space.

### 1.3 Caller fragments (`call_sites`)

Cleanup side cannot be *proved* from the callee's own listing; it is decided by
whether the callee's `ret N` is immediate. Caller-side corroboration
(`add esp,imm` after the call) is an optional cross-check:

```python
call_sites = ({"call_va": "0x00401260",
               "after": ["ADD ESP,0x8", "PUSH EAX"]}, ...)
```

`after` is a short verbatim instruction-text list taken from the caller. Only the
first ≤6 entries are used. If `call_sites` is empty — the default, and the only
mode reachable from today's `evidence.py`, which fetches one function — the
engine reports `cleanup.corroboration = "not_available"` and does **not** weaken
or strengthen anything. See rule **C-CALLER-XVAL** (§2.9).

### 1.4 Lexer

`split_operands(body)` splits on `,` at bracket depth 0, tracking `[`/`]`.

`parse_operand(text)` returns exactly one of:

```python
{"kind":"reg",  "reg":"ECX", "text":...}
{"kind":"imm",  "value":<int>, "text":...}          # 0x.. or bare decimal/hex
{"kind":"mem",  "size":<1|2|4|6|8|10|16|32>, "segment":"FS"|None,
               "base":"ECX"|None, "index":None, "scale":None,
               "disp":<signed int>, "text":...}
{"kind":"target","value":<int>, "text":...}          # 0x0041dca0 in CALL/JMP
{"kind":"symbol","text":"DAT_016b3c04"}
{"kind":"opaque","text":...}                        # never guessed
```

Memory-operand forms that occur in this binary and **must** parse (each one is
covered by a fixture or by a regression test against the real listing):

```
dword ptr [EBP + -0x48]        negative displacement
dword ptr [EBP + 0x8]          positive
dword ptr [EBP + 0xfffffef4]   Ghidra prints negatives UNSIGNED in 8 hex digits
word ptr [ECX]                 no displacement at all
MOV EAX,[0x016f2618]           no size prefix, absolute address
dword ptr FS:[0x2c]            TLS, with size
MOV EAX,FS:[0x2c]              TLS, no size, no space before the bracket
float ptr [ESP + 0x8]          x87 float load (NOT "dword")
dword ptr [EDX + ECX*0x4]      base + scaled index
dword ptr [EDX*0x4 + 0x417cc0] index + absolute
xmmword ptr [0x013eb8b0]       16-byte
[EBP + -0xc]                   LEA: no size prefix
MOVSD.REP ES:EDI,ESI           Ghidra decode artifact (see 1.5)
XADD.LOCK dword ptr [EAX],ECX  Ghidra decode artifact
```

Size token table: `byte 1, word 2, dword 4, qword 8, tbyte 10, fword 6, oword 16,
xmmword 16, ymmword 32, float 4, double 8, near 4, far 4`. Default when no size
token is present: `4` (and the record flags `size_inferred: true` on that
observation so a reader knows the width is a convention, not a reading).

Displacement normalisation (`norm_disp`), exact:

1. Strip a leading `-`; remember the sign.
2. Parse the rest as hex if it starts `0x`, else as decimal.
3. Re-apply the sign.
4. **Additionally**: if the literal is bare (no `0x`), exactly 8 characters, and
   ≥ `0x80000000`, subtract `0x100000000`. This is required — `0xfffffef4` in
   a real listing means `-0xc`.

### 1.5 Mnemonic normalisation

`mnemonic := BASE [ "." SUFFIX ]`, both uppercased.
`BASE` is used for semantics; `SUFFIX` is kept for artifact classification.

Ghidra emits `MOVSD.REP` and `MOVSS.REP` for string moves it mis-decodes, and
`XADD.LOCK`. These are **not** silently normalised: each emits a `STRING_OP`
observation (for `*.REP`/`*.LOCK` on a `MOVS`/`STOS` base) listing the clobbered
registers, because a REP count lives in ECX and therefore *destroys* ECX-as-
receiver evidence. An unrecognised mnemonic is still parsed for operands; only
the operand-shape rules are skipped.

### 1.6 AT&T fallback

Listing-wide detection: if ≥ 50 % of lines match `RE_ATT`
(`(^|\s)[a-z][a-z0-9]*[lqw]\s` or `retq`/`pushq` or `\$\(` or `\(%\w` or
`-?\d*\(%\w`), set `"syntax": "att"` and run the AT&T normaliser before the
Intel path: reverse operand order, strip `$`, `-4(%ebp)` → `base=EBP, disp=-4`,
`4(%eax,%ecx,8)` → `base=EAX, index=ECX, scale=8`, `(%eax)` → `base=EAX, disp=0`,
`*%eax` → load, `ret $0x10` → `ret 0x10`, `movl` → `mov`.

A **mixed** listing is not guessed at: lines that fail the AT&T grammar while
`syntax == "att"` emit `UNPARSED` observations and set
`parse.degraded = true`. `parse.degraded` never lowers confidence on its own
(partial parsing can only *remove* evidence, never add it), but it is reported,
and any rule whose precondition needs the dropped lines simply fails to fire.

## 2. Stage 1 — observed facts

**No inference lives in this stage.** Every entry is a fact read off one
instruction, or an arithmetic total over such facts.

### 2.0 Canonical ordering and identity

Observations are emitted in **strict listing order**, so `index` is
monotonically non-decreasing and, when addresses are present, so is the address.
Ids are assigned at emission: `"obs-%04d"`, 1-based. Implementations **must**
renumber after any multi-pass internal organisation; a record whose ids are not
in listing order is invalid. (The throwaway prototype used for cross-checking
this document emits in pass order; the spec requires listing order and the
fixtures assert on `index`, not on pass layout.)

Common fields on every observation: `id`, `kind`, `index`, `at` (or `null` when
`address_available` is false), `raw` (the verbatim instruction text).

### 2.1 Kinds

| `kind` | fields | meaning |
|---|---|---|
| `DATA_BYTE` | `count` | line had a bytes column and no mnemonic; not code |
| `UNPARSED` | `reason` | line matched no grammar rule; `reason ∈ {no_mnemonic, att_mismatch, unknown_mnemonic}` |
| `FRAME` | `push_ebp`, `push_ebp_at`, `mov_ebp_esp`, `mov_ebp_esp_at`, `sub`, `lea_esp`, `and_esp` | frame shape; emitted once, at the prologue |
| `ESP_ADJUST` | `delta`, `at` | one `sub/add esp,N`, `lea esp,[ebp-N]`, `and esp,N` |
| `RET` | `imm` (`int|null`) | one terminal return |
| `EXIT_POINT` | `form` (`ret`\|`jmp_out`) | a ret, or a transfer to an address outside the listing |
| `UNCOND_TRANSFER_OUT` | `target` | `jmp` to an address not in the listing (tail call) |
| `CALL_DIRECT` | `target` | `call 0x00xxxxxx` |
| `CALL_INDIRECT` | `via`, `base`, `disp` | `call dword ptr [...]` |
| `JMP_INDIRECT` | `via`, `base`, `disp` | `jmp dword ptr [...]` |
| `STRING_OP` | `form`, `clobbers` | rep/lock string op; `clobbers` includes `ECX` for rep forms |
| `STACK_SLOT_READ` | `base`, `disp`, `size`, `key` (`int|null`), `resolved` (`bool`) | an ESP/EBP-relative read classified against the frame model (§2.2) |
| `STACK_SLOT_WRITE` | same, plus `via` (`direct`) | a write to an entry-relative slot |
| `REG_READ` | `reg`, `count`, `first_use`, `first_write_index` | one per register, summary of all reads |
| `REG_WRITE` | `reg`, `write_kind`, `definite` | one per register, *first* write only |
| `REG_RESTORE` | `reg` | `pop r` / `mov esp,ebp` — a restore, not a definition |
| `VTABLE_SHAPED_LOAD` | `base`, `vtable_offset`, `reg`, `call_offset` | see §2.5 |
| `SEGMENT_TLS` | `segment`, `text` | any `FS:`/`GS:` operand |

`write_kind ∈ {zero, imm, mem_load, lea, reg, zero_extend, sign_extend, arith,
call_result, unknown}`. `definite` is `false` only for `REG_RESTORE`.

### 2.2 The ESP-delta model (the load-bearing mechanism)

Argument slots are *entry*-relative. Two coordinate systems are unified onto one
integer `key`, defined as the byte offset from the ESP value **at function
entry**:

```
key = 0                  return address          (never an argument)
key = 4, 8, 0xc, 0x10…   argument ordinals 1, 2, 3, 4…
key = 0xfffffef4-4 = …   local storage
```

Resolution:

* **EBP-based operand.** Requires `frame.fp`. If `disp < 0` → local (record it in
  `parse.local_extent`, stop). If `disp ∈ {0, 4}` → frame/return, stop. Else
  `key = disp - 4` (because `EBP == entry_ESP - 4`).
* **ESP-based operand.** Maintain `esp_delta` = current ESP − entry ESP. Then
  `key = disp - esp_delta`. If `key < 4`, the slot is the return address or a
  local; stop.

`esp_delta` update rules, in listing order:

| Instruction | Update |
|---|---|
| `push r` / `push imm` / `push mem` | `+4` |
| `pop r` | `-4` |
| `sub esp, N` | `+N` |
| `add esp, N` | `-N` |
| `lea esp, [ebp-N]` | `esp_delta = -(4 + N)` |
| `call …` | `0` (the return address is popped by the ret; the listing resumes with the pre-call ESP) |
| `ret` | `0` (terminal) |
| `and esp, 0xfffffff0` | **`esp_delta = UNKNOWN`** (poisons the model) |
| `leave` | `-(…)`: treat as `mov esp,ebp; pop ebp` |
| anything else touching ESP | **`esp_delta = UNKNOWN`** |

Once `esp_delta` is UNKNOWN it stays UNKNOWN. Every subsequent ESP-relative read
emits `STACK_SLOT_READ` with `key = null, resolved = false` and **contributes
nothing** to the slot table.

**EBP outranks ESP.** If `frame.fp` is true, argument slots are resolved from
EBP and `and esp,0xfffffff0` is harmless — the 1,375 aligned functions in this
binary with a frame pointer are still fully resolvable. This asymmetry is
deliberate and is what makes fixture F16 resolvable at all.

Slot table construction: group resolved observations by `key`. For each key emit
`{ordinal, entry_offset, ebp_offset, sizes[], written, read}`.
`gaps = ((max_key - 4) // 4 + 1) - count(keys)` — the number of argument
ordinals that are *never touched*. `gaps > 0` is legal (unused parameters exist)
and caps confidence; it is not an abstention.

### 2.3 Register read/write accounting

A register counts as *read* when it appears as a memory `base`/`index` or as a
plain register operand. `REG_READ` records the **first** use address, the total
count, and `first_write_index` — the listing index of the first `definite` write,
or `null`. This single field is the discriminator for every "incoming value"
question in §3.

### 2.4 Exit points and terminal immediates

`ret_imms = {o.imm for RET observations}`. Three cases:

* `|ret_imms| == 1` → `ret_imm` is that value (may be `None` for a bare `ret`).
* `ret_imms == {}` → no terminal return in the listing.
* `|ret_imms| > 1` → `ret_imm = "CONFLICT"`. Hard abstention (rule **C-RET-X**).

### 2.5 Vtable-shaped loads

Purely local, order-based, no type guessing:

1. Track, per register, the last defining instruction.
2. On `call`/`jmp [X + slot]` where `X` is a register: let `D` be `X`'s last def.
3. If `D` is `MOV X, [B + voff]` with `B` a 32-bit register, emit
   `VTABLE_SHAPED_LOAD{base:B, vtable_offset:voff, reg:X, call_offset:slot}`.

This is the real MSVC sequence — `MOV EDX,[EAX]` then `CALL dword ptr [ECX+0x1c]`
where both `EDX` and `ECX` were loaded from `[this]` — and it is deliberately
*not* the loose "load from an undefined register" heuristic, which produced two
false positives in cross-checking.

`vtable_offset` is a **candidate first slot** only. It is never called a vtable
address and never promoted to `OBSERVED` vtable evidence.

### 2.6 `this`-offset entropy

`receiver.offsets` = sorted distinct displacements reached through ECX by any
of the three shapes in §3.2. `receiver.max_offset` = the largest.
This is a **lower bound** on the object's size, not a layout claim: it bounds
*claims* ("any field at +0x3a9c implies an object ≥ 0x3aa0 bytes") and is the
only thing the record uses it for. The record labels it
`"bounds_only": true`.

## 3. Stage 2 — inference rules

Each rule: **precondition** (over observations), **conclusion**, **confidence**,
**counterexample** (what would break it). Rules are pure functions of the
observation list; no rule reads another rule's conclusion except where stated.

Confidence vocabulary (`abi_inference.CONFIDENCE`):

```
UNKNOWN  <  DERIVED  <  INFERRED  <  SUPPORTED
OBSERVED            a fact label, NOT a rung of the ladder
```

* `OBSERVED` marks a value read straight off the listing (`cleanup.side` from a
  literal `ret N`; `receiver.present: false` when ECX is never read). It is not
  a claim and is never promoted or demoted.
* `bump(x)` moves one rung up, capped at `SUPPORTED`. Used only for agreement.
* `drop(x, floor="INFERRED")` moves one rung down but **never below INFERRED**.
  A conflict may therefore demote `SUPPORTED → INFERRED` but can never turn an
  inference into an apparent fact. Used only for conflict.

### 3.1 Convention discrimination — the decision procedure

Inputs: `ret_imm`, the slot table, receiver evidence, `edx_incoming_deref`,
`esp_unresolved`.

**C1 — RET-CONFLICT**
*Precondition:* `|ret_imms| > 1`.
*Conclusion:* `calling_convention = null`, `confidence = UNKNOWN`,
`cleanup.side = "CONFLICT"`.
*Abstain:* `ret_immediates_disagree`.
*Counterexample that would break it:* none exists in a compiler-generated
function (0 / 58,757 in this binary). Hand-written asm, or an ICF/thunk merge.

**C2 — NO-RET**
*Precondition:* no `RET` observation.
*Conclusion:* everything `UNKNOWN`; `cleanup.side = null`.
*Abstain:* `no_terminal_ret`.
*Counterexample:* a function whose listing is truncated by the collector. F16 is
exactly this case and is expected to abstain.

**C3 — RET-IMM-CALLEE**
*Precondition:* exactly one `ret_imm` and `ret_imm > 0`.
*Conclusion:* `cleanup.side = "callee"`, `cleanup.bytes = ret_imm`,
`confidence = OBSERVED` (a literal read off the listing).
*Corroboration:* if `ret_imm >= 4 * len(slots)` — i.e. the callee pops at least
the whole argument area, which is what a `__stdcall` does even when a trailing
parameter is unused — nothing further. If `ret_imm < max_key` see **C4**.

**C4 — RET-IMM-SHORT**
*Precondition:* `ret_imm > 0` **and** `ret_imm < max_key` (a slot above the
popped area is read).
*Conclusion:* `cleanup.side = null`, `confidence = UNKNOWN`.
*Abstain:* `ret_imm_below_highest_slot`.
*Why it is a contradiction:* after `ret N`, everything at `key > N` belongs to
the **caller's** frame, which a callee cannot name. A read there means either a
bad listing, a mis-parsed displacement, or non-conforming code.
*Counterexample that would break it:* an SEH/cookie trampoline that deliberately
inspects caller slots. Empirically absent here.

**C5 — RET-0-CALLER**
*Precondition:* a single bare `ret` (`ret_imm` is `None`), or `ret_imm == 0`.
*Conclusion:* `cleanup.side = "caller"`, `cleanup.bytes = 0`,
`confidence = INFERRED`. The citation is the `RET` observation.
*Why INFERRED and not OBSERVED:* a bare `ret` is compatible with caller cleanup
(almost always) and, for a `__stdcall` with zero stack parameters, with callee
cleanup of zero bytes. The two are indistinguishable from the callee alone, so
`corroboration: "not_available"` is emitted and the value is capped at INFERRED.

**C6 — CONV-STDCALL**
*Precondition:* `cleanup.side == "callee"` **and** receiver absent **and**
`esp_unresolved == false`.
*Conclusion:* `calling_convention = "__stdcall"`, `confidence = INFERRED`.
*Rationale:* a callee that pops stack arguments with no register receiver is
`__stdcall` by definition.
*Counterexample:* hand-written `__cdecl` asm that pops by hand; or a
`__thiscall` member with no stack parameters whose author wrote `ret N` manually.

**C7 — CONV-THISCALL**
*Precondition:* `cleanup.side == "caller"` **and** receiver `present == True`.
*Conclusion:* `calling_convention = "__thiscall"`, `confidence = INFERRED`.
*Counterexample:* `__fastcall` — handled by **C8** first. And a hand-written
cdecl function that merely happens to use its incoming ECX as an object.

**C8 — CONV-FASTCALL**
*Precondition:* `edx_incoming_deref == true` **and** `esp_unresolved == false`
**and** `cleanup.side == "caller"`.
*Conclusion:* `calling_convention = "__fastcall"`, `confidence = INFERRED`.
*Rationale (this is the one strong discriminator in the whole engine):* **ECX
and EDX are volatile.** No compiler-generated `__cdecl`/`__thiscall`/`__stdcall`
function can read their incoming value, because the caller never promises
anything about it. A function that dereferences EDX *before any write to EDX* is
therefore reading a value only `__fastcall` guarantees. Note this
**overrides** C7: ECX-deref + EDX-incoming-deref is `__fastcall`, not an
ambiguity.
*Counterexample:* hand-written assembly, or a compiler intrinsic wrapper that
documents ECX/EDX as "incoming". Nothing in the disassembly rules that out, which
is why the ceiling is INFERRED and never SUPPORTED without external
corroboration.
*Precondition that keeps it honest:* `edx_incoming_deref` is defined as
*EDX is a memory base at a listing index strictly less than EDX's first definite
write* — not merely "EDX is dereferenced". F13 as originally drafted wrote EDX
from ECX first and was therefore correctly classified `__thiscall`; the fixture
was corrected, and that correction is the rule's regression test.

**C9 — CONV-CDECL**
*Precondition:* `cleanup.side == "caller"` **and** at least one resolved
argument slot **and** receiver absent **and** `edx_incoming_deref == false`.
*Conclusion:* `calling_convention = "__cdecl"`, `confidence = INFERRED`.
*Counterexample:* a `__thiscall` whose `this` is never dereferenced in any
observable way. Indistinguishable, which is exactly why receiver absence only
*weakens* the claim and never excludes `__thiscall`; the record always carries
`candidate_conventions` (see 5.2) listing what remains possible.

**C10 — CONV-NONE**
*Precondition:* no `ret`; or `ret 0` with **no** resolved slot **and** no
positive receiver evidence **and** `edx_incoming_deref == false`.
*Conclusion:* `calling_convention = null`, `confidence = UNKNOWN`.
*Abstain:* `no_discriminator`.
*Why:* such a function is byte-identical under all four conventions. Emitting
`__cdecl` here would be the single most common way this engine could fabricate
an exactness it does not have. F06 and F07 both land here.

**C11 — CONV-CAP-UNRESOLVED-ESP**
*Precondition:* `esp_unresolved == true` **and** `frame.fp == false`.
*Conclusion:* `calling_convention = null` (whatever C6–C9 would have said),
`confidence = UNKNOWN`, `ambiguities += ["esp_alignment_unknown"]`.
*Counterexample:* none; if the entry-relative offsets cannot be computed, the
argument layout is not known and the convention is not known.
*Note:* a frame-pointer function is exempt, because EBP resolution is unaffected
by `and esp` (§2.2).

### 3.2 Register-receiver evidence

Definitions over the listing, all order-based:

* `ecx_incoming_deref` — ECX is a memory base at an index `< ECX.first_write_index`
  (or ECX never definitely written). Three accepted shapes, matching what the
  compiler actually emits:
  * **R-DIRECT** `MOV r, [ECX+k]` before any ECX write.
  * **R-SPILL** `MOV [EBP-m], ECX` (at an index before ECX's first definite
    write) — the local is provably the entry value of ECX — then
    `MOV r, [EBP-m]`, then `[r+k]` dereferenced. **This is the dominant MSVC
    idiom: 13,954 of 25,349 ECX-using functions never deref ECX directly.**
  * **R-ALIAS** `MOV r, ECX`, then `[r+k]` dereferenced before `r` is rewritten.
* `ecx_deref_offsets` — the distinct `k` reached by any of the three.
* `ecx_written_through` — how many of those dereferences are the *destination*
  of a store.

**R1 — RECEIVER-PRESENT**
*Precondition:* `ecx_incoming_deref == true`.
*Conclusion:* `receiver = {present: true, register: "ECX", offsets, max_offset,
written_through, bounds_only: true}`.
*Confidence:*
* `DERIVED` — exactly one distinct offset, no write-through.
* `INFERRED` — ≥ 2 distinct offsets, or ≥ 1 write-through.
* `SUPPORTED` — ≥ 2 distinct offsets **and** ≥ 1 write-through **and**
  `ret_imm ∈ {None, 0}` (i.e. consistent with `__thiscall` cleanup), **and**
  no unresolved-ESP poisoning.
*Counterexample:* ECX is a scratch register whose value was set by an earlier
block. Ruled out by the "incoming value" half of the precondition, which is
precisely why fixture F06 (`MOV EAX,[global]; MOV ECX,[EAX+8]; MOV EAX,[ECX+0x1c]`
— ECX dereferenced, but reassigned first) is expected to abstain with
`ecx_reassigned_before_deref`.

**R0 — RECEIVER-UNDETERMINED** (abstention)
*Preconditions, each its own reason code:*
* `ecx_read_without_deref` — ECX read, never a memory base, no spill, no alias.
* `ecx_reassigned_before_deref` — ECX is a memory base but only after a definite
  ECX write.
* `ecx_used_as_counter` — ECX only ever holds a REP count (`STRING_OP` present
  and no deref of any shape).
*Conclusion:* `receiver.present = null`, `confidence = UNKNOWN`.
*Never* claim `present: false` from any of these — the receiver may exist and
simply be unused.

**R2 — RECEIVER-ABSENT**
*Precondition:* ECX is never read in any form.
*Conclusion:* `receiver.present = false`, `confidence = OBSERVED`.
*This is the only `present: false` the engine may emit.*

### 3.3 Stack arguments

**A1 — SLOT-TABLE**
*Precondition:* ≥ 1 resolved slot.
*Conclusion:* `stack_arguments = {slots, gaps, total_bytes: max_key,
confidence}`; slot `i` has `entry_offset: "entry_ESP+0x%x"`, and, when
`frame.fp`, `ebp_offset: "EBP+0x%x"`; `ordinal` is 1-based.
*Confidence:* `INFERRED`; downgraded to `DERIVED` when `gaps > 0` or when any
slot's `size` is `size_inferred`.
*Never emitted:* a parameter count. `len(slots)` is *slots observed*, not
*parameters declared*, and the record names it `observed_slots`. F02 reports
3; F17 reports 1 with `gaps: 1` and must not be read as "1 parameter".

**A2 — SLOT-WIDTH-UNIFORM**
*Precondition:* a slot carries two distinct `size` values.
*Conclusion:* `widths_ambiguous: true`, that slot's `confidence` →
`UNKNOWN`, and `stack_arguments.confidence` capped at `DERIVED`.
*Abstain:* `slot_width_ambiguous`.
*Counterexample:* overlapping reads of a 12-byte struct passed by value — a
legitimate `ColorRGB`-style case (see the persisted `0x004ae250` record, which
carries a 12-byte stack argument). The engine reports the ambiguity instead of
picking a width.

### 3.4 Cleanup

Covered by C3/C4/C5. Additionally:

**CL1 — CLEANUP-CALLER-XVAL**
*Precondition:* `call_sites` is non-empty and a fragment shows
`add esp, imm` (or a matching `pop` sequence) within 6 instructions after the
call whose target is this function.
*Conclusion:* `cleanup.corroboration = "caller_side_cleanup_confirmed"`.
If the same evidence shows **no** adjustment after a `ret N` callee, and
`ret_imm > 0`, then `cleanup.corroboration = "caller_side_cleanup_absent"` and
`cleanup.confidence` → `SUPPORTED`.
*With `call_sites == ()`:* `cleanup.corroboration = "not_available"`, no change
to any confidence. **This is the default path from today's `evidence.py`, so in
production `cleanup.confidence` is OBSERVED (for `ret N`) or INFERRED (for bare
`ret`) and essentially never SUPPORTED.** The record says so explicitly.

### 3.5 Return register and value class

A bounded value-origin pass, forward, per register, with classes
`{integral, pointer_like, aggregate_unknown, large_or_mask, opaque}`:

| Defining instruction | Class |
|---|---|
| `xor r, r` | `integral` |
| `mov r, imm` | `pointer_like` if `image_base ≤ imm < image_base + 0x02000000`, else `integral` if `0 ≤ imm ≤ 0xffff`, else `large_or_mask` |
| `mov r, [mem]` | `pointer_like` |
| `movzx/movsx r, …` | `integral` |
| `lea r, [mem]` | `pointer_like` |
| `mov r, r2` | inherit `class(r2)` |
| `imul/mul/div/idiv r, …` | `integral` |
| `add/sub/and/or/inc/dec/shl/shr/sar/neg/not r, …` | `integral` if either side is `integral`, else the common class if both agree, else `opaque` |
| `call` | `call_result` — treated as `opaque` |
| anything else | `opaque` |

**RT1 — RETURN-REGISTER**
*Precondition:* ≥ 1 `RET` **and** C2 did not fire.
*Conclusion:* `return.register` = `ST0` if any `fld/fst*` appears, else `XMM0` if
any XMM operand appears, else `EAX`.
*Confidence:* `INFERRED`. Never `SUPPORTED`: a call in the body makes every
register caller-saved and the *incoming* value irrelevant, and a `void` function
routinely clobbers EAX.
*Counterexample:* an SSE function that returns an integer in EAX after touching
XMM0 as a scratch — the heuristic would name `XMM0`. Hence the ceiling, and
hence `return.register_class` is what callers should key on.

**RT2 — RETURN-CLASS**
*Precondition:* RT1 fired, listing parses, C2 did not fire.
*Conclusion:* `return.register_class` from the class of `EAX` (or `XMM0`/`ST0`)
at the **last** definition site:
* `integral` → `"integral"`
* `pointer_like` → `"pointer_like"`
* `float_or_x87` when the register is `XMM0`/`ST0` → `"float_or_x87"`
* `opaque`/`large_or_mask`/mixed → `"aggregate_unknown"`
* no definition found, or the last def is in a different basic block than the
  `ret` and no dominance is provable → `"unknown"`, `confidence = UNKNOWN`.
*Confidence:* `INFERRED` for `integral`/`pointer_like`, `DERIVED` for
`float_or_x87` (register choice is a heuristic, see RT1), `UNKNOWN` otherwise.

**RT3 — VOID**
*Precondition:* **zero** `REG_WRITE` observations for EAX **and** zero `CALL`
observations in the whole listing **and** ≥ 1 `RET`.
*Conclusion:* `return.void_possible = true`, `confidence = DERIVED`.
*Never* emitted as `return_type: "void"`. Even RT3 is a `void_possible` flag, not
a type, and `return.type` is `null` in every record the engine produces.

**RT4 — AGGREGATE**
*Precondition:* a `STRING_OP` with a `movs/stos` base, or ≥ 2 distinct return
registers assigned.
*Conclusion:* `return.register_class = "aggregate_unknown"`,
`aggregate_evidence: {bulk_write: true|false}`.
*Counterexample:* a `memcpy`-style helper returning a pointer; a bulk fill does
not imply a struct return.

### 3.6 Hidden sret

**S1 — SRET-CANDIDATE** (hypothesis, INFERRED)
*Precondition:* `stack_arguments.slots[0].ordinal == 1` **and** its value is
loaded into a register `R` **and** `[R + k]` is the destination of a write
(STACK_SLOT_WRITE on a register-based address, i.e. *written through the
pointer*, not *written to the slot*).
*Conclusion:*
```json
"sret": {"present": null, "slot": 4, "confidence": "UNKNOWN",
         "ambiguity": "sret_vs_out_param",
         "candidates": ["hidden_sret", "out_parameter"],
         "hypothesis_confidence": "INFERRED",
         "eax_holds_slot0_at_ret": true,
         "basis": "entry slot 0 is loaded into a register that is then used as a memory base for a write; …"}
```
**The engine never sets `sret.present` to `true`.** This is a deliberate
conclusion, and cross-checking forced it: a function that takes `T* out` and a
function that returns a large `T` by hidden pointer compile to *the same
instruction sequence*, and the traditional tiebreaker — "EAX holds the pointer at
the return" — does not separate them, because an out-parameter function also
leaves that pointer in EAX. Both real fixtures that trigger S1 (F04, F15) report
`present: null`, `confidence: UNKNOWN`, with the raw fact
`eax_holds_slot0_at_ret` preserved. Only an SDK prototype or a persisted
`record["abi"]` may promote it, and only through §4 cross-validation, never
through inference.

**S2 — SRET-ABSENT**
*Precondition:* slot 0 is not written through a pointer.
*Conclusion:* `sret.present = false`, `confidence = DERIVED`.
*Counterexample:* a struct returned via a hidden pointer that the callee fills
through a *different* alias (e.g. after `add eax, 0x10`); the write then lands
at a displacement the heuristic does not attribute to slot 0. Recorded as
`sret.present = false` with `confidence = DERIVED`, and the record notes that
`DERIVED` absence is weak.

**S3 — THIS-AND-SRET-ORDER** (the ordering question, answered)
*Precondition:* S1 fired **and** receiver `present == true`.
*Conclusion:* `sret.this_interaction = {"this_register": "ECX",
"sret_slot": 4, "ordering": "not_applicable"}`, `confidence = DERIVED`.
*Reasoning:* in MSVC x86 a hidden struct-return pointer is **always stack slot
0**; `this` under `__thiscall` is in **ECX** and never occupies a stack slot.
The two therefore never contend, and there is no ordering question to answer for
thiscall. The genuine ambiguity is different and is the one reported: a
`__cdecl` function with an out-parameter at slot 0 looks identical, so the
ambiguity is *sret-vs-out-param*, never *sret-before-this*. The record states
this so a downstream consumer does not go looking for an ordering bug.

### 3.7 Variadic suspicion

**V1 — VARIADIC-SUSPICION**
*Preconditions (any one), each emitting a `VARIADIC_MARKER` observation:*
* a `rep stosd`/`XORPS`+`MOVUPS` zero-fill of a frame local **immediately
  followed by** `lea r,[ebp-N]; push r` immediately before a `call` — the
  MSVC va_list setup shape;
* an `and esp,`-adjacent huge-frame `sub esp, N` with `N > 0x1000` preceding a
  call (the `_chkstk`/`__alloca_probe` shape, minus the symbol, which the
  instruction text does not carry);
* a `mov r, imm` with `imm` a small count immediately before a `call`.

*Conclusion:* `variadic = "SUSPECTED"`, and **the calling convention is forced to
`null` / `UNKNOWN`** (rule **C12**).

**C12 — CONV-CAP-VARIADIC**
*Precondition:* `variadic == "SUSPECTED"`.
*Conclusion:* `calling_convention = null`, `confidence = UNKNOWN`, `cleanup`
retains its OBSERVED/INFERRED value, `stack_arguments.not_complete = true`.
*Abstain:* `variadic_not_decidable_from_listing`.
*Why:* the stack-argument extent of a variadic callee is exactly the thing the
slot table cannot determine, and `__cdecl` for a variadic function is a
statement about a calling sequence the listing does not contain. Abstaining is
the only honest answer.
*Confidence ceiling:* the engine can **never** emit `variadic: "confirmed"` and
never `variadic: "absent"`. Three-valued only: `"UNKNOWN" | "SUSPECTED"`.

**V2 — SEH-IS-NOT-VARIADIC** (a rule about *not* concluding)
*Precondition:* any `FS:[…]` / `GS:[…]` operand.
*Conclusion:* `seh_or_cookie_frame = true`, and this **may not** be counted as
variadic evidence. In this binary `FS:[0x2c]` is the SEH exception-list head
(1,888 functions) and `FS:[0x0]` is the installed-handler chain; neither implies
`__cdecl` variadic. Emitting `seh_or_cookie_frame` also lowers `frame.fp`-only
argument confidence if the frame is frameless, because an SEH frame pushes
additional words that the ESP-delta model does not track.

### 3.8 Dispatch, tail calls, entropy

**D1 — VTABLE-SHAPED** — reports §2.5 counts. `confidence = OBSERVED` for the
*shape*, `DERIVED` for `call_offset` as a slot index. Never names a vtable.

**T1 — TAIL-CALL** — *Precondition:* a `JMP`/`JMPX` to an address not in the
listing, and no `RET` in the listing. *Conclusion:*
`tail_call = {present: true, target, form: "jmp"}`, `after_frame_setup = bool`,
`verdict = ABI_UNKNOWN`, `calling_convention = null`. *Rationale:* a thunk
inherits its caller's frame; the callee's own `ret` never runs, so cleanup is the
caller's and nothing about the convention is observable. *Counterexample:* an
inter-function tail call inside a merged basic block, where the target is a real
local label that happens to be outside the collected listing.

**T2 — FRAME-EPILOGUE-THEN-JUMP** (the "naked wrapper") — *Precondition:* a
`RET` **and** a trailing out-of-listing `JMP` on a different path.
*Conclusion:* `tail_call.present = true`, `form = "epilogue_then_jmp"`,
`verdict = ABI_UNKNOWN`. F11 is this shape, and the slot table it yields is
reported but explicitly marked `"not_complete": true`, because the path that
actually returns was never observed.

## 4. Confidence model, verdict, and record shape

### 4.1 Verdict

```
ABI_INFERRED  iff  calling_convention != null
                and cleanup.side in {"callee","caller"}
                and cleanup.confidence != UNKNOWN
                and return.confidence   != UNKNOWN
ABI_UNKNOWN   otherwise
```

`completeness` is orthogonal: `CORE_RESOLVED` (verdict ABI_INFERRED and all
three core confidences ≥ INFERRED), `PARTIAL` (something resolved), `EMPTY`.

Expect `ABI_UNKNOWN` for a large share of this binary. That is the finding, not
a failure: 4,806 functions have no `ret`, ~14,000 have no argument reads and no
receiver, and 99.9 % of Ghidra's own convention reports are `unknown`.

### 4.2 Record

```json
{
  "schema": "openspore-abi-inference-1",
  "verdict": "ABI_INFERRED" | "ABI_UNKNOWN",
  "completeness": "CORE_RESOLVED" | "PARTIAL" | "EMPTY",
  "target": {"va": "0x0040ccb0" | null, "instructions": 71,
             "address_available": true, "syntax": "intel" | "att",
             "image_base": "0x00400000"},
  "parse": {"degraded": false, "unparsed": 0, "local_extent": 72,
            "frame": {"fp": true, "push_ebp": true, "mov_ebp_esp": true,
                      "sub": 8, "lea_esp": null, "and_esp": null},
            "esp_unresolved": false, "flow_complete": true},
  "observations": [
    {"id": "obs-0001", "kind": "RET", "index": 70,
     "at": "0x0040cd6f", "raw": "RET 0x4", "imm": 4}
  ],
  "inferences": [
    {"id": "C6", "claim": "calling convention is __stdcall",
     "confidence": "INFERRED", "based_on": ["obs-0001"]}
  ],
  "conventions": {"calling_convention": "__stdcall" | null,
                  "confidence": "INFERRED",
                  "candidate_conventions": ["__stdcall", "__cdecl"],
                  "ambiguities": [], "corroboration": "not_available"},
  "receiver": {"present": true | false | null, "register": "ECX" | null,
               "confidence": "SUPPORTED", "shape": "R-SPILL" | "R-DIRECT" | "R-ALIAS" | null,
               "offsets": [16, 20, 24], "distinct_offsets": 3,
               "max_offset": 24, "written_through": 1, "bounds_only": true},
  "stack_arguments": {"observed_slots": 3, "gaps": 0, "total_bytes": 12,
                      "confidence": "INFERRED", "not_complete": false,
                      "widths_ambiguous": false,
                      "slots": [{"ordinal": 1, "entry_offset": "entry_ESP+0x4",
                                 "ebp_offset": "EBP+0x8", "sizes": [4],
                                 "read": true, "written": false,
                                 "confidence": "INFERRED"}]},
  "cleanup": {"side": "callee" | "caller" | "CONFLICT" | null,
              "bytes": 12, "confidence": "OBSERVED",
              "corroboration": "not_available", "evidence": "ret 0xc"},
  "return": {"register": "EAX", "register_class": "pointer_like",
             "confidence": "INFERRED", "type": null,
             "void_possible": false, "aggregate_evidence": {"bulk_write": false}},
  "sret": {"present": null, "slot": 4, "confidence": "UNKNOWN",
           "ambiguity": "sret_vs_out_param",
           "candidates": ["hidden_sret", "out_parameter"],
           "hypothesis_confidence": "INFERRED", "eax_holds_slot0_at_ret": true,
           "basis": "…", "this_interaction": {"this_register": "ECX",
                                              "sret_slot": 4,
                                              "ordering": "not_applicable"}},
  "variadic": "UNKNOWN" | "SUSPECTED",
  "seh_or_cookie_frame": false,
  "dispatch": {"vtable_shaped_loads": 1, "indirect_calls": 1,
               "call_offsets": [28]},
  "tail_call": {"present": false, "target": null, "form": null,
                "after_frame_setup": false},
  "abstained_because": [
    "code: calling_convention_ambiguous: thiscall_vs_fastcall",
    "code: variadic_not_decidable_from_listing",
    "evidence: obs-0012"
  ],
  "cross_validation": {"ghidra": "no_information", "persisted": "no_information",
                       "agreement": false},
  "conflicts": [],
  "content_sha256": "<sha256 of this document with content_sha256 = null>"
}
```

Invariants, all testable:

* `observations` and `inferences` are disjoint in kind — no observation may
  contain a claim word (`convention`, `receiver`, `sret`, `parameter`). No
  inference may appear without `based_on`.
* Every id in `inferences[*].based_on` resolves to an id in `observations`.
  An empty `based_on` is legal only for `confidence: "OBSERVED"` facts.
* `return.type` is always `null`. The engine emits no C++ type, ever.
* All lists are sorted by a total order; all maps are emitted with sorted keys;
  `content_sha256` is computed over the document with that field set to `null`
  (mirroring `evidence.py:315`).
* No wall-clock, no PID, no path, no Ghidra endpoint URL inside the record.

### 4.3 Abstention is a first-class, tested output

`abstained_because` entries are `"<code>: <detail>"` with a closed vocabulary.
The complete set:

| code | fires when |
|---|---|
| `empty_listing` | no parseable instruction |
| `no_terminal_ret` | no `RET` observation |
| `ret_immediates_disagree` | ≥ 2 distinct `ret N` |
| `ret_imm_below_highest_slot` | `ret N` with `N < max_key` |
| `no_discriminator` | no slot, no receiver, no EDX-incoming-deref |
| `esp_alignment_unknown` | frameless **and** `esp_delta` poisoned |
| `frame_pointer_untrusted` | `push ebp` without `mov ebp,esp` and frameless |
| `receiver_not_determinable` | ECX read, no incoming-value deref (see R0) |
| `receiver_reassigned` | ECX deref only after a definite ECX write |
| `ecx_used_as_counter` | ECX only a REP count |
| `slot_width_ambiguous` | one key, several widths |
| `slot_gaps_present` | an argument ordinal is never touched (advisory, not fatal) |
| `sret_vs_out_param` | S1 fired |
| `variadic_not_decidable_from_listing` | V1 fired |
| `variadic_caps_convention` | C12 fired |
| `unparsed_lines_present` | `parse.degraded` |
| `truncated_listing` | the last instruction is not a `RET`/`JMP` and the caller's byte count suggests more instructions |
| `flow_not_modelled` | a back edge, or an indirect branch whose target is in the listing (dominance not provable) |

Each code has ≥ 1 fixture asserting it. `tests/test_abi_inference.py` must
assert (a) byte-identical output on repeat calls, (b) every `based_on` resolves,
(c) `return.type is None`, (d) the full code set matches this table.

## 5. Cross-validation (contribute, never contradict)

`cross_validate(record, ghidra_calling_convention, ghidra_parameter_count,
persisted_abi)` is a **separate pure function** so that the inference engine
stays testable without any external input. It mutates only the record handed to
it and returns `(record, conflicts)`.

### 5.1 Precedence

1. **Inference output is never overwritten.** Ghidra and `record["abi"]` can
   only add a conflict, or bump/demote a confidence rung. They can never set
   `calling_convention`, `sret.present`, or `receiver.present`.
2. **Ghidra `<unknown>` / empty / `default` ⇒ `no_information`.** No bump, no
   demote, no conflict. *Silence is not agreement.* With 58,691/58,757 reports
   `unknown`, this is the overwhelmingly common path and must be a no-op.
3. **Ghidra agrees** (`__stdcall` == inferred `__stdcall`) ⇒ `bump` capped at
   `SUPPORTED`, `cross_validation.agreement = true`.
4. **Ghidra disagrees** ⇒ append
   `{"kind": "inferred_vs_ghidra", "field": "calling_convention", "inferred", "ghidra", "resolution_status": "unresolved"}`
   and `drop(..., floor="INFERRED")`. A `SUPPORTED` claim becomes `INFERRED`; an
   `INFERRED` claim stays `INFERRED` and the conflict record is the signal.
5. **Persisted `record["abi"]` disagrees** ⇒
   `{"kind": "inferred_vs_persisted", …}` with the same demotion. This is the
   sibling of the `live_vs_persisted` record `evidence.py:300` already emits;
   both are kept, neither is deleted. The pack gains a conflict, and
   `validate.py`'s `ABI` check will read the conflict rather than a fabricated
   winner.
6. **Ghidra and persisted disagree with each other** ⇒
   `{"kind": "ghidra_vs_persisted", …}`; the engine records it and changes
   nothing. Choosing a winner by count is exactly what
   `docs/tooling/evidence-model.md` forbids.
7. **Agreement can never promote an abstention.** If `calling_convention` is
   `null`, the record stays `ABI_UNKNOWN` and the confidence stays `UNKNOWN`
   even if Ghidra names a convention. Verified: F08 + Ghidra `__thiscall` ⇒
   `ABI_UNKNOWN`, `UNKNOWN`, with the `inferred_vs_ghidra` conflict still
   emitted (an abstention plus a contradiction is exactly what a human must see).
8. **`ghidra_parameter_count` is reported, never used.** 99.1 % of this binary
   reports 0 parameters; the field is echoed in
   `cross_validation.ghidra_parameter_count` and nothing else. A future
   `SUPPORTED` path may compare it against `observed_slots`, and the comparison
   must be a *conflict* when they differ, never a correction.

### 5.2 `candidate_conventions`

Whenever a specific convention is emitted, the record also carries the full set
still consistent with the evidence, so no consumer can mistake the emitted name
for the only possibility. F01 emits `["__thiscall", "__fastcall"]` alongside
`"__thiscall"`; C10 emits `["__cdecl", "__thiscall", "__stdcall", "__fastcall"]`
alongside `null`.

## 6. Synthetic fixture set

Every fixture is a pure string/JSON literal under
`tests/fixtures/abi/<name>.json`. Each test asserts the **whole** expected
fragment, so a regression in any layer fails loudly. All expected outputs below
were produced by executing the rules in this document.

---

### F01 — canonical `__thiscall` member (spilled `this`)

```json
[{"address":"00401230","instruction":"PUSH EBP"},
 {"address":"00401231","instruction":"MOV EBP,ESP"},
 {"address":"00401233","instruction":"SUB ESP,0x8"},
 {"address":"00401236","instruction":"MOV dword ptr [EBP + -0x4],ECX"},
 {"address":"00401239","instruction":"MOV EAX,dword ptr [EBP + -0x4]"},
 {"address":"0040123c","instruction":"MOV ECX,dword ptr [EAX + 0x10]"},
 {"address":"0040123f","instruction":"MOV EDX,dword ptr [EAX + 0x14]"},
 {"address":"00401242","instruction":"ADD ECX,EDX"},
 {"address":"00401244","instruction":"MOV EDX,dword ptr [EBP + -0x4]"},
 {"address":"00401247","instruction":"MOV dword ptr [EDX + 0x18],ECX"},
 {"address":"0040124a","instruction":"MOV EAX,dword ptr [EDX + 0x18]"},
 {"address":"0040124d","instruction":"MOV ESP,EBP"},
 {"address":"0040124f","instruction":"POP EBP"},
 {"address":"00401250","instruction":"RET"}]
```

```json
{"verdict":"ABI_INFERRED","completeness":"CORE_RESOLVED",
 "conventions":{"calling_convention":"__thiscall","confidence":"INFERRED",
   "candidate_conventions":["__thiscall","__fastcall"],"ambiguities":[],
   "corroboration":"not_available"},
 "receiver":{"present":true,"register":"ECX","confidence":"SUPPORTED",
   "shape":"R-SPILL","offsets":[16,20,24],"distinct_offsets":3,
   "max_offset":24,"written_through":1,"bounds_only":true},
 "stack_arguments":{"observed_slots":0,"gaps":0,"total_bytes":0,
   "confidence":"DERIVED","not_complete":false,"slots":[]},
 "cleanup":{"side":"caller","bytes":0,"confidence":"INFERRED",
   "corroboration":"not_available","evidence":"ret with no immediate, no stack reads"},
 "return":{"register":"EAX","register_class":"pointer_like",
   "confidence":"INFERRED","type":null,"void_possible":false},
 "sret":{"present":false,"slot":null,"confidence":"DERIVED","ambiguity":null},
 "variadic":"UNKNOWN","abstained_because":[]}
```

---

### F02 — `__cdecl` with 3 stack arguments

```json
[{"address":"00401300","instruction":"PUSH EBP"},
 {"address":"00401301","instruction":"MOV EBP,ESP"},
 {"address":"00401303","instruction":"MOV EAX,dword ptr [EBP + 0x8]"},
 {"address":"00401306","instruction":"MOV ECX,dword ptr [EBP + 0xc]"},
 {"address":"00401309","instruction":"MOV EDX,dword ptr [EBP + 0x10]"},
 {"address":"0040130c","instruction":"ADD EAX,ECX"},
 {"address":"0040130e","instruction":"ADD EAX,EDX"},
 {"address":"00401310","instruction":"POP EBP"},
 {"address":"00401311","instruction":"RET"}]
```

```json
{"verdict":"ABI_INFERRED","completeness":"CORE_RESOLVED",
 "conventions":{"calling_convention":"__cdecl","confidence":"INFERRED",
   "candidate_conventions":["__cdecl","__thiscall"],"ambiguities":[]},
 "receiver":{"present":null,"register":null,"confidence":"UNKNOWN",
   "reason":"ecx_read_without_deref","offsets":[],"max_offset":null},
 "stack_arguments":{"observed_slots":3,"gaps":0,"total_bytes":12,
   "confidence":"INFERRED",
   "slots":[
     {"ordinal":1,"entry_offset":"entry_ESP+0x4","ebp_offset":"EBP+0x8","sizes":[4],"read":true,"written":false},
     {"ordinal":2,"entry_offset":"entry_ESP+0x8","ebp_offset":"EBP+0xc","sizes":[4],"read":true,"written":false},
     {"ordinal":3,"entry_offset":"entry_ESP+0xc","ebp_offset":"EBP+0x10","sizes":[4],"read":true,"written":false}]},
 "cleanup":{"side":"caller","bytes":0,"confidence":"INFERRED"},
 "return":{"register":"EAX","register_class":"pointer_like","confidence":"INFERRED","type":null},
 "sret":{"present":false,"slot":null,"confidence":"DERIVED","ambiguity":null},
 "abstained_because":["receiver_not_determinable: ecx_read_without_deref"]}
```

---

### F03 — `__stdcall` with `ret 0xc`

Same body as F02 with `{"address":"00401411","instruction":"RET 0xc"}` in place
of the final `RET`, and addresses rebased to `0x401400`.

```json
{"verdict":"ABI_INFERRED","completeness":"CORE_RESOLVED",
 "conventions":{"calling_convention":"__stdcall","confidence":"INFERRED",
   "candidate_conventions":["__stdcall"],"ambiguities":[]},
 "stack_arguments":{"observed_slots":3,"gaps":0,"total_bytes":12,
   "confidence":"INFERRED","slots":[{"ordinal":1,"entry_offset":"entry_ESP+0x4",
     "ebp_offset":"EBP+0x8","sizes":[4]},
     {"ordinal":2,"entry_offset":"entry_ESP+0x8","ebp_offset":"EBP+0xc","sizes":[4]},
     {"ordinal":3,"entry_offset":"entry_ESP+0xc","ebp_offset":"EBP+0x10","sizes":[4]}]},
 "cleanup":{"side":"callee","bytes":12,"confidence":"OBSERVED",
   "corroboration":"not_available","evidence":"ret 0xc"},
 "return":{"register":"EAX","register_class":"integral","confidence":"INFERRED","type":null},
 "abstained_because":["receiver_not_determinable: ecx_read_without_deref"]}
```

`return_class` is `integral` because the last `EAX` definition is an `IMUL` of two
stack-loaded values (§3.5), not a load. `cleanup.confidence` is `OBSERVED`,
**not** `SUPPORTED`, because `call_sites` is empty (CL1).

---

### F04 — `__thiscall` with a hidden-sret candidate

```json
[{"address":"00401500","instruction":"PUSH EBP"},
 {"address":"00401501","instruction":"MOV EBP,ESP"},
 {"address":"00401503","instruction":"SUB ESP,0x10"},
 {"address":"00401506","instruction":"MOV dword ptr [EBP + -0x4],ECX"},
 {"address":"00401509","instruction":"MOV EAX,dword ptr [EBP + 0x8]"},
 {"address":"0040150c","instruction":"MOV EDX,dword ptr [EBP + -0x4]"},
 {"address":"0040150f","instruction":"MOV EDX,dword ptr [EDX + 0x4]"},
 {"address":"00401512","instruction":"MOV ECX,dword ptr [EAX + 0x8]"},
 {"address":"00401515","instruction":"ADD ECX,0x10"},
 {"address":"00401518","instruction":"MOV dword ptr [EAX + 0x10],ECX"},
 {"address":"0040151b","instruction":"MOV EDX,dword ptr [EDX + 0x18]"},
 {"address":"0040151e","instruction":"MOV dword ptr [EAX + 0x4],EDX"},
 {"address":"00401521","instruction":"MOV EAX,dword ptr [EBP + 0x8]"},
 {"address":"00401524","instruction":"MOV ESP,EBP"},
 {"address":"00401526","instruction":"POP EBP"},
 {"address":"00401527","instruction":"RET"}]
```

```json
{"verdict":"ABI_INFERRED","completeness":"CORE_RESOLVED",
 "conventions":{"calling_convention":"__thiscall","confidence":"INFERRED"},
 "receiver":{"present":true,"register":"ECX","confidence":"INFERRED",
   "shape":"R-SPILL","offsets":[4,24],"max_offset":24,"written_through":2},
 "stack_arguments":{"observed_slots":1,"gaps":0,"total_bytes":4,
   "confidence":"INFERRED",
   "slots":[{"ordinal":1,"entry_offset":"entry_ESP+0x4","ebp_offset":"EBP+0x8",
             "sizes":[4],"read":true,"written":false}]},
 "cleanup":{"side":"caller","bytes":0,"confidence":"INFERRED"},
 "sret":{"present":null,"slot":4,"confidence":"UNKNOWN",
   "ambiguity":"sret_vs_out_param",
   "candidates":["hidden_sret","out_parameter"],
   "hypothesis_confidence":"INFERRED","eax_holds_slot0_at_ret":true,
   "this_interaction":{"this_register":"ECX","sret_slot":4,
                       "ordering":"not_applicable"}},
 "abstained_because":["sret_vs_out_param: entry slot 0 is written through a pointer"]}
```

The `sret` block is the single most important negative result in this
specification: **`present` stays `null`.** See §3.6/S1.

---

### F05 — `__cdecl` with explicit caller cleanup

```json
[{"address":"00401600","instruction":"PUSH EBP"},
 {"address":"00401601","instruction":"MOV EBP,ESP"},
 {"address":"00401603","instruction":"PUSH dword ptr [EBP + 0x8]"},
 {"address":"00401606","instruction":"PUSH ECX"},
 {"address":"00401607","instruction":"CALL 0x00401000"},
 {"address":"0040160c","instruction":"ADD ESP,0x8"},
 {"address":"0040160f","instruction":"MOV dword ptr [EBP + 0xc],EAX"},
 {"address":"00401612","instruction":"MOV EAX,dword ptr [EBP + 0xc]"},
 {"address":"00401615","instruction":"POP EBP"},
 {"address":"00401616","instruction":"RET"}]
```

```json
{"verdict":"ABI_INFERRED","completeness":"CORE_RESOLVED",
 "conventions":{"calling_convention":"__cdecl","confidence":"INFERRED"},
 "stack_arguments":{"observed_slots":2,"gaps":0,"total_bytes":8,
   "confidence":"INFERRED",
   "slots":[{"ordinal":1,"entry_offset":"entry_ESP+0x4","ebp_offset":"EBP+0x8",
             "sizes":[4],"read":true,"written":false},
            {"ordinal":2,"entry_offset":"entry_ESP+0x8","ebp_offset":"EBP+0xc",
             "sizes":[4],"read":true,"written":true}]},
 "cleanup":{"side":"caller","bytes":0,"confidence":"INFERRED",
   "corroboration":"not_available","evidence":"ret with no immediate"},
 "return":{"register":"EAX","register_class":"pointer_like","confidence":"INFERRED","type":null},
 "abstained_because":["receiver_not_determinable: ecx_read_without_deref"]}
```

Note `PUSH dword ptr [EBP+0x8]` is a **read** of slot 1, and
`MOV [EBP+0xc],EAX` is a **write** of slot 2 — a local reusing the argument
area, which is legal for `__cdecl` and is why `written: true` there is not an
error. `call_sites` is empty in this fixture, so the `ADD ESP,0x8` is *not*
available as corroboration; the fixture `F05b` repeats it with
`call_sites=[{"call_va":"0x00401607","after":["ADD ESP,0x8"]}]` and must yield
`cleanup.corroboration = "caller_side_cleanup_confirmed"`.

---

### F06 — leaf function with no frame

```json
[{"address":"00401700","instruction":"MOV EAX,dword ptr [0x016b3c04]"},
 {"address":"00401705","instruction":"MOV ECX,dword ptr [EAX + 0x8]"},
 {"address":"00401708","instruction":"MOV EAX,dword ptr [ECX + 0x1c]"},
 {"address":"0040170b","instruction":"RET"}]
```

```json
{"verdict":"ABI_UNKNOWN","completeness":"PARTIAL",
 "conventions":{"calling_convention":null,"confidence":"UNKNOWN",
   "candidate_conventions":["__cdecl","__thiscall","__stdcall","__fastcall"],
   "ambiguities":[]},
 "receiver":{"present":null,"register":null,"confidence":"UNKNOWN",
   "reason":"ecx_reassigned_before_deref","offsets":[]},
 "stack_arguments":{"observed_slots":0,"gaps":0,"total_bytes":0,
   "confidence":"DERIVED","slots":[]},
 "cleanup":{"side":"caller","bytes":0,"confidence":"INFERRED"},
 "return":{"register":"EAX","register_class":"pointer_like",
   "confidence":"INFERRED","type":null},
 "abstained_because":[
   "receiver_not_determinable: ecx_reassigned_before_deref",
   "no_discriminator: no stack-argument read and no positive receiver evidence"]}
```

**This is the fixture that proves the incoming-value rule.** `[ECX + 0x1c]` looks
exactly like a receiver dereference, but ECX was assigned one instruction
earlier, so it is a local pointer, not `this`. A rule that merely counted ECX
dereferences would have emitted `__thiscall` here.

---

### F07 — tail-call thunk

```json
[{"address":"00401800","instruction":"JMP 0x00401900"}]
```

```json
{"verdict":"ABI_UNKNOWN","completeness":"EMPTY",
 "conventions":{"calling_convention":null,"confidence":"UNKNOWN"},
 "receiver":{"present":false,"register":null,"confidence":"OBSERVED"},
 "stack_arguments":{"observed_slots":0,"gaps":0,"total_bytes":0,
   "confidence":"DERIVED","slots":[]},
 "cleanup":{"side":null,"bytes":null,"confidence":"UNKNOWN"},
 "return":{"register":null,"register_class":"unknown","confidence":"UNKNOWN","type":null},
 "tail_call":{"present":true,"target":"0x00401900","form":"jmp",
              "after_frame_setup":false},
 "abstained_because":["no_terminal_ret: function has no RET instruction"]}
```

Empirically 5,335 / 58,757 functions (9.1 %) have this shape.

---

### F08 — reads ECX but never dereferences it ⇒ **MUST ABSTAIN**

```json
[{"address":"00401900","instruction":"PUSH EBP"},
 {"address":"00401901","instruction":"MOV EBP,ESP"},
 {"address":"00401903","instruction":"MOV EAX,ECX"},
 {"address":"00401905","instruction":"MOV ECX,0x4"},
 {"address":"00401908","instruction":"SHR EAX,CL"},
 {"address":"0040190a","instruction":"POP EBP"},
 {"address":"0040190b","instruction":"RET"}]
```

```json
{"verdict":"ABI_UNKNOWN","completeness":"PARTIAL",
 "conventions":{"calling_convention":null,"confidence":"UNKNOWN",
   "candidate_conventions":["__cdecl","__thiscall","__stdcall","__fastcall"]},
 "receiver":{"present":null,"register":null,"confidence":"UNKNOWN",
   "reason":"ecx_read_without_deref"},
 "cleanup":{"side":"caller","bytes":0,"confidence":"INFERRED"},
 "return":{"register":"EAX","register_class":"aggregate_unknown",
   "confidence":"INFERRED","type":null},
 "abstained_because":[
   "receiver_not_determinable: ecx_read_without_deref",
   "no_discriminator: no stack-argument read and no positive receiver evidence"]}
```

`return_class` is `aggregate_unknown`, not `integral`: `MOV EAX,ECX` inherits
`opaque` (ECX's incoming class is undefined) and `SHR EAX,CL` is not in the
whitelist. Correct conservatism: an EAX built from a volatile register is
unclassifiable.

---

### F09 — vtable-shaped dispatch

```json
[{"address":"00401a00","instruction":"PUSH EBP"},
 {"address":"00401a01","instruction":"MOV EBP,ESP"},
 {"address":"00401a03","instruction":"MOV dword ptr [EBP + -0x4],ECX"},
 {"address":"00401a06","instruction":"MOV EAX,dword ptr [EBP + -0x4]"},
 {"address":"00401a09","instruction":"MOV EDX,dword ptr [EAX]"},
 {"address":"00401a0b","instruction":"PUSH dword ptr [EBP + 0x8]"},
 {"address":"00401a0e","instruction":"MOV EAX,dword ptr [EBP + -0x4]"},
 {"address":"00401a11","instruction":"MOV ECX,dword ptr [EAX]"},
 {"address":"00401a13","instruction":"CALL dword ptr [ECX + 0x1c]"},
 {"address":"00401a19","instruction":"ADD ESP,0x4"},
 {"address":"00401a1c","instruction":"MOV ESP,EBP"},
 {"address":"00401a1e","instruction":"POP EBP"},
 {"address":"00401a1f","instruction":"RET"}]
```

```json
{"verdict":"ABI_INFERRED","completeness":"CORE_RESOLVED",
 "conventions":{"calling_convention":"__thiscall","confidence":"INFERRED"},
 "receiver":{"present":true,"register":"ECX","confidence":"INFERRED",
   "shape":"R-SPILL","offsets":[0],"max_offset":0,"written_through":0},
 "stack_arguments":{"observed_slots":1,"gaps":0,"total_bytes":4,
   "confidence":"INFERRED",
   "slots":[{"ordinal":1,"entry_offset":"entry_ESP+0x4","ebp_offset":"EBP+0x8",
             "sizes":[4],"read":true,"written":false}]},
 "dispatch":{"vtable_shaped_loads":1,"indirect_calls":1,"call_offsets":[28]},
 "return":{"register":"EAX","register_class":"aggregate_unknown",
   "confidence":"INFERRED","type":null},
 "abstained_because":[]}
```

`call_offsets: [28]` is a **candidate slot index**, not a vtable fact.
`return_class` is `aggregate_unknown` because the return value is a `call`
result, which the whitelist refuses to classify. Note `receiver.offsets == [0]`:
a single offset with no write-through ⇒ `INFERRED`, not `SUPPORTED` (R1).

---

### F10 — variadic-looking ⇒ **MUST STAY UNKNOWN**

```json
[{"address":"00401b00","instruction":"PUSH EBP"},
 {"address":"00401b01","instruction":"MOV EBP,ESP"},
 {"address":"00401b03","instruction":"SUB ESP,0x20"},
 {"address":"00401b06","instruction":"XOR EAX,EAX"},
 {"address":"00401b08","instruction":"MOV ECX,0x8"},
 {"address":"00401b0a","instruction":"REP STOSD"},
 {"address":"00401b0c","instruction":"LEA EAX,[EBP + -0x20]"},
 {"address":"00401b0f","instruction":"PUSH EAX"},
 {"address":"00401b10","instruction":"PUSH dword ptr [EBP + 0x8]"},
 {"address":"00401b13","instruction":"PUSH 0x4"},
 {"address":"00401b15","instruction":"CALL 0x00402000"},
 {"address":"00401b1a","instruction":"ADD ESP,0xc"},
 {"address":"00401b1d","instruction":"POP EBP"},
 {"address":"00401b1e","instruction":"RET"}]
```

```json
{"verdict":"ABI_UNKNOWN","completeness":"PARTIAL",
 "conventions":{"calling_convention":null,"confidence":"UNKNOWN",
   "candidate_conventions":["__cdecl"],"ambiguities":["variadic_suspected"]},
 "variadic":"SUSPECTED",
 "receiver":{"present":null,"register":null,"confidence":"UNKNOWN",
   "reason":"ecx_used_as_counter"},
 "stack_arguments":{"observed_slots":1,"gaps":0,"total_bytes":4,
   "confidence":"DERIVED","not_complete":true,
   "slots":[{"ordinal":1,"entry_offset":"entry_ESP+0x4","ebp_offset":"EBP+0x8",
             "sizes":[4]}]},
 "cleanup":{"side":"caller","bytes":0,"confidence":"INFERRED"},
 "return":{"register":"EAX","register_class":"integral","confidence":"INFERRED","type":null},
 "abstained_because":[
   "variadic_not_decidable_from_listing: no caller-side va_list construction is visible",
   "variadic_caps_convention: variadic suspicion removes any guarantee about the stack-argument extent",
   "receiver_not_determinable: ecx_used_as_counter"]}
```

`ecx_used_as_counter`: `MOV ECX,0x8` + `REP STOSD` is a REP count, not a
receiver. The zero-fill + `lea` + `push` + `push imm` + `call` sequence is the
MSVC va_list setup shape (V1 marker 1). `variadic` is capped at `SUSPECTED`
forever — the callee's own listing contains no proof.

---

### F11 — naked wrapper (epilogue, then `jmp`)

```json
[{"address":"00401c00","instruction":"MOV EAX,dword ptr [ESP + 0x4]"},
 {"address":"00401c03","instruction":"PUSH dword ptr [ESP + 0x8]"},
 {"address":"00401c06","instruction":"JMP 0x00401d00"}]
```

```json
{"verdict":"ABI_UNKNOWN","completeness":"PARTIAL",
 "conventions":{"calling_convention":null,"confidence":"UNKNOWN"},
 "receiver":{"present":false,"register":null,"confidence":"OBSERVED"},
 "stack_arguments":{"observed_slots":1,"gaps":0,"total_bytes":4,
   "confidence":"DERIVED","not_complete":true,
   "slots":[{"ordinal":1,"entry_offset":"entry_ESP+0x4","sizes":[4]}]},
 "cleanup":{"side":null,"bytes":null,"confidence":"UNKNOWN"},
 "return":{"register":"EAX","register_class":"pointer_like",
   "confidence":"INFERRED","type":null},
 "tail_call":{"present":true,"target":"0x00401d00","form":"epilogue_then_jmp",
              "after_frame_setup":false},
 "abstained_because":[
   "no_terminal_ret: the only exit observed is a tail jump"]}
```

The slot table is reported but `not_complete: true`: the path that actually
returns to the caller was never observed, so slot 1 may not be the whole
argument list.

---

### F12 — two exits with different `ret` immediates ⇒ **MUST ABSTAIN**

```json
[{"address":"00401e00","instruction":"PUSH EBP"},
 {"address":"00401e01","instruction":"MOV EBP,ESP"},
 {"address":"00401e03","instruction":"CMP dword ptr [EBP + 0x8],0x0"},
 {"address":"00401e09","instruction":"JE 0x00401e20"},
 {"address":"00401e0b","instruction":"MOV EAX,dword ptr [EBP + 0xc]"},
 {"address":"00401e0e","instruction":"POP EBP"},
 {"address":"00401e0f","instruction":"RET 0xc"},
 {"address":"00401e20","instruction":"MOV EAX,dword ptr [EBP + 0x10]"},
 {"address":"00401e23","instruction":"POP EBP"},
 {"address":"00401e24","instruction":"RET 0x10"}]
```

```json
{"verdict":"ABI_UNKNOWN","completeness":"PARTIAL",
 "conventions":{"calling_convention":null,"confidence":"UNKNOWN",
   "ambiguities":["multiple_ret_immediates"]},
 "receiver":{"present":false,"register":null,"confidence":"OBSERVED"},
 "stack_arguments":{"observed_slots":3,"gaps":0,"total_bytes":12,
   "confidence":"INFERRED",
   "slots":[{"ordinal":1,"entry_offset":"entry_ESP+0x4","ebp_offset":"EBP+0x8","sizes":[4]},
            {"ordinal":2,"entry_offset":"entry_ESP+0x8","ebp_offset":"EBP+0xc","sizes":[4]},
            {"ordinal":3,"entry_offset":"entry_ESP+0xc","ebp_offset":"EBP+0x10","sizes":[4]}]},
 "cleanup":{"side":"CONFLICT","bytes":null,"confidence":"UNKNOWN",
   "evidence":"terminal ret immediates disagree: 0xc, 0x10"},
 "return":{"register":"EAX","register_class":"pointer_like",
   "confidence":"INFERRED","type":null},
 "abstained_because":[
   "ret_immediates_disagree: 0xc != 0x10 at two exits",
   "cleanup_undeterminable: ret immediates disagree at multiple exits"]}
```

Synthetic stress case: **0 of 58,757** functions in this binary behave this way.
That is precisely why it is an abstention rather than a "pick the majority"
heuristic.

---

### F13 — `__fastcall` (ECX *and* EDX incoming)

```json
[{"address":"00401f00","instruction":"PUSH EBP"},
 {"address":"00401f01","instruction":"MOV EBP,ESP"},
 {"address":"00401f03","instruction":"MOV EAX,dword ptr [ECX + 0x4]"},
 {"address":"00401f06","instruction":"MOV ECX,dword ptr [EDX + 0x10]"},
 {"address":"00401f09","instruction":"MOV dword ptr [EAX + 0x4],ECX"},
 {"address":"00401f0c","instruction":"MOV EDX,dword ptr [ECX + 0x8]"},
 {"address":"00401f0f","instruction":"MOV EAX,dword ptr [EDX + 0xc]"},
 {"address":"00401f12","instruction":"POP EBP"},
 {"address":"00401f13","instruction":"RET"}]
```

```json
{"verdict":"ABI_INFERRED","completeness":"CORE_RESOLVED",
 "conventions":{"calling_convention":"__fastcall","confidence":"INFERRED",
   "candidate_conventions":["__fastcall"],
   "ambiguities":[]},
 "receiver":{"present":true,"register":"ECX","confidence":"INFERRED",
   "shape":"R-DIRECT","offsets":[4,8],"max_offset":8,"written_through":1},
 "stack_arguments":{"observed_slots":0,"gaps":0,"total_bytes":0,
   "confidence":"DERIVED","slots":[]},
 "cleanup":{"side":"caller","bytes":0,"confidence":"INFERRED"},
 "return":{"register":"EAX","register_class":"pointer_like",
   "confidence":"INFERRED","type":null},
 "abstained_because":[]}
```

Rule C8 fires and **overrides C7**: EDX is a memory base at index 3, strictly
before EDX's first definite write at index 6, so the function is reading a value
only `__fastcall` guarantees. `candidate_conventions` is a single element because
nothing else survives. The regression test for this rule is the *rejected*
variant in which `MOV EDX,[ECX+0x8]` is moved to index 1 — that ordering must
yield `__thiscall`, and the pair is the rule's test.

---

### F14 — real `SporeApp.exe` thiscall, no stack arguments (`0x00432a50`)

Verbatim from the binary via `/disassemble_function`:

```json
[{"address":"00432a50","instruction":"PUSH EBP"},
 {"address":"00432a51","instruction":"MOV EBP,ESP"},
 {"address":"00432a53","instruction":"PUSH ECX"},
 {"address":"00432a54","instruction":"MOV dword ptr [EBP + -0x4],ECX"},
 {"address":"00432a57","instruction":"MOV EAX,dword ptr [EBP + -0x4]"},
 {"address":"00432a5a","instruction":"ADD EAX,0x4"},
 {"address":"00432a5d","instruction":"MOV ECX,0x1"},
 {"address":"00432a62","instruction":"XADD.LOCK dword ptr [EAX],ECX"},
 {"address":"00432a66","instruction":"INC ECX"},
 {"address":"00432a67","instruction":"MOV EAX,ECX"},
 {"address":"00432a69","instruction":"MOV ESP,EBP"},
 {"address":"00432a6b","instruction":"POP EBP"},
 {"address":"00432a6c","instruction":"RET"}]
```

```json
{"verdict":"ABI_INFERRED","completeness":"CORE_RESOLVED",
 "target":{"va":"0x00432a50","instructions":13,"address_available":true,
           "syntax":"intel","image_base":"0x00400000"},
 "conventions":{"calling_convention":"__thiscall","confidence":"INFERRED"},
 "receiver":{"present":true,"register":"ECX","confidence":"INFERRED",
   "shape":"R-SPILL","offsets":[4],"max_offset":4,"written_through":1},
 "stack_arguments":{"observed_slots":0,"gaps":0,"total_bytes":0,
   "confidence":"DERIVED","slots":[]},
 "cleanup":{"side":"caller","bytes":0,"confidence":"INFERRED"},
 "return":{"register":"EAX","register_class":"integral",
   "confidence":"INFERRED","type":null},
 "sret":{"present":false,"slot":null,"confidence":"DERIVED","ambiguity":null},
 "abstained_because":[]}
```

Two things this fixture pins down. (1) `PUSH ECX` is a *save*, not a def: the
receiver is still provably ECX, and `ecx_deref_offsets == [4]` off the
spill-reload. (2) `return_class == "integral"`, not `pointer_like` and not
`aggregate_unknown`: the last `EAX` definition is `MOV EAX,ECX`, inheriting
`ECX`'s class, which is `integral` from `MOV ECX,0x1` + `INC ECX` + `XADD`. A
rule that stopped at `MOV EAX,[EBP-0x4]` would wrongly answer `pointer_like`;
that is the return-class regression test. `XADD.LOCK` is a Ghidra decode
artifact and is accepted without complaint.

---

### F15 — real frameless x87 cdecl, 4 stack arguments (`0x01080e40`)

```json
[{"address":"01080e40","instruction":"FLD float ptr [ESP + 0x8]"},
 {"address":"01080e43","instruction":"FSUB float ptr [ESP + 0xc]"},
 {"address":"01080e46","instruction":"FABS"},
 {"address":"01080e47","instruction":"FCOMP float ptr [ESP + 0x10]"},
 {"address":"01080e4a","instruction":"FNSTSW AX"},
 {"address":"01080e4d","instruction":"TEST AH,0x5"},
 {"address":"01080e4f","instruction":"MOV EAX,dword ptr [ESP + 0x4]"},
 {"address":"01080e52","instruction":"JP 0x01080e5e"},
 {"address":"01080e54","instruction":"MOV CL,0x1"},
 {"address":"01080e56","instruction":"MOV byte ptr [EAX],CL"},
 {"address":"01080e58","instruction":"RET"},
 {"address":"01080e59","instruction":"XOR CL,CL"},
 {"address":"01080e5b","instruction":"MOV byte ptr [EAX],CL"},
 {"address":"01080e5d","instruction":"RET"}]
```

```json
{"verdict":"ABI_INFERRED","completeness":"CORE_RESOLVED",
 "target":{"va":"0x01080e40","address_available":true},
 "parse":{"frame":{"fp":false,"push_ebp":false,"mov_ebp_esp":false,
                   "sub":null,"lea_esp":null,"and_esp":null},
          "esp_unresolved":false,"degraded":false},
 "conventions":{"calling_convention":"__cdecl","confidence":"INFERRED",
   "candidate_conventions":["__cdecl","__thiscall"]},
 "receiver":{"present":false,"register":null,"confidence":"OBSERVED"},
 "stack_arguments":{"observed_slots":4,"gaps":0,"total_bytes":16,
   "confidence":"INFERRED",
   "slots":[{"ordinal":1,"entry_offset":"entry_ESP+0x4","sizes":[4],
             "read":true,"written":false,"note":"out-pointer, written through"},
            {"ordinal":2,"entry_offset":"entry_ESP+0x8","sizes":[4]},
            {"ordinal":3,"entry_offset":"entry_ESP+0xc","sizes":[4]},
            {"ordinal":4,"entry_offset":"entry_ESP+0x10","sizes":[4]}]},
 "cleanup":{"side":"caller","bytes":0,"confidence":"INFERRED",
   "evidence":"ret with no immediate, no stack reads"},
 "return":{"register":"ST0","register_class":"float_or_x87",
   "confidence":"DERIVED","type":null,"void_possible":false},
 "sret":{"present":null,"slot":4,"confidence":"UNKNOWN",
   "ambiguity":"sret_vs_out_param",
   "candidates":["hidden_sret","out_parameter"],
   "hypothesis_confidence":"INFERRED","eax_holds_slot0_at_ret":true,
   "this_interaction":null},
 "abstained_because":["sret_vs_out_param: entry slot 0 is written through a pointer"]}
```

This is the highest-value real fixture. It pins: frameless ESP-relative
resolution with no frame pointer; the `float ptr` size token; two `RET`s with the
*same* form (`None`), which is **not** a conflict; `ST0` as the return register
via the x87 path; and — most importantly — a **real** function where
`eax_holds_slot0_at_ret` is `true` and `sret.present` is still `null`. Any
implementation that promotes this to `present: true` on the strength of EAX is
wrong, and the persisted record for this VA, if one ever appears, must be
cross-validated rather than overwritten.

---

### F16 — truncated listing (prefix of `0x01082350`) ⇒ **MUST ABSTAIN**

```json
[{"address":"01082350","instruction":"PUSH EBP"},
 {"address":"01082351","instruction":"MOV EBP,ESP"},
 {"address":"01082353","instruction":"AND ESP,0xfffffff0"},
 {"address":"01082356","instruction":"SUB ESP,0x24"},
 {"address":"01082359","instruction":"FLD float ptr [ECX + 0x14]"},
 {"address":"0108235d","instruction":"MOV EDX,dword ptr [EBP + 0x8]"},
 {"address":"01082360","instruction":"FADD float ptr [ECX]"},
 {"address":"01082363","instruction":"PUSH EBX"},
 {"address":"01082364","instruction":"PUSH ESI"},
 {"address":"01082365","instruction":"PUSH EDI"},
 {"address":"01082366","instruction":"FADD float ptr [ECX + 0x28]"},
 {"address":"0108236a","instruction":"FCOM float ptr [0x01485378]"},
 {"address":"0108236f","instruction":"FNSTSW AX"},
 {"address":"01082372","instruction":"TEST AH,0x41"},
 {"address":"01082375","instruction":"JNZ 0x010823b9"}]
```

```json
{"verdict":"ABI_UNKNOWN","completeness":"PARTIAL",
 "conventions":{"calling_convention":null,"confidence":"UNKNOWN"},
 "parse":{"frame":{"fp":true,"push_ebp":true,"mov_ebp_esp":true,
                   "sub":36,"and_esp":4294967280},
          "esp_unresolved":true,
          "note":"esp_unresolved is set but harmless: frame.fp is true, so EBP resolution is used (2.2)"},
 "receiver":{"present":true,"register":"ECX","confidence":"INFERRED",
   "shape":"R-DIRECT","offsets":[0,20,40],"max_offset":40,"written_through":0},
 "stack_arguments":{"observed_slots":1,"gaps":0,"total_bytes":4,
   "confidence":"INFERRED",
   "slots":[{"ordinal":1,"entry_offset":"entry_ESP+0x4","ebp_offset":"EBP+0x8",
             "sizes":[4]}]},
 "cleanup":{"side":null,"bytes":null,"confidence":"UNKNOWN"},
 "return":{"register":"ST0","register_class":"float_or_x87",
   "confidence":"DERIVED","type":null},
 "tail_call":{"present":false},
 "abstained_because":[
   "no_terminal_ret: the listing is a prefix of a longer function",
   "truncated_listing: last instruction is a conditional branch and no RET or out-of-listing JMP terminates the listing"]}
```

Two lessons. (1) `and esp,0xfffffff0` poisons ESP resolution but **not** the
verdict, because the frame pointer carries the argument (`[EBP+0x8]`). If §2.2's
EBP-outranks-ESP rule were missing, this fixture would abstain for the wrong
reason. (2) A listing with no terminal `RET` must abstain even when the receiver
is perfectly clear. `receiver.offsets` reaches `+0x28`, which is the entropy
bound a layout claim may cite.

---

### F17 — text listing **with** an address column and a bytes column

```
00401230  55              PUSH EBP
00401231  8b ec           MOV EBP,ESP
00401233  8b 45 0c        MOV EAX,dword ptr [EBP+0xc]
00401236  33 c0           XOR EAX,EAX
00401238  c3              RET
```

```json
{"target":{"va":"0x00401230","instructions":5,"address_available":true},
 "verdict":"ABI_INFERRED","completeness":"CORE_RESOLVED",
 "conventions":{"calling_convention":"__cdecl","confidence":"INFERRED"},
 "receiver":{"present":false,"register":null,"confidence":"OBSERVED"},
 "stack_arguments":{"observed_slots":1,"gaps":1,"total_bytes":8,
   "confidence":"DERIVED",
   "slots":[{"ordinal":2,"entry_offset":"entry_ESP+0x8","ebp_offset":"EBP+0xc",
             "sizes":[4],"confidence":"INFERRED"}]},
 "cleanup":{"side":"caller","bytes":0,"confidence":"INFERRED"},
 "return":{"register":"EAX","register_class":"integral",
   "confidence":"INFERRED","type":null},
 "abstained_because":[]}
```

`gaps: 1` and `confidence: DERIVED`: argument ordinal 1 (`EBP+0x8`) is never
touched, so the observed slot is ordinal **2**, and `observed_slots: 1` must not
be read as "one parameter". The `33 c0` byte pair is the `XOR EAX,EAX` and the
`c3` the `RET` — the bytes column is consumed and discarded without corrupting
the mnemonic column.

---

### F18 — text listing with **no** address column, `ret 0x10`

```
55              PUSH EBP
8b ec           MOV EBP,ESP
8b 4c 24 08     MOV ECX,dword ptr [ESP+0x8]
8b 45 0c        MOV EAX,dword ptr [EBP+0xc]
33 c0           XOR EAX,EAX
c2 10 00        RET 0x10
```

```json
{"target":{"va":null,"instructions":6,"address_available":false},
 "verdict":"ABI_INFERRED","completeness":"CORE_RESOLVED",
 "parse":{"degraded":false,"esp_unresolved":false},
 "conventions":{"calling_convention":"__stdcall","confidence":"INFERRED"},
 "stack_arguments":{"observed_slots":2,"gaps":0,"total_bytes":8,
   "confidence":"INFERRED",
   "slots":[{"ordinal":1,"entry_offset":"entry_ESP+0x4",
             "sizes":[4],"note":"resolved from [ESP+8] with esp_delta=4"},
            {"ordinal":2,"entry_offset":"entry_ESP+0x8","ebp_offset":"EBP+0xc",
             "sizes":[4]}]},
 "cleanup":{"side":"callee","bytes":16,"confidence":"OBSERVED",
   "corroboration":"not_available","evidence":"ret 0x10"},
 "return":{"register":"EAX","register_class":"integral",
   "confidence":"INFERRED","type":null},
 "abstained_because":[]}
```

Two independent bases for the same argument area — `[ESP+8]` with
`esp_delta == 4` and `[EBP+0xc]` — resolve to the *same* key, which is the
cross-check that the ESP-delta model is right. `ret 0x10` (16) ≥ `total_bytes`
(8), so C4 does not fire and the extra 8 bytes are attributed to unused trailing
parameters. `address_available: false` and every `at` is `null`; citations use
`index` only.

---

### F19 — empty input

```json
[]
```

```json
{"verdict":"ABI_UNKNOWN","completeness":"EMPTY",
 "target":{"va":null,"instructions":0,"address_available":false},
 "observations":[],
 "conventions":{"calling_convention":null,"confidence":"UNKNOWN"},
 "cleanup":{"side":null,"bytes":null,"confidence":"UNKNOWN"},
 "return":{"register":null,"register_class":"unknown","confidence":"UNKNOWN","type":null},
 "abstained_because":[
   "empty_listing: no parseable instruction was supplied",
   "no_terminal_ret: function has no RET instruction"]}
```

An empty listing is a first-class result, not an exception, and it is the case
`evidence.py` hits whenever the disassembly category is `unavailable`. The
engine must never raise on it.

---

### F20 — data, not code

```
00401230  00 00 00 00
```

```json
{"verdict":"ABI_UNKNOWN","completeness":"EMPTY",
 "target":{"va":"0x00401230","instructions":0,"address_available":true},
 "observations":[{"id":"obs-0001","kind":"DATA_BYTE","index":0,
                  "at":"0x00401230","count":4}],
 "conventions":{"calling_convention":null,"confidence":"UNKNOWN"},
 "abstained_because":[
   "empty_listing: byte column with no mnemonic is not an instruction",
   "no_terminal_ret: function has no RET instruction"]}
```

Pins the bytes-column rule: four zero bytes with nothing after them must not be
tokenized as the mnemonic `00` with operands. `index == 0`, so the
observation-ordering invariant still holds.

---

## 7. Implementation notes

**Module layout** — one file, `abi_inference.py`, stdlib only, no imports from
`models.py` so it can be unit-tested in isolation:

```
parse_listing / parse_operand / parse_insn      # §1
extract(listing) -> (observations, frame_state) # §2  (no inference)
infer(observations, frame_state) -> record      # §3
cross_validate(record, ...) -> (record, conflicts)  # §5
analyze(...) = cross_validate(infer(extract(parse(...))))   # the public entry
finalize(record) -> record   # sorts, computes content_sha256
```

Structural separation is enforced by the signatures: `extract` has no
vocabulary for conventions, receivers, srets or returns, so it *cannot* emit a
claim. `infer` is the only function that may produce a `confidence` field.

**Integration with `evidence.py`** — add one category, leaving the existing
`record["abi"]` untouched:

```python
categories["abi_inference"] = _category(
    "available" if analysis else "unavailable",
    analysis,
    ["tools/reconstruction_tooling/abi_inference.py#analyze"],
    "inferred",          # -> evidence_state "INFERRED"
    "INFERRED" if (analysis or {}).get("verdict") == "ABI_INFERRED" else "UNKNOWN",
)
```

`_category` already maps `source_class "inferred"` → `evidence_state:
"INFERRED"`, which is the correct existing-vocabulary fit. Because
`verdict` is `ABI_UNKNOWN` for a large share of targets, the category's
`evidence_level` will honestly read `UNKNOWN` for those — and since
`context.py:99` treats `abi` as a critical category, **do not** make
`evidence_ready` depend on `abi_inference.availability`; that would unblock
targets whose ABI is genuinely unknown and would be exactly the fabrication the
mission forbids. Instead, publish it as a non-blocking section so a worker can
*read* the offset table while the validator still refuses to PASS on it.

**Validator** — `validate.py:156` computes `convention` from
`record["abi"]`. Add the inferred convention as a *second* signal:

```python
inferred = (evidence.get("categories", {}).get("abi_inference", {}) or {}).get("value") or {}
```

* both present and equal ⇒ the existing `PASS` path, plus
  `"inferred_source": "cross_validated"`.
* both present and different ⇒ the existing `FAIL` check fires **and** an
  `inferred_vs_persisted` conflict is already in `pack["conflicts"]`; change the
  `detail` string to name both sources. Never pick a winner.
* only `record["abi"]` ⇒ unchanged behaviour.
* only `abi_inference` ⇒ the check stays `WARN`, never `PASS`. A lone inference
  may not pass validation. This is the load-bearing line of the whole feature.

`RETURN SEMANTICS` (`validate.py:216`) must **not** read
`inferred["return"]["type"]`, which is always `null`. It continues to compare
`record["abi"].return_type` against the source span, exactly as today. A worker
may use `return.register_class` in its briefing, but the validator does not
consume it.

**Performance** — the listing is at most a few hundred instructions; extraction
is four linear passes and inference is O(instructions) plus sorting the slot
table. No CFG, no fixpoint. Target: under 1 ms per function, 58k functions
sweepable in well under a minute, which makes a full-binary corpus regression
test (`tests/expected/abi_corpus.json`) practical.

## 8. Test obligations

`tests/test_abi_inference.py`, stdlib `unittest`, no Ghidra, no network:

1. **F01–F20**, each asserting the complete expected fragment.
2. `test_deterministic` — every fixture, two calls, byte-identical JSON.
3. `test_citations_resolve` — every `based_on` id is in `observations`.
4. `test_no_types_emitted` — `record["return"]["type"] is None` for all fixtures,
   and no key anywhere in the record matches `r"(type_name|prototype|signature)"`.
5. `test_observations_have_no_claims` — no observation value is a string in
   `{"__cdecl","__thiscall","__stdcall","__fastcall"}` and no observation key is
   in `{"confidence","claim","verdict"}`.
6. `test_abstention_codes_closed` — the set of `abstained_because` codes across
   all fixtures is a subset of the §4.3 table, and every row of that table with a
   fixture is exercised.
7. `test_cross_validation_matrix` — F03 × {agree, `unknown`, disagree, absent}
   and F08 × {agree, disagree} over the eight cells of §5.1, asserting the exact
   confidence and conflict list per cell, including that Ghidra `unknown` is a
   no-op and that agreement never promotes an abstention.
8. `test_parser_degradation` — each of: address-only, bytes-only, neither,
   `;`-commented, AT&T-rendered, and a 50 %-mixed listing; each asserts
   `parse.degraded` or a successful parse and never an exception.
9. `test_unsupported_shapes_raise` — a float, an int, and `{"foo": 1}` raise
   `ValueError`.
10. `test_real_listing_regression` — F14, F15, F16 are verbatim bytes from
    `SporeApp.exe` 3.1.0.22 and their expected fragments are the contract; a
    Ghidra re-import that changes them is a real finding, not a test failure to
    be papered over.
