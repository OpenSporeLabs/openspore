"""FIELDS/OFFSETS: the evidenced absence for a body whose receiver is unknown.

The check already had one PASS that rests on an absence -- a body that names no
displacement through the receiver register -- but it sat inside
``if listing is not None and register:``, so it was reachable only when the
machine-derived record had already named that register. Whenever the record
abstained (``receiver_not_determinable``,
``ecx_address_taken_without_memory_access``, or a record naming no register at
all), a body that genuinely performs *no* field access fell through to
``NOT_AVAILABLE`` -- an absence of evidence that is disqualifying for the static
aggregate over a reconstruction with nothing wrong with it. Nine committed
targets sat in exactly that state.

So this file holds the second, receiver-agnostic absence arm, and it holds it
from every side the arm could be wrong in. The distinction it rests on is spelled
out in the detail string and pinned here: **the receiver's identity and layout
remain unknown, and separately this body performs no field access.** The second
is evidenced by a complete, fully parsed listing; the first is not claimed in
either direction, and no member name, offset or receiver identity is inferred
from the absence.

Fail-closed is the whole point, so each guard has a test that removes it and
shows the verdict go back to what it was: a truncated listing envelope, a
listing the machine parse did not consume in full, a source span that declares a
field offset, and a body that does address memory. The last one is asserted
twice -- with a displacement, and with a bare ``[ECX]`` that names no offset at
all, because a load of the word at offset zero is the same field claim as a load
of the word at ``0x80``.

The final test is a regression guard in the other direction: when the receiver
register *is* known, the pre-existing arms and their exact wording must be
untouched, so the new path is a strictly additional one.
"""

import json
import unittest
from pathlib import Path
from tempfile import TemporaryDirectory

from tools.reconstruction_tooling import validate as V
from tools.reconstruction_tooling.frontier import _INDEX_CACHE

TARGET = "0x00c0ffee"
HELPER = "00abcde1"
MANIFEST_REL = "knowledgegraph/research/source-reconstruction-manifest.json"
QUEUE_REL = "knowledgegraph/triage/queue-f0e310e0-v6.json"
SEMANTIC_REL = "knowledgegraph/research/semantic-decomp.json"
XREF_REL = "knowledgegraph/triage/xrefs-2540f2ca.tsv"
METADATA_REL = "reconstruction/metadata/pkg_fixture/00c0ffee.json"
SOURCE_REL = "src/fixture_pkg/fixture.cpp"
EVIDENCE_REL = "reconstruction/evidence"
PACK_REL = EVIDENCE_REL + "/" + TARGET[2:] + "/evidence.json"
OUT = [(TARGET, HELPER, "direct-call")]


def _json(value):
    return json.dumps(value)


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


# -- The real shapes -------------------------------------------------------
#
# The three bodies below are the shapes the committed corpus actually has, each
# reproduced instruction for instruction from a pack so the fixtures are the
# cases and not a sketch of them. All three name no memory operand at all, which
# is the property the new arm asks of a listing, and none of them names a
# receiver field.

# 0x0096ff70 and 0x007d9410 and 0x00980480: an adjustor thunk. The ``0xc`` in
# ``SUB ECX,0xc`` is an immediate, not a displacement -- it adjusts the receiver
# pointer the adjustor hands on, it does not read memory -- so it must not be
# read as a field access. That distinction is the whole reason this arm scans
# *operands* rather than hex literals.
ADJUSTOR_BODY = [{"address": "00c0ffee", "instruction": "SUB ECX,0xc"},
                 {"address": "00c0fff1", "instruction": "JMP 0x0096ffd0"}]

# 0x00980510 and 0x00980c50: a constant-returning stub.
CONSTANT_STUB_BODY = [{"address": "00c0ffee", "instruction": "MOV EAX,0x202"},
                      {"address": "00c0fff1", "instruction": "RET"}]

# A true leaf, and the generic case the other two are instances of: a call, an
# argument on the stack, and a return. It is kept separate because it is the
# shape the old arm could serve whenever the record happened to name a register,
# and the shape the new arm exists for when it does not.
LEAF_BODY = [{"address": "00c0ffee", "instruction": "PUSH ESI"},
             {"address": "00c0fff1", "instruction": "CALL 0x00abcde1"},
             {"address": "00c0fff6", "instruction": "ADD ESP,0x4"},
             {"address": "00c0fff9", "instruction": "XOR EAX,EAX"},
             {"address": "00c0fffb", "instruction": "RET"}]

# The refuting bodies, one per way a body can touch memory.
DISPLACED_BODY = [{"address": "00c0ffee", "instruction": "MOV EAX,dword ptr [ECX + 0x80]"},
                  {"address": "00c0fff2", "instruction": "RET"}]
# No displacement at all, and yet the same claim: the word at offset zero.
BARE_DEREF_BODY = [{"address": "00c0ffee", "instruction": "MOV EAX,dword ptr [ECX]"},
                   {"address": "00c0fff1", "instruction": "RET"}]
# An address taken without a read -- 0x009817c0's shape, whose receiver record
# abstained for exactly this reason. A ``LEA`` is not a memory access, and the
# check is not in a position to know that; the listing shows a bracket and the
# arm declines to read past it.
ADDRESS_TAKEN_BODY = [{"address": "00c0ffee", "instruction": "LEA EAX,[ECX + 0xc]"},
                      {"address": "00c0fff2", "instruction": "RET 0x4"}]
# An implicit memory operand with no bracket to find, the one shape a scan of
# bracketed operands alone would miss.
STRING_MOVE_BODY = [{"address": "00c0ffee", "instruction": "REP MOVSD"},
                    {"address": "00c0fff1", "instruction": "RET"}]

NO_FIELD_SOURCE = "  helper_00abcde1(1);\n  return 0;"
DECLARED_SOURCE = "  return *(int *)(this + 0x40);"
NAMED_FIELD_SOURCE = "  return state->field;"


def _receiver_record(register=None, offsets=(), reason=None, present=None, bounds_only=True):
    """A ``receiver`` sub-record that names no register unless asked to.

    The abstaining shapes are reproduced as the corpus carries them: ``register:
    null`` with the record's own ``reason``, and ``present: false`` with a
    ``confidence: OBSERVED`` observation of a body that never dereferences
    anything. Both are cases where *the record exists and says it cannot name a
    receiver*, which is different from the record being absent -- and different
    again from the record naming one.
    """
    record = {"bounds_only": bounds_only, "confidence": "UNKNOWN", "distinct_offsets": 0,
              "max_offset": None, "offsets": list(offsets), "register": register,
              "shape": None, "written_through": 0}
    if present is None:
        record["present"] = None if reason else (False if register is None else True)
    else:
        record["present"] = present
    if reason:
        record["reason"] = reason
    return record


def _machine_abi(receiver=None, parse=None, dispatch=None, instructions=()):
    """The machine-derived ABI envelope, as ``evidence.collect`` publishes it."""
    value = {"calling_convention": "__cdecl"}
    if receiver is not False:
        value["receiver"] = _receiver_record(**(receiver or {}))
    if parse is not False:
        value["parse"] = parse if parse is not None else {
            "declared_count": len(instructions), "degraded": False,
            "esp_unresolved": False, "flow_complete": True, "unparsed": 0}
    if dispatch is not False:
        value["dispatch"] = dispatch if dispatch is not None else {
            "indirect_calls": 0, "vtable_shaped_loads": 0}
    return value


def _machine_pack(instructions, receiver=None, parse=None, dispatch=None,
                  drop=(), truncated_listing=False, derived=False, **packs):
    """A pack with a complete listing and the machine records beside it.

    ``receiver`` is the ``receiver`` sub-record's keyword arguments, ``parse`` and
    ``dispatch`` are the sub-records themselves (``False`` to omit one entirely),
    and ``drop`` omits a sub-record from the envelope afterwards -- which is how a
    test says "never collected" rather than "says zero". ``truncated_listing``
    replaces the instruction list with the ``{"truncated": true}`` envelope the
    collector writes when a body is too long to publish whole.
    """
    value = _machine_abi(receiver=receiver, parse=parse, dispatch=dispatch,
                         instructions=instructions)
    for key in drop:
        value.pop(key, None)
    disassembly = ({"truncated": True,
                    "preview": [dict(item) for item in instructions]} if truncated_listing
                   else {"instructions": [dict(item) for item in instructions]})
    pack = _pack(disassembly=(True, disassembly), abi=(True, value))
    if derived:
        pack["categories"][V.ABI_DERIVED_CATEGORY] = _category(True, dict(value))
        pack["categories"]["abi"] = _category(True, {
            "architecture": "x86-32", "calling_convention": "__cdecl", "return_type": "int"})
    for key, override in packs.items():
        pack["categories"][key] = override
    return pack


class FieldsAbsenceFixture(unittest.TestCase):
    """A throwaway repository built from the same canonical inputs as production.

    The projection is rebuilt by the real index builder rather than hand-written,
    so a verdict here is reached by the same path production reaches it by. Only
    FIELDS/OFFSETS is asserted, so the harness hands in exactly the evidence that
    dimension reads plus what the aggregate needs to be a verdict at all.
    """

    def build(self, source_text, pack, edges=()):
        tmp = TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.addCleanup(_INDEX_CACHE.clear)
        root = Path(tmp.name)
        self.root = root

        (root / SOURCE_REL).parent.mkdir(parents=True, exist_ok=True)
        (root / SOURCE_REL).write_text(source_text, encoding="utf-8")
        _write(root / MANIFEST_REL,
               '{"schema":"openspore-source-reconstruction-manifest-1",'
               '"binary":{"sha256":"fixture","name":"SporeApp.exe","source":"fixture"},'
               '"functions":[{"va":"%s","normalized_symbol":"reconstruct_me_00c0ffee",'
               '"subsystem":"FIXTURE","package":"pkg_fixture","source_file":"%s",'
               '"body_status":"unresolved","observed_mechanics":[],'
               '"evidence_level":"SUPPORTED","runtime_gates":["gate-fixture-runtime"],'
               '"audit_runtime_validated":0}],'
               '"packages":[{"id":"pkg_fixture","status":"triage_only"}],"types":[]}'
               % (TARGET, SOURCE_REL))
        _write(root / QUEUE_REL, '{"schema":"openspore-triage-queue-1","queue":[]}')
        _write(root / SEMANTIC_REL, '{"schema":"openspore-semantic-decomp-1","records":[],'
               '"contradictions":[],"family_index":[]}')
        rows = ["caller_va\tcallee_va\treference_type\tcallsite_va"]
        for caller, callee, kind in edges:
            rows.append("%s\t%s\t%s\t00c0ff00" % (caller, callee, kind))
        _write(root / XREF_REL, "\n".join(rows) + "\n")
        _write(root / METADATA_REL,
               '{"va":"%s","abi":{"calling_convention":"__cdecl","return_type":"int"},"types":[]}'
               % TARGET)
        return V.validate(root=root, va=TARGET, evidence=pack, write=False)

    def fields(self, report):
        return report["static"]["checks"]["FIELDS/OFFSETS"]


def _write(path, payload):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(payload, encoding="utf-8")


# The fragments the new arm's detail must always carry, and the ones it must
# never carry. Written as constants so a test asserts against the shape and not
# against a string copied out of the implementation.
UNCLAIMED = "unclaimed in both directions"
NO_LAYOUT = "names no receiver register"
NO_FIELD_ACCESS = "performs no field access"
# Phrases that would turn the absence into a positive claim about a receiver.
# Each is a way this pass could be read as having established something the
# machine never said, and none of them may appear.
LAYOUT_CLAIMS = ("layout confirmed", "layout is confirmed", "layout established",
                 "no fields", "receiver is null", "receiver confirmed",
                 "no member", "identifies no field")


class ReceiverUnknownNoFieldBody(FieldsAbsenceFixture):
    """The three corpus shapes, each of which fell to NOT_AVAILABLE before."""

    def test_a_true_no_field_leaf_with_an_unknown_receiver_now_passes(self):
        # The case the arm exists for. A complete, fully parsed listing that names
        # no memory operand, a source that declares no offset, and a record that
        # abstained on the receiver. Before the arm this was NOT_AVAILABLE, which
        # is disqualifying for a reconstruction with no defect in it.
        report = self.build(_span(NO_FIELD_SOURCE),
                            _machine_pack(LEAF_BODY, receiver={"reason": "ecx_read_without_deref"}),
                            edges=OUT)
        fields = self.fields(report)
        self.assertEqual(fields["status"], "PASS", fields["detail"])
        self.assertEqual(fields["coverage"], "complete")
        self.assertIn(NO_FIELD_ACCESS, fields["detail"])
        self.assertIn(UNCLAIMED, fields["detail"])
        self.assertEqual(fields["evidence"], [V.INDEX_REL, V.EVIDENCE_REL])

    def test_the_detail_holds_the_two_claims_apart(self):
        # Requirement of the string itself: the receiver being unknown is not
        # claimed, and the body doing no field access is. Both halves have to be
        # there, and the second has to say what evidences it -- the complete
        # listing -- so a reader cannot mistake one for the other.
        report = self.build(_span(NO_FIELD_SOURCE),
                            _machine_pack(LEAF_BODY, receiver={"reason": "ecx_read_without_deref"}),
                            edges=OUT)
        detail = self.fields(report)["detail"]
        self.assertIn(NO_LAYOUT, detail)
        self.assertIn(UNCLAIMED, detail)
        self.assertIn("complete %d-instruction listing" % len(LEAF_BODY), detail)
        self.assertIn("consumed in full by the machine parse", detail)
        self.assertIn("no memory operand through any register at all", detail)
        # The unknown half is never upgraded into a fact about the target.
        for phrase in LAYOUT_CLAIMS:
            self.assertNotIn(phrase, detail)

    def test_an_adjustor_thunk_passes(self):
        # 0x0096ff70 / 0x007d9410 / 0x00980480, instruction for instruction. The
        # ``0xc`` is an immediate the adjustor hands on, not a displacement, and
        # a scan of hex literals rather than of operands would have read it as a
        # field access and left these three exactly where they were.
        report = self.build(_span("  return 0;"),
                            _machine_pack(ADJUSTOR_BODY, receiver={"present": False}),
                            edges=OUT)
        fields = self.fields(report)
        self.assertEqual(fields["status"], "PASS", fields["detail"])
        self.assertIn("the complete 2-instruction listing", fields["detail"])
        self.assertFalse(V._any_field_access([item["instruction"] for item in ADJUSTOR_BODY]))

    def test_a_constant_returning_stub_passes(self):
        # 0x00980510 / 0x00980c50. The literal 0x202 is a returned constant and
        # says nothing about a layout; the arm reads the absence of an operand,
        # not the presence of a number.
        report = self.build(_span("  return 0x202;"),
                            _machine_pack(CONSTANT_STUB_BODY, receiver={"present": False}),
                            edges=OUT)
        fields = self.fields(report)
        self.assertEqual(fields["status"], "PASS", fields["detail"])
        self.assertIn("the complete 2-instruction listing", fields["detail"])

    def test_a_record_that_names_no_register_agrees_with_one_that_abstains(self):
        # Two records that look the same to this check -- ``register: null`` -- and
        # arrived at it differently: one observed a body that never dereferences
        # anything, the other declined to name a receiver. The pass is about the
        # listing, so both reach it, and neither is reported as knowing more than
        # the other.
        for receiver in ({"present": False}, {"reason": "ecx_reassigned_before_deref"},
                         {"reason": "ecx_address_taken_without_memory_access"}):
            report = self.build(_span(NO_FIELD_SOURCE),
                                _machine_pack(ADJUSTOR_BODY, receiver=receiver), edges=OUT)
            self.assertEqual(self.fields(report)["status"], "PASS", receiver)


class CompleteListingRequired(FieldsAbsenceFixture):
    """The listing must be the whole body. Each guard, removed in turn."""

    def test_a_truncated_listing_envelope_never_reaches_the_arm(self):
        # ``_listing`` returns ``None`` for a ``{"truncated": true}`` envelope, so
        # the preview is never read as a body. This is the shape that matters
        # most here: the preview is a *prefix*, and a prefix of a body that later
        # reads ``[ECX + 0x80]`` is exactly what would manufacture a false
        # clearance -- so the fixture's preview is deliberately a body that reads
        # nothing, leaving the truncation guard as the only thing that can hold.
        report = self.build(_span(NO_FIELD_SOURCE),
                            _machine_pack(ADJUSTOR_BODY, receiver={"present": False},
                                          truncated_listing=True), edges=OUT)
        fields = self.fields(report)
        self.assertEqual(fields["status"], "NOT_AVAILABLE", fields["detail"])
        self.assertIn("no machine-derived receiver evidence", fields["detail"])
        self.assertNotIn(NO_FIELD_ACCESS, fields["detail"])
        self.assertIsNone(V._listing(_machine_pack(ADJUSTOR_BODY, truncated_listing=True)
                                     ["categories"]))

    def test_a_degraded_or_partly_unparsed_listing_never_reaches_the_arm(self):
        # The listing exists and is bounded, but the machine parse did not consume
        # it whole, so a field access could sit in an instruction the parse never
        # read. That is the difference between a body that performs no field
        # access and a fragment of one, and it is not a clearance.
        for parse in ({"declared_count": 2, "degraded": True, "unparsed": 0},
                      {"declared_count": 2, "degraded": False, "unparsed": 1},
                      {"declared_count": 2, "degraded": True, "unparsed": 3}):
            report = self.build(_span(NO_FIELD_SOURCE),
                                _machine_pack(ADJUSTOR_BODY, parse=parse,
                                              receiver={"present": False}), edges=OUT)
            fields = self.fields(report)
            self.assertEqual(fields["status"], "NOT_AVAILABLE", parse)
            self.assertNotIn(NO_FIELD_ACCESS, fields["detail"])

    def test_a_listing_with_no_parse_record_never_reaches_the_arm(self):
        # Completeness of the *body* is the second half of the guard and a missing
        # parse record says nothing about it. A record is not a count of zero:
        # absent is absent, and the arm reads it as absent.
        for drop in (("parse",),):
            report = self.build(_span(NO_FIELD_SOURCE),
                                _machine_pack(ADJUSTOR_BODY, drop=drop,
                                              receiver={"present": False}), edges=OUT)
            fields = self.fields(report)
            self.assertEqual(fields["status"], "NOT_AVAILABLE", fields["detail"])
            self.assertNotIn(NO_FIELD_ACCESS, fields["detail"])
        # And with no listing at all.
        report = self.build(_span(NO_FIELD_SOURCE), _pack(), edges=OUT)
        self.assertEqual(self.fields(report)["status"], "NOT_AVAILABLE")

    def test_a_truncated_derived_envelope_never_reaches_the_arm(self):
        # The parse record read from a truncated ``abi_derived`` envelope is a
        # fragment, and a fragment of a parse record is not a parse record. The
        # arm is refused the same way the other three machine-record checks are.
        # Both locations are emptied of the parse record, so what is left to be
        # mistaken for one is the truncated envelope itself.
        pack = _machine_pack(ADJUSTOR_BODY, receiver={"present": False}, drop=("parse",))
        pack["categories"][V.ABI_DERIVED_CATEGORY] = _category(
            True, {"truncated": True, "preview": "..."})
        report = self.build(_span(NO_FIELD_SOURCE), pack, edges=OUT)
        fields = self.fields(report)
        self.assertEqual(fields["status"], "NOT_AVAILABLE", fields["detail"])
        self.assertNotIn(NO_FIELD_ACCESS, fields["detail"])
        # The fragment is not a record of zero, and reading it as one is what
        # would have cleared the arm.
        self.assertEqual(V._machine_record(pack["categories"], pack["categories"]["abi"]["value"],
                                          {}, "parse"), {})


class FieldAccessRefutesTheArm(FieldsAbsenceFixture):
    """A body that addresses memory is out, however the record reads."""

    def test_a_displacement_through_an_unknown_register_never_reaches_the_arm(self):
        report = self.build(_span(NO_FIELD_SOURCE),
                            _machine_pack(DISPLACED_BODY, receiver={"reason": "ecx_reassigned_before_deref"}),
                            edges=OUT)
        fields = self.fields(report)
        self.assertEqual(fields["status"], "NOT_AVAILABLE", fields["detail"])
        self.assertNotIn(NO_FIELD_ACCESS, fields["detail"])
        self.assertTrue(V._any_field_access([item["instruction"] for item in DISPLACED_BODY]))

    def test_a_bare_dereference_is_a_field_access_too(self):
        # ``MOV EAX,[ECX]`` names no offset at all, and a scan that only looked
        # for displacements would have read the empty result as "no field access".
        # The word at offset zero is a field like any other, so the arm asks the
        # wider question and this stays out.
        report = self.build(_span(NO_FIELD_SOURCE),
                            _machine_pack(BARE_DEREF_BODY, receiver={"reason": "ecx_read_without_deref"}),
                            edges=OUT)
        fields = self.fields(report)
        self.assertEqual(fields["status"], "NOT_AVAILABLE", fields["detail"])
        self.assertTrue(V._any_field_access([item["instruction"] for item in BARE_DEREF_BODY]))

    def test_a_taken_address_is_not_treated_as_proved_absence(self):
        # 0x009817c0's shape, and the honest reading of it: a ``LEA`` takes an
        # address without reading memory, and the record abstained for precisely
        # that reason. The check is not in a position to resolve the question -- it
        # does not know which register is the receiver, or whether ``[ECX + 0xc]``
        # is a field at all -- so it declines and says nothing either way.
        report = self.build(_span(NO_FIELD_SOURCE),
                            _machine_pack(ADDRESS_TAKEN_BODY,
                                          receiver={"reason": "ecx_address_taken_without_memory_access"}),
                            edges=OUT)
        fields = self.fields(report)
        self.assertEqual(fields["status"], "NOT_AVAILABLE", fields["detail"])
        self.assertNotIn(NO_FIELD_ACCESS, fields["detail"])

    def test_an_implicit_memory_operand_is_not_missed(self):
        # A string move has no bracket to find, so a scan of bracketed operands
        # alone reads a body that copies memory as one that touches none.
        report = self.build(_span(NO_FIELD_SOURCE),
                            _machine_pack(STRING_MOVE_BODY, receiver={"present": False}), edges=OUT)
        fields = self.fields(report)
        self.assertEqual(fields["status"], "NOT_AVAILABLE", fields["detail"])
        self.assertTrue(V._any_field_access(["REP MOVSD"]))
        # A register-only mnemonic is not held against the body -- the scan is
        # over operands, not over a list of scary instructions.
        self.assertFalse(V._any_field_access(["MOV EAX,EBX", "XOR EAX,EAX", "RET"]))
        # And the one ambiguity, resolved the only direction that cannot produce a
        # false clearance: ``MOVSD`` spelled without brackets is the SSE register
        # move or the string dword move, and this cannot tell them apart, so it
        # declines rather than assumes. Over-reporting costs the arm its pass and
        # leaves the body the verdict it already had; the other reading would
        # clear a body that copies memory.
        self.assertTrue(V._any_field_access(["MOVSD XMM0,XMM1"]))

    def test_a_field_access_reached_through_an_alias_never_reaches_the_arm(self):
        # The body copies the receiver into another register and reads through the
        # copy, so nothing addresses ``ECX``. A filter on the receiver register
        # would have found nothing; the arm is register-agnostic, so it finds the
        # displacement regardless of which register carries it.
        body = [{"address": "00c0ffee", "instruction": "MOV EBX,ECX"},
                {"address": "00c0fff0", "instruction": "MOV EAX,dword ptr [EBX + 0x18]"},
                {"address": "00c0fff3", "instruction": "RET"}]
        report = self.build(_span(NO_FIELD_SOURCE),
                            _machine_pack(body, receiver={"reason": "ecx_reassigned_before_deref"}),
                            edges=OUT)
        self.assertEqual(self.fields(report)["status"], "NOT_AVAILABLE")
        self.assertTrue(V._any_field_access([item["instruction"] for item in body]))


class SourceDeclarationRefutesTheArm(FieldsAbsenceFixture):
    """A declared offset is the old arm's business, and it keeps it."""

    def test_a_declared_displacement_never_reaches_the_arm(self):
        # The source asserts an offset nothing grounds. The arm fires only on a
        # span that declares none, so this is still the ungrounded-declaration
        # review item -- and it is the aggregate, not the arm, that decides how
        # disqualifying that is.
        report = self.build(_span(DECLARED_SOURCE),
                            _machine_pack(ADJUSTOR_BODY, receiver={"present": False}), edges=OUT)
        fields = self.fields(report)
        self.assertEqual(fields["status"], "WARN", fields["detail"])
        self.assertIn("no machine-derived struct layout exists to corroborate", fields["detail"])
        self.assertIn("0x40", fields["detail"])
        self.assertNotIn(NO_FIELD_ACCESS, fields["detail"])

    def test_a_named_field_never_reaches_the_arm(self):
        report = self.build(_span(NAMED_FIELD_SOURCE),
                            _machine_pack(ADJUSTOR_BODY, receiver={"present": False}), edges=OUT)
        fields = self.fields(report)
        self.assertEqual(fields["status"], "WARN", fields["detail"])
        self.assertNotIn(NO_FIELD_ACCESS, fields["detail"])

    def test_a_type_name_and_a_method_call_are_not_declarations(self):
        # Neither is a physical claim, so neither keeps the arm out: a source that
        # only names a type has nothing declared to ground. Held here because it is
        # the other way a span can look like it claims a layout without doing so.
        for source in ("  Matrix3 value;\n  return 0;",
                       "  return ports->query_00abcde1();"):
            report = self.build(_span(source),
                                _machine_pack(ADJUSTOR_BODY, receiver={"present": False}), edges=OUT)
            self.assertEqual(self.fields(report)["status"], "PASS", source)


class KnownReceiverIsUnchanged(FieldsAbsenceFixture):
    """The regression guard: a known receiver register keeps the old arms.

    The new path is strictly additional. Where the record names a register, the
    detail is the one the existing arms have always produced, word for word, and
    the new arm's own wording appears nowhere -- asserted as exact equality
    rather than as a substring so an edit to either string fails here.
    """

    def test_a_bare_receiver_read_is_offset_zero_and_not_an_absence(self):
        # The old arm read this body as an *evidenced absence*: "names no
        # displacement through ECX, which is evidence that the body addresses no
        # receiver field". That conclusion is false and the machine says so --
        # ``MOV EAX,dword ptr [ECX]`` is a load of the word at offset zero, so the
        # body does address a receiver field. The verdict was right (nothing the
        # source asserts is ungrounded) but the sentence claimed more than the
        # listing supports, and 16 corpus targets held that same false absence
        # claim. Pinned by exact equality, and the false claim is asserted gone.
        body = [{"address": "00c0ffee", "instruction": "MOV EAX,dword ptr [ECX]"},
                {"address": "00c0fff1", "instruction": "RET"}]
        report = self.build(_span(NO_FIELD_SOURCE),
                            _machine_pack(body, receiver={"register": "ECX", "offsets": ()}),
                            edges=OUT)
        fields = self.fields(report)
        self.assertEqual(fields["status"], "PASS", fields["detail"])
        self.assertIn("reaches 1 receiver displacement(s) through ECX (0x0)", fields["detail"])
        self.assertIn("as proven (0x0)", fields["detail"])
        # The register is known, so this is still the receiver-relative arm and not
        # the register-agnostic one: neither of that arm's own phrases may appear.
        self.assertNotIn(NO_FIELD_ACCESS, fields["detail"])
        self.assertNotIn(UNCLAIMED, fields["detail"])
        # And the false absence statement is gone in both of its halves.
        self.assertNotIn("names no displacement through ECX", fields["detail"])
        self.assertNotIn("which is evidence that the body addresses no receiver field",
                         fields["detail"])

    def test_an_aliased_receiver_read_is_attributed_to_the_receiver(self):
        # The same arm with a body that copied its receiver before reading through
        # the copy. The old wording said the listing "names no displacement through
        # ECX" and then hedged the record's own 0x18 as "observed through a
        # register alias rather than through that register's own operands, so the
        # scan is the narrower of the two witnesses here". The scan is not narrower
        # -- it now follows the copy -- so the hedge is replaced by the attribution
        # the machine supports, and the record's ``bounds_only`` flag is reported as
        # what it is: the record's own statement that its enumeration is open.
        body = [{"address": "00c0ffee", "instruction": "MOV EBX,ECX"},
                {"address": "00c0fff0", "instruction": "MOV EAX,dword ptr [EBX + 0x18]"},
                {"address": "00c0fff3", "instruction": "RET"}]
        report = self.build(_span(NO_FIELD_SOURCE),
                            _machine_pack(body, receiver={"register": "ECX", "offsets": (0x18,)}),
                            edges=OUT)
        fields = self.fields(report)
        self.assertEqual(fields["status"], "PASS", fields["detail"])
        self.assertIn("reaches 1 receiver displacement(s) through ECX (0x18)", fields["detail"])
        self.assertIn("read alias-aware over receiver register ECX", fields["detail"])
        self.assertIn("as proven (0x18)", fields["detail"])
        self.assertNotIn("names no displacement through ECX", fields["detail"])
        self.assertNotIn("so the scan is the narrower of the two witnesses here",
                         fields["detail"])

    def test_the_grounded_wording_for_a_known_register_is_unchanged(self):
        body = [{"address": "00c0ffee", "instruction": "MOV EAX,dword ptr [ECX + 0x14]"},
                {"address": "00c0fff2", "instruction": "RET"}]
        report = self.build(_span(NO_FIELD_SOURCE),
                            _machine_pack(body, receiver={"register": "ECX", "offsets": (0, 4, 0x14)}),
                            edges=OUT)
        fields = self.fields(report)
        self.assertEqual(fields["status"], "PASS", fields["detail"])
        self.assertEqual(fields["detail"],
                         "the 0 displacement(s) the source span declares (none) and the 1 the "
                         "complete 2-instruction listing names through ECX (0x14) are all within "
                         "the machine-derived receiver bounds (0x0, 0x4, 0x14), so the offsets are "
                         "grounded within the machine-derived receiver bounds; the record states "
                         "where the body was seen reaching and not which member is which, so it "
                         "identifies no field by name")
        self.assertNotIn(UNCLAIMED, fields["detail"])

    def test_the_failure_and_warning_wording_for_a_known_register_is_unchanged(self):
        # The two non-PASS arms, held the same way: a known register routes here and
        # the new arm is nowhere near them.
        report = self.build(_span(NAMED_FIELD_SOURCE),
                            _machine_pack([{"address": "00c0ffee", "instruction": "RET"}],
                                          receiver={"register": "ECX", "offsets": (0,)}),
                            edges=OUT)
        fields = self.fields(report)
        self.assertEqual(fields["status"], "WARN", fields["detail"])
        self.assertIn("not corroborated", fields["detail"])
        self.assertNotIn(NO_FIELD_ACCESS, fields["detail"])

    def test_an_enumerating_record_still_refutes_a_declared_member(self):
        body = [{"address": "00c0ffee", "instruction": "MOV EAX,dword ptr [ECX]"},
                {"address": "00c0fff1", "instruction": "RET"}]
        report = self.build(_span(DECLARED_SOURCE),
                            _machine_pack(body, receiver={"register": "ECX", "offsets": (0,),
                                                          "bounds_only": False}),
                            edges=OUT)
        fields = self.fields(report)
        self.assertEqual(fields["status"], "FAIL", fields["detail"])
        # The refutation still stands, and it now names the second witness: the
        # declared offset appears nowhere in the complete listing under any base
        # register, *and* an enumerating record (bounds_only false) excludes it.
        self.assertIn("appear nowhere in the complete", fields["detail"])
        self.assertIn("is an enumeration (bounds_only is false) that does not contain them",
                      fields["detail"])


if __name__ == "__main__":
    unittest.main()
