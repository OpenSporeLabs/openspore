"""Dependency scheduling, SCC coordination and multi-worker concurrency.

Companion to :mod:`tests.test_orchestration`, which owns the single-target
lifecycle and the queue/lease contract. This file owns the properties that only
exist *between* targets:

* the wave structure is a real dependency order and nothing else -- independent
  work is never serialized, and a dependent waits for exactly its prerequisites;
* a strongly-connected component is one dispatch unit, because mutual recursion
  cannot be ordered;
* ``package``, ``cluster`` and ``analogues`` never create an ordering edge;
* a wave that cannot make progress is reported, not looped;
* a claim has exactly one winner, a lease is recoverable, a displaced worker
  cannot write, and a finished run leaves no lease behind;
* the plan is byte-identical for identical inputs, and the committed knowledge
  graph is never touched.

Every test builds a synthetic root in its own tempdir via
:mod:`tests.orchestration_fixture` and points the queue at it through
``OPENSPORE_DB``. ``write=False`` everywhere, no Ghidra, no network, no
display, no Wine, no real ``spore.db``. No test sleeps: lease clocks are moved
with SQL backdating and ordering is established with ``threading.Barrier`` and
``time.monotonic``.

The synthetic graph (probed, not assumed -- see ``WaveStructureTest``):

* ``A``, ``B``, ``D`` each call nothing and are called only by ``C``; they are
  the first wave;
* ``C`` calls ``A``, ``B`` and ``D``, so it is the only dependent target and
  always lands in a strictly later wave;
* ``P`` and ``Q`` call each other -- a real 2-cycle, one dispatch unit;
* ``E1``..``E4`` are isolated: no call edge at all, one shared
  package/cluster, so they are the cleanest possible "do not serialize by
  package" case.

The ``-- S<n> --`` markers below map to the required-test list; three extra
tests are named ``test_pinned_*`` and carry the ``file:line`` of a production
defect they hold still (following the convention in
:mod:`tests.test_orchestration`).

Run from the repo root::

    python3 -m unittest tests.test_orchestration_scheduling -v
"""
import json
import os
import re
import sqlite3
import threading
import time
import unittest
from concurrent.futures import ThreadPoolExecutor

from tools.mcp import registry
from tools.reconstruction_tooling import orchestrate as orch
from tools.reconstruction_tooling import queue as q
from tools.reconstruction_tooling import schedule as sched

from tests import orchestration_fixture as fx

# Keys, in the fixture's own vocabulary.
PREREQ = ("A", "B", "D")
DEPENDENT = ("C",)
CYCLE = ("P", "Q")
FLAT = fx.FLAT_KEYS
# Eight distinct rows with no dependency between them: the ingestion-isolation
# and dual-run target set.
EIGHT = ("A", "B", "D", "P", "Q", "E1", "E2", "E3")

VA_OF = {key: fx.TARGETS[key]["va"] for key in fx.TARGETS}

# The documented end-to-end op sequence, in order (same constant as
# tests/test_orchestration.py; a record that deviates from it took a branch
# this file did not intend to exercise).
HAPPY_PATH_OPS = ["claim", "brief", "launch", "ingest", "validate", "checkpoint",
                  "close"]

# A plan must be reproducible byte for byte, so it may not carry a wall clock.
# These are the key names and the string shape that would make it irreproducible.
_CLOCK_KEYS = ("generated_at", "created_at", "updated_at", "planned_at",
               "started_at", "finished_at", "timestamp", "now", "mtime",
               "elapsed", "seconds", "duration", "wall_clock")
_CLOCK_RE = re.compile(r"\d{4}-\d{2}-\d{2}[T ]\d{2}:\d{2}")


def queue_op(**params):
    return registry.dispatch("queue_op", params)


def wave_of(plan):
    # type: (dict) -> dict
    """VA -> index of the wave that scheduled it (every wave, not just ready)."""
    return {entry["va"]: wave["index"]
            for wave in plan["waves"] for entry in wave["targets"]}


def ready_waves(plan):
    return [wave for wave in plan["waves"] if wave["reason"] == "ready"]


def by_va(plan):
    return {item["va"]: item for item in plan["targets"]}


def longest_call_chain(keys=()):
    # type: (tuple) -> int
    """The longest chain of ``fx.CALL_EDGES`` over ``keys``, in nodes.

    Derived from the fixture's own edge table rather than hardcoded, so the
    wave-depth assertion cannot drift away from the graph it describes.

    Strongly-connected components are contracted first (``sched._tarjan``): a
    mutual-recursion cycle is one dispatch unit with no depth *inside* it, and
    counting the cycle as a chain would demand wave boundaries the scheduler is
    explicitly forbidden from creating.
    """
    keys = set(keys)
    adjacency = {key: set() for key in keys}
    for caller, callee, _site in fx.CALL_EDGES:
        if caller in keys and callee in keys and caller != callee:
            adjacency[caller].add(callee)
    components = sched._tarjan(adjacency)
    component_of = {member: index
                    for index, group in enumerate(components) for member in group}
    condensed = {index: {component_of[callee] for callee in adjacency[member]
                         if component_of[callee] != index}
                 for index, group in enumerate(components) for member in group}
    depth = {}

    def measure(index):
        if index in depth:
            return depth[index]
        best = 1
        for sink in condensed[index]:
            best = max(best, 1 + measure(sink))
        depth[index] = best
        return best

    return max([measure(index) for index in range(len(components))] or [0])


def integrate(root, keys):
    # type: (str, tuple) -> list
    """Promote finished targets to ``reconstructed`` in the canonical manifest.

    This is the integrator's job in production, not the orchestrator's: a
    worker stages a candidate under ``reconstruction/staging/`` and the
    integrator promotes it, which is what ``reconstruction_knowledge.status_for``
    reads (``body_status == "integrated"`` -> ``reconstructed``). Until that
    happens the canonical index still lists the target as an open callee, and
    ``frontier._score`` keeps its caller deferred. Writing the manifest here is
    the only way a test can observe the second wave without a human in the loop.
    """
    wanted = {VA_OF[key] for key in keys}
    path = os.path.join(root, fx.MANIFEST_REL)
    with open(path, encoding="utf-8") as handle:
        document = json.load(handle)
    promoted = []
    for function in document["functions"]:
        if function["va"] in wanted:
            function["body_status"] = "integrated"
            promoted.append(function["va"])
    with open(path, "w", encoding="utf-8") as handle:
        handle.write(json.dumps(document, indent=2, sort_keys=True) + "\n")
    fx.clear_index_cache()
    return sorted(promoted)


def clock_leaks(document):
    # type: (object) -> list
    """Every path in ``document`` that carries a wall clock or elapsed time."""
    found = []

    def walk(node, path):
        if isinstance(node, dict):
            for name, item in sorted(node.items()):
                if name in _CLOCK_KEYS:
                    found.append("%s/%s = %r" % (path, name, item))
                walk(item, "%s/%s" % (path, name))
        elif isinstance(node, list):
            for index, item in enumerate(node):
                walk(item, "%s[%d]" % (path, index))
        elif isinstance(node, str) and _CLOCK_RE.search(node):
            found.append("%s = %r" % (path, node))

    walk(document, "")
    return found


def _partition_of(plan):
    # type: (dict) -> dict
    """Rebuild the plan's own SCC partition from its reported members.

    ``sched.classify``/``sched.waves`` are pure, so re-running them on the
    plan's own classified records is a legitimate way to prove the wave loop
    terminates -- and it also proves the wave structure is a function of the
    classification rather than of any hidden run-time state.
    """
    members = {}
    for item in plan["targets"]:
        members.setdefault(item["scc"]["id"], list(item["scc"]["members"]))
    id_by_va = {va: identifier
                for identifier, group in members.items() for va in group}
    return {"id_by_va": id_by_va,
            "members_by_id": dict(members),
            "cycle_members": {va: list(item["scc"]["cycle_members"])
                              for va, item in by_va(plan).items()},
            "edge_count": plan["summary"]["scc_evidence_edges"],
            "degraded": plan["summary"]["dependency_degraded"]}


def reset_row(path, inv_id):
    """Put one row back to ``queued`` with plain SQL (no sleeping in a test)."""
    connection = sqlite3.connect(path)
    try:
        connection.execute(
            "UPDATE investigations SET status='queued', implementer_id=NULL, "
            "block_reason=NULL, checkpoint=NULL, attempts=NULL, "
            "evidence_refs=NULL WHERE id=?", (inv_id,))
        connection.commit()
    finally:
        connection.close()


class BarrierWorker(fx.RecordingWorker):
    """``fx.worker`` plus a per-VA concurrency rendezvous.

    ``gate_vas`` names the targets that must be in flight *simultaneously*.
    Each gated caller increments an arrival counter on entry and then blocks on
    the :class:`threading.Barrier` itself, so the group is provably inside the
    worker body at the same moment. Callers outside ``gate_vas`` pass straight
    through -- a target the orchestrator legitimately dispatches later (a
    promoted dependent) must not be able to satisfy or break a barrier that is
    not about it. The arrival counter also caps the group at ``parties`` so a
    fourth gated caller could never deadlock on the same barrier.

    The anti-serialization property is the whole point: if the gated targets are
    dispatched one after another, the first arrival waits out ``timeout``, the
    barrier breaks, :class:`BrokenBarrierError` escapes ``process_target`` and
    surfaces in ``run()["summary"]["errors"]``, and ``gate.broken`` is true. The
    test then fails for the *right* reason (serialized) instead of passing on a
    timing coincidence.

    ``max_active`` is the number of worker invocations simultaneously inside the
    worker body -- a direct measurement of parallelism, not a proxy for it.
    """

    def __init__(self, variant="ok", gate_vas=(), parties=3, timeout=10):
        fx.RecordingWorker.__init__(self, variant)
        self.gate_vas = frozenset(gate_vas)
        self.parties = int(parties)
        self.gate = threading.Barrier(self.parties, timeout=timeout)
        self.gated = []
        self.max_active = 0
        self._arrived = 0
        self._active = 0
        self._guard = threading.Lock()

    def __call__(self, package):
        va = package["target"]["va"]
        with self._guard:
            self._active += 1
            self.max_active = max(self.max_active, self._active)
            rendezvous = False
            if va in self.gate_vas and self._arrived < self.parties:
                self._arrived += 1
                self.gated.append(va)
                rendezvous = True
        try:
            if rendezvous:
                self.gate.wait()
            return fx.RecordingWorker.__call__(self, package)
        finally:
            with self._guard:
                self._active -= 1


class TimelineWorker(fx.RecordingWorker):
    """``fx.worker`` plus a per-VA dispatch/finish timeline and a call hook.

    ``timeline[va]["dispatch"]`` is stamped before anything else happens and
    ``["finish"]`` after the worker returns, on the same ``time.monotonic()``
    clock, so "the dependent started only after every prerequisite had
    finished" is a real timestamp comparison and not an inference from wave
    order. ``hook`` is called in the same window, which is how a test lets a
    second actor interfere while the worker is in flight.
    """

    def __init__(self, variant="ok", hook=None, timeline=None):
        fx.RecordingWorker.__init__(self, variant)
        self.hook = hook
        self.timeline = {} if timeline is None else timeline

    def __call__(self, package):
        va = package["target"]["va"]
        self.timeline.setdefault(va, {})["dispatch"] = time.monotonic()
        if self.hook is not None:
            self.hook(self, package)
        try:
            raw, detail = fx.RecordingWorker.__call__(self, package)
        finally:
            self.timeline[va]["finish"] = time.monotonic()
        return raw, detail


class WaveStructureTest(fx.FixtureTestCase):
    """S1-S10: the wave structure, and only the wave structure."""

    # -- the graph itself, asserted before it is relied on ---------------- #
    def test_synthetic_graph_is_the_documented_shape(self):
        self.make_root(keys=fx.DEFAULT_KEYS + FLAT)
        plan = self.plan(limit=50)
        table = by_va(plan)
        prereq = [table[VA_OF[key]] for key in PREREQ]
        c = table[VA_OF["C"]]
        self.assertEqual([item["role"] for item in prereq],
                         ["independent"] * 3, prereq)
        self.assertEqual(c["role"], "dependent", c)
        self.assertEqual(c["open_callees"],
                         sorted(VA_OF[key] for key in PREREQ), c)
        self.assertEqual([table[VA_OF[key]]["role"] for key in CYCLE],
                         ["coordinated"] * 2)
        self.assertEqual(table[VA_OF["P"]]["scc"]["members"],
                         sorted(VA_OF[key] for key in CYCLE))
        self.assertEqual([item["role"] for item in
                          (table[VA_OF[key]] for key in FLAT)],
                         ["independent"] * 4)
        # the A/B/D <- C fan-in really is a fan-in and nothing else
        self.assertEqual(sorted(VA_OF[key] for key in PREREQ),
                         sorted(c["open_callees"]))
        self.assertFalse(plan["summary"]["dependency_degraded"])

    # -- S1 --------------------------------------------------------------- #
    def test_independent_targets_are_not_serialized(self):
        self.make_root(keys=fx.DEFAULT_KEYS)
        plan = self.plan(limit=50)
        waves = wave_of(plan)
        indexes = {key: waves[VA_OF[key]] for key in PREREQ}
        self.assertEqual(indexes, {"A": 0, "B": 0, "D": 0}, indexes)
        self.assertEqual(len(set(indexes.values())), 1,
                         "independent targets were split across waves: %r" % (indexes,))
        # and they really are one wave's worth of work, not three consecutive ones
        first = ready_waves(plan)[0]
        self.assertEqual(sorted(entry["va"] for entry in first["targets"]),
                         sorted(VA_OF[key] for key in PREREQ + CYCLE))
        self.assertEqual(plan["summary"]["wave_widths"], [5, 1],
                         plan["summary"]["wave_widths"])

    # -- S2 --------------------------------------------------------------- #
    def test_dependent_target_waits_for_its_prerequisites(self):
        self.make_root(keys=fx.DEFAULT_KEYS)
        plan = self.plan(limit=50)
        waves = wave_of(plan)
        c = by_va(plan)[VA_OF["C"]]
        self.assertEqual(sorted(c["open_callees"]),
                         sorted(VA_OF[key] for key in PREREQ), c)
        for key in PREREQ:
            self.assertGreater(waves[VA_OF["C"]], waves[VA_OF[key]],
                               "C (%d) is not after %s (%d)"
                               % (waves[VA_OF["C"]], key, waves[VA_OF[key]]))
        # the ordering is caused by the call edges and nothing else: C is the
        # only target with a non-empty open_callees
        table = by_va(plan)
        self.assertEqual(sorted(va for va, item in table.items()
                                if item["open_callees"]), [VA_OF["C"]])
        # a prerequisite does not wait on its dependent
        for key in PREREQ:
            self.assertNotIn(VA_OF["C"], table[VA_OF[key]]["open_callees"])

    # -- S7 --------------------------------------------------------------- #
    def test_scc_is_not_inferred_from_package_or_cluster(self):
        self.make_root(keys=FLAT)
        plan = self.plan(limit=50)
        table = by_va(plan)
        # one package, one cluster, one subsystem, zero call edges
        self.assertEqual(len({item["cluster"] for item in plan["targets"]}), 1)
        self.assertEqual(plan["summary"]["by_cluster"],
                         {"cluster-flat": len(FLAT)}, plan["summary"])
        for key in FLAT:
            self.assertEqual(table[VA_OF[key]]["cluster"], "cluster-flat")
            self.assertEqual(table[VA_OF[key]]["scc"]["size"], 1,
                             "co-package targets were fused into one unit")
            self.assertEqual(table[VA_OF[key]]["open_callees"], [])
        indexes = {key: wave_of(plan)[VA_OF[key]] for key in FLAT}
        self.assertEqual(indexes, dict.fromkeys(FLAT, 0), indexes)
        # the strongest form of the negative: co-membership added no wave at all
        self.assertEqual(plan["summary"]["waves"], 1, plan["summary"])
        self.assertEqual(plan["summary"]["coordinated_units"], 0)

    # -- S8 --------------------------------------------------------------- #
    def test_analogues_never_create_a_dependency(self):
        from tools.reconstruction_tooling.frontier import _index

        self.make_root(keys=FLAT)
        # Analogues are only computed against *reconstructed* records
        # (reconstruction_knowledge.py:962-965), so the fixture has to integrate
        # something first. Integrating E1 and E2 makes them mutual analogues
        # with no call edge between them.
        integrated = integrate(self.info["root"], ("E1", "E2"))
        self.assertEqual(integrated, sorted(VA_OF[key] for key in ("E1", "E2")))
        index = _index(self.info["root"])
        first = index["records"][VA_OF["E1"]]
        second = index["records"][VA_OF["E2"]]
        self.assertEqual([item["va"] for item in first["analogues"]],
                         [VA_OF["E2"]], first["analogues"])
        self.assertEqual([item["va"] for item in second["analogues"]],
                         [VA_OF["E1"]], second["analogues"])
        self.assertNotIn(VA_OF["E2"], first["dependencies"]["callees"])
        self.assertNotIn(VA_OF["E1"], second["dependencies"]["callees"])
        # the analogue pair is reconstructed, so it is not plan work at all...
        plan = self.plan(limit=50)
        self.assertEqual(sorted(item["va"] for item in plan["targets"]),
                         sorted(VA_OF[key] for key in ("E3", "E4")))
        # ...and the planned targets that *do* carry the reconstructed pair as an
        # analogue still get no edge from it and still share one wave
        table = by_va(plan)
        for key in ("E3", "E4"):
            analogues = [item["va"] for item
                         in index["records"][VA_OF[key]]["analogues"]]
            self.assertEqual(analogues,
                             sorted(VA_OF[other] for other in ("E1", "E2")),
                             (key, analogues))
            self.assertEqual(table[VA_OF[key]]["open_callees"], [])
        self.assertEqual(wave_of(plan)[VA_OF["E3"]],
                         wave_of(plan)[VA_OF["E4"]])
        self.assertEqual(plan["summary"]["waves"], 1, plan["summary"])

    # -- S9 --------------------------------------------------------------- #
    def test_wave_depth_equals_true_dependency_depth(self):
        self.make_root(keys=fx.DEFAULT_KEYS)
        plan = self.plan(limit=50)
        expected = longest_call_chain(fx.DEFAULT_KEYS)
        self.assertEqual(expected, 2, "fixture edge table changed shape")
        self.assertEqual(len(ready_waves(plan)), expected, plan["waves"])
        self.assertEqual(plan["summary"]["waves"], expected, plan["summary"])
        # exactly one boundary, and it sits between the prerequisites and C
        self.assertEqual([wave["index"] for wave in ready_waves(plan)], [0, 1])
        self.assertEqual(plan["summary"]["wave_widths"], [5, 1])
        waves = wave_of(plan)
        self.assertEqual([waves[VA_OF[key]] for key in PREREQ], [0, 0, 0])
        self.assertEqual(waves[VA_OF["C"]], 1)
        # and no target is scheduled twice
        scheduled = [entry["va"] for wave in plan["waves"]
                     for entry in wave["targets"]]
        self.assertEqual(len(scheduled), len(set(scheduled)))
        self.assertEqual(sorted(scheduled),
                         sorted(item["va"] for item in plan["targets"]))

    # -- S10 -------------------------------------------------------------- #
    def test_no_progress_wave_is_reported_not_looped(self):
        # With the P/Q cycle exported into the TSV, both members list the other
        # as an open callee, so neither can ever be ready: the scheduler has to
        # say so instead of spinning.
        self.make_root(cycle_in_tsv=True)
        plan = self.plan(limit=50)
        table = by_va(plan)
        self.assertEqual(table[VA_OF["P"]]["open_callees"], [VA_OF["Q"]])
        self.assertEqual(table[VA_OF["Q"]]["open_callees"], [VA_OF["P"]])
        self.assertEqual([wave["reason"] for wave in plan["waves"]],
                         ["ready", "ready", "no_progress"], plan["waves"])
        stalled = plan["waves"][-1]
        self.assertEqual(stalled["targets"], [], stalled)
        self.assertEqual(stalled["waiting_on"],
                         sorted(VA_OF[key] for key in CYCLE), stalled)
        self.assertEqual(stalled["index"], len(plan["waves"]) - 1)
        # the loop terminates: waves() is a pure function of its input, so
        # re-running it can only reproduce the same terminal wave, never grow
        for _ in range(5):
            again = sched.waves(sched.classify(
                [dict(item) for item in plan["targets"]],
                {"records": {}}, _partition_of(plan)))
            self.assertEqual([wave["reason"] for wave in again],
                             ["ready", "ready", "no_progress"])
            self.assertEqual(again[-1]["waiting_on"], stalled["waiting_on"])
            self.assertEqual(len(again), 3)
        # the wave loop is bounded, and the bound is raised rather than waited
        # out: a plan whose waves never satisfy the bound fails loudly
        self.stub_validator("PASS")
        self.set_production("MAX_ITERATIONS", 1)
        with self.assertRaises(orch.OrchestrationBoundExceeded) as raised:
            orch.run(root=self.info["root"], limit=20, worker=fx.worker("ok"),
                     implementer_id="orch", write=False)
        self.assertEqual(raised.exception.code, "orchestration_bound_exceeded")
        # the bound reports how far it got, and it got exactly one round in:
        # A/B/D landed and nothing was promoted afterwards because the run
        # stopped at the bound, not because the promotion failed
        self.assertEqual(raised.exception.details,
                         {"waves": 1, "completed": len(PREREQ)},
                         raised.exception.details)
        # a tripped bound is loud *after* the work it bounded, never instead of
        # it, and it still leaves no lease behind
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])
        for key in PREREQ:
            self.assertEqual(fx.row(self.db, fx.inv_id(key))["status"], "done")


class DispatchOrderingTest(fx.FixtureTestCase):
    """S3-S6: concurrency, ordering and SCC dispatch through the real loop."""

    def test_all_three_prerequisites_run_concurrently(self):
        self.make_root(keys=("A", "B", "C", "D"))
        self.stub_validator("PASS")
        prereq = sorted(VA_OF[key] for key in PREREQ)
        self.assertEqual(
            sorted(VA_OF[key] for key in PREREQ
                   if by_va(self.plan(limit=20))[VA_OF[key]]["dispatchable"]),
            prereq)
        # only the three prerequisites are gated: the dependent is promoted
        # into a later dispatch round and must neither satisfy nor break this
        # barrier, which is about the prerequisites and nothing else
        worker = BarrierWorker("ok", gate_vas=prereq, parties=3, timeout=10)
        outcome = orch.run(root=self.info["root"], limit=20, worker=worker,
                           implementer_id="orch", write=False, max_workers=4)
        # a serialized dispatch breaks the barrier and lands here
        self.assertEqual(outcome["summary"]["errors"], [],
                         "a dispatch unit died: the prerequisites were not "
                         "run concurrently")
        self.assertFalse(worker.gate.broken,
                         "the concurrency barrier broke: dispatch was serialized")
        # exactly the three prerequisites rendezvoused, each exactly once
        self.assertEqual(sorted(worker.gated), prereq, worker.gated)
        self.assertEqual(len(worker.gated), 3, worker.gated)
        self.assertEqual(worker.max_active, 3,
                         "observed concurrency %d, expected 3"
                         % (worker.max_active,))
        self.assertEqual(sorted(record["va"] for record in outcome["results"]),
                         sorted(VA_OF[key] for key in PREREQ + DEPENDENT))
        for record in outcome["results"]:
            self.assertEqual(record["status"], "complete", record)
        # the three prerequisites ran in three separate threads
        gated_calls = [call for call in worker.calls if call["va"] in prereq]
        self.assertEqual(len(set(call["thread"] for call in gated_calls)), 3,
                         "the prerequisites shared a thread: they were serialized")
        # and the promoted dependent is not one of them
        promoted = [call for call in worker.calls
                    if call["va"] not in prereq]
        self.assertEqual([call["va"] for call in promoted], [VA_OF["C"]])
        self.assertNotIn(promoted[0]["thread"],
                         set(call["thread"] for call in gated_calls))

    def test_dependent_never_dispatched_before_its_prerequisite_completes(self):
        self.make_root(keys=("A", "B", "C", "D"))
        self.stub_validator("PASS")
        # the plan says up front that C is behind all three prerequisites
        plan = self.plan(limit=20)
        self.assertEqual(by_va(plan)[VA_OF["C"]]["open_callees"],
                         sorted(VA_OF[key] for key in PREREQ))
        self.assertGreater(wave_of(plan)[VA_OF["C"]],
                           max(wave_of(plan)[VA_OF[key]] for key in PREREQ))
        worker = TimelineWorker("ok")
        outcome = orch.run(root=self.info["root"], limit=20, worker=worker,
                           implementer_id="orch", write=False)
        # one run, four targets: the dependent is dispatched inside the same run
        self.assertEqual(outcome["summary"]["complete"], 4, outcome["summary"])
        self.assertEqual(sorted(record["va"] for record in outcome["results"]),
                         sorted(VA_OF[key] for key in PREREQ + DEPENDENT))
        self.assertEqual(sorted(worker.timeline),
                         sorted(VA_OF[key] for key in PREREQ + DEPENDENT))
        timeline = worker.timeline
        # the claim the test name makes: C entered the worker body strictly
        # after every one of A, B and D had left it
        latest_finish = max(timeline[VA_OF[key]]["finish"] for key in PREREQ)
        self.assertGreater(timeline[VA_OF["C"]]["dispatch"], latest_finish,
                           "C was dispatched at %r, but a prerequisite was still "
                           "running until %r"
                           % (timeline[VA_OF["C"]]["dispatch"], latest_finish))
        for key in PREREQ:
            self.assertLess(timeline[VA_OF[key]]["dispatch"],
                            timeline[VA_OF[key]]["finish"], key)
            self.assertLessEqual(timeline[VA_OF[key]]["finish"],
                                 timeline[VA_OF["C"]]["dispatch"], key)
            self.assertEqual(fx.row(self.db, fx.inv_id(key))["status"], "done")
        # the dependent did land, and only once
        self.assertEqual(fx.row(self.db, fx.inv_id("C"))["status"], "done")
        self.assertEqual(len([call for call in worker.calls
                              if call["va"] == VA_OF["C"]]), 1)
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])

    def test_dependent_is_dispatched_after_its_prerequisites_land(self):
        self.make_root(keys=("A", "B", "C", "D"))
        self.stub_validator("PASS")
        # plan level: C is deferred, in a later wave, and names its blockers
        deferred = self.plan(limit=20)
        self.assertEqual(by_va(deferred)[VA_OF["C"]]["role"], "dependent")
        self.assertEqual(by_va(deferred)[VA_OF["C"]]["reason"], "open_callees")
        self.assertEqual(by_va(deferred)[VA_OF["C"]]["open_callees"],
                         sorted(VA_OF[key] for key in PREREQ))
        self.assertIs(by_va(deferred)[VA_OF["C"]]["dispatchable"], False)
        self.assertGreater(wave_of(deferred)[VA_OF["C"]],
                           max(wave_of(deferred)[VA_OF[key]] for key in PREREQ))
        # one run now completes all four: IMPLEMENTED + validator PASS really
        # do complete a target, and the dependent is promoted in the next round
        worker = TimelineWorker("ok")
        outcome = orch.run(root=self.info["root"], limit=20, worker=worker,
                           implementer_id="orch", write=False)
        self.assertEqual(outcome["summary"]["targets"], 4, outcome["summary"])
        self.assertEqual(outcome["summary"]["complete"], 4, outcome["summary"])
        self.assertEqual(outcome["summary"]["waves"], 2, outcome["summary"])
        self.assertEqual(outcome["summary"]["skipped"], 0, outcome["summary"])
        self.assertEqual(outcome["summary"]["errors"], [], outcome["summary"])
        by_queue = {record["queue_id"]: record for record in outcome["results"]}
        for key in PREREQ + DEPENDENT:
            record = by_queue[fx.inv_id(key)]
            self.assertEqual((record["va"], record["status"],
                              record["outcome"], record["validation"], record["code"]),
                             (VA_OF[key], "complete", "IMPLEMENTED", "PASS",
                              "validated"), (key, record))
            # the documented happy-path op sequence, for a target that was
            # dispatched in the very first wave and one that was promoted
            self.assertEqual([event["op"] for event in record["events"]],
                             HAPPY_PATH_OPS, (key, record["events"]))
            self.assertEqual(fx.row(self.db, fx.inv_id(key))["status"], "done")
        # each target was offered exactly once, so promotion cannot spin
        self.assertEqual(sorted(call["va"] for call in worker.calls),
                         sorted(VA_OF[key] for key in PREREQ + DEPENDENT))
        # and the promotion really did happen after, not concurrently with,
        # the prerequisites
        self.assertGreater(worker.timeline[VA_OF["C"]]["dispatch"],
                           max(worker.timeline[VA_OF[key]]["finish"]
                               for key in PREREQ))
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])

    def test_promoted_dependent_still_has_to_win_its_claim(self):
        """Promotion only puts a target in front of ``claim()``; claim rules.

        A dependent promoted into a later round is offered to the queue like any
        other work. If another actor parked its row in the meantime, the claim
        is refused and the target is *skipped* -- never forced through, and never
        re-offered (``dispatched`` is per-run, so this is the single attempt).
        """
        self.make_root(keys=("A", "B", "C", "D"))
        self.stub_validator("PASS")
        inv = fx.inv_id("C")
        parked = {}

        def hook(worker, package):
            # C's row is still claimable at plan time, so C *is* in the plan and
            # will be promoted. Park it while A is in flight instead, which
            # leaves C in the plan with a blocked row -- the exact race.
            if package["target"]["va"] != VA_OF["A"]:
                return
            parked["claim"] = queue_op(op="claim", id=inv,
                                       implementer_id="operator",
                                       binary_sha256=fx.SHA)
            parked["release"] = queue_op(op="release", id=inv,
                                         implementer_id="operator", to="blocked",
                                         reason="operator:awaiting_upstream")

        worker = TimelineWorker("ok", hook=hook)
        outcome = orch.run(root=self.info["root"], limit=20, worker=worker,
                           implementer_id="orch", write=False)
        self.assertTrue(parked["claim"]["claimed"], parked["claim"])
        self.assertTrue(parked["release"]["released"], parked["release"])
        # C was offered once and refused, not forced and not retried
        self.assertEqual(outcome["summary"]["targets"], 4, outcome["summary"])
        self.assertEqual(outcome["summary"]["complete"], 3, outcome["summary"])
        self.assertEqual(outcome["summary"]["skipped"], 1, outcome["summary"])
        record = [item for item in outcome["results"]
                  if item["va"] == VA_OF["C"]][0]
        self.assertEqual((record["status"], record["code"]),
                         ("skipped", "blocked"), record)
        self.assertEqual(record["events"], [{"op": "claim", "ok": False,
                                            "code": "blocked"}], record)
        # no worker was ever run for it
        self.assertNotIn(VA_OF["C"], [call["va"] for call in worker.calls])
        self.assertNotIn(VA_OF["C"], worker.timeline)
        # the other actor's disposition is intact
        row = fx.row(self.db, inv)
        self.assertEqual((row["status"], row["implementer_id"],
                          row["block_reason"]),
                         ("blocked", None, "operator:awaiting_upstream"), row)
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])

    def test_one_run_promotes_its_own_dependent(self):
        """REGRESSION: a computed wave boundary has to be acted on.

        ``orchestrate.run`` used to build the plan once and never re-read the
        ``dispatchable`` flag, so a wave-2 dependent was scheduled, skipped, and
        left ``queued`` -- the wave boundary the scheduler had just computed
        bought nothing and the dependency order was a comment. ``run`` now keeps
        a ``dispatched`` set plus a ``ready_entries()`` pass that promotes a
        deferred target once every VA in its ``open_callees`` is ``complete``.

        A/B/D -> C must therefore finish in ONE run, in two dispatch rounds.
        The companion case is
        :meth:`test_promoted_dependent_still_has_to_win_its_claim`: promotion is
        not a bypass of the queue.
        """
        self.make_root(keys=("A", "B", "C", "D"))
        self.stub_validator("PASS")
        outcome = orch.run(root=self.info["root"], limit=20, worker=fx.worker("ok"),
                           implementer_id="orch", write=False)
        self.assertEqual(outcome["summary"]["targets"], 4, outcome["summary"])
        self.assertEqual(outcome["summary"]["complete"], 4, outcome["summary"])
        self.assertEqual(outcome["summary"]["waves"], 2, outcome["summary"])
        self.assertEqual(sorted(record["va"] for record in outcome["results"]),
                         sorted(VA_OF[key] for key in PREREQ + DEPENDENT))
        promoted = [record for record in outcome["results"]
                    if record["va"] == VA_OF["C"]][0]
        self.assertEqual((promoted["status"], promoted["code"],
                          promoted["outcome"], promoted["validation"]),
                         ("complete", "validated", "IMPLEMENTED", "PASS"),
                         promoted)
        self.assertEqual(fx.row(self.db, fx.inv_id("C"))["status"], "done")
        for key in PREREQ + DEPENDENT:
            self.assertEqual(fx.row(self.db, fx.inv_id(key))["status"], "done")
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])
        self.assertEqual(outcome["summary"]["errors"], [])

    def test_scc_members_share_one_dispatch_unit(self):
        self.make_root(keys=CYCLE)
        self.stub_validator("PASS")
        plan = self.plan(limit=20)
        table = by_va(plan)
        p, r = table[VA_OF["P"]], table[VA_OF["Q"]]
        self.assertEqual(p["scc"]["id"], r["scc"]["id"])
        self.assertGreater(p["scc"]["size"], 1)
        self.assertEqual(sorted(p["scc"]["members"]),
                         sorted(VA_OF[key] for key in CYCLE))
        # the plan schedules them as one unit, twice-listed, in ONE wave
        self.assertEqual(len(plan["waves"]), 1, plan["waves"])
        entries = {entry["va"]: entry for entry in plan["waves"][0]["targets"]}
        unit = entries[VA_OF["P"]]["unit"]
        self.assertIsNotNone(unit)
        self.assertEqual(entries[VA_OF["Q"]]["unit"], unit)
        for key in CYCLE:
            self.assertEqual(sorted(entries[VA_OF[key]]["unit_members"]),
                             sorted(VA_OF[other] for other in CYCLE))
        self.assertGreaterEqual(plan["summary"]["coordinated_units"], 1)
        self.assertEqual(plan["summary"]["largest_cycle"], 2)
        # and run() dispatches that unit with a single shared worker identity
        worker = fx.worker("ok")
        outcome = orch.run(root=self.info["root"], limit=20, worker=worker,
                           implementer_id="orch", write=False)
        self.assertEqual(outcome["summary"]["errors"], [])
        self.assertEqual(sorted(record["va"] for record in outcome["results"]),
                         sorted(VA_OF[key] for key in CYCLE))
        identities = sorted(set(call["implementer"] for call in worker.calls))
        self.assertEqual(identities, ["orch/%s" % unit],
                         "the cycle was split across worker identities: %r"
                         % (identities,))
        # NOT two independent workers: neither member is addressed on its own
        for key in CYCLE:
            self.assertNotIn("orch/%s" % VA_OF[key], identities)
        threads = sorted(set(call["thread"] for call in worker.calls))
        self.assertEqual(len(threads), 1, threads)
        self.assertIn(unit, threads[0], threads)
        for key in CYCLE:
            row = fx.row(self.db, fx.inv_id(key))
            self.assertEqual((row["status"], row["implementer_id"]),
                             ("done", "orch/%s" % unit), (key, row))

    def test_cycle_members_are_never_ordered_against_each_other(self):
        """A cycle must not become two waves either (``waves()`` guard path)."""
        self.make_root(keys=fx.DEFAULT_KEYS, cycle_in_tsv=True)
        plan = self.plan(limit=50)
        table = by_va(plan)
        for key in CYCLE:
            self.assertEqual(table[VA_OF[key]]["role"], "coordinated")
            self.assertEqual(table[VA_OF[key]]["scc"]["size"], 2)
            # each member is the other's open callee, so neither can be emitted
            # into a wave -- and above all they are never emitted separately
            self.assertEqual(table[VA_OF[key]]["open_callees"],
                             [VA_OF[other] for other in CYCLE
                              if other != key])
            self.assertEqual(table[VA_OF[key]]["dispatchable"], False)
        scheduled = {entry["va"] for wave in plan["waves"]
                     for entry in wave["targets"]}
        self.assertEqual(scheduled & {VA_OF[key] for key in CYCLE}, set())
        # they are reported together, in the terminal wave, as what stalled
        self.assertEqual(plan["waves"][-1]["reason"], "no_progress")
        self.assertEqual(plan["waves"][-1]["waiting_on"],
                         sorted(VA_OF[key] for key in CYCLE))
        # and with the cycle as the *only* work, that is the whole plan
        self.make_root_at("cycle-only", keys=CYCLE, cycle_in_tsv=True)
        alone = self.plan(limit=50)
        self.assertEqual([wave["reason"] for wave in alone["waves"]],
                         ["no_progress"], alone["waves"])
        self.assertEqual(alone["waves"][0]["targets"], [])
        self.assertEqual(alone["waves"][0]["waiting_on"],
                         sorted(VA_OF[key] for key in CYCLE))
        self.assertEqual(len(alone["waves"]), 1, alone["waves"])
        self.assertEqual(alone["summary"]["dispatchable"], 0)


class ClaimSafetyTest(fx.FixtureTestCase):
    """S11-S14, S16, S20: claim exclusivity, lease recovery, ownership guards."""

    RACERS = 8

    def setUp(self):
        super().setUp()
        self.make_root(keys=("A", "B", "C", "D"))
        self.ida = fx.inv_id("A")

    def claim(self, implementer, **kwargs):
        params = {"op": "claim", "id": self.ida, "implementer_id": implementer,
                  "binary_sha256": fx.SHA}
        params.update(kwargs)
        return queue_op(**params)

    # -- S11 -------------------------------------------------------------- #
    def test_concurrent_claims_have_exactly_one_winner(self):
        for attempt in range(3):
            reset_row(self.db, self.ida)
            gate = threading.Barrier(self.RACERS, timeout=30)
            names = ["racer-%d-%d" % (attempt, index)
                     for index in range(self.RACERS)]

            def race(name):
                gate.wait()
                return self.claim(name)

            with ThreadPoolExecutor(max_workers=self.RACERS) as executor:
                results = list(executor.map(race, names))
            winners = [item for item in results if item.get("claimed")]
            losers = [item for item in results
                      if item.get("code") == "already_claimed"]
            self.assertEqual(len(winners), 1, (attempt, results))
            self.assertEqual(len(losers), self.RACERS - 1, (attempt, results))
            self.assertEqual([item for item in results
                              if item not in winners and item not in losers], [],
                             (attempt, results))
            self.assertIs(winners[0]["idempotent"], False)
            owner = winners[0]["investigation"]["implementer_id"]
            self.assertIn(owner, names)
            for loser in losers:
                self.assertEqual(loser["implementer_id"], owner, loser)
                self.assertNotIn("investigation", loser)
            self.assertEqual([item["code"] for item in losers],
                             ["already_claimed"] * (self.RACERS - 1))
            active = fx.rows_by_status(self.db, "active")
            self.assertEqual(len(active), 1, (attempt, active))
            self.assertEqual(active[0]["id"], self.ida)
            self.assertIsNotNone(active[0]["implementer_id"])
            self.assertEqual(active[0]["implementer_id"], owner)
            self.assertEqual(fx.row(self.db, fx.inv_id("B"))["status"], "queued")
            self.assertIsNone(fx.row(self.db, fx.inv_id("B"))["implementer_id"])

    # -- S12 -------------------------------------------------------------- #
    def test_duplicate_claim_same_worker_is_idempotent(self):
        first = self.claim("alice")
        self.assertTrue(first["claimed"], first)
        stamp = fx.row(self.db, self.ida)["updated_at"]
        again = self.claim("alice")
        self.assertIs(again["claimed"], False, again)
        self.assertIs(again["idempotent"], True, again)
        self.assertEqual(again["id"], self.ida)
        after = fx.row(self.db, self.ida)
        self.assertEqual(after["updated_at"], stamp,
                         "a replayed claim renewed the lease clock")
        self.assertEqual(after["implementer_id"], "alice")
        self.assertEqual(after["status"], "active")
        self.assertIsNone(after["checkpoint"],
                          "a replayed claim fabricated a lease history")
        self.assertEqual(len(fx.rows_by_status(self.db, "active")), 1)

    # -- S13 -------------------------------------------------------------- #
    def test_duplicate_claim_different_worker_is_refused(self):
        self.claim("alice")
        before = fx.row(self.db, self.ida)
        refused = self.claim("bob")
        self.assertEqual(refused["code"], "already_claimed", refused)
        self.assertEqual(refused["implementer_id"], "alice", refused)
        self.assertIs(refused["stale"], False, refused)
        self.assertEqual(refused["id"], self.ida)
        after = fx.row(self.db, self.ida)
        self.assertEqual(after["implementer_id"], "alice")
        self.assertEqual(after["status"], "active")
        self.assertEqual(after["updated_at"], before["updated_at"])
        self.assertEqual(after["attempts"], before["attempts"])
        self.assertEqual(after["checkpoint"], before["checkpoint"])
        self.assertEqual(after, before, "a refused claim changed the row")

    # -- S14 -------------------------------------------------------------- #
    def test_stale_lease_recovery(self):
        claimed = self.claim("alice")
        self.assertTrue(claimed["claimed"], claimed)
        fx.backdate(self.db, self.ida, when=fx.FIXED_NOW, owner="alice")
        refused = self.claim("bob")
        self.assertEqual(refused["code"], "already_claimed", refused)
        self.assertIs(refused["stale"], True,
                      "a lease older than the TTL was not recognised as stale")
        self.assertEqual(refused["implementer_id"], "alice")
        self.assertEqual(fx.row(self.db, self.ida)["implementer_id"], "alice")
        taken = self.claim("bob", allow_stale=True, stale_after_seconds=60)
        self.assertTrue(taken["claimed"], taken)
        self.assertEqual(taken["investigation"]["implementer_id"], "bob")
        self.assertEqual(taken["displaced_owner"]["owner"], "alice")
        history = json.loads(fx.row(self.db, self.ida)["checkpoint"])["lease_history"]
        self.assertEqual([item["owner"] for item in history], ["alice"], history)
        self.assertEqual(history[0]["stale_after_seconds"], 60)
        row = fx.row(self.db, self.ida)
        self.assertEqual(row["implementer_id"], "bob")
        self.assertEqual(row["status"], "active")
        # the displaced owner can no longer write (S20's guard, from the other side)
        self.assertEqual(
            q.checkpoint(self.ida, "alice", payload={"x": 1})["code"], "not_owner")

    # -- S16 -------------------------------------------------------------- #
    def test_ingestion_by_a_non_owner_is_refused(self):
        target = {item["queue_id"]: item
                  for item in self.plan(limit=20)["targets"]}[self.ida]
        self.claim("owner")
        before = fx.row(self.db, self.ida)
        # 1. a checkpoint by a non-owner
        refused = q.checkpoint(self.ida, "intruder", payload={"x": 1},
                               stage="VALIDATE")
        self.assertEqual(refused["code"], "not_owner", refused)
        self.assertEqual(refused["implementer_id"], "owner")
        # 2. a close by a non-owner
        closed = q.close(self.ida, "intruder", disposition="done")
        self.assertEqual(closed["code"], "not_owner", closed)
        self.assertEqual(closed["implementer_id"], "owner")
        # 3. the whole lifecycle (claim -> brief -> launch -> ingest) as an intruder
        worker = fx.worker("ok")
        record = fx.process_target(self.info["root"], target, worker,
                                   "intruder", self.info["sha"], write=False)
        self.assertEqual(record["status"], "skipped", record)
        self.assertEqual(record["code"], "already_claimed", record)
        self.assertEqual([event["op"] for event in record["events"]], ["claim"])
        self.assertFalse(record["events"][0]["ok"])
        self.assertEqual(worker.calls, [], "an intruder ran a worker")
        self.assertEqual(fx.row(self.db, self.ida), before,
                         "an intruder's write landed on an owned row")
        # and once the row is terminal every further write is refused too
        queue_op(op="close", id=self.ida, implementer_id="owner", status="done")
        self.assertEqual(
            q.checkpoint(self.ida, "intruder", payload={"x": 2})["code"],
            "already_completed")
        self.assertEqual(
            queue_op(op="update", id=self.ida, implementer_id="intruder",
                     stage="DONE")["code"], "already_completed")
        again = fx.process_target(self.info["root"], target, worker, "intruder",
                                  self.info["sha"], write=False)
        self.assertEqual((again["status"], again["code"]),
                         ("skipped", "already_completed"), again)
        self.assertEqual(worker.calls, [])
        self.assertEqual(fx.row(self.db, self.ida)["status"], "done")
        # re-closing is an idempotent no-op, never a resurrection
        self.assertIs(q.close(self.ida, "owner", disposition="done")["closed"],
                      False)


class ConcurrentIngestionTest(fx.FixtureTestCase):
    """S15, S17-S19, S21: many targets, many owners, one queue."""

    def seeds(self, keys):
        return {key: {"attempts": json.dumps({"SEED": index + 1}),
                      "evidence_refs": json.dumps(["seed/%s" % key])}
                for index, key in enumerate(keys)}

    def test_concurrent_ingestion_of_distinct_targets_loses_nothing(self):
        self.make_root_at("ingest", keys=fx.DEFAULT_KEYS + FLAT)
        self.seed_db(rows=self.seeds(EIGHT))
        self.stub_validator("PASS")
        for round_index in range(2):
            fresh = self.seeds(EIGHT)
            for key in fresh:
                fresh[key]["status"] = "queued"
            self.seed_db(rows=fresh)
            plan = self.plan(limit=50)
            table = {item["queue_id"]: item for item in plan["targets"]}
            worker = fx.worker("ok")
            wanted = sorted(fx.inv_id(key) for key in EIGHT)
            self.assertEqual(sorted(set(table) & set(wanted)), wanted,
                             round_index)

            def ingest(key):
                return fx.process_target(self.info["root"],
                                         table[fx.inv_id(key)], worker,
                                         "w-%s" % key, self.info["sha"],
                                         write=False)

            with ThreadPoolExecutor(max_workers=8) as executor:
                records = dict(zip(EIGHT, executor.map(ingest, EIGHT)))
            for index, key in enumerate(EIGHT):
                record = records[key]
                self.assertEqual(record["va"], VA_OF[key], (key, record))
                self.assertEqual(record["queue_id"], fx.inv_id(key), (key, record))
                self.assertEqual(record["status"], "complete", (key, record))
                self.assertEqual(record["code"], "validated", (key, record))
                # attempts are counted for this target and no other: this row's
                # own seed, plus exactly one replace and one validation
                self.assertEqual(record["attempts"],
                                 {"SEED": index + 1, "REPLACE": 1, "VALIDATE": 1,
                                  "_total": 2}, (key, record))
                self.assertEqual(record["source_files"], [fx.source_rel(key)])
                row = fx.row(self.db, fx.inv_id(key))
                # no cross-contamination of ownership
                self.assertEqual(row["implementer_id"], "w-%s" % key, (key, row))
                self.assertEqual(row["status"], "done", (key, row))
                # this row's own seed survived every other thread's write
                self.assertEqual(json.loads(row["attempts"]),
                                 {"SEED": index + 1}, (key, row))
                self.assertEqual(json.loads(row["evidence_refs"]),
                                 ["seed/%s" % key], (key, row))
            self.assertEqual(fx.rows_by_status(self.db, "active"), [],
                             round_index)
            self.assertEqual(len(fx.rows_by_status(self.db, "done")), 8,
                             round_index)
            self.assertEqual(len(worker.calls), 8, round_index)
            self.assertEqual(len(set(call["thread"] for call in worker.calls)), 8,
                             "targets were serialised instead of run in parallel")

    def test_two_concurrent_runs_do_not_double_own(self):
        keys = ("A", "B", "D", "E1")
        self.make_root_at("dual", keys=keys)
        self.stub_validator("PASS")
        gate = threading.Barrier(2, timeout=30)
        outcomes = {}

        def run(name):
            gate.wait()
            outcomes[name] = orch.run(root=self.info["root"], limit=50,
                                      worker=fx.worker("ok"),
                                      implementer_id=name, write=False)

        with ThreadPoolExecutor(max_workers=2) as executor:
            list(executor.map(run, ("left", "right")))
        self.assertEqual(sorted(outcomes), ["left", "right"])
        records = [record for outcome in outcomes.values()
                   for record in outcome["results"]]
        self.assertTrue(records, "neither run dispatched anything")
        for name, outcome in sorted(outcomes.items()):
            self.assertEqual(outcome["summary"]["errors"], [], (name, outcome))
            self.assertEqual(outcome["summary"]["error"], 0, (name, outcome))
        for key in keys:
            mine = [record for record in records if record["va"] == VA_OF[key]]
            self.assertTrue(mine, key)
            complete = [record for record in mine
                        if record["status"] == "complete"]
            self.assertEqual(len(complete), 1,
                             "a target was completed twice: %r" % (mine,))
            self.assertEqual(sorted({record["queue_id"] for record in mine}),
                             [fx.inv_id(key)], mine)
            # exactly one owner, and the loser was told why
            losers = [record for record in mine if record["status"] != "complete"]
            for loser in losers:
                self.assertEqual(loser["status"], "skipped", (key, loser))
                self.assertIn(loser["code"],
                              ("already_claimed", "already_completed"),
                              (key, loser))
                self.assertEqual([event["op"] for event in loser["events"]],
                                 ["claim"])
            row = fx.row(self.db, fx.inv_id(key))
            self.assertEqual(row["status"], "done", (key, row))
            # the owner is the identity of exactly one of the two runs, and it
            # carries the dispatch unit (the VA) as its suffix
            self.assertIn(row["implementer_id"],
                          ["%s/%s" % (name, VA_OF[key])
                           for name in ("left", "right")], (key, row))
        # no (va, queue_id) pair was taken to completion by both runs
        pairs = [(record["va"], record["queue_id"]) for record in records
                 if record["status"] == "complete"]
        self.assertEqual(len(pairs), len(set(pairs)), pairs)
        self.assertEqual(sorted(set(pairs)),
                         sorted((VA_OF[key], fx.inv_id(key)) for key in keys))
        self.assertEqual(fx.rows_by_status(self.db, "active"), [],
                         "a lease survived a finished run")

    def test_target_obsolete_mid_run_is_discarded(self):
        self.make_root(keys=("A",))
        self.stub_validator("PASS")
        inv = fx.inv_id("A")
        seen = {}

        def hook(worker, package):
            # A second actor decides the target is obsolete while the worker is
            # in flight. It has to win the row the way a real adjudicator
            # would: the lease goes stale, then it claims and closes.
            implementer = package["lease"]["implementer_id"]
            fx.backdate(self.db, inv, when=fx.FIXED_NOW, owner=implementer)
            taken = queue_op(op="claim", id=inv, implementer_id="adjudicator",
                             binary_sha256=fx.SHA, allow_stale=True,
                             stale_after_seconds=60)
            seen["claim"] = taken
            seen["close"] = queue_op(op="close", id=inv,
                                      implementer_id="adjudicator",
                                      status="dropped")
            seen["displaced"] = taken.get("displaced_owner")

        worker = TimelineWorker("ok", hook=hook)
        target = self.plan(limit=20)["targets"][0]
        record = fx.process_target(self.info["root"], target, worker,
                                   "orch/0x00b3d300", self.info["sha"],
                                   write=False)
        self.assertTrue(seen["claim"]["claimed"], seen["claim"])
        self.assertEqual(seen["displaced"]["owner"], "orch/0x00b3d300")
        self.assertTrue(seen["close"]["closed"], seen["close"])
        self.assertEqual(seen["close"]["previous_status"], "active")
        # the worker's result was NOT recorded over the other disposition
        row = fx.row(self.db, inv)
        self.assertEqual(row["status"], "dropped", row)
        self.assertEqual(row["implementer_id"], "adjudicator", row)
        self.assertIsNone(row["evidence_refs"],
                          "a displaced worker's artifacts were persisted")
        self.assertIsNone(row["attempts"], row)
        # the only checkpoint on the row is the adjudicator's lease history; the
        # worker's own progress record never landed
        self.assertEqual(sorted(json.loads(row["checkpoint"])), ["lease_history"],
                         row["checkpoint"])
        # the work did happen -- the whole attempt trail is there -- and none of
        # it was persisted, which is the property that matters here
        self.assertEqual([event["op"] for event in record["events"]],
                         HAPPY_PATH_OPS, record["events"])
        # the close the orchestrator attempted after the drop was a no-op
        closes = [event for event in record["events"] if event["op"] == "close"]
        self.assertEqual(len(closes), 1, record["events"])
        self.assertIs(closes[0]["closed"], False, closes)
        self.assertEqual(fx.row(self.db, inv)["status"], "dropped")
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])
        # NOTE: what this record *reports* as its own status is a separate
        # question with its own pin -- see
        # :meth:`test_pinned_a_terminal_row_still_reports_a_completion`.

    def test_dependency_blocked_mid_run_stops_dependent_dispatch(self):
        self.make_root(keys=("A", "B", "C", "D"))
        self.stub_validator("PASS")
        inv = fx.inv_id("D")
        acted = {}

        def hook(worker, package):
            # A second actor parks D -- a real open callee of C -- while D's
            # worker is in flight, so D does not land. The disposition is the
            # non-terminal ``blocked``: the worker that parks a row keeps no
            # lease on it, and the row stays a live target, which is exactly
            # the case the promotion rule has to refuse.
            if package["target"]["va"] != VA_OF["D"]:
                return
            owner = package["lease"]["implementer_id"]
            acted["release"] = q.release(inv, owner, to="blocked",
                                        reason="operator:wrong_abi")

        # before the run, C is reported as a dependent on A, B and D
        before = self.plan(limit=20)
        self.assertEqual(by_va(before)[VA_OF["C"]]["role"], "dependent")
        self.assertEqual(by_va(before)[VA_OF["C"]]["open_callees"],
                         sorted(VA_OF[key] for key in PREREQ))
        self.assertIs(by_va(before)[VA_OF["C"]]["dispatchable"], False)
        self.assertGreater(wave_of(before)[VA_OF["C"]],
                           wave_of(before)[VA_OF["D"]])
        worker = TimelineWorker("ok", hook=hook)
        outcome = orch.run(root=self.info["root"], limit=20, worker=worker,
                           implementer_id="orch", write=False)
        self.assertTrue(acted["release"]["released"], acted["release"])
        # the two prerequisites nobody touched landed
        self.assertEqual(outcome["summary"]["complete"], 2, outcome["summary"])
        self.assertEqual(sorted(record["va"] for record in outcome["results"]
                                if record["status"] == "complete"),
                         sorted(VA_OF[key] for key in ("A", "B")))
        # D is reported as a conflict, not as a completion: its close was
        # refused because closing a blocked row is an adjudication
        d_record = [record for record in outcome["results"]
                    if record["va"] == VA_OF["D"]][0]
        self.assertEqual((d_record["status"], d_record["code"]),
                         ("conflict", "blocked"), d_record)
        closes = [event for event in d_record["events"] if event["op"] == "close"]
        self.assertEqual(len(closes), 1, d_record["events"])
        self.assertFalse(closes[0]["ok"], closes)
        d_row = fx.row(self.db, inv)
        self.assertEqual((d_row["status"], d_row["implementer_id"],
                          d_row["block_reason"]),
                         ("blocked", None, "operator:wrong_abi"), d_row)
        # ...so D never became a landed prerequisite, and C was never promoted
        self.assertNotIn(VA_OF["C"],
                         [record["va"] for record in outcome["results"]])
        self.assertNotIn(VA_OF["C"], worker.timeline)
        c_row = fx.row(self.db, fx.inv_id("C"))
        self.assertEqual(c_row["status"], "queued", c_row)
        self.assertIsNone(c_row["implementer_id"], c_row)
        self.assertIsNone(c_row["updated_at"],
                          "the dependent's row was written even though it was "
                          "never dispatched")
        # the run reports no promotion happened: one dispatch round only
        self.assertEqual(outcome["summary"]["waves"], 1, outcome["summary"])
        # and the plan still refuses to dispatch C: the frontier's own
        # disposition is still ``deferred`` because the canonical index has not
        # recorded the prerequisites as reconstructed
        after = self.plan(limit=20)
        table = by_va(after)
        self.assertIs(table[VA_OF["C"]]["dispatchable"], False)
        self.assertEqual(after["summary"]["dispatchable"], 0, after["summary"])
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])

    def test_a_terminal_row_never_reports_a_completion(self):
        """REGRESSION: a close that did not close is a conflict, not a done.

        ``_queue_close`` treats a re-close of an already-terminal row as an
        idempotent *success* (``closed: False``), so a guard that only checks
        ``q.ok(closed)`` never fires for the case that matters: a second actor
        dropping the row mid-run. The record was reported ``complete``, its VA
        entered ``run``'s ``completed`` set, and a dependent was promoted
        against a prerequisite that does not exist. The guard is on
        ``closed.get("closed")`` as well as ``q.ok(closed)``.

        The scenario is the one above with a *terminal* disposition: a second
        actor takes D's stale lease over and drops the row while D's worker is
        in flight. D then genuinely does not land, so ``D`` must not enter
        ``orchestrate.run``'s ``completed`` set and C must not be promoted.

        A close that reports ``closed: False`` to a caller that did not already
        own a terminal row means somebody else got there first, so the record
        is a conflict and the target never enters ``completed``.
        """
        self.make_root(keys=("A", "B", "C", "D"))
        self.stub_validator("PASS")
        inv = fx.inv_id("D")
        acted = {}

        def hook(worker, package):
            if package["target"]["va"] != VA_OF["D"]:
                return
            owner = package["lease"]["implementer_id"]
            fx.backdate(self.db, inv, when=fx.FIXED_NOW, owner=owner)
            acted["claim"] = queue_op(op="claim", id=inv,
                                      implementer_id="adjudicator",
                                      binary_sha256=fx.SHA, allow_stale=True,
                                      stale_after_seconds=60)
            acted["close"] = queue_op(op="close", id=inv,
                                      implementer_id="adjudicator",
                                      status="dropped")

        before = self.plan(limit=20)
        self.assertEqual(by_va(before)[VA_OF["C"]]["open_callees"],
                         sorted(VA_OF[key] for key in PREREQ))
        worker = TimelineWorker("ok", hook=hook)
        outcome = orch.run(root=self.info["root"], limit=20, worker=worker,
                           implementer_id="orch", write=False)
        self.assertTrue(acted["claim"]["claimed"], acted["claim"])
        self.assertEqual(acted["claim"]["displaced_owner"]["owner"],
                         "orch/0x00b3d600", acted["claim"])
        self.assertTrue(acted["close"]["closed"], acted["close"])
        # D's row really is gone: dropped by the other actor, not done
        d_row = fx.row(self.db, inv)
        self.assertEqual((d_row["status"], d_row["implementer_id"]),
                         ("dropped", "adjudicator"), d_row)
        # (1) D must NOT be reported as a completion
        d_record = [record for record in outcome["results"]
                    if record["va"] == VA_OF["D"]][0]
        self.assertEqual(d_record["status"], "conflict", d_record)
        self.assertEqual(d_record["code"], "target_obsolete", d_record)
        self.assertEqual(d_record["events"][-1]["op"], "close")
        self.assertFalse(d_record["events"][-1]["closed"], d_record)
        # (2) and C must NOT have been promoted, because D never landed
        self.assertNotIn(VA_OF["C"],
                         [record["va"] for record in outcome["results"]],
                         "C was promoted against a prerequisite that was "
                         "dropped, not reconstructed: %r" % (outcome["summary"],))
        self.assertNotIn(VA_OF["C"], worker.timeline)
        self.assertEqual(fx.row(self.db, fx.inv_id("C"))["status"], "queued")

    def test_closing_a_blocked_row_is_an_adjudication(self):
        """REGRESSION: closing a ``blocked`` row requires ``allow_blocked``.

        A blocked row has no lease holder (``queue.release`` clears
        ``implementer_id``), so an ownership check cannot tell the worker that
        parked the row from anyone else. Before this rule the displaced worker
        could close its own ``blocked`` row to ``done`` and erase the reason it
        was parked, leaving a row that is terminal *and* still carries a
        ``block_reason``. Closing one is now an explicit act of adjudication
        (``kg_tools._queue_close``), not a work item -- and the orchestrator's
        own close is refused, which is what makes
        :meth:`test_dependency_blocked_mid_run_stops_dependent_dispatch`
        report ``conflict`` instead of ``complete``.
        """
        self.make_root(keys=("A", "B"))
        inv = fx.inv_id("A")
        self.assertTrue(queue_op(op="claim", id=inv, implementer_id="worker",
                                 binary_sha256=fx.SHA)["claimed"])
        blocked = q.release(inv, "worker", to="blocked",
                            reason="operator:wrong_abi")
        self.assertTrue(blocked["released"], blocked)
        parked = fx.row(self.db, inv)
        self.assertEqual((parked["status"], parked["implementer_id"],
                          parked["block_reason"]),
                         ("blocked", None, "operator:wrong_abi"), parked)
        # the lease holder itself is refused: parking a row does not buy the
        # right to unpark it
        refused = queue_op(op="close", id=inv, implementer_id="worker",
                           status="done")
        self.assertEqual(refused["code"], "blocked", refused)
        self.assertEqual(refused["block_reason"], "operator:wrong_abi", refused)
        # a stranger is refused identically -- there is nothing to compare
        stranger = queue_op(op="close", id=inv, implementer_id="stranger",
                            status="done")
        self.assertEqual(stranger["code"], "blocked", stranger)
        # and the orchestrator's adapter cannot express the adjudication at all
        self.assertEqual(q.close(inv, "worker", disposition="done")["code"],
                         "blocked")
        # the row is byte-for-byte what it was
        self.assertEqual(fx.row(self.db, inv), parked,
                         "a refused close mutated a blocked row")
        # only an explicit adjudication may close it
        allowed = queue_op(op="close", id=inv, implementer_id="adjudicator",
                           status="done", allow_blocked=True)
        self.assertTrue(allowed["closed"], allowed)
        self.assertEqual(allowed["previous_status"], "blocked")
        final = fx.row(self.db, inv)
        self.assertEqual(final["status"], "done", final)
        self.assertIsNone(final["implementer_id"], final)

    def test_no_lease_survives_a_failed_run(self):
        keys = ("A", "B", "D", "E1")
        self.make_root_at("broken", keys=keys)
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])
        worker = fx.worker("malformed_json")
        # no validator stub: a malformed reply is rejected at ingest, so the
        # real validator never gets a say and the outcome cannot be an artefact
        # of a stubbed verdict
        outcome = orch.run(root=self.info["root"], limit=50, worker=worker,
                           implementer_id="orch", write=False)
        # the run terminates: every dispatchable target produced a routable
        # record and no thread died
        self.assertEqual(outcome["summary"]["errors"], [])
        self.assertEqual(outcome["summary"]["partial"], len(keys), outcome["summary"])
        self.assertEqual(outcome["summary"]["error"], 0, outcome["summary"])
        self.assertEqual(sorted(record["va"] for record in outcome["results"]),
                         sorted(VA_OF[key] for key in keys))
        for record in outcome["results"]:
            self.assertEqual(record["code"], "malformed_worker_output", record)
            self.assertEqual([event["op"] for event in record["events"]],
                             ["claim", "brief", "launch", "ingest", "release"])
        # no work is lost and no work is locked
        self.assertEqual(fx.rows_by_status(self.db, "active"), [],
                         "a lease survived a run of malformed replies")
        for key in keys:
            row = fx.row(self.db, fx.inv_id(key))
            self.assertNotEqual(row["status"], "active", (key, row))
            self.assertIn(row["status"], ("queued", "blocked"), (key, row))
            self.assertIsNone(row["implementer_id"], (key, row))
            self.assertEqual(row["block_reason"], None, (key, row))
        # PINNED (orchestrate.py:470 + kg_tools.py:901-906): the malformed
        # counter only persists through ``queue.checkpoint``, which is refused,
        # so ``MAX_MALFORMED`` is unreachable and each target is retried for
        # ever instead of escalating. The run is only finite because the plan
        # is. Intended assertion once fixed: a second run reports
        # ``code`` starting ``escalated:`` and never calls the worker again.
        self.assertEqual(len(worker.calls), len(keys))
        self.assertTrue(all(call["attempt"] == 1 for call in worker.calls))
        for key in keys:
            self.assertIsNone(fx.row(self.db, fx.inv_id(key))["attempts"])

    def test_stale_worker_after_takeover_cannot_write(self):
        self.make_root(keys=("A",))
        inv = fx.inv_id("A")
        first = queue_op(op="claim", id=inv, implementer_id="alice",
                         binary_sha256=fx.SHA)
        self.assertTrue(first["claimed"], first)
        fx.backdate(self.db, inv, when=fx.FIXED_NOW, owner="alice")
        taken = queue_op(op="claim", id=inv, implementer_id="bob",
                         binary_sha256=fx.SHA, allow_stale=True,
                         stale_after_seconds=60)
        self.assertTrue(taken["claimed"], taken)
        self.assertEqual(taken["displaced_owner"]["owner"], "alice")
        self.assertEqual(fx.row(self.db, inv)["implementer_id"], "bob")
        for name, result, code in (
                ("checkpoint", q.checkpoint(inv, "alice", payload={"x": 1},
                                            stage="VALIDATE"), "not_owner"),
                ("release", q.release(inv, "alice", to="queued"), "not_owner"),
                ("close", q.close(inv, "alice", disposition="done"), "not_owner"),
                # a claim is its own verb and names the refusal already_claimed
                ("claim", queue_op(op="claim", id=inv, implementer_id="alice",
                                   binary_sha256=fx.SHA), "already_claimed")):
            self.assertEqual(result.get("code"), code, (name, result))
            self.assertEqual(result.get("implementer_id"), "bob", (name, result))
        row = fx.row(self.db, inv)
        self.assertEqual(row["implementer_id"], "bob", row)
        self.assertEqual(row["status"], "active", row)
        self.assertIsNone(row["evidence_refs"])
        self.assertIsNone(row["attempts"])
        self.assertIsNone(row["block_reason"])
        # and the current owner is unaffected by the displaced worker's attempts
        self.assertTrue(
            queue_op(op="close", id=inv, implementer_id="bob",
                     status="done")["closed"])


class DeterminismAndIsolationTest(fx.FixtureTestCase):
    """S22-S24: reproducibility, and the committed graph's immunity."""

    # -- S22 -------------------------------------------------------------- #
    def test_plan_is_byte_identical_across_calls(self):
        from tools.reconstruction_tooling.models import canonical_json

        self.make_root(keys=fx.DEFAULT_KEYS + FLAT)
        first = self.plan(limit=50)
        second = self.plan(limit=50)
        self.assertEqual(canonical_json(first), canonical_json(second),
                         "the plan is not stable across two calls on one root")
        # a third call, after the index cache has been dropped, must agree too
        fx.clear_index_cache()
        third = self.plan(limit=50)
        self.assertEqual(canonical_json(first), canonical_json(third))
        # the FULL document carries no wall clock, which is what makes the
        # byte-for-byte comparison above possible at all
        self.assertEqual(clock_leaks(first), [])
        self.assertEqual(clock_leaks(first["targets"]), [])
        self.assertEqual(clock_leaks(first["waves"]), [])

    def test_plan_is_byte_identical_for_two_independent_roots(self):
        from tools.reconstruction_tooling.models import canonical_json

        documents = []
        for name in ("repeat-a", "repeat-b"):
            self.make_root_at(name, keys=fx.DEFAULT_KEYS + FLAT)
            documents.append(self.plan(limit=50))
        left, right = documents
        # the only documented difference between two identical synthetic roots
        # is the database path each one was given
        self.assertNotEqual(left["database"], right["database"])
        self.assertEqual(canonical_json(dict(left, database="<db>")),
                         canonical_json(dict(right, database="<db>")))

    # -- S23 -------------------------------------------------------------- #
    def test_run_is_deterministic_after_scrubbing(self):
        # Volatile keys, and why each one is legitimately volatile:
        #   seconds   -- orchestrate.run's measured wall clock (orchestrate.py:731)
        #   database  -- the absolute path of this root's temp queue database,
        #                reported at orchestrate.py:192 for auditing
        # Neither is an input to the plan or to a worker's result, and nothing
        # else has to be scrubbed.
        volatile = ("seconds", "database")
        captured = []
        for name in ("det-a", "det-b"):
            self.make_root_at(name, keys=("A", "B", "D", "E1"))
            self.stub_validator("PASS")
            outcome = orch.run(root=self.info["root"], limit=50,
                               worker=fx.worker("ok"), implementer_id="orch",
                               write=False)
            self.assertEqual(outcome["summary"]["errors"], [], name)
            captured.append({
                "summary": outcome["summary"],
                "plan_summary": outcome["plan"]["summary"],
                "database": outcome["plan"]["database"],
                "waves": [(wave["index"], wave["reason"],
                           [(entry["va"], entry["role"], entry["unit"])
                            for entry in wave["targets"]])
                          for wave in outcome["plan"]["waves"]],
                "results": [{key: value for key, value in record.items()
                             if key != "events"}
                            for record in outcome["results"]],
                # the per-target ``launch`` event carries the worker's own
                # elapsed time, the same clock as ``summary.seconds``
                "events": [[event for event in record["events"]]
                           for record in
                           sorted(outcome["results"],
                                  key=lambda item: str(item["va"]))],
            })
        first, second = captured
        self.assertEqual(fx.scrub(first, keys=volatile),
                         fx.scrub(second, keys=volatile))
        # the scrub is the minimum, not a convenience: the two runs report
        # different databases, and ``seconds`` is present in both summaries as
        # the only key that is not required to agree.
        self.assertNotEqual(first["database"], second["database"])
        self.assertIn("seconds", first["summary"])
        self.assertEqual(sorted(set(first["summary"]) ^ set(second["summary"])), [])
        for key in first["summary"]:
            if key in volatile:
                continue
            self.assertEqual(first["summary"][key], second["summary"][key], key)

    # -- S24 -------------------------------------------------------------- #
    def test_committed_database_and_working_tree_are_untouched(self):
        before_db = fx.committed_db_fingerprint()
        before_git = fx.git_status()
        self.assertIsNotNone(before_db["sha256"])
        self.make_root(keys=fx.DEFAULT_KEYS + FLAT)
        self.stub_validator("PASS")
        planned = self.plan(limit=50)
        # Derived from the plan, never hardcoded: every target the scheduler
        # considers available must come out of the run. "Available" is
        # schedule.classify's own set (schedule.py:291-292), which includes
        # ``dependent`` -- a dependent is offered once its prerequisites land,
        # so the run is expected to complete strictly more targets than the
        # plan marked ``dispatchable``.
        available = ("independent", "coordinated", "dependent", "uncertain")
        expected = sorted(item["va"] for item in planned["targets"]
                          if item["role"] in available)
        deferred_only = sorted(item["va"] for item in planned["targets"]
                               if not item["dispatchable"])
        # the only target the plan itself defers is the dependent
        self.assertEqual(deferred_only, [VA_OF[key] for key in DEPENDENT],
                         deferred_only)
        outcome = orch.run(root=self.info["root"], limit=50,
                           worker=fx.worker("ok"), implementer_id="orch",
                           write=False)
        self.assertEqual(outcome["summary"]["errors"], [])
        self.assertEqual(outcome["summary"]["targets"], len(expected),
                         outcome["summary"])
        self.assertEqual(outcome["summary"]["complete"], len(expected),
                         outcome["summary"])
        self.assertEqual(sorted(record["va"] for record in outcome["results"]),
                         expected)
        # the dependent was promoted and landed, which is what makes the count
        # larger than the plan's ``dispatchable`` total
        self.assertGreater(len(expected),
                           sum(1 for item in planned["targets"]
                               if item["dispatchable"]))
        self.assertEqual(planned["summary"]["dispatchable"],
                         len(expected) - len(DEPENDENT))
        after_db = fx.committed_db_fingerprint()
        after_git = fx.git_status()
        # sha256, mtime_ns and the WAL/shm side-file names, all unchanged
        self.assertEqual(after_db, before_db,
                         "the committed knowledge graph changed during a run")
        self.assertEqual(sorted(after_db["side_files"]),
                         sorted(before_db["side_files"]))
        # Tracked-file dirt must be identical. Untracked ("??") entries are
        # compared as a set difference only, because other agents share this
        # working tree; a new untracked path is reported, never asserted.
        self.assertEqual([item for item in after_git if item[0] != "??"],
                         [item for item in before_git if item[0] != "??"],
                         "a run dirtied the working tree")
        new_untracked = sorted(set(after_git) - set(before_git))
        self.assertEqual([item for item in new_untracked
                          if not item[1].startswith("tests/")], [],
                         "a pipeline run created files outside tests/: %r"
                         % (new_untracked,))
        # the run was pointed at the temp database the whole way through
        self.assertTrue(os.path.abspath(self.info["root"]).startswith(
            os.path.abspath(self.tmpdir) + os.sep))
        self.assertTrue(os.environ["OPENSPORE_DB"].startswith(
            os.path.abspath(self.tmpdir) + os.sep))
        self.assertTrue(q.db_is_isolated())
        # and every dispatched target really did land in the temp database only
        for record in outcome["results"]:
            self.assertEqual(record["status"], "complete", record)
            self.assertEqual(
                fx.row(self.db, record["queue_id"])["status"], "done", record)
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])


if __name__ == "__main__":
    unittest.main()
