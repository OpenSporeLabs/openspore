"""The complete xref evidence behind the CALLS check, and the wire-in that uses it.

``reconstruction/knowledge/index.json`` stores a *bounded* projection of the
Ghidra xref export: thirty edge rows per record, with ``edges_truncated`` set when
there were more. ``validate._machine_callees`` reads that window as the machine
callee set and warns on every record whose window is full, which is a permanent
``WARN`` on 149 of the 617 index records and disqualifying for a static pass.

This is the other half of the fix: read the export itself, whole, and let CALLS
adjudicate over that. The tests hold three lines at once.

* The reader is honest. A missing, unreadable or mis-shaped export is an explicit
  absence, never an empty callee set that could read as "this function calls
  nothing"; a read that *is* whole reports the row count beside the set, so a
  caller can tell a recorded absence from a missing read.
* The reader does not weaken the check. A named callee the complete export does
  not record is still a ``FAIL``; the export and the record's projection
  disagreeing is a finding that appears in the detail rather than being resolved
  silently in favour of one; and a missing export is never a clearance.
* The wire-in is behaviour-preserving where it can be. ``decide`` returns ``None``
  for every state that is not a complete read, so with the export unavailable the
  validator's own arms -- today's truncated warning included -- apply verbatim.

The reader is exercised hermetically over a hand-written TSV in a
``TemporaryDirectory``, so the >30-edge case is a 31-row file rather than the
27.8 MB export. The real corpus is used only for the pinned >30-edge regression
and the back-compat measurement, for the reason
``CallsExclusionBackCompat`` in ``test_validation_dimensions`` is: a measurement
over committed packs is the only thing that can say a change did not move
anything it was not supposed to.
"""

import json
import os
import unittest
from pathlib import Path
from tempfile import TemporaryDirectory

from tools.reconstruction_tooling import evidence
from tools.reconstruction_tooling import evidence_xrefs as X
from tools.reconstruction_tooling import validate as V
from tools.reconstruction_tooling.frontier import _INDEX_CACHE
from tools.reconstruction_tooling.models import ROOT as REPO_ROOT
from tools.reconstruction_knowledge import MAX_DEPENDENCY_EDGES
from tools.reconstruction_knowledge import XREF_REL as BUILDER_XREF_REL

TARGET = "0x00c0ffee"
HELPER = "0x00abcde1"
OTHER = "0x00aabb11"
THIRD = "0x00ddcc22"
CALLSITE = "0x00c0ff00"
EXT_TOKEN = "EXT:KERNEL32.DLL::QueryPerformanceCounter"
HEADER = "caller_va\tcallee_va\treference_type\tcallsite_va\tsource\tsnapshot_sha256"
MANIFEST_REL = "knowledgegraph/research/source-reconstruction-manifest.json"
QUEUE_REL = "knowledgegraph/triage/queue-f0e310e0-v6.json"
SEMANTIC_REL = "knowledgegraph/research/semantic-decomp.json"
METADATA_REL = "reconstruction/metadata/pkg_fixture/00c0ffee.json"
SOURCE_REL = "src/fixture_pkg/fixture.cpp"
DEFAULT_ABI = {"calling_convention": "__cdecl", "return_type": "int"}


def _row(caller, callee, kind="direct-call", callsite=CALLSITE):
    """One export row, with ``callee`` written verbatim.

    Verbatim is the point: a caller can pass an ``EXT:`` import token and get the
    shape the real export uses for a callee that is not an address.
    """
    return "%s\t%s\t%s\t%s\tghidra:SporeApp.exe\tsnap" % (caller, callee, kind, callsite)


def _write(path, payload):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(payload, encoding="utf-8")


def _edge_rows(callees, kind="direct-call"):
    """The ``dependencies.edges`` projection rows for one caller/callee set."""
    return [{"direction": "out", "other": callee, "reference_type": kind, "callsite": CALLSITE}
            for callee in callees]


# A complete seven-instruction body: a frame prologue, one conditional branch that
# closes inside the body, one displacement through the receiver, one call the
# export records, and no indirect transfer. The source span names the same one
# call and nothing else, so CALLS can reach every arm over it.
BODY = [{"address": "00c0ffee", "instruction": "PUSH EBP"},
        {"address": "00c0ffef", "instruction": "MOV EBP,ESP"},
        {"address": "00c0fff1", "instruction": "CMP ECX,0x0"},
        {"address": "00c0fff4", "instruction": "JZ 0x00c0fff9"},
        {"address": "00c0fff6", "instruction": "MOV EAX,dword ptr [ECX + 0x14]"},
        {"address": "00c0fff9", "instruction": "CALL 0x00abcde1"},
        {"address": "00c0fffe", "instruction": "RET"}]
LISTING = ([item["address"] for item in BODY], [item["instruction"] for item in BODY])
# A body with no outgoing transfer at all, so the "both oracles empty" arm has a
# fixture that genuinely contains nothing of the kind it claims nothing about.
STRAIGHT_BODY = [{"address": "00c0ffee", "instruction": "MOV EAX,0x7"},
                 {"address": "00c0fff1", "instruction": "RET"}]
SPAN_CALL = "  return helper_00abcde1(3);"


class ExportRoot(unittest.TestCase):
    """A throwaway root holding a hand-written xref export, and nothing else.

    Only the export: the reader resolves no other file, so a root with a TSV in it
    and nothing else is the whole fixture. Every read is therefore hermetic and
    fast, which is what lets the >30-edge case be a 31-row file.
    """

    def setUp(self):
        tmp = TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.addCleanup(X.reset_cache)
        self.root = Path(tmp.name)

    def export(self, rows, header=HEADER):
        _write(self.root / X.XREF_REL, "\n".join([header] + list(rows)) + "\n")
        return self.root

    def read(self, va, root=None):
        return X.authoritative_callees(root or self.root, va)

    def decide(self, *, callees, edges=None, truncated=False, root=None, va=TARGET,
               scoped_text=SPAN_CALL, listing=LISTING, source_path=Path(SOURCE_REL),
               record=None, edge_count=0):
        """``decide`` over a record whose projection holds ``edges``.

        ``listing`` is passed already resolved, the way ``validate`` resolves it,
        so a test states the listing it means instead of a pack that produces one.
        """
        dependencies = {"edges": _edge_rows(callees) if edges is None else edges,
                        "edges_truncated": truncated}
        if record is None:
            record = {"va": va, "name": "reconstruct_me_00c0ffee",
                      "normalized_symbol": "reconstruct_me_00c0ffee"}
        return X.decide(record=record, categories={}, abi_outer={}, abi_inner={},
                        listing=listing, scoped_text=scoped_text,
                        target_span={"name": "reconstruct_me_00c0ffee", "return_type": "int",
                                     "text": scoped_text},
                        source_path=source_path, dependencies=dependencies,
                        root=root or self.root)


class AuthoritativeReader(ExportRoot):
    """The reader, over a file small enough to write out in full."""

    def test_a_five_edge_record_reads_complete(self):
        self.export([_row(TARGET, HELPER), _row(TARGET, OTHER), _row(TARGET, THIRD),
                     _row(TARGET, HELPER, callsite="0x00c0ff10"),
                     _row(TARGET, OTHER, kind="thunk")])
        read = self.read(TARGET)
        self.assertEqual(read["state"], "complete")
        self.assertFalse(read["truncated"])
        self.assertEqual(read["va"], TARGET)
        self.assertEqual(read["callees"], frozenset({HELPER, OTHER, THIRD}))
        # Five rows, three distinct callees. The two counts are different facts and
        # the projection's cap truncates the first, not the second.
        self.assertEqual(read["edge_count"], 5)
        self.assertIn("5 outgoing call edge row(s) over 3 distinct address(es)", read["note"])

    def test_a_45_edge_record_is_complete_and_not_truncated(self):
        # The regression in miniature. Forty-five rows is well over the projection's
        # window, so a reader that read the projection instead of the export would
        # report a truncated set here -- and would be reporting it as the machine's
        # word about the function.
        callees = ["0x%08x" % (0x00401000 + step) for step in range(44)] + [HELPER]
        self.export([_row(TARGET, callee) for callee in callees])
        read = self.read(TARGET)
        self.assertEqual(read["state"], "complete")
        self.assertFalse(read["truncated"])
        self.assertEqual(read["edge_count"], 45)
        self.assertGreater(read["edge_count"], MAX_DEPENDENCY_EDGES)
        # The set is the whole of it, not a prefix of it.
        self.assertEqual(read["callees"], frozenset(callees))

    def test_a_missing_export_is_absent_and_never_a_clearance(self):
        read = self.read(TARGET)
        self.assertEqual(read["state"], "absent")
        self.assertTrue(read["truncated"])
        self.assertEqual(read["edge_count"], 0)
        self.assertIn(X.XREF_REL, read["note"])
        # An empty set is the shape that would read as "calls nothing", so the
        # state has to carry the absence -- and nothing may act on a degraded set.
        self.assertIsNone(self.decide(callees=[], root=self.root))

    def test_an_external_callee_stays_a_raw_name(self):
        # The real export's shape, verbatim: an external call's callee column holds
        # the import token and not an address (measured: all 5,481 external rows).
        self.export([_row(TARGET, EXT_TOKEN, kind="external"), _row(TARGET, HELPER)])
        read = self.read(TARGET)
        self.assertEqual(read["state"], "complete")
        # Counted as a call edge, because it is one; not address-comparable, because
        # there is no address to compare. That is exactly what
        # ``validate._machine_callees`` does with the same row.
        self.assertEqual(read["edge_count"], 2)
        self.assertEqual(read["callees"], frozenset({HELPER}))
        self.assertNotIn(EXT_TOKEN, read["callees"])
        self.assertIn("1 of those rows name an external import", read["note"])

    def test_every_call_reference_type_is_counted(self):
        self.export([_row(TARGET, HELPER, kind="direct-call"), _row(TARGET, OTHER, kind="thunk"),
                     _row(TARGET, THIRD, kind="computed-call"),
                     _row(TARGET, EXT_TOKEN, kind="external")])
        read = self.read(TARGET)
        self.assertEqual(read["edge_count"], 4)
        self.assertEqual(read["callees"], frozenset({HELPER, OTHER, THIRD}))
        # And the set the CALLS oracle derives from the same four rows agrees, which
        # is what lets the export replace the projection without changing a verdict.
        projection = {"edges": [
            {"direction": "out", "other": other, "reference_type": kind, "callsite": CALLSITE}
            for other, kind in ((HELPER, "direct-call"), (OTHER, "thunk"),
                                (THIRD, "computed-call"), (EXT_TOKEN, "external"))]}
        self.assertEqual(V._machine_callees(projection), set(read["callees"]))

    def test_a_data_reference_row_is_not_a_call_edge(self):
        # ``data-ref`` is a reference, not a call. Counting it would put an address
        # in the machine callee set that the body is never shown transferring to.
        self.export([_row(TARGET, HELPER), _row(TARGET, "013ef090", kind="data-ref"),
                     _row(TARGET, "013ef090", kind="vtable-ref")])
        read = self.read(TARGET)
        self.assertEqual(read["edge_count"], 1)
        self.assertEqual(read["callees"], frozenset({HELPER}))

    def test_an_incoming_edge_is_not_a_callee(self):
        # Direction, pinned where it is easiest to get wrong: the export is full of
        # rows where this VA is the ``callee_va``. Counting one as an out-edge would
        # make every high-fan-in function appear to call its own callers.
        self.export([_row(TARGET, HELPER), _row(OTHER, TARGET), _row(THIRD, TARGET)])
        read = self.read(TARGET)
        self.assertEqual(read["callees"], frozenset({HELPER}))
        self.assertEqual(read["edge_count"], 1)
        self.assertIn("2 incoming call edge row(s) reach it", read["note"])

    def test_a_row_with_fewer_than_four_fields_is_skipped(self):
        # ``load_xrefs`` gates rows at four fields. A reader that did not would count
        # rows the projection does not, and every count would disagree.
        _write(self.root / X.XREF_REL,
               "\n".join([HEADER, _row(TARGET, HELPER), "00c0ffee\tEXT:ONLY.TWO\tdirect-call"]) + "\n")
        read = self.read(TARGET)
        self.assertEqual(read["edge_count"], 1)
        self.assertEqual(read["callees"], frozenset({HELPER}))

    def test_a_file_that_is_not_an_export_is_a_schema_mismatch(self):
        self.export([_row(TARGET, HELPER)], header="from\tto\tkind\tsite")
        read = self.read(TARGET)
        self.assertEqual(read["state"], "schema_mismatch")
        self.assertTrue(read["truncated"])
        self.assertIn("declares columns", read["note"])
        self.assertIsNone(self.decide(callees=[]))

    def test_a_directory_where_the_export_should_be_is_unreadable(self):
        (self.root / X.XREF_REL).mkdir(parents=True)
        read = self.read(TARGET)
        self.assertEqual(read["state"], "unreadable")
        self.assertTrue(read["truncated"])
        self.assertIsNone(self.decide(callees=[]))

    def test_an_export_with_no_row_for_the_va_is_a_recorded_absence(self):
        # A VA the export says nothing about at all, in either direction.
        self.export([_row(OTHER, THIRD)])
        read = self.read(TARGET)
        # The file was read whole, so an empty set here is a fact about the export
        # and not a missing read -- which is the only reason an empty set is ever
        # safe to return, and the reason the degraded states return one only ever as
        # an absence.
        self.assertEqual(read["state"], "complete")
        self.assertFalse(read["truncated"])
        self.assertEqual(read["callees"], frozenset())
        self.assertIn("carries no outgoing call edge", read["note"])

    def test_a_request_that_is_not_an_address_reads_nothing(self):
        self.export([_row(TARGET, HELPER)])
        read = self.read("not-an-address")
        self.assertEqual(read["state"], "unreadable")
        self.assertTrue(read["truncated"])
        self.assertIn("not an address", read["note"])

    def test_the_index_is_built_once_per_export_identity(self):
        # The cost constraint the whole design answers: ``validate`` runs ~586 times
        # in a corpus sweep, and a 27.8 MB rescan per target is not available.
        self.export([_row(TARGET, HELPER)])
        X.reset_cache()
        for _ in range(50):
            self.read(TARGET)
        self.assertEqual(X.cache_stats(), (1, 1))

    def test_a_changed_export_is_reindexed(self):
        # The cache key is the file's identity and not its path: an export regenerated
        # under a running sweep must not be answered from the previous index.
        self.export([_row(TARGET, HELPER)])
        self.assertEqual(self.read(TARGET)["callees"], frozenset({HELPER}))
        path = self.root / X.XREF_REL
        stamp = path.stat().st_mtime_ns
        self.export([_row(TARGET, HELPER), _row(TARGET, OTHER)])
        os.utime(path, ns=(stamp, stamp + 10 ** 9))
        self.assertEqual(self.read(TARGET)["callees"], frozenset({HELPER, OTHER}))
        self.assertEqual(X.cache_stats()[1], 2)


class DecidePrecedence(ExportRoot):
    """Which arm the complete export reaches, and which it does not."""

    def test_a_complete_export_agreeing_with_the_listing_passes(self):
        self.export([_row(TARGET, HELPER)])
        check = self.decide(callees=[HELPER])
        self.assertEqual(check["status"], "PASS", check["detail"])
        self.assertEqual(check["coverage"], "complete")
        self.assertIn("machine-vs-machine rule", check["detail"])
        # The detail says which oracle it read, so a pass over the whole export is
        # not readable as a pass over a thirty-row window.
        self.assertIn("is read whole", check["detail"])

    def test_a_complete_export_disagreeing_with_the_listing_fails(self):
        self.export([_row(TARGET, HELPER), _row(TARGET, OTHER)])
        check = self.decide(callees=[HELPER, OTHER])
        self.assertEqual(check["status"], "FAIL", check["detail"])
        self.assertIn("machine-vs-machine rule", check["detail"])
        # Both directions are named, because either side could be the mistake.
        self.assertIn("export callee(s) the body does not show", check["detail"])
        self.assertIn(OTHER, check["detail"])

    def test_a_source_named_callee_the_export_does_not_record_is_a_fail(self):
        # The rule the wire-in must not weaken. The export is complete here, so the
        # absence is a fact about the machine and the named callee is a
        # contradiction -- not a "the oracle might not have seen it" review item.
        self.export([_row(TARGET, HELPER)])
        check = self.decide(callees=[HELPER],
                            scoped_text="  return helper_00abcde1(3) + helper_00aabb11(4);")
        self.assertEqual(check["status"], "FAIL", check["detail"])
        self.assertIn("source-vs-xref rule", check["detail"])
        self.assertIn(OTHER, check["detail"])

    def test_a_truncated_projection_no_longer_forces_a_warning(self):
        # The blocker itself. Thirty-one callees is one over the projection's window,
        # so the record carries ``edges_truncated``; the export records all of them,
        # so the flag is not evidence of a missing callee and must not reach the verdict.
        callees = ["0x%08x" % (0x00401000 + step) for step in range(30)] + [HELPER]
        self.export([_row(TARGET, callee) for callee in callees])
        # The projection holds a 30-row window, as the builder would have written it.
        check = self.decide(callees=callees, edges=_edge_rows(callees)[:MAX_DEPENDENCY_EDGES],
                            truncated=True, listing=(["00c0ffee", "00c0fff1"], ["MOV EAX,0x7", "RET"]),
                            scoped_text="  return 7;")
        self.assertNotEqual(check["status"], "WARN", check["detail"])
        self.assertNotIn("truncated at export time", check["detail"])
        # And the flag is accounted for rather than dropped.
        self.assertIn("edges_truncated flag is set", check["detail"])
        self.assertIn("31 outgoing call edge row(s)", check["detail"])

    def test_a_record_with_no_edge_list_defers(self):
        # The index's own record that the record was searched at all. The reader
        # cannot supply it -- a VA the export has no row for is indistinguishable
        # from a VA the export never covered -- so an unsearched record keeps
        # ``validate``'s own ``xref_present`` gate governing it, and an empty set is
        # never promoted over a projection that was never written.
        self.export([_row(TARGET, HELPER)])
        self.assertIsNone(X.decide(
            record={"va": TARGET, "name": "x"}, categories={}, abi_outer={}, abi_inner={},
            listing=None, scoped_text="", target_span={"text": ""},
            source_path=Path(SOURCE_REL), dependencies={"edges": None, "edges_truncated": False},
            root=self.root))
        self.assertIsNone(X.decide(
            record={"va": TARGET, "name": "x"}, categories={}, abi_outer={}, abi_inner={},
            listing=None, scoped_text="", target_span={"text": ""},
            source_path=Path(SOURCE_REL),
            dependencies={"edges_truncated": False}, root=self.root))

    def test_no_source_span_is_not_available(self):
        self.export([_row(TARGET, HELPER)])
        check = self.decide(callees=[HELPER], source_path=None)
        self.assertEqual(check["status"], "NOT_AVAILABLE")
        self.assertEqual(check["coverage"], "none")

    def test_an_empty_export_with_no_listing_is_not_available(self):
        # Neither oracle exists, so there is nothing to agree or disagree with. An
        # empty authoritative set is not on its own a clearance.
        self.export([_row(OTHER, TARGET)])
        check = self.decide(callees=[], listing=None)
        self.assertEqual(check["status"], "NOT_AVAILABLE")
        self.assertEqual(check["coverage"], "none")

    def test_both_oracles_empty_is_an_evidenced_absence(self):
        self.export([_row(OTHER, TARGET)])
        check = self.decide(callees=[], listing=(["00c0ffee", "00c0fff1"], ["MOV EAX,0x7", "RET"]),
                            scoped_text="  return 7;")
        self.assertEqual(check["status"], "PASS", check["detail"])
        self.assertEqual(check["coverage"], "complete")
        self.assertIn("each record no outgoing transfer", check["detail"])

    def test_a_record_with_no_listing_keeps_the_source_vs_xref_arms(self):
        self.export([_row(TARGET, HELPER)])
        check = self.decide(callees=[HELPER], listing=None)
        self.assertEqual(check["status"], "PASS", check["detail"])
        self.assertIn("no listing is available for the second machine side", check["detail"])
        check = self.decide(callees=[HELPER, OTHER], listing=None, scoped_text="  return 7;")
        self.assertEqual(check["status"], "WARN", check["detail"])
        self.assertIn("names no address-suffixed callee", check["detail"])

    def test_a_listing_jump_back_into_its_own_span_is_still_excluded(self):
        # The intra-procedural jump exclusion is part of the CALLS rule and this
        # module must not lose it, or a body with a loop reads as making a call to
        # its own first instruction.
        listing = (["00c0ffee", "00c0fff4", "00c10008", "00c1000c"],
                   ["MOV EAX,dword ptr [ESP + 0x4]", "JMP 0x00c10008",
                    "LEA EBX,[EDX + 0x18]", "RET"])
        self.export([_row(TARGET, HELPER)])
        check = self.decide(callees=[HELPER], listing=listing, scoped_text="  return 7;")
        self.assertIn("intra-procedural jump", check["detail"])
        self.assertIn("0x00c10008", check["detail"])


class RepoFixture(unittest.TestCase):
    """A throwaway repository built from the same canonical inputs as production.

    ``build_index`` is what produces the ``dependencies`` projection the check
    reads, so the projection in these fixtures is the real one -- truncation flag
    included, and included because the export is genuinely over the cap.

    ``drop_export`` removes the TSV *after* the index has been built. That is the
    shape the two layers are independent in: the index is a committed artefact and
    the export is a file, so "the export is unavailable" is a state a real
    checkout can be in while the index still projects thirty rows.
    """

    def build(self, source_text, edges, drop_export=False, listing=BODY):
        tmp = TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.addCleanup(_INDEX_CACHE.clear)
        self.addCleanup(X.reset_cache)
        root = Path(tmp.name)
        self.root = root
        _write(root / SOURCE_REL, source_text)
        _write(root / MANIFEST_REL,
               '{"schema":"openspore-source-reconstruction-manifest-1",'
               '"binary":{"sha256":"fixture","name":"SporeApp.exe","source":"fixture"},'
               '"functions":[{"va":"%s","normalized_symbol":"reconstruct_me_00c0ffee",'
               '"subsystem":"FIXTURE","package":"pkg_fixture","source_file":"%s",'
               '"body_status":"unresolved","observed_mechanics":[],'
               '"evidence_level":"SUPPORTED","runtime_gates":["gate-fixture"],'
               '"audit_runtime_validated":0}],'
               '"packages":[{"id":"pkg_fixture","status":"triage_only"}],"types":[]}'
               % (TARGET, SOURCE_REL))
        _write(root / QUEUE_REL, '{"schema":"openspore-triage-queue-1","queue":[]}')
        _write(root / SEMANTIC_REL, '{"schema":"openspore-semantic-decomp-1","records":[],'
                                    '"contradictions":[],"family_index":[]}')
        _write(root / X.XREF_REL, "\n".join([HEADER] + list(edges)) + "\n")
        _write(root / METADATA_REL, '{"va":"%s","abi":%s,"types":[]}'
               % (TARGET, json.dumps(DEFAULT_ABI)))
        pack = {
            "schema": "openspore-evidence-pack-1",
            "target": {"va": TARGET, "address_kind": "linked_va"},
            "evidence_state": "PERSISTED",
            "content_sha256": "0" * 64,
            "categories": {
                "abi": {"availability": "available", "value": {
                    "calling_convention": "__cdecl",
                    "receiver": {"register": "ECX", "offsets": [0, 4, 0x14], "bounds_only": True},
                    "parse": {"declared_count": len(listing), "degraded": False, "unparsed": 0},
                    "dispatch": {"indirect_calls": 0, "vtable_shaped_loads": 0}}},
                "disassembly": {"availability": "available",
                                "value": {"instructions": [dict(item) for item in listing]}},
            },
        }
        if drop_export:
            evidence._index(root)
            (root / X.XREF_REL).unlink()
        return V.validate(root=root, va=TARGET, evidence=pack, write=False)


class DeferralIsInvisible(RepoFixture):
    """With the export unavailable, every arm of the validator's own block applies.

    Asserted end to end rather than against ``decide``, because a deferral is only
    worth what it defers *to*: these say the export really is unreachable and the
    validator's verdict is still the one it was.
    """

    def _span(self, body):
        return "int __cdecl reconstruct_me_00c0ffee() {\n%s\n}\n" % body

    def test_a_truncated_projection_with_no_export_still_warns(self):
        edges = [_row(TARGET, HELPER)] + [_row(TARGET, "0x%08x" % (0x00401000 + step))
                                          for step in range(31)]
        report = self.build(self._span(SPAN_CALL), edges, drop_export=True)
        dependencies = V._record(evidence._index(self.root), TARGET)["dependencies"]
        self.assertTrue(dependencies["edges_truncated"])
        self.assertEqual(len(dependencies["edges"]), MAX_DEPENDENCY_EDGES)
        calls = report["static"]["checks"]["CALLS"]
        self.assertEqual(calls["status"], "WARN", calls["detail"])
        self.assertIn("truncated at export time", calls["detail"])
        self.assertNotIn("is read whole", calls["detail"])

    def test_an_untruncated_projection_with_no_export_keeps_its_arms(self):
        # The second half of the same claim: with the export gone and the
        # projection whole, the machine-vs-machine pass and the both-empty pass both
        # survive -- i.e. the deferral does not quietly turn a PASS into an absence.
        report = self.build(self._span(SPAN_CALL), [_row(TARGET, HELPER)], drop_export=True)
        calls = report["static"]["checks"]["CALLS"]
        self.assertEqual(calls["status"], "PASS", calls["detail"])
        self.assertIn("machine-vs-machine rule", calls["detail"])
        report = self.build(self._span("  return 7;"), [_row(OTHER, TARGET)], drop_export=True,
                            listing=STRAIGHT_BODY)
        calls = report["static"]["checks"]["CALLS"]
        self.assertEqual(calls["status"], "PASS", calls["detail"])
        self.assertIn("each record no outgoing transfer", calls["detail"])

    def test_the_same_repository_passes_with_the_export_present(self):
        # The control for the two tests above: same fixture, export present, and the
        # reader is reached. Without it, "the verdict is unchanged" could be true
        # for the wrong reason.
        report = self.build(self._span(SPAN_CALL), [_row(TARGET, HELPER)], drop_export=False)
        self.assertEqual(evidence._index(self.root)["records"][TARGET]
                         ["dependencies"]["edges_truncated"], False)
        read = X.authoritative_callees(self.root, TARGET)
        self.assertEqual(read["state"], "complete")
        self.assertEqual(read["callees"], frozenset({HELPER}))
        self.assertEqual(report["static"]["checks"]["CALLS"]["status"], "PASS")


class MutationTests(ExportRoot):
    """The two ways widening the evidence can hide something, held shut.

    Both stub ``authoritative_callees`` -- the one seam through which the complete
    set enters -- so the reader itself is not what is under test: what is under
    test is that whatever the reader says has to be visible in the verdict.
    """

    def _widen(self, **changes):
        original = X.authoritative_callees

        def mutated(root, va):
            read = original(root, va)
            read.update(changes)
            return read

        X.authoritative_callees = mutated
        self.addCleanup(setattr, X, "authoritative_callees", original)

    def test_a_callee_only_the_export_has_is_surfaced_not_hidden(self):
        self.export([_row(TARGET, HELPER)])
        self._widen(callees=frozenset({HELPER, OTHER}), edge_count=2)
        check = self.decide(callees=[HELPER])
        # A widened machine side disagrees with a bounded projection. The check still
        # fails on the machine-vs-machine rule, and the detail has to say *why* --
        # otherwise the same PASS would be reachable with the projection and
        # reachable for a different reason with the export, and no reader could tell
        # the two apart.
        self.assertEqual(check["status"], "FAIL", check["detail"])
        self.assertIn("dependency edge list is a scheduler projection", check["detail"])
        self.assertIn("1 callee(s) the export records are absent from it", check["detail"])
        self.assertIn(OTHER, check["detail"])

    def test_a_pass_becomes_a_fail_when_the_export_does_not_carry_the_claim(self):
        # The mutation that matters: the export is the oracle, so removing an edge
        # from it must remove a clearance, not leave one standing on the projection.
        self.export([_row(TARGET, HELPER)])
        baseline = self.decide(callees=[HELPER])
        self.assertEqual(baseline["status"], "PASS", baseline["detail"])
        self._widen(callees=frozenset())
        check = self.decide(callees=[HELPER])
        self.assertEqual(check["status"], "FAIL", check["detail"])
        self.assertIn("source-vs-xref rule", check["detail"])
        self.assertIn(HELPER, check["detail"])

    def test_a_projection_that_names_what_the_export_does_not_is_reported(self):
        # The other direction. Truncation cannot produce it -- the projection is a
        # prefix of the same rows -- so it means the index and the export on disk
        # disagree, which is a finding about the evidence and is named as one.
        self.export([_row(TARGET, OTHER)])
        check = self.decide(callees=[OTHER], edges=_edge_rows([HELPER]),
                            listing=(["00c0ffee", "00c0fff1"], ["MOV EAX,0x7", "RET"]),
                            scoped_text="  return 7;")
        self.assertIn("the projection names that this export does not record", check["detail"])
        self.assertIn(HELPER, check["detail"])

    def test_a_long_disagreement_is_summarised_with_a_true_count(self):
        # 0x0102df20's shape: 60 distinct callees against a 30-row window. The detail
        # has to stay readable, and the count beside the truncated list has to be the
        # true one rather than the number that fitted.
        callees = ["0x%08x" % (0x00401000 + step) for step in range(60)]
        self.export([_row(TARGET, callee) for callee in callees])
        check = self.decide(callees=callees, edges=_edge_rows(callees)[:MAX_DEPENDENCY_EDGES],
                            listing=(["00c0ffee", "00c0fff1"], ["MOV EAX,0x7", "RET"]),
                            scoped_text="  return 7;")
        # 60 export callees, a 30-row window: the clause names what the window lost
        # and summarises past twelve addresses, with the true count beside it.
        self.assertIn("30 callee(s) the export records are absent from it", check["detail"])
        self.assertIn("60 outgoing call edge row(s) and 60 distinct callee(s) the export records",
                      check["detail"])
        self.assertIn("and %d more" % (30 - X.MAX_NAMED_ADDRESSES), check["detail"])


# --------------------------------------------------------------------------
# Drift guards. This module restates three constants and the check-dict shape
# from ``validate``; if the validator moves them these fail, rather than the module
# quietly producing a differently-shaped check or reading a different set of
# reference types as a call.
# --------------------------------------------------------------------------
class DriftGuards(unittest.TestCase):

    def test_the_export_path_is_the_index_builders(self):
        self.assertEqual(X.XREF_REL, BUILDER_XREF_REL)

    def test_the_call_reference_types_are_the_validators(self):
        self.assertEqual(X.CALL_REFERENCE_TYPES, V.CALL_REFERENCE_TYPES)

    def test_the_projection_cap_is_the_index_builders(self):
        self.assertEqual(X.MAX_PROJECTED_EDGES, MAX_DEPENDENCY_EDGES)

    def test_the_evidence_paths_are_the_validators(self):
        self.assertEqual(X.INDEX_REL, V.INDEX_REL)
        self.assertEqual(X.EVIDENCE_REL, V.EVIDENCE_REL)

    def test_the_check_dict_has_the_validators_shape(self):
        self.assertEqual(X._check("PASS", "d", "complete", ["a"]),
                         V._check("PASS", "d", "complete", ["a"]))
        self.assertEqual(X._check("PASS", "d")["evidence"], [])


class RealCorpusRegression(unittest.TestCase):
    """The >30-edge regression, pinned against the committed export and index.

    Both counts are pinned rather than recomputed, because the point of the test
    is that the reader and the committed projection differ *by these amounts* on
    *these* targets: a change to the cap or to the export has to be a deliberate
    act that fails here.
    """

    # 0x00588570, ``Editors::cEditor::OnMouseDown``: 30 projected rows, all
    # outgoing, over 20 distinct callees; the export records 203 outgoing rows over
    # 92 distinct callees. 203 > 30, so this is the case the task names -- a record
    # whose projection is full and whose callee set is genuinely truncated.
    FAN_OUT = "0x00588570"
    FAN_OUT_NAME = "Editors::cEditor::OnMouseDown"
    FAN_OUT_PROJECTED_ROWS = 30
    FAN_OUT_PROJECTED_CALLEES = 20
    FAN_OUT_TRUE_ROWS = 203
    FAN_OUT_TRUE_CALLEES = 92
    # 0x0102df20: the worse shape. 30 projected rows mixing 1 incoming and 29
    # outgoing, so only 16 distinct callees survive the window; the export records
    # 236 outgoing rows over 104 distinct callees.
    FAN_IN = "0x0102df20"
    FAN_IN_PROJECTED_ROWS = 30
    FAN_IN_PROJECTED_CALLEES = 16
    FAN_IN_TRUE_ROWS = 236
    FAN_IN_TRUE_CALLEES = 104
    FAN_IN_TRUE_INCOMING = 1
    # 0x00b3d300: the false truncation. Its whole 30-row window is incoming edges,
    # so it carries ``edges_truncated`` with a callee set of exactly zero.
    ALL_IN = "0x00b3d300"
    ALL_IN_TRUE_INCOMING = 1941
    CASES = ((FAN_OUT, FAN_OUT_PROJECTED_ROWS, FAN_OUT_PROJECTED_CALLEES, FAN_OUT_TRUE_ROWS,
              FAN_OUT_TRUE_CALLEES),
             (FAN_IN, FAN_IN_PROJECTED_ROWS, FAN_IN_PROJECTED_CALLEES, FAN_IN_TRUE_ROWS,
              FAN_IN_TRUE_CALLEES))

    def setUp(self):
        X.reset_cache()
        self.addCleanup(X.reset_cache)
        self.index = json.loads((REPO_ROOT / "reconstruction/knowledge/index.json")
                                .read_text(encoding="utf-8"))

    def _dependencies(self, va):
        dependencies = self.index["records"][va]["dependencies"]
        self.assertTrue(dependencies["edges_truncated"],
                        "%s is the regression target precisely because its window is full" % va)
        self.assertEqual(len(dependencies["edges"]), MAX_DEPENDENCY_EDGES)
        return dependencies

    def test_the_projection_is_full_and_the_export_is_not(self):
        for va, rows, callees, true_rows, true_callees in self.CASES:
            with self.subTest(va=va):
                dependencies = self._dependencies(va)
                read = X.authoritative_callees(REPO_ROOT, va)
                self.assertEqual(read["state"], "complete")
                self.assertFalse(read["truncated"])
                # The blocker: more than thirty edges in the complete export, read as
                # complete, with the record's own cap sitting beside it.
                self.assertGreater(read["edge_count"], MAX_DEPENDENCY_EDGES)
                self.assertEqual(read["edge_count"], true_rows)
                self.assertEqual(len(read["callees"]), true_callees)
                # And the projection really does lose what the export keeps.
                self.assertEqual(len(dependencies["edges"]), rows)
                projected = V._machine_callees(dependencies)
                self.assertEqual(len(projected), callees)
                self.assertLess(len(projected), true_callees)
                self.assertTrue(projected < read["callees"],
                                "%s: the projection must be a strict subset of the export" % va)

    def test_the_identity_of_the_regression_targets(self):
        self.assertEqual(self.index["records"][self.FAN_OUT].get("name"), self.FAN_OUT_NAME)
        dependencies = self._dependencies(self.FAN_IN)
        self.assertEqual({row["direction"] for row in dependencies["edges"]}, {"in", "out"})
        read = X.authoritative_callees(REPO_ROOT, self.FAN_IN)
        self.assertIn("%d incoming call edge row(s) reach it" % self.FAN_IN_TRUE_INCOMING,
                      read["note"])

    def test_the_incoming_edge_shape(self):
        # The 124-of-149 false truncation on its clearest example: a full window
        # spent on incoming edges, so a target with 1,941 callers and 0 callees
        # carries the same flag as one whose callee set really was cut.
        dependencies = self._dependencies(self.ALL_IN)
        read = X.authoritative_callees(REPO_ROOT, self.ALL_IN)
        self.assertEqual(read["callees"], frozenset())
        self.assertEqual(read["edge_count"], 0)
        self.assertIn("%d incoming call edge row(s)" % self.ALL_IN_TRUE_INCOMING, read["note"])
        self.assertEqual({row["direction"] for row in dependencies["edges"]}, {"in"})

    def test_the_reader_covers_every_record_the_projection_covers(self):
        # The parity that makes widening the evidence safe. Over all 618 records the
        # export and the projection name the same callee set wherever the projection
        # is not truncated, and the export is a strict superset everywhere it is. A
        # disagreement on an untruncated record would mean the reader and the index
        # were built from different things, and every verdict computed from them
        # would be a comparison of two different questions.
        agree = disagree = 0
        for va, record in self.index["records"].items():
            dependencies = record.get("dependencies") or {}
            projected = V._machine_callees(dependencies)
            read = X.authoritative_callees(REPO_ROOT, va)
            self.assertEqual(read["state"], "complete", va)
            if read["callees"] == projected:
                agree += 1
                continue
            self.assertTrue(dependencies.get("edges_truncated"),
                            "%s disagrees with the export but was not truncated" % va)
            self.assertTrue(projected < read["callees"],
                            "%s: the projection must be a strict subset of the export" % va)
            disagree += 1
        self.assertEqual((agree, disagree), (540, 78))
        # One pass for 618 records: the cost constraint, measured.
        self.assertEqual(X.cache_stats(), (1, 1))


# --------------------------------------------------------------------------
# The corpus measurement, in the shape ``CallsExclusionBackCompat`` establishes.
# --------------------------------------------------------------------------
def _aggregate(checks):
    """``validate``'s static ladder, restated so a substituted verdict can be scored.

    ``validate`` inlines the ladder in its return, so there is no helper to call.
    The first assertion in the measurement below re-derives the aggregate from
    every unmodified report and requires it to equal what ``validate`` reported,
    so a drift in this copy is a failing test rather than a quietly wrong
    measurement.
    """
    values = [check["status"] for check in checks.values()]
    if "FAIL" in values:
        return "FAIL"
    if "UNKNOWN" in values:
        return "UNKNOWN"
    if "NOT_AVAILABLE" in values:
        return "NOT_AVAILABLE"
    if "WARN" in values:
        return "WARN"
    return "PASS"


class CorpusBackCompat(unittest.TestCase):
    """Only CALLS may move, and only where the complete export says something new.

    ``validate`` is not wired to ``decide`` -- wiring it in is the orchestrator's
    edit -- so the live side here is the real ``decide`` applied over the
    validator's own resolved inputs and the off side is ``validate`` untouched. The
    two differ in exactly the one thing being measured: whether the CALLS verdict
    was taken over the complete export or over the thirty-row projection.
    Nothing is written: both sides run over committed packs with ``write=False``.
    """

    PACK_GLOB = "reconstruction/evidence/*/evidence.json"
    # The validator's own severity order, restated so "weakened" has a meaning
    # independent of the aggregate: FAIL, UNKNOWN, NOT_AVAILABLE, WARN, PASS.
    LADDER = ("FAIL", "UNKNOWN", "NOT_AVAILABLE", "WARN", "PASS")

    def _targets(self):
        return ["0x" + path.parent.name for path in sorted(REPO_ROOT.glob(self.PACK_GLOB))]

    def _resolve(self, va):
        """``decide``'s arguments, resolved as ``validate`` resolves them.

        ``validate`` does not put the pack it judged in the report, so it is read
        from the path the pack lives at. A resolution failure is collected, never
        raised: a target this measurement could not resolve is a hole in the
        measurement and must be reported as one, not skipped quietly.
        """
        pack = json.loads((REPO_ROOT / "reconstruction/evidence" / va[2:] / "evidence.json")
                          .read_text(encoding="utf-8"))
        categories = pack.get("categories") or {}
        record = V._record(evidence._index(REPO_ROOT), va)
        source = V._source(REPO_ROOT, record)
        source_path = source["path"] if source else None
        span = V._target_span(V._read_source(source_path), record)
        outer, inner = V._abi_envelope(categories)
        return dict(record=record, categories=categories, abi_outer=outer, abi_inner=inner,
                    listing=V._listing(categories),
                    scoped_text=span.get("text", "") if span else "",
                    target_span=span, source_path=source_path,
                    dependencies=record.get("dependencies") or {}, root=REPO_ROOT)

    @staticmethod
    def _rule(detail):
        """Which of the check's own rules the verdict was reached under."""
        for rule in ("machine-vs-machine rule", "source-vs-xref rule"):
            if rule in detail:
                return rule
        return None

    def test_only_calls_moves_and_nothing_is_weakened(self):
        targets = self._targets()
        self.assertTrue(targets, "no evidence packs on disk to measure against")
        X.reset_cache()
        self.addCleanup(X.reset_cache)
        before_counts, after_counts = {}, {}
        changed, earned, aggregates, drifted = [], [], [], []
        for target in targets:
            report = V.validate(va=target, write=False)
            checks = report["static"]["checks"]
            off = checks["CALLS"]["status"]
            before_counts[off] = before_counts.get(off, 0) + 1
            # The ladder copy is only trustworthy if it reproduces what the validator
            # itself reported, on every pack, before anything is substituted.
            self.assertEqual(_aggregate(checks), report["static"]["status"], target)
            try:
                resolved = self._resolve(target)
                check = X.decide(**resolved)
            except Exception as exc:  # a resolution failure must not read as a verdict
                drifted.append((target, "resolve failed: %s" % exc))
                continue
            if check is None:
                # The export was not read whole: the validator's own verdict stands,
                # unchanged, and that is the case the wire-in must be invisible in.
                after_counts[off] = after_counts.get(off, 0) + 1
                continue
            on = check["status"]
            after_counts[on] = after_counts.get(on, 0) + 1
            # The substituted report, diffed check by check. "Only CALLS moves" is the
            # claim this measurement exists to support, so it is measured over the
            # dicts rather than asserted from the fact that only one key was assigned.
            after = {name: dict(value) for name, value in checks.items()}
            after["CALLS"] = check
            for name in sorted(checks):
                if after[name]["status"] != checks[name]["status"]:
                    self.assertEqual(name, "CALLS",
                                     "the complete export moved %s on %s (%s -> %s)"
                                     % (name, target, checks[name]["status"], after[name]["status"]))
            if _aggregate(after) != report["static"]["status"]:
                aggregates.append((target, report["static"]["status"], _aggregate(after)))
            if on == off:
                continue
            changed.append((target, off, on))
            # The ladder reads left to right from the strongest verdict to the
            # weakest, so ``index(on) > index(off)`` is a move to a weaker verdict.
            if self.LADDER.index(on) <= self.LADDER.index(off):
                continue
            # A move to a weaker verdict is only admissible if the wider evidence
            # *earned* it rather than the wider evidence having removed a claim. Every
            # such verdict is therefore re-checked here from the reader's own output
            # and not from the check's word about itself: the pass has to name a rule,
            # the source's claims have to be inside the complete callee set, and the
            # pass must not be standing on nothing at all.
            self.assertEqual(on, "PASS", "the complete export moved %s on %s to %s (%s -> %s)"
                             % (target, target, on, off, on))
            rule = self._rule(check["detail"])
            self.assertIsNotNone(rule, "%s reached PASS on %s naming no rule: %s"
                                 % (target, rule, check["detail"]))
            read = X.authoritative_callees(REPO_ROOT, target)
            self.assertEqual(read["state"], "complete", target)
            source_calls = V._callee_addresses(resolved["scoped_text"], resolved["record"])
            self.assertEqual(source_calls - read["callees"], set(),
                             "%s passed over a source claim the complete export does not record" % target)
            self.assertTrue(read["callees"] or resolved["listing"] is not None,
                            "%s passed as an absence with no export row and no listing" % target)
            earned.append((target, off, on, rule))
        self.assertEqual(drifted, [], "a target could not be resolved over the complete export")
        # One pass for the whole sweep: the cost constraint, measured.
        self.assertEqual(X.cache_stats()[1], 1, "the corpus sweep must pay for one export pass")
        print("\nCALLS authoritative-export back-compat: %d pack(s) measured; CALLS before %s, after "
              "%s; %d CALLS status(es) moved (0 outside CALLS, %d static aggregate(s) moved); %d moved "
              "to a weaker verdict, each re-checked against the reader and found earned: %s"
              % (len(targets), dict(sorted(before_counts.items())), dict(sorted(after_counts.items())),
                 len(changed), len(aggregates), len(earned),
                 ", ".join("%s %s->%s via the %s" % entry for entry in earned) or "none"))
        # Recorded on the case rather than returned: a test method that returns a
        # value is deprecated, and the moves are worth keeping for a reader.
        self.moved = changed


if __name__ == "__main__":
    unittest.main()
