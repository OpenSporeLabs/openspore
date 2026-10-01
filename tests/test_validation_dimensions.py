"""Fixtures for the two validation dimensions.

The validator returns a STATIC verdict on a reconstruction and a RUNTIME verdict
for the original process. These tests hold three lines at once:

* a genuinely strong static candidate can reach ``STATIC: PASS``;
* a candidate never reaches ``PASS`` merely because evidence is absent;
* a static ``PASS`` never reads as, or becomes, a runtime claim.

The last point is the one the whole split exists to protect, so it is asserted
from several directions rather than once.

The six per-dimension checks share one rule for reaching ``PASS``, and the tests
below hold both halves of it for each of them: the machine evidence must be
complete and bounded for that dimension, and the reconstruction must either make
no claim in it or have every claim grounded in that evidence. So each dimension
is tested for a grounded pass, an *evidenced absence* pass (nothing there, and a
complete listing is the evidence), a ``NOT_AVAILABLE`` where the evidence is
missing, and a ``WARN``/``FAIL`` where the claim is ungrounded or refuted.
"""

import json
import unittest
from pathlib import Path
from tempfile import TemporaryDirectory

from tools.reconstruction_tooling import validate as V
from tools.reconstruction_tooling.frontier import _INDEX_CACHE
from tools.reconstruction_tooling.models import ROOT as REPO_ROOT
from tools.reconstruction_knowledge import build_index

TARGET = "0x00c0ffee"
HELPER = "00abcde1"
MANIFEST_REL = "knowledgegraph/research/source-reconstruction-manifest.json"
QUEUE_REL = "knowledgegraph/triage/queue-f0e310e0-v6.json"
SEMANTIC_REL = "knowledgegraph/research/semantic-decomp.json"
XREF_REL = "knowledgegraph/triage/xrefs-2540f2ca.tsv"
METADATA_REL = "reconstruction/metadata/pkg_fixture/00c0ffee.json"
DEFAULT_ABI = {"calling_convention": "__cdecl", "return_type": "int"}
SOURCE_REL = "src/fixture_pkg/fixture.cpp"
EVIDENCE_REL = "reconstruction/evidence"
PACK_REL = EVIDENCE_REL + "/" + TARGET[2:] + "/evidence.json"


def _span(body, name="reconstruct_me_00c0ffee", returns="int", convention="__cdecl"):
    return "%s %s %s() {\n%s\n}\n" % (returns, convention, name, body)


def _category(available, value=None):
    return {"availability": "available" if available else "unavailable",
            "evidence_state": "PERSISTED" if available else "MISSING",
            "evidence_level": "SUPPORTED" if available else "UNKNOWN",
            "provenance": [], "value": value if available else None, "reason": None}


def _pack(**categories):
    """An evidence pack. Only the keys a check reads need to be present."""
    base = {
        "abi": _category(False),
        "types": _category(False),
        "globals": _category(False),
        "vtables": _category(False),
        "ghidra_function": _category(False),
        "disassembly": _category(False),
        "decompilation": _category(False),
        # The runtime category is a reserved slot: it is never searched, so it is
        # never available. A test that expects a static PASS must still succeed
        # with this present and unavailable -- that is the coupling being removed.
        "runtime": _category(False),
        "runtime_metadata": _category(True, {"gates": ["gate-fixture-runtime"], "validated": 0}),
        "function_identity": _category(True, {"va": TARGET}),
        "status": _category(True, {"status": "candidate"}),
    }
    for key, value in categories.items():
        if isinstance(value, tuple):
            base[key] = _category(value[0], value[1])
        else:
            base[key] = value
    return {"schema": "openspore-evidence-pack-1",
            "target": {"va": TARGET, "address_kind": "linked_va"},
            "evidence_state": "PERSISTED",
            "content_sha256": "0" * 64,
            "categories": base,
            "record": {}}


def _write(path, payload):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(payload, encoding="utf-8")


def _pack_json(pack, corrupt=False):
    """The pack exactly as ``evidence.collect`` would have written it to disk.

    The digest is stamped the way ``collect`` stamps it: over the pack with
    ``content_sha256`` set to ``None`` and with no ``paths`` key attached, since
    that is the document the stored hash actually covers. Stamping it any other
    way would produce a fixture the validator is right to refuse.
    """
    stamped = dict(pack)
    if corrupt:
        stamped["content_sha256"] = "f" * 64
    else:
        stamped["content_sha256"] = None
        from tools.reconstruction_tooling.models import sha256_json
        stamped["content_sha256"] = sha256_json(stamped)
    return json.dumps(stamped, indent=2, sort_keys=True) + "\n"


# A two-instruction listing carrying the literal 0x202. Every test below states a
# source literal it does *not* contain, so CONSTANTS can only reach a verdict that
# names a listing if these instructions were actually read: the check has no other
# route to one. CONTROL FLOW is the second witness -- NOT_AVAILABLE with no
# listing, PASS with one, because a two-instruction body carries no conditional
# branch and the whole listing is the evidence of that.
LISTING = {"instructions": [{"address": "00c0ffee", "instruction": "MOV EAX,0x202"},
                            {"address": "00c0fff0", "instruction": "RET"}]}
CONSTANT_SPAN = "  return helper_00abcde1(0x303);"

# A complete body that satisfies every dimension at once, so that "all eight
# checks pass" is a property of the fixture rather than a hope. It is 7
# instructions: a frame prologue, one conditional branch that closes inside the
# body, one displacement through the receiver at +0x14 (a bound the receiver
# record below carries), one call the xref export also records, and no indirect
# transfer. The source span names the same one call and nothing else.
BODY = [{"address": "00c0ffee", "instruction": "PUSH EBP"},
        {"address": "00c0ffef", "instruction": "MOV EBP,ESP"},
        {"address": "00c0fff1", "instruction": "CMP ECX,0x0"},
        {"address": "00c0fff4", "instruction": "JZ 0x00c0fff9"},
        {"address": "00c0fff6", "instruction": "MOV EAX,dword ptr [ECX + 0x14]"},
        {"address": "00c0fff9", "instruction": "CALL 0x00abcde1"},
        {"address": "00c0fffe", "instruction": "RET"}]
# The same body with the branch target moved past the last instruction, so the
# recovered listing is a slice and the branch graph does not close inside it.
OPEN_BODY = [dict(item) for item in BODY]
OPEN_BODY[3] = {"address": "00c0fff4", "instruction": "JZ 0x00c11000"}
# A body with no outgoing transfer and no displacement through the receiver, so
# that the "both oracles empty" and "no receiver displacement" cases have a
# fixture that genuinely contains nothing of the kind they claim nothing about.
STRAIGHT_BODY = [{"address": "00c0ffee", "instruction": "MOV EAX,0x7"},
                 {"address": "00c0fff1", "instruction": "RET"}]
# The two indirect-transfer shapes the detector used to be blind to: the
# register form MSVC actually emits for a virtual call, and the ``dword ptr``
# operand whose four-letter width no ``[A-Z]{2,3}`` pattern could match.
INDIRECT_BODY = [{"address": "00c0ffee", "instruction": "MOV EAX,dword ptr [ECX]"},
                 {"address": "00c0fff1", "instruction": "CALL EAX"},
                 {"address": "00c0fff4", "instruction": "JMP dword ptr [EAX*0x4 + 0x5dd840]"},
                 {"address": "00c0fff9", "instruction": "RET"}]
# The shape 0x006a2a80 has: the receiver is copied out of ECX into EBX on the
# second instruction and every receiver word is then addressed through the copy, so
# a scan of the listing for a displacement under ``[ECX`` finds nothing at all
# while the inference's own receiver record has seen all three of them. The two
# machine witnesses therefore disagree unless both are read, and the record is the
# only one of them that reaches a body that aliases its receiver -- which is why it
# is read as a record in its own right and not as a fallback.
ALIAS_BODY = [{"address": "00c0ffee", "instruction": "PUSH EBX"},
              {"address": "00c0fff0", "instruction": "MOV EBX,ECX"},
              {"address": "00c0fff2", "instruction": "MOV EAX,dword ptr [EBX + 0x18]"},
              {"address": "00c0fff5", "instruction": "MOV EDX,dword ptr [EBX + 0x1c]"},
              {"address": "00c0fff8", "instruction": "INC dword ptr [EBX + 0x34]"},
              {"address": "00c0fffa", "instruction": "POP EBX"},
              {"address": "00c0fffb", "instruction": "RET"}]
# The source that goes with it: the same three receiver words, addressed by the
# displacement the machine uses and naming no member.
ALIAS_SOURCE = ("  return *(int *)(this + 0x18) + *(int *)(this + 0x1c)"
                " + *(int *)(this + 0x34);")

# The shape 0x006a2f10 (App::PropertyList::AddPropertiesFrom) has. Two of the
# three direct transfers its listing shows are calls the xref export also records;
# the third is the preheader jump at 00c0fffd into the first block of a loop, and
# its target 00c10008 is ``LEA EAX,[ESI + 0x4]`` -- the body's own first loop
# instruction, not a callee. Counting that jump as a transfer out of the body made
# the two machine oracles disagree and failed a reconstruction that named no callee
# the machine does not show. The back edge at 00c10021 is a *conditional* branch,
# so it never named a target in the first place.
LOOP_BODY = [{"address": "00c0ffee", "instruction": "MOV EAX,dword ptr [ESP + 0x4]"},
             {"address": "00c0fff4", "instruction": "CMP EAX,0x0"},
             {"address": "00c0fff7", "instruction": "JZ 0x00c0fffd"},
             {"address": "00c0fff9", "instruction": "LEA EBX,[EDX + 0x18]"},
             {"address": "00c0fffd", "instruction": "JMP 0x00c10008"},
             {"address": "00c10008", "instruction": "LEA EAX,[ESI + 0x4]"},
             {"address": "00c1000b", "instruction": "PUSH EAX"},
             {"address": "00c1000c", "instruction": "PUSH ESI"},
             {"address": "00c1000d", "instruction": "MOV ECX,EBX"},
             {"address": "00c1000f", "instruction": "CALL 0x00abcde1"},
             {"address": "00c10014", "instruction": "MOV ECX,EAX"},
             {"address": "00c10016", "instruction": "CALL 0x00aabb11"},
             {"address": "00c1001b", "instruction": "ADD ESI,0x18"},
             {"address": "00c1001e", "instruction": "CMP ESI,0x30"},
             {"address": "00c10021", "instruction": "JNZ 0x00c10008"},
             {"address": "00c10023", "instruction": "RET 0x4"}]
# The two calls the loop body actually makes, and nothing else: the export for
# this body records no edge to 0x00c10008, because that address is not callee.
LOOP_EDGES = [(TARGET, HELPER, "direct-call"), (TARGET, "00aabb11", "direct-call")]
LOOP_SPAN = "  return helper_00abcde1(1) + helper_00aabb11(2);"


def _machine_abi(instructions, register="ECX", offsets=(0, 4, 0x14),
                  declared=None, indirect=0, degraded=False, unparsed=0, drop=()):
    """The machine-derived ABI sub-records the per-dimension checks read.

    These sit on the *envelope* of ``categories.abi.value`` -- the inference
    record -- and not inside the ABI it wraps, which is where the 200 committed
    packs carry them (measured: 190 of 200 have them on the envelope alone).
    ``drop`` removes one, which is how a test says "this oracle was never
    collected" rather than "this oracle says zero".
    """
    value = {"calling_convention": "__cdecl",
             "receiver": {"register": register, "offsets": list(offsets), "bounds_only": True},
             "parse": {"declared_count": len(instructions) if declared is None else declared,
                       "degraded": degraded, "unparsed": unparsed},
             "dispatch": {"indirect_calls": indirect, "vtable_shaped_loads": 0}}
    for key in drop:
        value.pop(key, None)
    return value


# The projection a pack collected now carries in ``categories.abi``: the persisted
# ABI, byte for byte, beside the derived envelope and gaining no machine record.
PERSISTED_ABI_PROJECTION = {"architecture": "x86-32", "calling_convention": "__cdecl",
                            "return_type": "int"}


def _machine_pack(instructions, categories=None, derived=False, abi_value=None, **abi):
    """A pack carrying a complete listing and the machine-derived ABI records.

    ``**abi`` goes to ``_machine_abi``; ``categories`` overrides other pack
    categories (a coverage shortfall, an unavailable reserved slot) and is applied
    last so a test can take the machine evidence away from one dimension.

    ``derived`` publishes the machine records in their own ``abi_derived``
    category -- the pack's declared home for the derivation, and where
    ``evidence.collect`` puts them for a pack collected now -- instead of on the
    ``abi`` envelope: ``True`` for the whole record, or a dict to publish exactly
    that value (a record with one sub-record removed, a truncated envelope).
    ``abi_value`` replaces the ``abi`` category's value outright, for a test that
    needs the two locations to disagree.
    """
    records = _machine_abi(instructions, **abi)
    derived_value = {}
    if derived is not False:
        derived_value = {V.ABI_DERIVED_CATEGORY: _category(True, records if derived is True else dict(derived))}
        if abi_value is None:
            abi_value = dict(PERSISTED_ABI_PROJECTION)
    pack = _pack(disassembly=(True, {"instructions": [dict(item) for item in instructions]}),
                 abi=(True, records if abi_value is None else abi_value))
    pack["categories"].update(derived_value)
    for key, value in (categories or {}).items():
        pack["categories"][key] = _category(*value) if isinstance(value, tuple) else value
    return pack



class DimensionFixture(unittest.TestCase):
    """A throwaway repository built from the same canonical inputs as production.

    The projection is rebuilt by ``build_index`` rather than hand-written, so
    these fixtures exercise the real path from manifest, xref export and metadata
    to a record -- including the address normalisation the CALLS oracle needs.
    """

    def build(self, source_text, pack, edges=(), abi=None, gates=("gate-fixture-runtime",),
              types=(), mechanics=(), write_source=True, validated=0,
              persist=False, corrupt=False, write=False, pack_va=None, from_disk=False):
        tmp = TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.addCleanup(_INDEX_CACHE.clear)
        root = Path(tmp.name)
        self.root = root

        if write_source:
            _write(root / SOURCE_REL, source_text)

        _write(root / MANIFEST_REL,
               '{"schema":"openspore-source-reconstruction-manifest-1",'
               '"binary":{"sha256":"fixture","name":"SporeApp.exe","source":"fixture"},'
               '"functions":[{"va":"%s","normalized_symbol":"reconstruct_me_00c0ffee",'
               '"subsystem":"FIXTURE","package":"pkg_fixture","source_file":"%s",'
               '"body_status":"unresolved","observed_mechanics":%s,'
               '"evidence_level":"SUPPORTED","runtime_gates":%s,'
               '"audit_runtime_validated":%d}],'
               '"packages":[{"id":"pkg_fixture","status":"triage_only"}],"types":[]}'
               % (TARGET, SOURCE_REL, _json(mechanics), _json(list(gates)), validated))
        _write(root / QUEUE_REL, '{"schema":"openspore-triage-queue-1","queue":[]}')
        _write(root / SEMANTIC_REL,
               '{"schema":"openspore-semantic-decomp-1","records":[],'
               '"contradictions":[],"family_index":[]}')
        rows = ["caller_va\tcallee_va\treference_type\tcallsite_va"]
        for caller, callee, kind in edges:
            rows.append("%s\t%s\t%s\t00c0ff00" % (caller, callee, kind))
        _write(root / XREF_REL, "\n".join(rows) + "\n")
        resolved_abi = DEFAULT_ABI if abi is None else abi
        _write(root / METADATA_REL,
               '{"va":"%s","abi":%s,"types":%s}' % (TARGET, _json(resolved_abi), _json(list(types))))

        if persist:
            # The production path: the pack the validator judges is the one
            # already committed under ``reconstruction/evidence/<va>/``, and
            # nothing is handed in.
            stored = dict(pack)
            if pack_va is not None:
                stored["target"] = {"va": pack_va, "address_kind": "linked_va"}
            _write(root / PACK_REL, _pack_json(stored, corrupt))
        if persist or from_disk:
            return V.validate(root=root, va=TARGET, evidence=None, write=write)
        return V.validate(root=root, va=TARGET, evidence=pack, write=write)


def _json(value):
    import json
    return json.dumps(value)


OUT = [(TARGET, HELPER, "direct-call")]


# --------------------------------------------------------------------------
# The uniform rule, once per dimension.
#
# A check reaches PASS iff (a) the machine evidence is complete and bounded for
# that dimension, and (b) the reconstruction either makes no claim in it or has
# every claim grounded in that evidence. (b) has two shapes -- agreement, and
# *evidenced* absence of the phenomenon -- and the second is the one that was
# missing: a value that is missing, unavailable or never collected is never
# evidence, so it never clears anything. Each dimension below is held for a
# grounded pass, an evidenced-absence pass, a missing-evidence NOT_AVAILABLE, an
# ungrounded-claim WARN, and (where the machine can refute) a FAIL.
# --------------------------------------------------------------------------
class CallDimension(DimensionFixture):

    def test_two_machine_sources_that_name_the_same_target_pass(self):
        # (a) both oracles present and untruncated; (b) the source's one claim is
        # one of the targets they name.
        report = self.build(_span("  return helper_00abcde1(3);"), _machine_pack(BODY), edges=OUT)
        calls = report["static"]["checks"]["CALLS"]
        self.assertEqual(calls["status"], "PASS")
        self.assertIn("machine-vs-machine rule", calls["detail"])
        self.assertEqual(calls["coverage"], "complete")

    def test_an_empty_set_in_both_oracles_is_evidenced_absence(self):
        # The export was searched and recorded nothing, the complete listing shows
        # no transfer, and the source names none. Two independent machine sources
        # agreeing that there is nothing here is the evidence for its absence.
        report = self.build(_span("  return 3;"), _machine_pack(STRAIGHT_BODY), edges=())
        calls = report["static"]["checks"]["CALLS"]
        self.assertEqual(calls["status"], "PASS")
        self.assertIn("each record no outgoing transfer", calls["detail"])
        self.assertEqual(calls["coverage"], "complete")

    def test_no_listing_is_not_available_not_pass(self):
        report = self.build(_span("  return 3;"), _pack(), edges=())
        calls = report["static"]["checks"]["CALLS"]
        self.assertEqual(calls["status"], "NOT_AVAILABLE")
        self.assertNotEqual(calls["status"], "PASS")

    def test_a_source_that_names_no_callee_is_a_warning(self):
        # The machine has a callee the source does not account for. That is a
        # review item, and it is not cleared by the two machine sources agreeing:
        # the sources agree about the *machine*, and the question here is what
        # the reconstruction says.
        report = self.build(_span("  return 3;"), _pack(), edges=OUT)
        self.assertEqual(report["static"]["checks"]["CALLS"]["status"], "WARN")

    def test_a_callee_reachable_only_by_a_tail_call_jump_is_not_a_failure(self):
        # The regression. The xref export records the call this body reaches by a
        # tail-call jump; reading only ``CALL`` made the listing's transfer set
        # empty, the two machine oracles disagreed, and a correct reconstruction
        # was failed on evidence that had not been read.
        body = [{"address": "00c0ffee", "instruction": "MOV EAX,0x1"},
                {"address": "00c0fff1", "instruction": "JMP 0x00abcde1"}]
        report = self.build(_span("  return helper_00abcde1(3);"), _machine_pack(body), edges=OUT)
        calls = report["static"]["checks"]["CALLS"]
        self.assertNotEqual(calls["status"], "FAIL")
        self.assertEqual(calls["status"], "PASS")
        self.assertIn("reached only by a jump", calls["detail"])

    def test_a_jump_back_into_the_body_is_not_a_callee(self):
        # The regression, and the other direction of the same pair. 0x006a2f10's
        # listing shows three direct transfers and its export records two callees;
        # the third is the preheader jump into the loop body, whose target 0x00c10008
        # is the body's own first loop instruction. A jump that lands back inside
        # the body transfers control within the function and reaches no callee, so
        # it is not a transfer out of the body and the two oracles agree.
        report = self.build(_span(LOOP_SPAN), _machine_pack(LOOP_BODY), edges=LOOP_EDGES)
        calls = report["static"]["checks"]["CALLS"]
        self.assertEqual(calls["status"], "PASS")
        self.assertEqual(calls["coverage"], "complete")
        self.assertIn("intra-procedural jump", calls["detail"])
        self.assertIn("0x00c10008", calls["detail"])
        # The two real callees are still compared, and the span is named so a
        # reader can see the exclusion was decided on the body and not on the
        # address being unfamiliar.
        self.assertIn("same 2 direct transfer target(s)", calls["detail"])
        self.assertIn("0x00c0ffee..0x00c10023", calls["detail"])
        # The one in-span jump is excluded, and the detail says how many and which.
        self.assertIn("1 intra-procedural jump(s)", calls["detail"])
        self.assertIn("a jump that lands back in the body is control flow and not a transfer out of it: 0x00c10008", calls["detail"])

    def test_every_in_span_jump_is_excluded_and_named(self):
        # Two unconditional edges inside one body, both landing back in it, and
        # both named: the exclusion reports its own work rather than silently
        # shrinking the set the two oracles are compared on.
        body = [dict(item) for item in LOOP_BODY]
        body[11] = {"address": "00c10016", "instruction": "JMP 0x00c1001b"}
        report = self.build(_span("  return helper_00abcde1(1);"), _machine_pack(body),
                            edges=[(TARGET, HELPER, "direct-call")])
        calls = report["static"]["checks"]["CALLS"]
        self.assertEqual(calls["status"], "PASS")
        self.assertIn("2 intra-procedural jump(s)", calls["detail"])
        self.assertIn("not a transfer out of it: 0x00c10008, 0x00c1001b", calls["detail"])
        # The one real call is still compared, and the two jumps are the whole of
        # the difference between the set the export records and the one the
        # listing shows.
        self.assertIn("same 1 direct transfer target(s)", calls["detail"])

    def test_a_jump_out_of_the_body_the_export_does_not_record_still_fails(self):
        # The filtering rule is one-sided. A JMP whose target lies outside the
        # body span transfers control out of it, which is a tail call; if the
        # export does not record it, the two oracles genuinely disagree and the
        # verdict is still a FAIL.
        body = [{"address": "00c0ffee", "instruction": "MOV EAX,0x1"},
                {"address": "00c0fff1", "instruction": "JMP 0x00d0ffee"},
                {"address": "00c0fff7", "instruction": "RET"}]
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _machine_pack(body), edges=OUT)
        calls = report["static"]["checks"]["CALLS"]
        self.assertEqual(calls["status"], "FAIL")
        self.assertIn("1 transfer(s) the body makes are not in the export: 0x00d0ffee", calls["detail"])
        self.assertNotIn("intra-procedural", calls["detail"])

    def test_a_genuine_disagreement_survives_the_filtering(self):
        # Filtering the in-span jump must not launder a real disagreement. This
        # body has an in-span jump *and* a tail call the export does not record
        # *and* an export callee the body does not show, and both directions of
        # the difference are named after the jump is excluded.
        body = [dict(item) for item in LOOP_BODY]
        body[11] = {"address": "00c10016", "instruction": "JMP 0x00d0ffee"}
        report = self.build(_span("  return helper_00abcde1(1);"), _machine_pack(body),
                            edges=LOOP_EDGES[:1] + [(TARGET, "00ccdd11", "direct-call")])
        calls = report["static"]["checks"]["CALLS"]
        self.assertEqual(calls["status"], "FAIL")
        # The filtered jump is reported, and is not one of the two disagreements.
        self.assertIn("intra-procedural jump", calls["detail"])
        self.assertIn("1 intra-procedural jump(s)", calls["detail"])
        self.assertIn("not in the export: 0x00d0ffee", calls["detail"])
        self.assertIn("the body does not show: 0x00ccdd11", calls["detail"])

    def test_a_call_inside_the_body_span_is_not_filtered(self):
        # The exclusion is for JMP alone. A CALL immediate that happens to land
        # inside the span is still compared with the export, so a disagreement
        # about it is still a FAIL rather than being dropped on geometry.
        body = [{"address": "00c0ffee", "instruction": "PUSH EBP"},
                {"address": "00c0fff0", "instruction": "CALL 0x00c0fff8"},
                {"address": "00c0fff8", "instruction": "MOV EAX,0x1"},
                {"address": "00c0fffb", "instruction": "RET"}]
        report = self.build(_span(LOOP_SPAN), _machine_pack(body), edges=LOOP_EDGES)
        calls = report["static"]["checks"]["CALLS"]
        self.assertEqual(calls["status"], "FAIL")
        self.assertIn("1 transfer(s) the body makes are not in the export: 0x00c0fff8", calls["detail"])
        self.assertNotIn("intra-procedural", calls["detail"])

    def test_a_listing_with_no_bounds_filters_nothing(self):
        # The exclusion needs a body span to judge against, and this listing has
        # none: one of its own instruction addresses does not parse, so the span
        # cannot be bounded and no filtering is invented for it. The two oracles
        # are compared on the raw transfer set, which is the pre-existing reading.
        body = [{"address": "not-an-address", "instruction": "MOV EAX,0x1"},
                {"address": "00c0fff1", "instruction": "JMP 0x00c0fff1"},
                {"address": "00c0fff4", "instruction": "RET"}]
        report = self.build(_span("  return helper_00abcde1(3);"), _machine_pack(body), edges=OUT)
        calls = report["static"]["checks"]["CALLS"]
        self.assertEqual(calls["status"], "FAIL")
        self.assertIn("1 transfer(s) the body makes are not in the export: 0x00c0fff1", calls["detail"])
        self.assertIn("1 export callee(s) the body does not show: 0x00abcde1", calls["detail"])
        self.assertNotIn("intra-procedural", calls["detail"])

    def test_the_exclusion_does_not_touch_the_branch_graph(self):
        # The filter is confined to CALLS. The same listing still closes its
        # branch graph inside the recovered body span, and CONTROL FLOW still
        # counts every conditional branch, so the jump that CALLS excludes is
        # still evidence for the dimension that owns it.
        report = self.build(_span(LOOP_SPAN), _machine_pack(LOOP_BODY), edges=LOOP_EDGES)
        flow = report["static"]["checks"]["CONTROL FLOW"]
        self.assertEqual(flow["status"], "PASS")
        self.assertIn("all 2 conditional branch target(s)", flow["detail"])
        self.assertIn("0x00c0ffee..0x00c10023", flow["detail"])
        self.assertEqual(report["static"]["checks"]["CALLS"]["status"], "PASS")


class GlobalsDimension(DimensionFixture):

    def test_a_body_that_names_no_data_address_passes(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _machine_pack(BODY), edges=OUT)
        globals_check = report["static"]["checks"]["GLOBALS"]
        self.assertEqual(globals_check["status"], "PASS")
        self.assertEqual(globals_check["coverage"], "complete")

    def test_evidenced_absence_a_complete_listing_with_no_data_address(self):
        # The same verdict reached the honest way round: the listing is complete
        # and names nothing in the data segment, so the target touches no global.
        report = self.build(_span("  return helper_00abcde1(3);"), _machine_pack(BODY), edges=OUT)
        self.assertNotIn("data address", report["static"]["checks"]["GLOBALS"]["detail"].split("and")[0])
        self.assertIn("no data-segment address", report["static"]["checks"]["GLOBALS"]["detail"])

    def test_no_listing_is_not_available_not_pass(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        self.assertEqual(report["static"]["checks"]["GLOBALS"]["status"], "NOT_AVAILABLE")

    def test_a_listing_that_names_a_data_address_warns_and_is_not_cleared(self):
        # The second machine side is the Ghidra data-reference artifact, and this
        # fixture writes no artifact, so there is none to corroborate against: a
        # listing that reaches a data address stays a review item rather than
        # being promoted on the strength of one source. The verdict and the
        # coverage are the point; the reason text names whichever second side is
        # actually missing, so it is asserted as an absence of that side rather
        # than as the wording of any one of them.
        body = [{"address": "00c0ffee", "instruction": "MOV EAX,dword ptr [0x015d115d]"},
                {"address": "00c0fff4", "instruction": "RET"}]
        report = self.build(_span("  return helper_00abcde1(3);"), _machine_pack(body), edges=OUT)
        globals_check = report["static"]["checks"]["GLOBALS"]
        self.assertEqual(globals_check["status"], "WARN")
        self.assertEqual(globals_check["coverage"], "partial")
        self.assertIn("no independent data-reference evidence is available",
                      globals_check["detail"])

    def test_a_source_global_the_listing_does_not_corroborate_warns(self):
        report = self.build(_span("  *g_flag = 0x015d115d;\n  return helper_00abcde1(3);"),
                            _machine_pack(BODY), edges=OUT)
        globals_check = report["static"]["checks"]["GLOBALS"]
        self.assertEqual(globals_check["status"], "WARN")
        self.assertIn("does not corroborate", globals_check["detail"])


class FieldsDimension(DimensionFixture):

    def test_a_displacement_within_the_machine_derived_bounds_passes(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _machine_pack(BODY), edges=OUT)
        fields = report["static"]["checks"]["FIELDS/OFFSETS"]
        self.assertEqual(fields["status"], "PASS")
        self.assertIn("within the machine-derived receiver bounds", fields["detail"])
        # Never a claim about the layout itself: ``bounds_only`` is true on 190 of
        # the 194 packs that carry a receiver record, so a pass here corroborates
        # bounds and nothing about which member is which.
        self.assertNotIn("field layout confirmed", fields["detail"])

    def test_a_bare_receiver_read_is_offset_zero_and_not_an_absence(self):
        # ``MOV EAX,dword ptr [ECX]`` loads the word at offset zero, so it *is* a
        # receiver field access. The old arm called this an evidenced absence
        # ("names no displacement through ECX, which is evidence that the body
        # addresses no receiver field") -- a true statement about displacements
        # followed by a false conclusion drawn from it. The verdict is unchanged
        # (nothing the source asserts is ungrounded); the claim is what moved.
        body = [{"address": "00c0ffee", "instruction": "MOV EAX,dword ptr [ECX]"},
                {"address": "00c0fff1", "instruction": "RET"}]
        report = self.build(_span("  return helper_00abcde1(3);"), _machine_pack(body), edges=OUT)
        fields = report["static"]["checks"]["FIELDS/OFFSETS"]
        self.assertEqual(fields["status"], "PASS", fields["detail"])
        self.assertIn("reaches 1 receiver displacement(s) through ECX (0x0)", fields["detail"])
        self.assertNotIn("which is evidence that the body addresses no receiver field",
                         fields["detail"])

    def test_no_listing_or_no_receiver_register_is_not_available_not_pass(self):
        for pack in (_pack(), _machine_pack(BODY, register=None)):
            report = self.build(_span("  return helper_00abcde1(3);"), pack, edges=OUT)
            self.assertEqual(report["static"]["checks"]["FIELDS/OFFSETS"]["status"],
                             "NOT_AVAILABLE")

    def test_a_named_field_no_machine_evidence_corroborates_warns(self):
        report = self.build(_span("  state->field = 1;\n  return helper_00abcde1(3);"),
                            _machine_pack(BODY), edges=OUT)
        fields = report["static"]["checks"]["FIELDS/OFFSETS"]
        self.assertEqual(fields["status"], "WARN")
        self.assertIn("not corroborated", fields["detail"])
        self.assertNotEqual(fields["status"], "PASS")

    def test_a_displacement_the_enumerating_record_does_not_contain_fails(self):
        # Only an *enumerating* receiver record can refute a declared member.
        # ``bounds_only`` states how far the body was seen reaching, so the same
        # declaration there is uncorroborated rather than contradicted.
        enumerating = [{"address": "00c0ffee", "instruction": "MOV EAX,dword ptr [ECX]"},
                       {"address": "00c0fff1", "instruction": "RET"}]
        value = _machine_abi(enumerating, offsets=(0,))
        value["receiver"]["bounds_only"] = False
        pack = _pack(disassembly=(True, {"instructions": enumerating}), abi=(True, value))
        report = self.build(_span("  return *(int *)(this + 0x40);"), pack, edges=OUT)
        fields = report["static"]["checks"]["FIELDS/OFFSETS"]
        self.assertEqual(fields["status"], "FAIL")
        self.assertIn("0x40", fields["detail"])
        # The same declaration against a bounds-only record warns instead.
        bounded = _machine_pack(enumerating, offsets=(0,))
        report = self.build(_span("  return *(int *)(this + 0x40);"), bounded, edges=OUT)
        self.assertEqual(report["static"]["checks"]["FIELDS/OFFSETS"]["status"], "WARN")

    def test_a_receiver_aliased_into_another_register_still_grounds_the_offsets(self):
        # The dogfood shape, and the one the check exists to bless. Every receiver
        # word is addressed through ``EBX`` after ``MOV EBX,ECX``, so the listing's
        # own scan under ``ECX`` finds nothing; the machine-derived receiver record
        # has seen all three offsets, and the source declares the same three. That
        # is a grounded pass, and before the reordering the grounded arm was not
        # reachable for it at all.
        report = self.build(_span(ALIAS_SOURCE),
                            _machine_pack(ALIAS_BODY, register="ECX", offsets=(0x18, 0x1c, 0x34)),
                            edges=())
        fields = report["static"]["checks"]["FIELDS/OFFSETS"]
        self.assertEqual(fields["status"], "PASS", fields["detail"])
        self.assertEqual(fields["coverage"], "complete")
        self.assertIn("grounded within the machine-derived receiver bounds", fields["detail"])
        # The witness that is empty here, stated so a reader can see which one spoke.
        self.assertEqual(V._receiver_displacements([item["instruction"] for item in ALIAS_BODY], "ECX"), set())
        # Bounds, never a layout: the record says where the body was seen reaching.
        self.assertNotIn("layout confirmed", fields["detail"])
        self.assertNotIn("layout is confirmed", fields["detail"])

    def test_a_displacement_outside_the_receiver_bounds_names_both_directions(self):
        # The source declares one offset the record does not contain and the body
        # uses another it does not. Either could be the mistake, so the detail has
        # to say which side of the difference each one is on rather than reporting
        # only that the two disagree.
        body = [{"address": "00c0ffee", "instruction": "MOV EAX,dword ptr [ECX + 0x18]"},
                {"address": "00c0fff2", "instruction": "RET"}]
        report = self.build(_span("  return *(int *)(this + 0x40);"),
                            _machine_pack(body, offsets=(0x18,)), edges=OUT)
        fields = report["static"]["checks"]["FIELDS/OFFSETS"]
        self.assertEqual(fields["status"], "WARN")
        self.assertIn("the source span declares 0x40", fields["detail"])
        self.assertIn("listing names 0x18 through that register", fields["detail"])
        self.assertIn("0x40", fields["detail"])

    def test_a_named_field_stays_a_warning_however_well_its_offsets_are_grounded(self):
        # The decision, pinned. A displacement is a *location* claim and
        # ``receiver.offsets`` is a set of locations, so the record can settle it.
        # A name is an *identity* claim -- which member is at that offset -- and no
        # machine record in the pack carries member names, so it cannot be settled
        # from a displacement set at all. Both halves are present here, and the
        # verdict is the name's: the detail reports the grounding so a reader can
        # see that it is the name alone that is uncorroborated.
        report = self.build(_span("  state->field = *(int *)(this + 0x14);\n  return helper_00abcde1(3);"),
                            _machine_pack(BODY, register="ECX", offsets=(0, 4, 0x14)), edges=OUT)
        fields = report["static"]["checks"]["FIELDS/OFFSETS"]
        self.assertEqual(fields["status"], "WARN")
        self.assertIn("not corroborated", fields["detail"])
        self.assertIn("grounded within the machine-derived receiver bounds", fields["detail"])
        self.assertNotEqual(report["static"]["status"], "PASS")

    def test_the_ungrounded_warning_still_speaks_with_a_listing_but_no_receiver(self):
        # The arm the reordering had to stop preempting. It is still the verdict
        # when there is genuinely no machine record to check a declaration against:
        # a complete listing and no receiver register is a complete listing and no
        # receiver register, however well the call dimension is served by it.
        value = _machine_abi(BODY)
        value.pop("receiver")
        pack = _machine_pack(BODY, abi_value=value)
        report = self.build(_span("  return *(int *)(this + 0x14);"), pack, edges=OUT)
        fields = report["static"]["checks"]["FIELDS/OFFSETS"]
        self.assertEqual(fields["status"], "WARN")
        self.assertIn("no machine-derived struct layout exists to corroborate", fields["detail"])
        # And with nothing declared and no record, the honest reading is the
        # absence of evidence rather than an ungrounded claim.
        report = self.build(_span("  return helper_00abcde1(3);"), pack, edges=OUT)
        self.assertEqual(report["static"]["checks"]["FIELDS/OFFSETS"]["status"], "NOT_AVAILABLE")

    def test_a_grounded_pass_never_rests_on_an_empty_receiver_record(self):
        # The structural invariant the reordering rests on: the grounded arm is
        # only reachable when there is a displacement to account for, and a
        # displacement inside the bounds implies the bounds are not empty. So a
        # record that carries a register and no offsets cannot clear a declaration
        # -- it warns, and a source that declares nothing against it is the
        # evidenced absence instead.
        body = [{"address": "00c0ffee", "instruction": "MOV EAX,dword ptr [ECX + 0x18]"},
                {"address": "00c0fff2", "instruction": "RET"}]
        report = self.build(_span(ALIAS_SOURCE), _machine_pack(body, offsets=()), edges=OUT)
        fields = report["static"]["checks"]["FIELDS/OFFSETS"]
        self.assertEqual(fields["status"], "WARN")
        self.assertIn("lie outside the machine-derived receiver bounds (none)", fields["detail"])
        # The same empty record against a body that addresses no receiver word at
        # all is the evidenced absence, not a pass resting on nothing.
        plain = [{"address": "00c0ffee", "instruction": "MOV EAX,0x7"},
                 {"address": "00c0fff1", "instruction": "RET"}]
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _machine_pack(plain, offsets=()), edges=OUT)
        fields = report["static"]["checks"]["FIELDS/OFFSETS"]
        self.assertEqual(fields["status"], "PASS")
        self.assertIn("names no displacement through ECX", fields["detail"])

    def test_a_named_member_of_a_type_the_reconstruction_introduced_still_warns(self):
        # The exact shape 0x006a2a80 has, kept so the next reader can see it was
        # met and decided on rather than overlooked. The source declares three
        # receiver words by displacement -- grounded, and reported as grounded --
        # and names three members of a union it introduced itself
        # (``product.full``, ``product.words.high``) to select the high half of a
        # 64-bit multiply. That name is a real layout claim and no machine record
        # in the pack carries member names, so it is not cleared, and the check
        # says which half of the declaration is uncorroborated. Excluding a member
        # access because its base happens to be a local would clear the claim on a
        # technicality of the source's own shape, which is the reasoning that
        # manufactures false passes.
        source = ("  product.full = (long long)count * stride;\n"
                  "  return *(int *)(this + 0x18) + product.words.high;")
        report = self.build(_span(source),
                            _machine_pack(ALIAS_BODY, register="ECX", offsets=(0x18, 0x1c, 0x34)),
                            edges=OUT)
        fields = report["static"]["checks"]["FIELDS/OFFSETS"]
        self.assertEqual(fields["status"], "WARN")
        self.assertIn("not corroborated", fields["detail"])
        self.assertIn("grounded within the machine-derived receiver bounds", fields["detail"])
        # Which is the point of the reordering: the displacement claim in the same
        # span is no longer reported as an uncorroborated declaration.
        self.assertNotIn("no machine-derived struct layout exists", fields["detail"])


class ConstantsDimension(DimensionFixture):

    def test_a_listed_constant_in_a_fully_parsed_listing_passes(self):
        body = [{"address": "00c0ffee", "instruction": "MOV EAX,0x202"},
                {"address": "00c0fff1", "instruction": "RET"}]
        report = self.build(_span("  return helper_00abcde1(0x202);"), _machine_pack(body), edges=OUT)
        constants = report["static"]["checks"]["CONSTANTS"]
        self.assertEqual(constants["status"], "PASS")
        self.assertIn("fully parsed", constants["detail"])

    def test_evidenced_absence_a_source_that_states_no_constant(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _machine_pack(BODY), edges=OUT)
        constants = report["static"]["checks"]["CONSTANTS"]
        self.assertEqual(constants["status"], "PASS")
        self.assertIn("states no hexadecimal constant", constants["detail"])

    def test_a_listing_with_no_parse_record_is_not_available_not_pass(self):
        # The listing exists and is bounded, but nothing says it was consumed in
        # full, so its completeness cannot be shown. That is an absence of
        # evidence, and it is the one shape that must never be read as a pass.
        pack = _pack(disassembly=(True, {"instructions": [dict(item) for item in BODY]}))
        report = self.build(_span("  return helper_00abcde1(3);"), pack, edges=OUT)
        constants = report["static"]["checks"]["CONSTANTS"]
        self.assertEqual(constants["status"], "NOT_AVAILABLE")
        self.assertNotEqual(constants["status"], "PASS")

    def test_a_degraded_or_partly_unparsed_listing_warns(self):
        for kwargs in ({"degraded": True}, {"unparsed": 3}):
            report = self.build(_span("  return helper_00abcde1(3);"),
                                _machine_pack(BODY, **kwargs), edges=OUT)
            constants = report["static"]["checks"]["CONSTANTS"]
            self.assertEqual(constants["status"], "WARN", kwargs)
            self.assertIn("not fully parsed", constants["detail"])

    def test_a_machine_refutation_fails(self):
        # A stated literal the listing does not contain, and a parse that claims a
        # different body. Both are the machine contradicting the claim rather than
        # merely failing to support it.
        body = [{"address": "00c0ffee", "instruction": "MOV EAX,0x7"},
                {"address": "00c0fff1", "instruction": "RET"}]
        report = self.build(_span("  return helper_00abcde1(0x202);"), _machine_pack(body), edges=OUT)
        self.assertEqual(report["static"]["checks"]["CONSTANTS"]["status"], "FAIL")
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _machine_pack(BODY, declared=len(BODY) + 2), edges=OUT)
        self.assertEqual(report["static"]["checks"]["CONSTANTS"]["status"], "FAIL")


class ControlFlowDimension(DimensionFixture):

    def test_a_branch_graph_that_closes_inside_the_body_passes(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _machine_pack(BODY), edges=OUT)
        flow = report["static"]["checks"]["CONTROL FLOW"]
        self.assertEqual(flow["status"], "PASS")
        self.assertIn("branch graph is closed inside it", flow["detail"])

    def test_evidenced_absence_a_straight_line_body(self):
        # Zero conditional branches: the complete listing *is* the evidence that
        # there is no branch, so this passes trivially rather than lacking an arm.
        body = [{"address": "00c0ffee", "instruction": "MOV EAX,0x7"},
                {"address": "00c0fff1", "instruction": "RET"}]
        report = self.build(_span("  return helper_00abcde1(3);"), _machine_pack(body), edges=OUT)
        flow = report["static"]["checks"]["CONTROL FLOW"]
        self.assertEqual(flow["status"], "PASS")
        self.assertIn("no conditional branch", flow["detail"])

    def test_no_listing_is_not_available_not_pass(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        self.assertEqual(report["static"]["checks"]["CONTROL FLOW"]["status"], "NOT_AVAILABLE")

    def test_a_branch_target_outside_the_body_warns(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _machine_pack(OPEN_BODY), edges=OUT)
        flow = report["static"]["checks"]["CONTROL FLOW"]
        self.assertEqual(flow["status"], "WARN")
        self.assertIn("flow continues past it", flow["detail"])

    def test_a_branch_whose_target_cannot_be_read_is_not_a_closed_graph(self):
        # An operand that is not an absolute address leaves no span to test
        # against. Unread is not closed, and must not be reported as closed.
        body = [{"address": "00c0ffee", "instruction": "CMP EAX,0x1"},
                {"address": "00c0fff1", "instruction": "JZ somewhere_else"},
                {"address": "00c0fff4", "instruction": "RET"}]
        report = self.build(_span("  return helper_00abcde1(3);"), _machine_pack(body), edges=OUT)
        flow = report["static"]["checks"]["CONTROL FLOW"]
        self.assertEqual(flow["status"], "WARN")
        self.assertIn("cannot be shown to close", flow["detail"])

    def test_source_keywords_are_reported_but_never_decide(self):
        # A source full of keywords against a straight-line body, and the reverse.
        # Neither reading may move the verdict: comparing CFG shape to keyword
        # count is unbounded in both directions, and making it a condition is what
        # left this check with no PASS arm at all.
        straight = [{"address": "00c0ffee", "instruction": "MOV EAX,0x7"},
                    {"address": "00c0fff1", "instruction": "RET"}]
        for source in ("  for (int i = 0; i < 4; ++i) { if (i) { while (i) { switch (i) {} } } }\n  return 3;",
                       "  return 3;"):
            report = self.build(_span(source), _machine_pack(straight), edges=OUT)
            flow = report["static"]["checks"]["CONTROL FLOW"]
            self.assertEqual(flow["status"], "PASS", source)
            self.assertIn("source span declares", flow["detail"])
            self.assertIn("not part of this verdict", flow["detail"])


class VirtualDispatchDimension(DimensionFixture):

    def test_a_body_with_no_indirect_transfer_and_a_zero_record_passes(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _machine_pack(BODY), edges=OUT)
        self.assertEqual(report["static"]["checks"]["VIRTUAL DISPATCH"]["status"], "PASS")

    def test_evidenced_absence_is_the_pass_shape_here(self):
        # This dimension's pass *is* the evidenced-absence shape: a complete body
        # with no dispatch site, corroborated by a record that counts none.
        direct_only = [{"address": "00c0ffee", "instruction": "CALL 0x00abcde1"},
                       {"address": "00c0fff1", "instruction": "RET"}]
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _machine_pack(direct_only), edges=OUT)
        dispatch = report["static"]["checks"]["VIRTUAL DISPATCH"]
        self.assertEqual(dispatch["status"], "PASS")
        self.assertIn("agrees at 0", dispatch["detail"])

    def test_no_listing_is_not_available_not_pass(self):
        report = self.build(_span("  return 3;"), _pack(), edges=OUT)
        self.assertEqual(report["static"]["checks"]["VIRTUAL DISPATCH"]["status"], "NOT_AVAILABLE")

    def test_a_register_and_a_dword_operand_transfer_are_both_detected(self):
        # The two detector bugs, at the unit level. ``[A-Z]{2,3}`` cannot match
        # ``dword``, so the memory form was invisible; and the register form --
        # the shape MSVC actually emits for a virtual call -- was not looked for
        # at all. The old pattern matched zero instructions in all 172 committed
        # listings.
        sites = V._indirect_sites([item["instruction"] for item in INDIRECT_BODY])
        self.assertEqual(len(sites), 2, sites)
        self.assertTrue(any(text.startswith("CALL EAX") for text in sites))
        self.assertTrue(any("dword ptr [" in text for text in sites))
        # A direct transfer and a plain load are not dispatch sites.
        self.assertEqual(V._indirect_sites(["CALL 0x00401000", "JMP 0x00c0ffe0",
                                            "MOV EAX,dword ptr [ECX + 0x14]", "RET"]), [])

    def test_a_detected_site_stops_a_false_refutation(self):
        # The consequence at the check level. This body dispatches twice, through
        # the two shapes the old detector was blind to, and the source declares a
        # slot boundary. The old verdict was a FAIL stating that the body contained
        # no indirect call; the honest verdict is a review item, because there is
        # a dispatch to review.
        report = self.build(_span("  return vtable->load_slot_00abcdef01();"),
                            _machine_pack(INDIRECT_BODY, indirect=2), edges=OUT)
        dispatch = report["static"]["checks"]["VIRTUAL DISPATCH"]
        self.assertNotEqual(dispatch["status"], "FAIL")
        self.assertEqual(dispatch["status"], "WARN")
        self.assertIn("2 indirect transfer(s)", dispatch["detail"])

    def test_a_record_that_disagrees_with_the_listing_warns(self):
        # The record counts one site and the complete listing names two, so one of
        # them is outside this listing: the site count is a lower bound.
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _machine_pack(INDIRECT_BODY, indirect=1), edges=OUT)
        dispatch = report["static"]["checks"]["VIRTUAL DISPATCH"]
        self.assertEqual(dispatch["status"], "WARN")
        self.assertIn("disagree", dispatch["detail"])


# --------------------------------------------------------------------------
# Where the machine records are read from.
#
# ``evidence.collect`` publishes the machine-derived ABI envelope -- ``parse``,
# ``dispatch``, ``receiver``, ``conventions`` and the rest -- in its own
# ``abi_derived`` category, and the ``abi`` category beside it holds the persisted
# projection and gains no machine record. The validator therefore reads each
# record from ``abi_derived`` first and falls back to the ``abi`` value, so a pack
# collected before the category existed reads exactly as it did. Each check below
# is held for all three states: the record present, absent everywhere, and present
# but contradicting the listing.
# --------------------------------------------------------------------------
class MachineRecordLocation(DimensionFixture):

    def test_the_category_name_is_the_cross_module_contract(self):
        # ``evidence.py`` publishes it under this exact name; renaming one side
        # would silently demote every machine record back to the fallback.
        self.assertEqual(V.ABI_DERIVED_CATEGORY, "abi_derived")

    def test_the_machine_records_are_read_from_the_derived_category(self):
        # Present, and present only there: the ``abi`` category holds the persisted
        # projection, which carries none of the three. So a validator that read
        # only the old location would report no parse record, no dispatch record
        # and no receiver -- and three dimensions would be structurally incapable
        # of PASS on every pack collected from now on.
        pack = _machine_pack(ALIAS_BODY, derived=True, register="ECX", offsets=(0x18, 0x1c, 0x34))
        for key in ("parse", "dispatch", "receiver"):
            self.assertNotIn(key, pack["categories"]["abi"]["value"])
            self.assertIn(key, pack["categories"][V.ABI_DERIVED_CATEGORY]["value"])
        report = self.build(_span(ALIAS_SOURCE), pack, edges=())
        checks = report["static"]["checks"]
        self.assertEqual(checks["FIELDS/OFFSETS"]["status"], "PASS", checks["FIELDS/OFFSETS"]["detail"])
        self.assertEqual(checks["CONSTANTS"]["status"], "PASS", checks["CONSTANTS"]["detail"])
        self.assertEqual(checks["VIRTUAL DISPATCH"]["status"], "PASS", checks["VIRTUAL DISPATCH"]["detail"])
        # The whole matrix, and the aggregate it adds up to: all eight adjudicated
        # and agreeing is the only way into a static PASS, so this is a property of
        # the fixture rather than a hope.
        for name in V.STATIC_CHECKS:
            self.assertEqual(checks[name]["status"], "PASS", name)
        self.assertEqual(report["static"]["status"], "PASS")
        self.assertEqual(report["runtime"]["status"], "GATED")
        self.assertEqual(report["runtime"]["validated"], 0)

    def test_the_derived_category_wins_over_the_abi_envelope(self):
        # Both locations populated and disagreeing. The declared home is read
        # first, and the reason it is the declared home is that it is the record
        # the collector actually derived: the ``abi`` value beside it is the
        # persisted projection, or -- for a pack whose persisted ABI was absent --
        # the same derivation published twice.
        pack = _machine_pack(ALIAS_BODY, derived=True, register="ECX", offsets=(0x18, 0x1c, 0x34))
        pack["categories"]["abi"]["value"]["dispatch"] = {"indirect_calls": 3}
        report = self.build(_span(ALIAS_SOURCE), pack, edges=())
        self.assertEqual(report["static"]["checks"]["VIRTUAL DISPATCH"]["status"], "PASS")

    def test_a_truncated_derived_envelope_is_never_read_as_a_record(self):
        # The refusal, on the new location. A ``{"truncated": true}`` value is a
        # fragment of a record, and reading it as one would be a record of zero
        # where none was ever collected.
        pack = _machine_pack(ALIAS_BODY, derived={"truncated": True, "preview": "..."},
                             register="ECX", offsets=(0x18, 0x1c, 0x34))
        report = self.build(_span(ALIAS_SOURCE), pack, edges=())
        checks = report["static"]["checks"]
        self.assertEqual(checks["CONSTANTS"]["status"], "NOT_AVAILABLE")
        self.assertEqual(checks["VIRTUAL DISPATCH"]["status"], "WARN")
        self.assertIn("not a record of zero", checks["VIRTUAL DISPATCH"]["detail"])
        self.assertEqual(checks["FIELDS/OFFSETS"]["status"], "WARN")
        self.assertIn("no machine-derived struct layout exists to corroborate", checks["FIELDS/OFFSETS"]["detail"])
        self.assertNotEqual(report["static"]["status"], "PASS")

    def test_a_truncated_derived_envelope_falls_back_to_a_complete_abi_value(self):
        # A fragment is not a record, and a refusal is not a ban on evidence: where
        # the ``abi`` value carries a complete record, that record is read.
        value = _machine_abi(ALIAS_BODY, register="ECX", offsets=(0x18, 0x1c, 0x34))
        pack = _machine_pack(ALIAS_BODY, derived={"truncated": True, "preview": "..."},
                             abi_value=value)
        report = self.build(_span(ALIAS_SOURCE), pack, edges=())
        self.assertEqual(report["static"]["checks"]["CONSTANTS"]["status"], "PASS")
        self.assertEqual(report["static"]["status"], "PASS")

    def test_the_abi_convention_confidence_is_read_from_the_derived_category(self):
        # A convention confidence is a machine record like the other three, and
        # the arm it feeds -- the one that warns when the oracle is not proven --
        # must not go unreachable because the record moved. Read from the old
        # location only, an APPROXIMATION would read as no confidence at all and
        # the check would pass on an unproven convention.
        records = _machine_abi(BODY)
        records["conventions"] = {"calling_convention": "__cdecl", "confidence": "APPROXIMATION"}
        for label, pack in (("abi value", _machine_pack(BODY, abi_value=dict(records))),
                            ("abi_derived", _machine_pack(BODY, derived=records))):
            report = self.build(_span("  return helper_00abcde1(3);"), pack, edges=OUT)
            abi = report["static"]["checks"]["ABI"]
            self.assertEqual(abi["status"], "WARN", label)
            self.assertIn("confidence is APPROXIMATION", abi["detail"])

    # -- CONSTANTS: present, absent, contradicting --------------------------
    def test_constants_reads_its_parse_record_from_the_derived_category(self):
        # Present: the parse consumed exactly the listing and nothing was left
        # unparsed, so the listing can be shown to have been consumed in full.
        body = [{"address": "00c0ffee", "instruction": "MOV EAX,0x202"},
                {"address": "00c0fff1", "instruction": "RET"}]
        pack = _machine_pack(body, derived=True)
        self.assertEqual(pack["categories"][V.ABI_DERIVED_CATEGORY]["value"]["parse"]["unparsed"], 0)
        report = self.build(_span("  return helper_00abcde1(0x202);"), pack, edges=OUT)
        constants = report["static"]["checks"]["CONSTANTS"]
        self.assertEqual(constants["status"], "PASS", constants["detail"])
        self.assertIn("fully parsed", constants["detail"])
        self.assertIn("2 of 2", constants["detail"])

    def test_a_parse_record_absent_from_both_locations_is_not_available_not_pass(self):
        # Absent: a complete listing that nothing says was consumed in full. That
        # is an absence of evidence about the evidence, and it is the one shape
        # that must never read as a pass.
        value = _machine_abi(BODY, drop=("parse",))
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _machine_pack(BODY, derived=value), edges=OUT)
        constants = report["static"]["checks"]["CONSTANTS"]
        self.assertEqual(constants["status"], "NOT_AVAILABLE")
        self.assertIn("carries no machine parse record", constants["detail"])
        self.assertNotEqual(report["static"]["status"], "PASS")

    def test_a_parse_record_in_the_derived_category_that_claims_a_different_body_fails(self):
        # Contradicting: the parse consumed a different number of instructions
        # than the listing holds, so the two disagree about the body. Preferred
        # location or not, the arm has to read the number that is actually there.
        records = _machine_abi(BODY)
        records["parse"] = {"declared_count": len(BODY) + 3, "degraded": False, "unparsed": 0}
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _machine_pack(BODY, derived=records), edges=OUT)
        constants = report["static"]["checks"]["CONSTANTS"]
        self.assertEqual(constants["status"], "FAIL")
        self.assertIn("disagree about the body", constants["detail"])

    def test_a_degraded_parse_in_the_derived_category_warns(self):
        # The record is present and honest about itself: a degraded parse is a
        # review item, not a refutation and not a clearance.
        records = _machine_abi(BODY)
        records["parse"] = {"declared_count": len(BODY), "degraded": True, "unparsed": 0}
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _machine_pack(BODY, derived=records), edges=OUT)
        constants = report["static"]["checks"]["CONSTANTS"]
        self.assertEqual(constants["status"], "WARN")
        self.assertIn("not fully parsed", constants["detail"])

    # -- VIRTUAL DISPATCH: present, absent, contradicting ------------------
    def test_dispatch_reads_its_indirect_call_count_from_the_derived_category(self):
        pack = _machine_pack(BODY, derived=True)
        self.assertEqual(pack["categories"][V.ABI_DERIVED_CATEGORY]["value"]["dispatch"]["indirect_calls"], 0)
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _machine_pack(BODY, derived=True), edges=OUT)
        dispatch = report["static"]["checks"]["VIRTUAL DISPATCH"]
        self.assertEqual(dispatch["status"], "PASS")
        self.assertEqual(dispatch["coverage"], "complete")
        self.assertIn("agrees at 0", dispatch["detail"])

    def test_a_dispatch_record_absent_from_both_locations_is_not_a_record_of_zero(self):
        value = _machine_abi(BODY, drop=("dispatch",))
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _machine_pack(BODY, derived=value), edges=OUT)
        dispatch = report["static"]["checks"]["VIRTUAL DISPATCH"]
        self.assertEqual(dispatch["status"], "WARN")
        self.assertNotEqual(dispatch["status"], "PASS")
        self.assertIn("not a record of zero", dispatch["detail"])
        self.assertNotEqual(report["static"]["status"], "PASS")

    def test_a_dispatch_record_that_contradicts_the_listing_warns(self):
        # Contradicting: the record counts two indirect calls and the complete
        # listing names none, so the two machine sources disagree and neither can
        # clear the other. Reported as a review item, never as a pass on the
        # listing's silence.
        records = _machine_abi(BODY)
        records["dispatch"] = {"indirect_calls": 2, "vtable_shaped_loads": 0}
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _machine_pack(BODY, derived=records), edges=OUT)
        dispatch = report["static"]["checks"]["VIRTUAL DISPATCH"]
        self.assertEqual(dispatch["status"], "WARN")
        self.assertIn("names 0 indirect dispatch site(s)", dispatch["detail"])
        self.assertIn("counts 2", dispatch["detail"])
        self.assertNotEqual(report["static"]["status"], "PASS")

    def test_a_site_the_listing_names_with_a_zero_record_is_still_a_warning(self):
        # The inverse disagreement, and the direction that is easier to get wrong:
        # the record says zero and the listing names a site, so the record is the
        # one that is short. Silence from one side never clears the other.
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _machine_pack(INDIRECT_BODY, derived=True, indirect=0), edges=OUT)
        dispatch = report["static"]["checks"]["VIRTUAL DISPATCH"]
        self.assertEqual(dispatch["status"], "WARN")
        self.assertIn("2 indirect transfer(s)", dispatch["detail"])


class TruncatedEnvelope(DimensionFixture):
    """A truncated pack's preview is a fragment, never a listing.

    23 of the 200 committed packs carry ``{"truncated": true, "preview": ...}``.
    Reading the preview as a body would let a partial oracle refute a constant the
    full body does contain -- a FAIL manufactured out of an absence.
    """

    def envelope(self):
        return _pack(disassembly=(True, {"truncated": True, "original_bytes": 22151,
                                         "preview": "PUSH EBP\nMOV EBP,ESP\nRET"}))

    def test_a_truncated_envelope_is_not_a_listing(self):
        report = self.build(_span(CONSTANT_SPAN), self.envelope(), edges=OUT, persist=True)
        for name in ("CONTROL FLOW", "GLOBALS", "FIELDS/OFFSETS", "VIRTUAL DISPATCH"):
            self.assertEqual(report["static"]["checks"][name]["status"], "NOT_AVAILABLE", name)
        # The 0x303 in the source is nowhere in the preview, and the preview is
        # therefore not allowed to refute it: CONSTANTS reads the fragment as
        # nothing at all and falls back to "stated but uncorroborated".
        constants = report["static"]["checks"]["CONSTANTS"]
        self.assertEqual(constants["status"], "WARN")
        self.assertIn("no machine listing is collected", constants["detail"])
        # The listing-dependent dimensions are all out of PASS. ABI and CALLS are
        # untouched by any of this: the source span agrees with the canonical ABI
        # record, and the xref export is a complete bounded oracle on its own for
        # the call set. A truncated disassembly says nothing about either.
        for name in ("GLOBALS", "FIELDS/OFFSETS", "CONSTANTS",
                     "CONTROL FLOW", "VIRTUAL DISPATCH"):
            self.assertNotEqual(report["static"]["checks"][name]["status"], "PASS", name)
        self.assertEqual(report["static"]["status"], "NOT_AVAILABLE")

    def test_a_truncated_envelope_says_so(self):
        report = self.build(_span(CONSTANT_SPAN), self.envelope(), edges=OUT, persist=True)
        self.assertIn("no complete listing is collected",
                      report["static"]["checks"]["CONTROL FLOW"]["detail"])

    def test_a_truncated_pack_never_reaches_pass(self):
        report = self.build(_span(CONSTANT_SPAN), self.envelope(), edges=OUT, persist=True)
        self.assertNotEqual(report["static"]["status"], "PASS")
        self.assertEqual(report["runtime"]["status"], "GATED")


# --------------------------------------------------------------------------
# Positive: a statically strong candidate earns a static PASS.
# --------------------------------------------------------------------------
class StaticPass(DimensionFixture):
    """A candidate whose every structural check is adjudicated and agrees.

    The aggregate now requires that: a PASS may not be asserted over a dimension
    that was not adjudicated, so "every check that could be evaluated agreed" is
    no longer enough. The fixture therefore carries a complete listing and the
    machine-derived ABI records rather than a pack that leaves most dimensions
    unjudged.
    """

    def report(self, **kwargs):
        return self.build(_span("  return helper_00abcde1(3);"), _machine_pack(BODY),
                          edges=OUT, **kwargs)

    def test_static_pass_when_every_check_is_adjudicated(self):
        report = self.report()
        self.assertEqual(report["static"]["status"], "PASS")
        # Back-compat alias: every existing consumer reads this and it means the
        # static dimension, unchanged.
        self.assertEqual(report["status"], "PASS")
        self.assertEqual(report["static"]["dimension"], "STATIC")
        for name in V.STATIC_CHECKS:
            self.assertEqual(report["static"]["checks"][name]["status"], "PASS", name)

    def test_static_pass_names_the_runtime_axis_as_gated(self):
        report = self.report()
        self.assertEqual(report["static"]["status"], "PASS")
        self.assertEqual(report["runtime"]["dimension"], "RUNTIME")
        self.assertEqual(report["runtime"]["status"], "GATED")
        self.assertTrue(report["runtime"]["gated"])
        self.assertEqual(report["runtime"]["validated"], 0)
        self.assertEqual(report["runtime"]["gates"], ["gate-fixture-runtime"])

    def test_a_static_pass_is_never_a_runtime_claim(self):
        report = self.report()
        self.assertEqual(report["static"]["status"], "PASS")
        self.assertNotEqual(report["runtime"]["status"], "PASS")
        # The gate is not merely flagged, it is repeated in the open questions so
        # a reader of the question list alone still sees it.
        self.assertIn("gate-fixture-runtime", report["unresolved_questions"])

    def test_a_static_pass_carries_an_open_runtime_gate_and_no_observation(self):
        """The two axes, held apart from a pass rather than from a warning.

        ``record["runtime"]["validated"]`` is 0 on every index record in this
        repository, so a static PASS is *always* accompanied by a gated runtime
        that observed nothing. Asserted together, so a change that ever let a
        static pass imply a runtime observation would fail here rather than in the
        campaign.
        """
        report = self.report()
        self.assertEqual(report["static"]["status"], "PASS")
        self.assertEqual(report["runtime"]["status"], "GATED")
        self.assertIs(report["runtime"]["gated"], True)
        self.assertEqual(report["runtime"]["validated"], 0)
        # The runtime axis is a sibling of the static one and is never one of its
        # checks: the ladder must not be able to read it.
        self.assertNotIn("runtime", report["static"]["checks"])
        self.assertNotIn("runtime", report["checks"])
        self.assertIn("runtime", report)
        text = V.render_markdown(report)
        self.assertIn("Static reconstruction: `PASS`", text)
        self.assertIn("Runtime (original process): `GATED`", text)
        self.assertIn("The two axes are independent", text)
        self.assertIn("attempted and nothing failed", text)
        # The evidence basis reports the runtime observation count next to the
        # static verdict, so the two are never merged into one number.
        self.assertIn("## Runtime", text)
        self.assertIn("Original-process observations validated: `0`", text)

    def test_static_pass_reports_how_much_it_actually_evaluated(self):
        report = self.report()
        basis = report["static"]["evidence_basis"]
        self.assertEqual(basis["static_checks_total"], len(V.STATIC_CHECKS))
        # A PASS is only reachable when nothing was left unjudged, so this is now
        # the total -- and the count that made a thin pass legible stays reported.
        self.assertEqual(basis["static_checks_evaluated"], basis["static_checks_total"])
        self.assertEqual(basis["static_checks_not_available"], 0)
        self.assertEqual(basis["static_checks_passed"], len(V.STATIC_CHECKS))
        self.assertEqual(basis["static_checks_evaluated"] + basis["static_checks_not_available"],
                         basis["static_checks_total"])

    def test_runtime_pass_when_the_record_reports_a_validated_observation(self):
        report = self.report(gates=(), validated=2)
        self.assertEqual(report["runtime"]["status"], "PASS")
        self.assertEqual(report["runtime"]["validated"], 2)
        self.assertFalse(report["runtime"]["gated"])

    def test_markdown_states_both_dimensions(self):
        report = self.report()
        text = V.render_markdown(report)
        self.assertIn("Static reconstruction: `PASS`", text)
        self.assertIn("Runtime (original process): `GATED`", text)
        self.assertIn("attempted and nothing failed", text)


# --------------------------------------------------------------------------
# The aggregate ladder: every structural check must be adjudicated.
# --------------------------------------------------------------------------
class AggregateLadder(DimensionFixture):
    """A PASS is only reachable when all eight structural checks are adjudicated.

    ``NOT_AVAILABLE`` used to be neutral -- an unjudged dimension was skipped
    like one that had been asked and had nothing to say -- so a single agreeing
    check carried a PASS while seven dimensions went unjudged, and the verdict
    itself did not say so. These tests hold the seven-of-eight case (which must
    be ``NOT_AVAILABLE``, not ``PASS``) and the eight-of-eight case, which is the
    only way in.
    """

    def strong(self, **kwargs):
        return self.build(_span("  return helper_00abcde1(3);"), _machine_pack(BODY, **kwargs),
                          edges=OUT)

    def test_seven_of_eight_adjudicated_is_not_available_not_pass(self):
        # A pack whose only defect is one missing oracle: the ABI envelope carries
        # no receiver, so FIELDS/OFFSETS cannot be adjudicated. The other seven
        # agree.
        report = self.strong(drop=("receiver",))
        checks = report["static"]["checks"]
        adjudicated = [name for name in V.STATIC_CHECKS if checks[name]["status"] != "NOT_AVAILABLE"]
        self.assertEqual(sorted(set(V.STATIC_CHECKS) - set(adjudicated)), ["FIELDS/OFFSETS"])
        for name in adjudicated:
            self.assertEqual(checks[name]["status"], "PASS", name)
        # The gate: seven clean checks are not seven-sevenths of a pass.
        self.assertEqual(report["static"]["status"], "NOT_AVAILABLE")
        self.assertNotEqual(report["status"], "PASS")

    def test_every_dimension_unjudged_is_not_available(self):
        # The old "nothing was attempted" case, now just the general one: a pack
        # that adjudicates nothing is NOT_AVAILABLE, and the basis says so.
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        self.assertEqual(report["static"]["status"], "NOT_AVAILABLE")
        basis = report["static"]["evidence_basis"]
        self.assertEqual(basis["static_checks_evaluated"] + basis["static_checks_not_available"],
                         len(V.STATIC_CHECKS))
        self.assertEqual(basis["static_checks_not_available"], len(V.STATIC_CHECKS) - basis["static_checks_evaluated"])

    def test_all_eight_adjudicated_and_agreeing_is_pass(self):
        report = self.strong()
        for name in V.STATIC_CHECKS:
            self.assertEqual(report["static"]["checks"][name]["status"], "PASS", name)
        self.assertEqual(report["static"]["status"], "PASS")

    def test_not_available_outranks_a_warning_in_the_aggregate(self):
        # Order matters and is deliberate. Here FIELDS/OFFSETS is a review item
        # (the body names a field the receiver's displacement bounds cannot
        # identify) and CONSTANTS is unjudged (no parse record says the listing
        # was consumed in full). An unjudged dimension means the verdict does not
        # speak for the reconstruction at all, which is a stronger thing to say
        # than a review item: "collect the evidence" is not the same request as
        # "review this", and collapsing the two would hide the first behind the
        # second.
        report = self.build(_span("  state->field = helper_00abcde1(0x14);"),
                            _machine_pack(BODY, drop=("parse",)), edges=OUT)
        checks = report["static"]["checks"]
        self.assertEqual(checks["FIELDS/OFFSETS"]["status"], "WARN")
        self.assertEqual(checks["CONSTANTS"]["status"], "NOT_AVAILABLE")
        self.assertEqual(report["static"]["status"], "NOT_AVAILABLE")

    # -- The severity ordering itself, rung by rung ------------------------
    # The tests above hold the ends of the ladder (all eight PASS is the only
    # way in; one unadjudicated dimension closes it). Nothing held the order
    # *between* the rungs, which is why a NOT_AVAILABLE-first aggregate could
    # ship: a coverage gap was allowed to mask a machine-established
    # contradiction. Each test below fixes exactly one adjacent pair, and each
    # fixture is built so that the pair under test is the only thing that can
    # have decided the verdict.

    def test_a_contradiction_outranks_an_unadjudicated_dimension(self):
        # The rung that was missing. VIRTUAL DISPATCH is a machine-positive
        # refutation: the reconstruction declares a slot boundary and the
        # complete listing contains no indirect transfer at all, so the machine
        # contradicts the claim rather than merely failing to support it.
        # CONSTANTS is NOT_AVAILABLE because the ABI envelope carries no parse
        # record, so nothing says the listing was consumed in full. The
        # contradiction is the loudest signal in the system and must not be
        # masked by a dimension that was only unadjudicated: the worst finding
        # is a finding regardless of how much else went unmeasured.
        report = self.build(_span("  return vtable->load_slot_00abcdef01();"),
                            _machine_pack(STRAIGHT_BODY, drop=("parse",)), edges=())
        checks = report["static"]["checks"]
        self.assertEqual(checks["VIRTUAL DISPATCH"]["status"], "FAIL")
        self.assertEqual(checks["CONSTANTS"]["status"], "NOT_AVAILABLE")
        # Exactly one unadjudicated dimension, so the FAIL is what named the
        # verdict rather than a dimension that merely had no evidence.
        self.assertEqual([name for name in V.STATIC_CHECKS
                          if checks[name]["status"] == "NOT_AVAILABLE"], ["CONSTANTS"])
        self.assertEqual(report["static"]["status"], "FAIL")

    def test_an_unknown_outranks_an_unadjudicated_dimension(self):
        # UNKNOWN outranks NOT_AVAILABLE because the two are not degrees of the
        # same statement: an unknown is a boundary the reconstruction declared
        # and this evidence cannot resolve, while NOT_AVAILABLE is the absence
        # of evidence to judge with. A pack with no listing therefore has both
        # at once -- a named open question and four dimensions with nothing to
        # read -- and reading the aggregate as NOT_AVAILABLE lets the silence
        # mask the question, which is the more precise and the more actionable
        # of the two.
        report = self.build(_span("  return vtable->load_slot_00abcdef01();"), _pack(), edges=OUT)
        checks = report["static"]["checks"]
        self.assertEqual(checks["VIRTUAL DISPATCH"]["status"], "UNKNOWN")
        self.assertTrue([name for name in V.STATIC_CHECKS
                         if checks[name]["status"] == "NOT_AVAILABLE"])
        self.assertEqual(report["static"]["status"], "UNKNOWN")

    def test_not_available_still_outranks_a_warning(self):
        # The minimal form of the same rule, and the opposite shape to the FAIL
        # above: six checks PASS, one is a review item (two detected dispatch
        # sites the source span does not describe) and one was never adjudicated
        # (no parse record). "Collect the evidence" and "review this" are
        # different requests, so the nearer failure does not get to speak for
        # both -- and the WARN must not be read as the aggregate here, which is
        # what made an absence of evidence look like a soft defect.
        report = self.build(_span("  return vtable->load_slot_00abcdef01();"),
                            _machine_pack(INDIRECT_BODY, indirect=2, drop=("parse",)),
                            edges=())
        checks = report["static"]["checks"]
        self.assertEqual(checks["VIRTUAL DISPATCH"]["status"], "WARN")
        self.assertEqual(checks["CONSTANTS"]["status"], "NOT_AVAILABLE")
        self.assertEqual([name for name in V.STATIC_CHECKS
                          if checks[name]["status"] != "PASS"],
                         ["CONSTANTS", "VIRTUAL DISPATCH"])
        self.assertEqual(report["static"]["status"], "NOT_AVAILABLE")

    def test_a_warning_still_outranks_a_pass_shortfall(self):
        # The last rung, held so the ordering cannot be read as "anything at all
        # outranks a pass": nothing failed, nothing is unknown and nothing went
        # unadjudicated. Seven checks agree and one is a review item, so the
        # aggregate is WARN and not the PASS a majority of agreeing checks would
        # otherwise hand it.
        report = self.build(_span("  state->field = helper_00abcde1(3);"),
                            _machine_pack(BODY), edges=OUT)
        checks = report["static"]["checks"]
        self.assertEqual(checks["FIELDS/OFFSETS"]["status"], "WARN")
        self.assertEqual([name for name in V.STATIC_CHECKS
                          if checks[name]["status"] != "PASS"], ["FIELDS/OFFSETS"])
        self.assertEqual(report["static"]["status"], "WARN")

    def test_the_coverage_floor_alone_still_holds_the_aggregate(self):
        # The floor is a rung of its own and is retained: zero available static
        # evidence categories cannot be a PASS however clean the eight checks
        # read. Held together with the fact that the rung is not independently
        # reachable today -- EVIDENCE COVERAGE only reaches NOT_AVAILABLE when
        # no static category is available, and a pack with no available category
        # has no listing either, so the five listing-dependent checks are
        # NOT_AVAILABLE and that rung already holds the verdict. Pinned so a
        # change that made the floor reachable on its own would fail here and be
        # reviewed, rather than pass unnoticed.
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _pack(function_identity=_category(False), status=_category(False),
                                  runtime_metadata=_category(False)), edges=OUT)
        self.assertEqual(report["static"]["evidence_coverage"]["status"], "NOT_AVAILABLE")
        self.assertEqual(sorted(name for name in V.STATIC_CHECKS
                                if report["static"]["checks"][name]["status"] == "NOT_AVAILABLE"),
                         ["CONSTANTS", "CONTROL FLOW", "FIELDS/OFFSETS", "GLOBALS",
                          "VIRTUAL DISPATCH"])
        self.assertEqual(report["static"]["status"], "NOT_AVAILABLE")
        # One category back and the floor lifts to WARN; the verdict is then held
        # by the unadjudicated dimensions alone, which is the reason the two
        # reasons for NOT_AVAILABLE are pinned separately rather than merged.
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _pack(function_identity=_category(False),
                                  runtime_metadata=_category(False)), edges=OUT)
        self.assertEqual(report["static"]["evidence_coverage"]["status"], "WARN")
        self.assertEqual(report["static"]["status"], "NOT_AVAILABLE")

    def test_the_coverage_floor_still_names_the_aggregate(self):
        # The floor is retained as a floor. It is also subsumed by the new rule
        # for every state it can currently be reached in -- a target with no
        # available static category has no listing either, so the five
        # listing-dependent checks are NOT_AVAILABLE anyway -- which is exactly
        # why it is worth pinning separately: the two reasons for the verdict must
        # not drift into one.
        pack = _pack(abi=_category(False), types=_category(False), globals=_category(False),
                     vtables=_category(False), ghidra_function=_category(False),
                     decompilation=_category(False), disassembly=_category(False),
                     function_identity=_category(False), status=_category(False),
                     runtime_metadata=_category(False))
        report = self.build(_span("  return helper_00abcde1(3);"), pack, edges=OUT)
        self.assertEqual(report["static"]["evidence_coverage"]["status"], "NOT_AVAILABLE")
        self.assertEqual(report["static"]["status"], "NOT_AVAILABLE")

    def test_a_false_pass_control_an_unjudged_reconstruction_is_never_validated(self):
        # No source artifact at all, with a complete listing and every machine
        # record present. Five dimensions can now read that evidence and pass on
        # it, because a reconstruction that makes no claim cannot be contradicted
        # -- and the aggregate is still NOT_AVAILABLE, because the three checks
        # that judge a reconstruction need one to judge. Evidence-complete but
        # reconstruction-absent is not STATIC_VALIDATED.
        report = self.build(_span("  return helper_00abcde1(3);"), _machine_pack(BODY),
                            edges=OUT, write_source=False)
        checks = report["static"]["checks"]
        self.assertEqual(checks["GLOBALS"]["status"], "PASS")
        self.assertEqual(checks["CONTROL FLOW"]["status"], "PASS")
        for name in ("ABI", "CALLS", "RETURN SEMANTICS"):
            self.assertEqual(checks[name]["status"], "NOT_AVAILABLE", name)
        self.assertEqual(report["static"]["status"], "NOT_AVAILABLE")
        self.assertIsNone(report["source"]["path"])
        self.assertEqual(report["runtime"]["status"], "GATED")


# --------------------------------------------------------------------------
# Negative: absence of evidence must never produce a PASS.
# --------------------------------------------------------------------------
class AbsenceIsNotAPass(DimensionFixture):

    def test_no_source_artifact_is_not_available_not_pass(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(),
                            edges=OUT, write_source=False)
        self.assertEqual(report["status"], "NOT_AVAILABLE")
        self.assertNotEqual(report["static"]["status"], "PASS")

    def test_no_evidence_categories_at_all_blocks_a_static_pass(self):
        pack = _pack(function_identity=_category(False), status=_category(False),
                     runtime_metadata=_category(False))
        report = self.build(_span("  return helper_00abcde1(3);"), pack, edges=OUT)
        self.assertEqual(report["static"]["evidence_coverage"]["status"], "NOT_AVAILABLE")
        # This is the safety floor: a reconstruction cannot be statically
        # validated against zero evidence, however clean its source looks.
        self.assertEqual(report["static"]["status"], "NOT_AVAILABLE")

    def test_no_call_oracle_is_not_available_not_pass(self):
        # The source names a callee and the export records none. That is missing
        # evidence, not agreement and not contradiction.
        report = self.build(_span("  return helper_00abcde1(3);"), _pack())
        self.assertEqual(report["static"]["checks"]["CALLS"]["status"], "NOT_AVAILABLE")

    def test_a_complete_export_is_read_whole_and_a_disagreement_is_a_failure(self):
        # ``dependencies.edges`` is a scheduler projection capped at 30 rows, and
        # ``edges_truncated`` is computed over the record's incoming *and* outgoing
        # rows, so it fired on 149 of 617 index records while only 25 of them have
        # more than 30 outgoing rows -- 47 project no outgoing callee at all. That
        # made a permanent WARN out of a category error: a bounded projection is
        # not the xref universe. The export that truncated it is still on disk, so
        # CALLS now reads the whole callee set.
        #
        # This is what that surfaces here: 32 callees recorded against the 1 direct
        # transfer the complete listing shows. Two bounded, independent machine
        # sources that disagree are inconsistent evidence, and the honest verdict
        # for that is a failure and not a pass. The absent-export case, where the
        # projection is all there is and still cannot clear or refute anything, is
        # held in tests.test_validation_xref_evidence.
        many = OUT + [("00c0ffee", "%08x" % (0x00401000 + step), "direct-call")
                      for step in range(31)]
        report = self.build(_span("  return helper_00abcde1(3);"), _machine_pack(BODY), edges=many)
        calls = report["static"]["checks"]["CALLS"]
        self.assertEqual(calls["status"], "FAIL", calls["detail"])
        self.assertNotIn("truncated at export time", calls["detail"])
        self.assertNotEqual(report["static"]["status"], "PASS")

    def test_a_declared_field_offset_still_warns_and_still_blocks(self):
        # The check has no PASS branch: no machine-derived struct layout exists
        # to corroborate an offset. A reconstruction that asserts one is therefore
        # a review item, and this is the gate that keeps it one.
        report = self.build(_span("  state->field = 1;\n  return helper_00abcde1(3);"),
                            _pack(types=(True, ["Matrix3"])), edges=OUT, types=("Matrix3",))
        fields = report["static"]["checks"]["FIELDS/OFFSETS"]
        self.assertEqual(fields["status"], "WARN")
        self.assertIn("no machine-derived struct layout exists to corroborate", fields["detail"])
        self.assertNotEqual(report["static"]["status"], "PASS")

    def test_naming_a_type_is_not_declaring_an_offset(self):
        # The record names a type and the source only calls through it. Nothing
        # physical is asserted, so there is nothing to corroborate and nothing to
        # warn about; reporting an unverified offset here would state a defect
        # that does not exist.
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _pack(types=(True, ["Matrix3"])), edges=OUT, types=("Matrix3",))
        fields = report["static"]["checks"]["FIELDS/OFFSETS"]
        self.assertEqual(fields["status"], "NOT_AVAILABLE")
        self.assertIn("declares no field offset", fields["detail"])

    def test_a_method_call_through_a_pointer_is_not_a_field(self):
        report = self.build(_span("  return ports->query_00abcde1();"), _pack(), edges=OUT)
        self.assertEqual(report["static"]["checks"]["FIELDS/OFFSETS"]["status"], "NOT_AVAILABLE")

    def test_an_explicit_displacement_counts_as_a_declared_offset(self):
        report = self.build(_span("  return *(int *)(this + 0x10);"), _pack(), edges=OUT)
        fields = report["static"]["checks"]["FIELDS/OFFSETS"]
        self.assertEqual(fields["status"], "WARN")
        self.assertIn("0x10", fields["detail"])

    def test_unknown_stays_unknown_when_there_is_no_listing_to_judge_it(self):
        # A declared slot boundary with no machine listing is an open question, not
        # a defect and not a clearance, and it is still UNKNOWN at the check level.
        # The aggregate is UNKNOWN, and the rule that puts it there is that UNKNOWN
        # outranks NOT_AVAILABLE in the severity ladder. The two tokens are not
        # degrees of the same statement: UNKNOWN is a specific boundary the
        # reconstruction declared and this evidence cannot resolve, while
        # NOT_AVAILABLE is the absence of any evidence to judge with. Here both
        # are present -- VIRTUAL DISPATCH is UNKNOWN and CONTROL FLOW (and the
        # other listing-dependent dimensions) are NOT_AVAILABLE -- so reading the
        # aggregate as NOT_AVAILABLE would let the unadjudicated dimensions mask
        # the adjudicated one, collapsing "we know what we cannot resolve" into
        # "we know nothing", and losing exactly the distinction the two tokens
        # exist to make. UNKNOWN is the more precise and the more actionable of the
        # two: it names the boundary, so the aggregate is UNKNOWN.
        report = self.build(_span("  return vtable->load_slot_00abcdef01();"), _pack(), edges=OUT)
        checks = report["static"]["checks"]
        self.assertEqual(checks["VIRTUAL DISPATCH"]["status"], "UNKNOWN")
        self.assertEqual(checks["CONTROL FLOW"]["status"], "NOT_AVAILABLE")
        self.assertEqual(report["static"]["status"], "UNKNOWN")
        self.assertIn("UNKNOWN", {"PASS", "WARN", "FAIL", "UNKNOWN", "NOT_AVAILABLE"})


# --------------------------------------------------------------------------
# Negative: a contradiction is a FAIL, and FAIL outranks everything.
# --------------------------------------------------------------------------
class Contradiction(DimensionFixture):
    """A contradiction is a FAIL, and FAIL outranks everything.

    The fixtures carry a complete listing and the machine records, so the FAIL
    that is asserted is a refutation by the machine rather than a side effect of a
    dimension that had no evidence at all.
    """

    def test_a_named_callee_with_no_call_edge_fails(self):
        # The export records a different callee, so it demonstrably covered this
        # caller's call sites; a source callee it does not have is then refuted.
        # The listing shows the same transfer, so the two machine sources agree
        # and the machine-vs-machine rule is not what fails here.
        pack = _machine_pack([{"address": "00c0ffee", "instruction": "CALL 0x00999999"},
                              {"address": "00c0fff0", "instruction": "RET"}])
        report = self.build(_span("  return helper_00abcde1(3);"), pack,
                            edges=[(TARGET, "00999999", "direct-call")])
        calls = report["static"]["checks"]["CALLS"]
        self.assertEqual(calls["status"], "FAIL")
        self.assertIn("0x00abcde1", calls["detail"])
        self.assertNotEqual(report["static"]["status"], "PASS")

    def test_a_source_constant_absent_from_the_listing_fails(self):
        pack = _machine_pack([{"address": "00c0ffee", "instruction": "MOV EAX,0x7"},
                              {"address": "00c0fff0", "instruction": "RET"}])
        report = self.build(_span("  return helper_00abcde1(0x202);"), pack, edges=OUT)
        constants = report["static"]["checks"]["CONSTANTS"]
        self.assertEqual(constants["status"], "FAIL")
        self.assertIn("0x202", constants["detail"])
        self.assertNotEqual(report["static"]["status"], "PASS")

    def test_a_parse_that_claims_a_different_body_fails(self):
        # The integrity arm: the parse consumed a different number of
        # instructions than the listing holds, so the two disagree about the body
        # and neither can be taken as the whole of it. The source claims nothing
        # here, so this cannot be mistaken for a judgement of the reconstruction.
        pack = _machine_pack(BODY, declared=len(BODY) - 1)
        report = self.build(_span("  return helper_00abcde1(3);"), pack, edges=OUT)
        constants = report["static"]["checks"]["CONSTANTS"]
        self.assertEqual(constants["status"], "FAIL")
        self.assertIn("disagree about the body", constants["detail"])
        self.assertNotEqual(report["static"]["status"], "PASS")

    def test_source_claiming_virtual_dispatch_with_no_indirect_call_fails(self):
        pack = _machine_pack([{"address": "00c0ffee", "instruction": "MOV EAX,0x7"},
                              {"address": "00c0fff0", "instruction": "RET"}])
        report = self.build(_span("  return vtable->load_slot_00abcdef01();"), pack, edges=OUT)
        self.assertEqual(report["static"]["checks"]["VIRTUAL DISPATCH"]["status"], "FAIL")
        self.assertNotEqual(report["static"]["status"], "PASS")

    def test_a_source_constant_present_in_the_listing_passes(self):
        pack = _machine_pack([{"address": "00c0ffee", "instruction": "MOV EAX,0x202"},
                              {"address": "00c0fff0", "instruction": "RET"}])
        report = self.build(_span("  return helper_00abcde1(0x202);"), pack, edges=OUT)
        constants = report["static"]["checks"]["CONSTANTS"]
        self.assertEqual(constants["status"], "PASS")
        # The pass is about the listing being whole, not about the constants
        # being right -- the source-vs-listing rule is the branch that judges the
        # reconstruction, and it is a separate one.
        self.assertIn("fully parsed", constants["detail"])


# --------------------------------------------------------------------------
# False-positive controls: the predicate must not fire on honest reconstructions.
# --------------------------------------------------------------------------
class FalsePositiveControls(DimensionFixture):

    def test_in_edges_do_not_count_as_outgoing_calls(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(),
                            edges=[("00aaaaaa", TARGET, "direct-call")])
        self.assertEqual(report["static"]["checks"]["CALLS"]["status"], "NOT_AVAILABLE")

    def test_data_references_are_not_calls(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(),
                            edges=[(TARGET, "015d115d", "data-ref")])
        self.assertEqual(report["static"]["checks"]["CALLS"]["status"], "NOT_AVAILABLE")

    def test_the_target_does_not_call_itself(self):
        # The span under test contains its own address-suffixed declaration, so a
        # naive token scan reports every reconstruction as self-recursive.
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        self.assertEqual(report["static"]["checks"]["CALLS"]["status"], "PASS")

    def test_data_addresses_in_names_are_not_calls(self):
        # A global named with a data address must not be read as a callee.
        report = self.build(
            _span("  g_unmodelled_015d115d = helper_00abcde1(3);\n  return 1;"),
            _pack(), edges=OUT)
        self.assertEqual(report["static"]["checks"]["CALLS"]["status"], "PASS")

    def test_extra_machine_callees_do_not_fail_a_subset_match(self):
        # The source need only account for the calls it names; a callee it does
        # not name is not a contradiction.
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(),
                            edges=OUT + [(TARGET, "00777777", "direct-call")])
        self.assertEqual(report["static"]["checks"]["CALLS"]["status"], "PASS")

    def test_branch_words_inside_comments_do_not_create_a_claim(self):
        # The real false positive this guards: a straight-line machine body read
        # as branching because the word appeared in a comment.
        pack = _pack(disassembly=(True, {"instructions": [
            {"address": "00c0ffee", "instruction": "MOV EAX,0x7"},
            {"address": "00c0fff0", "instruction": "RET"}]}))
        body = ("  // loop for each port in the list, if it is open\n"
                "  return helper_00abcde1(3);")
        report = self.build(_span(body), pack, edges=OUT)
        self.assertIn("declares no branch", report["static"]["checks"]["CONTROL FLOW"]["detail"])

    def test_a_comment_constant_is_not_held_against_the_listing(self):
        pack = _pack(disassembly=(True, {"instructions": [
            {"address": "00c0ffee", "instruction": "MOV EAX,0x7"},
            {"address": "00c0fff0", "instruction": "RET"}]}))
        body = "  // see 0x202 for the sentinel\n  return helper_00abcde1(3);"
        report = self.build(_span(body), pack, edges=OUT)
        self.assertEqual(report["static"]["checks"]["CONSTANTS"]["status"], "NOT_AVAILABLE")

    def test_observed_mechanics_is_never_promoted_to_a_verdict(self):
        # observed_mechanics is a worker-authored transcript of the same read
        # that produced the source. Agreeing with it is internal consistency.
        report = self.build(_span("  return helper_00abcde1(0x5158);"), _pack(),
                            edges=OUT, mechanics=["the literal 0x5158 is read"])
        constants = report["static"]["checks"]["CONSTANTS"]
        self.assertEqual(constants["status"], "WARN")
        self.assertIn("not independent evidence", constants["detail"])

    def test_a_straight_line_body_with_no_dispatch_passes_that_check(self):
        # Evidenced absence, not a missing value: a complete body with no indirect
        # transfer *and* a machine dispatch record that counts none. A missing
        # record would not do -- see the check's own regression test.
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _machine_pack([{"address": "00c0ffee", "instruction": "MOV EAX,0x7"},
                                           {"address": "00c0fff0", "instruction": "RET"}]),
                            edges=OUT)
        self.assertEqual(report["static"]["checks"]["VIRTUAL DISPATCH"]["status"], "PASS")

    def test_a_missing_dispatch_record_is_not_a_record_of_zero(self):
        # The listing alone shows no dispatch site, but the second machine oracle
        # was never collected. A missing record is not a count of zero, so the
        # absence is not corroborated by anything and the verdict is a review item.
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _machine_pack([{"address": "00c0ffee", "instruction": "MOV EAX,0x7"},
                                           {"address": "00c0fff0", "instruction": "RET"}],
                                          drop=("dispatch",)),
                            edges=OUT)
        dispatch = report["static"]["checks"]["VIRTUAL DISPATCH"]
        self.assertEqual(dispatch["status"], "WARN")
        self.assertNotEqual(dispatch["status"], "PASS")
        self.assertIn("not a record of zero", dispatch["detail"])


# --------------------------------------------------------------------------
# EVIDENCE COVERAGE is a measurement, scoped to the static axis.
# --------------------------------------------------------------------------
class EvidenceCoverageScope(DimensionFixture):

    def test_the_unavailable_runtime_category_is_out_of_the_denominator(self):
        pack = _pack(abi=_category(False), globals=_category(False), vtables=_category(False),
                     ghidra_function=_category(False), decompilation=_category(False),
                     disassembly=_category(False), runtime=_category(False))
        report = self.build(_span("  return helper_00abcde1(3);"), pack, edges=OUT)
        basis = report["static"]["evidence_basis"]
        # runtime is excluded, so the static total is the pack size minus one.
        self.assertEqual(basis["static_evidence_categories_total"], len(pack["categories"]) - 1)

    def test_runtime_availability_never_moves_the_static_verdict(self):
        """The coupling that made PASS unreachable: a reserved runtime slot that
        can never be available must not be able to veto a static verdict."""
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _machine_pack(BODY, categories={"runtime": _category(False)}), edges=OUT)
        self.assertEqual(report["runtime"]["status"], "GATED")
        self.assertEqual(report["static"]["status"], "PASS")

    def test_coverage_is_reported_but_never_sums_into_the_verdict(self):
        report = self.build(_span("  return helper_00abcde1(3);"),
                            _machine_pack(BODY, categories={"types": (True, ["Matrix3"])}), edges=OUT,
                            types=("Matrix3",))
        # Coverage is partial, so it WARNs -- and the aggregate is decided by the
        # eight static checks, not by the measurement. A coverage shortfall is a
        # fact about the campaign, not a defect in this reconstruction.
        self.assertEqual(report["static"]["evidence_coverage"]["status"], "WARN")
        self.assertEqual(report["static"]["status"], "PASS")

    def test_full_static_coverage_can_reach_pass_on_the_coverage_check(self):
        pack = _pack(abi=(True, {"calling_convention": "__cdecl"}),
                     types=(True, []), globals=(True, []), vtables=(True, []),
                     ghidra_function=(True, {}), decompilation=(True, ""),
                     disassembly=(True, {"instructions": []}))
        report = self.build(_span("  return helper_00abcde1(3);"), pack, edges=OUT)
        self.assertEqual(report["static"]["evidence_coverage"]["status"], "PASS")


# --------------------------------------------------------------------------
# Report shape compatibility.
# --------------------------------------------------------------------------
class ReportShape(DimensionFixture):

    def test_all_nine_checks_are_still_present(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        for name in ("ABI", "CALLS", "GLOBALS", "FIELDS/OFFSETS", "CONSTANTS",
                     "CONTROL FLOW", "VIRTUAL DISPATCH", "RETURN SEMANTICS",
                     "EVIDENCE COVERAGE"):
            self.assertIn(name, report["checks"])
        self.assertIn("status", report["static"]["evidence_coverage"])
        self.assertNotIn("EVIDENCE COVERAGE", report["static"]["checks"])

    def test_check_statuses_stay_inside_the_existing_alphabet(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        allowed = {"PASS", "WARN", "FAIL", "UNKNOWN", "NOT_AVAILABLE"}
        for name, check in report["checks"].items():
            self.assertIn(check["status"], allowed, name)

    def test_runtime_dimension_uses_its_own_alphabet(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        # NOT_AVAILABLE is deliberately not a runtime state: it means "a verdict
        # could not be reached" and would be indistinguishable from a category
        # that was searched and found empty.
        self.assertIn(report["runtime"]["status"], {"GATED", "PASS"})

    def test_legacy_aggregate_coverage_block_is_unchanged_in_shape(self):
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        self.assertEqual(sorted(report["coverage"]),
                         ["attempted", "not_available", "pass", "ratio", "total", "unknown", "warn"])
        self.assertEqual(report["coverage"]["total"], len(report["checks"]))


# --------------------------------------------------------------------------
# Runtime evidence collection must not claim a search it never did.
# --------------------------------------------------------------------------
class RuntimeCategoryHonesty(DimensionFixture):

    def test_the_runtime_slot_says_it_was_never_searched(self):
        from tools.reconstruction_tooling.evidence import _record_categories
        report = self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        index, _ = build_index(self.root)
        categories = _record_categories(index["records"][TARGET], index, self.root)
        runtime = categories["runtime"]
        self.assertEqual(runtime["availability"], "unavailable")
        self.assertIsNone(runtime["value"])
        self.assertNotEqual(runtime["reason"], "no exact source evidence found")
        self.assertIn("never searched", runtime["reason"])
        self.assertEqual(report["runtime"]["status"], "GATED")

    def test_the_gates_travel_in_runtime_metadata_not_in_the_reserved_slot(self):
        from tools.reconstruction_tooling.evidence import _record_categories
        self.build(_span("  return helper_00abcde1(3);"), _pack(), edges=OUT)
        index, _ = build_index(self.root)
        categories = _record_categories(index["records"][TARGET], index, self.root)
        self.assertEqual(categories["runtime_metadata"]["availability"], "available")
        self.assertEqual(categories["runtime_metadata"]["value"]["validated"], 0)
        self.assertIsNone(categories["runtime"]["value"])


# --------------------------------------------------------------------------
# Evidence provenance: the pack a verdict is reached over, and where it came from.
# --------------------------------------------------------------------------
class EvidenceProvenance(DimensionFixture):
    """The validator must judge the pack that exists, not one it cannot build.

    ``collect(live=False)`` never calls ``_live_disassembly``, so a validator that
    re-collected on every run saw ``disassembly = unavailable`` for every target
    even though 195 of the 200 committed packs carry a listing. That made five
    checks structurally incapable of PASS and reported the gap as a per-target
    ``NOT_AVAILABLE``. These tests hold the reuse path, the refusal path and the
    no-pack path apart, because only the first is allowed to use a listing.
    """

    def listing_pack(self):
        return _pack(disassembly=(True, LISTING))

    def test_a_verified_persisted_pack_is_used_instead_of_recollecting(self):
        report = self.build(_span(CONSTANT_SPAN),
                            self.listing_pack(), edges=OUT, persist=True)
        block = report["binary_evidence"]
        self.assertEqual(block["source"], "persisted_pack")
        self.assertEqual(block["integrity"], "verified")
        self.assertIsNone(block["integrity_note"])
        self.assertEqual(block["mode"], "PERSISTED")
        self.assertEqual(block["content_sha256"],
                         json.loads((self.root / PACK_REL).read_text())["content_sha256"])

    def test_the_persisted_listing_is_what_the_checks_read(self):
        # The source literal is absent from the listing, so CONSTANTS can only
        # FAIL if these instructions were read -- the check has no other route to
        # a verdict that names a listing.
        report = self.build(_span(CONSTANT_SPAN),
                            self.listing_pack(), edges=OUT, persist=True)
        constants = report["static"]["checks"]["CONSTANTS"]
        self.assertEqual(constants["status"], "FAIL")
        self.assertIn("0x303", constants["detail"])
        # CONTROL FLOW is NOT_AVAILABLE when no listing exists and PASS when one
        # does, so it is the other half of the same proof.
        self.assertEqual(report["static"]["checks"]["CONTROL FLOW"]["status"], "PASS")
        # And the third: with no ABI parse record and no dispatch record, the two
        # checks that require a machine count to corroborate the listing stay out
        # of PASS. A missing record is not a count of zero.
        self.assertEqual(report["static"]["checks"]["VIRTUAL DISPATCH"]["status"], "WARN")
        self.assertEqual(report["static"]["checks"]["FIELDS/OFFSETS"]["status"], "NOT_AVAILABLE")

    def test_a_corrupted_digest_falls_back_and_reports_the_mismatch(self):
        report = self.build(_span(CONSTANT_SPAN),
                            self.listing_pack(), edges=OUT, persist=True, corrupt=True)
        block = report["binary_evidence"]
        self.assertEqual(block["source"], "recollected_live_false")
        self.assertEqual(block["integrity"], "digest_mismatch")
        self.assertIn("content_sha256", block["integrity_note"])
        # The fallback is the weaker path and is used as one: no listing, so the
        # check that needed it is back to having no evidence.
        self.assertEqual(report["static"]["checks"]["CONTROL FLOW"]["status"], "NOT_AVAILABLE")
        self.assertEqual(report["static"]["checks"]["CONTROL FLOW"]["status"], "NOT_AVAILABLE")

    def test_a_pack_for_another_target_is_refused(self):
        report = self.build(_span(CONSTANT_SPAN),
                            self.listing_pack(), edges=OUT, persist=True, pack_va="0x00c0ffef")
        self.assertEqual(report["binary_evidence"]["source"], "recollected_live_false")
        self.assertEqual(report["binary_evidence"]["integrity"], "target_mismatch")
        self.assertIn("0x00c0ffef", report["binary_evidence"]["integrity_note"])
        self.assertEqual(report["static"]["checks"]["CONTROL FLOW"]["status"], "NOT_AVAILABLE")

    def test_an_unreadable_pack_is_refused_rather_than_raised(self):
        report = self.build(_span(CONSTANT_SPAN),
                            self.listing_pack(), edges=OUT, persist=True, corrupt=True)
        _write(self.root / PACK_REL, "{not json")
        # Re-validated through the same root: a file that cannot be parsed must
        # degrade to a collection, not raise out of the validator.
        report = V.validate(root=self.root, va=TARGET, evidence=None, write=False)
        self.assertEqual(report["binary_evidence"]["integrity"], "unreadable")
        self.assertEqual(report["binary_evidence"]["source"], "recollected_live_false")

    def test_no_persisted_pack_behaves_exactly_as_before(self):
        # Nothing on disk: the collector runs, the pack is written, and the
        # report says so. This is the path that was already correct and must not
        # drift -- including the absent-pack case still writing a pack.
        report = self.build(_span(CONSTANT_SPAN), self.listing_pack(),
                            edges=OUT, from_disk=True, write=True)
        self.assertEqual(report["binary_evidence"]["source"], "recollected_live_false")
        self.assertEqual(report["binary_evidence"]["integrity"], "absent")
        self.assertIn("no persisted evidence pack", report["binary_evidence"]["integrity_note"])
        # A live=False collection produces no listing, exactly as before.
        self.assertEqual(report["static"]["checks"]["CONTROL FLOW"]["status"], "NOT_AVAILABLE")
        written = json.loads((self.root / PACK_REL).read_text())
        self.assertEqual(written["categories"]["disassembly"]["availability"], "unavailable")
        self.assertTrue((self.root / EVIDENCE_REL / TARGET[2:] / "validation.json").is_file())

    def test_a_verified_pack_is_never_overwritten_by_a_weaker_collection(self):
        before = _pack_json(self.listing_pack())
        self.build(_span(CONSTANT_SPAN), self.listing_pack(),
                   edges=OUT, persist=True, write=True)
        after = (self.root / PACK_REL).read_text()
        self.assertEqual(json.loads(after)["content_sha256"], json.loads(before)["content_sha256"])
        self.assertEqual(json.loads(after)["categories"]["disassembly"]["availability"], "available")

    def test_a_pack_that_failed_verification_is_left_on_disk(self):
        # Overwriting it would destroy the only copy of a listing this collection
        # path cannot produce, so the write is withheld and the report says why.
        corrupt_digest = json.loads(_pack_json(self.listing_pack(), corrupt=True))["content_sha256"]
        self.build(_span(CONSTANT_SPAN), self.listing_pack(),
                   edges=OUT, persist=True, corrupt=True, write=True)
        stored = json.loads((self.root / PACK_REL).read_text())
        self.assertEqual(stored["content_sha256"], corrupt_digest)
        self.assertTrue((self.root / EVIDENCE_REL / TARGET[2:] / "validation.json").is_file())

    def test_a_caller_supplied_pack_is_reported_as_unchecked(self):
        # Nothing on disk to verify, and nothing claimed: the caller owns the pack.
        report = self.build(_span(CONSTANT_SPAN),
                            self.listing_pack(), edges=OUT)
        block = report["binary_evidence"]
        self.assertEqual(block["source"], "caller_supplied")
        self.assertEqual(block["integrity"], "unchecked")
        self.assertIsNone(block["integrity_note"])

    def test_the_briefing_and_the_verdict_quote_the_same_pack(self):
        # Before reuse the validator judged a live=False collection while the
        # briefing quoted the committed pack -- two different digests, so the
        # worker was held to evidence it was never shown.
        report = self.build(_span(CONSTANT_SPAN),
                            self.listing_pack(), edges=OUT, persist=True)
        self.assertEqual(report["worker_context"]["source"], "built_from_judged_pack")
        self.assertEqual(report["worker_context"]["pack_content_sha256"],
                         report["binary_evidence"]["content_sha256"])
        self.assertEqual(report["worker_context"]["pack_content_sha256"],
                         json.loads((self.root / PACK_REL).read_text())["content_sha256"])

    def test_reusing_a_pack_leaves_the_runtime_axis_gated(self):
        report = self.build(_span(CONSTANT_SPAN),
                            self.listing_pack(), edges=OUT, persist=True)
        self.assertEqual(report["runtime"]["status"], "GATED")
        self.assertTrue(report["runtime"]["gated"])
        self.assertEqual(report["runtime"]["validated"], 0)
        self.assertEqual(report["runtime"]["gates"], ["gate-fixture-runtime"])
        # The reserved slot stays reserved: a reused pack does not turn a
        # never-searched category into a runtime observation.
        stored = json.loads((self.root / PACK_REL).read_text())
        self.assertEqual(stored["categories"]["runtime"]["availability"], "unavailable")
        self.assertIsNone(stored["categories"]["runtime"]["value"])
        self.assertNotIn("runtime", report["static"]["checks"])

    def test_the_markdown_names_the_pack_provenance(self):
        report = self.build(_span(CONSTANT_SPAN),
                            self.listing_pack(), edges=OUT, persist=True)
        text = V.render_markdown(report)
        self.assertIn("## Binary evidence", text)
        self.assertIn("`persisted_pack`", text)
        self.assertIn("## Worker briefing", text)
        self.assertIn("built_from_judged_pack", text)

    def test_a_corrupted_pack_is_named_in_the_markdown(self):
        report = self.build(_span(CONSTANT_SPAN),
                            self.listing_pack(), edges=OUT, persist=True, corrupt=True)
        text = V.render_markdown(report)
        self.assertIn("Integrity note:", text)
        self.assertIn("recollected_live_false", text)


class CallsExclusionBackCompat(unittest.TestCase):
    """The exclusion, measured against every evidence pack on disk.

    The unit tests above hold the rule from both sides. This one holds it against
    the live corpus: it re-judges every pack twice, once with the exclusion live
    and once with it stubbed back to "exclude nothing", and requires that the
    *only* check whose status moves is ``CALLS`` -- and that it moves only for a
    body whose extra transfer was a jump back into its own span. Nothing is
    written: both passes run ``validate(..., write=False)``.
    """

    PACK_GLOB = "reconstruction/evidence/*/evidence.json"
    # The validator's own severity order, restated here so "weakened" has a
    # meaning independent of the aggregate: FAIL, UNKNOWN, NOT_AVAILABLE, WARN, PASS.
    LADDER = ("FAIL", "UNKNOWN", "NOT_AVAILABLE", "WARN", "PASS")

    def _targets(self):
        return ["0x" + path.parent.name for path in sorted(REPO_ROOT.glob(self.PACK_GLOB))]

    def test_only_calls_moves_and_only_for_an_in_span_jump(self):
        targets = self._targets()
        self.assertTrue(targets, "no evidence packs on disk to measure against")
        unfiltered = V._intra_procedural_jump_targets
        moved, changed = [], []
        for target in targets:
            with_filter = V.validate(va=target, write=False)
            V._intra_procedural_jump_targets = lambda addresses, texts: set()
            try:
                without = V.validate(va=target, write=False)
            finally:
                V._intra_procedural_jump_targets = unfiltered
            after = {name: check["status"]
                     for name, check in with_filter["static"]["checks"].items()}
            before = {name: check["status"]
                      for name, check in without["static"]["checks"].items()}
            for name in sorted(after):
                if after[name] != before[name]:
                    changed.append((target, name, before[name], after[name]))
            if with_filter["static"]["status"] != without["static"]["status"]:
                moved.append((target, without["static"]["status"], with_filter["static"]["status"]))
            # The detail has to account for the exclusion whenever it is used, so
            # a moved verdict is never an unexplained one.
            if "intra-procedural jump" in with_filter["static"]["checks"]["CALLS"]["detail"]:
                self.assertIn("inside the recovered body span", with_filter["static"]["checks"]["CALLS"]["detail"])
        self.assertEqual([entry for entry in changed if entry[1] != "CALLS"], [],
                         "the exclusion reached a check other than CALLS")
        for target, name, before_status, after_status in changed:
            self.assertLessEqual(self.LADDER.index(before_status), self.LADDER.index(after_status),
                                 "the exclusion weakened %s on %s (%s -> %s)" % (name, target, before_status, after_status))
        for target in {entry[0] for entry in changed}:
            pack = json.loads((REPO_ROOT / "reconstruction/evidence" / target[2:] / "evidence.json").read_text(encoding="utf-8"))
            listing = V._listing(pack.get("categories") or {})
            self.assertIsNotNone(listing, "%s has no listing to have filtered a jump" % target)
            self.assertTrue(V._intra_procedural_jump_targets(*listing),
                            "%s moved without an in-span jump to exclude" % target)
        print("\nCALLS exclusion back-compat: %d pack(s) measured, %d check status(es) moved, %d static aggregate(s) moved: %s"
              % (len(targets), len(changed), len(moved), changed or "none"))



# --------------------------------------------------------------------------
# Hexadecimal literals are compared by VALUE, not by spelling.
#
# Regression lock for the defect this wave exposed: ``_hex_tokens`` returned the
# lowercased token text, so the reconstruction's ``0x0C`` and the listing's
# ``0xc`` were two different constants and the CONSTANTS arm failed the target
# for a spelling the machine plainly contained. Width is not semantic.
#
# Every case below is written so that reverting the fix to ``token.lower()``
# turns it red -- that is what makes these tests mutation-resistant rather than
# merely descriptive.
# --------------------------------------------------------------------------
class HexTokenValueComparison(unittest.TestCase):

    def test_width_is_not_semantic(self):
        # The corpus defect verbatim: 0x0C in source, 0xc in the listing.
        self.assertEqual(V._hex_tokens("x = 0x0C;"), {"0xc"})
        self.assertEqual(V._hex_tokens("MOV EAX,dword ptr [ESI + 0xc]"), {"0xc"})
        self.assertEqual(V._hex_tokens("x = 0x0C;"), V._hex_tokens("[ESI + 0xc]"))

    def test_case_is_not_semantic(self):
        self.assertEqual(V._hex_tokens("0XABCDEF"), {"0xabcdef"})
        self.assertEqual(V._hex_tokens("0XAbCdEf"), V._hex_tokens("0xabcdef"))

    def test_a_value_is_still_itself(self):
        # The fix must not over-normalise into a bag-of-digits comparison.
        for left, right in (("0x4", "0x40"), ("0x0c", "0xc0"), ("0x100", "0x10"),
                            ("0x1", "0x2"), ("0xdead", "0xbeef"), ("0x0c", "0x0d")):
            self.assertNotEqual(V._hex_tokens(left), V._hex_tokens(right),
                                "%s and %s are different values" % (left, right))

    def test_leading_zeros_do_not_change_the_value(self):
        for spelling in ("0x0c", "0x0C", "0x00c", "0x0000c", "0xc"):
            self.assertEqual(V._hex_tokens(spelling), {"0xc"}, spelling)

    def test_a_bare_decimal_run_is_still_not_a_constant(self):
        # Preserved from the original rule: only an explicit 0x token counts, or
        # array sizes and line numbers would sweep in.
        self.assertEqual(V._hex_tokens("arr[12] = 34;"), set())

    def test_comments_still_contribute_nothing(self):
        self.assertEqual(V._hex_tokens("// 0xdeadbeef\nint x;"), set())
        self.assertEqual(V._hex_tokens("/* 0xc0de */ int x;"), set())

    def test_a_data_address_is_canonicalised_by_value(self):
        # GLOBALS intersects the same two token sets, so a source address and a
        # listing address must meet regardless of the width either was written at.
        self.assertEqual(V._hex_tokens("0x013EB258"), {"0x13eb258"})
        self.assertEqual(V._hex_tokens("0x013EB258"), V._hex_tokens("0x13eb258"))

    def test_the_mutation_the_defect_was(self):
        # A stand-in for the old implementation, asserted against the new one.
        # If someone restores textual comparison this fails by construction.
        import re as _re
        def old(text):
            return set(t.lower() for t in V.HEX_TOKEN.findall(V._code(text)))
        self.assertNotEqual(old("x = 0x0C;"), old("MOV EAX,[ESI + 0xc]"))
        self.assertEqual(V._hex_tokens("x = 0x0C;"), V._hex_tokens("MOV EAX,[ESI + 0xc]"))


class ConstantSpellingDoesNotDecideAVerdict(DimensionFixture):
    """The dimension-level statement of the same rule, through the real arm."""

    def test_a_source_spelling_the_listing_matches_by_value_passes(self):
        # Source states 0x0C, listing states 0xc. Same value, so the claim is
        # grounded and the arm passes instead of failing the target.
        body = [{"address": "00c0ffee", "instruction": "CMP byte ptr [ECX + 0xc],0x0"},
                {"address": "00c0fff1", "instruction": "RET"}]
        report = self.build(_span("  if (reconstruct_me_00abcde1(0x0C) == 0x0C) return 1;"),
                            _machine_pack(body), edges=OUT)
        constants = report["static"]["checks"]["CONSTANTS"]
        self.assertEqual(constants["status"], "PASS", constants["detail"])

    def test_a_genuinely_absent_value_still_fails(self):
        # The fix must not turn the arm into a rubber stamp: a value the listing
        # does not contain is still a machine refutation.
        body = [{"address": "00c0ffee", "instruction": "MOV EAX,0x7"},
                {"address": "00c0fff1", "instruction": "RET"}]
        report = self.build(_span("  return helper_00abcde1(0x202);"), _machine_pack(body), edges=OUT)
        self.assertEqual(report["static"]["checks"]["CONSTANTS"]["status"], "FAIL")

    def test_a_value_merely_shifted_by_one_digit_still_fails(self):
        # 0xc is present, 0xc0 is not: near-miss padding must not rescue it.
        body = [{"address": "00c0ffee", "instruction": "MOV EAX,dword ptr [ESI + 0xc]"},
                {"address": "00c0fff1", "instruction": "RET"}]
        report = self.build(_span("  return helper_00abcde1(0xc0);"), _machine_pack(body), edges=OUT)
        self.assertEqual(report["static"]["checks"]["CONSTANTS"]["status"], "FAIL")


if __name__ == "__main__":
    unittest.main()
