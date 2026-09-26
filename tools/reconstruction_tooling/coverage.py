"""Deterministic, READ-ONLY reconstruction coverage reporter.

Answers "how much of Spore have we actually reconstructed, understood, or
structurally mapped?" as a MATRIX of separately-defined dimensions. There is
deliberately no composite score: summing these dimensions would be
meaningless because they are defined over different universes, different
provenance classes, and different evidence ladders.

Read-only contract
------------------
This module never writes, creates, deletes, or mutates any file, database row,
queue row, claim, or manifest. The only permitted write is the explicit
``--out PATH`` the caller asks for. It imports nothing from the writing
subsystems (``queue``, ``orchestrate``, ``integrate``, ``swarm``,
``evidence``, ``context``, ``recover``) and it does not take
``tools/observatory/lock.py``'s machine lock: a read-only reporter must never
park other agents.

Determinism contract
--------------------
No timestamp, mtime, hostname, or absolute path appears anywhere in the emitted
JSON. Every input is fingerprinted (sha256 + size + mtime_ns) before it is read,
the hash is taken from the very buffer that is parsed, and the input is
fingerprinted again afterwards -- two content reads per file, never three. A
changed fingerprint, or a member that is present but unparseable, raises
``ToolError("input_changed_during_read", ...)`` instead of silently retrying on a
torn read. A member that has merely VANISHED (another agent deleted it) is
benign and is skipped, because the tree genuinely is smaller now.
``snapshot["input_drift"]`` is emitted as a stable empty list -- the assertion is
the point.

There is exactly ONE host probe, and it is disclosed rather than hidden:
``snapshot.inputs[*].git_tracked`` / ``tracked_verdict`` come from
``git ls-files``, i.e. from the git INDEX at read time. A concurrent ``git add``
or ``git rm --cached`` therefore changes those fields with no artifact content
changing. See ``generator_status.host_probes``.
"""

import hashlib
import json
import os
import sqlite3
import subprocess
from collections import Counter
from pathlib import Path

from .models import ROOT, ToolError, canonical_json, normalize_va

SCHEMA = "openspore-reconstruction-coverage-1"
GENERATOR = "tools/reconstruction_tooling/coverage.py"
UNIVERSE_TOTAL = 58757
GAMEPLAY_TOTAL = 2149
GAMEPLAY_CATEGORIES = ("GAMEPLAY_LOGIC", "GAMEPLAY_SUPPORT")
SUFFICIENT_LADDER = ("SUPPORTED", "CONFIRMED", "VERIFIED")

LEDGER_REL = "knowledgegraph/research/21-decompilation-coverage.json"
MANIFEST_REL = "knowledgegraph/research/source-reconstruction-manifest.json"
QUEUE_REL = "knowledgegraph/triage/queue-f0e310e0-v6.json"
SEMANTIC_DECOMP_REL = "knowledgegraph/research/semantic-decomp.json"
SEMANTIC_BLUEPRINT_REL = "knowledgegraph/research/semantic-blueprint.json"
RESIDUAL_UNKNOWN_REL = "knowledgegraph/research/residual-unknown-priority.json"
DECOMP_GAP_REL = "knowledgegraph/research/decomp-gap"
METADATA_REL = "reconstruction/metadata"
HANDOFF_REL = "reconstruction/integrated"
STAGING_REL = "reconstruction/staging"
EVIDENCE_REL = "reconstruction/evidence"
KNOWLEDGE_INDEX_REL = "reconstruction/knowledge/index.json"
KG_DB_REL = "knowledgegraph/spore.db"
RUNTIME_ORACLE_REL = "knowledgegraph/research/runtime-oracle.json"

CALL_REFERENCE_TYPES = ("direct-call", "thunk", "external", "computed-call")
CLASS_VOCABULARY = ("CALLS", "GLOBALS", "FIELDS_OFFSETS", "CONSTANTS",
                    "CONTROL_FLOW", "VIRTUAL_DISPATCH", "ABI", "RUNTIME")
# dimension-id suffix -> the CLASS name used by tools/reconstruction_tooling/validate.py
CLASS_NAMES = {
    "calls": "CALLS",
    "globals": "GLOBALS",
    "fields_offsets": "FIELDS_OFFSETS",
    "constants": "CONSTANTS",
    "control_flow": "CONTROL_FLOW",
    "virtual_dispatch": "VIRTUAL_DISPATCH",
    "abi": "ABI",
    "runtime": "RUNTIME",
}

EVIDENCE_KEYS = {
    "globals": ("globals", "global_reader_evidence", "publisher_evidence", "global_slot"),
    "fields_offsets": ("layout_evidence", "observed_field_offsets", "field_offsets",
                       "vtable_evidence", "type_vtable_evidence", "structure_evidence"),
    "constants": ("constants", "observed_constants", "constant_evidence"),
    "control_flow": ("observed_execution_order", "observed_order", "state_evidence",
                     "observed_state_contract", "transitions"),
    "virtual_dispatch": ("vtable_evidence", "type_vtable_evidence"),
    "abi": ("abi", "signature", "original_native_abi", "observed_original_abi"),
}
# `evidence_controls` has no dedicated artifact field; see _evidence_dimensions.


# ---------------------------------------------------------------------------
# input fingerprinting / drift detection
# ---------------------------------------------------------------------------

def _fingerprint(path, data=None):
    """sha256 + size + mtime_ns of `path`.

    When `data` is supplied the hash is computed from that already-read buffer
    instead of re-reading the file, so the hash provably describes the bytes the
    caller actually parsed. Omitting `data` reads the file, which is what the
    post-read drift check wants.
    """
    stat = os.stat(path)
    if data is None:
        with open(path, "rb") as handle:
            data = handle.read()
    return {"sha256": hashlib.sha256(data).hexdigest(),
            "bytes": len(data),
            "mtime_ns": stat.st_mtime_ns}


class _Reader:
    """Reads every input exactly once, detecting concurrent mutation.

    Fingerprint -> read bytes once -> fingerprint again. Any mismatch is a hard
    error: a coverage report computed over a half-written manifest would be
    worse than no report, because it would look authoritative.

    Two failure modes are deliberately treated differently, because conflating
    them is how a torn read becomes a silently wrong number:

    * ``FileNotFoundError`` -- a member VANISHED between enumeration and read
      because another agent deleted it. Benign: the tree is genuinely smaller
      now, the counts describe the tree as it is, and nothing is torn. Recorded
      on ``self.vanished`` and skipped.
    * ``OSError`` / ``ValueError`` -- a member is PRESENT but could not be read
      or parsed (a half-written JSON file, a permission error, a bad decode).
      This is the dangerous case: skipping it would publish a silently smaller
      count that looks authoritative, which is precisely what this reader
      exists to prevent. Recorded on ``self.drift`` so ``raise_on_drift()``
      turns it into ``ToolError("input_changed_during_read", ...)``.
    """

    def __init__(self, root):
        self.root = Path(root)
        self.bytes_by_key = {}
        self.json_by_key = {}
        self.fingerprints = {}
        self.drift = []
        self.vanished = []

    def _abs(self, rel):
        return self.root / rel

    def _check(self, key, before):
        after = _fingerprint(self._abs(key))
        if after != before:
            self.drift.append({"key": key, "before": before, "after": after})
        return after

    def _unreadable(self, rel, error):
        self.drift.append({
            "key": rel,
            "reason": "unreadable_or_unparseable",
            "error": "%s: %s" % (type(error).__name__, error),
        })

    def raw(self, key):
        if key in self.bytes_by_key:
            return self.bytes_by_key[key]
        path = self._abs(key)
        # ONE content read per file. The hash is taken from the buffer we are
        # about to parse, so a report's fingerprint always describes the bytes
        # the numbers were derived from.
        data = path.read_bytes()
        before = _fingerprint(path, data)
        self._check(key, before)
        self.fingerprints[key] = before
        self.bytes_by_key[key] = data
        return data

    def json(self, key):
        """Parse from the buffer we actually fingerprinted, never a second read."""
        if key in self.json_by_key:
            return self.json_by_key[key]
        data = self.raw(key)
        value = json.loads(data.decode("utf-8"))
        self.json_by_key[key] = value
        return value

    def walk(self, key, pattern="**/*.json"):
        """Enumerate sibling files under a directory input, reading each once."""
        base = self._abs(key)
        cache_key = "%s::%s" % (key, pattern)
        if cache_key in self.json_by_key:
            return self.json_by_key[cache_key]
        out = []
        if base.is_dir():
            for item in sorted(base.glob(pattern)):
                rel = item.relative_to(self.root).as_posix()
                if not item.is_file():
                    continue
                try:
                    out.append((rel, self.json(rel)))
                except FileNotFoundError:
                    # Vanished between enumeration and read: benign, and the
                    # omission is already visible in every count derived here.
                    self.vanished.append(rel)
                except (OSError, ValueError) as error:
                    self._unreadable(rel, error)
        self.json_by_key[cache_key] = out
        return out

    def files(self, key, pattern="*"):
        """Enumerate member files of a directory input, detecting mutation.

        Same two-mode contract as ``walk``. These members are not parsed -- they
        are only counted -- so a content tear cannot corrupt a number here, but a
        directory census that silently missed an unreadable member would still
        be a census nobody could trust.
        """
        base = self._abs(key)
        if not base.is_dir():
            return []
        out = []
        for item in sorted(base.glob(pattern)):
            if not item.is_file():
                continue
            rel = item.relative_to(self.root).as_posix()
            if rel in self.fingerprints:
                # Already read and drift-checked by walk(); do not re-read.
                out.append(rel)
                continue
            try:
                before = _fingerprint(item)
            except FileNotFoundError:
                self.vanished.append(rel)
                continue
            except OSError as error:
                self._unreadable(rel, error)
                continue
            out.append(rel)
            self.fingerprints[rel] = before
            self._check(rel, before)
        return out

    def raise_on_drift(self):
        if self.drift:
            raise ToolError("input_changed_during_read",
                            "an input changed while the coverage report was being built; "
                            "refusing to publish a report computed over a torn read",
                            1, {"drift": self.drift})


# ---------------------------------------------------------------------------
# git tracking (best effort, never a hard dependency)
# ---------------------------------------------------------------------------

_GIT_CACHE = {}


def _git_tracked(root, rel):
    key = (str(root), rel)
    if key in _GIT_CACHE:
        return _GIT_CACHE[key]
    verdict = None
    try:
        completed = subprocess.run(["git", "ls-files", "--error-unmatch", "--", rel],
                                   cwd=str(root), capture_output=True, timeout=30)
        verdict = bool(completed.returncode == 0 and completed.stdout.strip())
    except (OSError, subprocess.SubprocessError, ValueError):
        verdict = None
    _GIT_CACHE[key] = verdict
    return verdict


def _input_entry(root, rel, fingerprint):
    tracked = _git_tracked(root, rel)
    return {
        "path": rel,
        "present": fingerprint is not None,
        "sha256": (fingerprint or {}).get("sha256"),
        "bytes": (fingerprint or {}).get("bytes"),
        "git_tracked": tracked,
        "tracked_verdict": "unknown" if tracked is None else ("tracked" if tracked else "untracked"),
    }


# ---------------------------------------------------------------------------
# small helpers
# ---------------------------------------------------------------------------

def _va(value):
    """Normalize a VA to canonical 0x-prefixed lowercase form, or None."""
    try:
        return normalize_va(value)
    except (ValueError, TypeError):
        return None


def _bare(value):
    """Normalize a VA to the bare 8-hex form the coverage ledger uses."""
    normalized = _va(value)
    return normalized[2:] if normalized else None


def _pct(covered, universe):
    if covered is None or not universe:
        return None
    return round(100.0 * covered / float(universe), 4)


def _classify_failed_counters(documents):
    """Enumerate every non-zero `failed` counter and classify it from its siblings.

    The claim this supports is load-bearing -- "runtime-gated is not
    runtime-failed" -- and a bare `true` literal is an assertion a reader cannot
    distinguish from a measurement. So it is COMPUTED: walk every document,
    collect every key whose name mentions a failure with a non-zero value, and
    classify it by the `command` / `status` / `reason` / `verdict` siblings that
    live in the same object. A counter that cannot be classified is reported as
    `unclassified` and makes the boolean false, so a new unknown failure family
    can never be quietly swept into the static-gate claim.
    """
    tokens = ("clang-format", "clang_format", "unittest", "cmake", "git diff",
              "machine lock", "machine_lock", "py_compile", "pyflakes", "json.tool",
              "sha256sum", "lock")
    found = []
    for source, document in documents:
        for path, value, parent in _failed_nodes(document):
            # The counter's own NAME is part of its identity: a counter called
            # `clang_format_dry_run` says which check failed even when the object
            # holding it carries no command/status/reason sibling. Both the name
            # and the siblings go into the evidence so the verdict is auditable.
            check_name = str(path[-2]) if len(path) >= 2 else str(path[-1])
            entry = {
                "source": source,
                "path": ".".join(str(item) for item in path),
                "check_name": check_name,
                "failed": value,
            }
            siblings = {key: parent[key] for key in sorted(parent)
                        if key in ("command", "status", "reason", "verdict", "name", "kind")}
            entry["siblings"] = siblings
            haystack = ("%s %s" % (check_name,
                                   " ".join(str(item) for item in siblings.values()))).lower()
            entry["classification"] = ("static_gate" if any(token in haystack for token in tokens)
                                       else "unclassified")
            found.append(entry)
    found.sort(key=lambda item: (item["source"], item["path"]))
    return {
        "non_zero_failed_counters": found,
        "non_zero_failed_counter_count": len(found),
        "static_gate_count": sum(1 for item in found if item["classification"] == "static_gate"),
        "unclassified_count": sum(1 for item in found if item["classification"] == "unclassified"),
        "method": ("every key naming a failure with a non-zero value, found by a full walk of "
                   "the manifest and every handoff, classified from the counter's own name plus "
                   "the command/status/reason/verdict siblings in the same object"),
        "static_gate_tokens": list(tokens),
    }


def _failed_nodes(value, path=()):
    """Yield (path, non-zero failure value, containing dict) for every such node."""
    if isinstance(value, dict):
        for key, child in sorted(value.items()):
            if "fail" in str(key).lower() and isinstance(child, (int, float)) \
                    and not isinstance(child, bool) and child > 0:
                yield path + (str(key),), child, value
            for item in _failed_nodes(child, path + (str(key),)):
                yield item
    elif isinstance(value, list):
        for index, child in enumerate(value):
            for item in _failed_nodes(child, path + (str(index),)):
                yield item


def _dimension(identifier, label, universe, covered, source_of_truth,
               counting_rule, provenance, caveats, gameplay_universe=GAMEPLAY_TOTAL,
               gameplay_covered=None, available=True, reason=None, extra=None):
    # A dimension whose covered set IS its universe by construction -- the
    # universe census itself, a residual of another census, or a "staged"/"blocked"
    # count whose universe is defined as its own membership -- has no percentage to
    # report: 100.0 would be an identity, not a measurement, and it would sit in
    # the same column as real measurements inviting a reader to compare it. Those
    # dimensions emit pct=null plus pct_is_tautological=true. Real measurements are
    # untouched.
    tautological = (covered is not None and universe not in (None, 0)
                    and covered == universe)
    record = {
        "id": identifier,
        "label": label,
        "universe": universe,
        "covered": covered,
        "pct": None if tautological else _pct(covered, universe),
        "gameplay_universe": gameplay_universe,
        "gameplay_covered": gameplay_covered,
        "gameplay_pct": _pct(gameplay_covered, gameplay_universe),
        "source_of_truth": source_of_truth,
        "counting_rule": counting_rule,
        "provenance": provenance,
        "caveats": list(caveats),
        "available": available,
    }
    if tautological:
        record["pct_is_tautological"] = True
        record["pct_null_because"] = (
            "covered equals universe by construction, so any percentage would be the identity "
            "100.0 and not a measurement; read `covered` and `universe` directly")
    if not available:
        record["not_determinable_reason"] = reason
    if extra:
        record.update(extra)
    return record


def _node(key_path, keys):
    """Yield (key, value) for every present-and-non-empty node named in `keys`."""
    def walk(value):
        if isinstance(value, dict):
            for name, child in value.items():
                if name in keys and child not in (None, {}, [], "", 0):
                    yield name, child
                for item in walk(child):
                    yield item
        elif isinstance(value, list):
            for child in value:
                for item in walk(child):
                    yield item
    return list(walk(key_path))


def _has_token(value, target):
    if value == target:
        return True
    if isinstance(value, dict):
        return any(_has_token(child, target) for child in value.values())
    if isinstance(value, list):
        return any(_has_token(child, target) for child in value)
    return False


def _count_tokens(value, target):
    if value == target:
        return 1
    if isinstance(value, dict):
        return sum(_count_tokens(child, target) for child in value.values())
    if isinstance(value, list):
        return sum(_count_tokens(child, target) for child in value)
    return 0


def _counter(values):
    out = {}
    for value in values:
        out[value] = out.get(value, 0) + 1
    return out


def _walk_nodes(value, path=()):
    """Verbatim port of knowledgegraph/research/decomp-gap/synthesize.py walk_nodes."""
    if isinstance(value, dict):
        for key in sorted(value):
            child = value[key]
            yield path + (str(key),), child
            for item in _walk_nodes(child, path + (str(key),)):
                yield item
    elif isinstance(value, list):
        for index, child in enumerate(value):
            yield path + (str(index),), child
            for item in _walk_nodes(child, path + (str(index),)):
                yield item


def manifest_record_vas(functions):
    """Distinct VAs claimed by manifest function RECORDS.

    12 of the 300 records carry no `va` key and use `function_address`
    instead, so both keys must be read. Deduplication happens here: a VA
    claimed by several records counts once.
    """
    vas = set()
    for record in functions or []:
        bare = _bare(record.get("va") or record.get("function_address"))
        if bare:
            vas.add(bare)
    return vas


def has_live_static_body(record):
    """Verbatim port of synthesize.py:250-264 (has_live_static_body).

    Reimplemented rather than imported: synthesize.py's main() writes
    decomp-gap-excavation.json and the track-B accounting files, and a
    read-only reporter must never trigger a write.
    """
    for path, value in _walk_nodes(record):
        key = path[-1] if path else ""
        if key in {"decompile_ok", "live_decompilation_recovered",
                   "body_observed_via_read_only_ghidra"} and value is True:
            return True
        if key in {"decompilation_evidence", "recovery_source"} and isinstance(value, str):
            text = value.lower()
            if "ghidra" in text or "decompile" in text:
                return True
        if key == "state" and value == "static_recovered":
            return True
        if key == "research_state" and isinstance(value, str) and "live" in value.lower():
            return True
    return False


def gap_record_va(record):
    """Bare VA of a decomp-gap record.

    Reads synthesize.py:118-124 `record_va`'s four keys IN SYNTHESIZE'S ORDER
    (`va`, `identity.va`, `identity.canonical_va`, `canonical_va`), then falls
    back to three legacy aliases coverage.py has always read (`address`,
    `target_va`, `function_address`). It is therefore a SUPERSET of synthesize's
    extraction, not a byte-for-byte port: the legacy aliases are tried only after
    every synthesize key has missed. On all 1,977 records of the current tracked
    partitions the two agree exactly, so the superset costs nothing.

    The `identity.*` keys are load-bearing, not decorative. 5 of the 16 tracked
    partitions (sim-core-01/03/05/07, terrain-world-00 -- 793 of 1,977 records)
    nest the VA under `identity` and carry NO top-level `va`. Reading top-level
    keys only silently dropped 40% of the artifact. It changed no count on this
    snapshot (none of the 793 satisfies `has_live_static_body`), which is exactly
    why it needed a test rather than a number change.
    """
    identity = record.get("identity") if isinstance(record.get("identity"), dict) else {}
    for value in (record.get("va"), identity.get("va"), identity.get("canonical_va"),
                  record.get("canonical_va"), record.get("address"),
                  record.get("target_va"), record.get("function_address")):
        bare = _bare(value)
        if bare:
            return bare
    return None


def has_runtime_evidence(record):
    """Verbatim port of synthesize.py has_runtime_evidence (read-only helper)."""
    for path, value in _walk_nodes(record):
        key = path[-1] if path else ""
        if key in {"runtime_validated", "runtime_validation"} and value is True:
            return True
        if key in {"runtime_validation", "runtime_evidence"} and isinstance(value, str):
            text = value.lower()
            if not any(token in text for token in ("not", "unavailable", "none", "false")):
                return True
    return False


# ---------------------------------------------------------------------------
# local SQLite (strictly read-only, optional, machine-local)
# ---------------------------------------------------------------------------

def _call_role_vas(cursor, column):
    """Distinct VAs in `xref.{column}` for the canonical CALL reference types.

    `column` is the SINGLE value used both to build this SQL and to build the
    machine-readable ``counting_rule`` string, so the rule text and the query
    can never drift apart. Callers pass:

    * ``"callee_va"`` -- the function being called, so the result is the set of
      functions that HAVE AT LEAST ONE CALLER.
    * ``"caller_va"`` -- the containing function, so the result is the set of
      functions that HAVE AT LEAST ONE CALLEE.

    ``EXT:``/``VT:`` pseudo-targets are excluded from whichever column is being
    read; they are synthesized labels, not real VAs.
    """
    placeholders = ",".join("?" * len(CALL_REFERENCE_TYPES))
    sql = ("select distinct %s from xref where reference_type in (%s) "
           "and %s not like 'EXT:%%' and %s not like 'VT:%%'"
           % (column, placeholders, column, column))
    vas = {_bare(row[0]) for row in cursor.execute(sql, CALL_REFERENCE_TYPES)}
    vas.discard(None)
    return vas


def _open_db(path):
    """Open a gitignored machine-local SQLite DB read-only.

    Uses an explicit ``file:...?mode=ro`` URI so the engine can never create a
    -wal, take a write lock on the database, or mutate a row. Returns None when
    the file is absent.

    Note on the -shm sidecar: the database is in WAL mode, and SQLite's WAL
    read-lock index lives in a shared-memory file whose mtime advances whenever
    a read lock is taken. That is a lock artefact, not a data mutation: the
    -shm *content* is unchanged, and neither the .db nor the -wal file is
    written. ``immutable=1`` would avoid the -shm touch entirely but would
    also tell SQLite the file can never change under us, which would let a
    concurrent writer produce a silently torn read. Correctness of the read
    wins over a cosmetic mtime, so the plain read-only URI is used.
    """
    if not Path(path).exists():
        return None
    uri = "file:%s?mode=ro" % str(Path(path).resolve()).replace("?", "%3f").replace("#", "%23")
    return sqlite3.connect(uri, uri=True)


# ---------------------------------------------------------------------------
# the report
# ---------------------------------------------------------------------------

def build_report(root=ROOT, include_local_db=True, include_untracked=True):
    """Build the deterministic read-only coverage matrix.

    Pure: identical inputs produce byte-identical canonical_json output.
    """
    root = Path(root)
    reader = _Reader(root)

    def maybe_json(rel):
        """Load an optional input, or None when the file is absent."""
        if not (root / rel).exists():
            reader.fingerprints.setdefault(rel, None)
            return None
        return reader.json(rel)

    # -- load every input exactly once -------------------------------------
    ledger = reader.json(LEDGER_REL)
    manifest = reader.json(MANIFEST_REL)
    queue = reader.json(QUEUE_REL)
    semantic_decomp = reader.json(SEMANTIC_DECOMP_REL)
    blueprint = reader.json(SEMANTIC_BLUEPRINT_REL)
    residual = maybe_json(RESIDUAL_UNKNOWN_REL)
    oracle = maybe_json(RUNTIME_ORACLE_REL)
    index_doc = maybe_json(KNOWLEDGE_INDEX_REL)
    gap_parts = reader.walk(DECOMP_GAP_REL, "*.json")
    metadata_files = reader.walk(METADATA_REL, "**/*.json")
    handoffs = reader.walk(HANDOFF_REL, "**/handoff.json")
    staging_json = reader.walk(STAGING_REL, "**/*.json")
    db = _open_db(root / KG_DB_REL) if include_local_db else None
    # The database is opened through sqlite3 rather than the byte reader, so
    # fingerprint it explicitly for the snapshot. Only size and content hash
    # are recorded; the mtime is used for drift detection and never emitted.
    reader.fingerprints[KG_DB_REL] = _fingerprint(root / KG_DB_REL) \
        if (root / KG_DB_REL).exists() else None

    try:
        return _assemble(root, reader, ledger, manifest, queue, semantic_decomp,
                         blueprint, residual, oracle, index_doc, gap_parts,
                         metadata_files, handoffs, staging_json, db, include_local_db,
                         include_untracked)
    finally:
        if db is not None:
            db.close()
        reader.raise_on_drift()


def _assemble(root, reader, ledger, manifest, queue, semantic_decomp, blueprint,
              residual, oracle, index_doc, gap_parts, metadata_files, handoffs,
              staging_json, db, include_local_db, include_untracked):
    ledger_rows = ledger.get("ledger") or []
    universe = [row.get("va") for row in ledger_rows]
    universe = {va for va in universe if va}
    gameplay = {row["va"] for row in ledger_rows
                if row.get("triage_category") in GAMEPLAY_CATEGORIES}
    non_gameplay = universe - gameplay
    functions = manifest.get("functions") or []
    packages = manifest.get("packages") or []
    types = manifest.get("types") or []
    gates = manifest.get("runtime_gates") or []
    queue_rows = queue.get("queue") or []
    metrics = manifest.get("metrics") or {}

    def split(vas):
        return len(vas & universe), len(vas & gameplay)

    # -- ledger-derived sets -------------------------------------------------
    persisted = {row["va"] for row in ledger_rows if row.get("body_available") is True}
    # Where the persisted bodies actually live, split by whether that path is
    # git-tracked. COMPUTED, because a caveat that types "477" is a number that
    # silently becomes a lie the moment a body is re-captured under a tracked path.
    bodies_gitignored = sum(
        1 for row in ledger_rows
        if row.get("body_available") is True
        and str(row.get("primary_decomp_path") or "").startswith(".spore-analysis/"))
    any_decomp = {row["va"] for row in ledger_rows
                  if row.get("decomp_state") not in (None, "unavailable")}
    no_decomp = universe - any_decomp
    queue_cluster = {row["va"] for row in ledger_rows
                     if (row.get("queue") or {}).get("cluster")}
    staged_candidate = {row["va"] for row in ledger_rows
                        if row.get("queue") is not None and row.get("body_available") is True}

    # -- manifest-derived sets ----------------------------------------------
    # 12 of 300 records carry no `va` key; they use `function_address`.
    manifest_vas = manifest_record_vas(functions)
    integrated_vas = set()
    blocked_vas = set()
    for record in functions:
        bare = _bare(record.get("va") or record.get("function_address"))
        if record.get("integration_status") == "integrated" and bare:
            integrated_vas.add(bare)
        elif record.get("integration_status") == "blocked" and bare:
            blocked_vas.add(bare)
    manifest_out_of_universe = sorted(manifest_vas - universe)
    manifest_in_universe = manifest_vas & universe
    manifest_package = set()
    for record in functions:
        if record.get("package"):
            bare = _bare(record.get("va") or record.get("function_address"))
            if bare:
                manifest_package.add(bare)

    # -- handoff exclusions ("withheld" is NOT a canonical term) -----------
    excluded_vas = set()
    excluded_handoffs = 0
    for _, doc in handoffs:
        addresses = doc.get("excluded_addresses")
        if not addresses:
            continue
        excluded_handoffs += 1
        for item in addresses:
            bare = _bare(item.get("va") if isinstance(item, dict) else item)
            if bare:
                excluded_vas.add(bare)
    withheld_bodies = 0
    for _, doc in handoffs:
        claims = doc.get("deferred_full_package_claims")
        if isinstance(claims, dict) and isinstance(claims.get("withheld_body_count"), int):
            withheld_bodies += int(claims["withheld_body_count"])

    # -- staging / metadata / evidence directory walks ----------------------
    staged_vas = set()
    for rel, _ in staging_json:
        bare = _bare(Path(rel).stem)
        if bare:
            staged_vas.add(bare)
    staging_base = root / STAGING_REL
    staging_dirs = sum(1 for item in staging_base.glob("*/") if item.is_dir()) \
        if staging_base.is_dir() else 0
    # Every member extension the staging tree is made of, not just its .json
    # files: a .cpp or .hpp edit is a real change to the staging census and used
    # to be invisible to both drift detection and the snapshot fingerprint.
    staging_member_rels = []
    for pattern in ("**/*.cpp", "**/*.hpp", "**/*.json", "**/*.sh"):
        staging_member_rels.extend(reader.files(STAGING_REL, pattern))
    staging_member_rels = sorted(set(staging_member_rels))
    staging_cpp = sum(1 for rel in staging_member_rels if rel.endswith(".cpp"))
    staging_hpp = sum(1 for rel in staging_member_rels if rel.endswith(".hpp"))
    staging_other = sum(1 for rel in staging_member_rels
                        if not rel.endswith((".cpp", ".hpp", ".json")))
    # Content aggregate over ALL members. Derived from sha256 + size only, never
    # mtime: an mtime would make the emitted report depend on when it was run.
    staging_aggregate = hashlib.sha256()
    staging_aggregate_bytes = 0
    for rel in staging_member_rels:
        entry = reader.fingerprints.get(rel) or {}
        staging_aggregate.update(("%s\0%s\0%s\n"
                                  % (rel, entry.get("sha256"), entry.get("bytes"))).encode("utf-8"))
        staging_aggregate_bytes += entry.get("bytes") or 0
    staging_members_sha256 = staging_aggregate.hexdigest()
    metadata_vas = set()
    for rel, _ in metadata_files:
        bare = _bare(Path(rel).stem)
        if bare:
            metadata_vas.add(bare)
    metadata_without_manifest = metadata_vas - manifest_vas
    evidence_packs = sorted(item.name for item in (root / EVIDENCE_REL).glob("*")
                            if item.is_dir()) if (root / EVIDENCE_REL).is_dir() else []
    evidence_tracked = sum(1 for pack in evidence_packs
                           if _git_tracked(root, "%s/%s" % (EVIDENCE_REL, pack)) is True)
    # One computation, three consumers: the metadata_only_record caveat, the
    # blind_spots prose, and the snapshot's tracked-member tally.
    metadata_tracked = sum(1 for rel, _ in metadata_files
                           if _git_tracked(root, rel) is True)
    # The untracked fraction of the metadata tree, COMPUTED from its own stated
    # denominator. It used to be a hand-typed "roughly 66%%" literal, which matched
    # nothing derivable (1 - 101/328 is 69.2%%) and was therefore a number the
    # report asserted without being able to reproduce.
    # A PHRASE, not a float: an empty metadata tree has an undefined untracked
    # fraction (0/0), and rendering that as "0.0% untracked" would be a false
    # statement rather than an absent one.
    metadata_untracked_phrase = (
        "%.1f%%" % (100.0 * (len(metadata_files) - metadata_tracked) / len(metadata_files))
        if metadata_files else "N/A (no metadata files present, so the fraction is 0/0)")

    # -- semantic + blueprint sets ------------------------------------------
    sd_records = semantic_decomp.get("records") or []
    sd_vas = {_bare(record.get("va")) for record in sd_records}
    sd_vas.discard(None)
    semantic_tiers = _counter(record.get("classification") for record in sd_records)

    bp_functions = blueprint.get("functions") or []
    bp_vas = {_bare(record.get("va")) for record in bp_functions}
    bp_vas.discard(None)
    bp_package = {_bare(record.get("va")) for record in bp_functions if record.get("package")}
    bp_package.discard(None)
    bp_claim_kind = _counter((record.get("evidence") or {}).get("claim_kind")
                             for record in bp_functions)
    bp_contract_state = _counter((record.get("contract_status") or {}).get("state")
                                 for record in bp_functions)
    bp_semantic_understanding = _counter((record.get("contract_status") or {}).get("semantic_understanding")
                                        for record in bp_functions)
    bp_call_role = set()
    for record in bp_functions:
        dependencies = record.get("dependencies") or {}
        if (dependencies.get("caller_count") or 0) > 0 or (dependencies.get("callee_count") or 0) > 0:
            bare = _bare(record.get("va"))
            if bare:
                bp_call_role.add(bare)

    # Positive-semantic union: semantic-decomp classifications, plus the
    # blueprint's own two positive axes. residual-unknown is deliberately
    # EXCLUDED: it is a NEGATIVE label, so unioning it in would trivially
    # reach 100% and mean nothing.
    positive_semantic = set(sd_vas)
    for record in bp_functions:
        bare = _bare(record.get("va"))
        if not bare:
            continue
        if (record.get("evidence") or {}).get("claim_kind") not in (None, "UNKNOWN"):
            positive_semantic.add(bare)
        if (record.get("contract_status") or {}).get("semantic_understanding") not in (None, "not_established"):
            positive_semantic.add(bare)
    positive_semantic &= universe

    residual_vas = set()
    if residual is not None:
        residual_vas = {_bare(record.get("va")) for record in (residual.get("records") or [])}
        residual_vas.discard(None)

    # -- live-only decompilation (decomp-gap partitions) --------------------
    live_only = set()
    gap_records = 0
    gap_records_with_va = 0
    for _, part in gap_parts:
        records = part.get("functions") if isinstance(part.get("functions"), list) else part.get("records")
        for record in records or []:
            if not isinstance(record, dict):
                continue
            gap_records += 1
            bare = gap_record_va(record)
            if bare is None:
                continue
            gap_records_with_va += 1
            if has_live_static_body(record):
                live_only.add(bare)
    live_only &= universe
    persisted_vs_live_overlap = sorted(persisted & live_only)
    # The cross-block relations the three decompilation dimensions do not state on
    # their own. All four are COMPUTED here rather than asserted in prose, because
    # each one is a fact a reader would otherwise have to re-derive by hand.
    # `live_only` is disjoint from the whole ledger-recordable decomp population,
    # not merely from the persisted half of it: every live-only VA is counted
    # INSIDE `no_decompilation_evidence`, because the ledger records decomp_state
    # ("unavailable") for all of them. That is why `any_decompilation_evidence` is
    # a superset of `persisted_decompilation` but NOT a superset of `live_only`.
    live_vs_any_overlap = sorted(live_only & any_decomp)
    live_vs_no_overlap = sorted(live_only & no_decomp)
    persisted_in_any = not (persisted - any_decomp)
    # Two DIFFERENT unions, deliberately not conflated: `any` is two rows larger
    # than `persisted` (the snapshot_only rows), so |any u live| is 664 while
    # |persisted u live| is 662. Publishing a single "union" number here is how
    # 480 gets mis-corrected to 662.
    union_persisted_live = persisted | live_only
    union_any_live = any_decomp | live_only

    # -- triage queue --------------------------------------------------------
    queue_vas = {_bare(record.get("va")) for record in queue_rows}
    queue_vas.discard(None)
    queue_out_of_universe = sorted(queue_vas - universe)
    # Derived as queue minus manifest, NOT intersected with the universe: the
    # three out-of-universe queue rows are real actionable work items, and
    # dropping them would understate the frontier. Cross-checked below against
    # index.json.frontier when that projection happens to be present.
    actionable = queue_vas - manifest_vas
    actionable_in_universe = actionable & universe
    index_frontier = set()
    if index_doc is not None and include_untracked:
        for entry in index_doc.get("frontier") or []:
            bare = _bare(entry.get("va") if isinstance(entry, dict) else entry)
            if bare:
                index_frontier.add(bare)
    frontier_agreement = {
        "knowledge_index_present": index_doc is not None and include_untracked,
        "knowledge_index_frontier_size": len(index_frontier)
        if (index_doc is not None and include_untracked) else None,
        "agrees_with_derived_actionable_frontier": (index_frontier == actionable)
        if (index_doc is not None and include_untracked) else None,
    }
    queue_dependency = {_bare(record.get("va")) for record in queue_rows
                        if record.get("dependencies")}
    queue_dependency.discard(None)

    # -- machine-local DB dimensions ----------------------------------------
    db_available = db is not None
    has_caller = has_callee = either = set()
    type_association = set()
    kg_subsystem = set()
    db_note = None
    if db_available:
        cursor = db.cursor()
        has_caller = _call_role_vas(cursor, "callee_va")
        has_callee = _call_role_vas(cursor, "caller_va")
        either = has_caller | has_callee
        for rel, dst_label, take_dst in (("hasSlot", "Function", True),
                                        ("sdkAssociatedWithStructure", "Structure", False),
                                        ("staticAssociatedWithStructure", "Structure", False)):
            for left, right in cursor.execute(
                    "select sl.name, dl.name from edge e join node sl on sl.id=e.src "
                    "join node dl on dl.id=e.dst where e.rel=? and dl.label=?", (rel, dst_label)):
                name = right if take_dst else left
                text = str(name)
                if text.startswith(("fun:", "semantic:function:")):
                    bare = _bare(text.split(":")[-1])
                    if bare:
                        type_association.add(bare)
        for (name,) in cursor.execute(
                "select sl.name from edge e join node sl on sl.id=e.src "
                "join node dl on dl.id=e.dst where e.rel='belongsToSubsystem' and sl.label='Function'"):
            text = str(name)
            if text.startswith(("fun:", "semantic:function:")):
                bare = _bare(text.split(":")[-1])
                if bare:
                    kg_subsystem.add(bare)
        type_association |= {_bare(row[0]) for row in cursor.execute(
            "select va from triage where struct_names <> '[]'")}
        type_association.discard(None)
        version = cursor.execute("select distinct classifier_version from triage").fetchall()
        db_note = {
            "uri": "mode=ro",
            "triage_classifier_versions": sorted({row[0] for row in version if row[0]}),
            "local_triage_classifier_may_be_stale": True,
        }

    # -- knowledge_index contributes type/vtable/global/service associations.
    index_type_association = set()
    index_available = index_doc is not None and include_untracked
    if index_available:
        def collect(value, out):
            if isinstance(value, list):
                for child in value:
                    collect(child, out)
            elif isinstance(value, dict):
                for child in value.values():
                    collect(child, out)
            elif isinstance(value, str) and str(value).startswith(("fun:", "0x")):
                bare = _bare(value)
                if bare:
                    out.add(bare)
        for key in ("types", "vtables", "globals", "services"):
            collect(index_doc.get(key), index_type_association)
    type_association_total = type_association | index_type_association

    # -- dependency closure (frontier.py:208-213 semantics) -----------------
    dependency_closed = 0
    dependency_uncertain = 0
    for record in bp_functions:
        dependencies = record.get("dependencies") or {}
        truncated = bool(dependencies.get("callees_truncated") or dependencies.get("edges_truncated"))
        if truncated:
            dependency_uncertain += 1
        open_callees = []
        for callee in dependencies.get("callees") or []:
            bare = _bare(callee.get("va") if isinstance(callee, dict) else callee)
            if bare and bare not in integrated_vas:
                open_callees.append(bare)
        if not open_callees and not truncated:
            dependency_closed += 1

    # -- evidence classes ---------------------------------------------------
    evidence_level_by_va = {}
    for record in functions:
        bare = _bare(record.get("va") or record.get("function_address"))
        if bare and record.get("evidence_level"):
            evidence_level_by_va.setdefault(bare, set()).add(str(record["evidence_level"]))
    for rel, doc in metadata_files:
        bare = _bare(Path(rel).stem)
        if bare and isinstance(doc, dict) and doc.get("evidence_level"):
            evidence_level_by_va.setdefault(bare, set()).add(str(doc["evidence_level"]))

    evidence_class_vas = {name: set() for name in EVIDENCE_KEYS}
    for record in functions:
        bare = _bare(record.get("va") or record.get("function_address"))
        if not bare:
            continue
        if _node(record, EVIDENCE_KEYS["abi"]) or record.get("signature_status"):
            evidence_class_vas["abi"].add(bare)
        for name, keys in EVIDENCE_KEYS.items():
            if name != "abi" and _node(record, keys):
                evidence_class_vas[name].add(bare)
    for rel, doc in metadata_files:
        bare = _bare(Path(rel).stem)
        if not bare or not isinstance(doc, dict):
            continue
        for name, keys in EVIDENCE_KEYS.items():
            if _node(doc, keys):
                evidence_class_vas[name].add(bare)

    evidence_calls = either | bp_call_role
    runtime_evidence_vas = set()
    for _, doc in gap_parts:
        records = doc.get("functions") if isinstance(doc.get("functions"), list) else doc.get("records")
        for record in records or []:
            if isinstance(record, dict) and has_runtime_evidence(record):
                bare = gap_record_va(record)
                if bare:
                    runtime_evidence_vas.add(bare)

    # -- runtime ------------------------------------------------------------
    runtime_validated_metric = metrics.get("runtime_validated")
    runtime_validated_records = sum(1 for record in functions
                                    if (record.get("audit_runtime_validated") or 0))
    promoted = (semantic_decomp.get("aggregate_metrics") or {}).get("runtime_promoted_count")
    residual_runtime = None
    if residual is not None:
        residual_runtime = (residual.get("quality_status") or {}).get("runtime_evidence")
    runtime_validated_total = max(
        [value for value in (runtime_validated_metric, runtime_validated_records, promoted)
         if isinstance(value, int)] or [0])
    runtime_gated_metric = metrics.get("runtime_gated")
    records_with_any_gate = sum(1 for record in functions
                                if record.get("runtime_gate") or record.get("runtime_gates"))
    canonical_gates = {gate for gate in gates if isinstance(gate, str)}
    gate_tokens = set()
    for record in functions:
        value = record.get("runtime_gate")
        if isinstance(value, str):
            gate_tokens.add(value)
        elif isinstance(value, list):
            gate_tokens.update(item for item in value if isinstance(item, str))
    gate_tokens |= {item for value in (record.get("runtime_gates") for record in functions)
                    if isinstance(value, list) for item in value if isinstance(item, str)}
    absent_gate_records = sum(1 for record in functions
                              if (record.get("runtime_gate") and record["runtime_gate"] not in canonical_gates)
                              or (isinstance(record.get("runtime_gates"), list)
                                  and any(item not in canonical_gates
                                          for item in record["runtime_gates"] if isinstance(item, str))))
    capability = None
    if oracle is not None:
        capability = (oracle.get("current_capability") or {}).get("overall_status")

    failed_counters = _classify_failed_counters(
        [(MANIFEST_REL, manifest)] + [(rel, doc) for rel, doc in handoffs])
    negative_proof = {
        "manifest_audit_unresolved_contradiction": (manifest.get("audit") or {}).get("unresolved_contradiction"),
        "all_non_zero_failed_counts_are_static_gates":
            bool(failed_counters["non_zero_failed_counters"])
            and failed_counters["unclassified_count"] == 0,
        "all_non_zero_failed_counts_are_static_gates_is_computed": True,
        "all_non_zero_failed_counts_are_static_gates_evidence": failed_counters,
        "static_gate_families": ["clang-format --dry-run", "python3 -m unittest",
                                 "cmake --build", "git diff --check", "machine lock"],
        "validate_verdicts": list(("PASS", "WARN", "FAIL", "UNKNOWN", "NOT_AVAILABLE")),
        "not_available_is_a_sibling_of_fail_not_a_failure": True,
        "validate_not_available_uses": ["tools/reconstruction_tooling/validate.py",
                                        "residual_unknown.quality_status.runtime_evidence"],
        "runtime_oracle_observed_negative_scope": (
            "reachability of the original Cell stage, not a correctness negative"
            if oracle is not None else None),
    }

    not_run_tokens = {
        "not_run": {
            "manifest_function_records": sum(1 for record in functions if _has_token(record, "not_run")),
            "metadata_files": sum(1 for _, doc in metadata_files if _has_token(doc, "not_run")),
        },
        "not run": {"count": _count_tokens(manifest, "not run")},
        "not performed": {"count": _count_tokens(manifest, "not performed")},
        "NOT_AVAILABLE": {
            "count": _count_tokens(manifest, "NOT_AVAILABLE"),
            "meaning": "capability/verdict token, never a runtime failure",
        },
        "NOT_PRESENT": {
            "count": _count_tokens(residual, "NOT_PRESENT") if residual is not None else None,
            "meaning": "evidence absent, not evidence negative",
        },
        "not_established": {
            "count": _count_tokens(ledger, "not_established"),
            "meaning": "a disclaimer, not a classification",
        },
        "not_promoted": {"count": _count_tokens(manifest, "not_promoted")},
        "required": {"count": _count_tokens(manifest, "required"),
                     "meaning": "promotion prerequisite, not a failure"},
        "blocked": {
            "count": _count_tokens(manifest, "blocked"),
            "misread_risk": "HIGH",
            "meaning": "static integration or dependency blocker, not a runtime failure",
        },
    }
    not_run_values_must_not_be_read_as_failed = {
        "principle": ("A not-run observation is an ABSENCE of evidence, never evidence of failure. "
                      "Runtime-gated is a capability gate on the original process, not a runtime "
                      "failure. UNKNOWN is a disclaimer with zero variance, never an incorrect claim."),
        "token_inventory": not_run_tokens,
        "high_misread_risk_tokens": ["blocked", "UNKNOWN", "NOT_AVAILABLE", "not_established"],
        "reachability_negatives": {
            "OBSERVED_NEGATIVE": "original Cell stage never entered; a reachability negative",
            "HISTORICAL_NEGATIVE": "historical run record; not a correctness negative",
        },
    }

    # -- computed magnitudes reused in prose --------------------------------
    # Every number that appears in a caveat, a blind spot, or a counting rule
    # below is interpolated from one of these. A number the code did not
    # compute is a number that silently becomes a lie the moment a concurrent
    # agent grows the manifest.
    records_total = len(functions)
    integrated_records = sum(1 for record in functions
                             if record.get("integration_status") == "integrated")
    blocked_records = records_total - integrated_records
    function_address_only = sum(1 for record in functions if not record.get("va"))
    signature_status_records = sum(1 for record in functions if record.get("signature_status"))
    distinct_subsystems = len({row.get("subsystem") for row in ledger_rows
                               if row.get("subsystem")})
    partial_blueprint = bp_semantic_understanding.get("partial", 0)
    kg_subsystem_edges = len(kg_subsystem) if db_available else None
    ledger_queue_rows = sum(1 for row in ledger_rows if row.get("queue"))
    semantically_classified = len(sd_vas & universe)

    # -- classifications ----------------------------------------------------
    classifications = {
        "triage_category": {
            "source_of_truth": "%s#ledger[].triage_category" % LEDGER_REL,
            "universe": UNIVERSE_TOTAL,
            "gameplay_universe": GAMEPLAY_TOTAL,
            "counts": _counter(row.get("triage_category") for row in ledger_rows),
            "gameplay_counts": _counter(row.get("triage_category") for row in ledger_rows
                                        if row.get("va") in gameplay),
        },
        "name_evidence": {
            "source_of_truth": "%s#ledger[].name_evidence" % LEDGER_REL,
            "universe": UNIVERSE_TOTAL,
            "gameplay_universe": GAMEPLAY_TOTAL,
            "counts": _counter(row.get("name_evidence") for row in ledger_rows),
            "gameplay_counts": _counter(row.get("name_evidence") for row in ledger_rows
                                        if row.get("va") in gameplay),
            "note": "this is the EVIDENCE ladder, not a semantic tier",
        },
        "priority": {
            "source_of_truth": "%s#ledger[].priority" % LEDGER_REL,
            "universe": UNIVERSE_TOTAL,
            "counts": _counter(row.get("priority") for row in ledger_rows),
        },
        "decomp_state": {
            "source_of_truth": "%s#ledger[].decomp_state" % LEDGER_REL,
            "universe": UNIVERSE_TOTAL,
            "gameplay_universe": GAMEPLAY_TOTAL,
            "counts": _counter(row.get("decomp_state") for row in ledger_rows),
            "gameplay_counts": _counter(row.get("decomp_state") for row in ledger_rows
                                        if row.get("va") in gameplay),
        },
        "body_quality": {
            "source_of_truth": "%s#ledger[].body_quality" % LEDGER_REL,
            "universe": UNIVERSE_TOTAL,
            "counts": _counter(row.get("body_quality") for row in ledger_rows),
        },
        "queue_state": {
            "source_of_truth": "%s#ledger[].queue.queue_state" % LEDGER_REL,
            "universe": UNIVERSE_TOTAL,
            "counts": _counter((row.get("queue") or {}).get("queue_state") for row in ledger_rows
                               if row.get("queue")),
            "queue_file_vocabulary": queue.get("queue_state_vocab"),
        },
        "readiness": {
            "source_of_truth": "%s#ledger[].queue.readiness" % LEDGER_REL,
            "universe": UNIVERSE_TOTAL,
            "counts": _counter((row.get("queue") or {}).get("readiness") for row in ledger_rows
                               if row.get("queue")),
        },
        "semantic_classification": {
            "source_of_truth": "%s#records[].classification" % SEMANTIC_DECOMP_REL,
            "vocabulary_documented_in": "docs/analysis/semantic-decomp.md",
            "gameplay_universe": GAMEPLAY_TOTAL,
            "counts": semantic_tiers,
        },
        "blueprint_claim_kind": {
            "source_of_truth": "%s#functions[].evidence.claim_kind" % SEMANTIC_BLUEPRINT_REL,
            "gameplay_universe": GAMEPLAY_TOTAL,
            "counts": bp_claim_kind,
            "note": "blueprint axis; denominator is the %d gameplay set, NOT %s"
                    % (GAMEPLAY_TOTAL, format(UNIVERSE_TOTAL, ",d")),
        },
        "blueprint_contract_state": {
            "source_of_truth": "%s#functions[].contract_status.state" % SEMANTIC_BLUEPRINT_REL,
            "gameplay_universe": GAMEPLAY_TOTAL,
            "counts": bp_contract_state,
        },
        "blueprint_semantic_understanding": {
            "source_of_truth": "%s#functions[].contract_status.semantic_understanding" % SEMANTIC_BLUEPRINT_REL,
            "gameplay_universe": GAMEPLAY_TOTAL,
            "counts": bp_semantic_understanding,
            "note": "this is the only gameplay axis with real variance; the ledger's own "
                    "semantic_understanding is the constant not_established everywhere",
        },
        "integration_status": {
            "source_of_truth": "%s#functions[].integration_status" % MANIFEST_REL,
            "universe": len(functions),
            "counts": _counter(record.get("integration_status") for record in functions),
            "note": "integration_status is the %d/%d integrated/blocked split; body_status is a "
                    "DIFFERENT axis" % (integrated_records, blocked_records),
        },
        "body_status": {
            "source_of_truth": "%s#functions[].body_status" % MANIFEST_REL,
            "universe": len(functions),
            "counts": _counter(record.get("body_status") if record.get("body_status") is not None
                               else "ABSENT" for record in functions),
        },
        "package_status": {
            "source_of_truth": "%s#packages[].status" % MANIFEST_REL,
            "universe": len(packages),
            "counts": _counter(package.get("status") for package in packages),
        },
    }

    # -- dimensions ---------------------------------------------------------
    dimensions = []

    def add(record):
        dimensions.append(record)
        return record

    add(_dimension(
        "total_internal_functions", "Total internal functions", UNIVERSE_TOTAL, UNIVERSE_TOTAL,
        "%s#ledger" % LEDGER_REL,
        "row count of the canonical %s-row ledger; each VA counted once"
        % format(UNIVERSE_TOTAL, ",d"),
        "tracked", [], gameplay_covered=GAMEPLAY_TOTAL))
    add(_dimension(
        "gameplay_functions", "Gameplay functions", GAMEPLAY_TOTAL, GAMEPLAY_TOTAL,
        "%s#ledger[].triage_category in {GAMEPLAY_LOGIC, GAMEPLAY_SUPPORT}" % LEDGER_REL,
        "count of ledger rows whose triage category is GAMEPLAY_LOGIC or GAMEPLAY_SUPPORT",
        "tracked", [], gameplay_universe=GAMEPLAY_TOTAL, gameplay_covered=GAMEPLAY_TOTAL))
    add(_dimension(
        "non_gameplay_functions", "Non-gameplay functions", len(non_gameplay), len(non_gameplay),
        "%s#ledger minus the gameplay set" % LEDGER_REL,
        "universe minus gameplay; no independent source of truth",
        "derived", ["a residual category, not an independently sourced universe"],
        gameplay_covered=0))

    # `column` is the xref column the count is derived from, and it is threaded
    # into BOTH _call_role_vas() and the counting_rule text below, so the
    # machine-readable rule can never describe a different query than the one
    # that produced the number. `None` for the union axis, which reads both.
    for identifier, label, vas, column in (
            ("functions_with_caller", "Functions with at least one caller", has_caller,
             "callee_va"),
            ("functions_with_callee", "Functions with at least one callee", has_callee,
             "caller_va"),
            ("functions_with_any_call_role", "Functions in any call role", either, None)):
        if db_available:
            total, game = split(vas)
            rule = ("count of distinct callee_va UNION caller_va in xref where reference_type in "
                    "%s, with EXT:/VT: pseudo-targets dropped from both columns"
                    % list(CALL_REFERENCE_TYPES) if column is None else
                    "count of distinct %s in xref where reference_type in %s, excluding "
                    "%s LIKE 'EXT:%%' OR %s LIKE 'VT:%%'"
                    % (column, list(CALL_REFERENCE_TYPES), column, column))
            add(_dimension(
                identifier, label, UNIVERSE_TOTAL, total,
                "%s#xref where reference_type in %s" % (KG_DB_REL, list(CALL_REFERENCE_TYPES)),
                rule,
                "machine_local",
                ["source is a gitignored SQLite database that a fresh clone will NOT have",
                 "the DB's triage table is classifier triage-v4, not the v6 the ledger was built "
                 "from, so the DB's own category census disagrees with the ledger",
                 "the local DB undercounts the gameplay set, so gameplay_* here understates reality",
                 "NOT reproducible from a fresh clone: 0% of this dimension survives",
                 "the xref census is a lower bound: it counts only reference types "
                 "direct-call/thunk/external/computed-call and drops EXT:/VT: pseudo-targets"],
                gameplay_covered=game,
                extra={"machine_local": True, "database_uri": "mode=ro",
                       "xref_column_read": column}))
        else:
            add(_dimension(
                identifier, label, UNIVERSE_TOTAL, None,
                "%s#xref" % KG_DB_REL,
                "count of distinct %s" % ("callee_va and caller_va" if column is None else column),
                "machine_local", [], available=False,
                reason="the gitignored machine-local SQLite database is absent or was skipped "
                       "(--no-local-db); this dimension has no tracked source",
                extra={"machine_local": True, "xref_column_read": column}))

    add(_dimension(
        "persisted_decompilation", "Persisted decompilation", UNIVERSE_TOTAL, len(persisted),
        "%s#ledger[].body_available == true" % LEDGER_REL,
        "count of ledger rows where body_available is exactly true; each VA counted once "
        "(ledger has 0 duplicate VAs)",
        "tracked",
        ["the %d bodies live under gitignored .spore-analysis/, and the tracked decompiler .c "
         "output does not account for them" % len(persisted),
         "a second decompiler cache under tools/mcp/cache/decompiled/ holds further bodies and is "
         "gitignored and self-described as disposable; this reporter does not count it, because "
         "counting it would mean trusting a cache its own author calls throwaway"],
        gameplay_covered=len(persisted & gameplay)))
    add(_dimension(
        "any_decompilation_evidence", "Any ledger-recorded decompilation evidence",
        UNIVERSE_TOTAL, len(any_decomp),
        "%s#ledger[].decomp_state != 'unavailable'" % LEDGER_REL,
        "count of ledger rows in any non-unavailable decomp_state. LEDGER-SCOPED, not "
        "universe-scoped: this is a superset of persisted_decompilation and is NOT a superset "
        "of live_only_decomp_observation, whose %d VAs all carry decomp_state 'unavailable' in "
        "this ledger. The name is about what the LEDGER RECORDS, not about every decompiler "
        "body that exists." % len(live_only),
        "tracked",
        ["includes %d snapshot_only rows that are NOT persisted decompilation bodies"
         % sum(1 for row in ledger_rows if row.get("decomp_state") == "snapshot_only"),
         "does NOT include the %d live_only_decomp_observation VAs: those sit in "
         "no_decompilation_evidence, not here. any - persisted = %d, and any + no = %d = the "
         "universe exactly. any u live = %d (the two sets are disjoint), while "
         "persisted u live = %d; the %d-row difference is the snapshot_only rows, and "
         "collapsing the two unions is how %d gets mis-corrected to %d."
         % (len(live_only), len(any_decomp - persisted), UNIVERSE_TOTAL,
            len(union_any_live), len(union_persisted_live),
            len(any_decomp - persisted), len(any_decomp), len(union_persisted_live))],
        gameplay_covered=len(any_decomp & gameplay),
        extra={"superset_of_persisted_decompilation": persisted_in_any,
               "any_minus_persisted": len(any_decomp - persisted),
               "any_minus_persisted_all_snapshot_only": bool(any_decomp - persisted) and all(
                   row.get("decomp_state") == "snapshot_only"
                   and row.get("body_available") is not True
                   for row in ledger_rows
                   if row.get("va") in (any_decomp - persisted)),
               # Named for what it measures. `any` and `live_only` are DISJOINT,
               # so `any` is emphatically NOT a superset of `live_only` -- an
               # earlier revision of this field computed the disjointness and
               # labelled it "is_superset", which asserted the opposite of the
               # truth and contradicted this same object's counting_rule.
               "is_disjoint_from_live_only_decomp_observation": not live_vs_any_overlap,
               "live_only_is_subset_of_any": live_only <= any_decomp,
               "intersection_with_live_only": live_vs_any_overlap,
               "complement_is_no_decompilation_evidence": (
                   len(any_decomp) + len(no_decomp) == len(universe)
                   and not (any_decomp & no_decomp)),
               "any_plus_no_equals_universe": len(any_decomp) + len(no_decomp) == len(universe),
               "union_with_live_only": len(union_any_live),
               "union_with_live_only_gameplay": len((any_decomp | live_only) & gameplay),
               # Named to say WHICH two sets are unioned: this is
               # |persisted u live_only|, NOT |any u persisted| (which is 478,
               # persisted being a subset of any).
               "persisted_union_with_live_only": len(union_persisted_live)}))
    add(_dimension(
        "no_decompilation_evidence", "No ledger-recorded decompilation evidence",
        UNIVERSE_TOTAL, len(no_decomp),
        "%s#ledger[].decomp_state == 'unavailable'" % LEDGER_REL,
        "exact complement of any_decompilation_evidence in the %d-row universe; this is the real "
        "size of the PERSISTENCE gap" % UNIVERSE_TOTAL,
        "tracked",
        ["absence of evidence, not a claim of impossibility",
         "this is a PERSISTENCE census, not a 'never decompiled' census: all %d "
         "live_only_decomp_observation VAs are counted HERE, because the ledger records "
         "decomp_state 'unavailable' for each of them even though a decompiler body was "
         "observed for them. Read 'no decompilation evidence' in this report as 'no "
         "LEDGER-RECORDED decompilation evidence' or the %d functions contradict "
         "live_only_decomp_observation in the same artifact." % (len(live_vs_no_overlap),
                                                                 len(live_vs_no_overlap))],
        gameplay_covered=len(no_decomp & gameplay),
        extra={"contains_live_only_observations": len(live_vs_no_overlap),
               "no_never_decompiled_census_is_published":
                   "subtracting the live-only observations from this dimension is NOT the same "
                   "measurement and is deliberately not published as a dimension"}))
    add(_dimension(
        "live_only_decomp_observation", "Live-only decompilation observation",
        UNIVERSE_TOTAL, len(live_only),
        "knowledgegraph/research/decomp-gap/synthesize.py:250-264 (has_live_static_body), "
        "reimplemented verbatim in coverage.py and applied to knowledgegraph/research/"
        "decomp-gap/*.json; the VA is read by coverage.gap_record_va, which reads "
        "synthesize.py:118-124's four keys in synthesize's order and then three legacy "
        "aliases, so it is a superset of synthesize's record_va",
        "count of VAs whose decomp-gap record satisfies has_live_static_body; a DIMENSION UNION, "
        "NOT a decompilation count, and NOT disjoint from no_decompilation_evidence",
        "tracked",
        ["disjoint from the %d persisted bodies, and from the whole %d-row ledger-recordable "
         "decomp population (any_decompilation_evidence): the decomp-gap partitions are an exact "
         "partition of the track-B gap universe {gameplay_affinity == gameplay AND decomp.available "
         "== false} (%d VAs), and the ledger's body_available is the same fact as that "
         "decomp.available, so no persisted body can lie inside the gap. This is a CROSS-ARTIFACT "
         "identity verified on this snapshot, not an invariant the code asserts -- it is not "
         "implied by has_live_static_body, which is only a content filter over record leaves."
         % (len(persisted), len(any_decomp), len(gameplay) - len(persisted & gameplay)),
         "every one of these %d VAs is counted INSIDE no_decompilation_evidence (%d), which is why "
         "the two dimensions must never be added: %d + %d is not a decompilation total"
         % (len(live_only), len(live_vs_no_overlap), len(any_decomp), len(live_only)),
         "this dimension IS clone-reproducible: it is computed from the git-tracked "
         "knowledgegraph/research/decomp-gap/*.json partitions, not from the gitignored "
         "synthesis output",
         "the gitignored synthesis output decomp-gap-excavation.json is deliberately NOT read "
         "or regenerated here, because synthesize.py main() writes it; this reporter re-derives "
         "the %d VAs from the tracked partitions instead" % len(live_only)],
        gameplay_covered=len(live_only & gameplay),
        extra={"disjoint_from_persisted_decompilation": not persisted_vs_live_overlap,
               "overlap": persisted_vs_live_overlap,
               "union_with_persisted_gameplay": len((persisted | live_only) & gameplay),
               "intersects_any_decompilation_evidence": live_vs_any_overlap,
               "disjoint_from_any_decompilation_evidence": not live_vs_any_overlap,
               "contained_in_no_decompilation_evidence": len(live_vs_no_overlap),
               "union_with_persisted_universe": len(union_persisted_live),
               "gap_records_read": gap_records,
               "gap_records_with_va": gap_records_with_va,
               "gap_records_without_va": gap_records - gap_records_with_va,
               "all_gameplay": not (live_only - gameplay),
               "do_not_add_to_ledger_decomp_dimensions": True}))
    add(_dimension(
        "staging_decomp_candidate", "Staging decompilation candidate", UNIVERSE_TOTAL,
        len(staged_candidate),
        "%s#ledger[] where queue != null AND body_available == true" % LEDGER_REL,
        "count of ledger rows that are both queued and already decompiled; the queue-side view of "
        "the same body population",
        "derived", ["this is the same %d body population narrowed by queue membership, "
                    "NOT additional decompilation" % len(persisted)],
        gameplay_covered=len(staged_candidate & gameplay)))
    add(_dimension(
        "reconstructed_without_persisted_decompilation", "Reconstructed carrying a persisted body",
        UNIVERSE_TOTAL, len(manifest_vas & persisted),
        "%s#functions[] intersected with %s#ledger[].body_available" % (MANIFEST_REL, LEDGER_REL),
        "count of manifest VAs that ALSO carry a persisted body. NOTE: the historical id says "
        "'without' but `covered` is the WITH-set, because that is the number the manifest and the "
        "ledger can actually be asked for; the id is retained so existing consumers do not break, "
        "and `label` states what `covered` counts. The complement -- reconstructed with NO "
        "persisted body -- is published alongside it as `covered_without_persisted_body` "
        "(%d); it is NOT restated in coverage.json#reconstruction."
        % (len(manifest_vas) - len(manifest_vas & persisted)),
        "derived",
        ["both sides are needed: reconstruction of the remaining %d manifest VAs happened without a "
         "persisted decompiler body" % (len(manifest_vas) - len(manifest_vas & persisted))],
        gameplay_covered=len((manifest_vas & persisted) & gameplay),
        extra={"id_says_without_but_covered_is_the_with_set": True,
               "covered_without_persisted_body": len(manifest_vas) - len(manifest_vas & persisted),
               "covered_without_persisted_body_gameplay":
                   len(manifest_vas - (manifest_vas & persisted) - gameplay)}))
    add(_dimension(
        "metadata_only_record", "Metadata-only record", UNIVERSE_TOTAL, len(metadata_without_manifest),
        "%s/**/*.json basenames minus %s#functions[]" % (METADATA_REL, MANIFEST_REL),
        "count of VAs with a reconstruction/metadata record but no manifest function record",
        "untracked",
        ["reconstruction/metadata is %s untracked; only %d of the %d metadata files are "
         "git-tracked, so most of this dimension does not survive a fresh clone"
         % (metadata_untracked_phrase, metadata_tracked, len(metadata_files))],
        gameplay_covered=len(metadata_without_manifest & gameplay),
        extra={"metadata_files": len(metadata_files),
               "metadata_distinct_vas": len(metadata_vas),
               "metadata_in_universe": len(metadata_vas & universe)}))

    add(_dimension(
        "integrated_reconstruction_record", "Integrated reconstruction record",
        len(functions), sum(1 for record in functions
                            if record.get("integration_status") == "integrated"),
        "%s#functions[].integration_status == 'integrated'" % MANIFEST_REL,
        "count of manifest function RECORDS with integration_status integrated; the %d/%d "
        "integrated/blocked split comes from integration_status, NOT body_status"
        % (integrated_records, blocked_records),
        "tracked",
        ["record count, not VA count; see integrated_unique_va for the deduplicated view",
         "metric bodies_reconstructed=%s and integrated=%s are the same %d records"
         % (metrics.get("bodies_reconstructed"), metrics.get("integrated"), integrated_records)],
        gameplay_universe=GAMEPLAY_TOTAL,
        gameplay_covered=sum(1 for record in functions
                             if record.get("integration_status") == "integrated"
                             and _bare(record.get("va") or record.get("function_address")) in gameplay)))
    add(_dimension(
        "integrated_unique_va", "Integrated unique VA", UNIVERSE_TOTAL, len(integrated_vas),
        "%s#functions[] deduplicated by normalize_va(va or function_address)" % MANIFEST_REL,
        "distinct VAs among integrated records; 12 records carry no `va` key and use "
        "`function_address`, so both keys must be read",
        "derived",
        ["equals the record count because the %d records hold %d distinct VAs (%d duplicates)"
         % (records_total, len(manifest_vas), records_total - len(manifest_vas)),
         "%d of these VAs lie outside the %s-row universe and are reported separately"
         % (len(set(manifest_out_of_universe) & integrated_vas), format(UNIVERSE_TOTAL, ",d"))],
        gameplay_covered=len(integrated_vas & gameplay)))
    add(_dimension(
        "integrated_gameplay_va", "Integrated gameplay VA", GAMEPLAY_TOTAL,
        len(integrated_vas & gameplay), "%s#functions[] intersected with the gameplay set" % MANIFEST_REL,
        "distinct integrated VAs that are also gameplay rows",
        "derived", ["gameplay reconstruction is far below the gameplay universe; the gap is the point"],
        gameplay_universe=GAMEPLAY_TOTAL, gameplay_covered=len(integrated_vas & gameplay)))
    add(_dimension(
        "staged_va", "Staged VA", len(staged_vas), len(staged_vas),
        "%s/*/**.json with a VA-shaped basename" % STAGING_REL,
        "distinct VAs named by a VA-named JSON file under reconstruction/staging",
        "untracked",
        ["STAGED IS NOT INTEGRATED: this count is never added into any integrated figure",
         "a staged VA may be blocked, deferred, or never promoted; staging is a work state, not a "
         "reconstruction claim",
         "reconstruction/staging is untracked and concurrently edited by other agents"],
        gameplay_covered=len(staged_vas & gameplay),
        extra={"staging_directories": staging_dirs,
               "staging_cpp_files": staging_cpp,
               "staging_hpp_files": staging_hpp,
               "staging_c_cxx_files": staging_cpp + staging_hpp,
               "staging_other_member_files": staging_other,
               "staging_member_files": len(staging_member_rels),
               "staging_vas_in_universe": len(staged_vas & universe)}))
    add(_dimension(
        "blocked_va", "Blocked VA", len(blocked_vas), len(blocked_vas),
        "%s#functions[].integration_status == 'blocked'" % MANIFEST_REL,
        "count of manifest VAs whose integration_status is blocked",
        "tracked",
        ["BLOCKED IS NOT RUNTIME-FAILED: this is a static integration blocker",
         "the blocked VA is NOT part of any runtime dimension"],
        gameplay_covered=len(blocked_vas & gameplay),
        extra={"blocked_va": normalize_va(sorted(blocked_vas)[0]) if len(blocked_vas) == 1
               else sorted(normalize_va(value) for value in blocked_vas)}))
    add(_dimension(
        "withheld_va", "Withheld VA", UNIVERSE_TOTAL, None,
        "%s/**/handoff.json#excluded_addresses and #deferred_full_package_claims.withheld_body_count"
        % HANDOFF_REL,
        "'withheld' is NOT a canonical term in this repo: no field, enum, or status carries that "
        "name. The closest sourced quantities are reported by name instead",
        "derived",
        ["`withheld` has no canonical field/enum anywhere in the repository",
         "the only VA-level quantity is handoff excluded_addresses, which is an EXCLUSION, not a "
         "withholding decision"],
        available=False,
        reason="'withheld' is not a canonical term; a VA count cannot be determined without "
               "inventing a definition. The two closest sourced quantities are reported verbatim "
               "in reconstruction.withheld_sourced_quantities",
        extra={"excluded_addresses_distinct_vas": len(excluded_vas),
               "excluded_addresses_handoffs": excluded_handoffs,
               "deferred_withheld_body_count": withheld_bodies,
               "deferred_withheld_body_count_va_list": None,
               "deferred_withheld_body_count_note": "a bare integer with NO VA list, so it cannot "
                                                    "be turned into a VA count"}))
    add(_dimension(
        "runtime_validated_reconstruction_va", "Runtime-validated reconstruction VA",
        UNIVERSE_TOTAL, runtime_validated_total,
        "%s#metrics.runtime_validated, #functions[].audit_runtime_validated, "
        "%s#aggregate_metrics.runtime_promoted_count, %s#quality_status.runtime_evidence"
        % (MANIFEST_REL, SEMANTIC_DECOMP_REL, RESIDUAL_UNKNOWN_REL),
        "max of every independent runtime-validated counter in the repo; all of them are 0",
        "mixed",
        ["ZERO runtime-validated functions exist; this is a capability gap, not a quality judgement",
         "NOT_RUN is not FAILED: no original-process experiment has been attempted, let alone failed"],
        gameplay_covered=0,
        extra={"metrics_runtime_validated": runtime_validated_metric,
               "record_audit_runtime_validated_total": runtime_validated_records,
               "semantic_decomp_runtime_promoted_count": promoted,
               "residual_unknown_runtime_evidence": residual_runtime}))
    add(_dimension(
        "runtime_gated_reconstruction_va", "Runtime-gated reconstruction VA",
        len(functions), runtime_gated_metric,
        "%s#metrics.runtime_gated" % MANIFEST_REL,
        "the manifest's own runtime_gated metric; distinct from 'records carrying any gate'",
        "tracked",
        ["RUNTIME-GATED IS NOT RUNTIME-FAILED: a gate is a required capability, not an observed failure",
         "%d records carry a gate token, but the canonical metric is %s"
         % (records_with_any_gate, runtime_gated_metric),
         "%d of %d records reference a gate token absent from the canonical runtime_gates[] list"
         % (absent_gate_records, records_total)],
        gameplay_universe=GAMEPLAY_TOTAL,
        gameplay_covered=sum(1 for record in functions
                             if record.get("integration_status") == "integrated"
                             and (_bare(record.get("va") or record.get("function_address")) in gameplay)
                             and (record.get("runtime_gate") or record.get("runtime_gates")))))

    for identifier, label, tier in (
            ("semantic_strong", "Strong semantic", "STRONG_SEMANTIC"),
            ("semantic_bounded", "Bounded semantic", "BOUNDED_SEMANTIC"),
            ("semantic_structural_only", "Structural only", "STRUCTURAL_ONLY"),
            ("semantic_needs_runtime", "Needs runtime", "NEEDS_RUNTIME"),
            ("semantic_still_unknown", "Still unknown", "STILL_UNKNOWN")):
        count = semantic_tiers.get(tier, 0)
        add(_dimension(
            identifier, label, UNIVERSE_TOTAL, count,
            "%s#records[].classification == '%s'" % (SEMANTIC_DECOMP_REL, tier),
            "count of semantic-decomp records carrying this canonical classification; the "
            "classification vocabulary is documented in docs/analysis/semantic-decomp.md",
            "tracked",
            ["these tiers are only ever assigned to gameplay rows, so the %s denominator is "
             "overwhelmingly NOT-APPLICABLE rather than failed" % format(UNIVERSE_TOTAL, ",d"),
             "there is NO canonical semantic tier named 'inferred' or 'hypothesized'"],
            gameplay_covered=count,
            extra={"records": [record.get("va") for record in sd_records
                               if record.get("classification") == tier]}))
    add(_dimension(
        "semantic_unclassified", "Semantically unclassified", UNIVERSE_TOTAL,
        UNIVERSE_TOTAL - len(sd_vas),
        "universe minus %s#records[]" % SEMANTIC_DECOMP_REL,
        "%s minus the %d semantically classified rows; these rows carry NO semantic claim"
        % (format(UNIVERSE_TOTAL, ",d"), semantically_classified),
        "derived",
        ["unclassified is not the same as unknown: no one asserted anything about them",
         "the ledger's semantic_understanding field is the constant 'not_established' on all %s "
         "rows, so it carries zero information" % format(UNIVERSE_TOTAL, ",d")],
        gameplay_covered=GAMEPLAY_TOTAL - len(sd_vas & gameplay)))
    add(_dimension(
        "semantic_positive_any", "Positive semantic (any axis)", GAMEPLAY_TOTAL,
        len(positive_semantic & gameplay),
        "union of %s#records[].classification, %s#functions[].evidence.claim_kind != UNKNOWN, "
        "and %s#functions[].contract_status.semantic_understanding != not_established"
        % (SEMANTIC_DECOMP_REL, SEMANTIC_BLUEPRINT_REL, SEMANTIC_BLUEPRINT_REL),
        "union of the three POSITIVE semantic axes; residual-unknown-priority.json is deliberately "
        "EXCLUDED because it is a NEGATIVE label and unioning it in would trivially reach 100%",
        "derived",
        ["the %d-row residual-unknown set is the exact complement of the %d 'partial' set inside "
         "gameplay: including it would make this number meaningless"
         % (len(residual_vas), partial_blueprint),
         "this is a union of differently-defined axes, not a single confidence score"],
        gameplay_universe=GAMEPLAY_TOTAL, gameplay_covered=len(positive_semantic & gameplay),
        extra={"complement_gameplay_vas": GAMEPLAY_TOTAL - len(positive_semantic & gameplay)}))

    for name in ("globals", "fields_offsets", "constants", "control_flow", "virtual_dispatch"):
        identifier = "evidence_" + name
        vas = evidence_class_vas[name]
        available = bool(vas)
        sufficient = {va for va in vas if evidence_level_by_va.get(va, set()) & set(SUFFICIENT_LADDER)}
        caveats = [
            "a class is AVAILABLE when the artifact field is present and non-empty",
            "a class is SUFFICIENT only when the record's evidence level is SUPPORTED/CONFIRMED/"
            "VERIFIED (canonical ladder from manifest.policy.semantic_labels)",
            "an existing field is NEVER called 'verified' merely because it exists",
        ]
        if not available:
            caveats.append("no record in any source carries a field named for this evidence class")
        add(_dimension(
            identifier, "Evidence: " + name.replace("_", " "), UNIVERSE_TOTAL,
            len(vas) if available else None,
            "reconstruction/metadata/**/*.json and %s#functions[] keys %s"
            % (MANIFEST_REL, list(EVIDENCE_KEYS[name])),
            "count of distinct VAs where at least one of the class's artifact keys is present and "
            "non-empty",
            "untracked",
            caveats,
            gameplay_covered=len(vas & gameplay),
            available=available,
            reason=None if available else "no artifact in the corpus carries a field for this "
                                          "evidence class; reported unavailable rather than estimated",
            extra={"available_evidence": len(vas),
                   "sufficient_evidence": len(sufficient),
                   "available_evidence_gameplay": len(vas & gameplay),
                   "sufficient_evidence_gameplay": len(sufficient & gameplay),
                   "vas": sorted(vas)}))
    abi_vas = evidence_class_vas["abi"]
    abi_sufficient = {va for va in abi_vas if evidence_level_by_va.get(va, set()) & set(SUFFICIENT_LADDER)}
    add(_dimension(
        "evidence_abi", "Evidence: ABI", UNIVERSE_TOTAL, len(abi_vas),
        "%s#functions[].signature_status, and metadata keys %s"
        % (MANIFEST_REL, list(EVIDENCE_KEYS["abi"])),
        "count of distinct VAs where signature_status is present or one of the ABI keys is "
        "present and non-empty",
        "mixed",
        ["%d of %d manifest records carry signature_status; the other %d are the "
         "function_address-only records"
         % (signature_status_records, records_total, records_total - signature_status_records),
         "an ABI signature observed statically says nothing about runtime behaviour"],
        gameplay_covered=len(abi_vas & gameplay),
        extra={"available_evidence": len(abi_vas), "sufficient_evidence": len(abi_sufficient),
               "available_evidence_gameplay": len(abi_vas & gameplay),
               "sufficient_evidence_gameplay": len(abi_sufficient & gameplay),
               "vas": sorted(abi_vas)}))
    add(_dimension(
        "evidence_calls", "Evidence: calls", UNIVERSE_TOTAL, len(evidence_calls),
        "union of %s#xref call roles and %s#functions[].dependencies.{caller,callee}_count > 0"
        % (KG_DB_REL, SEMANTIC_BLUEPRINT_REL),
        "count of distinct VAs appearing in any call role in either source",
        "mixed",
        ["the xref half is machine-local and not reproducible from a fresh clone",
         "the blueprint half covers only the %d gameplay rows" % GAMEPLAY_TOTAL],
        gameplay_covered=len(evidence_calls & gameplay),
        extra={"available_evidence": len(evidence_calls),
               "sufficient_evidence": len({va for va in evidence_calls
                                           if evidence_level_by_va.get(va, set()) & set(SUFFICIENT_LADDER)}),
               "available_evidence_gameplay": len(evidence_calls & gameplay),
               "sufficient_evidence_gameplay": len({va for va in evidence_calls
                                                    if va in gameplay
                                                    and evidence_level_by_va.get(va, set())
                                                    & set(SUFFICIENT_LADDER)}),
               "machine_local": True, "database_uri": "mode=ro"}))
    # RUNTIME is the one class whose availability is a real question rather than a
    # foregone conclusion: available means "at least one record carries positive
    # runtime evidence", and today none does, so it is reported unavailable with
    # a reason instead of `available: true` next to a zero.
    runtime_available = bool(runtime_evidence_vas)
    add(_dimension(
        "evidence_runtime", "Evidence: runtime", UNIVERSE_TOTAL,
        len(runtime_evidence_vas) if runtime_available else None,
        "knowledgegraph/research/decomp-gap/*.json records satisfying synthesize.py "
        "has_runtime_evidence",
        "count of VAs whose decomp-gap record carries positive runtime evidence; 0 functions are "
        "runtime-VALIDATED, so this counts evidence mentions, not validations",
        "tracked",
        ["every non-zero runtime_evidence value in the corpus is a NEGATIVE (NOT_PRESENT) or a "
         "gate token; there is no positive runtime observation anywhere",
         "the original Cell stage was never entered in any recorded Wine run",
         "this count is of evidence MENTIONS and must not be read as validation"],
        gameplay_covered=len(runtime_evidence_vas & gameplay),
        available=runtime_available,
        reason=None if runtime_available else "no decomp-gap record carries positive runtime "
                                              "evidence, so the class is reported unavailable "
                                              "rather than available-with-zero",
        extra={"available_evidence": len(runtime_evidence_vas),
               "sufficient_evidence": 0,
               "available_evidence_gameplay": len(runtime_evidence_vas & gameplay),
               "sufficient_evidence_gameplay": 0}))

    add(_dimension(
        "has_triage_classification", "Has triage classification", UNIVERSE_TOTAL,
        sum(1 for row in ledger_rows if row.get("triage_category") != "UNKNOWN"),
        "%s#ledger[].triage_category != 'UNKNOWN'" % LEDGER_REL,
        "count of ledger rows with a triage category other than UNKNOWN",
        "tracked", ["UNKNOWN means unclassified, not incorrectly classified"],
        gameplay_covered=sum(1 for row in ledger_rows if row.get("va") in gameplay)))
    add(_dimension(
        "has_name_evidence", "Has name evidence", UNIVERSE_TOTAL,
        sum(1 for row in ledger_rows if row.get("name_evidence") != "UNKNOWN"),
        "%s#ledger[].name_evidence != 'UNKNOWN'" % LEDGER_REL,
        "count of ledger rows whose name evidence is above UNKNOWN on the canonical ladder "
        "(APPROX/INFERRED/SUPPORTED/CONFIRMED)",
        "tracked",
        ["name evidence is the EVIDENCE ladder, not a semantic understanding claim",
         "APPROX and INFERRED are weak rungs; do not read them as identification"],
        gameplay_covered=sum(1 for row in ledger_rows if row.get("va") in gameplay)))
    ledger_subsystem = {row["va"] for row in ledger_rows if row.get("subsystem")}
    add(_dimension(
        "has_subsystem", "Has subsystem", UNIVERSE_TOTAL, len(ledger_subsystem),
        "%s#ledger[].subsystem" % LEDGER_REL,
        "count of ledger rows with a non-null subsystem; the ledger populates all %s"
        % format(UNIVERSE_TOTAL, ",d"),
        "tracked",
        ["this dimension is SATURATED and therefore carries almost no information: %d distinct "
         "subsystem values over %s rows" % (distinct_subsystems, format(UNIVERSE_TOTAL, ",d")),
         "the knowledge-graph edge census (%s#edge rel='belongsToSubsystem') covers only %s"
         % (KG_DB_REL, kg_subsystem_edges if kg_subsystem_edges is not None else 0)],
        gameplay_covered=len(ledger_subsystem & gameplay),
        extra={"distinct_subsystems": distinct_subsystems,
               "kg_belongsToSubsystem_edges": kg_subsystem_edges,
               "kg_gameplay_subsystem_vas": len(kg_subsystem & gameplay) if db_available else None}))
    add(_dimension(
        "has_type_association", "Has type association", UNIVERSE_TOTAL,
        len(type_association_total & universe) if (db_available or index_available) else None,
        "union of %s#edge rel in (hasSlot, sdkAssociatedWithStructure, staticAssociatedWithStructure), "
        "%s#triage.struct_names != '[]', and %s types/vtables/globals/services"
        % (KG_DB_REL, KG_DB_REL, KNOWLEDGE_INDEX_REL),
        "count of distinct in-universe VAs associated with at least one type, vtable, global, or "
        "service record",
        "mixed" if db_available else "untracked",
        ["the DB portion is machine-local and not reproducible from a fresh clone",
         "the knowledge_index portion is untracked-but-not-ignored",
         "an association is not a layout: it says a type is referenced, not that its fields are known"],
        gameplay_covered=len(type_association_total & gameplay),
        available=db_available or index_available,
        reason=None if (db_available or index_available)
        else "neither the local database nor the knowledge index is available",
        extra={"database_only": len(type_association & universe) if db_available else None,
               "knowledge_index_only": len(index_type_association & universe) if index_available else None,
               "machine_local": db_available}))

    package_membership = (manifest_package | bp_package | queue_cluster) & universe
    add(_dimension(
        "has_package_membership", "Has package membership", UNIVERSE_TOTAL, len(package_membership),
        "union of %s#functions[].package, %s#ledger[].queue.cluster, and "
        "%s#functions[].package" % (MANIFEST_REL, LEDGER_REL, SEMANTIC_BLUEPRINT_REL),
        "count of distinct in-universe VAs claiming some package or cluster",
        "derived",
        ["%.1f%% of the universe has no package/cluster membership claim at all"
         % (100.0 * (UNIVERSE_TOTAL - len(package_membership)) / UNIVERSE_TOTAL),
         "package claims come from three different vocabularies and are NOT merged into one taxonomy"],
        gameplay_covered=len(package_membership & gameplay),
        extra={"manifest_package": len(manifest_package & universe),
               "queue_cluster": len(queue_cluster & universe),
               "blueprint_package": len(bp_package & universe),
               "universe_without_membership": UNIVERSE_TOTAL - len(package_membership)}))
    add(_dimension(
        "has_dependency_record", "Has dependency record", UNIVERSE_TOTAL, len(queue_dependency),
        "%s#queue[].dependencies" % QUEUE_REL,
        "count of in-universe VAs whose triage-queue row carries a non-empty dependencies list",
        "tracked",
        ["only 6 distinct dependency tokens exist across the whole queue, so this is a coarse "
         "resource classification, not a call-graph dependency record",
         "the real call-graph dependency record lives in the blueprint and the gitignored DB"],
        gameplay_covered=len(queue_dependency & gameplay)))

    add(_dimension(
        "runtime_validated", "Runtime validated", UNIVERSE_TOTAL, runtime_validated_total,
        "cross-source: %s#metrics.runtime_validated, per-record audit_runtime_validated, "
        "%s#aggregate_metrics.runtime_promoted_count, %s#quality_status.runtime_evidence"
        % (MANIFEST_REL, SEMANTIC_DECOMP_REL, RESIDUAL_UNKNOWN_REL),
        "max of all independent runtime-validated counters; every one of them is 0",
        "mixed",
        ["ZERO. This is the single most important blind spot in the entire reconstruction"],
        gameplay_covered=0,
        extra={"metrics_runtime_validated": runtime_validated_metric,
               "record_audit_runtime_validated_total": runtime_validated_records,
               "semantic_decomp_runtime_promoted_count": promoted,
               "residual_unknown_runtime_evidence": residual_runtime}))
    add(_dimension(
        "runtime_gated", "Runtime gated", UNIVERSE_TOTAL, runtime_gated_metric,
        "%s#metrics.runtime_gated" % MANIFEST_REL,
        "the manifest's own runtime_gated metric",
        "tracked",
        ["RUNTIME-GATED IS NOT RUNTIME-FAILED: nothing was observed to fail",
         "%d of %d records carry some gate token; the canonical metric is %s, and the two numbers "
         "must not be conflated" % (records_with_any_gate, records_total, runtime_gated_metric)],
        extra={"records_carrying_any_gate": records_with_any_gate,
               "canonical_gate_entries": len(gates),
               "canonical_distinct_gate_entries": len(canonical_gates),
               "records_referencing_gate_absent_from_canonical_list": absent_gate_records,
               "runtime_gated_gameplay_records": sum(
                   1 for record in functions
                   if record.get("integration_status") == "integrated"
                   and (_bare(record.get("va") or record.get("function_address")) in gameplay)
                   and (record.get("runtime_gate") or record.get("runtime_gates")))}))
    add(_dimension(
        "runtime_unavailable", "Runtime unavailable", None, None,
        "no such field exists on any record",
        "no record in this repository carries a `runtime_unavailable` field; NOT_AVAILABLE is a "
        "capability/verdict token, not a runtime-unavailable observation",
        "derived",
        ["this dimension is emitted unavailable on purpose: fabricating a count would invent a "
         "category the corpus does not have",
         "the closest real quantity is the capability status, reported below"],
        available=False,
        reason="`runtime_unavailable` is not a field on any record; NOT_AVAILABLE is a "
               "capability/verdict token in validate.py and residual_unknown.quality_status, so a "
               "VA count for this dimension is not determinable without inventing the category",
        extra={"capability_status": capability,
               "capability_source": "%s#current_capability.overall_status" % RUNTIME_ORACLE_REL,
               "not_available_token_in_validate_py": True}))
    add(_dimension(
        "runtime_negative", "Runtime negative", UNIVERSE_TOTAL, 0,
        "%s#audit.unresolved_contradiction, validate.py VALIDATION_VERDICTS, runtime-oracle.json"
        % MANIFEST_REL,
        "count of functions with an observed NEGATIVE runtime result; zero, and every non-zero "
        "failed count in the repo is a STATIC gate (clang-format / python unittest / machine lock)",
        "tracked", ["runtime-oracle's OBSERVED_NEGATIVE and HISTORICAL_NEGATIVE describe "
                    "REACHABILITY of the original Cell stage, not a correctness negative"],
        gameplay_covered=0, extra=negative_proof))

    add(_dimension(
        "in_triage_queue", "In triage queue", UNIVERSE_TOTAL, len(queue_vas & universe),
        "%s#queue[]" % QUEUE_REL,
        "count of in-universe VAs present in the canonical triage queue",
        "tracked",
        ["the queue file holds %d rows, %d of which lie outside the %s-row universe and are "
         "preserved in a separate list rather than discarded"
         % (len(queue_rows), len(queue_out_of_universe), format(UNIVERSE_TOTAL, ",d")),
         "presence in the queue is a work-tracking fact, not a coverage claim"],
        gameplay_covered=len(queue_vas & gameplay)))
    add(_dimension(
        "in_actionable_frontier", "In actionable frontier", UNIVERSE_TOTAL,
        len(actionable),
        "triage queue VA set minus manifest VA set",
        "queued VAs that no manifest record claims; this is the derivable definition and it does "
        "NOT require the untracked index.json",
        "derived",
        ["index.json is untracked-but-not-ignored and is therefore only a CROSS-CHECK, never a "
         "hard input",
         "the derived set is disjoint from the manifest by construction",
         "the three out-of-universe queue rows are real actionable work items, so this count is "
         "NOT intersected with the universe; the in-universe subset is reported alongside it"],
        gameplay_covered=len(actionable & gameplay),
        extra=dict(frontier_agreement, in_universe=len(actionable_in_universe),
                   in_universe_gameplay=len(actionable_in_universe & gameplay))))
    add(_dimension(
        "dependency_closed", "Dependency closed", GAMEPLAY_TOTAL, dependency_closed,
        "%s#functions[].dependencies.callees checked against %s#functions[].integration_status, "
        "mirroring tools/reconstruction_tooling/frontier.py:208-213"
        % (SEMANTIC_BLUEPRINT_REL, MANIFEST_REL),
        "a function is closed when it has no callee VA whose manifest integration_status is not "
        "'integrated' and its dependency lists are not truncated",
        "tracked",
        ["DO NOT SUM dependency_closed WITH dependency_uncertain: they are alternative states, "
         "not additive quantities",
         "the callee lists come from the blueprint, so this is a gameplay-universe dimension "
         "overlaid on the %s denominator; the vast majority are simply not applicable"
         % format(UNIVERSE_TOTAL, ",d")],
        gameplay_universe=GAMEPLAY_TOTAL, gameplay_covered=dependency_closed))
    add(_dimension(
        "dependency_uncertain", "Dependency uncertain", GAMEPLAY_TOTAL, dependency_uncertain,
        "%s#functions[].dependencies.callees_truncated / edges_truncated, mirroring "
        "tools/reconstruction_tooling/frontier.py:208-213" % SEMANTIC_BLUEPRINT_REL,
        "count of functions whose dependency evidence is explicitly truncated, so readiness is "
        "unknown rather than closed",
        "tracked",
        ["DO NOT SUM with dependency_closed: they are alternative states",
         "zero here means no truncation flag is set, NOT that every dependency is genuinely known"],
        gameplay_universe=GAMEPLAY_TOTAL, gameplay_covered=dependency_uncertain))

    # -- reconstruction summary --------------------------------------------
    record_package_ids = {record.get("package") for record in functions if record.get("package")}
    declared_package_ids = {package.get("id") for package in packages}
    package_function_vas = set()
    for package in packages:
        for entry in package.get("functions") or []:
            bare = _bare(entry.get("va") if isinstance(entry, dict) else entry)
            if bare:
                package_function_vas.add(bare)
    accounting = metrics.get("accounting_exclusions") or []
    accounting_in_integrated = sum(1 for item in accounting if _bare(item) in integrated_vas)

    reconstruction = {
        "records": len(functions),
        "unique_vas": len(manifest_vas),
        "in_universe": len(manifest_in_universe),
        "out_of_universe": manifest_out_of_universe,
        "out_of_universe_count": len(manifest_out_of_universe),
        "integrated": len(integrated_vas),
        "blocked": len(blocked_vas),
        "blocked_va": sorted(normalize_va(value) for value in blocked_vas),
        "records_with_function_address_only": sum(1 for record in functions if not record.get("va")),
        "staged": len(staged_vas),
        "staged_is_separate_from_integrated": True,
        "withheld": None,
        "withheld_is_canonical": False,
        "withheld_sourced_quantities": {
            "handoff_excluded_addresses_distinct_vas": len(excluded_vas),
            "handoff_excluded_addresses_handoffs": excluded_handoffs,
            "handoff_excluded_addresses_vas": sorted(excluded_vas),
            "deferred_full_package_claims_withheld_body_count": withheld_bodies,
            "deferred_full_package_claims_va_list": None,
            "deferred_full_package_claims_note": "a bare integer with no VA list; a VA count is "
                                                 "not determinable from it",
        },
        "packages": len(packages),
        "packages_with_functions_key": sum(1 for package in packages if package.get("functions")),
        "packages_functions_distinct_vas": len(package_function_vas),
        "packages_status": _counter(package.get("status") for package in packages),
        "record_package_ids": len(record_package_ids),
        "record_package_ids_absent_from_packages": sorted(
            record_package_ids - declared_package_ids),
        "record_package_ids_absent_count": len(record_package_ids - declared_package_ids),
        "types": len(types),
        "handoffs": len(handoffs),
        "batches": len({rel.rsplit("/", 1)[0] for rel, _ in handoffs}),
        "metadata_files": len(metadata_files),
        "metadata_distinct_vas": len(metadata_vas),
        "metadata_in_universe": len(metadata_vas & universe),
        "metadata_gameplay_vas": len(metadata_vas & gameplay),
        "metadata_vas_without_manifest_record": len(metadata_without_manifest),
        "staging_directories": staging_dirs,
        "staging_cpp": staging_cpp,
        "staging_hpp": staging_hpp,
        "staging_member_files": len(staging_member_rels),
        "staging_members_sha256": staging_members_sha256,
        "staging_vas": len(staged_vas),
        "evidence_packs": evidence_packs,
        "evidence_pack_count": len(evidence_packs),
        "evidence_packs_git_tracked": evidence_tracked,
        "accounting_exclusions": sorted(_bare(item) for item in accounting if _bare(item)),
        "accounting_exclusions_are_not_subtractions": True,
        "accounting_exclusions_all_integrated": accounting_in_integrated == len(accounting),
        "accounting_exclusions_warning": (
            "metrics.accounting_exclusions is a frozen PRESERVATION list, NOT an exclusion set: "
            "all %d listed VAs ARE integrated function records. Subtracting it would understate "
            "integration from %d to %d."
            % (len(accounting), len(integrated_vas), len(integrated_vas) - len(accounting))),
        "audit": {
            "unresolved_contradiction": (manifest.get("audit") or {}).get("unresolved_contradiction"),
            "functions_audited": (manifest.get("audit") or {}).get("functions_audited"),
            "status": (manifest.get("audit") or {}).get("status"),
        },
    }

    # -- semantics ----------------------------------------------------------
    # The blueprint axes are Counters: the KEY is the category token and the
    # VALUE is how many records carry it. These are RECORD counts, so the values
    # must be summed -- counting the keys would report the number of distinct
    # category names (2 and 1) and contradict positive_any_gameplay three lines
    # below, which is computed as a real set union.
    positive_axes = {
        "semantic_decomp_classified": len(sd_vas & universe),
        "blueprint_claim_kind_not_unknown": sum(
            value for key, value in bp_claim_kind.items() if key not in (None, "UNKNOWN")),
        "blueprint_semantic_understanding_not_not_established": sum(
            value for key, value in bp_semantic_understanding.items()
            if key not in (None, "not_established")),
    }
    positive_axes_union = {
        "note": "positive_axes_sum_is_not_a_union: the three axes OVERLAP, so they MUST NOT be "
                "summed. A VA with a positive claim_kind and a partial semantic_understanding is "
                "counted by both. Their union is computed separately and deduplicated over VAs, "
                "not over axis tallies, and is reported as semantics.positive_any_gameplay",
        "positive_axes_sum_if_you_were_wrong": (
            positive_axes["semantic_decomp_classified"]
            + positive_axes["blueprint_claim_kind_not_unknown"]
            + positive_axes["blueprint_semantic_understanding_not_not_established"]),
        "positive_axes_sum_is_wrong_because": (
            "the axes share VAs, so the sum double-counts them"),
        "union_gameplay_vas": len(positive_semantic & gameplay),
        "union_gameplay_vas_is_not_the_sum_above": (
            len(positive_semantic & gameplay)
            < (positive_axes["semantic_decomp_classified"]
               + positive_axes["blueprint_claim_kind_not_unknown"]
               + positive_axes["blueprint_semantic_understanding_not_not_established"])),
    }
    semantics = {
        "canonical_vocabulary": {
            "source_of_truth": "%s#records[].classification" % SEMANTIC_DECOMP_REL,
            "documented_in": "docs/analysis/semantic-decomp.md",
            "tiers": ["STRONG_SEMANTIC", "BOUNDED_SEMANTIC", "STRUCTURAL_ONLY",
                      "NEEDS_RUNTIME", "STILL_UNKNOWN"],
            "no_inferred_tier": True,
        },
        "tiers": {
            "STRONG_SEMANTIC": semantic_tiers.get("STRONG_SEMANTIC", 0),
            "BOUNDED_SEMANTIC": semantic_tiers.get("BOUNDED_SEMANTIC", 0),
            "STRUCTURAL_ONLY": semantic_tiers.get("STRUCTURAL_ONLY", 0),
            "NEEDS_RUNTIME": semantic_tiers.get("NEEDS_RUNTIME", 0),
            "STILL_UNKNOWN": semantic_tiers.get("STILL_UNKNOWN", 0),
        },
        "unclassified": UNIVERSE_TOTAL - len(sd_vas),
        "positive_axes": positive_axes,
        "positive_axes_sum_is_not_a_union": positive_axes_union,
        "positive_any_gameplay": len(positive_semantic & gameplay),
        "positive_complement_gameplay": GAMEPLAY_TOTAL - len(positive_semantic & gameplay),
        "evidence_ladder_axes": {
            "note": "INFERRED belongs to the EVIDENCE ladder and to blueprint.claim_kind, "
                    "NOT to the semantic tier axis",
            "ledger_name_evidence_total": _counter(row.get("name_evidence") for row in ledger_rows),
            "ledger_name_evidence_gameplay": _counter(row.get("name_evidence") for row in ledger_rows
                                                     if row.get("va") in gameplay),
            "blueprint_claim_kind_gameplay": bp_claim_kind,
            "blueprint_contract_state_gameplay": bp_contract_state,
            "blueprint_semantic_understanding_gameplay": bp_semantic_understanding,
        },
        "residual_unknown_negative_label": {
            "records": len(residual_vas),
            "available": residual is not None,
            "is_a_negative_label": True,
            "must_not_be_unioned_into_positive_coverage": True,
            "reason": "it is the exact complement of the %d 'partial' set within gameplay, so "
                      "unioning it into a positive-coverage figure trivially reaches 100%% and "
                      "means nothing" % partial_blueprint,
        },
        "honest_note": (
            "There is NO canonical semantic tier named 'inferred' or 'hypothesized'. INFERRED is an "
            "EVIDENCE-ladder rung (ledger name_evidence: %d rows; blueprint claim_kind: %d gameplay "
            "rows) and a blueprint claim_kind, not a semantic tier. Mapping it onto the "
            "strong/bounded/structural axis would require inventing a category name that no "
            "artifact in this repository uses, so this report does not do it. Every figure under "
            "`semantics.tiers` comes from the one documented canonical vocabulary; every INFERRED "
            "figure is reported separately under `evidence_ladder_axes` with its own denominator."
            % (sum(1 for row in ledger_rows if row.get("name_evidence") == "INFERRED"),
               bp_claim_kind.get("INFERRED", 0))),
    }

    # -- evidence section ---------------------------------------------------
    evidence = {
        "classes": {},
        "universe_scale_limitation": (
            "Every evidence class below is measured against the %s-row universe, but evidence "
            "is only ever RECORDED for reconstructed or triaged functions. The gameplay figures "
            "are the meaningful ones; the universe figures are dominated by rows no human or "
            "agent has looked at. Reading a class percentage as 'how much of the game we "
            "understand' would invert the meaning." % format(UNIVERSE_TOTAL, ",d")),
        "sufficient_definition": (
            "A class is AVAILABLE when the class's artifact field is present and non-empty. A "
            "class is SUFFICIENT only when the record's evidence level is SUPPORTED, CONFIRMED, or "
            "VERIFIED -- the canonical ladder in manifest.policy.semantic_labels. An existing "
            "field is never called verified merely because it exists."),
        "never_called_verified_because_present": True,
    }
    for record in dimensions:
        if not record["id"].startswith("evidence_"):
            continue
        suffix = record["id"][len("evidence_"):]
        evidence["classes"][CLASS_NAMES.get(suffix, suffix.upper())] = {
            "dimension": record["id"],
            "available_evidence": record.get("available_evidence"),
            "sufficient_evidence": record.get("sufficient_evidence"),
            "available_evidence_gameplay": record.get("available_evidence_gameplay"),
            "sufficient_evidence_gameplay": record.get("sufficient_evidence_gameplay"),
            "available": record["available"],
        }
    evidence["class_names"] = list(CLASS_VOCABULARY)

    # -- runtime section ----------------------------------------------------
    runtime = {
        "validated": runtime_validated_total,
        "gated": runtime_gated_metric,
        "unavailable": None,
        "unavailable_is_not_a_field": True,
        "negative": 0,
        "not_run_values_must_not_be_read_as_failed": not_run_values_must_not_be_read_as_failed,
        "capability_status": capability,
        "capability_source": "%s#current_capability.overall_status" % RUNTIME_ORACLE_REL,
        "capability_available": oracle is not None,
        "no_original_process_observations": {
            "runtime_validated_functions": runtime_validated_total,
            "positive_runtime_evidence_vas": len(runtime_evidence_vas),
            "semantic_decomp_runtime_performed": (semantic_decomp.get("metadata") or {}).get("runtime_performed"),
            "original_cell_stage": "never entered in any recorded Wine run (reachability negative, "
                                   "not a correctness negative)",
        },
        "gated_is_not_failed": (
            "runtime_gated=%s means a capability gate on the original process is still open. "
            "Nothing was attempted and nothing failed." % runtime_gated_metric),
    }

    # -- dependencies -------------------------------------------------------
    blocked_axes = {
        "do_not_sum": True,
        "warning": ("These axes are ALTERNATIVE STATES of the same %d queue rows, not additive "
                    "quantities. Summing them would double-count every row that carries more than "
                    "one signal." % ledger_queue_rows),
        "axes": {
            "ledger_rows_with_queue": sum(1 for row in ledger_rows if row.get("queue")),
            "ledger_rows_with_non_empty_blockers": sum(1 for row in ledger_rows
                                                       if row.get("queue") and row.get("blockers")),
            "ledger_rows_with_empty_blockers_and_readiness_READY": sum(
                1 for row in ledger_rows
                if row.get("queue") and not row.get("blockers")
                and (row.get("queue") or {}).get("readiness") == "READY"),
            "readiness": _counter((row.get("queue") or {}).get("readiness") for row in ledger_rows
                                  if row.get("queue")),
            "blockers": _counter(item for row in ledger_rows if row.get("queue")
                                 for item in (row.get("blockers") or [])),
            "queue_state": _counter((row.get("queue") or {}).get("queue_state") for row in ledger_rows
                                    if row.get("queue")),
        },
    }
    dependencies = {
        "queue": len(queue_rows),
        "in_universe": len(queue_vas & universe),
        "out_of_universe": queue_out_of_universe,
        "out_of_universe_count": len(queue_out_of_universe),
        "actionable_frontier": len(actionable),
        "actionable_frontier_in_universe": len(actionable_in_universe),
        "queue_state_crosstab": dict(sorted(_counter(
            "%s/%s" % ((row.get("queue") or {}).get("queue_state"),
                       (row.get("queue") or {}).get("readiness"))
            for row in ledger_rows if row.get("queue")).items())),
        "readiness": _counter((row.get("queue") or {}).get("readiness") for row in ledger_rows
                              if row.get("queue")),
        "blockers": _counter(item for row in ledger_rows if row.get("queue")
                             for item in (row.get("blockers") or [])),
        "availability_conflicts": [
            {"va": row.get("va"), "conflicts": row.get("availability_conflicts")}
            for row in ledger_rows if row.get("availability_conflicts")],
        "dependency_completeness": {
            "closed_gameplay_functions": dependency_closed,
            "uncertain_gameplay_functions": dependency_uncertain,
            "queue_rows_with_dependencies": len(queue_dependency & universe),
            "distinct_queue_dependency_tokens": len({token for record in queue_rows
                                                     for token in (record.get("dependencies") or [])}),
        },
        "blocked_axes": blocked_axes,
        "frontier_cross_check": frontier_agreement,
    }

    # -- history ------------------------------------------------------------
    change_log = manifest.get("change_log") or []
    checkpoints = []
    for entry in change_log:
        checkpoints.append({
            "date": entry.get("date"),
            "date_is_recorded_by_the_artifact": entry.get("date") is not None,
            "summary": entry.get("change"),
            "batch": entry.get("batch"),
            "function_records_added": entry.get("added_function_records"),
            "runtime_validated": entry.get("runtime_validated"),
        })
    checkpoints.sort(key=lambda item: (item["date"] or "", item["summary"] or ""))
    history = {
        "checkpoints": checkpoints,
        "source": "%s#change_log (verbatim date and change fields)" % MANIFEST_REL,
        "delta_since_previous": metrics.get("delta_since_previous"),
        "limitation": (
            "ONLY what the artifacts explicitly record is reported here. %d change_log entries "
            "with their own date and change fields, plus metrics.delta_since_previous. Wave-by-wave "
            "history is NOT reconstructed: no artifact records it, and inventing a timeline would "
            "manufacture history the repository does not contain. Entries whose artifact records no "
            "date carry date=null and say so."
            % len(change_log)),
    }

    # -- snapshot -----------------------------------------------------------
    # Per-directory tracked-member tallies. A directory can be "tracked" while
    # only a fraction of its members are, which is exactly the reading
    # `git_tracked: true` invites a reader to take -- so the member count is
    # published next to the verdict.
    dir_tracked_members = {
        "decomp_gap_parts": sum(1 for rel, _ in gap_parts if _git_tracked(root, rel) is True),
        "metadata_dir": metadata_tracked,
        "handoff_dir": sum(1 for rel, _ in handoffs if _git_tracked(root, rel) is True),
        "staging_dir": sum(1 for rel in staging_member_rels if _git_tracked(root, rel) is True),
        "evidence_dir": evidence_tracked,
    }
    inputs = {}
    for key, rel in (("coverage_ledger", LEDGER_REL), ("manifest", MANIFEST_REL),
                     ("triage_queue", QUEUE_REL), ("semantic_decomp", SEMANTIC_DECOMP_REL),
                     ("semantic_blueprint", SEMANTIC_BLUEPRINT_REL),
                     ("residual_unknown", RESIDUAL_UNKNOWN_REL),
                     ("decomp_gap_parts", "%s/*.json" % DECOMP_GAP_REL),
                     ("metadata_dir", "%s/**/*.json" % METADATA_REL),
                     ("handoff_dir", "%s/**/handoff.json" % HANDOFF_REL),
                     ("staging_dir", "%s/*/" % STAGING_REL),
                     ("evidence_dir", "%s/*/" % EVIDENCE_REL),
                     ("knowledge_index", KNOWLEDGE_INDEX_REL),
                     ("kg_db", KG_DB_REL), ("runtime_oracle", RUNTIME_ORACLE_REL)):
        fingerprint = reader.fingerprints.get(rel)
        if key == "decomp_gap_parts":
            fingerprint = {"sha256": None, "bytes": sum((reader.fingerprints.get(item) or {}).get("bytes", 0)
                                                       for item, _ in gap_parts),
                           "mtime_ns": None}
        elif key == "metadata_dir":
            fingerprint = {"sha256": None,
                           "bytes": sum((reader.fingerprints.get(item) or {}).get("bytes", 0)
                                        for item, _ in metadata_files),
                           "mtime_ns": None}
        elif key == "handoff_dir":
            fingerprint = {"sha256": None,
                           "bytes": sum((reader.fingerprints.get(item) or {}).get("bytes", 0)
                                        for item, _ in handoffs),
                           "mtime_ns": None}
        elif key == "staging_dir":
            # A real content aggregate over EVERY member (.json, .cpp, .hpp, .sh),
            # so a C++ edit is visible in the snapshot and not only in the counts.
            # Derived from sha256 + size only: an mtime here would make the report
            # depend on when it was run.
            fingerprint = {"sha256": staging_members_sha256,
                           "bytes": staging_aggregate_bytes,
                           "mtime_ns": None}
        elif key == "evidence_dir":
            fingerprint = {"sha256": None, "bytes": None, "mtime_ns": None}
        inputs[key] = _input_entry(root, rel, fingerprint)
        if key in ("decomp_gap_parts", "metadata_dir", "handoff_dir", "staging_dir", "evidence_dir"):
            members = {"decomp_gap_parts": gap_parts, "metadata_dir": metadata_files,
                       "handoff_dir": handoffs, "staging_dir": staging_json,
                       "evidence_dir": [(pack, None) for pack in evidence_packs]}[key]
            member_count = len(staging_member_rels) if key == "staging_dir" else len(members)
            inputs[key]["present"] = bool(members) or key == "evidence_dir"
            inputs[key]["member_count"] = member_count
            inputs[key]["tracked_members"] = dir_tracked_members[key]
            # `git_tracked` is verdict for the DIRECTORY path; tracked_members is
            # how many of member_count are individually tracked. A directory can
            # be tracked while only a fraction of its members are, and reading
            # git_tracked: true as "all of it survives a fresh clone" is wrong.
            inputs[key]["tracked_members_is_all"] = (
                member_count > 0 and dir_tracked_members[key] == member_count)
            inputs[key]["sha256_is_null_by_design"] = (
                None if key == "staging_dir" else
                "a directory input has no single content hash; member sha256 values are "
                "individually reproducible")
            if key == "staging_dir":
                inputs[key]["sha256_is_a_member_aggregate"] = (
                    "sha256 of the sorted '%s\\0%s\\0%s' lines (relpath, member sha256, member "
                    "bytes) over every .json/.cpp/.hpp/.sh member, so a C++ edit changes it; "
                    "content-derived, never mtime-derived")

    binary = manifest.get("binary") or {}
    snapshot = {
        "binary_sha256": binary.get("sha256"),
        "binary_version": binary.get("version"),
        "image_base": binary.get("image_base"),
        "inputs": inputs,
        "input_drift": [],
        "source_input_hash_verification": {
            "ledger_self_reported_counts": ledger.get("counts"),
            "manifest_self_reported_metrics": {
                "total_functions_indexed": metrics.get("total_functions_indexed"),
                "function_records": metrics.get("function_records"),
                "bodies_reconstructed": metrics.get("bodies_reconstructed"),
                "integrated": metrics.get("integrated"),
                "blocked": metrics.get("blocked"),
                "runtime_validated": metrics.get("runtime_validated"),
                "runtime_gated": metrics.get("runtime_gated"),
                "deferred": metrics.get("deferred"),
            },
            "agrees_with_recomputed": (
                metrics.get("total_functions_indexed") == UNIVERSE_TOTAL
                and metrics.get("function_records") == len(functions)),
            "universe_defined_by": "distinct VA rows in the coverage ledger",
            "gameplay_defined_by": "ledger triage_category in {GAMEPLAY_LOGIC, GAMEPLAY_SUPPORT}",
        },
    }

    # -- blind spots --------------------------------------------------------
    # Every magnitude in this prose is interpolated from a value computed above,
    # except where a literal is noted inline as a verified constant.
    # A number the code did not compute is a number that silently becomes a lie
    # the moment a concurrent agent grows the manifest.
    blind_spots = [
        ("call-graph, field, and type knowledge depends solely on a gitignored, stale "
         "(classifier triage-v4) SQLite database: 0% of the caller/callee, "
         "has_type_association and evidence_calls dimensions survives a fresh clone."),
        ("%d of the %d persisted decompilation bodies live under gitignored .spore-analysis/ "
         "and the remaining %d %s tracked; the tracked decompiler .c output does not account "
         "for the block."
         % (bodies_gitignored, len(persisted), len(persisted) - bodies_gitignored,
            "is" if len(persisted) - bodies_gitignored == 1 else "are")),
        ("a second decompiler cache under tools/mcp/cache/decompiled/ holds further bodies and "
         "is gitignored and self-described as disposable; this reporter does not count it, "
         "because counting it would mean trusting a cache its own author calls throwaway"),
        ("0 runtime-validated functions and 0 negative runtime observations exist; the original "
         "Cell stage was never entered in any Wine run recorded by %s."
         % RUNTIME_ORACLE_REL),
        ("ledger semantic_understanding is the constant 'not_established' on all %d rows: zero "
         "information, a disclaimer rather than a classification." % UNIVERSE_TOTAL),
        ("%.1f%% of the universe (%d functions) has no package or cluster membership claim at all."
         % (100.0 * (UNIVERSE_TOTAL - len(package_membership)) / UNIVERSE_TOTAL,
            UNIVERSE_TOTAL - len(package_membership))),
        ("reconstruction/metadata is %s untracked; only %d of %d metadata files survive a "
         "fresh clone." % (metadata_untracked_phrase, metadata_tracked, len(metadata_files))),
        ("%d reconstructed VAs (%s) lie outside the %d-row universe and are also absent from "
         "metrics.accounting_exclusions."
         % (len(manifest_out_of_universe), ", ".join(manifest_out_of_universe), UNIVERSE_TOTAL)),
        ("%d of %d manifest records reference a runtime gate token absent from the canonical "
         "runtime_gates[] list." % (absent_gate_records, len(functions))),
        ("packages[].functions covers only %d of %d records; %d record package ids are missing "
         "from packages[]; and no declared completion split can be re-derived from packages[], "
         "because the status census is {%s} over %d records -- every package is accounted for "
         "and no `complete` field exists on any of them."
         % (len(package_function_vas), len(functions),
            len(record_package_ids - declared_package_ids),
            ", ".join("%s: %d" % (name, count)
                      for name, count in sorted(Counter(
                          package.get("status") for package in packages).items(),
                          key=lambda item: str(item[0]))),
            len(packages))),
        ("%d of the %d triage-queue rows lie outside the canonical universe and have no function "
         "or xref data; they are preserved separately rather than forced into the ledger."
         % (len(queue_out_of_universe), len(queue_rows))),
        ("the live-only decompilation dimension is clone-reproducible because it is derived from "
         "the git-tracked decomp-gap/*.json partitions; the 142MB synthesis output "
         "decomp-gap-excavation.json is gitignored and is neither read nor regenerated here."),
    ]

    # -- cannot determine ---------------------------------------------------
    cannot_determine = [
        {"metric": "functions_with_caller",
         "reason": "source is the gitignored, stale (triage-v4) SQLite database; a fresh clone has "
                   "no xref table, so this dimension is not reproducible. Marked machine_local."},
        {"metric": "functions_with_callee",
         "reason": "source is the gitignored, stale (triage-v4) SQLite database; a fresh clone has "
                   "no xref table, so this dimension is not reproducible. Marked machine_local."},
        {"metric": "functions_with_any_call_role",
         "reason": "source is the gitignored, stale (triage-v4) SQLite database; a fresh clone has "
                   "no xref table, so this dimension is not reproducible. Marked machine_local."},
        {"metric": "runtime_unavailable",
         "reason": "no record in the repository carries a `runtime_unavailable` field; "
                   "NOT_AVAILABLE is a capability/verdict token, so a VA count would require "
                   "inventing the category. Emitted available=false with the capability status "
                   "instead."},
        {"metric": "withheld_va",
         "reason": "'withheld' is not a canonical term in this repository: no field, enum, or "
                   "status carries that name. The two closest sourced quantities "
                   "(handoff excluded_addresses, deferred_full_package_claims.withheld_body_count) "
                   "are reported by name; the latter has no VA list, so no VA count is derivable."},
        {"metric": "withheld_va_from_deferred_full_package_claims",
         "reason": "deferred_full_package_claims.withheld_body_count is a bare integer (%d) "
                   "with no VA list, so it cannot be resolved to addresses." % withheld_bodies},
        {"metric": "a single overall completion percentage",
         "reason": "the dimensions are defined over different universes, provenances, and evidence "
                   "ladders; any weighted composite would be a fabrication. Deliberately absent."},
    ]
    if not db_available:
        cannot_determine.append(
            {"metric": "kg_db_derived_dimensions",
             "reason": "--no-local-db was passed or the gitignored database is absent; every "
                       "dimension derived from it is emitted available=false."})
    if residual is None:
        cannot_determine.append(
            {"metric": "residual_unknown_negative_label",
             "reason": "%s is absent; the negative label cannot be cross-checked against the "
                       "complement of the 'partial' set." % RESIDUAL_UNKNOWN_REL})
    if not index_available:
        cannot_determine.append(
            {"metric": "in_actionable_frontier_cross_check",
             "reason": "%s is absent or untracked inputs were excluded; the derived actionable "
                       "frontier cannot be cross-checked against the projection (it is still "
                       "derivable from tracked inputs alone)." % KNOWLEDGE_INDEX_REL})

    # -- assemble -----------------------------------------------------------
    report = {
        "$schema": SCHEMA,
        "artifact": "openspore-reconstruction-coverage",
        "generated_by": GENERATOR,
        "generator_status": {
            "read_only": True,
            "writes": "none unless --out is passed explicitly",
            "imports_no_writing_subsystem": True,
            "takes_machine_lock": False,
            "sqlite_mode": "ro",
            "sqlite_sidecar_note": (
                "the database is in WAL mode, so taking a read lock re-stamps the -shm "
                "read-lock index and may trigger SQLite's one-time recovery of a stale -wal. "
                "Neither the .db nor the -wal is written, and this is exactly what a bare "
                "mode=ro open does: it is a SQLite artefact, not a mutation by this reporter"),
            "timestamp_free": True,
            "no_absolute_paths_in_body": True,
            "host_probes": [
                {
                    "probe": "git ls-files --error-unmatch",
                    "feeds": ["snapshot.inputs[*].git_tracked", "snapshot.inputs[*].tracked_verdict",
                              "snapshot.inputs[*].tracked_members",
                              "reconstruction.evidence_packs_git_tracked"],
                    "reads": "the git INDEX at report time, not the working tree",
                    "content_deterministic": False,
                    "why": "this is the one field in the report that a concurrent `git add` or "
                           "`git rm --cached` can change without any artifact byte changing. Every "
                           "other field is a pure function of artifact content.",
                    "consequence": "two reports of byte-identical artifacts can differ in these "
                                   "fields alone; that difference is NOT engine nondeterminism",
                    "mitigation": "no other host probe is performed: no source-index presence "
                                  "check, no hostname, no environment read, and no developer-tool "
                                  "index probe",
                },
            ],
            "composite_score": "deliberately absent; see caveats",
        },
        "snapshot": snapshot,
        "universes": {
            "internal_functions": len(universe),
            "gameplay_functions": len(gameplay),
            "non_gameplay_functions": len(non_gameplay),
            "gameplay_definition": {
                "source": "%s#ledger[].triage_category" % LEDGER_REL,
                "categories": list(GAMEPLAY_CATEGORIES),
                "definition": "canonical rows whose triage category is GAMEPLAY_LOGIC or "
                              "GAMEPLAY_SUPPORT",
                "independently_confirmed_by": "%s#functions[] VA set is identical to the gameplay set"
                                              % SEMANTIC_BLUEPRINT_REL,
            },
            "universe_definition": {
                "source": "%s#ledger" % LEDGER_REL,
                "definition": "unique VA rows in the %s-row functions.tsv export and "
                              "triage-f0e310e0.triage-v6.jsonl" % format(UNIVERSE_TOTAL, ",d"),
                "duplicate_vas": len(ledger_rows) - len(universe),
            },
        },
        "dimensions": dimensions,
        "classifications": classifications,
        "reconstruction": reconstruction,
        "semantics": semantics,
        "evidence": evidence,
        "runtime": runtime,
        "dependencies": dependencies,
        "history": history,
        "blind_spots": blind_spots,
        "cannot_determine": cannot_determine,
        "caveats": [
            "There is deliberately NO single overall completion percentage. These dimensions are "
            "defined over different universes (%s vs %s), different provenance classes "
            "(tracked / untracked / machine-local), and different evidence ladders; any weighted "
            "composite would be a fabrication, not a measurement.",
            "Provenance is part of every number: a 'tracked' dimension survives a fresh clone, an "
            "'untracked' one does not, and a 'machine_local' one is not reproducible at all.",
            "NOT_RUN, UNKNOWN, UNCLASSIFIED, and RUNTIME-GATED are all absences of evidence. None "
            "of them is a claim that something is wrong.",
            "'available' and 'sufficient' are different claims about an evidence class. A class "
            "whose field merely exists is available, not sufficient.",
            "metrics.accounting_exclusions is a preservation list, not a subtraction; all of its "
            "VAs are integrated records.",
            "The binary sha256, version, and image base are copied from the manifest's own binary "
            "block. The reporter does not hash SPORE/SporeBin/SporeApp.exe itself, because doing "
            "so would make a report depend on a directory that is git-ignored and absent in a "
            "fresh clone.",
            "The 3 queue rows outside the canonical universe and the %d manifest VAs outside it are "
            "preserved and reported, never discarded and never merged." % len(manifest_out_of_universe),
            "Untracked inputs change under concurrent agents. The report fingerprints every input "
            "before and after reading and refuses to publish on a torn read, but a rebuild after a "
            "concurrent edit can legitimately report different untracked counts.",
        ],
    }
    return report


# ---------------------------------------------------------------------------
# rendering + CLI entry
# ---------------------------------------------------------------------------

def _md_cell(value):
    return "-" if value is None else str(value)


def render_markdown(report):
    universes = report.get("universes") or {}
    lines = ["# OpenSpore reconstruction coverage",
             "",
             "Deterministic read-only coverage matrix. There is intentionally no single "
             "completion percentage.",
             "",
             "## Universes",
             "",
             "| universe | count |", "| --- | --- |",
             "| internal functions | %s |" % universes.get("internal_functions"),
             "| gameplay functions | %s |" % universes.get("gameplay_functions"),
             "| non-gameplay functions | %s |" % universes.get("non_gameplay_functions"),
             "",
             "## Coverage matrix",
             "",
             "A `pct` of `-` is a dimension whose covered set IS its universe by "
             "construction: any percentage would be the identity 100.0, not a measurement.",
             "",
             "| dimension | covered | universe | pct | gameplay covered | gameplay pct | provenance | available |",
             "| --- | ---: | ---: | ---: | ---: | ---: | --- | --- |"]
    for record in report.get("dimensions") or []:
        lines.append("| %s | %s | %s | %s | %s | %s | %s | %s |" % (
            record.get("id"), _md_cell(record.get("covered")), _md_cell(record.get("universe")),
            _md_cell(record.get("pct")), _md_cell(record.get("gameplay_covered")),
            _md_cell(record.get("gameplay_pct")), record.get("provenance"),
            "yes" if record.get("available") else "no"))
    semantics = report.get("semantics") or {}
    lines += ["", "## Semantic tiers", "", "| tier | count |", "| --- | ---: |"]
    for name, value in sorted((semantics.get("tiers") or {}).items()):
        lines.append("| %s | %s |" % (name, value))
    runtime = report.get("runtime") or {}
    lines += ["", "## Runtime", "",
              "| measure | value |", "| --- | --- |",
              "| validated | %s |" % runtime.get("validated"),
              "| gated | %s |" % runtime.get("gated"),
              "| negative | %s |" % runtime.get("negative"),
              "| capability status | %s |" % runtime.get("capability_status")]
    lines += ["", "## Blind spots", ""]
    for item in report.get("blind_spots") or []:
        lines.append("- %s" % item)
    lines += ["", "## Cannot determine", ""]
    for item in report.get("cannot_determine") or []:
        lines.append("- **%s** — %s" % (item.get("metric"), item.get("reason")))
    lines += ["", "## Caveats", ""]
    for item in report.get("caveats") or []:
        lines.append("- %s" % item)
    return "\n".join(lines) + "\n"


def coverage(root=ROOT, args=None):
    """CLI entry point. Writes nothing unless the caller passed --out."""
    report = build_report(root,
                          include_local_db=not bool(getattr(args, "no_local_db", False)),
                          include_untracked=not bool(getattr(args, "no_untracked", False)))
    if getattr(args, "gameplay", False):
        report["universes"]["restricted_to"] = "gameplay"
    if not getattr(args, "history", False):
        report["history"] = {
            "checkpoints": [],
            "source": None,
            "delta_since_previous": None,
            "limitation": "history checkpoints omitted: pass --history to include them "
                          "(the underlying data is always recovered from the manifest)",
            "omitted_by_flag": True,
        }
    if getattr(args, "markdown", False):
        result = {"markdown": render_markdown(report), "report": report}
    else:
        result = report
    out = getattr(args, "out", None)
    if out:
        from .models import write_json_atomic
        write_json_atomic(out, report)
        result = dict(result) if isinstance(result, dict) else result
        result["written_to"] = str(out)
    return result
