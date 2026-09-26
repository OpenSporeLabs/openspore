import re
from pathlib import Path

from .models import ROOT, ToolError, file_sha256, normalize_va, relative, write_json_atomic, write_text_atomic

INDEX_REL = "reconstruction/knowledge/index.json"
EVIDENCE_REL = "reconstruction/evidence"
SOURCE_SUFFIXES = (".c", ".cc", ".cpp", ".cxx", ".h", ".hpp")
SOURCE_ROLES = (("src/", "canonical"), ("reconstruction/staging/", "staging"))
RETURN_DECL = re.compile(r"(?m)^\s*(?:(?:extern\s+\"C\"|extern|static|inline|constexpr)\s+)*(?P<return>(?:const\s+)?[A-Za-z_][A-Za-z0-9_:<>*&]*)\s+(?:(?:[A-Z][A-Z0-9_]*|__[A-Za-z0-9_]+)\s+)*(?P<name>[A-Za-z_][A-Za-z0-9_:]*)\s*\([^;{}]*\)\s*(?:const\s*)?\{")
DEFINE = re.compile(r"(?m)^[ \t]*#[ \t]*define[ \t]+(?P<name>[A-Za-z_][A-Za-z0-9_]*)(?P<gap>[ \t]+)(?P<body>[^\n]*)")
CONVENTIONS = ("cdecl", "thiscall", "fastcall", "stdcall")
ABI_INFERENCE_SCHEMA = "openspore-abi-inference-"
RESOLVED_CONFLICT_STATES = {"resolved", "resolved_no_conflict", "agreed", "no_conflict", "closed"}

# The two validation dimensions. A reconstruction is judged against the static
# binary; the original process is a separate axis that no static verdict may
# speak for. ``report["status"]`` remains an alias of the static verdict so every
# existing consumer keeps its current meaning.
STATIC_DIMENSION = "STATIC"
RUNTIME_DIMENSION = "RUNTIME"
RUNTIME_CATEGORY = "runtime"
COVERAGE_CHECK = "EVIDENCE COVERAGE"
# The checks that judge the reconstruction against evidence. ``NOT_AVAILABLE`` on
# one of these is an absence of evidence, never evidence of failure, and is
# therefore neutral: it neither passes nor poisons the aggregate.
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
INDIRECT_CALL = re.compile(r"^\s*(?:CALL|JMP)\s+(?:[A-Z]{2,3}\s+PTR\s+)?\[", re.IGNORECASE)
CONDITIONAL_BRANCH = re.compile(r"^\s*J(?!MP\b)[A-Z]{1,3}\b|^\s*LOOP\w*\b", re.IGNORECASE)


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
        if normalized.startswith("fun") and va_token:
            candidates = [span for span, key in spans if va_token in key and "fun" in key]
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


def _code(text):
    """``text`` with comments removed.

    Every token comparison below is a claim about what the reconstruction *does*,
    so it must be made about code only. Scanning comments produced a real false
    positive: a source whose sole ``for`` was the English word inside ``// ...``
    was read as branching where the machine body was straight-line.
    """
    return LINE_COMMENT.sub(" ", BLOCK_COMMENT.sub(" ", text or ""))


def _hex_tokens(text):
    """Hexadecimal literals in ``text``.

    Only an explicitly written ``0x`` token counts. A pattern that also matches
    bare decimal runs would sweep in array sizes and line numbers, and a
    reconstruction would then be failed for disagreeing with a number that was
    never a constant.
    """
    return set(token.lower() for token in HEX_TOKEN.findall(_code(text)))


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


def _instructions(categories):
    """Machine instruction text for this target, or ``None``.

    ``None`` means "no independent listing exists", which is not the same claim as
    "the listing is empty". Only 4 of the 8 committed packs carry one, so most
    targets legitimately have nothing to compare against.
    """
    category = (categories.get("disassembly") or {}).get("value")
    if not isinstance(category, dict):
        return None
    items = category.get("instructions")
    if not isinstance(items, list):
        return None
    return [str(item.get("instruction", "")) for item in items if isinstance(item, dict)]


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
    """Absolute addresses in the data segment, from instruction text or source."""
    found = set()
    for token in _hex_tokens(" ".join(texts) if isinstance(texts, (list, tuple)) else texts):
        if CODE_END <= int(token, 16) < 0x02000000:
            found.add(token)
    return found


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


def validate(root=ROOT, va=None, evidence=None, context=None, write=True, out_dir=None):
    root = Path(root)
    if va is None:
        raise ToolError("missing_va", "a target VA is required", 2)
    try:
        va = normalize_va(va)
    except (TypeError, ValueError) as exc:
        raise ToolError("invalid_va", str(exc), 2)
    if evidence is None:
        from .evidence import collect
        evidence = collect(root=root, va=va, live=False, write=write, out_dir=out_dir)
    if context is None:
        from .context import build
        context = build(root=root, va=va, evidence=evidence, live=False, write=write, out_dir=out_dir)
    index = _index(root)
    record = _record(index, va)
    resolved = _source(root, record)
    source_path = resolved["path"] if resolved else None
    source_role = resolved["role"] if resolved else "missing"
    source_text = _read_source(source_path)
    target_span = _target_span(source_text, record)
    scoped_text = target_span.get("text", "") if target_span else ""
    categories = evidence.get("categories", {})
    persisted_abi = record.get("abi", {}) or {}
    derived_abi, abi_inference = _abi_category(categories)
    abi_sources = [persisted_abi, derived_abi]
    dependencies = record.get("dependencies", {}) or {}
    checks = {}
    convention = _convention_key(_abi_claim(abi_sources, "calling_convention", "convention"))
    persisted_claim = _convention_key(persisted_abi.get("calling_convention") or persisted_abi.get("convention"))
    derived_claim = _convention_key(derived_abi.get("calling_convention") or derived_abi.get("convention"))
    convention_claims = [claim for claim in (persisted_claim, derived_claim) if claim]
    source_conventions = _source_conventions(scoped_text, _convention_defines(source_text))
    mismatched = [claim for claim in convention_claims if not any(claim == key for key in source_conventions)]
    blocking_conflicts = _abi_conflicts(abi_inference, evidence)
    confidence = _derived_field(abi_inference, "conventions", "confidence").casefold()
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
    # The xref export is the one call oracle in this repository that is
    # independent of the reconstruction, so it is the one place a call set can be
    # adjudicated rather than merely described. Two absences are explicitly NOT
    # failures: a target with no out-edge, and a target whose edge list was
    # truncated at export time. Both are missing evidence.
    source_calls = _callee_addresses(scoped_text, record)
    machine_calls = _machine_callees(dependencies)
    edges_truncated = bool(dependencies.get("edges_truncated") or dependencies.get("callees_truncated"))
    if not source_path or not target_span:
        checks["CALLS"] = _check("NOT_AVAILABLE", "target source span is not deterministically available", "none")
    elif not machine_calls:
        checks["CALLS"] = _check("NOT_AVAILABLE", "the xref export records no call edge out of this target; there is no oracle to agree or disagree with", "none", [INDEX_REL])
    elif edges_truncated:
        checks["CALLS"] = _check("WARN", "the dependency edge list is truncated at export time, so the machine callee set is a lower bound and cannot bound the source", "partial", [INDEX_REL])
    elif not source_calls:
        checks["CALLS"] = _check("WARN", "the source span names no address-suffixed callee, so its %d call(s) cannot be compared with the machine" % len(machine_calls), "partial", [INDEX_REL])
    elif source_calls - machine_calls:
        missing = sorted(source_calls - machine_calls)
        checks["CALLS"] = _check("FAIL", "%d address-named source call(s) have no call edge in the xref export: %s" % (len(missing), ", ".join(missing)), "partial", [INDEX_REL])
    elif source_calls == machine_calls:
        checks["CALLS"] = _check("PASS", "all %d machine callee(s) and all %d address-named source call(s) agree with the xref export" % (len(machine_calls), len(source_calls)), "complete", [INDEX_REL])
    else:
        checks["CALLS"] = _check("PASS", "every one of the %d address-named source call(s) is a machine callee; %d further callee(s) are not address-named in the source" % (len(source_calls), len(machine_calls - source_calls)), "complete", [INDEX_REL])
    # -- GLOBALS -----------------------------------------------------------
    # No PASS branch and no FAIL branch, deliberately. The only machine-side
    # data-reference oracle in the index is ``data_reference_count``, non-zero for
    # 1 of 546 records, and ``record["globals"]`` is worker-authored prose, so
    # validating the source against it would be validating it against itself. A
    # FAIL is withheld too: a source may legitimately reach a data address
    # arithmetically, in which case the listing would not name it, and a verdict
    # that misfires on that is worse than no verdict.
    global_evidence = categories.get("globals", {}).get("value")
    data_refs = dependencies.get("data_reference_count") or 0
    listing = _instructions(categories)
    if not source_path:
        checks["GLOBALS"] = _check("NOT_AVAILABLE", "no canonical source artifact", "none")
    elif listing is not None:
        source_data = _data_addresses(scoped_text)
        machine_data = _data_addresses(listing)
        if source_data & machine_data:
            checks["GLOBALS"] = _check("WARN", "%d source data address(es) appear in the machine listing; read/write mode still needs per-access evidence" % len(source_data & machine_data), "partial", [INDEX_REL, EVIDENCE_REL])
        else:
            checks["GLOBALS"] = _check("NOT_AVAILABLE", "the source span names %d data address(es) and the %d-instruction listing corroborates none; the xref export records %d independent data reference(s)" % (len(source_data), len(listing), data_refs), "none", [EVIDENCE_REL])
    elif global_evidence:
        checks["GLOBALS"] = _check("WARN", "global references are recorded but they are reconstruction-authored; the xref export carries %d independent data reference(s) for this target" % data_refs, "partial", [INDEX_REL])
    else:
        checks["GLOBALS"] = _check("NOT_AVAILABLE", "no independent data-reference evidence exists for this target; the xref export records %d" % data_refs, "none", [INDEX_REL])
    # -- FIELDS/OFFSETS ----------------------------------------------------
    # No PASS branch and no FAIL branch. The type set carries names only, and the
    # types that carry declared offsets are reconstruction-declared, so nothing
    # here can corroborate a physical offset.
    #
    # The WARN is conditional on the source actually declaring an offset. Naming
    # a type is not declaring a field offset, and warning that "offsets are
    # reconstruction-declared and uncorroborated" about a span that declares none
    # states a defect that does not exist -- and it did so for 54 of the 57
    # targets this check was the sole blocker for, which made a uniform capability
    # gap look like a per-target finding. A target that does declare offsets
    # still WARNs, and still blocks.
    fields = categories.get("types", {}).get("value") or []
    if not source_path:
        checks["FIELDS/OFFSETS"] = _check("NOT_AVAILABLE", "no canonical source artifact", "none")
    else:
        declared = _field_declarations(scoped_text)
        if not declared:
            checks["FIELDS/OFFSETS"] = _check("NOT_AVAILABLE", "the source span declares no field offset, and no machine-derived struct layout is collected for this target; the record names %d type(s)" % len(fields), "none", [INDEX_REL])
        else:
            checks["FIELDS/OFFSETS"] = _check("WARN", "%d source field-offset declaration(s) (%s) are reconstruction-declared and no machine-derived struct layout exists to corroborate them" % (len(declared), ", ".join(sorted(declared)[:4])), "partial", [INDEX_REL])
    # -- CONSTANTS ---------------------------------------------------------
    # PASS and FAIL require the disassembly tier. ``observed_mechanics`` is a
    # worker-authored transcript of the same read that produced the source, so it
    # is reported as agreement-in-transcript and never promoted to a verdict.
    literal_evidence = record.get("observed_mechanics", [])
    source_constants = _hex_tokens(scoped_text)
    machine_constants = set()
    for text in listing or ():
        machine_constants |= _hex_tokens(text)
    if not source_path or not target_span:
        checks["CONSTANTS"] = _check("NOT_AVAILABLE", "target source span is not deterministically available", "none")
    elif listing is None:
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
    elif not source_constants:
        checks["CONSTANTS"] = _check("NOT_AVAILABLE", "the source span states no hexadecimal constant to compare with the %d-instruction listing" % len(listing), "none", [EVIDENCE_REL])
    elif source_constants - machine_constants:
        unproven = sorted(source_constants - machine_constants)
        checks["CONSTANTS"] = _check("FAIL", "%d source constant(s) are absent from the machine listing: %s" % (len(unproven), ", ".join(unproven)), "partial", [EVIDENCE_REL])
    else:
        checks["CONSTANTS"] = _check("PASS", "all %d source constant(s) appear in the %d-instruction machine listing" % (len(source_constants), len(listing)), "complete", [EVIDENCE_REL])
    # -- CONTROL FLOW ------------------------------------------------------
    # No PASS branch. ``ghidra_function.dispatch`` is null in every committed
    # pack because the bridge passes the field through without computing it, so
    # branching on it was branching on nothing. The listing is the real oracle.
    flow_words = {word: bool(re.search(r"\b%s\b" % word, _code(scoped_text))) for word in ("if", "for", "while", "switch")}
    if not source_path:
        checks["CONTROL FLOW"] = _check("NOT_AVAILABLE", "no canonical source artifact", "none")
    elif listing is None:
        checks["CONTROL FLOW"] = _check("NOT_AVAILABLE", "no machine control-flow evidence exists for this target: the bridge never populates the dispatch field and no listing is collected", "none", [INDEX_REL, EVIDENCE_REL])
    else:
        branches = sum(1 for text in listing if CONDITIONAL_BRANCH.match(text or ""))
        keywords = sorted(word for word, present in flow_words.items() if present)
        checks["CONTROL FLOW"] = _check("WARN", "the %d-instruction body has %d conditional branch(es) and the source span declares %s; CFG shape comparison is unbounded" % (len(listing), branches, ", ".join(keywords) or "no branch"), "partial", [INDEX_REL, EVIDENCE_REL])
    # -- VIRTUAL DISPATCH --------------------------------------------------
    # ``record["vtables"]`` is withdrawn as an oracle: it is a transitive
    # classifier association that contradicts the xref export outright (356 vtable
    # ids against a vtable_reference_count of 0 on the same record). Only the
    # listing can adjudicate a slot boundary.
    vtables = record.get("vtables", []) or []
    virtual_source = any(token in _code(scoped_text) for token in ("load_slot", "object_slot", "shell_slot", "vtable", "slot["))
    vtable_refs = dependencies.get("vtable_reference_count") or 0
    if not source_path:
        checks["VIRTUAL DISPATCH"] = _check("NOT_AVAILABLE", "no canonical source artifact", "none")
    elif listing is None:
        if virtual_source:
            checks["VIRTUAL DISPATCH"] = _check("UNKNOWN", "the source declares an opaque slot boundary and no machine listing exists to confirm or contradict it", "partial", [INDEX_REL])
        else:
            checks["VIRTUAL DISPATCH"] = _check("NOT_AVAILABLE", "no machine dispatch evidence is collected for this target; the xref export records %d vtable reference(s) and the record associates %d vtable(s), which are not independent of each other" % (vtable_refs, len(vtables)), "none", [INDEX_REL])
    else:
        indirect = [text for text in listing if INDIRECT_CALL.match(text or "")]
        if indirect and virtual_source:
            checks["VIRTUAL DISPATCH"] = _check("WARN", "the body has %d indirect dispatch site(s) and the source declares a slot boundary; slot offsets need review" % len(indirect), "partial", [INDEX_REL, EVIDENCE_REL])
        elif indirect:
            checks["VIRTUAL DISPATCH"] = _check("WARN", "the body has %d indirect dispatch site(s) that the source span does not describe" % len(indirect), "partial", [EVIDENCE_REL])
        elif virtual_source:
            checks["VIRTUAL DISPATCH"] = _check("FAIL", "the %d-instruction body contains no indirect call but the source span declares a virtual-slot boundary" % len(listing), "partial", [INDEX_REL, EVIDENCE_REL])
        else:
            checks["VIRTUAL DISPATCH"] = _check("PASS", "neither the %d-instruction body nor the source span claims virtual dispatch" % len(listing), "complete", [EVIDENCE_REL])
    canonical_return = _abi_claim(abi_sources, "return_type", "return_semantics")
    source_return = _return_type(target_span)
    if not source_path:
        checks["RETURN SEMANTICS"] = _check("NOT_AVAILABLE", "no canonical source artifact", "none")
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
    # One ladder, one check set. FAIL, UNKNOWN and WARN are now read from the
    # same set: previously WARN scanned every check, so the coverage metric could
    # hold a static PASS down while a FAIL could not.
    if structural_attempted == 0 or coverage_check["status"] == "NOT_AVAILABLE":
        aggregate = "NOT_AVAILABLE"
    elif any(check["status"] == "FAIL" for check in structural.values()):
        aggregate = "FAIL"
    elif any(check["status"] == "UNKNOWN" for check in structural.values()):
        aggregate = "UNKNOWN"
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
        "binary_evidence": {"mode": evidence.get("evidence_state"), "content_sha256": evidence.get("content_sha256")},
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
    destination = Path(out_dir) if out_dir else Path(root) / EVIDENCE_REL / va[2:]
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
