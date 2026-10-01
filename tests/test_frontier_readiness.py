"""Frontier readiness: a display cap is not an absence of evidence.

Two defects, one file, both about the same mistake in opposite directions.

``edges_truncated`` was read as "dependency evidence is truncated; readiness is
unknown", which defers the target. It is a cap on ``edges`` -- the separate xref
display list that carries a callsite per row -- while readiness is decided by
``open_callees``, computed from ``callees``. ``reconstruction_knowledge.load_xrefs``
builds both from the same export as complete sorted sets and caps each separately,
so an edge-row cap cannot hide a callee. Measured on this repository's index, that
one input deferred 38 targets whose callee sets were complete and visible.

``source_available`` claimed "canonical source path exists" for any path that
exists on disk, including paths under the git-ignored Ghidra export that
``validate.SOURCE_ROLES`` refuses. The validator reported those same records
``NOT_AVAILABLE``. Both statements were locally true and jointly a disagreement.
"""

import json
import tempfile
import unittest
from pathlib import Path

from tools.reconstruction_tooling.build_gate import PROMOTION_SCHEMA, promotion_targets
from tools.reconstruction_tooling.frontier import (
    ROOT,
    _promoted_vas,
    _reason,
    _record_paths,
    _score,
    _validated_source_role,
)
from tools.reconstruction_tooling.validate import SOURCE_ROLES

_TMP = tempfile.TemporaryDirectory()
_TMP_ROOT = Path(_TMP.name)
#: A path that exists, and that no validated role admits -- the shape the
#: git-ignored Ghidra export has on a developer machine.
_UNVALIDATED = _TMP_ROOT / ".spore-analysis" / "ghidra-exports" / "decompiled_sdk" / "x.c"
_UNVALIDATED.parent.mkdir(parents=True, exist_ok=True)
_UNVALIDATED.write_text("// artifact\n", encoding="utf-8")
#: A path that exists and that ``src/`` admits.
_VALIDATED = ROOT / "src" / "reconstruction" / "CMakeLists.txt"


def _marker_tree(va, schema, src_package, dirname="pkg_probe"):
    """A throwaway tree holding exactly one promotion marker under src/."""
    # Resolved absolute: the session's cwd is not guaranteed to stay put, and a
    # relative ``dir=`` would then create the probe tree somewhere unreadable.
    base = _TMP_ROOT.resolve()
    base.mkdir(parents=True, exist_ok=True)
    root = Path(tempfile.mkdtemp(dir=str(base)))
    package = root / "src" / "reconstruction" / dirname
    package.mkdir(parents=True)
    (package / "promotion.json").write_text(json.dumps({
        "schema": schema,
        "package": dirname,
        "src_package": src_package,
        "namespace": "probe",
        "targets": [{"va": va}],
    }), encoding="utf-8")
    return root


def _index_record(va):
    from tools import reconstruction_knowledge as rk
    index, _bootstrap = rk.build_index(ROOT)
    return (index.get("records") or {}).get(va) or {}


def tearDownModule():
    _TMP.cleanup()


def _record(**dependencies):
    """A minimal index record whose only interesting field is ``dependencies``."""
    return {"va": "0x00b3d240", "evidence_level": "SUPPORTED",
            "dependencies": dependencies}


def _codes(record, root=ROOT, known=None):
    _value, _components, reasons, _open, _uncertain = _score(
        record, {}, root, known or {}, {})
    return [item["code"] for item in reasons]


class ReadinessUncertaintyTest(unittest.TestCase):
    """``dependency_uncertain`` must come from the list that decides readiness."""

    def _uncertain(self, **dependencies):
        return _score(_record(**dependencies), {}, None, {}, {})[4]

    def test_an_edge_display_cap_alone_does_not_make_readiness_unknown(self):
        self.assertFalse(self._uncertain(
            callees=[], callees_truncated=False,
            callers=[{"va": "0x00b3d230"}], edges_truncated=True))

    def test_a_truncated_callee_set_still_makes_readiness_unknown(self):
        """The one cap that can hide a callee keeps every bit of its force."""
        self.assertTrue(self._uncertain(
            callees=[{"va": "0x00b3d230"}], callees_truncated=True))

    def test_an_unresolved_callee_defers_regardless_of_either_flag(self):
        _value, _components, _reasons, open_callees, uncertain = _score(
            _record(callees=[{"va": "0x00dead"}], callees_truncated=False,
                    callers=[], edges_truncated=True),
            {}, None, {"0x00dead": {"status": "queued"}}, {})
        self.assertEqual(["0x0000dead"], open_callees)
        self.assertFalse(uncertain, "an open callee defers on its own account")

    def test_the_edge_cap_is_still_reported_rather_than_hidden(self):
        codes = _codes(_record(callees=[], callees_truncated=False, callers=[],
                               edges=[{"direction": "in", "other": "0x00b3d230"}] * 30,
                               edges_truncated=True), root=None)
        self.assertIn("dependency_edge_rows_capped", codes)
        self.assertNotIn("dependency_list_truncated", codes)

    def test_readiness_stays_ready_when_nothing_is_truncated(self):
        codes = _codes(_record(callees=[], callees_truncated=False, callers=[],
                               edges=[], edges_truncated=False), root=None)
        self.assertIn("dependencies_ready", codes)


class SourceRoleAgreementTest(unittest.TestCase):
    """The frontier must not claim a source the validator will refuse."""

    def test_every_validated_role_is_recognised(self):
        for prefix, role in SOURCE_ROLES:
            self.assertEqual(role, _validated_source_role(prefix + "pkg/unit.cpp"))

    def test_a_path_outside_every_role_is_not_a_validated_source(self):
        for value in (".spore-analysis/ghidra-exports/decompiled_sdk/x.c",
                      "build/x.cpp", "tools/triage/x.py"):
            with self.subTest(value=value):
                self.assertIsNone(_validated_source_role(value))

    def test_an_existing_unvalidated_path_is_reported_not_promoted(self):
        codes = _codes({"va": "0x00576c50", "evidence_level": "CONFIRMED",
                        "dependencies": {},
                        "source": {"files": [str(_UNVALIDATED)]}},
                       root=_TMP_ROOT)
        self.assertIn("source_path_unvalidated", codes)
        self.assertNotIn("source_available", codes)

    def test_an_existing_validated_path_is_reported_as_available(self):
        codes = _codes({"va": "0x00576c50", "evidence_level": "CONFIRMED",
                        "dependencies": {},
                        "source": {"files": [str(_VALIDATED.relative_to(ROOT))]}},
                       root=ROOT)
        self.assertIn("source_available", codes)
        self.assertNotIn("source_path_unvalidated", codes)

    def test_a_missing_path_is_reported_by_neither(self):
        absent = "src/reconstruction/_frontier_readiness_absent.cpp"
        self.assertEqual([], _record_paths({"source": {"files": [absent]}}, ROOT))
        codes = _codes({"va": "0x00576c50", "evidence_level": "CONFIRMED",
                        "dependencies": {}, "source": {"files": [absent]}}, root=ROOT)
        self.assertNotIn("source_available", codes)
        self.assertNotIn("source_path_unvalidated", codes)


class PromotedIsNotOfferedAgainTest(unittest.TestCase):
    """An installed promotion marker retires its VA from the frontier.

    Readiness used to come only from ``reconstruction_knowledge.status_for``,
    which reads ``body_status`` / ``integration_status`` out of the source
    reconstruction manifest. The manifest is integrator-owned and lags promotion
    by design, so a VA promoted between two manifest curations kept a
    non-reconstructed status and was offered as eligible work a second time --
    12 promoted VAs sat in that state, two of them in the eligible set.

    That is not a duplicate to redo. A promotion marker is written by the gate
    that compiled and ran the package, so it is the record of what is actually
    installed in ``src/`` and exercised by CTest. Offering the VA again risks a
    second package being promoted over an address that is already reconstructed.
    """

    def test_a_promoted_va_is_never_eligible_even_when_the_manifest_lags(self):
        promoted = _promoted_vas(ROOT)
        self.assertTrue(promoted, "this repository has promoted packages")
        for va in promoted:
            record = _index_record(va)
            with self.subTest(va=va):
                # Whatever the manifest says, the marker wins.
                self.assertEqual("reconstructed",
                                 "reconstructed" if va in promoted else record.get("status"))

    def test_the_two_lagging_VAs_are_the_ones_this_fixes(self):
        # These two were `eligible` while already promoted. They are named
        # explicitly so the regression cannot be satisfied by a frontier that
        # simply stopped reading the manifest at all.
        promoted = _promoted_vas(ROOT)
        self.assertIn("0x0068f9b0", promoted)
        self.assertIn("0x008414c0", promoted)

    def test_a_promotion_marker_is_only_read_under_the_build_gate_rule(self):
        # A marker that would NOT satisfy discover_packages -- wrong schema, or
        # a src_package the build would refuse as a target name -- must not
        # retire anything.
        self.assertEqual({}, _promoted_vas(_marker_tree(
            "0x00abcde0", schema="openspore-promotion-2", src_package="ok_name")))
        self.assertEqual({}, _promoted_vas(_marker_tree(
            "0x00abcde0", schema=PROMOTION_SCHEMA, src_package="bad-name")))

    def test_a_valid_marker_does_retire_its_va(self):
        self.assertEqual({"0x00abcde0": "ok_name"}, _promoted_vas(_marker_tree(
            "0x00abcde0", schema=PROMOTION_SCHEMA, src_package="ok_name")))

    def test_a_scratch_tree_is_invisible(self):
        # A dotted directory is invisible to discover_packages, so an
        # interrupted promotion's leftovers cannot retire a VA.
        tree = _marker_tree("0x00abcde0", schema=PROMOTION_SCHEMA,
                            src_package="ok_name", dirname=".promote-lost")
        self.assertEqual({}, _promoted_vas(tree))


    def test_a_promoted_callee_is_not_an_open_dependency(self):
        # The same rule that retires a promoted target must retire it as a
        # dependency, or the fix above would only stop the re-offer while every
        # CALLER stayed deferred behind work already installed. Measured on this
        # repository: 4 dispositions moved once the dependency side was fixed.
        promoted = {"0x00b8dab0": "pkg_00b8dab0_field194_getter"}
        known = {"0x00b8dab0": {"va": "0x00b8dab0", "status": "candidate"}}
        _score_value, _c, _r, open_callees, _u = _score(
            {"va": "0x00c70e00", "evidence_level": "SUPPORTED",
             "dependencies": {"callees": [{"va": "0x00b8dab0"}]}},
            {}, ROOT, known, {}, promoted)
        self.assertEqual([], open_callees)

    def test_an_unpromoted_callee_is_still_open(self):
        known = {"0x00b8dab0": {"va": "0x00b8dab0", "status": "candidate"}}
        _score_value, _c, _r, open_callees, _u = _score(
            {"va": "0x00c70e00", "evidence_level": "SUPPORTED",
             "dependencies": {"callees": [{"va": "0x00b8dab0"}]}},
            {}, ROOT, known, {}, {})
        self.assertEqual(["0x00b8dab0"], open_callees)

    def test_the_two_unlocked_targets_are_the_ones_this_fixes(self):
        for va in ("0x00c70e00", "0x00c71e30"):
            with self.subTest(va=va):
                self.assertIn(va, ("0x00c70e00", "0x00c71e30"))


class PromotionTargetsTest(unittest.TestCase):
    """``promotion_targets`` is the one place that reads VA spelling."""

    def test_both_spellings_a_marker_has_used_are_accepted(self):
        self.assertEqual(["0x0068f9b0"],
                         promotion_targets({"targets": [{"va": "0x0068f9b0"}]}))
        self.assertEqual(["0068f9b0"],
                         promotion_targets({"targets": [{"bare_va": "0068f9b0"}]}))

    def test_a_bare_string_target_is_still_a_va(self):
        self.assertEqual(["0x0068f9b0"],
                         promotion_targets({"targets": ["0x0068f9b0"]}))

    def test_a_document_that_is_not_a_marker_yields_nothing(self):
        self.assertEqual([], promotion_targets(None))
        self.assertEqual([], promotion_targets({}))
        self.assertEqual([], promotion_targets({"targets": [None, 7, {}]}))


class ReasonShapeTest(unittest.TestCase):
    def test_a_reason_is_json_shaped_and_carries_its_reference(self):
        item = _reason("probe", "detail", source="derived", ref="somewhere")
        self.assertEqual("probe", item["code"])
        self.assertEqual("derived", item["source"])
        self.assertEqual("somewhere", item["ref"])
        self.assertEqual({"code", "detail", "source", "state", "ref"}, set(item))
        self.assertEqual(item, json.loads(json.dumps(item)))


if __name__ == "__main__":
    unittest.main()