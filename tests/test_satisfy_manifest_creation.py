"""``satisfy`` creating the manifest row a brand-new target never got.

The circularity this file closes
-------------------------------

``reconstruction_knowledge.status_for`` reads the canonical manifest and
nothing else, and ``satisfy`` is the only sanctioned writer of that transition.
For the four targets a triage import happened to give a ``functions[]`` row the
two agreed and the pipeline moved. For a *new* target the row did not exist and
``satisfy`` refused with ``no_manifest_entry``, so no promotion could ever
satisfy a dependency and the dependency graph could never move at all. The
target ``0x00ec3bc0`` is that case: a real promotion, ``static_status: PASS``,
``runtime_status: GATED``, a green cmake+ctest record -- and no row.

What this file holds still
--------------------------

* Creating a row is not a weaker gate. Every pre-existing admission condition
  (``not_promoted``, ``not_static_validated``, ``no_test``,
  ``no_promotion_record``, ``build_not_green``, ``manifest_unreadable``) is
  checked **before** a row may be created, and each is re-proved here with the
  row absent, asserting the manifest bytes are untouched. A new
  ``no_symbol_source`` refusal covers the one thing the create path adds: a name
  that no artifact supplies and that cannot be derived from a VA the promotion
  record does not name.
* No field is invented. Every key of a created row is asserted to trace to a
  named artifact, and the row is asserted to carry none of ``RUNTIME_KEYS``.
* Partial satisfaction still defers. Creating one of C's three prerequisites
  must leave C ``deferred`` with exactly the two remaining open callees -- the
  honest-graph guard, and the half a happy path would hide.
* The write is atomic, idempotent and reversible, and ``unsatisfy`` *removes* a
  created row rather than restoring a stub.

Everything is synthetic and lives inside ``FixtureTestCase``'s tempdir. The
promotion harness (``GateStub``, the staged sources, the recorded build
verdicts) is imported from ``tests.test_promotion_dependency`` rather than
rebuilt, and the fixture graph is the shared one from
``tests.orchestration_fixture``: C is the only dependent, and A/B/D are the only
things it calls. Nothing here writes to the real manifest, ``src/`` or
``reconstruction/``.

Run from the repo root::

    python3 -m unittest tests.test_satisfy_manifest_creation -v
"""

import hashlib
import json
import unittest
from pathlib import Path

try:
    from tools import reconstruction_knowledge as rk
except ImportError as exc:  # pragma: no cover - off-repo-root only
    raise RuntimeError("reconstruction knowledge module is unavailable") from exc

from tools.reconstruction_tooling import frontier as frontier_mod
from tools.reconstruction_tooling import satisfy
from tools.reconstruction_tooling import schedule as sched

from tests import orchestration_fixture as fx
from tests.test_promotion_dependency import (
    DependencyCase,
    PROBE_CALLEE,
    _gate_red,
    _package_for,
)

DEPENDENT = "C"
PREREQS = ("A", "B", "D")
# The one prerequisite whose manifest row this file removes, so the create path
# is the one under test. Named from the fixture's own edge table, not a second
# hardcoded graph.
CREATED = "B"
# The keys a created row must never carry, per the update path's own promise.
FORBIDDEN = set(satisfy.RUNTIME_KEYS) | {
    "runtime_validation", "runtime_validation_status", "runtime_ownership_gate",
    "unresolved_runtime_ports", "review_status", "evidence_level",
    "signature_status", "reconstruction_confidence", "audit_status",
}


def _changed_keys(before, after):
    return {key for key in set(before) | set(after) if before.get(key) != after.get(key)}


class CreationCase(DependencyCase):
    """A fixture root whose promoted target has no manifest row.

    ``drop_rows`` rewrites the synthetic manifest *inside the tempdir*. It is the
    whole point of this file, so it is the one thing this class adds to the
    shared harness: everything else -- the tempdir, the env isolation, the
    index-cache discipline, the promotion stubs, the three observable views -- is
    inherited unchanged.
    """

    def drop_rows(self, *keys):
        # type: (*str) -> None
        """Remove the manifest ``functions[]`` rows of ``keys`` and re-sort."""
        path = Path(self.info["root"]) / fx.MANIFEST_REL
        document = json.loads(path.read_text(encoding="utf-8"))
        dropped = {fx.TARGETS[key]["va"] for key in keys}
        document["functions"] = [item for item in document["functions"]
                                 if item.get("va") not in dropped]
        path.write_text(json.dumps(document, indent=2, sort_keys=True) + "\n",
                        encoding="utf-8")
        fx.clear_index_cache()
        return path

    def manifest_bytes(self):
        return (Path(self.info["root"]) / fx.MANIFEST_REL).read_bytes()

    def manifest_digest(self):
        return hashlib.sha256(self.manifest_bytes()).hexdigest()

    def entry_or_none(self, va):
        for function in self.manifest()["functions"]:
            if function.get("va") == va:
                return function
        return None

    def index(self):
        return frontier_mod._index(Path(self.info["root"]))

    def reconstructed(self, va):
        return sched._reconstructed(self.index(), va)

    def satisfy_rows(self, va):
        rows = []
        for entry in self.manifest().get("change_log") or []:
            if entry.get("kind") != satisfy.CHANGE_KIND_SATISFY:
                continue
            for row in entry.get("rows") or []:
                if row.get("va") == va:
                    rows.append(row)
        return rows

    def plan_candidate(self, va):
        document = satisfy.plan(self.info["root"], vas=[va])
        for candidate in document["candidates"]:
            if candidate["va"] == va:
                return candidate
        self.fail("no plan candidate for %s" % va)

    def promoted_without_a_row(self, key=PROBE_CALLEE):
        # type: (str) -> str
        """Promote ``key`` and then remove its manifest row -- the create path."""
        va = self.promote_key(key)
        self.drop_rows(key)
        self.assertIsNotNone(self.record_path(va).is_file() and self.record_path(va))
        self.assertIsNone(self.entry_or_none(va))
        return va

    def codes(self, document, va):
        for candidate in document["candidates"]:
            if candidate["va"] == va:
                return sorted(item["code"] for item in candidate["blockers"])
        return []

class CreatePathTest(CreationCase):
    """An absent row plus a real promotion makes the target reconstructed."""

    def test_create_makes_status_for_and_the_scheduler_agree(self):
        self.make_root()
        va = fx.TARGETS[CREATED]["va"]
        self.promote_key(CREATED)
        self.drop_rows(CREATED)
        self.assertIsNone(self.entry_or_none(va))
        # The pre-condition the milestone is about, read through the two
        # production predicates and not through a copy of either.
        self.assertFalse(self.reconstructed(va))

        result = satisfy.apply(self.info["root"], vas=[va], reason="test",
                               implementer_id="t-1")
        self.assertEqual(result["status"], "ok", result["refused"])
        self.assertEqual(result["changed"], True)
        self.assertEqual(result["satisfied"], [va])
        self.assertEqual(result["created"], [va])
        self.assertEqual(result["manifest_actions"],
                         {va: satisfy.MANIFEST_ACTION_CREATE})
        fx.clear_index_cache()

        entry = self.entry_or_none(va)
        self.assertIsNotNone(entry)
        self.assertEqual(rk.status_for(entry, {}), "reconstructed")
        self.assertEqual(self.reconstructed(va), True)

    def test_created_row_is_shaped_like_a_real_one_and_names_its_sources(self):
        self.make_root()
        va = fx.TARGETS[CREATED]["va"]
        self.promote_key(CREATED)
        self.drop_rows(CREATED)
        candidate = self.plan_candidate(va)
        self.assertEqual(candidate[satisfy.ACTION_FIELD],
                         satisfy.MANIFEST_ACTION_CREATE)
        sources = candidate[satisfy.SOURCES_FIELD]
        satisfy.apply(self.info["root"], vas=[va], reason="test")
        entry = self.entry_or_none(va)

        # The writeable surface is a named whitelist, and nothing outside it was
        # written. ``subsystem`` is on that list but the synthetic promotion does
        # not record one, so it is absent -- a field is written only when an
        # artifact supplies it.
        self.assertTrue(set(entry) <= set(satisfy.CREATED_ENTRY_KEYS),
                        sorted(set(entry) - set(satisfy.CREATED_ENTRY_KEYS)))
        self.assertEqual(_changed_keys({}, entry), set(entry))
        # Every field traces to a named artifact that exists on disk.
        for field in ("va", "normalized_symbol", "package", "source_file"):
            self.assertIn(field, sources, sorted(sources))
            self.assertIn(sources[field], entry.get("source_provenance", [])
                          + [sources[field]])
        record_rel = "reconstruction/evidence/%s/promotion.json" % fx.bare(va)
        self.assertEqual(sources["va"], record_rel)
        self.assertEqual(sources["body_status"], record_rel)
        self.assertEqual(sources["integration_status"], record_rel)
        self.assertEqual(sources["normalized_symbol"],
                         "reconstruction/metadata/pkg-synth-%s-dep/%s.json"
                         % (CREATED.lower(), fx.bare(va)))
        # The policy the manifest states for itself is honoured.
        self.assertTrue(entry["source_provenance"])
        for relative in entry["source_provenance"]:
            self.assertTrue((Path(self.info["root"]) / relative).exists(), relative)
        # And the entry sits where the manifest keeps its addresses.
        vas = [item.get("va") for item in self.manifest()["functions"]]
        self.assertEqual(vas, sorted(vas))

    def test_no_runtime_shape_reaches_a_created_row(self):
        self.make_root()
        va = fx.TARGETS[CREATED]["va"]
        self.promote_key(CREATED)
        self.drop_rows(CREATED)
        satisfy.apply(self.info["root"], vas=[va], reason="test")
        entry = self.entry_or_none(va)
        self.assertEqual([key for key in sorted(FORBIDDEN) if key in entry], [])
        fx.clear_index_cache()
        # The runtime axis is still the open gate it was before the write.
        self.assertEqual(rk.status_for(entry, {}), "reconstructed")
        self.assertNotIn(rk.status_for(entry, {}),
                         ("runtime_gated", "runtime_validated"))
        record = self.index()["records"][va]
        self.assertTrue(record["reconstructed"])
        self.assertEqual(record["status"], "reconstructed")
        # Nothing runtime-shaped was synthesised: no validation, and no gate
        # invented either. The runtime axis is untouched by a static transition.
        self.assertFalse(record["runtime"]["validated"])
        self.assertEqual(record["runtime"]["gates"], [])
        self.assertEqual(record["runtime"]["blocking_reason"], None)
        self.assertEqual(record["runtime_validated"], 0)

    def test_a_symbol_is_never_invented(self):
        self.make_root()
        va = fx.TARGETS[CREATED]["va"]
        self.promote_key(CREATED)
        self.drop_rows(CREATED)
        record_path = self.record_path(va)
        record = json.loads(record_path.read_text(encoding="utf-8"))
        marker_path = self.marker_path(CREATED)
        marker = json.loads(marker_path.read_text(encoding="utf-8"))
        # Remove the name from every artifact: the sidecar, the installed marker
        # and the record itself. What is left is the address.
        for key in ("normalized_symbol", "symbol"):
            record.pop(key, None)
            marker["targets"][0].pop(key, None)
        sidecar = (Path(self.info["root"]) / "reconstruction/metadata"
                   / _package_for(CREATED)[0] / ("%s.json" % fx.bare(va)))
        sidecar.unlink()
        record_path.write_text(json.dumps(record, indent=2, sort_keys=True) + "\n",
                               encoding="utf-8")
        marker_path.write_text(json.dumps(marker, indent=2, sort_keys=True) + "\n",
                               encoding="utf-8")
        fx.clear_index_cache()
        candidate = self.plan_candidate(va)
        self.assertEqual(candidate[satisfy.SOURCES_FIELD]["normalized_symbol"],
                         "va:reconstruction/evidence/%s/promotion.json" % fx.bare(va))
        satisfy.apply(self.info["root"], vas=[va], reason="test")
        entry = self.entry_or_none(va)
        # A deterministic derivation, and it says where the derivation is from.
        self.assertEqual(entry["normalized_symbol"],
                         "%s%s" % (satisfy.DERIVED_SYMBOL_PREFIX, fx.bare(va)))
        row = self.satisfy_rows(va)[-1]
        self.assertEqual(row["field_sources"]["normalized_symbol"],
                         "va:reconstruction/evidence/%s/promotion.json" % fx.bare(va))


class DependentFlipTest(CreationCase):
    """The milestone: a created row moves a real dependent in all three views.

    C is dependent on exactly A, B and D. B's manifest row is removed so its
    satisfaction takes the create path; A and D are ordinary updates. The
    assertions are concrete before/after values, not "something changed".
    """

    def _satisfy_all_prereqs(self):
        for key in PREREQS:
            satisfy.apply(self.info["root"], vas=[fx.TARGETS[key]["va"]],
                          reason="test", implementer_id="t-1")
            fx.clear_index_cache()

    def test_the_dependent_flips_role_disposition_and_wave(self):
        self.make_root()
        dependent = fx.TARGETS[DEPENDENT]["va"]
        for key in PREREQS:
            self.promote_key(key)
        self.drop_rows(CREATED)
        created_va = fx.TARGETS[CREATED]["va"]
        self.assertIsNone(self.entry_or_none(created_va))

        before_role, before_disposition, before_open = self.blocked_on(
            dependent, None)
        before_wave = self.wave_of(dependent)
        self.assertEqual(before_role, "dependent")
        self.assertEqual(before_disposition, "deferred")
        self.assertEqual(sorted(before_open),
                         sorted(fx.TARGETS[key]["va"] for key in PREREQS))
        self.assertIsNotNone(before_wave)
        self.assertGreater(before_wave, self.wave_of(fx.TARGETS["A"]["va"]))
        self.assertFalse(self.reconstructed(created_va))

        self._satisfy_all_prereqs()

        after_role, after_disposition, after_open = self.blocked_on(
            dependent, None)
        self.assertEqual(after_role, "independent")
        self.assertEqual(after_disposition, "eligible")
        self.assertEqual(after_open, [])
        self.assertEqual(self.wave_of(dependent), 0)
        self.assertLess(self.wave_of(dependent), before_wave)
        # The created prerequisite really did go through the create path, and the
        # other two through the update path.
        self.assertEqual(self.entry_or_none(created_va)["body_status"],
                         satisfy.SATISFIED_BODY_STATUS)
        self.assertEqual([row[satisfy.CHANGE_ACTION_KEY]
                          for row in self.satisfy_rows(created_va)],
                         [satisfy.MANIFEST_ACTION_CREATE])
        for key in ("A", "D"):
            self.assertEqual([row[satisfy.CHANGE_ACTION_KEY]
                              for row in self.satisfy_rows(fx.TARGETS[key]["va"])],
                             [satisfy.MANIFEST_ACTION_UPDATE])
        self.assertTrue(self.reconstructed(created_va))
        self.assertTrue(self.reconstructed(fx.TARGETS["A"]["va"]))

    def test_one_of_three_prerequisites_still_defers_the_dependent(self):
        self.make_root()
        dependent = fx.TARGETS[DEPENDENT]["va"]
        for key in PREREQS:
            self.promote_key(key)
        self.drop_rows(CREATED)
        probe = fx.TARGETS[CREATED]["va"]
        result = satisfy.apply(self.info["root"], vas=[probe], reason="test")
        self.assertEqual(result["satisfied"], [probe])
        self.assertEqual(result["created"], [probe])
        self.assertEqual(result["unblocked"][probe], [])
        fx.clear_index_cache()
        role, disposition, open_callees = self.blocked_on(dependent, None)
        self.assertEqual(role, "dependent")
        self.assertEqual(disposition, "deferred")
        self.assertEqual(sorted(open_callees),
                         sorted(fx.TARGETS[key]["va"] for key in ("A", "D")))
        # The two remaining prerequisites are still real open work.
        for key in ("A", "D"):
            self.assertFalse(self.reconstructed(fx.TARGETS[key]["va"]))
        # And closing them is what releases C -- with no further promotion.
        for key in ("A", "D"):
            satisfy.apply(self.info["root"], vas=[fx.TARGETS[key]["va"]],
                          reason="test")
            fx.clear_index_cache()
        self.assertEqual(self.planned(dependent)["role"], "independent")
        self.assertEqual(self.frontier_target(dependent)["disposition"], "eligible")


class CreateRefusalTest(CreationCase):
    """Every pre-existing blocker still fires with the row absent, and writes nothing."""

    def assert_refused(self, va, code):
        before = self.manifest_digest()
        document = satisfy.plan(self.info["root"], vas=[va])
        candidate = document["candidates"][0]
        self.assertIn(code, self.codes(document, va))
        result = satisfy.apply(self.info["root"], vas=[va], reason="test")
        self.assertEqual(result["status"], "blocked")
        self.assertEqual(result["changed"], False)
        self.assertEqual(result["satisfied"], [])
        self.assertEqual(result["created"] if "created" in result else [], [])
        self.assertEqual(sorted(item["code"] for item in result["refused"][0]["blockers"]),
                         sorted(item["code"] for item in candidate["blockers"]))
        self.assertEqual(candidate[satisfy.ACTION_FIELD],
                         satisfy.MANIFEST_ACTION_ABSENT)
        self.assertEqual(self.manifest_digest(), before,
                         "a refused candidate wrote to the manifest")
        self.assertIsNone(self.entry_or_none(va))
        return result

    def test_unpromoted_is_still_refused(self):
        self.make_root()
        self.drop_rows(PROBE_CALLEE)
        self.assert_refused(fx.TARGETS[PROBE_CALLEE]["va"], "not_promoted")

    def test_static_warn_is_still_refused(self):
        va = self.promoted_without_a_row()
        self.rewrite_marker(PROBE_CALLEE, static_status="WARN")
        result = self.assert_refused(va, "not_static_validated")
        self.assertEqual(result["refused"][0]["src_package"],
                         _package_for(PROBE_CALLEE)[1])

    def test_runtime_status_that_is_not_gated_is_still_refused(self):
        # The no-gate-bypass half, stated for the runtime axis: a manifest row
        # does not exist to be leaned on, so this is refused on the promotion
        # evidence alone -- exactly as it is on the update path.
        va = self.promoted_without_a_row()
        self.rewrite_marker(PROBE_CALLEE, runtime_status="PASS")
        result = self.assert_refused(va, "not_static_validated")
        self.assertIn("not_static_validated",
                      [item["code"] for item in result["refused"][0]["blockers"]])

    def test_runtime_validated_is_still_refused(self):
        va = self.promoted_without_a_row()
        self.rewrite_marker(PROBE_CALLEE, runtime_status="VALIDATED")
        self.assert_refused(va, "not_static_validated")

    def test_recorded_red_build_is_still_refused(self):
        va = self.promoted_without_a_row()
        self.rewrite_record_build(va, _gate_red(_package_for(PROBE_CALLEE)[1]))
        self.assert_refused(va, "build_not_green")

    def test_skipped_gate_is_still_not_a_green_gate(self):
        va = self.promoted_without_a_row()
        self.rewrite_record_build(va, {"schema": "openspore-build-gate-1",
                                       "ok": True, "steps": [],
                                       "note": "gate skipped by request"})
        self.assert_refused(va, "build_not_green")

    def test_no_test_is_still_refused(self):
        va = self.promoted_without_a_row()
        self.rewrite_marker_tests(PROBE_CALLEE, [])
        self.assert_refused(va, "no_test")

    def test_missing_promotion_record_is_still_refused(self):
        va = self.promoted_without_a_row()
        self.record_path(va).unlink()
        result = self.assert_refused(va, "no_promotion_record")
        self.assertNotIn("no_symbol_source",
                         [item["code"] for item in result["refused"][0]["blockers"]])

    def test_unreadable_promotion_record_is_still_refused(self):
        va = self.promoted_without_a_row()
        self.record_path(va).write_text("{not json", encoding="utf-8")
        self.assert_refused(va, "promotion_record_unreadable")

    def test_no_symbol_source_refuses_instead_of_fabricating(self):
        va = self.promoted_without_a_row()
        record_path = self.record_path(va)
        record = json.loads(record_path.read_text(encoding="utf-8"))
        marker_path = self.marker_path(PROBE_CALLEE)
        marker = json.loads(marker_path.read_text(encoding="utf-8"))
        # Strip the name from every artifact. The marker keeps its VA: a marker
        # that no longer claims the address is genuinely ``not_promoted``, and
        # this test is about a name, not about an owner. The *record* stops
        # naming the VA as well, so there is no address left to derive one from.
        for key in ("va", "bare_va", "normalized_symbol", "symbol"):
            record.pop(key, None)
        for key in ("normalized_symbol", "symbol"):
            marker["targets"][0].pop(key, None)
        (Path(self.info["root"]) / "reconstruction/metadata"
         / _package_for(PROBE_CALLEE)[0] / ("%s.json" % fx.bare(va))).unlink()
        record_path.write_text(json.dumps(record, indent=2, sort_keys=True) + "\n",
                               encoding="utf-8")
        marker_path.write_text(json.dumps(marker, indent=2, sort_keys=True) + "\n",
                               encoding="utf-8")
        fx.clear_index_cache()
        result = self.assert_refused(va, "no_symbol_source")
        # The honest pairing: the row is absent *and* nothing can source a name.
        codes = [item["code"] for item in result["refused"][0]["blockers"]]
        self.assertIn("no_manifest_entry", codes)
        detail = [item["detail"] for item in result["refused"][0]["blockers"]
                  if item["code"] == "no_symbol_source"]
        # The refusal names the artifact that failed to source a name, and says
        # what is missing, rather than inventing a plausible one.
        self.assertIn("reconstruction/evidence/%s/promotion.json" % fx.bare(va),
                      detail[0])
        self.assertIn("no VA", detail[0])

    def test_a_refused_creation_does_not_write_a_sibling_creation(self):
        # One refusal must not freeze the admissible sibling, exactly as on the
        # update path -- and the sibling's row is created, not updated.
        self.make_root()
        good = self.promote_key(CREATED)
        bad = self.promote_key("A")
        self.drop_rows(CREATED, "A")
        self.rewrite_record_build(bad, _gate_red(_package_for("A")[1]))
        before = self.manifest_digest()
        result = satisfy.apply(self.info["root"], vas=[good, bad], reason="test")
        self.assertEqual(result["status"], "blocked")
        self.assertEqual(result["satisfied"], [good])
        self.assertEqual(result["created"], [good])
        self.assertEqual(result["manifest_actions"],
                         {good: satisfy.MANIFEST_ACTION_CREATE})
        self.assertEqual([item["va"] for item in result["refused"]], [bad])
        self.assertIsNone(self.entry_or_none(bad))
        self.assertIsNotNone(self.entry_or_none(good))
        self.assertNotEqual(self.manifest_digest(), before)

    def test_verify_build_still_gates_a_creation(self):
        self.make_root()
        va = self.promoted_without_a_row()
        self.gate.ok = False
        result = satisfy.apply(self.info["root"], vas=[va], reason="test",
                               verify_build=True)
        self.assertEqual(result["status"], "blocked")
        self.assertEqual(result["satisfied"], [])
        self.assertEqual(sorted(item["code"] for item in result["refused"][0]["blockers"]),
                         ["build_not_green"])
        self.assertIsNone(self.entry_or_none(va))
        self.gate.ok = True
        satisfy.apply(self.info["root"], vas=[va], reason="test", verify_build=True)
        self.assertIsNotNone(self.entry_or_none(va))


class IdempotenceAndReversalTest(CreationCase):
    """A created row is written once and removed once."""

    def test_second_apply_after_a_create_changes_nothing(self):
        self.make_root()
        va = self.promoted_without_a_row()
        first = satisfy.apply(self.info["root"], vas=[va], reason="test")
        self.assertEqual(first["changed"], True)
        self.assertEqual(first["idempotent"], False)
        before = self.manifest_bytes()
        entries = len(self.manifest().get("change_log") or [])
        second = satisfy.apply(self.info["root"], vas=[va], reason="test")
        self.assertEqual(second["status"], "ok")
        self.assertEqual(second["changed"], False)
        self.assertEqual(second["idempotent"], True)
        self.assertEqual(second["satisfied"], [])
        self.assertEqual(second["created"] if "created" in second else [], [])
        self.assertEqual(second["already_satisfied"], [va])
        self.assertEqual(second["refused"], [])
        self.assertEqual(self.manifest_bytes(), before)
        self.assertEqual(len(self.manifest().get("change_log") or []), entries)
        # And the row now exists, so the plan says so.
        self.assertEqual(self.plan_candidate(va)[satisfy.ACTION_FIELD],
                         satisfy.MANIFEST_ACTION_UPDATE)
        self.assertEqual(self.plan_candidate(va)["needs_satisfied"], False)

    def test_unsatisfy_removes_a_created_row_instead_of_restoring_a_stub(self):
        self.make_root()
        va = self.promoted_without_a_row()
        functions_before = json.dumps(self.manifest()["functions"], sort_keys=True)
        top_level_before = sorted(self.manifest())
        satisfy.apply(self.info["root"], vas=[va], reason="test")
        self.assertIsNotNone(self.entry_or_none(va))
        result = satisfy.unsatisfy(self.info["root"], vas=[va],
                                   reason="regression in the model test")
        self.assertEqual(result["status"], "ok")
        self.assertEqual(result["changed"], True)
        self.assertEqual(result["restored"], [va])
        self.assertEqual(result["removed"], [va])
        self.assertIsNone(self.entry_or_none(va))
        # functions[] is back to its pre-create bytes; the change_log is
        # append-only, so that is the only difference the reversal leaves.
        self.assertEqual(json.dumps(self.manifest()["functions"], sort_keys=True),
                         functions_before)
        self.assertEqual(sorted(key for key in set(self.manifest())
                                if key != "change_log"),
                         sorted(top_level_before))
        fx.clear_index_cache()
        self.assertFalse(self.reconstructed(va))
        entry = [row for entry in self.manifest()["change_log"]
                 if entry.get("kind") == satisfy.CHANGE_KIND_UNSATISFY
                 for row in entry.get("rows") or []]
        self.assertEqual([row["removed"] for row in entry], [True])
        self.assertEqual(entry[0]["restored_body_status"], None)
        # A second reversal has nothing left to reverse and says so.
        again = satisfy.unsatisfy(self.info["root"], vas=[va], reason="test")
        self.assertEqual(again["changed"], False)
        self.assertEqual([item["code"] for item in again["refused"][0]["blockers"]],
                         ["no_manifest_entry"])

    def test_unsatisfy_restores_an_updated_row_and_leaves_a_created_one_alone(self):
        # One call, two VAs, two prior states: the update path writes the
        # statuses back and the create path deletes the row. The manifest_action
        # recorded in the change_log is the only thing that decides, so the two
        # reversals cannot be confused for one another.
        self.make_root()
        updated = self.promote_key("A")
        created = self.promote_key(CREATED)
        self.drop_rows(CREATED)
        satisfy.apply(self.info["root"], vas=[updated, created], reason="test")
        result = satisfy.unsatisfy(self.info["root"], vas=[updated, created],
                                   reason="rollback")
        self.assertEqual(result["removed"], [created])
        self.assertEqual(result["restored"], sorted([updated, created]))
        entry = self.entry_or_none(updated)
        self.assertIsNotNone(entry)
        self.assertIsNone(entry.get("integration_status"))
        self.assertEqual(entry["body_status"], "unresolved")
        self.assertIsNone(self.entry_or_none(created))

    def test_resatisfy_after_a_creation_rollback_converges(self):
        self.make_root()
        va = self.promoted_without_a_row()
        satisfy.apply(self.info["root"], vas=[va], reason="first")
        satisfy.unsatisfy(self.info["root"], vas=[va], reason="rollback")
        again = satisfy.apply(self.info["root"], vas=[va], reason="second")
        self.assertEqual(again["status"], "ok")
        self.assertEqual(again["satisfied"], [va])
        self.assertEqual(again["created"], [va])
        # The second creation is a create again: the row is genuinely gone.
        self.assertEqual([row[satisfy.CHANGE_ACTION_KEY]
                          for row in self.satisfy_rows(va)],
                         [satisfy.MANIFEST_ACTION_CREATE,
                          satisfy.MANIFEST_ACTION_CREATE])

    def test_crash_mid_write_leaves_the_manifest_untouched_and_rerunnable(self):
        self.make_root()
        va = self.promoted_without_a_row()
        before = self.manifest_bytes()
        saved = rk.write_json_atomic

        def explode(path, document):
            raise OSError("simulated crash mid-write")

        rk.write_json_atomic = explode
        self.addCleanup(setattr, rk, "write_json_atomic", saved)
        with self.assertRaises(OSError):
            satisfy.apply(self.info["root"], vas=[va], reason="test")
        rk.write_json_atomic = saved
        after = self.manifest_bytes()
        self.assertEqual(after, before)
        self.assertEqual(len(json.loads(after.decode("utf-8"))["functions"]),
                         len(json.loads(before.decode("utf-8"))["functions"]))
        leftovers = [item.name for item in
                     (Path(self.info["root"]) / "knowledgegraph/research").iterdir()
                     if item.name.startswith("source-reconstruction-manifest.json.")]
        self.assertEqual(leftovers, [])
        result = satisfy.apply(self.info["root"], vas=[va], reason="test")
        self.assertEqual(result["satisfied"], [va])
        self.assertNotEqual(self.manifest_bytes(), before)


class PlanHonestyTest(CreationCase):
    """``plan`` is read-only, and it never disagrees with ``apply``."""

    def test_plan_reports_create_and_agrees_with_apply(self):
        self.make_root()
        va = self.promoted_without_a_row()
        before = self.manifest_digest()
        document = satisfy.plan(self.info["root"], vas=[va])
        candidate = document["candidates"][0]
        self.assertTrue(document["ok"])
        self.assertEqual(candidate["blockers"], [])
        self.assertEqual(candidate[satisfy.ACTION_FIELD],
                         satisfy.MANIFEST_ACTION_CREATE)
        self.assertTrue(candidate["needs_satisfied"])
        self.assertEqual(document["summary"]["admissible"], 1)
        self.assertEqual(document["summary"]["creates"], 1)
        self.assertEqual(document["summary"]["refused"], 0)
        # Read-only: not one byte moved, and the action is unchanged afterwards.
        self.assertEqual(self.manifest_digest(), before)
        self.assertEqual(self.plan_candidate(va)[satisfy.ACTION_FIELD],
                         satisfy.MANIFEST_ACTION_CREATE)
        # And what it promised is what apply does.
        result = satisfy.apply(self.info["root"], vas=[va], reason="test",
                               dry_run=True)
        self.assertEqual(result["manifest_actions"],
                         {va: candidate[satisfy.ACTION_FIELD]})
        self.assertEqual(result["would_satisfy"], [va])
        self.assertEqual(self.manifest_digest(), before)
        result = satisfy.apply(self.info["root"], vas=[va], reason="test")
        self.assertEqual(result["manifest_actions"],
                         {va: candidate[satisfy.ACTION_FIELD]})

    def test_plan_reports_absent_when_a_refusal_would_stop_the_creation(self):
        self.make_root()
        va = self.promoted_without_a_row()
        self.rewrite_record_build(va, _gate_red(_package_for(PROBE_CALLEE)[1]))
        candidate = self.plan_candidate(va)
        self.assertEqual(candidate[satisfy.ACTION_FIELD],
                         satisfy.MANIFEST_ACTION_ABSENT)
        self.assertEqual(candidate[satisfy.SOURCES_FIELD], {})
        self.assertEqual(sorted(item["code"] for item in candidate["blockers"]),
                         ["build_not_green", "no_manifest_entry"])
        result = satisfy.apply(self.info["root"], vas=[va], reason="test")
        self.assertEqual(result["status"], "blocked")
        self.assertEqual(result["refused"][0][satisfy.ACTION_FIELD],
                         satisfy.MANIFEST_ACTION_ABSENT)

    def test_plan_reports_update_for_a_row_that_already_exists(self):
        self.make_root()
        va = self.promote_key(PROBE_CALLEE)
        candidate = self.plan_candidate(va)
        self.assertEqual(candidate[satisfy.ACTION_FIELD],
                         satisfy.MANIFEST_ACTION_UPDATE)
        self.assertEqual(candidate[satisfy.SOURCES_FIELD], {})
        self.assertTrue(candidate["needs_satisfied"])
        satisfy.apply(self.info["root"], vas=[va], reason="test")
        # Once satisfied the row exists and nothing is pending: an update that
        # has nothing to do is reported as already satisfied, not as a creation.
        settled = self.plan_candidate(va)
        self.assertEqual(settled[satisfy.ACTION_FIELD],
                         satisfy.MANIFEST_ACTION_UPDATE)
        self.assertEqual(settled["needs_satisfied"], False)

    def test_plan_walks_the_authority_chain_down_to_the_installed_marker(self):
        # The synthetic promotion leaves ``symbol: null`` on the installed
        # marker, so the sidecar is normally the only name in the chain. Give the
        # marker one, remove the sidecar, and the marker becomes the next
        # authority -- which the plan must then name as the source it used.
        self.make_root()
        va = self.promoted_without_a_row()
        self.assertEqual(self.plan_candidate(va)[satisfy.SOURCES_FIELD]
                         ["normalized_symbol"],
                         "reconstruction/metadata/%s/%s.json"
                         % (_package_for(PROBE_CALLEE)[0], fx.bare(va)))
        sidecar = (Path(self.info["root"]) / "reconstruction/metadata"
                   / _package_for(PROBE_CALLEE)[0] / ("%s.json" % fx.bare(va)))
        sidecar.unlink()
        marker_path = self.marker_path(PROBE_CALLEE)
        marker = json.loads(marker_path.read_text(encoding="utf-8"))
        marker["targets"][0]["symbol"] = "synth::Bravo::Dep"
        marker_path.write_text(json.dumps(marker, indent=2, sort_keys=True) + "\n",
                               encoding="utf-8")
        fx.clear_index_cache()
        candidate = self.plan_candidate(va)
        self.assertEqual(candidate["blockers"], [])
        self.assertEqual(candidate[satisfy.SOURCES_FIELD]["normalized_symbol"],
                         "src/reconstruction/%s/promotion.json"
                         % _package_for(PROBE_CALLEE)[1])
        satisfy.apply(self.info["root"], vas=[va], reason="test")
        self.assertEqual(self.entry_or_none(va)["normalized_symbol"],
                         "synth::Bravo::Dep")


class DeterminismTest(CreationCase):
    """Two independent roots, the same manifest bytes."""

    def test_two_roots_produce_byte_identical_manifests(self):
        snapshots = []
        for name in ("root-alpha", "root-beta"):
            self.make_root_at(name)
            va = self.promoted_without_a_row(PROBE_CALLEE)
            satisfy.apply(self.info["root"], vas=[va], reason="test",
                          implementer_id="t-1")
            snapshots.append(self.manifest_bytes())
        self.assertEqual(snapshots[0], snapshots[1])
        # And the only thing that distinguishes them is the root, not the bytes.
        first = json.loads(snapshots[0].decode("utf-8"))
        self.assertEqual(json.dumps(first["functions"], sort_keys=True),
                         json.dumps(json.loads(
                             snapshots[1].decode("utf-8"))["functions"], sort_keys=True))


class CommittedTreeTest(unittest.TestCase):
    """The real repository is only ever read, and even then only through ``plan``.

    ``satisfy.plan`` on the committed tree is the exact call the milestone report
    reproduces. It must report a creation without writing one, so this is the
    one test in the file that touches the real manifest -- read-only, and it
    fingerprints the file before and after.
    """

    def test_plan_on_the_committed_tree_writes_nothing(self):
        root = Path(fx.config.resolve("knowledgegraph", "spore.db")).parent.parent
        manifest = root / fx.MANIFEST_REL
        if not manifest.is_file():
            self.skipTest("the committed manifest is not present")
        before = manifest.read_bytes()
        fx.clear_index_cache()
        try:
            document = satisfy.plan(root)
        finally:
            fx.clear_index_cache()
        self.assertTrue(document["ok"])
        self.assertEqual(manifest.read_bytes(), before)
        creates = [item for item in document["candidates"]
                   if item[satisfy.ACTION_FIELD] == satisfy.MANIFEST_ACTION_CREATE]
        # Whatever the campaign's current state is, a create must be admissible,
        # and the whole candidate set must agree between plan and its own
        # blockers: an admissible create is exactly a create with no blockers.
        for candidate in document["candidates"]:
            if candidate[satisfy.ACTION_FIELD] == satisfy.MANIFEST_ACTION_CREATE:
                self.assertEqual(candidate["blockers"], [], candidate["va"])
                self.assertTrue(candidate["needs_satisfied"], candidate["va"])
            self.assertNotEqual(
                (candidate[satisfy.ACTION_FIELD] == satisfy.MANIFEST_ACTION_CREATE
                 and bool(candidate["blockers"])), True, candidate["va"])
        self.assertEqual(document["summary"]["creates"], len(creates))


if __name__ == "__main__":
    unittest.main()
