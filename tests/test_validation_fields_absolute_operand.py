"""FIELDS/OFFSETS: a *segment-absolute* operand is not a receiver field.

The receiver-agnostic absence arm added by
``test_validation_fields_absence`` passes a body whose complete, fully parsed
listing "names no memory operand through any register at all". It asks that
question through :func:`_any_field_access`, which is deliberately the widest
possible question: a hit is *any* bracketed operand, because over-reporting
costs a pass and under-reporting would clear a body that does address a field.

That conservatism is right for a *register-relative* operand, and it is wrong
for a **segment-absolute** one. Ghidra spells an absolute read
``MOV EAX,[0x0167ead8]``: it is bracketed, so ``_any_field_access`` reports a
field access, but there is no register in it and no displacement under one. It
addresses a fixed address. It cannot be a receiver field access, because a
receiver is only reachable through a register.

Six committed targets are exactly this shape -- a two-instruction global-slot
accessor, ``MOV EAX,[<slot>]`` / ``RET``, on the Simulator root table at
0x0167eac0:

    0x00b3d260  MOV EAX,[0x0167ead8] ; RET
    0x00b3d310  MOV EAX,[0x0167eae8] ; RET
    0x00b3d380  MOV EAX,[0x0167eb04] ; RET
    0x00b3d390  MOV EAX,[0x0167eb08] ; RET
    0x00b3d3d0  MOV EAX,[0x0167eb20] ; RET
    0x00b3d470  MOV EAX,[0x0167eb18] ; RET
    0x00d38840  MOV EAX,[0x0169e294] ; RET

and every one of them fell to ``NOT_AVAILABLE`` on this dimension for that
reason -- an absence of evidence that is disqualifying for a reconstruction with
nothing wrong with it.

So this file holds a third absence arm, narrower still than the second: the
listing addresses memory, but **every** operand it addresses is absolute, so the
body performs no *register-relative* access and therefore no receiver-relative
one either. What it must never become is a claim that the address is not a
global -- that is GLOBALS' dimension and this one says nothing about it.

The predicate is deliberately fail-closed in the same direction as its
sibling: an operand it cannot classify as absolute is treated as
register-relative, so an unrecognised form costs the pass rather than
manufacturing one. Every shape below is a way the arm could be wrong, asserted
so that it cannot be.
"""

import unittest

from tools.reconstruction_tooling import validate as V

from tests.test_validation_fields_absence import (  # noqa: F401
    BARE_DEREF_BODY,
    CONSTANT_STUB_BODY,
    DISPLACED_BODY,
    ADDRESS_TAKEN_BODY,
    STRING_MOVE_BODY,
    FieldsAbsenceFixture,
    _machine_pack,
    _span,
    NO_FIELD_SOURCE,
    OUT,
)

# The corpus shapes above, reproduced instruction for instruction. Each is a
# segment-absolute read: a bracket holding nothing but a literal.
ABSOLUTE_SLOT_BODY = [{"address": "00c0ffee", "instruction": "MOV EAX,[0x0167ead8]"},
                      {"address": "00c0fff1", "instruction": "RET"}]
# Ghidra also spells the same read with an explicit segment override, and with a
# width-qualified pointer type. Both are absolute and must be classified as such.
ABSOLUTE_SEGMENT_BODY = [{"address": "00c0ffee", "instruction": "MOV EAX,ds:[0x0167ead8]"},
                         {"address": "00c0fff1", "instruction": "RET"}]
ABSOLUTE_TYPED_BODY = [{"address": "00c0ffee", "instruction": "MOV EAX,dword ptr [0x0167ead8]"},
                       {"address": "00c0fff1", "instruction": "RET"}]
# An absolute *store*. Same class of operand, and it is still not a receiver
# field; the point of the arm is the operand's shape, not its access mode.
ABSOLUTE_STORE_BODY = [{"address": "00c0ffee", "instruction": "MOV dword ptr [0x0167ead8],EAX"},
                       {"address": "00c0fff1", "instruction": "RET"}]
# Two absolutes in one body, so the arm is not resting on a single instruction.
ABSOLUTE_PAIR_BODY = [{"address": "00c0ffee", "instruction": "MOV EAX,[0x0167ead8]"},
                      {"address": "00c0fff1", "instruction": "MOV ECX,[0x0167eae8]"},
                      {"address": "00c0fff2", "instruction": "RET"}]


class AbsoluteOperandClassification(unittest.TestCase):
    """:func:`_all_operands_absolute` -- the predicate, on its own terms."""

    def test_an_absolute_read_is_absolute(self):
        for body in (ABSOLUTE_SLOT_BODY, ABSOLUTE_SEGMENT_BODY, ABSOLUTE_TYPED_BODY,
                     ABSOLUTE_STORE_BODY, ABSOLUTE_PAIR_BODY):
            self.assertTrue(
                V._all_operands_absolute([item["instruction"] for item in body]), body)

    def test_a_register_relative_operand_is_not_absolute(self):
        """Every shape that addresses an object through a register.

        The bare ``[ECX]`` is here for the same reason its sibling test carries
        it: a load of the word at offset zero is the same field claim as a load
        at ``0x80``, so a displacement-based test would clear it.
        """
        for body in (DISPLACED_BODY, BARE_DEREF_BODY, ADDRESS_TAKEN_BODY):
            self.assertFalse(
                V._all_operands_absolute([item["instruction"] for item in body]), body)

    def test_a_scaled_index_is_not_absolute(self):
        # ``JMP dword ptr [EAX*0x4 + 0x5dd840]``: a jump table. The literal is
        # there and the operand is not absolute, which is exactly the case a
        # "contains a hex literal" test would get wrong.
        body = [{"address": "00c0ffee", "instruction": "JMP dword ptr [EAX*0x4 + 0x5dd840]"}]
        self.assertFalse(V._all_operands_absolute([item["instruction"] for item in body]))

    def test_a_body_with_no_operand_at_all_is_not_an_absolute_body(self):
        # The second arm's case, and it must stay that arm's case. Reporting True
        # here would let the narrower arm take over a body it has nothing new to
        # say about, and the detail string would then describe an absolute read
        # that does not exist.
        for body in (CONSTANT_STUB_BODY,):
            self.assertFalse(
                V._all_operands_absolute([item["instruction"] for item in body]), body)

    def test_an_empty_listing_is_never_absolute(self):
        # Vacuous truth is the failure mode of an ``all()`` over an empty
        # sequence, and it is exactly the direction this must not fail in.
        self.assertFalse(V._all_operands_absolute([]))
        self.assertFalse(V._all_operands_absolute(None))

    def test_an_unclassifiable_operand_counts_as_register_relative(self):
        """The fail-closed direction, asserted directly.

        A Ghidra placeholder (``[...]`` alone, an indirect marker, a symbolic
        name) is not something this predicate can prove absolute. Treating it as
        absolute would manufacture a pass from a form it does not understand, so
        it is treated as the unsafe direction instead.
        """
        for text in ("MOV EAX,[...]",
                     "MOV EAX,[indirect]",
                     "MOV EAX,[someGlobal]",
                     "MOV EAX,[base + 0x10]",
                     "MOV EAX,[ECX]",
                     "MOV EAX,ds:0x1234"):
            self.assertFalse(V._all_operands_absolute([text]), text)

    def test_an_implicit_memory_operand_is_not_an_absolute_body(self):
        # ``REP MOVSD`` has no bracket to classify at all. A body containing one
        # is doing memory traffic whose target this predicate has never seen.
        self.assertFalse(V._all_operands_absolute(["REP MOVSD", "RET"]))

    def test_one_register_operand_poisons_an_otherwise_absolute_body(self):
        # The ``all()`` must be over operands, not over instructions: a body that
        # is mostly absolute but touches a register once is not an absolute body.
        body = [{"instruction": "MOV EAX,[0x0167ead8]"},
                {"instruction": "MOV ECX,dword ptr [ECX + 0x80]"},
                {"instruction": "RET"}]
        self.assertFalse(V._all_operands_absolute([b["instruction"] for b in body]))


class AbsoluteOperandArm(FieldsAbsenceFixture):
    """The arm itself, over a real repository built by the real index builder."""

    def fields_for(self, body, receiver=None, source=None, **kwargs):
        report = self.build(source or _span(NO_FIELD_SOURCE),
                            _machine_pack(body, receiver=receiver
                                          if receiver is not None
                                          else {"reason": "ecx_read_without_deref"},
                                          **kwargs),
                            edges=OUT)
        return self.fields(report)

    def test_a_global_slot_accessor_now_passes(self):
        # The case the arm exists for, instruction for instruction from
        # 0x00b3d260. Before it this was NOT_AVAILABLE on a dimension where the
        # reconstruction had nothing wrong with it.
        fields = self.fields_for(ABSOLUTE_SLOT_BODY)
        self.assertEqual(fields["status"], "PASS", fields["detail"])
        self.assertEqual(fields["coverage"], "complete")
        self.assertIn(V.INDEX_REL, fields["evidence"])

    def test_the_detail_states_what_is_and_is_not_claimed(self):
        detail = self.fields_for(ABSOLUTE_SLOT_BODY)["detail"]
        # The claim the arm makes: no *register-relative* access, hence no
        # receiver field. Spelled in both halves so neither can be read alone.
        self.assertIn("register-relative", detail)
        self.assertIn("absolute", detail)
        # And what it must never claim. This dimension says nothing about whether
        # the address is a global -- that is GLOBALS' claim, on its own evidence.
        for phrase in ("no global", "touches no global", "is not a global",
                       "layout confirmed", "layout established", "no fields",
                       "receiver confirmed", "identifies no field"):
            self.assertNotIn(phrase, detail)

    def test_a_segment_override_and_a_typed_absolute_both_pass(self):
        for body in (ABSOLUTE_SEGMENT_BODY, ABSOLUTE_TYPED_BODY, ABSOLUTE_STORE_BODY,
                     ABSOLUTE_PAIR_BODY):
            self.assertEqual(self.fields_for(body)["status"], "PASS", body)

    def test_every_register_relative_shape_still_falls_through(self):
        """The regression guard in the direction that matters.

        These four are exactly the bodies ``test_validation_fields_absence``
        holds at NOT_AVAILABLE. The new arm must not reach any of them, or it
        would clear a body that does address a receiver field.
        """
        for body in (DISPLACED_BODY, BARE_DEREF_BODY, ADDRESS_TAKEN_BODY,
                     STRING_MOVE_BODY):
            fields = self.fields_for(body)
            self.assertEqual(fields["status"], "NOT_AVAILABLE", (body, fields["detail"]))
            self.assertNotIn("register-relative", fields["detail"])

    def test_the_guard_conditions_still_hold(self):
        """Every guard the sibling arm has, restated for this one.

        An absolute operand is not a licence to read a truncated listing, an
        unparsed body, or a source that declares its own offset -- and a missing
        parse record is not a record of zero.
        """
        truncated = self.fields_for(ABSOLUTE_SLOT_BODY, truncated_listing=True)
        self.assertEqual(truncated["status"], "NOT_AVAILABLE", truncated["detail"])
        self.assertNotIn("register-relative", truncated["detail"])

        for parse in ({"declared_count": 2, "degraded": True, "unparsed": 0},
                      {"declared_count": 2, "degraded": False, "unparsed": 1}):
            fields = self.fields_for(ABSOLUTE_SLOT_BODY, parse=parse)
            self.assertEqual(fields["status"], "NOT_AVAILABLE", parse)
            self.assertNotIn("register-relative", fields["detail"])

        dropped = self.fields_for(ABSOLUTE_SLOT_BODY, drop=("parse",))
        self.assertEqual(dropped["status"], "NOT_AVAILABLE", dropped["detail"])

    def test_a_source_that_declares_an_offset_does_not_reach_the_arm(self):
        # The declared arm sits above this one and is a WARN, not a PASS, so a
        # reconstruction that states its own offset must never be cleared by a
        # listing that happens to read memory absolutely.
        #
        # The source used here is a *receiver-relative* offset, because that is
        # what `_field_declarations` recognises as a field claim: it collects
        # `+ 0x40` displacements, `->field` member accesses and `offsetof`, and
        # it deliberately does not collect a bare absolute address. That is not
        # an oversight to route around -- `*(int *)(0x0167ead8)` names a fixed
        # address, which is a GLOBALS claim on its own evidence, not a field
        # offset, and reading it as a field would invent a layout claim the
        # source never makes.
        fields = self.fields_for(ABSOLUTE_SLOT_BODY,
                                 source=_span("  return *(int *)(this + 0x40);"))
        self.assertEqual(fields["status"], "WARN", fields["detail"])
        self.assertNotIn("register-relative", fields["detail"])
        # The same for a named member and for `offsetof`.
        for body in ("  return state->field;", "  return offsetof(T, m);"):
            fields = self.fields_for(ABSOLUTE_SLOT_BODY, source=_span(body))
            self.assertEqual(fields["status"], "WARN", (body, fields["detail"]))

    def test_a_source_naming_an_absolute_address_is_not_a_field_declaration(self):
        """The boundary this arm sits on, asserted from the detector's side.

        `_field_declarations` is the shared definition of "the source span
        declares a field offset", and the ``declared`` arm -- and therefore this
        one -- both key off it. It collects relative displacements, member
        accesses and `offsetof`, and not a bare absolute address. Pinning that
        here is what keeps the new arm from being widened later by someone who
        reads an absolute operand as an offset.
        """
        self.assertEqual(sorted(V._field_declarations("  return *(int *)(0x0167ead8);")), [])
        self.assertEqual(sorted(V._field_declarations("  return *(int *)(this + 0x40);")),
                         ["displacement 0x40"])
        self.assertEqual(sorted(V._field_declarations("  return state->field;")),
                         ["field field"])

    def test_the_arm_is_not_reachable_when_the_record_names_a_receiver(self):
        # With a register named, the pre-existing arms own the dimension. The new
        # path must be strictly additional: it may not change a verdict the
        # older, better-informed arms already reach.
        fields = self.fields_for(ABSOLUTE_SLOT_BODY,
                                 receiver={"register": "ECX", "offsets": []})
        self.assertNotEqual(fields["status"], "NOT_AVAILABLE", fields["detail"])
        self.assertNotIn("register-relative", fields["detail"])


if __name__ == "__main__":
    unittest.main()