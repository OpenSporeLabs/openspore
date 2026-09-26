import json
from pathlib import Path

from .models import ROOT, ToolError, bounded, canonical_json, compact, normalize_va, optional_json, relative, sha256_json, write_json_atomic, write_text_atomic

try:
    from tools.mcp import ghidra_tools
except ImportError as exc:
    raise RuntimeError("existing Ghidra module is unavailable") from exc

# Pure ABI inference is an optional, feature-detected collaborator. It is being
# developed in parallel and may be absent, may expose a different entry point
# name, or may raise on an input shape it does not recognise. None of that is
# allowed to change this module's behaviour: when the hook cannot run, the pack
# is bit-identical to what it was before the hook existed. The persisted
# ``record["abi"]`` stays the canonical ABI home either way -- a derived value
# is a pack-local projection and is never written back to the index.
try:
    from . import abi_infer
except ImportError:  # pragma: no cover - the module is optional by design
    abi_infer = None

ABI_INFER_REL = "tools/reconstruction_tooling/abi_infer.py"
# Entry points accepted on the collaborator, most specific first. This is a
# capability probe, not an API contract: an unrecognised module simply means no
# derivation happens. The engine's real signature is
# ``analyze(disassembly, *, call_sites, ghidra_calling_convention,
# ghidra_parameter_count, persisted_abi, image_base)``; ``analyze`` is therefore
# the primary name, and the rest are kept only for forward compatibility. Any
# of them reached under a name that does not accept the keyword arguments
# raises ``TypeError`` and degrades to ``None`` rather than to a half-applied
# derivation -- which is exactly what the previous positional-retry path did.
ABI_INFER_ENTRIES = ("analyze", "infer_abi", "derive_abi", "infer", "derive")
# --------------------------------------------------------------------------
# Storage bound for the derived ABI record. The number lives here and nowhere
# else.
#
# WHAT IT BOUNDS: the *stored* value of ``categories["abi"]["value"]`` when the
# engine's record would be larger than this. It is a bound on the transcript,
# never on the claims. A record that fits is stored byte-identical -- that is
# the overwhelming majority of derivations and it is what keeps the committed
# packs unchanged. A record that does not fit is stored as a *projection* (see
# ``_stored_derived_record``) which keeps every decision-relevant field complete
# and compacts only the per-instruction / per-slot transcript.
#
# WHAT IT MUST NEVER DO: turn the value into ``compact``'s opaque
# ``{"truncated": ...}`` envelope. ``validate._abi_category`` reads that
# envelope as "no derived record", so an envelope does not degrade the evidence,
# it deletes it -- and it used to delete it for exactly the functions with the
# most evidence, because the record is dominated by ``observations`` (a verbatim
# transcript of every instruction). A large target with no persisted ABI
# therefore stored an envelope and the whole feature went silently missing for
# the largest functions in the binary. The budget stays a bound, not an
# invitation to grow.
ABI_DERIVED_MAX_BYTES = 24000
#: Observation fields a projection always keeps: which observation, of which
#: kind, at which address, at which instruction index. This is the identity an
#: audit needs and the minimum ``inferences[].based_on`` needs to resolve.
ABI_DERIVED_OBSERVATION_IDENTITY = ("id", "index", "at", "kind")
#: Longest free-text value a projected observation keeps verbatim. Anything
#: longer is a verbatim instruction fragment or a prose reason -- transcript,
#: not a fact -- and is truncated with an ellipsis.
ABI_DERIVED_OBSERVATION_TEXT = 96
#: Element cap for the per-slot transcripts (the slot tables under
#: ``stack_arguments`` and the three copies of it inside ``abi``). The scalar
#: summary next to each list -- ``observed_slots``, ``derived_slots``, ``gaps``,
#: ``total_bytes``, ``confidence`` -- is never bounded, because that is where
#: the decision is.
ABI_DERIVED_TRANSCRIPT_ELEMENTS = 24
#: The same cap, cut to the bone, for a record that is still over budget.
ABI_DERIVED_TRANSCRIPT_ELEMENTS_MIN = 2
#: ``(dotted path of a transcript list, key of the marker its bound is
#: recorded under)``. The marker is a sibling of the list it bounds, so no list
#: ever grows a synthetic element and the bound is stated next to what it bounds.
ABI_DERIVED_TRANSCRIPTS = (
    ("stack_arguments.slots", "slots_bounded"),
    ("abi.stack_arguments", "stack_arguments_bounded"),
    ("abi.ordinary_stack_arguments", "ordinary_stack_arguments_bounded"),
    ("abi.ordinary_stack_argument_slots", "ordinary_stack_argument_slots_bounded"),
)
#: The keys the last resort keeps. A stored derived value is always a real
#: record with a readable ``verdict``, ``abi``, ``abstained_because`` and
#: ``conflicts`` -- never an envelope -- so this set is the floor.
ABI_DERIVED_MINIMUM_KEYS = ("schema", "verdict", "completeness", "abi",
                            "conventions", "abstained_because", "conflicts")
#: The reduction ladder, applied in this order, one rung at a time, stopping at
#: the first rung that fits. Order is the contract: the transcript goes first
#: (it is the bulk and the least decision-relevant), then the per-function
#: bookkeeping, then the ABI claim block, and only last the reasoning trace. A
#: rung is a no-op for a record that has nothing of its shape -- there are no
#: slot transcripts to shed in a record with no slots -- and a no-op rung still
#: fits, so the ladder simply moves past it. ``projection["applied_steps"]``
#: records exactly which rungs were consumed, so a rung that changed nothing is
#: visible rather than silent.
ABI_DERIVED_PROJECTION_STEPS = (
    "observations_identity_only",
    "transcripts_minimised",
    "observations_dropped",
    "parse_dropped",
    "dispatch_dropped",
    "abi_transcripts_dropped",
    "abi_claims_only",
)
#: How each rung leaves ``observations``, reported in the ``projection`` marker.
ABI_DERIVED_OBSERVATION_FORMS = {
    "observations_identity_only": "identity_only",
    "observations_dropped": "dropped",
}
DEFAULT_IMAGE_BASE = 0x00400000
# Fixed-priority convention tokens. Twin of ``CONVENTIONS`` in
# ``reconstruction_knowledge.extract_abi`` and of ``_convention_key`` in
# ``validate.py:118``; the order is the contract, because a string naming two
# conventions resolves to the first token it contains.
CONVENTION_KEYS = ("fastcall", "thiscall", "stdcall", "cdecl")

INDEX_REL = "reconstruction/knowledge/index.json"
EVIDENCE_REL = "reconstruction/evidence"
SNAPSHOT_GLOB = "ghidra_snapshot_*.json"
FUNCTION_KEYS = ("address", "va", "function_address")
DECOMPILATION_KEYS = ("decompiled", "decompiled_evidence", "decompilation", "code")


def _index(root):
    from .frontier import _index as fresh_index
    return fresh_index(root)


def _record(index, va):
    records = index.get("records", {}) if isinstance(index, dict) else {}
    return records.get(va, {}) if isinstance(records, dict) else {}


def _record_view(record):
    source = record.get("source", {}) or {}
    dependencies = record.get("dependencies", {}) or {}
    triage = record.get("triage", {}) or {}
    semantic = record.get("semantic", {}) or {}
    caller_values = dependencies.get("callers") or []
    callee_values = dependencies.get("callees") or []
    external_values = dependencies.get("external_callees") or []
    edge_values = dependencies.get("edge_rows") or dependencies.get("edges") or []
    return {
        "va": record.get("va"),
        "name": record.get("name") or record.get("normalized_symbol"),
        "package": record.get("package"),
        "subsystem": record.get("subsystem"),
        "status": record.get("status"),
        "reconstructed": record.get("reconstructed"),
        "blocked": record.get("blocked"),
        "runtime_gated": record.get("runtime_gated"),
        "evidence_level": record.get("evidence_level"),
        "abi": compact(record.get("abi", {}), 6000),
        "dependencies": compact({
            "callers": caller_values[:16],
            "callees": callee_values[:16],
            "external_callees": external_values[:16],
            "edges": edge_values[:24],
            "fan_in": dependencies.get("fan_in", len(caller_values)),
            "fan_out": dependencies.get("fan_out", len(callee_values)),
        }, 10000),
        "types": (record.get("types") or [])[:24],
        "globals": (record.get("globals") or [])[:16],
        "vtables": (record.get("vtables") or [])[:16],
        "runtime": compact(record.get("runtime", {}), 5000),
        "semantic": compact(semantic, 6000),
        "source": {key: source.get(key) for key in ("file", "files", "metadata", "handoffs", "decomp") if source.get(key)},
        "unresolved_questions": record.get("unresolved_questions", [])[:16],
        "analogues": compact(record.get("analogues", [])[:8], 5000),
        "triage": {key: triage.get(key) for key in ("rank", "priority", "evidence", "category", "cluster", "subsystem", "queue_state", "in_degree") if key in triage},
    }


def _target_conflicts(index, va):
    if not va:
        return []
    conflicts = []
    for item in index.get("contradictions", []) if isinstance(index, dict) else []:
        if not isinstance(item, dict):
            continue
        if item.get("va") == va or va in (item.get("anchors", []) or []):
            conflicts.append(item)
    return conflicts


def _walk_dicts(value):
    if isinstance(value, dict):
        yield value
        for key in sorted(value):
            yield from _walk_dicts(value[key])
    elif isinstance(value, list):
        for item in value:
            yield from _walk_dicts(item)


def _address(value):
    for key in FUNCTION_KEYS:
        if key in value:
            try:
                return normalize_va(value[key])
            except (TypeError, ValueError):
                return None
    return None


def _snapshot_function(root, va):
    candidates = []
    for path in sorted((Path(root) / "tools" / "re" / "data").glob(SNAPSHOT_GLOB)):
        document = optional_json(path)
        if document is None:
            continue
        for item in _walk_dicts(document):
            if _address(item) != va:
                continue
            if "name" not in item and "signature" not in item and not any(key in item for key in DECOMPILATION_KEYS):
                continue
            candidates.append((relative(path, root), item))
    if not candidates:
        return None
    provenance, value = candidates[0]
    return {"status": "ok", "mode": "snapshot", "provenance": provenance, "data": value}


def _live_function(va):
    try:
        response = ghidra_tools.ghidra_function({"address": va, "force": True})
    except Exception as exc:
        return {"status": "error", "mode": "live", "provenance": "GhidraMCP live query", "code": "ghidra_offline", "message": str(exc)}
    if not isinstance(response, dict) or response.get("status") != "ok":
        return {"status": "error", "mode": "live", "provenance": "GhidraMCP live query", "code": (response or {}).get("code", "ghidra_offline"), "message": (response or {}).get("message", "Ghidra function query failed")}
    if response.get("mode") != "live":
        return {"status": "error", "mode": "live", "provenance": response.get("provenance", "GhidraMCP live query"), "code": "live_unavailable", "message": "Ghidra returned %s instead of live evidence" % response.get("mode", "unknown")}
    data = response.get("data", response)
    if not isinstance(data, dict):
        return {"status": "error", "mode": "live", "provenance": response.get("provenance", "GhidraMCP live query"), "code": "invalid_response", "message": "Ghidra returned an invalid function response"}
    data = dict(data)
    data["va"] = va
    return {"status": "ok", "mode": "live", "provenance": response.get("provenance", "GhidraMCP /get_function_by_address + /analyze_function_complete"), "data": data}


def _live_decompile(va):
    try:
        response = ghidra_tools.ghidra_decompile({"address": va, "force": True})
    except Exception as exc:
        return {"status": "error", "mode": "live", "provenance": "GhidraMCP /decompile_function", "code": "ghidra_offline", "message": str(exc)}
    if not isinstance(response, dict) or response.get("status") != "ok":
        return {"status": "error", "mode": "live", "provenance": "GhidraMCP /decompile_function", "code": (response or {}).get("code", "decompile_failed"), "message": (response or {}).get("message", "Ghidra decompilation failed")}
    if response.get("mode") != "live":
        return {"status": "error", "mode": "live", "provenance": response.get("provenance", "GhidraMCP /decompile_function"), "code": "live_unavailable", "message": "Ghidra returned %s instead of live evidence" % response.get("mode", "unknown")}
    data = response.get("data", response)
    text = data.get("decompiled") if isinstance(data, dict) else None
    if not text:
        text = data.get("code") if isinstance(data, dict) else None
    if not text:
        return {"status": "error", "mode": "live", "provenance": response.get("provenance", "GhidraMCP /decompile_function"), "code": "empty_decompile", "message": "Ghidra returned no decompilation text"}
    return {"status": "ok", "mode": "live", "provenance": response.get("provenance", "GhidraMCP /decompile_function"), "text": str(text)}


def _live_disassembly(va):
    try:
        client = ghidra_tools._get_client()
        response = client.request("/disassemble_function", {"address": va})
    except Exception:
        return {"status": "error", "mode": "live", "provenance": "GhidraMCP /disassemble_function", "code": "disassembly_unavailable", "message": "Ghidra disassembly endpoint unavailable"}
    if not isinstance(response, dict) or response.get("status") != "ok":
        return {"status": "error", "mode": "live", "provenance": "GhidraMCP /disassemble_function", "code": "disassembly_unavailable", "message": "Ghidra disassembly unavailable"}
    data = response.get("data", response)
    if isinstance(data, dict) and data.get("mode") not in (None, "live"):
        return {"status": "error", "mode": "live", "provenance": "GhidraMCP /disassemble_function", "code": "live_unavailable", "message": "Ghidra returned %s instead of live disassembly" % data.get("mode")}
    # Two views of the same bridge response, deliberately. ``data`` is the
    # *stored* evidence: the 12000-byte budget every other category uses, so
    # the category value and the pack's ``content_sha256`` are exactly what they
    # were before this line. ``listing`` is the *derivation's* input, kept whole,
    # because ``compact`` hands the ABI engine a ``{"truncated": ...}`` envelope
    # for anything past the budget and ``_disassembly_payload`` rightly refuses
    # to derive from an envelope -- which silently starved the largest functions
    # in the binary, the ones with the most ABI evidence. Nothing serialises the
    # card as a whole (only ``data`` and ``provenance`` reach the pack), so the
    # uncompacted copy stays in memory and never lands on disk.
    return {"status": "ok", "mode": "live", "provenance": "GhidraMCP /disassemble_function",
            "data": compact(data, 12000), "listing": data}


def _abi_infer_entry():
    # type: () -> object
    """The callable ABI inference entry point, or ``None`` when unavailable."""
    if abi_infer is None:
        return None
    for name in ABI_INFER_ENTRIES:
        candidate = getattr(abi_infer, name, None)
        if callable(candidate):
            return candidate
    return None


def _expected_abi_schema():
    # type: () -> object
    """The engine's schema id, read off the module rather than written here."""
    return getattr(abi_infer, "SCHEMA", None) if abi_infer is not None else None


def _disassembly_payload(disassembly):
    # type: (object) -> object
    """The instruction payload inside a disassembly card, or ``None``.

    The card is ``{"status", "provenance", "data": <stored>,
    "listing": <uncompacted>}`` and the bridge response is
    ``{"instructions": [...], "count": N}``. The engine's ``normalize_listing``
    already accepts a dict carrying an ``"instructions"`` key, so the payload is
    forwarded whole -- no parser is re-implemented here.

    ``listing`` is preferred and ``data`` is the fallback. Both are looked up
    through the same acceptance test, so the two paths agree by construction:
    for a listing that fit the budget ``compact`` returned it unchanged, meaning
    ``listing is data`` and there is one payload, not two candidates. The
    fallback is what keeps a card built elsewhere -- a test fixture, or any
    future caller -- working without the new key.

    A payload that has been ``compact``-truncated (large functions) keeps
    neither key and is not an observation we may derive from, so it yields
    ``None`` rather than a truncated listing that would silently mis-derive.
    """
    if not isinstance(disassembly, dict) or disassembly.get("status") != "ok":
        return None
    for key in ("listing", "data"):
        candidate = disassembly.get(key)
        if not isinstance(candidate, dict):
            continue
        if not isinstance(candidate.get("instructions"), list) and "count" not in candidate:
            continue
        return candidate
    return None


def _image_base(index):
    # type: (object) -> int
    """The projection's image base as an int; the PE default when unusable."""
    binary = index.get("binary") if isinstance(index, dict) else None
    raw = binary.get("image_base") if isinstance(binary, dict) else None
    if raw is None or isinstance(raw, bool):
        return DEFAULT_IMAGE_BASE
    if isinstance(raw, int):
        return raw
    try:
        return int(str(raw).strip(), 0)
    except (TypeError, ValueError):
        return DEFAULT_IMAGE_BASE


def _stored_bytes(value):
    # type: (object) -> int
    """Serialised size of ``value`` in bytes -- the unit the budget is in.

    ``compact`` measures with ``canonical_json``, so the budget is measured the
    same way: a value that passes the budget here is a value ``compact`` would
    have passed through unchanged.
    """
    try:
        return len(canonical_json(value).encode("utf-8"))
    except (TypeError, ValueError):
        return ABI_DERIVED_MAX_BYTES + 1


def _at_path(document, path):
    # type: (object, str) -> object
    """The value at a dotted ``path``, or ``None`` when any step is missing."""
    node = document
    for key in path.split("."):
        if not isinstance(node, dict):
            return None
        node = node.get(key)
    return node


def _with_path(document, path, value):
    # type: (object, str, object) -> object
    """A copy of ``document`` with ``path`` set to ``value``.

    Pure: every container along the path is copied, so the input document is
    never mutated and two calls on the same input produce the same output.
    """
    keys = path.split(".")
    node = dict(document)
    cursor = node
    for key in keys[:-1]:
        child = cursor.get(key)
        cursor[key] = dict(child) if isinstance(child, dict) else {}
        cursor = cursor[key]
    cursor[keys[-1]] = value
    return node


def _summarise_observation(observation):
    # type: (object) -> object
    """One observation with its verbatim transcript text bounded.

    ``raw`` is the whole reason the record is large -- it is the disassembly
    text of the instruction, repeated by every observation that instruction
    produced -- so a projection drops it. Every other field is kept: the small
    scalars (``kind``, ``reg``, ``disp``, ``resolved``, ``size``, ...) are the
    facts the inferences cite, and the long strings are the prose reasons, which
    are truncated rather than dropped so the reason itself stays readable.
    """
    if not isinstance(observation, dict):
        return observation
    summarised = {}
    for key in sorted(observation):
        if key == "raw":
            continue
        value = observation[key]
        if isinstance(value, str) and len(value) > ABI_DERIVED_OBSERVATION_TEXT:
            summarised[key] = value[:ABI_DERIVED_OBSERVATION_TEXT] + "…"
        else:
            summarised[key] = value
    return summarised


def _identity_observation(observation):
    # type: (object) -> object
    """One observation reduced to its ``id`` -- the citation handle and nothing else.

    This is the rung that keeps ``inferences[].based_on`` resolvable on a large
    record: the id is the only thing a citation needs, and it is the cheapest
    thing an observation can be. ``id`` is never a generated value, so the
    mapping from the projection back to the full record is exact.
    """
    if not isinstance(observation, dict):
        return observation
    identifier = observation.get("id")
    return {"id": identifier} if isinstance(identifier, str) else dict(observation)


def _bound_transcripts(document, limit):
    # type: (object, int) -> object
    """Bound every per-slot transcript list to ``limit`` elements.

    The bound is stated as a sibling marker rather than as a synthetic element,
    so a list of slot dicts and a list of offset strings are handled by the same
    code and no reader can mistake the marker for a slot. The scalar summary
    beside the list is untouched -- that summary is the decision, the element
    list is the transcript of it.
    """
    bounded_document = document
    for path, marker in ABI_DERIVED_TRANSCRIPTS:
        items = _at_path(bounded_document, path)
        if not isinstance(items, list) or len(items) <= limit:
            continue
        parent_path, key = path.rsplit(".", 1)
        parent = _at_path(bounded_document, parent_path)
        if not isinstance(parent, dict):
            continue
        bounded_document = _with_path(
            bounded_document, parent_path,
            dict(parent, **{marker: {"kept": limit, "omitted": len(items) - limit}}))
        bounded_document = _with_path(bounded_document, path, items[:limit])
    return bounded_document


def _reduce_derived(document, step):
    # type: (object, str) -> object
    """Apply one rung of :data:`ABI_DERIVED_PROJECTION_STEPS` to ``document``."""
    if step == "observations_identity_only":
        observations = document.get("observations") if isinstance(document, dict) else None
        if not isinstance(observations, list):
            return document
        return _with_path(document, "observations",
                          [_identity_observation(item) for item in observations])
    if step == "transcripts_minimised":
        return _bound_transcripts(document, ABI_DERIVED_TRANSCRIPT_ELEMENTS_MIN)
    if step in ("observations_dropped", "parse_dropped", "dispatch_dropped"):
        if not isinstance(document, dict):
            return document
        result = dict(document)
        result.pop(step.replace("_dropped", ""), None)
        return result
    if step in ("abi_transcripts_dropped", "abi_claims_only"):
        if not isinstance(document, dict):
            return document
        if step == "abi_claims_only":
            # The floor. Keeps the four fields the validator and the briefing
            # read -- ``verdict``, ``abi``, ``abstained_because``, ``conflicts``
            # -- plus the schema, completeness and convention confidence that
            # label them. Every key here is a scalar or a short bounded list, so
            # this rung is small by construction and the ladder always lands.
            return {key: document[key] for key in ABI_DERIVED_MINIMUM_KEYS if key in document}
        abi = document.get("abi")
        if not isinstance(abi, dict):
            return document
        claims = {}
        for key in sorted(abi):
            if key.endswith("_bounded") or isinstance(abi[key], (list, dict)):
                continue
            claims[key] = abi[key]
        return _with_path(document, "abi", claims)
    return document


def _projection_marker(record, count, form, steps):
    # type: (object, int, str, object) -> dict
    """The ``projection`` key that marks a stored value as a projection.

    ``full_record_recoverable`` is a claim about *how*, not a promise about a
    store: the full record is the canonical derivation, and re-running
    ``abi_infer.analyze()`` on the same disassembly listing reproduces it byte
    for byte, because the engine is pure. Nothing is lost by storing the
    projection -- only the transcript, and only where the budget said so.
    """
    return {
        "observations": form,
        "full_record_recoverable": True,
        "original_bytes": _stored_bytes(record),
        "observation_count": count,
        "budget_bytes": ABI_DERIVED_MAX_BYTES,
        "applied_steps": list(steps),
    }


def _stored_derived_record(record):
    # type: (object) -> object
    """The value stored for ``categories["abi"]["value"]``.

    Returns ``record`` **unchanged** when it fits :data:`ABI_DERIVED_MAX_BYTES`.
    That is the case for the overwhelming majority of derivations, and it is
    what keeps the committed packs byte-identical, so the projection below is
    never reached for them.

    When the record does not fit, it returns a *projection*: the same document
    with the transcripts bounded and a ``projection`` marker naming what was
    done, so a consumer can tell a projection from a full record and knows how
    to get the full one back (re-run ``abi_infer.analyze()`` on the disassembly
    listing -- the canonical derivation, and pure, so it is reproducible).
    Every decision-relevant field stays complete: ``verdict``, ``completeness``,
    ``conventions``, ``abi``, ``abstained_because``, ``conflicts``,
    ``cross_validation``, ``inferences``, ``receiver``, ``cleanup``, ``return``,
    ``sret``, ``stack_arguments`` and ``target`` are never bounded, and the
    per-slot transcripts are bounded only in their element lists -- the scalar
    summary beside them is the decision.

    The ladder is walked one rung at a time and the first rung that fits wins,
    so a record gets the richest projection that fits rather than the poorest
    one that would. The rungs are, in order: every observation reduced to its
    ``id``; the per-slot element lists cut to the bone; ``observations`` dropped
    (its count stays in the marker); ``parse``; ``dispatch``; the ``abi``
    transcript lists; and finally the minimum key set. A rung that has nothing
    to remove on a given record is a no-op and the ladder moves past it -- the
    marker's ``applied_steps`` says which rungs were consumed. The last rung
    still carries ``verdict`` + ``abi`` + ``abstained_because`` + ``conflicts``,
    so ``validate._abi_category`` can always read a real record: the envelope
    form is never produced on this path.

    The engine's own ``content_sha256`` is carried through untouched, because it
    is the digest of the *full* record -- which is precisely what
    ``full_record_recoverable`` promises, and it is how a consumer checks that a
    re-derived record is the one this projection came from.

    A pure function of ``record``: every container it returns is freshly built
    and no leaf is mutated, so calling it twice on the same record gives the
    same bytes, and the record it was handed is untouched. Any structural
    surprise (a non-dict record, an ``observations`` value that is not a list)
    is carried through unchanged rather than raised on.
    """
    if not isinstance(record, dict):
        return record
    if _stored_bytes(record) <= ABI_DERIVED_MAX_BYTES:
        return record
    observations = record.get("observations")
    count = len(observations) if isinstance(observations, list) else 0
    form = "summarised"
    steps = ["observations_summarised"]
    candidate = dict(record)
    if isinstance(observations, list):
        candidate = _with_path(
            candidate, "observations",
            [_summarise_observation(item) for item in observations])
    candidate = _bound_transcripts(candidate, ABI_DERIVED_TRANSCRIPT_ELEMENTS)
    candidate = _with_path(candidate, "projection",
                           _projection_marker(record, count, form, steps))
    if _stored_bytes(candidate) <= ABI_DERIVED_MAX_BYTES:
        return candidate
    for step in ABI_DERIVED_PROJECTION_STEPS:
        candidate = _reduce_derived(candidate, step)
        form = ABI_DERIVED_OBSERVATION_FORMS.get(step, form)
        steps.append(step)
        candidate = _with_path(candidate, "projection",
                               _projection_marker(record, count, form, steps))
        if _stored_bytes(candidate) <= ABI_DERIVED_MAX_BYTES:
            return candidate
    # Unreachable for a record whose leaves are JSON scalars: the final rung is
    # the minimum key set, which is bounded by construction. Kept anyway so a
    # pathological record degrades to the richest floor that was reached
    # instead of raising or reverting to an envelope.
    return candidate


def _derived_abi(va, function, disassembly, persisted_abi=None, index=None):
    # type: (...) -> object
    """Infer an ABI record from live observations, without ever failing.

    Returns ``{"value": dict, "observations": [...]}`` or ``None``. ``None`` is
    the answer for every degraded case -- module absent, entry point not
    recognised, no observation to derive over, engine raising, engine returning
    a non-dict / empty dict, or a schema mismatch -- and the caller then behaves
    exactly as it did before this helper existed.

    Deriving requires at least one live *listing*: the engine reads instructions
    and nothing else, so a snapshot function card alone is not an observation.
    The listing it reads is the card's uncompacted ``listing`` view (see
    ``_live_disassembly``), which is why the largest functions -- the ones past
    the 12000-byte stored-evidence budget -- derive at all. An ABI record with
    nothing observed behind it would be invention, which is the one thing this
    repository's evidence rules forbid. Offline collection therefore never
    derives, and its pack stays bit-identical. ``va`` is kept as the first
    positional parameter for call-site continuity; the engine reads the target
    address off the listing itself, so it is not forwarded.

    The call uses the engine's real signature -- ``analyze(disassembly, *,
    ghidra_calling_convention, ghidra_parameter_count, persisted_abi,
    image_base)`` -- exactly once, with no positional retry: a retry cannot
    distinguish a signature rejection from a ``TypeError`` raised *inside* the
    engine, and the old retry path is what turned a signature mismatch into a
    silent, wrong derivation. The Ghidra convention keys are read with
    ``.get()`` because the parallel Ghidra agent may not have landed them yet
    (offline, snapshot, or an older adapter); absence is silence, which the
    engine already treats as no-information.

    ``persisted_abi`` is the index ``record["abi"]``. It is handed to the engine
    purely as an external corroboration/conflict oracle, never written back, and
    it is what makes the pack's ``derived_vs_persisted`` conflict possible. The
    return value is checked against ``abi_infer.SCHEMA`` read off the module: a
    future rename returns ``None`` (the derivation simply does not happen, and
    the pack looks exactly as it would with the hook deleted) instead of
    storing a record no consumer recognises. The check is deliberately silent at
    runtime to keep the degraded path byte-identical; the loud, testable form of
    it is "``abi_infer.SCHEMA`` exists and ``_derived_abi`` returns non-``None``
    for a live target with a disassembly", which the live end-to-end check
    covers.

    This never mutates ``record["abi"]``, never reads or writes ``index.json``,
    and persists nothing: the result is a pack-local projection whose canonical
    home remains ``reconstruction/metadata/**``.
    """
    payload = _disassembly_payload(disassembly)
    if payload is None:
        return None
    entry = _abi_infer_entry()
    if entry is None:
        return None
    schema = _expected_abi_schema()
    if not isinstance(schema, str) or not schema:
        return None
    data = (function or {}).get("data") if isinstance(function, dict) else None
    data = data if isinstance(data, dict) else {}
    try:
        value = entry(
            payload,
            ghidra_calling_convention=data.get("ghidra_calling_convention"),
            ghidra_parameter_count=data.get("parameter_count"),
            persisted_abi=persisted_abi if isinstance(persisted_abi, dict) else None,
            image_base=_image_base(index),
        )
    except Exception:
        # Includes the TypeError an unexpected entry-point name raises, and the
        # ValueError the engine re-raises for an input shape it does not accept.
        # One clear call, no retry: see the docstring.
        return None
    if not isinstance(value, dict) or not value:
        return None
    if value.get("schema") != schema:
        return None
    observations = []
    for source in (function, disassembly):
        # ``provenance`` is the ONLY key read off either card here. The
        # disassembly card also carries the uncompacted ``listing``, and nothing
        # below this point may copy it anywhere: the derived record is bounded by
        # ABI_DERIVED_MAX_BYTES, the observations are strings, and the pack
        # stores the *compacted* ``data``. A future edit that widened this loop
        # would put a 60 KB listing into evidence.json; this comment is the note
        # that says it must not happen.
        if isinstance(source, dict) and source.get("status") == "ok":
            provenance = source.get("provenance")
            if isinstance(provenance, str) and provenance.strip():
                observations.append(provenance)
    if not observations:
        return None
    try:
        return {"value": _stored_derived_record(value), "observations": observations}
    except Exception:
        # The projection is pure and total over a JSON-shaped record, so this
        # should be unreachable. It is here because the rule this module has
        # held since the hook landed is that no shape the collaborator hands
        # back may raise out of here: a record we cannot store is no derivation,
        # and the category falls back to what it would have been with the hook
        # deleted. Never an envelope, never an exception.
        return None


def _convention_of(abi):
    # type: (object) -> object
    """The calling convention an ABI record states, or ``None`` when silent.

    Accepts a persisted ABI dict, an ``openspore-abi-inference-1`` record (whose
    convention lives in the whitelisted ``abi`` sub-object), a bare free-text
    convention, or a list of free-text conventions. Never invents a value: a
    record that names no convention returns ``None``, which the conflict matcher
    below reads as silence rather than as disagreement.
    """
    if isinstance(abi, dict):
        nested = abi.get("abi")
        sources = [nested, abi] if isinstance(nested, dict) else [abi]
        for source in sources:
            value = source.get("calling_convention") or source.get("convention")
            if isinstance(value, str) and value.strip():
                return value
            if isinstance(value, (list, tuple)):
                items = [item for item in value if isinstance(item, str) and item.strip()]
                if items:
                    return items
        return None
    if isinstance(abi, str):
        return abi if abi.strip() else None
    if isinstance(abi, (list, tuple)):
        items = [item for item in abi if isinstance(item, str) and item.strip()]
        return items or None
    return None


def _convention_key(value):
    # type: (object) -> object
    """One convention key named by free text, or ``None``.

    Twin of ``validate._convention_key`` (``validate.py:118``): same fixed
    priority order, same four tokens, same case-folding. ``validate`` imports
    ``evidence`` at module level (``validate.py:20``), so ``evidence`` may not
    import ``validate`` without a cycle; the duplicate is the price, and the two
    must stay in step or one of them will disagree with the other about what a
    "calling convention" is.
    """
    text = str(value or "").casefold()
    for key in CONVENTION_KEYS:
        if key in text:
            return key
    return None


def _convention_keys(value):
    # type: (object) -> set
    """Every convention key a free-text value names, as a set.

    A value may be a list (``0x008db310`` persists ``["x86-32 thiscall, callee
    cleanup", "__thiscall observed"]``); each element is normalised and the keys
    are collected, so a record that names one convention twice does not look
    like a disagreement with itself.
    """
    if isinstance(value, dict):
        value = _convention_of(value)
    items = list(value) if isinstance(value, (list, tuple, set)) else [value]
    keys = set()
    for item in items:
        key = _convention_key(item)
        if key:
            keys.add(key)
    return keys


def _category(state, value, provenance, source_class="committed_artifact", evidence_level="OBSERVED", reason=None):
    if state == "available" and value in (None, {}, []):
        state = "unavailable"
    if state != "available":
        evidence_state = "MISSING"
    else:
        evidence_state = {"live": "LIVE", "derived": "DERIVED", "inferred": "INFERRED"}.get(source_class, "PERSISTED")
    return {
        "availability": state,
        "evidence_state": evidence_state,
        "evidence_level": evidence_level if state == "available" else "UNKNOWN",
        "provenance": provenance,
        "value": value if state == "available" else None,
        # "no exact source evidence found" is the right sentence for a category
        # that was looked for and came up empty. It is the wrong sentence for one
        # that was never looked for, which would report a permanent capability
        # gap as a per-target finding, so a caller may state its own reason.
        "reason": None if state == "available" else (reason or "no exact source evidence found"),
    }


def _existing_source_refs(source, root):
    result = {}
    for key in ("file", "decomp"):
        value = source.get(key)
        if isinstance(value, str) and (Path(root) / value).is_file():
            result[key] = value
    for key in ("files", "metadata", "handoffs"):
        values = source.get(key)
        if isinstance(values, list):
            result[key] = [value for value in values if isinstance(value, str) and (Path(root) / value).is_file()]
        elif isinstance(values, str) and (Path(root) / values).is_file():
            result[key] = values
    return result


def _record_categories(record, index, root):
    dependencies = record.get("dependencies", {}) or {}
    source = record.get("source", {}) or {}
    runtime = record.get("runtime", {}) or {}
    semantics = record.get("semantic") or {}
    source_refs = _existing_source_refs(source, root)
    values = {
        "function_identity": (compact(record, 6000) if record else None, [INDEX_REL]),
        "abi": (compact(record.get("abi", {}), 6000) or None, [INDEX_REL]),
        "callers_dependencies": (compact((dependencies.get("callers") or [])[:16], 6000) or [], [INDEX_REL]),
        "callees_dependencies": (compact((dependencies.get("callees") or [])[:16], 6000) or [], [INDEX_REL]),
        "external_callees": (compact((dependencies.get("external_callees") or [])[:16], 6000) or [], [INDEX_REL]),
        "types": (compact((record.get("types") or [])[:24], 6000) or [], [INDEX_REL]),
        "globals": (compact((record.get("globals") or [])[:16], 6000) or [], [INDEX_REL]),
        "vtables": (compact((record.get("vtables") or [])[:16], 6000) or [], [INDEX_REL]),
        "semantic_hypotheses": (compact(semantics, 6000) or None, ["knowledgegraph/research/semantic-decomp.json"]),
        # A reserved slot, not a search result. No original-process trace exists
        # anywhere in this repository, so this value is never computed and must
        # never be presented as one that was. ``runtime_metadata`` beside it
        # carries the real runtime information: the open gates.
        "runtime": (None, [INDEX_REL], "no original-process trace exists in this repository; this category is a reserved slot and was never searched"),
        "runtime_metadata": (compact(runtime, 5000) or None, [INDEX_REL]),
        "reconstruction": (compact(source_refs, 6000) or None, [INDEX_REL]),
        "contradictions": (compact(_target_conflicts(index, record.get("va")), 8000) or None, [INDEX_REL]),
    }
    result = {}
    for key, entry in values.items():
        value, provenance = entry[0], entry[1]
        reason = entry[2] if len(entry) > 2 else None
        state = "available" if value not in (None, {}, []) else "unavailable"
        result[key] = _category(state, value, provenance, "derived" if key in {"function_identity", "callers_dependencies", "callees_dependencies", "types", "globals", "vtables"} else "committed_artifact", "SUPPORTED", reason)
    result["status"] = _category("available" if record.get("status") else "unavailable", {"status": record.get("status"), "runtime_gated": record.get("runtime_gated"), "runtime_validated": (record.get("runtime", {}) or {}).get("validated", 0)}, [INDEX_REL], "derived", "SUPPORTED")
    return result


def collect(root=ROOT, va=None, live=False, write=True, out_dir=None):

    root = Path(root)
    if va is None:
        raise ToolError("missing_va", "a target VA is required", 2)
    try:
        va = normalize_va(va)
    except (TypeError, ValueError) as exc:
        raise ToolError("invalid_va", str(exc), 2)
    index = _index(root)
    projection = index.get("_tooling_projection", {"rebuilt": False, "source": INDEX_REL})
    record = _record(index, va)
    function = None
    decompilation = None
    disassembly = None
    live_attempts = []
    if live:
        function = _live_function(va)
        if function.get("status") != "ok":
            live_attempts.append({"kind": "function", "status": "unavailable", "mode": "LIVE", "code": function.get("code"), "message": function.get("message")})
            function = None
        decompilation = _live_decompile(va)
        if decompilation.get("status") != "ok":
            live_attempts.append({"kind": "decompilation", "status": "unavailable", "mode": "LIVE", "code": decompilation.get("code"), "message": decompilation.get("message")})
            decompilation = None
        disassembly = _live_disassembly(va)
        if disassembly.get("status") != "ok":
            live_attempts.append({"kind": "disassembly", "status": "unavailable", "mode": "LIVE", "code": disassembly.get("code"), "message": disassembly.get("message")})
            disassembly = None
    if function is None:
        function = _snapshot_function(root, va)
    if decompilation is None and function and function.get("data"):
        for key in DECOMPILATION_KEYS:
            text = function["data"].get(key)
            if isinstance(text, str) and text.strip():
                decompilation = {"status": "ok", "mode": function.get("mode", "snapshot"), "provenance": function["provenance"], "text": str(text)}
                break
    categories = _record_categories(record, index, root)
    if function and function.get("status") == "ok":
        categories["ghidra_function"] = _category("available", compact(function.get("data"), 12000), [function.get("provenance")], "live" if function.get("mode") == "live" else "committed_artifact", "OBSERVED" if function.get("mode") == "live" else "SUPPORTED")
    else:
        categories["ghidra_function"] = _category("unavailable", None, [], "unavailable", "UNKNOWN")
    if decompilation and decompilation.get("status") == "ok":
        categories["decompilation"] = _category("available", compact(decompilation.get("text"), 12000), [decompilation.get("provenance")], "live" if decompilation.get("mode") == "live" else "committed_artifact", "INFERRED")
    else:
        categories["decompilation"] = _category("unavailable", None, [], "unavailable", "UNKNOWN")
    if disassembly and disassembly.get("status") == "ok":
        # ``data``, never ``listing``: the category is the stored evidence and
        # keeps the 12000-byte budget, so this value -- and therefore the pack's
        # ``content_sha256`` -- is unaffected by the uncompacted copy the
        # derivation reads.
        categories["disassembly"] = _category("available", disassembly.get("data"), [disassembly.get("provenance")], "live", "OBSERVED")
    else:
        categories["disassembly"] = _category("unavailable", None, [], "unavailable", "UNKNOWN")
    # Derived ABI, evaluated after the observations exist and before the
    # provenance list is assembled so the derivation can cite its own source.
    derived = _derived_abi(va, function, disassembly, record.get("abi"), index)
    derived_filled = False
    if derived and categories.get("abi", {}).get("availability") == "unavailable":
        # Persisted ABI always wins: the ~263 records that carry one are the
        # canonical projection and must stay bit-identical. A derived record is
        # only ever a *first* observation, and is labelled DERIVED/INFERRED
        # because that is exactly what it is -- computed over an observation,
        # never observed itself.
        categories["abi"] = _category("available", derived["value"],
                                      [INDEX_REL] + derived["observations"],
                                      "derived", "INFERRED")
        derived_filled = True
    provenance = [
        {"ref": projection.get("source", INDEX_REL), "mode": "derived" if projection.get("rebuilt") else "persisted", "source_class": "generated_index"},
        {"ref": "knowledgegraph/triage/queue-f0e310e0-v6.json", "mode": "persisted", "source_class": "committed_artifact"},
        {"ref": "knowledgegraph/research/source-reconstruction-manifest.json", "mode": "persisted", "source_class": "committed_artifact"},
    ]
    for key, value in _existing_source_refs(record.get("source", {}) or {}, root).items():
        values = value if isinstance(value, list) else [value]
        for source_path in values:
            provenance.append({"ref": source_path, "mode": "persisted", "source_class": "committed_artifact"})
    if function and function.get("status") == "ok":
        provenance.append({"ref": function.get("provenance"), "mode": function.get("mode", "persisted"), "source_class": "ghidra"})
    if decompilation and decompilation.get("status") == "ok":
        provenance.append({"ref": decompilation.get("provenance"), "mode": decompilation.get("mode", "persisted"), "source_class": "ghidra"})
    if disassembly and disassembly.get("status") == "ok":
        provenance.append({"ref": disassembly.get("provenance"), "mode": "live", "source_class": "ghidra"})
    if derived:
        # Cited even when the persisted record won the category: the derived
        # value is still what the conflict check below compared against, so it
        # has to be traceable in the pack rather than invisible.
        provenance.append({"ref": ABI_INFER_REL, "mode": "derived", "source_class": "derived"})
        if derived_filled:
            for ref in derived["observations"]:
                provenance.append({"ref": ref, "mode": "derived", "source_class": "derived"})
    provenance = [item for item in provenance if item.get("ref")]
    provenance = list({(item["ref"], item["mode"]): item for item in provenance}.values())
    provenance.sort(key=lambda item: (item["mode"], item["ref"]))
    conflicts = _target_conflicts(index, va)
    # A Ghidra signature almost never spells a convention name, and Ghidra
    # reports `unknown` for 99.89% of this binary, so a *missing* convention on
    # either side is silence, not disagreement. Only two positive, normalised,
    # and disjoint claims conflict. See `_convention_keys`.
    if function and decompilation and record.get("abi"):
        signature = (function.get("data") or {}).get("signature")
        live_keys = _convention_keys(signature)
        persisted_keys = _convention_keys(record["abi"])
        if live_keys and persisted_keys and not (live_keys & persisted_keys):
            conflicts.append({"kind": "live_vs_persisted", "field": "signature/abi", "live": bounded(signature), "persisted": bounded(record["abi"]), "resolution_status": "unresolved"})
    # Sibling of the check above, not a replacement: that one needs a
    # decompilation, so a disassembly-derived ABI would otherwise get no conflict
    # checking at all. This one compares only the derived convention against the
    # persisted one, and only when a persisted convention exists -- for an empty
    # ``record["abi"]`` the derived value is a first observation, not a
    # disagreement, and synthesising a conflict out of it would invent one.
    # Same normaliser, same silence-is-not-disagreement policy, so the two
    # blocks can never accuse each other of the same pair disagreeing in one and
    # agreeing in the other.
    derived_convention = _convention_of((derived or {}).get("value"))
    persisted_convention = _convention_of(record.get("abi"))
    derived_keys = _convention_keys(derived_convention)
    persisted_keys = _convention_keys(persisted_convention)
    if derived and derived_keys and persisted_keys and not (derived_keys & persisted_keys):
        conflicts.append({"kind": "derived_vs_persisted", "field": "calling_convention", "derived": bounded(derived_convention), "persisted": bounded(persisted_convention), "resolution_status": "unresolved"})
    has_live = any(item and item.get("status") == "ok" and item.get("mode") == "live" for item in (function, decompilation, disassembly))
    state = "LIVE" if live and has_live else "PERSISTED"
    pack = {
        "schema": "openspore-evidence-pack-1",
        "target": {"va": va, "address_kind": "linked_va"},
        "collector": {"source_policy": "live_with_persisted_fallback" if live else "persisted", "live_requested": bool(live), "live_attempts": live_attempts, "projection": projection},
        "binary": compact(index.get("binary", {}), 6000),
        "evidence_state": state,
        "record": _record_view(record),
        "categories": categories,
        "provenance": provenance,
        "conflicts": compact(conflicts, 8000),
        "content_sha256": None,
    }
    pack["content_sha256"] = sha256_json(pack)
    destination = Path(out_dir) if out_dir else Path(root) / EVIDENCE_REL / va[2:]
    if write:
        write_json_atomic(destination / "evidence.json", pack)
        write_text_atomic(destination / "evidence.md", render_evidence_markdown(pack))
    pack["paths"] = {"directory": str(destination), "written": bool(write), "evidence_json": str(destination / "evidence.json") if write else None, "evidence_md": str(destination / "evidence.md") if write else None}
    return pack


def render_evidence_markdown(pack):
    target = pack["target"]["va"]
    lines = ["# Evidence %s" % target, "", "- Evidence state: `%s`" % pack["evidence_state"], "- Live requested: `%s`" % pack["collector"]["live_requested"], "- Content SHA-256: `%s`" % pack["content_sha256"], ""]
    for name, category in sorted(pack["categories"].items()):
        lines.extend(["## %s" % name, "", "- Availability: `%s`" % category.get("availability"), "- Evidence state: `%s`" % category.get("evidence_state"), "- Provenance: `%s`" % ", ".join(str(item) for item in category.get("provenance", []) or []), ""])
        if category.get("value") not in (None, {}, []):
            lines.append("```json")
            value = json.dumps(category["value"], indent=2, sort_keys=True, ensure_ascii=False)
            lines.append(value if len(value) <= 6000 else value[:6000] + "\n[TRUNCATED]")
            lines.extend(["```", ""])
    conflict_text = json.dumps(pack.get("conflicts", []), indent=2, sort_keys=True, ensure_ascii=False)
    lines.extend(["## Conflicts", "", "```json", conflict_text if len(conflict_text) <= 5000 else conflict_text[:5000] + "\n[TRUNCATED]", "```", ""])
    return "\n".join(lines)
