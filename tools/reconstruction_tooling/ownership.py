"""Deterministic reconciliation of duplicate VA ownership.

Many independently reconstructed packages can correspond to the same VA. The
promotion gate refuses that (``promote.BLOCKERS["duplicate_va"]``) because two
installed packages claiming one function is not a state the tree can be in:
one canonical identity, one set of sources. That refusal is correct and this
module does not weaken it. What it adds is the thing the refusal was missing --
a *reasoned* way to pick the one identity, recorded so that the choice is
auditable and so that the losing package's work is not thrown away.

Three properties define the policy:

* **Objective ranking, not recency.** Ownership is decided by a fixed, ordered
  list of evidence axes (:data:`AXES`). Every axis reads a persisted artifact
  and produces an integer; the winner is the maximum of the lexicographic
  tuple. Wall-clock timestamps are *never* an input. They are recorded under
  ``diagnostics`` and are explicitly excluded from the comparison key, so
  touching a file cannot change a decision.
* **Nothing is destroyed.** ``apply`` writes one ledger file. It never moves,
  renames or deletes a staging directory, a metadata handoff, an evidence pack
  or a source file. A superseded package keeps every artifact it had; what it
  loses is *the claim*, and the ledger records the claim's full provenance --
  the digests, the comparison that lost it, and the identity that won -- under
  ``superseded[]``.
* **Fail-safe on read.** :func:`resolve` returns a decision only when the
  ledger is internally consistent *and* still describes the tree: the
  recorded claimant set must equal the claimant set observed now, and every
  recorded input digest must still hash to what it hashed when the decision
  was made. Anything else -- a new claimant, an edited source, a missing
  canonical directory, an unknown schema -- yields ``None``, and the caller
  falls back to refusing with ``duplicate_va``. A ledger can therefore never
  become a blanket waiver.

The canonicalization rule in one line: *the claimant with the greatest
``(settled, validation, build_gate, evidence, completeness, provenance,
metadata_coherence)`` tuple wins; exact ties are broken by ascending package
name, which arbitrates identity deterministically and asserts nothing about
quality.*

This module changes no validation criterion, no ABI inference rule, and no
return semantics. It reads what other modules already wrote and adds a
recorded adjudication layer on top.
"""

import os
import re
from pathlib import Path

from .models import (ROOT, ToolError, canonical_json, file_sha256, load_json,
                     normalize_va, sha256_bytes, write_json_atomic)

LEDGER_SCHEMA = "openspore-va-ownership-1"
INVENTORY_SCHEMA = "openspore-ownership-inventory-1"
RECONCILIATION_SCHEMA = "openspore-ownership-reconciliation-1"

OWNERSHIP_REL = "reconstruction/ownership"
LEDGER_NAME = "ownership.json"
INDEX_REL = "reconstruction/knowledge/index.json"
MANIFEST_REL = "knowledgegraph/research/source-reconstruction-manifest.json"
EVIDENCE_REL = "reconstruction/evidence"
STAGING_REL = "reconstruction/staging"
METADATA_REL = "reconstruction/metadata"
SRC_REL = "src/reconstruction"
VALIDATION_NAME = "validation.json"
EVIDENCE_NAME = "evidence.json"
PROMOTION_NAME = "promotion.json"
BUILD_GATE_SCHEMA = "openspore-build-gate-1"
PROMOTION_SCHEMA = "openspore-promotion-1"
# The rule src/reconstruction/CMakeLists.txt applies to a src_package before it
# becomes a target name. Mirrors promote.SRC_NAME_RE so an installed directory
# this module counts as an owner is one the build would also accept.
SRC_NAME_RE = re.compile(r"^[A-Za-z0-9_]+$")
TEST_SUFFIX = "_test.cpp"
SOURCE_SUFFIXES = (".cpp", ".hpp", ".h")
# A bare 8-hex-digit run, not adjacent to more hex. Mirrors promote.VA_TOKEN so
# both modules agree on which staged filenames constitute a VA claim.
VA_TOKEN = re.compile(r"(?<![0-9a-zA-Z])(?:0x)?([0-9a-f]{8})(?![0-9a-zA-Z])")

# The ordered evidence axes. Order is precedence: earlier axes dominate
# completely, so a package that is already the settled integrated owner of a VA
# cannot be displaced by a package that merely validates better.
AXES = (
    "settled",
    "validation",
    "build_gate",
    "evidence",
    "completeness",
    "provenance",
    "metadata_coherence",
)

# The reported name for "every evidence axis is equal". Not an axis: it is the
# documented identity tiebreak, and it carries no quality claim.
TIE_BREAK = "package_name_order"

# Static status -> rank. Absent or unknown statuses rank 0, never above a
# status the validator actually emitted.
STATIC_RANK = {"PASS": 4, "WARN": 3, "UNKNOWN": 2, "NOT_AVAILABLE": 1}
# Evidence levels the knowledge index uses, strongest first. Anything else
# (or absence) ranks 0 -- an unrecognised label is not treated as strength.
EVIDENCE_LEVEL_RANK = {"OBSERVED": 2, "SUPPORTED": 1}
INTEGRITY_VERIFIED = "verified"

PROBLEMS = frozenset({
    "ledger_missing",
    "ledger_unreadable",
    "ledger_schema_unsupported",
    "entry_va_mismatch",
    "canonical_absent",
    "claimants_changed",
    "installed_conflict",
    "inputs_changed",
    "no_entry",
})


def _bare(value):
    # type: (object) -> str
    return normalize_va(value)[2:]


def _dashes(value):
    # type: (object) -> str
    return str(value).replace("_", "-").lower()


def _underscores(value):
    # type: (object) -> str
    return str(value).replace("-", "_").lower()


def same_package(left, right):
    # type: (object, object) -> bool
    """Compare package names in any of the spellings the tree uses.

    The tree is not consistent about one thing: a staging directory is dashed
    and lower case (``pkg-dfw-006a1540``), an installed directory is
    underscored (``pkg_dfw_006a1540``), a manifest ``package`` is usually
    shouted (``PKG-DFW-006A1540``), and a promotion marker carries the
    underscored form. Comparing them with ``==`` would miss an installed owner
    that is in fact the same package, which is the one comparison that must
    never be missed.
    """
    if not left or not right:
        return False
    left_spellings = {_dashes(left), _underscores(left), str(left).strip().lower()}
    right_spellings = {_dashes(right), _underscores(right), str(right).strip().lower()}
    return bool(left_spellings & right_spellings)


def _rel(root, path):
    # type: (Path, object) -> str
    try:
        return str(Path(path).resolve().relative_to(Path(root).resolve())).replace(os.sep, "/")
    except (OSError, ValueError):
        return str(path).replace(os.sep, "/")


def _read_json(path):
    # type: (Path) -> tuple
    """``(document, problem)``; ``problem`` is ``None``, ``"missing"`` or a text."""
    path = Path(path)
    if not path.is_file():
        return None, "missing"
    try:
        document = load_json(path)
    except (OSError, ValueError) as exc:
        return None, str(exc)
    if not isinstance(document, dict):
        return None, "document is not an object"
    return document, None


def ledger_path(root=ROOT):
    # type: (Path) -> Path
    return Path(root) / OWNERSHIP_REL / LEDGER_NAME


# ---------------------------------------------------------------------------
# Claim discovery
# ---------------------------------------------------------------------------


def _package_files(directory):
    # type: (Path) -> list
    base = Path(directory)
    if not base.is_dir():
        return []
    found = [path.relative_to(base).as_posix() for path in base.rglob("*")
             if path.is_file() and path.suffix in SOURCE_SUFFIXES]
    return sorted(found)


def _partition(files):
    # type: (list) -> tuple
    sources = [n for n in files if n.endswith(".cpp") and not n.endswith(TEST_SUFFIX)]
    headers = [n for n in files if n.endswith((".hpp", ".h"))]
    tests = [n for n in files if n.endswith(".cpp") and n.endswith(TEST_SUFFIX)]
    return sources, headers, tests


def _staging_packages(root):
    # type: (Path) -> list
    base = Path(root) / STAGING_REL
    if not base.is_dir():
        return []
    return sorted(entry.name for entry in base.iterdir() if entry.is_dir())


def claimant_map(root):
    # type: (Path) -> dict
    """VA -> sorted package names that claim it.

    Four redundant signals, deliberately the same ones
    :func:`promote._va_claims` uses, so this module and the gate can never
    disagree about what "a claim" is:

    * a metadata handoff ``metadata/<pkg>/<bare8>.json``;
    * a staged filename carrying the bare VA;
    * a persisted validation report whose ``source.path`` is inside
      ``staging/<pkg>/``;
    * a persisted validation report whose ``source.path`` is inside
      ``src/reconstruction/<pkg>/`` -- an *installed* claim, which is the one
      that matters most, because canonical source in ``src/`` is what a
      duplicate would collide with.

    A metadata handoff counts when the package it names can actually hold an
    identity: it is staged, it is src-resident, or the canonical manifest
    records it for that VA. A handoff for a package whose directory is gone and
    which nothing else claims is historical bookkeeping, not a claim -- scoring
    it would invent a claimant that no artifact backs.
    """
    root = Path(root)
    claims = {}

    def add(va, package):
        # type: (object, object) -> None
        if package:
            try:
                claims.setdefault(_bare(va), set()).add(str(package))
            except ValueError:
                return

    evidence = root / EVIDENCE_REL
    if evidence.is_dir():
        for entry in sorted(evidence.iterdir()):
            report, problem = _read_json(entry / VALIDATION_NAME)
            if report is None:
                continue
            source = report.get("source") or {}
            path = str(source.get("path") or "")
            for marker in (STAGING_REL + "/", SRC_REL + "/"):
                if path.startswith(marker):
                    add(_entry_bare(entry.name),
                        _dashes(path[len(marker):].split("/", 1)[0]))
    staged = _staging_packages(root)
    for package in staged:
        metadata = root / METADATA_REL / package
        if metadata.is_dir():
            for record in metadata.glob("*.json"):
                add(record.stem, package)
        for name in _package_files(root / STAGING_REL / package):
            for match in VA_TOKEN.finditer(name):
                add(match.group(1), package)
    # Metadata for a package the loop above did not reach: one that is
    # src-resident, or that the canonical manifest records for the VA. Those
    # are real owners whose handoff is the only thing left of them, so the
    # handoff has to be readable as a claim.
    known = set(staged) | set(_src_resident_packages(root))
    for bare, names in manifest_packages(root).items():
        known.update(_dashes(name) for name in names)
    metadata_root = root / METADATA_REL
    if metadata_root.is_dir():
        for package_dir in sorted(metadata_root.iterdir()):
            if not package_dir.is_dir() or package_dir.name in staged:
                continue
            if package_dir.name not in known:
                continue
            for record in package_dir.glob("*.json"):
                add(record.stem, package_dir.name)
    return {va: sorted(packages) for va, packages in claims.items()}


def _src_resident_packages(root):
    # type: (Path) -> set
    """Packages that occupy ``src/reconstruction/<src_package>``."""
    base = Path(root) / SRC_REL
    if not base.is_dir():
        return set()
    return {_dashes(entry.name) for entry in base.iterdir()
            if entry.is_dir() and not entry.name.startswith(".")}


def package_dir(root, package):
    # type: (Path, object) -> tuple
    """``(directory, location)`` for a claimant: staging wins over ``src/``.

    A package staged but not installed is read from ``staging/``; a package
    that only exists as canonical source is read from ``src/reconstruction/``.
    Reading both would let a stale staging copy shadow installed truth, so
    exactly one is used -- and which one is reported in the comparison.
    """
    root = Path(root)
    staged = root / STAGING_REL / str(package)
    if staged.is_dir():
        return staged, STAGING_REL
    installed = root / SRC_REL / _underscores(package)
    if installed.is_dir():
        return installed, SRC_REL
    return staged, STAGING_REL


def _entry_bare(name):
    # type: (str) -> str
    text = str(name).strip().lower()
    match = re.match(r"^(?:0x)?([0-9a-f]{1,8})$", text)
    return match.group(1) if match else text


def _va_key(va):
    # type: (str) -> str
    return "0x" + _entry_bare(va)


def installed_owners(root):
    # type: (Path) -> dict
    """VA -> installed src packages that already promote it.

    A marker is accepted only under the same rule the build applies: the frozen
    schema plus a ``src_package`` the build would take as a target name.
    """
    root = Path(root)
    owners = {}
    base = root / SRC_REL
    if not base.is_dir():
        return owners
    for entry in sorted(base.iterdir()):
        if not entry.is_dir() or entry.name.startswith("."):
            continue
        document, _problem = _read_json(entry / PROMOTION_NAME)
        if not _is_promotion(document):
            continue
        for target in document.get("targets", []) or []:
            try:
                owners.setdefault(_bare(target.get("va")), set()).add(entry.name)
            except (ValueError, TypeError):
                continue
    return {va: sorted(names) for va, names in owners.items()}


def _is_promotion(document):
    # type: (object) -> bool
    """A real installed marker, under the rule the build itself applies.

    The schema must be the frozen promotion schema and the ``src_package``
    must be a name the build would take as a target name. A directory that
    fails either test was never a promotion as far as any reader is
    concerned, so it claims no VA.
    """
    if not isinstance(document, dict):
        return False
    if document.get("schema") != PROMOTION_SCHEMA:
        return False
    name = document.get("src_package")
    if not isinstance(name, str) or not SRC_NAME_RE.match(name):
        return False
    return isinstance(document.get("targets"), list)


def manifest_packages(root):
    # type: (Path) -> dict
    """VA -> the ``package`` the canonical manifest already records for it.

    ``functions[]`` is heterogeneous: most rows carry ``va``, 28 carry only
    ``function_address``. Both are read, and a row that declares neither is
    skipped rather than guessed at.
    """
    document, _problem = _read_json(Path(root) / MANIFEST_REL)
    packages = {}
    if not document:
        return packages
    for row in document.get("functions", []) or []:
        if not isinstance(row, dict):
            continue
        raw = row.get("va") or row.get("function_address")
        if raw is None:
            continue
        try:
            bare = _bare(raw)
        except ValueError:
            continue
        package = row.get("package")
        if package:
            packages.setdefault(bare, set()).add(str(package))
    return {va: sorted(names) for va, names in packages.items()}


# ---------------------------------------------------------------------------
# Per-claimant comparison
# ---------------------------------------------------------------------------


def _metadata_va(document):
    # type: (dict) -> object
    for key in ("va", "address", "function_address", "entry", "target_va"):
        value = document.get(key)
        if isinstance(value, str):
            return value
    return None


def _metadata_worker_ownership(document):
    # type: (dict) -> object
    for key in ("worker_ownership", "implementer_id", "owner", "ownership"):
        value = document.get(key)
        if value:
            return value
    return None


def compare_claimant(root, va, package, context):
    # type: (Path, str, str, dict) -> dict
    """Score one ``(VA, package)`` claim on every axis, from persisted artifacts.

    Every value here is read from a file another module already wrote. Nothing
    is inferred, defaulted upward, or taken from a clock.
    """
    root = Path(root)
    package = str(package)
    directory, location = package_dir(root, package)
    files = _package_files(directory)
    sources, headers, tests = _partition(files)
    metadata_paths = sorted((root / METADATA_REL / package).glob("%s.json" % va)) \
        if (root / METADATA_REL / package).is_dir() else []
    metadata_rel = ["%s/%s/%s" % (METADATA_REL, package, path.name)
                    for path in metadata_paths]
    metadata, metadata_problem = (None, "missing")
    if metadata_paths:
        metadata, metadata_problem = _read_json(metadata_paths[0])

    # settled: how firmly this package already holds the identity. 3 = a real
    # installed promotion marker, which means it cleared the full machine gate
    # (validation PASS + GATED + m32 build + ctest); 2 = the canonical manifest
    # records it for the VA; 1 = it occupies src/reconstruction/<src_package> as
    # integrator-owned canonical source; 0 = none of those. A settled owner is
    # not up for arbitration -- a better-validating duplicate still loses to it,
    # because installing the duplicate is precisely the collision being avoided.
    manifest_names = context["manifest"].get(va) or []
    installed = [name for name in (context["installed"].get(va) or [])
                 if same_package(name, package)]
    if installed:
        settled = 3
    elif any(same_package(name, package) for name in manifest_names):
        settled = 2
    elif location == SRC_REL:
        settled = 1
    else:
        settled = 0

    # validation: the rank of the static status of the persisted report that
    # names a source file *inside this package*. A report naming another
    # claimant says nothing about this one, so it scores 0 -- sharing a VA is
    # not sharing a verdict.
    validation = 0
    validation_status = None
    validation_path = None
    validation_static = None
    report = context["reports"].get(va)
    if isinstance(report, dict):
        source = str((report.get("source") or {}).get("path") or "")
        marker = STAGING_REL + "/"
        if source.startswith(marker) and source[len(marker):].split("/", 1)[0] == package:
            static = report.get("static") if isinstance(report.get("static"), dict) else {}
            validation_status = static.get("status") or report.get("status")
            validation = STATIC_RANK.get(str(validation_status), 0)
            coverage = report.get("coverage") if isinstance(report.get("coverage"), dict) else {}
            validation_static = coverage.get("ratio")
            validation_path = "%s/%s/%s" % (EVIDENCE_REL, va, VALIDATION_NAME)

    # build_gate: a persisted openspore-build-gate-1 verdict that is ok for
    # this exact src package. Only the promotion record writes one, so this is
    # 1 for an installed-and-gated package and 0 everywhere else. Absence is
    # "unverified", never "failed".
    build_gate = 0
    build_detail = None
    record_path = root / EVIDENCE_REL / va / PROMOTION_NAME
    record, record_problem = _read_json(record_path)
    if isinstance(record, dict):
        build = record.get("build") if isinstance(record.get("build"), dict) else {}
        if build.get("schema") == BUILD_GATE_SCHEMA and build.get("ok"):
            verdict = (build.get("packages") or {}).get(_underscores(package))
            if verdict and verdict.get("ok"):
                build_gate = 1
                build_detail = {"test_count": verdict.get("test_count"),
                                "m32": build.get("m32"), "cxx": build.get("cxx")}

    # evidence: what the persisted pack says about *this* package. A pack is a
    # property of the VA, so the per-claimant question is whether the pack
    # attributes the reconstruction to this package at all: 0 = no pack, or the
    # pack names other packages; 1 = the pack names a file in this package;
    # +1 when the pack's binary evidence is verified; + the record's evidence
    # level rank (OBSERVED=2, SUPPORTED=1). An unrecognised level contributes
    # nothing -- an unknown label is not strength.
    evidence = 0
    evidence_detail = None
    pack_path = root / EVIDENCE_REL / va / EVIDENCE_NAME
    pack, _pack_problem = _read_json(pack_path)
    if isinstance(pack, dict):
        attributed = _pack_names_package(pack, package)
        if attributed:
            evidence = 1
            binary = pack.get("binary_evidence") if isinstance(pack.get("binary_evidence"), dict) else {}
            inner = pack.get("record") if isinstance(pack.get("record"), dict) else {}
            level = str(inner.get("evidence_level") or "")
            if str(binary.get("integrity") or "") == INTEGRITY_VERIFIED:
                evidence += 1
            evidence += EVIDENCE_LEVEL_RANK.get(level, 0)
        evidence_detail = {"attributed_to_package": attributed,
                           "integrity": (pack.get("binary_evidence") or {}).get("integrity")
                           if isinstance(pack.get("binary_evidence"), dict) else None,
                           "evidence_level": str((pack.get("record") or {}).get("evidence_level") or "")
                           or None,
                           "evidence_state": pack.get("evidence_state")}

    # completeness: how much of the promotable shape the package actually
    # stages. Three boolean facts, counted.
    completeness = (1 if sources else 0) + (1 if headers else 0) + (1 if tests else 0)

    # provenance: worker-declared ownership of this VA. 3 = a staging
    # ownership.json that lists the VA in ``owned``; 2 = a metadata record with
    # worker ownership; 1 = a metadata record at all; 0 = none.
    provenance = 0
    worker_ownership = _metadata_worker_ownership(metadata) if metadata else None
    ownership_doc, _own_problem = _read_json(directory / "ownership.json")
    owned_vas = []
    if isinstance(ownership_doc, dict):
        for item in ownership_doc.get("owned", []) or []:
            raw = item.get("va") if isinstance(item, dict) else item
            if raw is None:
                continue
            try:
                owned_vas.append(_va_key(raw))
            except ValueError:
                continue
    declares_this_va = _va_key(va) in owned_vas
    if declares_this_va:
        provenance = 3
    elif worker_ownership:
        provenance = 2
    elif metadata is not None:
        provenance = 1

    # metadata_coherence: does the handoff agree with itself and with the
    # claim? 2 = parses and self-declares this VA and this package; 1 = parses
    # with those fields absent; 0 = absent, unparseable, or self-contradicting.
    metadata_coherence = 0
    metadata_conflict = None
    if metadata is not None:
        declared_va = _metadata_va(metadata)
        declared_package = metadata.get("package")
        conflict = []
        if declared_va is not None:
            try:
                if _bare(declared_va) != va:
                    conflict.append("declares VA %s" % declared_va)
            except ValueError:
                conflict.append("declares unparseable VA %r" % (declared_va,))
        if declared_package and _dashes(declared_package) != _dashes(package):
            conflict.append("declares package %s" % declared_package)
        if conflict:
            metadata_conflict = "; ".join(conflict)
        else:
            metadata_coherence = 1 if (declared_va is None and not declared_package) else 2
    elif metadata_problem not in (None, "missing"):
        metadata_conflict = "unreadable: %s" % metadata_problem

    comparison = {
        "settled": settled,
        "validation": validation,
        "build_gate": build_gate,
        "evidence": evidence,
        "completeness": completeness,
        "provenance": provenance,
        "metadata_coherence": metadata_coherence,
    }
    return {
        "va": _va_key(va),
        "package": package,
        "src_package": _underscores(package),
        "comparison": comparison,
        "rank_key": [comparison[axis] for axis in AXES],
        "validation": {
            "report": validation_path,
            "static_status": validation_status,
            "static_coverage_ratio": validation_static,
        },
        "build": {"verified": bool(build_gate), "detail": build_detail},
        "evidence": evidence_detail,
        "metadata": {
            "records": metadata_rel,
            "readable": metadata is not None,
            "worker_ownership": worker_ownership,
            "conflict": metadata_conflict,
        },
        "staging": {
            "dir": "%s/%s" % (location, package),
            "location": location,
            "sources": sources,
            "headers": headers,
            "tests": tests,
            "worker_ownership_declares_va": declares_this_va,
        },
        # Timestamps are diagnostics. They are reported and never ranked; see
        # the module docstring and tests/test_ownership_reconciliation.py.
        "diagnostics": _timestamps(directory, metadata_paths),
        "digests": _claim_digests(root, directory, files, metadata_paths, va),
    }


def _pack_names_package(pack, package):
    # type: (dict, str) -> bool
    """Does the persisted evidence pack attribute this VA to ``package``?

    The pack records which sources the reconstruction lives in, so it can name
    a package the claimant map never saw -- a package that was integrated and
    whose staging directory is long gone. That attribution is the only
    per-claimant thing a VA-scoped artifact can say, and it is the honest
    question to ask: does the evidence point at *this* reconstruction?
    """
    record = pack.get("record") if isinstance(pack.get("record"), dict) else {}
    source = record.get("source") if isinstance(record.get("source"), dict) else {}
    paths = []
    for key in ("file",):
        if isinstance(source.get(key), str):
            paths.append(source[key])
    for key in ("files", "metadata", "handoffs"):
        values = source.get(key)
        if isinstance(values, list):
            paths.extend(item for item in values if isinstance(item, str))
    if not paths and isinstance(record.get("package"), str):
        return _dashes(record["package"]) == _dashes(package)
    wanted = _dashes(package)
    for path in paths:
        for prefix in (STAGING_REL + "/", SRC_REL + "/"):
            if path.startswith(prefix):
                if _dashes(path[len(prefix):].split("/", 1)[0]) == wanted:
                    return True
        if _dashes(path.rsplit("/", 1)[0]) == wanted:
            return True
    return False


def _timestamps(staging, metadata_paths):
    # type: (Path, list) -> dict
    found = {}
    for label, path in [("staging_dir", Path(staging))] + \
            [("metadata", p) for p in metadata_paths]:
        try:
            found[label] = int(os.path.getmtime(path))
        except OSError:
            continue
    return found


def _claim_digests(root, staging, files, metadata_paths, va):
    # type: (Path, Path, list, list, str) -> dict
    """Every digest that must still hold for this decision to remain valid.

    An unreadable input yields ``{}`` rather than a partial set: a decision
    that cannot be re-verified is a decision that does not apply.
    """
    digests = {"staging_files": {}, "metadata": None, "validation": None,
               "evidence": None}
    base = Path(staging)
    for name in files:
        try:
            digests["staging_files"][name] = file_sha256(base / name)
        except OSError:
            return {}
    if metadata_paths:
        try:
            digests["metadata"] = file_sha256(metadata_paths[0])
        except OSError:
            return {}
    evidence = Path(root) / EVIDENCE_REL / va
    for key, name in (("validation", VALIDATION_NAME), ("evidence", EVIDENCE_NAME)):
        path = evidence / name
        if not path.is_file():
            continue
        try:
            digests[key] = file_sha256(path)
        except OSError:
            return {}
    return digests


def _context(root):
    # type: (Path) -> dict
    root = Path(root)
    reports = {}
    evidence = root / EVIDENCE_REL
    if evidence.is_dir():
        for entry in sorted(evidence.iterdir()):
            if not entry.is_dir():
                continue
            bare = _entry_bare(entry.name)
            if not re.match(r"^[0-9a-f]{1,8}$", bare):
                continue
            report, _problem = _read_json(entry / VALIDATION_NAME)
            if report is not None:
                reports[bare] = report
    return {
        "reports": reports,
        "manifest": manifest_packages(root),
        "installed": installed_owners(root),
    }


# ---------------------------------------------------------------------------
# Inventory and decision
# ---------------------------------------------------------------------------


def duplicates(root=ROOT):
    # type: (Path) -> list
    """Every VA with more than one claimant, in canonical VA order."""
    claims = claimant_map(root)
    return ["0x" + va for va in sorted(claims) if len(claims[va]) > 1]


def _decide(va, claimants):
    # type: (str, list) -> tuple
    """The canonical claimant and the ordering that produced it.

    The winner is the maximum of the rank tuple. The final tiebreak is
    ascending package name -- a total order, so the result never depends on
    iteration order, and explicitly not a claim that either package is better.
    """
    ordered = sorted(claimants, key=lambda row: (tuple(-value for value in row["rank_key"]),
                                                 row["package"]))
    canonical = ordered[0]
    tied = [row["package"] for row in ordered
            if row["rank_key"] == canonical["rank_key"] and row["package"] != canonical["package"]]
    return canonical, ordered, tied


def _deciding_axis(canonical, other):
    # type: (dict, dict) -> str
    for axis in AXES:
        if canonical["comparison"][axis] != other["comparison"][axis]:
            return axis
    return TIE_BREAK


def _axis_reason(canonical, other):
    # type: (dict, dict) -> str
    """Why ``other`` lost to ``canonical``, in one readable clause."""
    axis = _deciding_axis(canonical, other)
    if axis == TIE_BREAK:
        return ("axis %r: the evidence is equivalent, so the lower package name "
                "takes the identity (%s over %s); this arbitrates identity and "
                "claims nothing about quality"
                % (TIE_BREAK, canonical["package"], other["package"]))
    return "axis %r: canonical %d vs superseded %d" % (
        axis, canonical["comparison"][axis], other["comparison"][axis])


def inventory(root=ROOT, vas=None):
    # type: (Path, object) -> dict
    """Read-only. Every duplicated VA, with the full comparison behind it.

    Writes nothing, opens no file for writing, takes no timestamp.
    """
    root = Path(root)
    context = _context(root)
    claims = claimant_map(root)
    wanted = None
    if vas:
        wanted = set()
        for value in vas:
            wanted.add(_bare(value))
    rows = []
    for bare in sorted(claims):
        if len(claims[bare]) < 2:
            continue
        if wanted is not None and bare not in wanted:
            continue
        claimants = [compare_claimant(root, bare, package, context)
                     for package in claims[bare]]
        canonical, ordered, tied = _decide(bare, claimants)
        superseded = []
        for row in ordered:
            if row["package"] == canonical["package"]:
                continue
            superseded.append({
                "package": row["package"],
                "src_package": row["src_package"],
                "role": "superseded",
                "superseded_by": canonical["package"],
                "reason": _axis_reason(canonical, row),
                "comparison": row["comparison"],
                "rank_key": row["rank_key"],
                "retained_artifacts": {
                    "dir": row["staging"]["dir"],
                    "location": row["staging"]["location"],
                    "retained_files": row["staging"]["sources"] + row["staging"]["headers"]
                    + row["staging"]["tests"],
                    "metadata": row["metadata"]["records"],
                    "worker_ownership": row["metadata"]["worker_ownership"],
                },
                "provenance_preserved": True,
                "deleted": False,
            })
        rows.append({
            "va": _va_key(bare),
            "canonical": canonical["package"],
            "canonical_src_package": canonical["src_package"],
            "deciding_axis": _deciding_axis(
                canonical, ordered[1]) if len(ordered) > 1 else None,
            "tied_on_rank": tied,
            "claimants": ordered,
            "superseded": superseded,
            "already_installed": sorted(context["installed"].get(bare) or []),
            "manifest_package": context["manifest"].get(bare) or [],
            "inputs_sha256": {
                "claimants": {row["package"]: row["digests"] for row in ordered},
            },
        })
    return {
        "schema": INVENTORY_SCHEMA,
        "ok": True,
        "rule": rule_description(),
        "entries": rows,
        "summary": {
            "duplicate_vas": len(rows),
            "claimants": sum(len(row["claimants"]) for row in rows),
            "superseded": sum(len(row["superseded"]) for row in rows),
            "settled_canonical": len([row for row in rows
                                      if row["claimants"][0]["comparison"]["settled"]]),
        },
    }


def rule_description():
    # type: () -> dict
    """The frozen statement of what the canonicalization rule is.

    Kept as data so the ledger, the plan and the docs cannot drift apart, and
    so an auditor can read the rule without reading the code.
    """
    return {
        "summary": ("greatest (settled, validation, build_gate, evidence, "
                    "completeness, provenance, metadata_coherence) tuple wins; "
                    "exact ties are broken by ascending package name"),
        "axes": list(AXES),
        "axis_definitions": {
            "settled": ("3 = already installed with a real promotion marker, "
                        "which means it cleared the full machine gate; 2 = the "
                        "canonical manifest records it for the VA; 1 = it "
                        "occupies src/reconstruction/<src_package> as "
                        "integrator-owned canonical source; 0 = none of those. A "
                        "settled owner is not up for arbitration"),
            "validation": ("rank of the static status of the persisted "
                           "validation report that names a source file inside "
                           "this package: PASS=4, WARN=3, UNKNOWN=2, "
                           "NOT_AVAILABLE=1, else 0. A VA has exactly one "
                           "report, so this axis separates the package the "
                           "validator actually looked at -- and records how "
                           "well -- from the ones it did not, which score 0"),
            "build_gate": ("1 when a persisted openspore-build-gate-1 verdict "
                           "is ok for this exact src package, else 0; absence "
                           "means unverified, never failed"),
            "evidence": ("what the persisted pack says about *this* package: 0 "
                         "= no pack, or the pack attributes the VA to other "
                         "packages; 1 = the pack names a file in this package; "
                         "+1 when its binary evidence is verified; +2 for an "
                         "OBSERVED record evidence level, +1 for SUPPORTED, +0 "
                         "for anything unrecognised"),
            "completeness": ("count of the three promotable shapes staged: a "
                             "non-test .cpp, a .hpp/.h, and a *_test.cpp"),
            "provenance": ("3 = a staging ownership.json lists the VA in "
                           "``owned``; 2 = a metadata record carries worker "
                           "ownership; 1 = a metadata record exists; 0 = none"),
            "metadata_coherence": ("2 = the handoff parses and self-declares "
                                    "this VA and this package; 1 = it parses "
                                    "with those fields absent; 0 = absent, "
                                    "unreadable, or self-contradicting"),
        },
        "tie_break": ("ascending package name -- a total order so the result "
                      "never depends on iteration order; it arbitrates identity "
                      "and asserts nothing about quality"),
        "timestamps_are_inputs": False,
        "timestamp_policy": ("recorded under each claimant's ``diagnostics`` and "
                             "excluded from every comparison"),
        "non_destructive": ("apply writes the ledger only; no staging directory, "
                            "metadata handoff, evidence pack or source file is "
                            "moved, renamed or deleted"),
        "fail_safe": ("resolve() returns a decision only when the recorded "
                      "claimant set still equals the observed one and every "
                      "recorded input digest still matches; otherwise the "
                      "caller refuses with duplicate_va as before"),
    }


# ---------------------------------------------------------------------------
# Apply
# ---------------------------------------------------------------------------


def _ledger_document(root, rows):
    # type: (Path, list) -> dict
    entries = {}
    for row in rows:
        entries[row["va"]] = {
            "va": row["va"],
            "canonical": row["canonical"],
            "canonical_src_package": row["canonical_src_package"],
            "deciding_axis": row["deciding_axis"],
            "tied_on_rank": row["tied_on_rank"],
            "claimants": [entry["package"] for entry in row["claimants"]],
            "claimant_rows": row["claimants"],
            "superseded": row["superseded"],
            "duplicate_relationship": {
                "kind": "duplicate_va",
                "resolved": True,
                "resolution": "canonical_owner_selected",
                "claimant_count": len(row["claimants"]),
            },
            "already_installed": row["already_installed"],
            "manifest_package": row["manifest_package"],
            "inputs_sha256": row["inputs_sha256"],
        }
    index_path = Path(root) / INDEX_REL
    manifest_path = Path(root) / MANIFEST_REL
    return {
        "schema": LEDGER_SCHEMA,
        "generated_by": "tools/reconstruction_tooling/ownership.py",
        "rule": rule_description(),
        "inputs": {
            INDEX_REL: file_sha256(index_path) if index_path.is_file() else None,
            MANIFEST_REL: file_sha256(manifest_path) if manifest_path.is_file() else None,
        },
        "entries": entries,
        "summary": {
            "duplicate_vas": len(entries),
            "superseded": sum(len(entry["superseded"]) for entry in entries.values()),
        },
    }


def apply(root=ROOT, vas=None, write=True):
    # type: (Path, object, bool) -> dict
    """Write the ownership ledger for every duplicated VA.

    Additive and idempotent: the only file written is the ledger, and writing
    the same tree twice produces the same bytes. No artifact is removed, so a
    superseded package keeps its source, its metadata handoff and its evidence
    exactly as its worker left them.

    ``vas`` restricts which duplicates are *re-adjudicated*. It does not
    restrict what the ledger may end up containing: a filtered run merges into
    the ledger already on disk and carries every other entry forward untouched.
    Replacing the file with only the filtered rows would silently drop the
    recorded provenance relationship of every other VA and -- because
    :func:`resolve` is fail-safe -- quietly return all of them to
    ``duplicate_va`` with nothing to explain it. A filtered run asked to merge
    into a ledger it cannot read refuses instead of writing a partial one.
    """
    root = Path(root)
    report = inventory(root, vas=vas)
    document = _ledger_document(root, report["entries"])
    if vas:
        document = _merge_ledger(root, document, [row["va"] for row in report["entries"]])
    path = ledger_path(root)
    if write:
        write_json_atomic(path, document)
    canonical = sorted(entry["canonical"] for entry in document["entries"].values())
    return {
        "schema": RECONCILIATION_SCHEMA,
        "ok": True,
        "status": "reconciled" if document["entries"] else "nothing_to_reconcile",
        "changed": bool(write and document["entries"]),
        "ledger": _rel(root, path) if write else None,
        "written": bool(write and document["entries"]),
        "rule": document["rule"],
        "reconciled_vas": sorted(row["va"] for row in report["entries"]),
        "carried_forward_vas": sorted(document.get("carried_forward") or []),
        "entries": {
            va: {
                "canonical": entry.get("canonical"),
                "deciding_axis": entry.get("deciding_axis"),
                "claimants": entry.get("claimants") or [],
                "superseded": [row["package"] for row in entry.get("superseded") or []],
                "tied_on_rank": entry.get("tied_on_rank") or [],
            }
            for va, entry in sorted(document["entries"].items())
        },
        "summary": {
            "duplicate_vas": report["summary"]["duplicate_vas"],
            "reconciled": report["summary"]["duplicate_vas"],
            "claimants": report["summary"]["claimants"],
            "packages_retained": report["summary"]["superseded"],
            "packages_superseded": report["summary"]["superseded"],
            "canonical_packages": len(set(canonical)),
            "ledger_entries": len(document["entries"]),
        },
    }


def _merge_ledger(root, document, reconciled):
    # type: (Path, dict, list) -> dict
    """Fold a filtered adjudication into the ledger already on disk.

    This is the difference between "re-adjudicate one VA" and "the ledger now
    only knows about one VA". The second reading destroys recorded
    relationships, so it is not an option: entries outside the filter are
    carried forward verbatim and listed in ``carried_forward_vas``.
    """
    path = ledger_path(root)
    existing, problem = _read_json(path)
    if existing is None:
        if problem == "missing":
            return document
        raise ToolError("ownership_ledger_unreadable",
                        "%s cannot be read, so a filtered reconciliation would "
                        "discard its contents: %s" % (_rel(root, path), problem), 4)
    if existing.get("schema") != LEDGER_SCHEMA:
        raise ToolError("ownership_ledger_unsupported",
                        "%s has schema %r, expected %r; refusing to merge into it"
                        % (_rel(root, path), existing.get("schema"), LEDGER_SCHEMA), 4)
    previous = existing.get("entries")
    if not isinstance(previous, dict):
        previous = {}
    carried = sorted(set(previous) - set(reconciled))
    merged = dict(previous)
    merged.update(document["entries"])
    document["entries"] = merged
    document["carried_forward"] = carried
    document["summary"] = {
        "duplicate_vas": len(merged),
        "superseded": sum(len(entry.get("superseded") or []) for entry in merged.values()),
    }
    return document


# ---------------------------------------------------------------------------
# Read-side resolution (consumed by the promotion gate)
# ---------------------------------------------------------------------------


def _digests_match(root, va, entry, context):
    # type: (Path, str, dict, dict) -> bool
    """Re-take every recorded digest and compare.

    This is the check that makes the ledger safe to trust: a source edited
    after the decision, a handoff rewritten, an evidence pack regenerated --
    any of them changes a digest and the entry stops resolving, so the gate
    falls back to refusing rather than acting on a decision made about
    different bytes.
    """
    recorded = (entry.get("inputs_sha256") or {}).get("claimants") or {}
    if not recorded:
        return False
    for package, digests in sorted(recorded.items()):
        if not digests:
            return False
        fresh = compare_claimant(root, va, package, context)
        if fresh["digests"] != digests:
            return False
    return True


def resolve(root, va):
    # type: (Path, object) -> dict
    """The ledger's decision for one VA, or a refusal explaining why there is none.

    Returns ``{"status": "resolved", ...}`` only when every consistency check
    passes. Any failure returns ``{"status": "unresolved", "problem": ...}``
    and the caller must keep refusing with ``duplicate_va``. There is no code
    path here that turns an unreconciled duplicate into a permitted one.
    """
    root = Path(root)
    try:
        bare = _bare(va)
    except ValueError:
        return {"status": "unresolved", "problem": "no_entry", "va": str(va)}
    path = ledger_path(root)
    document, problem = _read_json(path)
    if document is None:
        return {"status": "unresolved",
                "problem": "ledger_missing" if problem == "missing" else "ledger_unreadable",
                "va": _va_key(bare)}
    if document.get("schema") != LEDGER_SCHEMA:
        return {"status": "unresolved", "problem": "ledger_schema_unsupported",
                "va": _va_key(bare)}
    entry = (document.get("entries") or {}).get(_va_key(bare))
    if not isinstance(entry, dict):
        return {"status": "unresolved", "problem": "no_entry", "va": _va_key(bare)}
    if _va_key(entry.get("va")) != _va_key(bare):
        return {"status": "unresolved", "problem": "entry_va_mismatch", "va": _va_key(bare)}

    # The recorded claimant set must still be exactly the observed one. A
    # package that started claiming this VA after the decision was written is
    # not covered by it, and the whole entry stops being usable -- the ledger
    # is a record of one adjudication, not a standing waiver.
    observed = claimant_map(root).get(bare) or []
    if sorted(entry.get("claimants") or []) != observed:
        return {"status": "unresolved", "problem": "claimants_changed", "va": _va_key(bare),
                "recorded": sorted(entry.get("claimants") or []), "observed": observed}

    canonical = str(entry.get("canonical") or "")
    if not canonical:
        return {"status": "unresolved", "problem": "no_entry", "va": _va_key(bare)}
    context = _context(root)
    if not package_dir(root, canonical)[0].is_dir():
        return {"status": "unresolved", "problem": "canonical_absent", "va": _va_key(bare),
                "canonical": canonical}
    # A foreign *installed* owner is the one collision the claimant set cannot
    # see, because a promoted package is identified by its marker rather than
    # by a staged filename. Two installed packages promoting one VA is a real
    # duplicate that no arbitration can excuse, so it refuses here.
    installed = context["installed"].get(bare) or []
    foreign_installed = sorted(name for name in installed
                               if not same_package(name, canonical))
    if foreign_installed:
        return {"status": "unresolved", "problem": "installed_conflict", "va": _va_key(bare),
                "installed": installed, "canonical": canonical}
    if not _digests_match(root, bare, entry, context):
        return {"status": "unresolved", "problem": "inputs_changed", "va": _va_key(bare)}
    return {
        "status": "resolved",
        "va": _va_key(bare),
        "canonical": canonical,
        "canonical_src_package": entry.get("canonical_src_package") or _underscores(canonical),
        "deciding_axis": entry.get("deciding_axis"),
        "superseded": [str(row.get("package")) for row in entry.get("superseded") or []
                       if isinstance(row, dict)],
        "tied_on_rank": entry.get("tied_on_rank") or [],
        "claimants": list(entry.get("claimants") or []),
    }


def policy_digest():
    # type: () -> str
    """Digest of the frozen rule, so a policy change is visible in the ledger."""
    return sha256_bytes(canonical_json(rule_description()))


def _selfcheck(rule):
    # type: (dict) -> None
    if list(rule.get("axes") or ()) != list(AXES):
        raise ToolError("ownership_rule_mismatch",
                        "the ownership rule on disk does not match this module", 4)
    if rule.get("timestamps_are_inputs"):
        raise ToolError("ownership_rule_mismatch",
                        "the ownership rule on disk makes timestamps an input", 4)


__all__ = [
    "AXES", "INVENTORY_SCHEMA", "LEDGER_SCHEMA", "PROBLEMS", "RECONCILIATION_SCHEMA",
    "apply", "claimant_map", "compare_claimant", "duplicates", "installed_owners",
    "inventory", "ledger_path", "manifest_packages", "policy_digest", "resolve",
    "rule_description",
]
