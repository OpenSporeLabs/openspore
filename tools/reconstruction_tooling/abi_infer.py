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

CALLEE_SAVED = ("EBX", "EBP", "EDI", "ESI")

# `ret imm16` is the only return-with-pop form x86-32 encodes, so a terminal
# immediate outside this range is not a possible stack pop at all.
MAX_RET_IMMEDIATE = 0xFFFF

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
    "FUCOMI", "FUCOMIP", "FLDCW", "FNSTCW", "FSTCW", "FNCLEX", "FNINIT", "FWAIT",
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
BRANCH_MNEM = frozenset((
    "JA", "JAE", "JB", "JBE", "JECXZ", "JE", "JG", "JGE", "JL", "JLE", "JNE",
    "JNO", "JNP", "JNS", "JNZ", "JO", "JP", "JPE", "JPO", "JRCXZ", "JS", "JZ",
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
                if not in_listing:
                    observation = emit(insn, "UNCOND_TRANSFER_OUT", target=_fmt_hex(target))
                    state.transfer_out.append({"obs": observation, "target": target,
                                               "index": index})
                    state.exits.append({"form": "jmp_out", "index": index,
                                        "target": target, "obs": observation})
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


def infer(observations, state=None, frame=None, meta=None, image_base=0x00400000):
    """Stage 2: the rule set, the only place a `confidence` field is produced.

    Called as `infer(disassembly)` it is the whole inference without
    cross-validation, which is how the test plan's fixture generators drive it;
    called with the full `(observations, state, frame, meta)` tuple it is the
    bare second stage, as the specification's module layout describes.
    """
    if state is None or frame is None or meta is None:
        return analyze(observations, image_base=image_base)
    return _infer_rules(observations, state, frame, meta, image_base)


def _infer_rules(observations, state, frame, meta, image_base=0x00400000):
    abstained = []
    inferences = []
    seen_codes = set()

    def abstain(code, detail):
        if code not in ABSTENTION_CODES:
            raise AssertionError("unregistered abstention code %r" % code)
        entry = "%s: %s" % (code, detail)
        if entry in seen_codes:
            return
        seen_codes.add(entry)
        abstained.append(entry)

    def infer_rule(rule, claim, confidence, based_on, value=None):
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
    if receiver["present"] is True:
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
    if tail["present"] and not has_ret:
        conventions["calling_convention"] = None
        conventions["confidence"] = "UNKNOWN"
        conventions["ambiguities"] = list(conventions["ambiguities"]) + ["tail_call"]
        not_complete = True
        stack_arguments["not_complete"] = True
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
            cross["ghidra"] = "disagrees"
            conflicts.append({
                "kind": "inferred_vs_ghidra", "field": "calling_convention",
                "inferred": None, "ghidra": ghidra,
                "resolution_status": "unresolved",
            })
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
            cross["persisted"] = "disagrees"
            conflicts.append({
                "kind": "inferred_vs_persisted", "field": "calling_convention",
                "inferred": None, "persisted": persisted,
                "resolution_status": "unresolved",
            })
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
            ghidra_parameter_count=None, persisted_abi=None, image_base=0x00400000):
    """Infer ABI facts from one function's disassembly. Pure; never raises.

    `disassembly` accepts a list of {"address", "instruction"} dicts, a dict
    with an "instructions" key, a list of raw listing lines, a raw listing
    string, or None/""/[] (a legal empty listing). Any other shape raises
    ValueError. `call_sites` is an optional tuple of caller fragments used only
    for the CL1 cleanup corroboration; the default reports
    corroboration "not_available" and changes nothing.
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
        record = _infer_rules(observations, state, frame, meta, image_base)
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
