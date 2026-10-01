"""Turning a promoted package into a satisfied dependency.

``promote`` decides whether a staged package may live in ``src/``. It is
deliberately silent about the scheduler: promotion answers "is this a real
reconstruction?", not "may its callers now be dispatched?". The gap this module
fills is the second question, and closing it is the only sanctioned way for a
promoted VA to stop being an open callee.

Why the two must be separate
----------------------------

The scheduler's dependency predicate is ``schedule._reconstructed`` -- nothing
else. It reads ``record["reconstructed"]`` / ``record["status"]`` out of the
generated projection, and those are derived by ``reconstruction_knowledge``
from the canonical manifest's ``body_status`` / ``integration_status``
(``status_for``). So a dependency becomes satisfied when, and only when, a
manifest ``functions[]`` entry says ``integrated``. This module is the
sanctioned writer of that transition, and it is deliberately the *only* one
that writes it from a promotion rather than from a human editing the manifest.

What may be written
-------------------

Exactly five things: ``body_status``, ``integration_status``, ``source_file``
and ``source_files``, and one top-level ``change_log`` entry. The transition is
built as a shallow copy of the existing manifest entry with only those keys
replaced, so a runtime key cannot be written even by accident.

``review_status`` is deliberately **not** written. It is inside the permitted
set but nothing in a promotion is a review verdict: a build gate and a static
validator are not a reviewer, and writing ``approved`` would manufacture the
one piece of the reconstruction the campaign has never collected. Leaving the
existing value untouched is the honest reading of the permission.

Runtime validation cannot leak
------------------------------

A promoted package is ``static_status == "PASS"`` and
``runtime_status == "GATED"`` by construction (``promote`` refuses every other
composition), and the runtime axis is an open gate. Satisfying a dependency
therefore changes the *static* story only. The VA stays runtime-GATED by the
absence of ``record["runtime"]["validated"]`` in the projection, and
``status_for`` returns ``"reconstructed"`` rather than a runtime state because
``integration == "integrated"`` is checked before any runtime gate. Nothing here
writes, clears or synthesises a runtime field, and ``RUNTIME_KEYS`` names the
keys a test pins byte-for-byte across a write.

Green is never inferred
-----------------------

A satisfied dependency is a claim that the promoted bytes compile and pass their
model tests, so the build verdict is load-bearing in the worst way: a compile
failure that reported itself as satisfied would unblock every caller of a
package that does not build. The verdict is therefore read from the promotion
record's ``build`` field, and green requires ``build["ok"] is True`` **and** a
recorded step list -- the gate always reports its steps, and a verdict carrying
``note: "gate skipped by request"`` with an empty ``steps`` is a *skipped* gate,
not a green build. The absence of a recorded failure is not a pass. Passing
``verify_build=True`` re-runs ``build_gate.gate`` on the installed package and
demands the same thing from a live compile.

Creating a row that was never there
----------------------------------

``knowledgegraph/research/source-reconstruction-manifest.json`` is the only
input ``reconstruction_knowledge.status_for`` reads, and the four targets that
were already ``STATIC_VALIDATED`` pass only because a triage import happened to
give them a ``functions[]`` row. A genuinely new target therefore could never
satisfy a dependency, so the dependency graph could never move. This module
closes that circularity: when the row is **absent** and every admission
condition is otherwise met, the row is created from the promotion record.

Creating is not a weaker gate
----------------------------

The create path runs the *identical* admission sequence as the update path --
``not_promoted``, ``ambiguous_owner``, ``promotion_unreadable``,
``not_static_validated``, ``no_test``, ``no_promotion_record`` /
``promotion_record_unreadable``, ``build_not_green``, ``manifest_unreadable``
-- and only then, and only if none of them fired, does the row get built. The
absent row is therefore never a way around a promotion: it is the *last* thing
looked at, and it is the only condition the create path adds. A candidate whose
row is absent and whose promotion is incomplete is refused with
``no_manifest_entry`` plus whatever else is wrong, and writes nothing.

No field is invented
--------------------

Every field of a created row names the artifact it came from, in the authority
order the brief fixes: the promotion record ``reconstruction/evidence/<bare8>/
promotion.json`` (schema ``openspore-promotion-record-1``), then the installed
``src/reconstruction/<pkg>/promotion.json`` (schema ``openspore-promotion-1``),
then the validation report. ``va`` comes from the promotion record. The symbol
comes from the metadata sidecar the record names, else from the installed
marker, else from the VA itself -- and the VA-derived form is only taken when
the record names that VA, because a name with no artifact behind it is a
fabrication. If nothing supplies one the candidate is refused with
``no_symbol_source``. The per-field origins are surfaced in the plan
(``manifest_sources``) and in the ``change_log`` row, so the provenance of a
created row is auditable after the fact and not merely asserted here.

What a created row does *not* get is as load-bearing as what it does. No
``evidence_level``: it is a semantic label out of ``policy.semantic_labels`` and
a judgement about evidence strength, not a fact any artifact records. No
``signature_status``: that is a Ghidra observation. No ``review_status``: the
existing write path already declines to invent a review verdict, and a created
row has the same problem plus the absence of a row to inherit from. No
``runtime_gate`` family, ever. And no top-level ``metrics`` rewrite: those
counters are independently maintained and their derivation rules are not
recoverable from ``functions[]`` (``signature_records`` counts 300 records of
which 288 carry a ``signature_status``), so recomputing them would be a guess
and bumping one of them would be a different guess. ``policy.source_provenance_
required`` *is* honoured, so every created row carries the real artifact paths
it was built from.

Reversal is a removal
--------------------

A created row has no prior state to restore, so ``unsatisfy`` deletes it rather
than writing back two nulls. The ``change_log`` row carries
``manifest_action``, so the reversal is decidable from the manifest alone: the
same recovery story the update path already has, with the one extra step that a
row which never existed must not be resurrected as a stub.

No second anything
------------------

This module writes the canonical manifest through the canonical atomic writer
and then calls ``integrate.apply`` -- the only writer of ``index.json`` /
``bootstrap.json`` -- and clears ``frontier._INDEX_CACHE`` so a same-process
caller cannot read the projection this write invalidated. It creates no queue,
no manifest, no database, no lock file and no status sidecar, and it never
touches ``reconstruction/staging/``. There is exactly one manifest and exactly
one projection, and this module is a writer of both, not a third place.
"""

import sqlite3
from datetime import datetime, timezone
from pathlib import Path

from . import frontier as frontier_mod
from . import integrate as integrate_mod
from . import promote as promote_mod
from . import schedule as sched
from .models import ROOT, load_json, normalize_va

try:
    from tools import reconstruction_knowledge as rk
except ImportError as exc:
    raise RuntimeError("reconstruction knowledge module is unavailable") from exc

PLAN_SCHEMA = "openspore-satisfy-plan-1"
RESULT_SCHEMA = "openspore-satisfy-result-1"
MANIFEST_REL = "knowledgegraph/research/source-reconstruction-manifest.json"
CHANGE_LOG_KEY = "change_log"
EVIDENCE_REL = "reconstruction/evidence"
EVIDENCE_NAME = "evidence.json"
PROMOTION_NAME = "promotion.json"
SATISFIED_BODY_STATUS = "integrated"
SATISFIED_INTEGRATION_STATUS = "integrated"
# The keys whose values must be identical before and after a write. Named here
# rather than only in a test because they are the shape of the leak this module
# is written to prevent.
RUNTIME_KEYS = ("runtime_gate", "runtime_gates", "runtime_validated",
                "audit_runtime_gated")
CHANGE_KIND_SATISFY = "satisfy"
CHANGE_KIND_UNSATISFY = "unsatisfy"
# The three states a manifest row can be in, as the plan reports them. ``create``
# is a promise, not a fact: it is only reported when every other admission
# condition already passed, so a plan that says ``create`` is a plan ``apply``
# will carry out.
MANIFEST_ACTION_UPDATE = "update"
MANIFEST_ACTION_CREATE = "create"
MANIFEST_ACTION_ABSENT = "absent"
MANIFEST_ACTIONS = (MANIFEST_ACTION_UPDATE, MANIFEST_ACTION_CREATE,
                    MANIFEST_ACTION_ABSENT)
# Where the change_log row says which of the two happened, so ``unsatisfy`` can
# tell "restore the prior statuses" from "delete the row that was created".
CHANGE_ACTION_KEY = "manifest_action"
# The plan/result field names.
ACTION_FIELD = "manifest_action"
SOURCES_FIELD = "manifest_sources"
# A created row is built key by key from this list. Naming every writable key is
# the point: a runtime key cannot be written by a created row even by accident,
# exactly as it cannot be written by an updated one.
CREATED_ENTRY_KEYS = ("va", "normalized_symbol", "package", "subsystem",
                      "body_status", "integration_status", "source_file",
                      "source_files", "source_provenance")
# The order the symbol is looked for in: most specific artifact first.
SYMBOL_KEYS = ("normalized_symbol", "symbol")
# The last resort, and only when the promotion record names the VA. A name
# derived from the address is a deterministic derivation, not an invention, but
# it is only honest when the artifact that claims this VA says so.
DERIVED_SYMBOL_PREFIX = "fun_"

BLOCKERS = frozenset({
    "va_invalid",
    "not_promoted",
    "ambiguous_owner",
    "promotion_unreadable",
    "not_static_validated",
    "no_test",
    "no_promotion_record",
    "promotion_record_unreadable",
    "build_not_green",
    "no_manifest_entry",
    "no_symbol_source",
    "manifest_unreadable",
    "no_change_log",
    "unsatisfy_not_satisfied",
})


def _blocker(code, detail):
    # type: (str, str) -> dict
    if code not in BLOCKERS:
        raise AssertionError("undeclared blocker code: %s" % code)
    return {"code": code, "detail": detail}


def _bare(value):
    # type: (object) -> str
    return normalize_va(value)[2:]


def _read_json(path):
    # type: (Path) -> tuple
    """``(document, problem)``; ``problem`` is ``None``, ``"missing"`` or text."""
    if not Path(path).is_file():
        return None, "missing"
    try:
        return load_json(path), None
    except (OSError, ValueError) as exc:
        return None, "%s: %s" % (type(exc).__name__, exc)


def _today():
    # type: () -> str
    return datetime.now(timezone.utc).strftime("%Y-%m-%d")


def _database(root):
    # type: (Path) -> object
    """The call-graph database, opened read-only, or ``None``.

    Opened the way ``frontier._claims`` opens it: one path per root, ``mode=ro``
    on the URI, so the committed knowledge graph cannot be written from here
    even by accident.
    """
    path = Path(root) / frontier_mod.DB_REL
    if not path.is_file():
        return None
    try:
        return sqlite3.connect("file:%s?mode=ro" % path, uri=True, timeout=5.0)
    except sqlite3.Error:  # pragma: no cover - defensive
        return None


def _callers_of_record(dependencies):
    # type: (object) -> list
    """Callers named by one evidence pack's dependency block, normalised."""
    if not isinstance(dependencies, dict):
        return []
    found = set()
    for endpoint in dependencies.get("callers", []) or []:
        value = endpoint.get("va") if isinstance(endpoint, dict) else endpoint
        try:
            found.add(normalize_va(value))
        except (TypeError, ValueError):
            continue
    for edge in dependencies.get("edges", []) or []:
        if not isinstance(edge, dict) or edge.get("direction") != "in":
            continue
        try:
            found.add(normalize_va(edge.get("other")))
        except (TypeError, ValueError):
            continue
    return sorted(found)


def _evidence_callers(root, bare):
    # type: (Path, str) -> list
    document, _problem = _read_json(Path(root) / EVIDENCE_REL / bare / EVIDENCE_NAME)
    record = document.get("record") if isinstance(document, dict) else None
    return _callers_of_record((record or {}).get("dependencies"))


def _callers(root, va, database):
    # type: (Path, str, object) -> list
    """Every real caller of ``va``: the xref table plus the evidence edges.

    The xref table is the whole binary and the evidence pack is the narrower
    per-VA view; a caller present in only one of them is still a real caller,
    and dropping it would silently under-report what a promotion unblocks.
    """
    bare = _bare(va)
    found = set()
    if database is not None:
        query = ("SELECT DISTINCT caller_va FROM xref WHERE callee_va=? "
                 "AND reference_type IN (%s)" % ",".join("?" * len(sched.CALL_REFERENCE_TYPES)))
        try:
            for row in database.execute(query, (bare,) + sched.CALL_REFERENCE_TYPES):
                try:
                    found.add(normalize_va(row[0]))
                except (TypeError, ValueError):
                    continue
        except sqlite3.Error:
            pass
    found.update(_evidence_callers(root, bare))
    return sorted(found)


def _functions_by_va(document):
    # type: (object) -> dict
    found = {}
    for function in (document.get("functions") or []) if isinstance(document, dict) else []:
        if not isinstance(function, dict):
            continue
        try:
            va = normalize_va(function.get("va") or function.get("function_address"))
        except (TypeError, ValueError):
            continue
        found[va] = function
    return found


def _triage_by_va(root):
    # type: (Path) -> dict
    try:
        document = frontier_mod._queue(root)
    except Exception:
        return {}
    found = {}
    for row in (document or {}).get("queue", []) or []:
        if not isinstance(row, dict):
            continue
        try:
            va = normalize_va(row.get("va"))
        except (TypeError, ValueError):
            continue
        found[va] = row
    return found


def _status(function, triage_row):
    # type: (dict, dict) -> str
    """The authoritative status, through the only function that derives one."""
    try:
        return str(rk.status_for(function or {}, triage_row or {}))
    except Exception:  # pragma: no cover - status_for is total on a mapping
        return "unresolved"


def _needs_satisfied(va, status):
    # type: (str, str) -> bool
    """Ask the scheduler's own predicate, not a copy of it."""
    index = {"records": {va: {"reconstructed": status == "reconstructed",
                              "status": status}}}
    return not sched._reconstructed(index, va)


class _Dependencies(object):
    """Caller/disposition view over the existing frontier and scheduler.

    Every eligibility question is answered by ``frontier.frontier`` and
    ``schedule.classify``; this class only decides *which* functions to ask
    about and caches the answer for the length of one call. It re-derives no
    rule of its own: a target is deferred because ``frontier`` said so, and a
    prerequisite is open because ``schedule._open_callees`` said so.
    """

    def __init__(self, root, database):
        # type: (Path, object) -> None
        self._root = Path(root)
        self._database = database
        self._survey = False
        self._classified = False
        self._index = False

    def _load_survey(self):
        if self._survey is False:
            try:
                self._survey = frontier_mod.frontier(
                    self._root,
                    type("Args", (), {"limit": 1000, "offset": 0})())
            except Exception:
                self._survey = None
        return self._survey or {}

    def _load_index(self):
        if self._index is False:
            try:
                self._index = frontier_mod._index(self._root)
            except Exception:
                self._index = {"records": {}}
        return self._index or {"records": {}}

    def classified(self):
        # type: () -> dict
        """VA -> its ``schedule.classify`` row, for the whole survey."""
        if self._classified is False:
            survey = self._load_survey()
            considered = [target for target in survey.get("targets", []) or []
                          if target.get("disposition") in ("eligible", "deferred")]
            if not considered:
                self._classified = {}
            else:
                database = _database(self._root)
                try:
                    partition = sched.scc_partition(
                        root=self._root,
                        vas=[target["va"] for target in considered],
                        db=database)
                finally:
                    if database is not None:
                        database.close()
                targets = []
                for target in considered:
                    prepared = dict(target)
                    prepared["claim_state"] = (target.get("claim") or {}).get("state")
                    prepared["priority"] = target.get("score", 0)
                    prepared["queue_row"] = None
                    targets.append(prepared)
                self._classified = {row["va"]: row
                                    for row in sched.classify(targets, self._load_index(),
                                                              partition)}
        return self._classified

    def _open_callees(self, va):
        # type: (str) -> list
        """What ``schedule._open_callees`` believes is blocking ``va``."""
        survey = self._load_survey()
        target = next((item for item in survey.get("targets", []) or []
                       if item.get("va") == va), None)
        if target is None:
            return []
        universe = set(item.get("va") for item in survey.get("targets", []) or [])
        return sched._open_callees(target, universe, self._load_index())

    def deferred_on(self, va):
        # type: (str) -> list
        """Callers of ``va`` that the frontier defers *because of* ``va``.

        Both halves are required and neither is this module's opinion: the
        frontier must have called the caller ``deferred`` and listed ``va`` in
        its open callees, and the scheduler must independently agree that
        ``va`` is still an open prerequisite. A caller the frontier defers for
        another reason, or one the scheduler does not treat as blocked, is not
        a dependent of this promotion and is not reported as one.
        """
        survey = self._load_survey()
        by_va = {target.get("va"): target for target in survey.get("targets", []) or []}
        classified = self.classified()
        reported = []
        for caller in _callers(self._root, va, self._database):
            target = by_va.get(caller)
            if target is None or target.get("disposition") != "deferred":
                continue
            if va not in (target.get("open_dependencies") or target.get("open_callees") or []):
                continue
            row = classified.get(caller)
            if row is None or va not in self._open_callees(caller):
                continue
            reported.append(caller)
        return sorted(reported)

    def unblocked(self, va):
        # type: (str) -> list
        """Callers of ``va`` the frontier now calls ``eligible``.

        Read *after* the manifest write, so this is the post-transition fact:
        the caller no longer lists ``va`` as an open callee and its disposition
        is ``eligible``.
        """
        survey = self._load_survey()
        by_va = {target.get("va"): target for target in survey.get("targets", []) or []}
        reported = []
        for caller in _callers(self._root, va, self._database):
            target = by_va.get(caller)
            if target is None or target.get("disposition") != "eligible":
                continue
            if va in (target.get("open_dependencies") or target.get("open_callees") or []):
                continue
            reported.append(caller)
        return sorted(reported)


def _promoted_packages(root):
    # type: (Path) -> dict
    """Bare VA -> the ``src`` package that promotes it, and its marker."""
    found = {}
    for bare, owners in promote_mod._promoted_va_owners(root).items():
        for owner in sorted(owners):
            document, problem = _read_json(
                Path(root) / promote_mod.SRC_REL / owner / PROMOTION_NAME)
            if document is None:
                found.setdefault(bare, []).append((owner, None, problem))
            else:
                found.setdefault(bare, []).append((owner, document, None))
    return found


def _target_of(marker, bare):
    # type: (object, str) -> object
    for target in (marker or {}).get("targets", []) or []:
        if not isinstance(target, dict):
            continue
        try:
            if _bare(target.get("va")) == bare:
                return target
        except (TypeError, ValueError):
            continue
    return None


def _src_sources(root, src_package, target):
    # type: (Path, str, dict) -> list
    """Installed source paths of one promoted target, as repo-relative files."""
    found = []
    for name in (target or {}).get("sources") or []:
        relative_path = "%s/%s/%s" % (promote_mod.SRC_REL, src_package, name)
        if (Path(root) / relative_path).is_file():
            found.append(relative_path)
    return sorted(found)


def _build_green(build):
    # type: (object) -> tuple
    """``(green, detail)`` for a recorded build verdict.

    A skipped gate records ``ok: True`` and an empty ``steps`` list. Treating
    that as green would make "nobody compiled it" indistinguishable from "it
    compiled", which is exactly the confusion this module exists to prevent, so
    a green verdict must carry at least one recorded step.
    """
    if not isinstance(build, dict):
        return False, "the promotion record carries no build verdict (%r)" % (
            type(build).__name__,)
    if build.get("ok") is not True:
        return False, "the recorded build verdict is %r, not ok=true" % (
            build.get("ok"),)
    if not build.get("steps"):
        return False, "the recorded build verdict is a skipped gate (%r), not a build" % (
            build.get("note") or "no steps recorded",)
    return True, ""


def _adjudicate(root, va, functions, triage, packages, dependencies, manifest_problem):
    # type: (Path, str, dict, dict, dict, object, object) -> dict
    """Decide whether one VA may become a satisfied dependency, and why not."""
    candidate = {
        "va": va,
        "src_package": None,
        "promotion_record": None,
        "static_status": None,
        "runtime_status": None,
        "current_status": None,
        "current_body_status": None,
        "current_integration_status": None,
        "needs_satisfied": False,
        "dependents_unblocked": [],
        "blockers": [],
        ACTION_FIELD: MANIFEST_ACTION_ABSENT,
        SOURCES_FIELD: {},
        "_target": None,
        "_marker": None,
        "_record": None,
        "_created": None,
        "_triage": {},
    }
    bare = _bare(va)
    owners = packages.get(bare) or []
    if not owners:
        candidate["blockers"].append(_blocker(
            "not_promoted",
            "no src/reconstruction/*/promotion.json claims 0x%s" % bare))
    elif len(owners) > 1:
        candidate["blockers"].append(_blocker(
            "ambiguous_owner",
            "0x%s is promoted by %s" % (bare, ", ".join(sorted(item[0] for item in owners)))))
    else:
        src_package, marker, problem = owners[0]
        candidate["src_package"] = src_package
        marker_rel = "%s/%s/%s" % (promote_mod.SRC_REL, src_package, PROMOTION_NAME)
        if marker is None:
            candidate["blockers"].append(_blocker(
                "promotion_unreadable" if problem != "missing" else "not_promoted",
                "%s %s" % (marker_rel, problem)))
        else:
            target = _target_of(marker, bare)
            if marker.get("schema") != promote_mod.PACKAGE_SCHEMA:
                candidate["blockers"].append(_blocker(
                    "not_promoted",
                    "%s carries schema %r, expected %r"
                    % (marker_rel, marker.get("schema"), promote_mod.PACKAGE_SCHEMA)))
            elif target is None:
                candidate["blockers"].append(_blocker(
                    "not_promoted", "%s does not list 0x%s as a target" % (marker_rel, bare)))
            else:
                _adjudicate_target(root, bare, src_package, target, candidate)
                candidate["_target"] = target
                candidate["_marker"] = marker
    if manifest_problem is not None:
        candidate["blockers"].append(_blocker(
            "manifest_unreadable", "%s %s" % (MANIFEST_REL, manifest_problem)))
    candidate["_triage"] = triage.get(va) or {}
    function = functions.get(va)
    if function is None:
        _adjudicate_absent(root, va, candidate)
    else:
        candidate[ACTION_FIELD] = MANIFEST_ACTION_UPDATE
        status = _status(function, candidate["_triage"])
        candidate["current_status"] = status
        candidate["current_body_status"] = function.get("body_status")
        candidate["current_integration_status"] = function.get("integration_status")
        candidate["needs_satisfied"] = _needs_satisfied(va, status)
    if dependencies is not None:
        candidate["dependents_unblocked"] = dependencies.deferred_on(va)
    return candidate


def _adjudicate_absent(root, va, candidate):
    # type: (Path, str, dict) -> None
    """Decide what an absent manifest row means: a creation, or a refusal.

    An absent row is a *provisionable* state, not a verdict. It is adjudicated
    last, after every promotion condition, so it can only ever add the action --
    never remove a blocker. The status reported is the one ``status_for`` derives
    from an entry that does not exist, so ``needs_satisfied`` is the scheduler's
    own answer for a target with no row rather than an assumption that it is
    already satisfied.
    """
    status = _status({}, candidate.get("_triage") or {})
    candidate["current_status"] = status
    candidate["needs_satisfied"] = _needs_satisfied(va, status)
    if candidate["blockers"]:
        candidate["blockers"].append(_blocker(
            "no_manifest_entry", "%s has no functions[] entry for %s" % (MANIFEST_REL, va)))
        return
    entry, sources, problem = _created_entry(root, va, candidate)
    if entry is None:
        candidate["blockers"].append(_blocker(
            "no_manifest_entry", "%s has no functions[] entry for %s" % (MANIFEST_REL, va)))
        candidate["blockers"].append(_blocker("no_symbol_source", problem))
        return
    candidate["_created"] = entry
    candidate[SOURCES_FIELD] = sources
    candidate[ACTION_FIELD] = MANIFEST_ACTION_CREATE


def _adjudicate_target(root, bare, src_package, target, candidate):
    # type: (Path, str, str, dict, dict) -> None
    """The promotion evidence half: statuses, a test TU, and a green build."""
    static = target.get("static_status")
    runtime = target.get("runtime_status")
    candidate["static_status"] = static
    candidate["runtime_status"] = runtime
    if static != promote_mod.REQUIRED_STATIC_STATUS or \
            runtime != promote_mod.REQUIRED_RUNTIME_STATUS:
        candidate["blockers"].append(_blocker(
            "not_static_validated",
            "static_status is %r and runtime_status is %r; a dependency may only be "
            "satisfied by the composition static %s + runtime %s"
            % (static, runtime, promote_mod.REQUIRED_STATIC_STATUS,
               promote_mod.REQUIRED_RUNTIME_STATUS)))
    if not (target.get("tests") or []):
        candidate["blockers"].append(_blocker(
            "no_test", "the promoted target lists no test translation unit"))
    record_rel = "%s/%s/%s" % (EVIDENCE_REL, bare, PROMOTION_NAME)
    candidate["promotion_record"] = record_rel
    record, problem = _read_json(Path(root) / record_rel)
    if record is None:
        candidate["blockers"].append(_blocker(
            "no_promotion_record" if problem == "missing" else "promotion_record_unreadable",
            "%s %s" % (record_rel, problem)))
        return
    candidate["_record"] = record
    green, detail = _build_green(record.get("build"))
    if not green:
        candidate["blockers"].append(_blocker("build_not_green", "%s: %s" % (record_rel, detail)))


def _entry_va(function):
    # type: (object) -> str
    """The canonical VA of one ``functions[]`` entry, or ``""`` if unreadable."""
    if not isinstance(function, dict):
        return ""
    try:
        return normalize_va(function.get("va") or function.get("function_address"))
    except (TypeError, ValueError):
        return ""


def _named(mapping):
    # type: (object) -> object
    """The first non-empty name any artifact offers, by manifest preference."""
    if not isinstance(mapping, dict):
        return None
    for key in SYMBOL_KEYS:
        value = mapping.get(key)
        if isinstance(value, str) and value.strip():
            return value.strip()
    return None


def _metadata_paths(candidate, bare):
    # type: (dict, str) -> list
    """Candidate locations of the metadata sidecar, most authoritative first.

    The promotion record names its own sidecar, so that path is first; the
    package spellings follow because a record without a ``metadata`` field is
    legal and the directory is still derivable.
    """
    record = candidate.get("_record") or {}
    marker = candidate.get("_marker") or {}
    relative = []
    for owner in (record, marker):
        value = owner.get("metadata")
        if isinstance(value, str) and value.strip():
            relative.append(value.strip())
    for package in (record.get("package"), marker.get("package"),
                    candidate.get("src_package")):
        if isinstance(package, str) and package.strip():
            relative.append("%s/%s/%s.json"
                            % (promote_mod.METADATA_REL, package.strip(), bare))
    ordered = []
    for item in relative:
        if item not in ordered:
            ordered.append(item)
    return ordered


def _validation_rel(candidate):
    # type: (dict) -> object
    """The validation report the promotion names, or ``None``."""
    for owner in (candidate.get("_record") or {}, candidate.get("_marker") or {},
                  candidate.get("_target") or {}):
        value = owner.get("validation")
        if isinstance(value, str) and value.strip():
            return value.strip()
    return None


def _artifact_names(root, candidate, bare):
    # type: (Path, dict, str) -> list
    """``(name, artifact)`` for every artifact that names this target, best first.

    In the order the brief fixes: the promotion record, then the metadata
    sidecar it names, then the installed marker, then the validation report.
    """
    found = []
    record_rel = candidate.get("promotion_record")
    name = _named(candidate.get("_record"))
    if name is not None and record_rel:
        found.append((name, record_rel))
    for relative in _metadata_paths(candidate, bare):
        document, _problem = _read_json(Path(root) / relative)
        name = _named(document)
        if name is not None:
            found.append((name, relative))
    name = _named(candidate.get("_target"))
    if name is not None and candidate.get("src_package"):
        found.append((name, "%s/%s/%s" % (promote_mod.SRC_REL,
                                          candidate["src_package"],
                                          PROMOTION_NAME)))
    validation = _validation_rel(candidate)
    if validation is not None:
        document, _problem = _read_json(Path(root) / validation)
        name = _named(document)
        if name is not None:
            found.append((name, validation))
    return found


def _created_symbol(root, va, candidate):
    # type: (Path, str, dict) -> tuple
    """``(name, artifact, problem)`` for a row this module would create.

    The name is looked for in the artifacts in authority order and, as a last
    resort, derived from the VA -- but only when the promotion record names that
    VA, because the record is what ties a row to an address. With no artifact
    behind it, a name is a fabrication, so the candidate is refused.
    """
    bare = _bare(va)
    named = _artifact_names(root, candidate, bare)
    if named:
        name, artifact = named[0]
        return name, artifact, None
    record = candidate.get("_record")
    if not isinstance(record, dict):
        return None, None, ("the promotion record is absent, so no artifact "
                            "supplies a name for 0x%s" % bare)
    recorded = record.get("va") or record.get("bare_va")
    try:
        anchored = recorded is not None and _bare(recorded) == bare
    except (TypeError, ValueError):
        anchored = False
    if not anchored:
        return None, None, ("no artifact supplies a name for 0x%s and %s names "
                            "no VA to derive one from"
                            % (bare, candidate.get("promotion_record") or
                               "the promotion record"))
    return "%s%s" % (DERIVED_SYMBOL_PREFIX, bare), "va:%s" % candidate.get("promotion_record"), None


def _created_entry(root, va, candidate):
    # type: (Path, str, dict) -> tuple
    """``(entry, field_sources, problem)`` for a manifest row to be created.

    Built key by key from ``CREATED_ENTRY_KEYS`` and nothing else, so no runtime
    key can appear; every key that is written names the artifact it was read
    from in ``field_sources``, which the plan surfaces and the ``change_log``
    records.
    """
    bare = _bare(va)
    entry = {}
    sources = {}
    record = candidate.get("_record")
    record_rel = candidate.get("promotion_record")
    if not isinstance(record, dict) or not record_rel:
        return None, {}, "the promotion record is absent, so no field can be sourced"
    va_recorded = record.get("va")
    try:
        canonical = normalize_va(va_recorded)
    except (TypeError, ValueError):
        return None, {}, ("%s records no VA, so a created row cannot be tied to "
                          "an address" % record_rel)
    if canonical != va:
        return None, {}, ("%s records VA %r, not %s" % (record_rel, va_recorded, va))
    entry["va"] = va
    sources["va"] = record_rel
    name, artifact, problem = _created_symbol(root, va, candidate)
    if name is None:
        return None, {}, problem
    entry["normalized_symbol"] = name
    sources["normalized_symbol"] = artifact
    provenance = [record_rel]
    for relative in _metadata_paths(candidate, bare):
        if (Path(root) / relative).is_file():
            provenance.append(relative)
    marker = candidate.get("_marker") or {}
    if candidate.get("src_package"):
        marker_rel = "%s/%s/%s" % (promote_mod.SRC_REL, candidate["src_package"],
                                   PROMOTION_NAME)
        provenance.append(marker_rel)
    validation = _validation_rel(candidate)
    if validation is not None:
        provenance.append(validation)
    entry["body_status"] = SATISFIED_BODY_STATUS
    entry["integration_status"] = SATISFIED_INTEGRATION_STATUS
    sources["body_status"] = record_rel
    sources["integration_status"] = record_rel
    for key in ("package", "subsystem"):
        value = record.get(key)
        if not isinstance(value, str) or not value.strip():
            continue
        entry[key] = value.strip()
        sources[key] = record_rel
    sources_list = _src_sources(Path(root), candidate["src_package"],
                                candidate.get("_target"))
    if sources_list:
        entry["source_file"] = sources_list[0]
        entry["source_files"] = list(sources_list)
        sources["source_file"] = sources_list[0]
        sources["source_files"] = ",".join(sources_list)
    # ``policy.source_provenance_required`` is the manifest's own rule, so a row
    # created here carries the real paths it was built from.
    entry["source_provenance"] = sorted(set(provenance))
    sources["source_provenance"] = ",".join(entry["source_provenance"])
    entry = {key: entry[key] for key in CREATED_ENTRY_KEYS if key in entry}
    leaked = [key for key in RUNTIME_KEYS if key in entry]
    if leaked:  # pragma: no cover - the whitelist above makes this unreachable
        raise AssertionError("a created entry carries runtime keys: %s" % leaked)
    return entry, sources, None


def _wanted(root, vas, packages):
    # type: (Path, object, dict) -> list
    """Which VAs to adjudicate: the named ones, or every promoted VA."""
    if vas is None:
        return ["0x%s" % bare for bare in sorted(packages)]
    wanted = []
    for value in vas:
        try:
            wanted.append(normalize_va(value))
        except (TypeError, ValueError):
            wanted.append(str(value))
    return wanted


def _candidates(root, vas, dependencies=None):
    # type: (Path, object, object) -> tuple
    """``(candidates, manifest_document, manifest_problem)``; writes nothing."""
    root = Path(root)
    document, problem = _read_json(root / MANIFEST_REL)
    functions = _functions_by_va(document)
    triage = _triage_by_va(root)
    packages = _promoted_packages(root)
    candidates = []
    for va in _wanted(root, vas, packages):
        try:
            canonical = normalize_va(va)
        except (TypeError, ValueError):
            refused = {
                "va": va, "src_package": None, "promotion_record": None,
                "static_status": None, "runtime_status": None,
                "current_status": None, "current_body_status": None,
                "current_integration_status": None, "needs_satisfied": False,
                "dependents_unblocked": [],
                ACTION_FIELD: MANIFEST_ACTION_ABSENT,
                SOURCES_FIELD: {},
                "blockers": [_blocker("va_invalid", "not an x86-32 VA: %r" % (va,))],
            }
            candidates.append(refused)
            continue
        candidates.append(_adjudicate(root, canonical, functions, triage,
                                      packages, dependencies, problem))
    return candidates, document, problem


def _gate_module():
    # type: () -> object
    """The build-gate module, resolved the way ``promote`` resolves it.

    ``importlib.import_module`` and not ``from . import build_gate``: the latter
    answers from the package attribute when one is set and only falls back to
    ``sys.modules`` when it is not, so the two could disagree about which module
    a substituted gate is. Resolving both verbs the same way means a caller that
    swaps the gate gets the same verdict out of ``promote`` and out of
    ``satisfy``.
    """
    import importlib

    module = importlib.import_module(".build_gate", __package__)
    if not hasattr(module, "gate"):
        raise ImportError("build_gate exposes no gate()")
    return module


def _verify_live_builds(root, candidates):
    # type: (Path, list) -> list
    """Re-run the build gate for every candidate about to be written.

    The recorded verdict is the default evidence; this is the opt-in
    re-verification, and it demands the same ``ok`` plus a real step list from a
    live compile of the installed package.
    """
    build_gate = _gate_module()

    for candidate in candidates:
        gate = build_gate.gate(str(root), packages=[candidate["src_package"]])
        green = bool(gate.get("ok")) and bool(gate.get("steps"))
        verdict = (gate.get("packages") or {}).get(candidate["src_package"])
        if not green or not isinstance(verdict, dict) or verdict.get("ok") is not True:
            candidate["blockers"].append(_blocker(
                "build_not_green",
                "a live build gate for %s is not green: ok=%r packages=%r"
                % (candidate["src_package"], gate.get("ok"),
                   verdict.get("status") if isinstance(verdict, dict) else verdict)))
    return candidates


def _transition(root, function, candidate):
    # type: (Path, dict, dict) -> dict
    """The new manifest entry: a copy with five keys replaced at most.

    ``dict(function)`` is a shallow copy, so every key this module does not
    name -- every runtime key, every audit finding, every unresolved question --
    is carried over by value and cannot be dropped, cleared or synthesised.
    """
    updated = dict(function)
    updated["body_status"] = SATISFIED_BODY_STATUS
    updated["integration_status"] = SATISFIED_INTEGRATION_STATUS
    sources = _src_sources(Path(root), candidate["src_package"], candidate.get("_target"))
    if sources:
        existing = [item for item in (updated.get("source_files") or [])
                    if isinstance(item, str)]
        updated["source_files"] = sorted(set(existing) | set(sources))
        if not updated.get("source_file"):
            updated["source_file"] = sources[0]
    return updated


def _change_log_entry(vas, reason, implementer_id, kind, rows):
    # type: (list, object, object, str, list) -> dict
    entry = {
        "kind": kind,
        "date": _today(),
        "reason": str(reason).strip() if reason else None,
        "implementer_id": str(implementer_id).strip() if implementer_id else None,
        "vas": sorted(vas),
        "rows": rows,
    }
    return entry


def _invalidate(root):
    # type: (Path) -> None
    """Drop this root's projection from the process-global cache.

    ``frontier._INDEX_CACHE`` is keyed by resolved root and never invalidated.
    A same-process caller after a manifest write would otherwise read the index
    this write just made stale -- a green but wrong answer, which is the worst
    failure mode this layer has.
    """
    frontier_mod._INDEX_CACHE.pop(str(Path(root).resolve()), None)


def plan(root=ROOT, vas=None):
    # type: (Path, object) -> dict
    """Read-only. Decide which VAs a promotion may satisfy, and refuse the rest.

    Writes nothing, creates no scratch directory, and takes no timestamp. A
    refused candidate does not make ``ok`` false: ``ok`` reports that the plan
    itself ran, exactly as ``promote.plan`` reports it.
    """
    root = Path(root)
    database = _database(root)
    try:
        dependencies = _Dependencies(root, database)
        candidates, _document, _problem = _candidates(root, vas, dependencies)
    finally:
        if database is not None:
            database.close()
    public = [{key: candidate[key] for key in
               ("va", "src_package", "promotion_record", "static_status",
                "runtime_status", "current_status", "current_body_status",
                "current_integration_status", "needs_satisfied",
                "dependents_unblocked", ACTION_FIELD, SOURCES_FIELD,
                "blockers")}
              for candidate in candidates]
    admissible = [item for item in public if not item["blockers"]]
    return {
        "schema": PLAN_SCHEMA,
        "ok": True,
        "candidates": public,
        "summary": {
            "candidates": len(public),
            "admissible": len(admissible),
            "needs_satisfied": len([item for item in admissible if item["needs_satisfied"]]),
            "already_satisfied": len([item for item in admissible if not item["needs_satisfied"]]),
            "refused": len([item for item in public if item["blockers"]]),
            "creates": len([item for item in admissible
                            if item[ACTION_FIELD] == MANIFEST_ACTION_CREATE]),
            "updates": len([item for item in admissible
                            if item[ACTION_FIELD] == MANIFEST_ACTION_UPDATE]),
            "dependents_unblocked": len([va for item in public
                                         for va in item["dependents_unblocked"]]),
        },
    }


def _classify(candidates):
    # type: (list) -> tuple
    """``(writable, already, refused)``; an already-satisfied VA is not a refusal.

    A VA that is already reconstructed needs no promotion to stay reconstructed,
    so a broken promotion marker must not turn a re-run into a failure. Its
    blockers stay in the plan, where they are still reported.
    """
    writable = []
    already = []
    refused = []
    for candidate in candidates:
        if not candidate["needs_satisfied"]:
            already.append(candidate)
        elif candidate["blockers"]:
            refused.append(candidate)
        else:
            writable.append(candidate)
    return writable, already, refused


def _result(status, changed, idempotent, satisfied, already, refused, extra=None):
    # type: (str, bool, bool, list, list, list, object) -> dict
    result = {
        "schema": RESULT_SCHEMA,
        "status": status,
        "changed": bool(changed),
        "idempotent": bool(idempotent),
        "satisfied": satisfied,
        "already_satisfied": already,
        "refused": refused,
        "summary": {
            "requested": len(satisfied) + len(already) + len(refused),
            "satisfied": len(satisfied),
            "already_satisfied": len(already),
            "refused": len(refused),
        },
    }
    result.update(extra or {})
    return result


def _refused_row(candidate):
    # type: (dict) -> dict
    return {"va": candidate["va"], "src_package": candidate["src_package"],
            ACTION_FIELD: candidate.get(ACTION_FIELD, MANIFEST_ACTION_ABSENT),
            "blockers": candidate["blockers"]}


def _insert_sorted(entries, entry):
    # type: (list, dict) -> list
    """``entries`` with ``entry`` inserted at its address-sorted position.

    The canonical manifest keeps ``functions[]`` in address order, and a row
    appended to the end of an ordered list is a new invariant for every reader
    downstream. An entry whose own address cannot be read sorts last, so a
    malformed row can never push a real one out of reach.
    """
    va = _entry_va(entry)
    position = len(entries)
    for index, item in enumerate(entries):
        other = _entry_va(item)
        if other and other > va:
            position = index
            break
    return entries[:position] + [entry] + entries[position:]


def _written_functions(document, replacements, creations):
    # type: (dict, dict, dict) -> list
    """The new ``functions`` list: updates in place, creations sorted in."""
    entries = list(document.get("functions") or [])
    written = [replacements.get(_entry_va(item), item) if isinstance(item, dict) else item
               for item in entries]
    for va in sorted(creations):
        written = _insert_sorted(written, creations[va])
    return written


def apply(root=ROOT, vas=None, reason=None, implementer_id=None, dry_run=False,
          verify_build=False):
    # type: (Path, object, object, object, bool, bool) -> dict
    """Mark promoted VAs as satisfied dependencies in the canonical manifest.

    All or nothing *per VA*, and one write for the whole call: a VA is written
    only if every condition holds for it, and a refused VA leaves the manifest
    entry of its own callers and its own row exactly as they were. A refusal
    never blocks an admissible sibling, because that is how ``promote.apply``
    treats a refused package, and one broken promotion in a batch must not
    freeze the other ninety-nine.

    ``dry_run`` reports the decision without writing. ``verify_build`` re-runs
    ``build_gate.gate`` for the installed package of each candidate instead of
    trusting the recorded verdict, on top of the recorded verdict being checked
    either way.
    """
    root = Path(root)
    database = _database(root)
    try:
        dependencies = _Dependencies(root, database)
        candidates, document, problem = _candidates(root, vas, dependencies)
    finally:
        if database is not None:
            database.close()
    if problem is not None:
        return _result("error", False, True, [], [], [_refused_row(item) for item in candidates],
                       {"code": "manifest_unreadable", "detail": problem})
    if verify_build:
        preliminary = [candidate for candidate in candidates
                       if candidate["needs_satisfied"] and not candidate["blockers"]]
        if preliminary:
            try:
                _verify_live_builds(root, preliminary)
            except Exception as exc:
                return _result("error", False, True, [], [],
                               [_refused_row(item) for item in candidates],
                               {"code": "build_gate_unavailable", "detail": str(exc)})
    writable, already, refused = _classify(candidates)
    already_vas = sorted(item["va"] for item in already)
    refused_rows = [_refused_row(item) for item in refused]
    actions = {item["va"]: item[ACTION_FIELD] for item in writable}
    if not writable:
        # Nothing to write: a refused run writes nothing, and a run over already
        # satisfied VAs is a no-op rather than a second change_log entry.
        status = "blocked" if refused_rows else "ok"
        return _result(status, False, True, [], already_vas, refused_rows,
                       {"dry_run": bool(dry_run), "would_satisfy": [],
                        "manifest_actions": {}})
    if dry_run:
        return _result("blocked" if refused_rows else "ok", False, False, [],
                       already_vas, refused_rows,
                       {"dry_run": True, "manifest_actions": actions,
                        "would_satisfy": sorted(item["va"] for item in writable)})

    updated = dict(document)
    functions = _functions_by_va(document)
    replacements = {}
    creations = {}
    rows = []
    for candidate in writable:
        created = candidate.get("_created")
        if created is not None:
            # A creation is the same transition from a different prior state:
            # the admitted conditions are identical, so the row is the finished
            # entry the plan already described, field for field.
            prior_body = None
            prior_integration = None
            creations[candidate["va"]] = created
            action = MANIFEST_ACTION_CREATE
            field_sources = candidate.get(SOURCES_FIELD) or {}
        else:
            function = functions[candidate["va"]]
            replacements[candidate["va"]] = _transition(root, function, candidate)
            prior_body = function.get("body_status")
            prior_integration = function.get("integration_status")
            action = MANIFEST_ACTION_UPDATE
            field_sources = {}
        rows.append({
            "va": candidate["va"],
            "src_package": candidate["src_package"],
            "promotion_record": candidate["promotion_record"],
            CHANGE_ACTION_KEY: action,
            "prior_body_status": prior_body,
            "prior_integration_status": prior_integration,
            "body_status": SATISFIED_BODY_STATUS,
            "integration_status": SATISFIED_INTEGRATION_STATUS,
            "field_sources": field_sources,
        })
    updated["functions"] = _written_functions(document, replacements, creations)
    change_log = list(updated.get(CHANGE_LOG_KEY) or [])
    change_log.append(_change_log_entry([row["va"] for row in rows], reason,
                                        implementer_id, CHANGE_KIND_SATISFY, rows))
    updated[CHANGE_LOG_KEY] = change_log
    rk.write_json_atomic(root / MANIFEST_REL, updated)
    # Invalidated before the projection is rebuilt, so nothing that runs between
    # the write and the rebuild can read the index this write just made stale.
    _invalidate(root)

    warnings = []
    try:
        applied = integrate_mod.apply(root)
        projection = {"status": str(applied.get("status")), "changed": bool(applied.get("changed")),
                      "index": applied.get("index"), "bootstrap": applied.get("bootstrap")}
    except Exception as exc:
        projection = {"status": "error", "detail": "%s: %s" % (type(exc).__name__, exc)}
        warnings.append(
            "the manifest was written but the generated projection could not be "
            "rebuilt (%s); run `openspore integrate apply` to regenerate it" % exc)
    unblocked = {}
    connection = _database(root)
    try:
        after = _Dependencies(root, connection)
        for row in rows:
            unblocked[row["va"]] = after.unblocked(row["va"])
    finally:
        if connection is not None:
            connection.close()
    return _result("blocked" if refused_rows else "ok", True, False,
                   sorted(row["va"] for row in rows), already_vas, refused_rows,
                   {"dry_run": False, "projection": projection, "warnings": warnings,
                    "unblocked": unblocked, "manifest_actions": actions,
                    "created": sorted(row["va"] for row in rows
                                      if row[CHANGE_ACTION_KEY] == MANIFEST_ACTION_CREATE),
                    "knowledge_graph": {
                        "recorded": False,
                        "reason": "tools.reconstruction_knowledge exposes no public "
                                  "recorder, and inventing one here would add a "
                                  "second write path to the knowledge graph",
                    }})


def unblock_dependents(root, va):
    # type: (Path, object) -> list
    """Which real callers of ``va`` the frontier now calls ``eligible``.

    Read-only, and answered by ``frontier.frontier`` plus
    ``schedule._open_callees`` rather than by a second eligibility rule.
    """
    root = Path(root)
    canonical = normalize_va(va)
    database = _database(root)
    try:
        return _Dependencies(root, database).unblocked(canonical)
    finally:
        if database is not None:
            database.close()


def _satisfy_rows(change_log, va):
    # type: (list, str) -> tuple
    """The newest ``satisfy`` row for ``va``, and the entry that carried it."""
    for entry in reversed(change_log):
        if not isinstance(entry, dict) or entry.get("kind") != CHANGE_KIND_SATISFY:
            continue
        for row in entry.get("rows") or []:
            if isinstance(row, dict) and row.get("va") == va:
                return row, entry
    return None, None


def unsatisfy(root=ROOT, vas=None, reason=None, implementer_id=None, dry_run=False):
    # type: (Path, object, object, object, bool) -> dict
    """Roll a satisfied dependency back to the status its promotion replaced.

    A build or test failure *after* a promotion must be able to re-defer every
    caller, so the reversal is a first-class operation rather than a manual
    manifest edit. The prior statuses come from the ``change_log`` entry
    ``apply`` wrote, which is the only place they were kept; a VA with no such
    entry is refused with ``no_change_log`` rather than guessed at.

    A row this module *created* has no prior status, so the reversal deletes it
    rather than writing back two nulls -- a stub row would be a manifest entry
    claiming a target the campaign has no record of. The ``change_log`` row
    records which of the two happened in its ``manifest_action`` field, so the
    decision is readable from the manifest alone; a row written by an older
    ``apply`` has no such field and is treated as an update, which is what it
    was.
    """
    root = Path(root)
    document, problem = _read_json(root / MANIFEST_REL)
    if document is None:
        return _result("error", False, True, [], [], [],
                       {"code": "manifest_unreadable", "detail": problem, "restored": []})
    functions = _functions_by_va(document)
    triage = _triage_by_va(root)
    change_log = list(document.get(CHANGE_LOG_KEY) or [])
    wanted = []
    for value in (vas or []):
        try:
            wanted.append(normalize_va(value))
        except (TypeError, ValueError):
            continue
    restored = []
    removed = []
    already_open = []
    refused = []
    replacements = {}
    for va in wanted:
        function = functions.get(va)
        if function is None:
            refused.append({"va": va, "blockers": [
                _blocker("no_manifest_entry",
                         "%s has no functions[] entry for %s" % (MANIFEST_REL, va))]})
            continue
        row, _entry = _satisfy_rows(change_log, va)
        if row is None:
            refused.append({"va": va, "blockers": [
                _blocker("no_change_log",
                         "no satisfy change_log entry records the prior status of %s" % va)]})
            continue
        if _needs_satisfied(va, _status(function, triage.get(va) or {})):
            # Already open: nothing to roll back, and reporting it as a
            # restoration would claim a write that did not happen.
            already_open.append(va)
            continue
        restored.append(va)
        if row.get(CHANGE_ACTION_KEY) == MANIFEST_ACTION_CREATE:
            removed.append(va)
            continue
        replacement = dict(function)
        replacement["body_status"] = row.get("prior_body_status")
        replacement["integration_status"] = row.get("prior_integration_status")
        replacements[va] = replacement
    if not restored:
        return _result("blocked" if refused else "ok", False, True, [],
                       already_open, refused,
                       {"dry_run": bool(dry_run), "restored": [], "removed": []})
    if dry_run:
        return _result("blocked" if refused else "ok", False, False, [],
                       already_open, refused,
                       {"dry_run": True, "would_restore": sorted(restored),
                        "restored": [], "would_remove": sorted(removed)})
    updated = dict(document)
    written = []
    for function in (updated.get("functions") or []):
        va = _entry_va(function)
        if va in replacements:
            written.append(replacements[va])
        elif va in removed:
            continue
        else:
            written.append(function)
    updated["functions"] = written
    change_log.append(_change_log_entry(
        restored, reason, implementer_id, CHANGE_KIND_UNSATISFY,
        [{"va": va,
          "removed": va in removed,
          "restored_body_status": (None if va in removed
                                   else replacements[va].get("body_status")),
          "restored_integration_status": (None if va in removed
                                          else replacements[va].get("integration_status"))}
         for va in sorted(restored)]))
    updated[CHANGE_LOG_KEY] = change_log
    rk.write_json_atomic(root / MANIFEST_REL, updated)
    projection = {}
    warnings = []
    try:
        applied = integrate_mod.apply(root)
        projection = {"status": str(applied.get("status")),
                      "changed": bool(applied.get("changed"))}
    except Exception as exc:
        projection = {"status": "error", "detail": "%s: %s" % (type(exc).__name__, exc)}
        warnings.append(
            "the manifest was written but the generated projection could not be "
            "rebuilt (%s); run `openspore integrate apply` to regenerate it" % exc)
    _invalidate(root)
    return _result("blocked" if refused else "ok", True, False, sorted(restored),
                   already_open, refused,
                   {"dry_run": False, "restored": sorted(restored),
                    "removed": sorted(removed),
                    "projection": projection, "warnings": warnings})
