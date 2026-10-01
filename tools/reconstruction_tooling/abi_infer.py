#!/usr/bin/env python3
"""Pure x86-32 ABI-fact inference over Ghidra disassembly text.

What it does
------------
Given only the instruction stream of one function, this module derives the ABI
facts the stream itself can prove: a calling-convention *name* or nothing, the
register that carries a receiver, an entry-relative argument-slot table, the
cleanup side and byte count, a return register and a machine-level value class,
bounded `this`-offset observations, and always an explicit list of the reasons
it declined to conclude anything.

It is a pure function
---------------------
No file system, no Ghidra, no network, no clock, no randomness, no mutable
module state. `analyze(same_bytes) == analyze(same_bytes)` byte for byte, in
this interpreter and in a fresh one. The only imports are `re`, `bisect`, and
the two I/O-free helpers `canonical_json` / `sha256_json` from `models.py`.

Abstention policy
-----------------
`ABI_UNKNOWN` with a populated `abstained_because` is a *successful* result and
the expected one for a large share of SporeApp.exe. Weak or absent evidence
yields abstention, never a guessed exact signature. Silence from an external
source (Ghidra reports `unknown` for 99.89% of this binary) is never read as
agreement. Confidence is raised only by external agreement (capped at
`SUPPORTED`) and lowered only by conflict (never below `INFERRED`); a partial
parse removes evidence but never lowers confidence on its own. A conflict does
demote, and it does so visibly -- see the last deviation below.

It emits no C++ types
---------------------
No C++ type, parameter name, class name, field name or prototype string, ever.
`return.type` is `null` in every record. `sret.present` is never `true`: MSVC
sret and an out-parameter compile to the same instruction sequence, so the
engine reports the ambiguity instead of picking a winner. The `abi` block is
restricted to the 23-name whitelist of
`tools/reconstruction_knowledge.py::extract_abi`, so a derived record stays
conformant to the existing ABI schema instead of founding a second store.

Specification: `docs/tooling/abi-inference-spec.md`.
Test plan: `docs/tooling/abi-inference-tests.md`.
Confidence scale: `knowledgegraph/scale.py` (mirrored by `CONFIDENCE_ORDER`).

Deliberate deviations from the two documents, each forced by a contradiction
between them or by the real binary. Nothing here weakens a rule to make a test
pass; where two expected outputs cannot both hold, the one that is derivable
from the rule text is implemented and the other is reported.

* Confidence vocabulary. The contract mandates the canonical 7-level scale, so
  the spec's rung "DERIVED" is emitted as "APPROXIMATION" (same position).
* `C6B`. The spec has no rule for a *thiscall* that also pops its stack
  arguments, which is what MSVC emits for a member with arguments and is the
  shape of `0x008db310` and `0x004bdc00`. C6 alone would have to abandon them.
* `A1-IMM`. With callee cleanup and no argument read at all, the popped area is
  reported as `derived_slots` with `observed: false`, never as a parameter
  count (`0x00951230`).
* `R1` confidence needs three distinct offsets for `SUPPORTED`, not two:
  fixtures F01 and F13 have the same shape at two and three offsets and pin
  different answers.
* A load off a register that is provably the receiver (`MOV r,[ECX+k]`, then
  `[r+m]`) is treated as a receiver-rooted pointer. R-ALIAS only covers
  `MOV r,ECX`; without this, F13's `written_through` and `0x008db310`'s
  write-through are lost. The chain is never followed transitively.
* `flow_not_modelled` is raised when the linear ESP walk does not return to
  balance. Ghidra emits a function body in address order across basic blocks, so
  this is the honest signal that the listing is not one path.
* `untrusted_frame_stack_reads` / `frame_pointer_untrusted` require EBP to be
  loaded from a register or used as a memory base, not merely `push ebp` without
  `mov ebp,esp`: 11,995 functions in this binary match the loose form and most
  of them use EBP as an ordinary callee-saved register.
* `norm_disp` unwraps any eight-hex-digit literal >= 0x80000000, prefix or not,
  because Ghidra prints displacements as `0xfffffef4`. Immediates are *not*
  unwrapped, so `and esp,0xfffffff0` keeps its mask value.
* Layout invariance holds for every field except the provenance keys: the
  verbatim `raw` text, the `at` address and the `index`-derived fields. A text
  listing with a header row and one without cannot agree on listing positions.

Closed abstention vocabulary (`ABSTENTION_CODES`)
------------------------------------------------
`empty_listing`, `no_terminal_ret`, `ret_immediates_disagree`,
`ret_immediates_not_dword_multiple`, `ret_immediate_out_of_range`,
`ret_imm_below_highest_slot`,
`no_discriminator`, `esp_alignment_unknown`, `frame_pointer_untrusted`,
`untrusted_frame_stack_reads`, `receiver_not_determinable`,
`receiver_undetermined_blocks_convention`, `receiver_reassigned`,
`ecx_used_as_counter`, `ecx_address_taken_without_memory_access`,
`ecx_and_edx_indistinguishable`, `slot_width_ambiguous`, `slot_gaps_present`,
`sret_vs_out_param`, `variadic_not_decidable_from_listing`,
`variadic_caps_convention`, `unparsed_lines_present`, `truncated_listing`,
`flow_not_modelled`, `cleanup_undeterminable`.

Deliberate deviations, part two: rules narrowed toward abstention
----------------------------------------------------------------
Each of these makes a *positive* claim harder to reach. None adds a convention,
a type or a parameter name, and none can make a record look more authoritative
than the evidence behind it.

* `C6` and `C9` require receiver **absent**, not merely "not present", and `C6B`
  requires receiver **present**. The spec's own preconditions say "receiver
  absent" and the only sound `present: false` is R2 ("ECX is never read in any
  form"). R0's `present: null` is a known-unknown -- the receiver may exist and
  simply be unused -- so it satisfies none of the three, and the record abstains
  with `receiver_undetermined_blocks_convention` instead of naming a convention.
  `C6B` itself is untouched and still reaches the genuinely receiver-present
  real members (`0x008db310`, `0x004bdc00`).
* `C8-E` together with `C6B` is a contradiction, not a decision. A callee that
  pops its own arguments cannot also be reading an incoming EDX, so both
  readings are kept as claims at `UNKNOWN`, the ambiguity is named
  `ecx_and_edx_indistinguishable`, and the convention is null. The plan wanted a
  `conflicts` entry here; `conflicts` is reserved for *external* cross-validation
  (spec 5.1), so an internal collision is reported in `conventions.ambiguities`
  and `abstained_because` where it belongs.
* `ret N` with `N % 4 != 0` is a contradiction (`ret_immediates_not_dword_multiple`,
  plus `cleanup.contradiction`). C3 has no divisibility test in the spec and
  `ABSTENTION_CODES` had no code for one, so this is a **documented spec gap**
  the test plan caught first: a 6-byte pop is not a whole number of x86-32 stack
  arguments, so `cleanup.side`, `cleanup.bytes`, the derived slot count and the
  convention are all withheld rather than reported as `callee`/6 with four bytes
  of arguments beside it.
* A terminal `ret` immediate outside the 16-bit range x86-32 can encode is a
  contradiction too (`ret_immediate_out_of_range`). Also absent from both
  documents. Beyond being unsound, the un-bounded form is what made A1-IMM
  expand `ret_imm / 4` derived slots: `ret 0x100000000` is a billion-iteration
  loop, so the engine was not total on arbitrary text.
* A fourth variadic marker, `varargs_or_alloca_prologue`: two zero-initialised
  frame locals followed by a call, the MSVC va_list zero-fill. Spec 3.7 lists
  three markers and this is not one of them; without it a body carrying the
  classic variadic prologue names a convention. Like the other three it caps the
  convention through C12.
* A cross-validation conflict now demotes visibly. `drop(floor="INFERRED")` is a
  no-op for a convention that already sits on its floor, and `_drop` refuses to
  move an `OBSERVED` fact label, so a disagreement used to change nothing a
  consumer reads. The cleanup claim -- the one machine fact a disagreement is
  most often about -- is capped at `SUPPORTED` whenever a conflict exists. The
  cap is downward-only: values, sides and citations are untouched, and the
  record can only look *less* authoritative.
"""

import bisect
import re

from .models import canonical_json, sha256_json

SCHEMA = "openspore-abi-inference-1"
CONVENTIONS = ("__cdecl", "__stdcall", "__thiscall", "__fastcall")
VERDICTS = ("ABI_INFERRED", "ABI_UNKNOWN")

# Canonical 7-level scale, mirrored verbatim from knowledgegraph/scale.py
# EV_ORDER (weakest -> strongest). The engine only ever emits the first five
# rungs: OBSERVED labels a value read straight off the listing rather than an
# inference rung, and CONFIRMED/VERIFIED need evidence this engine never has.
CONFIDENCE_ORDER = (
    "UNKNOWN", "APPROXIMATION", "INFERRED", "SUPPORTED", "OBSERVED",
    "CONFIRMED", "VERIFIED",
)

# The spec ladder (UNKNOWN < DERIVED < INFERRED < SUPPORTED, with OBSERVED as a
# fact label) is embedded positionally in the canonical scale: the spec's
# "DERIVED" is this scale's "APPROXIMATION". No third name exists here.
_DERIVED = "APPROXIMATION"

# The only inner keys permitted inside record["abi"] (extract_abi whitelist).
ABI_KEYS = frozenset((
    "architecture", "calling_convention", "convention", "return_type",
    "return_width_bytes", "return_register", "stack_cleanup_bytes",
    "stack_cleanup_owner", "hidden_this_register", "hidden_receiver",
    "hidden_this", "hidden_this_type", "receiver_register", "receiver",
    "stack_arguments", "ordinary_stack_arguments",
    "ordinary_stack_argument_slots", "saved_registers", "ret_form",
    "termination", "return_semantics", "return", "return_observation",
))

# Closed abstention vocabulary (spec 4.3) plus the codes the spec's own
# fixtures and docs/tooling/abi-inference-tests.md additionally require.
ABSTENTION_CODES = frozenset((
    "empty_listing", "no_terminal_ret", "ret_immediates_disagree",
    "ret_immediates_not_dword_multiple", "ret_immediate_out_of_range",
    "ret_imm_below_highest_slot",
    "no_discriminator", "esp_alignment_unknown",
    "frame_pointer_untrusted", "untrusted_frame_stack_reads",
    "receiver_not_determinable", "receiver_undetermined_blocks_convention",
    "receiver_reassigned", "ecx_used_as_counter",
    "ecx_address_taken_without_memory_access", "ecx_and_edx_indistinguishable",
    "slot_width_ambiguous",
    "slot_gaps_present", "sret_vs_out_param",
    "variadic_not_decidable_from_listing", "variadic_caps_convention",
    "unparsed_lines_present", "truncated_listing", "flow_not_modelled",
    "cleanup_undeterminable",
))

# Closed rule-id vocabulary. `infer_rule` refuses an id that is not registered,
# for the same reason `abstain` refuses an unregistered code: a claim filed under
# a name no document defines is unreadable, and a typo is indistinguishable from
# a new rule. As with `abstain`, `analyze` catches the resulting
# `AssertionError` and returns the empty record, so the check is loud in tests
# (call `_infer_rules` directly) and safe in production (no record is lost
# mid-flight); the ids below are the complete set the engine can emit.
#
# The `-` qualified ids are **engine-local**: the specification defines the
# family (`C6`, `C8`, `A1`, `T1`, `V1`) and the engine needed a second, distinct
# claim inside the same family.
#   A1-IMM  argument slots derived from a terminal `ret N` alone (spec 3.4 gap).
#   C6B     a `__thiscall` that also pops its own stack arguments (spec gap).
#   C8-E    an incoming EDX read, the observation C8-E reasons from.
#   V1-VFT  **vftable slot membership, register-receiver form** -- the rule the
#           2026-09-28 extension adds. The proposal names it `V1`, but `V1` is
#           the specification's VARIADIC-SUSPICION rule, which this engine
#           implements as `record["variadic"]` and which is still live, so the
#           membership claim is filed under the same family with the qualifier
#           the other engine-local rules use.
#   R1-VFT  **vftable slot membership, callee-pop receiver form** -- the rule the
#           2026-09-29 extension adds. It is the *same fact* `V1-VFT` claims for
#           the caller-cleanup shape (where the receiver has to be in a register),
#           established for the callee-pop shape from the membership plus a read
#           of the *incoming* ECX. It never runs in the caller-cleanup shape: one
#           receiver fact gets one rule, and that one is `V1-VFT`.
#   R2-VFT  **vftable slot membership, callee-pop receiver form, address-taken
#           ECX** -- the rule the 2026-09-30 extension adds. Same fact, same
#           cleanup shape, same sound membership; the difference is the *class of
#           read*. `R1-VFT` fires when the body reads the incoming ECX and
#           dereferences or copies it; `R2-VFT` fires when the body takes its
#           **address** (`LEA r,[ECX+k]`) and never dereferences it at all, which
#           is why the engine's own reason for such a body is the different
#           unknown `ecx_address_taken_without_memory_access`. The two rules are
#           disjoint by construction (see `_vftable_address_receiver`).
#   T1-FWD  **tail-call forwarding** -- likewise named `T1` by the proposal, but
#           `T1` is the specification's TAIL-CALL rule and the engine already
#           emits it (for every listing whose only exit is an out-of-listing
#           `JMP`); two different claims may not share one id, and renaming the
#           existing one would rewrite committed goldens. So the forwarding claim
#           is `T1-FWD` and the existing tail-transfer claim keeps `T1`.
RULE_IDS = frozenset((
    "A1", "A1-IMM", "A2",
    "C1", "C2", "C3", "C4", "C5", "C6", "C6B", "C7", "C8", "C8-E", "C9",
    "C10", "C11", "C12",
    "D1",
    "R0", "R1", "R1-VFT", "R2", "R2-VFT",
    "RT1", "RT2", "RT3", "RT4",
    "S1", "S2", "S3",
    "T1", "T1-FWD", "T2",
    "V2",
    "V1-VFT",
))

#: The basis a vftable membership must declare to be usable by ``V1-VFT``. It is
#: the *only* accepted basis, and a caller that cannot state it has no
#: membership: the triage heuristics behind ``vtables.json`` measure under 45%
#: precision and are refuted by ``0x01053e00``, whose five index-claimed tables
#: are all unsound. See ``tools/reconstruction_tooling/vftables.py``.
VFTABLE_BASIS = "vftable_predicate"

CALLEE_SAVED = ("EBX", "EBP", "EDI", "ESI")

# `ret imm16` is the only return-with-pop form x86-32 encodes, so a terminal
# immediate outside this range is not a possible stack pop at all.
MAX_RET_IMMEDIATE = 0xFFFF

# The largest `LEA` displacement `R2-VFT` will read as a member offset: an
# object-sized address, and dword-aligned because every scalar in a 32-bit
# object is. It is a *narrowing* -- see `_incoming_member_leas` -- not the step
# that decides the receiver, and it is bounded so that a mask or a table constant
# cannot pass as a member address.
MAX_MEMBER_DISPLACEMENT = 0x7FC

GPR32 = ("EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI")
GPR16 = ("AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI")
GPR8 = ("AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH")

SUBREG_PARENT = {
    "AX": "EAX", "CX": "ECX", "DX": "EDX", "BX": "EBX",
    "SP": "ESP", "BP": "EBP", "SI": "ESI", "DI": "EDI",
    "AL": "EAX", "CL": "ECX", "DL": "EDX", "BL": "EBX",
    "AH": "EAX", "CH": "ECX", "DH": "EDX", "BH": "EBX",
}
SUBREG_PARENT.update({name: name for name in GPR32})

SIZE_TOKENS = {
    "BYTE": 1, "WORD": 2, "DWORD": 4, "QWORD": 8, "TBYTE": 10, "FWORD": 6,
    "OWORD": 16, "XMMWORD": 16, "YMMWORD": 32, "FLOAT": 4, "DOUBLE": 8,
    "NEAR": 4, "FAR": 4,
    "BYTE PTR": 1, "WORD PTR": 2, "DWORD PTR": 4, "QWORD PTR": 8,
    "TBYTE PTR": 10, "XMMWORD PTR": 16, "FLOAT PTR": 4, "DOUBLE PTR": 8,
    "OWORD PTR": 16, "NEAR PTR": 4,
}

X87_OPS = frozenset((
    "FLD", "FST", "FSTP", "FADD", "FADDP", "FSUB", "FSUBP", "FSUBR", "FSUBRP",
    "FMUL", "FMULP", "FDIV", "FDIVP", "FDIVR", "FDIVRP", "FABS", "FCHS", "FSQRT",
    "FIADD", "FISUB", "FISUBR", "FIMUL", "FIDIV", "FCOMP", "FCOMPP", "FCOMI",
    "FCOMIP", "FUCOMI", "FUCOMIP", "FLDCW", "FNSTCW", "FSTCW", "FNCLEX", "FNINIT",
    "FWAIT",
    "FXAM", "FNEG", "FNOP", "FNSTSW", "FRNDINT", "FTST", "FCOM", "FUCOM", "FUCOMP",
    "FUCOMPP", "FXCH", "FDECSTP", "FINCSTP", "FCHS", "FCMOVB", "FCMOVBE", "FCMOVE",
    "FCMOVNB", "FCMOVNBE", "FCMOVNE", "FCMOVNU", "FCMOVU", "FLDZ", "FLDPI", "FLD1",
    "FLDL2T", "FLDL2E", "FLDLOG2", "FLDLN2", "FILD", "FIST", "FISTP", "FISTTP",
    "FICOM", "FICOMP", "FPATAN", "FPREM", "FPREM1", "FPTAN", "FRSTOR", "FSCALE",
    "FSIN", "FSINCOS", "FBLD", "FBSTP", "FYL2X", "FYL2XP1",
))

# Mnemonics whose memory operand is written. Everything else that takes a
# memory operand reads it. PUSH/POP are listed explicitly: their operand is the
# value transferred, so a `push [EBP+8]` is a *read* of that slot.
STORE_MNEM = frozenset((
    "MOV", "MOVUPS", "MOVAPS", "MOVSS", "MOVSD", "MOVLPS", "MOVHPS", "MOVLPD",
    "MOVHPD", "MOVNTI", "MOVDQU", "MOVDQA", "MOVBE", "XADD", "XCHG", "ADD", "SUB",
    "ADC", "SBB", "AND", "OR", "XOR", "NOT", "NEG", "INC", "DEC", "IMUL",
    "STOSB", "STOSW", "STOSD", "STOSQ", "CMPXCHG", "CMPXCHG8B", "CMPXCHG16B",
    "SETZ", "SETNZ", "SETE", "SETNE", "SETA", "SETAE", "SETB", "SETBE", "SETAE",
    "SETG", "SETGE", "SETL", "SETLE", "SETC", "SETNC", "SETP", "SETNP", "SETO",
    "SETNO", "SETS", "SETNS", "SETNG", "SETNGE", "SETNL", "SETNLE", "SETNA",
    "SETNAE", "SETNBE", "SETPE", "SETPO", "ADDPS", "ADDSS", "SUBPS", "SUBSS",
    "ANDPS", "ORPS", "XORPS", "LODSB", "LODSW", "LODSD",
))

# Bounded value-origin pass (spec 3.5).
ARITH_MNEM = frozenset((
    "ADD", "SUB", "AND", "OR", "INC", "DEC", "SHL", "SHR", "SAR", "ROL", "ROR",
    "NEG", "NOT", "BSWAP", "ADC", "SBB",
))
MUL_MNEM = frozenset(("IMUL", "MUL", "DIV", "IDIV"))
# Every x86 conditional-branch mnemonic Ghidra/objdump may emit, including the
# carry-flag synonyms. Ghidra renders carry branches as ``JC`` where objdump and
# the Intel manual write ``JB``; they are the same opcode (0x72 rel8) and the same
# condition (CF=1). Omitting the synonym made a well-formed carry branch parse as
# ``kind="unparsed"`` / ``reason="unknown_mnemonic"``, which marks the whole
# listing ``degraded`` and holds CONSTANTS at WARN on a body that is in fact fully
# parsed. The synonyms are listed explicitly rather than derived, because
# BRANCH_MNEM also feeds ``_BRANCH_TARGET_MNEM`` and the canonical mnemonics must
# stay stable; adding a spelling here does not add a new semantics, and the
# branch-condition readers already key off the opcode/condition, not the
# spelling.
BRANCH_MNEM = frozenset((
    "JA", "JAE", "JB", "JBE", "JECXZ", "JE", "JG", "JGE", "JL", "JLE", "JNE",
    "JNO", "JNP", "JNS", "JNZ", "JO", "JP", "JPE", "JPO", "JRCXZ", "JS", "JZ",
    # carry-flag and inverted synonyms of the entries above (same opcodes).
    # JNC is the carry-CLEAR spelling of JAE/JNB; JC is the carry-SET spelling
    # of JB. Both are real 0x70-0x7F short-jump opcodes and both are emitted by
    # one disassembler or the other for the same bytes.
    "JC", "JNA", "JNB", "JNBE", "JNC", "JNG", "JNGE", "JNL", "JNLE",
    "LOOP", "LOOPE", "LOOPNE", "JMP",
))

KNOWN_MNEMONICS = frozenset((
    "AAA", "AAD", "AAM", "AAS", "ADC", "ADD", "ADDPS", "ADDSS", "AND", "ANDN",
    "ANDPS", "ARPL", "BOUND", "BSF", "BSR", "BSWAP", "BT", "BTC", "BTR", "BTS",
    "CALL", "CBW", "CDQ", "CDQE", "CLC", "CLD", "CLI", "CLTS", "CMC", "CMP",
    "CMPSB", "CMPSD", "CMPSW", "CMPXCHG", "CMPXCHG8B", "CMPXCHG16B", "COMISD",
    "COMISS", "CPUID", "CQO", "CRC32", "CVTDQ2PS", "CVTPS2DQ", "CVTSS2SD",
    "CVTSD2SS", "CVTSI2SD", "CVTSI2SS", "CVTSS2SI", "CVTSD2SI", "CWD", "CWDE",
    "DAA", "DAS", "DEC", "DIV", "DIVPD", "DIVPS", "DIVSS", "ENDBR32", "ENDBR64",
    "FICOM", "FIDIVR", "HLT", "IDIV", "IMUL", "IN", "INC", "INS", "INSD", "INSW",
    "INT", "INT1", "INT3", "INTO", "INVD", "INVLPG", "IRET", "IRETD", "JMPX",
    "LAHF", "LAR", "LDS", "LEA", "LEAVE", "LES", "LFENCE", "LFS", "LGDT", "LGS",
    "LIDT", "LLDT", "LMSW", "LODSB", "LODSD", "LODSW", "LSL", "LSS", "LTR",
    "MASKMOVDQU", "MFENCE", "MONITOR", "MOV", "MOVAPS", "MOVBE", "MOVQ", "MOVSB",
    "MOVSHDUP", "MOVSS", "MOVSW", "MOVSX", "MOVSXD", "MOVUPD", "MOVUPS", "MOVZX",
    "MUL", "MULPD", "MULPS", "MULSS", "MWAIT", "NEG", "NOP", "OR", "ORPD", "ORPS",
    "OUT", "OUTSB", "OUTSD", "OUTSW", "PACKSSDW", "PACKSSWB", "PACKUSWB", "PADDB",
    "PADDD", "PADDQ", "PADDSB", "PADDSW", "PADDUSB", "PADDUSW", "PADDW", "PALIGNR",
    "PAND", "PANDN", "PAVGB", "PAVGW", "PCMPEQB", "PCMPEQD", "PCMPGTB", "PCMPGTD",
    "PCMPGTW", "PEXTRW", "PINSRW", "PMADDWD", "PMAXSW", "PMAXUB", "PMINSW",
    "PMINUB", "PMULHUW", "PMULHW", "PMULLW", "PMULUDQ", "POR", "PSADBW", "PSHUFD",
    "PSHUFHW", "PSHUFLW", "PSHUFW", "PSLLD", "PSLLDQ", "PSLLQ", "PSLLW", "PSRAD",
    "PSRAW", "PSRLD", "PSRLDQ", "PSRLQ", "PSRLW", "PSUBB", "PSUBD", "PSUBQ",
    "PSUBSB", "PSUBSW", "PSUBUSB", "PSUBUSW", "PSUBW", "PUNPCKHBW", "PUNPCKHDQ",
    "PUNPCKHQDQ", "PUNPCKHWD", "PUSH", "PUSHA", "PUSHAD", "PUSHF", "PUSHFD",
    "PXOR", "RCL", "RCR", "RDMSR", "RDPMC", "RDTSC", "RET", "RETF", "RETFQ",
    "RETN", "ROL", "ROR", "RSM", "SAHF", "SAL", "SAR", "SBB", "SCASB", "SCASD",
    "SCASW", "SFENCE", "SGDT", "SHL", "SHLD", "SHR", "SHRD", "SHUFPS", "SIDT",
    "SLDT", "SLTR", "SMSW", "STC", "STD", "STI", "STOSB", "STOSD", "STOSW", "STR",
    "SUB", "SUBPD", "SUBPS", "SUBSS", "SWAPGS", "SYSCALL", "SYSENTER", "SYSEXIT",
    "SYSLRET", "TDC", "TEST", "TZCNT", "UCOMISD", "UCOMISS", "UD0", "UD1", "UD2",
    "UNPCKHPD", "UNPCKHPS", "UNPCKLDQ", "UNPCKLQDQ", "VERR", "VERW", "WAIT",
    "WBINVD", "WRMSR", "XADD", "XCHG", "XGETBV", "XLATB", "XOR", "XORPD", "XORPS",
    "XSAVE", "XSETBV", "ENDBR", "KMOVW", "POP", "REP", "REPE", "REPNE", "REPZ",
    "REPNZ", "LOCK", "MOVSD", "MOVSS", "STOS", "CMPSB", "CMPSW", "STOSD", "STOSB",
)) | X87_OPS | STORE_MNEM | BRANCH_MNEM

RE_ATT = re.compile(
    r"(^|\s)[a-z][a-z0-9]*[lqw]\s|retq|pushq|\$\(|\(%\w|-?\d*\(%\w"
    r"|%[a-z]{2,3}\b|\$\s?0x[0-9a-f]")
RE_COMMENT = re.compile(r";|//")
RE_ADDR = re.compile(r"^0x([0-9A-Fa-f]{1,8})(?=\s|$)|^([0-9A-Fa-f]{6,8})(?=\s|$)")
RE_BYTE_GROUP = re.compile(r"^([0-9A-Fa-f]{2,30})(?=\s|$)")
RE_SEGMENT = re.compile(r"^(FS|GS|DS|ES|CS|SS):", re.IGNORECASE)
RE_RULER = re.compile(r"^[-=+|\s]+$")
RE_HEADER = re.compile(
    r"^(?:Listing|Address|Instruction|Bytes|Opcode|Label|Comment)\b", re.IGNORECASE)
RE_SIZE_PREFIX = re.compile(
    r"^(" + "|".join(re.escape(key) for key in sorted(SIZE_TOKENS, key=len, reverse=True))
    + r")\s+", re.IGNORECASE)
RE_LABEL = re.compile(r"^[A-Za-z_.?$@][\w.$?]*:[^ ]*$")
RE_ADDRESS_LABEL = re.compile(r"^[0-9A-Fa-f]{4,8}$")

_BRANCH_TARGET_MNEM = frozenset(("CALL", "JMP", "JMPX")) | BRANCH_MNEM
REP_PREFIXES = frozenset(("REP", "REPE", "REPNE", "REPZ", "REPNZ", "LOCK"))


def _fmt_hex(value):
    """Format a 32-bit value the way the rest of the tooling does."""
    return "0x%08x" % (int(value) & 0xFFFFFFFF)


def _signed32(value):
    value = int(value) & 0xFFFFFFFF
    return value - 0x100000000 if value >= 0x80000000 else value


def _index_of(value):
    return CONFIDENCE_ORDER.index(value)


def _at_least(value, floor):
    return value in CONFIDENCE_ORDER and _index_of(value) >= _index_of(floor)


def _weaker(value, ceiling):
    """Cap a confidence at `ceiling` without raising it."""
    if value not in CONFIDENCE_ORDER or ceiling not in CONFIDENCE_ORDER:
        return value
    return CONFIDENCE_ORDER[min(_index_of(value), _index_of(ceiling))]


def _bump(value):
    """One rung up, capped at SUPPORTED. OBSERVED is a fact and is never promoted."""
    if value not in CONFIDENCE_ORDER or _index_of(value) >= _index_of("OBSERVED"):
        return value
    return CONFIDENCE_ORDER[min(_index_of(value) + 1, _index_of("SUPPORTED"))]


def _drop(value, floor="INFERRED"):
    """One rung down, never below `floor`. OBSERVED is a fact and is never demoted."""
    if value not in CONFIDENCE_ORDER or value == "OBSERVED":
        return value
    if _index_of(value) <= _index_of(floor):
        return value
    return CONFIDENCE_ORDER[max(_index_of(value) - 1, _index_of(floor))]


def norm_disp(literal):
    """Normalise a displacement literal to a signed 32-bit int.

    A leading '-' is stripped and re-applied. A literal written as exactly eight
    hex digits whose value is >= 0x80000000 is unwrapped: Ghidra renders the
    displacement of -0xc as 0xfffffef4, with or without the 0x prefix, so the
    prefix must not be what decides it.
    """
    text = str(literal).strip()
    negative = text.startswith("-")
    if negative:
        text = text[1:].strip()
    prefixed = text[:2].lower() == "0x"
    body = text[2:] if prefixed else text
    if not body or any(character not in "0123456789abcdefABCDEF" for character in body):
        raise ValueError("not a displacement literal: %r" % literal)
    value = int(body, 16)
    if len(body) == 8 and value >= 0x80000000:
        value -= 0x100000000
    return -value if negative else value


def _parse_int(token):
    """Parse an immediate. No unsigned unwrapping: `and esp,0xfffffff0` is a mask."""
    text = str(token).strip()
    negative = text.startswith("-")
    if negative:
        text = text[1:].strip()
    prefixed = text[:2].lower() == "0x"
    body = text[2:] if prefixed else text
    if not body or any(character not in "0123456789abcdefABCDEF" for character in body):
        raise ValueError("not an immediate literal: %r" % token)
    if prefixed:
        value = int(body, 16)
    elif body.isdigit():
        value = int(body, 10)
    else:
        value = int(body, 16)
    return -value if negative else value


def split_operands(body):
    """Split an operand list on ',' at bracket depth 0."""
    parts = []
    depth = 0
    current = []
    for character in body:
        if character == "[":
            depth += 1
        elif character == "]":
            depth = max(0, depth - 1)
        if character == "," and depth == 0:
            parts.append("".join(current).strip())
            current = []
            continue
        current.append(character)
    tail = "".join(current).strip()
    if tail:
        parts.append(tail)
    return [part for part in parts if part]


def _parse_mem(inside, text, segment):
    base = None
    index = None
    scale = None
    disp = 0
    body = inside.replace("+ -", "- ")
    body = body.replace("+", " + ").replace("-", " - ")
    sign = 1
    for token in body.split():
        upper = token.upper()
        if upper == "+":
            sign = 1
            continue
        if upper == "-":
            sign = -1
            continue
        if "*" in token:
            register, _, magnitude = token.partition("*")
            register = register.upper()
            if register in GPR32:
                index = register
                try:
                    scale = (int(magnitude, 16) if magnitude[:2].lower() == "0x"
                             else int(magnitude, 10))
                except ValueError:
                    scale = None
                continue
            return None
        if upper in GPR32:
            base = upper
            continue
        try:
            disp += sign * norm_disp(token)
        except ValueError:
            return None
    return {"kind": "mem", "size": None, "size_inferred": False,
            "segment": segment, "base": base, "index": index, "scale": scale,
            "disp": _signed32(disp), "text": text}


def parse_operand(text, context="mem"):
    """Classify one operand into reg / imm / mem / target / symbol / opaque."""
    raw = str(text).strip()
    if not raw:
        return {"kind": "opaque", "text": raw}
    size = None
    size_inferred = False
    while True:
        size_match = RE_SIZE_PREFIX.match(raw)
        if not size_match:
            break
        candidate = " ".join(size_match.group(1).upper().split())
        if candidate not in SIZE_TOKENS:
            break
        size = SIZE_TOKENS[candidate]
        raw = raw[size_match.end():].strip()
    segment = None
    match = RE_SEGMENT.match(raw)
    if match:
        segment = match.group(1).upper()
        raw = raw[match.end():].strip()
        if raw and not raw.startswith("["):
            inner = raw.upper()
            if inner in GPR32:
                return {"kind": "mem", "size": size or 4,
                        "size_inferred": size is None, "segment": segment,
                        "base": inner, "index": None, "scale": None, "disp": 0,
                        "text": text}
    if raw.startswith("["):
        close = raw.rfind("]")
        if close < 0 or raw[close + 1:].strip():
            return {"kind": "opaque", "text": text}
        parsed = _parse_mem(raw[1:close].strip(), text, segment)
        if parsed is None:
            return {"kind": "opaque", "text": text}
        if size is None:
            size = 4
            size_inferred = True
        parsed["size"] = size
        parsed["size_inferred"] = size_inferred
        return parsed
    upper = raw.upper()
    if upper in GPR32 or upper in GPR16 or upper in GPR8:
        return {"kind": "reg", "reg": upper, "text": text}
    if re.match(r"^(XMM|YMM|MM)\d+$", upper) or re.match(r"^ST\(\d\)$", upper):
        return {"kind": "reg", "reg": upper, "text": text}
    if re.match(r"^(CR|DR|TR)\d+$", upper):
        return {"kind": "reg", "reg": upper, "text": text}
    if raw.startswith("*") and raw[1:].strip().upper() in GPR32:
        return {"kind": "reg", "reg": raw[1:].strip().upper(), "text": text}
    try:
        value = _parse_int(raw)
    except ValueError:
        if raw[0].isalpha() or raw[0] in "_$.?@":
            return {"kind": "symbol", "text": text}
        return {"kind": "opaque", "text": text}
    if context == "target":
        return {"kind": "target", "value": value, "text": text}
    return {"kind": "imm", "value": value, "text": text}


def parse_insn(text, index=0, va=None):
    """Parse one instruction line into mnemonic, suffix and classified operands."""
    raw = str(text).strip()
    body = raw
    if ":" in body and not body.startswith("["):
        head, _, tail = body.partition(":")
        if RE_ADDRESS_LABEL.match(head) and tail.strip():
            body = tail.strip()
    if not body:
        return {"index": index, "va": va, "raw": raw, "base": "", "suffix": "",
                "prefix": "", "operands": [], "known": False, "empty": True}
    head, _, tail = body.partition(" ")
    tail = tail.strip()
    mnemonic = head.upper()
    suffix = ""
    if "." in mnemonic:
        mnemonic, _, suffix = mnemonic.partition(".")
    prefix = ""
    if mnemonic in REP_PREFIXES:
        prefix = mnemonic
        rest = tail.strip()
        if suffix:
            mnemonic = suffix
            suffix = ""
        else:
            first, _, remainder = rest.partition(" ")
            if first.upper() in KNOWN_MNEMONICS:
                mnemonic = first.upper()
                tail = remainder.strip()
            else:
                mnemonic = ""
    operands = split_operands(tail) if tail else []
    context = "target" if mnemonic in _BRANCH_TARGET_MNEM else "imm"
    return {
        "index": index,
        "va": va,
        "raw": raw,
        "base": mnemonic,
        "suffix": suffix,
        "prefix": prefix,
        "operands": [parse_operand(part, context) for part in operands],
        "known": mnemonic in KNOWN_MNEMONICS,
        "empty": False,
    }




_ATT_SIZE = {
    "MOVSD": "dword ptr", "MOVSS": "dword ptr", "MOVL": "dword ptr",
    "MOVAPS": "xmmword ptr", "MOVUPS": "xmmword ptr", "MOVDQA": "xmmword ptr",
    "MOVDQU": "xmmword ptr", "MOVQ": "qword ptr", "MOVBQA": "xmmword ptr",
    "MOVW": "word ptr", "MOVB": "byte ptr", "LEAW": "word ptr",
}


def _att_operand_to_intel(text, mnemonic="MOV"):
    """Normalise one AT&T operand to Intel syntax.

    In AT&T a parenthesised operand *is* the memory operand, so the width has to
    be supplied from the mnemonic; `*` marks an indirect branch target instead.
    """
    token = text.strip()
    if not token:
        return token
    if token.startswith("%"):
        return token[1:].upper()
    indirect = False
    if token.startswith("*"):
        indirect = True
        token = token[1:].strip()
    if token.startswith("$"):
        return token[1:]
    match = re.match(r"^(.*?)\((.*)\)$", token)
    if not match:
        return token.upper() if re.match(r"^[a-z]+$", token) else token
    disp, inside = match.group(1), match.group(2)
    if disp == "":
        displacement = ""
    elif disp.startswith("0x") or disp.startswith("-0x") or re.match(r"^-?\d+$", disp):
        displacement = disp if disp.startswith("-") or disp.startswith("0x") else "0x" + disp
    else:
        displacement = disp

    parts = [piece.strip() for piece in inside.split(",") if piece.strip()]
    registers = [piece[1:].upper() for piece in parts if piece.startswith("%")]
    scale = None
    for piece in parts:
        if not piece.startswith("%") and re.match(r"^\d+$", piece):
            scale = int(piece, 10)
    base = registers[0] if registers else None
    index = registers[1] if len(registers) > 1 else None
    if index is not None and scale is None:
        scale = 1
    inner = []
    if base:
        inner.append(base)
    if index:
        inner.append("%s*0x%x" % (index, scale if scale else 1))
    if displacement:
        inner.append(displacement)
    rendered = "[" + " + ".join(inner) + "]"
    if mnemonic == "LEA":
        return rendered
    return _ATT_SIZE.get(mnemonic, "dword ptr") + " " + rendered


def _att_bare_form(text):
    """`ret`, `retq` and `je 0x00401024` are AT&T but match no suffix pattern."""
    if "[" in text or "]" in text or "%" in text or "$" in text:
        return False
    head, _, tail = text.partition(" ")
    if head.upper() not in KNOWN_MNEMONICS:
        return False
    tail = tail.strip()
    if not tail:
        return True
    try:
        _parse_int(tail)
    except ValueError:
        return False
    return True


def normalize_att_line(line):
    """AT&T -> Intel for a single line, or None when the line is not AT&T."""
    text = line.strip()
    if not text:
        return None
    address = None
    match = re.match(r"^(0x)?([0-9a-f]{4,8}):\s+(.*)$", text)
    if match:
        address = int(match.group(2), 16)
        text = match.group(3).strip()
    if not RE_ATT.search(text) and not _att_bare_form(text):
        return None
    head, _, tail = text.partition(" ")
    mnemonic = head.lower()
    suffix = ""
    while mnemonic and mnemonic[-1] in "lqw":
        suffix = mnemonic[-1].upper()
        mnemonic = mnemonic[:-1]
    mnemonic = mnemonic.upper()
    if mnemonic in ("RET", "RETF", "IRET", "IRETD", "LEAVE", "NOP", "PUSHFD", "POPFD"):
        operands = [piece.strip() for piece in tail.split(",") if piece.strip()]
        converted = [piece[1:] if piece.startswith("$")
                     else _att_operand_to_intel(piece, mnemonic) for piece in operands]
        body = " ".join(converted)
    else:
        operands = [piece.strip() for piece in tail.split(",") if piece.strip()]
        converted = [_att_operand_to_intel(piece, mnemonic) for piece in reversed(operands)]
        body = ", ".join(converted)
    return (address, ("%s%s %s" % (mnemonic, ("." + suffix) if suffix else "", body)).strip())


def normalize_listing(disassembly):
    """Accept every legal input shape and return (lines, meta).

    Accepted, in priority order: a list of {"address", "instruction"} dicts; a
    dict with an "instructions" list; a list of raw listing lines; a raw listing
    string; None / "" / []. Anything else raises ValueError. Silently coercing
    an unrecognised shape is forbidden.
    """
    if disassembly is None:
        return [], {"layout": "empty", "declared_count": None, "address_available": False}

    if isinstance(disassembly, bool):
        raise ValueError("unsupported disassembly shape: bool")
    if isinstance(disassembly, dict):
        instructions = disassembly.get("instructions")
        if not isinstance(instructions, list):
            raise ValueError(
                "unsupported disassembly shape: dict without an 'instructions' list")
        declared = disassembly.get("count")
        lines, meta = normalize_listing(instructions)
        meta["layout"] = "json_instruction_list"
        meta["declared_count"] = declared if isinstance(declared, int) else None
        return lines, meta
    if isinstance(disassembly, (int, float)):
        raise ValueError("unsupported disassembly shape: %s" % type(disassembly).__name__)
    if isinstance(disassembly, list):
        if not disassembly:
            return [], {"layout": "empty", "declared_count": None,
                        "address_available": False}
        if all(isinstance(item, dict) for item in disassembly):
            lines = []
            for item in disassembly:
                if "instruction" not in item and "text" not in item:
                    raise ValueError(
                        "unsupported disassembly shape: dict without an 'instruction'")
                raw = item.get("instruction", item.get("text"))
                lines.append((item.get("address"), "" if raw is None else str(raw), False))
            return lines, {"layout": "json_instruction_list", "declared_count": None,
                           "address_available": any(line[0] is not None for line in lines)}
        if all(isinstance(item, str) for item in disassembly):
            return [(None, item, False) for item in disassembly], {
                "layout": "plain_text", "declared_count": None,
                "address_available": False}
        raise ValueError("unsupported disassembly shape: mixed list")
    if isinstance(disassembly, str):
        if not disassembly.strip():
            return [], {"layout": "empty", "declared_count": None,
                        "address_available": False}
        lines = disassembly.splitlines()
        if len(lines) == 1:
            att = normalize_att_line(lines[0])
            if att is not None and (att[0] is not None or "%" in lines[0]):
                address, text = att
                return ([(address, text, False)] if text else []), {
                    "layout": "att_text", "declared_count": None,
                    "address_available": address is not None}
        matched = sum(1 for line in lines if RE_ATT.search(line))
        if lines and matched * 2 >= len(lines):
            converted = []
            for line in lines:
                att = normalize_att_line(line)
                if att is None:
                    converted.append((None, line, True))
                    continue
                converted.append((att[0], att[1], False))
            return converted, {"layout": "att_text", "declared_count": None,
                               "address_available": any(item[0] is not None
                                                       for item in converted)}
        layout = "gcodebrowser_text" if any(
            RE_ADDR.match(line.strip()[:10] or "") for line in lines) else "plain_text"
        return [(None, line, False) for line in lines], {
            "layout": layout, "declared_count": None, "address_available": False}
    raise ValueError("unsupported disassembly shape: %s" % type(disassembly).__name__)


def _split_line_columns(line):
    """Address / bytes / mnemonic column split, exactly per spec 1.2."""
    text = line
    position = 0
    while position < len(text) and text[position] in " \t":
        position += 1
    address = None
    match = RE_ADDR.match(text[position:])
    if match:
        address = int(match.group(1) or match.group(2), 16)
        position += match.end()
    byte_groups = []
    while len(byte_groups) < 15:
        cursor = position
        while cursor < len(text) and text[cursor] in " \t":
            cursor += 1
        group = RE_BYTE_GROUP.match(text[cursor:])
        if not group or len(group.group(1)) % 2:
            break
        byte_groups.append(group.group(1))
        position = cursor + group.end()
        while position < len(text) and text[position] in " \t":
            position += 1
    remainder = text[position:].strip()
    if byte_groups and remainder and address is None and not remainder[0].isupper():
        return None, [], text.strip()
    if byte_groups and not remainder:
        return address, byte_groups, ""
    return address, byte_groups, remainder


def _is_scaffolding(text):
    return bool(RE_RULER.match(text) or RE_HEADER.match(text))


def parse_listing(disassembly):
    """Normalise the input, split columns and parse every line.

    Returns (insns, meta) where each insn is the dict produced by `parse_insn`
    plus a "kind" of "insn" / "data" / "blank" / "unparsed" and, for unparsed
    lines, the reason.
    """
    lines, meta = normalize_listing(disassembly)
    insns = []
    for index, entry in enumerate(lines):
        va, raw_line, att_mismatch = entry
        text = RE_COMMENT.split(raw_line, 1)[0].rstrip()
        if not text.strip():
            insns.append({"index": index, "va": None, "raw": raw_line, "base": "",
                          "suffix": "", "operands": [], "known": False,
                          "empty": True, "kind": "blank"})
            continue
        if _is_scaffolding(text.strip()):
            insns.append({"index": index, "va": None, "raw": raw_line, "base": "",
                          "suffix": "", "operands": [], "known": False,
                          "empty": True, "kind": "blank"})
            continue
        address, byte_groups, remainder = _split_line_columns(text)
        if address is None and va is not None:
            address = va if isinstance(va, int) else _coerce_va(va)
        if not remainder:
            insns.append({"index": index, "va": address, "raw": remainder,
                          "base": "", "suffix": "", "operands": [], "known": False,
                          "empty": True, "kind": "data", "byte_count": len(byte_groups)})
            continue
        parsed = parse_insn(remainder, index=index, va=address)
        parsed["va"] = address
        if att_mismatch:
            parsed["kind"] = "unparsed"
            parsed["reason"] = "att_mismatch"
        elif not parsed["known"]:
            parsed["kind"] = "unparsed"
            parsed["reason"] = "unknown_mnemonic"
        else:
            parsed["kind"] = "insn"
        insns.append(parsed)
    meta["address_available"] = any(item.get("va") is not None for item in insns)
    meta["instruction_count"] = sum(1 for item in insns if item["kind"] == "insn")
    meta["unparsed_count"] = sum(1 for item in insns if item["kind"] == "unparsed")
    return insns, meta


def _coerce_va(value):
    if isinstance(value, bool):
        return None
    if isinstance(value, int):
        return value & 0xFFFFFFFF
    text = str(value).strip().lower()
    prefixed = text[:3] == "0x" or text[:4] == "rva:"
    if prefixed:
        text = text[3:] if text[:3] == "0x" else text[4:]
    if not text or any(character not in "0123456789abcdef" for character in text):
        return None
    return int(text, 16) & 0xFFFFFFFF


def _parent(register):
    if register is None:
        return None
    return SUBREG_PARENT.get(register, register)


def _is_store(insn, operand_index):
    if operand_index != 0:
        return False
    return insn["base"] in STORE_MNEM


def _operand_reg(operand):
    if operand["kind"] == "reg":
        return operand["reg"]
    return None


def _operand_names_register(operand, name):
    """How many times `name` appears as a register in one rendered operand.

    Counted on the operand's own text, not on its decomposed fields, because the
    two are not equivalent: `[ECX + ECX + 0x4]` and `[ECX + 0x4]` both decompose
    to base ``ECX``, no index register and displacement ``4``. Only the text
    tells a member address from a sum over the same register.
    """
    text = operand.get("text")
    if not isinstance(text, str):
        return -1
    return len(re.findall(r"\b%s\b" % re.escape(name), text, re.IGNORECASE))


def _frame_prepass(insns):
    frame = {
        "push_ebp": False, "push_ebp_at": None, "mov_ebp_esp": False,
        "mov_ebp_esp_at": None, "sub": None, "lea_esp": None, "and_esp": None,
        "fp": False, "ebp_is_general_register": False,
    }
    real = [item for item in insns if item["kind"] == "insn"]
    for item in real:
        base = item["base"]
        operands = item["operands"]
        if base == "PUSH" and operands and _operand_reg(operands[0]) == "EBP":
            frame["push_ebp"] = True
            if frame["push_ebp_at"] is None:
                frame["push_ebp_at"] = item["index"]
        if (base in ("MOV", "LEA") and len(operands) == 2
                and _operand_reg(operands[0]) == "EBP"
                and _operand_reg(operands[1]) == "ESP"):
            if base == "MOV":
                frame["mov_ebp_esp"] = True
                if frame["mov_ebp_esp_at"] is None:
                    frame["mov_ebp_esp_at"] = item["index"]
            else:
                disp = operands[0].get("disp")
                if isinstance(disp, int) and disp < 0 and frame["lea_esp"] is None:
                    frame["lea_esp"] = -disp
        if base == "SUB" and len(operands) == 2 and _operand_reg(operands[0]) == "ESP":
            value = operands[1].get("value")
            if isinstance(value, int) and (frame["sub"] is None or value > frame["sub"]):
                frame["sub"] = value
        if base == "AND" and len(operands) == 2 and _operand_reg(operands[0]) == "ESP":
            value = operands[1].get("value")
            if isinstance(value, int) and frame["and_esp"] is None:
                frame["and_esp"] = value
    mov_index = frame["mov_ebp_esp_at"]
    if mov_index is not None:
        leading_pushes = all(item["base"] == "PUSH"
                            for item in real if item["index"] < mov_index)
        frame["fp"] = bool(leading_pushes)
    for item in real:
        if item["index"] == mov_index or item["base"] in ("POP", "LEAVE", "LEAVEQ"):
            continue
        for position, operand in enumerate(item["operands"]):
            if operand["kind"] != "reg" or not _is_store(item, position):
                continue
            if SUBREG_PARENT.get(operand["reg"]) == "EBP" and item["base"] not in ("MOV", "LEA"):
                frame["fp"] = False
            if SUBREG_PARENT.get(operand["reg"]) == "EBP" and item["base"] in ("MOV", "LEA"):
                if item["index"] != mov_index:
                    frame["fp"] = False
                if item["base"] == "MOV" and item["index"] != mov_index \
                        and len(item["operands"]) > 1 \
                        and item["operands"][1]["kind"] == "reg":
                    frame["ebp_is_general_register"] = True
        for operand in item["operands"]:
            if operand["kind"] == "mem" and (operand["base"] == "EBP"
                                             or operand["index"] == "EBP"):
                frame["ebp_is_general_register"] = True
    return frame


class _State(object):
    """Mutable extraction state. Never escapes `extract`."""

    def __init__(self, insns, frame, meta, image_base):
        self.insns = insns
        self.real = [item for item in insns if item["kind"] == "insn"]
        self.frame = frame
        self.meta = meta
        self.image_base = image_base
        self.esp_delta = 0
        self.esp_poison_reason = None
        self.local_extent = 0
        self.flow_complete = True
        self.ecx_first_write = None
        self.ecx_reads = 0
        self.ecx_addr_taken = False
        self.ecx_derefs = []
        self.edx_derefs = []
        self.ecx_alias = {}
        self.ecx_spills = {}
        self.ecx_rep = False
        self.edx_first_write = None
        self.vclass = {}
        self.vdef_index = {}
        self.reg_def = {}
        self.reg_reads = {}
        self.subreg_written = set()
        self.reg_read_counts = {}
        self.reg_read_obs = {}
        self.reg_writes = {}
        self.reg_restores = {}
        self.pushed = {}
        self.saved = []
        self.ret_obs = []
        self.transfer_out = []
        self.exits = []
        self.calls_direct = []
        self.calls_indirect = []
        self.jmps_indirect = []
        self.jmps_direct = []
        self.vtable_loads = []
        self.string_ops = []
        self.seh = False
        self.slot_reads = []
        self.slot_writes = []
        self.stores_through_reg = []
        self.slot0_loads = []
        self.observations = []
        self.frame_citations = []
        self.variadic_markers = []
        self.has_call = False
        self.has_xmm = False
        self.has_x87 = False
        self.listing_vas = set()
        self.instructions = 0
        self.call_indices = [item["index"] for item in insns
                             if item["kind"] == "insn" and item["base"] == "CALL"]

    def incoming(self, register, index):
        first = self.ecx_first_write if register == "ECX" else (
            self.edx_first_write if register == "EDX" else None)
        if register not in ("ECX", "EDX"):
            return True
        return first is None or index < first

    def mem_base_is_incoming(self, register, index):
        if register == "ECX":
            return self.incoming("ECX", index)
        if register == "EDX":
            return self.incoming("EDX", index)
        return True

    def define(self, register, index, kind):
        parent = _parent(register)
        if parent is None:
            return
        if parent == "ECX" and self.ecx_first_write is None:
            self.ecx_first_write = index
        if parent == "EDX" and self.edx_first_write is None:
            self.edx_first_write = index
        if parent not in self.reg_writes:
            self.reg_writes[parent] = {"index": index, "kind": kind}
        if parent not in self.vclass:
            self.vclass[parent] = "opaque"
            self.vdef_index[parent] = index
        self.reg_def.pop(parent, None)
        self.ecx_alias.pop(parent, None)


def _is_image_pointer(value, image_base):
    return image_base <= value < image_base + 0x02000000


def _classify_write(state, insn, position):
    """Bounded forward value-origin classification for one defined register."""
    base = insn["base"]
    destination = insn["operands"][position]
    register = _operand_reg(destination)
    if register is None:
        return None
    parent = _parent(register)
    if register in GPR8 or register in GPR16:
        parent = _parent(register)
    source = insn["operands"][position + 1] if len(insn["operands"]) > position + 1 else None
    if base in ("XOR", "SUB") and len(insn["operands"]) > 1:
        other = insn["operands"][1]
        if other["kind"] == "reg" and _operand_reg(other) == register:
            return "integral"
    if base == "AND" and len(insn["operands"]) > 1:
        other = insn["operands"][1]
        if other["kind"] == "reg" and _operand_reg(other) == register:
            return "integral"
    if base in ("MOV", "MOVBE") and source is not None:
        if source["kind"] == "imm":
            value = source["value"]
            if _is_image_pointer(value, state.image_base):
                return "pointer_like"
            if 0 <= value <= 0xFFFF:
                return "integral"
            return "large_or_mask"
        if source["kind"] == "mem":
            return "pointer_like"
        if source["kind"] == "reg":
            return state.vclass.get(_parent(_operand_reg(source)), "opaque")
    if base in ("MOVZX", "MOVSX", "MOVSXD", "CBW", "CWDE", "CDQE"):
        return "integral"
    if base == "LEA":
        return "pointer_like"
    if base in MUL_MNEM:
        return "integral"
    if base in ARITH_MNEM:
        left = state.vclass.get(parent, "opaque")
        right = "opaque"
        if source is not None and source["kind"] == "reg":
            right = state.vclass.get(_parent(_operand_reg(source)), "opaque")
        if "integral" in (left, right):
            return "integral"
        if left == right:
            return left
        return "opaque"
    if base in ("CMOVZ", "CMOVNZ", "CMOVBE", "CMOVA"):
        if source is not None and source["kind"] == "reg":
            return state.vclass.get(_parent(_operand_reg(source)), "opaque")
        return "opaque"
    if base == "POP":
        return "opaque"
    if base in ("XCHG",) and source is not None and source["kind"] == "reg":
        return state.vclass.get(_parent(_operand_reg(source)), "opaque")
    if base in X87_OPS:
        return "opaque"
    if base == "CALL":
        return "call_result"
    return "opaque"


def _spill_key(operand, frame, esp_delta):
    """Identify a resolved *local* slot; returns (base, disp) or None."""
    if operand["kind"] != "mem" or operand["index"] is not None:
        return None
    base = operand["base"]
    if base == "EBP" and frame["fp"]:
        if operand["disp"] < 0:
            return ("EBP", operand["disp"])
        return None
    if base == "ESP" and esp_delta is not None:
        if operand["disp"] - esp_delta < 0:
            return ("ESP", operand["disp"] - esp_delta)
    return None


def extract(insns, meta, image_base=0x00400000):
    """Stage 1: read facts off the listing. No convention, receiver or sret
    vocabulary exists here, so no claim can leak out of this pass."""
    frame = _frame_prepass(insns)
    state = _State(insns, frame, meta, image_base)
    state.listing_vas = {item["va"] for item in insns
                         if item["kind"] == "insn" and item["va"] is not None}
    observations = []
    emitted_frame = [False]

    def emit(insn, kind, **fields):
        record = {
            "id": "obs-%04d" % (len(observations) + 1),
            "kind": kind,
            "index": insn["index"],
            "at": _fmt_hex(insn["va"]) if insn.get("va") is not None else None,
            "raw": insn.get("raw", ""),
        }
        record.update(fields)
        observations.append(record)
        return record["id"]

    for insn in insns:
        kind = insn["kind"]
        if kind == "blank":
            continue
        if kind == "data":
            emit(insn, "DATA_BYTE", count=insn["byte_count"])
            continue
        if kind == "unparsed":
            emit(insn, "UNPARSED", reason=insn["reason"])
            continue
        state.instructions += 1
        base = insn["base"]
        operands = insn["operands"]
        index = insn["index"]

        if base in X87_OPS:
            state.has_x87 = True
        if any(operand["kind"] == "reg" and operand["reg"].startswith("XMM")
               for operand in operands):
            state.has_xmm = True

        is_lea = base == "LEA"
        first_operand_is_store = bool(operands) and base in STORE_MNEM

        def note_read(register):
            parent = _parent(register)
            if register != parent and register in state.subreg_written:
                return
            if parent in state.reg_reads:
                state.reg_read_counts[parent] = state.reg_read_counts.get(parent, 1) + 1
            else:
                state.reg_reads[parent] = index
                state.reg_read_counts[parent] = 1
                state.reg_read_obs[parent] = emit(
                    insn, "REG_READ", reg=parent, count=1, first_use=index,
                    first_write_index=None)
            if parent == "ECX":
                state.ecx_reads += 1

        for position, operand in enumerate(operands):
            if operand["kind"] == "reg":
                register = operand["reg"]
                parent = _parent(register)
                if base == "POP" and position == 0:
                    state.reg_restores.setdefault(parent, emit(
                        insn, "REG_RESTORE", reg=parent))
                    if parent in state.pushed and parent not in state.saved:
                        state.saved.append(parent)
                    state.pushed.pop(parent, None)
                    continue
                if base in ("CMP", "TEST"):
                    continue
                if _is_store(insn, position):
                    continue
                note_read(register)
                continue
            if operand["kind"] != "mem":
                continue
            base_register = operand["base"]
            index_register = operand["index"]
            if base_register is not None:
                note_read(base_register)
            if index_register is not None:
                note_read(index_register)
            if operand["segment"] in ("FS", "GS"):
                state.seh = True
                emit(insn, "SEGMENT_TLS", segment=operand["segment"],
                     text=operand["text"])
            if is_lea and base_register == "ECX":
                state.ecx_addr_taken = True

        if base == "PUSH" and operands and operands[0]["kind"] == "reg":
            pushed = _parent(_operand_reg(operands[0]))
            state.pushed.setdefault(pushed, index)

        # --- memory operand classification -------------------------------------
        for position, operand in enumerate(operands):
            if operand["kind"] != "mem":
                continue
            is_store = bool(first_operand_is_store and position == 0)
            local = _spill_key(operand, frame, state.esp_delta)
            key, resolved, note = _resolve_slot(state, operand)
            if key is not None and resolved:
                size = operand["size"]
                entry = {"obs": None, "key": key, "size": size, "index": index,
                         "inferred": operand["size_inferred"], "read": False,
                         "written": False, "base": operand["base"],
                         "disp": operand["disp"]}
                if is_store:
                    state.slot_writes.append(entry)
                else:
                    state.slot_reads.append(entry)
                entry["obs"] = emit(
                    insn, "STACK_SLOT_WRITE" if is_store else "STACK_SLOT_READ",
                    base=operand["base"], disp=operand["disp"], size=size,
                    key=key, resolved=True,
                    **({"via": "direct"} if is_store else {}))
                target = None
                if key == 4 and not is_store:
                    if position > 0 and operands[position - 1]["kind"] == "reg" \
                            and _is_store(insn, position - 1):
                        target = _parent(_operand_reg(operands[position - 1]))
                    elif position + 1 < len(operands) \
                            and operands[position + 1]["kind"] == "reg":
                        target = _parent(_operand_reg(operands[position + 1]))
                if target is not None:
                    state.slot0_loads.append({"obs": entry["obs"], "reg": target,
                                              "index": index, "key": key})
                if operand["disp"] < 0 and -operand["disp"] > state.local_extent:
                    state.local_extent = -operand["disp"]
            else:
                if operand["base"] in ("EBP", "ESP"):
                    emit(insn, "STACK_SLOT_WRITE" if is_store else "STACK_SLOT_READ",
                         base=operand["base"], disp=operand["disp"],
                         size=operand["size"], key=None, resolved=False,
                         reason=note,
                         **({"via": "direct"} if is_store else {}))
                if operand["disp"] < 0 and -operand["disp"] > state.local_extent:
                    state.local_extent = -operand["disp"]
            if is_store and operand["base"] is not None \
                    and operand["base"] not in ("EBP", "ESP"):
                state.stores_through_reg.append(
                    {"reg": operand["base"], "disp": operand["disp"], "index": index,
                     "obs": observations[-1]["id"]})
            if not is_lea:
                _record_ecx_access(state, index, operand, is_store, local)

        _record_string_op(state, emit, insn)
        _record_frame(emit, insn, operands, state, emitted_frame)
        _record_transfers(state, emit, insn, operands)
        _record_vtable(state, emit, insn, operands)
        _record_variadic_marker(state, emit, insn, operands)
        _note_va_list_zero_fill(state, emit, insn, operands)
        _update_esp(state, insn, operands)
        _update_registers(state, insn, operands, emit)
    return observations, state, frame


def _resolve_slot(state, operand):
    """Map a frame-relative operand onto the unified entry-ESP key (spec 2.2)."""
    frame = state.frame
    base = operand["base"]
    disp = operand["disp"]
    if base == "EBP":
        if not frame["fp"]:
            return None, False, "untrusted_frame"
        if disp < 0:
            return None, False, "local"
        if disp in (0, 4):
            return None, False, "frame"
        return disp - 4, True, "ebp"
    if base == "ESP":
        if state.esp_delta is None:
            return None, False, "esp_unresolved"
        key = disp - state.esp_delta
        if key < 4:
            return None, False, "local"
        return key, True, "esp"
    return None, False, "not_frame_relative"


def _record_ecx_access(state, index, operand, is_store, local):
    base = operand["base"]
    if base is None or operand["index"] is not None:
        return
    offset = operand["disp"]
    shape = None
    if base == "ECX":
        incoming = state.ecx_first_write is None or index < state.ecx_first_write
        state.ecx_derefs.append({"index": index, "offset": offset,
                                 "store": bool(is_store), "incoming": incoming,
                                 "shape": "R-DIRECT" if incoming else None})
    elif base in state.ecx_alias:
        shape = "R-ALIAS"
        state.ecx_derefs.append({"index": index,
                                 "offset": state.ecx_alias[base] + offset,
                                 "store": bool(is_store), "incoming": True,
                                 "shape": shape})
    if base == "EDX" and (state.edx_first_write is None
                          or index < state.edx_first_write):
        state.edx_derefs.append({"index": index, "offset": offset,
                                 "store": bool(is_store), "incoming": True})



def _record_string_op(state, emit, insn):
    base = insn["base"]
    suffix = insn.get("suffix") or insn.get("prefix") or ""
    if suffix not in ("REP", "REPE", "REPNE", "LOCK", "REPZ", "REPNZ"):
        return
    if not (base.startswith("MOVS") or base.startswith("STOS") or base.startswith("LODS")
            or base.startswith("SCAS") or base.startswith("CMPS")
            or base.startswith("XADD") or base.startswith("XCHG")
            or base.startswith("CMPXCHG") or base.startswith("ADD")
            or base.startswith("SUB") or base.startswith("CMP")
            or base.startswith("INC") or base.startswith("DEC")
            or base.startswith("NEG") or base.startswith("NOT")
            or base.startswith("BT") or base.startswith("BTS")
            or base.startswith("BTR") or base.startswith("BTC")):
        return
    clobbers = []
    for operand in insn["operands"]:
        names = []
        register = _operand_reg(operand)
        if register:
            names.append(register)
        if operand["kind"] == "mem":
            names.extend([operand.get("base"), operand.get("index")])
        for name in names:
            if name and _parent(name) not in clobbers:
                clobbers.append(_parent(name))
    rep = suffix in ("REP", "REPE", "REPNE", "REPZ", "REPNZ")
    is_string = base.startswith("MOVS") or base.startswith("STOS")
    if rep and "ECX" not in clobbers:
        clobbers.append("ECX")
    if rep and "ECX" in clobbers:
        state.ecx_rep = True
    observation = emit(insn, "STRING_OP", form=base + ("." + suffix if suffix else ""),
                       clobbers=sorted(clobbers), rep=bool(rep),
                       string_base=bool(is_string))
    entry = {"obs": observation, "rep": bool(rep), "string_base": bool(is_string),
             "index": insn["index"]}
    state.string_ops.append(entry)
    if rep and is_string:
        _note_va_list_shape(state, emit, insn)


def _record_frame(emit, insn, operands, state, emitted_frame):
    base = insn["base"]
    frame = state.frame
    is_frame_op = False
    if base == "PUSH" and operands and _operand_reg(operands[0]) == "EBP":
        is_frame_op = True
    if base == "MOV" and len(operands) == 2 and _operand_reg(operands[0]) == "EBP":
        is_frame_op = True
    if base in ("SUB", "AND") and operands and _operand_reg(operands[0]) == "ESP":
        is_frame_op = True
    if base == "LEA" and len(operands) == 2 and _operand_reg(operands[0]) == "ESP":
        is_frame_op = True
    if not is_frame_op or emitted_frame[0]:
        return
    emitted_frame[0] = True
    payload = dict(frame)
    state.frame_citations.append(emit(insn, "FRAME", **payload))


def _target_value(operands):
    for operand in operands:
        if operand["kind"] in ("target", "imm"):
            return operand["value"]
    return None


def _record_transfers(state, emit, insn, operands):
    base = insn["base"]
    index = insn["index"]
    va = insn.get("va")
    if base in ("RET", "RETN", "RETF", "RETFQ", "IRET", "IRETD"):
        immediate = None
        for operand in operands:
            if operand["kind"] in ("imm", "target"):
                immediate = operand["value"]
        form = "RET" if immediate is None else "RET 0x%x" % immediate
        observation = emit(insn, "RET", imm=immediate, form=form)
        state.ret_obs.append({"obs": observation, "imm": immediate, "index": index,
                              "form": form})
        state.exits.append({"form": "ret", "index": index})
        return
    if base in ("JMP", "JMPX"):
        indirect = _indirect_target(operands)
        if indirect is not None:
            via, register, disp = indirect
            observation = emit(insn, "JMP_INDIRECT", via=via, base=register, disp=disp)
            state.jmps_indirect.append({"obs": observation, "index": index,
                                        "via": via, "base": register, "disp": disp})
        else:
            target = _target_value(operands)
            if target is not None:
                in_listing = state.listing_vas and target in state.listing_vas
                observation = None
                if not in_listing:
                    observation = emit(insn, "UNCOND_TRANSFER_OUT", target=_fmt_hex(target))
                    state.transfer_out.append({"obs": observation, "target": target,
                                               "index": index})
                    state.exits.append({"form": "jmp_out", "index": index,
                                        "target": target, "obs": observation})
                # Every *direct* JMP to a static target is recorded, whether or
                # not it leaves the listing. `transfer_out` only keeps the ones
                # that leave, so a jump into the middle of the body -- which
                # `tail_call.target` then never sees -- is invisible there, and
                # `T1-FWD` has to be able to reject it by name rather than by
                # omission. A JMP through a register or a memory operand is not
                # recorded at all: its target is not a static address, so no
                # target record could be resolved for it.
                state.jmps_direct.append({"obs": observation, "target": target,
                                         "index": index, "va": va,
                                         "in_listing": bool(in_listing)})
        return
    if base == "CALL":
        state.has_call = True
        indirect = _indirect_target(operands)
        if indirect is not None:
            via, register, disp = indirect
            observation = emit(insn, "CALL_INDIRECT", via=via, base=register, disp=disp)
            state.calls_indirect.append({"obs": observation, "index": index,
                                         "via": via, "base": register, "disp": disp,
                                         "target": None})
        else:
            target = _target_value(operands)
            observation = emit(insn, "CALL_DIRECT", target=_fmt_hex(target)
                               if target is not None else None)
            state.calls_direct.append({"obs": observation, "target": target,
                                       "index": index})
        return
    if base in BRANCH_MNEM:
        target = _target_value(operands)
        if target is None:
            return
        if va is not None and target <= va:
            state.flow_complete = False
        if state.listing_vas and target not in state.listing_vas:
            state.flow_complete = False


def _indirect_target(operands):
    for position, operand in enumerate(operands):
        if operand["kind"] == "mem":
            return ("memory", operand["base"], operand["disp"])
    if len(operands) == 1 and operands[0]["kind"] == "reg":
        return ("register", _parent(_operand_reg(operands[0])), None)
    return None


def _record_vtable(state, emit, insn, operands):
    base = insn["base"]
    if base not in ("CALL", "JMP", "JMPX"):
        return
    indirect = _indirect_target(operands)
    if indirect is None:
        return
    via, register, disp = indirect
    if via == "register" and register is None:
        return
    if via == "memory" and register is None:
        return
    definition = state.reg_def.get(register)
    if not definition:
        return
    if definition["mnem"] not in ("MOV", "LEA"):
        return
    load_base = definition["base"]
    if load_base is None or load_base in ("ESP", "EBP"):
        return
    vtable_offset = definition["disp"]
    if via == "memory":
        call_offset = disp
    else:
        call_offset = vtable_offset
    observation = emit(insn, "VTABLE_SHAPED_LOAD", base=load_base,
                       vtable_offset=vtable_offset, reg=register,
                       call_offset=call_offset, via=via)
    state.vtable_loads.append({"obs": observation, "vtable_offset": vtable_offset,
                               "call_offset": call_offset, "index": insn["index"]})


def _note_va_list_shape(state, emit, insn):
    """V1 marker 1: a bulk fill followed by lea r,[frame]; push r, then a call."""
    window = [item for item in state.insns
              if insn["index"] < item["index"] <= insn["index"] + 8
              and item["kind"] == "insn"]
    for offset, item in enumerate(window):
        if item["base"] != "LEA":
            continue
        if not any(operand["kind"] == "mem" and operand.get("base") in ("EBP", "ESP")
                   for operand in item["operands"]):
            continue
        for follow in window[offset + 1:offset + 4]:
            if follow["base"] == "PUSH" and follow["operands"] \
                    and _operand_reg(follow["operands"][0]) is not None:
                if _next_call(state, follow["index"]) is not None:
                    state.variadic_markers.append(emit(
                        insn, "VARIADIC_MARKER", marker="va_list_setup_shape",
                        detail="bulk fill, then lea r,[frame]; push r, before a call"))
                return
            if follow["base"] == "CALL":
                return


def _record_variadic_marker(state, emit, insn, operands):
    base = insn["base"]
    index = insn["index"]
    if base == "SUB" and len(operands) == 2 and _operand_reg(operands[0]) == "ESP":
        value = operands[1].get("value")
        if isinstance(value, int) and value > 0x1000:
            following = _next_call(state, index)
            if following is not None:
                state.variadic_markers.append(emit(
                    insn, "VARIADIC_MARKER", marker="huge_frame_before_call",
                    detail="sub esp,0x%x precedes a call at index %d" % (value, following)))
    if base == "CMP" and len(operands) == 2 and _operand_reg(operands[0]) == "ESP":
        following = _next_call(state, index)
        if following is not None and following <= index + 2:
            state.variadic_markers.append(emit(
                insn, "VARIADIC_MARKER", marker="stack_probe_before_call",
                detail="cmp esp,reg precedes a call at index %d" % following))
    if base in ("MOV", "LEA") and len(operands) == 2 \
            and _operand_reg(operands[0]) is not None \
            and operands[1]["kind"] == "imm":
        # The count is the *source* immediate. Reading `operands[0]["value"]`
        # here would be dead code: a register destination carries no `value` key,
        # so the two conditions could never both hold and this marker -- one of
        # the three shapes spec 3.7 names -- could never fire.
        value = operands[1].get("value")
        following = _next_call(state, index)
        if isinstance(value, int) and 0 <= value <= 0x40 and following is not None \
                and following <= index + 2:
            state.variadic_markers.append(emit(
                insn, "VARIADIC_MARKER", marker="small_count_before_call",
                detail="mov r,0x%x immediately precedes a call at index %d"
                       % (value, following)))


def _is_zero_frame_local(insn, operands):
    """`mov dword ptr [EBP-m], 0` with m > 0: one half of a va_list zero-fill."""
    if insn["base"] != "MOV" or len(operands) != 2:
        return False
    destination = operands[0]
    source = operands[1]
    if destination["kind"] != "mem" or destination["base"] != "EBP":
        return False
    if destination["index"] is not None:
        return False
    if not isinstance(destination["disp"], int) or destination["disp"] >= 0:
        return False
    if destination["size"] != 4:
        return False
    return source["kind"] == "imm" and source.get("value") == 0


def _note_va_list_zero_fill(state, emit, insn, operands):
    """Second half of the MSVC va_list setup shape.

    Two distinct zero-initialised frame locals, then a call, is what the
    compiler emits while building the hidden va_list of a variadic frame. One
    zero-fill is ordinary initialisation; two of them, at distinct displacements,
    immediately before a call is a shape a non-variadic prologue has no reason
    to produce. Not in spec 3.7's list of three markers -- see the module
    docstring's deviations.
    """
    if not state.frame["fp"] or not _is_zero_frame_local(insn, operands):
        return
    first = operands[0]["disp"]
    window = [item for item in state.insns
              if insn["index"] < item["index"] <= insn["index"] + 8
              and item["kind"] == "insn"]
    for item in window:
        if not _is_zero_frame_local(item, item["operands"]):
            continue
        if item["operands"][0]["disp"] == first:
            continue
        call = _next_call(state, item["index"])
        if call is None or call > insn["index"] + 8:
            continue
        state.variadic_markers.append(emit(
            insn, "VARIADIC_MARKER", marker="varargs_or_alloca_prologue",
            detail="two zero-initialised frame locals (EBP+0x%x, EBP+0x%x) "
                   "precede a call at index %d"
                   % (first, item["operands"][0]["disp"], call)))
        return



def _next_call(state, index):
    calls = state.call_indices
    position = bisect.bisect_right(calls, index)
    return calls[position] if position < len(calls) else None


def _update_esp(state, insn, operands):
    base = insn["base"]
    delta = state.esp_delta
    if delta is None:
        return

    def poison(reason):
        state.esp_delta = None
        if state.esp_poison_reason is None:
            state.esp_poison_reason = reason

    if base in ("RET", "RETN", "RETF", "IRET", "IRETD", "CALL", "JMP", "JMPX"):
        return
    if base == "PUSH":
        state.esp_delta = delta + 4
        return
    if base == "POP":
        state.esp_delta = delta - 4
        return
    if base == "SUB" and len(operands) == 2 and _operand_reg(operands[0]) == "ESP":
        value = operands[1].get("value")
        if isinstance(value, int):
            state.esp_delta = delta + value
            return
        poison("sub esp with a non-constant immediate")
        return
    if base == "ADD" and len(operands) == 2 and _operand_reg(operands[0]) == "ESP":
        value = operands[1].get("value")
        if isinstance(value, int):
            state.esp_delta = delta - value
            return
        poison("add esp with a non-constant immediate")
        return
    if base == "AND" and len(operands) == 2 and _operand_reg(operands[0]) == "ESP":
        poison("and esp,%s" % operands[1].get("text", "?"))
        return
    if base == "LEA" and len(operands) == 2 and _operand_reg(operands[0]) == "ESP":
        if not state.frame["fp"]:
            poison("lea esp,[ebp-N] without a frame pointer")
            return
        source = operands[1]
        if source["kind"] == "mem" and source["base"] == "EBP" \
                and isinstance(source["disp"], int) and source["disp"] < 0:
            state.esp_delta = -(4 - source["disp"])
            return
        poison("lea esp,[%s]" % source.get("text", "?"))
        return
    if base == "MOV" and len(operands) == 2 and _operand_reg(operands[0]) == "ESP":
        if _operand_reg(operands[1]) == "EBP" and state.frame["fp"]:
            state.esp_delta = -4
            return
        poison("mov esp,%s" % operands[1].get("text", "?"))
        return
    if base in ("LEAVE", "LEAVEQ"):
        if state.frame["fp"]:
            state.esp_delta = -4
        else:
            poison("leave without a frame pointer")
        return
    for position, operand in enumerate(operands):
        if operand["kind"] != "reg" or _parent(operand["reg"]) != "ESP":
            continue
        if base in ("CMP", "TEST"):
            continue
        if _is_store(insn, position):
            poison("%s writes esp" % base)


def _update_registers(state, insn, operands, emit):
    base = insn["base"]
    index = insn["index"]
    pending_alias = None
    if base in ("ADD", "SUB") and len(operands) == 2 \
            and operands[0]["kind"] == "reg" and operands[1]["kind"] == "imm":
        register = _parent(_operand_reg(operands[0]))
        if register in state.ecx_alias:
            magnitude = operands[1]["value"]
            pending_alias = (register, state.ecx_alias[register]
                             + (magnitude if base == "ADD" else -magnitude))
    for position, operand in enumerate(operands):
        if operand["kind"] == "reg":
            register = operand["reg"]
            if base == "POP" and position == 0:
                state.vclass.setdefault(_parent(register), "opaque")
                continue
            if base in ("CMP", "TEST", "PUSH"):
                continue
            if not _is_store(insn, position):
                continue
            parent = _parent(register)
            if register != parent:
                state.subreg_written.add(register)
            value_class = _classify_write(state, insn, position)
            state.vclass[parent] = value_class
            state.vdef_index[parent] = index
            state.reg_def[parent] = _remember_def(insn, position)
            if parent not in state.reg_writes:
                emit(insn, "REG_WRITE", reg=parent,
                     write_kind=_write_kind(insn, value_class), definite=True)
            state.define(register, index, _write_kind(insn, value_class))
            if base in ("MOV", "LEA") and position == 0 and len(operands) > 1:
                _propagate_ecx_alias(state, insn, position)
            continue
    if pending_alias is not None:
        state.ecx_alias[pending_alias[0]] = pending_alias[1]
    if base in ("MOV", "MOVZX", "MOVSX") and len(operands) == 2:
        destination = operands[0]
        source = operands[1]
        if destination["kind"] == "mem" and source["kind"] == "reg" \
                and _parent(_operand_reg(source)) == "ECX":
            local = _spill_key(destination, state.frame, state.esp_delta)
            if local is not None and (state.ecx_first_write is None
                                      or index < state.ecx_first_write):
                state.ecx_spills[local] = (index, True)
    if base == "POP" and operands and operands[0]["kind"] == "reg":
        register = _parent(_operand_reg(operands[0]))
        if register in state.pushed and register not in state.saved:
            state.saved.append(register)


def _propagate_ecx_alias(state, insn, position):
    operands = insn["operands"]
    destination = operands[position]
    source = operands[position + 1] if len(operands) > position + 1 else None
    if source is None or destination["kind"] != "reg":
        return
    register = _parent(_operand_reg(destination))
    index = insn["index"]
    is_lea = insn["base"] == "LEA"
    if source["kind"] == "reg":
        other = _parent(_operand_reg(source))
        if other == "ECX" and register != "ECX" and state.incoming("ECX", index):
            state.ecx_alias[register] = 0
        return
    if source["kind"] != "mem":
        return
    base = source["base"]
    if base == register:
        return
    if base == "ECX" and state.incoming("ECX", index):
        state.ecx_alias[register] = source["disp"]
        return
    local = _spill_key(source, state.frame, state.esp_delta)
    if local is not None and local in state.ecx_spills:
        if state.ecx_spills[local][0] < index:
            state.ecx_alias[register] = 0


def _remember_def(insn, position):
    operands = insn["operands"]
    source = operands[position + 1] if len(operands) > position + 1 else None
    base = None
    disp = 0
    if source is not None and source["kind"] == "mem":
        base = source["base"]
        disp = source["disp"]
    return {"mnem": insn["base"], "base": base, "disp": disp, "index": insn["index"]}


def _write_kind(insn, value_class):
    base = insn["base"]
    operands = insn["operands"]
    if base in ("XOR", "SUB") and len(operands) > 1:
        other = operands[1]
        if other["kind"] == "reg" and _operand_reg(other) == _operand_reg(operands[0]):
            return "zero"
    if base in ("MOV", "MOVZX", "MOVSX", "MOVSXD", "LEA") and len(operands) > 1:
        source = operands[1]
        if source["kind"] == "imm":
            return "imm"
        if source["kind"] == "mem":
            return "mem_load"
        if source["kind"] == "reg":
            return "reg"
    if base == "LEA":
        return "lea"
    if base in ("MOVZX",):
        return "zero_extend"
    if base in ("MOVSX", "MOVSXD", "CBW", "CWDE", "CDQE"):
        return "sign_extend"
    if base in ARITH_MNEM or base in MUL_MNEM:
        return "arith"
    if base == "CALL":
        return "call_result"
    if base in ("POP",):
        return "unknown"
    if value_class == "opaque":
        return "unknown"
    return "reg"


def _terminal_citations(observations):
    return [observations[-1]["id"]] if observations else []


def _slot_table(state, frame):
    grouped = {}
    for entry in sorted(state.slot_reads + state.slot_writes,
                        key=lambda item: (item["key"], item["index"])):
        record = grouped.setdefault(entry["key"], {
            "key": entry["key"], "sizes": [], "read": False, "written": False,
            "inferred": False, "ebp_offset": None, "obs": [],
        })
        if entry["size"] not in record["sizes"]:
            record["sizes"].append(entry["size"])
        if entry["inferred"]:
            record["inferred"] = True
        if entry["read"]:
            record["read"] = True
        if entry["written"]:
            record["written"] = True
        if record["ebp_offset"] is None and entry["base"] == "EBP":
            record["ebp_offset"] = entry["disp"]
        record["obs"].append(entry["obs"])
    keys = sorted(grouped)
    max_key = keys[-1] if keys else 0
    gaps = (((max_key - 4) // 4) + 1 - len(keys)) if max_key >= 4 else 0
    slots = []
    for key in keys:
        record = grouped[key]
        slot = {
            "ordinal": (key - 4) // 4 + 1,
            "entry_offset": "entry_ESP+0x%x" % key,
            "sizes": sorted(record["sizes"]),
            "read": record["read"],
            "written": record["written"],
            "observed": True,
            "size_inferred": record["inferred"],
        }
        if record["ebp_offset"] is not None:
            slot["ebp_offset"] = "EBP+0x%x" % record["ebp_offset"]
        if len(slot["sizes"]) > 1:
            slot["confidence"] = "UNKNOWN"
        slots.append(slot)
    return grouped, keys, max_key, gaps, slots


def _as_address(value):
    """An int or a ``0x``-prefixed hex string as an int, else ``None``."""
    if isinstance(value, bool) or value is None:
        return None
    if isinstance(value, int):
        return value if 0 <= value <= 0xFFFFFFFF else None
    text = str(value).strip().lower()
    if text.startswith("0x"):
        text = text[2:]
    if not text or len(text) > 8:
        return None
    try:
        number = int(text, 16)
    except ValueError:
        return None
    return number if 0 <= number <= 0xFFFFFFFF else None


def _as_index(value):
    """A non-negative int, else ``None``. ``bool`` is not an index."""
    if isinstance(value, bool) or not isinstance(value, int) or value < 0:
        return None
    return value


def vftable_memberships(value):
    """The `vftable_slots` input, normalised to a sorted tuple of memberships.

    An entry is a ``{"table": <va>, "slot_index": <int>, "basis": ...}`` mapping
    (a two-element ``(table, slot_index)`` sequence is accepted too) and it is
    **kept only when its basis is :data:`VFTABLE_BASIS`** -- the sound predicate
    of ``tools/reconstruction_tooling/vftables.py``. A membership asserted from
    the triage heuristics (``vtables.json``, the index) is dropped here, which is
    the whole point of demanding the basis: those sources measure under 45%
    precision and ``0x01053e00`` is a live counterexample, so an entry that
    cannot state how it was established is an absence of evidence, never a
    membership.

    Nothing raises. A caller's malformed entry removes evidence; it never adds
    a claim and never turns an abstention into a positive one.
    """
    if value is None:
        return ()
    entries = [value] if isinstance(value, dict) else value
    if not isinstance(entries, (list, tuple)):
        return ()
    out = []
    for entry in entries:
        table = slot = None
        if isinstance(entry, dict):
            if entry.get("basis") != VFTABLE_BASIS:
                continue
            table = _as_address(entry.get("table"))
            slot = _as_index(entry.get("slot_index"))
        elif isinstance(entry, (list, tuple)) and len(entry) == 2:
            table = _as_address(entry[0])
            slot = _as_index(entry[1])
        if table is None or slot is None:
            continue
        out.append((table, slot))
    return tuple(sorted(set(out)))


def tail_target(value, hop_va):
    """The `tail_target_record` input, validated against the hop it claims to be.

    Returns ``None`` unless every one of these holds, because each of them is a
    precondition of ``T1-FWD`` and the caller cannot be asked twice:

    * it is a mapping whose ``va`` -- when it states one -- is the address this
      thunk actually jumps to, so a record resolved for a different target is
      never applied to this one;
    * ``entry`` is true: the target is a **function entry**, read off the
      target's own listing (whose first instruction must be the target address).
      This is what separates a thunk from a jump into the middle of a body, and
      it is the check ``0x007e6100`` fails;
    * ``in_text`` is true and ``import_pointer`` is not true: the target is a
      code address of this image, not a pointer read out of an import table;
    * ``record`` is a derived record for that target.

    A target whose record names no convention is still returned: the *cleanup*
    a tail hop inherits is settled by the target even when the target's own
    convention is not, and ``0x00980480`` is exactly that case. What may be
    forwarded is decided by the caller, not here.
    """
    if not isinstance(value, dict):
        return None
    stated = value.get("va")
    if stated is not None and _as_address(stated) != hop_va:
        return None
    if value.get("entry") is not True:
        return None
    if value.get("in_text") is not True:
        return None
    if value.get("import_pointer") is True:
        return None
    record = value.get("record")
    if not isinstance(record, dict) or not record:
        return None
    conventions = record.get("conventions")
    if not isinstance(conventions, dict):
        return None
    span = value.get("listing_span")
    return {"va": hop_va, "record": record,
            "source": value.get("source") if isinstance(value.get("source"), str) else None,
            "listing_span": span if isinstance(span, (list, tuple)) and len(span) == 2 else None}


def _adjustor_delta(state, before):
    """The signed `this` adjustment a thunk applies before it jumps, or ``None``.

    MSVC emits a `this`-adjustor thunk as ``SUB ECX, imm`` (or ``ADD``) followed
    by the jump; the value is what the *incoming* receiver is offset by, so it is
    reported as the signed delta to add to `this` and the instruction that
    produced it. Only an immediate on ECX counts. A ``LEA ECX, [ECX+d]`` form is
    not recognised, and a thunk using it therefore reports **no** delta -- an
    absence, which is the safe direction, and stated here so the limitation is
    not mistaken for a measurement.
    """
    for item in state.insns:
        if item["kind"] != "insn" or item["index"] >= before:
            break
        if item["base"] not in ("SUB", "ADD"):
            continue
        operands = item["operands"]
        if len(operands) != 2 or _operand_reg(operands[0]) != "ECX":
            continue
        value = operands[1].get("value")
        if not isinstance(value, int) or isinstance(value, bool):
            continue
        return (-value if item["base"] == "SUB" else value)
    return None


def _shared_target_hops(state):
    """The direct ``JMP`` sites that all name one static target, or ``None``.

    ``S1`` used to require exactly one direct ``JMP`` *site*. That is a proxy
    for the property the rule actually rests on, which is that every path leaving
    this body leaves it at the same address. Two sites naming the same address
    have that property; ``0x00841440`` is the real shape of it -- a ``JZ`` whose
    two arms each store to ``[ESP + 0x8]`` and each then jump to ``0x0083c780``.
    What S1 means is the target set, not the site count, and nothing in the
    forwarded claim is read off how many sites there were.

    Returns the hops naming the shared target, or ``None``:

    * a ``RET`` anywhere in the listing -- unchanged, and the same half as before;
    * no direct jump at all, so there is no static target to resolve;
    * **more than one distinct target**: a body with two genuine exits may reach
      two conventions, so the abstention is exactly what it was, and this is the
      case ``0x007e6100`` and the ``JMP a; JMP b`` pair keep pinning;
    * on the multi-site half only, an indirect jump anywhere in the body (a path
      may leave at an address no target record covers) or a last instruction that
      is not one of the hops (a path may run off the end of the listing). Both
      guard a path that leaves *without* reaching the shared target, and both are
      confined to the multi-site half so the single-site answer is byte for byte
      what it always was.
    """
    if state.ret_obs or not state.jmps_direct:
        return None
    targets = {hop["target"] for hop in state.jmps_direct}
    if len(targets) != 1:
        return None
    hops = [hop for hop in state.jmps_direct if hop["target"] in targets]
    if len(hops) > 1:
        if state.jmps_indirect:
            return None
        real = [item for item in state.insns if item["kind"] == "insn"]
        if not real or real[-1]["index"] != max(hop["index"] for hop in hops):
            return None
    return hops


def _tail_forward(state, frame, tail, stack_arguments, target_value, hop_va,
                  infer_rule, terminal):
    """``T1-FWD`` -- forward a thunk's ABI to a resolved tail target.

    Returns ``None`` when any precondition fails, or a dict describing what may
    be forwarded. Preconditions, all required:

    * **S1** every exit this body owns leaves it at *one* address, and no ``RET``
      anywhere in the listing. An exit is a ``RET`` or a *direct* ``JMP`` to a
      static target, whether or not it leaves the listing; a conditional branch
      is not an exit, because control comes back. One address, not one site: see
      :func:`_shared_target_hops`, which is where the two-exit-same-target case
      and its two extra guards are decided. Note what the counting leaves: a
      conditional branch *out of* the listing is not an exit, so a body whose
      real shape is a conditional tail jump can still forward. The record says so
      (``parse.flow_complete`` is false and ``completeness`` is PARTIAL), which
      is where that gap is reported rather than hidden -- and it is the
      specification's own reading, since ``0x007e6100`` has three conditional
      branches and the specification attributes its rejection to S3, S4 and S6.
    * **S2** that exit is a direct ``JMP`` to a static target. A jump through a
      register or through memory is not in ``state.jmps_direct`` at all, so a
      body whose only exit is ``JMP [0x013cc118]`` fails here.
    * **S3** the target is not inside this body (no in-listing jump) **and** is
      a function entry (see :func:`tail_target`).
    * **S4** ``esp_delta == 0`` and no frame setup: the thunk must not have
      adjusted the stack, or the target's argument area is not the caller's.
    * **S5** the target's own record states a concrete convention. S5 gates the
      *convention*; the *cleanup* is forwarded on the weaker condition that the
      target's cleanup is concrete, which is what lets ``0x00980480`` gain
      ``{callee, 4, OBSERVED}`` from a target whose convention still abstains.
    * **S6** the argument areas are compatible: when the thunk itself resolved a
      stack slot, that area must equal the target's. A thunk that read no stack
      word establishes no area, so nothing is contradicted -- ``0x0096ff70``
      (``SUB ECX,0xc; JMP``) forwards to a target that pops 4, while
      ``0x007e6100`` (4 bytes of its own, 20 at the target) does not.
    * **S7** the target is a code address of this image and not an import
      pointer (see :func:`tail_target`).

    Confidence is the target's own, capped: a forward is an inference about a
    function whose own body never observed a convention, so it starts at
    ``INFERRED`` and is then capped by whatever the target's record claims. The
    forwarded cleanup is the target's own claim, unchanged.
    """
    hops = _shared_target_hops(state)
    if hops is None:
        return None                                   # S1 (RET) / S1,S2 (exits)
    hop = hops[0]
    if hop["in_listing"]:
        return None                                   # S3, in-listing half
    if state.esp_delta != 0 or tail["after_frame_setup"]:
        return None                                   # S4
    if not isinstance(target_value, dict):
        return None                                   # S3/S5/S7
    target_record = target_value["record"]
    conventions = target_record["conventions"]
    target_conventions = conventions["calling_convention"]
    confidence = _weaker("INFERRED", conventions.get("confidence"))
    target_stack = target_record.get("stack_arguments") or {}
    target_bytes = target_stack.get("total_bytes")
    thunk_bytes = stack_arguments.get("total_bytes")
    if stack_arguments.get("observed_slots") and thunk_bytes != target_bytes:
        return None                                   # S6
    if thunk_bytes is None or not isinstance(target_bytes, int):
        return None                                   # S6, unusable areas
    target_cleanup = target_record.get("cleanup") or {}
    forwarded_cleanup = None
    if target_cleanup.get("side") in ("callee", "caller") \
            and target_cleanup.get("confidence") not in (None, "UNKNOWN") \
            and isinstance(target_cleanup.get("bytes"), int):
        forwarded_cleanup = {
            "side": target_cleanup["side"], "bytes": target_cleanup["bytes"],
            "confidence": _weaker(target_cleanup["confidence"], "OBSERVED"),
            "corroboration": "forwarded_from_tail_target",
            "evidence": "forwarded from the tail target %s: %s" % (
                _fmt_hex(hop_va), target_cleanup.get("evidence")),
        }
    if target_conventions not in CONVENTIONS and forwarded_cleanup is None:
        return None                                   # S5, nothing to forward
    citations = [item["obs"] for item in hops if item.get("obs")] or list(terminal)
    # One address is what S1 requires; how many sites reached it is stated in the
    # claim and counted in the citations, so a reader never sees one arm read and
    # the other assumed. The phrasing is the pre-existing single-site text
    # whenever there is one site, so every single-site record is unchanged.
    sites = ("this listing is a single ESP-neutral direct jump" if len(hops) == 1 else
             "all %d of this listing's direct jumps resolve to that one ESP-neutral "
             "target" % len(hops))
    value = {
        "target": _fmt_hex(hop_va),
        "target_calling_convention": target_conventions,
        "target_cleanup_side": target_cleanup.get("side"),
        "target_stack_bytes": target_bytes,
    }
    if target_value.get("source"):
        value["target_source"] = target_value["source"]
    source = target_value.get("source")
    if target_conventions in CONVENTIONS:
        infer_rule("T1-FWD",
                   "calling convention is %s, forwarded from the tail target %s: "
                   "%s, inherits its caller's frame and never runs its own RET, so "
                   "the two calls are one call%s" % (
                       target_conventions, _fmt_hex(hop_va), sites,
                       " (resolved from %s)" % source if source else ""),
                   confidence, citations, target_conventions)
        value["confidence"] = confidence
    else:
        infer_rule("T1-FWD",
                   "the stack cleanup is %s with %d byte(s), forwarded from the "
                   "tail target %s; the target's own calling convention is not "
                   "decided, so none is forwarded%s" % (
                       forwarded_cleanup["side"], forwarded_cleanup["bytes"],
                       _fmt_hex(hop_va),
                       " (resolved from %s)" % source if source else ""),
                   forwarded_cleanup["confidence"], citations, value)
    delta = _adjustor_delta(state, hop["index"])
    if delta is not None:
        value["this_adjustor_delta"] = delta
    return {"convention": target_conventions if target_conventions in CONVENTIONS else None,
            "confidence": confidence, "cleanup": forwarded_cleanup,
            "adjustor_delta": delta, "value": value}


def _incoming_ecx_reads(state):
    """The observations that read ECX *before* the body first writes it.

    The distinction this makes is the whole of ``R1-VFT``, and the engine's
    ``ecx_read_without_deref`` reason does not make it: that reason is raised
    whenever ECX is read anywhere at all, including a read of a value the body
    itself loaded a moment earlier. ``0x00e51010`` is the real shape --
    ``MOV ECX,dword ptr [ESP + 0x4]`` then ``MOV ECX,dword ptr [0x016b3c0c]`` --
    where ECX is an ordinary argument, the incoming ECX is never looked at, and
    the receiver is the first callee-popped stack word. A rule keyed on the
    reason alone would call that a register receiver.

    So the gate is stated on the def/use relation instead, which is what
    "incoming" means everywhere else in this module (``state.ecx_first_write``,
    :func:`_record_ecx_access`): an ECX read at an index strictly below the
    first write, or any ECX read at all when the body never writes it.
    """
    first = state.ecx_first_write
    out = []
    for item in state.observations:
        if item.get("kind") != "REG_READ" or item.get("reg") != "ECX":
            continue
        if first is None or item.get("index", 0) < first:
            out.append(item)
    return out


#: Mnemonics that write ECX **implicitly**, with no ECX operand. A single
#: ``STOS``/``LODS`` adjusts ECX, so the incoming value is not preserved; the
#: ``REP`` forms clobber it outright and are refused separately through
#: ``state.ecx_rep``. ``CALL`` is here for the same reason and is the sharpest
#: of the three: x86-32 makes ECX volatile, so *any* call leaves ECX undefined,
#: and a read after one is a read of the callee's leftover, not of a parameter.
IMPLICIT_ECX_DEFS = frozenset((
    "STOSB", "STOSW", "STOSD", "STOSQ",
    "LODSB", "LODSW", "LODSD", "LODSQ",
    "CALL",
))

#: Mnemonics that define **both** operands rather than only the first, so a
#: destination-only reading of them misses the second definition.
TWO_OPERAND_DEFS = frozenset(("XCHG", "CMPXCHG", "CMPXCHG8B", "CMPXCHG16B"))


def _ecx_def_indices(state):
    """Every index at which the body **defines** ECX, from the parsed listing.

    This is deliberately self-contained rather than read off
    ``state.ecx_first_write``, and the reason is that three classes of definition
    never reach that field:

    * ``LEA ECX,[ECX+0x8]`` -- ``STORE_MNEM`` has no ``LEA``, so a ``this``
      adjustor written as a ``LEA`` is recorded as no definition at all, and the
      adjustor is then indistinguishable from a member address computed from the
      incoming receiver;
    * ``XCHG r,ECX`` -- ``_is_store`` is only true for operand 0, so the second
      operand of an exchange defines nothing;
    * ``CALL`` -- ECX is volatile in x86-32, so a read after a call reads the
      callee's leftover, and no register operand exists to record.

    Each of those three is a *false positive* for a rule keyed on "the incoming
    ECX", and ``R2-VFT`` is keyed on exactly that. So the rule states its own
    def/use relation, from the listing, in full. Nothing else in the engine
    changes: :func:`_incoming_ecx_reads` still reads ``state.ecx_first_write``,
    and every existing record is byte-identical.

    Conservative by construction: a definition the listing does not spell out is
    assumed away rather than assumed absent, and a body this rule refuses where
    a reader might have accepted it is a lost promotion, never a wrong claim.
    """
    out = set()
    for item in state.insns:
        if item["kind"] != "insn":
            continue
        base = item["base"]
        if base in IMPLICIT_ECX_DEFS:
            out.add(item["index"])
            continue
        operands = item["operands"]
        for position, operand in enumerate(operands):
            if operand["kind"] != "reg" or _parent(operand["reg"]) != "ECX":
                continue
            if position == 0 and (base == "POP" or _is_store(item, 0)
                                  or base == "LEA"):
                out.add(item["index"])
            elif position > 0 and base in TWO_OPERAND_DEFS:
                out.add(item["index"])
    return out


def _ecx_rooted_accesses(state):
    """Every memory operand based on ECX, in listing order, ``LEA`` excluded.

    ``_record_ecx_access`` skips an operand that carries an index register, so
    ``MOV EAX,[ECX + ECX*4 + 0x8]`` is invisible to it. That is a *sound*
    omission for ``R1`` -- the incoming-dereference fact it supports does not
    need the indexed form, and claiming an offset for it would be a guess -- but
    it is not a sound basis for a rule that asserts "this body performs no memory
    access through ECX at all". So the assertion ``R2-VFT`` makes is stated over
    this list, which is complete.

    ``LEA`` is excluded because it computes an address rather than performing an
    access; that is exactly the difference between the two rules.
    """
    out = []
    for item in state.insns:
        if item["kind"] != "insn" or item["base"] == "LEA":
            continue
        for operand in item["operands"]:
            if operand["kind"] == "mem" and operand["base"] == "ECX":
                out.append({"index": item["index"],
                            "at": _fmt_hex(item["va"]) if item.get("va") is not None
                            else None,
                            "index_reg": operand["index"],
                            "disp": operand["disp"]})
    return out


def _incoming_member_leas(state, defs):
    """The `LEA r32, [ECX + k]` sites that read the **incoming** ECX.

    This is ``R2-VFT``'s positive dataflow condition. ``defs`` is
    :func:`_ecx_def_indices`; a site is incoming when no definition precedes it.

    Four conditions, all necessary:

    * the base register is **ECX** and the **index register is absent**. A
      scaled or indexed form is a table computation, not a member address;
      ``[ECX + ECX*2 + 0x4]`` is the compiler's own idiom for one.
    * the **destination is not ECX**. ``LEA ECX,[ECX + 0x8]`` is a ``this``
      adjustor -- it *defines* the register -- and an adjustor is not a member
      address read off the receiver. Such a site is in ``defs``, so the incoming
      test already rejects it; the test is here as well because it is the
      property, and a reader should not have to know that.
    * the displacement is a **member displacement**: ``0 <= k``,
      ``k % 4 == 0`` and ``k <= :data:`MAX_MEMBER_DISPLACEMENT```. A negative
      displacement is a pre-adjustment (``this + k`` is a member address; the
      base of a multiple-inheritance object is a *pre-adjusted* pointer and the
      adjustment is its own statement), a non-multiple-of-four one cannot be the
      offset of any scalar in a 32-bit object, and the cap bounds the claim to an
      object-sized address rather than a mask. This is a **narrowing, not the
      load-bearing step** -- the argument that decides the receiver is in
      :func:`_vftable_address_receiver` -- and it is stated as one so a reader
      can tell which guard is which.
    * the site is **incoming**: no ECX definition at or before it. A body in the
      COM / ``__stdcall`` interface form loads its receiver off the stack, and
      ``MOV ECX,[ESP+0x4]; LEA EAX,[ECX+4]`` is an *integer* argument being
      offset, not a receiver. A call before the site is a definition too: ECX is
      volatile, so what follows a call is the callee's leftover.

    Returns a list of ``{"index", "at", "dest", "disp"}`` in listing order, or
    the empty list. Nothing here raises: a malformed operand is an absence.
    """
    out = []
    for item in state.insns:
        if item["kind"] != "insn" or item["base"] != "LEA":
            continue
        operands = item["operands"]
        if len(operands) < 2 or operands[0]["kind"] != "reg" \
                or operands[1]["kind"] != "mem":
            continue
        mem = operands[1]
        if mem["base"] != "ECX" or mem["index"] is not None:
            continue
        # `[ECX + ECX + 0x4]` is a sum, and the parser reports it exactly as it
        # reports `[ECX + 0x4]`: base ECX, no index register, displacement 4. The
        # only place the two differ is the operand's own text, so the count is
        # taken there. Without it the rule would read an integer doubling as a
        # member address, which is the one form of the scaled idiom the operand
        # dict cannot see.
        if _operand_names_register(mem, "ECX") != 1:
            continue
        destination = _parent(_operand_reg(operands[0]))
        if destination == "ECX":
            continue
        disp = mem["disp"]
        if not isinstance(disp, int) or isinstance(disp, bool):
            continue
        if disp < 0 or disp % 4 or disp > MAX_MEMBER_DISPLACEMENT:
            continue
        if any(def_index <= item["index"] for def_index in defs):
            continue
        out.append({"index": item["index"],
                    "at": _fmt_hex(item["va"]) if item.get("va") is not None else None,
                    "dest": destination, "disp": disp})
    return out


def _incoming_ecx_null_test(state, defs):
    """Whether the body null-tests the **incoming** ECX and branches on it.

    **Corroboration only.** ``R2-VFT`` does not require it and does not refuse
    without it: a compiler may omit a null guard where the caller guarantees a
    non-null ``this`` (``__assume``), so "the body null-tests ``this``" is not a
    property the ABI guarantees, and a rule that required it would be fitted to
    the fixtures rather than to the machine. It is reported because it is
    decisive evidence *when present*: ``TEST ECX,ECX`` followed by a conditional
    branch guards against exactly the failure a null receiver produces, and no
    integer-argument reading of the same body explains one.

    Returns ``True``/``False``. Only a ``TEST``/``CMP`` of ECX against itself at
    an incoming index, immediately followed by a conditional jump, counts: a
    comparison whose result is discarded, or one that compares ECX against a
    value, is not a null test.
    """
    real = [item for item in state.insns if item["kind"] == "insn"]
    for position, item in enumerate(real):
        if item["base"] not in ("TEST", "CMP"):
            continue
        if any(def_index <= item["index"] for def_index in defs):
            continue
        registers = [_operand_reg(op) for op in item["operands"]]
        if [name for name in registers if name] != ["ECX", "ECX"]:
            continue
        follower = real[position + 1] if position + 1 < len(real) else None
        if follower is None or not follower["base"].startswith("J") \
                or follower["base"] in ("JMP", "JMPQ"):
            continue
        return True
    return False


def _incoming_ecx_reads_before(state, defs):
    """The ``REG_READ`` observations of ECX that precede every ECX definition."""
    out = []
    for item in state.observations:
        if item.get("kind") != "REG_READ" or item.get("reg") != "ECX":
            continue
        index = item.get("index")
        if not isinstance(index, int) or isinstance(index, bool):
            continue
        if any(def_index <= index for def_index in defs):
            continue
        out.append(item)
    return out


def _vftable_dispatch_receiver(state, memberships, receiver_evidence, cleanup):
    """``R1-VFT``'s guard, or ``None``. Returns ``(table, slot, citations)``.

    Why the callee-cleanup vftable shape is not what ``V1-VFT`` refused
    ---------------------------------------------------------------------
    ``V1-VFT`` fires on a sound vftable slot that the **caller** cleans and
    reads no entry-relative stack word, and it rests the register receiver on
    that: a callee popping nothing has no argument in the popped area, so the
    receiver is in a register, and of ``__thiscall``/``__fastcall`` only ECX
    carries one. The **callee**-popping shape was left out because a
    callee-popped first word *can* be the receiver -- the COM / ``__stdcall``
    interface member -- and membership alone would have called all of them
    ``__thiscall``. ``0x01053e00`` is that shape: ``MOV ESI,dword ptr
    [ESP + 0x20]`` is ``entry_ESP+0x4``, the first popped word, and the body
    dereferences it.

    So membership is not enough, and neither is "the body reads ECX" on its own:
    ECX is also where a ``__fastcall`` first argument arrives, and
    ``0x00e51010`` shows the shape that must stay out (``MOV ECX,dword ptr
    [ESP + 0x4]`` -- ECX loaded *from* the first popped word and forwarded as an
    ordinary argument, incoming ECX never read).

    What settles it is the pair, and each half is a positive machine fact:

    * the address is a slot of a table the image proves is vptr-backed
      (``vftables.py`` predicate P: a vptr is stored at a small non-negative
      offset from a non-frame register, so the vptr sits at the head of the
      object and any dispatch to this slot computed its target as
      ``[object + 4 * slot]``). Every caller therefore hands this function the
      object address in the register it used as that base -- ECX, the one
      register the x86-32 member-call forms reserve for it;
    * the body reads that incoming ECX **before writing it**
      (:func:`_incoming_ecx_reads`). A body in the COM form obtains its
      receiver from the stack word and has no register parameter at all, so it
      never reads ECX -- which is exactly why ``0x01053e00`` and all six
      ``__stdcall`` callee-pop slots in the corpus are ``present: False``.

    The middle step -- that a body which reads the delivered register uses it as
    the object -- is a compiler-model step, the same kind ``C8-E``/``C8`` already
    make for EDX, and it is capped at ``INFERRED`` for the same reason: assembly
    and intrinsic wrappers exist and external corroboration is the only thing
    that can raise it.

    Every precondition, and what each one refuses:

    * a **sound** membership (``vftable_memberships`` has already dropped every
      entry that cannot state :data:`VFTABLE_BASIS`). No membership, no claim:
      the record is byte-identical to the unarmed one, which is the assertion
      ``VftableRuleTest`` makes for every refused target;
    * ``reason == "ecx_read_without_deref"`` -- the exact known-unknown this
      rule resolves. The three sibling reasons (``ecx_reassigned_before_deref``,
      ``ecx_address_taken_without_memory_access``, ``ecx_used_as_counter``) are
      different unknowns and stay unknown;
    * at least one **incoming** ECX read (:func:`_incoming_ecx_reads`), which is
      what excludes ``0x00e51010``, ``0x00e5c0f0`` and ``0x00e7d660``;
    * ``cleanup["side"] == "callee"``. The caller-cleanup shape is ``V1-VFT``'s,
      and one receiver fact gets one rule.

    It claims the **receiver** and nothing else. No convention (that is the
    ordinary ``C6B`` arm reading this function's own ``ret imm``), no class, no
    layout, no ``offsets``: the body never dereferenced the receiver, so the
    record states where the receiver is and not what it points into.
    """
    if receiver_evidence.get("present") is not None:
        return None
    if receiver_evidence.get("reason") != "ecx_read_without_deref":
        return None
    if not memberships:
        return None
    if cleanup.get("side") != "callee":
        return None
    reads = _incoming_ecx_reads(state)
    if not reads:
        return None
    return memberships[0][0], memberships[0][1], [item["id"] for item in reads]


def _vftable_address_receiver(state, memberships, receiver_evidence, cleanup):
    """``R2-VFT``'s guard, or ``None``. Returns the cited machine facts.

    The same fact ``R1-VFT`` claims, from a different class of read
    --------------------------------------------------------------------
    ``R1-VFT`` fires when the body reads its incoming ECX. It does not care
    what the body does with the value, and that is its strength: it cannot
    distinguish ``MOV ESI,ECX`` from ``MOV EAX,[ECX+4]``. It has a matching
    weakness. A body that never *touches memory* through the receiver at all --
    that copies nothing, dereferences nothing, and only ever computes the
    **address** of something inside it -- satisfies ``R1-VFT``'s
    ``ecx_read_without_deref`` guard only by accident of instruction choice, and
    in fact it does not: the engine's own ``receiver.reason`` for such a body is
    ``ecx_address_taken_without_memory_access``, which ``R1-VFT`` refuses as a
    different unknown. ``0x009817c0`` is the real shape: ``TEST ECX,ECX``,
    ``LEA EAX,[ECX + 0xc]``, ``RET 0x4``, twice, with two LEAs and no
    dereference anywhere.

    So the two rules are separated by an instruction, not by a distinction
    between two kinds of receiver, and that is the point of the evidence.

    The proof obligation, and why the guard is enough
    -------------------------------------------------
    The load-bearing step is a fact about the x86-32 MSVC calling convention, not
    a compiler heuristic. Enumerate the register parameters: ``__thiscall``
    passes ``this`` in ECX; ``__fastcall`` passes its first argument in ECX;
    ``__cdecl``, ``__stdcall`` and ``__clrcall`` pass none. Now intersect with
    cleanup. **An ``__fastcall`` callee never pops, and neither does a
    ``__cdecl`` or ``__clrcall`` callee.** So for a body whose terminal ``ret
    imm`` pops its own arguments, the only convention under which ECX is
    *defined on entry* is the one callee-popping convention that has a register
    parameter at all -- a ``__thiscall`` that pops -- and in it ECX is ``this``.
    A body that reads an undefined register is not a body a compiler emits.

    The COM / ``__stdcall`` interface member, the shape that would otherwise
    take its receiver off the stack, has no register parameter and therefore
    never reads its incoming ECX. ``0x01053e00`` is the real shape of that and is
    still refused, and the falsifier battery re-asserts it in miniature and in
    full, with a membership forced on.

    The residual risk is hand-written assembly and intrinsic wrappers, which is
    why this is capped at ``INFERRED`` for the same reason ``R1-VFT`` and ``C8``
    are: only external corroboration raises it.

    The independent witness, inside this binary
    ------------------------------------------
    ``0x00950eb0`` -- the function three of the corpus targets **tail-call
    into** -- is a member of 17 sound tables, pops 4, and its body is
    ``MOV EAX,ECX; MOV ECX,[ESP+0x4]; ...; TEST EAX,EAX; JZ; ADD EAX,0x4; RET
    0x4``. ``R1-VFT`` already resolves *it* to ``__thiscall`` with
    ``receiver.register == "ECX"``, on nothing but a copy. The machine fact this
    rule claims for the three bodies that tail-call into it is therefore already
    asserted by the shipped engine, for their own delegate.

    Every precondition, and what each one refuses:

    * a **sound** membership (:func:`vftable_memberships` has already dropped
      every entry that cannot state :data:`VFTABLE_BASIS`). No membership, no
      claim, and the record is byte-identical to the unarmed one;
    * ``cleanup["side"] == "callee"``. The caller-cleanup shape is ``V1-VFT``'s
      and a body with no terminal ``RET`` has no cleanup to read; a *conflicting*
      cleanup is not ``"callee"`` either, so the ambiguous case is refused;
    * **the receiver is still undetermined** (``receiver_evidence["present"]`` is
      not ``True``). This is the disjointness guard, and it is three guards in
      one. An *incoming dereference* through ECX is ``R1``'s evidence and ``R1``'s
      alone; an ``R-ALIAS`` dereference through a register copied from the
      incoming ECX (``MOV ESI,ECX; MOV EAX,[ESI]``, the shape nine of the ten
      ``R1-VFT`` corpus targets have) is the same class, and ``R1`` already owns
      it -- so the record must not carry a second rule for one receiver; and a
      dereference *after* ECX was written is the record's own
      ``ecx_reassigned_before_deref`` unknown, which this rule does not resolve
      and must not launder;
    * **no memory access rooted at ECX at all**, including the indexed forms
      :func:`_record_ecx_access` skips (``MOV EAX,[ECX + ECX*4 + 0x8]``). This
      states the positive fact the claim rests on -- the body *computes* an
      address from the receiver and never performs an access through it -- over a
      list that is complete;
    * **ECX is never a ``REP`` counter** (``state.ecx_rep``). A repeat count is an
      ordinary integer, and a body can be both. This is read positively and not
      off ``receiver.reason``, which ranks the address-taken unknown *above* the
      counter one and would therefore admit every such body on an outranked
      label -- pinned by ``test_11_a_rep_string_op_makes_ecx_a_counter``;
    * at least one **incoming member ``LEA``** (:func:`_incoming_member_leas`),
      which is what excludes ``0x00e51010``'s shape, a stack- or local-derived
      scalar in ECX, register reuse, an adjustor, a read after a call, and a body
      that only tests ECX.

    A guard of the form "a register loaded from the first popped word is never
    dereferenced" was written, measured and **rejected**: it is not a soundness
    requirement (the register-parameter argument above already excludes the COM
    reading) and it refuses a real shape, a ``__thiscall`` that takes a pointer
    argument on the stack and dereferences it. ``test_16`` pins that decision.

    It claims the **receiver register** and nothing else. No convention (that is
    the ordinary ``C6B`` arm reading this function's own ``ret imm``), no class,
    no vtable identity, no receiver type, no field, no layout -- and in
    particular the ``LEA`` displacements are **not** published as
    ``receiver.offsets``, which means displacements the body actually
    dereferenced. They appear only in the rule's own ``value``.
    """
    if not memberships:
        return None
    if receiver_evidence.get("present") is not None:
        return None
    if cleanup.get("side") != "callee":
        return None
    if state.ecx_rep:
        return None
    accesses = _ecx_rooted_accesses(state)
    if accesses:
        return None
    defs = _ecx_def_indices(state)
    leas = _incoming_member_leas(state, defs)
    if not leas:
        return None
    reads = _incoming_ecx_reads_before(state, defs)
    if not reads:
        return None
    return {"table": memberships[0][0], "slot": memberships[0][1],
            "citations": [item["id"] for item in reads],
            "leas": leas, "null_test": _incoming_ecx_null_test(state, defs)}


def _receiver_evidence(state):
    derefs = state.ecx_derefs
    incoming = [item for item in derefs if item["incoming"]]
    incoming_offsets = sorted({item["offset"] for item in incoming})
    written_through = sum(1 for item in incoming if item["store"])
    shape = None
    if incoming:
        shape = min(incoming, key=lambda item: item["index"])["shape"]
    if incoming:
        return {"present": True, "register": "ECX", "shape": shape,
                "offsets": incoming_offsets, "distinct_offsets": len(incoming_offsets),
                "max_offset": incoming_offsets[-1] if incoming_offsets else None,
                "written_through": written_through, "reason": None}
    if derefs:
        return {"present": None, "register": None, "shape": None, "offsets": [],
                "distinct_offsets": 0, "max_offset": None, "written_through": 0,
                "reason": "ecx_reassigned_before_deref"}
    if state.ecx_addr_taken:
        return {"present": None, "register": None, "shape": None, "offsets": [],
                "distinct_offsets": 0, "max_offset": None, "written_through": 0,
                "reason": "ecx_address_taken_without_memory_access"}
    if state.ecx_rep:
        return {"present": None, "register": None, "shape": None, "offsets": [],
                "distinct_offsets": 0, "max_offset": None, "written_through": 0,
                "reason": "ecx_used_as_counter"}
    if state.ecx_reads:
        return {"present": None, "register": None, "shape": None, "offsets": [],
                "distinct_offsets": 0, "max_offset": None, "written_through": 0,
                "reason": "ecx_read_without_deref"}
    return {"present": False, "register": None, "shape": None, "offsets": [],
            "distinct_offsets": 0, "max_offset": None, "written_through": 0,
            "reason": None}


def infer(observations, state=None, frame=None, meta=None, image_base=0x00400000,
          vftable_slots=(), tail_target_record=None):
    """Stage 2: the rule set, the only place a `confidence` field is produced.

    Called as `infer(disassembly)` it is the whole inference without
    cross-validation, which is how the test plan's fixture generators drive it;
    called with the full `(observations, state, frame, meta)` tuple it is the
    bare second stage, as the specification's module layout describes.
    """
    if state is None or frame is None or meta is None:
        return analyze(observations, image_base=image_base,
                       vftable_slots=vftable_slots,
                       tail_target_record=tail_target_record)
    return _infer_rules(observations, state, frame, meta, image_base,
                        vftable_slots, tail_target_record)


def _infer_rules(observations, state, frame, meta, image_base=0x00400000,
                 vftable_slots=(), tail_target_record=None):
    abstained = []
    inferences = []
    seen_codes = set()
    # The two new evidence classes, normalised once, up front, so every arm below
    # reads the same value and a malformed input is an absence rather than a
    # claim. Both default to empty, and with them empty every arm added by the
    # 2026-09-28 extension is false, so a record is byte-identical to the one the
    # rules before it produced.
    memberships = vftable_memberships(vftable_slots)

    def abstain(code, detail):
        if code not in ABSTENTION_CODES:
            raise AssertionError("unregistered abstention code %r" % code)
        entry = "%s: %s" % (code, detail)
        if entry in seen_codes:
            return
        seen_codes.add(entry)
        abstained.append(entry)

    def infer_rule(rule, claim, confidence, based_on, value=None):
        if rule not in RULE_IDS:
            raise AssertionError("unregistered rule id %r" % rule)
        citations = sorted({item for item in based_on if item})
        if not citations:
            return
        entry = {"id": rule, "claim": claim, "confidence": confidence,
                 "based_on": citations}
        if value is not None:
            entry["value"] = value
        if any(other["id"] == rule for other in inferences):
            suffix = 2
            while any(other["id"] == "%s#%d" % (rule, suffix) for other in inferences):
                suffix += 1
            entry["id"] = "%s#%d" % (rule, suffix)
        inferences.append(entry)

    ret_citations = [entry["obs"] for entry in state.ret_obs]
    terminal = _terminal_citations(observations)
    esp_poisoned = state.esp_delta is None
    unbalanced = bool((not frame["fp"]) and state.ret_obs and state.esp_delta not in (None, 0))
    esp_unresolved = esp_poisoned
    flow_complete = bool(state.flow_complete and not unbalanced)
    if unbalanced:
        abstain("flow_not_modelled",
                "the linear ESP walk ends at %+d, so the listing is not one path"
                % state.esp_delta)
    if meta["unparsed_count"]:
        abstain("unparsed_lines_present",
                "%d line(s) matched no grammar rule" % meta["unparsed_count"])
    frame_observations = [item for item in observations
                          if item["kind"] in ("STACK_SLOT_READ", "STACK_SLOT_WRITE")]
    untrusted_frame = bool(frame["push_ebp"] and not frame["mov_ebp_esp"]
                           and not frame["fp"] and frame_observations
                           and frame["ebp_is_general_register"])
    if untrusted_frame:
        for item in frame_observations:
            item["trust"] = "untrusted_frame"
        abstain("untrusted_frame_stack_reads",
                "push ebp with no mov ebp,esp: EBP is a general register, so every "
                "frame-relative offset is uncalibrated")
        abstain("frame_pointer_untrusted",
                "push ebp without mov ebp,esp, and EBP is loaded from a register or "
                "used as a memory base, so it is a general register")

    grouped, keys, max_key, gaps, slots = _slot_table(state, frame)

    # ---- cleanup: C1, C2, C3, C4, C5 --------------------------------------
    immediates = sorted({entry["imm"] for entry in state.ret_obs},
                        key=lambda item: (item is not None, item))
    conflict = len(immediates) > 1
    ret_imm = immediates[0] if len(immediates) == 1 else None
    has_ret = bool(state.ret_obs)
    cleanup = {"side": None, "bytes": None, "confidence": "UNKNOWN",
               "corroboration": "not_available", "evidence": None}
    rule_cleanup = None
    if not has_ret:
        tail = any(entry.get("form") == "jmp_out" for entry in state.exits)
        truncated = _is_truncated(state)
        if tail:
            detail = "the only exit observed is a tail jump"
        elif truncated:
            detail = "the listing is a prefix of a longer function"
        else:
            detail = "function has no RET instruction"
        abstain("no_terminal_ret", detail)
        infer_rule("C2", "no terminal return is present in the listing", "UNKNOWN", terminal)
    elif conflict:
        rendered = ", ".join("0x%x" % item for item in immediates if item is not None)
        abstain("ret_immediates_disagree", "%s disagree at two exits" % " != ".join(
            "0x%x" % item for item in immediates if item is not None))
        abstain("cleanup_undeterminable",
                "ret immediates disagree at multiple exits (%s)" % rendered)
        cleanup = {"side": "CONFLICT", "bytes": None, "confidence": "UNKNOWN",
                   "corroboration": "not_available",
                   "evidence": "terminal ret immediates disagree: %s" % rendered}
        infer_rule("C1", "calling convention is undetermined because the terminal "
                         "return immediates disagree", "UNKNOWN", ret_citations)
    elif ret_imm is None or ret_imm == 0:
        cleanup = {"side": "caller", "bytes": 0, "confidence": "INFERRED",
                   "corroboration": "not_available",
                   "evidence": "ret with no immediate" + (
                       ", no stack reads" if not keys else "")}
        infer_rule("C5", "the caller cleans up the stack: a bare RET is compatible "
                         "with caller cleanup and, for a zero-parameter __stdcall, "
                         "with zero bytes of callee cleanup", "INFERRED", ret_citations,
                   {"side": "caller", "bytes": 0})
        rule_cleanup = "C5"
    elif ret_imm % 4 != 0:
        # C3 has no divisibility test, and a 6-byte pop is not a whole number of
        # x86-32 stack arguments, so nothing about the argument area follows from
        # it: not the cleanup side, not the slot count, not a convention. Reporting
        # `callee`/6 at OBSERVED and then claiming four bytes of arguments against
        # a six-byte pop is the record contradicting itself.
        cleanup = {"side": None, "bytes": None, "confidence": "UNKNOWN",
                   "corroboration": "not_available",
                   "evidence": "ret 0x%x is not a whole number of dword stack "
                               "arguments" % ret_imm,
                   "contradiction": {
                       "kind": "ret_immediate_not_dword_multiple",
                       "detail": "RET 0x%x" % ret_imm,
                       "based_on": ret_citations}}
        abstain("ret_immediates_not_dword_multiple",
                "ret 0x%x pops %d byte(s), which is not a whole number of 4-byte "
                "stack arguments, so the popped area cannot be an argument count"
                % (ret_imm, ret_imm))
    elif not 0 <= ret_imm <= MAX_RET_IMMEDIATE:
        # `ret imm16` is the only form x86-32 has, so an immediate outside the
        # 16-bit range is not a possible pop at all. Reporting it as a callee pop
        # would also make A1-IMM expand `ret_imm / 4` derived slots, which for
        # `ret 0x100000000` is a billion-iteration loop -- i.e. the engine stops
        # being total on arbitrary text. Not in either document; see the module
        # docstring's deviations.
        cleanup = {"side": None, "bytes": None, "confidence": "UNKNOWN",
                   "corroboration": "not_available",
                   "evidence": "ret 0x%x is outside the 16-bit immediate an x86-32 "
                               "ret can encode" % ret_imm,
                   "contradiction": {
                       "kind": "ret_immediate_out_of_range",
                       "detail": "RET 0x%x" % ret_imm,
                       "based_on": ret_citations}}
        abstain("ret_immediate_out_of_range",
                "ret 0x%x is outside the 16-bit immediate x86-32 can encode, so it "
                "is not a possible stack pop" % ret_imm)
    else:
        cleanup = {"side": "callee", "bytes": ret_imm, "confidence": "OBSERVED",
                   "corroboration": "not_available", "evidence": "ret 0x%x" % ret_imm}
        infer_rule("C3", "the callee pops %d byte(s) of stack arguments" % ret_imm,
                   "OBSERVED", ret_citations, {"side": "callee", "bytes": ret_imm})
        rule_cleanup = "C3"
        if ret_imm < max_key:
            cleanup = {"side": None, "bytes": ret_imm, "confidence": "UNKNOWN",
                       "corroboration": "not_available",
                       "evidence": "ret 0x%x but entry slot 0x%x is read" % (
                           ret_imm, max_key)}
            abstain("ret_imm_below_highest_slot",
                    "ret 0x%x pops less than the highest read slot 0x%x; everything "
                    "above it belongs to the caller's frame" % (ret_imm, max_key))
            infer_rule("C4", "cleanup side is undetermined: a slot above the popped "
                             "area is read", "UNKNOWN", ret_citations,
                       {"side": None, "bytes": ret_imm})
            rule_cleanup = "C4"

    # ---- stack arguments: A1, A2, and immediate-derived slots ---------------
    immediate_slots = []
    if cleanup["side"] == "callee" and not keys and isinstance(cleanup["bytes"], int) \
            and cleanup["bytes"] > 0 and cleanup["bytes"] % 4 == 0:
        for ordinal in range(cleanup["bytes"] // 4):
            key = 4 + ordinal * 4
            slot = {
                "ordinal": ordinal + 1,
                "entry_offset": "entry_ESP+0x%x" % key,
                "sizes": [4],
                "read": False,
                "written": False,
                "observed": False,
                "size_inferred": False,
                "source": "ret_immediate",
            }
            immediate_slots.append(slot)
        max_key = cleanup["bytes"]
        gaps = len(immediate_slots)
    all_slots = slots + immediate_slots
    widths_ambiguous = any(len(slot["sizes"]) > 1 for slot in slots)
    if widths_ambiguous:
        abstain("slot_width_ambiguous",
                "one entry slot is read at more than one width")
    not_complete = False
    stack_confidence = "INFERRED" if keys else _DERIVED
    if immediate_slots:
        stack_confidence = _DERIVED
    if gaps > 0 or any(slot.get("size_inferred") for slot in slots):
        stack_confidence = _weaker(stack_confidence, _DERIVED)
    if widths_ambiguous:
        stack_confidence = _weaker(stack_confidence, _DERIVED)
    if gaps > 0 and len(slots) > 1:
        abstain("slot_gaps_present",
                "argument ordinal(s) below the highest read slot are never touched")
    if state.seh and not frame["fp"]:
        stack_confidence = _weaker(stack_confidence, _DERIVED)
    if unbalanced:
        stack_confidence = _weaker(stack_confidence, _DERIVED)

    stack_arguments = {
        "observed_slots": len(slots),
        "derived_slots": len(immediate_slots),
        "gaps": gaps,
        "total_bytes": max_key,
        "confidence": stack_confidence,
        "not_complete": not_complete,
        "widths_ambiguous": widths_ambiguous,
        "slots": all_slots,
    }
    if keys:
        infer_rule("A1", "entry-relative argument slots", stack_confidence,
                   [entry["obs"] for entry in state.slot_reads + state.slot_writes],
                   {"observed_slots": len(slots), "gaps": gaps, "total_bytes": max_key})
    if immediate_slots:
        infer_rule("A1-IMM",
                   "argument slots derived from the terminal immediate alone; no "
                   "argument read was observed, so this is the popped area and not "
                   "a parameter count", _DERIVED, ret_citations,
                   {"derived_slots": len(immediate_slots), "total_bytes": max_key})
    if widths_ambiguous:
        infer_rule("A2", "one entry slot carries several read widths", "UNKNOWN",
                   [entry["obs"] for entry in state.slot_reads + state.slot_writes])

    # ---- receiver: R1, R0, R2 ----------------------------------------------
    receiver_evidence = _receiver_evidence(state)
    receiver_confidence = "UNKNOWN"
    receiver = {
        "present": receiver_evidence["present"],
        "register": receiver_evidence["register"],
        "confidence": "UNKNOWN",
        "shape": receiver_evidence["shape"],
        "offsets": receiver_evidence["offsets"],
        "distinct_offsets": receiver_evidence["distinct_offsets"],
        "max_offset": receiver_evidence["max_offset"],
        "written_through": receiver_evidence["written_through"],
        "bounds_only": True,
    }
    # ---- R1-VFT: the callee-pop receiver form ------------------------------
    # See `_vftable_dispatch_receiver` for the argument. The whole rule is one
    # guarded upgrade of the receiver block above; the convention it enables is
    # named by the ordinary C6B arm further down, off this function's own
    # `ret imm`, so nothing here states a convention and nothing here can reach
    # the caller-cleanup shape that V1-VFT already owns.
    dispatch = _vftable_dispatch_receiver(state, memberships, receiver_evidence,
                                          cleanup)
    if dispatch is not None:
        table, slot, citations = dispatch
        receiver["present"] = True
        receiver["register"] = "ECX"
        receiver["provenance"] = "vftable_slot_dispatch"
        receiver_confidence = "INFERRED"
        infer_rule("R1-VFT",
                   "ECX carries the receiver: %s is slot %d of the vptr-backed "
                   "vftable at %s, so it is a virtual member of some class and every "
                   "virtual call that reaches it indexes the vptr through the object "
                   "address; the body reads its incoming ECX before writing it, and a "
                   "body that reads a register the vtable dispatch delivered uses the "
                   "object, so the receiver is in ECX. The callee pops its own stack "
                   "arguments, which is the COM / __stdcall interface form, and that "
                   "is the one shape in which a virtual member takes its receiver from "
                   "the first popped stack word instead -- a body in that form never "
                   "reads its incoming ECX, which is why this body reading it is what "
                   "decides the two apart"
                   % ((_first_va(observations) or "this function"), slot,
                      _fmt_hex(table)),
                   "INFERRED", citations,
                   {"table": _fmt_hex(table), "slot_index": slot,
                    "membership_count": len(memberships), "receiver_register": "ECX",
                    "receiver_provenance": "vftable_slot_dispatch",
                     "cleanup_side": cleanup["side"],
                     "incoming_ecx_reads": len(citations)})
    # ---- R2-VFT: the same fact from an address-taken ECX -------------------
    # See `_vftable_address_receiver` for the argument. Identical in shape and
    # in what it is allowed to claim; the only difference is the class of read,
    # and the two are disjoint by construction (R2-VFT refuses any body with an
    # ECX memory access at all). It runs only when R1-VFT did not, so a record
    # never carries two rules for one receiver.
    addressed = None
    if dispatch is None:
        addressed = _vftable_address_receiver(state, memberships, receiver_evidence,
                                              cleanup)
    if addressed is not None:
        table, slot = addressed["table"], addressed["slot"]
        leas = addressed["leas"]
        receiver["present"] = True
        receiver["register"] = "ECX"
        receiver["provenance"] = "vftable_slot_address"
        receiver_confidence = "INFERRED"
        infer_rule("R2-VFT",
                   "ECX carries the receiver: %s is slot %d of the vptr-backed "
                   "vftable at %s, so it is a virtual member of some class and every "
                   "virtual call that reaches it indexes the vptr through the object "
                   "address; the body takes the address of its incoming ECX (LEA at "
                   "%s) and never touches memory through it%s, and a body that computes "
                   "an address from a register the vtable dispatch delivered computes "
                   "it from the object, so the receiver is in ECX. The callee pops its "
                   "own stack arguments, which is the COM / __stdcall interface form, "
                   "and that is the one shape in which a virtual member takes its "
                   "receiver from the first popped stack word instead -- a body in that "
                   "form has no register parameter and never reads its incoming ECX, "
                   "which is why this body reading it is what decides the two apart"
                   % ((_first_va(observations) or "this function"), slot,
                      _fmt_hex(table),
                      ", ".join(item["at"] for item in leas
                                if item["at"]) or "the sites cited below",
                      ", after a null test of it" if addressed["null_test"] else ""),
                   "INFERRED", addressed["citations"],
                   {"table": _fmt_hex(table), "slot_index": slot,
                    "membership_count": len(memberships), "receiver_register": "ECX",
                    "receiver_provenance": "vftable_slot_address",
                    "cleanup_side": cleanup["side"],
                    "incoming_ecx_reads": len(addressed["citations"]),
                    "incoming_member_leas": len(leas),
                    "member_lea_sites": [item["at"] for item in leas
                                         if item["at"]],
                    "member_lea_displacements": [item["disp"] for item in leas],
                    "incoming_ecx_null_test": addressed["null_test"]})
    # `dispatch` is load-bearing and not cosmetic. When R1-VFT has already set
    # `present`, neither the R1 arm nor R2 may run: R1 would claim the *same*
    # receiver a second time, by dereference, with an empty offset list, and R2
    # would claim the opposite one ("ECX is never read in any form"), which the
    # listing refutes. One receiver fact gets one rule, whichever rule it is.
    # The same holds for `addressed`, and it is the reason R2-VFT is entered
    # only when `dispatch is None`.
    if dispatch is not None or addressed is not None:
        pass
    elif receiver["present"] is True:
        receiver_confidence = "INFERRED"
        if (receiver["distinct_offsets"] >= 3 and receiver["written_through"] >= 1
                and ret_imm in (None, 0) and not esp_unresolved):
            receiver_confidence = "SUPPORTED"
        infer_rule("R1", "ECX carries a receiver and is dereferenced before any "
                         "definite write to it", receiver_confidence,
                   _ecx_citations(state),
                   {"register": "ECX", "offsets": receiver["offsets"],
                    "written_through": receiver["written_through"]})
    elif receiver["present"] is None:
        reason = receiver_evidence["reason"]
        receiver["reason"] = reason
        abstain("receiver_not_determinable", reason)
        if reason == "ecx_address_taken_without_memory_access":
            abstain("ecx_address_taken_without_memory_access",
                    "LEA takes ECX's address without any memory access through it")
        infer_rule("R0", "the register receiver is undetermined: %s" % reason, "UNKNOWN",
                   _ecx_citations(state), {"register": None, "reason": reason})
    else:
        receiver_confidence = "OBSERVED"
        infer_rule("R2", "ECX is never read in any form, so there is no register "
                         "receiver", "OBSERVED", terminal, {"present": False})
    receiver["confidence"] = receiver_confidence

    edx_incoming_deref = bool(state.edx_derefs)
    if edx_incoming_deref:
        infer_rule("C8-E", "EDX is a memory base before any definite write to it",
                   "OBSERVED", _edx_citations(state) or terminal, {"register": "EDX"})

    # ---- variadic and SEH: V1, V2 ------------------------------------------
    variadic = "SUSPECTED" if state.variadic_markers else "UNKNOWN"
    if variadic == "SUSPECTED":
        abstain("variadic_not_decidable_from_listing",
                "no caller-side va_list construction is visible")
    if state.seh:
        infer_rule("V2", "an FS:/GS: operand is an SEH or cookie frame, which is not "
                         "variadic evidence", "OBSERVED", _segment_citations(state),
                   {"seh_or_cookie_frame": True})

    # ---- convention: C6, C6B, C7, C8, C9, C10, C11, C12 ---------------------
    conventions = {
        "calling_convention": None,
        "confidence": "UNKNOWN",
        "candidate_conventions": list(CONVENTIONS),
        "ambiguities": [],
        "corroboration": "not_available",
    }
    convention_rule = None
    receiver_undetermined = receiver["present"] is None
    if not has_ret or conflict:
        pass
    elif variadic == "SUSPECTED":
        abstain("variadic_caps_convention",
                "variadic suspicion removes any guarantee about the stack-argument "
                "extent")
        conventions["candidate_conventions"] = ["__cdecl"]
        conventions["ambiguities"] = ["variadic_suspected"]
        not_complete = True
        stack_arguments["not_complete"] = True
        stack_arguments["confidence"] = _weaker(stack_arguments["confidence"], _DERIVED)
        infer_rule("C12", "the calling convention is not decidable from the listing",
                   "UNKNOWN", state.variadic_markers)
        convention_rule = "C12"
    elif esp_unresolved and not frame["fp"]:
        conventions["candidate_conventions"] = list(CONVENTIONS)
        conventions["ambiguities"] = ["esp_alignment_unknown"]
        abstain("esp_alignment_unknown",
                "the entry-relative ESP offset is unknown and there is no frame "
                "pointer to fall back on")
        infer_rule("C11", "the entry-relative argument offsets are unknown, so the "
                          "convention is unknown", "UNKNOWN", _frame_citations(state))
        convention_rule = "C11"
    elif edx_incoming_deref and cleanup["side"] == "caller" and not esp_unresolved:
        conventions["calling_convention"] = "__fastcall"
        conventions["confidence"] = "INFERRED"
        conventions["candidate_conventions"] = ["__fastcall"]
        infer_rule("C8", "calling convention is __fastcall: ECX and EDX are both "
                         "volatile, so reading the incoming EDX before any write to "
                         "it can only be a compiler-guaranteed register argument",
                   "INFERRED", _ecx_citations(state) + _edx_citations(state),
                   "__fastcall")
        convention_rule = "C8"
    elif receiver_undetermined and (
            (cleanup["side"] == "callee" and not esp_unresolved)
            or (cleanup["side"] == "caller" and keys and not edx_incoming_deref)):
        # C6 and C9 discriminate on receiver *absence* -- the spec's own
        # preconditions read "receiver absent" -- and C6B needs presence. The only
        # sound `present: false` is R2 ("ECX is never read in any form"), while
        # R0's `present: null` is a known-unknown: the receiver may exist and
        # simply be unused. A null receiver is therefore neither absent nor
        # present, so none of the three preconditions can be evaluated and none
        # may fire. Naming a convention here would be a guess dressed as a rule.
        # This is checked before the C8-E/C6B collision below, because that
        # collision is about a *receiver-present* reading, which a null receiver
        # does not establish.
        conventions["candidate_conventions"] = (
            ["__stdcall", "__thiscall"] if cleanup["side"] == "callee"
            else ["__cdecl", "__thiscall"])
        conventions["ambiguities"] = ["receiver_undetermined"]
        abstain("receiver_undetermined_blocks_convention",
                "the register receiver is undetermined (%s), and the convention "
                "rule that would apply discriminates on receiver absence"
                % receiver_evidence["reason"])
        infer_rule("C10", "the calling convention is unknown: the receiver is "
                          "undetermined (%s) and every remaining discriminator "
                          "needs receiver absence" % receiver_evidence["reason"],
                   "UNKNOWN", _ecx_citations(state))
        convention_rule = "C10"
    elif edx_incoming_deref and cleanup["side"] == "callee":
        # Two mutually exclusive readings in one body, and neither wins on the
        # evidence. C8-E reads the incoming EDX, which no compiler-generated
        # __cdecl/__thiscall/__stdcall function can do -- that is the spec's one
        # strong discriminator. C6B reads a callee that pops its own arguments,
        # and its own claim text says that "rules out cdecl and fastcall". Both
        # cannot hold: an __fastcall callee does not pop, and a popping __thiscall
        # has no incoming register argument. Asserting one while the other stands
        # is the record silently resolving its own contradiction, so it abstains
        # and both readings stay visible.
        conventions["candidate_conventions"] = ["__thiscall", "__fastcall"]
        conventions["ambiguities"] = ["ecx_and_edx_indistinguishable"]
        not_complete = True
        stack_arguments["not_complete"] = True
        stack_arguments["confidence"] = _weaker(stack_arguments["confidence"], _DERIVED)
        abstain("ecx_and_edx_indistinguishable",
                "EDX is dereferenced before any write to it (C8-E) and the callee "
                "pops its own stack arguments (C6B); a fastcall callee does not "
                "pop and a popping thiscall has no incoming register argument")
        infer_rule("C6B", "the reading that this is a __thiscall member which pops "
                          "its own stack arguments is present and undecided: it "
                          "excludes __fastcall, while C8-E asserts an incoming EDX "
                          "that only __fastcall guarantees", "UNKNOWN",
                   _ecx_citations(state) + ret_citations)
        convention_rule = "C6B"
    elif cleanup["side"] == "caller" and receiver["present"] is True:
        conventions["calling_convention"] = "__thiscall"
        conventions["confidence"] = "INFERRED"
        conventions["candidate_conventions"] = ["__thiscall", "__fastcall"]
        infer_rule("C7", "calling convention is __thiscall: the receiver arrives in "
                         "ECX and the caller cleans the stack", "INFERRED",
                   _ecx_citations(state) + ret_citations, "__thiscall")
        convention_rule = "C7"
    elif cleanup["side"] == "callee" and not esp_unresolved:
        if receiver["present"] is True:
            conventions["calling_convention"] = "__thiscall"
            conventions["confidence"] = "INFERRED"
            conventions["candidate_conventions"] = ["__thiscall"]
            infer_rule("C6B", "calling convention is __thiscall: the callee pops the "
                              "stack arguments, which rules out cdecl and fastcall, "
                              "and the receiver arrives in ECX", "INFERRED",
                       _ecx_citations(state) + ret_citations, "__thiscall")
            convention_rule = "C6B"
        else:
            conventions["calling_convention"] = "__stdcall"
            conventions["confidence"] = "INFERRED"
            conventions["candidate_conventions"] = ["__stdcall"]
            infer_rule("C6", "calling convention is __stdcall: a callee that pops "
                             "stack arguments with no register receiver", "INFERRED",
                       ret_citations, "__stdcall")
            convention_rule = "C6"
    elif (cleanup["side"] == "caller" and keys and receiver["present"] is False
          and not edx_incoming_deref):
        conventions["calling_convention"] = "__cdecl"
        conventions["confidence"] = "INFERRED"
        conventions["candidate_conventions"] = ["__cdecl", "__thiscall"]
        infer_rule("C9", "calling convention is __cdecl: the caller cleans the stack "
                         "and at least one entry slot is read", "INFERRED",
                   [entry["obs"] for entry in state.slot_reads + state.slot_writes]
                   + ret_citations, "__cdecl")
        convention_rule = "C9"
    elif (memberships and cleanup["side"] == "caller" and not keys
          and receiver["present"] is not True and not edx_incoming_deref):
        # V1-VFT. The function is the value of a slot of a table the image itself
        # proves is a vptr-backed vftable (predicate P, three clauses, in
        # `vftables.py`), the callee pops nothing, and no entry-relative stack
        # slot was read. A virtual function is never `static`, so it has a
        # receiver and a class; the receiver is not in the callee-popped area
        # (nothing is popped and no stack word is read as an argument), so on
        # x86-32 MSVC it is in a register, and of __thiscall/__fastcall only
        # ECX carries one -- with the incoming EDX read excluded above, nothing
        # else remains. The disjunction is over an exhaustive set.
        #
        # The cleanup clause is load-bearing, not decorative: measured on the
        # frontier, twelve targets are sound vftable slots in the callee-pop
        # (COM/__stdcall interface) form, and membership alone would have
        # asserted __thiscall on every one of them. `0x01053e00` is the sharpest
        # case -- the receiver is its first callee-popped stack word -- and it
        # also fails P on all five tables the triage index claims for it.
        table, slot = memberships[0]
        own_va = _first_va(observations)
        conventions["calling_convention"] = "__thiscall"
        conventions["confidence"] = "INFERRED"
        conventions["candidate_conventions"] = ["__thiscall", "__fastcall"]
        stack_arguments["total_bytes"] = 0
        receiver["register"] = "ECX"
        receiver["provenance"] = "vftable_slot"
        infer_rule("V1-VFT",
                   "calling convention is __thiscall: %s is slot %d of the vptr-backed "
                   "vftable at %s, so it is a virtual member of some class; the callee "
                   "pops nothing and no stack word is read as an argument, so the "
                   "receiver is in a register, and ECX is the only one that carries one"
                   % (own_va if own_va else "this function",
                      slot, _fmt_hex(table)),
                   "INFERRED", ret_citations,
                   {"table": _fmt_hex(table), "slot_index": slot,
                    "membership_count": len(memberships), "receiver_register": "ECX",
                    "cleanup_side": cleanup["side"],
                    "receiver_provenance": "vftable_slot"})
        convention_rule = "V1-VFT"
    else:
        conventions["candidate_conventions"] = list(CONVENTIONS)
        # The reason has to name what is actually missing. The spec's own C10
        # sentence ("byte-identical under all four conventions") is true for the
        # argless leaf and false for a body whose cleanup is a non-dword pop, and
        # a wrong abstention reason is the same defect as a wrong convention.
        if cleanup["side"] is None and isinstance(ret_imm, int) and ret_imm > 0:
            c10_detail = ("the callee pop of 0x%x is not a whole number of dword "
                          "stack arguments, so no convention follows from it" % ret_imm)
            c10_claim = ("the calling convention is unknown: the terminal pop is "
                         "not a whole number of dword arguments")
        elif not keys and receiver["present"] is not True and not edx_incoming_deref:
            c10_detail = "no stack-argument read and no positive receiver evidence"
            c10_claim = "the function is byte-identical under all four conventions"
        else:
            c10_detail = ("the cleanup side %r and receiver state %r do not combine "
                          "into a discriminator"
                          % (cleanup["side"], receiver["present"]))
            c10_claim = ("the calling convention is unknown: no rule's precondition "
                         "is satisfied by this body's cleanup and receiver state")
        abstain("no_discriminator", c10_detail)
        infer_rule("C10", c10_claim, "UNKNOWN", terminal)
        convention_rule = "C10"

    # ---- hidden return: S1, S2, S3 -----------------------------------------
    sret = _sret_block(state, receiver, not_complete, ret_citations, infer_rule,
                       lambda code, detail: abstain(code, detail))
    tail = _tail_call(state, frame, ret_citations, infer_rule, terminal)
    return_block = _return_block(state, frame, ret_imm, has_ret, conflict,
                                 infer_rule, terminal, ret_citations)
    # ---- tail-call forwarding: T1-FWD -------------------------------------
    # Placed *before* the override below, and the override is then skipped when a
    # forward was established. A thunk whose target's ABI was resolved is not an
    # unknown convention that a tail call made undecidable -- it is a call whose
    # convention was read off the function the call actually reaches -- so the
    # override must not demote it back to UNKNOWN. When no forward was
    # established the override runs exactly as before, byte for byte.
    forwarded = None
    if tail["present"] and not has_ret and state.jmps_direct:
        # The site count is no longer the gate; `_tail_forward` re-derives the
        # shared target through `_shared_target_hops` and refuses everything the
        # old `== 1` refused. `jmps_direct[0]` is that shared target whenever the
        # guard can pass, and is ignored when it cannot.
        hop_va = state.jmps_direct[0]["target"]
        forwarded = _tail_forward(state, frame, tail, stack_arguments,
                                  tail_target(tail_target_record, hop_va), hop_va,
                                  infer_rule, terminal)
    if forwarded:
        if forwarded["cleanup"] is not None:
            cleanup = dict(forwarded["cleanup"])
        if forwarded["convention"] is not None:
            conventions["calling_convention"] = forwarded["convention"]
            conventions["confidence"] = forwarded["confidence"]
            conventions["corroboration"] = "forwarded_from_tail_target"
            conventions["candidate_conventions"] = [forwarded["convention"]]
            convention_rule = "T1-FWD"
        if forwarded["adjustor_delta"] is not None:
            # A this-adjustor thunk adjusts the receiver it was handed; the size
            # of that adjustment belongs to the receiver and is reported as its
            # own field. The receiver's *identity* is never copied: the target's
            # `this` is a different object, and only the thunk's own body can
            # say which class either belongs to.
            receiver["adjustor_delta"] = forwarded["adjustor_delta"]
    if tail["present"] and not has_ret and not forwarded:
        conventions["calling_convention"] = None
        conventions["confidence"] = "UNKNOWN"
        conventions["ambiguities"] = list(conventions["ambiguities"]) + ["tail_call"]
        not_complete = True
        stack_arguments["not_complete"] = True
    elif forwarded and forwarded["convention"] is None:
        # The cleanup moved but no convention did, so the record still does not
        # name one: the ambiguity stays, and what is new is the cleanup.
        conventions["ambiguities"] = list(conventions["ambiguities"]) + ["tail_call"]
    stack_arguments["not_complete"] = not_complete

    dispatch = {
        "vtable_shaped_loads": len(state.vtable_loads),
        "indirect_calls": len(state.calls_indirect) + len(state.jmps_indirect),
        "call_offsets": sorted({entry["call_offset"] for entry in state.vtable_loads}),
    }
    if state.vtable_loads:
        infer_rule("D1", "a load of the form mov r,[base+off] is dispatched through "
                         "r or through [r+off]; the offset is a candidate slot index, "
                         "not a vtable fact", "OBSERVED",
                   [entry["obs"] for entry in state.vtable_loads],
                   {"vtable_shaped_loads": dispatch["vtable_shaped_loads"],
                    "call_offsets": dispatch["call_offsets"]})

    if meta["instruction_count"] == 0:
        abstain("empty_listing", _empty_detail(observations))

    if _is_truncated(state):
        abstain("truncated_listing",
                "the last instruction is neither a return nor an out-of-listing "
                "transfer, so the listing stops mid-function")

    verdict = "ABI_UNKNOWN"
    if (conventions["calling_convention"] is not None
            and cleanup["side"] in ("callee", "caller")
            and cleanup["confidence"] != "UNKNOWN"
            and return_block["confidence"] != "UNKNOWN"
            and not tail["present"]):
        verdict = "ABI_INFERRED"
    completeness = "PARTIAL"
    if state.instructions == 0 or (not has_ret and not keys
                                  and receiver["present"] is not True
                                  and not state.calls_direct
                                  and not state.calls_indirect):
        completeness = "EMPTY"
    elif verdict == "ABI_INFERRED" \
            and _at_least(cleanup["confidence"], "INFERRED") \
            and _at_least(conventions["confidence"], "INFERRED"):
        completeness = "CORE_RESOLVED"

    record = {
        "schema": SCHEMA,
        "verdict": verdict,
        "completeness": completeness,
        "target": {
            "va": _first_va(observations),
            "instructions": state.instructions,
            "address_available": bool(meta["address_available"]),
            "syntax": "att" if meta["layout"] == "att_text" else "intel",
            "image_base": _fmt_hex(image_base),
        },
        "parse": {
            "degraded": bool(meta["unparsed_count"]),
            "unparsed": meta["unparsed_count"],
            "layout": meta["layout"],
            "local_extent": state.local_extent,
            "frame": dict(frame),
            "esp_unresolved": esp_unresolved,
            "flow_complete": flow_complete,
        },
        "observations": observations,
        "inferences": inferences,
        "abi": {},
        "conventions": conventions,
        "receiver": receiver,
        "stack_arguments": stack_arguments,
        "cleanup": cleanup,
        "return": return_block,
        "sret": sret,
        "variadic": variadic,
        "seh_or_cookie_frame": bool(state.seh),
        "dispatch": dispatch,
        "tail_call": tail,
        "abstained_because": abstained,
        "cross_validation": {
            "ghidra": "no_information",
            "persisted": "no_information",
            "agreement": False,
            "ghidra_calling_convention": None,
            "ghidra_parameter_count": None,
            "persisted_calling_convention": None,
        },
        "conflicts": [],
        "content_sha256": None,
    }
    if meta.get("declared_count") is not None:
        record["parse"]["declared_count"] = meta["declared_count"]
    record["abi"] = _abi_block(record, state, frame)
    return record


def _empty_detail(observations):
    if any(item["kind"] == "DATA_BYTE" for item in observations):
        return "byte column with no mnemonic is not an instruction"
    return "no parseable instruction was supplied"


def _first_va(observations):
    for item in observations:
        if item.get("at"):
            return item["at"]
    return None


def _is_truncated(state):
    real = [item for item in state.insns if item["kind"] == "insn"]
    if not real or state.ret_obs or state.transfer_out:
        return False
    last = real[-1]
    return last["base"] not in ("RET", "RETN", "JMP", "JMPX")


def _ecx_citations(state):
    citations = [item["id"] for item in state.observations
                 if re.search(r"\bECX\b", item.get("raw") or "")]
    return citations or list(state.frame_citations)


def _edx_citations(state):
    return [item["id"] for item in state.observations
            if re.search(r"\bEDX\b", item.get("raw") or "")]


def _segment_citations(state):
    return [item["id"] for item in state.observations
            if item["kind"] == "SEGMENT_TLS"]


def _frame_citations(state):
    return list(state.frame_citations)


def _sret_block(state, receiver, not_complete, ret_citations, infer_rule, abstain):
    block = {"present": None, "slot": None, "confidence": _DERIVED,
             "ambiguity": None, "candidates": None, "hypothesis_confidence": None,
             "eax_holds_slot0_at_ret": None, "basis": None,
             "this_interaction": None}
    loads = [entry for entry in state.slot0_loads if entry.get("key") == 4]
    written_through = None
    for load in loads:
        for store in state.stores_through_reg:
            if store["reg"] == load["reg"] and store["index"] > load["index"]:
                written_through = load
                break
        if written_through is not None:
            break
    if written_through is not None:
        block["present"] = None
        block["slot"] = 4
        block["confidence"] = "UNKNOWN"
        block["ambiguity"] = "sret_vs_out_param"
        block["candidates"] = ["hidden_sret", "out_parameter"]
        block["hypothesis_confidence"] = "INFERRED"
        block["basis"] = (
            "entry slot 0 is loaded into a register that is then the base of a "
            "write; a hidden struct-return pointer and an out-parameter compile to "
            "the same sequence, so the distinction is not decidable from the "
            "callee's own listing")
        eax_def = state.vdef_index.get("EAX")
        block["eax_holds_slot0_at_ret"] = any(
            load["reg"] == "EAX" and load["index"] == eax_def for load in loads)
        if receiver["present"] is True:
            block["this_interaction"] = {"this_register": "ECX", "sret_slot": 4,
                                         "ordering": "not_applicable"}
        infer_rule("S1", "a hidden struct-return pointer is a hypothesis only: entry "
                         "slot 0 is written through a pointer", "INFERRED",
                   [written_through["obs"]] + [entry["obs"] for entry in loads],
                   {"present": None, "slot": 4,
                    "ambiguity": "sret_vs_out_param"})
        if receiver["present"] is True:
            infer_rule("S3", "in MSVC x86 a hidden struct-return pointer is always "
                             "stack slot 0 while this is in ECX, so the two never "
                             "contend", _DERIVED, ret_citations,
                       {"ordering": "not_applicable"})
        abstain("sret_vs_out_param", "entry slot 0 is written through a pointer")
        return block
    block["present"] = False
    block["confidence"] = _DERIVED
    block["basis"] = ("entry slot 0 is not written through a pointer; DERIVED absence "
                      "is weak, a struct filled through another alias would be missed")
    infer_rule("S2", "entry slot 0 is not written through a pointer", _DERIVED,
               ret_citations or _terminal_citations(state.observations),
               {"present": False})
    return block


def _tail_call(state, frame, ret_citations, infer_rule, terminal):
    block = {"present": False, "target": None, "form": None,
             "after_frame_setup": False}
    if not state.transfer_out:
        return block
    last = state.transfer_out[-1]
    frame_setup = bool(frame["push_ebp"] or frame["sub"] or frame["and_esp"])
    if state.ret_obs:
        block = {"present": True, "target": _fmt_hex(last["target"]),
                 "form": "epilogue_then_jmp", "after_frame_setup": frame_setup}
        infer_rule("T2", "the function can reach a caller by transferring out of the "
                         "listing, so the path that actually returns was never "
                         "observed", "UNKNOWN", [last["obs"]] + ret_citations,
                   {"form": "epilogue_then_jmp"})
        return block
    block = {"present": True, "target": _fmt_hex(last["target"]), "form": "jmp",
             "after_frame_setup": frame_setup}
    infer_rule("T1", "this listing is a tail transfer: it inherits its caller's frame "
                     "and never runs its own RET", "UNKNOWN",
               [last["obs"]] + terminal, {"form": "jmp"})
    return block


def _return_block(state, frame, ret_imm, has_ret, conflict, infer_rule, terminal,
                  ret_citations):
    block = {"register": None, "register_class": "unknown", "confidence": "UNKNOWN",
             "type": None, "void_possible": False,
             "aggregate_evidence": {"bulk_write": False}}
    if state.has_x87:
        register = "ST0"
    elif state.has_xmm and "XMM0" in state.vclass:
        register = "XMM0"
    elif has_ret or "EAX" in state.vclass:
        register = "EAX"
    else:
        register = None
    if register is None:
        return block
    block["register"] = register
    bulk = any(entry["rep"] and entry["string_base"] for entry in state.string_ops)
    block["aggregate_evidence"]["bulk_write"] = bool(bulk)
    if register in ("ST0", "XMM0"):
        block["register_class"] = "float_or_x87"
        block["confidence"] = _DERIVED
        infer_rule("RT1", "the return value is carried in %s: an x87 or SSE "
                          "instruction appears in the body" % register, _DERIVED,
                   _frame_citations(state) or terminal, register)
        return block
    value_class = state.vclass.get("EAX", "opaque")
    last_call = max([entry["index"] for entry in
                     state.calls_direct + state.calls_indirect], default=-1)
    eax_def = state.vdef_index.get("EAX", -1)
    if state.has_call and last_call > eax_def:
        value_class = "call_result"
    if value_class in ("integral",):
        block["register_class"] = "integral"
        block["confidence"] = "INFERRED"
    elif value_class == "pointer_like":
        block["register_class"] = "pointer_like"
        block["confidence"] = "INFERRED"
    elif value_class == "call_result":
        block["register_class"] = "aggregate_unknown"
        block["confidence"] = "INFERRED"
    elif value_class in ("opaque", "large_or_mask"):
        block["register_class"] = "aggregate_unknown"
        block["confidence"] = "INFERRED"
    else:
        block["register_class"] = "unknown"
        block["confidence"] = "UNKNOWN"
    if bulk:
        block["register_class"] = "aggregate_unknown"
        block["confidence"] = "INFERRED"
        infer_rule("RT4", "a bulk string write reaches the return register, which is "
                          "not a struct-return signature", "INFERRED",
                   [entry["obs"] for entry in state.string_ops],
                   {"bulk_write": True})
    if has_ret and not conflict:
        infer_rule("RT1", "the return value is carried in EAX", block["confidence"],
                   ret_citations or terminal, register)
        infer_rule("RT2", "the last value written to EAX classifies as %s"
                   % block["register_class"], block["confidence"],
                   ret_citations or terminal,
                   {"register_class": block["register_class"]})
    if (not state.reg_writes.get("EAX") and not state.has_call and has_ret
            and not conflict):
        block["void_possible"] = True
        infer_rule("RT3", "EAX is never written and no call can clobber it, so a void "
                          "return is possible; this is a flag, never a type", _DERIVED,
                   ret_citations, {"void_possible": True})
    return block


def _return_semantics(block):
    register = block["register"]
    kind = block["register_class"]
    if register is None or kind == "unknown":
        text = "undetermined"
    elif kind == "float_or_x87":
        text = "float_or_x87_in_%s" % register
    elif kind == "integral":
        text = "integral_in_%s" % register
    elif kind == "pointer_like":
        text = "pointer_like_in_%s" % register
    else:
        text = "unclassified_in_%s" % register
    if block["void_possible"]:
        text += ";void_possible"
    return text


def _abi_block(record, state, frame):
    abi = {"architecture": "x86-32"}
    convention = record["conventions"]["calling_convention"]
    if convention is not None:
        abi["calling_convention"] = convention
    cleanup = record["cleanup"]
    if cleanup["side"] in ("callee", "caller"):
        abi["stack_cleanup_bytes"] = cleanup["bytes"]
        abi["stack_cleanup_owner"] = cleanup["side"]
    form = state.ret_obs[0]["form"] if state.ret_obs else None
    if form is not None and cleanup["side"] != "CONFLICT":
        abi["ret_form"] = form
        abi["termination"] = form
    receiver = record["receiver"]
    if receiver["present"] is True:
        abi["hidden_this_register"] = "ECX"
        abi["receiver_register"] = "ECX"
        abi["hidden_this"] = True
        abi["receiver"] = True
    elif receiver["present"] is False:
        abi["receiver"] = False
    if record["return"]["register"] is not None:
        abi["return_register"] = record["return"]["register"]
        abi["return_semantics"] = _return_semantics(record["return"])
    slots = record["stack_arguments"]["slots"]
    if slots:
        abi["stack_arguments"] = slots
        abi["ordinary_stack_arguments"] = slots
        abi["ordinary_stack_argument_slots"] = [slot["entry_offset"] for slot in slots]
    saved = sorted({register for register in state.saved if register in CALLEE_SAVED})
    if saved:
        abi["saved_registers"] = saved
    return {key: abi[key] for key in sorted(abi) if key in ABI_KEYS}


def _normalise_convention(value):
    if value is None:
        return None
    if isinstance(value, bool):
        return None
    text = str(value).strip()
    if not text:
        return None
    lowered = text.lower()
    if lowered in ("unknown", "default", "none", "n/a", "null"):
        return None
    if lowered in ("__cdecl", "cdecl"):
        return "__cdecl"
    if lowered in ("__stdcall", "stdcall"):
        return "__stdcall"
    if lowered in ("__thiscall", "thiscall"):
        return "__thiscall"
    if lowered in ("__fastcall", "fastcall"):
        return "__fastcall"
    return None


def cross_validate(record, ghidra_calling_convention=None, ghidra_parameter_count=None,
                   persisted_abi=None):
    """Add agreement, demotion or a conflict. Never overwrite an inference.

    Precedence (spec 5.1): an external claim may only bump (capped at SUPPORTED),
    drop (floor INFERRED) or record a conflict. It may never set
    calling_convention, sret.present or receiver.present, and it can never
    promote an abstention. Ghidra silence is not agreement.

    **Our own abstention is not disagreement either.** That sentence used to
    exempt only the Ghidra arm's silence, while both arms treated
    ``inferred is None`` -- the engine having declined to name a convention --
    as a conflict against whatever the oracle said. A conflict is a record
    asserting the two sources *contradict* each other, and an abstention
    contradicts nothing: the engine never said the oracle was wrong, it said the
    listing cannot decide. The arms below are ordered the other way round, so a
    silence is recorded as the silence it is (``no_information``, which is what
    the field already says when no oracle answered) and no conflict is opened.
    Measured: this opened a false conflict on ``0x005a2320`` and would have
    opened one on all 25 ``no_terminal_ret`` targets -- every thunk and every
    tail-jump body, where the engine abstains by design.
    """
    ghidra = _normalise_convention(ghidra_calling_convention)
    persisted = None
    if isinstance(persisted_abi, dict):
        persisted = _normalise_convention(persisted_abi.get("calling_convention"))
    cross = record["cross_validation"]
    cross["ghidra_calling_convention"] = (
        str(ghidra_calling_convention) if ghidra_calling_convention is not None else None)
    if isinstance(ghidra_parameter_count, int) and not isinstance(
            ghidra_parameter_count, bool):
        cross["ghidra_parameter_count"] = ghidra_parameter_count
    cross["persisted_calling_convention"] = (
        str(persisted_abi.get("calling_convention"))
        if isinstance(persisted_abi, dict) and persisted_abi.get("calling_convention")
        is not None else None)
    conflicts = list(record.get("conflicts") or [])
    inferred = record["conventions"]["calling_convention"]
    conventions = record["conventions"]

    if ghidra is not None:
        if inferred is None:
            # An abstention against an external claim: recorded as the silence it
            # is. `cross["ghidra"]` keeps its "no_information" value, so the pack
            # shows an oracle that answered and an engine that declined.
            pass
        elif ghidra == inferred:
            cross["ghidra"] = "agrees"
            cross["agreement"] = True
            conventions["confidence"] = _bump(conventions["confidence"])
            conventions["corroboration"] = "ghidra_agrees"
        else:
            cross["ghidra"] = "disagrees"
            conventions["confidence"] = _drop(conventions["confidence"])
            conflicts.append({
                "kind": "inferred_vs_ghidra", "field": "calling_convention",
                "inferred": inferred, "ghidra": ghidra,
                "resolution_status": "unresolved",
            })
    if persisted is not None:
        if inferred is None:
            # As above: the same silence, for the same reason.
            pass
        elif persisted == inferred:
            cross["persisted"] = "agrees"
            if not cross["agreement"]:
                cross["agreement"] = True
            conventions["confidence"] = _bump(conventions["confidence"])
            if conventions["corroboration"] == "not_available":
                conventions["corroboration"] = "persisted_agrees"
        else:
            cross["persisted"] = "disagrees"
            conventions["confidence"] = _drop(conventions["confidence"])
            conflicts.append({
                "kind": "inferred_vs_persisted", "field": "calling_convention",
                "inferred": inferred, "persisted": persisted,
                "resolution_status": "unresolved",
            })
    if ghidra is not None and persisted is not None and ghidra != persisted:
        conflicts.append({
            "kind": "ghidra_vs_persisted", "field": "calling_convention",
            "ghidra": ghidra, "persisted": persisted,
            "resolution_status": "unresolved",
        })
    cleanup = record["cleanup"]
    if (isinstance(persisted_abi, dict)
            and isinstance(persisted_abi.get("stack_cleanup_bytes"), int)
            and not isinstance(persisted_abi.get("stack_cleanup_bytes"), bool)
            and isinstance(cleanup.get("bytes"), int)
            and persisted_abi["stack_cleanup_bytes"] != cleanup["bytes"]):
        conflicts.append({
            "kind": "inferred_vs_persisted", "field": "stack_cleanup_bytes",
            "inferred": cleanup["bytes"],
            "persisted": persisted_abi["stack_cleanup_bytes"],
            "resolution_status": "unresolved",
        })
        cleanup["confidence"] = _drop(cleanup["confidence"])
    if conflicts:
        # A conflict that changes nothing a consumer can read is not a
        # demotion, it is a footnote. The convention claim usually sits on its
        # INFERRED floor and `_drop` refuses to move an OBSERVED fact label, so
        # the affected cleanup claim -- the one machine fact a disagreement is
        # most often about -- is capped one rung below OBSERVED instead. Capping
        # downward can only make the record look *less* authoritative, never
        # more, and the value, the side and the citations are all untouched.
        cleanup["confidence"] = _weaker(cleanup["confidence"], "SUPPORTED")
    record["conflicts"] = conflicts
    return record, conflicts


def _sorted_deep(value):
    if isinstance(value, dict):
        return {key: _sorted_deep(value[key]) for key in sorted(value, key=str)}
    if isinstance(value, list):
        return [_sorted_deep(item) for item in value]
    return value


def finalize(record):
    """Sort every map, then hash the document with `content_sha256` set to null."""
    ordered = _sorted_deep(record)
    ordered["content_sha256"] = None
    ordered["content_sha256"] = sha256_json(ordered)
    return ordered


def _empty_record(image_base):
    return {
        "schema": SCHEMA,
        "verdict": "ABI_UNKNOWN",
        "completeness": "EMPTY",
        "target": {"va": None, "instructions": 0, "address_available": False,
                   "syntax": "intel", "image_base": _fmt_hex(image_base)},
        "parse": {"degraded": False, "unparsed": 0, "layout": "empty",
                  "local_extent": 0,
                  "frame": {"push_ebp": False, "push_ebp_at": None,
                            "mov_ebp_esp": False, "mov_ebp_esp_at": None,
                            "sub": None, "lea_esp": None, "and_esp": None,
                            "fp": False, "ebp_is_general_register": False},
                  "esp_unresolved": False, "flow_complete": True},
        "observations": [],
        "inferences": [],
        "abi": {},
        "conventions": {"calling_convention": None, "confidence": "UNKNOWN",
                        "candidate_conventions": list(CONVENTIONS),
                        "ambiguities": [], "corroboration": "not_available"},
        "receiver": {"present": False, "register": None, "confidence": "OBSERVED",
                     "shape": None, "offsets": [], "distinct_offsets": 0,
                     "max_offset": None, "written_through": 0, "bounds_only": True},
        "stack_arguments": {"observed_slots": 0, "derived_slots": 0, "gaps": 0,
                            "total_bytes": 0, "confidence": _DERIVED,
                            "not_complete": False, "widths_ambiguous": False,
                            "slots": []},
        "cleanup": {"side": None, "bytes": None, "confidence": "UNKNOWN",
                    "corroboration": "not_available", "evidence": None},
        "return": {"register": None, "register_class": "unknown",
                   "confidence": "UNKNOWN", "type": None, "void_possible": False,
                   "aggregate_evidence": {"bulk_write": False}},
        "sret": {"present": False, "slot": None, "confidence": _DERIVED,
                 "ambiguity": None, "candidates": None,
                 "hypothesis_confidence": None, "eax_holds_slot0_at_ret": None,
                 "basis": None, "this_interaction": None},
        "variadic": "UNKNOWN",
        "seh_or_cookie_frame": False,
        "dispatch": {"vtable_shaped_loads": 0, "indirect_calls": 0, "call_offsets": []},
        "tail_call": {"present": False, "target": None, "form": None,
                      "after_frame_setup": False},
        "abstained_because": [],
        "cross_validation": {"ghidra": "no_information", "persisted": "no_information",
                             "agreement": False, "ghidra_calling_convention": None,
                             "ghidra_parameter_count": None,
                             "persisted_calling_convention": None},
        "conflicts": [],
        "content_sha256": None,
    }


def analyze(disassembly, *, call_sites=(), ghidra_calling_convention=None,
            ghidra_parameter_count=None, persisted_abi=None, image_base=0x00400000,
            vftable_slots=(), tail_target_record=None):
    """Infer ABI facts from one function's disassembly. Pure; never raises.

    `disassembly` accepts a list of {"address", "instruction"} dicts, a dict
    with an "instructions" key, a list of raw listing lines, a raw listing
    string, or None/""/[] (a legal empty listing). Any other shape raises
    ValueError. `call_sites` is an optional tuple of caller fragments used only
    for the CL1 cleanup corroboration; the default reports
    corroboration "not_available" and changes nothing.

    `vftable_slots` and `tail_target_record` are the two evidence classes added
    by the 2026-09-28 extension, both keyword-only and both defaulting to the
    empty answer, so every call site written before them is unaffected and every
    record is byte-identical while the evidence is absent. They are inputs
    because the engine has no image and no other function's listing: membership
    in a vptr-backed vftable is proved by `tools/reconstruction_tooling/
    vftables.py` over the PE bytes, and a tail target's ABI has to be derived
    from *its* listing. Neither may be smuggled through `cross_validate`, whose
    documented precedence forbids an external claim from setting a convention.
    See `vftable_memberships` and `tail_target` for the accepted shapes.
    """
    try:
        image_base = int(image_base)
    except (TypeError, ValueError):
        image_base = 0x00400000
    try:
        insns, meta = parse_listing(disassembly)
        observations, state, frame = extract(insns, meta, image_base)
        _complete_observations(state, observations)
        state.observations = observations
        record = _infer_rules(observations, state, frame, meta, image_base,
                              vftable_slots, tail_target_record)
        record, _ = cross_validate(record, ghidra_calling_convention,
                                   ghidra_parameter_count, persisted_abi)
        _apply_caller_corroboration(record, state, call_sites)
        return finalize(record)
    except ValueError:
        raise
    except Exception as error:
        record = _empty_record(image_base)
        record["parse"]["internal_error"] = type(error).__name__
        record["abstained_because"] = [
            "empty_listing: no parseable instruction was supplied",
            "no_terminal_ret: function has no RET instruction",
        ]
        return finalize(record)


def _complete_observations(state, observations):
    for item in observations:
        if item["kind"] != "REG_READ":
            continue
        register = item["reg"]
        item["count"] = state.reg_read_counts.get(register, 1)
        write = state.reg_writes.get(register)
        item["first_write_index"] = write["index"] if write else None


def _apply_caller_corroboration(record, state, call_sites):
    cleanup = record["cleanup"]
    if not call_sites:
        return
    adjusted = None
    for site in call_sites:
        if not isinstance(site, dict):
            continue
        after = site.get("after")
        if not isinstance(after, list):
            continue
        total = 0
        matched = False
        for line in after[:6]:
            parsed = parse_insn(str(line))
            operands = parsed["operands"]
            if parsed["base"] == "ADD" and len(operands) == 2 \
                    and _operand_reg(operands[0]) == "ESP" \
                    and isinstance(operands[1].get("value"), int):
                total += operands[1]["value"]
                matched = True
            elif parsed["base"] == "POP" and operands:
                total += 4
                matched = True
        if matched:
            adjusted = total if adjusted is None else min(adjusted, total)
    if adjusted is None:
        return
    if cleanup["side"] == "caller" and adjusted > 0:
        cleanup["corroboration"] = "caller_side_cleanup_confirmed"
    elif cleanup["side"] == "callee" and adjusted == 0 \
            and isinstance(cleanup["bytes"], int) and cleanup["bytes"] > 0:
        cleanup["corroboration"] = "caller_side_cleanup_absent"
        cleanup["confidence"] = _bump(cleanup["confidence"])
    else:
        cleanup["corroboration"] = "caller_side_cleanup_inconclusive"
