"""Fixtures for the two validation dimensions.

The validator returns a STATIC verdict on a reconstruction and a RUNTIME verdict
for the original process. These tests hold three lines at once:

* a genuinely strong static candidate can reach ``STATIC: PASS``;
* a candidate never reaches ``PASS`` merely because evidence is absent;
* a static ``PASS`` never reads as, or becomes, a runtime claim.

The last point is the one the whole split exists to protect, so it is asserted
from several directions rather than once.
"""

import unittest
from pathlib import Path
from tempfile import TemporaryDirectory

from tools.reconstruction_tooling import validate as V
from tools.reconstruction_tooling.frontier import _INDEX_CACHE
from tools.reconstruction_knowledge import build_index

TARGET = "0x00c0ffee"
HELPER = "00abcde1"
MANIFEST_REL = "knowledgegraph/research/source-reconstruction-manifest.json"
QUEUE_REL = "knowledgegraph/triage/queue-f0e310e0-v6.json"
SEMANTIC_REL = "knowledgegraph/research/semantic-decomp.json"
XREF_REL = "knowledgegraph/triage/xrefs-2540f2ca.tsv"
METADATA_REL = "reconstruction/metadata/pkg_fixture/00c0ffee.json"
DEFAULT_ABI = {"calling_convention": "__cdecl", "return_type": "int"}
SOURCE_REL = "src/fixture_pkg/fixture.cpp"


def _span(body, name="reconstruct_me_00c0ffee", returns="int", convention="__cdecl"):
    return "%s %s %s() {\n%s\n}\n" % (returns, convention, name, body)


def _category(available, value=None):
    return {"availability": "available" if available else "unavailable",
            "evidence_state": "PERSISTED" if available else "MISSING",
            "evidence_level": "SUPPORTED" if available else "UNKNOWN",
            "provenance": [], "value": value if available else None, "reason": None}


def _pack(**categories):
    """An evidence pack. Only the keys a check reads need to be present."""
    base = {
        "abi": _category(False),
        "types": _category(False),
        "globals": _category(False),
        "vtables": _category(False),
        "ghidra_function": _category(False),
        "disassembly": _category(False),
        "decompilation": _category(False),
        # The runtime category is a reserved slot: it is never searched, so it is
        # never available. A test that expects a static PASS must still succeed
        # with this present and unavailable -- that is the coupling being removed.
        "runtime": _category(False),
        "runtime_metadata": _category(True, {"gates": ["gate-fixture-runtime"], "validated": 0}),
        "function_identity": _category(True, {"va": TARGET}),
        "status": _category(True, {"status": "candidate"}),
    }
    for key, value in categories.items():
        if isinstance(value, tuple):
            base[key] = _category(value[0], value[1])
        else:
            base[key] = value
    return {"schema": "openspore-evidence-pack-1",
            "target": {"va": TARGET, "address_kind": "linked_va"},
            "evidence_state": "PERSISTED",
            "content_sha256": "0" * 64,
            "categories": base,
            "record": {}}


def _write(path, payload):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(payload, encoding="utf-8")


class DimensionFixture(unittest.TestCase):
    """A throwaway repository built from the same canonical inputs as production.

    The projection is rebuilt by ``build_index`` rather than hand-written, so
    these fixtures exercise the real path from manifest, xref export and metadata
    to a record -- including the address normalisation the CALLS oracle needs.
    """

    def build(self, source_text, pack, edges=(), abi=None, gates=("gate-fixture-runtime",),
              types=(), mechanics=(), write_source=True, validated=0):
        tmp = TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.addCleanup(_INDEX_CACHE.clear)
        root = Path(tmp.name)
        self.root = root

        if write_source:
            _write(root / SOURCE_REL, source_text)

        _write(root / MANIFEST_REL,
               '{"schema":"openspore-source-reconstruction-manifest-1",'
               '"binary":{"sha256":"fixture","name":"SporeApp.exe","source":"fixture"},'
               '"functions":[{"va":"%s","normalized_symbol":"reconstruct_me_00c0ffee",'
               '"subsystem":"FIXTURE","package":"pkg_fixture","source_file":"%s",'
               '"body_status":"unresolved","observed_mechanics":%s,'
               '"evidence_level":"SUPPORTED","runtime_gates":%s,'
               '"audit_runtime_validated":%d}],'
               '"packages":[{"id":"pkg_fixture","status":"triage_only"}],"types":[]}'
               % (TARGET, SOURCE_REL, _json(mechanics), _json(list(gates)), validated))
        _write(root / QUEUE_REL, '{"schema":"openspore-triage-queue-1","queue":[]}')
        _write(root / SEMANTIC_REL,
               '{"schema":"openspore-semantic-decomp-1","records":[],'
               '"contradictions":[],"family_index":[]}')
        rows = ["caller_va\tcallee_va\treference_type\tcallsite_va"]
        for caller, callee, kind in edges:
            rows.append("%s\t%s\t%s\t00c0ff00" % (caller, callee, kind))
        _write(root / XREF_REL, "\n".join(rows) + "\n")
        resolved_abi = DEFAULT_ABI if abi is None else abi
        _write(root / METADATA_REL,
               '{"va":"%s","abi":%s,"types":%s}' % (TARGET, _json(resolved_abi), _json(list(types))))

        return V.validate(root=root, va=TARGET, evidence=pack, write=False)


def _json(value):
    import json
    return json.dumps(value)


OUT = [(TARGET, HELPER, "direct-call")]


# --------------------------------------------------------------------------
# Positive: a statically strong candidate earns a static PASS.
# --------------------------------------------------------------------------
class StaticPass(DimensionFixture):

    def test_static_pass_when_every_evaluated_check_agrees(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        self.assertEqual(report["static"]["status"], "PASS")
        # Back-compat alias: every existing consumer reads this and it means the
        # static dimension, unchanged.
        self.assertEqual(report["status"], "PASS")
        self.assertEqual(report["static"]["dimension"], "STATIC")
        self.assertEqual(report["static"]["checks"]["CALLS"]["status"], "PASS")
        self.assertEqual(report["static"]["checks"]["ABI"]["status"], "PASS")
        self.assertEqual(report["static"]["checks"]["RETURN SEMANTICS"]["status"], "PASS")

    def test_static_pass_names_the_runtime_axis_as_gated(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        self.assertEqual(report["static"]["status"], "PASS")
        self.assertEqual(report["runtime"]["dimension"], "RUNTIME")
        self.assertEqual(report["runtime"]["status"], "GATED")
        self.assertTrue(report["runtime"]["gated"])
        self.assertEqual(report["runtime"]["validated"], 0)
        self.assertEqual(report["runtime"]["gates"], ["gate-fixture-runtime"])

    def test_a_static_pass_is_never_a_runtime_claim(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        self.assertEqual(report["static"]["status"], "PASS")
        self.assertNotEqual(report["runtime"]["status"], "PASS")
        # The gate is not merely flagged, it is repeated in the open questions so
        # a reader of the question list alone still sees it.
        self.assertIn("gate-fixture-runtime", report["unresolved_questions"])

    def test_static_pass_reports_how_much_it_actually_evaluated(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        basis = report["static"]["evidence_basis"]
        self.assertEqual(basis["static_checks_total"], len(V.STATIC_CHECKS))
        self.assertLess(basis["static_checks_evaluated"], basis["static_checks_total"])
        self.assertGreater(basis["static_checks_evaluated"], 0)
        self.assertEqual(basis["static_checks_evaluated"] + basis["static_checks_not_available"],
                         basis["static_checks_total"])

    def test_runtime_pass_when_the_record_reports_a_validated_observation(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(),
                            edges=OUT, gates=(), validated=2)
        self.assertEqual(report["runtime"]["status"], "PASS")
        self.assertEqual(report["runtime"]["validated"], 2)
        self.assertFalse(report["runtime"]["gated"])

    def test_markdown_states_both_dimensions(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        text = V.render_markdown(report)
        self.assertIn("Static reconstruction: `PASS`", text)
        self.assertIn("Runtime (original process): `GATED`", text)
        self.assertIn("attempted and nothing failed", text)


# --------------------------------------------------------------------------
# Negative: absence of evidence must never produce a PASS.
# --------------------------------------------------------------------------
class AbsenceIsNotAPass(DimensionFixture):

    def test_no_source_artifact_is_not_available_not_pass(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(),
                            edges=OUT, write_source=False)
        self.assertEqual(report["status"], "NOT_AVAILABLE")
        self.assertNotEqual(report["static"]["status"], "PASS")

    def test_no_evidence_categories_at_all_blocks_a_static_pass(self):
        pack = _pack(function_identity=_category(False), status=_category(False),
                     runtime_metadata=_category(False))
        report = self.build(_span("  return helper_00abcde1(3);"), pack, edges=OUT)
        self.assertEqual(report["static"]["evidence_coverage"]["status"], "NOT_AVAILABLE")
        # This is the safety floor: a reconstruction cannot be statically
        # validated against zero evidence, however clean its source looks.
        self.assertEqual(report["static"]["status"], "NOT_AVAILABLE")

    def test_no_call_oracle_is_not_available_not_pass(self):
        # The source names a callee and the export records none. That is missing
        # evidence, not agreement and not contradiction.
        report = self.build(_span("  return helper_00abcde1(3);"), _pack())
        self.assertEqual(report["static"]["checks"]["CALLS"]["status"], "NOT_AVAILABLE")

    def test_truncated_oracle_is_a_warning_not_a_pass(self):
        many = OUT + [("00c0ffee", "%08x" % (0x00401000 + step), "direct-call")
                      for step in range(31)]
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=many)
        self.assertEqual(report["static"]["checks"]["CALLS"]["status"], "WARN")
        self.assertEqual(report["static"]["status"], "WARN")

    def test_a_declared_field_offset_still_warns_and_still_blocks(self):
        # The check has no PASS branch: no machine-derived struct layout exists
        # to corroborate an offset. A reconstruction that asserts one is therefore
        # a review item, and this is the gate that keeps it one.
        report = self.build(_span("  state->field = 1;\n  return helper_00abcde1(3);"),
                            _pack(types=(True, ["Matrix3"])), edges=OUT, types=("Matrix3",))
        fields = report["static"]["checks"]["FIELDS/OFFSETS"]
        self.assertEqual(fields["status"], "WARN")
        self.assertIn("no machine-derived struct layout exists to corroborate", fields["detail"])
        self.assertNotEqual(report["static"]["status"], "PASS")

    def test_naming_a_type_is_not_declaring_an_offset(self):
        # The record names a type and the source only calls through it. Nothing
        # physical is asserted, so there is nothing to corroborate and nothing to
        # warn about; reporting an unverified offset here would state a defect
        # that does not exist.
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _pack(types=(True, ["Matrix3"])), edges=OUT, types=("Matrix3",))
        fields = report["static"]["checks"]["FIELDS/OFFSETS"]
        self.assertEqual(fields["status"], "NOT_AVAILABLE")
        self.assertIn("declares no field offset", fields["detail"])

    def test_a_method_call_through_a_pointer_is_not_a_field(self):
        report = self.build(_span("  return ports->query_00abcde1();"), _pack(), edges=OUT)
        self.assertEqual(report["static"]["checks"]["FIELDS/OFFSETS"]["status"], "NOT_AVAILABLE")

    def test_an_explicit_displacement_counts_as_a_declared_offset(self):
        report = self.build(_span("  return *(int *)(this + 0x10);"), _pack(), edges=OUT)
        fields = report["static"]["checks"]["FIELDS/OFFSETS"]
        self.assertEqual(fields["status"], "WARN")
        self.assertIn("0x10", fields["detail"])

    def test_unknown_stays_unknown_and_outranks_a_pass(self):
        report = self.build(_span("  return vtable->load_slot_00abcdef01();"), _pack(),
                            edges=OUT)
        self.assertEqual(report["static"]["checks"]["VIRTUAL DISPATCH"]["status"], "UNKNOWN")
        self.assertEqual(report["static"]["status"], "UNKNOWN")


# --------------------------------------------------------------------------
# Negative: a contradiction is a FAIL, and FAIL outranks everything.
# --------------------------------------------------------------------------
class Contradiction(DimensionFixture):

    def test_a_named_callee_with_no_call_edge_fails(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(),
                            edges=[(TARGET, "00999999", "direct-call")])
        self.assertEqual(report["static"]["checks"]["CALLS"]["status"], "FAIL")
        self.assertEqual(report["static"]["status"], "FAIL")

    def test_a_source_constant_absent_from_the_listing_fails(self):
        pack = _pack(disassembly=(True, {"instructions": [
            {"address": "00c0ffee", "instruction": "MOV EAX,0x7"},
            {"address": "00c0fff0", "instruction": "RET"}]}))
        report = self.build(_span("  return helper_00abcde1(0x202);"), pack, edges=OUT)
        self.assertEqual(report["static"]["checks"]["CONSTANTS"]["status"], "FAIL")
        self.assertEqual(report["static"]["status"], "FAIL")

    def test_source_claiming_virtual_dispatch_with_no_indirect_call_fails(self):
        pack = _pack(disassembly=(True, {"instructions": [
            {"address": "00c0ffee", "instruction": "MOV EAX,0x7"},
            {"address": "00c0fff0", "instruction": "RET"}]}))
        report = self.build(_span("  return vtable->load_slot_00abcdef01();"), pack, edges=OUT)
        self.assertEqual(report["static"]["checks"]["VIRTUAL DISPATCH"]["status"], "FAIL")

    def test_a_source_constant_present_in_the_listing_passes(self):
        pack = _pack(disassembly=(True, {"instructions": [
            {"address": "00c0ffee", "instruction": "MOV EAX,0x202"},
            {"address": "00c0fff0", "instruction": "RET"}]}))
        report = self.build(_span("  return helper_00abcde1(0x202);"), pack, edges=OUT)
        self.assertEqual(report["static"]["checks"]["CONSTANTS"]["status"], "PASS")


# --------------------------------------------------------------------------
# False-positive controls: the predicate must not fire on honest reconstructions.
# --------------------------------------------------------------------------
class FalsePositiveControls(DimensionFixture):

    def test_in_edges_do_not_count_as_outgoing_calls(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(),
                            edges=[("00aaaaaa", TARGET, "direct-call")])
        self.assertEqual(report["static"]["checks"]["CALLS"]["status"], "NOT_AVAILABLE")

    def test_data_references_are_not_calls(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(),
                            edges=[(TARGET, "015d115d", "data-ref")])
        self.assertEqual(report["static"]["checks"]["CALLS"]["status"], "NOT_AVAILABLE")

    def test_the_target_does_not_call_itself(self):
        # The span under test contains its own address-suffixed declaration, so a
        # naive token scan reports every reconstruction as self-recursive.
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        self.assertEqual(report["static"]["checks"]["CALLS"]["status"], "PASS")

    def test_data_addresses_in_names_are_not_calls(self):
        # A global named with a data address must not be read as a callee.
        report = self.build(
            _span("  g_unmodelled_015d115d = helper_00abcde1(3);\n  return 1;"),
            _pack(), edges=OUT)
        self.assertEqual(report["static"]["checks"]["CALLS"]["status"], "PASS")

    def test_extra_machine_callees_do_not_fail_a_subset_match(self):
        # The source need only account for the calls it names; a callee it does
        # not name is not a contradiction.
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(),
                            edges=OUT + [(TARGET, "00777777", "direct-call")])
        self.assertEqual(report["static"]["checks"]["CALLS"]["status"], "PASS")

    def test_branch_words_inside_comments_do_not_create_a_claim(self):
        # The real false positive this guards: a straight-line machine body read
        # as branching because the word appeared in a comment.
        pack = _pack(disassembly=(True, {"instructions": [
            {"address": "00c0ffee", "instruction": "MOV EAX,0x7"},
            {"address": "00c0fff0", "instruction": "RET"}]}))
        body = ("  // loop for each port in the list, if it is open\n"
                "  return helper_00abcde1(3);")
        report = self.build(_span(body), pack, edges=OUT)
        self.assertIn("declares no branch", report["static"]["checks"]["CONTROL FLOW"]["detail"])

    def test_a_comment_constant_is_not_held_against_the_listing(self):
        pack = _pack(disassembly=(True, {"instructions": [
            {"address": "00c0ffee", "instruction": "MOV EAX,0x7"},
            {"address": "00c0fff0", "instruction": "RET"}]}))
        body = "  // see 0x202 for the sentinel\n  return helper_00abcde1(3);"
        report = self.build(_span(body), pack, edges=OUT)
        self.assertEqual(report["static"]["checks"]["CONSTANTS"]["status"], "NOT_AVAILABLE")

    def test_observed_mechanics_is_never_promoted_to_a_verdict(self):
        # observed_mechanics is a worker-authored transcript of the same read
        # that produced the source. Agreeing with it is internal consistency.
        report = self.build(_span("  return helper_00abcde1(0x5158);"), _pack(),
                            edges=OUT, mechanics=["the literal 0x5158 is read"])
        constants = report["static"]["checks"]["CONSTANTS"]
        self.assertEqual(constants["status"], "WARN")
        self.assertIn("not independent evidence", constants["detail"])

    def test_a_straight_line_body_with_no_dispatch_passes_that_check(self):
        pack = _pack(disassembly=(True, {"instructions": [
            {"address": "00c0ffee", "instruction": "MOV EAX,0x7"},
            {"address": "00c0fff0", "instruction": "RET"}]}))
        report = self.build(_span("  return helper_00abcde1(3);"), pack, edges=OUT)
        self.assertEqual(report["static"]["checks"]["VIRTUAL DISPATCH"]["status"], "PASS")


# --------------------------------------------------------------------------
# EVIDENCE COVERAGE is a measurement, scoped to the static axis.
# --------------------------------------------------------------------------
class EvidenceCoverageScope(DimensionFixture):

    def test_the_unavailable_runtime_category_is_out_of_the_denominator(self):
        pack = _pack(abi=_category(False), globals=_category(False), vtables=_category(False),
                     ghidra_function=_category(False), decompilation=_category(False),
                     disassembly=_category(False), runtime=_category(False))
        report = self.build(_span("  return helper_00abcde1(3);"), pack, edges=OUT)
        basis = report["static"]["evidence_basis"]
        # runtime is excluded, so the static total is the pack size minus one.
        self.assertEqual(basis["static_evidence_categories_total"], len(pack["categories"]) - 1)

    def test_runtime_availability_never_moves_the_static_verdict(self):
        """The coupling that made PASS unreachable: a reserved runtime slot that
        can never be available must not be able to veto a static verdict."""
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _pack(runtime=_category(False)), edges=OUT)
        self.assertEqual(report["runtime"]["status"], "GATED")
        self.assertEqual(report["static"]["status"], "PASS")

    def test_coverage_is_reported_but_never_sums_into_the_verdict(self):
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _pack(types=(True, ["Matrix3"])), edges=OUT, types=("Matrix3",))
        # Coverage is partial, so it WARNs -- and the aggregate is decided by the
        # eight static checks, not by the measurement. A coverage shortfall is a
        # fact about the campaign, not a defect in this reconstruction.
        self.assertEqual(report["static"]["evidence_coverage"]["status"], "WARN")
        self.assertEqual(report["static"]["status"], "PASS")

    def test_full_static_coverage_can_reach_pass_on_the_coverage_check(self):
        pack = _pack(abi=(True, {"calling_convention": "__cdecl"}),
                     types=(True, []), globals=(True, []), vtables=(True, []),
                     ghidra_function=(True, {}), decompilation=(True, ""),
                     disassembly=(True, {"instructions": []}))
        report = self.build(_span("  return helper_00abcde1(3);"), pack, edges=OUT)
        self.assertEqual(report["static"]["evidence_coverage"]["status"], "PASS")


# --------------------------------------------------------------------------
# Report shape compatibility.
# --------------------------------------------------------------------------
class ReportShape(DimensionFixture):

    def test_all_nine_checks_are_still_present(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        for name in ("ABI", "CALLS", "GLOBALS", "FIELDS/OFFSETS", "CONSTANTS",
                     "CONTROL FLOW", "VIRTUAL DISPATCH", "RETURN SEMANTICS",
                     "EVIDENCE COVERAGE"):
            self.assertIn(name, report["checks"])
        self.assertIn("status", report["static"]["evidence_coverage"])
        self.assertNotIn("EVIDENCE COVERAGE", report["static"]["checks"])

    def test_check_statuses_stay_inside_the_existing_alphabet(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        allowed = {"PASS", "WARN", "FAIL", "UNKNOWN", "NOT_AVAILABLE"}
        for name, check in report["checks"].items():
            self.assertIn(check["status"], allowed, name)

    def test_runtime_dimension_uses_its_own_alphabet(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        # NOT_AVAILABLE is deliberately not a runtime state: it means "a verdict
        # could not be reached" and would be indistinguishable from a category
        # that was searched and found empty.
        self.assertIn(report["runtime"]["status"], {"GATED", "PASS"})

    def test_legacy_aggregate_coverage_block_is_unchanged_in_shape(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        self.assertEqual(sorted(report["coverage"]),
                         ["attempted", "not_available", "pass", "ratio", "total", "unknown", "warn"])
        self.assertEqual(report["coverage"]["total"], len(report["checks"]))


# --------------------------------------------------------------------------
# Runtime evidence collection must not claim a search it never did.
# --------------------------------------------------------------------------
class RuntimeCategoryHonesty(DimensionFixture):

    def test_the_runtime_slot_says_it_was_never_searched(self):
        from tools.reconstruction_tooling.evidence import _record_categories
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        index, _ = build_index(self.root)
        categories = _record_categories(index["records"][TARGET], index, self.root)
        runtime = categories["runtime"]
        self.assertEqual(runtime["availability"], "unavailable")
        self.assertIsNone(runtime["value"])
        self.assertNotEqual(runtime["reason"], "no exact source evidence found")
        self.assertIn("never searched", runtime["reason"])
        self.assertEqual(report["runtime"]["status"], "GATED")

    def test_the_gates_travel_in_runtime_metadata_not_in_the_reserved_slot(self):
        from tools.reconstruction_tooling.evidence import _record_categories
        self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        index, _ = build_index(self.root)
        categories = _record_categories(index["records"][TARGET], index, self.root)
        self.assertEqual(categories["runtime_metadata"]["availability"], "available")
        self.assertEqual(categories["runtime_metadata"]["value"]["validated"], 0)
        self.assertIsNone(categories["runtime"]["value"])


if __name__ == "__main__":
    unittest.main()
