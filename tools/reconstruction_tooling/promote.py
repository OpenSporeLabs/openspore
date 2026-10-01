"""Promotion of validated staging packages into ``src/reconstruction/``.

A package is promoted when, and only when, the two axes compose:
``report["static"]["status"] == "PASS"`` and
``report["runtime"]["status"] == "GATED"`` (see
``docs/tooling/validation-dimensions.md``). ``STATIC_VALIDATED`` is that
composition; nothing here emits the token, and neither axis is ever
manufactured. The runtime axis is an open gate, so a promoted package
carries ``runtime_status: "GATED"`` forever and never a runtime PASS.

Three invariants shape the module:

* **All or nothing.** A compile or test failure must not leave half a
  package in ``src/`` and must not be recorded as a promotion. The package
  is therefore built and gated in a scratch tree that no discovery path can
  see, and only a green gate installs it.
* **Nothing is invented.** Every field in
  ``src/reconstruction/<pkg>/promotion.json`` is copied from a persisted
  artifact (the validation report, the evidence pack, the metadata record,
  the knowledge index) or is a digest of one. No ABI fact, no symbol, no
  status is derived here.
* **Deterministic.** ``src/**/promotion.json`` carries no wall clock, no pid
  and no absolute path, so a re-run over unchanged inputs reproduces it byte
  for byte. Timestamps live only in
  ``reconstruction/evidence/<bare8>/promotion.json``, the provenance side,
  which is allowed to be dated.
* **One writer per package.** An install is a directory rename, which is
  atomic but not exclusive: two promotions of the same package could both
  decide the package is absent and both install. A per-package lock directory
  makes the second one wait and then observe the first one's result. The lock
  is per package, so promotions of different packages never contend, and a lock
  whose owner is gone is stolen rather than waited on.
* **One reading of "promoted".** A ``src/reconstruction/*`` directory counts as
  promoted only when its marker carries the frozen schema and a ``src_package``
  the build would accept -- the rule ``build_gate.discover_packages`` and
  ``src/reconstruction/CMakeLists.txt`` apply. Scratch, lock and recovery trees
  are dotted and are invisible to this module, to the gate and to CMake alike.
  Two staging packages whose names normalize to one ``src_package`` are
  refused, not merged.

The unit of promotion is the *package*, not the VA: one gate call covers one
package, and a single refused VA refuses its whole package, because
installing a subset would leave the tree unable to match its own staging
source on the next attempt.
"""

import importlib
import os
import re
import shutil
import sys
import tempfile
import time
from datetime import datetime, timezone
from pathlib import Path

from . import ownership
from .models import (ROOT, canonical_json, file_sha256, load_json,
                     normalize_va, write_json_atomic)

PLAN_SCHEMA = "openspore-promotion-plan-1"
RESULT_SCHEMA = "openspore-promotion-result-1"
PACKAGE_SCHEMA = "openspore-promotion-1"
RECORD_SCHEMA = "openspore-promotion-record-1"
VALIDATION_SCHEMA = "openspore-structural-validation-1"
# The frozen contract spells this "openspoke-build-gate-1". The shipped
# build_gate.py spells it "openspore-build-gate-1"; the gate's own value
# always wins, and this constant is only the fallback for a skipped gate.
BUILD_SCHEMA = "openspore-build-gate-1"

SRC_REL = "src/reconstruction"
STAGING_REL = "reconstruction/staging"
METADATA_REL = "reconstruction/metadata"
EVIDENCE_REL = "reconstruction/evidence"
INDEX_REL = "reconstruction/knowledge/index.json"
VALIDATION_NAME = "validation.json"
EVIDENCE_NAME = "evidence.json"
PROMOTION_NAME = "promotion.json"
# Dotted so a ``src/reconstruction/*`` glob cannot reach it, and inside
# ``src/reconstruction/`` so the install is a same-filesystem rename.
SCRATCH_NAME = ".promote-tmp"
# Where a previous tree goes when it cannot be put back after a failed
# install. Dotted for the same reason as SCRATCH_NAME, and one level deeper so
# no ``*/promotion.json`` glob -- CMake's or Python's -- can reach it.
LOST_NAME = ".promote-lost"
# One lock per package, so two promotions of different packages never wait on
# each other.
LOCK_PREFIX = ".promote-lock-"
LOCK_OWNER = "owner"
LOCK_TIMEOUT = 120.0
LOCK_POLL = 0.02
TEST_SUFFIX = "_test.cpp"
REQUIRED_STATIC_STATUS = "PASS"
REQUIRED_RUNTIME_STATUS = "GATED"
# The rule ``src/reconstruction/CMakeLists.txt`` applies to a src_package
# before it becomes a target name. Mirrored here so a marker that the build
# would reject is not reported as a promotion.
SRC_NAME_RE = re.compile(r"^[A-Za-z0-9_]+$")
# Only these ever cross into src/. ``.sh``, ``.json``, ``metadata/`` and
# ``*.py`` in a staging directory are worker scratch, not reconstruction.
SOURCE_SUFFIXES = (".cpp", ".hpp", ".h")

BLOCKERS = frozenset({
    "validation_report_missing",
    "validation_unreadable",
    "validation_schema_unsupported",
    "static_not_pass",
    "runtime_not_gated",
    "validation_stale",
    "source_missing",
    "no_sources",
    "no_header",
    "no_test",
    "duplicate_va",
    "superseded_ownership",
    "ownership_unreconciled",
    "no_metadata_record",
    "metadata_unreadable",
    "namespace_mismatch",
    "binary_content",
    "drifted_existing",
    "would_drop_files",
    "inputs_changed",
    "sibling_refused",
    "package_refused",
    "src_package_collision",
    "package_locked",
})

# A bare 8-hex-digit run, not adjacent to more hex. Written as 0x + 8 digits
# this would never match a padded VA: "006a2ef0" is a leading zero plus seven
# digits, so the optional "0" leaves too few to fill the group.
VA_TOKEN = re.compile(r"(?<![0-9a-zA-Z])(?:0x)?([0-9a-f]{8})(?![0-9a-zA-Z])")
NAMESPACE_TOKEN = re.compile(r"namespace\s+([A-Za-z_]\w*(?:::[A-Za-z_]\w*)*)")
# The gate's project skeleton. The reconstruction policy flags are the real
# ones from the repository root; nothing else is needed to compile and ctest a
# promoted package.
GATE_PROJECT = """cmake_minimum_required(VERSION 3.16)
project(openspore_promotion_gate CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Werror)

enable_testing()

add_subdirectory(src)
"""


def _blocker(code, detail):
    # type: (str, str) -> dict
    if code not in BLOCKERS:
        raise AssertionError("undeclared blocker code: %s" % code)
    return {"code": code, "detail": detail}


def _dashes(value):
    # type: (str) -> str
    return str(value).replace("_", "-").lower()


def _underscores(value):
    # type: (str) -> str
    return str(value).replace("-", "_").lower()


def _resolve_package(package):
    # type: (object) -> tuple
    """Accept either spelling and return ``(dashed, underscored)``."""
    if package is None:
        return None, None
    text = str(package).strip().strip("/")
    if not text:
        return None, None
    if text.startswith(SRC_REL + "/"):
        text = text[len(SRC_REL) + 1:]
    text = text.replace("/", "-")
    dashed = _dashes(text)
    return dashed, _underscores(dashed)


def _bare(value):
    # type: (object) -> str
    return normalize_va(value)[2:]


def _rel(root, path):
    # type: (Path, Path) -> str
    try:
        return str(Path(path).resolve().relative_to(Path(root).resolve())).replace(os.sep, "/")
    except (OSError, ValueError):
        return str(path).replace(os.sep, "/")


def _source_locations(role, source_path, root):
    # type: (str, object, Path) -> tuple
    """Map a validation report's ``source`` block to ``(staging, src, pkg)``.

    ``validate._source`` already ranks ``src/`` above
    ``reconstruction/staging/``, so a report naming a canonical artifact
    describes a package that was promoted before; its staging twin, when one
    exists, still describes what the package should contain.
    """
    text = str(source_path or "").replace(os.sep, "/")
    if role not in ("canonical", "staging"):
        return None, None, None
    if text.startswith(STAGING_REL + "/"):
        rest = text[len(STAGING_REL) + 1:]
        if "/" not in rest:
            return None, None, None
        package = rest.split("/", 1)[0]
        return Path(root) / STAGING_REL / package, None, package
    if text.startswith(SRC_REL + "/"):
        rest = text[len(SRC_REL) + 1:]
        if "/" not in rest:
            return None, None, None
        src_package = rest.split("/", 1)[0]
        package = _dashes(src_package)
        staging = Path(root) / STAGING_REL / package
        return (staging if staging.is_dir() else None), Path(root) / SRC_REL / src_package, package
    return None, None, None


def _package_files(directory):
    # type: (Path) -> list
    """Every promotable file in a package directory, as sorted relative paths."""
    if directory is None or not Path(directory).is_dir():
        return []
    base = Path(directory)
    found = []
    for path in base.rglob("*"):
        if path.is_file() and path.suffix in SOURCE_SUFFIXES:
            found.append(path.relative_to(base).as_posix())
    return sorted(found)


def _partition(files):
    # type: (list) -> tuple
    sources = [name for name in files if name.endswith(".cpp") and not name.endswith(TEST_SUFFIX)]
    headers = [name for name in files if name.endswith((".hpp", ".h"))]
    tests = [name for name in files if name.endswith(".cpp") and name.endswith(TEST_SUFFIX)]
    return sources, headers, tests


def _namespace_sequence(text):
    # type: (str) -> list
    """The namespace components a translation unit opens, flattened in order.

    A closing comment such as ``}  // namespace openspore::reconstruction::p``
    is skipped: the ``}`` earlier on that line means the scope is closing,
    and counting it would let any file that merely mentions the namespace in
    a trailing comment satisfy the check.
    """
    components = []
    for match in NAMESPACE_TOKEN.finditer(text or ""):
        line_start = text.rfind("\n", 0, match.start()) + 1
        if "}" in text[line_start:match.start()]:
            continue
        line_end = text.find("\n", match.end())
        tail = text[match.end():len(text) if line_end < 0 else line_end]
        if "{" not in tail:
            continue
        components.extend(match.group(1).split("::"))
    return components


def _declares_namespace(text, src_package):
    # type: (str, str) -> bool
    wanted = ["openspore", "reconstruction", src_package]
    components = _namespace_sequence(text)
    for start in range(0, max(0, len(components) - len(wanted) + 1)):
        if components[start:start + len(wanted)] == wanted:
            return True
    return False


def _binary_offence(path):
    # type: (Path) -> str
    data = Path(path).read_bytes()
    if b"\x00" in data:
        return "contains NUL bytes"
    try:
        data.decode("utf-8")
    except UnicodeDecodeError:
        return "is not UTF-8 text"
    printable = sum(1 for byte in data if byte in (9, 10, 13) or 32 <= byte < 127 or byte >= 128)
    if data and printable / len(data) < 0.85:
        return "has a high proportion of non-text bytes"
    return ""


def _index_records(root):
    # type: (Path) -> dict
    try:
        index = load_json(Path(root) / INDEX_REL)
    except (OSError, ValueError):
        return {}
    records = index.get("records", {}) if isinstance(index, dict) else {}
    return records if isinstance(records, dict) else {}


def _record(records, va):
    # type: (dict, str) -> dict
    found = records.get(normalize_va(va)) or records.get(_bare(va))
    return found if isinstance(found, dict) else {}


def _read_json(path):
    # type: (Path) -> tuple
    """``(document, problem)``; ``problem`` is ``None``, ``"missing"`` or text."""
    if not Path(path).exists():
        return None, "missing"
    try:
        return load_json(path), None
    except (OSError, ValueError) as exc:
        return None, "%s: %s" % (type(exc).__name__, exc)


def _validation_reports(root):
    # type: (Path) -> list
    base = Path(root) / EVIDENCE_REL
    if not base.is_dir():
        return []
    return sorted((_bare(entry.name), entry / VALIDATION_NAME)
                  for entry in base.iterdir() if entry.is_dir() and (entry / VALIDATION_NAME).is_file())


def _staging_packages(root):
    # type: (Path) -> list
    base = Path(root) / STAGING_REL
    if not base.is_dir():
        return []
    return sorted(entry.name for entry in base.iterdir() if entry.is_dir())


def _discovery(root):
    # type: (Path) -> list
    """Every VA a promotion could concern, as ``(bare, package_hint)``.

    Validation reports are the anchor, but a report-only view hides a staged
    package that has not been validated yet -- the exact case an operator
    asks about. Each staging package therefore also contributes its
    unreported metadata VAs, and, when it has no metadata at all, one entry
    with no VA whose blockers say so.
    """
    reports = _validation_reports(root)
    found = [(bare, None) for bare, _path in reports]
    seen = set(bare for bare, _hint in found)
    for package in _staging_packages(root):
        metadata = Path(root) / METADATA_REL / package
        stems = sorted(record.stem for record in metadata.glob("*.json")) if metadata.is_dir() else []
        for stem in stems:
            if stem not in seen:
                seen.add(stem)
                found.append((stem, package))
        if not stems:
            found.append((None, package))
    return found


def _va_claims(root, reports):
    # type: (Path, list) -> dict
    """Which staging packages claim which VA, from three independent signals.

    A package claims a VA when it holds ``metadata/<pkg>/<bare8>.json``, when
    a staged filename carries the bare VA, or when a validation report names
    a source file inside it. The signals are deliberately redundant: a
    metadata record is the strongest statement of intent, but only a handful
    of packages have one, and the filename and report signals catch the rest.
    """
    claims = {}

    def add(va, package):
        if package:
            claims.setdefault(_bare(va), set()).add(package)

    for bare, path in reports:
        report, problem = _read_json(path)
        if report is None:
            continue
        source = report.get("source") or {}
        add(bare, _source_locations(source.get("role"), source.get("path"), root)[2])
    for package in _staging_packages(root):
        metadata = Path(root) / METADATA_REL / package
        if metadata.is_dir():
            for record in metadata.glob("*.json"):
                add(record.stem, package)
        for name in _package_files(Path(root) / STAGING_REL / package):
            for match in VA_TOKEN.finditer(name):
                add(match.group(1), package)
    return claims


def _promoted_marker(path):
    # type: (Path) -> dict
    """An installed ``promotion.json``, or ``{}`` when it is not a real marker.

    The same acceptance rule as ``build_gate.discover_packages`` and as
    ``src/reconstruction/CMakeLists.txt``: the schema must be the frozen one and
    the ``src_package`` must be a name the build would accept. A marker that
    fails either test is not a promotion as far as any reader is concerned --
    it is never reported by :func:`promoted_packages` and its targets never
    claim a VA -- because treating it as one would make this module disagree
    with the build about what exists.
    """
    document, _problem = _read_json(Path(path))
    if not isinstance(document, dict):
        return {}
    if document.get("schema") != PACKAGE_SCHEMA:
        return {}
    package = document.get("src_package")
    if not isinstance(package, str) or not SRC_NAME_RE.match(package):
        return {}
    return document


def _promoted_va_owners(root):
    # type: (Path) -> dict
    """VA -> src packages that already claim it, from installed markers."""
    owners = {}
    base = Path(root) / SRC_REL
    if not base.is_dir():
        return owners
    for entry in sorted(base.iterdir()):
        if not entry.is_dir() or entry.name.startswith("."):
            continue
        document = _promoted_marker(entry / PROMOTION_NAME)
        if not document:
            continue
        for target in document.get("targets", []) or []:
            try:
                owners.setdefault(_bare(target.get("va")), set()).add(entry.name)
            except ValueError:
                continue
    return owners


def _digests_of(root, candidate):
    # type: (Path, dict) -> dict
    """Every input digest this promotion depends on, taken as one set.

    Re-taken immediately before the install; any difference between the two
    sets is ``inputs_changed`` and nothing is written.
    """
    digests = {"files": {}, "validation": None, "metadata": None, "evidence": None}
    directory = candidate.get("_package_dir")
    if directory:
        for name in candidate.get("_files", []):
            digests["files"][name] = file_sha256(Path(directory) / name)
    if not candidate.get("bare_va"):
        return digests
    report_path = Path(root) / EVIDENCE_REL / candidate["bare_va"] / VALIDATION_NAME
    if report_path.is_file():
        digests["validation"] = file_sha256(report_path)
    if candidate.get("metadata"):
        metadata_path = Path(root) / candidate["metadata"]
        if metadata_path.is_file():
            digests["metadata"] = file_sha256(metadata_path)
    evidence_path = Path(root) / EVIDENCE_REL / candidate["bare_va"] / EVIDENCE_NAME
    if evidence_path.is_file():
        digests["evidence"] = file_sha256(evidence_path)
    return digests


def _candidate(root, bare, hint, index, claims, owners, overwrite):
    # type: (Path, str, object, dict, dict, dict, bool) -> dict
    """Adjudicate one VA.

    ``hint`` names the staging package a metadata record points at, for a VA
    that no validation report has claimed. Every staging package is
    therefore adjudicated, and a package with no report is refused with a
    reason instead of being absent from the plan.
    """
    report_path = Path(root) / EVIDENCE_REL / bare / VALIDATION_NAME if bare else None
    report, problem = _read_json(report_path) if report_path is not None else (None, "missing")
    candidate = {
        "va": ("0x%s" % bare) if bare else None,
        "bare_va": bare,
        "package": None,
        "src_package": None,
        "staging_dir": None,
        "src_dir": None,
        "sources": [],
        "headers": [],
        "tests": [],
        "static_status": None,
        "runtime_status": None,
        "promoted": False,
        "blockers": [],
        "metadata": None,
        "_report": report,
        "_record": {},
        "_files": [],
        "_package_dir": None,
        "_abi": {"calling_convention": None, "return_type": None, "stack_cleanup_bytes": None},
        "_digests": {"files": {}, "validation": None, "metadata": None, "evidence": None},
    }
    if report is None:
        candidate["blockers"].append(_blocker(
            "validation_report_missing" if problem == "missing" else "validation_unreadable",
            "%s: %s" % (_rel(root, report_path) if report_path is not None else bare, problem)))
    else:
        if report.get("schema") != VALIDATION_SCHEMA:
            candidate["blockers"].append(_blocker(
                "validation_schema_unsupported",
                "schema is %r, expected %r" % (report.get("schema"), VALIDATION_SCHEMA)))
        static = report.get("static") if isinstance(report.get("static"), dict) else {}
        runtime = report.get("runtime") if isinstance(report.get("runtime"), dict) else {}
        static_status = static.get("status") or report.get("status")
        runtime_status = runtime.get("status")
        candidate["static_status"] = static_status
        candidate["runtime_status"] = runtime_status
        if static_status != REQUIRED_STATIC_STATUS:
            candidate["blockers"].append(_blocker(
                "static_not_pass", "static.status is %r, required %r" % (static_status, REQUIRED_STATIC_STATUS)))
        if runtime_status != REQUIRED_RUNTIME_STATUS:
            candidate["blockers"].append(_blocker(
                "runtime_not_gated", "runtime.status is %r, required %r" % (runtime_status, REQUIRED_RUNTIME_STATUS)))

    source = (report or {}).get("source") or {}
    staging, src, package = _source_locations(source.get("role"), source.get("path"), root)
    named = Path(root) / str(source.get("path")) if source.get("path") else None
    if report is not None and (package is None or named is None or not named.is_file()):
        candidate["blockers"].append(_blocker(
            "source_missing", "report source %r (role %r) is not a file in the tree"
            % (source.get("path"), source.get("role"))))
        return candidate
    if package is None:
        package = hint
        if package:
            staging = Path(root) / STAGING_REL / package
            src = None
    if package is None:
        return candidate
    src_package = _underscores(package)
    directory = staging if staging is not None else src
    files = _package_files(directory)
    sources, headers, tests = _partition(files)
    candidate["package"] = package
    candidate["src_package"] = src_package
    candidate["staging_dir"] = _rel(root, staging) if staging is not None else None
    candidate["src_dir"] = _rel(root, src) if src is not None else None
    candidate["sources"] = sources
    candidate["headers"] = headers
    candidate["tests"] = tests
    candidate["metadata"] = "%s/%s/%s.json" % (METADATA_REL, package, bare) if bare else None
    candidate["_files"] = files
    candidate["_package_dir"] = str(directory)

    record = _record(index, candidate["va"]) if bare else {}
    abi = record.get("abi") if isinstance(record.get("abi"), dict) else {}
    candidate["_record"] = record
    candidate["symbol"] = record.get("normalized_symbol") or record.get("name")
    candidate["subsystem"] = record.get("subsystem")
    candidate["_abi"] = {
        "calling_convention": abi.get("calling_convention"),
        "return_type": abi.get("return_type"),
        "stack_cleanup_bytes": abi.get("stack_cleanup_bytes"),
    }

    if report is not None:
        recorded = source.get("sha256")
        if not recorded:
            candidate["blockers"].append(_blocker(
                "validation_stale", "the report records no digest for %s" % source.get("path")))
        elif file_sha256(named) != recorded:
            candidate["blockers"].append(_blocker(
                "validation_stale", "%s no longer hashes to the digest the report observed" % source.get("path")))

    if not sources:
        candidate["blockers"].append(_blocker("no_sources", "package %s stages no non-test .cpp" % package))
    if not headers:
        candidate["blockers"].append(_blocker("no_header", "package %s stages no .hpp or .h" % package))
    if not tests:
        candidate["blockers"].append(_blocker("no_test", "package %s stages no %s file" % (package, TEST_SUFFIX)))

    if bare:
        _check_ownership(root, candidate, bare, claims, owners)

    if not candidate["metadata"]:
        candidate["blockers"].append(_blocker(
            "no_metadata_record", "no metadata record names a VA for package %s" % package))
    else:
        metadata, metadata_problem = _read_json(Path(root) / candidate["metadata"])
        if metadata is None and metadata_problem == "missing":
            candidate["blockers"].append(_blocker(
                "no_metadata_record", "%s does not exist" % candidate["metadata"]))
        elif metadata is None:
            candidate["blockers"].append(_blocker(
                "metadata_unreadable", "%s: %s" % (candidate["metadata"], metadata_problem)))

    text = ""
    for name in files:
        offender = _binary_offence(Path(directory) / name)
        if offender:
            candidate["blockers"].append(_blocker("binary_content", "%s %s" % (name, offender)))
            continue
        text += (Path(directory) / name).read_text(encoding="utf-8", errors="replace")
    if files and not _declares_namespace(text, src_package):
        candidate["blockers"].append(_blocker(
            "namespace_mismatch", "no namespace openspore::reconstruction::%s" % src_package))

    candidate["_digests"] = _digests_of(root, candidate)
    _check_installed(root, candidate, overwrite)
    return candidate


def _check_ownership(root, candidate, bare, claims, owners):
    # type: (Path, dict, str, dict, dict) -> None
    """Apply the reconciled ownership decision for this VA, if there is one.

    The default is this module's own refusal: ``duplicate_va`` whenever more
    than one package claims the VA, and again whenever some other installed
    package already promotes it. That is unchanged by anything here.

    What the reconciliation ledger adds runs in one direction only. When
    :func:`ownership.resolve` returns a decision -- which it does only after
    re-deriving the claimant set and re-taking every recorded input digest
    against the tree as it is now -- the canonical package loses its duplicate
    blocker and every other claimant gains a ``superseded_ownership`` blocker
    instead. An unreconciled, stale, newly-contested or differently-shaped
    ledger yields no decision, and this function does nothing at all.

    The ledger is consulted even when this module's own narrower staging-only
    claim view saw no contest, because the ledger's view is a superset: it also
    sees a package that owns the VA as canonical source in ``src/``, which is
    precisely the incumbent a fresh re-reconstruction must not displace. That
    asymmetry can only ever add a refusal, never remove one.
    """
    claimants = sorted(claims.get(bare, set()))
    foreign = sorted(owners.get(bare, set()) - {candidate["src_package"]})
    decision = ownership.resolve(root, bare)
    if decision.get("status") != "resolved":
        if len(claimants) > 1:
            candidate["blockers"].append(_blocker(
                "duplicate_va", "0x%s is claimed by %s" % (bare, ", ".join(claimants))))
        if foreign:
            candidate["blockers"].append(_blocker(
                "duplicate_va", "0x%s is already promoted by %s" % (bare, ", ".join(foreign))))
        return
    canonical = decision.get("canonical")
    package = candidate.get("package")
    candidate["ownership"] = {
        "canonical": canonical,
        "deciding_axis": decision.get("deciding_axis"),
        "superseded_by": None,
        "tied_on_rank": decision.get("tied_on_rank") or [],
        "claimants": decision.get("claimants") or [],
    }
    if ownership.same_package(package, canonical):
        # The canonical owner is clear. Whether the other claimants have been
        # re-arbitrated since is not decided here: ``resolve`` already
        # re-derived the full claimant set -- including installed owners and
        # src-resident incumbents, which this module's staging-only view does
        # not see -- and returned ``unresolved`` if it no longer matches. A
        # second, narrower re-check here would compare a different set against
        # the ledger and refuse canonical owners for losers the ledger already
        # adjudicated.
        return
    candidate["ownership"]["superseded_by"] = canonical
    candidate["blockers"].append(_blocker("superseded_ownership",
        "0x%s is owned by %s (reconciled on axis %r); %s is a recorded "
        "duplicate of it, and its source, metadata and evidence are retained "
        "under %s/%s"
        % (bare, canonical, decision.get("deciding_axis"), package,
           ownership.OWNERSHIP_REL, ownership.LEDGER_NAME)))


def _installed_files(src_dir):
    # type: (Path) -> dict
    found = {}
    for path in sorted(Path(src_dir).rglob("*")):
        if path.is_file():
            found[path.relative_to(src_dir).as_posix()] = path
    return found


def _check_installed(root, candidate, overwrite):
    # type: (Path, dict, bool) -> None
    """Compare the installed tree with what this promotion would reproduce.

    A directory with no ``promotion.json`` was never a deliberate promotion
    state -- discovery only reads marked directories -- so identical content
    is a crashed run to complete, and different content is a drifted tree
    that must not be overwritten silently.
    """
    src_dir = Path(root) / SRC_REL / candidate["src_package"]
    if not src_dir.is_dir():
        return
    installed = _installed_files(src_dir)
    candidate["_installed"] = installed
    package_dir = Path(candidate["_package_dir"])
    differs = [name for name in candidate["_files"]
               if name not in installed
               or installed[name].read_bytes() != (package_dir / name).read_bytes()]
    extra = sorted(set(installed) - set(candidate["_files"]) - {PROMOTION_NAME})
    if not differs and not extra:
        # The installed sources already are the promotion, marker or no
        # marker; a marker-less tree is a crashed run to finish.
        return
    if overwrite:
        return
    if extra:
        candidate["blockers"].append(_blocker(
            "would_drop_files", "%s holds files the promotion would not reproduce: %s"
            % (candidate["src_package"], ", ".join(extra))))
    if differs:
        candidate["blockers"].append(_blocker(
            "drifted_existing", "%s differs from staging in %s" % (candidate["src_package"], ", ".join(differs))))


def _public_candidate(candidate):
    # type: (dict) -> dict
    keys = ("va", "package", "src_package", "staging_dir", "sources", "headers",
            "tests", "static_status", "runtime_status", "promoted", "blockers")
    public = {key: candidate[key] for key in keys}
    if candidate.get("ownership"):
        public["ownership"] = candidate["ownership"]
    return public


def _flag_name_collisions(groups):
    # type: (dict) -> None
    """Refuse a group whose normalized name is shared by two staging packages.

    The normalization is lossy -- ``pkg-x-y`` and ``pkg_x_y`` both become
    ``pkg_x_y`` -- and the normalized name is a directory name, a CMake target
    name and the key the installed marker is grouped under. Two distinct
    staging packages landing on one name would be silently merged into a single
    installed package whose marker names only one of them, so the collision is
    a refusal rather than a last-writer-wins.
    """
    for key, group in groups.items():
        names = sorted(set(candidate["package"] for candidate in group
                           if candidate["package"]))
        if len(names) < 2:
            continue
        detail = "%s is the normalized name of %s" % (key, ", ".join(names))
        for candidate in group:
            candidate["blockers"].append(_blocker("src_package_collision", detail))


def _load_candidates(root, package=None, va=None, overwrite=False):
    # type: (Path, object, object, bool) -> list
    reports = _validation_reports(root)
    index = _index_records(root)
    claims = _va_claims(root, reports)
    owners = _promoted_va_owners(root)
    wanted_package = _resolve_package(package)[0]
    wanted_va = None if va is None else _bare(va)
    candidates = []
    for bare, hint in _discovery(root):
        if wanted_va is not None and bare != wanted_va:
            continue
        candidate = _candidate(root, bare, hint, index, claims, owners, overwrite)
        if wanted_package is not None and candidate["package"] != wanted_package:
            continue
        candidates.append(candidate)
    groups = {}
    for candidate in candidates:
        key = candidate["src_package"] or candidate["package"] or candidate["va"]
        groups.setdefault(key, []).append(candidate)
    _flag_name_collisions(groups)
    for group in groups.values():
        # Identity is a property of the whole installed package: the marker
        # holds every target, so it can only be compared as a unit.
        identical = _identical(root, group)[0]
        for candidate in group:
            candidate["promoted"] = identical
    return candidates


def _plan_document(candidates):
    # type: (list) -> dict
    public = [_public_candidate(candidate) for candidate in candidates]
    eligible = [item for item in public if not item["blockers"]]
    return {
        "schema": PLAN_SCHEMA,
        "ok": True,
        "candidates": public,
        "summary": {
            "candidates": len(public),
            "eligible": len(eligible),
            "promoted": len([item for item in eligible if item["promoted"]]),
            "refused": len([item for item in public if item["blockers"]]),
        },
    }


def plan(root=ROOT, package=None, va=None):
    # type: (Path, object, object) -> dict
    """Read-only. Decide what a promotion would do and refuse what it would not.

    Writes nothing, creates no scratch directory, takes no timestamp, and
    opens no file for writing. ``ok`` reports that the plan itself ran; a
    refused candidate does not make it False.
    """
    return _plan_document(_load_candidates(Path(root), package=package, va=va))


def promoted_packages(root=ROOT):
    # type: (Path) -> list
    """Every src package carrying a promotion marker, sorted.

    A directory counts only when its marker is a real one -- frozen schema and
    a buildable ``src_package`` -- so this agrees with
    ``build_gate.discover_packages`` and with the ``*/promotion.json`` glob in
    ``src/reconstruction/CMakeLists.txt``. An interrupted promotion's scratch,
    lock and recovery trees are dotted and carry no marker, so they are absent
    here as they are from the build.
    """
    base = Path(root) / SRC_REL
    if not base.is_dir():
        return []
    return sorted(entry.name for entry in base.iterdir()
                  if entry.is_dir() and not entry.name.startswith(".")
                  and _promoted_marker(entry / PROMOTION_NAME))


def package_state(root, package):
    # type: (Path, object) -> dict
    """What is known about one package, addressed by either spelling."""
    root = Path(root)
    dashed, src_package = _resolve_package(package)
    if dashed is None:
        raise ValueError("a package is required")
    staging = Path(root) / STAGING_REL / dashed
    document = _promoted_marker(Path(root) / SRC_REL / src_package / PROMOTION_NAME)
    candidates = _load_candidates(root, package=dashed)
    return {
        "package": dashed,
        "src_package": src_package,
        "staging_dir": _rel(root, staging) if staging.is_dir() else None,
        "exists": staging.is_dir(),
        "promoted": bool(document),
        "targets": [{
            "va": candidate["va"],
            "symbol": candidate.get("symbol"),
            "subsystem": candidate.get("subsystem"),
            "static_status": candidate["static_status"],
            "runtime_status": candidate["runtime_status"],
            "promoted": candidate["promoted"],
            "blockers": candidate["blockers"],
        } for candidate in candidates],
    }


def _target_document(root, candidate):
    # type: (Path, dict) -> dict
    """One entry of ``src/reconstruction/<pkg>/promotion.json``."""
    bare = candidate["bare_va"]
    digests = candidate["_digests"]
    evidence_rel = "%s/%s/%s" % (EVIDENCE_REL, bare, EVIDENCE_NAME)
    evidence, _problem = _read_json(Path(root) / evidence_rel)
    binary = evidence.get("binary") if isinstance(evidence, dict) else None
    return {
        "va": candidate["va"],
        "bare_va": bare,
        "symbol": candidate.get("symbol"),
        "subsystem": candidate.get("subsystem"),
        "sources": sorted(candidate["sources"]),
        "headers": sorted(candidate["headers"]),
        "tests": sorted(candidate["tests"]),
        "staging_dir": candidate["staging_dir"],
        "staging_sha256": dict(digests.get("files") or {}),
        "metadata": candidate["metadata"],
        "metadata_sha256": digests.get("metadata"),
        "validation": "%s/%s/%s" % (EVIDENCE_REL, bare, VALIDATION_NAME),
        "validation_sha256": digests.get("validation"),
        "evidence": evidence_rel,
        "evidence_sha256": digests.get("evidence"),
        "static_status": candidate["static_status"],
        "runtime_status": candidate["runtime_status"],
        # Copied verbatim, never synthesised: a promoted package has an open
        # runtime gate, and this is the report's own wording of that fact.
        "runtime_validation": (candidate.get("_report") or {}).get("runtime"),
        "binary_sha256": binary.get("sha256") if isinstance(binary, dict) else None,
        "abi": dict(candidate.get("_abi") or {}),
    }


def _package_document(root, candidates, previous=None):
    # type: (Path, list, object) -> dict
    document = {
        "schema": PACKAGE_SCHEMA,
        "package": candidates[0]["package"],
        "src_package": candidates[0]["src_package"],
        "namespace": "openspore::reconstruction::%s" % candidates[0]["src_package"],
        "targets": sorted((_target_document(root, candidate) for candidate in candidates),
                          key=lambda target: target["bare_va"]),
    }
    if previous is not None:
        document["supersedes"] = previous
    return document


def _identical(root, candidates):
    # type: (Path, list) -> tuple
    """Is the installed tree exactly what this promotion would write?

    Compares the would-be marker bytes and the source digests, so a package
    that was edited in ``src/`` after promotion is not mistaken for an
    already-promoted one.
    """
    candidate = candidates[0]
    if not candidate["src_package"]:
        return False, None
    src_dir = Path(root) / SRC_REL / candidate["src_package"]
    marker = src_dir / PROMOTION_NAME
    if not marker.is_file():
        return False, None
    document, _problem = _read_json(marker)
    if document is None:
        return False, None
    planned = _package_document(root, candidates, document.get("supersedes"))
    if canonical_json(planned) != marker.read_text(encoding="utf-8"):
        return False, document
    digests = candidate["_digests"].get("files") or {}
    if not digests:
        return False, document
    expected = set(digests)
    for name in sorted(expected):
        path = src_dir / name
        if not path.is_file() or file_sha256(path) != digests[name]:
            return False, document
    installed = set(_installed_files(src_dir))
    if installed - expected - {PROMOTION_NAME}:
        return False, document
    return True, document


def _scratch(root):
    # type: (Path) -> Path
    """A private scratch tree beside the packages it may replace.

    Dotted so no ``src/reconstruction/*`` glob sees it, and inside
    ``src/reconstruction/`` so that installing is a same-filesystem rename
    rather than a copy that could be interrupted half way.

    The name *ends* in the owner's pid because that is the only thing
    :func:`_sweep_scratch` can read back out of a directory name.
    ``tempfile.mkdtemp`` names do not end in one, so every tree it made looked
    ownerless and a *live* run's tree was swept out from under it by the next
    run -- the opposite of what the sweep promises.
    """
    holder = Path(root) / SRC_REL / SCRATCH_NAME
    holder.mkdir(parents=True, exist_ok=True)
    try:
        _sweep_scratch(holder)
        for _attempt in range(64):
            candidate = holder / ("%s.%d" % (os.urandom(4).hex(), os.getpid()))
            try:
                os.mkdir(str(candidate))
            except FileExistsError:
                continue
            except OSError:
                return Path(tempfile.mkdtemp(dir=str(holder)))
            return candidate
    except BaseException:
        # The holder was created before anything could fail in it, so a run
        # that dies here would otherwise be the one run that leaves a trace
        # under src/ for a promotion that wrote nothing.
        _drop_scratch(holder)
        raise
    raise OSError("could not create a scratch tree under %s" % holder)


def _alive(pid):
    # type: (int) -> bool
    try:
        os.kill(pid, 0)
    except ProcessLookupError:
        return False
    except OSError:
        return True
    return True


def _sweep_scratch(holder):
    # type: (Path) -> None
    """Drop scratch trees left by a run whose process is gone.

    A live run's tree is never touched, so two concurrent promotions cannot
    delete each other's work. The name convention is the one :func:`_scratch`
    writes: ``<pid>.<random>``.
    """
    for entry in sorted(holder.iterdir()):
        if not entry.is_dir():
            continue
        owner = entry.name.rsplit(".", 1)[-1]
        if owner.isdigit() and _alive(int(owner)):
            continue
        shutil.rmtree(entry, ignore_errors=True)


def _drop_scratch(scratch):
    # type: (Path) -> None
    """Remove the scratch tree, then the holder if it is now empty.

    A run that leaves no trace under ``src/`` is part of the promise that a
    refused promotion writes nothing. ``rmdir`` on the holder fails while a
    concurrent run holds a tree inside it, which is the safe outcome.
    """
    shutil.rmtree(scratch, ignore_errors=True)
    try:
        scratch.parent.rmdir()
    except OSError:
        pass


def _lock_is_live(holder):
    # type: (Path) -> bool
    """Is the promotion holding this lock still running?

    A lock whose owner file is not there yet belongs to a thread that is
    between ``mkdir`` and the write, so it counts as live and the reader waits
    rather than stealing.
    """
    owner = holder / LOCK_OWNER
    try:
        pid = int(owner.read_text(encoding="utf-8").strip())
    except (OSError, ValueError):
        return True
    return _alive(pid)


def _acquire_package_lock(root, src_package, timeout=None):
    # type: (Path, str, object) -> object
    """Take an exclusive, crash-tolerant lock on one package's install.

    ``os.mkdir`` is the atomic primitive, so exactly one promotion of a
    package runs at a time. The lock is per package, never global, so two
    promotions of different packages never wait on each other. A lock whose
    owner process is gone is stolen rather than waited on, so a killed run
    cannot wedge a package; the same pid-reuse caveat as :func:`_sweep_scratch`
    applies. Returns the lock directory, or None when the wait ran out.
    """
    holder = Path(root) / SRC_REL / (LOCK_PREFIX + src_package)
    holder.parent.mkdir(parents=True, exist_ok=True)
    deadline = time.time() + (LOCK_TIMEOUT if timeout is None else timeout)
    while True:
        try:
            os.mkdir(str(holder))
        except FileExistsError:
            if not _lock_is_live(holder):
                shutil.rmtree(str(holder), ignore_errors=True)
                continue
            if time.time() >= deadline:
                return None
            time.sleep(LOCK_POLL)
        except OSError:
            return None
        else:
            try:
                (holder / LOCK_OWNER).write_text("%d\n" % os.getpid(), encoding="utf-8")
            except OSError:
                shutil.rmtree(str(holder), ignore_errors=True)
                return None
            return holder


def _release_package_lock(holder):
    # type: (object) -> None
    """Give up a lock taken by :func:`_acquire_package_lock`."""
    if holder is None:
        return
    shutil.rmtree(str(holder), ignore_errors=True)


def _stage_tree(scratch, candidate):
    # type: (Path, dict) -> Path
    """Copy exactly the files that will be promoted into a scratch install tree."""
    install = scratch / "install"
    install.mkdir(parents=True)
    origin = Path(candidate["_package_dir"])
    for name in candidate["_files"]:
        if Path(name).suffix not in SOURCE_SUFFIXES:
            raise AssertionError("refusing to promote %s: not a source suffix" % name)
        destination = install / name
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(origin / name, destination)
    return install


def _gate_module():
    # type: () -> object
    """The build-gate module, or an ImportError naming why it is unavailable.

    The single seam both :func:`apply` and :func:`_gate` go through, so the
    pre-flight verdict and the gate that actually runs can never disagree about
    whether a gate exists.

    Resolution order is the package attribute, then the dotted ``sys.modules``
    entry, then a real import -- which is exactly what ``from . import
    build_gate`` does, and it is the order callers that inject a substitute
    module rely on. Note the consequence: a substitute left bound to the
    package attribute by a previous run is indistinguishable from the real
    module, so a test that swaps the gate in place must put it back. This
    module cannot detect that, and does not pretend to.
    """
    holder = sys.modules[__package__]
    module = getattr(holder, "build_gate", None)
    if module is None:
        module = importlib.import_module(".build_gate", __package__)
    if not hasattr(module, "gate"):
        raise ImportError("build_gate exposes no gate()")
    return module


def _gate(root, scratch, src_package, build, ctest, build_dir, jobs):
    # type: (Path, Path, str, bool, bool, object, object) -> dict
    """Compile and test the exact bytes about to be installed, in scratch.

    The gate is the authority on a promotion, so it is run through the same
    CMake path the real build uses: the mirror is a minimal project whose
    ``src/reconstruction`` holds this repository's own reconstruction
    CMakeLists plus exactly the install tree, and the repo's CMakeLists is
    copied verbatim rather than imitated. Nothing is written under the real
    ``src/``, and a red configure, compile or ctest leaves the destination
    untouched.
    """
    if not build and not ctest:
        return {"schema": BUILD_SCHEMA, "ok": True, "steps": [], "packages": {},
                "note": "gate skipped by request"}
    build_gate = _gate_module()
    gate_root = _gate_mirror(root, scratch, src_package)
    result = build_gate.gate(str(gate_root), packages=[src_package],
                             build_dir=str(build_dir or (scratch / "build")), jobs=jobs)
    if not isinstance(result, dict):
        raise ValueError("build gate returned %r, not a dict" % type(result).__name__)
    return result


def _gate_mirror(root, scratch, src_package):
    # type: (Path, Path, str) -> Path
    """Build the throwaway project the gate configures.

    Its layout is the real one -- ``src/reconstruction/<pkg>/promotion.json``
    -- so the gate's own package discovery finds the candidate, and the
    repository's ``src/reconstruction/CMakeLists.txt`` is copied rather than
    reimplemented, so the gate cannot pass on a weaker build than the one the
    real tree performs. A repository without that file yields a project with
    no reconstruction subdirectory, and the gate then reports no test rows and
    refuses, which is the honest outcome.
    """
    gate_root = scratch / "gate-root"
    reconstruction = gate_root / "src" / "reconstruction"
    package_dir = reconstruction / src_package
    package_dir.mkdir(parents=True, exist_ok=True)
    for name in _package_files(scratch / "install"):
        destination = package_dir / name
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(scratch / "install" / name, destination)
    shutil.copyfile(scratch / "install" / PROMOTION_NAME, package_dir / PROMOTION_NAME)
    entry = Path(root) / "src" / "reconstruction" / "CMakeLists.txt"
    if entry.is_file():
        shutil.copyfile(entry, reconstruction / "CMakeLists.txt")
        (gate_root / "src" / "CMakeLists.txt").write_text("add_subdirectory(reconstruction)\n",
                                                          encoding="utf-8")
    (gate_root / "CMakeLists.txt").write_text(GATE_PROJECT, encoding="utf-8")
    return gate_root


def _install(root, src_package, install, scratch):
    # type: (Path, str, Path, Path) -> list
    """Move a fully-built tree into place; return the files it dropped.

    A package that does not exist yet is installed by ``os.replace`` of a
    sibling directory, so the destination appears whole or not at all. A
    package that does exist is renamed aside into the scratch tree first, so
    the only interruption window is a rename, and the destination is then
    either the new tree, the old tree under ``superseded/`` in scratch, or
    absent. No reader can ever observe a half-written package, and a re-run
    rebuilds from staging in every case.

    A failure of the second rename is the one window in which the previous
    tree exists nowhere else, so it is put back before the error propagates
    (see :func:`_restore_superseded`). Without that the caller's ``finally``
    would delete the only copy along with the rest of the scratch tree.
    """
    destination = Path(root) / SRC_REL / src_package
    destination.parent.mkdir(parents=True, exist_ok=True)
    dropped = []
    if destination.exists():
        dropped = sorted(_installed_files(destination))
        os.replace(destination, scratch / "superseded")
    try:
        os.replace(install, destination)
    except OSError as failure:
        recovery = _restore_superseded(destination, scratch)
        if recovery:
            raise OSError("%s; the previous tree is at %s" % (failure, recovery))
        raise
    return [name for name in dropped if name not in _installed_files(destination)]


def _restore_superseded(destination, scratch):
    # type: (Path, Path) -> str
    """Put the previous package tree back after a failed install.

    Returns the recovery path when the old tree could not be returned to the
    destination and was moved to ``src/reconstruction/.promote-lost/<pkg>``
    instead, so that the caller's scratch cleanup cannot destroy it. Empty
    string when the restore succeeded or when there was nothing to restore.
    """
    previous = Path(scratch) / "superseded"
    if not previous.is_dir():
        return ""
    if not destination.exists():
        try:
            os.replace(previous, destination)
            return ""
        except OSError:
            pass
    recovery = Path(destination).parent / LOST_NAME / Path(destination).name
    try:
        recovery.parent.mkdir(parents=True, exist_ok=True)
        shutil.rmtree(str(recovery), ignore_errors=True)
        os.replace(previous, recovery)
    except OSError:
        return ""
    return str(recovery)


def _record_document(root, candidate, build):
    # type: (Path, dict, object) -> dict
    target = _target_document(root, candidate)
    inputs = [target["staging_dir"] and "%s/%s" % (STAGING_REL, candidate["package"]),
              target["metadata"], target["validation"], target["evidence"], INDEX_REL]
    previous, _problem = _read_json(Path(root) / EVIDENCE_REL / candidate["bare_va"] / PROMOTION_NAME)
    return {
        "schema": RECORD_SCHEMA,
        "va": target["va"],
        "bare_va": target["bare_va"],
        "package": candidate["package"],
        "src_package": candidate["src_package"],
        "namespace": "openspore::reconstruction::%s" % candidate["src_package"],
        "sources": target["sources"],
        "headers": target["headers"],
        "tests": target["tests"],
        "staging_dir": target["staging_dir"],
        "staging_sha256": target["staging_sha256"],
        "metadata": target["metadata"],
        "metadata_sha256": target["metadata_sha256"],
        "validation": target["validation"],
        "validation_sha256": target["validation_sha256"],
        "evidence": target["evidence"],
        "evidence_sha256": target["evidence_sha256"],
        "static_status": target["static_status"],
        "runtime_status": target["runtime_status"],
        "build": build,
        "promoted_on": datetime.now(timezone.utc).strftime("%Y-%m-%d"),
        "provenance": [name for name in inputs if name and (Path(root) / name).exists()],
        "supersedes": previous,
    }


def _write_record(root, candidate, build):
    # type: (Path, dict, object) -> bool
    """Write the provenance record for one VA; single atomic replace each."""
    path = Path(root) / EVIDENCE_REL / candidate["bare_va"] / PROMOTION_NAME
    document = _record_document(root, candidate, build)
    payload = canonical_json(document)
    if path.is_file() and path.read_text(encoding="utf-8") == payload:
        return False
    write_json_atomic(path, document)
    return True


def _merge_build(results):
    # type: (dict) -> object
    live = {name: value for name, value in results.items() if isinstance(value, dict)}
    if not live:
        return None
    steps = []
    packages = {}
    tests = {}
    schema = BUILD_SCHEMA
    for name in sorted(live):
        result = live[name]
        schema = result.get("schema", schema)
        steps.extend(result.get("steps", []) or [])
        packages.update(result.get("packages", {}) or {})
        for row in result.get("tests", []) or []:
            if isinstance(row, dict) and row.get("name"):
                tests[row["name"]] = row
    return {"schema": schema,
            "ok": all(bool(result.get("ok")) for result in live.values()),
            "steps": steps, "tests": [tests[name] for name in sorted(tests)],
            "packages": packages}


def _refuse(result, group, code, detail):
    # type: (dict, list, str, str) -> None
    for candidate in group:
        candidate["blockers"].append(_blocker(code, detail))
        result["refused"].append({"va": candidate["va"], "package": candidate["package"],
                                  "blockers": candidate["blockers"]})
    result["status"] = "blocked"


def _promote_package(root, group, result, build, ctest, build_dir, jobs, rebuild):
    # type: (Path, list, dict, bool, bool, object, object, bool) -> dict
    """Install one package: re-verify, gate in scratch, then replace.

    Held under an exclusive per-package lock for its whole duration, including
    the identity check, so two concurrent promotions of the same package cannot
    both install: the second one waits, and then observes the first one's tree
    and reports it as already promoted.
    """
    candidate = group[0]
    src_package = candidate["src_package"]
    lock = _acquire_package_lock(root, src_package)
    if lock is None:
        _refuse(result, group, "package_locked",
                "another promotion holds the install lock for %s" % src_package)
        return {"build": None}

    scratch = None
    try:
        identical, marker = _identical(root, group)
        if identical and not rebuild:
            # The recorded build result is returned rather than recomputed: a
            # re-run that changes nothing must not spend a compile, and must not
            # restate a gate the caller did not ask for. A missing record is the
            # one case that writes, because it means the install landed and the
            # provenance write did not.
            previous, _problem = _read_json(
                Path(root) / EVIDENCE_REL / candidate["bare_va"] / PROMOTION_NAME)
            recorded = previous.get("build") if isinstance(previous, dict) else None
            changed = False
            if previous is None:
                for item in group:
                    changed = _write_record(root, item, recorded) or changed
            if changed:
                result["changed"] = True
                result["idempotent"] = False
            for item in group:
                result["already_promoted"].append(item["va"])
            result["packages"].append({"package": candidate["package"], "src_package": src_package,
                                       "status": "already_promoted", "build": recorded})
            return {"build": recorded}

        fresh = _digests_of(root, candidate)
        if fresh != candidate["_digests"]:
            _refuse(result, group, "inputs_changed", "inputs moved under the promotion; nothing was written")
            return {"build": None}

        scratch = _scratch(root)
        install = _stage_tree(scratch, candidate)
        write_json_atomic(install / PROMOTION_NAME,
                          _package_document(root, group, (marker or {}).get("supersedes")))
        gate = _gate(root, scratch, src_package, build, ctest, build_dir, jobs)
        if not gate.get("ok"):
            _refuse(result, group, "package_refused", "the build gate reported ok=false; nothing was written to src/")
            return {"build": gate}
        dropped = _install(root, src_package, install, scratch)
        if dropped:
            result["overwritten"][src_package] = dropped
        try:
            for item in group:
                _write_record(root, item, gate)
        except Exception as exc:
            # The install is finished and correct, so this is not a failed
            # promotion: src/ holds exactly the tree the gate approved. Only
            # the provenance side is missing, and the next run writes it (the
            # already_promoted branch is written for that case alone). Reporting
            # an error here would be a false statement about src/.
            result["warnings"].append({
                "va": candidate["va"],
                "code": "promotion_record_unwritten",
                "detail": "%s: %s" % (type(exc).__name__, exc),
            })
    except ImportError as exc:
        return {"error": "build_gate_unavailable", "detail": str(exc)}
    except Exception as exc:
        # Anything the gate or the filesystem raises is an error, never a
        # promotion: the destination is untouched until the gate is green, and
        # the package is all-or-nothing once the install starts -- either the
        # new tree is there or the old one was put back.
        return {"error": "promotion_failed", "detail": "%s: %s" % (type(exc).__name__, exc)}
    finally:
        if scratch is not None:
            _drop_scratch(scratch)
        _release_package_lock(lock)
    for item in group:
        result["promoted"].append(item["va"])
    result["changed"] = True
    result["idempotent"] = False
    result["packages"].append({"package": candidate["package"], "src_package": src_package,
                               "status": "promoted", "build": gate, "overwritten": dropped})
    return {"build": gate}


def apply(root=ROOT, package=None, va=None, overwrite=False, build=True, ctest=True,
          build_dir=None, jobs=None, rebuild=False):
    # type: (Path, object, object, bool, bool, bool, object, object, bool) -> dict
    """Promote every eligible package; all-or-nothing per package.

    ``rebuild`` re-runs the gate for a package that is already promoted and
    byte-identical. By default such a package is left untouched and its last
    recorded gate result is returned instead.
    """
    root = Path(root)
    candidates = _load_candidates(root, package=package, va=va, overwrite=overwrite)
    snapshot = _plan_document(candidates)
    result = {
        "schema": RESULT_SCHEMA,
        "status": "ok",
        "changed": False,
        "idempotent": True,
        "promoted": [],
        "already_promoted": [],
        "refused": [],
        "build": None,
        "packages": [],
        "overwritten": {},
        "warnings": [],
        "summary": {},
    }
    if build or ctest:
        try:
            _gate_module()
        except ImportError as exc:
            result["status"] = "error"
            result["code"] = "build_gate_unavailable"
            result["detail"] = str(exc)
            result["summary"] = _summary(snapshot, result, 0)
            return result

    groups = {}
    for candidate in candidates:
        key = candidate["src_package"] or candidate["package"] or candidate["va"]
        groups.setdefault(key, []).append(candidate)

    builds = {}
    for key in sorted(groups):
        group = groups[key]
        refused = [candidate for candidate in group if candidate["blockers"]]
        if refused:
            reasons = sorted({item["code"] for candidate in refused for item in candidate["blockers"]})
            for candidate in group:
                if not candidate["blockers"]:
                    candidate["blockers"].append(_blocker(
                        "sibling_refused", "package %s is refused by %s" % (key, ", ".join(reasons))))
                result["refused"].append({"va": candidate["va"], "package": candidate["package"],
                                          "blockers": candidate["blockers"]})
            result["status"] = "blocked"
            continue
        outcome = _promote_package(root, group, result, build, ctest, build_dir, jobs, rebuild)
        builds[key] = outcome.get("build")
        if outcome.get("error"):
            result["status"] = "error"
            result["code"] = outcome["error"]
            result["detail"] = outcome.get("detail")
            result["summary"] = _summary(snapshot, result, len(groups))
            return result
    result["build"] = _merge_build(builds)
    if result["refused"]:
        result["status"] = "blocked"
    result["summary"] = _summary(snapshot, result, len(groups))
    return result


def _summary(snapshot, result, packages):
    # type: (dict, dict, int) -> dict
    return {
        "candidates": snapshot["summary"]["candidates"],
        "eligible": snapshot["summary"]["eligible"],
        "promoted": len(result["promoted"]),
        "already_promoted": len(result["already_promoted"]),
        "refused": len(result["refused"]),
        "packages": packages,
    }
