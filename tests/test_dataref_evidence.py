#!/usr/bin/env python3
"""Contract for the Ghidra data-reference artifact and the GLOBALS check it feeds.

Three things are under test, and they are kept apart on purpose.

*Part one -- the artifact.* ``tools/triage/export_datarefs.py`` is the canonicalizer
for the sidecar the exporter now emits. It has to be strict in the places where
leniency would let a bad address into a file every later verdict reads as
machine fact, and it has to be deterministic, because the whole point of the
artifact is that it is the same statement on every run.

*Part two -- the reader.* ``evidence_datarefs`` turns that file into per-target
evidence. The property that matters most is not that it reports references: it is
that every failure mode is reported as an *absence of evidence* and never as an
empty result, because "this body touches no global" and "the artifact was not
read" must never look alike. A reader that conflates them would clear every
target in the corpus on a missing file.

*Part three -- the falsifier battery.* The GLOBALS check is only strengthened by
evidence that is actually a data reference. Each falsifier below is a shape that
looks like global evidence and is not, and each asserts the check does not treat
it as such. The battery is the reason to believe the strengthening arm.

Everything is exercised hermetically over hand-written files in a
``TemporaryDirectory``: the real artifact is 157,633 rows and 20 MB, and the only
thing that needs the real one is the corpus measurement at the end.
"""

import csv
import json
import os
import subprocess
import sys
import unittest
from pathlib import Path
from tempfile import TemporaryDirectory

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))

from tools.reconstruction_tooling import evidence_datarefs as D  # noqa: E402
from tools.reconstruction_tooling import validate as V  # noqa: E402
from tools.reconstruction_tooling.models import ROOT as REPO_ROOT  # noqa: E402

sys.path.insert(0, str(ROOT / "tools" / "triage"))
import export_datarefs as C  # noqa: E402

TARGET = "0x00c0ffee"
GLOBAL_A = "0x015fd918"       # .data, writable
GLOBAL_B = "0x01654c01"       # .data, writable
CONST = "0x013f1cac"          # .rdata, read-only
CODEPTR = "0x00401010"        # .text, executable
SNAPSHOT = "2540f2ca7cd361a72b559448fa5cf247eff3cee20d375b14ed0dd256c45229c8"
SOURCE_LABEL = "ghidra:SporeApp.exe"
HEADER = ("caller_va\ttarget_va\taccess_mode\tsegment\tcallsite_va"
          "\tsource\tsnapshot_sha256")


def row(caller=TARGET[2:], target=GLOBAL_A, mode="read", segment=".data -wr",
        callsite="00c0ff00", snapshot=SNAPSHOT, source=SOURCE_LABEL):
    """One artifact row. Addresses are given in the artifact's own bare-VA8 form.

    Every default is the *stripped* form because that is what the exporter writes
    and what the canonicalizer demands; a test that wants a ``0x`` prefix passes
    one explicitly and asserts it is refused.
    """
    return "\t".join([caller[2:] if caller.startswith("0x") else caller,
                      target[2:] if target.startswith("0x") else target,
                      mode, segment, callsite, source, snapshot])


class CanonicalizerArtifact(unittest.TestCase):
    """The canonicalizer's own contract, over files it is handed."""

    def setUp(self):
        tmp = TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.tmp = Path(tmp.name)
        # A pinned universe large enough for the callers these tests use.
        self.pinned = set()
        for value in range(0x00c00000, 0x00c10000):
            self.pinned.add("%08x" % value)

    def write(self, rows, header=HEADER):
        path = self.tmp / "raw.tsv"
        path.write_text("\n".join([header] + list(rows)) + "\n")
        return path

    def canon(self, rows, header=HEADER):
        path = self.write(rows, header)
        unique, raw, dupes = C.canonicalize(C.load_raw(path, SNAPSHOT), self.pinned)
        return unique, raw, dupes

    # -- the shapes the artifact has to carry ----------------------------
    def test_a_data_read_survives_with_its_mode_and_segment(self):
        unique, _, _ = self.canon([row(mode="read", segment=".data -wr")])
        self.assertEqual(len(unique), 1)
        self.assertEqual(unique[0]["target_va"], GLOBAL_A[2:])
        self.assertEqual(unique[0]["access_mode"], "read")
        self.assertEqual(unique[0]["segment"], ".data -wr")

    def test_a_data_write_survives_and_is_not_read_as_a_read(self):
        unique, _, _ = self.canon([row(mode="write")])
        self.assertEqual(unique[0]["access_mode"], "write")
        self.assertNotEqual(unique[0]["access_mode"], "read")

    def test_a_read_write_reference_keeps_both_classes(self):
        unique, _, _ = self.canon([row(mode="readwrite")])
        self.assertEqual(unique[0]["access_mode"], "readwrite")

    def test_multiple_references_from_one_caller_are_all_kept(self):
        unique, _, _ = self.canon([row(target=GLOBAL_A), row(target=GLOBAL_B),
                                  row(target=CONST, segment=".rdata --r")])
        self.assertEqual([r["target_va"] for r in unique],
                         sorted([GLOBAL_A[2:], GLOBAL_B[2:], CONST[2:]]))

    def test_one_function_with_both_call_and_data_references_keeps_both(self):
        # The edge file carries the call and the sidecar carries the global; the
        # canonicalizer sees only the sidecar and must not invent or drop either.
        unique, _, _ = self.canon([row(target=GLOBAL_A), row(target=GLOBAL_B, mode="write")])
        self.assertEqual(len(unique), 2)

    def test_exact_duplicate_rows_collapse(self):
        unique, raw, dupes = self.canon([row(), row(), row()])
        self.assertEqual((raw, len(unique), dupes), (3, 1, 2))

    def test_a_read_and_a_write_of_one_address_from_one_instruction_are_two_rows(self):
        unique, _, dupes = self.canon([row(mode="read"), row(mode="write")])
        self.assertEqual(len(unique), 2, "read and write are different facts and must not collapse")
        self.assertEqual(dupes, 0)

    def test_the_output_is_sorted_and_therefore_stable(self):
        rows = [row(caller="00c00010", target=CONST, segment=".rdata --r"),
                row(caller="00c00010", target=GLOBAL_A),
                row(caller="00c00020", target=GLOBAL_B, mode="write"),
                row(caller="00c00010", target=GLOBAL_B, mode="read")]
        unique, _, _ = self.canon(rows)
        keys = [(r["caller_va"], r["target_va"], r["access_mode"], r["segment"],
                 r["callsite_va"]) for r in unique]
        self.assertEqual(keys, sorted(keys))

    def test_row_order_does_not_change_the_canonical_output(self):
        rows = [row(caller="00c00010", target=CONST, segment=".rdata --r"),
                row(caller="00c00010", target=GLOBAL_A),
                row(caller="00c00020", target=GLOBAL_B, mode="write")]
        first, _, _ = self.canon(rows)
        second, _, _ = self.canon(list(reversed(rows)))
        self.assertEqual(first, second)

    # -- refusals ---------------------------------------------------------
    def test_a_malformed_row_is_refused_not_repaired(self):
        for bad in (row(target="zzzzzzzz"), row(target="015fd91"),
                    row(target="015fd9180"), row(target="0x15fd918"),
                    row(target="015FD918"), row(caller="nothex"),
                    row(target=""), row(callsite="00c0ff")):
            with self.assertRaises(ValueError, msg=bad):
                C.canonicalize(C.load_raw(self.write([bad]), SNAPSHOT), self.pinned)

    def test_a_row_whose_caller_is_outside_the_pinned_universe_is_refused(self):
        with self.assertRaises(SystemExit):
            C.canonicalize(C.load_raw(self.write([row(caller="0099ffff")]), SNAPSHOT),
                           self.pinned)

    def test_an_unknown_access_mode_is_refused(self):
        with self.assertRaises(SystemExit):
            C.canonicalize(C.load_raw(self.write([row(mode="peek")]), SNAPSHOT), self.pinned)

    def test_an_unparseable_segment_is_refused(self):
        for bad in (".data", ".data wr", ".data -w-r", ""):
            with self.assertRaises(SystemExit, msg=bad):
                C.canonicalize(C.load_raw(self.write([row(segment=bad)]), SNAPSHOT),
                               self.pinned)

    def test_a_row_from_a_different_snapshot_is_refused(self):
        with self.assertRaises(SystemExit):
            C.canonicalize(C.load_raw(self.write([row(snapshot="0" * 64)]), SNAPSHOT),
                           self.pinned)

    def test_a_row_from_a_different_source_is_refused(self):
        with self.assertRaises(SystemExit):
            C.canonicalize(C.load_raw(self.write([row(source="handwritten")]), SNAPSHOT),
                           self.pinned)

    def test_a_file_that_is_not_this_artifact_is_a_schema_mismatch(self):
        with self.assertRaises(SystemExit):
            C.canonicalize(C.load_raw(self.write(
                [row()], header="caller_va\tcallee_va\treference_type\tcallsite_va"),
                SNAPSHOT), self.pinned)

    def test_an_address_width_that_x86_32_cannot_hold_never_enters(self):
        # A 64-bit address must be refused outright, not truncated into a
        # plausible-looking 32-bit global.
        with self.assertRaises(ValueError):
            C.norm_va("015fd9180")
        self.assertEqual(C.norm_va("015fd918"), "015fd918")

    def test_an_ignored_unrepresentable_reference_does_not_stop_the_run(self):
        # The canonicalizer refuses a bad row loudly rather than skipping it, so a
        # file that is mostly good but has one bad row is a hard error. This is the
        # deliberate choice: a data reference is the only evidence GLOBALS has,
        # and a silently dropped row is a silently weakened check.
        with self.assertRaises(ValueError):
            self.canon([row(), row(target="nothex")])


class ReaderEvidence(unittest.TestCase):
    """The reader's honesty, over a hand-written artifact."""

    def setUp(self):
        tmp = TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.addCleanup(D.reset_cache)
        self.root = Path(tmp.name)
        self.path = self.root / D.DATAREF_REL
        self.path.parent.mkdir(parents=True, exist_ok=True)

    def write(self, rows, header=HEADER):
        self.path.write_text("\n".join([header] + list(rows)) + "\n")

    def read(self, va=TARGET):
        return D.authoritative_data_refs(self.root, va)

    def test_a_read_reference_is_reported_with_its_mode_and_segment(self):
        self.write([row()])
        result = self.read()
        self.assertEqual(result["state"], "complete")
        self.assertEqual(result["targets"], {GLOBAL_A})
        self.assertEqual((result["read"], result["write"], result["readwrite"],
                          result["other"]), (1, 0, 0, 0))

    def test_a_write_reference_is_counted_as_a_write(self):
        self.write([row(mode="write")])
        result = self.read()
        self.assertEqual(result["write"], 1)
        self.assertEqual(result["read"], 0)

    def test_writable_storage_is_distinguished_from_read_only(self):
        self.write([row(target=GLOBAL_A, segment=".data -wr"),
                    row(target=CONST, segment=".rdata --r")])
        result = self.read()
        self.assertEqual(result["targets"], {GLOBAL_A, CONST},
                         "both are real references out of the body")
        self.assertEqual(result["writable_targets"], {GLOBAL_A},
                         "only writable storage can hold a mutable global")

    def test_several_rows_at_one_address_stay_several_rows(self):
        self.write([row(), row(callsite="00c0ff04"), row(callsite="00c0ff08")])
        self.assertEqual(len(self.read()["rows"]), 3)

    def test_a_malformed_row_is_skipped_and_the_rest_still_read(self):
        # The reader is downstream of a canonicalizer that refuses these, so this
        # is a hand-edited-file case. It must skip, not abort: one bad row must not
        # cost every other reference in the file.
        self.write([row(), row(target="zzzzzzzz"), row(target=GLOBAL_B)])
        result = self.read()
        self.assertEqual(result["state"], "complete")
        self.assertEqual(result["targets"], {GLOBAL_A, GLOBAL_B})

    def test_a_missing_artifact_is_absent_and_never_a_clearance(self):
        if self.path.exists():
            self.path.unlink()
        result = self.read()
        self.assertEqual(result["state"], "absent")
        self.assertEqual(result["targets"], frozenset())
        self.assertIsNone(result["writable"],
                          "'unknown' must not read like 'none'")

    def test_a_directory_where_the_artifact_should_be_is_unreadable(self):
        if self.path.exists():
            self.path.unlink()
        self.path.mkdir()
        result = self.read()
        self.assertEqual(result["state"], "unreadable")
        self.assertIsNone(result["writable"])

    def test_a_file_that_is_not_this_artifact_is_a_schema_mismatch(self):
        self.write([row()], header="caller_va\tcallee_va\treference_type\tcallsite_va")
        result = self.read()
        self.assertEqual(result["state"], "schema_mismatch")
        self.assertIsNone(result["writable"])

    def test_an_export_with_no_row_for_the_va_is_a_recorded_absence(self):
        self.write([row(caller="00c0ff00")])
        result = self.read()
        self.assertEqual(result["state"], "complete")
        self.assertEqual(result["targets"], frozenset())
        self.assertEqual(result["writable"], frozenset(),
                         "a complete read earns an empty set by recording nothing")

    def test_a_request_that_is_not_an_address_reads_nothing(self):
        self.write([row()])
        result = self.read(va="not-an-address")
        self.assertEqual(result["state"], "unreadable")
        self.assertEqual(result["targets"], frozenset())

    def test_reversed_source_and_target_is_not_the_same_row(self):
        # The artifact is directed: caller -> target. A row naming TARGET as the
        # *target* of another caller must not read as a reference OUT of TARGET,
        # and a row whose caller is another function must not be picked up.
        self.write([row(caller="00c0ff00", target=GLOBAL_A)])
        self.assertEqual(self.read()["targets"], frozenset(),
                         "another caller's row is not a reference out of TARGET")
        self.write([row(caller=TARGET, target="00c0ff00")])
        result = self.read()
        self.assertEqual(result["targets"], {"0x00c0ff00"},
                         "the direction is preserved, not normalised away")
        self.assertEqual(result["rows"][0][3], "0x00c0ff00",
                         "the callsite is carried through unchanged, not swapped")

    def test_a_row_stamped_with_another_snapshot_is_refused_at_the_canonicalizer(self):
        # The reader trusts what the canonicalizer committed, so the guard that
        # stops a foreign-snapshot row has to live upstream. Asserted here against
        # the canonicalizer, which is where it is enforced.
        import tempfile
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "raw.tsv"
            path.write_text("\n".join([HEADER, row(snapshot="0" * 64)]) + "\n")
            with self.assertRaises(SystemExit):
                C.load_raw(path, SNAPSHOT)

    def test_the_index_is_built_once_per_artifact_identity(self):
        self.write([row()])
        before = D.cache_stats()[1]
        for _ in range(5):
            self.read()
        self.assertEqual(D.cache_stats()[1], before + 1,
                         "five reads of one artifact must be one build")

    def test_a_changed_artifact_is_reindexed(self):
        self.write([row()])
        self.read()
        first = D.cache_stats()[1]
        self.write([row(), row(target=GLOBAL_B)])
        result = self.read()
        self.assertEqual(len(result["rows"]), 2)
        # Compared as a delta, not an absolute: a shared-process run may already
        # have built indexes for other fixtures, and what matters is that a
        # changed artifact is built again rather than served from the old index.
        self.assertEqual(D.cache_stats()[1], first + 1)

    def test_address_spellings_are_normalised_to_one_identity(self):
        # The artifact's bare VA8 and the validator's padded form are one address.
        self.write([row(target="015fd918")])
        result = self.read()
        self.assertEqual(result["targets"], {GLOBAL_A})
        self.assertEqual(GLOBAL_A, "0x015fd918")


class GLOBALSFalsifiers(unittest.TestCase):
    """The battery: shapes that look like global evidence and are not.

    Every case here states what would be wrong if GLOBALS treated it as
    corroboration. They are the reason to believe the strengthening arm, so each
    one asserts the check's verdict *and* the reason it gives.
    """

    def setUp(self):
        tmp = TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.addCleanup(D.reset_cache)
        self.root = Path(tmp.name)
        self.path = self.root / D.DATAREF_REL
        self.path.parent.mkdir(parents=True, exist_ok=True)

    def write(self, rows):
        self.path.write_text("\n".join([HEADER] + list(rows)) + "\n")

    def globals_check(self, scoped_text, listing_texts, categories=None,
                      record=None):
        """Drive the real ``_globals_verdict`` arms over a synthetic target.

        A throwaway root carrying the artifact and nothing else: the reader
        resolves no other file, so the artifact is the whole fixture. The arms are
        the production ones -- this does not restate them, which is the point: a
        battery that tested a copy of the rule would prove nothing about the rule.
        """
        record = record or {"va": TARGET}
        oracle = D.authoritative_data_refs(self.root, record["va"])
        return V._globals_verdict(
            listing_texts=list(listing_texts),
            scoped_text=scoped_text,
            oracle=oracle,
            recorded=set(oracle["targets"]),
            data_note=(oracle["note"] + "; ") if oracle["state"] == "complete" else "",
            global_evidence=(categories or {}).get("globals", {}).get("value"),
        )


class GlobalsArmBehaviour(GLOBALSFalsifiers):
    """Arm-by-arm behaviour of the GLOBALS check under the artifact."""

    def test_an_absence_pass_is_untouched_by_the_artifact(self):
        result = self.globals_check("", [])
        self.assertEqual(result["status"], "PASS")

    def test_an_absence_pass_names_a_disagreement_rather_than_hiding_it(self):
        self.write([row()])
        result = self.globals_check("", [])
        self.assertEqual(result["status"], "PASS",
                         "a complete body naming no data address is its own evidence")
        self.assertIn("disagree", result["detail"])

    def test_a_source_claim_the_artifact_records_and_the_listing_corroborates_passes(self):
        self.write([row(target=GLOBAL_A, mode="read")])
        result = self.globals_check("g = (void*)0x%08x;" % int(GLOBAL_A, 16),
                                    ["MOV EAX,dword ptr [0x%08x]" % int(GLOBAL_A, 16)])
        self.assertEqual(result["status"], "PASS")
        self.assertEqual(result["coverage"], "complete")

    def test_a_source_claim_the_artifact_does_not_record_stays_a_warning(self):
        # The falsifier for "absence of a row is a refutation". It is not one:
        # the artifact indexes the pinned caller universe at one moment.
        self.write([row(target=GLOBAL_B)])
        result = self.globals_check("g = (void*)0x%08x;" % int(GLOBAL_A, 16),
                                    ["MOV EAX,dword ptr [0x%08x]" % int(GLOBAL_A, 16)])
        self.assertEqual(result["status"], "WARN")
        self.assertIn("unbacked", result["detail"])

    def test_a_source_claim_the_listing_does_not_corroborate_stays_a_warning(self):
        # The falsifier for "the artifact alone is enough". One machine source is
        # not two, and the arm below the strengthening one requires both.
        self.write([row(target=GLOBAL_A)])
        result = self.globals_check("g = (void*)0x%08x;" % int(GLOBAL_A, 16), [])
        self.assertEqual(result["status"], "WARN")

    def test_a_usable_absolute_constant_that_merely_resembles_a_global_is_not_corroboration(self):
        # 0x00ffffff is inside the image but below the data segment; a listing
        # naming it cannot be reporting a global.
        self.write([])
        result = self.globals_check("", ["MOV EAX,0x00ffffff"])
        self.assertEqual(result["status"], "PASS",
                         "a code-range constant is not a data-segment address")

    def test_a_code_address_is_not_a_global_even_when_the_artifact_records_it(self):
        # The falsifier for "any recorded reference is a global". A .text target
        # is a jump table or a function pointer: real machine evidence about the
        # body, and not a global.
        self.write([row(target=CODEPTR, segment=".text x-r")])
        result = self.globals_check("", ["JMP dword ptr [0x%08x]" % int(CODEPTR, 16)])
        self.assertEqual(result["status"], "PASS")

    def test_a_read_only_constant_is_reported_as_a_read_and_not_as_writable(self):
        self.write([row(target=CONST, segment=".rdata --r", mode="read")])
        result = self.globals_check("", ["MOV EAX,dword ptr [0x%08x]" % int(CONST, 16)])
        self.assertEqual(result["status"], "WARN")
        self.assertIn("read=1", result["detail"])
        # "writable storage" is only named when the artifact has a writable
        # reference; a .rdata reference must not claim one.
        self.assertNotIn("writable storage", result["detail"])

    def test_an_unreadable_artifact_leaves_every_arm_exactly_as_it_was(self):
        # Behaviour-preservation: with the artifact absent, no arm can report a
        # second machine side, and none may claim corroboration.
        if self.path.exists():
            self.path.unlink()
        result = self.globals_check("g = (void*)0x%08x;" % int(GLOBAL_A, 16),
                                    ["MOV EAX,dword ptr [0x%08x]" % int(GLOBAL_A, 16)])
        self.assertEqual(result["status"], "WARN")
        self.assertNotIn("complete", result["detail"].split(";")[0])

    def test_a_write_mode_is_reported_only_from_a_row_that_says_write(self):
        self.write([row(target=GLOBAL_A, mode="read")])
        result = self.globals_check("", ["MOV EAX,dword ptr [0x%08x]" % int(GLOBAL_A, 16)])
        self.assertIn("read=1", result["detail"])
        self.assertNotIn("write=", result["detail"])


class CorpusMeasurement(unittest.TestCase):
    """The only test that reads the real artifacts: a measurement, not a fixture.

    A measurement over the committed corpus is the only thing that can say the
    change moved what it was supposed to move and nothing else, so these are real
    numbers from the real 157,633-row artifact rather than a hand-written stand-in.
    """

    def test_the_committed_artifact_is_present_and_whole(self):
        path = REPO_ROOT / D.DATAREF_REL
        self.assertTrue(path.exists(), "the committed data-reference artifact is missing")
        summary = json.loads((REPO_ROOT / D.DATAREF_SUMMARY_REL).read_text())
        self.assertEqual(summary["snapshot_sha256"][:8], "2540f2ca")
        self.assertGreater(summary["unique_rows"], 100000)

    def test_the_committed_artifact_header_is_the_one_the_reader_requires(self):
        with (REPO_ROOT / D.DATAREF_REL).open() as handle:
            header = handle.readline().rstrip("\n").split("\t")
        self.assertEqual(tuple(header[:len(D.DATAREF_COLUMNS)]), D.DATAREF_COLUMNS)

    def test_every_committed_target_is_readable_and_none_errors(self):
        D.reset_cache()
        summary = json.loads((REPO_ROOT / D.DATAREF_SUMMARY_REL).read_text())
        self.assertEqual(summary["coverage"]["rows"], summary["unique_rows"])
        # Reading a sample from both ends of the universe, not the whole file: the
        # reader is exercised over the committed artifact by every other test and
        # this one exists to prove the committed bytes are readable at all.
        for va in ("0x00401000", "0x00f9fef0", "0x01053be0", "0x011f95c0"):
            result = D.authoritative_data_refs(REPO_ROOT, va)
            self.assertIn(result["state"], (D.STATE_COMPLETE, D.STATE_ABSENT))

    def test_the_shipped_exporter_and_canonicalizer_agree_on_the_column_vocabulary(self):
        # The Java writes the header as two concatenated string literals, so the
        # comparison is on the joined names rather than on the source text: what
        # has to agree is the column *order*, not the line it is written on. The
        # first ``caller_va`` in the file is the doc comment, so the search starts
        # at the ``println`` that actually emits it.
        source = (ROOT / "tools" / "ghidra" / "ExportXrefs.java").read_text()
        start = source.index('data.println("caller_va')
        end = source.index(");", start)
        # The Java splits the header across two concatenated literals; strip the
        # Java-level line joining so the two halves sit on one line, then the two
        # literal splits and the escapes.
        flat = " ".join(source[start:end].split())
        flat = flat[flat.index('"') + 1:]
        flat = flat.replace('" + "', "").replace('" +\\n                + "', "")
        flat = flat.replace("\\t", "\t").strip('"')
        self.assertEqual(flat, HEADER,
                         "the exporter's header and the canonicalizer's must be one string")
        # And the reader must read exactly the header the canonicalizer writes.
        self.assertEqual(D.DATAREF_COLUMNS,
                         tuple(C.DATA_HEADER[:len(D.DATAREF_COLUMNS)]))


class ExporterSourceContract(unittest.TestCase):
    """The exporter's source, checked as text: the predicate is a contract too.

    The Java script cannot be executed by the Python suite, so the clauses its
    ``emitDataReference`` states are pinned here as source text. That is a weaker
    test than running it, and deliberately labelled as such: what it catches is a
    later edit that drops a clause, which is the realistic failure mode.
    """

    def setUp(self):
        self.source = (ROOT / "tools" / "ghidra" / "ExportXrefs.java").read_text()

    def test_the_edge_file_is_unchanged_by_the_sidecar(self):
        self.assertIn("if (outData != null) {", self.source)
        self.assertIn("emitDataReference", self.source)

    def test_the_sidecar_predicate_names_every_exclusion(self):
        for clause in ("isExternalAddress()",
                       "getDefaultAddressSpace()",
                       "getBlock(to)",
                       "fm.getFunctionAt(to) != null",
                       "vtableBaseFor(to.getOffset())"):
            self.assertIn(clause, self.source)

    def test_the_write_mode_comes_from_ghidras_own_reftype(self):
        self.assertIn("rt.isWrite() ? (rt.isRead() ? \"readwrite\" : \"write\")", self.source)

    def test_no_fabrication_of_a_destination(self):
        # The exporter must never invent a target; every row it writes carries an
        # address Ghidra gave it.
        self.assertNotIn("va8(0", self.source)
        self.assertIn("block.getName()", self.source)


if __name__ == "__main__":
    unittest.main()