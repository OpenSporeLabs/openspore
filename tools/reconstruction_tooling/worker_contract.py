"""The reconstruction worker contract: what a worker receives, what it returns.

Two halves, both machine-readable, both deterministic:

``briefing(va, ...)``
    A compact target package. It reuses the evidence pack and context brief
    that already exist rather than re-deriving them, and adds the planning
    facts a worker needs but the context brief does not carry: the frontier
    reason, the dependency edges, the SCC membership, and the validation
    requirements as machine data.

``parse_result(raw, ...)``
    A strict parser for the worker's reply. It is deliberately unforgiving:
    an unparseable or unidentifiable result is a *typed* failure the
    orchestrator can route on, never a best-effort guess. The target VA is
    taken from the orchestrator's own claim record, never from the payload, so
    a confused worker cannot be recorded against the wrong function.

    Two layers, and the split is the whole safety argument:

    ``unwrap_reply(raw)``
        Turns whatever the worker wrote on stdout into *text plus provenance*,
        without deciding what the text means. It knows three channels: a bare
        JSON document (a plain subprocess worker), an OpenCode event stream
        (newline-delimited events), and plain prose.

    ``extract_result_document(text, blocks)``
        Locates exactly one candidate result inside that text, or refuses.
        Strictest signal first -- an explicit fence, then the final assistant
        text block, then the whole reply -- and at every step *ambiguity is a
        failure*, never a pick.

The outcome vocabulary is explicit about the difference between "I did it" and
"I could not": ``STILL_UNKNOWN`` is a legitimate, non-failing answer, and the
briefing tells the worker that reporting it is correct behaviour rather than a
failure to be papered over.
"""

import json
import re

from .models import ROOT, ToolError, compact, normalize_va, sha256_json

BRIEFING_SCHEMA = "openspore-worker-briefing-1"
RESULT_SCHEMA = "openspore-worker-result-1"

# Outcome vocabulary. Ordered by how far the orchestrator may advance the
# target: a worker may only ever reach IMPLEMENTED, and only on a validator
# PASS (see orchestrate.reconcile).
OUTCOMES = (
    "IMPLEMENTED",          # candidate source exists and was produced
    "PARTIAL",              # some claims modelled, material uncertainty remains
    "STRUCTURAL_ONLY",      # signature/layout/ABI only; no body semantics claimed
    "STILL_UNKNOWN",        # evidence does not support any semantic claim
    "BLOCKED",              # worker cannot proceed (needs a gate or an answer)
    "FAILED_VALIDATION",    # worker ran, candidate rejected by the validator
)
TERMINAL_OUTCOMES = ("IMPLEMENTED", "PARTIAL", "STRUCTURAL_ONLY")
# Outcomes that mean the worker did not produce a reviewable candidate. None of
# them is a reason to close the row; all of them cost an attempt.
UNSATISFIED_OUTCOMES = ("STILL_UNKNOWN", "BLOCKED", "FAILED_VALIDATION")

VALIDATION_VERDICTS = ("PASS", "WARN", "FAIL", "UNKNOWN", "NOT_AVAILABLE")

# --------------------------------------------------------------------------- #
# reply channels
# --------------------------------------------------------------------------- #
# The three shapes a worker's stdout is allowed to take. Named so a failure
# report says which one arrived, which is the difference between "the worker
# wrote prose" and "the worker wrote a malformed event stream".
CHANNEL_JSON_DOCUMENT = "json_document"   # one bare JSON object, nothing else
CHANNEL_EVENT_STREAM = "event_stream"     # newline-delimited OpenCode events
CHANNEL_TEXT = "text"                     # prose, with or without a result

# Fence info strings that mark a block as *the* result. The briefing asks for
# one, because it is the cheapest thing a worker can do to make its answer
# unambiguous -- but the parser does not use a fence to break a tie. A fence
# decides nothing on its own; it only labels where an already-unique result was
# found. ``json`` is included because it is what models actually reach for.
RESULT_FENCE_MARKERS = ("json", "worker-result", "openspore-worker-result",
                        "openspore-worker-result-1", "result")
_FENCE = re.compile(r"^[ \t]*`{3,}[ \t]*([A-Za-z0-9_.+-]*)[ \t]*$", re.MULTILINE)
_FENCE_CLOSE = re.compile(r"^[ \t]*`{3,}[ \t]*$", re.MULTILINE)

# Keys that make a JSON object *claim* to be a worker result. This is the
# ambiguity set, and it is deliberately loose: an object carrying a wrong
# ``schema`` is still a result claim and must be rejected by the schema check
# with a useful reason, not silently skipped as "some other JSON". Anything not
# in this set is a code sample, a log line, or a nested field, and is ignored.
_CLAIM_KEYS = ("schema", "outcome", "va")


def _claims_result(document):
    # type: (object) -> bool
    return isinstance(document, dict) and any(key in document
                                               for key in _CLAIM_KEYS)


def _balanced_spans(text):
    # type: (str) -> list
    """Every balanced ``{...}`` span in ``text``, outermost first, in order.

    Braces inside JSON string literals must not open or close a span, so the
    scanner tracks quoting and escapes rather than counting delimiters.

    Nested spans are returned too, not just the outermost. That is what lets
    ``_candidates`` count a result-shaped object a worker buried inside a
    wrapper as a *second* candidate: a reply holding a quoted example plus a
    real answer must come out ambiguous, and a scanner that only reported
    outermost spans would silently pick one of the two.
    """
    spans = []
    starts = []
    in_string = False
    escaped = False
    for index, char in enumerate(text):
        if in_string:
            if escaped:
                escaped = False
            elif char == "\\":
                escaped = True
            elif char == '"':
                in_string = False
            continue
        if char == '"':
            in_string = True
        elif char == "{":
            starts.append(index)
        elif char == "}" and starts:
            spans.append((starts.pop(), index + 1))
    # Outermost first, so a caller that cares about order sees the container
    # before the thing it contains.
    spans.sort(key=lambda span: (span[0], -span[1]))
    return spans


def _candidates(text):
    # type: (str) -> list
    """Result-claiming JSON objects in ``text``, in order of appearance.

    A span that does not parse is skipped rather than reported: a truncated or
    garbled object is a *missing* result, and the two failures are
    distinguishable by the caller from the surviving count.

    ``nested`` records that the object sits inside another balanced span. It
    does not change the accept/reject decision -- a single result is a single
    result wherever it sits -- but it is carried into the parse report so a
    nested payload (a quoted template, an example) is visible in the evidence
    instead of silently indistinguishable from a top-level answer.
    """
    spans = _balanced_spans(text)
    found = []
    for start, end in spans:
        try:
            document = json.loads(text[start:end])
        except ValueError:
            continue
        if not _claims_result(document):
            continue
        nested = any(other_start < start and end < other_end
                     for other_start, other_end in spans)
        found.append({"document": document, "offset": start, "end": end,
                      "nested": nested})
    return found


def _fenced_spans(text):
    # type: (str) -> list
    """``(marker, body_start, body_end)`` for every result-marker fence.

    Offsets, not bodies: the stage locator needs to know whether a given
    candidate sits *inside* a marked fence rather than merely somewhere in the
    reply.
    """
    spans = []
    for match in _FENCE.finditer(text):
        marker = (match.group(1) or "").strip().lower()
        if marker not in RESULT_FENCE_MARKERS:
            continue
        body_start = match.end()
        close = _FENCE_CLOSE.search(text, body_start)
        if close is None:
            continue
        spans.append((marker, body_start, close.start()))
    return spans


def _block_offsets(text, blocks):
    # type: (str, object) -> list
    """Locate each assistant text block inside the joined reply text.

    The event-stream channel joins its blocks with newlines to make ``text``,
    so a block's position can be recovered by walking the same join. Blocks that
    cannot be located are dropped rather than guessed at.
    """
    located = []
    cursor = 0
    for block in (blocks or []):
        if not isinstance(block, str) or not block:
            continue
        found = text.find(block, cursor)
        if found == -1:
            continue
        located.append((found, found + len(block)))
        cursor = found + len(block)
    return located


def _locate_stage(text, blocks, candidate):
    # type: (str, object, dict) -> str
    """Describe *how* the single accepted result was found. Provenance only.

    This never influences the decision -- it exists so the parse report says
    where in a real reply the answer came from, which is what makes a change in
    the worker's output format visible in the evidence instead of silently
    altering which text is read.
    """
    start, end = candidate["offset"], candidate["end"]
    for marker, body_start, body_end in _fenced_spans(text):
        if body_start <= start and end <= body_end:
            return "fenced_result:%s" % marker
    located = _block_offsets(text, blocks)
    if len(located) > 1:
        for index, (block_start, block_end) in enumerate(located):
            if block_start <= start and end <= block_end:
                return ("final_text_block" if index == len(located) - 1
                        else "earlier_text_block")
    return "whole_reply"


def unwrap_reply(raw, max_bytes=4 * 1024 * 1024):
    # type: (object, int) -> dict
    """Classify a worker's stdout into text plus provenance.

    Returns ``{"text", "channel", "blocks", "tool_calls", "document",
    "oversized", "bytes"}``. ``blocks`` is the ordered list of assistant text
    blocks when the channel exposes them, because "which block is the answer"
    is only answerable if the blocks are kept separate. Never raises.
    """
    if raw is None:
        return {"text": "", "channel": CHANNEL_TEXT, "blocks": [],
                "tool_calls": 0, "document": None, "oversized": False,
                "bytes": 0, "empty": True}
    if isinstance(raw, (bytes, bytearray)):
        text = bytes(raw).decode("utf-8", errors="replace")
    else:
        text = str(raw)
    size = len(text.encode("utf-8"))
    if size > max_bytes:
        return {"text": "", "channel": CHANNEL_TEXT, "blocks": [],
                "tool_calls": 0, "document": None, "oversized": True,
                "bytes": size, "empty": True}
    stripped = text.strip()
    if not stripped:
        return {"text": "", "channel": CHANNEL_TEXT, "blocks": [],
                "tool_calls": 0, "document": None, "oversized": False,
                "bytes": size, "empty": True}

    # Channel 1: the whole reply is one JSON object. This is the contract a
    # plain subprocess worker (tests/fixtures/fake_worker.py) speaks, and it
    # stays first so that channel is never perturbed by the heuristics below.
    try:
        document = json.loads(stripped)
    except ValueError:
        document = None
    if isinstance(document, dict):
        return {"text": text, "channel": CHANNEL_JSON_DOCUMENT, "blocks": [text],
                "tool_calls": 0, "document": document, "oversized": False,
                "bytes": size, "empty": False}
    if isinstance(document, list):
        return {"text": text, "channel": CHANNEL_JSON_DOCUMENT, "blocks": [text],
                "tool_calls": 0, "document": None, "oversized": False,
                "bytes": size, "empty": False}

    # Channel 2: an OpenCode event stream. Recognised structurally -- every
    # non-blank line is a JSON object carrying a string ``type`` and a ``part``
    # -- never by a format guess, so ordinary prose that happens to contain
    # one JSON object cannot be mistaken for an event stream.
    blocks = []
    tool_calls = 0
    events = 0
    stream = True
    for line in stripped.splitlines():
        line = line.strip()
        if not line:
            continue
        try:
            event = json.loads(line)
        except ValueError:
            stream = False
            break
        if not isinstance(event, dict) or not isinstance(event.get("type"), str) \
                or "part" not in event:
            stream = False
            break
        events += 1
        part = event.get("part")
        if event.get("type") == "tool_use" or (isinstance(part, dict)
                                               and part.get("type") == "tool"):
            tool_calls += 1
        if event.get("type") == "text" and isinstance(part, dict) \
                and isinstance(part.get("text"), str):
            blocks.append(part["text"])
    if stream and events:
        return {"text": "\n".join(blocks) if blocks else "",
                "channel": CHANNEL_EVENT_STREAM, "blocks": blocks,
                "tool_calls": tool_calls, "document": None,
                "oversized": False, "bytes": size, "empty": not blocks,
                "events": events}

    # Channel 3: prose.
    return {"text": text, "channel": CHANNEL_TEXT, "blocks": [text],
            "tool_calls": 0, "document": None, "oversized": False,
            "bytes": size, "empty": False}


def extract_result_document(text, blocks=None):
    # type: (str, object) -> dict
    """Find the one worker result in ``text``, or explain why there isn't one.

    One decision rule, and it is deliberately the strictest one available:
    **exactly one object in the whole reply may claim to be a worker result.**

    Two claims is an unconditional refusal. It is not resolved by preferring a
    fence, by preferring the last text block, by preferring the object whose VA
    matches, or by preferring the one that validates -- because each of those is
    a guess, and a guess here is how a worker gets recorded against the wrong
    function or how a quoted template gets recorded as the worker's answer. The
    asymmetry decides it: a false accept is unrecoverable, while a false reject
    is a counted, bounded retry the worker can fix by obeying the contract it
    was handed.

    Nesting does not hide a claim. A result buried inside a wrapper is still a
    claim, so a reply carrying a quoted example *and* a real answer is
    ambiguous rather than quietly resolved in favour of whichever one the
    scanner happened to reach first.

    Where the single accepted result was found -- a result-marker fence, the
    final assistant text block, or anywhere in the reply -- is recorded as
    ``stage`` for provenance, and never used to break a tie.
    """
    text = text or ""
    if not text.strip():
        return {"found": False, "ambiguous": False, "document": None,
                "candidates": 0, "stage": "empty",
                "reason": "no text to search for a result document"}

    found = _candidates(text)
    if len(found) == 1:
        return {"found": True, "ambiguous": False,
                "document": found[0]["document"], "candidates": 1,
                "stage": _locate_stage(text, blocks, found[0]),
                "nested": bool(found[0].get("nested"))}
    if len(found) > 1:
        return {"found": False, "ambiguous": True, "document": None,
                "candidates": len(found), "stage": "ambiguous",
                "reason": "%d objects claim to be a worker result; refusing to "
                          "choose between them" % len(found)}
    return {"found": False, "ambiguous": False, "document": None,
            "candidates": 0, "stage": "no_result",
            "reason": "no object claiming to be a worker result was found"}

# Sections the worker is expected to fill in its result. Kept in one place so
# the briefing, the result schema, and the docs cannot drift.
REQUIRED_RESULT_FIELDS = (
    "schema", "va", "outcome", "summary", "source_files", "observed_mechanics",
    "unresolved_questions", "evidence_refs",
)
OPTIONAL_RESULT_FIELDS = (
    "normalized_symbol", "reconstructed_symbol", "package", "subsystem",
    "types", "observed_original_abi", "layout", "globals", "vtables", "services",
    "state_events", "semantic_findings", "confidence", "runtime_gates",
    "blockers", "validation", "attempts_used", "notes",
)

# The rules a worker must follow. Shipped in the briefing so a stateless
# subagent gets them without the orchestrator re-explaining anything.
WORKER_RULES = (
    "Evidence only. Never invent a constant, offset, vtable slot, or name.",
    "If the evidence does not support a claim, report STILL_UNKNOWN; that is a "
    "correct answer, not a failure.",
    "Do not commit, do not modify tools/mcp/**, and never touch another "
    "worker's staging package or metadata record.",
    "x86-32 only. The reconstructed symbol must embed the 8-hex target VA so "
    "the validator can locate the span.",
    "Write candidate source under reconstruction/staging/<your-package>/; the "
    "integrator promotes it to src/ after review.",
    "Emit exactly one JSON document matching openspore-worker-result-1. Put it "
    "in a single fenced block tagged json -- a line containing ```json, then "
    "exactly one JSON object, then a line containing ```. Narrating, tool use "
    "and prose are all fine before the fence; the fence is what marks which "
    "payload is the result, and it is what the parser reads.",
    "Emit that result object exactly once. If you want to give a second "
    "answer you have two answers, not one: keep the supported one in the "
    "result and move the other into unresolved_questions. Two result objects "
    "are rejected as ambiguous, never merged and never picked between.",
    "You have a bounded turn budget and it is not generous. Emit the result "
    "block as soon as you have a defensible answer, and treat a run that is "
    "going long as a reason to stop investigating and report rather than to "
    "keep digging. A run that ends with no result object is discarded and "
    "retried from scratch, so an unfinished investigation is worth nothing; a "
    "PARTIAL result that names its open questions is worth everything.",
    "If you are out of budget, or the evidence will not settle a question, the "
    "correct move is a result with outcome STILL_UNKNOWN and the open "
    "questions filled in. That is a successful run, not a failure.",
)


def _section_data(context, key):
    # type: (dict, str) -> object
    sections = (context or {}).get("sections") or {}
    section = sections.get(key) or {}
    return section.get("data")


def _section_state(context, key):
    # type: (dict, str) -> str
    sections = (context or {}).get("sections") or {}
    return ((sections.get(key) or {}).get("state")) or "missing"


def _missing(required, satisfied, reason):
    # type: (list, list, object) -> list
    absent = [item for item in required if item not in satisfied]
    if absent and reason:
        absent.append(reason)
    return absent


def briefing(va, root=ROOT, target=None, evidence=None, context=None,
             validation=None, implementer_id=None, inv_id=None, binary_sha256=None,
             scc=None, attempt=1, max_attempts=3, workers=(), previous=None):
    # type: (...) -> dict
    """Assemble the compact target package a worker is handed.

    ``target`` is a swarm target dict (as emitted by ``openspore swarm``);
    ``evidence``/``context``/``validation`` are the already-collected tool
    outputs, so the briefing never rebuilds them. Everything is bounded through
    the same ``compact`` helper the evidence pack uses, so a 6MB decompilation
    cannot swamp the prompt.
    """
    try:
        va = normalize_va(va)
    except (TypeError, ValueError) as exc:
        raise ToolError("invalid_va", str(exc), 2)
    target = target or {}
    evidence = evidence or {}
    context = context or {}
    validation = validation or {}
    categories = evidence.get("categories", {}) or {}
    record = _section_data(context, "02_function_identity") or {}
    status = _section_data(context, "03_current_status") or {}
    abi = _section_data(context, "06_abi") or {}
    calls = _section_data(context, "07_callers_callees") or {}
    types_fields = _section_data(context, "08_types_fields_globals") or {}
    state_events = _section_data(context, "09_state_event_relationships") or {}
    dependencies = _section_data(context, "10_dependencies") or {}
    analogues = _section_data(context, "11_related_functions") or []
    existing = _section_data(context, "12_existing_reconstruction") or {}
    semantics = _section_data(context, "13_semantic_hypotheses") or {}
    conflicts = _section_data(context, "14_conflicts_questions") or {}
    provenance = _section_data(context, "15_validation_and_provenance") or {}
    required_categories = list(provenance.get("required_categories") or [])

    decompilation = categories.get("decompilation") or {}
    disassembly = categories.get("disassembly") or {}
    ghidra_function = categories.get("ghidra_function") or {}
    evidence_refs = sorted({
        str(item)
        for item in (evidence.get("provenance") or [])
        if isinstance(item, str)
    } | {
        str(item.get("ref"))
        for item in (evidence.get("provenance") or [])
        if isinstance(item, dict) and item.get("ref")
    })

    absent = _missing(
        ["DECOMPILATION", "DISASSEMBLY"],
        [name for name, category in (("DECOMPILATION", decompilation),
                                     ("DISASSEMBLY", disassembly))
         if category.get("availability") == "available"],
        None if decompilation.get("availability") == "available"
        else "no persisted or live decompilation for this target",
    )
    absent += _missing(
        ["ABI"], ["ABI"] if abi else [],
        None if abi else "no ABI projection; derive it from the disassembly "
                        "and say so in unresolved_questions",
    )

    package = {
        "schema": BRIEFING_SCHEMA,
        "target": {
            "va": va,
            "queue_va": va[2:],
            "queue_id": inv_id or target.get("queue_id"),
            "name": record.get("name") or target.get("name"),
            "package": target.get("package"),
            "subsystem": record.get("subsystem") or target.get("subsystem"),
            "cluster": target.get("cluster"),
            "category": target.get("category"),
            "evidence_level": target.get("evidence_level"),
        },
        "lease": {
            "implementer_id": implementer_id,
            "binary_sha256": binary_sha256 or target.get("binary_sha256"),
            "attempt": int(attempt),
            "max_attempts": int(max_attempts),
            "heartbeat_every_seconds": 600,
        },
        "objective": (
            "Recover bounded x86-32 source semantics for %s (%s). Claim only "
            "what the evidence supports and report the rest."
            % (va, record.get("name") or target.get("name") or "unresolved symbol")
        ),
        "current_status": compact(status, 2000),
        "frontier_reason": {
            # A target may arrive as a raw swarm entry (``priority``/
            # ``reason_codes``) or as a classified plan record (``score``/
            # ``reason``). Read both so the section is never blank.
            "score": target.get("priority", target.get("score")),
            "role": target.get("role"),
            "role_reason": target.get("reason"),
            "score_components": compact(target.get("score_components") or {}, 2000),
            "reason_codes": list(target.get("reason_codes")
                                 or ([target["reason"]] if target.get("reason") else [])),
            "claim_state": target.get("claim_state"),
            "runtime_gated": bool(target.get("runtime_gated")),
            "evidence_ready": bool(target.get("evidence_ready")),
            "dispatchable": target.get("dispatchable"),
        },
        "decompilation": compact(decompilation.get("value"), 12000),
        "disassembly": compact(disassembly.get("value"), 8000),
        "ghidra_function": compact(ghidra_function.get("value"), 6000),
        "callers": compact(calls.get("callers") or [], 4000),
        "callees": compact(calls.get("callees") or [], 4000),
        "xrefs": compact(calls.get("edge_rows") or [], 6000),
        "abi": compact(abi, 4000),
        "types": compact(types_fields.get("types") or [], 3000),
        "fields_offsets": compact((types_fields.get("types") or []) if types_fields else [], 3000),
        "globals": compact(types_fields.get("globals") or [], 3000),
        "vtables": compact(types_fields.get("vtables") or [], 3000),
        "services": compact((_section_data(context, "08_types_fields_globals") or {}).get("services") or [], 3000),
        "state_event_links": compact(state_events, 4000),
        "semantic_findings": compact(semantics, 4000),
        "contradictions": compact(conflicts.get("conflicts") or [], 5000),
        "analogues": compact(analogues, 4000),
        "dependencies": {
            "open_dependencies": list(target.get("dependencies") or []),
            "scc": compact(scc or {"id": None, "size": 1, "members": [va]}, 2000),
            "callers": compact(calls.get("callers") or [], 3000),
            "callees": compact(calls.get("callees") or [], 3000),
            "external_callees": compact(dependencies.get("external_callees") or [], 2000),
            "truncated": {
                "callers": bool(dependencies.get("callers_truncated")),
                "callees": bool(dependencies.get("callees_truncated")),
                "edges": bool(dependencies.get("edges_truncated")),
            },
        },
        "existing_reconstruction": compact(existing, 4000),
        "reconstruction_constraints": {
            "architecture": "x86-32",
            "symbol_must_embed_va": va[2:],
            "write_under": "reconstruction/staging/<package>/",
            "promotion": "src/ is integrator-owned; do not edit it",
            "metadata_sidecar": "reconstruction/metadata/<package>/%s.json" % va[2:],
            "rules": list(WORKER_RULES),
            "outcomes": list(OUTCOMES),
        },
        "validation_requirements": {
            "required_categories": required_categories,
            "baseline_status": validation.get("status"),
            "baseline_checks": sorted((validation.get("checks") or {}).keys()),
            "gate": ("the orchestrator runs `openspore validate` on your "
                     "candidate; only a PASS may complete the target"),
        },
        "evidence": {
            "state": evidence.get("evidence_state"),
            "content_sha256": evidence.get("content_sha256"),
            "context_content_sha256": context.get("content_sha256"),
            "refs": evidence_refs,
            "missing_sections": absent,
        },
        "rules": list(WORKER_RULES),
        "result_contract": {
            "schema": RESULT_SCHEMA,
            "required": list(REQUIRED_RESULT_FIELDS),
            "optional": list(OPTIONAL_RESULT_FIELDS),
            "outcomes": list(OUTCOMES),
            "verdicts": list(VALIDATION_VERDICTS),
            "fence": "```json ... ```",
            "fence_markers": list(RESULT_FENCE_MARKERS),
            "note": ("Emit exactly one result object inside a ```json fence. "
                     "Prose, narration and tool output before the fence are "
                     "ignored. Two result objects are refused as ambiguous "
                     "rather than resolved, and a reply with no result object "
                     "is malformed -- a natural-language final message alone is "
                     "not a result."),
        },
    }
    if workers:
        package["scc"]["co_workers"] = sorted(
            str(item) for item in workers if str(item) != va)
    if previous:
        package["retry"] = {
            "attempt": int(attempt),
            "previous_outcome": previous.get("outcome"),
            "previous_summary": previous.get("summary"),
            "validator_findings": compact(
                (previous.get("validation") or {}).get("checks") or {}, 4000),
            "instruction": ("The previous attempt was not accepted. Address the "
                            "validator findings above; if the evidence genuinely "
                            "cannot support the claim, return STILL_UNKNOWN."),
        }
    package["content_sha256"] = sha256_json(package)
    return package


def render_briefing_markdown(package):
    # type: (dict) -> str
    """Human-readable rendering of the same package (never the only channel)."""
    target = package.get("target", {})
    lines = [
        "# Worker briefing %s" % target.get("va"),
        "",
        "- Queue id: `%s`" % (target.get("queue_id") or "(no row yet)"),
        "- Name: %s" % (target.get("name") or "(unresolved)"),
        "- Subsystem/cluster: %s / %s" % (target.get("subsystem"), target.get("cluster")),
        "- Evidence level: %s" % target.get("evidence_level"),
        "- Attempt %s of %s" % (package["lease"]["attempt"], package["lease"]["max_attempts"]),
        "- Briefing SHA-256: `%s`" % package.get("content_sha256"),
        "",
        "## Objective", "", package.get("objective", ""), "",
        "## Rules", "",
    ]
    lines.extend("- %s" % rule for rule in package.get("rules", []))
    lines.extend(["", "## Missing evidence", ""])
    missing = (package.get("evidence") or {}).get("missing_sections") or []
    lines.extend(["- %s" % item for item in missing] or ["- none"])
    lines.extend(["", "## Outcome vocabulary", ""])
    lines.extend("- `%s`" % item for item in package.get("result_contract", {}).get("outcomes", []))
    return "\n".join(lines)


def _fail(reason, **extra):
    # type: (str, object) -> dict
    result = {"accepted": False, "code": "malformed_worker_output",
              "reason": reason}
    result.update(extra)
    return result


def parse_result(raw, va=None, inv_id=None, max_bytes=4 * 1024 * 1024):
    # type: (object, object, object, int) -> dict
    """Parse and validate a worker reply.

    Returns ``{"accepted": bool, ...}``. Never raises for a bad payload: the
    orchestrator routes on the failure, and an unparseable reply is a normal,
    countable outcome rather than an exception that loses the claim.

    Strictness is unchanged, only *reach* is. Extraction decides which object
    is the result; every check below is the same check the single-document
    path always ran, so a reply that reaches them with prose wrapped around it
    is validated exactly as strictly as a bare one. Widening what can be
    located never widens what is acceptable.
    """
    import hashlib

    if raw is None:
        return _fail("worker produced no output")
    if isinstance(raw, (bytes, bytearray)):
        text = bytes(raw).decode("utf-8", errors="replace")
    else:
        text = str(raw)
    digest = hashlib.sha256(text.encode("utf-8")).hexdigest()
    envelope = unwrap_reply(text, max_bytes=max_bytes)
    if envelope.get("oversized"):
        return _fail("worker result exceeds the size bound", raw_sha256=digest,
                     raw_bytes=envelope["bytes"])
    if envelope.get("empty"):
        return _fail("worker produced empty output", raw_sha256=digest,
                     raw_sha256_present=True)
    provenance = {"channel": envelope["channel"],
                  "text_blocks": len(envelope.get("blocks") or []),
                  "tool_calls": envelope.get("tool_calls", 0)}

    document = envelope.get("document")
    extraction = {"stage": "json_document", "candidates": 1, "nested": False}
    if document is None:
        extraction = extract_result_document(envelope.get("text", ""),
                                             envelope.get("blocks"))
        document = extraction.get("document")
    if document is None:
        if extraction.get("ambiguous"):
            return _fail("ambiguous worker output: %s"
                         % extraction.get("reason"),
                         raw_sha256=digest, extraction_stage=extraction["stage"],
                         candidates=extraction.get("candidates", 0), **provenance)
        return _fail("no worker result document found: %s"
                     % extraction.get("reason"),
                     raw_sha256=digest, extraction_stage=extraction.get("stage"),
                     candidates=extraction.get("candidates", 0), **provenance)
    provenance["extraction_stage"] = extraction.get("stage")
    provenance["nested_result"] = bool(extraction.get("nested"))
    if not isinstance(document, dict):
        return _fail("worker result must be a JSON object, got %s"
                     % type(document).__name__, raw_sha256=digest)

    missing = [field for field in REQUIRED_RESULT_FIELDS if field not in document]
    if missing:
        return _fail("worker result is missing required field(s): %s"
                     % ", ".join(missing), raw_sha256=digest,
                     missing=missing)
    if document.get("schema") != RESULT_SCHEMA:
        return _fail("worker result schema must be %r, got %r"
                     % (RESULT_SCHEMA, document.get("schema")),
                     raw_sha256=digest)
    outcome = document.get("outcome")
    if outcome not in OUTCOMES:
        return _fail("unknown outcome %r; expected one of: %s"
                     % (outcome, ", ".join(OUTCOMES)), raw_sha256=digest,
                     outcome=outcome)

    reported = document.get("va")
    try:
        reported = normalize_va(reported) if reported is not None else None
    except (TypeError, ValueError):
        return _fail("worker result 'va' is not a valid address: %r" % reported,
                     raw_sha256=digest, va=reported)
    if reported is not None and va is not None and reported != normalize_va(va):
        # A worker that answers for a different function is not recoverable by
        # guessing; refuse rather than misattribute the artifacts.
        return _fail("worker result va %s does not match the assigned target %s"
                     % (reported, normalize_va(va)), raw_sha256=digest,
                     reported_va=reported, expected_va=normalize_va(va))

    for field in ("source_files", "unresolved_questions", "evidence_refs"):
        value = document.get(field)
        if value is not None and not isinstance(value, list):
            return _fail("worker result %r must be a list" % field,
                         raw_sha256=digest, field=field)
    mechanics = document.get("observed_mechanics")
    if mechanics is not None and not isinstance(mechanics, list):
        return _fail("worker result 'observed_mechanics' must be a list",
                     raw_sha256=digest, field="observed_mechanics")

    # A hostile payload must be refused, never raised on. ``validation`` is
    # read with an explicit type check because an unchecked ``.get`` here used
    # to let a bare string or list escape as AttributeError, and an exception
    # out of this function leaves the queue row active with a live lease.
    validation = document.get("validation")
    if validation is not None and not isinstance(validation, dict):
        return _fail("worker result 'validation' must be an object, got %s"
                     % type(validation).__name__, raw_sha256=digest,
                     field="validation")
    verdict = (validation or {}).get("status")
    if verdict is not None and verdict not in VALIDATION_VERDICTS:
        return _fail("worker reported an unknown validation verdict %r" % verdict,
                     raw_sha256=digest, verdict=verdict)

    # The VA the orchestrator recorded is authoritative; the payload is only
    # cross-checked above.
    document["va"] = normalize_va(va) if va is not None else reported
    document["queue_id"] = inv_id
    return {
        "accepted": True,
        "raw_sha256": digest,
        "outcome": outcome,
        "result": document,
        "channel": provenance["channel"],
        "extraction_stage": provenance.get("extraction_stage"),
        "text_blocks": provenance["text_blocks"],
        "tool_calls": provenance["tool_calls"],
        "nested_result": provenance["nested_result"],
    }


def result_template(va, implementer_id=None, queue_id=None):
    # type: (object, object, object) -> dict
    """A fillable skeleton, so a worker never has to guess the field names."""
    va = normalize_va(va)
    return {
        "schema": RESULT_SCHEMA,
        "va": va,
        "outcome": "STILL_UNKNOWN",
        "summary": "",
        "normalized_symbol": "opaque_%s" % va[2:],
        "reconstructed_symbol": "reconstruct_%s" % va[2:],
        "source_files": [],
        "types": [],
        "observed_mechanics": [],
        "semantic_findings": [],
        "unresolved_questions": [],
        "evidence_refs": [],
        "implementer_id": implementer_id,
        "queue_id": queue_id,
    }
