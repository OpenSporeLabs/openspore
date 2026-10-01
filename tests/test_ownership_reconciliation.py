"""Tests for duplicate-ownership reconciliation.

Subject: ``tools/reconstruction_tooling/ownership.py`` and the way
``promote.py`` consults it. Everything builds a synthetic repository under its
own ``mkdtemp`` and passes it as ``root=``; the real repository is never
written. The build gate is a stub injected into ``sys.modules`` for the same
reason ``tests/test_promotion.py`` stubs it -- a promotion that is not gated is
the failure these tests exist to prevent, and nothing here should compile
anything.

The policy under test, in the order the assertions appear:

* the canonical owner is the greatest objective-evidence tuple, and *only*
  that -- never the newest, never the first, never the alphabetically lucky
  one except as a documented identity tiebreak;
* timestamps are diagnostics and never an input;
* losing ownership destroys nothing: both provenance records survive, the
  duplicate relationship is recorded, and the canonical VA identity is unique;
* the ledger is fail-safe on read -- a missing, stale, contested or
  differently-shaped ledger leaves the gate refusing exactly as it did before.

Run from the repo root::

    python3 -m unittest tests.test_ownership_reconciliation -v
"""
import hashlib
import json
import os
import shutil
import sys
import tempfile
import time
import types
import unittest
from pathlib import Path

from tools.reconstruction_tooling import ownership, promote

GATE_MODULE = "tools.reconstruction_tooling.build_gate"
VA = "0x006a2ef0"
BARE = "006a2ef0"
OTHER_VA = "0x006a2f00"

HEADER = """#pragma once

namespace openspore::reconstruction::%(package)s {

int Body(void *self, unsigned int key);

}  // namespace openspore::reconstruction::%(package)s
"""

SOURCE = """#include "%(stem)s.hpp"

namespace openspore::reconstruction::%(package)s {

int Body(void *self, unsigned int key) {
  (void)self;
  (void)key;
  return 0;
}

}  // namespace openspore::reconstruction::%(package)s
"""

TEST_SOURCE = """#include "%(stem)s.hpp"

#include <cstdlib>

int main() {
  using namespace openspore::reconstruction::%(package)s;
  if (Body(nullptr, 1u) != 0) {
    std::abort();
  }
  return 0;
}
"""


def _bare(va):
    """Accept either VA spelling and return bare 8-char hex."""
    text = str(va).strip().lower()
    if text.startswith("0x"):
        text = text[2:]
    return text


def _digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def _tree_digest(root):
    """A digest of every file under ``root``: path plus content, sorted."""
    entries = []
    for path in sorted(Path(root).rglob("*")):
        if path.is_file():
            entries.append("%s:%s" % (path.relative_to(root).as_posix(), _digest(path)))
        elif path.is_dir():
            entries.append("%s/" % path.relative_to(root).as_posix())
    return hashlib.sha256("\n".join(entries).encode("utf-8")).hexdigest()


class OwnershipFixture(unittest.TestCase):
    """A synthetic repository with two packages claiming one VA."""

    def setUp(self):
        self.root = Path(tempfile.mkdtemp(prefix="ownership-test."))
        self.addCleanup(shutil.rmtree, str(self.root), True)
        for relative in ("reconstruction/staging", "reconstruction/metadata",
                         "reconstruction/evidence", "reconstruction/knowledge",
                         "knowledgegraph/research", "src/reconstruction"):
            (self.root / relative).mkdir(parents=True, exist_ok=True)
        self._reported = {}
        self.gate_result = {"schema": "openspoke-build-gate-1", "ok": True,
                            "steps": [{"name": "compile", "ok": True, "returncode": 0}],
                            "packages": {}}
        self._install_gate()

    def _install_gate(self):
        module = types.ModuleType(GATE_MODULE)
        outer = self

        def gate(root, packages=None, build_dir=None, jobs=None):
            return json.loads(json.dumps(outer.gate_result))

        module.gate = gate
        package, name = GATE_MODULE.rsplit(".", 1)
        previous = sys.modules.get(name)
        self.addCleanup(self._restore_gate, package, name, previous)
        sys.modules[name] = module
        setattr(sys.modules[package], name, module)

    def _restore_gate(self, package, name, previous):
        sys.modules.pop(name, None)
        import importlib
        holder = importlib.import_module(package)
        if previous is not None:
            sys.modules[name] = previous
            setattr(holder, name, previous)
        elif hasattr(holder, name):
            delattr(holder, name)

    # -- writers ---------------------------------------------------------

    def _write(self, path, text):
        path = Path(path)
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")

    def stage(self, package, va=BARE, header=True, test=True, metadata=True,
              report=None, ownership_json=None, body=None, location="staging",
              namespace=None):
        """Stage one package that claims ``va``.

        ``report`` is the static status of a validation report naming *this*
        package's source, or ``None`` for no report at all -- which is what an
        un-validated duplicate looks like. ``location="src"`` writes the package
        as integrator-owned canonical source instead of staging.
        """
        stem = package.replace("-", "_").lower()
        src_package = stem
        if location == "src":
            directory = self.root / "src/reconstruction" / src_package
        else:
            directory = self.root / "reconstruction/staging" / package
        directory.mkdir(parents=True, exist_ok=True)
        values = {"stem": stem,
                  "package": namespace if namespace is not None else src_package}
        if header:
            self._write(directory / (stem + ".hpp"), HEADER % values)
        if test:
            self._write(directory / (stem + "_model_test.cpp"), TEST_SOURCE % values)
        self._write(directory / (stem + ".cpp"), (body or SOURCE) % values)
        if ownership_json is not None:
            self._write(directory / "ownership.json", json.dumps(ownership_json))
        if metadata:
            self._write(self.root / "reconstruction/metadata" / package / (_bare(va) + ".json"),
                        json.dumps({"va": va, "package": package, "worker_ownership": "worker-%s" % package}))
        if report is not None:
            self.write_validation(va, package=package, stem=stem, static=report,
                                  location=location)
        return {"package": package, "src_package": src_package, "stem": stem}

    def write_validation(self, va, package, stem, static="PASS", runtime="GATED",
                         location="staging", source_path=None):
        # A VA has exactly one validation report, by construction of
        # evidence/<bare8>/validation.json. Writing a second one for the same
        # VA would silently overwrite the first and make a comparison test
        # assert something the artifact model cannot express, so refuse.
        if _bare(va) in self._reported:
            raise AssertionError("VA %s already has a report naming %s"
                                 % (va, self._reported[_bare(va)]))
        self._reported[_bare(va)] = package
        if source_path is None:
            prefix = "reconstruction/staging" if location == "staging" else "src/reconstruction"
            source_path = "%s/%s/%s.cpp" % (prefix, package if location == "staging"
                                            else package.replace("-", "_").lower(), stem)
        report = {
            "schema": "openspore-structural-validation-1",
            "target": va,
            "status": static,
            "source": {"path": source_path,
                       "role": "staging" if location == "staging" else "src",
                       "sha256": _digest(self.root / source_path)},
            "static": {"dimension": "STATIC", "status": static, "checks": {}},
            "runtime": {"dimension": "RUNTIME", "status": runtime,
                        "gated": runtime == "GATED", "gates": [], "validated": 0},
            "coverage": {"ratio": 1.0, "total": 9, "pass": 9, "warn": 0,
                         "unknown": 0, "not_available": 0, "attempted": 9},
        }
        self._write(self.root / "reconstruction/evidence" / _bare(va) / "validation.json",
                    json.dumps(report, indent=2, sort_keys=True) + "\n")

    def write_evidence(self, va=BARE, integrity="verified", level="OBSERVED",
                       package=None):
        record = {"evidence_level": level, "va": va}
        if package is not None:
            prefix = ("reconstruction/staging" if (self.root / "reconstruction/staging" / package).is_dir()
                      else "src/reconstruction")
            record["source"] = {"file": "%s/%s/%s.cpp"
                                % (prefix, package if prefix.endswith("staging")
                                   else package.replace("-", "_").lower(),
                                   package.replace("-", "_").lower())}
        self._write(self.root / "reconstruction/evidence" / _bare(va) / "evidence.json",
                    json.dumps({"schema": "openspore-evidence-1", "target": va,
                                "evidence_state": "present",
                                "binary_evidence": {"integrity": integrity},
                                "record": record}))

    def write_promotion_record(self, va=BARE, package="", src_package="", ok=True):
        self._write(self.root / "reconstruction/evidence" / _bare(va) / "promotion.json",
                    json.dumps({"schema": "openspore-promotion-record-1", "va": va,
                                "package": package, "src_package": src_package,
                                "static_status": "PASS", "runtime_status": "GATED",
                                "build": {"schema": "openspore-build-gate-1", "ok": ok,
                                          "m32": True,
                                          "packages": {src_package: {"ok": ok, "test_count": 1}}}}))

    def install_promoted(self, src_package, va=BARE):
        directory = self.root / "src/reconstruction" / src_package
        directory.mkdir(parents=True, exist_ok=True)
        self._write(directory / "promotion.json",
                    json.dumps({"schema": "openspore-promotion-1", "src_package": src_package,
                                "package": src_package.replace("_", "-"),
                                "targets": [{"va": va, "src_package": src_package}]}))

    def write_manifest(self, rows):
        self._write(self.root / "knowledgegraph/research/source-reconstruction-manifest.json",
                    json.dumps({"schema": "openspore-source-reconstruction-manifest-1",
                                "status": "authoritative", "functions": rows}))

    # -- readers ---------------------------------------------------------

    def codes(self, document, package=None):
        return sorted(item["code"] for candidate in document["candidates"]
                      if package is None or candidate["package"] == package
                      for item in candidate["blockers"])

    def entry(self, va=VA):
        for row in ownership.inventory(self.root, vas=[va])["entries"]:
            if row["va"] == va:
                return row
        return None

    def reconcile(self, vas=None):
        return ownership.apply(self.root, vas=vas, write=True)


class ClaimDiscoveryTest(OwnershipFixture):
    """A claim is recognised from every signal the gate recognises it from."""

    def test_metadata_handoff_alone_is_a_claim(self):
        self.stage("pkg-alpha", metadata=True, report=None)
        self.assertEqual(ownership.claimant_map(self.root).get(BARE), ["pkg-alpha"])

    def test_a_va_bearing_staged_filename_is_a_claim(self):
        self.stage("pkg-alpha", metadata=False, report=None)
        directory = self.root / "reconstruction/staging/pkg-alpha"
        self._write(directory / "helper_006a2ef0_extra.hpp", "#pragma once\n")
        self.assertEqual(ownership.claimant_map(self.root).get(BARE), ["pkg-alpha"])

    def test_a_validation_report_naming_staging_is_a_claim(self):
        self.stage("pkg-alpha", metadata=False, report="PASS")
        self.assertEqual(ownership.claimant_map(self.root).get(BARE), ["pkg-alpha"])

    def test_a_validation_report_naming_src_is_a_claim(self):
        self.stage("pkg-alpha", metadata=False, report=None, location="src")
        self.write_validation(VA, package="pkg-alpha", stem="pkg_alpha", location="src")
        self.assertEqual(ownership.claimant_map(self.root).get(BARE), ["pkg-alpha"])

    def test_all_four_signals_report_the_same_claimant_set_as_the_gate(self):
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)
        mine = ownership.claimant_map(self.root)
        theirs = promote._va_claims(self.root, promote._validation_reports(self.root))
        for va in set(mine) | set(theirs):
            # The gate's staging-only view is a subset: it never sees a package
            # that exists only as canonical source in src/.
            self.assertTrue(set(mine[va]) >= set(theirs.get(va, [])),
                            "ownership lost a claim the gate sees at %s" % va)


class CanonicalizationRuleTest(OwnershipFixture):
    """The winner is decided by evidence, in a fixed order."""

    def test_a_static_pass_report_outranks_an_unvalidated_duplicate(self):
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)
        self.assertEqual(self.entry()["canonical"], "pkg-alpha")
        self.assertEqual(self.entry()["deciding_axis"], "validation")

    def test_the_status_ranks_are_strictly_ordered_as_documented(self):
        order = [ownership.STATIC_RANK[name]
                 for name in ("PASS", "WARN", "UNKNOWN", "NOT_AVAILABLE")]
        self.assertEqual(order, sorted(order, reverse=True))
        self.assertEqual(len(set(order)), len(order))
        self.assertEqual(min(order), 1)

    def test_the_package_the_validator_named_outranks_the_one_it_did_not(self):
        # One report per VA, so the validation axis is really "was this package
        # validated, and how well" -- never a comparison between two verdicts.
        self.stage("pkg-alpha", report="WARN")
        self.stage("pkg-beta", report=None)
        ranks = {row["package"]: row["comparison"]["validation"]
                 for row in self.entry()["claimants"]}
        self.assertEqual(ranks, {"pkg-alpha": ownership.STATIC_RANK["WARN"],
                                 "pkg-beta": 0})

    def test_an_installed_promotion_outranks_a_better_validating_duplicate(self):
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)
        self.install_promoted("pkg_beta")
        self.assertEqual(self.entry()["canonical"], "pkg-beta")
        self.assertEqual(self.entry()["deciding_axis"], "settled")

    def test_a_manifest_record_outranks_a_better_validating_duplicate(self):
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)
        self.write_manifest([{"va": VA, "package": "PKG-BETA",
                              "body_status": "integrated"}])
        self.assertEqual(self.entry()["canonical"], "pkg-beta")
        self.assertEqual(self.entry()["deciding_axis"], "settled")

    def test_canonical_source_in_src_outranks_a_staging_duplicate(self):
        # The re-reconstruction validates cleanly; the function is already
        # canonical in src/ from an integrator batch. Settled wins, and that is
        # the whole point: promoting the fresh copy is the collision the gate
        # exists to refuse.
        self.stage("pkg-integrated", location="src", report=None)
        self.stage("pkg-fresh", report="PASS")
        row = self.entry()
        self.assertEqual(row["canonical"], "pkg-integrated")
        self.assertEqual(row["deciding_axis"], "settled")
        self.assertEqual({item["package"]: item["staging"]["location"]
                          for item in row["claimants"]},
                         {"pkg-integrated": "src/reconstruction",
                          "pkg-fresh": "reconstruction/staging"})

    def test_a_verified_build_gate_outranks_an_unverified_duplicate(self):
        self.stage("pkg-alpha", report=None)
        self.stage("pkg-beta", report=None)
        self.write_promotion_record(va=BARE, package="pkg-beta",
                                    src_package="pkg_beta", ok=True)
        row = self.entry()
        self.assertEqual(row["canonical"], "pkg-beta")
        self.assertEqual(row["deciding_axis"], "build_gate")
        self.assertEqual(row["claimants"][0]["comparison"]["build_gate"], 1)

    def test_worker_provenance_breaks_a_tie(self):
        self.stage("pkg-alpha", report=None, ownership_json={
            "package": "pkg-alpha",
            "owned": [{"va": VA, "role": "body"}]})
        self.stage("pkg-beta", report=None)
        row = self.entry()
        self.assertEqual(row["canonical"], "pkg-alpha")
        self.assertEqual(row["deciding_axis"], "provenance")

    def test_metadata_coherence_breaks_a_tie(self):
        self.stage("pkg-alpha", report=None)
        self.stage("pkg-beta", report=None)
        # Same worker provenance on both sides, so provenance cannot decide it.
        self._write(self.root / "reconstruction/metadata/pkg-alpha" / (BARE + ".json"),
                    json.dumps({"va": VA, "package": "pkg-alpha",
                                "worker_ownership": "worker-alpha"}))
        # pkg-beta's handoff contradicts itself: it claims a different VA.
        self._write(self.root / "reconstruction/metadata/pkg-beta" / (BARE + ".json"),
                    json.dumps({"va": OTHER_VA, "package": "pkg-beta",
                                "worker_ownership": "worker-beta"}))
        row = self.entry()
        self.assertEqual(row["canonical"], "pkg-alpha")
        self.assertEqual(row["deciding_axis"], "metadata_coherence")

    def test_an_unrecognised_status_scores_zero_and_never_wins(self):
        self.stage("pkg-mmm-reported", report="SOMETHING_NEW")
        self.stage("pkg-aaa-unreported", report=None)
        ranks = {row["package"]: row["comparison"]["validation"]
                 for row in self.entry()["claimants"]}
        self.assertEqual(ranks, {"pkg-mmm-reported": 0, "pkg-aaa-unreported": 0})
        # Equal evidence, so the identity tiebreak applies -- and it does not
        # reward the package the validator happened to look at.
        self.assertEqual(self.entry()["deciding_axis"], ownership.TIE_BREAK)
        self.assertEqual(self.entry()["canonical"], "pkg-aaa-unreported")

    def test_evidence_ranks_only_the_package_the_pack_actually_names(self):
        self.stage("pkg-alpha", report=None)
        self.stage("pkg-beta", report=None)
        self.write_evidence(package="pkg-alpha", level="PROBABLY_FINE")
        ranks = {row["package"]: row["comparison"]["evidence"]
                 for row in self.entry()["claimants"]}
        # The pack names pkg-alpha, so it is attributed; the unrecognised level
        # adds nothing, and the un-named package scores zero rather than the
        # "a pack exists" one point a VA-scoped reading would have given it.
        self.assertEqual(ranks, {"pkg-alpha": 2, "pkg-beta": 0})
        self.assertEqual(self.entry()["deciding_axis"], "evidence")
        # ... and drop the verified-integrity point to prove where it came from.
        self.write_evidence(package="pkg-alpha", level="PROBABLY_FINE",
                            integrity="unverified")
        self.assertEqual({row["package"]: row["comparison"]["evidence"]
                          for row in self.entry()["claimants"]}["pkg-alpha"], 1)

    def test_a_verified_observed_pack_outranks_a_bare_one(self):
        self.stage("pkg-alpha", report=None)
        self.stage("pkg-beta", report=None)
        self.write_evidence(package="pkg-alpha", level="SUPPORTED")
        self.assertEqual(self.entry()["deciding_axis"], "evidence")
        weaker = {row["package"]: row["comparison"]["evidence"]
                  for row in self.entry()["claimants"]}["pkg-alpha"]
        self.write_evidence(package="pkg-alpha", level="OBSERVED")
        stronger = {row["package"]: row["comparison"]["evidence"]
                    for row in self.entry()["claimants"]}["pkg-alpha"]
        self.assertGreater(stronger, weaker)

    def test_the_rule_is_frozen_and_self_describing(self):
        rule = ownership.rule_description()
        self.assertEqual(list(rule["axes"]), list(ownership.AXES))
        self.assertFalse(rule["timestamps_are_inputs"])
        for axis in ownership.AXES:
            self.assertIn(axis, rule["axis_definitions"])


class TimestampIndependenceTest(OwnershipFixture):
    """A clock must not be an input. These are the tests that prove it."""

    def test_touching_every_file_reversed_leaves_the_decision_unchanged(self):
        # A genuine evidence tie, so the decision rests entirely on the identity
        # tiebreak. Making the losing side the newest file on disk must not
        # change anything -- which is exactly what a recency rule would do.
        self.stage("pkg-alpha", report=None)
        self.stage("pkg-beta", report=None)
        before = self.entry()
        self.assertEqual(before["deciding_axis"], ownership.TIE_BREAK)
        later = time.time() + 100000
        for path in sorted(self.root.rglob("*.json"), reverse=True):
            os.utime(path, (later, later))
        after = self.entry()
        self.assertEqual(after["canonical"], before["canonical"])
        self.assertEqual(after["canonical"], "pkg-alpha")

    def test_rewriting_the_losing_side_afterwards_does_not_flip_the_decision(self):
        self.stage("pkg-alpha", report=None)
        self.stage("pkg-beta", report=None)
        # Edit the loser last, and make it richer. Provenance is a real axis, so
        # this *may* flip the decision -- but only on that axis, and the flip
        # must be reported as a provenance decision, never as a recency one.
        self._write(self.root / "reconstruction/staging/pkg-beta/ownership.json",
                    json.dumps({"package": "pkg-beta",
                                "owned": [{"va": VA, "role": "body"}]}))
        row = self.entry()
        self.assertEqual(row["canonical"], "pkg-beta")
        self.assertEqual(row["deciding_axis"], "provenance")

    def test_diagnostics_report_timestamps_but_they_are_not_the_key(self):
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)

        row = self.entry()
        keys = {tuple(item["rank_key"]) for item in row["claimants"]}
        self.assertEqual(len(keys), len(row["claimants"]))
        for item in row["claimants"]:
            self.assertTrue(set(item["comparison"]) == set(ownership.AXES))
            self.assertEqual(item["rank_key"],
                             [item["comparison"][axis] for axis in ownership.AXES])

    def test_an_equivalent_tie_breaks_on_package_name_not_on_time(self):
        self.stage("pkg-zeta", report=None)
        self.stage("pkg-alpha", report=None)
        self.assertEqual(self.entry()["canonical"], "pkg-alpha")
        self.assertEqual(self.entry()["deciding_axis"], ownership.TIE_BREAK)
        self.assertEqual(sorted(self.entry()["tied_on_rank"]), ["pkg-zeta"])

    def test_the_name_tiebreak_is_a_total_order_not_a_coincidence(self):
        self.stage("pkg-mmm", report=None)
        self.stage("pkg-aaa", report=None)
        self.stage("pkg-zzz", report=None)
        row = self.entry()
        self.assertEqual(row["canonical"], "pkg-aaa")
        self.assertEqual(sorted(row["tied_on_rank"]), ["pkg-mmm", "pkg-zzz"])
        self.assertEqual([item["package"] for item in row["superseded"]],
                         ["pkg-mmm", "pkg-zzz"])


class ProvenancePreservationTest(OwnershipFixture):
    """Losing ownership must cost a claim, never a file."""

    def test_both_provenance_records_survive_a_reconciliation(self):
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)
        self.reconcile()
        document = json.loads(ownership.ledger_path(self.root).read_text(encoding="utf-8"))
        entry = document["entries"][VA]
        self.assertEqual(entry["canonical"], "pkg-alpha")
        self.assertEqual([row["package"] for row in entry["superseded"]], ["pkg-beta"])
        loser = entry["superseded"][0]
        self.assertEqual(loser["superseded_by"], "pkg-alpha")
        self.assertTrue(loser["provenance_preserved"])
        self.assertFalse(loser["deleted"])
        self.assertEqual(loser["retained_artifacts"]["metadata"],
                         ["reconstruction/metadata/pkg-beta/%s.json" % BARE])
        self.assertIn("pkg_beta.cpp", loser["retained_artifacts"]["retained_files"])
        self.assertEqual(loser["retained_artifacts"]["worker_ownership"], "worker-pkg-beta")

    def test_apply_writes_the_ledger_and_deletes_nothing(self):
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)
        before = _tree_digest(self.root)
        self.reconcile()
        after = _tree_digest(self.root)
        self.assertNotEqual(before, after)
        # Take the ledger away again -- file *and* the directory it created,
        # because `before` was taken when neither existed -- and everything
        # that was there before must be byte-identical.
        ledger = ownership.ledger_path(self.root)
        ledger.unlink()
        ledger.parent.rmdir()
        self.assertEqual(before, _tree_digest(self.root))
        for package in ("pkg-alpha", "pkg-beta"):
            directory = self.root / "reconstruction/staging" / package
            self.assertTrue(directory.is_dir(), "%s was removed" % package)
            self.assertTrue(list(directory.glob("*.cpp")))
            self.assertTrue((self.root / "reconstruction/metadata" / package
                             / (BARE + ".json")).is_file())

    def test_the_duplicate_relationship_is_recorded(self):
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)
        self.reconcile()
        document = json.loads(ownership.ledger_path(self.root).read_text(encoding="utf-8"))
        relationship = document["entries"][VA]["duplicate_relationship"]
        self.assertEqual(relationship["kind"], "duplicate_va")
        self.assertTrue(relationship["resolved"])
        self.assertEqual(relationship["resolution"], "canonical_owner_selected")
        self.assertEqual(relationship["claimant_count"], 2)

    def test_the_canonical_identity_is_unique(self):
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)
        self.stage("pkg-gamma", report=None)

        self.reconcile()
        document = json.loads(ownership.ledger_path(self.root).read_text(encoding="utf-8"))
        entry = document["entries"][VA]
        self.assertEqual(len([entry["canonical"]]), 1)
        self.assertNotIn(entry["canonical"],
                         [row["package"] for row in entry["superseded"]])
        self.assertEqual(sorted(entry["claimants"]),
                         ["pkg-alpha", "pkg-beta", "pkg-gamma"])

    def test_a_filtered_apply_merges_rather_than_replaces(self):
        self.stage("pkg-alpha", report="PASS", va=VA)
        self.stage("pkg-beta", report=None, va=VA)
        self.stage("pkg-gamma", report="PASS", va=OTHER_VA)
        self.stage("pkg-delta", report=None, va=OTHER_VA)
        self.reconcile()
        self.assertEqual(len(self._ledger()["entries"]), 2)
        # Re-adjudicating one VA must not erase the other one's record. Losing
        # it would silently return that VA to duplicate_va with nothing to
        # explain it, because resolve is fail-safe by design.
        self.stage("pkg-latecomer", report=None, va=VA)
        result = self.reconcile(vas=[VA])
        self.assertEqual(result["reconciled_vas"], [VA])
        self.assertEqual(result["carried_forward_vas"], [OTHER_VA])
        self.assertEqual(sorted(self._ledger()["entries"]), sorted([VA, OTHER_VA]))
        self.assertEqual(ownership.resolve(self.root, OTHER_VA)["status"], "resolved")
        # And the re-adjudicated one really did pick up the new claimant.
        self.assertIn("pkg-latecomer", self._ledger()["entries"][VA]["claimants"])

    def test_a_filtered_apply_refuses_to_merge_into_an_unreadable_ledger(self):
        from tools.reconstruction_tooling.models import ToolError
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)
        self.reconcile()
        ownership.ledger_path(self.root).write_text("{ this is not json",
                                                   encoding="utf-8")
        with self.assertRaises(ToolError) as raised:
            self.reconcile(vas=[VA])
        self.assertEqual(raised.exception.code, "ownership_ledger_unreadable")
        # The damaged ledger is left exactly as it was, not overwritten.
        self.assertIn("not json", ownership.ledger_path(self.root).read_text())

    def test_a_filtered_apply_refuses_to_merge_into_a_foreign_schema(self):
        from tools.reconstruction_tooling.models import ToolError
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)
        self.reconcile()
        path = ownership.ledger_path(self.root)
        self._write(path, json.dumps({"schema": "something-else", "entries": {}}))
        with self.assertRaises(ToolError) as raised:
            self.reconcile(vas=[VA])
        self.assertEqual(raised.exception.code, "ownership_ledger_unsupported")

    def test_a_filtered_apply_with_no_ledger_writes_only_the_filtered_rows(self):
        self.stage("pkg-alpha", report="PASS", va=VA)
        self.stage("pkg-beta", report=None, va=VA)
        self.stage("pkg-gamma", report="PASS", va=OTHER_VA)
        self.stage("pkg-delta", report=None, va=OTHER_VA)
        result = self.reconcile(vas=[VA])
        self.assertEqual(sorted(self._ledger()["entries"]), [VA])
        self.assertEqual(result["carried_forward_vas"], [])

    def _ledger(self):
        return json.loads(ownership.ledger_path(self.root).read_text(encoding="utf-8"))

    def test_apply_is_idempotent(self):
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)
        self.reconcile()
        first = ownership.ledger_path(self.root).read_bytes()
        self.reconcile()
        self.assertEqual(first, ownership.ledger_path(self.root).read_bytes())


class LedgerFailSafeTest(OwnershipFixture):
    """A ledger that no longer describes the tree must be ignored."""

    def test_resolve_refuses_when_no_ledger_exists(self):
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)
        decision = ownership.resolve(self.root, VA)
        self.assertEqual(decision["status"], "unresolved")
        self.assertEqual(decision["problem"], "ledger_missing")
        self.assertIn("duplicate_va", self.codes(promote.plan(root=self.root)))

    def test_resolve_refuses_an_unsupported_schema(self):
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)
        self.reconcile()
        path = ownership.ledger_path(self.root)
        document = json.loads(path.read_text(encoding="utf-8"))
        document["schema"] = "openspore-va-ownership-99"
        self._write(path, json.dumps(document))
        self.assertEqual(ownership.resolve(self.root, VA)["problem"],
                         "ledger_schema_unsupported")
        self.assertIn("duplicate_va", self.codes(promote.plan(root=self.root)))

    def test_resolve_refuses_when_a_new_claimant_appears(self):
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)
        self.reconcile()
        self.stage("pkg-latecomer", report=None)
        decision = ownership.resolve(self.root, VA)
        self.assertEqual(decision["status"], "unresolved")
        self.assertEqual(decision["problem"], "claimants_changed")
        self.assertIn("pkg-latecomer", decision["observed"])
        self.assertIn("duplicate_va", self.codes(promote.plan(root=self.root)))

    def test_resolve_refuses_when_a_source_is_edited_after_the_decision(self):
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)
        self.reconcile()
        self.assertEqual(ownership.resolve(self.root, VA)["status"], "resolved")
        path = self.root / "reconstruction/staging/pkg-beta/pkg_beta.cpp"
        self._write(path, SOURCE % {"stem": "pkg_beta", "package": "pkg_beta"} + "\n// edited\n")
        decision = ownership.resolve(self.root, VA)
        self.assertEqual(decision["status"], "unresolved")
        self.assertEqual(decision["problem"], "inputs_changed")
        self.assertIn("duplicate_va", self.codes(promote.plan(root=self.root)))

    def test_resolve_refuses_when_the_canonical_directory_disappears(self):
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)
        self.reconcile()
        self.assertEqual(ownership.resolve(self.root, VA)["status"], "resolved")
        shutil.rmtree(str(self.root / "reconstruction/staging/pkg-alpha"))
        # The ledger stops authorising ...
        self.assertEqual(ownership.resolve(self.root, VA)["problem"], "canonical_absent")
        # ... and the gate still refuses. It refuses on source_missing rather
        # than duplicate_va because the report's source went with the directory,
        # which is a refusal too -- just an earlier and more specific one.
        self.assertTrue(self.codes(promote.plan(root=self.root)))

    def test_resolve_refuses_when_a_foreign_package_already_promotes_the_va(self):
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)
        self.reconcile()
        self.assertEqual(ownership.resolve(self.root, VA)["status"], "resolved")
        self.install_promoted("pkg_other", va=VA)
        decision = ownership.resolve(self.root, VA)
        self.assertEqual(decision["status"], "unresolved")
        self.assertEqual(decision["problem"], "installed_conflict")
        self.assertIn("duplicate_va", self.codes(promote.plan(root=self.root)))

    def test_resolve_reports_a_ledger_that_is_not_there_yet(self):
        # The ledger is checked before the entry, so "no ledger" is the honest
        # first answer even for a VA that is not in the corpus at all.
        self.assertEqual(ownership.resolve(self.root, "0xdeadbeef")["problem"],
                         "ledger_missing")
        self.stage("pkg-alpha", report="PASS")
        self.stage("pkg-beta", report=None)
        self.reconcile()
        self.assertEqual(ownership.resolve(self.root, "0xdeadbeef")["problem"], "no_entry")

    def test_resolve_rejects_a_va_it_cannot_parse(self):
        self.assertEqual(ownership.resolve(self.root, "not-a-va")["status"], "unresolved")


class PromotionGateIntegrationTest(OwnershipFixture):
    """What the ledger does to the gate -- in one direction only."""

    def _two_packages(self, alpha_report="PASS", beta_report=None):
        self.stage("pkg-alpha", report=alpha_report)
        self.stage("pkg-beta", report=beta_report)

    def test_the_gate_still_refuses_without_a_ledger(self):
        self._two_packages()
        document = promote.plan(root=self.root)
        self.assertIn("duplicate_va", self.codes(document))
        self.assertNotIn("superseded_ownership", self.codes(document))

    def test_a_reconciled_canonical_owner_loses_the_duplicate_blocker(self):
        self._two_packages()
        self.reconcile()
        document = promote.plan(root=self.root)
        self.assertNotIn("duplicate_va", self.codes(document))
        self.assertNotIn("superseded_ownership", self.codes(document))
        row = [c for c in document["candidates"] if c["va"] == VA][0]
        self.assertEqual(row["package"], "pkg-alpha")
        self.assertEqual(row["ownership"]["canonical"], "pkg-alpha")

    def _reconstruction_of_an_integrated_function(self):
        """Stage a clean re-reconstruction of a function already in src/.

        This is the one shape in which a promotion *candidate* can lose
        arbitration: only the candidate's own source is named by a report, and
        the incumbent is settled by owning canonical source.
        """
        self.stage("pkg-incumbent", location="src", report=None)
        self.stage("pkg-rebuild", report="PASS")
        return self.root / "reconstruction/staging/pkg-rebuild/pkg_rebuild.cpp"

    def test_the_losing_candidate_is_refused_with_superseded_ownership(self):
        staged = self._reconstruction_of_an_integrated_function()
        self.reconcile()
        self.assertEqual(self.entry()["canonical"], "pkg-incumbent")
        document = promote.plan(root=self.root)
        codes = self.codes(document)
        self.assertIn("superseded_ownership", codes)
        self.assertNotIn("duplicate_va", codes)
        detail = [b["detail"] for c in document["candidates"]
                  for b in c["blockers"] if b["code"] == "superseded_ownership"][0]
        self.assertIn("pkg-incumbent", detail)
        # The refusal is a claim, not a deletion: every file is still there.
        self.assertTrue(staged.is_file())
        self.assertTrue((self.root / "reconstruction/metadata/pkg-rebuild"
                         / (BARE + ".json")).is_file())

    def test_a_stale_ledger_puts_the_duplicate_blocker_back(self):
        self._two_packages()
        self.reconcile()
        self.assertNotIn("duplicate_va", self.codes(promote.plan(root=self.root)))
        # A new claimant the ledger knows nothing about.
        self.stage("pkg-latecomer", report=None)
        codes = self.codes(promote.plan(root=self.root))
        self.assertIn("duplicate_va", codes)
        self.assertNotIn("superseded_ownership", codes)

    def test_reconciliation_does_not_relax_any_other_blocker(self):
        # A package whose namespace does not match its directory, validated
        # against those exact bytes so the report is not stale.
        self.stage("pkg-alpha", report="PASS", namespace="some_other_package")
        self.stage("pkg-beta", report=None)
        self.reconcile()
        codes = self.codes(promote.plan(root=self.root))
        self.assertIn("namespace_mismatch", codes)
        self.assertNotIn("duplicate_va", codes)
        self.assertNotIn("superseded_ownership", codes)

    def test_an_edited_source_makes_the_ledger_stale_again(self):
        self._two_packages(alpha_report="PASS")
        self.reconcile()
        self.assertNotIn("duplicate_va", self.codes(promote.plan(root=self.root)))
        # A ledger written about different bytes is ignored, not obeyed.
        self._write(self.root / "reconstruction/staging/pkg-beta/pkg_beta.cpp",
                    SOURCE % {"stem": "pkg_beta", "package": "pkg_beta"} + "\n//\n")
        self.assertIn("duplicate_va", self.codes(promote.plan(root=self.root)))

    def test_reconciliation_never_promotes_a_losing_package(self):
        self._reconstruction_of_an_integrated_function()
        self.reconcile()
        self.gate_result["packages"] = {"pkg_rebuild": {"ok": True}}
        result = promote.apply(root=self.root, package="pkg-rebuild",
                               build=False, ctest=False)
        self.assertEqual(result["status"], "blocked")
        self.assertEqual(result["promoted"], [])
        self.assertFalse((self.root / "src/reconstruction/pkg_rebuild").exists())
        codes = {item["code"] for row in result["refused"] for item in row["blockers"]}
        self.assertIn("superseded_ownership", codes)


class RealRepositoryTest(unittest.TestCase):
    """The live tree, read only: the ledger must describe it exactly."""

    def test_the_real_repository_has_duplicate_vas_and_all_are_reconciled(self):
        root = Path(__file__).resolve().parents[1]
        ledger = ownership.ledger_path(root)
        if not ledger.is_file():
            self.skipTest("no ownership ledger has been written yet")
        document = json.loads(ledger.read_text(encoding="utf-8"))
        self.assertEqual(document["schema"], ownership.LEDGER_SCHEMA)
        self.assertEqual(list(document["rule"]["axes"]), list(ownership.AXES))
        inventory = ownership.inventory(root)
        self.assertEqual(sorted(document["entries"]), sorted(inventory and
                 [row["va"] for row in inventory["entries"]]))
        for va, entry in document["entries"].items():
            self.assertEqual(ownership.resolve(root, va)["status"], "resolved", va)
            self.assertEqual(entry["canonical"] in entry["claimants"], True)
            self.assertNotIn(entry["canonical"],
                             [row["package"] for row in entry["superseded"]])


if __name__ == "__main__":
    unittest.main()
