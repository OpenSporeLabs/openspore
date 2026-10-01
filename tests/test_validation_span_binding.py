"""How ``validate._target_span`` binds a reconstructed symbol to a target.

One rule, and the bug it was meant to serve: the worker briefing tells a worker
that *the reconstructed symbol must embed the 8-hex target VA so the validator
can locate the span*, and the VA token is the authoritative binder. A record
that carries no descriptive name -- a bare Ghidra placeholder, ``FUN_00bba790``,
which is what every target the SDK never named carries -- has no words to narrow
a span with, so the token alone is the whole contract. The old binder demanded
the literal substring ``fun`` in the *span* key as well, which is a proxy that
only holds when the binary itself has a descriptive name, so a worker's symbol
carrying the VA was rejected and the target could never be adjudicated at all:
``ABI``, ``CALLS`` and ``RETURN SEMANTICS`` all read "target source span is not
deterministically available" for a source that was present, compiled, and named
the target.

So the two halves held here are:

* a placeholder-named record binds on the VA token alone, and only on that token
  -- a source with no token-bearing span still refuses, so nothing is bound that
  the contract does not authorise; and
* every record that has a real name keeps the strict word-narrowed path, byte
  for byte. The last two tests prove that the hard way: they run the whole
  validator twice over the same fixture, once with the shipped binder and once
  with the pre-fix binder restored in-process, and require the two reports to be
  equal.

The legacy binder below is the code as it stood before the fix, kept verbatim
so "unchanged" is asserted against the actual old behaviour rather than against
a description of it.
"""

import json
import shutil
import tempfile
import unittest
from pathlib import Path

from tests.orchestration_fixture import build_root
from tests.test_validation_dimensions import (BODY, DEFAULT_ABI, HELPER, MANIFEST_REL,
                                             METADATA_REL, QUEUE_REL, SEMANTIC_REL,
                                             TARGET, XREF_REL, _machine_pack, _write)
from tools.reconstruction_tooling import validate as V
from tools.reconstruction_tooling.frontier import _INDEX_CACHE

KEY = "A"
# The synthetic target, and the same address the evidence-pack fixture in
# ``tests/test_validation_dimensions.py`` is built around, so its listing, its
# body and its xref edge are reused rather than re-invented.
FIXTURE_VA = TARGET
# The staging path a metadata sidecar points a brand-new target at. The SDK never
# named this target, so there is no manifest entry to carry the source, exactly
# as for 0x00bba790.
STAGING_REL = "reconstruction/staging/pkg_fixture/sim_%s.cpp" % FIXTURE_VA[2:]


def _legacy_target_span(text, record):
    """``_target_span`` as it stood before the fix, verbatim.

    Used only to assert that the change is confined to the placeholder case: the
    reports it produces for a real-named record, and for a record that binds to
    nothing, must be identical to the shipped binder's.
    """
    import re

    raw_names = []
    for key in ("name", "normalized_symbol"):
        value = record.get(key)
        if isinstance(value, str) and value:
            candidate = value.rsplit("::", 1)[-1]
            if candidate and candidate not in raw_names:
                raw_names.append(candidate)
    spans = [(span, V._normalized_name(span["name"])) for span in V._function_spans(text)]
    va_token = str(record.get("va", "")).replace("0x", "").casefold()
    for raw_name in raw_names:
        normalized = V._normalized_name(raw_name)
        words = [word.casefold() for word in re.findall(r"[A-Z]?[a-z]+|[0-9]+", raw_name) if word]
        if normalized.startswith("fun") and va_token:
            candidates = [span for span, key in spans if va_token in key and "fun" in key]
        elif va_token and words:
            candidates = [span for span, key in spans if va_token in key
                          and all(word in key for word in words)]
        else:
            candidates = []
        if candidates:
            return candidates[0]
    return None


class _Legacy(object):
    """Swap ``validate._target_span`` for the pre-fix binder, then restore it."""

    def __init__(self, test):
        self.test = test

    def __enter__(self):
        self.saved = V._target_span
        V._target_span = _legacy_target_span
        return self

    def __exit__(self, *exc):
        V._target_span = self.saved
        return False


def _definition(name, body="  return 0;", returns="int", convention="__cdecl"):
    return 'extern "C" %s %s %s() {\n%s\n}\n' % (returns, convention, name, body)


# --------------------------------------------------------------------------
# The binder itself.
# --------------------------------------------------------------------------
class PlaceholderBindingTest(unittest.TestCase):

    # The live case, verbatim: the record carries only the Ghidra placeholder and
    # the worker's symbol embeds the VA and does not contain the word ``fun``.
    TARGET_VA = "0x00bba790"
    WORKER_SYMBOL = "sim_00bba790_flush_pending_and_select_vector"
    RECORD = {"va": "0x00bba790", "name": "FUN_00bba790",
              "normalized_symbol": "FUN_00bba790"}

    def _source(self, *names):
        return "".join(_definition(name) for name in names)

    def test_a_placeholder_record_binds_a_symbol_that_embeds_the_va(self):
        span = V._target_span(self._source(self.WORKER_SYMBOL), self.RECORD)
        self.assertIsNotNone(span, "the VA token is the documented binder and it is present")
        self.assertEqual(span["name"], self.WORKER_SYMBOL)

    def test_a_placeholder_record_binds_nothing_when_no_span_embeds_the_va(self):
        # The negative control at binder level: a token is required, so a file
        # that never names the target still refuses rather than binding the first
        # function it happens to contain.
        text = self._source("sim_flush_pending_and_select_vector",
                            "helper_00bba640_refresh")
        self.assertIsNone(V._target_span(text, self.RECORD))

    def test_a_placeholder_binds_to_a_span_whose_own_name_also_embeds_the_va(self):
        # Both spans carry the token, so the first declared one wins. This is
        # today's ``candidates[0]`` behaviour, asserted rather than assumed: the
        # fix does not add an ambiguity refusal, so a file that embeds the token
        # twice still binds to the first, and a reader can see that is the rule.
        first = "sim_f00bba790_ports"
        second = self.WORKER_SYMBOL
        text = self._source(first, second)
        span = V._target_span(text, self.RECORD)
        self.assertEqual(span["name"], first)
        self.assertEqual(_legacy_target_span(text, self.RECORD), None,
                         "the pre-fix binder refused both, which is the defect")

    def test_the_placeholder_pattern_matches_only_a_bare_placeholder(self):
        for name in ("FUN_00bba790", "fun_00bba790", "FUN_00BBA790",
                     "FUN_00bba790_00bba790"):
            self.assertIsNotNone(V.PLACEHOLDER_SYMBOL.match(V._normalized_name(name)),
                                 name)
        for name in ("FunctionPool::Reset", "Funny::Reset", "fun_00bba79",
                     "FUN_00bba790_extra", "fund_00bba790"):
            self.assertIsNone(V.PLACEHOLDER_SYMBOL.match(V._normalized_name(name)),
                              name)

    def test_a_real_name_is_never_read_as_a_placeholder(self):
        # The narrowing is on the *name*, and the record is reduced to its last
        # ``::`` component first, so this is the string the pattern sees.
        self.assertIsNone(V.PLACEHOLDER_SYMBOL.match(
            V._normalized_name("FunctionPool::Reset".rsplit("::", 1)[-1])))


class RealNameStrictPathTest(unittest.TestCase):

    VA = "0x006a2ef0"
    REAL = {"va": "0x006a2ef0", "name": "App::PropertyList::RemoveProperty",
            "normalized_symbol": "App::PropertyList::RemoveProperty"}

    def test_a_span_embedding_the_va_but_missing_a_word_does_not_bind(self):
        # The strict path, held: a real name narrows to its words and every one
        # of them must appear. ``sim_006a2ef0_flush`` carries the token and none
        # of ``remove``/``property``, so it is not this target's span.
        text = 'extern "C" int __cdecl sim_006a2ef0_flush() {\n  return 0;\n}\n'
        self.assertIsNone(V._target_span(text, self.REAL))
        self.assertIsNone(_legacy_target_span(text, self.REAL))

    def test_a_span_carrying_every_word_does_bind(self):
        text = 'extern "C" int __cdecl app_propertylist_removeproperty_006a2ef0() {\n  return 0;\n}\n'
        span = V._target_span(text, self.REAL)
        self.assertIsNotNone(span)
        self.assertEqual(span["name"], "app_propertylist_removeproperty_006a2ef0")

    def test_a_name_beginning_with_function_keeps_the_strict_path(self):
        # The name the loose ``startswith("fun")`` test would have captured. Its
        # only word is ``reset``, so a token-bearing span that omits it must not
        # bind -- which is exactly what the old code did *not* guarantee for a
        # name it misfiled as a placeholder.
        record = {"va": "0x006a2ef0", "name": "FunctionPool::Reset",
                  "normalized_symbol": "FunctionPool::Reset"}
        text = 'extern "C" int __cdecl sim_006a2ef0_flush() {\n  return 0;\n}\n'
        self.assertIsNone(V._target_span(text, record))
        bound = 'extern "C" int __cdecl functionpool_reset_006a2ef0() {\n  return 0;\n}\n'
        self.assertIsNotNone(V._target_span(bound, record))


# --------------------------------------------------------------------------
# End to end, on a synthetic root shaped like a target the SDK never named:
# a triage-only record (so both of its names are the Ghidra placeholder), a
# staging source reached through a metadata sidecar, and a machine pack with a
# complete listing.
# --------------------------------------------------------------------------
class BindEndToEndTest(unittest.TestCase):
    # A body the pack can fully satisfy, so a bound span reaches a verdict on
    # every axis and the aggregate is decided by the binding alone.
    SPAN_BODY = "  return helper_00abcde1(3);"

    def setUp(self):
        self.tmp = tempfile.mkdtemp(prefix="openspore-span-binding-")
        self.addCleanup(shutil.rmtree, self.tmp, True)
        self.addCleanup(_INDEX_CACHE.clear)
        _INDEX_CACHE.clear()
        self._built = 0

    def build(self, source_text, triage_name):
        """A synthetic root whose single record is named ``triage_name``."""
        self._built += 1
        root = Path(self.tmp) / ("root-%d" % self._built)
        info = build_root(str(root), keys=(KEY,))
        self.info = info
        # Re-name the record and re-point its source, keeping every canonical
        # artifact ``build_root`` already wrote valid and re-hashed.
        _write(root / MANIFEST_REL, json.dumps({
            "schema": "openspore-source-reconstruction-manifest-1",
            "binary": {"sha256": info["sha"], "name": "SporeApp.exe",
                       "source": "synthetic-fixture"},
            "functions": [{"va": FIXTURE_VA, "subsystem": "synth_io",
                           "package": "PKG-SYNTH-ALPHA", "body_status": "unresolved",
                           "observed_mechanics": [], "evidence_level": "SUPPORTED"}],
            "packages": [{"id": "PKG-SYNTH-ALPHA", "status": "triage_only"}],
            "types": []}, indent=2, sort_keys=True) + "\n")
        _write(root / QUEUE_REL, json.dumps({
            "schema": "openspore-triage-queue-1",
            "queue": [{"va": FIXTURE_VA, "name": triage_name, "package": "PKG-SYNTH-ALPHA",
                       "subsystem": "synth_io", "queue_state": "queued"}]},
            indent=2, sort_keys=True) + "\n")
        _write(root / SEMANTIC_REL, json.dumps({
            "schema": "openspore-semantic-decomp-1", "records": [],
            "contradictions": [], "family_index": []}, indent=2, sort_keys=True) + "\n")
        # The one out-edge the CALLS oracle needs: the body below makes exactly
        # one call, and the export has to record it or the check is decided by the
        # fixture rather than by the binding under test.
        _write(root / XREF_REL, "caller_va\tcallee_va\treference_type\tcallsite_va\n"
                 "%s\t%s\tdirect-call\t00c0ff00\n" % (FIXTURE_VA[2:], HELPER))
        _write(root / STAGING_REL, source_text)
        _write(root / METADATA_REL, json.dumps({
            "va": FIXTURE_VA, "abi": DEFAULT_ABI, "types": [],
            "source_files": [STAGING_REL]}, indent=2, sort_keys=True) + "\n")
        # The index is read through the same cached path the validator uses, so
        # this fixture exercises the production lookup and not a private one.
        index = V._index(root)
        record = V._record(index, FIXTURE_VA)
        # The fixture is only meaningful if it really is the shape under test.
        self.assertEqual(record.get("name"), triage_name)
        self.assertEqual(record.get("normalized_symbol"), triage_name)
        self.assertEqual(V._source(root, record)["path"].name,
                         Path(STAGING_REL).name)
        return root, record

    def validate(self, source_text, triage_name):
        root, _record = self.build(source_text, triage_name)
        return self.over(root)

    def over(self, root, legacy=False):
        """One validation run over an already-built root.

        Both binders run over the *same* root so the two reports are comparable
        field for field -- the report embeds the root path, so two roots would
        differ on that alone and the comparison would prove nothing.
        """
        pack = _machine_pack(BODY)
        pack["target"] = {"va": FIXTURE_VA, "address_kind": "linked_va"}
        if legacy:
            with _Legacy(self):
                return V.validate(root=root, va=FIXTURE_VA, evidence=pack, write=False)
        return V.validate(root=root, va=FIXTURE_VA, evidence=pack, write=False)

    def both(self, source_text, triage_name):
        """``(shipped report, pre-fix report)`` over one root."""
        root, _record = self.build(source_text, triage_name)
        return self.over(root), self.over(root, legacy=True)

    def test_a_placeholder_record_now_binds_and_the_aggregate_leaves_not_available(self):
        # The symbol embeds the VA and the record is a bare placeholder: the case
        # the fix exists for.
        report, legacy = self.both(
            'extern "C" int __cdecl sim_00c0ffee_flush_pending() {\n%s\n}\n'
            % self.SPAN_BODY, "FUN_00c0ffee")
        checks = report["checks"]
        refusal = "target source span is not deterministically available"
        for name in ("ABI", "CALLS"):
            self.assertNotEqual(checks[name]["detail"], refusal, name)
            self.assertNotEqual(checks[name]["status"], "NOT_AVAILABLE", name)
        self.assertNotEqual(checks["RETURN SEMANTICS"]["status"], "NOT_AVAILABLE")
        self.assertNotEqual(report["static"]["status"], "NOT_AVAILABLE")
        # And the gate is not merely opened: with a complete listing and a source
        # span that agrees with it, every structural check passes, so the target
        # can reach the verdict promotion needs.
        self.assertEqual(report["static"]["status"], "PASS")
        for name, check in sorted(checks.items()):
            if name == "EVIDENCE COVERAGE":
                continue
            self.assertEqual(check["status"], "PASS", "%s: %s" % (name, check["detail"]))
        # And the whole difference the fix makes is the three refusals becoming
        # verdicts, not any threshold moving: the pre-fix binder cannot bind this
        # record at all.
        self.assertEqual(legacy["static"]["status"], "NOT_AVAILABLE")
        self.assertEqual(legacy["checks"]["ABI"]["detail"], refusal)
        self.assertEqual(legacy["checks"]["CALLS"]["detail"], refusal)
        self.assertEqual(legacy["checks"]["RETURN SEMANTICS"]["detail"],
                         "return evidence is not deterministically available")
        moved = sorted(name for name in checks
                       if checks[name]["status"] != legacy["checks"][name]["status"])
        self.assertEqual(moved, ["ABI", "CALLS", "RETURN SEMANTICS"])

    def test_a_source_that_does_not_embed_the_va_still_refuses_byte_identically(self):
        # The negative control: the token is the binder, so a symbol without it
        # binds nothing and every refusal is the one the pre-fix code emitted.
        text = ('extern "C" int __cdecl sim_flush_pending() {\n%s\n}\n'
                % self.SPAN_BODY)
        report, legacy = self.both(text, "FUN_00c0ffee")
        self.assertEqual(report["checks"]["ABI"]["detail"],
                         "target source span is not deterministically available")
        self.assertEqual(report["checks"]["CALLS"]["detail"],
                         "target source span is not deterministically available")
        self.assertEqual(report["checks"]["RETURN SEMANTICS"]["detail"],
                         "return evidence is not deterministically available")
        self.assertEqual(report["static"]["status"], "NOT_AVAILABLE")
        self.assertEqual(report, legacy,
                         "the refusal is not byte-identical to the pre-fix verdict")

    def test_a_real_named_record_is_unchanged_byte_for_byte(self):
        # The proof that the strict path was not touched: a real name, a matching
        # source, and the whole report compared against the pre-fix binder.
        text = ('extern "C" int __cdecl sim_00c0ffee_flush_pending() {\n%s\n}\n'
                % self.SPAN_BODY)
        report, legacy = self.both(text, "FlushPending")
        self.assertEqual(report["static"]["status"], "PASS")
        self.assertEqual(report, legacy,
                         "a real-named record's verdict changed, so the strict path moved")

    def test_a_real_named_record_with_no_matching_span_is_unchanged(self):
        # And the other direction: a real name that binds to nothing refuses
        # exactly as it did, because the VA token alone is not enough for it.
        text = ('extern "C" int __cdecl other_helper() {\n%s\n}\n'
                % self.SPAN_BODY)
        report, legacy = self.both(text, "FlushPending")
        self.assertEqual(report["static"]["status"], "NOT_AVAILABLE")
        self.assertEqual(report, legacy)


if __name__ == "__main__":  # pragma: no cover
    unittest.main()
