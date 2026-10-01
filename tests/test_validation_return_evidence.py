"""The machine-derived return evidence record, and what it is allowed to conclude.

``validate`` judges RETURN SEMANTICS from one field: a canonical
``return_type``/``return_semantics`` string in either ABI source, compared to the
source's declared return type as a string. Where no such field exists the
dimension reads ``NOT_AVAILABLE``, which is disqualifying for a static PASS. That
is the shape this module was written for, and it is why the tests below spend
most of their assertions on the *negative* direction: the evidence it reads is a
complete machine listing plus a parse record, and the only thing worse than
failing to adjudicate a target is adjudicating one on a fragment of its body.

Three lines are held, in this order:

* a provable machine state over a complete, fully-parsed body reaches a verdict;
* every way the evidence can be incomplete -- truncated, empty, unparsed,
  degraded, or a count that disagrees with the listing -- reaches no state at
  all, and no state is reachable by patching ``classify`` past that gate;
* where the machine reads a value but cannot bound it (``UNCLASSIFIED``), or
  where a hidden pointer is returned (``SRET``), the dimension says which state
  it is in and stops. Neither passes, and neither fails the reconstruction.

The last class is measured against the live corpus at the bottom of the file,
over every committed evidence pack, and is what keeps the module from being wrong
in a way no unit test would notice: a rule that only ever adds verdicts looks fine
in isolation and quietly refutes correct reconstructions in bulk.
"""

import json
import unittest
from pathlib import Path

from tools.reconstruction_tooling import evidence_returns as R
from tools.reconstruction_tooling import validate as V
from tools.reconstruction_tooling.evidence import _index
from tools.reconstruction_tooling.models import ROOT as REPO_ROOT
from tools.reconstruction_tooling.models import load_json

TARGET = "0x00c0ffee"


def _listing(*rows):
    """A listing as ``(addresses, texts)``. Addresses are explicit, because the
    branch targets in the two-return bodies have to resolve into the listing for
    the paths to exist at all -- a target that resolves to nothing is one path,
    not two, and the test would quietly stop testing what it claims to.
    """
    pairs = [row if isinstance(row, tuple) else (row,) for row in rows]
    return ([address for address, _ in pairs], [text for _, text in pairs])


# A body that returns a value the machine can size: the last thing written to EAX
# before the RET is a one-byte move, and nothing between it and the RET touches
# EAX. ``App::PropertyList::Write`` (0x006a1540) has exactly this shape, and it is
# the one committed target whose return evidence this module can adjudicate.
BYTE_RETURN = _listing(("0x00c0ffee", "PUSH EBP"), ("0x00c0ffef", "MOV EBP,ESP"),
                       ("0x00c0fff1", "MOV AL,BL"), ("0x00c0fff3", "POP EBX"),
                       ("0x00c0fff4", "RET"))
# The same body with a four-byte move, which is the other shape MSVC emits for a
# scalar return: ``MOV EAX,dword ptr [X]``.
WORD_RETURN = _listing(("0x00c0ffee", "PUSH EBP"), ("0x00c0ffef", "MOV EBP,ESP"),
                       ("0x00c0fff1", "MOV EAX,dword ptr [EBX + 0x18]"),
                       ("0x00c0fff7", "RET"))
# The last value-producing operation is a call. On x86-32 whether the caller may
# read EAX after a call is decided by the callee's own signature, which this
# listing cannot show, so the width is not statically determinable. 0x006a14d0 has
# this shape (``... CALL EDX | POP EDI | POP ESI | RET 0x4``) and is the case this
# module is required *not* to resolve.
CALL_RETURN = _listing(("0x00c0ffee", "PUSH EBP"), ("0x00c0ffef", "MOV EBP,ESP"),
                       ("0x00c0fff1", "MOV EAX,0x1"), ("0x00c0fff3", "CALL 0x00abcde1"),
                       ("0x00c0fff8", "RET"))
# A body the record names EAX for and that never writes it: the two-witness void
# claim. The store and the pop are decoys -- one reads the register, the other
# names a different one.
UNWRITTEN_REGISTER = _listing(("0x00c0ffee", "PUSH EBP"), ("0x00c0ffef", "MOV EBP,ESP"),
                              ("0x00c0fff1", "MOV dword ptr [EBX + 0x4],0x1"),
                              ("0x00c0fff7", "POP EBP"), ("0x00c0fff9", "RET"))
# Two returns, reached with different widths. The intersection over the paths is
# not a single width, so no width is determinable -- the shape a linear "last
# instruction before the RET" scan would have resolved by picking one of them.
TWO_WIDTHS = _listing(("0x00c0ffee", "PUSH EBP"), ("0x00c0ffef", "MOV EBP,ESP"),
                      ("0x00c0fff1", "TEST EAX,EAX"), ("0x00c0fff3", "JZ 0x00c0fff9"),
                      ("0x00c0fff5", "MOV EAX,dword ptr [EBX]"),
                      ("0x00c0fff8", "JMP 0x00c0fffb"),
                      ("0x00c0fff9", "MOV AL,0x1"), ("0x00c0fffb", "RET"))
# The same two paths, both one byte. A width that holds on *every* path is a
# width, which is what the two-width case above is being contrasted against.
TWO_EXITS_ONE_WIDTH = _listing(("0x00c0ffee", "PUSH EBP"), ("0x00c0ffef", "MOV EBP,ESP"),
                                ("0x00c0fff1", "TEST EAX,EAX"), ("0x00c0fff3", "JZ 0x00c0fff9"),
                                ("0x00c0fff5", "MOV AL,0x1"), ("0x00c0fff8", "JMP 0x00c0fffb"),
                                ("0x00c0fff9", "MOV AL,0x2"), ("0x00c0fffb", "RET"))


def _parse(count, degraded=False, unparsed=0):
    return {"declared_count": count, "degraded": degraded, "unparsed": unparsed,
            "layout": "json_instruction_list"}


def _abi(register="EAX", **extra):
    abi = {"calling_convention": "__thiscall", "return_register": register, "ret_form": "RET 0x4"}
    abi.update(extra)
    return abi


def _state(listing, register="EAX", parse=None, abi=None, sret=None):
    """``classify`` over a synthetic listing, with the guard satisfied by default."""
    return R.classify(abi_sources=[abi if abi is not None else _abi(register)], listing=listing,
                      parse=parse if parse is not None else _parse(len(listing[1])), sret=sret)


def _verdict(listing, declared="void", register="EAX", parse=None, abi=None, sret=None,
             truncated=False):
    """``decide`` over a synthetic listing, called with the wiring block's own arguments."""
    envelope = dict(abi if abi is not None else _abi(register))
    envelope["parse"] = parse if parse is not None else _parse(len(listing[1]))
    if sret is not None:
        envelope["sret"] = sret
    return R.decide(record={"va": TARGET, "abi": {}}, categories={"abi": {"value": envelope}},
                    abi_outer=envelope, abi_inner={}, listing=None if truncated else listing,
                    scoped_text="", target_span={"name": "reconstruct_me_00c0ffee",
                                                "return_type": declared, "text": ""},
                    source_path=Path("src/pkg/reconstruct.cpp"))


class StateVocabulary(unittest.TestCase):

    def test_the_vocabulary_is_the_one_the_states_are_drawn_from(self):
        self.assertEqual(R.STATES, ("VOID_PROVEN", "WIDTH", "SRET_PROVEN", "SRET_SUSPECTED",
                                    "UNCLASSIFIED", "NOT_AVAILABLE"))

    def test_every_state_the_classifier_emits_is_in_the_vocabulary(self):
        seen = set()
        for listing in (BYTE_RETURN, WORD_RETURN, CALL_RETURN, TWO_WIDTHS,
                        TWO_EXITS_ONE_WIDTH, UNWRITTEN_REGISTER):
            state = _state(listing)
            self.assertIn(state["kind"], R.STATES, state["state"])
            seen.add(state["state"])
        # A width state names its instance; the kind is what a caller matches on.
        self.assertIn("WIDTH_1_IN_EAX", seen)
        self.assertIn("WIDTH_4_IN_EAX", seen)
        self.assertEqual(R.width_state(1, "EAX"), "WIDTH_1_IN_EAX")


class MachineStates(unittest.TestCase):

    def test_a_record_naming_no_return_register_is_a_proven_void(self):
        state = _state(BYTE_RETURN, abi=_abi("none"))
        self.assertEqual(state["state"], "VOID_PROVEN")
        self.assertTrue(state["provable"])
        self.assertIn("claims no return register", state["reason"])

    def test_a_negated_register_field_is_a_denial_not_a_carrier(self):
        # The index projection writes this field as prose, and "EAX is not assigned
        # a defined result by the target body" names a register while denying that
        # it carries one. Reading the leading token as a carrier would turn a
        # negative record into a width claim over a body the record says returns
        # nothing.
        state = _state(BYTE_RETURN, abi=_abi("EAX is not assigned a defined result by the target body"))
        self.assertEqual(state["state"], "VOID_PROVEN")
        self.assertIn("claims no return register", state["reason"])

    def test_a_one_byte_write_is_a_one_byte_width(self):
        state = _state(BYTE_RETURN)
        self.assertEqual(state["state"], "WIDTH_1_IN_EAX")
        self.assertEqual(state["width"], 1)
        self.assertEqual(state["register"], "EAX")
        self.assertTrue(state["provable"])

    def test_a_four_byte_write_is_a_four_byte_width(self):
        state = _state(WORD_RETURN)
        self.assertEqual(state["state"], "WIDTH_4_IN_EAX")
        self.assertEqual(state["width"], 4)

    def test_a_sub_register_field_is_widened_to_its_parent(self):
        # A record that spells the return register AL states the width in its own
        # spelling; the state name must not depend on which layer said it.
        self.assertEqual(_state(BYTE_RETURN, abi=_abi("AL"))["state"], "WIDTH_1_IN_EAX")

    def test_a_call_as_the_last_value_producer_is_unclassified(self):
        state = _state(CALL_RETURN)
        self.assertEqual(state["state"], "UNCLASSIFIED")
        self.assertIn("cannot bound", state["reason"])
        self.assertFalse(state["provable"])

    def test_two_returns_with_different_widths_claim_no_width(self):
        state = _state(TWO_WIDTHS)
        self.assertEqual(state["state"], "UNCLASSIFIED")
        self.assertFalse(state["provable"])

    def test_two_paths_that_agree_on_one_width_do_claim_it(self):
        # The contrast that makes the case above meaningful: the analysis is not
        # refusing anything with two paths, it is refusing two *different* widths.
        state = _state(TWO_EXITS_ONE_WIDTH)
        self.assertEqual(state["state"], "WIDTH_1_IN_EAX")

    def test_a_register_the_body_never_writes_is_a_two_witness_void(self):
        state = _state(UNWRITTEN_REGISTER)
        self.assertEqual(state["state"], "VOID_PROVEN")
        self.assertIn("no path", state["reason"])

    def test_a_memory_operand_based_on_the_register_is_not_a_write(self):
        # ``MOV dword ptr [EBX + 0x4],0x1`` writes memory and touches no register
        # as a destination; a detector that matched a register anywhere in the
        # operand would read this void as a four-byte return.
        self.assertEqual(_state(UNWRITTEN_REGISTER)["state"], "VOID_PROVEN")

    def test_an_x87_return_register_is_unclassified_with_its_reason(self):
        state = _state(WORD_RETURN, abi=_abi("ST0"))
        self.assertEqual(state["state"], "UNCLASSIFIED")
        self.assertIn("float or double", state["reason"])

    def test_an_sse_return_register_is_unclassified_with_its_reason(self):
        state = _state(WORD_RETURN, abi=_abi("XMM0"))
        self.assertEqual(state["state"], "UNCLASSIFIED")
        self.assertIn("SSE register", state["reason"])

    def test_a_record_that_contradicts_itself_is_unclassified(self):
        # 0x006a2a80's shape: ``return_register`` says none while the envelope's
        # nested ``return`` sub-record says EAX. Picking either would be picking
        # whichever field this module read first.
        abi = dict(_abi("none"), **{"return": {"register": "EAX", "register_class": "integral",
                                               "confidence": "INFERRED"}})
        state = _state(UNWRITTEN_REGISTER, abi=abi)
        self.assertEqual(state["state"], "UNCLASSIFIED")
        self.assertIn("contested", state["reason"])

    def test_a_hidden_pointer_return_is_suspected_before_any_width(self):
        state = _state(BYTE_RETURN, sret={"present": None, "ambiguity": "sret_vs_out_param",
                                          "candidates": ["hidden_sret", "out_parameter"], "slot": 4})
        self.assertEqual(state["state"], "SRET_SUSPECTED")
        self.assertFalse(state["provable"])

    def test_a_proven_hidden_pointer_return_needs_the_record_to_agree_with_itself(self):
        proven = {"present": True, "eax_holds_slot0_at_ret": True, "slot": 4}
        self.assertEqual(_state(BYTE_RETURN, sret=proven)["state"], "SRET_PROVEN")
        # The record asserting the hidden pointer while its own flag says the
        # return register does not hold the slot is not a proof of anything.
        self.assertEqual(_state(BYTE_RETURN, sret=dict(proven, eax_holds_slot0_at_ret=False))["state"],
                         "SRET_SUSPECTED")

    def test_a_bulk_write_through_the_return_is_an_sret_hypothesis(self):
        abi = dict(_abi(), **{"return": {"register": "EAX", "register_class": "aggregate_unknown",
                                         "aggregate_evidence": {"bulk_write": True},
                                         "confidence": "INFERRED"}})
        self.assertEqual(_state(BYTE_RETURN, abi=abi)["state"], "SRET_SUSPECTED")

    def test_no_return_field_at_all_is_not_a_record_of_void(self):
        state = _state(BYTE_RETURN, abi={"calling_convention": "__thiscall", "ret_form": "RET"})
        self.assertEqual(state["state"], "NOT_AVAILABLE")
        self.assertIn("no ABI field records a return register", state["reason"])


class FailClosed(unittest.TestCase):
    """Every way the evidence can be incomplete reaches no state at all."""

    def _assert_no_state(self, state, reason_fragment):
        self.assertEqual(state["state"], "NOT_AVAILABLE", state["reason"])
        self.assertFalse(state["provable"])
        self.assertIn(reason_fragment, state["reason"])

    def test_a_truncated_envelope_yields_no_state(self):
        # ``validate._listing`` is what returns ``None`` for a truncated envelope,
        # so the guard sees an absence and refuses. A ``{"truncated": true}``
        # preview is a *fragment* of the body, and a body half seen is exactly
        # what a void body looks like -- which is why this is a refusal and not a
        # warning.
        self._assert_no_state(R.classify(abi_sources=[_abi()], listing=None, parse=_parse(5)),
                              "truncated")

    def test_an_empty_listing_yields_no_state(self):
        self._assert_no_state(R.classify(abi_sources=[_abi()], listing=([], []), parse=_parse(0)),
                              "empty")

    def test_a_missing_parse_record_yields_no_state(self):
        self._assert_no_state(R.classify(abi_sources=[_abi()], listing=BYTE_RETURN, parse={}),
                              "no machine parse record")

    def test_a_degraded_parse_yields_no_state(self):
        self._assert_no_state(_state(BYTE_RETURN, parse=_parse(len(BYTE_RETURN[1]), degraded=True)),
                              "degraded")

    def test_an_unparsed_instruction_yields_no_state(self):
        self._assert_no_state(_state(BYTE_RETURN, parse=_parse(len(BYTE_RETURN[1]), unparsed=2)),
                              "not parsed")

    def test_a_declared_count_that_disagrees_with_the_listing_yields_no_state(self):
        self._assert_no_state(_state(BYTE_RETURN, parse=_parse(len(BYTE_RETURN[1]) + 3)),
                              "disagree about the body")

    def test_a_non_integer_declared_count_yields_no_state(self):
        self._assert_no_state(_state(BYTE_RETURN, parse={"declared_count": "five"}),
                              "declares no instruction count")

    def test_flipping_degraded_is_the_only_thing_that_unlocks_a_state(self):
        # Each of the other two holes is closed while ``degraded`` stays flipped,
        # so one field is what unlocks it -- and what it unlocks is a width claim
        # over a whole body, not a bare name.
        broken = {"degraded": True, "unparsed": 0, "declared_count": len(BYTE_RETURN[1])}
        self._assert_no_state(_state(BYTE_RETURN, parse=broken), "degraded")
        self._assert_no_state(_state(BYTE_RETURN, parse=dict(broken, degraded=False, unparsed=1)),
                              "not parsed")
        self._assert_no_state(_state(BYTE_RETURN, parse=dict(broken, degraded=False, declared_count=99)),
                              "disagree about the body")
        self.assertEqual(_state(BYTE_RETURN, parse=dict(broken, degraded=False))["state"],
                         "WIDTH_1_IN_EAX")

    def test_a_truncated_pack_cannot_pass_even_with_classify_patched(self):
        # The guard is read twice, and the second read is made from the raw listing
        # and parse record rather than from the state. Patching ``classify`` to an
        # over-strong answer therefore buys nothing -- which is the property that
        # holds if this module is ever revised to reach for the wrong evidence.
        original = R.classify
        R.classify = lambda **kwargs: {"state": "VOID_PROVEN", "kind": "VOID_PROVEN",
                                       "provable": True, "reason": "patched"}
        try:
            self.assertIsNone(_verdict(BYTE_RETURN, declared="void", truncated=True),
                              "a truncated pack reached a verdict")
            # And the case a half-seen body actually arrives in: a listing that is
            # present but whose parse was degraded.
            self.assertIsNone(_verdict(BYTE_RETURN, declared="void",
                                       parse=_parse(len(BYTE_RETURN[1]), degraded=True)))
            self.assertIsNone(_verdict(BYTE_RETURN, declared="void",
                                       parse=_parse(len(BYTE_RETURN[1]) + 1)))
            # No source artifact either: the existing arm owns that target.
            self.assertIsNone(_verdict(BYTE_RETURN, declared="void",
                                       parse=_parse(len(BYTE_RETURN[1]), unparsed=1)))
        finally:
            R.classify = original

    def test_a_patched_width_state_cannot_pass_a_truncated_pack_either(self):
        original = R.classify
        R.classify = lambda **kwargs: {"state": R.width_state(1, "EAX"), "kind": "WIDTH",
                                       "provable": True, "width": 1, "register": "EAX",
                                       "reason": "patched"}
        try:
            self.assertIsNone(_verdict(BYTE_RETURN, declared="bool", truncated=True))
        finally:
            R.classify = original

    def test_the_guard_still_applies_once_the_patch_is_removed(self):
        self.assertEqual(_verdict(BYTE_RETURN, declared="bool")["status"], "PASS")


class Comparison(unittest.TestCase):

    def test_void_source_and_proven_void_pass(self):
        verdict = _verdict(UNWRITTEN_REGISTER, declared="void")
        self.assertEqual(verdict["status"], "PASS")
        self.assertEqual(verdict["coverage"], "complete")
        # The claim has to say where it came from, or a reader cannot tell a proof
        # from a name-shaped guess.
        self.assertIn("proven from the complete listing and the parse record", verdict["detail"])
        self.assertEqual(verdict["evidence"], [R.INDEX_REL, R.EVIDENCE_REL])

    def test_a_value_source_where_the_machine_proves_void_fails(self):
        verdict = _verdict(UNWRITTEN_REGISTER, declared="int")
        self.assertEqual(verdict["status"], "FAIL")
        self.assertIn("returns nothing", verdict["detail"])

    def test_a_width_match_passes_and_says_the_width_is_what_matched(self):
        verdict = _verdict(BYTE_RETURN, declared="bool")
        self.assertEqual(verdict["status"], "PASS")
        self.assertEqual(verdict["coverage"], "complete")
        self.assertIn("WIDTH_1_IN_EAX", verdict["detail"])
        self.assertIn("The width is corroborated by the machine", verdict["detail"])
        self.assertIn("remains a source-side choice", verdict["detail"])
        self.assertIn("is not verified here", verdict["detail"])

    def test_every_type_of_the_matching_width_passes(self):
        # bool, char and std::int8_t are different C types and only the width is
        # claimed, so none of them is a failure -- and none of them is a proof of
        # the spelling either.
        for declared in ("bool", "char", "unsigned char", "std::int8_t"):
            self.assertEqual(_verdict(BYTE_RETURN, declared=declared)["status"], "PASS", declared)

    def test_a_width_disagreement_is_a_warn_and_not_a_refutation(self):
        verdict = _verdict(BYTE_RETURN, declared="int")
        self.assertEqual(verdict["status"], "WARN")
        self.assertIn("review item rather than a refutation", verdict["detail"])
        self.assertIn("hidden-pointer", verdict["detail"])

    def test_void_where_the_machine_returns_a_width_fails(self):
        verdict = _verdict(BYTE_RETURN, declared="void")
        self.assertEqual(verdict["status"], "FAIL")
        self.assertIn("mirrored case", verdict["detail"])

    def test_a_type_of_unknown_width_is_never_matched_against_a_machine_width(self):
        # A typedef, a class, a template and an alias have no width a static read
        # can establish. Reading one as a width match would clear a reconstruction
        # returning a 64-byte struct on the strength of a one-byte register write.
        for declared in ("MyResult", "std::string", "CountType", "decltype(x)", "auto"):
            verdict = _verdict(BYTE_RETURN, declared=declared)
            self.assertEqual(verdict["status"], "NOT_AVAILABLE", declared)
            self.assertIn("cannot be computed", verdict["detail"])

    def test_a_pointer_is_four_bytes_and_is_compared_as_a_width(self):
        self.assertEqual(_verdict(WORD_RETURN, declared="void *")["status"], "PASS")
        self.assertEqual(_verdict(BYTE_RETURN, declared="char *")["status"], "WARN")

    def test_unclassified_is_not_available_even_when_the_source_says_void(self):
        verdict = _verdict(CALL_RETURN, declared="void")
        self.assertEqual(verdict["status"], "NOT_AVAILABLE")
        self.assertIn("UNCLASSIFIED", verdict["detail"])

    def test_a_proven_hidden_pointer_return_is_never_a_verdict(self):
        verdict = _verdict(BYTE_RETURN, declared="void",
                           sret={"present": True, "eax_holds_slot0_at_ret": True, "slot": 4})
        self.assertEqual(verdict["status"], "NOT_AVAILABLE")
        self.assertIn("SRET_PROVEN", verdict["detail"])

    def test_a_missing_source_artifact_defers(self):
        # The existing "no canonical source artifact" arm is more accurate about a
        # missing source than anything this module could say, so it keeps the
        # target.
        self.assertIsNone(R.decide(record={"va": TARGET, "abi": {}}, categories={},
                                   abi_outer=_abi(), abi_inner={}, listing=BYTE_RETURN,
                                   scoped_text="", target_span=None, source_path=None))

    def test_a_canonical_return_type_defers_to_the_existing_string_comparison(self):
        # 506 of 586 committed packs carry one, and their current PASS or WARN must
        # not be re-derived by a second, differently-evidenced oracle.
        self.assertIsNone(_verdict(BYTE_RETURN, declared="bool", abi=_abi("EAX", return_type="bool")))

    def test_a_canonical_return_semantic_no_longer_defers(self):
        # 0x006a2f10's shape: the derived record's ``unclassified_in_EAX``. This
        # USED to defer, and deferring is what was wrong: ``return_semantics`` is
        # a register-class classification or prose, never a C or C++ type name, so
        # the deferral handed the target to a string comparison between a
        # classification phrase and the source's declared type. The two could
        # never agree, every such target was reported as "return type differs or
        # is semantically renamed", and this module's width-based route -- which
        # FAILs a genuine void/value contradiction -- never ran at all.
        #
        # So the phrase is no longer a canonical return *type*
        # (``validate._canonical_return_type`` reads ``return_type`` only) and the
        # strict route adjudicates instead. Here it is stronger, not weaker: a
        # 5-instruction listing that writes EAX at a determinate 1-byte width
        # before its single return is a proven width, so a source declaring
        # ``void`` is a genuine contradiction and the mirrored FAIL is the right
        # answer. Declaring the width of that one byte would PASS.
        verdict = _verdict(BYTE_RETURN, declared="void",
                           abi=_abi("EAX", return_semantics="unclassified_in_EAX"))
        self.assertIsNotNone(verdict)
        self.assertEqual(verdict["status"], "FAIL")
        self.assertIn("WIDTH_1_IN_EAX", verdict["detail"])

    def test_a_prose_return_semantic_also_does_not_defer(self):
        # The persisted ABI layer renders ``return_semantics`` as prose. A prose
        # sentence is not a type either, so it does not hand the target to a
        # string comparison; the width route owns it and agrees.
        verdict = _verdict(BYTE_RETURN, declared="std::uint8_t",
                           abi=_abi("EAX",
                                    return_semantics="the low byte of EAX carries the result"))
        self.assertIsNotNone(verdict)
        self.assertEqual(verdict["status"], "PASS")

    def test_no_listing_at_all_defers(self):
        self.assertIsNone(_verdict(BYTE_RETURN, declared="void", truncated=True))


class CorpusBackCompat(unittest.TestCase):
    """The measurement, against every evidence pack committed to the repository.

    Each pack is judged twice -- once with ``decide`` live and once with it stubbed
    back to ``None``, which is the wiring's own "defer" branch -- and the two
    reports may differ in exactly one check, in exactly one direction.

    The direction is the load-bearing assertion. A new evidence route is allowed
    to make a dimension *stronger* and never weaker: ``NOT_AVAILABLE`` to
    ``PASS``, ``UNKNOWN`` to ``WARN``, ``WARN`` to ``PASS``. Anything else means
    this module has refuted a reconstruction the machine never contradicted, and on
    this corpus that would be silent -- the unit tests above would not see it,
    because a fixture is chosen to fit the rule it is testing.
    """

    PACK_GLOB = "reconstruction/evidence/*/evidence.json"
    # The validator's own severity order, restated here so "weakened" has a meaning
    # independent of the aggregate: FAIL, UNKNOWN, NOT_AVAILABLE, WARN, PASS.
    LADDER = ("FAIL", "UNKNOWN", "NOT_AVAILABLE", "WARN", "PASS")
    CHECK = "RETURN SEMANTICS"

    def _targets(self):
        return ["0x" + path.parent.name for path in sorted(REPO_ROOT.glob(self.PACK_GLOB))]

    def _judged(self, target, decide):
        """Re-judge one target with ``decide`` in place, and report the wiring's own output.

        ``decide`` is the seam the wiring block calls, so stubbing it to ``None`` is
        that block's deferral branch rather than a second implementation of the
        wiring. Which means the check the validator produced under the stub *is*
        today's behaviour, whatever the wiring does, and the check it produces with
        ``decide`` live is today's behaviour with the block's verdict merged over it
        once the block exists.
        """
        original = R.decide
        R.decide = decide
        try:
            report = V.validate(root=REPO_ROOT, va=target, write=False)
        finally:
            R.decide = original
        record = V._record(_index(REPO_ROOT), target)
        resolved = V._source(REPO_ROOT, record)
        source_path = resolved["path"] if resolved else None
        span = V._target_span(V._read_source(source_path), record)
        pack = load_json(REPO_ROOT / "reconstruction/evidence" / target[2:] / "evidence.json")
        categories = pack.get("categories") or {}
        outer, inner = V._abi_envelope(categories)
        keywords = dict(record=record, categories=categories, abi_outer=outer, abi_inner=inner,
                        listing=V._listing(categories),
                        scoped_text=span.get("text", "") if span else "",
                        target_span=span, source_path=source_path)
        return report, decide(**keywords), keywords

    def test_the_return_evidence_route_never_weakens_a_verdict(self):
        targets = self._targets()
        self.assertTrue(targets, "no evidence packs on disk to measure against")
        live, stubbed = R.decide, (lambda **keywords: None)
        changed, other_checks, states, wired = [], [], {}, 0
        for target in targets:
            _, verdict, keywords = self._judged(target, live)
            report, _, _ = self._judged(target, stubbed)
            baseline = dict(report["checks"][self.CHECK])
            # The wiring the orchestrator adds: ``decide``'s verdict merged over
            # the validator's own arm, and nothing else touched.
            wired_check = dict(baseline, **verdict) if verdict else baseline
            own = report["checks"][self.CHECK]
            # Whether the block is already in place is not this test's business, so
            # both readings are accepted: the validator's own output is either the
            # un-merged arm or the merged one, and never anything else.
            self.assertIn(own, (baseline, wired_check),
                          "%s: the validator's own RETURN SEMANTICS is neither the un-wired arm nor the "
                          "wired one" % target)
            wired += 1 if own == wired_check else 0
            state = R.classify(
                abi_sources=[keywords["record"].get("abi") or {},
                             keywords["abi_outer"], keywords["abi_inner"]],
                listing=keywords["listing"],
                parse=V._machine_record(keywords["categories"], keywords["abi_outer"],
                                        keywords["abi_inner"], "parse"),
                sret=V._machine_record(keywords["categories"], keywords["abi_outer"],
                                       keywords["abi_inner"], "sret"))
            states[state["state"]] = states.get(state["state"], 0) + 1
            for name, check in report["static"]["checks"].items():
                if name != self.CHECK and check != report["static"]["checks"][name]:
                    other_checks.append((target, name))
            if baseline["status"] != wired_check["status"]:
                changed.append((target, baseline["status"], wired_check["status"]))
        self.assertEqual(other_checks, [], "the return-evidence route reached a check other than %s"
                                              % self.CHECK)
        for target, before_status, after_status in changed:
            self.assertLessEqual(self.LADDER.index(before_status), self.LADDER.index(after_status),
                                 "the return-evidence route weakened %s (%s -> %s)"
                                 % (target, before_status, after_status))
        for target, before_status, after_status in changed:
            if after_status != "PASS":
                continue
            # A moved target has to have earned it: a listing, and a parse record
            # that consumed that listing in full.
            categories = load_json(REPO_ROOT / "reconstruction/evidence" / target[2:] / "evidence.json").get("categories") or {}
            outer, inner = V._abi_envelope(categories)
            listing = V._listing(categories)
            parse = V._machine_record(categories, outer, inner, "parse")
            self.assertIsNotNone(listing, "%s passed with no complete listing" % target)
            self.assertIsNot(parse.get("degraded"), True, "%s passed on a degraded parse" % target)
            self.assertEqual(parse.get("unparsed") or 0, 0, "%s passed with an unparsed instruction" % target)
            self.assertEqual(parse.get("declared_count"), len(listing[1]),
                             "%s passed on a parse that disagrees with the listing" % target)
        print("\nRETURN evidence back-compat: %d pack(s) measured, %d already reported by the "
              "validator itself, %d moved by the wiring: %s"
              % (len(targets), wired, len(changed), changed or "none"))
        print("RETURN evidence machine states over the corpus: %s"
              % json.dumps(dict(sorted(states.items()))))


if __name__ == "__main__":
    unittest.main()
