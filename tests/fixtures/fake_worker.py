#!/usr/bin/env python3
"""A synthetic reconstruction worker, usable two ways.

* as a subprocess: ``python3 fake_worker.py --variant ok`` -- the briefing is
  one JSON document on stdin, the reply is one JSON document on stdout;
* as an importable module: ``fake_worker.build_result(briefing, "ok")``.

Deliberately stdlib-only and dependency-free: no ``tools.*`` import, no
Ghidra, no network, no display, no game assets. The contract constants are
duplicated here on purpose -- a real worker process must not be able to reach
into the orchestrator's own modules, and a test that proves the contract is
reproducible from this file alone is worth more than one that shares the
implementation with the thing under test.

Exit codes: 0 for a well-formed reply, 1 when the variant deliberately emits
something the contract parser must reject (``--variant malformed_json``).
"""
from __future__ import print_function

import argparse
import json
import sys

BRIEFING_SCHEMA = "openspore-worker-briefing-1"
RESULT_SCHEMA = "openspore-worker-result-1"

OUTCOMES = ("IMPLEMENTED", "PARTIAL", "STRUCTURAL_ONLY", "STILL_UNKNOWN",
            "BLOCKED", "FAILED_VALIDATION")
VARIANTS = ("ok", "still_unknown", "failed_validation", "block",
            "malformed_json", "malformed_shape", "bad_schema", "bad_outcome",
            "wrong_va")
REQUIRED_FIELDS = ("schema", "va", "outcome", "summary", "source_files",
                   "observed_mechanics", "unresolved_questions", "evidence_refs")

# Used by --variant wrong_va: a valid result for a function nobody assigned.
OTHER_VA = "0x00b3d400"


def read_briefing(stream=None):
    """Parse the briefing document from ``stream`` (stdin by default)."""
    handle = stream if stream is not None else sys.stdin
    raw = handle.read()
    if not raw.strip():
        raise ValueError("fake_worker received an empty briefing on stdin")
    return json.loads(raw)


def _bare(va):
    text = str(va).strip().lower()
    return text[2:] if text.startswith("0x") else text


def _camel(name):
    words = [word for word in str(name or "").replace("_", " ").split() if word]
    return "".join(word[:1].upper() + word[1:] for word in words) or "Opaque"


def build_result(briefing, variant="ok", other_va=OTHER_VA):
    """Build this worker's reply for ``briefing``.

    The VA comes from the briefing the orchestrator actually handed over, and
    the reconstructed symbol embeds the 8-hex VA so the validator can find the
    span -- the two rules the briefing's ``rules`` list states.
    """
    if variant not in VARIANTS:
        raise ValueError("unknown variant %r; expected one of %s"
                         % (variant, ", ".join(VARIANTS)))
    target = (briefing or {}).get("target") or {}
    va = target.get("va") or "0x00000000"
    name = target.get("name")
    if variant == "malformed_json":
        return "{ this is deliberately not json\n"
    if variant == "malformed_shape":
        return json.dumps({"schema": RESULT_SCHEMA, "va": va,
                           "outcome": "IMPLEMENTED"})
    if variant == "bad_schema":
        document = _document(va, name, other_va)
        document["schema"] = "openspore-worker-result-0"
        return json.dumps(document, indent=2, sort_keys=True) + "\n"
    if variant == "bad_outcome":
        document = _document(va, name, other_va)
        document["outcome"] = "ALMOST_DONE"
        return json.dumps(document, indent=2, sort_keys=True) + "\n"
    outcome = {"ok": "IMPLEMENTED", "still_unknown": "STILL_UNKNOWN",
               "failed_validation": "FAILED_VALIDATION",
               "block": "BLOCKED", "wrong_va": "IMPLEMENTED"}[variant]
    document = _document(other_va if variant == "wrong_va" else va, name,
                         other_va)
    document["outcome"] = outcome
    return json.dumps(document, indent=2, sort_keys=True) + "\n"


def _document(va, name, other_va):
    bare = _bare(va)
    return {
        "schema": RESULT_SCHEMA,
        "va": va,
        "outcome": "IMPLEMENTED",
        "summary": "fake_worker reconstructed %s" % (name or bare),
        "normalized_symbol": name or ("fun_%s" % bare),
        "reconstructed_symbol": "reconstruct_%s_%s" % (bare, _camel(name)),
        "source_files": ["reconstruction/staging/fake_worker/%s.cpp" % bare],
        "observed_mechanics": ["decrements its first argument by one"],
        "semantic_findings": [{"claim": "returns value-1 when value > 0"}],
        "unresolved_questions": [],
        "evidence_refs": ["reconstruction/knowledge/index.json#/records/%s" % va],
    }


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--variant", choices=VARIANTS, default="ok")
    parser.add_argument("--briefing", default=None,
                        help="read the briefing from this path instead of stdin")
    args = parser.parse_args(argv)
    try:
        if args.briefing:
            with open(args.briefing, encoding="utf-8") as handle:
                briefing = json.load(handle)
        else:
            briefing = read_briefing()
    except (OSError, ValueError) as exc:
        sys.stderr.write("fake_worker: %s\n" % exc)
        return 2
    sys.stdout.write(build_result(briefing, args.variant))
    return 1 if args.variant == "malformed_json" else 0


if __name__ == "__main__":
    sys.exit(main())
