import re
from pathlib import Path

from .evidence_datarefs import authoritative_data_refs as _read_data_refs
from .models import (ROOT, ToolError, file_sha256, load_json, normalize_va, relative, sha256_json,
                     write_json_atomic, write_text_atomic)

INDEX_REL = "reconstruction/knowledge/index.json"
EVIDENCE_REL = "reconstruction/evidence"
# The Ghidra data-reference artifact ``evidence_datarefs`` reads, named here so a
# check dict can cite it. Restated from that module and pinned by its tests, so a
# move of the artifact is a failing test rather than a silently uncited check.
DATAREF_REL = "knowledgegraph/triage/datarefs-2540f2ca.tsv"
SOURCE_SUFFIXES = (".c", ".cc", ".cpp", ".cxx", ".h", ".hpp")
SOURCE_ROLES = (("src/", "canonical"), ("reconstruction/staging/", "staging"))
RETURN_DECL = re.compile(r"(?m)^\s*(?:(?:extern\s+\"C\"|extern|static|inline|constexpr)\s+)*(?P<return>(?:const\s+)?[A-Za-z_][A-Za-z0-9_:<>*&]*)\s+(?:(?:[A-Z][A-Z0-9_]*|__[A-Za-z0-9_]+)\s+)*(?P<name>[A-Za-z_][A-Za-z0-9_:]*)\s*\([^;{}]*\)\s*(?:const\s*)?\{")
DEFINE = re.compile(r"(?m)^[ \t]*#[ \t]*define[ \t]+(?P<name>[A-Za-z_][A-Za-z0-9_]*)(?P<gap>[ \t]+)(?P<body>[^\n]*)")
QUOTED_INCLUDE = re.compile(r'(?m)^[ \t]*#[ \t]*include[ \t]+"(?P<name>[^"]+)"')
CONVENTIONS = ("cdecl", "thiscall", "fastcall", "stdcall")
ABI_INFERENCE_SCHEMA = "openspore-abi-inference-"
RESOLVED_CONFLICT_STATES = {"resolved", "resolved_no_conflict", "agreed", "no_conflict", "closed"}
EVIDENCE_PACK_SCHEMA = "openspore-evidence-pack-1"
# The pack's own home for the machine-derived ABI envelope: the
# ``openspore-abi-inference-1`` record carrying ``parse``, ``dispatch``,
# ``receiver`` and the rest. It is where those sub-records live for a pack
# collected now -- the ``abi`` category holds the *persisted* projection beside it,
# byte for byte, and gains no machine record -- so it is read first and the
# ``abi`` value is the fallback for a pack collected before the category existed.
ABI_DERIVED_CATEGORY = "abi_derived"
# Where the pack a verdict was reached over came from. Reported verbatim, because
# reusing a pack and collecting a fresh one are not the same claim: the first is
# evidence that already existed and was verified, the second is a collection this
# process made and can be no better than what it can reach.
EVIDENCE_SOURCE_CALLER = "caller_supplied"
EVIDENCE_SOURCE_PERSISTED = "persisted_pack"
EVIDENCE_SOURCE_RECOLLECTED = "recollected_live_false"
# The pack came in with the call, so there is nothing on disk for the validator to
# verify and nothing is claimed: unchecked, never ``verified``.
EVIDENCE_INTEGRITY_UNCHECKED = "unchecked"
# Why the pack on disk was or was not used. Only ``verified`` puts a persisted
# pack's contents in front of a check; every other state falls through to the
# collection path and is reported rather than swallowed.
PERSISTED_VERIFIED = "verified"
PERSISTED_ABSENT = "absent"
PERSISTED_UNREADABLE = "unreadable"
PERSISTED_SCHEMA_MISMATCH = "schema_mismatch"
PERSISTED_TARGET_MISMATCH = "target_mismatch"
PERSISTED_DIGEST_MISMATCH = "digest_mismatch"
# The briefing the worker is handed, recorded rather than read. See ``validate``.
CONTEXT_SOURCE_CALLER = "caller_supplied"
CONTEXT_SOURCE_BUILT = "built_from_judged_pack"

# The two validation dimensions. A reconstruction is judged against the static
# binary; the original process is a separate axis that no static verdict may
# speak for. ``report["status"]`` remains an alias of the static verdict so every
# existing consumer keeps its current meaning.
STATIC_DIMENSION = "STATIC"
RUNTIME_DIMENSION = "RUNTIME"
RUNTIME_CATEGORY = "runtime"
COVERAGE_CHECK = "EVIDENCE COVERAGE"
# The checks that judge the reconstruction against evidence. ``NOT_AVAILABLE`` on
# one of these is an absence of evidence, never evidence of failure and never
# evidence of success either: it is neutral about the reconstruction and
# disqualifying for the aggregate, which a PASS may not be asserted over a
# dimension that was not adjudicated. See the ladder in ``validate``.
STATIC_CHECKS = ("ABI", "CALLS", "GLOBALS", "FIELDS/OFFSETS", "CONSTANTS",
                 "CONTROL FLOW", "VIRTUAL DISPATCH", "RETURN SEMANTICS")
# Edge types that prove a call really happened. Anything else in the xref export
# is a data reference and cannot adjudicate a call set.
CALL_REFERENCE_TYPES = ("direct-call", "thunk", "computed-call", "external")
# A worker names a callee by suffixing its VA onto the symbol. That convention is
# what makes a call set comparable against the machine at all. The code range is
# the .text span of the 3.1.0.22 image (measured from the xref export: every
# direct-call target lies in 0x00401010..0x011f95c0); it keeps data addresses that
# appear inside names -- ``g_unmodelled_015d115d`` -- out of the call set.
CALLEE_TOKEN = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*_([0-9a-fA-F]{8}))\b")
# The ``g_`` form of the same convention, and the only spelling a reconstruction
# uses to NAME a data-segment address. See ``_data_addresses``. The ``g_`` prefix
# is what keeps this from matching the ``helper_00abcde1`` callee names above, or
# any other identifier that happens to end in eight hex digits.
GLOBAL_NAME = re.compile(r"\bg_([0-9a-fA-F]{8})\b")
CODE_START = 0x00400000
CODE_END = 0x01300000
HEX_TOKEN = re.compile(r"0[xX][0-9a-fA-F]+")
BLOCK_COMMENT = re.compile(r"/\*.*?\*/", re.DOTALL)
LINE_COMMENT = re.compile(r"//[^\n]*")
# A physical field offset the reconstruction asserts. Whether a member access is
# a field or a method call is decided after the match, not by a lookahead: a
# lookahead lets the identifier backtrack (``query_00abcde1(`` matches as the
# field ``query_00abcde``), which reports every method call as an offset.
MEMBER_ACCESS = re.compile(r"(?:->|\.)(\s*)([A-Za-z_][A-Za-z0-9_]*)")
OFFSET_LITERAL = re.compile(r"(?:\+\s*(0[xX][0-9a-fA-F]+)|\[\s*(0[xX][0-9a-fA-F]+)\s*\])")
OFFSETOF = re.compile(r"\boffsetof\s*\(\s*([A-Za-z_][A-Za-z0-9_:<>]*)")
# A transfer to an immediate address. ``JMP`` is read as well as ``CALL`` because
# MSVC compiles a tail call as a jump to the callee, so a callee reachable only
# through a jump is a callee the xref export records. Reading only ``CALL`` made
# such a body look as if it made no call at all, and a reconstruction that named
# the tail callee was then refuted by evidence that had not been read.
DIRECT_TRANSFER = re.compile(r"^\s*(?:CALL|JMP)\s+(0[xX][0-9a-fA-F]+)\b", re.IGNORECASE)
JUMP_TRANSFER = re.compile(r"^\s*JMP\s+(0[xX][0-9a-fA-F]+)\b", re.IGNORECASE)
# The absolute operand of a conditional branch. The mnemonic is deliberately the
# same expression the branch count uses, so a branch that is counted is a branch
# whose target is looked for.
BRANCH_OPERAND = re.compile(r"^\s*(?:J(?!MP\b)[A-Z]{1,3}|LOOP\w*)\b\s+(0[xX][0-9a-fA-F]+)\b", re.IGNORECASE)
CONDITIONAL_BRANCH = re.compile(r"^\s*J(?!MP\b)[A-Z]{1,3}\b|^\s*LOOP\w*\b", re.IGNORECASE)
# An indirect transfer: a call or jump whose target is computed at run time.
# Two shapes, and the previous pattern had both of them wrong.
# * ``[A-Z]{2,3}`` cannot match ``dword``: Ghidra spells the memory operand
#   ``dword ptr [EAX*0x4 + 0x5dd840]`` and no other form of bracketed operand
#   appears in this binary, so the pattern matched a shape the listing never
#   emits and therefore matched nothing at all -- zero hits across all 172
#   listings.
# * The shape that actually matters on x86 is the *register* transfer. MSVC
#   compiles a virtual call to ``CALL EAX`` after loading the slot, and a
#   detector that only looked for brackets saw none of those 144 sites and
#   reported clearly dispatching bodies as bodies with no indirect call -- which
#   is what turned 0x00580cb0, with two register sites and a declared slot
#   boundary, into a FAIL stating that the body contained none.
# The register list is spelled out rather than matched as ``[A-Za-z]{1,4}`` so a
# Ghidra operand prefix (``near ptr``, ``short``) can never be read as a
# register, and so an immediate is never mistaken for one.
INDIRECT_REGISTERS = ("EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI")
INDIRECT_TRANSFER = re.compile(r"^\s*(?:CALL|JMP)\s+(?:\w+\s+PTR\s+)?(?:\w+:\s*)?\[", re.IGNORECASE)
INDIRECT_REGISTER_TRANSFER = re.compile(r"^\s*(?:CALL|JMP)\s+(?:%s)(?![\w])" % "|".join(INDIRECT_REGISTERS), re.IGNORECASE)
# A bracketed memory operand, and a hex literal inside one. The lookbehind skips
# a scale factor (``[EAX*0x4 + 0x5dd840]``: 0x4 is a multiplier, not a
# displacement) and the register name itself.
MEMORY_OPERAND = re.compile(r"\[([^\]]*)\]")
OPERAND_DISPLACEMENT = re.compile(r"(?<![\w.*])0[xX]([0-9a-fA-F]+)")
# The x86 instructions whose memory operand is implicit and so carries no bracket
# in the listing: the string operations and the port I/O pair. Ghidra brackets
# everything else -- ``INDIRECT_TRANSFER`` is built on that -- so these are the
# whole of the exception, and they are matched with their width suffix and their
# ``REP`` prefix optional because the listing spells both. ``MOVSD`` is in this
# set deliberately: spelled without brackets it is ambiguous between the SSE
# register move and the string move, and reading the register form as memory is
# the direction that cannot produce a false clearance.
IMPLICIT_MEMORY_MNEMONIC = re.compile(
    r"^\s*(?:REP|REPNE|REPNZ|REPE|REPZ|NO)?\s*"
    r"(?:MOVS[BWDQ]?|STOS[BWDQ]?|LODS[BWDQ]?|SCAS[BWDQ]?|CMPS[BWDQ]?|"
    r"INS[BWDQ]?|OUTS[BWDQ]?|IN|OUT)\b", re.IGNORECASE)
# A memory operand Ghidra spells as a *segment-absolute* address: a bracket whose
# entire content is an optional segment override, Ghidra's optional pointer-type
# decoration, and a numeric literal -- and nothing else. ``[0x0167ead8]``,
# ``ds:[0x0167ead8]`` and ``dword ptr [0x0167ead8]`` are all this one form.
#
# The anchoring is the whole contract. A register, an index, a scale factor, a
# symbol, or a placeholder all leave something in the operand that this pattern
# does not accept, so the operand is not classified as absolute and the caller
# falls back to the safe direction. That is deliberate: an operand this module
# cannot *prove* absolute must never be the basis of an absence.
ABSOLUTE_OPERAND = re.compile(
    r"^\s*(?:[A-Za-z]{2,8}\s*:\s*)?(?:\w+\s+ptr\s+)?"
    r"(?:0[xX][0-9a-fA-F]+|\d+)\s*$")
# A bare Ghidra placeholder, matched on the normalized form: ``fun`` followed by
# 8-hex runs and nothing else, so ``FUN_00bba790`` and a name that repeats the
# token match while a real name that merely begins with the same letters
# (``FunctionPool::Reset``) does not. This is the name a target carries when the
# SDK never named it, so it holds no descriptive words to narrow a span with --
# see ``_target_span`` for why the VA token alone is the binder there.
PLACEHOLDER_SYMBOL = re.compile(r"^fun(?:[0-9a-f]{8})+$")


def _index(root):
    from .evidence import _index as fresh_index
    return fresh_index(root)


def _record(index, va):
    records = index.get("records", {}) if isinstance(index, dict) else {}
    return records.get(va, {}) if isinstance(records, dict) else {}


def _source(root, record):
    """Resolve a worker source artifact, reporting which root was used.

    ``src/`` is canonical and always wins; ``reconstruction/staging/`` is
    unintegrated worker output and is only consulted when no canonical
    artifact exists. Any other directory is rejected.
    """
    source = record.get("source", {}) or {}
    candidates = []
    if source.get("file"):
        candidates.append(source["file"])
    candidates.extend(source.get("files", []) or [])
    base = Path(root).resolve()
    for prefix, role in SOURCE_ROLES:
        for value in candidates:
            value = str(value)
            if not value.startswith(prefix):
                continue
            path = base / value
            try:
                if not path.resolve().is_relative_to(base):
                    continue
            except OSError:
                continue
            if path.exists() and path.suffix in SOURCE_SUFFIXES:
                return {"path": path, "role": role}
    return None


def _read_source(path):
    if path is None:
        return ""
    try:
        return path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return ""


def _local_header_text(source_path, text):
    """Text of the headers ``source_path`` includes by quoted name.

    A package spells its calling-convention token once, as a macro, in the
    package's own header; the reconstructed body then names the macro. Reading
    only the body's file resolves no define, so ``_convention_defines`` sees
    nothing and the span reads as declaring no convention at all -- a fact the
    package states is lost, and the ABI check drops to WARN for a source that
    does declare one.

    Only quoted includes are followed, and only into the same directory: an
    angle-bracket include is a system header and a dotted or slashed name could
    name a file outside the package, so neither is read here.
    """
    if source_path is None:
        return ""
    directory = source_path.parent
    chunks = []
    for match in QUOTED_INCLUDE.finditer(text or ""):
        name = match.group("name")
        if not name or "/" in name or "\\" in name:
            continue
        chunk = _read_source(directory / name)
        if chunk:
            chunks.append(chunk)
    return "\n".join(chunks)


def _function_spans(text):
    spans = []
    for match in RETURN_DECL.finditer(text):
        start = match.start()
        brace = text.find("{", match.start(), match.end())
        if brace < 0:
            continue
        depth = 0
        end = brace
        for index in range(brace, len(text)):
            if text[index] == "{":
                depth += 1
            elif text[index] == "}":
                depth -= 1
                if depth == 0:
                    end = index + 1
                    break
        spans.append({"name": match.group("name"), "return_type": match.group("return"), "text": text[start:end]})
    return spans


def _normalized_name(value):
    return re.sub(r"[^a-z0-9]", "", str(value).casefold())


def _target_span(text, record):
    raw_names = []
    for key in ("name", "normalized_symbol"):
        value = record.get(key)
        if isinstance(value, str) and value:
            candidate = value.rsplit("::", 1)[-1]
            if candidate and candidate not in raw_names:
                raw_names.append(candidate)
    spans = [(span, _normalized_name(span["name"])) for span in _function_spans(text)]
    va_token = str(record.get("va", "")).replace("0x", "").casefold()
    for raw_name in raw_names:
        normalized = _normalized_name(raw_name)
        words = [word.casefold() for word in re.findall(r"[A-Z]?[a-z]+|[0-9]+", raw_name) if word]
        if va_token and PLACEHOLDER_SYMBOL.match(normalized):
            # The record names no function, only an address: every word of a
            # placeholder is the address, so the word-narrowed arm below would
            # have nothing to narrow with and its only word is the token itself.
            # The binding the worker briefing specifies -- "the reconstructed
            # symbol must embed the 8-hex target VA" -- is the whole contract
            # here, and requiring the literal ``fun`` in the span key as well
            # rejected the very symbols a worker is told to write, so a target
            # the SDK never named could never bind to any span and no check that
            # needs one could ever be adjudicated. Still a bind on the VA token
            # alone, and still ``candidates[0]`` on multiple matches below.
            # Definition over declaration needs no preference here:
            # ``_function_spans`` reports definitions only, because a prototype
            # ends in ``;`` and never reaches ``RETURN_DECL``'s required brace.
            candidates = [span for span, key in spans if va_token in key]
        elif va_token and words:
            # No length floor: a short last ``::`` component ("Write", "Release")
            # is a real name, and the VA token is what binds a span to a target.
            candidates = [span for span, key in spans if va_token in key and all(word in key for word in words)]
        else:
            candidates = []
        if candidates:
            return candidates[0]
    return None


def _convention_key(value):
    text = str(value or "").casefold()
    for key in ("fastcall", "thiscall", "stdcall", "cdecl"):
        if key in text:
            return key
    return None


def _convention_defines(text):
    """Map every ``#define`` name in ``text`` to the convention it resolves to.

    A package macro carries the calling-convention token exactly once, in its
    own definition; the entry declaration then only names the macro. Resolving
    the definition recovers a fact the file already states instead of treating
    the target as if it declared no convention.
    """
    result = {}
    for match in DEFINE.finditer(text or ""):
        key = _convention_key(match.group("body"))
        if key:
            result[match.group("name")] = key
    return result


def _source_conventions(scoped_text, defines):
    """Conventions the target span declares, literally or through a macro."""
    conventions = [key for key in CONVENTIONS if re.search(r"__%s\b" % key, scoped_text, re.IGNORECASE)]
    for name, key in (defines or {}).items():
        if key in conventions:
            continue
        if re.search(r"\b%s\b" % re.escape(name), scoped_text):
            conventions.append(key)
    return conventions


def _abi_category(categories):
    """Split the pack's ``abi`` category into (facts, inference record).

    The category holds either a copy of the persisted ABI or an
    ``openspore-abi-inference-1`` record wrapping a derived one; both shapes are
    accepted so the oracle widens without assuming the derived record exists.
    """
    category = categories.get("abi", {}) or {}
    value = category.get("value")
    if not isinstance(value, dict) or value.get("truncated") is True:
        return {}, None
    if str(value.get("schema", "")).startswith(ABI_INFERENCE_SCHEMA):
        derived = value.get("abi")
        return (derived if isinstance(derived, dict) else {}), value
    return value, None


def _abi_claim(sources, *keys):
    """First non-empty claim for ``keys`` across the ABI sources, in order."""
    for source in sources:
        if not isinstance(source, dict):
            continue
        for key in keys:
            value = source.get(key)
            if value not in (None, "", [], {}):
                return value
    return None


def _canonical_return_type(abi_sources):
    """The canonical C/C++ return-type claim across the ABI sources, or ``None``.

    ``return_type`` only, and deliberately not ``return_semantics``. That field
    is a *classification*, not a type: the derived ABI layer renders it in its
    own register-class vocabulary (``unclassified_in_EAX``,
    ``pointer_like_in_EAX``, ``integral_in_EAX``, ``float_or_x87_in_ST0``,
    ``aggregate_unknown_in_EAX``) and the persisted layer renders it as prose
    ("EAX receives the receiver verbatim; ..."). A measured survey of the
    committed packs found no ``return_semantics`` value that is a C or C++ type
    name at all.

    Admitting one of those as a return type is what made the string-agreement
    arm meaningless: it compared a register-class phrase against the source's
    declared C++ type, so the two could never agree, every such target was
    reported as "return type differs or is semantically renamed", and the
    machine-evidenced route in ``evidence_returns`` -- which compares WIDTHS and
    which fails a genuine void/value contradiction -- deferred as well, because
    it deferred on the same predicate. The WARN said nothing true about the
    reconstruction; it recorded a vocabulary mismatch as a defect in the source.

    Narrowing the claim here lets that stricter route run, and it cannot admit
    anything the old arm would not have:

    * a target whose claim is a real ``return_type`` keeps the string arm
      untouched, so every current PASS and WARN on those is unchanged;
    * a target whose claim was a ``return_semantics`` phrase could only have
      reached the old PASS by having a source type spelled identically to a
      register-class phrase, which no C++ declaration does, so the only
      reachable old outcome was that spurious WARN;
    * ``decide`` reaches PASS only from ``VOID_PROVEN`` or a machine-derived
      ``WIDTH_n_IN_R`` over a whole, non-degraded listing, FAILs a declared
      value where the machine proves void (and the mirror), and WARNs a width
      disagreement -- so a moved target is judged by a strictly stricter oracle
      than the string compare it replaces, and UNCLASSIFIED / SRET states stay
      NOT_AVAILABLE.
    """
    return _abi_claim(abi_sources, "return_type")


def _derived_field(inference, *keys):
    """Read a nested string field out of the derived ABI record, defensively."""
    value = inference if isinstance(inference, dict) else {}
    for key in keys:
        if not isinstance(value, dict):
            return ""
        value = value.get(key)
    return str(value) if isinstance(value, str) else ""


def _abi_conflicts(inference, pack):
    """Unresolved ABI-bearing conflicts from the derived record and the pack."""
    items = []
    for source in ((inference or {}).get("conflicts"), (pack or {}).get("conflicts")):
        if isinstance(source, list):
            items.extend(item for item in source if isinstance(item, dict))
    blocking = []
    for item in items:
        kind = str(item.get("kind", "")).casefold()
        field = str(item.get("field", "")).casefold()
        abi_bearing = kind == "live_vs_persisted" or any(token in field for token in ("abi", "signature", "convention"))
        if not abi_bearing:
            continue
        state = str(item.get("resolution_status") or item.get("status") or "").casefold()
        if item.get("resolved") is True or state.startswith("resolved") or state in RESOLVED_CONFLICT_STATES:
            continue
        blocking.append(item)
    return blocking


def _check(status, detail, coverage="partial", evidence=None):
    return {"status": status, "detail": detail, "coverage": coverage, "evidence": evidence or []}


def _dispatch_verdict(**kwargs):
    """The positively-corroborated VIRTUAL DISPATCH check, or ``None`` to defer.

    Imported lazily, and only for the arm that needs it: the module reads no state
    of its own, so there is nothing to gain by loading it for the 239 corpus
    targets whose listing is absent, and a caller that never reaches a body which
    dispatches never pays for it. A ``None`` means the module's evidence does not
    adjudicate this target, and the caller's own arms then stand unchanged.
    """
    from . import evidence_dispatch
    return evidence_dispatch.decide(**kwargs)


def _code(text):
    """``text`` with comments removed.

    Every token comparison below is a claim about what the reconstruction *does*,
    so it must be made about code only. Scanning comments produced a real false
    positive: a source whose sole ``for`` was the English word inside ``// ...``
    was read as branching where the machine body was straight-line.
    """
    return LINE_COMMENT.sub(" ", BLOCK_COMMENT.sub(" ", text or ""))


def _hex_tokens(text):
    """Hexadecimal literals in ``text``, compared by value.

    Only an explicitly written ``0x`` token counts. A pattern that also matches
    bare decimal runs would sweep in array sizes and line numbers, and a
    reconstruction would then be failed for disagreeing with a number that was
    never a constant.

    Each token comes back in one canonical spelling -- ``0x%x`` of its integer
    value -- because *width is not semantic*. Comparing the lowercased text
    instead made the reconstruction's ``0x0C`` and the listing's ``0xc`` two
    different constants, so a listing that plainly contains the constant
    refuted a source that plainly contains it, and the CONSTANTS arm failed a
    target on spelling alone (measured: 52 of the 78 corpus CONSTANTS failures
    were ``0x0c``-vs-``0xc`` pairs and nothing else). The rule the arm states is
    about a literal being *absent from the machine*; absence is a question about
    the value, so value is what is compared. Case is likewise not semantic and
    is normalised away by the same conversion.
    """
    found = set()
    for token in HEX_TOKEN.findall(_code(text)):
        try:
            found.add("%#x" % int(token, 16))
        except ValueError:
            continue
    return found


def _address(value):
    """Canonical ``0x%08x`` form, or ``None`` if ``value`` is not an address.

    The xref export reaches the index in both forms -- the TSV column is bare hex
    while the rebuilt projection prefixes it -- so both sides of every comparison
    are normalised before they are compared. Skipping this made a real address
    never match itself.
    """
    if not isinstance(value, str):
        return None
    text = value.strip().lower()
    if text.startswith("0x"):
        text = text[2:]
    if not text or len(text) > 8 or any(char not in "0123456789abcdef" for char in text):
        return None
    return "0x%08x" % int(text, 16)


def _callee_addresses(text, record):
    """Addresses the source names as callees, via the ``symbol_<va>`` convention.

    The target's own address is excluded: its declaration sits inside the span
    under test, so without this every reconstruction would appear to call itself.
    Addresses outside the code range are excluded because names also carry data
    addresses.
    """
    own = str(record.get("va", "")).replace("0x", "").casefold()
    found = set()
    for name, token in CALLEE_TOKEN.findall(_code(text)):
        if token.casefold() == own:
            continue
        value = int(token, 16)
        if CODE_START <= value < CODE_END:
            found.add("0x%08x" % value)
    return found


def _machine_callees(dependencies):
    """Addresses the xref export records this function calling.

    Independent of the reconstruction: the export is produced by Ghidra from the
    binary, not by the worker that wrote the source.
    """
    edges = dependencies.get("edges") or []
    found = set()
    for edge in edges:
        if not isinstance(edge, dict):
            continue
        if edge.get("direction") != "out":
            continue
        if edge.get("reference_type") not in CALL_REFERENCE_TYPES:
            continue
        address = _address(edge.get("other"))
        if address:
            found.add(address)
    return found


def _listing(categories):
    """The machine listing as ``(addresses, texts)``, or ``None``.

    ``None`` means "no independent listing exists", which is not the same claim as
    "the listing is empty" and is never a licence to pass a check. Three cases
    collapse into it, all of them absences of evidence:

    * no ``disassembly`` category, or a value that is not an object;
    * a ``{"truncated": true, "preview": ...}`` envelope. The preview is a
      *fragment* of the body. Reading it as a listing lets a partial oracle refute
      a constant the full body does contain, so a truncated pack stays
      ``NOT_AVAILABLE`` and says so;
    * an empty instruction list. A recovered function always ends in a return, so
      *an empty body is not evidence about a body -- it is the absence of one.
    """
    category = (categories.get("disassembly") or {}).get("value")
    if not isinstance(category, dict) or category.get("truncated") is True:
        return None
    items = category.get("instructions")
    if not isinstance(items, list) or not items:
        return None
    addresses, texts = [], []
    for item in items:
        if not isinstance(item, dict):
            return None
        addresses.append(_address(item.get("address")))
        texts.append(str(item.get("instruction", "")))
    return addresses, texts


def _instructions(categories):
    """Machine instruction text for this target, or ``None``."""
    listing = _listing(categories)
    return listing[1] if listing is not None else None


def _direct_transfer_targets(texts):
    """Addresses the body transfers control to directly (``CALL`` or ``JMP``)."""
    found = set()
    for text in texts or ():
        match = DIRECT_TRANSFER.match(str(text or ""))
        if not match:
            continue
        address = _address(match.group(1))
        if address:
            found.add(address)
    return found


def _jump_transfer_targets(texts):
    """Addresses the body reaches by a tail-call jump rather than a call."""
    found = set()
    for text in texts or ():
        match = JUMP_TRANSFER.match(str(text or ""))
        if not match:
            continue
        address = _address(match.group(1))
        if address:
            found.add(address)
    return found


def _intra_procedural_jump_targets(addresses, texts):
    """``JMP`` immediates that land back inside the listing's own span, or ``None``.

    ``None`` means the span cannot be bounded -- an empty listing, or one whose
    instruction addresses do not all parse -- and then no filtering is invented:
    the same ``[lo, hi]`` notion CONTROL FLOW tests its branch graph against is
    the only body boundary this check is entitled to assert, and an unbounded one
    excludes nothing.

    A jump whose target lies *inside* the body transfers control within the
    function -- a preheader edge into a block, or a loop back edge -- and so
    reaches no callee: the callee set is by definition made of addresses the body
    transfers control *to*, and a target the body already contains is not one.
    Counting it as a direct transfer made the listing's transfer set disagree
    with the xref export for every body containing a loop, so a correct
    reconstruction was failed on a target the machine itself shows to be its own
    code. The converse is deliberately not filtered: a ``JMP`` outside the span
    *is* a tail call, the export records those, and dropping it would reintroduce
    the miss this pair of detectors already had once.

    ``CALL`` is untouched by design. A call immediate inside the span is a real
    transfer whose target happens to share the span, and the export is the oracle
    that says whether it is there; dropping it on geometry alone would silence a
    disagreement rather than resolve one.
    """
    bounds = _span_bounds(addresses)
    if bounds is None:
        return None
    low, high = bounds
    return {target for target in _jump_transfer_targets(texts) if low <= int(target, 16) <= high}


def _indirect_sites(texts):
    """Indirect dispatch sites: a transfer through a register or a memory operand."""
    found = []
    for text in texts or ():
        text = str(text or "")
        if INDIRECT_TRANSFER.match(text) or INDIRECT_REGISTER_TRANSFER.match(text):
            found.append(text)
    return found


def _span_bounds(addresses):
    """``(low, high)`` instruction addresses of a listing, or ``None``.

    ``None`` means the span cannot be bounded, which is not the same claim as a
    body that happens to be narrow: an address that does not parse leaves the
    body unbounded, and an unbounded body cannot be shown to contain its own
    branch targets.
    """
    if not addresses or any(value is None for value in addresses):
        return None
    numbers = [int(value, 16) for value in addresses]
    return min(numbers), max(numbers)


def _branch_closure(addresses, texts):
    """Conditional branches that do not close inside the recovered body.

    Returns ``(escaping, unbounded)``. ``escaping`` holds the absolute targets
    outside ``[min(addresses), max(addresses)]`` -- flow that continues past the
    listing, so the listing is a slice rather than a body. ``unbounded`` counts
    branches that are not escaped so much as unread: an operand that is not an
    absolute address, or a listing whose own instruction addresses do not all
    parse, leaves no span to test against. A graph that cannot be *shown* to
    close is not a graph that closes, and must not be reported as one.
    """
    branches = [str(text or "") for text in texts if CONDITIONAL_BRANCH.match(str(text or ""))]
    bounds = _span_bounds(addresses)
    if not branches:
        return [], 0
    if bounds is None:
        return [], len(branches)
    low, high = bounds
    escaping, unbounded = [], 0
    for text in branches:
        match = BRANCH_OPERAND.search(text)
        target = _address(match.group(1)) if match else None
        if target is None:
            unbounded += 1
        elif not low <= int(target, 16) <= high:
            escaping.append(target)
    return escaping, unbounded


def _receiver_displacements(texts, register):
    """Non-zero displacements of memory operands naming ``register``.

    Only the base register's own displacements count. A displacement under a
    different base says something about a different object, and reading it as a
    receiver field would invent a claim the body never makes.
    """
    token = re.compile(r"(?<![\w.])%s(?![\w])" % re.escape(str(register)))
    found = set()
    for text in texts or ():
        for match in MEMORY_OPERAND.finditer(str(text or "")):
            operand = match.group(1)
            if not token.search(operand):
                continue
            for literal in OPERAND_DISPLACEMENT.findall(operand):
                number = int(literal, 16)
                if number:
                    found.add(number)
    return found


def _any_field_access(texts):
    """Whether *any* instruction in ``texts`` addresses memory at all.

    The register-agnostic sibling of ``_receiver_displacements``, and it exists
    because of the case that helper cannot serve: when the machine-derived record
    names no receiver register, filtering the listing on a base register would be
    filtering on the very thing that is unknown. So the question here is the widest
    possible one, and the answer the caller is allowed to act on is only the widest
    no -- a body that reaches no memory operand of any kind addresses no object, and
    so no receiver field.

    A hit is a bracketed operand of *any* kind (Ghidra brackets every memory
    operand, so the bracket is the marker: a load, a store, an address-taken
    ``LEA``, a frame slot, a displacement under any register) or one of the few
    instructions whose operand is implicit and therefore unbracketed
    (``IMPLICIT_MEMORY_MNEMONIC``). A bare ``[ECX]`` is the same field claim as
    ``[ECX + 0x80]`` -- the word at offset zero -- so a displacement test alone
    would clear a body that reads its receiver.

    Over-reporting is the safe direction, and deliberately so: a false hit costs
    the caller its pass and leaves it the arm it already had, while a false miss
    would clear a body that does address a field.
    """
    for text in texts or ():
        line = str(text or "")
        if MEMORY_OPERAND.search(line) or IMPLICIT_MEMORY_MNEMONIC.match(line):
            return True
    return False


def _all_operands_absolute(texts):
    """Whether every memory operand in ``texts`` is a segment-absolute address.

    The narrower sibling of :func:`_any_field_access`, and the question the
    third FIELDS/OFFSETS absence arm asks. ``_any_field_access`` is the widest
    question there is -- a hit is *any* bracket -- because over-reporting costs a
    pass and under-reporting would clear a body that does address a field. That
    conservatism is right for a register-relative operand and wrong for an
    absolute one: Ghidra spells a fixed-address read ``MOV EAX,[0x0167ead8]``,
    which is bracketed, so ``_any_field_access`` reports a field access, but it
    names no register and addresses no object. A receiver is reachable only
    through a register, so an absolute operand cannot be a receiver field access.

    Deliberately fail-closed, and in the same direction as its sibling:

    * An operand that is not provably absolute -- a register, a scaled index, a
      symbol, a bare ``[...]`` placeholder -- is treated as register-relative.
      Manufacturing a clearance from a form this cannot read would be the one
      error the whole family of arms is built to avoid.
    * An empty or absent listing is **False**, not vacuously True. ``all()`` over
      nothing is True, and that is precisely the wrong answer here: the
      second arm already owns a body with no operand at all, and reporting True
      would let this arm describe an absolute read that does not exist.
    * An implicit-memory instruction (``REP MOVSD`` and its family) carries no
      bracket to classify, so a body containing one is doing memory traffic whose
      target was never seen. False.

    What a True answer licenses is narrow and is stated by the caller, not here:
    the body performs no *register-relative* access, and so performs no
    receiver-relative one. Whether the absolute address is a global is
    GLOBALS' dimension and this predicate says nothing about it.
    """
    if not texts:
        return False
    saw_operand = False
    for text in texts:
        line = str(text or "")
        if IMPLICIT_MEMORY_MNEMONIC.match(line):
            return False
        for match in MEMORY_OPERAND.finditer(line):
            saw_operand = True
            if not ABSOLUTE_OPERAND.match(match.group(1)):
                return False
    # No operand anywhere is the second arm's case, not this one's.
    return saw_operand


def _declared_displacements(declarations):
    """The numeric displacements among ``_field_declarations`` results."""
    found = set()
    for entry in declarations or ():
        match = re.search(r"0[xX]([0-9a-fA-F]+)$", str(entry))
        if match:
            found.add(int(match.group(1), 16))
    return found


def _abi_envelope(categories):
    """The pack's raw ``abi`` value, outer layer included, and the derived ABI.

    ``_abi_category`` unwraps the inference envelope and hands back the derived
    ABI. The machine-derived facts the per-dimension checks need -- the receiver
    register and its displacement bounds, the parse record, the dispatch count --
    are recorded on the *envelope* rather than inside the derived ABI (measured:
    190 of 200 packs carry them only on the envelope), so they are read from both
    layers and the outer one wins.
    """
    value = (categories.get("abi") or {}).get("value")
    outer = value if isinstance(value, dict) else {}
    derived, _ = _abi_category(categories)
    return outer, derived


def _abi_envelope_field(outer, derived, key):
    """A machine-derived sub-record of the ABI envelope, outer layer first."""
    for source in (outer, derived):
        value = source.get(key) if isinstance(source, dict) else None
        if isinstance(value, dict) and value:
            return value
    return {}


def _machine_record(categories, abi_outer, abi_inner, key):
    """The machine-derived sub-record ``key``: ``abi_derived`` first, then ``abi``.

    One place, so the three checks that read a machine record (CONSTANTS reads
    ``parse``, VIRTUAL DISPATCH reads ``dispatch``, FIELDS/OFFSETS reads
    ``receiver``) and the ABI check's own convention confidence all resolve it
    identically. ``abi_derived`` wins because it is the pack's declared home for
    the derivation; the ``abi`` value is kept as the fallback so a pack collected
    before that category existed, or one whose ``abi`` value *is* the derived
    envelope, reads exactly as it did before.

    A ``{"truncated": true}`` envelope is refused on either layer, the way
    ``_abi_category`` refuses one: its preview is a fragment, and a fragment is
    never a record -- least of all a count of zero, which is how an absence of
    evidence becomes a clearance. ``{}`` is returned for a key no source carries,
    so every caller still has to decide what a missing record means.
    """
    value = (categories.get(ABI_DERIVED_CATEGORY) or {}).get("value")
    if isinstance(value, dict) and value.get("truncated") is not True:
        record = value.get(key)
        if isinstance(record, dict) and record:
            return record
    if isinstance(abi_outer, dict) and abi_outer.get("truncated") is True:
        abi_outer = {}
    return _abi_envelope_field(abi_outer, abi_inner, key)


def _hex_values(values):
    """``values`` as one readable ``0x..`` list, ordered numerically."""
    return ", ".join("0x%x" % value for value in sorted(set(values))) or "none"


def _field_declarations(text):
    """Physical field offsets the source span asserts.

    This is the difference between *naming* a type and *declaring* an offset
    inside it. Naming a type is not a claim about memory layout, so it must not
    be reported as an unverified one. Over-reporting is the safe direction here:
    a method call that slips through costs a warning, never a false clearance.
    """
    code = _code(text)
    found = set()
    for match in MEMBER_ACCESS.finditer(code):
        if code[match.end():].lstrip().startswith("("):
            continue  # a method call through a pointer asserts no offset
        found.add("field %s" % match.group(2))
    for base, indexed in OFFSET_LITERAL.findall(code):
        found.add("displacement %s" % (base or indexed))
    found.update("offsetof %s" % name for name in OFFSETOF.findall(code))
    return found


def _data_addresses(texts):
    """Absolute addresses in the data segment, from instruction text or source.

    Two spellings are recognised, and both are needed because the two inputs are
    written in different conventions:

    * a ``0x``-prefixed literal, which is how the machine listing renders an
      address;
    * the repository's own ``g_<va8>`` global-name convention, which is how a
      reconstruction *names* the address it touches. This is the same convention
      ``CALLEE_TOKEN`` already reads on the call side -- a worker suffixes the VA
      onto the symbol -- and the codebase documents it by example in its own
      comment on ``g_unmodelled_015d115d``. Reading only ``0x`` literals meant a
      reconstruction that declared its global correctly was invisible to the
      check, so its claims could never be corroborated and the second machine
      side went unused. Measured over ``reconstruction/staging``: 11 distinct
      data-range addresses are named this way, which is sparse enough that the
      convention is a real choice rather than an accident of density.

    Emitted in ``normalize_va``'s zero-padded ``0x%08x`` form, which is the
    spelling every other address identity test in this module uses --
    ``_address``, ``_machine_callees``, and the data-reference reader. It used to
    inherit ``_hex_tokens``' unpadded ``0x%x`` spelling, which is fine inside a
    set comparison and wrong the moment a set leaves this function: a listing's
    ``0x15fd918`` and the artifact's ``0x015fd918`` are one address, and
    comparing them as strings made every intersection silently empty. That is
    the exact failure mode ``_hex_tokens`` documents for CONSTANTS (52 of 78
    corpus failures were ``0x0c``-vs-``0xc``), and width is not semantic here
    either, so the canonical form is applied at the boundary.

    The ``g_`` prefix is required, so ``helper_00abcde1``-style callee names and
    any other 8-hex-digit identifier cannot be read as a global: only the prefix
    that this repository uses for globals qualifies.
    """
    joined = " ".join(texts) if isinstance(texts, (list, tuple)) else texts
    found = set()
    for token in _hex_tokens(joined):
        if CODE_END <= int(token, 16) < 0x02000000:
            found.add("0x%08x" % int(token, 16))
    for match in GLOBAL_NAME.finditer(joined or ""):
        value = int(match.group(1), 16)
        if CODE_END <= value < 0x02000000:
            found.add("0x%08x" % value)
    return found


def _globals_verdict(*, listing_texts, scoped_text, oracle, recorded, data_note,
                     global_evidence):
    """The GLOBALS check, as a function of its two machine sides and the source.

    Extracted from ``validate`` so the falsifier battery can drive the real arms
    over a synthetic target instead of a stand-in that could drift from them. The
    ordering below is the whole safety argument and is preserved exactly:

    1. No listing at all -- there is no first machine side, so there is nothing to
       corroborate against. ``NOT_AVAILABLE`` unless the reconstruction at least
       declares globals, in which case it is a warning about an unbacked claim.
    2. Neither side names a data-segment address -- a ``PASS``, on the listing's
       own evidence, which needs no second source. If the artifact does record
       references here the disagreement is stated rather than hidden.
    3. Every source-named address is recorded by the artifact AND the listing
       corroborates at least one -- the only arm that turns a warning into a pass.
    4. Everything else is a warning, with the artifact's own reading attached.

    Arm 3 is the strengthening. It is deliberately narrow in two ways: it needs
    *all* the source's addresses recorded rather than some, so a reconstruction
    cannot pass by getting one address right and others wrong; and it needs the
    listing too, so one machine source is never on its own enough.
    """
    data = oracle
    data_evidence = [DATAREF_REL] if data["state"] == "complete" else []
    if listing_texts is None:
        if global_evidence:
            return _check("WARN", "global references are recorded but they are reconstruction-authored; %sno complete listing is available for a second machine side" % data_note, "partial", [INDEX_REL] + data_evidence)
        return _check("NOT_AVAILABLE", "no independent data-reference evidence establishes a global for this target and no complete listing is available%s" % data_note, "none", [INDEX_REL] + data_evidence)
    source_data = _data_addresses(scoped_text)
    machine_data = _data_addresses(listing_texts)
    corroborated = source_data & set(recorded)
    if not machine_data and not source_data:
        extra = ""
        if data["state"] == "complete" and recorded:
            extra = ("; the data-reference artifact does record %d reference(s) out of this "
                     "body to %s, which this arm's listing scan does not show, so the two "
                     "machine sources disagree and the evidence needs review"
                     % (len(data["rows"]), ", ".join(sorted(recorded))))
        return _check("PASS", "the complete %d-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global%s%s" % (len(listing_texts), extra, data_note), "complete", [INDEX_REL, EVIDENCE_REL] + data_evidence)
    if corroborated and (source_data & machine_data):
        modes = []
        for label, count in (("read", data["read"]), ("write", data["write"]),
                             ("read-write", data["readwrite"]),
                             ("address-taken", data["other"])):
            if count:
                modes.append("%d %s" % (count, label))
        return _check("PASS", "the machine-vs-machine rule: all %d data address(es) the source span names are recorded as Ghidra data references out of this body, and the complete %d-instruction listing corroborates %d of them; the artifact records %s across %d reference row(s)%s"
                      % (len(corroborated), len(listing_texts),
                         len(source_data & machine_data),
                         ", ".join(modes) or "no access mode", len(data["rows"]),
                         data_note),
                      "complete", [INDEX_REL, EVIDENCE_REL, DATAREF_REL])
    if source_data & machine_data:
        return _check("WARN", "%d source data address(es) appear in the machine listing; %s" % (len(source_data & machine_data), _globals_data_gap(data, source_data, recorded)), "partial", [INDEX_REL, EVIDENCE_REL] + data_evidence)
    if source_data:
        return _check("WARN", "the source span names %d data address(es) the complete %d-instruction listing does not corroborate: %s; %s" % (len(source_data), len(listing_texts), ", ".join(sorted(source_data)), _globals_data_gap(data, source_data, recorded)), "partial", [INDEX_REL, EVIDENCE_REL] + data_evidence)
    return _check("WARN", "the complete %d-instruction listing names %d data address(es) (%s); %s" % (len(listing_texts), len(machine_data), ", ".join(sorted(machine_data)), _globals_data_gap(data, machine_data, recorded)), "partial", [INDEX_REL, EVIDENCE_REL] + data_evidence)


def _globals_data_gap(data, named, recorded):
    """Why the data-reference artifact does not close the GLOBALS gap, in words.

    Three cases, and they are genuinely different facts so they are worded
    differently rather than collapsed into one message:

    * The artifact was not read whole. Nothing is claimed about the named
      addresses, and the artifact's own note (which says why) is carried instead.
    * The artifact was read whole and records some of them. The named addresses
      it does not record are named, and the ones it does are reported with their
      access mode -- so a reader can see which claim is unbacked without having to
      open the artifact.
    * The artifact was read whole and records none of them. This is the shape a
      refutation would have, and it is deliberately reported as an absence rather
      than acted on: the artifact indexes the *pinned caller universe* at one
      moment, and a body whose references were read at another would produce
      exactly this. So it says the claim is unbacked and stops there.

    ``recorded`` is the artifact's address set in the validator's own ``0x..``
    form, so the comparison is against the same spelling ``_data_addresses``
    produces and a disagreement cannot be a formatting artefact.
    """
    if data["state"] != "complete":
        return ("no independent data-reference evidence is available for this target (%s), so "
                "the addresses it names have no second machine side to be checked against"
                % data["note"])
    missing = sorted(set(named) - set(recorded))
    if missing:
        return ("the data-reference artifact is read whole and records %d reference row(s) out of "
                "this body, none of which is %d of the address(es) under review (%s), so those "
                "claims are unbacked by Ghidra's reference database rather than refuted by it"
                % (len(data["rows"]), len(missing), ", ".join(missing)))
    return ("the data-reference artifact is read whole and records %d reference row(s) out of this "
            "body covering every address under review, with access mode(s) %s"
            % (len(data["rows"]),
               ", ".join("%s=%d" % (mode, count) for mode, count in
                         (("read", data["read"]), ("write", data["write"]),
                          ("readwrite", data["readwrite"]), ("other", data["other"]))
                         if count) or "none"))


def _runtime_dimension(record, categories):
    """The runtime axis, derived from the record -- never asserted.

    Runtime is a capability gate on the original process. Nothing in this
    repository has run it, so the honest resting state is "a gate is open",
    which is an absence of evidence. It is deliberately not spelled
    ``NOT_AVAILABLE``: that token means "a verdict could not be reached" and is
    indistinguishable from a category that was searched and came up empty, which
    would misreport a permanent capability gap as a per-target finding.
    """
    block = record.get("runtime", {}) or {}
    gates = [str(value) for value in (block.get("gates") or []) if isinstance(value, str)]
    validated = block.get("validated")
    validated = validated if isinstance(validated, int) and validated > 0 else 0
    declared = (categories.get("runtime_metadata") or {}).get("value")
    if not isinstance(declared, dict):
        declared = {}
    if not gates:
        gates = [str(value) for value in (declared.get("gates") or []) if isinstance(value, str)]
    if validated:
        return {"dimension": RUNTIME_DIMENSION, "status": "PASS",
                "validated": validated, "gated": False, "gates": sorted(set(gates)),
                "reason": "the canonical record reports original-process validation"}
    return {"dimension": RUNTIME_DIMENSION, "status": "GATED",
            "validated": 0, "gated": True, "gates": sorted(set(gates)),
            "reason": "no original-process trace exists in this repository; the "
                      "gate is open, nothing was attempted, and nothing failed"}


def _return_type(span):
    return span.get("return_type") if span else None


def _evidence_destination(root, va, out_dir=None):
    """Where this target's evidence pack lives and where validation is written."""
    return Path(out_dir) if out_dir else Path(root) / EVIDENCE_REL / va[2:]


def _pack_digest(pack):
    """Recompute a pack's content hash exactly the way ``collect`` computes it.

    ``evidence.collect`` hashes the pack with ``content_sha256`` set to ``None``
    and before ``paths`` is attached (evidence.py:969, then 974), so the digest
    covers the pack minus those two things. Re-hashing the loaded dict as it sits
    on disk can never match -- ``content_sha256`` holds the very value being
    verified, and ``paths`` was never part of the hashed document -- so a check
    written that way would reject every intact pack and, having done so, be
    worthless.
    """
    probe = dict(pack)
    probe.pop("paths", None)
    probe["content_sha256"] = None
    return sha256_json(probe)


def _persisted_pack(destination, va):
    """The evidence pack already on disk for ``va``, if it may be trusted.

    Returns ``(pack, state, note)``. ``pack`` is ``None`` for every state other
    than ``verified`` -- absent, unreadable, wrong schema, wrong target, or a
    digest that does not reproduce -- and ``note`` says which in words, because a
    pack that failed verification must not vanish silently into a weaker
    collection. Nothing here raises: an absent pack is the ordinary case and has
    to reach the collection path exactly as it did before.
    """
    path = destination / "evidence.json"
    if not path.is_file():
        return None, PERSISTED_ABSENT, "no persisted evidence pack at %s" % path
    try:
        pack = load_json(path)
    except (OSError, ValueError) as exc:
        return None, PERSISTED_UNREADABLE, "the persisted evidence pack at %s is unreadable: %s" % (path, exc)
    if not isinstance(pack, dict):
        return None, PERSISTED_UNREADABLE, "the persisted evidence pack at %s is not a JSON object" % path
    if pack.get("schema") != EVIDENCE_PACK_SCHEMA:
        return None, PERSISTED_SCHEMA_MISMATCH, ("the persisted pack at %s declares schema %r, not %r"
                                                  % (path, pack.get("schema"), EVIDENCE_PACK_SCHEMA))
    target = pack.get("target") if isinstance(pack.get("target"), dict) else {}
    # Both sides go through ``_address``: the pack spells a target as
    # ``0x00409c00`` and a caller may spell the same address without the prefix
    # or padding, and that is agreement, not a mismatch.
    if _address(target.get("va")) != _address(va):
        return None, PERSISTED_TARGET_MISMATCH, ("the persisted pack at %s records target %r, not the requested %s"
                                                 % (path, target.get("va"), va))
    if not isinstance(pack.get("categories"), dict):
        return None, PERSISTED_SCHEMA_MISMATCH, "the persisted pack at %s carries no categories object" % path
    stored = pack.get("content_sha256")
    recomputed = _pack_digest(pack)
    if stored != recomputed:
        return None, PERSISTED_DIGEST_MISMATCH, ("the persisted pack at %s does not reproduce its own content_sha256: "
                                                 "stored %s, recomputed %s" % (path, stored, recomputed))
    return pack, PERSISTED_VERIFIED, None


def _context_pack_digest(context):
    """The pack digest the briefing quotes, read defensively.

    A value that disagrees with ``report["binary_evidence"]["content_sha256"]``
    is the signal that a worker was briefed from different evidence than the one
    its candidate is judged against -- the divergence the shared pack removes.
    """
    sections = context.get("sections") if isinstance(context, dict) else None
    data = ((sections or {}).get("04_evidence_state") or {}).get("data")
    if not isinstance(data, dict):
        return None
    return data.get("content_sha256")


def validate(root=ROOT, va=None, evidence=None, context=None, write=True, out_dir=None):
    root = Path(root)
    if va is None:
        raise ToolError("missing_va", "a target VA is required", 2)
    try:
        va = normalize_va(va)
    except (TypeError, ValueError) as exc:
        raise ToolError("invalid_va", str(exc), 2)
    # -- evidence ----------------------------------------------------------
    # The pack a verdict is reached over has to be the pack that exists. 195 of
    # the 200 committed packs carry a disassembly listing, and
    # ``collect(live=False)`` cannot produce one: it never calls
    # ``_live_disassembly``, so it stored ``disassembly = unavailable`` and
    # ``_instructions`` returned ``None`` for every single target. Five checks
    # were then structurally incapable of PASS and the resulting capability gap
    # was reported as a per-target ``NOT_AVAILABLE`` -- the machine evidence was
    # on disk, hash-anchored, and thrown away. So a pack that verifies is loaded
    # and used; anything that fails verification falls through to the collection
    # path unchanged and says which failure it was.
    destination = _evidence_destination(root, va, out_dir)
    if evidence is None:
        evidence, persisted_state, persisted_note = _persisted_pack(destination, va)
        if evidence is None:
            from .evidence import collect
            # ``write`` is withheld whenever a pack file exists but did not
            # verify. A collection made on this path is strictly weaker than what
            # that file may hold -- it can produce no listing at all -- so
            # overwriting would destroy the only copy of evidence this path
            # cannot re-derive. A verified pack is never rewritten either: it is
            # already the better pack, and a "is the new one at least as good"
            # comparison would be a heuristic where refusing to write is exact.
            evidence = collect(root=root, va=va, live=False,
                               write=bool(write) and persisted_state == PERSISTED_ABSENT,
                               out_dir=out_dir)
            evidence_source = EVIDENCE_SOURCE_RECOLLECTED
        else:
            evidence_source = EVIDENCE_SOURCE_PERSISTED
        evidence_integrity = persisted_state
    else:
        evidence_source = EVIDENCE_SOURCE_CALLER
        evidence_integrity = EVIDENCE_INTEGRITY_UNCHECKED
        persisted_note = None
    # The briefing is built from the same object the checks below judge, so what
    # the worker was told and what the candidate is graded against cannot drift
    # apart. ``live`` is not passed because ``evidence`` is never ``None`` here:
    # the flag could only ever be ignored, and passing it invites a reader to
    # believe the briefing came from a different collection than the verdict.
    context_supplied = context is not None
    if context is None:
        from .context import build
        context = build(root=root, va=va, evidence=evidence, write=write, out_dir=out_dir)
    index = _index(root)
    record = _record(index, va)
    resolved = _source(root, record)
    source_path = resolved["path"] if resolved else None
    source_role = resolved["role"] if resolved else "missing"
    source_text = _read_source(source_path)
    header_text = _local_header_text(source_path, source_text)
    target_span = _target_span(source_text, record)
    scoped_text = target_span.get("text", "") if target_span else ""
    categories = evidence.get("categories", {})
    persisted_abi = record.get("abi", {}) or {}
    derived_abi, abi_inference = _abi_category(categories)
    abi_sources = [persisted_abi, derived_abi]
    dependencies = record.get("dependencies", {}) or {}
    # The machine listing and the machine-derived sub-records of the ABI envelope
    # are read once, here, because five of the checks below judge against them and
    # each of them needs the same question answered first: is this evidence
    # complete and bounded, or is it missing? ``None`` is the answer for the
    # second, and a check that has it may not pass.
    listing = _listing(categories)
    listing_addresses, listing_texts = listing if listing is not None else (None, None)
    abi_outer, abi_inner = _abi_envelope(categories)
    checks = {}
    convention = _convention_key(_abi_claim(abi_sources, "calling_convention", "convention"))
    persisted_claim = _convention_key(persisted_abi.get("calling_convention") or persisted_abi.get("convention"))
    derived_claim = _convention_key(derived_abi.get("calling_convention") or derived_abi.get("convention"))
    convention_claims = [claim for claim in (persisted_claim, derived_claim) if claim]
    source_conventions = _source_conventions(scoped_text, _convention_defines(source_text + "\n" + header_text))
    mismatched = [claim for claim in convention_claims if not any(claim == key for key in source_conventions)]
    blocking_conflicts = _abi_conflicts(abi_inference, evidence)
    # A convention record like the other three, so it is resolved the same way.
    # Reading the old location only would make the arm that warns about an unproven
    # oracle unreachable on every pack whose derivation is published in
    # ``abi_derived`` -- a missing record must not read as a proven one.
    conventions = _machine_record(categories, abi_outer, abi_inner, "conventions")
    confidence = str(conventions.get("confidence") or "").casefold()
    if not source_path or not target_span:
        checks["ABI"] = _check("NOT_AVAILABLE", "target source span is not deterministically available", "none")
    elif blocking_conflicts:
        first = blocking_conflicts[0]
        checks["ABI"] = _check("FAIL", "unresolved ABI conflict %s; the validator will not pick a winner" % (first.get("conflict_id") or first.get("kind") or "unlabelled"), "partial", [INDEX_REL, EVIDENCE_REL])
    elif source_conventions and mismatched:
        # Every oracle the source contradicts is a failure on its own terms; a
        # second, weaker oracle never rescues a contradiction against the first.
        label = "persisted" if mismatched[0] == persisted_claim else "derived"
        checks["ABI"] = _check("FAIL", "source convention %s conflicts with %s %s" % (source_conventions, label, mismatched[0]), "partial", [INDEX_REL])
    elif str(_derived_field(abi_inference, "verdict")) == "ABI_UNKNOWN":
        abstained = (abi_inference or {}).get("abstained_because")
        entries = [item for item in abstained if isinstance(item, str)] if isinstance(abstained, list) else []
        reason = entries[0] if entries else "no reason recorded"
        checks["ABI"] = _check("WARN", "the derived ABI record abstained (ABI_UNKNOWN): %s" % reason, "partial", [INDEX_REL, EVIDENCE_REL])
    elif confidence in {"unknown", "approximation"}:
        checks["ABI"] = _check("WARN", "derived calling-convention confidence is %s; the oracle is not proven" % confidence.upper(), "partial", [INDEX_REL, EVIDENCE_REL])
    elif convention and source_conventions:
        checks["ABI"] = _check("PASS", "calling convention is present in the target source span and canonical metadata", "partial", [INDEX_REL])
    else:
        checks["ABI"] = _check("WARN", "target ABI is not deterministically extractable from the available source", "partial", [INDEX_REL])
    # -- CALLS -------------------------------------------------------------
    # Two machine sources, independent of the reconstruction: the xref export
    # (``dependencies.edges``) and the disassembly listing. Each is read on its
    # own terms and the two are then compared, which is the only shape in which a
    # call set can be adjudicated rather than described. The export is *present*
    # only when it projected an edge list for this record at all: a record with no
    # ``edges`` key was never searched, and reading its empty result as "this
    # function calls nothing" is exactly how an absence of evidence becomes a
    # clearance. A source claim the export does not record is a refutation and
    # still holds; a truncated export explains any such absence, so truncation is
    # read first.
    source_calls = _callee_addresses(scoped_text, record)
    machine_calls = _machine_callees(dependencies)
    listing_transfers = _direct_transfer_targets(listing_texts)
    # A jump back into the listing's own span is intra-procedural control flow, not
    # a transfer out of the body, so it is excluded from the set the export is
    # compared against -- and it is reported wherever the set is reported, so a
    # reader can tell a filtered jump from a real disagreement. An unbounded span
    # filters nothing: see the helper.
    intra_jumps = _intra_procedural_jump_targets(listing_addresses, listing_texts)
    filtered_jumps = intra_jumps or set()
    listing_calls = listing_transfers - filtered_jumps
    edges_truncated = bool(dependencies.get("edges_truncated") or dependencies.get("callees_truncated"))
    xref_present = isinstance(dependencies.get("edges"), list)
    machines_agree = xref_present and listing is not None and not edges_truncated
    jump_note = ""
    if filtered_jumps:
        low, high = _span_bounds(listing_addresses)
        jump_note = ("; %d intra-procedural jump(s) target inside the recovered body span 0x%08x..0x%08x are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: %s" % (len(filtered_jumps), low, high, ", ".join(sorted(filtered_jumps))))
    # -- CALLS: the authoritative xref export, read whole --------------------
    # ``dependencies.edges`` is a *scheduler projection* of the export, capped at
    # MAX_DEPENDENCY_EDGES=30 rows per record, and ``edges_truncated`` is computed
    # over that record's incoming *and* outgoing rows -- with the projection sorted
    # so that every incoming row precedes every outgoing one (measured on the 617
    # index records: 149 carry the flag, but only 25 have more than 30 outgoing
    # rows and 47 project no outgoing callee at all, their whole 30-row window
    # spent on fan-in). So the flag is set far more often than the callee set is
    # truncated, and warning on it unconditionally was a permanent WARN on a
    # category error: a bounded projection is not the xref universe.
    #
    # The export that truncated it is still on disk, so CALLS reads it for this VA
    # and adjudicates over the whole callee set. ``None`` here means the export is
    # not available -- absent, unreadable, of another shape -- and every arm below
    # is then reached exactly as it was before.
    from .evidence_xrefs import decide as _decide_calls
    _authoritative = _decide_calls(record=record, categories=categories, abi_outer=abi_outer,
                                   abi_inner=abi_inner, listing=listing, scoped_text=scoped_text,
                                   target_span=target_span, source_path=source_path,
                                   dependencies=dependencies, root=root)
    if _authoritative is not None:
        checks["CALLS"] = _authoritative
    elif not source_path or not target_span:
        checks["CALLS"] = _check("NOT_AVAILABLE", "target source span is not deterministically available", "none")
    elif edges_truncated:
        checks["CALLS"] = _check("WARN", "the dependency edge list is truncated at export time, so the machine callee set is a lower bound and cannot bound the source", "partial", [INDEX_REL])
    elif not machine_calls and listing is None:
        # An empty out-edge set with no second machine side is not a refutation:
        # the export recorded nothing and nothing else was collected, so there is
        # still no oracle to agree or disagree with. Read as a finding it would
        # refute every reconstruction that names a callee, on the strength of an
        # absence.
        checks["CALLS"] = _check("NOT_AVAILABLE", "the xref export records no call edge out of this target and no listing is available; neither call oracle exists, so there is nothing to agree or disagree with", "none", [INDEX_REL])
    elif source_calls - machine_calls:
        # The source-vs-xref rule, and it still speaks first: a named callee the
        # export does not record is a contradiction whatever the listing holds.
        missing = sorted(source_calls - machine_calls)
        checks["CALLS"] = _check("FAIL", "the source-vs-xref rule: %d address-named source call(s) have no call edge in the xref export: %s" % (len(missing), ", ".join(missing)), "partial", [INDEX_REL])
    elif machines_agree and not machine_calls and not listing_calls:
        # Both oracles searched and both empty. That is not a missing value: two
        # independent machine sources agree that this body transfers control
        # nowhere, which is the evidence for the absence of a call.
        checks["CALLS"] = _check("PASS", "the machine-vs-machine rule: the xref export and the complete %d-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either%s" % (len(listing_texts), jump_note), "complete", [INDEX_REL, EVIDENCE_REL])
    elif machines_agree and machine_calls != listing_calls:
        # Two bounded, independent machine sources that do not agree. Either the
        # export does not carry every transfer the body makes -- the export records
        # calls and not jumps, so a tail call is exactly such a gap -- or the
        # listing is a slice. Both are statements about the evidence, and the
        # honest verdict for inconsistent evidence is not a pass.
        extra = sorted(listing_calls - machine_calls)
        absent = sorted(machine_calls - listing_calls)
        detail = "the machine-vs-machine rule: the xref export records %d callee(s) and the complete %d-instruction listing %d direct transfer(s), and the two sets disagree%s" % (len(machine_calls), len(listing_texts), len(listing_calls), jump_note)
        if extra:
            detail += "; %d transfer(s) the body makes are not in the export: %s" % (len(extra), ", ".join(extra))
        if absent:
            detail += "; %d export callee(s) the body does not show: %s" % (len(absent), ", ".join(absent))
        checks["CALLS"] = _check("FAIL", detail, "partial", [INDEX_REL, EVIDENCE_REL])
    elif machines_agree:
        # The two independent machine sources name the same set of targets. A
        # source claim outside that set is already a FAIL above, so nothing the
        # reconstruction says here is unaccounted for.
        checks["CALLS"] = _check("PASS", "the machine-vs-machine rule: the xref export and the complete %d-instruction listing name the same %d direct transfer target(s)%s%s; the source span names %d of them and no others" % (len(listing_texts), len(machine_calls), (", including a target reached only by a jump" if machine_calls & _jump_transfer_targets(listing_texts) else ""), jump_note, len(source_calls)), "complete", [INDEX_REL, EVIDENCE_REL])
    elif not source_calls:
        checks["CALLS"] = _check("WARN", "the source span names no address-suffixed callee, so its %d call(s) cannot be compared with the machine" % len(machine_calls), "partial", [INDEX_REL])
    elif source_calls == machine_calls:
        checks["CALLS"] = _check("PASS", "the source-vs-xref rule: all %d machine callee(s) and all %d address-named source call(s) agree with the xref export; no listing is available for the second machine side" % (len(machine_calls), len(source_calls)), "partial", [INDEX_REL])
    else:
        checks["CALLS"] = _check("PASS", "the source-vs-xref rule: every one of the %d address-named source call(s) is a machine callee; %d further callee(s) are not address-named in the source" % (len(source_calls), len(machine_calls - source_calls)), "partial", [INDEX_REL])
    # -- GLOBALS -----------------------------------------------------------
    # Two machine sides exist, and they are independent in what they can say.
    #
    # The listing is a *rendering* of the body: it shows the operands, so it can
    # name a data-segment address a reader can point at in the text.
    #
    # The data-reference artifact (``evidence_datarefs``) is Ghidra's own
    # reference database for the body, over the frozen 58,757-function universe,
    # and it says something the listing cannot: whether each reference is a READ
    # or a WRITE, and which segment the address lives in. Before it existed, the
    # edge export carried no data-reference edge type at all (its ``data-ref``
    # rows are defined as references to *function entries*), so there was no
    # second machine side and every non-absence was an uncheckable warning.
    #
    # The arms below are ordered so this can only ever add corroboration:
    #
    #   * A PASS is left alone. The absence arm ("the listing names no data
    #     address") is positive evidence on its own and does not need a second
    #     source, and a corroborating artifact that contradicts it is a finding
    #     about the evidence, not a licence to revoke a pass -- so it is
    #     reported and the verdict stands.
    #   * A WARN becomes a PASS only when the artifact independently records a
    #     reference to every address the source names, and the listing
    #     corroborates at least one of them. Two machine sources agreeing, plus
    #     the reconstruction agreeing with them, is the same shape CALLS already
    #     accepts.
    #   * Every other WARN stays a WARN, with the artifact's own reading added to
    #     the detail. In particular an address the artifact does NOT record is
    #     never on its own a refutation: the artifact's universe is the pinned
    #     caller set, and a body whose references were read at a different moment
    #     than the reconstruction would produce exactly this shape.
#   * If the artifact is absent, unreadable or mis-shaped, every arm below is
    #     reached exactly as it was before, and ``NOT_AVAILABLE`` keeps its
    #     wording. That is what makes the wire-in behaviour-preserving.
    data = _read_data_refs(root, record.get("va"))
    checks["GLOBALS"] = _globals_verdict(
        listing_texts=listing_texts,
        scoped_text=scoped_text,
        oracle=data,
        recorded=set(data["targets"]) if data["state"] == "complete" else set(),
        data_note=(data["note"] + "; ") if data["state"] == "complete" else "",
        global_evidence=categories.get("globals", {}).get("value"),
    )
    # -- FIELDS/OFFSETS ----------------------------------------------------
    # The machine-derived ``receiver`` record (``abi_derived`` first, ``abi`` second:
    # see ``_machine_record``) names the base register the body addresses the
    # receiver through and the displacements it was seen using there. So a body
    # can be checked against it. What it is *not* is a field layout --
    # ``bounds_only`` is true on 190 of 194 packs carrying it and 75 of those list
    # no offsets at all -- so a pass here says the displacements are grounded
    # within the machine-derived receiver bounds, and never that a field layout is
    # confirmed. Naming a field is not declaring an offset (so a type mention is
    # not a claim) and declaring an offset nothing grounds is not a pass; the arm
    # that warned about an uncorroborated declaration is kept for the case where no
    # machine evidence exists to ground it, and it is reached only when there is
    # no receiver register or no complete listing -- never ahead of the grounded
    # arms below, which is the single most common shape and used to be preempted.
    fields = categories.get("types", {}).get("value") or []
    declared = _field_declarations(scoped_text)
    receiver = _machine_record(categories, abi_outer, abi_inner, "receiver")
    register = receiver.get("register")
    bounds = set(value for value in (receiver.get("offsets") or []) if isinstance(value, int))
    declared_numbers = _declared_displacements(declared)
    named_fields = sorted(entry for entry in declared if entry.startswith("field "))
    # Two machine witnesses, and neither substitutes for the other. The record is
    # the inference's own observation, which follows a register alias
    # (``MOV EBX,ECX`` then ``[EBX+0x18]``) that the literal-operand scan below
    # cannot see; the scan is the listing's own, read straight off the operands.
    # For a body that aliases its receiver -- the shape 0x006a2a80 has -- the scan
    # is empty while the record is not, so the record is the only witness that can
    # ground a declaration the body makes through the alias. Neither being empty
    # is a count of zero: an empty set here is an absence, and the arms below only
    # ever pass over an absence the complete listing accounts for.
    displacements = _receiver_displacements(listing_texts, register) if listing is not None and register else set()
    outside = sorted((displacements | declared_numbers) - bounds)
    unclaimed = sorted(declared_numbers - bounds)
    # The parse record, read the one way this module reads any machine record, and
    # asked only the completeness question: a listing with an instruction the
    # machine parse did not consume is not the whole of the body, and a body half
    # seen cannot be shown to contain no field access. It gates the receiver-agnostic
    # absence arm below and nothing else -- the arms above need a register, which is
    # a property of the record rather than of the listing's wholeness. Read here
    # rather than reused from the CONSTANTS arm below, which keeps that arm's own
    # reads untouched.
    parse_record = _machine_record(categories, abi_outer, abi_inner, "parse")
    listing_fully_parsed = bool(parse_record) and parse_record.get("degraded") is not True \
        and not (parse_record.get("unparsed") or 0)
    # The FIELDS/OFFSETS readings the alias-aware scan settles and the arms below
    # cannot. Taken first, so a pack the scan repairs never reaches an arm that
    # assumes the receiver register's own operands are the whole witness -- the
    # body that copies its receiver into a scratch register and then reads
    # ``[EBX+0x18]`` is invisible to ``_receiver_displacements`` (measured: 16
    # corpus targets held a PASS whose "addresses no receiver field" claim the
    # machine refutes, and 16 more were told the source and the body disagree with
    # a record the complete listing itself contradicts). ``decide`` returns ``None``
    # whenever it has nothing to add -- no complete listing, no receiver register, a
    # verdict weaker than the one below, or a verdict identical to it -- and every
    # arm below then applies byte for byte as it did before. Imported here rather
    # than at module scope because that module reads this one.
    from .evidence_fields import decide as _fields_decide
    _fields_verdict = _fields_decide(record=record, categories=categories, abi_outer=abi_outer,
                                     abi_inner=abi_inner, listing=listing, scoped_text=scoped_text,
                                     target_span=target_span, source_path=source_path)
    if _fields_verdict is not None:
        checks["FIELDS/OFFSETS"] = _fields_verdict
    elif listing is not None and register:
        if unclaimed and receiver.get("bounds_only") is not True:
            # Only an *enumerating* record can refute a declared member. With
            # ``bounds_only`` the record states where the body was seen reaching
            # and no more, so a declared member outside that window is
            # uncorroborated rather than contradicted, and it warns.
            checks["FIELDS/OFFSETS"] = _check("FAIL", "the machine-derived receiver record enumerates the displacement(s) %s and the source span declares %s, which is not among them" % (sorted("0x%x" % value for value in bounds), ", ".join("0x%x" % value for value in unclaimed)), "partial", [INDEX_REL, EVIDENCE_REL])
        elif outside:
            # Both directions are named, because either one could be the mistake and
            # naming only the disagreement would hide which side made it: a
            # displacement the source declares that the body never shows, and a
            # displacement the body shows that the source never accounts for.
            checks["FIELDS/OFFSETS"] = _check("WARN", "%d displacement(s) (%s) lie outside the machine-derived receiver bounds (%s) for %s, so the source and the body disagree with the receiver record; the source span declares %s, and the complete %d-instruction listing names %s through that register" % (len(outside), _hex_values(outside), _hex_values(bounds), register, _hex_values(declared_numbers), len(listing_texts), _hex_values(displacements)), "partial", [INDEX_REL, EVIDENCE_REL])
        elif named_fields:
            # A name is a stronger claim than a displacement, and the receiver
            # record is a set of displacements: it says nothing about which member
            # is which, so it can neither confirm nor refute ``->field`` and the
            # name stays a review item however well the offsets beside it are
            # grounded. The offsets are reported either way, so a reader sees
            # exactly which half of the declaration the machine evidence reaches.
            detail = "the source span names field %s and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it" % ", ".join(entry[6:] for entry in named_fields[:4])
            if bounds and (displacements or declared_numbers):
                detail += "; the %d displacement(s) in that same span are grounded within the machine-derived receiver bounds (%s), so it is the name alone that is uncorroborated" % (len(displacements | declared_numbers), _hex_values(bounds))
            checks["FIELDS/OFFSETS"] = _check("WARN", detail, "partial", [INDEX_REL, EVIDENCE_REL])
        elif not displacements and not declared_numbers:
            # The evidenced absence, and the only PASS that needs no bounds: there
            # is nothing to ground and the complete listing is the evidence that
            # there is nothing.
            detail = "the complete %d-instruction listing names no displacement through %s, which is evidence that the body addresses no receiver field; the source span declares no field offset either" % (len(listing_texts), register)
            if bounds:
                detail += ("; the machine-derived receiver record does enumerate %d displacement(s) (%s), which it observed through a register alias rather than through that register's own operands, so the scan is the narrower of the two witnesses here"
                           % (len(bounds), _hex_values(bounds)))
            checks["FIELDS/OFFSETS"] = _check("PASS", detail, "complete", [INDEX_REL, EVIDENCE_REL])
        else:
            # The grounded arm, and it is reached only over a non-empty bounds set:
            # ``outside`` empty with a displacement to account for means the
            # record holds it, so this can never pass against an absent record.
            checks["FIELDS/OFFSETS"] = _check("PASS", "the %d displacement(s) the source span declares (%s) and the %d the complete %d-instruction listing names through %s (%s) are all within the machine-derived receiver bounds (%s), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name" % (len(declared_numbers), _hex_values(declared_numbers), len(displacements), len(listing_texts), register, _hex_values(displacements), _hex_values(bounds)), "complete", [INDEX_REL, EVIDENCE_REL])

    elif declared:
        checks["FIELDS/OFFSETS"] = _check("WARN", "%d source field-offset declaration(s) (%s) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against" % (len(declared), ", ".join(sorted(declared)[:4])), "partial", [INDEX_REL])
    elif (listing is not None and listing_fully_parsed
          and not _any_field_access(listing_texts)):
        # The second evidenced absence, and it is the arm for the case the guard
        # above excludes by construction: the record abstains on the receiver
        # (``receiver_not_determinable``, ``ecx_address_taken_without_memory_access``,
        # or a record naming no register at all), so there is no register to scan
        # the listing under and the check had no way to say anything about a body
        # that performs no field access -- an adjustor thunk, a constant stub, a
        # leaf -- and it fell to NOT_AVAILABLE, which is disqualifying for a
        # reconstruction with nothing wrong with it.
        #
        # What makes it evidence is the same thing the first absence rests on and
        # nothing else: a listing that is *complete* (``_listing`` already returns
        # ``None`` for a truncated envelope and for an empty body) and that the
        # machine parse consumed in full, read over *any* register because the
        # receiver register is exactly what is unknown. A body that addresses no
        # memory operand at all addresses no object, so it addresses no receiver
        # field; a single bracket anywhere -- through any register, any
        # displacement, a bare ``[ECX]`` -- takes the body out of this arm and
        # back to the one it already had.
        #
        # Two things are deliberately not claimed. The first is that the receiver
        # is undetermined, and the detail says that as an absence of a record
        # rather than as a fact about the target. The second is that any layout
        # has been confirmed: nothing here knows a receiver exists, and the pass
        # is about the body having no field access, not about a receiver having
        # no fields.
        checks["FIELDS/OFFSETS"] = _check("PASS", "the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete %d-instruction listing was consumed in full by the machine parse (degraded=%s, unparsed=%d) and names no memory operand through any register at all, which is the evidence that this function performs no field access; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist" % (len(listing_texts), bool(parse_record.get("degraded")), int(parse_record.get("unparsed") or 0)), "complete", [INDEX_REL, EVIDENCE_REL])
    elif (listing is not None and listing_fully_parsed
          and _all_operands_absolute(listing_texts)):
        # The third evidenced absence, and the narrowest of the three: the body
        # *does* address memory, but every operand it addresses is a
        # segment-absolute address.
        #
        # The case is the Simulator root-slot accessors -- seven committed
        # two-instruction bodies of the shape ``MOV EAX,[0x0167ead8]`` / ``RET``
        # over the 0x0167eac0 table. Ghidra brackets an absolute read, so the arm
        # above reads it as a field access and declines; but an absolute operand
        # names no register, and a receiver is reachable only through a register,
        # so it cannot be a receiver field access. Nothing about the target is
        # wrong; the arm above simply has no way to say anything about it, and it
        # fell to NOT_AVAILABLE.
        #
        # Every guard the arm above holds is held here too, and they are the same
        # guards rather than new ones: the listing must be complete (``_listing``
        # already returns ``None`` for a truncated envelope and for an empty body)
        # and consumed in full by the machine parse, and the source span must
        # declare no field offset -- the ``declared`` arm above is reached first
        # precisely so a reconstruction that states its own offset is a WARN and
        # never a clearance.
        #
        # What this claims is the narrow half only: the body performs no
        # *register-relative* access, so it performs no receiver-relative one.
        # Three things are deliberately NOT claimed, and the detail says so:
        #
        #   * that the receiver is undetermined -- that is an absence of a record,
        #     not a fact about the target;
        #   * that any layout is confirmed -- nothing here knows a receiver
        #     exists;
        #   * that the absolute address is not a global. That is GLOBALS'
        #     dimension, it is judged on its own two machine sides, and an
        #     absence of register-relative access says nothing whatsoever about
        #     it. This arm must not be readable as a claim that the body touches
        #     no global, because the very body this arm clears is a global-slot
        #     reader.
        absolute = [match.group(1) for text in listing_texts
                    for match in MEMORY_OPERAND.finditer(str(text))]
        checks["FIELDS/OFFSETS"] = _check("PASS", "the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete %d-instruction listing was consumed in full by the machine parse (degraded=%s, unparsed=%d) and every memory operand it names (%s) is a segment-absolute address naming no register, which is the evidence that this function performs no register-relative access and therefore no receiver-relative one -- a receiver is reachable only through a register, so an absolute operand cannot address one; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist; what this says about the absolute addresses themselves is nothing: whether one of them is a global is GLOBALS' question, judged on its own machine sides, and this arm neither confirms nor denies it" % (len(listing_texts), bool(parse_record.get("degraded")), int(parse_record.get("unparsed") or 0), ", ".join(absolute) if absolute else "none"), "complete", [INDEX_REL, EVIDENCE_REL])
    else:
        checks["FIELDS/OFFSETS"] = _check("NOT_AVAILABLE", "the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names %d type(s)" % len(fields), "none", [INDEX_REL])

    # -- CONSTANTS ---------------------------------------------------------
    # Two questions, kept apart. The first judges the reconstruction: does the
    # listing show every hexadecimal literal the source span states? The second
    # judges the evidence: was that listing fully consumed by the machine parse?
    # Only when both hold may this pass, and then the claim it makes is about the
    # listing being whole -- never that the reconstruction's constants are
    # correct, which is the first question's to answer and not this pass's.
    # ``observed_mechanics`` is a worker-authored transcript of the same read that
    # produced the source, so it is reported as agreement-in-transcript and never
    # promoted to a verdict.
    literal_evidence = record.get("observed_mechanics", [])
    source_constants = _hex_tokens(scoped_text)
    machine_constants = set()
    for text in listing_texts or ():
        machine_constants |= _hex_tokens(text)
    parse = _machine_record(categories, abi_outer, abi_inner, "parse")
    declared_count = parse.get("declared_count")
    if listing is None:
        mechanics = set()
        for entry in literal_evidence or []:
            if isinstance(entry, str):
                mechanics |= _hex_tokens(entry)
        if source_constants and mechanics:
            unproven = sorted(source_constants - mechanics)
            detail = ("all %d source constant(s) appear in the recorded mechanics transcript" % len(source_constants)) if not unproven else ("%d source constant(s) are absent from the recorded mechanics transcript: %s" % (len(unproven), ", ".join(unproven)))
            checks["CONSTANTS"] = _check("WARN", detail + "; that transcript is reconstruction-authored and is not independent evidence", "partial", [INDEX_REL])
        elif source_constants or literal_evidence:
            checks["CONSTANTS"] = _check("WARN", "source constants are present and no machine listing is collected for this target, so they cannot be corroborated", "partial", [INDEX_REL])
        else:
            checks["CONSTANTS"] = _check("NOT_AVAILABLE", "no constant evidence available", "none")
    elif source_constants - machine_constants:
        # The source-vs-listing rule, and it speaks first: a listing that does not
        # contain a stated literal refutes the claim whether or not the listing is
        # shown to be whole, and a truncated envelope never reaches here at all.
        unproven = sorted(source_constants - machine_constants)
        checks["CONSTANTS"] = _check("FAIL", "the source-vs-listing rule: %d source constant(s) are absent from the machine listing: %s" % (len(unproven), ", ".join(unproven)), "partial", [EVIDENCE_REL])
    elif not parse or not isinstance(declared_count, int):
        checks["CONSTANTS"] = _check("NOT_AVAILABLE", "the %d-instruction listing exists but carries no machine parse record, so it cannot be shown to have been consumed in full" % len(listing_texts), "none", [EVIDENCE_REL])
    elif declared_count != len(listing_texts):
        # The integrity check: the parse consumed a different number of
        # instructions than the listing holds, so the two disagree about the body.
        checks["CONSTANTS"] = _check("FAIL", "the machine parse declared %d instruction(s) and the listing holds %d, so the two disagree about the body and neither can be taken as the whole of it" % (declared_count, len(listing_texts)), "partial", [EVIDENCE_REL])
    elif parse.get("degraded") is True or (parse.get("unparsed") or 0) > 0:
        checks["CONSTANTS"] = _check("WARN", "the machine listing is not fully parsed: %d of %d instruction(s) consumed, degraded=%s, unparsed=%d" % (declared_count, len(listing_texts), bool(parse.get("degraded")), int(parse.get("unparsed") or 0)), "partial", [EVIDENCE_REL])
    elif source_constants:
        checks["CONSTANTS"] = _check("PASS", "the machine listing is fully parsed (%d of %d instruction(s), %d unparsed) and all %d source constant(s) appear in it" % (declared_count, len(listing_texts), int(parse.get("unparsed") or 0), len(source_constants)), "complete", [EVIDENCE_REL])
    else:
        checks["CONSTANTS"] = _check("PASS", "the machine listing is fully parsed (%d of %d instruction(s), %d unparsed) and the source span states no hexadecimal constant for it to lack" % (declared_count, len(listing_texts), int(parse.get("unparsed") or 0)), "complete", [EVIDENCE_REL])
    # -- CONTROL FLOW ------------------------------------------------------
    # The machine claim in this dimension is bounded, so the check can have a PASS
    # arm at all: take the span the listing itself occupies and ask whether the
    # branch graph closes inside it. ``ghidra_function.dispatch`` is null in every
    # committed pack because the bridge passes the field through without computing
    # it, so branching on it was branching on nothing; the listing is the real
    # oracle. A straight-line body passes trivially -- the complete listing *is*
    # the evidence that there is no branch.
    #
    # The source's ``if``/``for``/``while``/``switch`` words are reported inside
    # the detail and are never part of the verdict. Comparing CFG shape against
    # keyword count is unbounded in both directions -- a compiler reorders blocks
    # and merges identical tails -- and making it a condition is what left this
    # check with no PASS arm and held the whole static aggregate at zero.
    flow_words = {word: bool(re.search(r"\b%s\b" % word, _code(scoped_text))) for word in ("if", "for", "while", "switch")}
    keywords = sorted(word for word, present in flow_words.items() if present)
    keyword_note = "the source span declares %s" % (", ".join(keywords) if keywords else "no branch keyword")
    if listing is None:
        checks["CONTROL FLOW"] = _check("NOT_AVAILABLE", "no machine control-flow evidence exists for this target: the bridge never populates the dispatch field and no complete listing is collected", "none", [INDEX_REL, EVIDENCE_REL])
    else:
        branches = [text for text in listing_texts if CONDITIONAL_BRANCH.match(text or "")]
        if not branches:
            checks["CONTROL FLOW"] = _check("PASS", "the complete %d-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; %s, and keyword shape is a source-side signal that is not part of this verdict" % (len(listing_texts), keyword_note), "complete", [INDEX_REL, EVIDENCE_REL])
        else:
            bounds = _span_bounds(listing_addresses)
            escaping, unbounded = _branch_closure(listing_addresses, listing_texts)
            if unbounded:
                checks["CONTROL FLOW"] = _check("WARN", "%d of %d conditional branch(es) in the %d-instruction listing have no absolute target the recovered body can be bounded against, so the branch graph cannot be shown to close; %s" % (unbounded, len(branches), len(listing_texts), keyword_note), "partial", [INDEX_REL, EVIDENCE_REL])
            elif escaping:
                checks["CONTROL FLOW"] = _check("WARN", "%d of %d conditional branch target(s) fall outside the recovered body span 0x%08x..0x%08x, so the listing is a slice and flow continues past it; %s" % (len(escaping), len(branches), bounds[0], bounds[1], keyword_note), "partial", [INDEX_REL, EVIDENCE_REL])
            else:
                checks["CONTROL FLOW"] = _check("PASS", "all %d conditional branch target(s) in the complete %d-instruction listing lie inside the recovered body span 0x%08x..0x%08x, so the branch graph is closed inside it; %s, and keyword shape is a source-side signal that is not part of this verdict" % (len(branches), len(listing_texts), bounds[0], bounds[1], keyword_note), "complete", [INDEX_REL, EVIDENCE_REL])
    # -- VIRTUAL DISPATCH --------------------------------------------------
    # ``record["vtables"]`` is withdrawn as an oracle: it is a transitive
    # classifier association that contradicts the xref export outright (356 vtable
    # ids against a vtable_reference_count of 0 on the same record). What is left
    # is the listing and the ABI envelope's own dispatch record, two machine
    # sources: the record agrees with the listing on 169 of 172 packs and covers
    # targets whose listing was truncated away. A pass needs both to say zero --
    # a complete listing that shows no indirect transfer, corroborated by a record
    # that also counts none.
    vtables = record.get("vtables", []) or []
    virtual_source = any(token in _code(scoped_text) for token in ("load_slot", "object_slot", "shell_slot", "vtable", "slot["))
    vtable_refs = dependencies.get("vtable_reference_count") or 0
    dispatch = _machine_record(categories, abi_outer, abi_inner, "dispatch")
    dispatch_count = dispatch.get("indirect_calls")
    if not isinstance(dispatch_count, int):
        dispatch_count = None
    if listing is None:
        if virtual_source:
            checks["VIRTUAL DISPATCH"] = _check("UNKNOWN", "the source declares an opaque slot boundary and no machine listing exists to confirm or contradict it", "partial", [INDEX_REL])
        else:
            checks["VIRTUAL DISPATCH"] = _check("NOT_AVAILABLE", "no machine dispatch evidence is collected for this target; the xref export records %d vtable reference(s) and the record associates %d vtable(s), which are not independent of each other" % (vtable_refs, len(vtables)), "none", [INDEX_REL])
    else:
        sites = _indirect_sites(listing_texts)
        proven_empty = not sites and dispatch_count == 0
        if virtual_source and not sites:
            # Now based on the fixed detector, so it can no longer fire on a body
            # whose only dispatch is a register transfer or a ``dword ptr``
            # operand -- the two shapes it used to be blind to.
            checks["VIRTUAL DISPATCH"] = _check("FAIL", "the complete %d-instruction body contains no indirect transfer through a register or a memory operand%s, but the source span declares a virtual-slot boundary" % (len(listing_texts), " and the machine dispatch record agrees at 0" if dispatch_count == 0 else ""), "partial", [INDEX_REL, EVIDENCE_REL])
        elif proven_empty:
            checks["VIRTUAL DISPATCH"] = _check("PASS", "the complete %d-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at %d, so neither the body nor the source span claims virtual dispatch" % (len(listing_texts), dispatch_count), "complete", [INDEX_REL, EVIDENCE_REL])
        elif not sites and dispatch_count is None:
            checks["VIRTUAL DISPATCH"] = _check("WARN", "the complete %d-instruction body names no indirect transfer, but no machine dispatch record was collected to corroborate it; a missing record is not a record of zero" % len(listing_texts), "partial", [EVIDENCE_REL])
        else:
            # A body that does dispatch, read positively. ``_dispatch_verdict``
            # returns ``None`` for anything its own evidence does not adjudicate --
            # an incomplete listing, an unparsed one, a dispatch record that is
            # missing or disagrees with the listing's own site count, or a site
            # whose shape is not a vtable slot -- and the arm below is then reached
            # exactly as it was before.
            adjudicated = _dispatch_verdict(
                record=record, categories=categories, abi_outer=abi_outer, abi_inner=abi_inner,
                listing=listing, scoped_text=scoped_text, target_span=target_span,
                source_path=source_path, dependencies=dependencies)
            if adjudicated is not None:
                checks["VIRTUAL DISPATCH"] = adjudicated
            else:
                detail = "the complete %d-instruction body names %d indirect dispatch site(s) and the machine dispatch record counts %s" % (len(listing_texts), len(sites), dispatch_count if dispatch_count is not None else "nothing -- no record was collected")
                if sites and dispatch_count is not None and len(sites) != dispatch_count:
                    detail += "; the two machine sources disagree, so the listing is probably a slice and the site count is a lower bound"
                if virtual_source:
                    detail += " and the source declares a slot boundary, so slot offsets need review"
                elif sites:
                    detail += " that the source span does not describe"
                checks["VIRTUAL DISPATCH"] = _check("WARN", detail, "partial", [INDEX_REL, EVIDENCE_REL])
    # ``return_type`` only -- see ``_canonical_return_type`` for why a
    # ``return_semantics`` classification is not a return type here.
    canonical_return = _canonical_return_type(abi_sources)
    source_return = _return_type(target_span)
    # A canonical return claim is present on 506 of the 586 committed packs and the
    # two arms below already own those. The remaining ones carry no ``return_type``
    # in any layer, so the check could only read NOT_AVAILABLE there -- but the
    # evidence for a verdict does exist: the ABI envelope's return sub-record, and
    # the complete machine listing, between them determine whether a value comes
    # back at all and at what width. ``decide`` states that in an explicit
    # vocabulary (``VOID_PROVEN``, ``WIDTH_n_IN_R``, ``SRET_PROVEN``,
    # ``UNCLASSIFIED``, ``NOT_AVAILABLE``) and returns ``None`` whenever it is not
    # adjudicating -- so the string-agreement PASS and the "semantically renamed"
    # WARN below are untouched, and no absent record is ever read as a void.
    from . import evidence_returns as _returns_evidence
    _return_evidence = _returns_evidence.decide(record=record, categories=categories, abi_outer=abi_outer,
                                                 abi_inner=abi_inner, listing=listing, scoped_text=scoped_text,
                                                 target_span=target_span, source_path=source_path)
    if not source_path:
        checks["RETURN SEMANTICS"] = _check("NOT_AVAILABLE", "no canonical source artifact", "none")
    elif _return_evidence:
        checks["RETURN SEMANTICS"] = _check(_return_evidence["status"], _return_evidence["detail"],
                                            _return_evidence["coverage"], _return_evidence["evidence"])
    elif canonical_return and source_return:
        if str(canonical_return).replace(" ", "").casefold() == str(source_return).replace(" ", "").casefold():
            checks["RETURN SEMANTICS"] = _check("PASS", "return type agrees with the bounded ABI record", "partial", [INDEX_REL])
        else:
            checks["RETURN SEMANTICS"] = _check("WARN", "return type differs or is semantically renamed; review required", "partial", [INDEX_REL])
    else:
        checks["RETURN SEMANTICS"] = _check("NOT_AVAILABLE", "return evidence is not deterministically available", "none")
    # -- EVIDENCE COVERAGE -------------------------------------------------
    # A coverage measurement, not a verdict on the reconstruction, and scoped to
    # the static dimension: the ``runtime`` category belongs to the other axis and
    # is permanently unavailable, so counting it in this denominator let a
    # capability gap veto a static verdict. It is reported in full and excluded
    # from the aggregate -- except for its NOT_AVAILABLE floor, which is a real
    # gate: a reconstruction cannot be statically validated against zero evidence.
    static_categories = [value for key, value in categories.items() if key != RUNTIME_CATEGORY]
    evidence_available = sum(1 for value in static_categories if value.get("availability") == "available")
    if evidence_available == 0:
        checks[COVERAGE_CHECK] = _check("NOT_AVAILABLE", "no static evidence category is available for this target", "none")
    elif evidence_available < len(static_categories):
        checks[COVERAGE_CHECK] = _check("WARN", "%d of %d static evidence categories are available" % (evidence_available, len(static_categories)), "partial", [INDEX_REL])
    else:
        checks[COVERAGE_CHECK] = _check("PASS", "all %d static evidence categories are available" % len(static_categories), "complete", [INDEX_REL])
    coverage_check = checks[COVERAGE_CHECK]
    attempted = sum(1 for check in checks.values() if check["status"] != "NOT_AVAILABLE")
    passed = sum(1 for check in checks.values() if check["status"] == "PASS")
    warned = sum(1 for check in checks.values() if check["status"] == "WARN")
    unknown = sum(1 for check in checks.values() if check["status"] == "UNKNOWN")
    structural = {name: check for name, check in checks.items() if name != COVERAGE_CHECK}
    structural_attempted = sum(1 for check in structural.values() if check["status"] != "NOT_AVAILABLE")
    structural_passed = sum(1 for check in structural.values() if check["status"] == "PASS")
    # One ladder, one check set. FAIL, UNKNOWN and WARN are read from the same
    # set: previously WARN scanned every check, so the coverage metric could hold
    # a static PASS down while a FAIL could not.
    #
    # Every structural check must be adjudicated for a PASS. ``NOT_AVAILABLE``
    # used to be neutral -- skipped, like a dimension that was never asked -- so a
    # PASS could rest on a single evaluated check while seven went unjudged, and
    # nothing in the verdict said so. That is a false-PASS vector: an absence of
    # evidence was being averaged in as if it were agreement. NA now names the
    # aggregate instead of being absorbed by it, which subsumes the old
    # "nothing was attempted" case (all eight NA is one NA), and the
    # ``EVIDENCE COVERAGE`` floor stays a floor: a reconstruction cannot be
    # statically validated against zero evidence however clean its checks read.
    #
    # Severity, loudest first. A FAIL is a contradiction the machine positively
    # established -- an ABI conflict, a source constant absent from the listing,
    # a displacement outside the machine-derived receiver bounds -- so it is the
    # loudest signal in the system and must never be masked by an unadjudicated
    # dimension: the worst finding is a finding regardless of how much else went
    # unmeasured. UNKNOWN is next, because it is a declared boundary nobody could
    # judge. NA outranks WARN because the two mean opposite things about the
    # distance to agreement: WARN means "adjudicated and ungrounded", which is the
    # nearer failure, while NA means "not adjudicated". PASS still requires all
    # eight structural checks to be PASS -- the all-or-nothing requirement is the
    # strengthening here and it is not relaxed by this ordering.
    if any(check["status"] == "FAIL" for check in structural.values()):
        aggregate = "FAIL"
    elif any(check["status"] == "UNKNOWN" for check in structural.values()):
        aggregate = "UNKNOWN"
    elif any(check["status"] == "NOT_AVAILABLE" for check in structural.values()):
        aggregate = "NOT_AVAILABLE"
    elif coverage_check["status"] == "NOT_AVAILABLE":
        aggregate = "NOT_AVAILABLE"
    elif any(check["status"] == "WARN" for check in structural.values()):
        aggregate = "WARN"
    else:
        aggregate = "PASS"
    runtime = _runtime_dimension(record, categories)
    questions = []
    for value in record.get("unresolved_questions", []) or []:
        if isinstance(value, str):
            questions.append(value)
    for value in runtime["gates"]:
        questions.append(str(value))
    all_questions = sorted(set(questions))
    questions = all_questions[:32]
    # ``evidence_basis`` is what makes a thin PASS legible as thin. A static PASS
    # means every check that could be evaluated agreed; it does not mean the whole
    # corpus was checked, and the count of what actually was is reported here
    # rather than left for a reader to infer from a single word.
    evidence_basis = {
        "static_checks_total": len(structural),
        "static_checks_evaluated": structural_attempted,
        "static_checks_passed": structural_passed,
        "static_checks_not_available": len(structural) - structural_attempted,
        "static_evidence_categories_available": evidence_available,
        "static_evidence_categories_total": len(static_categories),
    }
    report = {
        "schema": "openspore-structural-validation-1",
        "target": va,
        "source": {"path": relative(source_path, root) if source_path else None, "sha256": None, "role": source_role},
        "binary_evidence": {"mode": evidence.get("evidence_state"),
                            "content_sha256": evidence.get("content_sha256"),
                            "source": evidence_source,
                            "integrity": evidence_integrity,
                            "integrity_note": persisted_note},
        # The briefing, recorded and deliberately not read. ``context`` is built
        # from the same record and the same pack as the checks above, so reading
        # it here could contribute no fact that is not already in evidence -- but
        # it would make a verdict depend on a worker-facing document, which is a
        # path for the judged party to edit the inputs of its own judgement. Its
        # identity travels with the report so a reader can confirm for themselves
        # that both were built from one pack.
        "worker_context": {"source": CONTEXT_SOURCE_CALLER if context_supplied else CONTEXT_SOURCE_BUILT,
                           "status": context.get("status") if isinstance(context, dict) else None,
                           "content_sha256": context.get("content_sha256") if isinstance(context, dict) else None,
                           "pack_content_sha256": _context_pack_digest(context)},
        "status": aggregate,
        "static": {
            "dimension": STATIC_DIMENSION,
            "status": aggregate,
            "checks": structural,
            "coverage": {"attempted": structural_attempted, "pass": structural_passed,
                         "warn": sum(1 for check in structural.values() if check["status"] == "WARN"),
                         "unknown": sum(1 for check in structural.values() if check["status"] == "UNKNOWN"),
                         "not_available": len(structural) - structural_attempted,
                         "total": len(structural),
                         "ratio": round(structural_passed / len(structural), 3) if structural else 0.0},
            "evidence_basis": evidence_basis,
            "evidence_coverage": coverage_check,
        },
        "runtime": runtime,
        "checks": checks,
        "coverage": {"attempted": attempted, "pass": passed, "warn": warned, "unknown": unknown, "not_available": len(checks) - attempted, "total": len(checks), "ratio": round(passed / len(checks), 3) if checks else 0.0},
        "unresolved_questions": questions,
        "unresolved_questions_omitted": max(0, len(all_questions) - len(questions)),
        "provenance": [INDEX_REL, EVIDENCE_REL + "/" + va[2:] + "/evidence.json"],
    }
    if source_path:
        report["source"]["sha256"] = file_sha256(source_path)
    if write:
        write_json_atomic(destination / "validation.json", report)
        write_text_atomic(destination / "validation.md", render_markdown(report))
    report["paths"] = {"directory": str(destination), "written": bool(write), "validation_json": str(destination / "validation.json") if write else None, "validation_md": str(destination / "validation.md") if write else None}
    return report


def render_markdown(report):
    static = report.get("static") or {}
    runtime = report.get("runtime") or {}
    lines = ["# Validation %s" % report["target"], "",
             "- Static reconstruction: `%s`" % static.get("status", report.get("status")),
             "- Runtime (original process): `%s`" % runtime.get("status"),
             "- Source: `%s`" % (report["source"].get("path") or "missing"), "",
             "The two axes are independent. A static verdict says the reconstruction agrees with the",
             "binary; it says nothing about the original process, and is never a runtime claim.", "",
             "## Static checks", "",
             "| Check | Status | Coverage | Detail |", "|---|---|---|---|"]
    for name, check in (static.get("checks") or report.get("checks") or {}).items():
        detail = check["detail"].replace("|", "\\|")
        lines.append("| %s | `%s` | `%s` | %s |" % (name, check["status"], check["coverage"], detail))
    basis = static.get("evidence_basis") or {}
    if basis:
        lines.extend(["", "Static evidence basis: %d of %d static checks evaluated, %d passed, %d had no evidence to evaluate; %d of %d static evidence categories available."
                      % (basis.get("static_checks_evaluated", 0), basis.get("static_checks_total", 0),
                         basis.get("static_checks_passed", 0), basis.get("static_checks_not_available", 0),
                         basis.get("static_evidence_categories_available", 0),
                         basis.get("static_evidence_categories_total", 0))])
    coverage_check = static.get("evidence_coverage")
    if coverage_check:
        lines.append("")
        lines.append("Evidence coverage is a measurement, not a verdict: `%s` -- %s"
                     % (coverage_check["status"], coverage_check["detail"]))
    evidence_block = report.get("binary_evidence") or {}
    lines.extend(["", "## Binary evidence", "",
                  "- Evidence state: `%s`" % evidence_block.get("mode"),
                  "- Pack source: `%s`" % evidence_block.get("source"),
                  "- Pack integrity: `%s`" % evidence_block.get("integrity"),
                  "- Content SHA-256: `%s`" % evidence_block.get("content_sha256")])
    note = evidence_block.get("integrity_note")
    if note:
        # A pack that failed verification is the one case a reader must not have
        # to go looking for: the verdict below was reached over a different pack.
        lines.append("- Integrity note: %s" % note)
    context_block = report.get("worker_context") or {}
    if context_block:
        lines.extend(["", "## Worker briefing", "",
                      "- Source: `%s`" % context_block.get("source"),
                      "- Briefing status: `%s`" % context_block.get("status"),
                      "- Content SHA-256: `%s`" % context_block.get("content_sha256"),
                      "- Pack digest quoted by the briefing: `%s`" % context_block.get("pack_content_sha256")])
    lines.extend(["", "## Runtime", "",
                  "- Status: `%s`" % runtime.get("status"),
                  "- Original-process observations validated: `%s`" % runtime.get("validated", 0),
                  "- Reason: %s" % runtime.get("reason", "")])
    gates = runtime.get("gates") or []
    lines.append("- Open runtime gates: %s" % (", ".join("`%s`" % gate for gate in gates) if gates else "none recorded"))
    lines.extend(["", "A gated runtime is an open capability gate on the original process. Nothing was",
                  "attempted and nothing failed.", "",
                  "## Unresolved questions", ""])
    lines.extend("- %s" % value for value in report["unresolved_questions"])
    if not report["unresolved_questions"]:
        lines.append("- None recorded in the canonical record.")
    lines.append("")
    return "\n".join(lines)
