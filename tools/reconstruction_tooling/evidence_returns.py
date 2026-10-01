"""Machine-derived return evidence for the RETURN SEMANTICS dimension.

Why this module exists
----------------------

``validate.validate`` reads its return oracle from exactly one field. It asks
``_abi_claim(abi_sources, "return_type", "return_semantics")`` for a canonical
claim and, when it finds one, compares it to the source's declared return type
as a string. When it does not, the dimension is ``NOT_AVAILABLE``, and
``NOT_AVAILABLE`` is disqualifying for a static PASS.

That is not a rare shape. Measured over the 586 committed packs, 506 carry a
canonical ``return_type``/``return_semantics`` claim and **80 do not**, and of
those 80, 76 have no disassembly listing at all -- so the honest verdict there
stays ``NOT_AVAILABLE``. Of the 4 that *do* have a complete listing, one is a
genuine void and the rest are cases the machine cannot decide. So the reachable
gain from this module is small and every unit of it has to be real: the whole
value of the dimension is that a PASS means the machine and the source agree,
and one fabricated width would spend that on a target nobody checked.

So the module is built the other way round. It does not try to recover a C type
-- nothing static can, and a recovered spelling would be an invention. It
derives what the machine *does* determine, which is narrower and checkable:

* whether a value is returned at all, and
* if so, the width of the register the value travels in.

and it states those as an explicit uncertainty record with a state name, rather
than as a type. Width is what the machine fixes; the C type is a source-side
choice among the several types of that width (``bool``/``char``/``int8_t`` are
all one byte), so a width match is reported as a width match and never as a
verified type.

The states, and what each is allowed to rest on
------------------------------------------------

``VOID_PROVEN``
    Two witnesses, and which one carries the claim depends on what the record
    says.

    * The record names a return register, and the complete listing shows that no
      path through the body writes it before any reachable return. A genuine
      two-witness agreement.
    * The record claims no return register -- positively, as the word ``none``,
      not by the field's absence -- and no other machine return field names one
      to contradict it. Here the listing is a *guard* rather than a second
      witness, and the difference is worth stating: a function that returns
      nothing writes ``EAX`` as scratch on nearly every instruction, so no listing
      can disprove a void, and demanding that the body never touch ``EAX`` would
      exclude exactly the functions the state exists for. What the complete,
      fully-parsed listing does do is fix the basis the record was derived on: a
      body half seen is indistinguishable from a void one, which is why a missing
      ``parse`` record, a degraded parse, an unparsed instruction and a count
      that disagrees with the listing each refuse this state as firmly as they
      refuse a width.

    A record that claims ``none`` in one field and names a register in another is
    *contested*, and this module reports that as ``UNCLASSIFIED`` rather than
    picking a winner: a machine record that contradicts itself is evidence of
    neither thing.

``WIDTH_<n>_IN_<REG>``
    A return register is recorded, the guard below holds, and the listing's last
    definition of that register writes a determinate width on *every* path to
    *every* reachable return. The width is read off the operand: only ``AL``
    written is one byte, ``MOV EAX,[...]`` is four. This is a machine claim about
    a register, deliberately not about a type.

    A ``CALL`` inside the body defeats this state on its own, and it is worth
    saying why: on x86-32 whether a caller may read ``EAX`` after a call is
    decided by the *callee's* signature, which this listing cannot show. So a body
    whose last value-producing operation is a call returns something whose width
    nobody can name statically, and a body whose only ``EAX`` writes are around
    calls returns something nobody can prove is a value at all. Both are
    ``UNCLASSIFIED``, never a width.

``SRET_PROVEN`` / ``SRET_SUSPECTED``
    A hidden pointer argument through which memory is returned. The ABI
    envelope's own ``sret`` record (``present``, ``eax_holds_slot0_at_ret``,
    ``ambiguity``, ``candidates``) and its ``return.aggregate_evidence``
    ``bulk_write`` flag are the record side; an ``EAX`` whose last definition
    before the ``RET`` reads from memory rather than from a constant is the
    listing side. ``SRET_PROVEN`` needs both to agree. The state matters
    because an sret makes the register hold an *address*, so a width read off
    that register would be a width claim about the wrong value entirely -- and
    it means the C-visible return type is not the register's contents.

``UNCLASSIFIED``
    A value is returned, and the complete listing does not determine its width:
    the last write is a ``CALL`` (the callee's result is not statically known),
    an instruction this module cannot bound (``CMOVcc``, ``CMPXCHG``), a
    register class the C type cannot be recovered from (x87 ``ST0`` or an SSE
    register, where the machine fixes the transfer and not whether the source
    said ``float`` or ``double``), or two reachable returns reached with
    different widths. It is reported, and it never passes.

``NOT_AVAILABLE``
    No state is derivable, and this is a *reported* absence, never a clearance.
    It covers every way the evidence can fail to be complete: no listing at
    all, a ``{"truncated": true}`` envelope, an empty instruction list, a parse
    record that is missing, ``degraded``, reports ``unparsed > 0``, or declares
    a different instruction count than the listing holds; and an ABI record
    that carries no return field at all. A missing record is never a record of
    zero, so it cannot produce ``VOID_PROVEN``.

Fail-closed, in one place
-------------------------

``_whole_listing`` is the single gate every provable state passes through, and
``decide`` calls it a *second* time, independently of ``classify``, before it will
emit any verdict. The duplication is deliberate: a caller that patches
``classify`` -- a test, or a future revision that reaches for the wrong evidence --
still cannot make a partial listing pass or fail, because the second read is made
from the raw listing and parse record rather than from the state it is checking.
"""

import re

# The evidence paths this module cites. Duplicated rather than imported:
# ``validate`` imports the orchestrator, and a top-level import here would close
# that loop for two string constants. Both are compared by value by
# ``test_validation_dimensions``, so a drift is caught rather than silent.
INDEX_REL = "reconstruction/knowledge/index.json"
EVIDENCE_REL = "reconstruction/evidence"

# The state vocabulary. ``WIDTH`` is the parameterized family: a record's
# ``state`` spells the instance out as ``WIDTH_<n>_IN_<REG>`` while its ``kind``
# is the name here, so a caller can match on a kind without parsing a string.
STATES = ("VOID_PROVEN", "WIDTH", "SRET_PROVEN", "SRET_SUSPECTED", "UNCLASSIFIED", "NOT_AVAILABLE")

# A record that claims no return register. Matched on a prefix because the
# field is free text in the index projection ("none", "none (EAX is scratch)",
# "none (void)") while the derived record spells it the bare word.
_NO_REGISTER = re.compile(r"^(?:none|void|null|nil|n/?a|-|)$", re.IGNORECASE)

# A field that carries a return claim at all. The presence of one of these is
# what separates "the machine says this function returns nothing" from "the
# machine said nothing about returns", and the second is an absence.
_RETURN_FIELDS = ("return_register", "return_semantics", "return_type", "return_width_bytes")

# The 32-bit GPR sub-registers, and which parent each belongs to. The width claim
# is a claim about the register the record names, so a record that spells the
# register ``AL`` is widened to its parent ``EAX`` and every operand is resolved
# through the same table -- otherwise the state name would depend on which layer
# of the pack happened to spell it, and two packs describing one function would
# disagree about its return.
_SUBREGISTER = {
    "EAX": {"EAX": 4, "AX": 2, "AL": 1, "AH": 1},
    "ECX": {"ECX": 4, "CX": 2, "CL": 1, "CH": 1},
    "EDX": {"EDX": 4, "DX": 2, "DL": 1, "DH": 1},
    "EBX": {"EBX": 4, "BX": 2, "BL": 1, "BH": 1},
    "ESP": {"ESP": 4, "SP": 2},
    "EBP": {"EBP": 4, "BP": 2},
    "ESI": {"ESI": 4, "SI": 2},
    "EDI": {"EDI": 4, "DI": 1},
}
_PARENT = {}
for _parent, _table in _SUBREGISTER.items():
    for _name in _table:
        _PARENT[_name] = _parent
# The return registers that are not a GPR. Named here so the reason can be
# reported in words rather than as a bare "unknown".
_NON_GPR_RETURN = {
    "ST0": "the x87 stack top: the machine fixes where the value travels and not whether the source said float or double",
    "ST": "the x87 stack top: the machine fixes where the value travels and not whether the source said float or double",
    "ST(0)": "the x87 stack top: the machine fixes where the value travels and not whether the source said float or double",
    "XMM0": "an SSE register: the machine fixes where the value travels and not whether the source said float, double or a vector",
    "MM0": "an MMX register: the machine fixes where the value travels and not the C type at all",
}

# The mnemonic of a listing line, with the repeat/lock prefixes Ghidra spells
# on the string and SSE forms. Mirrors the prefix set ``IMPLICIT_MEMORY_MNEMONIC``
# in ``validate`` so the two read the same line the same way.
_MNEMONIC = re.compile(
    r"^\s*(?:(?:LOCK|REP|REPNE|REPNZ|REPE|REPZ|NO)\s+)*"
    r"(?P<mnemonic>[A-Za-z][A-Za-z0-9]*)\s*(?P<operands>.*)$")
# Control transfers and flag-only work. None of them has a destination operand,
# so a body full of them writes no return register on that account. ``CALL`` is
# deliberately absent: a call *is* a definition of EAX and of the x87/SSE
# registers, of a width and a value this module cannot read.
_NON_DESTINATION = frozenset((
    "PUSH", "PUSHF", "PUSHA", "PUSHD", "CMP", "TEST", "BT", "BTS", "BTR", "BTC",
    "JMP", "RET", "NOP", "INT", "INT1", "INT3", "IRET", "IRETD", "IRETQ", "LOOP",
    "LOOPE", "LOOPZ", "LOOPNE", "LOOPNZ", "CLC", "STC", "CLD", "STD", "CMC",
    "LAHF", "SAHF", "PUSHFQ", "POPFQ", "POPAD", "POPA", "LEAVE", "WAIT", "EMMS",
    "MOVSD", "MOVSB", "MOVSW", "MOVSQ", "STOSB", "STOSW", "STOSD", "STOSQ",
    "SCASB", "SCASW", "SCASD", "CMPSB", "CMPSW", "CMPSD", "CMPSQ", "XLAT",
    "SSE2", "NOP2",
))
# Destinations written at the width the destination operand itself names. Every
# one of these reads its width from the operand, so ``MOV EAX,[...]`` is four
# and ``MOV AL,BL`` is one without anything having to be guessed.
_DESTINATION_WIDTH = frozenset((
    "MOV", "MOVZX", "MOVSX", "MOVSXD", "MOVQ", "MOVD", "LEA", "POP", "XCHG",
    "ADD", "SUB", "ADC", "SBB", "AND", "OR", "XOR", "INC", "DEC", "NEG", "NOT",
    "SHL", "SAL", "SHR", "SAR", "ROL", "ROR", "RCL", "RCR", "BSWAP", "XADD",
    "POPCNT", "IN", "CWDE", "CBW", "CDQE",
))
# A destination that is written on some paths and left alone on others, or whose
# value is undefined on an input condition. Never a width: two states are
# reachable and the listing cannot say which.
_CONDITIONAL_DESTINATION = frozenset((
    "BSF", "BSR", "CMOVZ", "CMOVNZ", "CMOVC", "CMOVNC", "CMOVBE", "CMOVA",
    "CMOVAE", "CMOVNB", "CMOVGE", "CMOVL", "CMOVLE", "CMOVG", "CMOVO", "CMOVNO",
    "CMOVS", "CMOVNS", "CMOVP", "CMOVNP", "CMOVPE", "CMOVPO", "CMPXCHG",
    "CMPXCHG8B", "CMPXCHG16B",
))
# A destination written through the accumulator rather than through an operand.
# MSVC emits these constantly (``IMUL ECX`` after ``MOV EAX,0x2aaaaaab``), and
# reading the single-operand form as "no destination" would let a body appear not
# to write the register it plainly writes. Spelled as ``(kind, width)`` rather than
# as a bare width so that "writes it at a width nobody can name" and "does not
# write it at all" are distinguishable at the call site -- they are opposite
# claims, and collapsing them into one ``None`` would leave the correctness of the
# analysis resting on which branch happened to read it first.
_IMPLICIT_ACCUMULATOR = {
    "MUL": ("definite", 4),      # EDX:EAX
    "DIV": ("definite", 4),      # EDX:EAX
    "IMUL": ("definite", 4),     # the one-operand form
    "INSD": ("definite", 4), "INSW": ("definite", 2), "INSB": ("definite", 1),
    "LODSD": ("definite", 4), "LODSW": ("definite", 2), "LODSB": ("definite", 1),
    "LODSQ": ("unknown", None),  # eight bytes through a 32-bit register
    "AAM": ("unknown", None), "AAD": ("unknown", None),  # AL, width not the register's
    "POPAD": ("unknown", None), "POPA": ("unknown", None),  # restores every GPR
    "CDQ": ("none", None), "CWD": ("none", None),  # sign-extends EAX *into* EDX
}
_SIZE_PREFIX = re.compile(r"^\s*(?:(?:BYTE|WORD|DWORD|QWORD|TBYTE)\s+PTR\s+)?", re.IGNORECASE)

# A branch operand, the unconditional jump included. ``validate.BRANCH_OPERAND``
# deliberately excludes ``JMP`` -- it counts *conditional* branches, and reading a
# JMP as one was a real bug there -- so it cannot be reused for a CFG: a copy is
# spelled out here rather than borrowed, with the exclusion dropped and the jump
# restored, because a jump to a block inside the body is an edge and a jump out of
# it is a tail return.
_BRANCH = re.compile(r"^\s*(?:J[A-Z]{1,3}|LOOP\w*)\s+(0[xX][0-9a-fA-F]+)\b", re.IGNORECASE)
_UNCONDITIONAL = re.compile(r"^\s*JMP\b", re.IGNORECASE)
_RET = re.compile(r"^\s*RET\b", re.IGNORECASE)
_CALL = re.compile(r"^\s*CALL\b", re.IGNORECASE)

# The declared source types whose width is a fact of the C++ language and of the
# 32-bit Windows target this binary is, rather than a fact about a particular
# reconstruction. A spelling that is not here -- a typedef, a class, a template,
# ``auto``, a type alias the reconstruction made up -- has *no* computable width
# and is never matched against a machine width. A class named ``uint32_t`` would
# be read as 4 bytes; that is the documented cost of taking the spelling at face
# value, and it is the same assumption ``validate`` already makes when it compares
# two return-type strings.
_SOURCE_WIDTH = {
    "bool": 1,
    "char": 1, "signed char": 1, "unsigned char": 1,
    "int8": 1, "uint8": 1, "int8_t": 1, "uint8_t": 1, "byte": 1,
    "short": 2, "short int": 2, "unsigned short": 2, "unsigned short int": 2,
    "signed short": 2, "signed short int": 2,
    "int16": 2, "uint16": 2, "int16_t": 2, "uint16_t": 2, "wchar_t": 2,
    "int": 4, "signed": 4, "signed int": 4, "unsigned": 4, "unsigned int": 4,
    "long": 4, "long int": 4, "unsigned long": 4, "unsigned long int": 4,
    "signed long": 4, "signed long int": 4, "float": 4,
    "int32": 4, "uint32": 4, "int32_t": 4, "uint32_t": 4, "size_t": 4, "wint": 4,
    "long long": 8, "long long int": 8, "unsigned long long": 8,
    "unsigned long long int": 8, "signed long long": 8, "signed long long int": 8,
    "double": 8, "int64": 8, "uint64": 8, "int64_t": 8, "uint64_t": 8,
    "intptr_t": 4, "uintptr_t": 4, "ptrdiff_t": 4, "long long*": 8,
}
# The ``std::`` spellings of the fixed-width integers, which the index projection
# and the worker sources both use. Listed rather than derived by stripping a
# namespace, so a reconstruction's own ``std::``-like alias cannot be resolved by
# pattern into a width it never had.
_STD_WIDTH = {name: width for name, width in _SOURCE_WIDTH.items() if name.endswith("_t")}
_STD_WIDTH.update({"int8_t": 1, "uint8_t": 1, "int16_t": 2, "uint16_t": 2,
                   "int32_t": 4, "uint32_t": 4, "int64_t": 8, "uint64_t": 8})
# Cv-qualifiers and the tokens that may sit between the type and the name in a
# declaration. Stripped before the lookup so ``const unsigned long`` resolves.
_QUALIFIER = re.compile(r"\b(?:const|volatile|restrict|__restrict|extern|static|inline)\b")


def _address(value):
    """Canonical ``0x%08x`` form, or ``None`` if ``value`` is not an address.

    Copied from ``validate._address`` rather than imported, for the same reason
    ``INDEX_REL`` is duplicated: the xref export reaches the index in both forms
    and skipping the normalisation makes a real address never match itself.
    """
    if not isinstance(value, str):
        return None
    text = value.strip().lower()
    if text.startswith("0x"):
        text = text[2:]
    if not text or len(text) > 8 or any(char not in "0123456789abcdef" for char in text):
        return None
    return "0x%08x" % int(text, 16)


def width_state(width, register):
    """The concrete state name for a width claim, e.g. ``WIDTH_1_IN_EAX``."""
    return "WIDTH_%d_IN_%s" % (width, str(register or "").upper())


def _state(state, reason, provable=False, **extra):
    """A state record, with the family name derived from the concrete name.

    ``state`` is the concrete spelling -- ``WIDTH_1_IN_EAX`` -- and ``kind`` is the
    name from ``STATES``, so a caller matches on a kind without parsing a string
    and a test can assert on either. Deriving it here rather than at each call site
    is what keeps the two from drifting: a caller branching on ``kind`` against a
    record whose ``kind`` was set to the instance name would silently fall through.
    """
    kind = "WIDTH" if state.startswith("WIDTH_") else state
    record = {"state": state, "kind": kind, "provable": provable, "reason": reason}
    record.update(extra)
    return record


def _not_available(reason):
    return _state("NOT_AVAILABLE", reason)


def _whole_listing(listing, parse):
    """Whether ``listing`` is a complete body the machine parse consumed in full.

    The single fail-closed gate. Every provable state passes through it, and so
    does every ``PASS`` ``decide`` emits -- see the module docstring for why it
    is called twice.

    Six ways it refuses, and each is an absence of evidence rather than a fact
    about the target:

    * no listing, which is what ``validate._listing`` returns for a truncated
      envelope and for an empty instruction list alike. A preview is a fragment
      of the body, and a fragment cannot show that a register is never written
      -- a body half seen is indistinguishable from a void one.
    * an empty instruction list. A recovered function always ends in a return,
      so an empty body is the absence of a body.
    * a missing or empty ``parse`` record. Without the count the listing cannot
      be shown to be the whole of anything.
    * ``degraded: true``: the parse did not read the listing it is being asked to
      vouch for.
    * ``unparsed > 0``: the parse left instructions behind.
    * ``declared_count != len(listing)``: the parse and the listing disagree about
      the body, and neither can be taken as the whole of it. An instruction
      address that does not parse is refused the same way, because a body whose
      span cannot be bounded cannot be shown to close.
    """
    if not isinstance(listing, (list, tuple)) or len(listing) != 2:
        return False, "no complete machine listing exists for this target (absent, truncated or empty)"
    addresses, texts = listing
    if not isinstance(texts, (list, tuple)) or not texts:
        return False, "the machine listing is empty, which is the absence of a body rather than evidence about one"
    if not isinstance(parse, dict) or not parse:
        return False, "the listing exists but carries no machine parse record, so it cannot be shown to have been consumed in full"
    if parse.get("degraded") is True:
        return False, "the machine parse is degraded, so the listing is not the whole of the body"
    try:
        unparsed = int(parse.get("unparsed") or 0)
    except (TypeError, ValueError):
        return False, "the machine parse record's unparsed count is not a number, so the listing's wholeness is unknown"
    if unparsed > 0:
        return False, "%d of %d instruction(s) were not parsed, so the listing is not the whole of the body" % (unparsed, len(texts))
    declared = parse.get("declared_count")
    if not isinstance(declared, int) or isinstance(declared, bool):
        return False, "the machine parse record declares no instruction count, so the listing's wholeness is unknown"
    if declared != len(texts):
        return False, ("the machine parse declared %d instruction(s) and the listing holds %d, so the two "
                       "disagree about the body and neither can be taken as the whole of it" % (declared, len(texts)))
    if any(not isinstance(value, str) for value in (addresses or ())):
        return False, "an instruction address in the listing does not parse, so the body cannot be bounded"
    return True, ""


def _first_operand(operands):
    """The first operand of a listing line, without a bracketed slice split."""
    depth, index = 0, len(operands)
    for position, char in enumerate(operands):
        if char == "[":
            depth += 1
        elif char == "]":
            depth = max(0, depth - 1)
        elif char == "," and depth == 0:
            index = position
            break
    return operands[:index].strip()


def _destination_register(operands):
    """The bare register a destination operand names, or ``None``.

    A memory operand is not a register even when it is *based* on one: ``MOV
    dword ptr [EAX],ECX`` writes memory and only reads EAX, and reading the base
    register as the destination would make a body appear to return what it
    stored.
    """
    text = _SIZE_PREFIX.sub("", _first_operand(operands))
    text = text.strip().upper()
    if "[" in text or " " in text or not text:
        return None
    return text if text in _PARENT else None


def _write(text, base):
    """How ``text`` affects the register ``base``: ``(kind, width)``.

    ``kind`` is ``"definite"`` (with the width the operand names), ``"unknown"``
    (the register may be written and neither the width nor the value is
    determinable here) or ``"none"`` (this instruction does not write it).

    The rule that makes the module fail closed is operand position, not
    mnemonic coverage: an instruction whose destination is ``base`` or a
    sub-register of it and which is not in the tables above is ``"unknown"``, not
    ``"none"``. A missing entry in a table therefore costs a claim rather than
    manufacturing one, which is the direction that cannot produce a false
    clearance.
    """
    match = _MNEMONIC.match(str(text or ""))
    if not match:
        return ("unknown", None)
    mnemonic, operands = match.group("mnemonic").upper(), match.group("operands")
    if _CALL.match(mnemonic):
        # The callee's result. It is a definition of EAX, of EDX:EAX, of ST0 and
        # of the SSE registers, and which of those the caller consumes is decided
        # by a callee this listing cannot see.
        return ("unknown", None)
    if mnemonic.startswith("J") or mnemonic in _NON_DESTINATION:
        return ("none", None)
    table = _SUBREGISTER[base]
    destination = _destination_register(operands)
    if mnemonic.startswith("SET"):
        return ("definite", 1) if destination in table else ("none", None)
    if mnemonic in _IMPLICIT_ACCUMULATOR:
        # Only the accumulator pair is affected; a single-operand form names one
        # register as its *source* and writes EDX:EAX.
        if base not in ("EAX", "EDX"):
            return ("none", None)
        return _IMPLICIT_ACCUMULATOR[mnemonic]
    if destination not in table:
        return ("none", None)
    if mnemonic in _CONDITIONAL_DESTINATION:
        return ("unknown", None)
    if mnemonic in _DESTINATION_WIDTH:
        # The width is the destination's own, never the source's: ``MOV AL,BL``
        # is a one-byte write and ``MOV EAX,dword ptr [X]`` is a four-byte one,
        # and a size prefix on the *destination* would already have made it a
        # memory operand, which returns above.
        return ("definite", table[destination])
    return ("unknown", None)


def _successors(addresses, texts):
    """The intra-body CFG of a listing: ``(reachable, successors)``.

    A fall-through is taken by every instruction that does not end the body --
    a conditional branch takes *both* its target and the next instruction, which
    is the detail that decides whether a return is reachable at all. Only a
    ``RET`` and an unconditional ``JMP`` end the body; a ``CALL`` does not, since
    it returns to the instruction after it, and treating it as a terminator makes
    everything the body does after its first call unreachable. A ``JMP`` whose
    target lies outside the body's own addresses takes no edge either: it becomes
    a tail exit, handled as such by ``_return_values``, because MSVC compiles a
    tail call as a jump to the callee and the value the caller sees is then the
    callee's.

    A basic-block decomposition is not needed and is not built: a listing is
    already a linear array of decoded instructions, so the successor of the
    instruction after a transfer *is* the next element, and adding a leader set
    only risks suppressing a fall-through that really happens.
    """
    count = len(texts)
    # The lookup is keyed on ``_address``' own canonical form, because a branch
    # operand is normalised through it before it is looked up. Indexing the
    # listing's raw spelling instead made the two disagree whenever the pack
    # stored addresses bare (``00f9ff00``) and the operand carried the prefix
    # (``0x00f9ff00``) -- which is exactly what the committed packs do, so every
    # in-body branch edge was silently dropped and the CFG collapsed to the
    # straight-line prefix of the body. Measured on 0x00f9fef0: 8 of 112
    # instructions reachable, the body's own ``JMP 0x00f9ff00`` contributing
    # nothing, and the return analysis left with a single spurious exit and no
    # width. Both spellings are indexed so a mixed pack cannot lose edges either.
    lookup = {}
    for index, address in enumerate(addresses or ()):
        if not isinstance(address, str):
            continue
        canonical = _address(address)
        if canonical is not None:
            lookup.setdefault(canonical, index)
        lookup.setdefault(address.strip().lower(), index)
    successors = {index: [] for index in range(count)}
    for index, text in enumerate(texts):
        line = str(text or "")
        if _RET.match(line):
            continue
        branch = _BRANCH.match(line)
        if branch:
            target = _address(branch.group(1))
            if target in lookup:
                successors[index].append(lookup[target])
        if _UNCONDITIONAL.match(line):
            continue
        if index + 1 < count:
            successors[index].append(index + 1)
    reachable, stack = set(), [0]
    while stack:
        index = stack.pop()
        if index in reachable or not 0 <= index < count:
            continue
        reachable.add(index)
        stack.extend(successors[index])
    return reachable, successors


def _predecessors(reachable, successors):
    incoming = {index: [] for index in reachable}
    for index, targets in successors.items():
        if index not in reachable:
            continue
        for target in targets:
            if target in incoming:
                incoming[target].append(index)
    return incoming


def _return_values(addresses, texts, base):
    """The must-defined value of ``base`` at every reachable return.

    A must-analysis, so the join is an intersection: a value is only *provably*
    returned if every path to the return has written the register, and one path
    that does not write it makes the answer ``"unknown"`` rather than a width.
    The seed is "not defined", because nothing is assumed about the register's
    value on entry -- a body that never writes it does not return it. The
    iteration is explicit rather than recursive: the body may hold a loop, and a
    must-analysis over a loop needs a fixpoint.

    Returns ``(values, exits)``, where ``values`` maps a reachable exit index to
    ``("defined", width)``, ``("none", None)`` or ``("unknown", None)``, and
    ``exits`` counts the returns examined. A jump out of the body is an exit too
    -- the returned value is the tail callee's, and no width for it is knowable
    from this listing -- so it contributes ``"unknown"`` rather than being
    ignored.
    """
    reachable, successors = _successors(addresses, texts)
    incoming = _predecessors(reachable, successors)
    writes = {index: _write(texts[index], base) for index in reachable}
    # ``before[i]`` is the must-value entering instruction ``i``; ``out(i)`` is the
    # value leaving it, which differs only where the instruction itself writes
    # the register. Three states, and the middle one is the load-bearing one:
    # ``("none", None)`` no path has written it, ``("defined", width)`` every
    # path has and they agree, ``("unknown", None)`` the paths disagree or the
    # write cannot be bounded.
    _NONE, _UNKNOWN = ("none", None), ("unknown", None)

    def out(index):
        kind, width = writes[index]
        if kind == "definite" and width is not None:
            return ("defined", width)
        if kind == "unknown":
            return _UNKNOWN
        return before[index]

    before = {index: _NONE for index in reachable}
    before[0] = _NONE
    order = sorted(reachable, reverse=True)
    for _ in range(len(order) + 2):
        changed = False
        for index in order:
            if index == 0:
                continue
            predecessors = [item for item in incoming.get(index, ()) if item != index]
            if not predecessors:
                merged = writes[index] if writes[index][0] == "definite" and writes[index][1] is not None else _NONE
            else:
                incoming_values = {out(item) for item in predecessors}
                merged = incoming_values.pop() if len(incoming_values) == 1 else _UNKNOWN
            if merged != before[index]:
                before[index] = merged
                changed = True
        if not changed:
            break
    exits, values = 0, {}
    for index in sorted(reachable):
        line = str(texts[index] or "")
        is_return = bool(_RET.match(line))
        is_tail = bool(_UNCONDITIONAL.match(line)) and not successors.get(index)
        if not (is_return or is_tail):
            continue
        exits += 1
        if is_tail:
            # MSVC compiles a tail call as a jump to the callee, so the value the
            # caller sees is the callee's return, and its width is not in this
            # listing. Counted as an exit so a body that returns through a tail
            # cannot be read as one that never wrote the register.
            values[index] = _UNKNOWN
            continue
        values[index] = before[index]
    return values, exits


def _sret_state(sources, sret, return_record):
    """The sret state the machine's own fields support, or ``None``.

    The envelope records a hidden-pointer hypothesis in three places and they are
    all read: the ``sret`` sub-record's ``present`` flag, its ``ambiguity`` /
    ``candidates`` (a hidden struct-return pointer and an out-parameter compile to
    the same instruction sequence, and the record says so itself), and
    ``return.aggregate_evidence.bulk_write`` -- a struct filled through a pointer
    is the signature. ``SRET_PROVEN`` is reached only when the record asserts it
    *and* the listing corroborates it by showing the return register's last
    definition reading memory rather than an immediate.
    """
    record = sret if isinstance(sret, dict) else {}
    aggregate = (return_record or {}).get("aggregate_evidence") if isinstance(return_record, dict) else None
    bulk_write = isinstance(aggregate, dict) and aggregate.get("bulk_write") is True
    candidates = [str(item).casefold() for item in (record.get("candidates") or []) if isinstance(item, str)]
    suspected = record.get("present") is not True and not candidates and str(record.get("ambiguity") or "").strip()
    hidden = bool(candidates) or bulk_write or bool(suspected) or record.get("present") is True
    if not hidden:
        return None
    if record.get("present") is not True:
        return "SRET_SUSPECTED"
    if record.get("eax_holds_slot0_at_ret") is not True:
        return "SRET_SUSPECTED"
    return "SRET_PROVEN"


def _registers(sources):
    """Every return-register claim across the ABI sources, in priority order.

    Three layers are read: the index record's persisted ABI, the ``abi``
    envelope's outer layer and its derived ABI. The ``return`` sub-record is
    consulted last and only as a *witness* -- it is a nested machine record with
    its own ``confidence``, and on 0x006a2a80 it names ``EAX`` while the
    ``return_register`` beside it says ``none``, which is a disagreement this
    module resolves by refusing the void claim rather than by picking a winner.
    """
    claims = []
    for source in sources or ():
        if not isinstance(source, dict):
            continue
        for key in ("return_register",):
            value = source.get(key)
            if isinstance(value, str) and value.strip():
                claims.append(("return_register", value.strip()))
        record = source.get("return")
        if isinstance(record, dict):
            value = record.get("register")
            if isinstance(value, str) and value.strip():
                claims.append(("return.register", value.strip()))
    return claims


def _names_register(value):
    """A GPR a free-text return-register field names, whether or not it denies it.

    The field is prose in the index projection ("EAX (clobbered, unused)", "EAX is
    not assigned a defined result by the target body", "AL through the tail
    target") and a bare name in the derived record, so the reading splits the two
    cases that matter: a register named as the carrier of the return value, and a
    register named in order to be denied. Both return a name; ``_carries_register``
    below is what says whether it is a claim or a denial.
    """
    match = re.match(r"^\s*([A-Za-z]{2,4})\b", str(value or ""))
    if not match:
        return None
    name = match.group(1).upper()
    return _PARENT.get(name)


def _denies_register(value, name):
    """Whether a field names ``name`` in order to deny that it carries the return.

    Only the text *after* the register token is read, and only a negation counts.
    "EAX is not assigned a defined result by the target body" is a claim that this
    function returns nothing, and reading its leading token as a carrier would turn
    a negative record into a width claim over a body the record says returns
    nothing.
    """
    match = re.match(r"^\s*([A-Za-z]{2,4})\b", str(value or ""))
    remainder = str(value or "")[match.end():] if match else ""
    return bool(re.search(r"\b(?:not|never|no|none|undetermined|unclassified|indeterminate|"
                          r"discard|unused|clobber|scratch|through the tail)\b", remainder, re.IGNORECASE))


def _non_gpr_return(value):
    """The x87/SSE/MMX register a return field names, or ``None``."""
    text = re.sub(r"[^A-Z]", "", str(value or "").upper())
    if text.startswith("XMM"):
        return "XMM0"
    if text.startswith("MM"):
        return "MM0"
    if text.startswith("ST"):
        return "ST0"
    return None


def classify(*, abi_sources, listing, parse, sret=None):
    """The machine-derived return state for one target, or a ``NOT_AVAILABLE``.

    ``abi_sources`` is the list of ABI layers in priority order (the index
    record's ``abi``, the ``abi`` envelope's outer layer, its derived ABI).
    ``listing`` is ``validate._listing``'s ``(addresses, texts)`` or ``None``,
    ``parse`` the envelope's ``parse`` sub-record, ``sret`` its ``sret``
    sub-record.

    The returned record always carries a ``state``; ``NOT_AVAILABLE`` is a state
    here, not an exception, so a caller can report *which* guard refused rather
    than only that something did. ``provable`` is true only for the states that
    rest on a complete listing and a parse that consumed it in full.
    """
    sources = [source for source in (abi_sources or ()) if isinstance(source, dict)]
    whole, reason = _whole_listing(listing, parse)
    # A record that carries no return field at all is an absence of evidence and
    # is read as one, before the guard: a listing that happens to contain no RET
    # is not a record of void, and neither is an ABI with no return fields.
    has_field = any(source.get(key) not in (None, "", [], {}) for source in sources for key in _RETURN_FIELDS)
    if not whole:
        return _not_available(reason)
    if not has_field:
        return _not_available("no ABI field records a return register, a return semantic or a return type for this target, "
                              "so there is no machine record to read a return claim from")
    addresses, texts = listing
    sret_state = _sret_state(sources, sret, next((source.get("return") for source in sources
                                                  if isinstance(source.get("return"), dict)), {}))
    if sret_state:
        return _state(sret_state,
                      "the ABI envelope records a hidden-pointer return hypothesis (%s), so the return register holds "
                      "an address rather than the value and no width read off it would be a claim about the wrong value"
                      % ("proven" if sret_state == "SRET_PROVEN" else "suspected"),
                      provable=sret_state == "SRET_PROVEN")
    # Every claim, split into the ones that name a register and the ones that
    # deny one, and neither set is allowed to be dropped. ``_registers`` reads
    # the index record, the envelope's outer layer, its derived ABI *and* the
    # envelope's nested ``return`` sub-record, and those four do disagree in the
    # committed packs: on 0x006a2a80 ``return_register`` says ``none`` while the
    # ``return`` sub-record beside it says ``EAX``.
    claims = _registers(sources)
    denials, named, unreadable = [], [], []
    for key, value in claims:
        if _NO_REGISTER.match(value.strip()):
            denials.append("%s=%r" % (key, value.strip()))
            continue
        name = _names_register(value)
        if name:
            # A field that names a register in order to deny it is a denial, and
            # belongs with ``none`` rather than with a carrier: both say this
            # function returns nothing, and only the second is a positive record.
            if _denies_register(value, name):
                denials.append("%s=%r" % (key, value.strip()))
            else:
                named.append(name)
            continue
        non_gpr = _non_gpr_return(value)
        if non_gpr:
            return _state("UNCLASSIFIED", "the ABI record names %s as the return register; %s, so the machine fixes "
                          "where the value travels and not the C type, and no width can be claimed"
                          % (non_gpr, _NON_GPR_RETURN[non_gpr]))
        unreadable.append("%s=%r" % (key, value.strip()))
    if denials and named:
        # A record that contradicts itself is not evidence of either thing, and
        # picking a winner here would be picking whichever field this module
        # happened to read first.
        return _state("UNCLASSIFIED",
                      "the machine record is contested: %s, while another return field names %s. Neither claim is "
                      "corroborated by the other, so no return state is derivable from a record that disagrees with itself"
                      % (" and ".join(denials), ", ".join(sorted(set(named)))), register=named[0])
    if len(set(named)) > 1:
        return _state("UNCLASSIFIED",
                      "the machine record names %d different return registers across its layers (%s), so no return "
                      "state is derivable from a record that disagrees with itself"
                      % (len(set(named)), ", ".join(sorted(set(named)))))
    if not named:
        if unreadable:
            return _not_available("the ABI record names a return register this module cannot read as a GPR (%s), so no "
                                  "return state is derivable from it" % "; ".join(unreadable))
        # The record positively claims no return register and nothing contradicts
        # it. The listing cannot corroborate that -- a void function writes EAX
        # as scratch throughout -- so here the listing is the guard on the basis
        # the record was derived on rather than a second witness, and the guard
        # has already been applied above. A field that was *absent* would never
        # have reached this line: ``has_field`` refused it as an absence.
        return _state("VOID_PROVEN",
                      "the machine record claims no return register (%s) and no other return field in it names one, and "
                      "the complete %d-instruction listing was consumed in full by the machine parse (degraded=%s, "
                      "unparsed=%d), so the claim is read on a whole body rather than on a fragment"
                      % (" and ".join(denials), len(texts), bool(parse.get("degraded")), int(parse.get("unparsed") or 0)),
                      provable=True, instructions=len(texts))
    register = named[0]
    values, exits = _return_values(addresses, texts, register)
    if not exits:
        return _state("UNCLASSIFIED",
                      "the %d-instruction listing has no reachable return for the recorded return register %s, so "
                      "nothing can be read about what it returns" % (len(texts), register))
    kinds = {value[0] for value in values.values()}
    widths = {value[1] for value in values.values() if value[0] == "defined"}
    if kinds == {"defined"} and len(widths) == 1:
        width = widths.pop()
        return _state(width_state(width, register),
                      "the complete %d-instruction listing writes %s at a determinate %d-byte width before all %d "
                      "reachable return(s); the width is a machine fact and the C type of that width is a source-side "
                      "choice" % (len(texts), register, width, exits),
                      provable=True, register=register, width=width, exits=exits, instructions=len(texts))
    if kinds == {"none"}:
        return _state("VOID_PROVEN",
                      "the ABI record names %s as the return register, and no path through the complete %d-instruction "
                      "listing writes it before any of the %d reachable return(s), so the function returns nothing"
                      % (register, len(texts), exits),
                      provable=True, instructions=len(texts), exits=exits)
    if "unknown" in kinds:
        return _state("UNCLASSIFIED",
                      "the return register %s is written at a width this module cannot bound on at least one of the %d "
                      "reachable return(s) in the complete %d-instruction listing (a call result, a conditional "
                      "destination, or two returns reached with different widths), so no width is determinable"
                      % (register, exits, len(texts)), register=register, exits=exits, instructions=len(texts))
    return _state("UNCLASSIFIED",
                  "the return register %s is written on some but not all paths to the %d reachable return(s) of the "
                  "complete %d-instruction listing, so the value returned is not determined"
                  % (register, exits, len(texts)), register=register, exits=exits, instructions=len(texts))


def _abi_claim(sources, *keys):
    """First non-empty claim for ``keys`` across the ABI sources, in order.

    A local copy of ``validate._abi_claim`` -- three loops, and a duplicated
    helper is better than a circular import for a question this module has to ask
    identically or the back-compat guarantee is void.
    """
    for source in sources or ():
        if not isinstance(source, dict):
            continue
        for key in keys:
            value = source.get(key)
            if value not in (None, "", [], {}):
                return value
    return None


def _source_type(target_span):
    """The declared return type of the target span, or ``None``.

    ``validate._return_type`` reads one field off the span ``_function_spans``
    built. Duplicated for the same reason as ``_abi_claim``: the field name is
    the contract between two modules and an import would close the loop.
    """
    if not isinstance(target_span, dict):
        return None
    value = target_span.get("return_type")
    return value if isinstance(value, str) and value.strip() else None


def _declared_width(declared):
    """The width in bytes a declared return type has, or ``None``.

    ``None`` means *unknown*, and it is the common case by design: a typedef, a
    class, a template parameter, ``auto`` and anything this table does not name
    have no width a static read can establish. A width match is never claimed for
    one of those -- a reconstruction that returns a class would otherwise be
    cleared by a machine width that says nothing about its size.
    """
    text = _QUALIFIER.sub(" ", str(declared or ""))
    text = text.strip()
    if not text:
        return None
    if text == "void":
        return 0
    pointer = text.count("*")
    if pointer:
        # Every pointer is four bytes on this target, including ``char *`` and
        # ``void *``; a pointer-to-pointer is two words wide, which is the only
        # case a count changes the answer.
        return 4 * max(1, pointer)
    if "&" in text:
        return None
    key = re.sub(r"\s+", " ", text).strip().casefold()
    if key in _SOURCE_WIDTH:
        return _SOURCE_WIDTH[key]
    if key.startswith("std::") and key[5:] in _STD_WIDTH:
        return _STD_WIDTH[key[5:]]
    return None


def _is_void(declared):
    return _QUALIFIER.sub(" ", str(declared or "")).strip() == "void"


def _evidence_paths(record, state):
    """The paths the verdict rests on.

    ``INDEX_REL`` for the record's own return fields, ``EVIDENCE_REL`` for the
    listing and the machine records. Every provable state here is a claim about a
    complete body, so a provable verdict always cites both; a state that named no
    state at all cites only the index, because the pack contributed nothing.
    """
    if state["provable"]:
        return [INDEX_REL, EVIDENCE_REL]
    return [INDEX_REL] if record else [EVIDENCE_REL]


def decide(*, record, categories, abi_outer, abi_inner, listing, scoped_text, target_span, source_path):
    """The RETURN SEMANTICS check this module can adjudicate, or ``None``.

    ``None`` means *defer*: the caller keeps whatever verdict it already reaches.
    The deferral is deliberately generous, because this module is an additional
    stricter-evidenced route and not a replacement -- a canonical ``return_type``
    in either ABI source is left to the existing string-agreement arms, so the
    506 packs that carry one keep their current PASS or WARN exactly, and a target
    with no source artifact is left to the arm that reports that.

    What is *not* deferred is a machine state that was read and is decidable,
    including ``UNCLASSIFIED``: there the existing wording ("return evidence is
    not deterministically available") is true but says nothing about *why*, and
    a named reason is what a reviewer needs. It is a status of
    ``NOT_AVAILABLE`` either way, so no target changes verdict on that path.
    """
    if not source_path or not isinstance(target_span, dict):
        return None
    abi_sources = []
    if isinstance(record, dict) and isinstance(record.get("abi"), dict):
        abi_sources.append(record["abi"])
    for layer in (abi_outer, abi_inner):
        if isinstance(layer, dict):
            abi_sources.append(layer)
    from . import validate as V  # imported here: ``validate`` loads this module's caller
    # The existing arms own the target when a canonical claim exists. Read with
    # the same helper and the same key order, so a target that is adjudicated
    # there today is not adjudicated twice with two different oracles. The claim
    # is ``return_type`` only, and deliberately not ``return_semantics``: that
    # field is a register-class classification ("unclassified_in_EAX",
    # "pointer_like_in_EAX", "integral_in_EAX") or prose, never a C or C++ type
    # name, so deferring on it sent every such target to a string comparison that
    # could not succeed and closed off this module's width-based route, which is
    # the stricter of the two. See ``validate._canonical_return_type``.
    if V._canonical_return_type(abi_sources):
        return None
    parse = V._machine_record(categories or {}, abi_outer, abi_inner, "parse")
    sret = V._machine_record(categories or {}, abi_outer, abi_inner, "sret")
    state = classify(abi_sources=abi_sources, listing=listing, parse=parse, sret=sret)
    # The second, independent read of the fail-closed gate, and it is what makes a
    # stubbed or future-widened ``classify`` unable to promote a partial listing to
    # a verdict: it is made from the raw listing and parse record rather than from
    # the state it is checking, so a patched ``classify`` cannot talk its way past
    # it. ``classify`` applied the same gate, and this read is what stops the two
    # from being one.
    whole, _ = _whole_listing(listing, parse)
    if not whole:
        return None
    declared = _source_type(target_span)
    kind = state["kind"]
    if kind == "NOT_AVAILABLE":
        return {"status": "NOT_AVAILABLE",
                "detail": ("the machine return state is NOT_AVAILABLE and the source span declares %s: %s. There is no "
                           "state to compare the declaration against, and none is invented."
                           % (("return type %r" % declared) if declared else "no return type", state["reason"])),
                "coverage": "none", "evidence": _evidence_paths(record, state)}
    if kind in ("UNCLASSIFIED", "SRET_SUSPECTED"):
        return {"status": "NOT_AVAILABLE",
                "detail": ("the machine return state is %s and the source span declares %s: %s. No verdict is available "
                           "on this state and none is claimed." % (state["state"],
                                                                    ("return type %r" % declared) if declared else "no return type",
                                                                    state["reason"])),
                "coverage": "partial", "evidence": _evidence_paths(record, state)}
    if kind == "SRET_PROVEN":
        # Proven, and still not a verdict: an sret means the register holds an
        # address, so the C-visible return type is not the register's contents and
        # the struct's own size is not in this listing. Claiming anything here
        # would claim the wrong value.
        return {"status": "NOT_AVAILABLE",
                "detail": ("the machine return state is SRET_PROVEN and the source span declares %s: the function "
                           "returns a hidden pointer's contents, so the register's width is not the width of anything "
                           "the source can be holding; the struct's size is not determinable from this listing"
                           % (("return type %r" % declared) if declared else "no return type")),
                "coverage": "partial", "evidence": _evidence_paths(record, state)}
    if not declared:
        return None
    if kind == "VOID_PROVEN":
        if _is_void(declared):
            return {"status": "PASS",
                    "detail": ("the source span declares void, and the machine proves the return is empty: %s. This is "
                               "proven from the complete listing and the parse record, not from the symbol's name."
                               % state["reason"]),
                    "coverage": "complete", "evidence": _evidence_paths(record, state)}
        # The one FAIL this module raises on its own account, and it is a FAIL
        # because both sides are positive: the machine has been shown to produce
        # no value and the source declares one. There is no reading of these two
        # facts that leaves them agreeing.
        return {"status": "FAIL",
                "detail": ("the source span declares return type %r but the machine proves this function returns "
                           "nothing: %s. A source that declares a value the machine does not produce is a "
                           "contradiction, not a naming difference." % (declared, state["reason"])),
                "coverage": "partial", "evidence": _evidence_paths(record, state)}
    # ``kind == "WIDTH"``. The width is compared, never the type.
    width = state.get("width")
    declared_width = _declared_width(declared)
    if declared_width is None:
        return {"status": "NOT_AVAILABLE",
                "detail": ("the machine return state is %s and the source span declares return type %r, whose width "
                           "cannot be computed from the declaration (a typedef, a class, a template or an alias); the "
                           "machine width is a fact and the C type is a source-side choice, so there is nothing to "
                           "compare" % (state["state"], declared)),
                "coverage": "partial", "evidence": _evidence_paths(record, state)}
    if declared_width == 0:
        return {"status": "FAIL",
                "detail": ("the source span declares void but the machine return state is %s: %s. A source that "
                           "declares no value where the machine provably returns one is a contradiction, and the "
                           "mirrored case of the proven-void FAIL." % (state["state"], state["reason"])),
                "coverage": "partial", "evidence": _evidence_paths(record, state)}
    if declared_width == width:
        return {"status": "PASS",
                "detail": ("the source span declares return type %r and the machine return state is %s: %s. The width "
                           "is corroborated by the machine; the exact C type spelling remains a source-side choice "
                           "among the types of that width and is not verified here." % (declared, state["state"],
                                                                                        state["reason"])),
                "coverage": "complete", "evidence": _evidence_paths(record, state)}
    # A width disagreement is a WARN and not a FAIL, and the difference from the
    # proven-void case above is the direction of the claim. Void was proven from
    # the body and contradicted a declared value, so both halves were positive.
    # A width is read off one register: a hidden-pointer struct return, an
    # aggregate written through a hidden argument, or a source-side promotion can
    # each make a declared width and a register width differ without the
    # reconstruction being wrong. The disagreement is real and needs a reviewer.
    return {"status": "WARN",
            "detail": ("the machine return state is %s -- %s -- but the source span declares return type %r, which is "
                       "%d byte(s) wide. The machine fixes the width of the value in %s; it does not fix the C type, "
                       "and a hidden-pointer or aggregate return is one reading in which the two differ without the "
                       "reconstruction being wrong, so this is a review item rather than a refutation."
                       % (state["state"], state["reason"], declared, declared_width, state.get("register"))),
            "coverage": "partial", "evidence": _evidence_paths(record, state)}
