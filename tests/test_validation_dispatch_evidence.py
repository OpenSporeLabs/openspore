"""The positively-corroborated VIRTUAL DISPATCH verdict, held from both sides.

The dimension this module serves could only pass a body that dispatched
*nothing*: a complete listing with no indirect transfer in it, corroborated by a
dispatch record counting zero. A body that correctly performed a virtual call was
therefore always a WARN, and a WARN there read as an accounting problem when it
was in fact the absence of a positive arm. Measured over the 418 committed
reports that left PASS 72 / NOT_AVAILABLE 239 / WARN 46 / UNKNOWN 61, with every
one of those 72 passes reading "nothing there".

So the tests below hold the new arm and the old ones at once:

* a body whose complete listing shows the canonical two-level load, fully parsed
  and corroborated by an agreeing dispatch record, *passes* -- and the detail
  names each slot displacement, because the displacement is the evidence;
* every way of failing to be that body is a WARN naming the condition that
  failed: a degraded parse, an unparsed instruction, a count disagreement, a
  missing record, a site that is not a vtable slot, a source slot offset the
  machine does not show;
* the arms that already existed stay reachable, asserted as ``decide`` returning
  ``None`` for them rather than as a status, so the guarantee is structural;
* and the classification cannot be asserted by anything but the listing bytes.
  The mutation tests patch the module's own classifier -- to claim a
  ``VTABLE_SLOT`` the listing does not show, and to report the wrong number of
  sites -- and require the guard to refuse anyway.

The last class re-judges every pack on disk twice, once with ``decide`` live and
once stubbed back to ``None``, and requires that the only check whose status
moves is VIRTUAL DISPATCH, that it only ever moves toward a stronger verdict, and
that every moved target can show a complete listing, a fully-consumed parse, an
agreeing dispatch count and an all-``VTABLE_SLOT`` site set. Nothing is written:
both arms read each pack as it stands.
"""

import collections
import json
import unittest

from tools.reconstruction_tooling import evidence_dispatch as D
from tools.reconstruction_tooling import validate as V
from tools.reconstruction_tooling.models import ROOT as REPO_ROOT

# The unpatched classifier, captured at import. The mutation tests patch
# ``D.classify_sites`` and restore it; the ones that need the real behaviour to
# build their lie on top of come through here, so no test is ever comparing
# against something it just replaced.
_REAL_CLASSIFY = D.classify_sites
_REAL_DECIDE = D.decide

# -- the shapes the dimension has to tell apart ----------------------------------
# The canonical x86-32 virtual call, measured at 0x0067e6f0: the table word is
# read out of an object, then the slot word is read out of the table, then the
# transfer goes through the register holding it.
CANONICAL = ["MOV ECX,dword ptr [ESI + 0x10]",
             "MOV EAX,dword ptr [ECX]",
             "MOV EDX,dword ptr [EAX + 0x1c]",
             "CALL EDX"]
# 0x006a2ad0's loop head: the self-referential form, where the table word and the
# slot are read through the same register.
SELF_BASE = ["MOV EAX,dword ptr [EDI]",
             "MOV EDX,dword ptr [ESI]",
             "MOV EAX,dword ptr [EAX + 0x14]",
             "LEA ECX,[ESI + 0x4]",
             "CALL EAX"]
# A frame slot holding a function pointer: a real dispatch whose identity the
# listing does not establish.
FRAME_SLOT = ["PUSH EAX", "MOV ESI,dword ptr [ESP + 0x1c]", "PUSH 0x1", "CALL ESI"]
# A switch: indexed into a table of code addresses, which is not a dispatch.
JUMP_TABLE = ["JMP dword ptr [EAX*0x4 + 0x5dd840]"]


def _listing(texts):
    addresses = ["0x%08x" % (0x1000 + index * 2) for index in range(len(texts))]
    return addresses, list(texts)


def _pack(texts, *, indirect=None, declared=None, unparsed=0, degraded=False,
          drop_dispatch=False, drop_parse=False, truncated_dispatch=False,
          truncated_parse=False, on_abi_layer=False):
    """A minimal evidence pack carrying only what this dimension reads.

    ``indirect`` defaults to the number of indirect transfers the listing really
    holds, so a test that is about a *different* failure does not have to state
    the count twice and accidentally agree with itself.
    """
    if indirect is None:
        indirect = sum(1 for text in (texts or ()) if D._transfer(text)[0] is not None)
    if texts is None:
        listing_value = {"truncated": True, "preview": ["MOV EAX,dword ptr [ECX]"]}
    else:
        listing_value = {"instructions": [{"address": address, "instruction": text}
                                          for address, text in zip(*_listing(texts))]}
    count = len(texts or ())
    derived = {}
    if not drop_dispatch:
        derived["dispatch"] = ({"truncated": True, "preview": {"indirect_calls": 0}}
                               if truncated_dispatch else
                               {"call_offsets": [], "indirect_calls": indirect, "vtable_shaped_loads": 0})
    if not drop_parse:
        derived["parse"] = ({"truncated": True} if truncated_parse else
                            {"declared_count": count if declared is None else declared,
                             "degraded": degraded, "unparsed": unparsed})
    categories = {"disassembly": {"availability": "available", "value": listing_value}}
    # A pack collected before ``abi_derived`` existed carries the envelope on the
    # ``abi`` value instead, and the resolution order has to read it there.
    categories["abi" if on_abi_layer else "abi_derived"] = {"availability": "available",
                                                            "value": dict(derived)}
    return categories


def _decide(texts, scoped_text="", *, source_path="src/pkg/pkg.cpp", span=True, **pack):
    """``decide`` over a synthetic listing, with the arguments validate passes."""
    categories = _pack(texts, **pack)
    return D.decide(record={"va": "0x00001000", "vtables": [{"id": 1}, {"id": 2}]},
                    categories=categories,
                    abi_outer=categories.get("abi", {}).get("value") or {},
                    abi_inner={},
                    listing=None if texts is None else _listing(texts),
                    scoped_text=scoped_text,
                    target_span={"text": scoped_text} if span else None,
                    source_path=source_path,
                    dependencies={"vtable_reference_count": 0})


class SiteShapeTest(unittest.TestCase):
    """``classify_sites`` over synthetic listings: the shapes must be told apart."""

    def test_the_canonical_two_level_load_is_a_vtable_slot(self):
        sites = D.classify_sites(*_listing(CANONICAL))
        self.assertEqual(len(sites), 1)
        site = sites[0]
        self.assertEqual(site["shape"], "VTABLE_SLOT")
        self.assertEqual(site["slot_offset"], 0x1c)
        self.assertEqual(site["base"], "EAX")
        self.assertEqual(site["text"], "CALL EDX")
        self.assertEqual(site["address"], "0x00001006")
        self.assertIn("0x1c", site["reason"])

    def test_a_self_referential_table_word_is_still_a_vtable_slot(self):
        # ``MOV EAX,[EDI]`` then ``MOV EAX,[EAX + 0x14]``: the base register of the
        # slot load is the register the slot load itself writes, so resolving the
        # base against that same instruction would make the shape self-fulfilling.
        site = D.classify_sites(*_listing(SELF_BASE))[0]
        self.assertEqual(site["shape"], "VTABLE_SLOT")
        self.assertEqual(site["slot_offset"], 0x14)
        self.assertIn("0x00001000", site["reason"])

    def test_a_table_word_with_no_earlier_load_is_not_a_vtable_slot(self):
        # There is one memory load here and it reads the *table*, so there is no
        # two-level chain at all. This is the case a self-referential resolution
        # would get wrong, and it is why the base is resolved strictly before the
        # load that reads it.
        site = D.classify_sites(*_listing(["MOV EAX,dword ptr [EAX + 0x14]", "PUSH 0x1", "CALL EAX"]))[0]
        self.assertNotEqual(site["shape"], "VTABLE_SLOT")
        self.assertIsNone(site["slot_offset"])
        self.assertIn("no definition earlier in the listing", site["reason"])

    def test_a_load_straight_from_a_data_segment_global_is_a_function_pointer(self):
        site = D.classify_sites(*_listing(["MOV EDX,dword ptr [0x6f1a2b3c]", "PUSH 0x0", "CALL EDX"]))[0]
        self.assertEqual(site["shape"], "FUNCTION_POINTER")
        self.assertIsNone(site["slot_offset"])
        self.assertIn("no base register", site["reason"])

    def test_a_frame_slot_holding_a_function_pointer_is_a_function_pointer(self):
        site = D.classify_sites(*_listing(FRAME_SLOT))[0]
        self.assertEqual(site["shape"], "FUNCTION_POINTER")
        self.assertIn("ESP is defined by an immediate or register assignment", site["reason"])
        self.assertIn("not shown to be a table word", site["reason"])

    def test_a_table_word_under_a_base_with_no_definition_is_a_function_pointer(self):
        # The same shape with nothing at all defining the base register, which is
        # the other way the two-level chain can fail to be there.
        site = D.classify_sites(*_listing(["MOV ESI,dword ptr [ESP + 0x1c]", "CALL ESI"]))[0]
        self.assertEqual(site["shape"], "FUNCTION_POINTER")
        self.assertIn("ESP has no definition earlier in the listing", site["reason"])

    def test_a_jump_table_is_not_virtual_dispatch(self):
        site = D.classify_sites(*_listing(JUMP_TABLE))[0]
        self.assertEqual(site["shape"], "INDIRECT_NON_VTABLE")
        self.assertIsNone(site["slot_offset"])
        self.assertIn("jump table", site["reason"])

    def test_a_call_through_a_memory_operand_is_not_virtual_dispatch(self):
        # 0x01021bb0's ``CALL dword ptr [ESP + 0x30]``: a frame slot, not a slot of
        # a table, and the transfer names no register to read.
        site = D.classify_sites(*_listing(["PUSH EBX", "CALL dword ptr [ESP + 0x30]"]))[0]
        self.assertEqual(site["shape"], "INDIRECT_NON_VTABLE")

    def test_a_target_defined_by_a_preceding_call_is_unresolved(self):
        # 0x00a85790 dispatches through EDX at 0x00a85815 and then again at
        # 0x00a8581d: the second transfer goes through whatever the first returned,
        # which is a chain a walk that ignored ``CALL`` would have called a slot.
        sites = D.classify_sites(*_listing(["MOV ECX,dword ptr [ESI]",
                                            "MOV EDX,dword ptr [ECX + 0x1c]",
                                            "CALL EDX", "POP EDI", "JMP 0x00001010",
                                            "PUSH 0x0", "PUSH EAX", "CALL EDX"]))
        self.assertEqual([site["shape"] for site in sites], ["VTABLE_SLOT", "UNRESOLVED"])
        self.assertIn("preceding CALL", sites[1]["reason"])

    def test_a_target_defined_by_a_pop_is_unresolved(self):
        site = D.classify_sites(*_listing(["POP ESI", "PUSH 0x0", "CALL ESI"]))[0]
        self.assertEqual(site["shape"], "UNRESOLVED")
        self.assertIn("not a memory load", site["reason"])

    def test_a_target_defined_by_an_opaque_lea_is_unresolved(self):
        site = D.classify_sites(*_listing(["LEA EAX,[ESI + 0x4]", "PUSH EAX", "CALL EAX"]))[0]
        self.assertEqual(site["shape"], "UNRESOLVED")
        self.assertIn("LEA", site["reason"])

    def test_a_target_with_no_definition_at_all_is_unresolved(self):
        site = D.classify_sites(*_listing(["NOP", "CALL EDX"]))[0]
        self.assertEqual(site["shape"], "UNRESOLVED")
        self.assertIn("no instruction in the listing defines EDX", site["reason"])

    def test_a_string_operation_between_the_load_and_the_call_ends_the_chain(self):
        # ``MOVSD`` has no named operands, so a walk that modelled only named ones
        # would step over it and keep the chain alive across a write the machine
        # really performs.
        site = D.classify_sites(*_listing(["MOV EAX,dword ptr [EDI]", "MOVSD",
                                           "MOV EAX,dword ptr [EAX + 0x8]", "CALL EAX"]))[0]
        self.assertNotEqual(site["shape"], "VTABLE_SLOT")

    def test_a_mixture_of_shapes_is_visible(self):
        sites = D.classify_sites(*_listing(["MOV EAX,dword ptr [EDI]",
                                            "MOV EAX,dword ptr [EAX + 0x14]", "CALL EAX",
                                            "MOV EDX,dword ptr [ESP + 0x8]", "CALL EDX",
                                            "JMP dword ptr [EAX*0x4 + 0x5dd840]"]))
        self.assertEqual([site["shape"] for site in sites],
                         ["VTABLE_SLOT", "FUNCTION_POINTER", "INDIRECT_NON_VTABLE"])
        self.assertEqual([site["slot_offset"] for site in sites], [0x14, None, None])

    def test_direct_calls_and_branches_are_not_sites(self):
        self.assertEqual(D.classify_sites(*_listing(["CALL 0x00921580", "JZ 0x00001010",
                                                      "JMP 0x00001020", "RET 0x4"])), [])

    def test_the_site_detector_agrees_with_the_validator_it_sits_beside(self):
        # If these two ever disagree, "the two machine sources agree" is a claim
        # about two different quantities and the arm measures nothing.
        for texts in (CANONICAL, SELF_BASE, FRAME_SLOT, JUMP_TABLE,
                      ["CALL EAX"], ["MOV EAX,dword ptr [ECX]", "RET"]):
            _addresses, _texts = _listing(texts)
            self.assertEqual(len(D.classify_sites(_addresses, _texts)),
                             len(V._indirect_sites(_texts)),
                             "site count differs on %r" % (texts,))

    def test_every_reported_shape_is_in_the_declared_vocabulary(self):
        for texts in (CANONICAL, SELF_BASE, FRAME_SLOT, JUMP_TABLE,
                      ["LEA EAX,[ESI]", "CALL EAX"], ["CALL dword ptr [ESP + 0x30]"]):
            for site in D.classify_sites(*_listing(texts)):
                self.assertIn(site["shape"], D.STATES)
                self.assertTrue(site["reason"])
                if site["shape"] != "VTABLE_SLOT":
                    self.assertIsNone(site["slot_offset"])


class DecideArmTest(unittest.TestCase):
    """``decide``: the new PASS, and every way of failing to be it."""

    def test_a_proven_vtable_dispatch_passes_and_names_its_slot(self):
        check = _decide(CANONICAL)
        self.assertEqual(check["status"], "PASS")
        self.assertEqual(check["coverage"], "complete")
        self.assertIn("dispatches slot 0x1c", check["detail"])
        self.assertIn("two-level table load", check["detail"])
        self.assertIn("independently counts 1", check["detail"])
        self.assertEqual(check["evidence"], [D.INDEX_REL, D.EVIDENCE_REL])

    def test_every_slot_displacement_is_named_not_just_the_first(self):
        texts = CANONICAL + ["MOV EAX,dword ptr [ECX]", "MOV EAX,dword ptr [EAX + 0x48]",
                             "PUSH 0x1", "CALL EAX"]
        check = _decide(texts, indirect=2)
        self.assertEqual(check["status"], "PASS")
        self.assertIn("0x1c", check["detail"])
        self.assertIn("0x48", check["detail"])
        self.assertIn("independently counts 2", check["detail"])

    def test_a_truncated_listing_yields_no_verdict_at_all(self):
        # ``decide`` must not speak for a listing it cannot see: it returns None
        # and the caller's NOT_AVAILABLE arm stands.
        self.assertIsNone(_decide(None, indirect=1))

    def test_an_empty_body_yields_no_verdict_at_all(self):
        self.assertIsNone(_decide([], indirect=0))

    def test_a_degraded_parse_refuses_the_pass(self):
        check = _decide(CANONICAL, degraded=True, unparsed=1)
        self.assertEqual(check["status"], "WARN")
        self.assertIn("the machine parse is degraded", check["detail"])
        self.assertIn("1 instruction(s) were left unparsed", check["detail"])

    def test_unparsed_instructions_refuse_the_pass(self):
        check = _decide(CANONICAL, unparsed=2)
        self.assertEqual(check["status"], "WARN")
        self.assertIn("2 instruction(s) were left unparsed", check["detail"])

    def test_a_parse_count_that_disagrees_with_the_listing_refuses_the_pass(self):
        check = _decide(CANONICAL, declared=99)
        self.assertEqual(check["status"], "WARN")
        self.assertIn("the machine parse declared 99 instruction(s) and the listing holds 4", check["detail"])

    def test_a_missing_parse_record_refuses_the_pass(self):
        check = _decide(CANONICAL, drop_parse=True)
        self.assertEqual(check["status"], "WARN")
        self.assertIn("no machine parse record was collected", check["detail"])

    def test_a_truncated_parse_envelope_refuses_the_pass(self):
        check = _decide(CANONICAL, truncated_parse=True)
        self.assertEqual(check["status"], "WARN")
        self.assertIn("the machine parse record is a truncated envelope", check["detail"])

    def test_a_missing_dispatch_record_is_not_a_record_of_zero(self):
        check = _decide(CANONICAL, drop_dispatch=True)
        self.assertEqual(check["status"], "WARN")
        self.assertIn("a missing record is not a record of zero", check["detail"])

    def test_a_truncated_dispatch_envelope_refuses_the_pass(self):
        check = _decide(CANONICAL, truncated_dispatch=True)
        self.assertEqual(check["status"], "WARN")
        self.assertIn("the machine dispatch record is a truncated envelope", check["detail"])
        self.assertIn("a missing record is not a record of zero", check["detail"])

    def test_a_non_integer_dispatch_count_refuses_the_pass(self):
        check = _decide(CANONICAL, indirect="one")
        self.assertEqual(check["status"], "WARN")
        self.assertIn("which is not a count", check["detail"])

    def test_a_boolean_dispatch_count_is_not_a_count_of_one(self):
        # ``True`` is an ``int`` in Python. Reading it as 1 would turn a broken
        # record into an agreement with a one-site body.
        check = _decide(CANONICAL, indirect=True)
        self.assertEqual(check["status"], "WARN")
        self.assertIn("which is not a count", check["detail"])

    def test_a_dispatch_count_below_the_listing_refuses_the_pass(self):
        check = _decide(CANONICAL, indirect=0)
        self.assertEqual(check["status"], "WARN")
        self.assertIn("counts 0 and the listing names 1", check["detail"])
        self.assertIn("lower bound", check["detail"])

    def test_a_dispatch_count_above_the_listing_refuses_the_pass(self):
        # The other direction is the slice: the record counted transfers the
        # listing does not show, so the listing is not the whole body.
        check = _decide(CANONICAL, indirect=4)
        self.assertEqual(check["status"], "WARN")
        self.assertIn("counts 4 and the listing names 1", check["detail"])
        self.assertIn("probably a slice", check["detail"])

    def test_one_unresolved_site_among_vtable_slots_is_a_warn(self):
        check = _decide(CANONICAL + ["POP ESI", "PUSH 0x0", "CALL ESI"], indirect=2)
        self.assertEqual(check["status"], "WARN")
        self.assertIn("classify as UNRESOLVED", check["detail"])
        # The proven site is still reported, so the detail is not only a refusal.
        self.assertIn("dispatches slot 0x1c", check["detail"])

    def test_a_jump_table_among_vtable_slots_is_a_warn(self):
        check = _decide(CANONICAL + JUMP_TABLE, indirect=2)
        self.assertEqual(check["status"], "WARN")
        self.assertIn("classify as INDIRECT_NON_VTABLE", check["detail"])

    def test_a_body_of_only_frame_slot_calls_never_claims_a_vtable(self):
        check = _decide(FRAME_SLOT, indirect=1)
        self.assertEqual(check["status"], "WARN")
        self.assertIn("classify as FUNCTION_POINTER", check["detail"])

    def test_the_arms_that_already_existed_still_defer(self):
        # Each of these is a case the existing logic owns: a proven-empty body, a
        # source that claims a slot the machine does not have, and a body with no
        # site and no record. ``decide`` returns None for all of them, so the
        # caller's own verdict is reached unchanged.
        empty = ["MOV EAX,dword ptr [ECX]", "RET"]
        self.assertIsNone(_decide(empty, indirect=0), "proven_empty must keep the existing PASS")
        self.assertIsNone(_decide(empty, indirect=1),
                          "a source claiming a slot with no site must keep the existing FAIL")
        self.assertIsNone(_decide(empty, drop_dispatch=True),
                          "no site and no record must keep the existing WARN")

    def test_a_source_slot_offset_that_matches_the_machine_passes_both_claims(self):
        scoped = ('extern "C" void __thiscall Re_00001000(void *self) {\n'
                  "  return self->vtable_00->dispatch_1c(self);\n}\n")
        check = _decide(CANONICAL, scoped_text=scoped)
        self.assertEqual(check["status"], "PASS")
        self.assertIn("states displacement(s) 0x1c", check["detail"])
        self.assertIn("agrees with the machine and is adjudicated here too", check["detail"])

    def test_a_source_slot_offset_the_machine_does_not_show_is_a_warn_naming_both(self):
        scoped = ('extern "C" void __thiscall Re_00001000(void *self) {\n'
                  "  return self->vtable_00->dispatch_48(self);\n}\n")
        check = _decide(CANONICAL, scoped_text=scoped)
        self.assertEqual(check["status"], "WARN")
        self.assertIn("the source span states slot displacement(s) 0x48", check["detail"])
        self.assertIn("the machine reads 0x1c", check["detail"])

    def test_a_source_slot_boundary_with_no_readable_offset_splits_the_claim(self):
        # 0x00641e10's real source: the slot is named as an *index* (``1u`` is four
        # bytes), which this parser does not convert. The machine dispatch is still
        # proven, and the detail has to say the source's naming is not verified
        # rather than implying one verdict covers both.
        scoped = ('extern "C" void __thiscall Re_00001000(void *self, void *owned) {\n'
                  "  const OpaqueDispatchTable *const vtable = vtable_of(owned);\n"
                  "  const OpaqueSlotTarget slot = slot_target_at(vtable, 1u);\n"
                  "  slot(owned);\n}\n")
        check = _decide(CANONICAL, scoped_text=scoped)
        self.assertEqual(check["status"], "PASS")
        self.assertIn("states no slot displacement this parser can read", check["detail"])
        self.assertIn("NOT verified by this check", check["detail"])
        self.assertIn("0x1c", check["detail"])

    def test_a_slot_offset_named_only_in_a_comment_is_not_a_source_claim(self):
        scoped = ('extern "C" void __thiscall Re_00001000(void *self) {\n'
                  "  // the machine reads slot_48 at 0x1004\n"
                  "  return self->field_00->field_04(self);\n}\n")
        check = _decide(CANONICAL, scoped_text=scoped)
        self.assertEqual(check["status"], "PASS")
        self.assertIn("declares no slot boundary", check["detail"])

    def test_a_target_with_no_bound_source_span_says_so(self):
        check = _decide(CANONICAL, span=False, source_path=None)
        self.assertEqual(check["status"], "PASS")
        self.assertIn("No canonical source span is bound to this target", check["detail"])

    def test_a_pack_with_the_envelope_on_the_abi_layer_still_passes(self):
        check = _decide(CANONICAL, on_abi_layer=True)
        self.assertEqual(check["status"], "PASS")
        self.assertIn("independently counts 1", check["detail"])

    def test_the_withdrawn_oracles_are_named_but_carry_no_weight(self):
        # A record claiming two vtables and a dependency record claiming zero
        # references are the two things validate.py withdrew as an oracle. The pass
        # must not depend on either, and must say it read neither.
        check = _decide(CANONICAL)
        self.assertIn("2 vtable(s)", check["detail"])
        self.assertIn("0 vtable reference(s)", check["detail"])
        self.assertIn("not independent of each other", check["detail"])

    def test_the_module_agrees_with_validate_on_the_paths_it_reports(self):
        self.assertEqual(D.INDEX_REL, V.INDEX_REL)
        self.assertEqual(D.EVIDENCE_REL, V.EVIDENCE_REL)

    def test_a_verdict_is_nothing_but_a_check_dict(self):
        # A static verdict only: no runtime axis, no gate, nothing a consumer of
        # the runtime dimension could read as a runtime claim.
        check = _decide(CANONICAL)
        self.assertEqual(set(check), {"status", "detail", "coverage", "evidence"})
        self.assertNotIn("RUNTIME", check["detail"])
        self.assertNotIn("runtime", check)


class GuardMutationTest(unittest.TestCase):
    """The guards are load-bearing, not decoration.

    Each test patches the module's own classifier to lie, and requires ``decide``
    to refuse anyway. Without these, a bug in the shape analysis would surface as
    a pass on a body that does not dispatch -- the one failure this module exists
    to make impossible.
    """

    def _with_classifier(self, replacement, texts=CANONICAL, **pack):
        original = D.classify_sites
        D.classify_sites = replacement
        try:
            return _decide(texts, **pack)
        finally:
            D.classify_sites = original

    def test_a_claimed_slot_the_listing_does_not_show_still_refuses_the_pass(self):
        def liar(addresses, texts):
            return [{"address": "0x00001006", "text": "CALL EDX", "shape": "VTABLE_SLOT",
                     "slot_offset": 0x48, "base": "EAX",
                     "reason": "claimed without a two-level load in the listing"}]
        check = self._with_classifier(liar)
        self.assertEqual(check["status"], "WARN")
        self.assertIn("not reproducible from the listing bytes", check["detail"])

    def test_a_claimed_displacement_the_listing_does_not_show_still_refuses(self):
        def liar(addresses, texts):
            sites = _REAL_CLASSIFY(addresses, texts)
            sites[0]["slot_offset"] = 0x48
            return sites
        check = self._with_classifier(liar)
        self.assertEqual(check["status"], "WARN")
        self.assertIn("not reproducible from the listing bytes", check["detail"])

    def test_a_claimed_base_the_listing_does_not_show_still_refuses(self):
        def liar(addresses, texts):
            sites = _REAL_CLASSIFY(addresses, texts)
            sites[0]["base"] = "EBX"
            return sites
        check = self._with_classifier(liar)
        self.assertEqual(check["status"], "WARN")
        self.assertIn("not reproducible from the listing bytes", check["detail"])

    def test_a_wrong_site_count_still_refuses_the_pass(self):
        def liar(addresses, texts):
            return _REAL_CLASSIFY(addresses, texts) + [
                {"address": "0x00009999", "text": "CALL EBX", "shape": "VTABLE_SLOT",
                 "slot_offset": 0x8, "base": "EBX", "reason": "invented"}]
        check = self._with_classifier(liar)
        self.assertEqual(check["status"], "WARN")
        self.assertIn("the classifier returned 2 classification(s) for the 1 indirect transfer(s)",
                      check["detail"])

    def test_a_classifier_that_reports_nothing_still_refuses_the_pass(self):
        check = self._with_classifier(lambda addresses, texts: [])
        self.assertEqual(check["status"], "WARN")
        self.assertIn("the classifier returned 0 classification(s)", check["detail"])

    def test_a_whole_body_of_proven_slots_still_passes(self):
        # The counterpart: a correct classifier is not refused, so the guard is not
        # simply refusing everything.
        self.assertEqual(self._with_classifier(_REAL_CLASSIFY)["status"], "PASS")

    def test_removing_the_parse_record_removes_the_pass(self):
        self.assertEqual(_decide(CANONICAL)["status"], "PASS")
        self.assertEqual(_decide(CANONICAL, drop_parse=True)["status"], "WARN")

    def test_removing_the_dispatch_record_removes_the_pass(self):
        self.assertEqual(_decide(CANONICAL)["status"], "PASS")
        self.assertEqual(_decide(CANONICAL, drop_dispatch=True)["status"], "WARN")

    def test_a_truncated_envelope_removes_the_pass_on_either_layer(self):
        self.assertEqual(_decide(CANONICAL)["status"], "PASS")
        self.assertEqual(_decide(CANONICAL, truncated_parse=True)["status"], "WARN")
        self.assertEqual(_decide(CANONICAL, truncated_dispatch=True)["status"], "WARN")


class DispatchBackCompat(unittest.TestCase):
    """The drop-in, measured against every evidence pack on disk.

    The unit tests hold the rule from both sides. This one holds it against the
    live corpus: every pack is judged twice, once with ``decide`` live and once
    stubbed back to ``None``, and the requirement is that the *only* check whose
    status moves is VIRTUAL DISPATCH, that it only ever moves toward a stronger
    verdict, and that every moved target can show the evidence its new status
    rests on -- a complete listing, a parse record that consumed it in full, a
    dispatch record that agrees, and an all-``VTABLE_SLOT`` site set.

    Both arms read each pack as it stands; nothing is written. The arms are built
    by running the whole validator with the module live and again with it stubbed,
    and then applying the verdict the live run produced to the stubbed report's
    VIRTUAL DISPATCH position. That works whether or not ``validate.py`` has been
    wired yet: before wiring the two validator runs are identical and the
    substitution is the whole difference; after wiring the live run already carries
    it and the substitution is a no-op on the same key.
    """

    PACK_GLOB = "reconstruction/evidence/*/evidence.json"
    CHECK = "VIRTUAL DISPATCH"
    # The validator's own severity order, so "strengthened" means something
    # independent of the aggregate: FAIL, UNKNOWN, NOT_AVAILABLE, WARN, PASS.
    LADDER = ("FAIL", "UNKNOWN", "NOT_AVAILABLE", "WARN", "PASS")

    def _targets(self):
        return ["0x" + path.parent.name for path in sorted(REPO_ROOT.glob(self.PACK_GLOB))]

    def _decide_inputs(self, target):
        """The exact arguments validate passes, taken from validate's own helpers."""
        categories = json.loads((REPO_ROOT / "reconstruction/evidence" / target[2:] / "evidence.json")
                                .read_text(encoding="utf-8")).get("categories") or {}
        record = V._record(V._index(REPO_ROOT), target)
        abi_outer, abi_inner = V._abi_envelope(categories)
        resolved = V._source(REPO_ROOT, record) if record else None
        span = None
        if resolved and resolved.get("path"):
            span = V._target_span(V._read_source(resolved["path"]) or "", record)
        return dict(record=record, categories=categories, abi_outer=abi_outer, abi_inner=abi_inner,
                    listing=V._listing(categories),
                    scoped_text=span.get("text", "") if span else "",
                    target_span=span, source_path=resolved.get("path") if resolved else None,
                    dependencies=record.get("dependencies") or {}), categories, abi_outer, abi_inner

    def _report(self, target, stub):
        original = D.decide
        if stub:
            D.decide = lambda **kwargs: None
        try:
            return V.validate(va=target, write=False)["static"]["checks"]
        finally:
            D.decide = original

    def test_only_dispatch_moves_and_only_on_its_own_evidence(self):
        targets = self._targets()
        self.assertTrue(targets, "no evidence packs on disk to measure against")
        before_status, after_status = collections.Counter(), collections.Counter()
        changed, deferred, rewritten = [], 0, 0
        for target in targets:
            inputs, categories, abi_outer, abi_inner = self._decide_inputs(target)
            stubbed = self._report(target, stub=True)
            live = self._report(target, stub=False)
            if stubbed != live:
                rewritten += 1
            D.decide = lambda **kwargs: None
            try:
                self.assertIsNone(D.decide(**inputs), "the stubbed arm did not defer")
            finally:
                D.decide = _REAL_DECIDE
            verdict = _REAL_DECIDE(**inputs)
            if verdict is None:
                deferred += 1
                continue
            before = stubbed[self.CHECK]["status"]
            if verdict["status"] == before:
                continue
            changed.append((target, before, verdict["status"], inputs,
                            categories, abi_outer, abi_inner))
            before_status[before] += 1
            after_status[verdict["status"]] += 1
        # Only this check is ever written by the drop-in, so on a validator the
        # module is already wired into, the two runs above may differ nowhere
        # else. Asserted over the whole corpus rather than reasoned about.
        for target in targets:
            stubbed, live = self._report(target, stub=True), self._report(target, stub=False)
            differing = sorted(name for name in set(stubbed) | set(live)
                               if stubbed.get(name) != live.get(name))
            self.assertEqual([name for name in differing if name != self.CHECK], [],
                             "%s: the drop-in reached a check other than %s" % (target, self.CHECK))
        self.assertTrue(changed, "the corpus produced no movement at all, so the measurement is "
                                 "not measuring the arm it claims to measure")
        for target, before, after, inputs, categories, abi_outer, abi_inner in changed:
            self.assertEqual(after, "PASS", "%s moved to a state that is not a pass" % target)
            self.assertLessEqual(self.LADDER.index(before), self.LADDER.index(after),
                                 "%s was weakened (%s -> %s)" % (target, before, after))
            self.assertIsNotNone(inputs["listing"], "%s moved without a complete listing" % target)
            parse = D._machine_record(categories, abi_outer, abi_inner, "parse")
            self.assertTrue(parse, "%s moved with no parse record" % target)
            self.assertEqual(parse.get("declared_count"), len(inputs["listing"][1]),
                             "%s moved with a parse that does not cover the listing" % target)
            self.assertIsNot(parse.get("degraded"), True, "%s moved on a degraded parse" % target)
            self.assertEqual(parse.get("unparsed") or 0, 0,
                             "%s moved with unparsed instructions" % target)
            dispatch = D._machine_record(categories, abi_outer, abi_inner, "dispatch")
            self.assertTrue(dispatch, "%s moved with no dispatch record" % target)
            sites = D.classify_sites(*inputs["listing"])
            self.assertTrue(sites, "%s moved with no classified site" % target)
            self.assertEqual(dispatch.get("indirect_calls"), len(sites),
                             "%s moved with a disagreeing dispatch count" % target)
            self.assertEqual([site["shape"] for site in sites], ["VTABLE_SLOT"] * len(sites),
                             "%s moved on a site that is not a vtable slot" % target)
        print("\nVIRTUAL DISPATCH dispatch evidence: %d pack(s) measured, %d deferred to the "
              "existing arms, %d status(es) moved %s -> %s, %d pack(s) whose report differs at all "
              "with the module live (a wired validator)" % (len(targets), deferred, len(changed),
                                                             dict(before_status), dict(after_status),
                                                             rewritten))


if __name__ == "__main__":
    unittest.main()
