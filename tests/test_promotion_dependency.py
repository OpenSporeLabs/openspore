"""Dependency promotion: a promoted package that really unblocks its callers.

``test_promotion.py`` owns "may this package enter ``src/``". This file owns the
question that follows it: once it is in ``src/``, may the scheduler stop treating
its callers as blocked? The two answers are separate on purpose, and this suite
is what proves the second one cannot be had for free.

The mechanism under test is a single manifest transition.
``reconstruction_knowledge.status_for`` reads ``body_status`` /
``integration_status``; ``schedule._reconstructed`` reads the projection built
from that; ``frontier._score`` drops a callee from ``open_callees`` when the
callee is ``reconstructed``. So writing ``integrated`` onto a promoted VA makes
its callers independent in ``schedule.classify``, eligible in ``frontier``, and
moves them into an earlier wave -- three views of one predicate. Every test here
observes all three, through the production functions, never through a copy of
the rule.

What the suite holds still:

* a dependency is satisfied only by a real promotion: static ``PASS`` +
  runtime ``GATED``, a test TU, a provenance record, and a **green recorded
  build verdict**. A skipped gate is not a green gate;
* a compile failure can never produce a satisfied dependency, so a red verdict
  leaves every caller ``deferred``;
* the runtime axis cannot leak: the runtime keys of the manifest entry are
  byte-identical across the write, ``status_for`` never returns a runtime state,
  and ``runtime.validated`` stays falsy. A promoted package is runtime-``GATED``
  forever, and satisfying a dependency is a statement about the reconstruction,
  not an observation of the original process;
* the write is atomic, idempotent, and reversible: a crash mid-write leaves a
  valid manifest that can be re-run, a re-run writes nothing, and ``unsatisfy``
  restores the prior status from the ``change_log`` and re-defers the callers;
* the call graph is read from the real xref table, read-only, and the committed
  knowledge graph is never written.

The synthetic graph is the shared one from
:mod:`tests.orchestration_fixture`: ``A``, ``B`` and ``D`` are called by ``C``
and by nothing else, so ``C`` is the only dependent and it is dependent on
exactly those three. Satisfying ``B`` alone must therefore *not* move ``C`` --
which is the sharper half of the test, because a rule that unblocked a caller
whose other prerequisites are open would be a bug the happy path would hide.

Nothing here writes outside its own ``mkdtemp``. The one test that reads the
committed ``knowledgegraph/spore.db`` opens it ``mode=ro`` and fingerprints it
before and after to prove it did not move.

Run from the repo root::

    python3 -m unittest tests.test_promotion_dependency -v
"""

import hashlib
import json
import sqlite3
import sys
import types
import unittest
from io import StringIO
from pathlib import Path

try:
    from tools import reconstruction_knowledge as rk
except ImportError as exc:  # pragma: no cover - off-repo-root only
    raise RuntimeError("reconstruction knowledge module is unavailable") from exc

from tools.reconstruction_tooling import cli
from tools.reconstruction_tooling import frontier as frontier_mod
from tools.reconstruction_tooling import promote
from tools.reconstruction_tooling import satisfy
from tools.reconstruction_tooling import schedule as sched

from tests import orchestration_fixture as fx

GATE_MODULE = "tools.reconstruction_tooling.build_gate"
# The fixture's own vocabulary: C is the only dependent, and A/B/D are the only
# things it calls. Naming them here keeps the assertions readable and keeps them
# derived from the fixture rather than from a second hardcoded graph.
DEPENDENT = "C"
PREREQS = ("A", "B", "D")
PROBE_CALLEE = "B"

HEADER = """#pragma once

namespace openspore::reconstruction::%(package)s {

int Dep(void *self, int value);

}  // namespace openspore::reconstruction::%(package)s
"""

SOURCE = """#include "%(stem)s.hpp"

namespace openspore::reconstruction::%(package)s {

int Dep(void *self, int value) {
  (void)self;
  return value - 1;
}

}  // namespace openspore::reconstruction::%(package)s
"""

TEST_SOURCE = """#include "%(stem)s.hpp"

#include <cstdlib>

namespace {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

}  // namespace

int main() {
  using namespace openspore::reconstruction::%(package)s;
  check(Dep(nullptr, 2) == 1);
  return 0;
}
"""


def _package_for(key):
    # type: (str) -> tuple
    """``(package, src_package, stem)`` for a fixture key.

    The package name is suffixed so the promoted directory never collides with
    the fixture's own ``src/reconstruction/pkg_synth_<key>/`` -- ``promote``
    refuses to install over a drifted package, and a collision would make every
    promotion in this file a ``drifted_existing`` refusal.
    """
    stem = "%s_dep" % key.lower()
    return ("pkg-synth-%s-dep" % key.lower(), "pkg_synth_%s_dep" % key.lower(), stem)


def _gate_green(package, step="compile"):
    return {"schema": "openspore-build-gate-1", "ok": True,
            "steps": [{"name": step, "ok": True, "returncode": 0}],
            "tests": [{"name": "recon_%s_%s_test" % (package, "x"), "ok": True,
                       "returncode": 0}],
            "packages": {package: {"ok": True, "status": "ok"}}}


def _gate_red(package):
    return {"schema": "openspore-build-gate-1", "ok": False,
            "steps": [{"name": "compile", "ok": False, "returncode": 1}],
            "tests": [], "packages": {package: {"ok": False, "status": "test_failed"}}}


class GateStub(object):
    """Stand-in for the compile-and-test gate, deciding green or red explicitly.

    The gate is another agent's module and a promotion that is not gated is the
    failure this file exists to prevent, so the verdict is chosen here rather
    than earned by a compiler. The recorded verdict keeps a non-empty ``steps``
    on purpose: satisfy must reject a *skipped* gate, and a stub that reported
    one would hide that.
    """

    def __init__(self):
        self.ok = True
        self.calls = []

    def install(self, test):
        module = types.ModuleType(GATE_MODULE)
        outer = self

        def gate(root, packages=None, build_dir=None, jobs=None, **kwargs):
            outer.calls.append({"root": str(root), "packages": list(packages or [])})
            for name in packages or ():
                return json.loads(json.dumps(
                    _gate_green(name) if outer.ok else _gate_red(name)))
            return json.loads(json.dumps(_gate_green("")))

        module.gate = gate
        package, name = GATE_MODULE.rsplit(".", 1)
        previous = getattr(sys.modules[package], name, None)
        sys.modules[GATE_MODULE] = module
        setattr(sys.modules[package], name, module)

        def restore():
            sys.modules.pop(GATE_MODULE, None)
            if previous is not None:
                sys.modules[GATE_MODULE] = previous
                setattr(sys.modules[package], name, previous)
            else:
                delattr(sys.modules[package], name)

        test.addCleanup(restore)


class DependencyCase(fx.FixtureTestCase):
    """A fixture root with promotion artifacts, and the views to observe it."""

    def setUp(self):
        super(DependencyCase, self).setUp()
        self.gate = GateStub()
        self.gate.install(self)

    # -- promotion ---------------------------------------------------------- #
    def ensure_root(self):
        # type: () -> str
        """The synthetic root, built on first use.

        ``make_root`` is deliberately not called twice: it names a fresh
        directory per call, so a second call would orphan the staged package
        the first one installed.
        """
        if self.info is None:
            self.make_root()
        return self.info["root"]

    def promote_key(self, key, static="PASS", runtime="GATED", tests=True,
                    green=True):
        # type: (str, str, str, bool, bool) -> str
        """Stage, validate and promote one synthetic target. Returns its VA."""
        self.stage_key(key, static, runtime, tests)
        self.gate.ok = green
        result = promote.apply(Path(self.ensure_root()), package=_package_for(key)[0])
        self.assertEqual(result["status"], "ok", result.get("refused"))
        self.assertTrue((Path(self.ensure_root()) / "src/reconstruction"
                         / _package_for(key)[1] / "promotion.json").is_file())
        fx.clear_index_cache()
        return fx.TARGETS[key]["va"]

    def stage_key(self, key, static="PASS", runtime="GATED", tests=True):
        # type: (str, str, str, bool) -> str
        """Write the staging package and the evidence a promotion reads."""
        package, src_package, stem = _package_for(key)
        bare = fx.bare(fx.TARGETS[key]["va"])
        staging = Path(self.ensure_root()) / "reconstruction/staging" / package
        staging.mkdir(parents=True, exist_ok=True)
        fields = {"package": src_package, "stem": stem}
        (staging / (stem + ".hpp")).write_text(HEADER % fields, encoding="utf-8")
        (staging / (stem + ".cpp")).write_text(SOURCE % fields, encoding="utf-8")
        if tests:
            (staging / (stem + "_test.cpp")).write_text(TEST_SOURCE % fields, encoding="utf-8")
        metadata = Path(self.ensure_root()) / "reconstruction/metadata" / package
        metadata.mkdir(parents=True, exist_ok=True)
        (metadata / (bare + ".json")).write_text(json.dumps(
            {"va": fx.TARGETS[key]["va"], "package": package,
             "normalized_symbol": "synth::%s::Dep" % key}), encoding="utf-8")
        evidence = Path(self.ensure_root()) / "reconstruction/evidence" / bare
        evidence.mkdir(parents=True, exist_ok=True)
        (evidence / "evidence.json").write_text(json.dumps(
            {"schema": "openspore-evidence-1", "target": fx.TARGETS[key]["va"],
             "binary": {"sha256": "b" * 64}}), encoding="utf-8")
        self.write_validation(bare, package, stem, static, runtime)
        return fx.TARGETS[key]["va"]

    def write_validation(self, bare, package, stem, static="PASS", runtime="GATED"):
        source = "reconstruction/staging/%s/%s.cpp" % (package, stem)
        payload = (Path(self.info["root"]) / source).read_bytes()
        report = {
            "schema": "openspore-structural-validation-1",
            "target": "0x" + bare,
            "status": static,
            "source": {"path": source, "role": "staging",
                       "sha256": hashlib.sha256(payload).hexdigest()},
            "static": {"dimension": "STATIC", "status": static, "checks": {}},
            "runtime": {"dimension": "RUNTIME", "status": runtime,
                        "gated": runtime == "GATED", "gates": [],
                        "validated": 0,
                        "reason": "the original process was never observed"},
        }
        path = Path(self.info["root"]) / "reconstruction/evidence" / bare / "validation.json"
        path.write_text(json.dumps(report, indent=2, sort_keys=True) + "\n", encoding="utf-8")
        return path

    def record_path(self, va):
        return (Path(self.info["root"]) / "reconstruction/evidence"
                / fx.bare(va) / "promotion.json")

    def rewrite_record_build(self, va, build):
        path = self.record_path(va)
        document = json.loads(path.read_text(encoding="utf-8"))
        document["build"] = build
        path.write_text(json.dumps(document, indent=2, sort_keys=True) + "\n", encoding="utf-8")
        return document

    def read_marker(self, key):
        _package, src_package, _stem = _package_for(key)
        return json.loads((Path(self.info["root"]) / "src/reconstruction"
                           / src_package / "promotion.json").read_text(encoding="utf-8"))

    def marker_path(self, key):
        _package, src_package, _stem = _package_for(key)
        return (Path(self.info["root"]) / "src/reconstruction" / src_package / "promotion.json")

    def rewrite_marker(self, key, **fields):
        path = self.marker_path(key)
        document = json.loads(path.read_text(encoding="utf-8"))
        document["targets"][0].update(fields)
        path.write_text(json.dumps(document, indent=2, sort_keys=True) + "\n", encoding="utf-8")

    def rewrite_marker_tests(self, key, tests):
        self.rewrite_marker(key, tests=tests)

    # -- the three views ---------------------------------------------------- #
    def manifest(self):
        return json.loads((Path(self.info["root"]) / fx.MANIFEST_REL).read_text(encoding="utf-8"))

    def manifest_entry(self, va):
        for function in self.manifest()["functions"]:
            if function.get("va") == va:
                return function
        self.fail("no manifest entry for %s" % va)

    def frontier_target(self, va):
        survey = frontier_mod.frontier(
            Path(self.info["root"]),
            type("Args", (), {"limit": 1000, "offset": 0})())
        for target in survey["targets"]:
            if target["va"] == va:
                return target
        self.fail("%s is not in the frontier" % va)

    def planned(self, va):
        for target in self.plan(limit=100)["targets"]:
            if target["va"] == va:
                return target
        self.fail("%s is not in the plan" % va)

    def wave_of(self, va):
        planning = self.plan(limit=100)
        for wave in planning["waves"]:
            for entry in wave["targets"]:
                if entry["va"] == va:
                    return wave["index"]
        return None

    def codes(self, document, va):
        for candidate in document["candidates"]:
            if candidate["va"] == va:
                return sorted(item["code"] for item in candidate["blockers"])
        return []

    def blocked_on(self, va, callee):
        """``(role, disposition, open_callees)`` of ``va`` in both views."""
        planned = self.planned(va)
        target = self.frontier_target(va)
        return (planned["role"], target["disposition"],
                target.get("open_dependencies") or [])


def _index_records(root):
    index, _bootstrap = rk.build_index(root)
    return index["records"]


class FullChainTest(DependencyCase):
    """The end-to-end proof: a real promotion really moves a real caller.

    Asserted through the production functions and in this order, because each
    step is the precondition of the next: ``schedule.classify`` (role),
    ``frontier`` (disposition), ``schedule.waves`` (wave index). The names come
    from the fixture's own edge table, so the test cannot describe a graph it
    did not build.
    """

    def test_satisfying_the_only_prerequisite_flips_the_dependent(self):
        self.make_root()
        dependent = fx.TARGETS[DEPENDENT]["va"]
        for key in PREREQS:
            self.promote_key(key)
        for key in PREREQS:
            self.assertEqual(self.promote_key(key), fx.TARGETS[key]["va"])

        before_role, before_disposition, before_open = self.blocked_on(
            dependent, None)
        self.assertEqual(before_role, "dependent")
        self.assertEqual(before_disposition, "deferred")
        self.assertEqual(sorted(before_open),
                         sorted(fx.TARGETS[key]["va"] for key in PREREQS))
        before_wave = self.wave_of(dependent)
        self.assertIsNotNone(before_wave)
        self.assertGreater(before_wave, self.wave_of(fx.TARGETS["A"]["va"]))

        satisfied = []
        for key in PREREQS:
            va = fx.TARGETS[key]["va"]
            result = satisfy.apply(self.info["root"], vas=[va],
                                   reason="test", implementer_id="t-1")
            self.assertEqual(result["status"], "ok", result["refused"])
            self.assertEqual(result["satisfied"], [va])
            satisfied.append(va)
        self.assertEqual(satisfied, [fx.TARGETS[key]["va"] for key in PREREQS])

        after_role, after_disposition, after_open = self.blocked_on(dependent, None)
        self.assertEqual(after_role, "independent")
        self.assertEqual(after_disposition, "eligible")
        self.assertEqual(after_open, [])
        self.assertEqual(self.wave_of(dependent), 0)
        self.assertLess(self.wave_of(dependent), before_wave)
        for key in PREREQS:
            # A satisfied prerequisite leaves the plan entirely: the frontier
            # excludes it, and a target that is not in the plan cannot occupy a
            # wave. That is why the dependent's wave index is the only place a
            # wave comparison is meaningful.
            self.assertEqual(self.frontier_target(fx.TARGETS[key]["va"])["disposition"],
                             "excluded")
            self.assertIsNone(self.wave_of(fx.TARGETS[key]["va"]))
        self.assertEqual(satisfy.unblock_dependents(self.info["root"], dependent), [])

    def test_one_prerequisite_does_not_move_a_dependent_with_others_open(self):
        self.make_root()
        dependent = fx.TARGETS[DEPENDENT]["va"]
        probe = fx.TARGETS[PROBE_CALLEE]["va"]
        for key in PREREQS:
            self.promote_key(key)
        result = satisfy.apply(self.info["root"], vas=[probe], reason="test")
        self.assertEqual(result["satisfied"], [probe])
        self.assertEqual(result["unblocked"][probe], [])
        role, disposition, open_callees = self.blocked_on(dependent, None)
        self.assertEqual(role, "dependent")
        self.assertEqual(disposition, "deferred")
        self.assertEqual(sorted(open_callees),
                         sorted(fx.TARGETS[key]["va"] for key in ("A", "D")))
        for key in ("A", "D"):
            satisfy.apply(self.info["root"], vas=[fx.TARGETS[key]["va"]], reason="test")
        self.assertEqual(satisfy.unblock_dependents(self.info["root"], probe),
                         [dependent])
        self.assertEqual(self.frontier_target(dependent)["disposition"], "eligible")

    def test_dependents_unblocked_names_the_real_caller_before_the_write(self):
        self.make_root()
        probe = fx.TARGETS[PROBE_CALLEE]["va"]
        dependent = fx.TARGETS[DEPENDENT]["va"]
        self.promote_key(PROBE_CALLEE)
        document = satisfy.plan(self.info["root"], vas=[probe])
        candidate = document["candidates"][0]
        self.assertEqual(candidate["dependents_unblocked"], [dependent])
        self.assertEqual(candidate["needs_satisfied"], True)
        self.assertEqual(document["summary"]["dependents_unblocked"], 1)


class RefusalTest(DependencyCase):
    """A refusal is a machine-readable reason, and it writes nothing."""

    def assert_refused(self, va, code):
        self.ensure_root()
        before = self.manifest()
        document = satisfy.plan(self.info["root"], vas=[va])
        self.assertIn(code, self.codes(document, va))
        result = satisfy.apply(self.info["root"], vas=[va], reason="test")
        self.assertEqual(result["status"], "blocked")
        self.assertEqual(result["changed"], False)
        self.assertEqual(result["satisfied"], [])
        self.assertEqual(sorted(item["code"] for item in result["refused"][0]["blockers"]),
                         sorted(item["code"] for item in
                                [candidate for candidate in document["candidates"]
                                 if candidate["va"] == va][0]["blockers"]))
        self.assertEqual(self.manifest(), before)
        return result

    def test_static_warn_runtime_gated_refused(self):
        self.promote_key(PROBE_CALLEE)
        self.rewrite_marker(PROBE_CALLEE, static_status="WARN")
        result = self.assert_refused(fx.TARGETS[PROBE_CALLEE]["va"],
                                     "not_static_validated")
        self.assertEqual(result["refused"][0]["src_package"],
                         _package_for(PROBE_CALLEE)[1])
        document = satisfy.plan(self.info["root"], vas=[fx.TARGETS[PROBE_CALLEE]["va"]])
        self.assertEqual(document["candidates"][0]["static_status"], "WARN")
        self.assertEqual(document["candidates"][0]["runtime_status"], "GATED")

    def test_static_pass_runtime_pass_refused(self):
        self.promote_key(PROBE_CALLEE)
        self.rewrite_marker(PROBE_CALLEE, runtime_status="PASS")
        self.assert_refused(fx.TARGETS[PROBE_CALLEE]["va"], "not_static_validated")

    def test_promote_itself_refuses_the_same_composition(self):
        # The composition is refused twice over: the promotion engine never
        # installs such a package, and satisfy refuses an installed one whose
        # marker drifted. Neither is a second rule; both read the same two
        # statuses.
        self.stage_key(PROBE_CALLEE, static="WARN")
        result = promote.apply(Path(self.ensure_root()),
                              package=_package_for(PROBE_CALLEE)[0])
        self.assertEqual(result["status"], "blocked")
        self.assertFalse(self.marker_path(PROBE_CALLEE).exists())
        codes = self.codes(satisfy.plan(self.info["root"],
                                        vas=[fx.TARGETS[PROBE_CALLEE]["va"]]),
                           fx.TARGETS[PROBE_CALLEE]["va"])
        self.assertIn("not_promoted", codes)

    def test_recorded_red_build_refused(self):
        va = self.promote_key(PROBE_CALLEE)
        self.rewrite_record_build(va, _gate_red(_package_for(PROBE_CALLEE)[1]))
        self.assert_refused(va, "build_not_green")

    def test_skipped_gate_is_not_a_green_gate(self):
        va = self.promote_key(PROBE_CALLEE)
        self.rewrite_record_build(va, {"schema": "openspore-build-gate-1", "ok": True,
                                       "steps": [], "note": "gate skipped by request"})
        self.assert_refused(va, "build_not_green")

    def test_missing_build_verdict_is_not_a_green_gate(self):
        va = self.promote_key(PROBE_CALLEE)
        self.rewrite_record_build(va, None)
        self.assert_refused(va, "build_not_green")

    def test_no_test_refused(self):
        va = self.promote_key(PROBE_CALLEE)
        self.rewrite_marker_tests(PROBE_CALLEE, [])
        self.assert_refused(va, "no_test")

    def test_missing_promotion_record_refused(self):
        va = self.promote_key(PROBE_CALLEE)
        self.record_path(va).unlink()
        self.assert_refused(va, "no_promotion_record")

    def test_unpromoted_va_refused(self):
        self.ensure_root()
        result = self.assert_refused(fx.TARGETS[PROBE_CALLEE]["va"], "not_promoted")

    def test_refusal_of_one_va_does_not_write_the_other(self):
        self.make_root()
        good = self.promote_key(PROBE_CALLEE)
        bad = self.promote_key("A")
        self.rewrite_record_build(bad, _gate_red(_package_for("A")[1]))
        before = self.manifest_entry(bad)
        result = satisfy.apply(self.info["root"], vas=[good, bad], reason="test")
        self.assertEqual(result["status"], "blocked")
        self.assertEqual(result["satisfied"], [good])
        self.assertEqual(result["summary"]["refused"], 1)
        self.assertEqual(result["refused"][0]["va"], bad)
        self.assertEqual(self.manifest_entry(bad), before)
        self.assertEqual(self.manifest_entry(good)["body_status"], "integrated")

    def test_dry_run_writes_nothing(self):
        self.make_root()
        va = self.promote_key(PROBE_CALLEE)
        before = self.manifest()
        result = satisfy.apply(self.info["root"], vas=[va], reason="test", dry_run=True)
        self.assertEqual(result["status"], "ok")
        self.assertEqual(result["changed"], False)
        self.assertEqual(result["satisfied"], [])
        self.assertEqual(result["would_satisfy"], [va])
        self.assertEqual(self.manifest(), before)


class NoFalseSatisfactionTest(DependencyCase):
    """A build that is not proven green must never become a satisfied dependency.

    This is the whole point of the bridge, stated as a negative: the failure it
    must make impossible is a red package whose callers the scheduler releases.
    """

    def test_red_verdict_leaves_every_caller_deferred(self):
        self.make_root()
        dependent = fx.TARGETS[DEPENDENT]["va"]
        for key in PREREQS:
            va = self.promote_key(key)
            self.rewrite_record_build(va, _gate_red(_package_for(key)[1]))
        result = satisfy.apply(
            self.info["root"],
            vas=[fx.TARGETS[key]["va"] for key in PREREQS], reason="test")
        self.assertEqual(result["status"], "blocked")
        self.assertEqual(result["satisfied"], [])
        self.assertEqual(sorted(item["code"] for item in result["refused"][0]["blockers"]),
                         ["build_not_green"])
        role, disposition, open_callees = self.blocked_on(dependent, None)
        self.assertEqual(role, "dependent")
        self.assertEqual(disposition, "deferred")
        self.assertEqual(sorted(open_callees),
                         sorted(fx.TARGETS[key]["va"] for key in PREREQS))
        records = _index_records(self.info["root"])
        for key in PREREQS:
            self.assertFalse(records[fx.TARGETS[key]["va"]]["reconstructed"])
        self.assertFalse(records[dependent]["reconstructed"])

    def test_no_static_validated_token_is_ever_emitted(self):
        self.make_root()
        va = self.promote_key(PROBE_CALLEE)
        before = rk.status_for(self.manifest_entry(va), {})
        satisfy.apply(self.info["root"], vas=[va], reason="test")
        after = rk.status_for(self.manifest_entry(va), {})
        self.assertNotIn("STATIC_VALIDATED", json.dumps(
            {"before": before, "after": after}))


class RuntimeLeakTest(DependencyCase):
    """The runtime axis is an open gate and stays one across the write."""

    def snapshot(self, va):
        entry = dict(self.manifest_entry(va))
        return ({key: entry.get(key) for key in satisfy.RUNTIME_KEYS}, entry)

    def test_runtime_keys_are_byte_identical_across_the_write(self):
        self.make_root()
        va = self.promote_key(PROBE_CALLEE)
        # A runtime-gated record, so the test would notice a write that dropped
        # a gate as easily as one that invented a validation.
        path = Path(self.info["root"]) / fx.MANIFEST_REL
        document = json.loads(path.read_text(encoding="utf-8"))
        for function in document["functions"]:
            if function.get("va") == va:
                function["runtime_gate"] = "gate-synth-open"
                function["runtime_gates"] = ["gate-synth-open", "gate-synth-second"]
                function["audit_runtime_gated"] = True
                function["runtime_validated"] = 0
        path.write_text(json.dumps(document, indent=2, sort_keys=True) + "\n", encoding="utf-8")
        before, before_entry = self.snapshot(va)
        result = satisfy.apply(self.info["root"], vas=[va], reason="test")
        self.assertEqual(result["satisfied"], [va])
        after, after_entry = self.snapshot(va)
        self.assertEqual(after, before)
        self.assertEqual(_changed_keys(before_entry, after_entry),
                         {"body_status", "integration_status", "source_files"})

    def test_satisfying_reports_reconstructed_not_a_runtime_state(self):
        self.make_root()
        va = self.promote_key(PROBE_CALLEE)
        satisfy.apply(self.info["root"], vas=[va], reason="test")
        status = rk.status_for(self.manifest_entry(va), {})
        self.assertEqual(status, "reconstructed")
        self.assertNotIn(status, ("runtime_gated", "runtime_validated"))
        records = _index_records(self.info["root"])
        self.assertTrue(records[va]["reconstructed"])
        self.assertFalse(records[va]["runtime"]["validated"])

    def test_no_runtime_field_is_written_even_when_absent(self):
        self.make_root()
        va = self.promote_key(PROBE_CALLEE)
        path = Path(self.info["root"]) / fx.MANIFEST_REL
        document = json.loads(path.read_text(encoding="utf-8"))
        for function in document["functions"]:
            if function.get("va") == va:
                for key in satisfy.RUNTIME_KEYS:
                    function.pop(key, None)
        path.write_text(json.dumps(document, indent=2, sort_keys=True) + "\n", encoding="utf-8")
        before = self.manifest_entry(va)
        satisfy.apply(self.info["root"], vas=[va], reason="test")
        after = self.manifest_entry(va)
        self.assertEqual([key for key in satisfy.RUNTIME_KEYS if key in after], [])
        self.assertEqual(_changed_keys(before, after),
                         {"body_status", "integration_status", "source_files"})


def _changed_keys(before, after):
    return {key for key in set(before) | set(after) if before.get(key) != after.get(key)}


class AtomicityTest(DependencyCase):
    """A write that dies half way leaves a manifest that can be re-run."""

    def test_crash_before_the_rename_leaves_the_manifest_valid(self):
        self.make_root()
        va = self.promote_key(PROBE_CALLEE)
        before = (Path(self.info["root"]) / fx.MANIFEST_REL).read_bytes()
        saved = rk.write_json_atomic

        def explode(path, document):
            raise OSError("simulated crash mid-write")

        rk.write_json_atomic = explode
        self.addCleanup(setattr, rk, "write_json_atomic", saved)
        with self.assertRaises(OSError):
            satisfy.apply(self.info["root"], vas=[va], reason="test")
        rk.write_json_atomic = saved
        after = (Path(self.info["root"]) / fx.MANIFEST_REL).read_bytes()
        self.assertEqual(after, before)
        self.assertEqual(len(json.loads(after.decode("utf-8"))["functions"]),
                         len(json.loads(before.decode("utf-8"))["functions"]))
        leftovers = [item.name for item in
                     (Path(self.info["root"]) / "knowledgegraph/research").iterdir()
                     if item.name.startswith("source-reconstruction-manifest.json.")]
        self.assertEqual(leftovers, [])
        result = satisfy.apply(self.info["root"], vas=[va], reason="test")
        self.assertEqual(result["satisfied"], [va])
        self.assertNotEqual((Path(self.info["root"]) / fx.MANIFEST_REL).read_bytes(), before)

    def test_change_log_records_the_prior_status(self):
        self.make_root()
        va = self.promote_key(PROBE_CALLEE)
        prior = self.manifest_entry(va).get("body_status")
        satisfy.apply(self.info["root"], vas=[va], reason="why",
                      implementer_id="t-9")
        entries = [entry for entry in self.manifest()["change_log"]
                   if entry.get("kind") == "satisfy"]
        self.assertEqual(len(entries), 1)
        self.assertEqual(entries[0]["reason"], "why")
        self.assertEqual(entries[0]["implementer_id"], "t-9")
        self.assertEqual(entries[0]["rows"][0]["prior_body_status"], prior)
        self.assertEqual(entries[0]["rows"][0]["va"], va)
        self.assertEqual(entries[0]["rows"][0]["promotion_record"],
                         "reconstruction/evidence/%s/promotion.json" % fx.bare(va))

    def test_only_the_permitted_manifest_keys_change(self):
        self.make_root()
        va = self.promote_key(PROBE_CALLEE)
        path = Path(self.info["root"]) / fx.MANIFEST_REL
        before = json.loads(path.read_text(encoding="utf-8"))
        satisfy.apply(self.info["root"], vas=[va], reason="test")
        after = json.loads(path.read_text(encoding="utf-8"))
        permitted = {"body_status", "integration_status", "source_file", "source_files"}
        for old, new in zip(before["functions"], after["functions"]):
            if old.get("va") == va:
                changed = {key for key in set(old) | set(new)
                           if old.get(key) != new.get(key)}
                self.assertTrue(changed <= permitted, sorted(changed))
            else:
                self.assertEqual(old, new)
        self.assertEqual({key for key in set(before) | set(after)
                          if before.get(key) != after.get(key)},
                         {"functions", "change_log"})


class IdempotenceTest(DependencyCase):
    """Re-running over a satisfied VA writes nothing at all."""

    def test_second_apply_changes_nothing(self):
        self.make_root()
        va = self.promote_key(PROBE_CALLEE)
        first = satisfy.apply(self.info["root"], vas=[va], reason="test")
        self.assertEqual(first["changed"], True)
        self.assertEqual(first["idempotent"], False)
        before = (Path(self.info["root"]) / fx.MANIFEST_REL).read_bytes()
        index_before = (Path(self.info["root"])
                        / "reconstruction/knowledge/index.json").read_bytes()
        second = satisfy.apply(self.info["root"], vas=[va], reason="test")
        self.assertEqual(second["status"], "ok")
        self.assertEqual(second["changed"], False)
        self.assertEqual(second["idempotent"], True)
        self.assertEqual(second["satisfied"], [])
        self.assertEqual(second["already_satisfied"], [va])
        self.assertEqual(second["refused"], [])
        self.assertEqual((Path(self.info["root"]) / fx.MANIFEST_REL).read_bytes(), before)
        self.assertEqual((Path(self.info["root"])
                          / "reconstruction/knowledge/index.json").read_bytes(),
                         index_before)

    def test_already_satisfied_is_reported_even_when_the_marker_is_broken(self):
        self.make_root()
        va = self.promote_key(PROBE_CALLEE)
        satisfy.apply(self.info["root"], vas=[va], reason="test")
        self.rewrite_record_build(va, _gate_red(_package_for(PROBE_CALLEE)[1]))
        result = satisfy.apply(self.info["root"], vas=[va], reason="test")
        self.assertEqual(result["status"], "ok")
        self.assertEqual(result["already_satisfied"], [va])
        self.assertEqual(result["changed"], False)
        self.assertIn("build_not_green", self.codes(
            satisfy.plan(self.info["root"], vas=[va]), va))


class ReversalTest(DependencyCase):
    """A failure after a promotion must be able to re-defer the callers."""

    def test_unsatisfy_restores_the_prior_status_and_re_defers(self):
        self.make_root()
        dependent = fx.TARGETS[DEPENDENT]["va"]
        for key in PREREQS:
            self.promote_key(key)
        prior = {key: self.manifest_entry(fx.TARGETS[key]["va"]).get("body_status")
                 for key in PREREQS}
        satisfy.apply(self.info["root"],
                      vas=[fx.TARGETS[key]["va"] for key in PREREQS], reason="test")
        self.assertEqual(self.frontier_target(dependent)["disposition"], "eligible")
        result = satisfy.unsatisfy(
            self.info["root"], vas=[fx.TARGETS[key]["va"] for key in PREREQS],
            reason="regression in the model test")
        self.assertEqual(result["status"], "ok")
        self.assertEqual(result["changed"], True)
        for key in PREREQS:
            entry = self.manifest_entry(fx.TARGETS[key]["va"])
            self.assertEqual(entry.get("body_status"), prior[key])
            self.assertIsNone(entry.get("integration_status"))
        self.assertEqual(self.planned(dependent)["role"], "dependent")
        self.assertEqual(self.frontier_target(dependent)["disposition"], "deferred")

    def test_unsatisfy_without_a_change_log_entry_is_refused(self):
        self.make_root()
        va = self.promote_key(PROBE_CALLEE)
        result = satisfy.unsatisfy(self.info["root"], vas=[va], reason="test")
        self.assertEqual(result["status"], "blocked")
        self.assertEqual(result["changed"], False)
        self.assertEqual([item["code"] for item in result["refused"][0]["blockers"]],
                         ["no_change_log"])

    def test_unsatisfy_is_idempotent(self):
        self.make_root()
        va = self.promote_key(PROBE_CALLEE)
        satisfy.apply(self.info["root"], vas=[va], reason="test")
        satisfy.unsatisfy(self.info["root"], vas=[va], reason="test")
        before = (Path(self.info["root"]) / fx.MANIFEST_REL).read_bytes()
        again = satisfy.unsatisfy(self.info["root"], vas=[va], reason="test")
        self.assertEqual(again["changed"], False)
        self.assertEqual(again["idempotent"], True)
        self.assertEqual(again["already_satisfied"], [va])
        self.assertEqual((Path(self.info["root"]) / fx.MANIFEST_REL).read_bytes(), before)

    def test_resatisfy_after_a_rollback_converges(self):
        self.make_root()
        va = self.promote_key(PROBE_CALLEE)
        satisfy.apply(self.info["root"], vas=[va], reason="first")
        satisfy.unsatisfy(self.info["root"], vas=[va], reason="rollback")
        again = satisfy.apply(self.info["root"], vas=[va], reason="second")
        self.assertEqual(again["satisfied"], [va])
        self.assertEqual(again["status"], "ok")


class CallGraphTest(DependencyCase):
    """The dependency data is real, read read-only, and never written."""

    def test_dependents_come_from_the_seeded_xref_rows(self):
        self.make_root()
        probe = fx.TARGETS[PROBE_CALLEE]["va"]
        dependent = fx.TARGETS[DEPENDENT]["va"]
        self.promote_key(PROBE_CALLEE)
        seeded = {("0x" + row[0]) for row in fx.xref_rows(self.info["keys"])
                  if row[1] == fx.bare(probe)}
        self.assertEqual(seeded, {dependent})
        document = satisfy.plan(self.info["root"], vas=[probe])
        self.assertEqual(document["candidates"][0]["dependents_unblocked"],
                         sorted(seeded))
        result = satisfy.apply(self.info["root"], vas=[probe], reason="test")
        self.assertEqual(result["satisfied"], [probe])
        # C still calls A and D, so satisfying B alone unblocks nothing: the
        # caller set is real, and so is the requirement that all of it be met.
        self.assertEqual(result["unblocked"][probe], [])
        self.assertEqual(self.frontier_target(dependent)["disposition"], "deferred")

    def test_real_repository_xref_query_is_read_only(self):
        database = Path(fx.config.resolve("knowledgegraph", "spore.db"))
        if not database.is_file():
            self.skipTest("the committed knowledge graph is not present")
        target = "0x01021370"
        before = fx.committed_db_fingerprint()
        connection = sqlite3.connect("file:%s?mode=ro" % database, uri=True, timeout=5.0)
        try:
            query = ("SELECT caller_va, callee_va, reference_type FROM xref "
                     "WHERE callee_va=? AND reference_type IN (%s)"
                     % ",".join("?" * len(sched.CALL_REFERENCE_TYPES)))
            rows = connection.execute(
                query, (target[2:],) + sched.CALL_REFERENCE_TYPES).fetchall()
            with self.assertRaises(sqlite3.OperationalError):
                connection.execute("UPDATE xref SET source='written'")
        finally:
            connection.close()
        after = fx.committed_db_fingerprint()
        # The database is in WAL mode, so a read-only handle legitimately creates
        # the -shm/-wal side files. What must not change is the database itself:
        # the same bytes at the same mtime, which is what a write would break.
        for key in ("sha256", "mtime_ns"):
            self.assertEqual(after[key], before[key])
        self.assertTrue(rows, "the committed graph has no caller rows for %s" % target)
        for caller, callee, kind in rows:
            self.assertEqual(len(caller), 8)
            self.assertEqual(callee, target[2:])
            self.assertIn(kind, sched.CALL_REFERENCE_TYPES)
            int(caller, 16)

    def test_callers_are_also_read_from_the_evidence_pack(self):
        self.make_root()
        probe = fx.TARGETS[PROBE_CALLEE]["va"]
        self.promote_key(PROBE_CALLEE)
        path = (Path(self.info["root"]) / "reconstruction/evidence"
                / fx.bare(probe) / "evidence.json")
        document = json.loads(path.read_text(encoding="utf-8"))
        document["record"] = {"dependencies": {
            "callers": [{"va": fx.TARGETS[DEPENDENT]["va"]}],
            "edges": [{"direction": "in", "other": fx.TARGETS[DEPENDENT]["va"],
                       "reference_type": "direct-call"}]}}
        path.write_text(json.dumps(document), encoding="utf-8")
        found = satisfy._callers(Path(self.info["root"]), probe, None)
        self.assertEqual(found, [fx.TARGETS[DEPENDENT]["va"]])


class CliFixtureTest(DependencyCase):
    """The verbs driven through ``cli.main`` against a synthetic root.

    ``cli.main`` resolves the repository root from its own module attribute, so
    the root is pointed at the fixture for the length of the test and restored
    afterwards. That is the only way to observe the envelope a real ``apply``
    produces -- including the case where every named target is refused -- without
    writing to the real repository.
    """

    def setUp(self):
        super(CliFixtureTest, self).setUp()
        saved = cli.ROOT
        self.addCleanup(setattr, cli, "ROOT", saved)

    def run_cli(self, argv):
        argv = list(argv) + ["--json"]
        saved, sys.stdout = sys.stdout, StringIO()
        try:
            code = cli.main(argv)
            return code, json.loads(sys.stdout.getvalue())
        finally:
            sys.stdout = saved

    def point_at_fixture(self):
        self.make_root()
        cli.ROOT = Path(self.info["root"])
        return self.info["root"]

    def test_promote_apply_with_a_refusal_is_a_successful_command(self):
        root = self.point_at_fixture()
        package = _package_for(PROBE_CALLEE)[0]
        self.stage_key(PROBE_CALLEE, static="WARN")
        code, envelope = self.run_cli(["promote", "apply", package])
        self.assertEqual(code, 0)
        self.assertEqual(envelope["command"], "promote")
        self.assertEqual(envelope["status"], "ok")
        self.assertTrue(envelope["ok"])
        self.assertNotIn("code", envelope)
        result = envelope["result"]
        self.assertEqual(result["schema"], "openspore-promotion-result-1")
        self.assertEqual(result["status"], "blocked")
        self.assertEqual(result["summary"]["refused"], 1)
        self.assertEqual(result["refused"][0]["blockers"][0]["code"], "static_not_pass")
        self.assertEqual(len(envelope["warnings"]), 1)
        self.assertIn("apply_ok_with_refusals", envelope["warnings"][0])
        self.assertFalse((Path(root) / "src/reconstruction"
                          / _package_for(PROBE_CALLEE)[1]).exists())

    def test_satisfy_apply_with_a_refusal_is_a_successful_command(self):
        self.point_at_fixture()
        va = self.promote_key(PROBE_CALLEE)
        self.rewrite_record_build(va, _gate_red(_package_for(PROBE_CALLEE)[1]))
        before = self.manifest()
        code, envelope = self.run_cli(["satisfy", "apply", va, "--reason", "test"])
        self.assertEqual(code, 0)
        self.assertEqual(envelope["status"], "ok")
        self.assertTrue(envelope["ok"])
        self.assertNotIn("code", envelope)
        result = envelope["result"]
        self.assertEqual(result["schema"], "openspore-satisfy-result-1")
        self.assertEqual(result["status"], "blocked")
        self.assertEqual(result["refused"][0]["va"], va)
        self.assertEqual([item["code"] for item in result["refused"][0]["blockers"]],
                         ["build_not_green"])
        self.assertIn("apply_ok_with_refusals", envelope["warnings"][0])
        self.assertEqual(self.manifest(), before)

    def test_satisfy_apply_end_to_end_through_the_cli(self):
        self.point_at_fixture()
        for key in PREREQS:
            self.promote_key(key)
        dependent = fx.TARGETS[DEPENDENT]["va"]
        vas = [fx.TARGETS[key]["va"] for key in PREREQS]
        self.assertEqual(self.frontier_target(dependent)["disposition"], "deferred")
        code, envelope = self.run_cli(["satisfy", "apply"] + vas
                                      + ["--reason", "model tests green"])
        self.assertEqual(code, 0)
        self.assertTrue(envelope["ok"])
        self.assertEqual(envelope["warnings"], [])
        result = envelope["result"]
        self.assertEqual(result["status"], "ok")
        self.assertEqual(result["changed"], True)
        self.assertEqual(result["satisfied"], sorted(vas))
        for va in vas:
            self.assertEqual(result["unblocked"][va], [dependent])
        self.assertEqual(self.frontier_target(dependent)["disposition"], "eligible")
        self.assertEqual(self.planned(dependent)["role"], "independent")
        for va in vas:
            self.assertEqual(self.manifest_entry(va)["body_status"], "integrated")
        code, envelope = self.run_cli(["satisfy", "apply"] + vas)
        self.assertEqual(code, 0)
        self.assertEqual(envelope["result"]["changed"], False)
        self.assertEqual(envelope["result"]["already_satisfied"], sorted(vas))

    def test_satisfy_apply_dry_run_through_the_cli(self):
        self.point_at_fixture()
        va = self.promote_key(PROBE_CALLEE)
        before = self.manifest()
        code, envelope = self.run_cli(["satisfy", "apply", va, "--dry-run"])
        self.assertEqual(code, 0)
        self.assertTrue(envelope["ok"])
        result = envelope["result"]
        self.assertTrue(result["dry_run"])
        self.assertEqual(result["would_satisfy"], [va])
        self.assertEqual(result["satisfied"], [])
        self.assertEqual(result["changed"], False)
        self.assertEqual(self.manifest(), before)

    def test_both_verbs_reject_live_against_a_fixture_root(self):
        self.point_at_fixture()
        for argv in (["promote", "plan", _package_for(PROBE_CALLEE)[0], "--live"],
                     ["satisfy", "plan", fx.TARGETS[PROBE_CALLEE]["va"], "--live"]):
            code, envelope = self.run_cli(argv)
            self.assertEqual(code, 2)
            self.assertEqual(envelope["code"], "unsupported_option")

    def test_promote_plan_matches_the_action_and_package_shape(self):
        self.point_at_fixture()
        package = _package_for(PROBE_CALLEE)[0]
        self.promote_key(PROBE_CALLEE)
        code, envelope = self.run_cli(["promote", "plan", package])
        self.assertEqual(code, 0)
        self.assertEqual(envelope["result"]["schema"], "openspore-promotion-plan-1")
        self.assertTrue(envelope["result"]["candidates"][0]["promoted"])
        underscored = package.replace("-", "_")
        code, envelope = self.run_cli(["promote", "plan", underscored])
        self.assertEqual(code, 0)
        self.assertTrue(envelope["result"]["candidates"][0]["promoted"])


class CliTest(unittest.TestCase):
    """The two new verbs, on the real repository, read-only.

    ``cli.main`` resolves the repository root itself, so these are the only
    assertions that run against the committed tree. Both verbs used here are
    read-only (``plan``), so the real repository is not modified.
    """

    def run_cli(self, argv):
        argv = list(argv) + ["--json"]
        saved, sys.stdout = sys.stdout, StringIO()
        try:
            code = cli.main(argv)
            return code, sys.stdout.getvalue()
        finally:
            sys.stdout = saved

    def test_promote_plan_envelope(self):
        code, output = self.run_cli(["promote", "plan", "pkg-property-remove-006a2ef0"])
        self.assertEqual(code, 0)
        envelope = json.loads(output)
        self.assertEqual(envelope["$schema"], "openspore-cli-result-1")
        self.assertEqual(envelope["command"], "promote")
        self.assertEqual(envelope["status"], "ok")
        self.assertTrue(envelope["ok"])
        result = envelope["result"]
        self.assertEqual(result["schema"], "openspore-promotion-plan-1")
        self.assertTrue(result["ok"])
        for key in ("candidates", "summary"):
            self.assertIn(key, result)
        for key in ("candidates", "eligible", "promoted", "refused"):
            self.assertIn(key, result["summary"])
        for candidate in result["candidates"]:
            self.assertIn("va", candidate)
            self.assertIn("blockers", candidate)

    def test_satisfy_plan_envelope(self):
        code, output = self.run_cli(["satisfy", "plan", "0x01021370"])
        self.assertEqual(code, 0)
        envelope = json.loads(output)
        self.assertEqual(envelope["command"], "satisfy")
        self.assertEqual(envelope["status"], "ok")
        self.assertTrue(envelope["ok"])
        result = envelope["result"]
        self.assertEqual(result["schema"], "openspore-satisfy-plan-1")
        self.assertTrue(result["ok"])
        self.assertIn("candidates", result)
        for key in ("candidates", "admissible", "needs_satisfied",
                    "already_satisfied", "refused", "dependents_unblocked"):
            self.assertIn(key, result["summary"])
        candidate = result["candidates"][0]
        for key in ("va", "src_package", "promotion_record", "static_status",
                    "runtime_status", "current_status", "current_body_status",
                    "current_integration_status", "needs_satisfied",
                    "dependents_unblocked", "blockers"):
            self.assertIn(key, candidate)

    def test_satisfy_plan_rejects_live(self):
        code, output = self.run_cli(["satisfy", "plan", "0x01021370", "--live"])
        self.assertEqual(code, 2)
        envelope = json.loads(output)
        self.assertEqual(envelope["code"], "unsupported_option")
        self.assertFalse(envelope["ok"])

    def test_promote_apply_rejects_no_write(self):
        code, output = self.run_cli(["promote", "apply", "pkg-property-remove-006a2ef0",
                                     "--no-write"])
        self.assertEqual(code, 2)
        envelope = json.loads(output)
        self.assertEqual(envelope["code"], "unsupported_option")

    def test_both_verbs_reject_live(self):
        for argv in (["promote", "plan", "pkg-property-remove-006a2ef0", "--live"],):
            code, output = self.run_cli(argv)
            self.assertEqual(code, 2)
            self.assertEqual(json.loads(output)["code"], "unsupported_option")


if __name__ == "__main__":
    unittest.main()
