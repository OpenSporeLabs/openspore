"""Shared synthetic fixtures for the orchestration integration tests.

Not named ``test_*`` on purpose, so ``unittest discover`` ignores it
(same convention as ``tests/diff_real.py``).

Everything here is synthetic and lives inside a caller-supplied tempdir:

* :func:`build_root` writes the *minimum* set of canonical artifacts that
  ``tools/reconstruction_knowledge.build_index`` insists on reading, plus a
  small ``src/reconstruction/<pkg>/<stem>.cpp`` per target so
  ``tools.reconstruction_tooling.validate`` can resolve a source span.
* :func:`synthetic_db` creates the queue database from the committed
  ``knowledgegraph/schema.sql`` and seeds ``investigations`` rows. It is
  written to ``<root>/knowledgegraph/spore.db`` on purpose: that is the exact
  path ``tools.reconstruction_tooling.frontier._claims`` opens for a
  non-repo root, so the plan layer and the queue layer agree on one database.

Canonical artifacts required by ``build_index`` (verified by reading it):

===========================================  ==================================
``knowledgegraph/research/source-reconstruction-manifest.json``  ``load_json``
``knowledgegraph/triage/queue-f0e310e0-v6.json``                 ``load_json``
``knowledgegraph/research/semantic-decomp.json``                 ``load_json``
``knowledgegraph/triage/xrefs-2540f2ca.tsv``                     ``open()``
===========================================  ==================================

``reconstruction/metadata``, ``reconstruction/integrated`` and
``knowledgegraph/research/conflicts`` are globbed, so they are optional.
The four files above are also re-hashed byte-wise at the end of
``build_index``, so all four must exist.

Two views of the call graph are deliberately modelled separately because the
production code reads them from separate files:

* the **TSV export** feeds ``frontier``'s ``open_callees`` (and therefore the
  eligible/deferred split);
* the **SQLite ``xref`` table** feeds ``schedule.scc_partition`` (and
  therefore the strongly-connected-component grouping).

Keeping the P/Q cycle out of the TSV is what makes both members *eligible*,
so the coordinated SCC unit is actually dispatched instead of being deferred
forever by their own mutual edge. ``build_root(cycle_in_tsv=True)`` models
the other case and ``test_orchestration_scheduling`` pins the behaviour.
"""

import hashlib
import contextlib
import json
import os
import shutil
import sqlite3
import subprocess
import tempfile
import threading
import time
import unittest

from tools.mcp import config

# A synthetic build identity. Never the real binary's sha.
SHA = "d" * 64
FIXED_NOW = "2020-01-01 00:00:00"
FIXED_NOW_ISO = "2020-01-01T00:00:00Z"

MANIFEST_REL = "knowledgegraph/research/source-reconstruction-manifest.json"
QUEUE_REL = "knowledgegraph/triage/queue-f0e310e0-v6.json"
XREF_TSV_REL = "knowledgegraph/triage/xrefs-2540f2ca.tsv"
SEMANTIC_REL = "knowledgegraph/research/semantic-decomp.json"

# key -> spec. ``camel`` is the human name; the reconstructed C++ symbol is
# ``reconstruct_<bare_va>_<camel>`` so ``validate._target_span`` can find the
# span by VA token *and* by name words.
TARGETS = {
    "A": {"va": "0x00b3d300", "camel": "AlphaReader", "package": "PKG-SYNTH-ALPHA",
          "subsystem": "synth_io", "cluster": "cluster-alpha", "priority": "P1"},
    "B": {"va": "0x00b3d400", "camel": "BravoWriter", "package": "PKG-SYNTH-ALPHA",
          "subsystem": "synth_io", "cluster": "cluster-alpha", "priority": "P1"},
    "C": {"va": "0x00b3d500", "camel": "CharlieSink", "package": "PKG-SYNTH-ALPHA",
          "subsystem": "synth_io", "cluster": "cluster-alpha", "priority": "P2"},
    "D": {"va": "0x00b3d600", "camel": "DeltaReader", "package": "PKG-SYNTH-ALPHA",
          "subsystem": "synth_io", "cluster": "cluster-alpha", "priority": "P0"},
    "P": {"va": "0x00b3d700", "camel": "PapaLoop", "package": "PKG-SYNTH-LOOP",
          "subsystem": "synth_loop", "cluster": "cluster-loop", "priority": "P1"},
    "Q": {"va": "0x00b3d800", "camel": "QuebecLoop", "package": "PKG-SYNTH-LOOP",
          "subsystem": "synth_loop", "cluster": "cluster-loop", "priority": "P1"},
    # Four extra independent targets: nothing calls them and they call nothing,
    # so they widen the frontier without adding a wave.
    "E1": {"va": "0x00b3d900", "camel": "EchoOne", "package": "PKG-SYNTH-FLAT",
           "subsystem": "synth_flat", "cluster": "cluster-flat", "priority": "P3"},
    "E2": {"va": "0x00b3da00", "camel": "EchoTwo", "package": "PKG-SYNTH-FLAT",
           "subsystem": "synth_flat", "cluster": "cluster-flat", "priority": "P3"},
    "E3": {"va": "0x00b3db00", "camel": "EchoThree", "package": "PKG-SYNTH-FLAT",
           "subsystem": "synth_flat", "cluster": "cluster-flat", "priority": "P3"},
    "E4": {"va": "0x00b3dc00", "camel": "EchoFour", "package": "PKG-SYNTH-FLAT",
           "subsystem": "synth_flat", "cluster": "cluster-flat", "priority": "P3"},
}

DEFAULT_KEYS = ("A", "B", "C", "D", "P", "Q")
FLAT_KEYS = ("E1", "E2", "E3", "E4")

# Call edges as (caller, callee, callsite) over the key namespace. C calls
# A, B and D, so C is the only dependent target; A, B and D are wave 0. The
# last two form the 2-cycle P -> Q -> P.
CALL_EDGES = (
    ("C", "A", "0x00b3d510"),
    ("C", "B", "0x00b3d520"),
    ("C", "D", "0x00b3d530"),
    ("P", "Q", "0x00b3d710"),
    ("Q", "P", "0x00b3d810"),
)
CYCLE_KEYS = ("P", "Q")

RESULT_SCHEMA = "openspore-worker-result-1"
VALID_OUTCOMES = ("IMPLEMENTED", "PARTIAL", "STRUCTURAL_ONLY", "STILL_UNKNOWN",
                  "BLOCKED", "FAILED_VALIDATION")
TERMINAL_OUTCOMES = ("IMPLEMENTED", "PARTIAL", "STRUCTURAL_ONLY")


def sha256_file(path):
    """Streamed sha256, mirroring tests/viewer/test_server.py::_sha256."""
    digest = hashlib.sha256()
    with open(path, "rb") as handle:
        for block in iter(lambda: handle.read(65536), b""):
            digest.update(block)
    return digest.hexdigest()


def bare(va):
    return va[2:] if va.startswith("0x") else va


def source_rel(key):
    return "src/reconstruction/pkg_synth_%s/%s.cpp" % (key.lower(), key.lower())


def symbol(key):
    return "reconstruct_%s_%s" % (bare(TARGETS[key]["va"]), TARGETS[key]["camel"])


def inv_id(key):
    """Canonical queue id ``kind:bare_hex:name`` (see kg_tools._derive_inv_id)."""
    return "fun:%s:%s" % (bare(TARGETS[key]["va"]), TARGETS[key]["camel"])


def source_text(key, convention=None):
    """A deterministic C++ span ``validate._target_span`` can locate.

    The convention token goes *after* the return type because
    ``validate.RETURN_DECL`` only accepts calling-convention macros in that
    position; putting it before the return type silently defeats the match.
    """
    header = "// synthetic fixture source for %s (%s)\n" % (
        TARGETS[key]["camel"], TARGETS[key]["va"])
    if convention:
        header += "// persisted ABI convention disagrees with this source\n"
    return (
        header
        + "#include <stdint.h>\n\n"
        + "extern \"C\" int %s%s(int value) {\n"
        % ("__%s " % convention if convention else "", symbol(key))
        + "    int total = value;\n"
        + "    if (total > 0) {\n"
        + "        total = total - 1;\n"
        + "    }\n"
        + "    return total;\n"
        + "}\n"
    )


def _write(path, text):
    parent = os.path.dirname(path)
    if parent:
        os.makedirs(parent, exist_ok=True)
    with open(path, "w", encoding="utf-8") as handle:
        handle.write(text)


def _write_json(path, document):
    _write(path, json.dumps(document, indent=2, sort_keys=True) + "\n")


def build_root(tmp, keys=DEFAULT_KEYS, cycle_in_tsv=False, conflicts=(),
               xrefs=True):
    """Materialise a synthetic OpenSpore root under ``tmp``.

    ``keys``          which of :data:`TARGETS` to materialise.
    ``cycle_in_tsv``  also export the P/Q cycle into the TSV the frontier
                      reads (frontier then defers both members forever).
    ``conflicts``     keys that get a metadata record claiming ``cdecl`` while
                      their source declares ``__thiscall`` -- a deterministic
                      validator FAIL.
    ``xrefs``         write the SQLite ``xref`` rows (done by
                      :func:`synthetic_db`, this flag only controls the TSV
                      plus a placeholder note so both stay in sync).

    Returns a dict describing the root. ``db`` is created by
    :func:`synthetic_db`; the returned ``db_path`` is where it must go.
    """
    keys = tuple(keys)
    root = os.path.abspath(tmp)
    os.makedirs(root, exist_ok=True)

    # -- manifest --------------------------------------------------------- #
    functions = []
    triage = []
    for key in keys:
        spec = TARGETS[key]
        functions.append({
            "va": spec["va"],
            "normalized_symbol": spec["camel"],
            "subsystem": spec["subsystem"],
            "package": spec["package"],
            "source_file": source_rel(key),
            "body_status": "unresolved",
            "observed_mechanics": ["synthetic fixture record for %s" % key],
            "evidence_level": "SUPPORTED",
        })
        triage.append({
            "va": spec["va"],
            "name": spec["camel"],
            "package": spec["package"],
            "subsystem": spec["subsystem"],
            "cluster": spec["cluster"],
            "priority": spec["priority"],
            "evidence": "SUPPORTED",
            "queue_state": "queued",
            "rank": 100 + len(triage),
            "category": "ENGINE_IMPLEMENTATION",
            "dependencies": [],
        })
    _write_json(os.path.join(root, MANIFEST_REL), {
        "schema": "openspore-source-reconstruction-manifest-1",
        "binary": {"sha256": SHA, "name": "SporeApp.exe",
                   "source": "synthetic-fixture"},
        "functions": functions,
        "packages": [{"id": TARGETS[key]["package"], "status": "triage_only"}
                     for key in keys],
        "types": [],
    })
    _write_json(os.path.join(root, QUEUE_REL), {
        "schema": "openspore-triage-queue-1",
        "queue": triage,
    })
    _write_json(os.path.join(root, SEMANTIC_REL), {
        "schema": "openspore-semantic-decomp-1",
        "records": [{"va": TARGETS[key]["va"],
                     "subsystem": TARGETS[key]["subsystem"],
                     "package": TARGETS[key]["package"],
                     "hypothesis": "synthetic %s" % key}
                    for key in keys],
        "contradictions": [],
        "family_index": [],
    })

    # -- TSV xref export (feeds frontier's open_callees) -------------------- #
    lines = ["caller_va\tcallee_va\treference_type\tcallsite_va"]
    for caller, callee, site in CALL_EDGES:
        if caller not in keys or callee not in keys:
            continue
        if set((caller, callee)) == set(CYCLE_KEYS) and not cycle_in_tsv:
            continue
        lines.append("%s\t%s\tdirect-call\t%s" % (bare(TARGETS[caller]["va"]),
                                                  bare(TARGETS[callee]["va"]),
                                                  site))
    _write(os.path.join(root, XREF_TSV_REL), "\n".join(lines) + "\n")

    # -- canonical source + optional metadata ------------------------------ #
    for key in keys:
        conflict = key in conflicts
        _write(os.path.join(root, source_rel(key)),
               source_text(key, "thiscall" if conflict else None))
        if conflict:
            _write_json(os.path.join(
                root, "reconstruction", "metadata", "pkg_synth_%s" % key.lower(),
                "%s.json" % bare(TARGETS[key]["va"])), {
                "va": TARGETS[key]["va"],
                "abi": {"calling_convention": "cdecl", "return_type": "int"},
                "source_files": [source_rel(key)],
            })

    return {
        "root": root,
        "keys": keys,
        "sha": SHA,
        "db_path": os.path.join(root, "knowledgegraph", "spore.db"),
        "ids": {key: inv_id(key) for key in keys},
        "vas": {key: TARGETS[key]["va"] for key in keys},
    }


def xref_rows(keys=DEFAULT_KEYS, cycle=True):
    """SQLite ``xref`` rows for the scheduler's SCC pass."""
    rows = []
    for caller, callee, site in CALL_EDGES:
        if caller not in keys or callee not in keys:
            continue
        if set((caller, callee)) == set(CYCLE_KEYS) and not cycle:
            continue
        rows.append((bare(TARGETS[caller]["va"]), bare(TARGETS[callee]["va"]),
                     "direct-call", bare(site)))
    return rows


def synthetic_db(root_info, rows=(), keys=None, xrefs=True):
    """Create the synthetic queue DB and seed ``investigations`` rows.

    ``rows`` may be a mapping ``key -> column overrides`` (a ``queued`` row is
    created for every key in ``keys`` regardless) or a sequence of explicit
    tuples. Returns the database path.
    """
    keys = tuple(root_info["keys"]) if keys is None else tuple(keys)
    path = root_info["db_path"] if isinstance(root_info, dict) else \
        os.path.join(str(root_info), "knowledgegraph", "spore.db")
    os.makedirs(os.path.dirname(path), exist_ok=True)
    if os.path.exists(path):
        os.unlink(path)
    with open(config.resolve("knowledgegraph", "schema.sql"),
              encoding="utf-8") as handle:
        schema = handle.read()
    connection = sqlite3.connect(path)
    try:
        connection.executescript(schema)
        overrides = rows if isinstance(rows, dict) else {}
        extra = [] if isinstance(rows, dict) else list(rows or ())
        for key in keys:
            spec = TARGETS[key]
            patch = dict(overrides.get(key, {}))
            connection.execute(
                "INSERT INTO investigations(id,kind,va,name,subsystem,mode,"
                "why_interesting,stage,status,binary_sha256) "
                "VALUES(?,?,?,?,?,?,?,?,?,?)",
                (inv_id(key), "function", bare(spec["va"]), spec["camel"],
                 spec["subsystem"], "replace", "synthetic fixture", "QUEUED",
                 patch.pop("status", "queued"), patch.pop("binary_sha256", SHA)))
            for column, value in sorted(patch.items()):
                connection.execute(
                    "UPDATE investigations SET %s=? WHERE id=?" % column,
                    (value, inv_id(key)))
        for row in extra:
            connection.execute(
                "INSERT INTO investigations(id,kind,va,name,subsystem,mode,"
                "why_interesting,stage,status,binary_sha256) "
                "VALUES(?,?,?,?,?,?,?,?,?,?)", row)
        if xrefs:
            for caller, callee, kind, site in xref_rows(keys):
                connection.execute(
                    "INSERT INTO xref(caller_va,callee_va,reference_type,"
                    "callsite_va,source,snapshot_sha256) "
                    "VALUES(?,?,?,?,?,?)",
                    (caller, callee, kind, site, "synthetic-fixture", SHA))
        connection.commit()
    finally:
        connection.close()
    return path


def backdate(path, inv_id_value, when=FIXED_NOW, owner=None, status="active"):
    """Force a lease clock with plain SQL (no sleeping in a test)."""
    connection = sqlite3.connect(path)
    try:
        fields = ["status=?", "updated_at=?"]
        values = [status, when]
        if owner is not None:
            fields.append("implementer_id=?")
            values.append(owner)
        values.append(inv_id_value)
        connection.execute(
            "UPDATE investigations SET %s WHERE id=?" % ", ".join(fields), values)
        connection.commit()
    finally:
        connection.close()


def row(path, inv_id_value):
    connection = sqlite3.connect(path)
    connection.row_factory = sqlite3.Row
    try:
        found = connection.execute(
            "SELECT * FROM investigations WHERE id=?", (inv_id_value,)).fetchone()
        return dict(found) if found is not None else None
    finally:
        connection.close()


def rows_by_status(path, status):
    connection = sqlite3.connect(path)
    connection.row_factory = sqlite3.Row
    try:
        return [dict(item) for item in connection.execute(
            "SELECT * FROM investigations WHERE status=? ORDER BY id",
            (status,))]
    finally:
        connection.close()


def result_document(key, outcome="IMPLEMENTED", va=None, schema=RESULT_SCHEMA,
                    source_files=None, **extra):
    """A contract-valid worker result for ``key``."""
    document = {
        "schema": schema,
        "va": va if va is not None else TARGETS[key]["va"],
        "outcome": outcome,
        "summary": "synthetic worker result for %s" % key,
        "normalized_symbol": TARGETS[key]["camel"],
        "reconstructed_symbol": symbol(key),
        "source_files": list(source_files) if source_files is not None
        else [source_rel(key)],
        "observed_mechanics": ["reads the first argument"],
        "semantic_findings": [{"claim": "decrements its argument"}],
        "unresolved_questions": [],
        "evidence_refs": ["reconstruction/knowledge/index.json#/records/%s"
                          % TARGETS[key]["va"]],
    }
    document.update(extra)
    return document


VARIANT_OUTCOME = {
    "ok": "IMPLEMENTED",
    "still_unknown": "STILL_UNKNOWN",
    "failed_validation": "FAILED_VALIDATION",
    "block": "BLOCKED",
    "pass_on_second": "IMPLEMENTED",
    "delay": "IMPLEMENTED",
    "malformed_shape": "IMPLEMENTED",
    "bad_schema": "IMPLEMENTED",
    "bad_outcome": "IMPLEMENTED",
    "wrong_va": "IMPLEMENTED",
    "warn": "IMPLEMENTED",
}
WORKER_VARIANTS = tuple(sorted(list(VARIANT_OUTCOME) + ["malformed_json"]))


class RecordingWorker(object):
    """Deterministic in-process worker.

    ``__call__(package) -> (raw_output, launch_detail)`` -- exactly what
    ``orchestrate.process_target`` destructures. Every invocation is recorded
    (VA, attempt, lease owner, thread, index) under a lock so a test can
    assert both *what* ran and *how many times* it ran.

    Variants:

    ``ok``                a valid ``IMPLEMENTED`` result.
    ``still_unknown``     valid, honest "the evidence does not support a claim".
    ``failed_validation`` the worker ran and the candidate was rejected.
    ``warn``              valid result; used with a WARN verdict.
    ``block``             valid ``BLOCKED`` result.
    ``malformed_json``    not JSON at all, non-zero exit.
    ``malformed_shape``   JSON object missing required result fields.
    ``bad_schema``        wrong ``schema`` value.
    ``bad_outcome``       outcome outside the vocabulary.
    ``wrong_va``          a perfectly valid result for a *different* VA.
    ``pass_on_second``    malformed on the first call, valid afterwards.
    ``delay(seconds)``    sleeps, then behaves like ``ok``.
    """

    def __init__(self, variant="ok", seconds=0.0, barrier=None, key_for_va=None):
        if variant not in WORKER_VARIANTS:
            raise ValueError("unknown worker variant %r" % (variant,))
        self.variant = variant
        self.seconds = float(seconds)
        self.barrier = barrier
        self.key_for_va = key_for_va
        self.calls = []
        self._lock = threading.Lock()
        self._count = 0

    # -- introspection ----------------------------------------------------- #
    @property
    def vas(self):
        return [call["va"] for call in self.calls]

    def count(self, va=None, thread=None, implementer=None):
        result = 0
        for call in self.calls:
            if va is not None and call["va"] != va:
                continue
            if thread is not None and call["thread"] != thread:
                continue
            if implementer is not None and call["implementer"] != implementer:
                continue
            result += 1
        return result

    def attempts(self):
        return sorted(call["attempt"] for call in self.calls)

    # -- the worker itself -------------------------------------------------- #
    def _key(self, package):
        if self.key_for_va is not None:
            return self.key_for_va(package["target"]["va"])
        va = package["target"]["va"]
        for key, spec in TARGETS.items():
            if spec["va"] == va:
                return key
        raise AssertionError("briefing carried an unknown VA %r" % (va,))

    def document(self, package, key):
        variant = self.variant
        if variant == "malformed_shape":
            return json.dumps({"schema": RESULT_SCHEMA,
                               "va": TARGETS[key]["va"],
                               "outcome": "IMPLEMENTED"})
        if variant == "bad_schema":
            return json.dumps(result_document(key, schema="openspore-wrong-9"))
        if variant == "bad_outcome":
            return json.dumps(result_document(key, outcome="ALMOST_DONE"))
        if variant == "wrong_va":
            other = next(name for name in sorted(TARGETS)
                         if name != key and TARGETS[name]["va"]
                         != TARGETS[key]["va"])
            return json.dumps(result_document(key, va=TARGETS[other]["va"]))
        return json.dumps(result_document(key, outcome=VARIANT_OUTCOME[variant]))

    def __call__(self, package):
        with self._lock:
            self._count += 1
            index = self._count
            self.calls.append({
                "index": index,
                "va": package["target"]["va"],
                "attempt": package["lease"]["attempt"],
                "implementer": package["lease"]["implementer_id"],
                "thread": threading.current_thread().name,
                "unit": (package.get("scc") or {}).get("id"),
                "co_workers": sorted((package.get("scc") or {}).get(
                    "co_workers") or []),
                "briefing_sha256": package.get("content_sha256"),
            })
        key = self._key(package)
        variant = self.variant
        if variant == "pass_on_second" and index == 1:
            variant = "malformed_json"
        if self.barrier is not None:
            self.barrier.wait(timeout=30)
        if self.seconds:
            time.sleep(self.seconds)
        if variant == "malformed_json":
            return ("{not json at all\n", {"returncode": 1, "timed_out": False,
                                           "failure": "nonzero_exit"})
        if variant == "malformed_shape" or variant == "bad_schema" \
                or variant == "bad_outcome" or variant == "wrong_va":
            saved, self.variant = self.variant, variant
            try:
                raw = self.document(package, key)
            finally:
                self.variant = saved
            return (raw, {"returncode": 0, "timed_out": False})
        return (self.document(package, key),
                {"returncode": 0, "timed_out": False})


def worker(variant="ok", **kwargs):
    """Factory mirroring ``orchestrate.callable_worker`` but deterministic."""
    return RecordingWorker(variant, **kwargs)


class StubValidator(object):
    """A ``validate()`` stand-in that can emit any verdict deterministically.

    The real validator now returns a static verdict that can be ``PASS`` (see
    ``tests/test_validation_dimensions.py`` for the fixtures that prove it), but
    an orchestration test needs a verdict it chose, not one earned, and needs it
    without a Ghidra session. ``report["status"]`` is an alias of the static
    dimension, so a stub here stands in for the static axis alone.
    """

    def __init__(self, status="PASS", reason="synthetic stub validator"):
        self.status = status
        self.reason = reason
        self.calls = []
        self._lock = threading.Lock()

    def __call__(self, root=None, va=None, write=True, out_dir=None, **kwargs):
        with self._lock:
            self.calls.append(va)
        return {
            "schema": "openspore-structural-validation-1",
            "target": va,
            "status": self.status,
            "static": {"dimension": "STATIC", "status": self.status, "checks": {},
                       "coverage": {}, "evidence_basis": {},
                       "evidence_coverage": {"status": "PASS", "detail": "stub",
                                             "coverage": "complete", "evidence": []}},
            "runtime": {"dimension": "RUNTIME", "status": "GATED", "validated": 0,
                        "gated": True, "gates": ["stub-runtime-gate"],
                        "reason": "stub: the original process was never observed"},
            "source": {"path": None, "role": "missing"},
            "checks": {"STUB": {"status": self.status, "detail": self.reason,
                                "coverage": "complete", "evidence": []}},
            "coverage": {"attempted": 1, "pass": 1 if self.status == "PASS" else 0,
                         "warn": 1 if self.status == "WARN" else 0, "unknown": 0,
                         "not_available": 0, "total": 1, "ratio": 1.0},
            "unresolved_questions": [],
        }

    @property
    def count(self):
        return len(self.calls)


def clear_index_cache():
    """``frontier._INDEX_CACHE`` is process-global and keyed by root."""
    from tools.reconstruction_tooling import frontier as frontier_mod

    frontier_mod._INDEX_CACHE.clear()
    return frontier_mod._INDEX_CACHE


# --------------------------------------------------------------------------- #
# a plan-driven dispatch loop, for tests that want the plan's waves verbatim
# --------------------------------------------------------------------------- #
# SUPERSEDED as a stand-in for ``orchestrate.run``. This helper exists because
# ``run()`` used to be a silently empty no-op: ``threading.Thread(target=
# thread_fn, name=...)`` omitted ``args=(unit_key, members)``, so every dispatch
# thread died before ``dispatch`` ran. That is fixed (the ``args=`` is present
# again, and ``test_orchestration.RunPipelinePinnedDefectTest`` is a live
# regression test for it), so ``orchestrate.run`` is the path the
# wave-ordering and concurrency tests should use.
#
# What this still buys: it walks the *plan's* waves exactly as written, with no
# promotion pass. ``orchestrate.run`` now re-evaluates dispatchability after
# every wave, so a dependent whose prerequisites land mid-run is dispatched by
# ``run()`` but NOT by this helper. Every test that asserts promotion must go
# through ``orchestrate.run``; this is for the tests that specifically want the
# frozen-plan view (determinism of the lifecycle, isolation of the committed
# graph). It is intentionally *not* a second copy of ``run``'s loop.
def dispatch_waves(root, plan, worker, implementation, max_workers=4,
                   live=False, write=False, ttl=1800, thread_exceptions=None):
    """Run ``sched.waves()`` in wave order with a bounded thread pool.

    Same unit grouping, same ``worker_id = "%s/%s" % (implementation,
    unit_key)`` and the same ``process_target`` arguments as
    ``orchestrate.run``, but **without** its post-wave promotion pass: only
    targets the plan marked ``dispatchable`` are sent. Returns
    ``(results, errors)``.
    """
    by_va = {item["va"]: item for item in plan["targets"]}
    results = []
    errors = []
    lock = threading.Lock()
    for wave in plan.get("waves", []):
        if wave.get("reason") != "ready" or not wave.get("targets"):
            continue
        slots = {}
        for entry in wave["targets"]:
            if not (by_va.get(entry["va"]) or {}).get("dispatchable"):
                continue
            unit = entry.get("unit") or entry["va"]
            slots.setdefault(unit, []).append(entry)
        units = sorted(slots.items(), key=lambda item: item[0])

        def dispatch(unit_key, members):
            worker_id = "%s/%s" % (implementation, unit_key)
            local = []
            for entry in members:
                target = dict(by_va[entry["va"]])
                target["scc"] = {"id": unit_key if len(members) > 1 else None,
                                 "size": len(members),
                                 "members": [item["va"] for item in members]}
                try:
                    local.append(process_target(
                        root, target, worker, worker_id, plan["binary_sha256"],
                        live=live, write=write, ttl=ttl, root_index=plan))
                except Exception as exc:  # noqa: BLE001 - mirror run()
                    if thread_exceptions is not None:
                        thread_exceptions.append((unit_key, exc))
                    local.append({"va": entry["va"], "status": "error",
                                  "code": getattr(exc, "code", "tool_error"),
                                  "message": str(exc), "events": []})
            return local

        def thread_fn(unit_key, members):
            try:
                produced = dispatch(unit_key, members)
            except Exception as exc:  # noqa: BLE001
                with lock:
                    errors.append("%s: %s" % (unit_key, exc))
                return
            with lock:
                results.extend(produced)

        pool = []
        for unit_key, members in units:
            while len(pool) >= max(1, int(max_workers)):
                pool.pop(0).join()
            thread = threading.Thread(target=thread_fn,
                                      args=(unit_key, members),
                                      name="test-%s" % unit_key)
            pool.append(thread)
            thread.start()
        for thread in pool:
            thread.join()
    return sorted(results, key=lambda item: str(item.get("va"))), errors


def process_target(root, target, worker, implementer_id, binary_sha256, **kwargs):
    """``orchestrate.process_target`` looked up at call time.

    Late binding matters: the tests that need a different verdict swap
    ``orchestrate.validate`` (via :class:`StubValidator`) and this indirection
    keeps the swap effective for :func:`dispatch_waves` too.
    """
    from tools.reconstruction_tooling import orchestrate as orchestrate_mod

    return orchestrate_mod.process_target(root, target, worker, implementer_id,
                                          binary_sha256, **kwargs)


# --------------------------------------------------------------------------- #
# base TestCase
# --------------------------------------------------------------------------- #
class FixtureTestCase(unittest.TestCase):
    """Tempdir + env isolation + ``frontier._INDEX_CACHE`` discipline.

    ``frontier._INDEX_CACHE`` is a process-global dict keyed by root; a stale
    entry makes the *next* synthetic root silently reuse the previous root's
    projection, which produces a green but wrong suite. It is cleared in
    ``setUp`` *and* in ``addCleanup`` (belt and braces: a test that raises
    mid-``setUp`` must not leave an index behind for its neighbours).
    """

    def setUp(self):
        self._saved_env = {}
        for name in ("OPENSPORE_DB", "OPENSPORE_GHIDRA", "OPENSPORE_MCP_TRUSTED",
                     "DISPLAY", "OPENSPORE_RECONSTRUCTION_INDEX"):
            self._saved_env[name] = os.environ.get(name)
        self.tmpdir = tempfile.mkdtemp(prefix="openspore-orchestration-test-")
        self.addCleanup(self._restore)
        os.environ.pop("OPENSPORE_MCP_TRUSTED", None)  # gates stay closed
        os.environ.pop("DISPLAY", None)  # never needs a display
        os.environ["OPENSPORE_GHIDRA"] = "http://127.0.0.1:9"  # offline
        self.addCleanup(self._assert_cache_empty)
        self.addCleanup(clear_index_cache)
        clear_index_cache()
        self.info = None
        self.db = None
        self._saved_production = {}

    # -- helpers ----------------------------------------------------------- #
    def make_root(self, **kwargs):
        """Build a synthetic root under ``self.tmpdir`` and point the queue at it."""
        name = "root-%d" % (len(os.listdir(self.tmpdir)) + 1)
        self.info = build_root(os.path.join(self.tmpdir, name), **kwargs)
        self.db = synthetic_db(self.info)
        os.environ["OPENSPORE_DB"] = self.db
        clear_index_cache()
        return self.info

    def make_root_at(self, name, **kwargs):
        self.info = build_root(os.path.join(self.tmpdir, name), **kwargs)
        self.db = synthetic_db(self.info)
        os.environ["OPENSPORE_DB"] = self.db
        clear_index_cache()
        return self.info

    def seed_db(self, rows=()):
        """Re-seed the current root's DB in place (same root, new rows)."""
        self.db = synthetic_db(self.info, rows=rows)
        os.environ["OPENSPORE_DB"] = self.db
        return self.db

    def stub_validator(self, status="PASS"):
        """Swap ``orchestrate.validate`` for a verdict stub, restored on cleanup."""
        from tools.reconstruction_tooling import orchestrate as orchestrate_mod

        stub = StubValidator(status)
        if "validate" not in self._saved_production:
            self._saved_production["validate"] = orchestrate_mod.validate
        orchestrate_mod.validate = stub
        self.addCleanup(self._restore_production)
        return stub

    def set_production(self, name, value):
        from tools.reconstruction_tooling import orchestrate as orchestrate_mod

        if name not in self._saved_production:
            self._saved_production[name] = getattr(orchestrate_mod, name)
        setattr(orchestrate_mod, name, value)
        self.addCleanup(self._restore_production)

    def plan(self, root=None, **kwargs):
        from tools.reconstruction_tooling import orchestrate as orchestrate_mod

        return orchestrate_mod.plan(root=root or self.info["root"], **kwargs)

    # -- teardown ---------------------------------------------------------- #
    def _restore_production(self):
        from tools.reconstruction_tooling import orchestrate as orchestrate_mod

        for name, value in self._saved_production.items():
            setattr(orchestrate_mod, name, value)
        self._saved_production.clear()

    def _restore(self):
        from tools.reconstruction_tooling import orchestrate as orchestrate_mod

        self._restore_production()
        for name, value in self._saved_env.items():
            if value is None:
                os.environ.pop(name, None)
            else:
                os.environ[name] = value
        del orchestrate_mod  # noqa: F821 - keep the import honest
        shutil.rmtree(self.tmpdir, ignore_errors=True)

    def _assert_cache_empty(self):
        from tools.reconstruction_tooling import frontier as frontier_mod

        self.assertEqual(getattr(frontier_mod, "_INDEX_CACHE", None), {},
                         "frontier._INDEX_CACHE was not cleared between tests")


def scrub(value, keys=("seconds",)):
    """Drop volatile timing keys so two runs can be compared byte for byte."""
    if isinstance(value, dict):
        return {name: scrub(item, keys) for name, item in sorted(value.items())
                if name not in keys}
    if isinstance(value, list):
        return [scrub(item, keys) for item in value]
    return value


@contextlib.contextmanager
def spy_queue(names=("checkpoint", "release", "close")):
    """Record every ``queue.*`` call the orchestrator makes, and delegate.

    ``orchestrate`` resolves ``q.checkpoint`` etc. as module attributes at call
    time, so wrapping the attribute on the ``queue`` module records the real
    arguments and the real return value without touching production code. Used
    to assert on payloads that the orchestrator *attempts* to persist even
    while the durable write is being refused.
    """
    from tools.reconstruction_tooling import queue as queue_mod

    original = {name: getattr(queue_mod, name) for name in names}
    seen = {name: [] for name in names}

    def make(name):
        def wrapper(*args, **kwargs):
            result = original[name](*args, **kwargs)
            seen[name].append({"args": args, "kwargs": kwargs, "result": result})
            return result
        return wrapper

    try:
        for name in names:
            setattr(queue_mod, name, make(name))
        yield seen
    finally:
        for name, function in original.items():
            setattr(queue_mod, name, function)


def summary_of(results):
    """A stable, ordering-independent summary of ``process_target`` records."""
    counts = {}
    for record in results:
        counts[record.get("status")] = counts.get(record.get("status"), 0) + 1
    return {
        "statuses": dict(sorted(counts.items())),
        "codes": sorted(str(record.get("code")) for record in results),
        "vas": sorted(str(record.get("va")) for record in results),
        "operations": [sorted(event["op"] for event in record.get("events", []))
                       for record in
                       sorted(results, key=lambda item: str(item.get("va")))],
    }


def committed_db_fingerprint():
    """sha256 + mtime_ns + WAL side-file names of the committed knowledge graph.

    Mirrors ``tests/viewer/test_server.py::_sha256``/``_side_files``.
    """
    root = os.path.dirname(config.resolve("knowledgegraph", "spore.db"))
    path = os.path.join(root, "spore.db")
    fingerprint = {
        "sha256": sha256_file(path) if os.path.exists(path) else None,
        "mtime_ns": os.stat(path).st_mtime_ns if os.path.exists(path) else None,
        "side_files": sorted(name for name in os.listdir(root)
                             if name.startswith("spore.db")),
    }
    return fingerprint


def git_status(repo_root=None):
    """``git status --porcelain`` as a list of (code, path) pairs."""
    root = repo_root or os.path.dirname(config.resolve("knowledgegraph", "spore.db"))
    output = subprocess.run(["git", "-C", root, "status", "--porcelain"],
                            stdout=subprocess.PIPE, stderr=subprocess.DEVNULL,
                            check=True).stdout.decode("utf-8", "replace")
    pairs = []
    for line in output.splitlines():
        if not line:
            continue
        pairs.append((line[:2].strip() or line[:2], line[3:].strip()))
    return pairs

