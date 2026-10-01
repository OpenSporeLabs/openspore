"""FIELDS/OFFSETS read off the complete machine listing, alias-aware.

The check this module feeds already had two machine witnesses for "which
displacements does this body reach through its receiver": the machine-derived
``receiver`` record, and a scan of the listing's own memory operands filtered on
the *named* receiver register. Measured on the 418 committed reports the dimension
sat at ``PASS 55 / WARN 201 / NOT_AVAILABLE 162``, and three defects account for
the 201.

* **16** were a false contradiction. ``0x0067e6f0`` is the clean case: the
  complete 26-instruction listing shows ``CMP byte ptr [ECX + 0x64]``,
  ``MOV ESI,dword ptr [ECX + 0x50]`` and ``LEA EDI,[ECX + 0x4c]``, the source
  declares exactly ``0x4c, 0x50, 0x64``, and the derived record's ``bounds`` are
  ``{0x50, 0x60, 0x64}``. Every offset the source asserts is in the machine
  listing, and the verdict read *"1 displacement(s) (0x4c) lie outside the
  machine-derived receiver bounds ... so the source and the body disagree with the
  receiver record"*. That sentence is false. The listing is a complete, fully
  parsed body; the record says of itself ``bounds_only: true``, which is a
  statement about how far the body was *seen* reaching and not an enumeration of
  the receiver. A witness that declares itself incomplete cannot contradict a
  witness that is complete, and this module reads them the other way round.
* **16** were a false *absence*. The evidenced-absence arm reads
  ``not displacements and not declared_numbers`` -- the naive scan -- and asserts
  that "the body addresses no receiver field". For ``0x00c471c0`` the body opens
  ``MOV ESI,ECX`` and then reads ``[ESI]`` and ``[ESI + 0x130]``; for
  ``0x005dd7a0`` it opens ``MOV ESI,ECX`` and reaches ``0x5c``, ``0x102``,
  ``0xd1``, ``0x14`` and ``0x2c``. Those sixteen targets carry a PASS whose
  detail states something about the machine that the machine itself refutes. The
  record noticed -- both are ``shape: R-ALIAS`` -- which is why the existing
  wording has to append a clause explaining that the record saw displacements the
  scan could not. A hedge in the detail does not repair a false claim in it: the
  claim needs an alias-aware scan, not an apology.
* **158** are not a contradiction at all. 162 carry no complete listing or no
  receiver record, so no machine evidence exists to adjudicate against, and
  nothing here can move them or should pretend to.

Two further problems are structural rather than counted, and are why this is a
module and not a patch to one regex.

**Source-wide offsets against a receiver-only window.** ``OFFSET_LITERAL``
matches any ``+ 0x..`` or ``[0x..]`` in the span, so ``declared_numbers`` is
"every offset the source states anywhere", and it was then differenced against the
*receiver's* bounds. A source that declares an offset belonging to a second object
was reported as disagreeing with the receiver record. ``0x006a2ad0`` is the real
instance: the source declares ``0x4, 0x14, 0x18, 0x1c, 0x30`` and the verdict read
*"4 displacement(s) (0x4, 0x14, 0x18, 0x1c) lie outside the machine-derived
receiver bounds (0x0, 0x30) for ECX"*. Of those, ``0x18`` and ``0x30`` are
receiver displacements the machine shows through the ``EDI`` alias and the record
simply did not enumerate; ``0x4`` and ``0x14`` are offsets of the element and of
the receiver's table word; ``0x1c`` belongs to the argument object. The source's
own header partitions them exactly that way. Comparing them against a receiver
window is an apples-to-oranges test that manufactures a contradiction out of an
attribution the validator never attempted. So the source-wide set is kept, but it
is not compared against the receiver: each declared displacement is tiered by
*what witnesses it*, and only a witness that speaks about the receiver can settle
a receiver claim.

**An uncorroborated name held at WARN.** Fourteen targets reach the
``named_fields`` arm: the source names a member (``->active_index_0a8``,
``->bucket_count_008``) and the derived record is a set of displacements, so it can
neither confirm nor refute an identity. This module keeps that WARN, and the
argument is in ``_named_detail``: ``MEMBER_ACCESS`` is treated as a layout claim
precisely because naming a *type* is not one, so a member name is inside this
check's subject, and a PASS over it would be a PASS over a claim that was never
adjudicated -- the direction the FAIL-CLOSED rules forbid ("never infer field
layout to obtain a PASS"). It is also the honest resting state: no machine record
in the pack carries member names, so there is no evidence to wait for, and WARN is
this codebase's word for "adjudicated and ungrounded". A separate verdict field
would be the tidier instrument and is not representable -- the check dict is fixed
to ``_check``'s four keys -- while the detail is where both implementations
already report the offsets in the same span, and the reconstruction's own
convention of embedding the offset in the identifier (``active_index_0a8`` at
``0xa8``) narrows such a name to an offset claim plus a word: the offset half is
now settled by the listing, the word half is not, and the WARN is for the word.

The precedence implemented here, and why it is the honest reading of a
``bounds_only`` record: the ground truth for "which offsets the body reaches
through the receiver" is the **union** of the alias-aware scan of the complete
listing and the derived record's offsets, and where they differ **the listing
governs**. The listing is a complete, fully parsed instruction stream: it
enumerates the accesses that exist. The record is the inference's own observation,
and ``bounds_only`` is its own statement that the enumeration is open -- "this is
where the body was seen reaching" is a lower bound, and a lower bound cannot refute
anything. So a declared offset in the union is grounded and the detail names which
witness carried it; a declared offset outside it is an ungrounded claim, ``WARN``,
or ``FAIL`` where an *enumerating* record (``bounds_only is not True``) positively
excludes it and the complete listing does not show it either -- the existing
distinction, kept. And a declared offset the machine shows under *some* base is
neither: it is reported as unattributed, naming the bases it was seen under, and
no receiver contradiction is claimed for it, because the source asserted a
displacement, the body uses that displacement, and the only thing unestablished is
which object it sits on -- a limit of this check, not a defect of the
reconstruction.

The fail-closed direction runs through all of it. An absence claim needs a whole
body, so it needs a listing the machine parse consumed in full *and* a
``declared_count`` matching the instruction list; the third term is the one
``validate``'s ``listing_fully_parsed`` does not test, and a body the two disagree
about the size of is one neither can call whole. No ``PASS`` leaves this module
without a complete, fully consumed, count-matched listing. A missing ``receiver``
record is never read as "no fields": with no register the only absence this module
will speak to is the register-agnostic one, and every other case defers. A register
established on one arm of a branch is a ``may`` and grounds nothing on its own.
And nothing here reads or writes a runtime claim: the static dimension is the whole
of the subject.

``decide`` returns ``None`` -- defer to ``validate``'s own block, byte for byte --
in every case where the alias-aware evidence does not change the verdict or repair
a false statement in it, and never returns a weaker verdict than the block it would
replace. The wire-in is therefore behaviour-preserving by construction.
"""

import re

# ``validate.INDEX_REL`` / ``validate.EVIDENCE_REL``, restated because a check dict
# names its own evidence and this module must be readable without importing the
# validator. ``DriftGuard`` in the tests pins the two values to it.
INDEX_REL = "reconstruction/knowledge/index.json"
EVIDENCE_REL = "reconstruction/evidence"

# ``validate.MEMORY_OPERAND`` and ``validate.OPERAND_DISPLACEMENT``, restated for the
# same reason and for a second one: the scan below must classify operands exactly as
# the validator's own ``_receiver_displacements`` and ``_any_field_access`` do, or the
# two witnesses would disagree for a reason that has nothing to do with aliasing. The
# lookbehind on the displacement is what skips a scale factor (``[EAX*0x4 +
# 0x5dd840]``: ``0x4`` is a multiplier, not a displacement).
MEMORY_OPERAND = re.compile(r"\[([^\]]*)\]")
OPERAND_DISPLACEMENT = re.compile(r"(?<![\w.*])0[xX]([0-9a-fA-F]+)")
# A mnemonic and its operand text. ``IMPLICIT_MEMORY_MNEMONIC`` is not restated: it
# belongs to the register-agnostic absence, which this module asks the validator's own
# ``_any_field_access`` about rather than answering a second time.
MNEMONIC = re.compile(r"^\s*([A-Za-z][A-Za-z0-9]*)\b\s*(.*)$", re.DOTALL)

# The x86-32 general registers, spelled out rather than matched as ``[A-Za-z]{1,4}`` for
# the reason ``validate.INDIRECT_REGISTERS`` gives: a Ghidra operand prefix (``near
# ptr``, ``short``, ``dword ptr``) must never be read as a register. A sub-register
# spelling (``AL``, ``AX``, ``AH``) is deliberately absent, and that is a fail-closed
# decision rather than an oversight -- an 8- or 16-bit operand is a partial write, so
# the full 32-bit register's value afterwards is unknown, and the scan kills the full
# register rather than carry a value half of it contradicts.
REGISTERS = ("EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI")
REGISTER_TOKEN = re.compile(r"(?<![\w.])(%s)(?![\w])" % "|".join(REGISTERS), re.IGNORECASE)
# A destination written as ``dword ptr [ESI + 0x4]`` names a memory operand and not a
# register, so a store is recognised by the absence of a leading register token.
DESTINATION = re.compile(
    r"^(?:(?:byte|word|dword|qword|tword|oword|xmmword|short|near|far|ptr)\s+)*(%s)(?![\w])"
    % "|".join(REGISTERS), re.IGNORECASE)
# The legacy 8- and 16-bit spellings, with the full register each one is a window onto.
# They are matched only to be *killed*: an 8- or 16-bit write is a partial write, so the
# full register's value afterwards is unknown, and carrying the earlier value would claim
# a receiver attribution for a register the body has just partly overwritten. ``MOV BL,0x1``
# is the shape -- half of ``EBX`` changes and the rest does not, so nothing about what
# ``EBX`` now holds can be carried forward.
PARTIAL_REGISTER = re.compile(
    r"(?<![\w.])(AL|AH|AX|CL|CH|CX|DL|DH|DX|BL|BH|BX|SI|DI|BP|SP)(?![\w])", re.IGNORECASE)
PARTIAL_PARENT = {"AL": "EAX", "AH": "EAX", "AX": "EAX", "BL": "EBX", "BH": "EBX", "BX": "EBX",
                  "CL": "ECX", "CH": "ECX", "CX": "ECX", "DL": "EDX", "DH": "EDX", "DX": "EDX",
                  "SI": "ESI", "DI": "EDI", "BP": "EBP", "SP": "ESP"}

# Registers a call may destroy under the x86-32 Windows convention, which is what makes
# a chain survive a call: ``EBX``/``ESI``/``EDI``/``EBP`` are callee-saved, so an
# ``LEA``-derived interior pointer is still that pointer after the callee returns. This
# is a *must* and not a heuristic -- it is the one platform fact the scan relies on --
# and it is what lets ``0x006a2a80``'s ``LEA ESI,[EBX + 0x18]`` reach ``[ESI + 0x4]``
# across the ``CALL`` between them.
CALLER_SAVED = ("EAX", "ECX", "EDX")
# Mnemonics that provably write no register, so a mention is a read. ``LEA`` and
# ``PUSH`` are here as reads of their source operand; their own destination is handled
# explicitly below.
NO_REGISTER_WRITE = frozenset((
    "CMP", "TEST", "NOP", "LEA", "PUSH", "CLD", "STD", "BT", "BSF", "LZCNT",
    "CMPS", "MOVS", "STOS", "PREFETCH", "LFENCE", "MFENCE", "SFENCE"))
# Read-modify-write forms whose first operand is a memory operand write no register.
MEMORY_DESTINATION = frozenset((
    "ADD", "SUB", "AND", "OR", "XOR", "ADC", "SBB", "CMP", "TEST", "INC", "DEC",
    "NEG", "NOT", "SHL", "SHR", "SAR", "ROL", "ROR", "SHLD", "SHRD"))
# Forms that write their single operand.
UNARY_WRITE = frozenset(("NEG", "NOT", "INC", "DEC", "IDIV", "DIV", "MUL", "IMUL"))
# A control transfer ends the straight-line prefix. ``CALL`` is deliberately not one: it
# falls through, and the callee returns to the next instruction, so a value defined
# before it is still defined after it.
CONTROL_TRANSFER = frozenset(("JMP", "RET", "IRET", "IRETD", "INT", "INT3", "UD2", "HLT"))
# The largest displacement the scan will fold into a ``LEA`` chain. A ``LEA`` operand at
# or above this is an address computation and not an interior offset, and folding one
# would manufacture a receiver-relative displacement out of a global: measured, the
# largest offset any committed ``receiver`` record enumerates is 5748 (``0x1674``), so
# the bound costs no real field and refuses the ambiguous case.
CHAIN_LIMIT = 0x10000

# Statuses and their order of strength. ``FAIL`` is a *finding* rather than a strength,
# so it ranks lowest: this module may replace a FAIL it can show is not warranted, and
# may never replace a PASS with a WARN.
RANK = {"PASS": 3, "WARN": 2, "NOT_AVAILABLE": 1, "UNKNOWN": 1, "FAIL": 0}
# How many offsets a detail names before it counts the rest. The largest committed set
# is nine, and a detail is one line of a table, so it has to stay one line.
MAX_NAMED = 8


def _hex(values):
    """``values`` as a readable, numerically ordered ``0x..`` list."""
    return ", ".join("0x%x" % value for value in sorted(set(values))) or "none"


def _named(values, limit=MAX_NAMED):
    """``_hex`` with a summary tail, so a detail stays one line of a table."""
    ordered = sorted(set(values))
    if len(ordered) <= limit:
        return _hex(ordered)
    return "%s and %d more" % (_hex(ordered[:limit]), len(ordered) - limit)


def _canonical(token):
    """``token`` as a full 32-bit register name, or ``None``."""
    text = str(token or "").upper()
    return text if text in REGISTERS else None


def _parse(text):
    """``(mnemonic, operands)`` for one listing line, or ``None``.

    ``None`` means the line could not be read as an instruction, which is the one
    thing the scan refuses to guess about: an unread line could be anything, including
    the copy that establishes an alias, so ``bounded`` goes false and no ``must``
    claim survives. An unbalanced bracket is the same case -- the operand it opens may
    be the memory operand whose displacement is at stake.
    """
    match = MNEMONIC.match(str(text or ""))
    if not match:
        return None
    operands = match.group(2).strip()
    if operands.count("[") != operands.count("]"):
        return None
    return match.group(1).upper(), ([part.strip() for part in operands.split(",")]
                                    if operands else [])


def _memory_operands(operands):
    """``(index, base register, displacements)`` for each bracketed operand.

    The first register in the bracket is the base: Ghidra spells an indexed operand
    ``[EAX + ECX*4 + 0x10]``, so the base comes first and the index follows, and a
    bracket with no register at all (``[0x5dd840]``) is an absolute address with no
    base to attribute anything to. A register that follows ``*`` is an index, not a
    base, and is skipped.
    """
    found = []
    for position, operand in enumerate(operands or ()):
        for match in MEMORY_OPERAND.finditer(operand):
            inner = match.group(1)
            base = None
            for token in REGISTER_TOKEN.finditer(inner):
                if inner[token.start() - 1:token.start()] == "*":
                    continue
                base = _canonical(token.group(1))
                break
            found.append((position, base,
                          [int(value, 16) for value in OPERAND_DISPLACEMENT.findall(inner)]))
    return found


def _destination(operand):
    """The full 32-bit register ``operand`` writes, or ``None``.

    ``None`` for a memory destination, for a partial-register spelling, and for an
    operand that is not a register at all. Each of those means the full register has to be
    treated as killed, which is what ``_mentioned`` collects.
    """
    match = DESTINATION.match(str(operand or ""))
    return _canonical(match.group(1)) if match else None


def _mentioned(text):
    """Every full register ``text`` names, whole or as a window onto one.

    Used to kill: an instruction this scan does not model, and a destination spelled
    partially. Both are the same question -- which registers could this line have
    changed beyond what the modelled forms account for.
    """
    found = {_canonical(token.group(1)) for token in REGISTER_TOKEN.finditer(str(text or ""))}
    found.update(PARTIAL_PARENT[token.group(1).upper()]
                 for token in PARTIAL_REGISTER.finditer(str(text or "")))
    found.discard(None)
    return found


def _is_conditional(mnemonic):
    """Whether ``mnemonic`` is a conditional branch (``JMP`` excluded)."""
    return (len(mnemonic) in (2, 3, 4) and mnemonic[0] == "J" and mnemonic != "JMP"
            and mnemonic[1:].isalpha())


def _kill(destination, operand, branched_at, state):
    """Invalidate whatever ``operand`` writes: a full register, a window onto one, or nothing."""
    if destination is not None:
        _define(destination, None, branched_at, state)
        return
    for register in _mentioned(operand):
        _define(register, None, branched_at, state)


def _define(register, value, branched_at, state):
    """Install ``value`` (an offset, or ``None`` to kill) for ``register``.

    A value established after the first control transfer is a ``may``: its definition
    may not have run on the path that reaches a later use. The receiver parameter is
    the exception and is not special-cased here -- it is installed as a ``must`` before
    the loop, and only a write to it can take that away.
    """
    if register is None:
        return
    if value is None:
        state.pop(register, None)
        return
    state[register] = (value, branched_at is None)


def receiver_offsets(texts, register):
    """Receiver-relative displacements the body reaches, alias-aware.

    A thin, stable wrapper over ``_scan``, and deliberately not the function ``decide``
    calls: a verdict read through a patchable public seam is a verdict about the patch,
    and the two are separated here so that patching this name -- the obvious thing for a
    test or a caller to do -- cannot move a check. ``MutationGuards`` in the tests
    asserts exactly that, because the separation is invisible at the call site and
    therefore has to be pinned.

    Returns ``{"must", "may", "aliases", "unresolved", "bounded"}``.

    ``must`` is the set of offsets the body *provably* reaches through the receiver or
    through a register derived from it, and it is what grounds a declared offset.
    ``may`` is the same measurement for a value that could not be proven -- a register
    the body copies or derives from the receiver *after* control flow has branched is a
    witness, not a proof, and grounds nothing on its own. ``aliases`` records every
    attribution with the register it was read through, the operand's own displacement
    and the absolute offset it composes to, so a reader can watch a chain resolve
    instead of taking the composition on trust. ``unresolved`` holds the lines that
    could not be parsed, and ``bounded`` is false whenever that list is non-empty -- or
    whenever no analysis ran at all, which is what a missing ``register`` produces.

    Four shapes make an access attributable, and each is a machine fact rather than a
    pattern:

    * the receiver register's own operands, which need no alias at all. A bare
      ``[ECX]`` is offset zero: the word at the base *is* a field claim, and a scan that
      only collected displacements would read it as the absence of one.
    * a **copy** -- ``MOV EBX,ECX``, which is how ``0x006a2a80`` and ``0x006a2ad0`` both
      open -- and ``XCHG``, which makes each register hold the other's old value.
    * an **address chain** -- ``LEA ESI,[EBX + 0x18]`` then ``[ESI + 0x4]``. The chain
      composes: the second access is the *receiver* at ``0x18 + 0x4``, so ``0x1c`` is
      what the body reaches and ``0x4`` is a displacement from an interior address,
      which is not a receiver offset. Both numbers are reported -- the absolute in
      ``must``, the chain's own displacement in ``aliases`` -- because folding ``0x4``
      into a receiver claim is precisely the error this module exists to remove:
      ``0x006a2ad0``'s ``0x4`` is a field of the *element*, and clearing it as a
      receiver field is the false attribution that put four displacements "outside the
      receiver bounds" in that verdict.
    * a ``PUSH``/``POP`` pair, honoured only inside the straight-line prefix. A pop
      after a branch need not pair with the push that precedes it in listing order, so
      outside the prefix the popped register is killed instead.

    A value is **invalidated** by any write to its register: a loaded value kills the
    register (``MOV ESI,[ECX + 0x50]`` makes ``ESI`` a node pointer and not an interior
    receiver address), a call kills the caller-saved set, and any instruction whose
    register-write effect this scan does not model kills every register it mentions.
    Killing too much costs a witness; keeping a dead value would invent an offset the
    body never touches, and the second error is the one that puts a claim in a verdict.

    The must/may split is a dominance argument in listing order, and its one assumption
    is stated rather than hidden. The receiver register is the function's *parameter*,
    so its incoming value is live on every path and stays a ``must`` until something
    writes it; a value *derived* from it counts as a ``must`` only while its definition
    lies in the straight-line prefix every path from the function entry executes. A
    definition after the first control transfer may or may not have run, so everything
    derived from it is a ``may``. ``0x0067e6f0`` is what makes both halves necessary: its
    receiver accesses sit after a ``JZ`` and are still musts, because they go through
    the parameter, while a ``LEA``-derived pointer set up after that branch would be
    only a may.
    """
    return _scan(texts, register)


def _scan(texts, register):
    """The scan itself. See ``receiver_offsets``, which is the documented entry point."""
    source = _canonical(register)
    report = {"must": set(), "may": set(), "aliases": [], "unresolved": [], "bounded": False}
    if source is None:
        # No base register means no base to attribute a displacement to. Reporting
        # nothing is the only honest answer, and ``bounded`` is false because nothing
        # was analysed: a caller's use of that flag is "may this be read as a complete
        # enumeration", and nothing here is one.
        return report
    state = {source: (0, True)}
    shadow = []
    unresolved = []
    aliases = []
    branched_at = None
    for position, text in enumerate(texts or ()):
        line = str(text or "")
        parsed = _parse(line)
        if parsed is None:
            unresolved.append(line)
            continue
        mnemonic, operands = parsed
        for _index, base, displacements in _memory_operands(operands):
            if base not in state:
                continue
            offset, proven = state[base]
            for displacement in (displacements or [0]):
                absolute = offset + displacement
                (report["must"] if proven else report["may"]).add(absolute)
                aliases.append({"register": base, "displacement": displacement,
                                "absolute": absolute, "must": proven, "instruction": line})
        # -- register writes, most specific form first -------------------------
        if mnemonic == "LEA" and len(operands) == 2 and "[" in operands[1]:
            destination = _destination(operands[0])
            memory = _memory_operands([operands[1]])
            value = None
            if memory and memory[0][1] in state and len(memory[0][2]) <= 1:
                step = memory[0][2][0] if memory[0][2] else 0
                if step < CHAIN_LIMIT:
                    value = state[memory[0][1]][0] + step
            _define(destination, value, branched_at, state)
        elif mnemonic == "MOV" and len(operands) == 2:
            destination = _destination(operands[0])
            value = None
            if "[" not in operands[1]:
                source_register = _canonical(operands[1])
                if source_register in state:
                    value = state[source_register][0]
            if destination is None:
                for register in _mentioned(operands[0]):
                    _define(register, None, branched_at, state)
            else:
                _define(destination, value, branched_at, state)
        elif mnemonic == "XCHG" and len(operands) == 2:
            first = _destination(operands[0]) or _canonical(operands[0])
            second = _destination(operands[1]) or _canonical(operands[1])
            held = [state[register][0] if register in state else None
                    for register in (first, second)]
            _define(first, held[1], branched_at, state)
            _define(second, held[0], branched_at, state)
        elif mnemonic == "PUSH" and len(operands) == 1:
            if branched_at is None:
                pushed = _canonical(operands[0])
                shadow.append(state[pushed][0] if pushed in state else None)
        elif mnemonic == "POP" and len(operands) == 1:
            _define(_destination(operands[0]),
                    shadow.pop() if (branched_at is None and shadow) else None,
                    branched_at, state)
        elif mnemonic == "CALL":
            for register in CALLER_SAVED:
                state.pop(register, None)
        elif mnemonic in CONTROL_TRANSFER or _is_conditional(mnemonic):
            if branched_at is None:
                branched_at = position
            shadow = []
        elif mnemonic in NO_REGISTER_WRITE:
            pass
        elif mnemonic in MEMORY_DESTINATION and operands and "[" in operands[0]:
            pass
        elif mnemonic in MEMORY_DESTINATION and len(operands) == 2:
            _kill(_destination(operands[0]), operands[0], branched_at, state)
        elif mnemonic in UNARY_WRITE and len(operands) == 1:
            _kill(_destination(operands[0]), operands[0], branched_at, state)
        else:
            # Not a form this scan models. Killing every register the line mentions is
            # the fail-closed direction: it can only lose a witness, never invent one,
            # and a witness lost here is reported as unproven rather than wrong.
            for register in _mentioned(line):
                _define(register, None, branched_at, state)
    report["aliases"] = aliases
    report["unresolved"] = unresolved
    report["bounded"] = not unresolved
    return report


# -- reading the pack ------------------------------------------------------


def _check(status, detail, coverage="partial", evidence=None):
    """The shape ``validate._check`` returns.

    Restated rather than imported so this module is readable and testable on its own;
    ``DriftGuard`` asserts the two agree key for key, so a change to the validator's
    shape is a failing test here and not a silently malformed check.
    """
    return {"status": status, "detail": detail, "coverage": coverage, "evidence": evidence or []}


def _oracle():
    """``validate``'s own FIELDS/OFFSETS readers, imported rather than re-derived.

    Which function names a machine record, which displacements a source span declares,
    and whether a body addresses memory at all *are* the FIELDS/OFFSETS check's
    definitions, and re-deriving any of them here would be a second, drifting copy of
    the rule this module exists to feed. The import is inside the function because
    ``validate`` is the module that calls ``decide``: at call time ``validate`` is fully
    initialised, so the direction of the edge is unambiguous.
    """
    from . import validate
    return validate


def _read_facts(oracle, categories, abi_outer, abi_inner, listing, scoped_text):
    """Everything the arms read out of the pack, through ``validate``'s helpers.

    Two completeness predicates come back, and they are deliberately different.
    ``fully_parsed`` is this module's: the parse record exists, it is neither degraded
    nor short of instructions, *and* its ``declared_count`` equals the instruction
    list's own length -- the third term is the one ``validate``'s
    ``listing_fully_parsed`` does not test, and a body the two disagree about the size
    of is a body neither can call whole. ``parse_consumed`` is ``validate``'s weaker one,
    reproduced so the naive status this module compares itself against is the verdict
    the validator would really have reached.
    """
    receiver = oracle._machine_record(categories, abi_outer, abi_inner, "receiver")
    bounds = set(value for value in (receiver.get("offsets") or []) if isinstance(value, int))
    declared = oracle._field_declarations(scoped_text)
    texts = listing[1]
    parse = oracle._machine_record(categories, abi_outer, abi_inner, "parse")
    parse_consumed = bool(parse) and parse.get("degraded") is not True and not (parse.get("unparsed") or 0)
    fully_parsed, note = _parse_state(parse, len(texts))
    return {
        "register": receiver.get("register"),
        "bounds": bounds,
        "bounds_only": receiver.get("bounds_only"),
        "declared": declared,
        "declared_numbers": oracle._declared_displacements(declared),
        "named_fields": sorted(entry for entry in declared if entry.startswith("field ")),
        "any_field": oracle._any_field_access(texts),
        "body": _body_displacements(texts),
        "parse_consumed": parse_consumed,
        "fully_parsed": fully_parsed,
        "note": note,
    }


def _parse_state(parse, count):
    """``(whole body, note)`` for a parse record against a listing of ``count``.

    The note is the sentence the verdict quotes, so it states the measurement rather
    than a verdict: a reader has to be able to see which of the three conditions held.
    """
    if not parse:
        return False, "no machine parse record was collected for this listing"
    degraded = parse.get("degraded") is True
    unparsed = int(parse.get("unparsed") or 0)
    declared = parse.get("declared_count")
    if not isinstance(declared, int):
        return False, "the machine parse record counts no instructions of its own"
    if declared != count:
        return False, ("the machine parse declared %d instruction(s) and the listing holds %d, so the two "
                       "disagree about the body" % (declared, count))
    if degraded or unparsed:
        return False, ("it was not consumed in full by the machine parse (%d of %d instruction(s) read, "
                       "degraded=%s, unparsed=%d)" % (declared - unparsed, declared, degraded, unparsed))
    return True, ("it was consumed in full by the machine parse (declared_count=%d, degraded=false, "
                  "unparsed=0)" % declared)


def _body_displacements(texts):
    """Every displacement the complete listing shows, under any base register.

    The weakest of the witnesses, and the only one that says nothing about *which*
    object a displacement belongs to. It exists for one question: is a displacement the
    source states present in the body at all? A displacement the machine shows somewhere
    cannot be a claim about a field that does not exist, and this set is what keeps such
    a claim from being reported as a receiver contradiction.
    """
    found = set()
    for text in texts or ():
        for match in MEMORY_OPERAND.finditer(str(text or "")):
            for value in OPERAND_DISPLACEMENT.findall(match.group(1)):
                found.add(int(value, 16))
    return found


def _witness_bases(texts, wanted):
    """Which base registers the listing shows ``wanted`` displacements under.

    Named in the detail so an unattributed displacement is reported as "this body uses
    it, on that base" rather than as a bare number the reader has to take on trust. A
    displacement seen through the receiver is excluded by the caller, so what is left
    here is genuinely some other object.
    """
    bases = {}
    for text in texts or ():
        for match in MEMORY_OPERAND.finditer(str(text or "")):
            inner = match.group(1)
            base = "no register"
            for token in REGISTER_TOKEN.finditer(inner):
                if inner[token.start() - 1:token.start()] == "*":
                    continue
                base = str(token.group(1)).upper()
                break
            for value in OPERAND_DISPLACEMENT.findall(inner):
                number = int(value, 16)
                if number in wanted:
                    bases.setdefault(number, set()).add(base)
    if not bases:
        return "no base register at all"
    return "; ".join("0x%x under %s" % (number, ", ".join(sorted(bases[number])))
                     for number in sorted(bases))


def _naive(oracle, texts, register, bounds, bounds_only, declared, declared_numbers,
           named_fields, parse_consumed, any_field):
    """``(status, reason)`` for the verdict ``validate``'s own block reaches.

    Computed to decide *whether to speak* and to guarantee this module never returns a
    weaker verdict, not to judge anything. Every fact it reads comes from ``validate``'s
    own helpers, so the conditions cannot drift from the block they mirror; only the
    reasons are named here, because a reason is what decides whether a same-status
    verdict is still worth replacing.
    """
    if register:
        displacements = oracle._receiver_displacements(texts, register)
        if (declared_numbers - bounds) and bounds_only is not True:
            return "FAIL", "refutation"
        if (displacements | declared_numbers) - bounds:
            return "WARN", "outside_bounds"
        if named_fields:
            return "WARN", "uncorroborated_name"
        if not displacements and not declared_numbers:
            return "PASS", "absence"
        return "PASS", "grounded"
    if declared:
        return "WARN", "no_record_to_check_against"
    if parse_consumed and not any_field:
        return "PASS", "absence_without_a_register"
    return "NOT_AVAILABLE", "no_evidence"


# -- the verdict -----------------------------------------------------------


def _precedence(listing_size, register, scan, bounds, fully_parsed, note):
    """The clause stating which witness governed, and where they differ.

    A ``bounds_only`` record says where the body was *seen* reaching; the complete
    listing enumerates the accesses that exist. So the listing governs, the record widens
    what a receiver-relative claim may be grounded in, and any difference is stated
    rather than resolved silently -- a reader has to be able to see that a displacement
    the record does not enumerate is not thereby absent, and that one it enumerates and
    the listing does not show is a statement about the inference rather than about the
    body.
    """
    proven = set(scan["must"])
    maybe = set(scan["may"])
    only_record = bounds - proven - maybe
    clauses = ["the %d-instruction listing is the governing witness for what this body reaches -- %s -- and "
               "it is read alias-aware over receiver register %s, so that a copy, an XCHG, an address chain "
               "and a push/pop pair all keep the receiver attribution"
               % (listing_size, note, register),
               "the scan attributes %d displacement(s) to the receiver as proven (%s) and %d more only on "
               "one arm of a branch, which is a may and grounds nothing (%s)"
               % (len(proven), _hex(proven), len(maybe), _hex(maybe))]
    if bounds:
        clauses.append("the machine-derived receiver record enumerates %d displacement(s) (%s), which is "
                       "its own observation of where the body was seen reaching; its bounds_only flag is "
                       "its own statement that the enumeration is open, so it widens what a claim may be "
                       "grounded in and refutes nothing" % (len(bounds), _hex(bounds)))
    if only_record:
        clauses.append("%d of those (%s) the scan does not attribute to the receiver, and the listing "
                       "governs there" % (len(only_record), _hex(only_record)))
    if proven - bounds:
        clauses.append("the listing shows %d displacement(s) the record does not enumerate (%s), and a "
                       "complete listing outranks a record that declares itself incomplete"
                       % (len(proven - bounds), _hex(proven - bounds)))
    if not fully_parsed:
        clauses.append("all of that is a lower bound: the evidence is not known to be the whole body, so "
                       "no absence is claimed from it")
    return "; ".join(clauses)


def _absence(register, listing_size, note):
    """The evidenced absence of receiver field access, for a named register.

    Two claims, kept apart. The body addresses no receiver field, and that rests on the
    complete listing, on the machine parse having consumed it whole, and on a scan that
    follows a copy, an XCHG, an address chain and a push/pop pair -- so a field access
    made through a register the receiver was moved into is still seen, and the negative
    claim is worth something. The receiver's layout is not established by any of it and is
    not claimed.
    """
    return ("the complete %d-instruction listing is the whole body: %s; the alias-aware scan of it over "
            "receiver register %s finds no memory operand addressed through the receiver or through any "
            "register derived from it -- it follows a copy, an XCHG, an address chain and a push/pop pair, "
            "so a field access made through a register the receiver was moved into would still be seen -- "
            "which is evidence that this body addresses no receiver field; the source span declares no "
            "field offset either, so there is no offset here to ground and none is claimed to exist; "
            "which member sits at which displacement is not established by any record in this pack and is "
            "not claimed here" % (listing_size, note, register))


def _absence_without_register(listing_size, note):
    """The evidenced absence for a body whose receiver the record never named.

    The register-agnostic state, and the one case where a pass says nothing at all about a
    receiver: the record abstained, so the receiver's identity and its layout are
    unclaimed in both directions and neither is established here. What is claimed rests
    on the listing and nothing else -- it is complete, the machine parse consumed it in
    full, and it names no memory operand through any register at all, so the body
    addresses no object and so no receiver field. A single bracket anywhere, through any
    register, with or without a displacement, takes the body out of this state.
    """
    return ("the machine-derived ABI record names no receiver register, so this pass claims nothing about "
            "the receiver: its identity and its layout are unclaimed in both directions and neither is "
            "established here; separately, the complete %d-instruction listing names no memory operand "
            "through any register at all and %s, which is the "
            "evidence that this function performs no field access; the source span declares no field offset "
            "either, so there is no offset here to ground and none is claimed to exist"
            % (listing_size, note))


def _grounded(register, listing_size, note, scan, bounds, fully_parsed, declared_numbers,
              grounded, unattributed, may_only, bases):
    proven = set(scan["must"])
    if declared_numbers:
        clauses = ["the source span declares %d displacement(s) (%s) and every one of them is a displacement "
                   "the complete %d-instruction listing shows: %d attributed to the receiver %s as proven "
                   "(%s)" % (len(declared_numbers), _named(declared_numbers), listing_size,
                              len(grounded & proven), register, _hex(grounded & proven))]
    else:
        clauses = ["the source span declares no field offset, so there is nothing of its own to ground and "
                   "nothing ungrounded either; the complete %d-instruction listing nevertheless reaches %d "
                   "receiver displacement(s) through %s (%s), all of which the record accounts for or the "
                   "listing is the better witness on" % (listing_size, len(proven), register, _hex(proven))]
    carried = grounded - proven
    if carried:
        clauses.append("%d more (%s) are grounded in the machine-derived receiver record rather than in the "
                       "scan" % (len(carried), _hex(carried)))
    if unattributed:
        clauses.append("%d more (%s) are shown by the listing under a base that is not the receiver -- %s -- "
                       "so the body does use those displacements, on an object this check cannot identify; "
                       "that is a limit of the attribution here and not a disagreement with the receiver, and "
                       "no receiver contradiction is claimed for them"
                       % (len(unattributed), _hex(unattributed), bases))
    if may_only:
        clauses.append("%d (%s) are reached through the receiver only on one arm of a branch, which is a may "
                       "witness and does not ground an offset on its own"
                       % (len(may_only), _hex(may_only)))
    clauses.append(_precedence(listing_size, register, scan, bounds, fully_parsed, note))
    return "; ".join(clauses)


def _ungrounded(register, listing_size, note, scan, bounds, bounds_only, declared_numbers,
                ungrounded, fail):
    proven = set(scan["must"])
    named = ", ".join("0x%x" % value for value in sorted(ungrounded))
    if fail:
        return ("the source-vs-listing rule: %d of the %d displacement(s) the source span declares (%s) "
                "appear nowhere in the complete %d-instruction listing, under any base register, and the "
                "machine-derived receiver record is an enumeration (bounds_only is false) that does not "
                "contain them either; the listing was read whole (%s) and the alias-aware scan over %s "
                "attributed %d receiver displacement(s) (%s) to it, so this is a refuted claim and not a "
                "scan that could not follow the receiver"
                % (len(ungrounded), len(declared_numbers), named, listing_size, note, register,
                   len(proven), _hex(proven)))
    return ("%d of the %d displacement(s) the source span declares (%s) appear nowhere in the complete "
            "%d-instruction listing, under any base register, and are not among the %d the machine-derived "
            "receiver record enumerates (%s), so the reconstruction states a field offset the machine does "
            "not show; the record is bounds_only, so it states where the body was seen reaching and cannot "
            "refute the claim either, which is why this is a review item and not a failure; the listing was "
            "read whole (%s) and the alias-aware scan over %s attributed %d receiver displacement(s) (%s) "
            "to it, so the absence is not a scan that could not follow the receiver"
            % (len(ungrounded), len(declared_numbers), named, listing_size, len(bounds), _hex(bounds),
               note, register, len(proven), _hex(proven)))


def _may_only(register, listing_size, note, scan, bounds, fully_parsed, declared_numbers, may_only):
    return ("%d of the %d displacement(s) the source span declares (%s) are reached through the receiver "
            "only on one arm of a branch: the register carrying them is established after control flow has "
            "split, so each is a may witness, and a may grounds no declared offset on its own; %s"
            % (len(may_only), len(declared_numbers), _named(may_only),
               _precedence(listing_size, register, scan, bounds, fully_parsed, note)))


def _named_only(named_fields, register, listing_size, note, scan, bounds, fully_parsed,
                declared_numbers):
    return ("the source span names %d member(s) (%s) and no machine record in this pack carries member "
            "names, so the identity of the member at a given displacement can be neither confirmed nor "
            "refuted by any machine evidence here and the name stays a review item: a displacement is a "
            "location claim and this pack settles those, a name is an identity claim and it settles none; "
            "the %d displacement(s) declared alongside (%s) are reported above with the witness each one "
            "rests on; %s"
            % (len(named_fields), ", ".join(entry[6:] for entry in named_fields[:4]),
               len(declared_numbers), _hex(declared_numbers),
               _precedence(listing_size, register, scan, bounds, fully_parsed, note)))


def _unproven(register, listing_size, note, scan, bounds, declared_numbers, proven):
    return ("the source span declares %d displacement(s) (%s) and the alias-aware scan of the listing "
            "attributes %d receiver displacement(s) (%s) to %s, so nothing the source states is missing from "
            "what the machine shows; but the listing is not known to be the whole body (%s), so that "
            "enumeration is a lower bound and is reported as one rather than as a pass; %s"
            % (len(declared_numbers), _named(declared_numbers), len(proven), _hex(proven), register, note,
               _precedence(listing_size, register, scan, bounds, False, note)))


def decide(*, record, categories, abi_outer, abi_inner, listing,
           scoped_text, target_span, source_path):
    """The FIELDS/OFFSETS verdict taken over the alias-aware scan, or ``None`` to defer.

    ``None`` means "this module has nothing to add here", and every arm of
    ``validate``'s own block then applies unchanged, byte for byte. It is returned when
    there is no complete listing to scan (no new evidence exists), when the reading
    helpers cannot be reached (the facts would be read differently from the ones the
    validator reads), when the machine-derived record names no register and the body is
    not the register-agnostic absence (a missing record is not a record of "no fields",
    so no other claim is made on its behalf), when this module's verdict would be weaker
    than the one it would replace, and when the verdict is the same status for the same
    reason.

    It speaks in three situations, and each is a repair rather than a preference:

    * the alias-aware evidence grounds a source claim the receiver record alone would
      have called a contradiction -- ``0x0067e6f0``'s ``0x4c``, and ``0x0067e730``'s
      ``0x4c`` and ``0x50``, all three ``LEA``-derived, all in the complete listing, all
      absent from a record that declares itself ``bounds_only``;
    * the scan shows the machine *does* reach a receiver field where the existing absence
      arm asserts that it does not, so a PASS whose detail is a false statement about the
      body is replaced by one that names the offsets -- ``0x00c471c0`` and ``0x005dd7a0``
      among sixteen;
    * the register-agnostic absence, which this module owns and states with the
      count-match half of the completeness guard the existing wording does not carry, so
      the state is first-class rather than incidental.

    ``source_path``, ``target_span`` and ``record`` are accepted and not read. The span
    is already resolved into ``scoped_text``, which is what the declaration scan
    consumes, and judging an absent source is not this dimension's business:
    ``validate`` reports that once and uniformly, and this module must not report it
    twice or differently.
    """
    if listing is None:
        return None
    try:
        oracle = _oracle()
        facts = _read_facts(oracle, categories, abi_outer, abi_inner, listing, scoped_text)
    except (ImportError, AttributeError):
        # A helper this module reads by name is gone or renamed. Deferring is the safe
        # direction: the validator's own block then judges the pack exactly as it did
        # before, which is never a worse answer than a half-read one.
        return None
    texts = listing[1]
    listing_size = len(texts)
    register = facts["register"]
    declared = facts["declared"]
    declared_numbers = facts["declared_numbers"]
    named_fields = facts["named_fields"]
    bounds = facts["bounds"]
    bounds_only = facts["bounds_only"]
    fully_parsed = facts["fully_parsed"]
    note = facts["note"]
    scan = _scan(texts, register) if register else {
        "must": set(), "may": set(), "aliases": [], "unresolved": [], "bounded": False}
    naive_status, naive_reason = _naive(oracle, texts, register, bounds, bounds_only, declared,
                                        declared_numbers, named_fields, facts["parse_consumed"],
                                        facts["any_field"])

    verdict = _adjudicate(register, listing_size, note, scan, bounds, bounds_only, fully_parsed,
                          declared, declared_numbers, named_fields, facts["body"], facts["any_field"],
                          texts)
    if verdict is None:
        return None
    status = verdict["status"]
    # Never weaker than the verdict being replaced. ``FAIL`` is exempt because it is a
    # finding rather than a strength, and the tiering above is what shows the finding was
    # not warranted: the offset is in the machine body, or the record is not an
    # enumeration.
    if RANK[status] < RANK[naive_status] and naive_status != "FAIL":
        return None
    stronger = RANK[status] > RANK[naive_status]
    proven, maybe = set(scan["must"]), set(scan["may"])
    outside = (oracle._receiver_displacements(texts, register) | declared_numbers) - bounds if register else set()
    # A reason the alias-aware evidence contradicts outright: every displacement the
    # existing block called a disagreement is one the machine body or the receiver-relative
    # scan accounts for.
    falsified = naive_reason == "outside_bounds" and outside <= (proven | maybe | facts["body"])
    absence_repair = naive_reason == "absence" and bool(proven or maybe)
    owned = naive_reason == "absence_without_a_register" and status == "PASS"
    # A refutation this module reaches the same way, with a second witness. The validator
    # refutes on the record alone; this reaches the same FAIL having also read the
    # complete listing and found the displacement under no base register at all, which is
    # what turns "the record does not contain it" into "the machine does not show it".
    corroborated = naive_status == "FAIL" and status == "FAIL"
    if not (stronger or falsified or absence_repair or owned or corroborated):
        return None
    return _check(status, verdict["detail"], verdict["coverage"], [INDEX_REL, EVIDENCE_REL])


def _adjudicate(register, listing_size, note, scan, bounds, bounds_only, fully_parsed,
                declared, declared_numbers, named_fields, body, any_field, texts):
    """The arm for this pack, as ``{"status", "detail", "coverage"}``, or ``None``.

    ``None`` is a deferral: this module declines to speak rather than returning a verdict
    it cannot support. The arms are ordered loudest first, the same way the validator's
    are, because a refuted claim outranks a name nobody could confirm, and both outrank
    a pass.
    """
    if not register:
        # With no register there is no receiver-relative claim to make in either
        # direction, and a missing record is not a record of "no fields". The one state
        # that needs no receiver is the register-agnostic absence, and it needs a body
        # that addresses no memory operand at all.
        if declared or any_field or not fully_parsed:
            return None
        return {"status": "PASS", "detail": _absence_without_register(listing_size, note),
                "coverage": "complete"}
    proven = set(scan["must"])
    maybe = set(scan["may"])
    ungrounded = declared_numbers - (proven | maybe | bounds | body)
    may_only = (declared_numbers & maybe) - proven - bounds
    unattributed = (declared_numbers & body) - proven - maybe - bounds
    grounded = declared_numbers & (proven | bounds)
    # Only an *enumerating* record can refute a declared offset, and only once the
    # complete listing has failed to show it as well. ``bounds_only`` is a lower bound by
    # its own account, so with it the claim is uncorroborated rather than contradicted.
    fail = bool(ungrounded) and bounds_only is not True
    whole = fully_parsed and scan["bounded"]
    if ungrounded:
        return {"status": "FAIL" if fail else "WARN",
                "detail": _ungrounded(register, listing_size, note, scan, bounds, bounds_only,
                                      declared_numbers, ungrounded, fail),
                "coverage": "partial"}
    if not declared_numbers and not named_fields and not (proven | maybe | bounds):
        if not whole:
            # The evidenced absence needs a whole body, and this is not one. Deferring
            # leaves the validator's own arm in place rather than downgrading a verdict
            # this module has no standing to weaken.
            return None
        return {"status": "PASS", "detail": _absence(register, listing_size, note),
                "coverage": "complete"}
    if may_only:
        return {"status": "WARN",
                "detail": _may_only(register, listing_size, note, scan, bounds, fully_parsed,
                                    declared_numbers, may_only),
                "coverage": "partial"}
    if named_fields:
        return {"status": "WARN",
                "detail": _named_only(named_fields, register, listing_size, note, scan, bounds,
                                      fully_parsed, declared_numbers),
                "coverage": "partial"}
    if not whole:
        return {"status": "WARN",
                "detail": _unproven(register, listing_size, note, scan, bounds, declared_numbers,
                                    proven),
                "coverage": "partial"}
    return {"status": "PASS",
            "detail": _grounded(register, listing_size, note, scan, bounds, fully_parsed,
                                declared_numbers, grounded, unattributed, may_only,
                                _witness_bases(texts, unattributed)),
            "coverage": "complete"}

