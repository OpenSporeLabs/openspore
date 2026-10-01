"""Positively-corroborated virtual dispatch for the VIRTUAL DISPATCH dimension.

The dimension this module serves had exactly one PASS arm, and it was the
*absence* of dispatch: a complete listing naming no indirect transfer at all,
corroborated by a machine dispatch record that also counted none. So a body that
correctly performs a virtual call could never pass -- it was always held at WARN
with a detail that read as though something were unaccounted for ("names 1
indirect dispatch site(s) and the machine dispatch record counts 1 and the source
declares a slot boundary, so slot offsets need review"). Measured over the 418
committed reports: PASS 72, NOT_AVAILABLE 239, WARN 46, UNKNOWN 61, and every
one of those 72 passes was "nothing there".

The evidence for the positive claim was already being collected and simply not
read. The complete listing shows the canonical x86-32 virtual-call shape
directly, and the envelope's ``dispatch`` record counts the sites independently.
So this module reads the two, derives each site's shape from the listing bytes,
and reports the dispatch that is there.

What each shape is allowed to rest on, and why the boundaries are where they are:

``VTABLE_SLOT``
    The two-level load, read off the listing with a must-analysis of register
    definitions. The target register is loaded from a memory operand whose base
    register was itself loaded from a memory operand -- ``MOV EAX,[EDI]`` /
    ``MOV EAX,[EAX+0x14]`` / ``CALL EAX`` -- and the *second* load's displacement
    is the slot offset. That displacement is machine evidence, read out of the
    instruction rather than inferred, and it is what makes the source's slot
    naming comparable against anything. Measured over the committed corpus this
    is 246 of 257 indirect sites, and all 246 displacements are multiples of 4,
    which is what a dword-indexed table looks like on x86-32. Two machine
    sources must agree before this may pass: this shape, and the ``dispatch``
    record's ``indirect_calls``.

``FUNCTION_POINTER``
    A real dispatch whose *identity* is not established: the target register is
    loaded, but the listing does not show the word it came from being read out of
    an object. Loaded straight from a global, out of a frame slot, or through an
    indexed operand. A dispatch, certainly; a *virtual* dispatch, not shown.

``INDIRECT_NON_VTABLE``
    The transfer target is a memory operand, so there is no register chain to
    read: ``CALL dword ptr [ESP + 0x30]``, and the jump tables
    ``JMP dword ptr [EAX*0x4 + 0x5dd840]``. A jump table is not a virtual
    dispatch and is never counted as one.

``UNRESOLVED``
    The target register's value cannot be traced at all: defined by an unmodelled
    path, an opaque ``LEA``, a ``CALL`` result (the caller-saved set is treated as
    clobbered, so a real call between the load and the indirect call ends the
    chain), or by nothing in the listing at all.

Two oracles are deliberately *not* consulted and no third is invented to replace
them. ``record["vtables"]`` is withdrawn in ``validate.py`` as a transitive
classifier association that contradicts the xref export outright, and
``dependencies["vtable_reference_count"]`` is 0 on essentially every record --
they are not independent of each other, so agreeing with them would prove
nothing. The xref export's ``computed-call`` edge type is the same family: it
categorises a transfer without establishing which one, so it is not read here
either. Everything below rests on the listing bytes and the envelope's own
records.

Nothing here speaks about run time. This is the static dimension only; the
runtime axis is a separate verdict in ``validate`` and is untouched.
"""

import re

STATES = ("VTABLE_SLOT", "FUNCTION_POINTER", "INDIRECT_NON_VTABLE", "UNRESOLVED")

# The literal paths the checks in this package report, restated rather than
# imported. ``validate`` is not imported at module scope: it is the caller, and
# importing it here would be a circular import at the one moment -- its own
# import -- that cannot resolve it. The test module asserts these equal
# validate's own, so a rename there fails loudly here.
INDEX_REL = "reconstruction/knowledge/index.json"
EVIDENCE_REL = "reconstruction/evidence"

# ``validate.INDIRECT_REGISTERS``, spelled out rather than matched as
# ``[A-Za-z]{1,4}`` so a Ghidra operand prefix can never be read as a register
# and an immediate is never mistaken for one.
INDIRECT_REGISTERS = ("EAX", "EBX", "ECX", "EDX", "ESI", "EDI", "EBP", "ESP")
_REGISTERS = "|".join(INDIRECT_REGISTERS)
# The two indirect-transfer shapes, kept identical to ``validate``'s so the site
# set this module judges is the site set the existing arms count. A difference
# here would make "the two machine sources agree" a claim about two quantities
# that are not the same quantity.
INDIRECT_TRANSFER = re.compile(r"^\s*(?:CALL|JMP)\s+(?:\w+\s+PTR\s+)?(?:\w+:\s*)?\[", re.IGNORECASE)
INDIRECT_REGISTER_TRANSFER = re.compile(r"^\s*(?:CALL|JMP)\s+(?:%s)(?![\w])" % _REGISTERS, re.IGNORECASE)
MEMORY_OPERAND = re.compile(r"\[([^\]]*)\]")
# A displacement inside a memory operand. The lookbehind skips a scale factor
# (``[EAX*0x4 + 0x5dd840]``: 0x4 is a multiplier, not a displacement) and the
# register name itself -- the same exclusion ``validate.OPERAND_DISPLACEMENT``
# makes.
OPERAND_DISPLACEMENT = re.compile(r"(?<![\w.*])0[xX]([0-9a-fA-F]+)")
_REGISTER_TOKEN = re.compile(r"(?<![\w.])(%s)(?![\w])" % _REGISTERS, re.IGNORECASE)
# The tokens that say a source declares a slot boundary: ``validate``'s own set,
# so both halves of the source/machine comparison rest on one notion of
# "declares a slot".
VIRTUAL_SOURCE_TOKENS = ("load_slot", "object_slot", "shell_slot", "vtable", "slot[")

_BLOCK_COMMENT = re.compile(r"/\*.*?\*/", re.DOTALL)
_LINE_COMMENT = re.compile(r"//[^\n]*")
_HEX_ADDRESS = re.compile(r"^[0-9a-fA-F]{1,8}$")

_LOAD = re.compile(r"^\s*MOV\s+(?P<dst>%s)\s*,\s*(?:\w+\s+PTR\s+)?\[(?P<operand>[^\]]*)\]" % _REGISTERS,
                   re.IGNORECASE)
# A store: the first operand is memory, so nothing in the register file is
# defined. Matched so the ``MOV`` arm can decline rather than falling through to
# the clobber-everything default and reporting a store as an opaque write.
_STORE = re.compile(r"^\s*MOV\s*(?:\w+\s+PTR\s+)?\[", re.IGNORECASE)
_PLAIN_MOVE = re.compile(r"^\s*MOV\s+(?P<dst>%s)(?![\w])" % _REGISTERS, re.IGNORECASE)
_ADDRESS_OF = re.compile(r"^\s*LEA\s+(?P<dst>%s)(?![\w])" % _REGISTERS, re.IGNORECASE)
_ZEROED = re.compile(r"^\s*(?:XOR|SUB)\s+(?P<dst>%s)\s*,\s*(?P=dst)\b" % _REGISTERS, re.IGNORECASE)
# The mnemonic. Ghidra puts its own prefixes (``dword ptr``, ``near ptr``)
# *after* the mnemonic and only the repeat/lock prefixes before it, so stripping
# the latter is the whole of the normalisation.
_INSTRUCTION = re.compile(r"^\s*(?:(?:REP|REPNE|REPNEZ|REPE|REPEZ|REPZ|REPNZ|LOCK|NO)\s+)*"
                          r"(?P<mnem>[A-Z][A-Z0-9]*)\b(?P<operands>.*)$", re.IGNORECASE)
# Mnemonics whose destination is the first register operand they name. Anything
# neither listed here nor read-only is treated as writing every register it
# mentions, which is the direction that cannot invent a proven dispatch.
_ALU_DESTINATION = ("ADD", "SUB", "AND", "OR", "XOR", "ADC", "SBB", "IMUL", "SHL", "SAL", "SHR",
                    "SAR", "ROL", "ROR", "RCL", "RCR", "NEG", "NOT", "INC", "DEC", "MOVZX",
                    "MOVSX", "MOVSXD", "BSWAP")
_TWO_SIDED = ("XCHG",)
# Instructions with no named destination that still define registers. ``CALL`` is
# here on purpose: a real call between the load and the indirect transfer leaves
# the target register holding a callee's return value, which is exactly the
# ``UNRESOLVED`` case, and a chain that walked straight past the call would claim
# a proven dispatch the machine does not show.
_IMPLICIT_DEFINITIONS = {
    "CALL": ("EAX", "ECX", "EDX"),
    "MUL": ("EAX", "EDX"),
    "DIV": ("EAX", "EDX"),
    "IDIV": ("EAX", "EDX"),
    "CDQ": ("EAX", "EDX"),
    "CWD": ("EAX", "EDX"),
    "CWDE": ("EAX", "EDX"),
}
# Mnemonics that only read. Leaving a *writing* instruction out of this list is
# the safe mistake: it is then handled as an opaque write, which costs a site its
# pass and never invents one.
_READ_ONLY = ("CMP", "TEST", "PUSH", "JMP", "RET", "NOP", "INT3", "CLC", "STC", "CD", "STD",
              "WAIT", "FWAIT", "HLT", "END", "LOCK", "BT", "BTS", "BTR", "BTC")
# The string operations and the port pair: their memory operands and their
# register effects are both implicit, so a ``MOVSD`` between the load and the
# call must end the chain rather than be walked past.
_IMPLICIT_MEMORY = re.compile(
    r"^\s*(?:REP|REPNE|REPNZ|REPE|REPZ|NO)?\s*"
    r"(?:MOVS[BWDQ]?|STOS[BWDQ]?|LODS[BWDQ]?|SCAS[BWDQ]?|CMPS[BWDQ]?|"
    r"INS[BWDQ]?|OUTS[BWDQ]?|IN|OUT)\b", re.IGNORECASE)

# -- the source side --------------------------------------------------------------
# The three narrow forms a source states its slot offsets in, all read off the
# code with comments removed. The extraction is deliberately narrow, because the
# result is compared as a *subset* of the machine displacements: reading too much
# would invent a contradiction and cost a correct reconstruction its pass, while
# reading too little is honest and is reported as "no offset this parser can
# read". Both directions are accounted for in ``decide``.
_SLOT_MEMBER = re.compile(r"\bslot_([0-9a-fA-F]{1,3})\b")
_SLOT_CALL = re.compile(r"\b(?P<callee>[A-Za-z_][A-Za-z0-9_:]*)\s*(?:<[^;()]*>)?\s*\((?P<args>[^;()]*)\)")
_QUALIFIED_SLOT_CALL = re.compile(r"(?P<qualifier>[A-Za-z0-9_>\-\.\*() ]*?)\b[A-Za-z_][A-Za-z0-9_]*"
                                  r"_(?P<offset>[0-9a-fA-F]{1,3})\s*\(")
_OFFSET_ADDED = re.compile(r"\b(?P<base>[A-Za-z_][A-Za-z0-9_]*)(?:\s*\))?\s*\+\s*0[xX](?P<offset>[0-9a-fA-F]+)")
_HEX_LITERAL = re.compile(r"0[xX]([0-9a-fA-F]+)")
_SLOT_WORD = re.compile(r"vtable|vftable|slot|dispatch", re.IGNORECASE)


def _code(text):
    """``text`` with comments removed.

    Every comparison made against the source is a claim about what the
    reconstruction *does*, so it is made about code: a slot offset named in a
    comment is a note about the machine, not a declaration by the source.
    Duplicated from ``validate._code`` rather than imported, for the reason in
    the module docstring.
    """
    return _LINE_COMMENT.sub(" ", _BLOCK_COMMENT.sub(" ", text or ""))


def _address(value):
    """``0x%08x`` form of ``value``, or ``None`` if it is not an address.

    The listing's addresses arrive already canonical from ``validate._listing``,
    but a site that cannot be named in its own detail is a site that cannot be
    audited, so anything unnameable is reported as unnameable rather than
    dropped.
    """
    if not isinstance(value, str):
        return None
    text = value.strip().lower()
    if text.startswith("0x"):
        text = text[2:]
    if not _HEX_ADDRESS.match(text):
        return None
    return "0x%08x" % int(text, 16)


def _hex(value):
    """``0x..`` for a displacement, spelled the way a listing spells it."""
    return "0x%x" % int(value)


def _instruction(text):
    """``(mnemonic, operand_text)`` for a listing line, or ``(None, text)``."""
    match = _INSTRUCTION.match(str(text or ""))
    if not match:
        return None, str(text or "")
    return match.group("mnem").upper(), match.group("operands") or ""


def _memory_shape(operand):
    """``(registers, displacement, indexed)`` for a memory operand.

    ``indexed`` is true when the operand carries a scale factor, which makes it
    one element of a table chosen by a computed index rather than a field. That
    distinction is the difference between a switch and a virtual call:
    ``[EAX*0x4 + 0x5dd840]`` is a jump table, and reading it as a field would
    classify a switch as virtual dispatch.
    """
    operand = str(operand or "")
    if "*" in operand:
        return [], 0, True
    registers = [token.upper() for token in _REGISTER_TOKEN.findall(operand)]
    displacement = 0
    for literal in OPERAND_DISPLACEMENT.findall(operand):
        displacement = int(literal, 16)
    return registers, displacement, False


def _define(text, definitions, index):
    """Record what the listing line ``text`` defines in ``definitions``.

    ``definitions`` maps a register to ``(kind, payload, listing index)`` and is
    written with ``setdefault``, so a caller that walks the listing sees the
    *nearest* definition of each register and can stop early.

    The kinds are the analysis's whole vocabulary, and each one is a distinct way
    a reconstruction could be wrong about what a transfer dispatches to:

    ``load``      read out of memory -- ``(registers, displacement, indexed)``
    ``address``   ``LEA``: an address was formed, no object was read
    ``value``     assigned from an immediate or another register
    ``zero``      ``XOR r,r`` / ``SUB r,r``: known to be zero
    ``call``      a real call clobbered it, so it holds a callee's return value
    ``opaque``    written by something this parser does not model
    """
    if _IMPLICIT_MEMORY.match(text):
        for register in INDIRECT_REGISTERS:
            definitions.setdefault(register, ("opaque", "a string or port instruction", index))
        return
    mnemonic, operands = _instruction(text)
    if mnemonic is None:
        return
    load = _LOAD.match(text)
    if load:
        registers, displacement, indexed = _memory_shape(load.group("operand"))
        definitions.setdefault(load.group("dst").upper(), ("load", (registers, displacement, indexed), index))
        return
    if _STORE.match(text):
        return
    address = _ADDRESS_OF.match(text)
    if address:
        definitions.setdefault(address.group("dst").upper(), ("address", None, index))
        return
    zero = _ZEROED.match(text)
    if zero:
        definitions.setdefault(zero.group("dst").upper(), ("zero", None, index))
        return
    if mnemonic == "POP":
        for token in _REGISTER_TOKEN.findall(operands):
            definitions.setdefault(token.upper(), ("value", None, index))
        return
    if mnemonic == "PUSH":
        definitions.setdefault("ESP", ("value", None, index))
        return
    if mnemonic in _IMPLICIT_DEFINITIONS:
        for register in _IMPLICIT_DEFINITIONS[mnemonic]:
            definitions.setdefault(register, ("call", None, index))
        return
    if mnemonic in _ALU_DESTINATION or mnemonic in _TWO_SIDED:
        tokens = [token.upper() for token in _REGISTER_TOKEN.findall(operands)]
        for register in (tokens[:2] if mnemonic in _TWO_SIDED else tokens[:1]):
            definitions.setdefault(register, ("value", None, index))
        return
    if mnemonic in _READ_ONLY:
        return
    if mnemonic == "MOV":
        plain = _PLAIN_MOVE.match(text)
        if plain:
            definitions.setdefault(plain.group("dst").upper(), ("value", None, index))
        return
    for token in _REGISTER_TOKEN.findall(operands):
        definitions.setdefault(token.upper(), ("opaque", mnemonic, index))


def _definitions(texts, limit):
    """Register definitions established by ``texts[:limit]``.

    A backward walk with nearest-definition-wins, so the entry for a register is
    the closest instruction before ``limit`` that defines it. The listing index
    is carried in each entry, which is what lets the base register of a two-level
    load be resolved *strictly before the load that reads it*: without that,
    ``MOV EAX,[EAX+0x14]`` would resolve its own base against itself and a body
    containing no two-level load at all would classify as a proven dispatch.
    That is the one way this classification could be right by accident, and the
    index is what makes it impossible.
    """
    definitions = {}
    for position in range(limit - 1, -1, -1):
        _define(texts[position], definitions, position)
    return definitions


_KIND_REASON = {
    "address": "an LEA, which forms an address without reading an object",
    "value": "an immediate or register assignment, not a memory load",
    "zero": "a self-subtraction that leaves it zero",
    "call": "a preceding CALL, so it holds that callee's return value",
}


def _table_word(definitions, register):
    """The load that put a table word into ``register``, or ``None``.

    ``None`` unless the nearest definition of ``register`` is a memory load with
    a base register. A frame slot, a global, an indexed operand, an ``LEA`` and
    no definition at all all return ``None``: the listing does not show the word
    to be a pointer into an object's table, which is exactly the claim a virtual
    dispatch needs and exactly what may not be assumed.
    """
    entry = definitions.get(register)
    if entry is None or entry[0] != "load":
        return None
    registers, _base_displacement, indexed = entry[1]
    if indexed or not registers:
        return None
    return entry


def _classify_at(addresses, texts, index):
    """``(shape, slot_offset, base, reason)`` for the transfer at ``index``."""
    kind, target = _transfer(texts[index])
    text = str(texts[index] or "").strip()
    here = _address(addresses[index]) if index < len(addresses) else None
    if kind == "memory":
        operand = MEMORY_OPERAND.search(text)
        return ("INDIRECT_NON_VTABLE", None, None,
                "the target is the memory operand %s, so no register chain exists to read; a scaled "
                "operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a "
                "frame slot, and neither is a virtual dispatch"
                % (operand.group(0) if operand else text))
    before = _definitions(texts, index)
    entry = before.get(target)
    if entry is None:
        return ("UNRESOLVED", None, None,
                "no instruction in the listing defines %s before %s, so its value comes from an "
                "unmodelled path, the incoming arguments, or the stack" % (target, here or "the transfer"))
    kind, payload, _position = entry
    if kind != "load":
        return ("UNRESOLVED", None, None,
                "%s is defined by %s before %s"
                % (target, _KIND_REASON.get(kind, "an instruction this parser does not model"),
                   here or "the transfer"))
    registers, displacement, indexed = payload
    if indexed:
        return ("FUNCTION_POINTER", None, None,
                "%s is loaded through an indexed operand, so the word it names is a table element "
                "chosen by a computed index rather than a field" % target)
    if not registers:
        return ("FUNCTION_POINTER", None, None,
                "%s is loaded straight from the absolute address of the operand, with no base "
                "register, so the listing shows a data-segment function pointer and no object" % target)
    base = registers[0]
    # Strictly before the load that reads it: this is what stops a self-referential
    # ``MOV EAX,[EAX+disp]`` from being read as its own two-level chain.
    outer_definitions = _definitions(texts, _position)
    table = _table_word(outer_definitions, base)
    if table is None:
        outer = outer_definitions.get(base)
        if outer is None:
            why = ("%s has no definition earlier in the listing, so the word it names is not shown "
                   "to be a table" % base)
        else:
            why = ("%s is defined by %s earlier in the listing, so the word it names is not shown "
                   "to be a table word" % (base, _KIND_REASON.get(outer[0], outer[0])))
        return ("FUNCTION_POINTER", None, None,
                "%s is loaded from [%s%s], but %s" % (target, base,
                                                     "" if not displacement else " + %s" % _hex(displacement),
                                                     why))
    object_registers, object_displacement, _ = table[1]
    table_at = _address(addresses[table[2]]) if table[2] < len(addresses) else None
    return ("VTABLE_SLOT", displacement, base,
            "%s is loaded from the table word %s holds, which %s read out of %s%s, so the transfer "
            "reads slot displacement %s of that table"
            % (target, base, table_at or "an earlier instruction", object_registers[0],
               "" if not object_displacement else " + %s" % _hex(object_displacement),
               _hex(displacement)))


def _transfer(text):
    """``("memory", None)`` / ``("register", name)`` for an indirect transfer."""
    text = str(text or "")
    if INDIRECT_TRANSFER.match(text):
        return "memory", None
    register = INDIRECT_REGISTER_TRANSFER.match(text)
    if register:
        return "register", register.group(0).split()[-1].upper()
    return None, None


def _site_indices(texts):
    """The listing positions that hold an indirect transfer, in order."""
    return [index for index, text in enumerate(texts) if _transfer(text)[0] is not None]


def classify_sites(addresses, texts):
    """Classify every indirect transfer in a listing, by shape.

    ``addresses`` and ``texts`` are the two halves ``validate._listing``
    returns. One entry per indirect transfer, in listing order, each a dict with
    ``address``, ``text``, ``shape`` (one of ``STATES``), ``slot_offset`` (the
    displacement the machine reads the slot word at, or ``None``), ``base`` (the
    register holding the table word, or ``None``) and ``reason`` -- the sentence a
    verdict is allowed to quote.

    The classification is a consequence of the listing bytes and of nothing else.
    No vtable image, no ``record["vtables"]`` association and no xref category is
    consulted, so a shape cannot be asserted that the instructions do not show,
    and the same listing always classifies the same way.
    """
    texts = [str(text or "") for text in (texts or ())]
    listed = list(addresses or ())
    found = []
    for index in _site_indices(texts):
        shape, slot_offset, base, reason = _classify_at(listed, texts, index)
        found.append(_entry(_address(listed[index]) if index < len(listed) else None,
                            texts[index], shape, slot_offset, base, reason))
    return found


def _entry(address, text, shape, slot_offset, base, reason):
    return {"address": address, "text": str(text or ""), "shape": shape,
            "slot_offset": slot_offset, "base": base, "reason": reason}


def _reproducible(addresses, texts, index, entry):
    """Whether ``entry`` is what the listing itself says about the site at ``index``.

    ``decide`` re-derives every classification it is handed and refuses to pass
    on a disagreement. This is not redundancy for its own sake: the shape is the
    whole basis of the new PASS arm, so a shape that cannot be reproduced from the
    listing bytes is a claim about the code that the code does not support, and it
    has to fail closed even when it arrives from inside this module.
    """
    shape, slot_offset, base, _ = _classify_at(addresses, texts, index)
    return (shape == entry.get("shape") and slot_offset == entry.get("slot_offset")
            and base == entry.get("base"))


def _machine_record(categories, abi_outer, abi_inner, key):
    """The machine-derived sub-record ``key``: ``abi_derived`` first, then ``abi``.

    The same resolution order ``validate._machine_record`` uses, restated because
    importing it would be the circular import. ``abi_derived`` is the pack's
    declared home for the derivation; the ``abi`` value is the fallback for a
    pack collected before that category existed, or one whose ``abi`` value
    already *is* the derived envelope. A ``{"truncated": true}`` layer is refused
    on either side: its preview is a fragment, and a fragment is never a record --
    least of all a count, which is how an absence of evidence becomes a clearance.
    ``{}`` is returned when neither layer carries the key, so a missing record
    stays distinguishable from a record of zero all the way to the verdict.
    """
    value = (categories.get("abi_derived") or {}).get("value")
    if isinstance(value, dict) and value.get("truncated") is not True:
        record = value.get(key)
        if isinstance(record, dict) and record:
            return record
    if isinstance(abi_outer, dict) and abi_outer.get("truncated") is True:
        abi_outer = {}
    for source in (abi_outer if isinstance(abi_outer, dict) else {},
                   abi_inner if isinstance(abi_inner, dict) else {}):
        record = source.get(key)
        if isinstance(record, dict) and record:
            return record
    return {}


def _count(value):
    """``value`` when it is a real count, else ``None``.

    ``bool`` is refused: ``True`` is an ``int`` in Python and would read as a
    count of one, which is precisely the direction in which a missing record must
    not fail.
    """
    if isinstance(value, bool) or not isinstance(value, int):
        return None
    return value


def _site_clause(site):
    """One site's shape, in the short form the preamble lists.

    The long ``reason`` is not repeated here: a site that is not a proven slot is
    named once, in the failure that refused the pass, and the pass preamble
    carries the shape alone so the reader sees the mixture without reading every
    site's justification twice.
    """
    where = site.get("address") or "(an unaddressed position)"
    if site.get("shape") == "VTABLE_SLOT":
        return "%s dispatches slot %s through the table word in %s" % (
            where, _hex(site["slot_offset"]), site.get("base") or "a register")
    return "%s is %s" % (where, site.get("shape"))


def _source_slot_offsets(text):
    """Displacements the source span states for its slots, or an empty set.

    Three narrow forms, all read off the code with comments removed: a member
    literally named ``slot_XX``; a hex literal passed to a call whose callee
    names a slot; and a hex offset in a qualified call or an added expression
    whose base names a slot.
    """
    code = _code(text)
    found = set()
    for match in _SLOT_MEMBER.finditer(code):
        found.add(int(match.group(1), 16))
    for match in _SLOT_CALL.finditer(code):
        if not _SLOT_WORD.search(match.group("callee")):
            continue
        for literal in _HEX_LITERAL.findall(match.group("args")):
            found.add(int(literal, 16))
    for match in _QUALIFIED_SLOT_CALL.finditer(code):
        if _SLOT_WORD.search(match.group("qualifier")):
            found.add(int(match.group("offset"), 16))
    for match in _OFFSET_ADDED.finditer(code):
        if _SLOT_WORD.search(match.group("base")):
            found.add(int(match.group("offset"), 16))
    return found


def _source_claim(scoped_text, target_span, source_path):
    """``(declares, declared_offsets)`` for the source side of the dimension.

    ``declares`` is ``validate``'s own token test, over code only, so both halves
    of the comparison rest on one notion of "declares a slot". It is
    three-valued: ``False`` is a source that declares no slot, ``True`` is one
    that does, and ``None`` is a target with no bound source span at all -- an
    absence of a source, which is a different claim from a statement about one.
    """
    if not source_path or not target_span:
        return None, set()
    return any(token in _code(scoped_text) for token in VIRTUAL_SOURCE_TOKENS), _source_slot_offsets(scoped_text)


def decide(*, record, categories, abi_outer, abi_inner, listing,
           scoped_text, target_span, source_path, dependencies):
    """A positively-corroborated VIRTUAL DISPATCH check, or ``None`` to defer.

    ``None`` means "this module's evidence does not adjudicate this target", and
    the caller must then reach exactly the arms it reached before -- so every
    existing verdict stays reachable and every existing detail stays byte for
    byte. That holds structurally rather than by promise: the arms this module
    does not speak for are a missing or truncated listing, and a listing naming
    no indirect transfer at all (``proven_empty``'s PASS, the
    source-claims-a-slot FAIL, and the "a missing record is not a record of zero"
    WARN), and every one of those returns ``None`` here.

    What is left is the case the dimension could not express: a body that names
    one or more indirect transfers. A PASS needs *all* of the following, and the
    detail names each one it relies on and each one it is missing:

    * a complete listing. ``listing`` is the pair ``validate._listing`` returns
      and is ``None`` for a truncated envelope, an absent category and an empty
      body alike, so none of those can reach a state stronger than the caller's
      ``NOT_AVAILABLE``;
    * a machine parse record that consumed the listing in full:
      ``declared_count == len(listing)``, ``degraded is not True``,
      ``unparsed == 0``;
    * a ``dispatch`` record that is not a ``{"truncated": true}`` envelope and
      whose ``indirect_calls`` is an integer that *agrees* with the number of
      indirect transfers the listing shows. These are two independent machine
      sources and one of them is a derived record, so their agreement is
      corroboration; a disagreement in either direction means the listing may be
      a slice, and a slice proves nothing;
    * every site classified ``VTABLE_SLOT``. A body that mixes a proven vtable
      dispatch with an unresolved function-pointer call is a real body whose
      *identity* is not established, so it is a WARN;
    * every classification reproducible from the listing bytes.

    On the source side the honest split is preferred. If the source declares a
    slot boundary and states offsets, they must all appear among the machine slot
    displacements or the check is a WARN naming both. If it declares a boundary
    but states no offset this parser can read -- a real measured case, because
    reconstructions also name a slot as an *index* (``slot_target_at(vtable, 1u)``,
    which is four bytes) or through a convention this parser does not decode --
    then the machine dispatch is proven and the source's slot naming is
    explicitly *not* verified, and the detail says so instead of implying one
    verdict covers both.
    """
    if not listing:
        return None
    addresses, texts = listing
    texts = [str(text or "") for text in (texts or ())]
    if not texts:
        return None
    indices = _site_indices(texts)
    if not indices:
        return None

    dispatch = _machine_record(categories, abi_outer, abi_inner, "dispatch")
    parse = _machine_record(categories, abi_outer, abi_inner, "parse")
    classified = classify_sites(addresses, texts)
    declares, declared = _source_claim(scoped_text, target_span, source_path)
    machine_offsets = sorted({site["slot_offset"] for site in classified
                              if site["shape"] == "VTABLE_SLOT" and site["slot_offset"] is not None})

    failures = []
    # -- the listing was consumed in full ---------------------------------------
    if parse.get("truncated") is True:
        # ``_machine_record`` refuses a truncated *layer*; this catches a truncated
        # *sub-record*, which it cannot see. Either way a preview is a fragment,
        # and a fragment is never a record -- least of all a count.
        failures.append("the machine parse record is a truncated envelope, and a fragment is never "
                        "a record")
    elif not parse:
        failures.append("no machine parse record was collected, so the listing cannot be shown to "
                        "have been read in full")
    else:
        declared_count = _count(parse.get("declared_count"))
        unparsed = _count(parse.get("unparsed"))
        if declared_count is None or unparsed is None:
            failures.append("the machine parse record carries no usable count (declared_count=%r, "
                            "unparsed=%r)" % (parse.get("declared_count"), parse.get("unparsed")))
        else:
            if declared_count != len(texts):
                failures.append("the machine parse declared %d instruction(s) and the listing holds "
                                "%d, so the two disagree about the body and neither is the whole of it"
                                % (declared_count, len(texts)))
            if parse.get("degraded") is True:
                failures.append("the machine parse is degraded")
            if unparsed:
                failures.append("%d instruction(s) were left unparsed" % unparsed)
    # -- the two machine sources agree -----------------------------------------
    dispatch_count = _count(dispatch.get("indirect_calls"))
    if dispatch.get("truncated") is True:
        failures.append("the machine dispatch record is a truncated envelope, so it cannot "
                        "corroborate the listing; a missing record is not a record of zero")
    elif not dispatch:
        failures.append("no machine dispatch record was collected to corroborate the listing; a "
                        "missing record is not a record of zero")
    elif dispatch_count is None:
        failures.append("the machine dispatch record counts %r, which is not a count"
                        % (dispatch.get("indirect_calls"),))
    elif dispatch_count != len(indices):
        failures.append("the machine dispatch record counts %d and the listing names %d indirect "
                        "transfer(s); the two machine sources disagree, so the listing is probably a "
                        "slice and the site count is a lower bound" % (dispatch_count, len(indices)))
    # -- every site is a proven vtable slot -------------------------------------
    if len(classified) != len(indices):
        failures.append("the classifier returned %d classification(s) for the %d indirect transfer(s) "
                        "the listing names, so the site set is not accounted for"
                        % (len(classified), len(indices)))
    # Grouped by shape, and the reason quoted once per shape: a body that mixes a
    # proven slot with five frame-slot calls must name all of them without
    # repeating the same sentence six times.
    by_shape = {}
    for site in classified:
        if site.get("shape") != "VTABLE_SLOT":
            by_shape.setdefault(site["shape"], []).append(site)
    for shape in sorted(by_shape):
        group = by_shape[shape]
        failures.append("%d of the %d indirect transfer(s) classify as %s (%s), so the dispatch's "
                        "identity is not established: %s"
                        % (len(group), len(indices), shape,
                           ", ".join(site.get("address") or "an unaddressed position" for site in group),
                           group[0]["reason"]))
    for site, index in zip(classified, indices):
        if site.get("shape") == "VTABLE_SLOT" and not _reproducible(addresses, texts, index, site):
            failures.append("the classification of the site at %s is not reproducible from the "
                            "listing bytes" % (site.get("address") or "an unaddressed position"))
    # -- the source's slot naming does not contradict the machine ---------------
    if declares and declared and not declared <= set(machine_offsets):
        failures.append("the source span states slot displacement(s) %s and the machine reads %s, so "
                        "the two disagree about which slot is dispatched"
                        % (", ".join(_hex(value) for value in sorted(declared)),
                           ", ".join(_hex(value) for value in machine_offsets) or "no slot at all"))

    preamble = ("the complete %d-instruction body names %d indirect transfer(s): %s"
                % (len(texts), len(indices), "; ".join(_site_clause(site) for site in classified)))
    # The two machine facts, each stated only when the record that carries it is
    # actually there. A phrasing that asserted a clean parse for a record that was
    # never collected would be the one sentence in the detail that lies.
    if parse and parse.get("truncated") is not True and _count(parse.get("declared_count")) is not None:
        parse_note = ("the machine parse consumed %d of %d instruction(s) with %d unparsed and "
                      "degraded=%s" % (parse["declared_count"], len(texts),
                                        _count(parse.get("unparsed")) or 0, bool(parse.get("degraded"))))
    else:
        parse_note = "no usable machine parse record was collected"
    if dispatch and dispatch.get("truncated") is not True:
        dispatch_note = ("the machine dispatch record independently counts %s"
                         % (dispatch_count if dispatch_count is not None else "no integer"))
    else:
        dispatch_note = "no usable machine dispatch record was collected"
    corroboration = "%s, and %s" % (parse_note, dispatch_note)
    if failures:
        return _check("WARN",
                      "%s; %s, so the dispatch is visible in the machine listing but is not proven: %s"
                      % (preamble, corroboration, " and ".join(failures)))
    detail = ("%s; %s. Every site is a two-level table load, so the machine dispatch is proven "
              "against the original binary: the reconstruction dispatches, and it dispatches through "
              "the slots the machine reads at those displacements. %s"
              % (preamble, corroboration, _withdrawn_oracles(record, dependencies)))
    if declares and declared:
        detail += (" The source span declares a slot boundary and states displacement(s) %s, all of "
                   "which are among the machine slot displacement(s), so its slot naming agrees with "
                   "the machine and is adjudicated here too"
                   % ", ".join(_hex(value) for value in sorted(declared)))
    elif declares:
        detail += (" The source span declares a slot boundary but states no slot displacement this "
                   "parser can read, so the two claims are reported separately: the machine dispatch "
                   "is proven, and the source's own slot naming is NOT verified by this check")
    elif declares is None:
        detail += (" No canonical source span is bound to this target, so nothing is claimed about a "
                   "reconstruction's slot naming; this verdict is about the machine alone")
    else:
        detail += (" The source span declares no slot boundary, so nothing is claimed about a "
                   "reconstruction's slot naming; this verdict is about the machine alone")
    return _check("PASS", detail, "complete")


def _check(status, detail, coverage="partial"):
    """A check dict shaped exactly like ``validate._check``'s output.

    The evidence paths are the two every other dimension check in this package
    reports, so the verdict sits in the same evidence graph as the arms it
    replaces.
    """
    return {"status": status, "detail": detail, "coverage": coverage,
            "evidence": [INDEX_REL, EVIDENCE_REL]}


def _withdrawn_oracles(record, dependencies):
    """The two oracles this dimension refuses to read, named for the detail.

    Not load-bearing -- a caller that never mentions them gets the same verdict.
    They are reported because a reader of a PASS on a body that dispatches is
    entitled to know the verdict did not come from the record's own vtable
    association (withdrawn in ``validate.py`` as contradicting the xref export) or
    from the export's vtable reference count (0 on essentially every record, and
    so not independent of the other).
    """
    vtables = (record or {}).get("vtables") or []
    references = (dependencies or {}).get("vtable_reference_count") or 0
    return ("Neither %s nor the xref export's %d vtable reference(s) was read: they are not "
            "independent of each other, so agreement with them would prove nothing."
            % ("the record's own association with %d vtable(s)" % len(vtables), references))
