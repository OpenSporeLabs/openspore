"""Tests for the read-only deterministic reconstruction coverage reporter.

The read-only guarantees are the load-bearing part of this suite: a coverage
reporter that quietly mutated a queue row or an SQLite database would corrupt
the very state it claims to measure.
"""

import inspect
import io
import json
import re
import shutil
import sqlite3
import sys
import tempfile
import time
import unittest
from contextlib import redirect_stdout
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))

from reconstruction_tooling import cli, coverage as cov
from reconstruction_tooling.models import (ROOT, ToolError, canonical_json,
                                          normalize_va, sha256_json)

REPORT = None
# Data files: byte content AND mtime must both be untouched.
MUTATION_SENSITIVE = (
    "knowledgegraph/spore.db",
    "knowledgegraph/triage/queue-f0e310e0-v6.json",
    "knowledgegraph/research/source-reconstruction-manifest.json",
)
# SQLite sidecars: the write-ahead log and its shared-memory read-lock index.
# They hold no data of ours. Opening a WAL database read-only re-stamps their
# mtime and can trigger SQLite's one-time recovery of a stale WAL, so a bare
# mode=ro open does exactly the same thing. Their CONTENT must be identical,
# and any mtime drift must also be produced by the control open.
CONTENT_SENSITIVE = (
    "knowledgegraph/spore.db-wal",
    "knowledgegraph/spore.db-shm",
)
WATCHED_TREES = (
    "reconstruction/knowledge",
    "knowledgegraph/triage",
    "reconstruction/metadata",
)


def report():
    global REPORT
    if REPORT is None:
        REPORT = cov.build_report(ROOT)
    return REPORT


def dim(identifier):
    for record in report()["dimensions"]:
        if record["id"] == identifier:
            return record
    raise AssertionError("no dimension %r in the report" % identifier)


def classification(name, key="counts"):
    return report()["classifications"][name][key]


def fingerprint(path):
    path = Path(path)
    if not path.exists():
        return None
    stat = path.stat()
    return (stat.st_size, stat.st_mtime_ns, hash(path.read_bytes()))


def tree_fingerprint(root, rels):
    out = {}
    for rel in rels:
        base = Path(root) / rel
        if not base.exists():
            out[rel] = None
            continue
        entries = []
        for item in sorted(base.rglob("*")):
            try:
                entries.append((item.relative_to(base).as_posix(), item.stat().st_size))
            except OSError:
                continue
        out[rel] = entries
    return out


def input_aggregate(report_value):
    """The per-input identity used to decide "did an input actually change?".

    The WHOLE aggregate is required, not sha256 alone: coverage.py emits
    sha256=null for four of the five directory inputs, so a sha256-only
    comparison reports an EMPTY differing set for a report that visibly
    changed -- and then blames engine nondeterminism for a concurrent write.
    """
    return {key: (entry.get("sha256"), entry.get("bytes"), entry.get("member_count"))
            for key, entry in (report_value["snapshot"]["inputs"] or {}).items()}


def differing_inputs(left, right):
    first = input_aggregate(left)
    second = input_aggregate(right)
    return {key for key in first if first[key] != second.get(key)}


def _diff_keys(left_text, right_text):
    """Top-level report keys whose canonical JSON differs between two reports."""
    left, right = json.loads(left_text), json.loads(right_text)
    return {key for key in set(left) | set(right)
            if canonical_json(left.get(key)) != canonical_json(right.get(key))}


class CoverageTest(unittest.TestCase):
    # -- 1 ---------------------------------------------------------------
    def test_universe_is_exact(self):
        universes = report()["universes"]
        self.assertEqual(universes["internal_functions"], 58757)
        self.assertEqual(universes["gameplay_functions"], 2149)
        self.assertEqual(universes["non_gameplay_functions"], 56608)
        self.assertEqual(universes["gameplay_functions"] + universes["non_gameplay_functions"],
                         universes["internal_functions"])
        self.assertEqual(dim("total_internal_functions")["covered"], 58757)
        self.assertEqual(dim("gameplay_functions")["covered"], 2149)
        self.assertEqual(dim("non_gameplay_functions")["covered"], 56608)

    # -- 2 ---------------------------------------------------------------
    def test_unique_va_dedup(self):
        # A synthetic manifest-like set: 5 records, 3 distinct VAs, and one
        # record that uses `function_address` instead of `va`.
        synthetic = [
            {"va": "0x00401000"},
            {"va": "0x00401000"},
            {"function_address": "0x00401010"},
            {"va": "0X00401020"},
            {"va": "not-a-va"},
        ]
        distinct = cov.manifest_record_vas(synthetic)
        self.assertEqual(len(synthetic), 5)
        self.assertEqual(len(distinct), 3)
        self.assertIn(normalize_va("0x00401000"), [normalize_va(value) for value in distinct])
        self.assertIn(normalize_va("0x00401010"), [normalize_va(value) for value in distinct])
        self.assertIn(normalize_va("0x00401020"), [normalize_va(value) for value in distinct])

        records = dim("integrated_reconstruction_record")
        unique = dim("integrated_unique_va")
        # 300 records exist; 299 are integrated and 1 is blocked. The record
        # dimension counts integrated RECORDS, the unique dimension counts
        # distinct VAs among them.
        self.assertEqual(records["covered"], 299)
        self.assertEqual(unique["covered"], 299)
        self.assertEqual(records["universe"], 300)
        self.assertNotEqual(records["universe"], report()["reconstruction"]["packages"])
        self.assertEqual(report()["reconstruction"]["records"], 300)
        self.assertEqual(report()["reconstruction"]["unique_vas"], 300)
        self.assertEqual(report()["reconstruction"]["in_universe"], 296)
        self.assertEqual(len(report()["reconstruction"]["out_of_universe"]), 4)
        # 12 records carry `function_address` rather than `va`.
        self.assertEqual(report()["reconstruction"]["records_with_function_address_only"], 12)

    # -- 3 ---------------------------------------------------------------
    def test_staged_versus_integrated(self):
        records = dim("integrated_reconstruction_record")
        blocked = dim("blocked_va")
        staged = dim("staged_va")
        self.assertEqual(records["covered"], 299)
        self.assertEqual(blocked["covered"], 1)
        self.assertEqual(blocked["blocked_va"], "0x00dd0e10")
        self.assertEqual(normalize_va(blocked["blocked_va"]), "0x00dd0e10")
        # Staged is reported on its own and never folded into the integrated figure.
        self.assertTrue(report()["reconstruction"]["staged_is_separate_from_integrated"])
        self.assertGreater(staged["covered"], 0)
        self.assertNotEqual(staged["covered"], records["covered"])
        self.assertTrue(any("never added into any integrated figure" in caveat.lower()
                            for caveat in staged["caveats"]))
        # accounting_exclusions is a preservation list, NOT a subtraction.
        reconstruction = report()["reconstruction"]
        self.assertEqual(len(reconstruction["accounting_exclusions"]), 5)
        self.assertTrue(reconstruction["accounting_exclusions_are_not_subtractions"])
        self.assertTrue(reconstruction["accounting_exclusions_all_integrated"])
        self.assertIn("NOT an exclusion set", reconstruction["accounting_exclusions_warning"])
        self.assertEqual(records["covered"], 299)
        self.assertNotEqual(records["covered"], 299 - len(reconstruction["accounting_exclusions"]))

    # -- 4 ---------------------------------------------------------------
    def test_persisted_versus_live_only(self):
        persisted = dim("persisted_decompilation")
        live = dim("live_only_decomp_observation")
        self.assertEqual(persisted["covered"], 478)
        self.assertEqual(persisted["gameplay_covered"], 172)
        self.assertEqual(live["covered"], 184)
        self.assertEqual(live["gameplay_covered"], 184)
        self.assertTrue(live["disjoint_from_persisted_decompilation"])
        # The overlap is a real, independently recomputed VA list, not a count.
        # The previous assertion read `persisted.get("vas", [])`, a key the emitter
        # never produces, so it reduced to `set() & overlap == set()` and could
        # never fail. Disjointness is now checked against the report's own VA list
        # AND against the count arithmetic below.
        self.assertEqual(live["overlap"], [])
        self.assertNotIn("vas", persisted)
        # The 184 live observations are a dimension union, never a decompilation count.
        self.assertIn("NOT a decompilation count", live["counting_rule"])
        self.assertEqual(live["union_with_persisted_gameplay"], 356)
        self.assertEqual(live["union_with_persisted_universe"], 662)
        self.assertEqual(live["contained_in_no_decompilation_evidence"], 184)
        self.assertTrue(live["all_gameplay"])
        # No other dimension may claim the 184 as persisted decompilation.
        self.assertEqual(persisted["covered"], 478)
        self.assertEqual(persisted["gameplay_covered"], 172)

    # -- 4a --------------------------------------------------------------
    def test_any_versus_no_decomp_evidence_is_a_true_partition(self):
        """`any` and `no` are an exact partition of the universe, over ONE universe.

        Both are read off the SAME ledger rows, so unlike `live_only` they are
        complements by construction rather than by coincidence.
        """
        any_decomp = dim("any_decompilation_evidence")
        no_decomp = dim("no_decompilation_evidence")
        persisted = dim("persisted_decompilation")
        self.assertEqual(any_decomp["covered"] + no_decomp["covered"], 58757)
        self.assertEqual(any_decomp["gameplay_covered"] + no_decomp["gameplay_covered"], 2149)
        self.assertTrue(any_decomp["any_plus_no_equals_universe"])
        self.assertTrue(any_decomp["complement_is_no_decompilation_evidence"])
        # persisted is a PROPER subset of any, and the 2-row difference is
        # entirely snapshot_only rows -- the reason `any` is not `persisted`.
        self.assertTrue(any_decomp["superset_of_persisted_decompilation"])
        self.assertEqual(any_decomp["any_minus_persisted"],
                         any_decomp["covered"] - persisted["covered"])
        self.assertEqual(any_decomp["any_minus_persisted"], 2)
        self.assertTrue(any_decomp["any_minus_persisted_all_snapshot_only"])
        # Non-vacuous: the flag is guarded on a non-empty difference, and the two
        # rows really are non-persisted (body_available is not true).
        self.assertGreater(any_decomp["any_minus_persisted"], 0)

    # -- 4b --------------------------------------------------------------
    def test_live_only_is_disjoint_from_the_ledger_decomp_partition(self):
        """The 184 live-only VAs lie INSIDE `no`, never inside `any`.

        This is the relation that makes 480 look wrong. It is not: `any` is a
        LEDGER count, and the ledger records decomp_state "unavailable" for every
        one of the 184, so `any` and `live_only` are disjoint by universe and the
        184 are members of `no`. Asserting this is what stops a future reader from
        "correcting" 480 to 662 or from adding the two dimensions.
        """
        any_decomp = dim("any_decompilation_evidence")
        live = dim("live_only_decomp_observation")
        no_decomp = dim("no_decompilation_evidence")
        self.assertEqual(live["intersects_any_decompilation_evidence"], [])
        self.assertTrue(live["disjoint_from_any_decompilation_evidence"])
        # `any` does NOT contain `live`: the sets are disjoint, so a superset
        # claim here would assert the opposite of the truth.
        self.assertTrue(any_decomp["is_disjoint_from_live_only_decomp_observation"])
        self.assertFalse(any_decomp["live_only_is_subset_of_any"])
        self.assertEqual(any_decomp["intersection_with_live_only"], [])
        # Contained in `no`, and the containment is the whole 184.
        self.assertEqual(no_decomp["contains_live_only_observations"], 184)
        self.assertEqual(live["contained_in_no_decompilation_evidence"], 184)
        # Because the two sets are disjoint, the union IS additive -- and it is
        # 664, not 662: `any` is two rows larger than `persisted`. Conflating the
        # two unions is the arithmetic slip this test exists to catch.
        self.assertEqual(any_decomp["union_with_live_only"], 664)
        self.assertEqual(any_decomp["covered"] + live["covered"], 664)
        self.assertEqual(any_decomp["persisted_union_with_live_only"], 662)
        self.assertEqual(live["union_with_persisted_universe"], 662)
        self.assertEqual(any_decomp["union_with_live_only"] - any_decomp["persisted_union_with_live_only"],
                         any_decomp["any_minus_persisted"])
        # Gameplay side of the same union: 173 + 184, disjoint, so additive.
        self.assertEqual(any_decomp["union_with_live_only_gameplay"], 357)
        # The report must forbid the addition it just made arithmetically valid.
        self.assertTrue(live["do_not_add_to_ledger_decomp_dimensions"])

    # -- 4c --------------------------------------------------------------
    def test_no_decomp_evidence_is_a_persistence_census_not_a_never_decompiled_census(self):
        """`no` must not be readable as "never decompiled" -- 184 of its rows were.

        The contradiction is the whole audit finding, so it is pinned here: the
        dimension's own `covered` set and the live-only set are reported as
        overlapping, and the caveat that reconciles them is present.
        """
        no_decomp = dim("no_decompilation_evidence")
        self.assertEqual(no_decomp["covered"], 58277)
        self.assertIn("persistence", no_decomp["counting_rule"].lower())
        joined = " ".join(no_decomp["caveats"]).lower()
        self.assertIn("live_only_decomp_observation", joined)
        self.assertIn("unavailable", no_decomp["source_of_truth"])
        # The label must name the scope it actually measures. Asserting merely
        # "the label changed" would be satisfied by any nonsense label.
        self.assertIn("ledger-recorded", no_decomp["label"].lower())
        self.assertIn("184", " ".join(no_decomp["caveats"]))
        self.assertIn("no_never_decompiled_census_is_published", no_decomp)

    # -- 4d --------------------------------------------------------------
    def test_gap_va_extraction_reaches_every_record(self):
        """Every decomp-gap record must yield a VA, including the `identity.va` dialect.

        5 of the 16 tracked partitions nest the VA under `identity` and carry no
        top-level `va`; 793 of 1,977 records. Reading top-level keys only silently
        dropped 40% of the artifact. This count was 1,184/1,977 before the fix and
        did not change the 184 (the skipped records carry no live-body key), which
        is exactly why it needed a test rather than a number change.
        """
        live = dim("live_only_decomp_observation")
        self.assertEqual(live["gap_records_read"], 1977)
        self.assertEqual(live["gap_records_with_va"], 1977)
        self.assertEqual(live["gap_records_without_va"], 0)
        # And the widened extraction must not have moved the count.
        self.assertEqual(live["covered"], 184)

    # -- 4e --------------------------------------------------------------
    def test_reconstructed_with_persisted_body_id_is_not_contradictory(self):
        record = dim("reconstructed_without_persisted_decompilation")
        # The historical id says "without"; `covered` is the WITH-set. The report
        # must disclose that rather than leave the id and the count in conflict.
        self.assertTrue(record["id_says_without_but_covered_is_the_with_set"])
        self.assertIn("ALSO carry a persisted body", record["counting_rule"])
        complement = record["covered_without_persisted_body"]
        self.assertEqual(complement, 151)
        self.assertEqual(record["covered"] + complement, 300)

    # -- 4f --------------------------------------------------------------
    def test_untracked_percentage_is_computed_not_asserted(self):
        """No percentage may be a hand-typed literal with no denominator.

        `reconstruction/metadata is ~66% untracked` was a string constant matching
        nothing derivable: its own siblings gave 1 - 101/328 = 69.2%. The emitter
        now computes the figure, and this test re-derives it from the two counts the
        report publishes alongside it.

        Scope, stated honestly: this proves the PUBLISHED FIGURE is derived from its
        stated denominator, which is the defect class that was fixed. It cannot
        prove the emitter's formula is the intended one -- only a synthetic
        metadata tree could, and building one would mean faking a git index.
        `tracked_members` is deliberately NOT re-read from `git ls-files` here: it
        is the report's one declared host probe, so a concurrent `git add` shifts
        it after the cached report was built and the test would be racy by design.
        """
        snapshot = report()["snapshot"]["inputs"]
        tracked = snapshot["metadata_dir"]["tracked_members"]
        total = dim("metadata_only_record")["metadata_files"]
        self.assertGreater(total, 0)
        expected = "%.1f%%" % (100.0 * (total - tracked) / total)
        caveat = dim("metadata_only_record")["caveats"][0]
        # The published figure must equal the derived one. A hand-typed 66% fails
        # here, because the denominator gives 69.2%.
        self.assertIn(expected, caveat)
        self.assertRegex(caveat, r"^reconstruction/metadata is \d+\.\d% untracked;")
        self.assertNotIn("roughly", caveat)
        blind = [item for item in report()["blind_spots"] if "untracked" in item]
        self.assertEqual(len(blind), 1)
        self.assertIn(expected, blind[0])
        # Both string sites must publish the SAME figure and the SAME counts.
        self.assertIn("only %d of %d metadata files" % (tracked, total), blind[0])
        self.assertIn("only %d of the %d metadata files" % (tracked, total), caveat)

    # -- 5 ---------------------------------------------------------------
    def test_gameplay_subset_accounting(self):
        for record in report()["dimensions"]:
            gameplay = record.get("gameplay_covered")
            if gameplay is not None:
                self.assertLessEqual(gameplay, 2149, record["id"])
        self.assertEqual(dim("persisted_decompilation")["gameplay_covered"], 172)
        self.assertEqual(classification("decomp_state", "gameplay_counts")["unavailable"], 1976)
        self.assertEqual(classification("decomp_state", "gameplay_counts")["decompiler_export"], 172)
        self.assertEqual(classification("decomp_state", "gameplay_counts")["snapshot_only"], 1)
        self.assertEqual(classification("body_quality")["unavailable"], 58277)
        non_gameplay_bodies = (classification("decomp_state")["decompiler_export"]
                               - classification("decomp_state", "gameplay_counts")["decompiler_export"]
                               + 1)
        self.assertEqual(172 + 306, 478)
        self.assertEqual(non_gameplay_bodies, 306)
        # The gameplay "any decompilation evidence" axis is 173, one more than
        # persisted: the extra row is a snapshot_only capture.
        self.assertEqual(dim("any_decompilation_evidence")["gameplay_covered"], 173)
        self.assertEqual(dim("no_decompilation_evidence")["gameplay_covered"], 1976)
        self.assertEqual(classification("triage_category")["GAMEPLAY_LOGIC"], 1656)
        self.assertEqual(classification("triage_category")["GAMEPLAY_SUPPORT"], 493)
        self.assertEqual(classification("triage_category", "gameplay_counts").get("UNKNOWN", 0), 0)
        self.assertEqual(classification("name_evidence")["UNKNOWN"], 39883)
        self.assertEqual(classification("name_evidence", "gameplay_counts").get("UNKNOWN", 0), 0)
        self.assertEqual(classification("name_evidence")["INFERRED"], 12371)
        self.assertEqual(classification("name_evidence")["SUPPORTED"], 3836)
        self.assertEqual(classification("name_evidence")["APPROX"], 1500)
        self.assertEqual(classification("name_evidence")["CONFIRMED"], 1167)
        self.assertEqual(classification("priority")["P3"], 52140)
        self.assertEqual(classification("priority")["P1"], 6261)
        self.assertEqual(classification("priority")["IGNORE"], 178)
        self.assertEqual(classification("priority")["P0"], 159)
        self.assertEqual(classification("priority")["P2"], 19)
        self.assertEqual(classification("triage_category")["UNKNOWN"], 39716)
        self.assertEqual(classification("triage_category")["ENGINE_IMPLEMENTATION"], 11585)
        self.assertEqual(classification("triage_category")["THIRD_PARTY_OR_RUNTIME"], 4080)
        self.assertEqual(classification("triage_category")["ENGINE_INTERFACE"], 1227)

    # -- 6 ---------------------------------------------------------------
    def test_semantic_classification(self):
        tiers = report()["semantics"]["tiers"]
        self.assertEqual(tiers["STRONG_SEMANTIC"], 4)
        self.assertEqual(tiers["BOUNDED_SEMANTIC"], 8)
        self.assertEqual(tiers["STRUCTURAL_ONLY"], 5)
        self.assertEqual(tiers["NEEDS_RUNTIME"], 15)
        self.assertEqual(tiers["STILL_UNKNOWN"], 0)
        self.assertEqual(dim("semantic_unclassified")["covered"], 58725)
        self.assertEqual(4 + 8 + 5 + 15 + 0, 32)
        self.assertEqual(dim("semantic_unclassified")["covered"] + 32, 58757)
        semantics = report()["semantics"]
        self.assertTrue(semantics["canonical_vocabulary"]["no_inferred_tier"])
        note = semantics["honest_note"]
        self.assertIn("NO canonical semantic tier named 'inferred'", note)
        self.assertIn("INFERRED is an", note)
        self.assertIn("evidence_ladder_axes", semantics)
        self.assertEqual(dim("semantic_strong")["covered"], 4)
        self.assertEqual(dim("semantic_bounded")["covered"], 8)
        self.assertEqual(dim("semantic_structural_only")["covered"], 5)
        self.assertEqual(dim("semantic_needs_runtime")["covered"], 15)
        self.assertEqual(dim("semantic_still_unknown")["covered"], 0)
        self.assertEqual(report()["semantics"]["positive_any_gameplay"], 976)
        self.assertEqual(report()["semantics"]["positive_complement_gameplay"], 1173)
        residual = semantics["residual_unknown_negative_label"]
        self.assertTrue(residual["is_a_negative_label"])
        self.assertTrue(residual["must_not_be_unioned_into_positive_coverage"])
        self.assertEqual(residual["records"], 1976)
        # The blueprint's own axes keep the 2149 gameplay denominator separate.
        self.assertEqual(classification("blueprint_claim_kind", "counts"),
                         {"UNKNOWN": 1254, "INFERRED": 484, "SEMANTIC": 411})
        self.assertEqual(report()["classifications"]["blueprint_claim_kind"]["gameplay_universe"], 2149)
        self.assertEqual(classification("blueprint_semantic_understanding", "counts"),
                         {"not_established": 1976, "partial": 173})
        # The ledger's own semantic_understanding has zero variance: the single
        # token not_established covers the whole 58,757-row ledger.
        self.assertEqual(classification("triage_category")["UNKNOWN"] > 0, True)
        self.assertEqual(dim("semantic_unclassified")["universe"], 58757)

    # -- 7 ---------------------------------------------------------------
    def test_runtime_gated_is_not_runtime_failed(self):
        self.assertEqual(dim("runtime_validated")["covered"], 0)
        self.assertEqual(dim("runtime_gated")["covered"], 299)
        self.assertEqual(dim("runtime_negative")["covered"], 0)
        self.assertIs(dim("runtime_unavailable")["available"], False)
        self.assertIsNone(dim("runtime_unavailable")["covered"])
        self.assertIn("not a field", dim("runtime_unavailable")["not_determinable_reason"])
        self.assertEqual(report()["runtime"]["validated"], 0)
        self.assertEqual(report()["runtime"]["gated"], 299)
        self.assertEqual(report()["runtime"]["negative"], 0)
        self.assertEqual(report()["runtime"]["capability_status"],
                         "TECHNICALLY_FEASIBLE_NOT_IMPLEMENTED")
        inventory = report()["runtime"]["not_run_values_must_not_be_read_as_failed"]
        self.assertTrue(inventory)
        self.assertIn("not_run", inventory["token_inventory"])
        self.assertIn("NOT_AVAILABLE", inventory["token_inventory"])
        self.assertIn("blocked", inventory["high_misread_risk_tokens"])
        self.assertEqual(inventory["token_inventory"]["blocked"]["misread_risk"], "HIGH")
        self.assertIn("OBSERVED_NEGATIVE", inventory["reachability_negatives"])
        self.assertIn("not_established", inventory["token_inventory"])
        self.assertIn("NOT_PRESENT", inventory["token_inventory"])
        self.assertIn("not run", inventory["token_inventory"])
        self.assertIn("not performed", inventory["token_inventory"])
        self.assertIn("not_promoted", inventory["token_inventory"])
        self.assertIn("required", inventory["token_inventory"])
        # Every non-zero "failed" count in the repo is a static gate.
        self.assertEqual(report()["runtime"]["no_original_process_observations"]
                         ["runtime_validated_functions"], 0)
        proof = dim("runtime_negative")
        self.assertIsNone(proof["manifest_audit_unresolved_contradiction"])
        self.assertIn("FAIL", proof["validate_verdicts"])
        self.assertIn("NOT_AVAILABLE", proof["validate_verdicts"])
        self.assertTrue(proof["not_available_is_a_sibling_of_fail_not_a_failure"])

    # -- 8 ---------------------------------------------------------------
    def test_deterministic_output(self):
        # Another agent writes reconstruction/* in this worktree, so two builds
        # can straddle a real input change. That is not engine
        # nondeterminism. Assert purity precisely: the two builds must either
        # be byte-identical, or differ *only* where a recorded input's aggregate
        # also differs.
        #
        # Two rules this test must never break:
        #  * It may NEVER skip. A determinism test that can skip is a test that
        #    can silently stop testing. If a concurrent write makes the
        #    comparison impossible, that is a FAILURE naming the input, never a
        #    skip and never a silent pass.
        #  * "Did an input change?" must be answered from the whole per-input
        #    aggregate (sha256, bytes, member_count), not from sha256 alone.
        #    coverage.py deliberately emits sha256=null for four of the five
        #    directory inputs, so a sha256-only comparison reports an EMPTY
        #    differing set for a report that visibly changed -- and then blames
        #    "engine nondeterminism" for a concurrent write.
        first = cov.build_report(ROOT)
        second = cov.build_report(ROOT)
        differing = differing_inputs(first, second)
        if canonical_json(first) != canonical_json(second):
            # A concurrent write really did happen; retry to separate that from
            # engine nondeterminism. The retry loop only decides WHY; the final
            # outcome below is always an assertion.
            for attempt in range(5):
                time.sleep(1.0)
                first = cov.build_report(ROOT)
                second = cov.build_report(ROOT)
                if canonical_json(first) == canonical_json(second):
                    differing = set()
                    break
                differing = differing_inputs(first, second)
            else:
                self.fail(
                    "two builds never agreed across 6 attempts while reconstruction/ was being "
                    "rewritten. Inputs that changed between the last pair of builds: %s. The last "
                    "pair of reports differed in these keys: %s. This is reported as a failure, "
                    "not skipped: rerun when the other agent is idle."
                    % (sorted(differing) or "none",
                       sorted(set(_diff_keys(canonical_json(first), canonical_json(second))))))
        # Identical input aggregates MUST mean identical output. This is the real
        # determinism assertion, and it is unconditional.
        self.assertEqual(differing, set(),
                         "these inputs changed between the two builds (%s), so the comparison "
                         "cannot isolate engine nondeterminism; rerun when the other agent is "
                         "idle" % sorted(differing))
        self.assertEqual(canonical_json(first), canonical_json(second))
        self.assertEqual(sha256_json(first), sha256_json(second))
        self.assertEqual(first["snapshot"]["input_drift"], [])
        self.assertEqual(second["snapshot"]["input_drift"], [])

        # No host time, hostname, mtime, or absolute path may appear in the body.
        forbidden_key = re.compile(r"(time|date|generated|hostname|created|updated|mtime)", re.I)
        absolute = re.compile(r"^/|^(?:[A-Za-z]:[\\/]|/home/|/tmp/|/root/)")

        def walk(value, path):
            if isinstance(value, dict):
                for key, child in value.items():
                    here = path + (str(key),)
                    if forbidden_key.search(str(key)) and not isinstance(child, (dict, list)):
                        # A host-time leak looks like an epoch second/ns count or a
                        # fractional mtime, not like any small count. Keys such as
                        # runtime_validated are false positives of the name filter
                        # and are allowed to carry ordinary small integers.
                        if isinstance(child, bool):
                            pass
                        elif isinstance(child, float):
                            self.fail("%s carries a float under a time-like key: %r"
                                      % (".".join(here), child))
                        elif isinstance(child, int) and abs(child) >= 10 ** 11:
                            self.fail("%s carries an epoch-sized value under a time-like key: %r"
                                      % (".".join(here), child))
                    if not isinstance(child, (dict, list)) and isinstance(child, str):
                        self.assertIsNone(absolute.match(child),
                                          "%s holds an absolute path: %r" % (".".join(here), child))
                    walk(child, here)
            elif isinstance(value, list):
                for index, child in enumerate(value):
                    walk(child, path + (str(index),))

        walk(first, ())
        text = canonical_json(first)
        self.assertNotIn(str(ROOT), text)
        self.assertNotIn(".codegraph", text)
        for forbidden in ("time.time", "datetime", "socket.gethostname"):
            self.assertNotIn(forbidden, text)

    # -- 9 ---------------------------------------------------------------
    def test_stale_metadata_safety(self):
        # Build against a throwaway temp root, never the real repository. The
        # tree is a symlink mirror of the real inputs so the report can be
        # assembled end-to-end; the mutation hook rewrites a symlinked file
        # into a real file so the write lands in the temp dir, not in the repo.
        workdir = Path(tempfile.mkdtemp(prefix="coverage-drift-"))
        self.addCleanup(shutil.rmtree, str(workdir), ignore_errors=True)
        for rel in (cov.LEDGER_REL, cov.MANIFEST_REL, cov.QUEUE_REL,
                    cov.SEMANTIC_DECOMP_REL, cov.SEMANTIC_BLUEPRINT_REL):
            link = workdir / rel
            link.parent.mkdir(parents=True, exist_ok=True)
            if not link.exists():
                link.symlink_to(ROOT / rel)

        # Replace the manifest symlink with a real, mutable copy.
        target = workdir / cov.MANIFEST_REL
        target.unlink()
        target.write_text((ROOT / cov.MANIFEST_REL).read_text(encoding="utf-8"),
                          encoding="utf-8")

        original = cov._fingerprint
        state = {"mutated": False}

        def mutating_fingerprint(path, data=None):
            result = original(path, data) if data is not None else original(path)
            # Mutate exactly once, after the manifest's own post-read check.
            if Path(path) == target and not state["mutated"]:
                state["mutated"] = True
                target.write_text(target.read_text(encoding="utf-8") + "\n",
                                  encoding="utf-8")
            return result

        cov._fingerprint = mutating_fingerprint
        self.addCleanup(setattr, cov, "_fingerprint", original)
        with self.assertRaises(ToolError) as caught:
            cov.build_report(workdir)
        self.assertEqual(caught.exception.code, "input_changed_during_read")
        self.assertIn("drift", caught.exception.details)
        self.assertTrue(caught.exception.details["drift"])
        self.assertTrue(any(item["key"] == cov.MANIFEST_REL
                            for item in caught.exception.details["drift"]))

        # The sqlite URI is read-only, and machine-local dimensions say so.
        self.assertTrue(report()["generator_status"]["read_only"])
        self.assertEqual(report()["generator_status"]["sqlite_mode"], "ro")
        self.assertFalse(report()["generator_status"]["takes_machine_lock"])
        for identifier in ("functions_with_caller", "functions_with_callee",
                           "functions_with_any_call_role"):
            record = dim(identifier)
            self.assertEqual(record["provenance"], "machine_local", identifier)
            self.assertTrue(record["machine_local"], identifier)
            self.assertEqual(record["database_uri"], "mode=ro", identifier)
            self.assertTrue(any("gitignored" in caveat for caveat in record["caveats"]), identifier)

        self._assert_db_is_read_only()

    # -- 9b --------------------------------------------------------------
    def _assert_db_is_read_only(self):
        """Two independent, NON-EXECUTING checks that the engine cannot write.

        GUARD: the write probe below must NEVER target the shared
        `knowledgegraph/spore.db`. That file is a gitignored, SHARED database
        that other agents and tools read; a `CREATE TABLE` issued against it
        succeeds or fails depending on nothing but whether the URI is right, so
        a test that "proves" read-only by attempting a real write has already
        created a table by the time it discovers the URI was wrong. The previous
        version of this test did exactly that, and left
        `coverage_should_not_write` behind in the shared database. A read-only
        test must have no possible side effect, so the write is now attempted
        against a THROWAWAY COPY in a TemporaryDirectory, and the real
        database is only ever opened for SELECT/PRAGMA.
        """
        # (1) Non-executing: assert on the URI the engine constructs. This is the
        #     property that actually matters, and it cannot touch any file.
        source = inspect.getsource(cov._open_db)
        self.assertIn("mode=ro", source)
        self.assertIn("sqlite3.connect(uri, uri=True)", source)
        # The constructed URI itself, built the way _open_db builds it, must
        # carry mode=ro. Building a string writes nothing.
        probe = "file:%s?mode=ro" % str((ROOT / cov.KG_DB_REL).resolve()).replace("?", "%3f")
        self.assertTrue(probe.endswith("?mode=ro"))
        self.assertIn("?mode=ro", probe)

        # (2) Executing, but only against a disposable copy of the database.
        database = ROOT / cov.KG_DB_REL
        if not database.exists():
            self.skipTest("the gitignored machine-local database is absent; the read-only "
                          "write probe has nothing to run against")
        with tempfile.TemporaryDirectory(prefix="coverage-ro-copy-") as scratch:
            copy = Path(scratch) / "spore.db"
            shutil.copy2(database, copy)
            connection = cov._open_db(copy)
            self.addCleanup(connection.close)
            # Before issuing any write, prove the handle really is the throwaway
            # copy. If it were ever pointed at the shared database, this fails
            # here -- before the CREATE TABLE could land in it.
            attached = [row[2] for row in connection.execute("PRAGMA database_list")]
            self.assertTrue(attached, "no database is attached")
            for location in attached:
                self.assertIn(str(copy), location,
                              "the read-only probe is NOT pointed at the temp copy "
                              "(attached: %r); refusing to issue a write" % attached)
            # A SELECT works on the copy...
            self.assertIsInstance(connection.execute("select count(*) from sqlite_master")
                                  .fetchone(), tuple)
            # ...and the identical write statement the old test aimed at the SHARED
            # database is refused here. Nothing outside the temp dir is touched.
            with self.assertRaises(sqlite3.OperationalError):
                connection.execute(
                    "create table if not exists coverage_should_not_write (x integer)")
            # The copy is unchanged: the write left no table behind.
            names = {row[0] for row in connection.execute(
                "select name from sqlite_master where type='table'")}
            self.assertNotIn("coverage_should_not_write", names)

    # -- 10 --------------------------------------------------------------
    def test_no_queue_or_claim_mutation(self):
        # Data files: byte content AND mtime must both be untouched.
        before = {rel: fingerprint(ROOT / rel) for rel in MUTATION_SENSITIVE}

        # Control: what does a BARE read-only open of the same database do?
        # Any sidecar drift the report causes must be drift SQLite causes for
        # any reader at all, not something the reporter introduced.
        def control_open():
            connection = sqlite3.connect("file:%s?mode=ro" % (ROOT / cov.KG_DB_REL).resolve(),
                                         uri=True)
            connection.execute("select count(*) from triage").fetchone()
            connection.close()

        control_before = {rel: fingerprint(ROOT / rel) for rel in CONTENT_SENSITIVE}
        control_open()
        control_after = {rel: fingerprint(ROOT / rel) for rel in CONTENT_SENSITIVE}
        control_drifted = {rel for rel in CONTENT_SENSITIVE
                           if control_after[rel] != control_before[rel]}

        cov.build_report(ROOT)
        buffer = io.StringIO()
        with redirect_stdout(buffer):
            self.assertEqual(cli.main(["coverage", "--json"]), 0)
        after = {rel: fingerprint(ROOT / rel) for rel in MUTATION_SENSITIVE}
        after_sidecars = {rel: fingerprint(ROOT / rel) for rel in CONTENT_SENSITIVE}

        for rel in MUTATION_SENSITIVE:
            self.assertEqual(before[rel], after[rel],
                             "%s changed across a coverage report" % rel)
        self.assertIsNotNone(before[cov.KG_DB_REL])
        # Sidecar CONTENT must be byte-identical to what a bare read-only open
        # leaves behind. SQLite re-stamps mtime when it takes a WAL read lock;
        # that is a lock artefact, and the control proves it is not ours.
        for rel in CONTENT_SENSITIVE:
            if after_sidecars[rel] is None:
                continue
            self.assertEqual(after_sidecars[rel][0], control_after[rel][0],
                             "%s size changed across a coverage report" % rel)
            self.assertEqual(after_sidecars[rel][2], control_after[rel][2],
                             "%s content differs from a bare read-only open" % rel)
            if after_sidecars[rel] != control_after[rel]:
                self.assertIn(rel, control_drifted,
                              "%s mtime drifted but a bare read-only open does not drift it, "
                              "so the reporter caused it" % rel)
        # The reporter must not import the writing subsystems, and must not take
        # the shared machine lock. Check real import statements, not prose.
        source = Path(cov.__file__).read_text(encoding="utf-8")
        code = "\n".join(line for line in source.splitlines()
                         if not line.strip().startswith("#"))
        imports = re.findall(r"^\s*(?:from\s+\S+\s+import|import\s+\S+)", code, re.M)
        for statement in imports:
            for forbidden in ("queue", "orchestrate", "integrate", "swarm",
                              "evidence", "context", "recover", "lock", "observatory"):
                self.assertNotRegex(
                    statement, r"(?:^|\.)\b%s\b" % forbidden,
                    "coverage.py must not import the writing subsystem %r" % forbidden)
        # The only models imports permitted are the read-only ones.
        for statement in imports:
            if statement.strip().startswith("from .models"):
                for name in re.findall(r"import\s+(.+)$", statement):
                    for symbol in [item.strip() for item in name.split(",")]:
                        self.assertIn(symbol, {
                            "ROOT", "ToolError", "canonical_json", "normalize_va",
                            "file_sha256", "load_json", "optional_json", "write_json_atomic",
                        }, "coverage.py may only import read-only helpers from .models")
        # The generated report is not a queue claim of any kind.
        self.assertNotIn("worker_id", canonical_json(report()))

    # -- 11 --------------------------------------------------------------
    def test_cli_is_read_only(self):
        # Another agent is actively writing reconstruction/* in this worktree,
        # so an absolute listing comparison would fail for reasons that have
        # nothing to do with this reporter. Take two control snapshots with no
        # reporter running: anything that drifts between them is the other
        # agent, not us. What we assert is that the reporter's own effect is
        # indistinguishable from not having run it at all.
        def snapshot():
            return tree_fingerprint(ROOT, WATCHED_TREES)

        control_before = snapshot()
        time.sleep(0.2)
        control_after = snapshot()
        self.assertEqual(control_before, control_after,
                         "watched trees are being mutated during the test; rerun when the "
                         "other agent is idle")

        before = snapshot()
        buffer = io.StringIO()
        with redirect_stdout(buffer):
            self.assertEqual(cli.main(["coverage", "--json"]), 0)
        after = snapshot()
        self.assertEqual(before, after)
        # The emitted envelope is valid JSON carrying the report.
        envelope = json.loads(buffer.getvalue())
        self.assertTrue(envelope["ok"])
        self.assertEqual(envelope["command"], "coverage")
        self.assertEqual(envelope["result"]["$schema"], cov.SCHEMA)
        # --live is rejected: a read-only reporter has no live mode.
        with redirect_stdout(io.StringIO()):
            self.assertEqual(cli.main(["coverage", "--json", "--live"]), 2)
        # --markdown renders without writing anything.
        buffer = io.StringIO()
        with redirect_stdout(buffer):
            self.assertEqual(cli.main(["coverage", "--markdown"]), 0)
        self.assertIn("Coverage matrix", buffer.getvalue())
        self.assertEqual(snapshot(), after)

    # -- 12 --------------------------------------------------------------
    def test_percentages_are_not_a_composite(self):
        banned = re.compile(r"overall|percent_complete|completion|score|progress_pct", re.I)
        for key in report():
            self.assertIsNone(banned.search(str(key)),
                              "top-level key %r looks like a composite score" % key)
        text = cov.render_markdown(report())
        self.assertIn("Coverage matrix", text)
        self.assertIn("| dimension | covered | universe | pct |", text)
        for record in report()["dimensions"]:
            self.assertIn(record["id"], text)
        self.assertNotRegex(text, r"\d+(\.\d+)?% complete")
        # A composite would have to state a single percentage; assert none does.
        self.assertIsNone(re.search(r"(?i)overall\s+(\d+(\.\d+)?)\s*%", text))
        self.assertIsNone(re.search(r"(?i)completion\s*[:=]\s*\d", text))
        self.assertIn("no single completion percentage", text)
        # Individual dimension percentages are fine; summing them is not offered.
        self.assertTrue(any(record.get("pct") for record in report()["dimensions"]))

    # -- 13 --------------------------------------------------------------
    def test_cannot_determine_is_explicit(self):
        entries = report()["cannot_determine"]
        self.assertTrue(entries)
        for entry in entries:
            self.assertIn("metric", entry)
            self.assertIn("reason", entry)
            self.assertTrue(entry["metric"])
            self.assertTrue(entry["reason"])
        metrics = {entry["metric"] for entry in entries}
        for identifier in ("functions_with_caller", "functions_with_callee",
                           "functions_with_any_call_role", "runtime_unavailable",
                           "withheld_va"):
            self.assertIn(identifier, metrics)
        # The caller/callee dimensions are explicitly machine-local.
        for identifier in ("functions_with_caller", "functions_with_callee",
                           "functions_with_any_call_role"):
            record = dim(identifier)
            self.assertEqual(record["provenance"], "machine_local")
            self.assertTrue(any("not reproducible" in caveat.lower()
                                for caveat in record["caveats"]), identifier)
            self.assertTrue(any("triage-v4" in caveat for caveat in record["caveats"]), identifier)
        # Nothing is ever estimated: unavailable dimensions carry null, not a guess.
        for record in report()["dimensions"]:
            if not record["available"]:
                self.assertIsNone(record["covered"], record["id"])
                self.assertIsNone(record["pct"], record["id"])
                self.assertTrue(record["not_determinable_reason"], record["id"])
            else:
                self.assertIsNotNone(record["covered"], record["id"])
                self.assertTrue(record["source_of_truth"], record["id"])
                self.assertTrue(record["counting_rule"], record["id"])


# ---------------------------------------------------------------------------
# STABLE vs VOLATILE
#
# STABLE figures are derived only from tracked inputs that no other agent is
# concurrently rewriting (the ledger, the manifest, the queue, the semantic
# artifacts, the decomp-gap parts). They are pinned to exact literals.
#
# VOLATILE figures walk reconstruction/{metadata,staging,evidence} or the git
# INDEX, which another agent is actively writing. Those get STRUCTURAL
# invariants only (0 <= n, subset relations, upper bounds). Pinning a volatile
# literal produces exactly the false failure this suite is supposed to avoid.
#
# SEMI-STABLE figures come from the gitignored knowledgegraph/spore.db. They are
# pinned when the database is present and skipped -- with an explicit message --
# when it is not. A database-absent skip is legitimate; an engine-nondeterminism
# skip never is.
# ---------------------------------------------------------------------------

LEDGER = None


def ledger():
    """The 49 MB coverage ledger, parsed once. Read-only, never written."""
    global LEDGER
    if LEDGER is None:
        with open(ROOT / cov.LEDGER_REL, encoding="utf-8") as handle:
            LEDGER = json.load(handle)
    return LEDGER


def require_db():
    """Skip with an explicit message when the machine-local database is absent."""
    if not (ROOT / cov.KG_DB_REL).exists():
        raise unittest.SkipTest(
            "the gitignored machine-local SQLite database is absent, so the DB-derived "
            "caller/callee/type-association figures cannot be checked on this machine")


def read_only_db():
    connection = cov._open_db(ROOT / cov.KG_DB_REL)
    require_db()
    return connection


class CoverageSemanticsTest(unittest.TestCase):
    """Gap-closing assertions. Every one of these fails on the regression it
    covers; none of them restates the implementation."""

    # -- 14: positive_axes counts RECORDS, not categories ------------------
    def test_positive_axes_count_records_not_categories(self):
        axes = report()["semantics"]["positive_axes"]
        # The bug these pin: the axes iterated the COUNTER KEYS, so they
        # reported the number of distinct category names (2 and 1).
        self.assertEqual(axes["semantic_decomp_classified"], 32)
        self.assertEqual(axes["blueprint_claim_kind_not_unknown"], 895)
        self.assertEqual(axes["blueprint_semantic_understanding_not_not_established"], 173)
        # ...and they must agree with the per-category census they are built from.
        claim_kind = classification("blueprint_claim_kind", "counts")
        self.assertEqual(axes["blueprint_claim_kind_not_unknown"],
                         sum(count for token, count in claim_kind.items()
                             if token not in (None, "UNKNOWN")))
        understanding = classification("blueprint_semantic_understanding", "counts")
        self.assertEqual(axes["blueprint_semantic_understanding_not_not_established"],
                         sum(count for token, count in understanding.items()
                             if token not in (None, "not_established")))
        # The three axes OVERLAP, so they must never be summed, and the report
        # must say so with the real union alongside.
        note = report()["semantics"]["positive_axes_sum_is_not_a_union"]
        self.assertIn("MUST NOT be summed", note["note"])
        self.assertEqual(note["union_gameplay_vas"], report()["semantics"]["positive_any_gameplay"])
        self.assertTrue(note["union_gameplay_vas_is_not_the_sum_above"])
        # The union is strictly smaller than the naive sum, i.e. the axes really
        # do share VAs; otherwise the warning would be vacuous.
        self.assertLess(note["union_gameplay_vas"], note["positive_axes_sum_if_you_were_wrong"])

    # -- 15: caller/callee direction --------------------------------------
    def test_caller_callee_direction_is_not_swapped(self):
        caller = dim("functions_with_caller")
        callee = dim("functions_with_callee")
        # callee_va is the function BEING CALLED, so it is the caller-side set.
        self.assertEqual(caller["xref_column_read"], "callee_va")
        self.assertEqual(callee["xref_column_read"], "caller_va")
        # The machine-readable rule must name the column it actually read, or a
        # reader is told the wrong query produced the number.
        self.assertIn("callee_va", caller["counting_rule"])
        self.assertNotIn("caller_va", caller["counting_rule"])
        self.assertIn("caller_va", callee["counting_rule"])
        self.assertNotIn("callee_va", callee["counting_rule"])
        # A function with a callee need not have a caller and vice versa, so the
        # two sets are genuinely different; the union is strictly larger.
        self.assertNotEqual(caller["covered"], callee["covered"])
        union = dim("functions_with_any_call_role")
        self.assertGreater(union["covered"], max(caller["covered"], callee["covered"]))
        # Direction, re-derived from the database independently of the engine.
        require_db()
        connection = read_only_db()
        self.addCleanup(connection.close)
        placeholders = ",".join("?" * len(cov.CALL_REFERENCE_TYPES))
        from_callee = {row[0] for row in connection.execute(
            "select distinct callee_va from xref where reference_type in (%s)" % placeholders,
            cov.CALL_REFERENCE_TYPES) if row[0] and not row[0].startswith(("EXT:", "VT:"))}
        from_caller = {row[0] for row in connection.execute(
            "select distinct caller_va from xref where reference_type in (%s)" % placeholders,
            cov.CALL_REFERENCE_TYPES) if row[0] and not row[0].startswith(("EXT:", "VT:"))}
        universes = report()["universes"]["internal_functions"]
        self.assertEqual(caller["covered"], len(from_callee & _universe_bare()))
        self.assertEqual(callee["covered"], len(from_caller & _universe_bare()))
        self.assertEqual(union["covered"], len((from_callee | from_caller) & _universe_bare()))
        self.assertEqual(universes, 58757)

    # -- 16: the CALL reference_type filter is exactly these four ----------
    def test_call_reference_type_filter_is_exact(self):
        self.assertEqual(cov.CALL_REFERENCE_TYPES,
                         ("direct-call", "thunk", "external", "computed-call"))
        for identifier in ("functions_with_caller", "functions_with_callee",
                           "functions_with_any_call_role"):
            rule = dim(identifier)["counting_rule"]
            for reference_type in cov.CALL_REFERENCE_TYPES:
                self.assertIn(reference_type, rule, identifier)
            # No fifth reference type may be silently admitted.
            self.assertNotIn("computed", rule.replace("computed-call", ""), identifier)
            for other in ("data-read", "data-write", "unresolved", "any", "all"):
                self.assertNotIn("'%s'" % other, rule, identifier)
        # The filter is load-bearing: widening it to every reference type changes
        # the answer, so it is not a decorative clause in the prose.
        require_db()
        connection = read_only_db()
        self.addCleanup(connection.close)
        everything = {row[0] for row in connection.execute(
            "select distinct callee_va from xref where callee_va is not null")}
        universe = _universe_bare()
        self.assertGreater(len(everything & universe), dim("functions_with_caller")["covered"])

    # -- 17: the EXT:/VT: exclusion is applied ----------------------------
    def test_ext_and_vt_pseudo_targets_are_excluded(self):
        require_db()
        connection = read_only_db()
        self.addCleanup(connection.close)
        universe = _universe_bare()
        for column, identifier in (("callee_va", "functions_with_caller"),
                                   ("caller_va", "functions_with_callee")):
            placeholders = ",".join("?" * len(cov.CALL_REFERENCE_TYPES))
            filtered = {row[0] for row in connection.execute(
                "select distinct %s from xref where reference_type in (%s) "
                "and %s not like 'EXT:%%' and %s not like 'VT:%%'" % ((column, placeholders,
                                                                      column, column)),
                cov.CALL_REFERENCE_TYPES) if row[0]}
            unfiltered = {row[0] for row in connection.execute(
                "select distinct %s from xref where reference_type in (%s)" % (column, placeholders),
                cov.CALL_REFERENCE_TYPES) if row[0]}
            # The exclusion can only ever remove rows, never add them.
            self.assertLessEqual(len(filtered), len(unfiltered), column)
            pseudo = {va for va in unfiltered if va.startswith(("EXT:", "VT:"))}
            self.assertEqual(len(unfiltered) - len(filtered), len(pseudo), column)
            # ...and where pseudo-targets exist they are never real VAs, so they
            # never reach the universe either way.
            self.assertFalse(pseudo & universe, column)
            # The reported figure is the FILTERED one.
            self.assertEqual(dim(identifier)["covered"], len(filtered & universe))
            self.assertIn("EXT:%", dim(identifier)["counting_rule"])
            self.assertIn("VT:%", dim(identifier)["counting_rule"])
            self.assertIn(column, dim(identifier)["counting_rule"])
        # The counts alone cannot prove the filter ran: _bare() already discards
        # any value that is not a VA, so an EXT:/VT: row would be dropped either
        # way. Assert the clause itself is in the query the helper builds, and
        # that it is applied to BOTH sides of the union.
        helper = inspect.getsource(cov._call_role_vas)
        self.assertIn("not like 'EXT:%%'", helper)
        self.assertIn("not like 'VT:%%'", helper)
        self.assertGreaterEqual(helper.count("%s not like"), 2,
                                "the exclusion must be applied to the column being read")
        # At least one column genuinely carries pseudo-targets, so the exclusion
        # is load-bearing somewhere rather than decorative in both.
        self.assertTrue(
            any(row[0].startswith(("EXT:", "VT:")) for row in connection.execute(
                "select distinct callee_va from xref")
                if row[0]),
            "no EXT:/VT: pseudo-target exists, so the documented exclusion cannot bite")

    # -- 18/19: absolute caller/callee figures (SEMI-STABLE) --------------
    def test_caller_callee_absolute_counts(self):
        require_db()
        self.assertEqual(dim("functions_with_caller")["covered"], 33643)
        self.assertEqual(dim("functions_with_callee")["covered"], 41031)
        self.assertEqual(dim("functions_with_any_call_role")["covered"], 49451)
        # Gameplay figures come from the same DB but are a different subset.
        self.assertLessEqual(dim("functions_with_caller")["gameplay_covered"], 2149)
        self.assertLessEqual(dim("functions_with_callee")["gameplay_covered"], 2149)

    # -- 20: type association (SEMI-STABLE) -------------------------------
    def test_type_association_count(self):
        require_db()
        record = dim("has_type_association")
        self.assertEqual(record["covered"], 6807)
        # It is a UNION, so each part is bounded by the whole.
        self.assertLessEqual(record["database_only"], record["covered"])
        self.assertLessEqual(record["knowledge_index_only"], record["covered"])
        self.assertEqual(record["database_only"], 6733)
        self.assertEqual(record["knowledge_index_only"], 454)
        self.assertTrue(record["machine_local"])

    # -- 21: package membership (STABLE) ----------------------------------
    def test_package_membership_count(self):
        record = dim("has_package_membership")
        self.assertEqual(record["covered"], 2344)
        self.assertEqual(record["universe"], 58757)
        # union of three vocabularies, each bounded by the whole
        for part in ("manifest_package", "queue_cluster", "blueprint_package"):
            self.assertLessEqual(record[part], record["covered"], part)
        self.assertEqual(record["manifest_package"], 296)
        self.assertEqual(record["queue_cluster"], 365)
        self.assertEqual(record["blueprint_package"], 2149)
        self.assertEqual(record["universe_without_membership"], 58757 - 2344)

    # -- 22: queue census (STABLE) ----------------------------------------
    def test_queue_census(self):
        dependencies = report()["dependencies"]
        self.assertEqual(dependencies["queue"], 368)
        self.assertEqual(dependencies["in_universe"], 365)
        self.assertEqual(dependencies["out_of_universe_count"], 3)
        self.assertEqual(dependencies["out_of_universe"],
                         ["00e3a400", "00e7b6c0", "00e7d2c0"])
        self.assertEqual(dim("in_triage_queue")["covered"], 365)
        # 368 = 365 in-universe + exactly the 3 listed out-of-universe rows.
        self.assertEqual(dependencies["in_universe"] + dependencies["out_of_universe_count"],
                         dependencies["queue"])
        with open(ROOT / cov.QUEUE_REL, encoding="utf-8") as handle:
            self.assertEqual(dependencies["queue"], len(json.load(handle)["queue"]))

    # -- 23: readiness census (STABLE) ------------------------------------
    def test_readiness_census(self):
        readiness = report()["dependencies"]["readiness"]
        self.assertEqual(readiness, {"LIKELY_INFRASTRUCTURE": 182, "NEEDS_RE": 101,
                                    "READY_WITH_LOCAL_CONTEXT": 29, "DEPENDENCY_FIRST": 24,
                                    "ENGINE_BOUNDARY": 23, "READY": 6})
        self.assertEqual(sum(readiness.values()), 365)
        self.assertEqual(readiness, report()["dependencies"]["blocked_axes"]["axes"]["readiness"])
        self.assertEqual(classification("readiness"), readiness)

    # -- 24: blockers empty-set is EXACTLY the READY rows -----------------
    def test_blockers_empty_set_is_exactly_the_ready_rows(self):
        axes = report()["dependencies"]["blocked_axes"]["axes"]
        self.assertEqual(axes["ledger_rows_with_queue"], 365)
        self.assertEqual(axes["ledger_rows_with_non_empty_blockers"], 359)
        self.assertEqual(axes["ledger_rows_with_empty_blockers_and_readiness_READY"], 6)
        # Re-derive the row-level split straight from the ledger, so "exactly"
        # is checked rather than assumed.
        non_empty, empty = set(), set()
        for row in ledger()["ledger"]:
            if not row.get("queue"):
                continue
            if row.get("blockers"):
                non_empty.add(row["va"])
            else:
                empty.add(row["va"])
        self.assertEqual(len(non_empty), 359)
        self.assertEqual(len(empty), 6)
        self.assertEqual(non_empty & empty, set())
        ready = {row["va"] for row in ledger()["ledger"]
                 if row.get("queue") and (row.get("queue") or {}).get("readiness") == "READY"}
        self.assertEqual(len(ready), 6)
        # The two sets are the SAME set, in both directions.
        self.assertEqual(empty, ready)
        self.assertEqual(non_empty, {row["va"] for row in ledger()["ledger"]
                                     if row.get("queue") and row.get("blockers")})
        # The blocker-token census is a separate axis and must not be summed.
        self.assertEqual(sum(report()["dependencies"]["blockers"].values()), 540)
        self.assertEqual(report()["dependencies"]["blockers"], axes["blockers"])

    # -- 25: manifest types (STABLE) --------------------------------------
    def test_manifest_types_census(self):
        self.assertEqual(report()["reconstruction"]["types"], 137)
        with open(ROOT / cov.MANIFEST_REL, encoding="utf-8") as handle:
            manifest = json.load(handle)
        self.assertEqual(report()["reconstruction"]["types"], len(manifest["types"]))
        self.assertGreater(report()["reconstruction"]["types"], 0)

    # -- 26: runtime gate census (STABLE) ---------------------------------
    def test_runtime_gate_census(self):
        record = dim("runtime_gated")
        self.assertEqual(record["canonical_gate_entries"], 262)
        self.assertEqual(record["canonical_distinct_gate_entries"], 232)
        self.assertLess(record["canonical_distinct_gate_entries"],
                        record["canonical_gate_entries"])
        with open(ROOT / cov.MANIFEST_REL, encoding="utf-8") as handle:
            manifest = json.load(handle)
        gates = [gate for gate in manifest["runtime_gates"] if isinstance(gate, str)]
        self.assertEqual(record["canonical_gate_entries"], len(gates))
        self.assertEqual(record["canonical_distinct_gate_entries"], len(set(gates)))
        # The canonical metric is a manifest metric, not a record census: the
        # two must never be conflated.
        self.assertEqual(record["covered"], manifest["metrics"]["runtime_gated"])
        self.assertNotEqual(record["covered"], record["records_carrying_any_gate"])

    # -- 27: actionable frontier (STABLE) ---------------------------------
    def test_actionable_frontier_agrees_with_the_knowledge_index(self):
        record = dim("in_actionable_frontier")
        dependencies = report()["dependencies"]
        self.assertEqual(record["covered"], 231)
        self.assertEqual(record["in_universe"], 228)
        self.assertEqual(dependencies["actionable_frontier"], 231)
        self.assertEqual(dependencies["actionable_frontier_in_universe"], 228)
        # 231 actionable = the 228 in-universe ones + the 3 out-of-universe rows.
        self.assertEqual(record["in_universe"] + dependencies["out_of_universe_count"],
                         record["covered"])
        # The 137 in-universe queue rows NOT in the frontier are exactly the ones
        # a manifest record already claims: actionable is queue MINUS manifest.
        self.assertEqual(dependencies["in_universe"] - record["in_universe"], 137)
        index_path = ROOT / cov.KNOWLEDGE_INDEX_REL
        if not index_path.exists():
            self.skipTest("%s is absent; the frontier cross-check has nothing to compare"
                          % cov.KNOWLEDGE_INDEX_REL)
        cross = dependencies["frontier_cross_check"]
        self.assertTrue(cross["knowledge_index_present"])
        self.assertEqual(cross["knowledge_index_frontier_size"], 231)
        self.assertTrue(cross["agrees_with_derived_actionable_frontier"])
        # SET-EQUAL, not merely the same size.
        with open(index_path, encoding="utf-8") as handle:
            index = json.load(handle)
        self.assertEqual({normalize_va(entry["va"]) for entry in index["frontier"]},
                         _derived_actionable_frontier())

    # -- 28: available vs sufficient is a real distinction ----------------
    def test_available_and_sufficient_are_different_claims(self):
        classes = report()["evidence"]["classes"]
        self.assertEqual(sorted(classes), sorted(cov.CLASS_VOCABULARY))
        for name, entry in classes.items():
            for key in ("available_evidence", "sufficient_evidence",
                        "available_evidence_gameplay", "sufficient_evidence_gameplay"):
                self.assertIsInstance(entry[key], int, "%s.%s" % (name, key))
            # SUFFICIENT is a subset of AVAILABLE, never a superset.
            self.assertLessEqual(entry["sufficient_evidence"], entry["available_evidence"], name)
            self.assertLessEqual(entry["sufficient_evidence_gameplay"],
                                 entry["available_evidence_gameplay"], name)
            if entry["available_evidence"] > 0 and name != "RUNTIME":
                # The ladder filter must actually bite: an existing field is
                # never 'sufficient' merely because it exists.
                self.assertLess(entry["sufficient_evidence"], entry["available_evidence"], name)
        # At least one VA is available-but-insufficient in every populated class,
        # which is the whole point of reporting two numbers.
        self.assertTrue(report()["evidence"]["never_called_verified_because_present"])
        self.assertIn("never called verified merely because it exists",
                      report()["evidence"]["sufficient_definition"])
        # RUNTIME: available=false must not sit next to a positive count.
        runtime = classes["RUNTIME"]
        self.assertIs(runtime["available"], False)
        self.assertEqual(runtime["available_evidence"], 0)
        self.assertEqual(runtime["sufficient_evidence"], 0)
        self.assertIs(dim("evidence_runtime")["available"], False)
        self.assertIsNone(dim("evidence_runtime")["covered"])
        self.assertIn("rather than available-with-zero",
                      dim("evidence_runtime")["not_determinable_reason"])

    # -- 29: the canonical sufficient ladder ------------------------------
    def test_sufficient_evidence_ladder_is_exact(self):
        self.assertEqual(cov.SUFFICIENT_LADDER, ("SUPPORTED", "CONFIRMED", "VERIFIED"))
        self.assertEqual(set(cov.SUFFICIENT_LADDER), {"SUPPORTED", "CONFIRMED", "VERIFIED"})
        # OBSERVED is NOT a sufficient rung: it is a reachability/observation
        # token, and admitting it would let a mere observation pass as proof.
        for rejected in ("OBSERVED", "OBSERVED_NEGATIVE", "INFERRED", "APPROX",
                         "UNKNOWN", "NOT_AVAILABLE", "PARTIAL"):
            self.assertNotIn(rejected, cov.SUFFICIENT_LADDER)
        definition = report()["evidence"]["sufficient_definition"]
        for rung in cov.SUFFICIENT_LADDER:
            self.assertIn(rung, definition)
        self.assertNotIn("OBSERVED", definition)
        # The ladder is load-bearing: every class's sufficient count is a strict
        # subset of its available count, so the filter is applied, not decorative.
        classes = report()["evidence"]["classes"]
        for name, entry in classes.items():
            if entry["available_evidence"] > 0 and name != "RUNTIME":
                self.assertNotEqual(entry["sufficient_evidence"],
                                    entry["available_evidence"], name)

    # -- 30: summary <-> dimension cross-checks ---------------------------
    def test_summary_matches_dimensions_and_exclusions_are_computed(self):
        reconstruction = report()["reconstruction"]
        # The summary and the dimension must not drift apart.
        self.assertEqual(reconstruction["integrated"], dim("integrated_unique_va")["covered"])
        self.assertEqual(reconstruction["integrated"],
                         dim("integrated_reconstruction_record")["covered"])
        self.assertEqual(reconstruction["blocked"], dim("blocked_va")["covered"])
        self.assertEqual(reconstruction["records"], dim("integrated_reconstruction_record")["universe"])
        self.assertEqual(reconstruction["unique_vas"], dim("integrated_reconstruction_record")["universe"])
        # accounting_exclusions is a PRESERVATION list.
        self.assertEqual(len(reconstruction["accounting_exclusions"]), 5)
        self.assertTrue(reconstruction["accounting_exclusions_are_not_subtractions"])
        # Independently resolve all five exclusion VAs to manifest records.
        with open(ROOT / cov.MANIFEST_REL, encoding="utf-8") as handle:
            manifest = json.load(handle)
        status_by_va = {}
        for record in manifest["functions"]:
            bare = normalize_va(record.get("va") or record.get("function_address"))
            if bare:
                status_by_va.setdefault(bare, set()).add(record.get("integration_status"))
        for bare in reconstruction["accounting_exclusions"]:
            canonical = normalize_va(bare)
            self.assertIn(canonical, status_by_va, bare)
            self.assertEqual(status_by_va[canonical], {"integrated"}, bare)
        # ...and the boolean the report publishes is the real computation, not a
        # hardcoded literal: doctor the manifest so one exclusion is NOT
        # integrated and the flag must flip to false.
        self.assertTrue(reconstruction["accounting_exclusions_all_integrated"])
        workdir = _mirrored_root(self)
        target = workdir / cov.MANIFEST_REL
        doctored = json.loads(target.read_text(encoding="utf-8"))
        stranger = next(row["va"] for row in ledger()["ledger"]
                        if normalize_va(row["va"]) not in status_by_va)
        doctored["metrics"]["accounting_exclusions"] = \
            list(doctored["metrics"]["accounting_exclusions"]) + [stranger]
        target.write_text(json.dumps(doctored), encoding="utf-8")
        rebuilt = cov.build_report(workdir, include_local_db=False)
        self.assertIs(rebuilt["reconstruction"]["accounting_exclusions_all_integrated"], False)

    # -- 31: tautological percentages are marked, not reported ------------
    def test_tautological_percentages_are_null_and_flagged(self):
        tautological = ("total_internal_functions", "gameplay_functions",
                        "non_gameplay_functions", "staged_va", "blocked_va", "has_subsystem")
        for record in report()["dimensions"]:
            by_construction = (record.get("covered") is not None
                               and record.get("universe") not in (None, 0)
                               and record["covered"] == record["universe"])
            if record["id"] in tautological:
                self.assertTrue(by_construction, record["id"])
                self.assertIs(record["pct_is_tautological"], True, record["id"])
                self.assertIsNone(record["pct"], record["id"])
                self.assertIn("by construction", record["pct_null_because"])
            else:
                # No real measurement may be relabelled as tautological.
                self.assertIsNone(record.get("pct_is_tautological"), record["id"])
                if by_construction and record["available"]:
                    self.fail("%s is 100%% by construction but is not flagged tautological"
                              % record["id"])
        # And the flag is exactly those six -- no more, no fewer.
        self.assertEqual({record["id"] for record in report()["dimensions"]
                          if record.get("pct_is_tautological")}, set(tautological))
        # A real measurement next to them still reports a percentage.
        self.assertIsNotNone(dim("persisted_decompilation")["pct"])
        self.assertIsNotNone(dim("has_package_membership")["pct"])

    # -- 32: torn vs vanished directory members ---------------------------
    def test_torn_member_raises_and_vanished_member_is_tolerated(self):
        with tempfile.TemporaryDirectory(prefix="coverage-torn-") as scratch:
            base = Path(scratch)
            watched = base / "watched"
            watched.mkdir()
            (watched / "good.json").write_text('{"a": 1}', encoding="utf-8")
            # A deliberately TRUNCATED JSON file: present, but unparseable.
            (watched / "torn.json").write_text('{"a": 1, "b": [2, 3', encoding="utf-8")

            reader = cov._Reader(base)
            parts = reader.walk("watched")
            # The torn file is NOT silently dropped: it is recorded as drift.
            self.assertEqual([rel for rel, _ in parts], ["watched/good.json"])
            self.assertTrue(reader.drift, "a torn member must be recorded, not skipped")
            entry = [item for item in reader.drift if "torn.json" in item["key"]][0]
            self.assertEqual(entry["reason"], "unreadable_or_unparseable")
            self.assertIn("JSONDecodeError", entry["error"])
            with self.assertRaises(ToolError) as caught:
                reader.raise_on_drift()
            self.assertEqual(caught.exception.code, "input_changed_during_read")

            # A VANISHED member is benign: the tree genuinely is smaller now,
            # and nothing is torn. It needs its own clean directory so the torn
            # file above cannot leak into this walk.
            clean = base / "clean"
            clean.mkdir()
            (clean / "good.json").write_text('{"a": 1}', encoding="utf-8")
            gone = cov._Reader(base)
            original = cov._Reader.json

            def vanishing_json(self_reader, key):
                if key == "clean/good.json":
                    (base / key).unlink()
                return original(self_reader, key)

            cov._Reader.json = vanishing_json
            self.addCleanup(setattr, cov._Reader, "json", original)
            try:
                tolerated = gone.walk("clean")
            finally:
                cov._Reader.json = original
            self.assertEqual(tolerated, [])
            self.assertEqual(gone.vanished, ["clean/good.json"])
            self.assertEqual(gone.drift, [])
            gone.raise_on_drift()  # must not raise

    # -- 33: a torn member aborts a whole report -------------------------
    def test_torn_member_aborts_the_whole_report(self):
        workdir = _mirrored_root(self)
        metadata = workdir / cov.METADATA_REL
        metadata.mkdir(parents=True, exist_ok=True)
        (metadata / "torn.json").write_text('{"va": "0x00401000", "evidence', encoding="utf-8")
        with self.assertRaises(ToolError) as caught:
            cov.build_report(workdir, include_local_db=False)
        self.assertEqual(caught.exception.code, "input_changed_during_read")
        self.assertTrue(any("torn.json" in item["key"]
                            for item in caught.exception.details["drift"]))

    # -- 34: VOLATILE figures get structural invariants only -------------
    def test_volatile_counts_hold_structural_invariants(self):
        reconstruction = report()["reconstruction"]
        # reconstruction/metadata is being rewritten by another agent right now,
        # so these get invariants, never literals.
        self.assertGreaterEqual(reconstruction["metadata_files"], 0)
        self.assertLessEqual(reconstruction["metadata_distinct_vas"],
                             reconstruction["metadata_files"])
        self.assertLessEqual(reconstruction["metadata_in_universe"],
                             reconstruction["metadata_distinct_vas"])
        self.assertLessEqual(reconstruction["metadata_gameplay_vas"], 2149)
        self.assertEqual(reconstruction["metadata_vas_without_manifest_record"],
                         reconstruction["metadata_distinct_vas"]
                         - (reconstruction["metadata_distinct_vas"]
                            - reconstruction["metadata_vas_without_manifest_record"]))
        # reconstruction/staging likewise.
        self.assertGreaterEqual(reconstruction["staging_cpp"], 0)
        self.assertGreaterEqual(reconstruction["staging_hpp"], 0)
        self.assertGreaterEqual(reconstruction["staging_member_files"],
                                reconstruction["staging_cpp"] + reconstruction["staging_hpp"])
        self.assertLessEqual(dim("staged_va")["staging_vas_in_universe"],
                             reconstruction["staging_vas"])
        self.assertEqual(reconstruction["staging_member_files"],
                         dim("staged_va")["staging_member_files"])
        # Evidence classes other than CALLS walk metadata/, so: invariants only.
        classes = report()["evidence"]["classes"]
        for name, entry in classes.items():
            if name == "CALLS":
                continue
            self.assertGreaterEqual(entry["available_evidence"], 0, name)
            self.assertLessEqual(entry["available_evidence_gameplay"], 2149, name)
            self.assertLessEqual(entry["available_evidence_gameplay"],
                                 entry["available_evidence"], name)
        self.assertLessEqual(dim("evidence_abi")["gameplay_covered"], 2149)
        self.assertLessEqual(dim("evidence_calls")["gameplay_covered"], 2149)
        self.assertGreaterEqual(reconstruction["evidence_pack_count"], 0)
        # Every reported VA list is a set of well-formed VAs.
        for name, entry in classes.items():
            for value in dim(entry["dimension"]).get("vas", []):
                self.assertRegex(value, r"^[0-9a-f]{8}$", name)

    # -- 35: the git-index probe is disclosed -----------------------------
    def test_git_index_probe_is_disclosed_not_hidden(self):
        status = report()["generator_status"]
        probes = status["host_probes"]
        self.assertIsInstance(probes, list)
        self.assertTrue(probes)
        git_probe = [item for item in probes if "git" in item["probe"]]
        self.assertEqual(len(git_probe), 1, "the git-index probe must be disclosed exactly once")
        disclosed = git_probe[0]
        self.assertIs(disclosed["content_deterministic"], False)
        self.assertIn("git_tracked", " ".join(disclosed["feeds"]))
        self.assertTrue(disclosed["why"])
        self.assertTrue(disclosed["consequence"])
        # A directory can be "tracked" while only some members are; the reader
        # must not be invited to read git_tracked as "all of it survives a
        # fresh clone". metadata_dir and handoff_dir are exactly that case.
        partial = []
        for key in ("metadata_dir", "staging_dir", "handoff_dir", "decomp_gap_parts",
                    "evidence_dir"):
            entry = report()["snapshot"]["inputs"][key]
            self.assertIn("tracked_members", entry, key)
            self.assertIn("member_count", entry, key)
            self.assertLessEqual(entry["tracked_members"], entry["member_count"], key)
            self.assertIs(entry["tracked_members_is_all"],
                          entry["tracked_members"] == entry["member_count"], key)
            if entry["tracked_members"] < entry["member_count"]:
                partial.append(key)
        # The distinction is load-bearing here, not hypothetical: at least one
        # directory is partly tracked and partly not.
        self.assertTrue(partial, "no directory input has a mixed tracked/untracked membership")
        self.assertIn("metadata_dir", partial)
        # A directory the git index does not track at all can still have tracked
        # members (staging_dir), so the directory verdict is not a member summary.
        staging = report()["snapshot"]["inputs"]["staging_dir"]
        self.assertIs(staging["git_tracked"], False)
        self.assertGreater(staging["tracked_members"], 0)

    # -- 36: the static-gate claim is computed ---------------------------
    def test_static_gate_claim_is_computed_with_evidence(self):
        proof = dim("runtime_negative")
        self.assertIs(proof["all_non_zero_failed_counts_are_static_gates_is_computed"], True)
        evidence = proof["all_non_zero_failed_counts_are_static_gates_evidence"]
        counters = evidence["non_zero_failed_counters"]
        self.assertTrue(counters, "the corpus does contain non-zero failed counters")
        self.assertEqual(evidence["non_zero_failed_counter_count"], len(counters))
        self.assertEqual(evidence["unclassified_count"], 0)
        self.assertEqual(proof["all_non_zero_failed_counts_are_static_gates"],
                         evidence["unclassified_count"] == 0)
        # Every counter names its own check, its value, and its siblings, so a
        # reader can audit the verdict rather than take it on faith.
        for entry in counters:
            self.assertTrue(entry["path"])
            self.assertTrue(entry["check_name"])
            self.assertGreater(entry["failed"], 0)
            self.assertEqual(entry["classification"], "static_gate")
        self.assertTrue(any(entry["siblings"] for entry in counters),
                        "classification reads command/status/reason siblings, so at least one "
                        "counter must have them")
        # The classifier is real: a non-gate family is NOT classified as a gate.
        self.assertEqual(cov._classify_failed_counters(
            [("x", {"checks": {"fuzz": {"failed": 4, "command": "libFuzzer corpus run"}}})]
        )["unclassified_count"], 1)
        # ...and the published boolean is the classification, not a literal: put
        # an unclassifiable non-zero failure into the manifest and the flag must
        # flip to false. A hardcoded `true` cannot survive this.
        workdir = _mirrored_root(self)
        target = workdir / cov.MANIFEST_REL
        doctored = json.loads(target.read_text(encoding="utf-8"))
        doctored.setdefault("metrics", {}).setdefault("tests_passing", {})["fuzz_campaign"] = {
            "command": "libFuzzer corpus replay", "passed": 0, "failed": 17}
        target.write_text(json.dumps(doctored), encoding="utf-8")
        rebuilt = cov.build_report(workdir, include_local_db=False)["dimensions"]
        rebuilt_proof = [item for item in rebuilt if item["id"] == "runtime_negative"][0]
        self.assertIs(rebuilt_proof["all_non_zero_failed_counts_are_static_gates"], False)
        self.assertEqual(
            rebuilt_proof["all_non_zero_failed_counts_are_static_gates_evidence"]
            ["unclassified_count"], 1)


def _universe_bare():
    return {row["va"] for row in ledger()["ledger"] if row.get("va")}


def _derived_actionable_frontier():
    """Recompute the actionable frontier from the two tracked inputs."""
    universe = _universe_bare()
    with open(ROOT / cov.MANIFEST_REL, encoding="utf-8") as handle:
        manifest = json.load(handle)
    manifest_vas = {normalize_va(value)
                    for value in cov.manifest_record_vas(manifest["functions"])}
    with open(ROOT / cov.QUEUE_REL, encoding="utf-8") as handle:
        queue = json.load(handle)
    queue_vas = {normalize_va(row.get("va")) for row in queue["queue"]}
    queue_vas.discard(None)
    return queue_vas - manifest_vas


def _mirrored_root(case):
    """A throwaway root with symlinks to the tracked inputs coverage needs."""
    workdir = Path(tempfile.mkdtemp(prefix="coverage-mirror-"))
    case.addCleanup(shutil.rmtree, str(workdir), ignore_errors=True)
    for rel in (cov.LEDGER_REL, cov.MANIFEST_REL, cov.QUEUE_REL,
                cov.SEMANTIC_DECOMP_REL, cov.SEMANTIC_BLUEPRINT_REL):
        link = workdir / rel
        link.parent.mkdir(parents=True, exist_ok=True)
        if not link.exists():
            link.symlink_to(ROOT / rel)
    # The manifest must be a real, mutable file so a test can doctor it.
    target = workdir / cov.MANIFEST_REL
    if target.is_symlink():
        target.unlink()
        target.write_text((ROOT / cov.MANIFEST_REL).read_text(encoding="utf-8"),
                          encoding="utf-8")
    return workdir


class TestDisciplineTest(unittest.TestCase):
    """The suite's own guarantees: a determinism test must not be able to skip,
    and the input-change comparison must actually see a directory change."""

    def test_determinism_test_can_never_skip(self):
        source = inspect.getsource(CoverageTest.test_deterministic_output)
        self.assertNotIn("skipTest", source)
        self.assertNotIn("skipUnless", source)
        self.assertNotIn("expectedFailure", source)
        # The retry loop is allowed, but its terminal outcome must be a failure.
        self.assertIn("self.fail(", source)
        self.assertIn("for attempt in range(5)", source)
        # ...and the outcome is asserted unconditionally afterwards.
        self.assertIn("self.assertEqual(canonical_json(first), canonical_json(second))", source)

    def test_input_aggregate_sees_a_directory_only_change(self):
        left = {"snapshot": {"inputs": {
            "manifest": {"sha256": "a", "bytes": 10, "member_count": None},
            "metadata_dir": {"sha256": None, "bytes": 100, "member_count": 3},
        }}}
        # Same manifest; a directory input grew by one member. sha256 is null on
        # both sides -- exactly the case a sha256-only comparison misses.
        right = {"snapshot": {"inputs": {
            "manifest": {"sha256": "a", "bytes": 10, "member_count": None},
            "metadata_dir": {"sha256": None, "bytes": 140, "member_count": 4},
        }}}
        self.assertEqual(differing_inputs(left, left), set())
        self.assertEqual(differing_inputs(left, right), {"metadata_dir"})
        # A content change on a real file is seen too.
        changed = {"snapshot": {"inputs": {
            "manifest": {"sha256": "b", "bytes": 10, "member_count": None},
            "metadata_dir": {"sha256": None, "bytes": 100, "member_count": 3},
        }}}
        self.assertEqual(differing_inputs(left, changed), {"manifest"})
        # And the real report's directory inputs really do carry a null sha256,
        # which is why sha256 alone is not enough.
        inputs = report()["snapshot"]["inputs"]
        self.assertIsNone(inputs["metadata_dir"]["sha256"])
        self.assertIsNone(inputs["handoff_dir"]["sha256"])
        self.assertIsNotNone(inputs["manifest"]["sha256"])
        self.assertIsNotNone(inputs["staging_dir"]["sha256"])


if __name__ == "__main__":
    unittest.main()
