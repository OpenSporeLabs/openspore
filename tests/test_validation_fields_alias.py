"""FIELDS/OFFSETS: the alias-aware receiver scan, and the evidence it feeds.

Measured on the 418 committed reports, the dimension sat at ``PASS 55 / WARN 201 /
NOT_AVAILABLE 162``. This file holds the fix for the three defects that account for
the 201, and the guards that keep the fix from becoming a way of passing things the
machine does not show.

**The scan.** ``validate._receiver_displacements`` filters the listing's memory
operands on the *named* receiver register, so a body that moves the receiver into
another register is invisible to it: ``0x006a2a80`` opens ``MOV EBX,ECX`` and reaches
nothing under ``ECX`` at all, and the existing code works around that by trusting the
derived record instead. But a derived ``bounds_only`` record is a lower bound by its
own account, and the two witnesses then disagree: on ``0x0067e6f0`` the listing shows
``0x4c`` through ``ECX`` via ``LEA EDI,[ECX + 0x4c]``, the record enumerates
``{0x50, 0x60, 0x64}``, the source declares ``0x4c, 0x50, 0x64``, and the verdict was
a ``WARN`` claiming a disagreement that does not exist. So the scan has to be
alias-aware, and the two witnesses have to be ranked rather than merely unioned --
which is what ``evidence_fields`` does, with the listing governing, because it is a
complete parse of the body and the record says of itself that its enumeration is open.

**The scan's own tests** are unit tests, because every rule in it is a claim about
x86 and each one is falsifiable on its own: a copy, an address chain that composes, a
bare ``[ECX]`` that is offset zero, an alias killed by a write, an alias established
on one arm of a branch (a *may*, and a may grounds nothing), a frame slot that belongs
to somebody else, an unread line that makes the whole scan unbounded, and no register
at all, where the answer is to report nothing rather than guess.

One test states a reading rather than a result. The chain
``LEA ESI,[EBX + 0x18]`` then ``[ESI + 0x4]`` resolves to the receiver at ``0x1c``; the
assertion is that ``0x1c`` is in ``must`` and that the chain record names ``0x4`` as the
*chain's* displacement. Putting ``0x4`` in ``must`` would be the false attribution the
module exists to remove: ``0x006a2ad0``'s ``0x4`` is a field of the element the loop
walks, and clearing it as a receiver field is precisely what put four displacements
"outside the receiver bounds" in that verdict.

**The arms** are the real shapes, reproduced instruction for instruction from the
committed packs: ``0x0067e6f0`` (declared offsets all in the complete listing, one of
them outside a ``bounds_only`` window), ``0x0067e730`` (field accesses, no
declarations), ``0x006a2a80`` (the alias shape, which must not regress),
``0x006a2ad0`` (declarations on a second object), and the register-agnostic absence.

**The guards** are asserted by removing each and watching the verdict change: a
truncated listing, a parse the machine did not consume in full, a ``declared_count``
that disagrees with the instruction list, a missing ``receiver`` record, a
``bounds_only`` record asked to refute, and a fabricated scan. The last of these is the
mutation test, and it works because ``decide`` re-derives the ground truth from the
listing itself rather than through the public ``receiver_offsets`` convenience wrapper:
patching that wrapper cannot move a verdict, because a verdict that read a patchable
seam would be a verdict about the patch.

The last class is the corpus measurement. Every committed pack is judged twice, once
with ``decide`` live and once with it stubbed to ``None``, and the assertions are the
three that matter for a drop-in: only ``FIELDS/OFFSETS`` moves, it only ever moves
toward a stronger verdict, and every target it moves names the concrete machine
offsets that justified the move in its own detail.
"""

import json
import unittest
from pathlib import Path
from tempfile import TemporaryDirectory
from unittest import mock

from tools.reconstruction_tooling import evidence_fields as F
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
REPO_ROOT = Path(__file__).resolve().parents[1]
OUT = [(TARGET, HELPER, "direct-call")]


# -- the real shapes --------------------------------------------------------
#
# Reproduced instruction for instruction from the committed packs, so the fixtures are
# the cases and not a sketch of them. Addresses are the real ones; the fixture pack
# carries its own, and only the instruction text is what the scan reads.

# 0x0067e6f0, 26 instructions, register ECX, derived bounds {0x50, 0x60, 0x64}. The
# three receiver displacements the source declares are all here, and 0x4c is reachable
# only through the LEA -- which is the whole case.
CHEAT_BODY = [
    "CMP byte ptr [ECX + 0x64],0x0",
    "JZ 0x0067e726",
    "PUSH ESI",
    "MOV ESI,dword ptr [ECX + 0x50]",
    "PUSH EDI",
    "LEA EDI,[ECX + 0x4c]",
    "CMP ESI,EDI",
    "JZ 0x0067e724",
    "PUSH EBX",
    "MOV EBX,dword ptr [ESP + 0x10]",
    "MOV ECX,dword ptr [ESI + 0x10]",
    "MOV EAX,dword ptr [ECX]",
    "MOV EDX,dword ptr [EAX + 0x1c]",
    "PUSH EBX",
    "PUSH 0x1",
    "CALL EDX",
    "PUSH ESI",
    "CALL 0x00921580",
    "MOV ESI,EAX",
    "ADD ESP,0x4",
    "CMP ESI,EDI",
    "JNZ 0x0067e707",
    "POP EBX",
    "POP EDI",
    "POP ESI",
    "RET 0x4",
]
CHEAT_DECLARED = "  auto *p = reinterpret_cast<OpaqueWord *>(self + 0x4c);\n" \
                 "  return *reinterpret_cast<OpaqueWord *>(self + 0x50) + self[0x64] + p;"

# 0x0067e730, 24 instructions: the same shape without the leading guard, and a source
# that declares nothing at all. There is nothing of its own to ground and nothing
# ungrounded either, which is a pass and not a warning.
FUNC44H_DECLARED = "  return step(self);"

# 0x006a2a80, 36 instructions: the alias shape, opening ``MOV EBX,ECX`` and reaching
# 0x18, 0x1c and 0x34 -- through EBX, and through ESI after ``LEA ESI,[EBX + 0x18]``.
ALIAS_BODY = [
    "PUSH EBX",
    "PUSH EBP",
    "PUSH ESI",
    "MOV EBX,ECX",
    "MOV EBP,dword ptr [EBX + 0x18]",
    "PUSH EDI",
    "MOV EDI,dword ptr [EBX + 0x1c]",
    "LEA ESI,[EBX + 0x18]",
    "PUSH EBP",
    "PUSH EDI",
    "PUSH EDI",
    "CALL 0x00612b20",
    "MOV ECX,dword ptr [ESI + 0x4]",
    "ADD ESP,0xc",
    "PUSH ECX",
    "PUSH EAX",
    "MOV ECX,ESI",
    "CALL 0x00685a30",
    "SUB EDI,EBP",
    "MOV EAX,0xd5555555",
    "IMUL EDI",
    "SAR EDX,0x2",
    "MOV EAX,EDX",
    "SHR EAX,0x1f",
    "ADD EAX,EDX",
    "LEA EDX,[EAX + EAX*0x2]",
    "ADD EDX,EDX",
    "ADD EDX,EDX",
    "POP EDI",
    "ADD EDX,EDX",
    "ADD dword ptr [ESI + 0x4],EDX",
    "INC dword ptr [EBX + 0x34]",
    "POP ESI",
    "POP EBP",
    "POP EBX",
    "RET",
]
ALIAS_DECLARED = "  return *(int *)(self + 0x18) + *(int *)(self + 0x1c)" \
                 " + *(int *)(self + 0x34);"

# 0x006a2ad0, 33 instructions: ``MOV EDI,ECX`` at 0x006a2ad6, then receiver reads at
# 0x0, 0x18 and 0x30 -- and three displacements that belong to other objects, which is
# what the source declares alongside them.
COPYFROM_BODY = [
    "PUSH EBX",
    "MOV EBX,dword ptr [ESP + 0x8]",
    "PUSH EDI",
    "MOV EDI,ECX",
    "CMP EDI,EBX",
    "JZ 0x006a2b13",
    "PUSH ESI",
    "LEA ECX,[EDI + 0x18]",
    "CALL 0x006a28f0",
    "MOV ESI,dword ptr [EBX + 0x18]",
    "MOV EBX,dword ptr [EBX + 0x1c]",
    "CMP ESI,EBX",
    "JZ 0x006a2b07",
    "NOP",
    "MOV EAX,dword ptr [EDI]",
    "MOV EDX,dword ptr [ESI]",
    "MOV EAX,dword ptr [EAX + 0x14]",
    "LEA ECX,[ESI + 0x4]",
    "PUSH ECX",
    "PUSH EDX",
    "MOV ECX,EDI",
    "CALL EAX",
    "ADD ESI,0x18",
    "CMP ESI,EBX",
    "JNZ 0x006a2af0",
    "MOV ECX,dword ptr [EDI + 0x30]",
    "PUSH ECX",
    "MOV ECX,EDI",
    "CALL 0x006a1710",
    "POP ESI",
    "POP EDI",
    "POP EBX",
    "RET 0x4",
]
# The source's own header partitions these five, and the verdict has to be able to say
# the same thing the header does: 0x18 and 0x30 are receiver displacements, 0x18 and
# 0x1c are the argument object's, 0x4 is the element's, 0x14 is the receiver's table
# word's.
COPYFROM_DECLARED = (
    "  resize(static_cast<unsigned char *>(self) + 0x18);\n"
    "  const unsigned char *element = *reinterpret_cast<const unsigned char *const *>(\n"
    "      static_cast<const unsigned char *>(other) + 0x18);\n"
    "  const unsigned char *end = *reinterpret_cast<const unsigned char *const *>(\n"
    "      static_cast<const unsigned char *>(other) + 0x1c);\n"
    "  const std::uint32_t first = *reinterpret_cast<const std::uint32_t *>(element);\n"
    "  void *second = element + 0x4;\n"
    "  const unsigned char *table = *reinterpret_cast<const unsigned char *const *>(self);\n"
    "  slot = *reinterpret_cast<Slot *>(const_cast<unsigned char *>(table) + 0x14);\n"
    "  set_parent(self, *reinterpret_cast<void *const *>(\n"
    "      static_cast<const unsigned char *>(self) + 0x30));\n"
    "  return first;")

# 0x0096ff70's adjustor thunk: no memory operand at all, and the ``0xc`` is an immediate
# the adjustor hands on rather than a displacement. A scan of hex literals rather than of
# operands would have read it as a field access.
ADJUSTOR_BODY = ["SUB ECX,0xc", "JMP 0x0096ffd0"]
# A body that addresses memory through a base that is nobody's receiver.
FRAME_BODY = ["MOV EAX,dword ptr [EBP + 0x34]", "RET"]
# The other false positive, and the one the register-agnostic absence arm cannot reach:
# ``ECX`` here is the *index* of the operand and ``EAX`` is its base, so 0x10 is an array
# stride and not a receiver field -- while a filter on the named register, which only asks
# whether the operand mentions it, counts it as one. No receiver word is read at all.
INDEXED_BODY = ["MOV EAX,dword ptr [EAX + ECX*4 + 0x10]", "RET"]
# The same, but the frame slot is read and a receiver word too, so the body does address
# a receiver and the absence claim would be false.
MIXED_BODY = ["MOV EAX,dword ptr [EBP + 0x34]", "MOV EDX,dword ptr [ECX + 0x8]", "RET"]
# An enumerating record's shape, for the refutation test: the body reads offset zero and
# nothing else, and the source claims 0x40.
ENUM_BODY = ["MOV EAX,dword ptr [ECX]", "RET"]
DECLARED_ALONE = "  return *(int *)(self + 0x40);"


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
        base[key] = value if isinstance(value, dict) and "availability" in value \
            else _category(*value) if isinstance(value, tuple) else value
    return {"schema": "openspore-evidence-pack-1",
            "target": {"va": TARGET, "address_kind": "linked_va"},
            "evidence_state": "PERSISTED",
            "content_sha256": "0" * 64,
            "categories": base,
            "record": {}}


def _receiver(register=None, offsets=(), bounds_only=True, reason=None, present=None):
    record = {"bounds_only": bounds_only, "confidence": "INFERRED", "distinct_offsets": len(offsets),
              "max_offset": max(offsets) if offsets else None, "offsets": list(offsets),
              "register": register, "shape": "R-ALIAS" if register else None, "written_through": 0}
    if present is not None:
        record["present"] = present
    else:
        record["present"] = reason is None and bool(register)
    if reason:
        record["reason"] = reason
    return record


def _parse(declared_count=None, degraded=False, unparsed=0):
    return {"declared_count": declared_count, "degraded": degraded, "esp_unresolved": False,
            "flow_complete": True, "unparsed": unparsed}


def _machine_pack(texts, receiver=None, parse=None, drop=(), truncated=False):
    """A pack with an untruncated listing and the machine records beside it.

    ``receiver`` is the ``receiver`` sub-record itself (``None`` to carry no record at
    all, which is different again from a record that names no register); ``parse`` is
    the ``parse`` sub-record, defaulting to one that consumed the listing in full; and
    ``drop`` omits a sub-record afterwards, which is how a test says "never collected"
    rather than "says zero". ``truncated`` writes the ``{"truncated": true}`` envelope
    the collector writes for a body too long to publish whole.
    """
    value = {"calling_convention": "__cdecl", "dispatch": {"indirect_calls": 0}}
    if receiver is not None:
        value["receiver"] = receiver
    if parse is not False:
        value["parse"] = parse if parse is not None else _parse(len(texts))
    for key in drop:
        value.pop(key, None)
    disassembly = ({"truncated": True, "preview": [item for item in texts]} if truncated
                   else {"instructions": [{"address": "%08x" % (0x00C0FF00 + 6 * index), "instruction": item}
                                          for index, item in enumerate(texts)]})
    return _pack(disassembly=(True, disassembly), abi=(True, value))


# -- the wire-in, end to end -------------------------------------------------


def _write(path, payload):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(payload, encoding="utf-8")


class FieldsAliasFixture(unittest.TestCase):
    """The stub is a switch, so the same harness reaches both arms of the wire-in."""

    """A throwaway repository built from the same canonical inputs as production.

    The projection is rebuilt by the real index builder rather than hand-written, so a
    verdict here is reached by the same path production reaches it by. The wire-in is
    the snippet the orchestrator is asked to insert, run as a function so the corpus
    measurement can drive both arms of it.
    """

    def build(self, source_text, pack, edges=()):
        tmp = TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.addCleanup(_INDEX_CACHE.clear)
        root = Path(tmp.name)
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
        return root

    def judge(self, root, pack, stubbed=False):
        """``validate`` with the wire-in applied -- the orchestrator's snippet verbatim.

        The snippet is written once, as ``_wired``, and used by every test in this class
        *and* by the corpus measurement, so the thing measured is the thing the
        orchestrator is asked to insert rather than a paraphrase of it. ``stubbed=True``
        is the ``None`` arm, and it is reached by patching ``decide`` itself rather than
        by not calling it: that holds whether or not the orchestrator has already pasted
        the snippet into ``validate``, and a test that only passes in one of those two
        states is a test of the wiring rather than of the module.
        """
        if stubbed:
            with mock.patch.object(F, "decide", return_value=None):
                return V.validate(root=root, va=TARGET, evidence=pack, write=False)
        return _wired(root, TARGET, pack,
                      V.validate(root=root, va=TARGET, evidence=pack, write=False))

    def fields(self, report):
        return report["static"]["checks"]["FIELDS/OFFSETS"]


# -- receiver_offsets: the rules of the scan, one test each -----------------


class ReceiverOffsetsScan(unittest.TestCase):
    """Every rule the alias-aware scan relies on, falsifiable on its own."""

    def test_a_copy_of_the_receiver_carries_the_attribution(self):
        # 0x006a2a80 and 0x006a2ad0 both open this way. The validator's own scan finds
        # nothing here, which is the defect: a filter on the named register cannot see a
        # body that moved the receiver out of it.
        report = F.receiver_offsets(["MOV EBX,ECX", "MOV EAX,dword ptr [EBX + 0x18]", "RET"], "ECX")
        self.assertEqual(report["must"], {0x18})
        self.assertEqual(report["may"], set())
        self.assertTrue(report["bounded"])
        self.assertEqual(V._receiver_displacements(
            ["MOV EBX,ECX", "MOV EAX,dword ptr [EBX + 0x18]", "RET"], "ECX"), set())
        # The attribution is reported, not merely concluded, so a reader can see which
        # register carried it.
        self.assertEqual([entry["register"] for entry in report["aliases"]], ["EBX"])

    def test_an_address_chain_resolves_to_the_receiver_and_names_its_own_displacement(self):
        # ``LEA ESI,[EBX + 0x18]`` then ``[ESI + 0x4]``. The second access is the
        # *receiver* at 0x18 + 0x4, so 0x1c is the receiver-relative claim; 0x4 is a
        # displacement from an interior address, and is reported as the chain's own
        # displacement rather than folded into ``must`` -- folding it in is the false
        # attribution that produced 0x006a2ad0's bogus "0x4 lies outside the receiver
        # bounds".
        report = F.receiver_offsets(
            ["MOV EBX,ECX", "LEA ESI,[EBX + 0x18]", "MOV EAX,dword ptr [ESI + 0x4]", "RET"], "ECX")
        self.assertIn(0x18, report["must"])
        self.assertIn(0x1C, report["must"])
        self.assertNotIn(0x4, report["must"])
        chain = [entry for entry in report["aliases"] if entry["register"] == "ESI"]
        self.assertEqual([(entry["displacement"], entry["absolute"]) for entry in chain], [(4, 0x1C)])

    def test_a_chain_survives_a_call_because_the_frame_is_callee_saved(self):
        # The x86-32 Windows convention, and the one platform fact the scan relies on:
        # EBX/ESI/EDI/EBP survive a call, so a pointer derived before one is still that
        # pointer after it. Without this the 0x006a2a80 chain would be lost at the CALL.
        report = F.receiver_offsets(
            ["MOV EBX,ECX", "LEA ESI,[EBX + 0x18]", "CALL 0x00612b20", "MOV EAX,dword ptr [ESI + 0x4]",
             "RET"], "ECX")
        self.assertIn(0x1C, report["must"])

    def test_a_bare_dereference_is_offset_zero(self):
        # ``MOV EAX,[ECX]`` names no displacement and is still a field claim -- the word
        # at the base. A scan that collected only displacements would read it as the
        # absence of one, which is how a body that reads its receiver was cleared.
        report = F.receiver_offsets(["MOV EAX,dword ptr [ECX]", "RET"], "ECX")
        self.assertEqual(report["must"], {0})
        self.assertEqual(report["aliases"][0]["displacement"], 0)

    def test_an_alias_overwritten_before_use_contributes_nothing(self):
        # The load makes ESI a node pointer, not an interior receiver address. A scan
        # that kept the earlier binding would claim 0x4 for the receiver, and 0x4 is
        # 0x006a2ad0's *element* field.
        report = F.receiver_offsets(
            ["MOV EBX,ECX", "MOV ESI,dword ptr [EBX + 0x18]", "MOV EAX,dword ptr [ESI + 0x4]",
             "RET"], "ECX")
        self.assertEqual(report["must"], {0x18})
        self.assertNotIn(0x1C, report["must"])
        self.assertNotIn(0x4, report["must"])

    def test_a_write_to_the_receiver_itself_ends_the_parameter(self):
        # ``MOV ECX,dword ptr [ESI + 0x10]`` at 0x0067e707 puts a fresh value in the
        # receiver register; the ``[ECX]`` that follows reads that value and is not a
        # receiver-relative access by virtue of the register's name.
        report = F.receiver_offsets(
            ["MOV ESI,dword ptr [ECX + 0x50]", "MOV ECX,dword ptr [ESI + 0x10]",
             "MOV EAX,dword ptr [ECX]", "RET"], "ECX")
        self.assertEqual(report["must"], {0x50})

    def test_an_alias_established_on_one_arm_of_a_branch_is_a_may(self):
        # The copy sits after the branch, so it may not have run on the path that reaches
        # the access. A may is a witness and grounds nothing on its own, and the detail
        # has to say which it is.
        report = F.receiver_offsets(
            ["CMP byte ptr [ECX + 0x64],0x0", "JZ 0x00c0fff0", "MOV EBX,ECX",
             "MOV EAX,dword ptr [EBX + 0x18]", "RET"], "ECX")
        self.assertEqual(report["must"], {0x64})
        self.assertEqual(report["may"], {0x18})
        self.assertFalse(any(entry["must"] for entry in report["aliases"] if entry["register"] == "EBX"))

    def test_the_receiver_parameter_is_a_must_on_both_arms(self):
        # The other half of the same rule, and 0x0067e6f0 is why both halves are
        # needed: its receiver accesses sit after a JZ and are still proven, because they
        # go through the function's parameter and a branch cannot change that.
        self.assertEqual(F.receiver_offsets(CHEAT_BODY, "ECX")["must"], {0x4C, 0x50, 0x64})

    def test_a_write_through_an_unrelated_base_is_not_the_receiver(self):
        # A frame slot. The displacement is real and it is not a receiver field, which is
        # the distinction 0x006a2ad0's 0x14 turns on.
        report = F.receiver_offsets(FRAME_BODY, "ECX")
        self.assertEqual(report["must"], set())
        # And with a receiver word in the same body, only that word is claimed.
        self.assertEqual(F.receiver_offsets(MIXED_BODY, "ECX")["must"], {0x8})

    def test_a_push_pop_pair_inside_the_prefix_is_followed_and_across_a_branch_is_not(self):
        inside = F.receiver_offsets(
            ["PUSH ECX", "POP EBX", "MOV EAX,dword ptr [EBX + 0x20]", "RET"], "ECX")
        self.assertEqual(inside["must"], {0x20})
        across = F.receiver_offsets(
            ["PUSH ECX", "JZ 0x00c0fff0", "POP EBX", "MOV EAX,dword ptr [EBX + 0x20]", "RET"], "ECX")
        self.assertEqual(across["must"], set())

    def test_an_xchg_swaps_the_two_values(self):
        report = F.receiver_offsets(["XCHG EBX,ECX", "MOV EAX,dword ptr [EBX + 0x40]", "RET"], "ECX")
        self.assertEqual(report["must"], {0x40})

    def test_an_unreadable_line_makes_the_scan_unbounded(self):
        # The one thing the scan refuses to guess about: an unread line could be the
        # copy that establishes an alias, so nothing it reports is a complete
        # enumeration and no absence may be claimed from it.
        report = F.receiver_offsets(["MOV EBX,ECX", "", "MOV EAX,dword ptr [EBX + 0x18]"], "ECX")
        self.assertFalse(report["bounded"])
        self.assertEqual(report["unresolved"], [""])
        # An unbalanced bracket is the same case: the operand it opens may be the memory
        # operand whose displacement is at stake.
        self.assertFalse(F.receiver_offsets(["MOV EAX,dword ptr [ECX + 0x8"], "ECX")["bounded"])
        # A sub-register write is a partial write, so the full register is unknown.
        partial = F.receiver_offsets(["MOV EBX,ECX", "MOV BL,0x1", "MOV EAX,dword ptr [EBX + 0x18]"], "ECX")
        self.assertEqual(partial["must"], set())

    def test_no_register_reports_nothing_rather_than_guessing(self):
        # A missing receiver register is not a licence to call every displacement a
        # receiver field. ``bounded`` is false because nothing was analysed, and a caller
        # reading that flag as "may I treat this as a complete enumeration" is right not
        # to.
        for register in (None, "", "R0"):
            report = F.receiver_offsets(CHEAT_BODY, register)
            self.assertEqual(report["must"], set())
            self.assertEqual(report["may"], set())
            self.assertEqual(report["aliases"], [])
            self.assertFalse(report["bounded"])
        # An empty listing is likewise nothing, not a zero.
        self.assertEqual(F.receiver_offsets([], "ECX")["must"], set())
        self.assertTrue(F.receiver_offsets([], "ECX")["bounded"])


# -- decide: the arms, on the real shapes -----------------------------------


def _status(verdict):
    """``verdict``'s status, or ``None`` for a deferral. The module's own word for "no opinion"."""
    return verdict["status"] if verdict is not None else None


def _decide(texts, scoped="", receiver=None, parse=None, drop=(), truncated=False,
            drop_receiver=False):
    """``decide`` over a fixture pack, with the arguments the wire-in passes.

    The same eight arguments ``validate``'s block has in hand, so a verdict here is
    reached by the path the orchestrator's snippet reaches it by.
    """
    pack = _machine_pack(texts, receiver=None if drop_receiver else receiver, parse=parse,
                         drop=drop, truncated=truncated)
    categories = pack["categories"]
    abi_outer, abi_inner = V._abi_envelope(categories)
    return F.decide(record=pack["record"], categories=categories, abi_outer=abi_outer,
                    abi_inner=abi_inner, listing=V._listing(categories), scoped_text=scoped,
                    target_span={"text": scoped}, source_path=Path(SOURCE_REL))


class WitnessPrecedence(unittest.TestCase):
    """0x0067e6f0 and 0x0067e730: the listing against a bounds-only record."""

    def test_declared_offsets_all_in_the_listing_pass_with_the_precedence_stated(self):
        verdict = _decide(CHEAT_BODY, CHEAT_DECLARED,
                          receiver=_receiver("ECX", (0x50, 0x60, 0x64)))
        self.assertIsNotNone(verdict)
        self.assertEqual(verdict["status"], "PASS", verdict["detail"])
        self.assertEqual(verdict["coverage"], "complete")
        self.assertEqual(verdict["evidence"], [V.INDEX_REL, V.EVIDENCE_REL])
        # The detail has to be checkable against the binary, so it names the offsets, the
        # witness that carries each, and the two directions of the disagreement.
        for fragment in ("0x4c", "0x50", "0x64", "0x60", "governing witness",
                         "the listing shows 1 displacement(s) the record does not enumerate (0x4c)",
                         "1 of those (0x60) the scan does not attribute to the receiver"):
            self.assertIn(fragment, verdict["detail"])
        # And it is a pass about offsets only: nothing here says a layout was confirmed.
        self.assertNotIn("layout confirmed", verdict["detail"])

    def test_a_body_with_field_accesses_and_no_declarations_passes(self):
        # 0x0067e730. There is nothing the source asserts, so nothing of its own is
        # ungrounded; the machine's own reach is still reported, including the 0x4c the
        # record does not enumerate.
        verdict = _decide(CHEAT_BODY, FUNC44H_DECLARED,
                          receiver=_receiver("ECX", (0x50, 0x60)))
        self.assertEqual(verdict["status"], "PASS", verdict["detail"])
        self.assertIn("declares no field offset", verdict["detail"])
        self.assertIn("0x4c", verdict["detail"])

    def test_the_alias_shape_does_not_regress(self):
        # 0x006a2a80, whose record and whose listing agree once the scan follows the
        # alias. Nothing here is repaired, so ``decide`` defers and the validator's own
        # wording stands: replacing a correct verdict with a different correct one is
        # churn, and the contract is that ``None`` means byte-identical.
        verdict = _decide(ALIAS_BODY, ALIAS_DECLARED,
                          receiver=_receiver("ECX", (0x18, 0x1C, 0x34)))
        self.assertIsNone(verdict)
        self.assertEqual(F.receiver_offsets(ALIAS_BODY, "ECX")["must"], {0x18, 0x1C, 0x34})

    def test_offsets_on_a_second_object_are_not_a_receiver_contradiction(self):
        # 0x006a2ad0. The source declares five displacements; two are receiver words the
        # machine shows through the EDI alias, and three belong to the argument object,
        # the element and the receiver's table word. The old verdict called all three a
        # disagreement with the receiver record, which is a comparison between a
        # source-wide set and a receiver-only window.
        verdict = _decide(COPYFROM_BODY, COPYFROM_DECLARED,
                          receiver=_receiver("ECX", (0x0, 0x30)))
        self.assertEqual(verdict["status"], "PASS", verdict["detail"])
        self.assertIn("0x18, 0x30", verdict["detail"])
        self.assertIn("0x4, 0x14, 0x1c", verdict["detail"])
        # Named, not asserted: the detail says which base each was seen under, because
        # "shown somewhere in the body" is a weaker statement than "a receiver field" and
        # a reader has to be able to see that.
        self.assertIn("0x4 under ESI", verdict["detail"])
        self.assertIn("0x14 under EAX", verdict["detail"])
        self.assertIn("0x1c under EBX", verdict["detail"])
        self.assertNotIn("lie outside the machine-derived receiver bounds", verdict["detail"])


class UngroundedClaims(FieldsAliasFixture):
    """What happens when the machine really does not show the claim.

    These are asserted on the *effective* verdict -- the wire-in applied, with ``decide``
    live -- and not on ``decide`` alone, because on a pack whose only fault is an
    ungrounded displacement the validator's own verdict is already right: the same
    warning, for a compatible reason. ``decide`` defers there, and deferring is the
    contract. What these tests pin is the outcome a reader of the report sees, and that
    the module can never turn any of them into the one verdict that would be a lie.
    """

    def judge_fields(self, receiver):
        pack = _machine_pack(ENUM_BODY, receiver=receiver)
        root = self.build(_span(DECLARED_ALONE), pack, edges=OUT)
        fields = self.fields(self.judge(root, pack))
        return fields, _decide(ENUM_BODY, DECLARED_ALONE, receiver=receiver)

    def test_a_declared_offset_the_machine_shows_nowhere_warns(self):
        fields, verdict = self.judge_fields(_receiver("ECX", (0,)))
        self.assertEqual(fields["status"], "WARN", fields["detail"])
        self.assertIn("0x40", fields["detail"])
        # And the module never claims a pass over it, whatever it decides to say.
        self.assertIn(_status(verdict), (None, "WARN"))

    def test_an_enumerating_record_refutes_it_instead(self):
        # The distinction the existing code already draws and this module keeps: only an
        # enumerating record (bounds_only false) can refute a declared displacement, and
        # only once the complete listing has failed to show it too.
        fields, verdict = self.judge_fields(_receiver("ECX", (0,), bounds_only=False))
        self.assertEqual(fields["status"], "FAIL", fields["detail"])
        self.assertIn(_status(verdict), (None, "FAIL"))

    def test_a_bounds_only_record_never_refutes(self):
        # ``bounds_only`` is the record's own statement that its enumeration is open, so
        # the same declaration is uncorroborated rather than contradicted. This is the one
        # outcome that would be a lie -- a FAIL against a witness that has disclaimed the
        # power to exclude anything -- and it is asserted with the flag flipped, on the
        # effective verdict and on the module's own, because a guarantee that lives in only
        # one of them is not a guarantee.
        for bounds_only in (True, False):
            record = _receiver("ECX", (0,), bounds_only=bounds_only)
            fields, verdict = self.judge_fields(record)
            if bounds_only:
                self.assertEqual(fields["status"], "WARN", fields["detail"])
                self.assertNotEqual(_status(verdict), "FAIL")
            else:
                # The refutation stands, and the module may add the second witness to it
                # but must never weaken it.
                self.assertEqual(fields["status"], "FAIL", fields["detail"])
                self.assertIn(_status(verdict), (None, "FAIL"))
        # A record that enumerates nothing at all, while saying so, refutes nothing beyond
        # what the complete listing already failed to show.
        empty, _empty_verdict = self.judge_fields(_receiver("ECX", ()))
        self.assertEqual(empty["status"], "WARN", empty["detail"])

    def test_a_may_does_not_ground_a_declaration(self):
        # The alias is established after the branch, so 0x18 is a witness and not a proof.
        body = ["CMP byte ptr [ECX + 0x64],0x0", "JZ 0x00c0fff0", "MOV EBX,ECX",
                "MOV EAX,dword ptr [EBX + 0x18]", "RET"]
        verdict = _decide(body, "  return *(int *)(self + 0x18);", receiver=_receiver("ECX", (0x64,)))
        self.assertEqual(verdict["status"], "WARN", verdict["detail"])
        self.assertIn("may", verdict["detail"])
        self.assertIn("grounds no declared offset on its own", verdict["detail"])

    def test_an_uncorroborated_member_name_stays_a_warning(self):
        # The decision, pinned. A displacement is a location claim and this pack settles
        # those; a member name is an identity claim, and no machine record in the pack
        # carries member names, so nothing settles it. A PASS here would be a pass over a
        # claim that was never adjudicated, and the naming gap would vanish from the one
        # place a reviewer looks.
        verdict = _decide(CHEAT_BODY, "  return self->bucket_count_008 + *(int *)(self + 0x50);",
                          receiver=_receiver("ECX", (0x50, 0x60, 0x64)))
        self.assertEqual(verdict["status"], "WARN", verdict["detail"])
        self.assertIn("bucket_count_008", verdict["detail"])
        self.assertIn("no machine record in this pack carries member names", verdict["detail"])


class EvidencedAbsence(FieldsAliasFixture):
    """The absence state, and the two facts that must never be inferred to reach it."""

    def test_a_whole_body_that_reaches_no_receiver_word_is_an_evidenced_absence(self):
        # The state, with a known register, on the shape the existing arm cannot serve:
        # the naive scan reads 0x10 as a receiver displacement because the operand mentions
        # ECX as an index, so the validator warns about a disagreement with its own record
        # on a body that reads no receiver word at all.
        naive = V._receiver_displacements(INDEXED_BODY, "ECX")
        self.assertEqual(naive, {0x10})
        verdict = _decide(INDEXED_BODY, "  return 0;",
                          receiver=_receiver("ECX", (), reason="ecx_read_without_deref"))
        self.assertEqual(verdict["status"], "PASS", verdict["detail"])
        self.assertIn("no memory operand addressed through the receiver", verdict["detail"])
        self.assertIn("is not claimed here", verdict["detail"])

    def test_an_absence_this_module_has_nothing_to_repair_is_left_exactly_as_it_was(self):
        # 0x0096ff70's shape, where the naive scan and the record agree that the body
        # reaches no receiver field. There is nothing false in the existing wording, so
        # this module declines to speak: a correct verdict is not improved by being
        # rewritten, and ``None`` is the contract that keeps the validator's own
        # exact-wording tests true.
        pack = _machine_pack(ADJUSTOR_BODY,
                             receiver=_receiver("ECX", (), reason="ecx_read_without_deref"))
        root = self.build(_span("  return 0;"), pack, edges=OUT)
        self.assertIsNone(_decide(ADJUSTOR_BODY, "  return 0;",
                                  receiver=_receiver("ECX", (), reason="ecx_read_without_deref")))
        fields = self.fields(self.judge(root, pack))
        self.assertEqual(fields["status"], "PASS", fields["detail"])
        self.assertIn("names no displacement through ECX", fields["detail"])

    def test_a_body_that_reaches_a_receiver_word_through_an_alias_is_not_an_absence(self):
        # The false absence this replaces. ``validate``'s arm reads the naive scan, finds
        # nothing through ECX, and asserts the body addresses no receiver field -- while
        # the body opens ``MOV EBX,ECX`` and reads through EBX.
        verdict = _decide(ALIAS_BODY, "  return step(self);",
                          receiver=_receiver("ECX", (0x18, 0x1C, 0x34)))
        self.assertEqual(verdict["status"], "PASS", verdict["detail"])
        self.assertNotIn("addresses no receiver field", verdict["detail"])
        self.assertIn("0x18, 0x1c, 0x34", verdict["detail"])

    def test_no_receiver_record_and_no_memory_operand_is_an_absence_with_the_layout_unclaimed(self):
        # Goal E, and the state the record's abstention used to make unreachable. The
        # receiver's identity and layout are unclaimed in both directions; what is
        # claimed rests on the listing alone.
        verdict = _decide(ADJUSTOR_BODY, "  return 0;", drop_receiver=True)
        self.assertEqual(verdict["status"], "PASS", verdict["detail"])
        for fragment in ("names no receiver register", "unclaimed in both directions",
                         "performs no field access", "consumed in full by the machine parse",
                         "no memory operand through any register at all"):
            self.assertIn(fragment, verdict["detail"])
        for phrase in ("layout confirmed", "layout established", "no fields",
                       "receiver is null", "no member", "identifies no field"):
            self.assertNotIn(phrase, verdict["detail"])

    def test_no_receiver_record_and_a_body_that_does_address_memory_is_not_available(self):
        # A missing receiver record is never a record of "no fields". With no register
        # there is no receiver-relative claim to make in either direction, and a body
        # that reaches memory cannot be shown to reach no receiver field -- so this
        # defers and the validator's own NOT_AVAILABLE stands.
        for receiver in (None, _receiver(None, reason="receiver_not_determinable"),
                         _receiver(None, (), present=False)):
            verdict = _decide(FRAME_BODY, "  return 0;", drop_receiver=receiver is None,
                              receiver=receiver)
            self.assertIsNone(verdict, receiver)


class FailClosed(unittest.TestCase):
    """Every guard, removed in turn, and the verdict that has to survive it."""

    def _cheat(self, **kwargs):
        kwargs.setdefault("receiver", _receiver("ECX", (0x50, 0x60, 0x64)))
        return _decide(CHEAT_BODY, CHEAT_DECLARED, **kwargs)

    def test_a_truncated_listing_never_reaches_an_absence_or_an_offset_claim(self):
        # The preview is a prefix, and a prefix of a body that later reads ``[ECX + 0x80]``
        # is exactly what would manufacture a clearance.
        self.assertIsNone(_decide(ADJUSTOR_BODY, "  return 0;",
                                  receiver=_receiver(None, (), present=False), truncated=True))
        self.assertIsNone(_decide(CHEAT_BODY, CHEAT_DECLARED,
                                  receiver=_receiver("ECX", (0x50, 0x60, 0x64)), truncated=True))
        self.assertIsNone(V._listing(_machine_pack(ADJUSTOR_BODY, truncated=True)["categories"]))

    def test_an_empty_listing_is_not_a_body(self):
        self.assertIsNone(_decide([], "  return 0;",
                                  receiver=_receiver("ECX", (), present=False)))

    def test_a_degraded_parse_removes_the_pass(self):
        # The listing is untruncated and every declared offset is in it, but the machine
        # parse did not consume the body, so the enumeration is a lower bound and the
        # verdict is reported rather than passed.
        verdict = self._cheat(parse=_parse(len(CHEAT_BODY), degraded=True))
        self.assertEqual(verdict["status"], "WARN", verdict["detail"])
        self.assertIn("not consumed in full", verdict["detail"])

    def test_an_unparsed_instruction_removes_the_pass(self):
        verdict = self._cheat(parse=_parse(len(CHEAT_BODY), unparsed=2))
        self.assertEqual(verdict["status"], "WARN", verdict["detail"])

    def test_a_count_mismatch_between_the_parse_and_the_listing_removes_the_pass(self):
        # The third completeness term, and the one the validator's own
        # ``listing_fully_parsed`` does not test: two artefacts that disagree about the
        # size of the body cannot both be right about it.
        verdict = self._cheat(parse=_parse(len(CHEAT_BODY) - 1))
        self.assertEqual(verdict["status"], "WARN", verdict["detail"])
        self.assertIn("disagree about the body", verdict["detail"])

    def test_a_missing_parse_record_removes_the_absence(self):
        # An absent record is not a record of zero: nothing says the body is whole.
        for drop in (("parse",),):
            verdict = _decide(ADJUSTOR_BODY, "  return 0;",
                              receiver=_receiver("ECX", (), present=False), drop=drop)
            self.assertIsNone(verdict)
        verdict = _decide(ADJUSTOR_BODY, "  return 0;",
                          receiver=_receiver("ECX", (), present=False), parse=False)
        self.assertIsNone(verdict)

    def test_no_listing_defers_rather_than_guessing(self):
        self.assertIsNone(_decide(CHEAT_BODY, CHEAT_DECLARED,
                                  receiver=_receiver("ECX", (0x50, 0x60, 0x64)), truncated=True))

    def test_an_unbounded_or_unparsed_body_is_never_passed(self):
        # The whole fail-closed surface in one loop: with the evidence degraded, with the
        # evidence miscounted, or with a line the scan cannot read, the module either
        # defers or warns, and never passes -- whatever the source claims.
        claims = ("  return 0;", "  return *(int *)(self + 0x18);", "  return self->field;")
        bodies = ((ADJUSTOR_BODY, _receiver("ECX", (), present=False)),
                  (MIXED_BODY, _receiver("ECX", ())),
                  (ALIAS_BODY, _receiver("ECX", (0x18, 0x1C, 0x34))))
        for texts, receiver in bodies:
            for scoped in claims:
                for parse in (_parse(len(texts), degraded=True),
                              _parse(len(texts), unparsed=1),
                              _parse(len(texts) + 3), False):
                    verdict = _decide(list(texts) + [""] if parse is False else texts,
                                      scoped, receiver=receiver, parse=parse)
                    self.assertNotEqual(getattr(verdict, "get", lambda *_: {})("status"),
                                        "PASS", (texts[0], scoped))


class MutationGuards(FieldsAliasFixture):
    """Fabricated evidence must not reach a verdict.

    ``decide`` re-derives the ground truth from the listing through the module's own
    scan, so patching the public ``receiver_offsets`` wrapper -- the seam a caller or a
    test would reach for -- cannot move a verdict. A verdict that read a patchable seam
    would be a verdict about the patch, which is the failure mode this class exists to
    make impossible to reintroduce silently.
    """

    def test_a_fabricated_scan_does_not_reach_the_verdict(self):
        categories = _machine_pack(CHEAT_BODY, receiver=_receiver("ECX", (0x50, 0x60, 0x64)))
        abi_outer, abi_inner = V._abi_envelope(categories["categories"])
        listing = V._listing(categories["categories"])
        arguments = dict(record=categories["record"], categories=categories["categories"],
                         abi_outer=abi_outer, abi_inner=abi_inner, listing=listing,
                         scoped_text=CHEAT_DECLARED, target_span={"text": CHEAT_DECLARED},
                         source_path=Path(SOURCE_REL))
        honest = F.decide(**arguments)
        fabricated = {"must": {0x4C, 0x50, 0x64, 0xDEAD}, "may": set(), "aliases": [],
                      "unresolved": [], "bounded": True}
        with mock.patch.object(F, "receiver_offsets", return_value=fabricated):
            # The patch is live, or the test proves nothing.
            self.assertEqual(F.receiver_offsets(CHEAT_BODY, "ECX")["must"], fabricated["must"])
            patched_decide = F.decide(**arguments)
        self.assertEqual(honest["status"], "PASS")
        self.assertEqual(patched_decide["status"], "PASS")
        # Byte for byte, not merely the same status: the fabricated 0xdead never appears.
        self.assertEqual(honest["detail"], patched_decide["detail"])
        self.assertNotIn("0xdead", patched_decide["detail"])

    def test_degraded_flipped_to_true_removes_the_pass(self):
        clean = _parse(len(CHEAT_BODY))
        self.assertEqual(_decide(CHEAT_BODY, CHEAT_DECLARED,
                                 receiver=_receiver("ECX", (0x50, 0x60, 0x64)),
                                 parse=clean)["status"], "PASS")
        self.assertEqual(_decide(CHEAT_BODY, CHEAT_DECLARED,
                                 receiver=_receiver("ECX", (0x50, 0x60, 0x64)),
                                 parse=_parse(len(CHEAT_BODY), degraded=True))["status"], "WARN")

    def test_deleting_the_parse_record_removes_the_absence(self):
        # On a body this module speaks about, so the guard being exercised is this
        # module's: an absent record is not a record of zero, nothing says the body is
        # whole, and no absence is claimed from it.
        receiver = _receiver("ECX", (), reason="ecx_read_without_deref")
        self.assertEqual(_decide(INDEXED_BODY, "  return 0;", receiver=receiver)["status"], "PASS")
        # ``parse=False`` is how the fixture says "never collected" rather than "says
        # zero", and an absent record is what the guard is about.
        self.assertIsNone(_decide(INDEXED_BODY, "  return 0;", receiver=receiver, parse=False))
        # And the effective verdict loses the pass with it, on either guard: what is left
        # is the validator's own warning about a displacement in an indexed operand, which
        # is not a pass either.
        pack = _machine_pack(INDEXED_BODY, receiver=receiver, drop=("parse",))
        root = self.build(_span("  return 0;"), pack, edges=OUT)
        self.assertNotEqual(self.fields(self.judge(root, pack))["status"], "PASS")

    def test_bounds_only_can_never_produce_a_fail(self):
        # Asked the only way that matters: the record's own flag is the last thing between
        # a warning and a refutation. With the flag set, no verdict from this module is a
        # FAIL under any circumstances here; with it flipped the refutation is reached
        # again, with the complete listing as a second witness, and is never weakened.
        for offsets, bounds_only in (((0,), True), ((0,), False), ((), False), ((0, 0x40), True)):
            verdict = _decide(ENUM_BODY, DECLARED_ALONE,
                              receiver=_receiver("ECX", offsets, bounds_only=bounds_only))
            if bounds_only:
                self.assertNotEqual(_status(verdict), "FAIL", (offsets, bounds_only))
                continue
            if _status(verdict) is None:
                continue
            self.assertEqual(_status(verdict), "FAIL", (offsets, bounds_only))
            self.assertIn("bounds_only is false", verdict["detail"])
            self.assertIn("appear nowhere in the complete 2-instruction listing", verdict["detail"])


class DriftGuard(unittest.TestCase):
    """What this module restates has to keep matching the validator."""

    def test_the_restated_paths_and_patterns_match_validate(self):
        self.assertEqual(F.INDEX_REL, V.INDEX_REL)
        self.assertEqual(F.EVIDENCE_REL, V.EVIDENCE_REL)
        self.assertEqual(F.MEMORY_OPERAND.pattern, V.MEMORY_OPERAND.pattern)
        self.assertEqual(F.OPERAND_DISPLACEMENT.pattern, V.OPERAND_DISPLACEMENT.pattern)

    def test_the_check_dict_is_shaped_like_validate_check(self):
        verdict = _decide(CHEAT_BODY, CHEAT_DECLARED, receiver=_receiver("ECX", (0x50, 0x60, 0x64)))
        self.assertEqual(sorted(verdict), sorted(V._check("PASS", "detail")))
        self.assertIn(verdict["status"], ("PASS", "WARN", "FAIL", "NOT_AVAILABLE", "UNKNOWN"))
        self.assertIn(verdict["coverage"], ("none", "partial", "complete"))


# -- the wire-in, end to end -------------------------------------------------


class WireInEndToEnd(FieldsAliasFixture):
    """The snippet, reached through the real validator, on the real shapes."""

    def test_the_wire_in_moves_the_false_contradiction_and_leaves_the_rest_alone(self):
        root = self.build(_span(CHEAT_DECLARED),
                          _machine_pack(CHEAT_BODY, receiver=_receiver("ECX", (0x50, 0x60, 0x64))),
                          edges=OUT)
        stubbed = self.judge(root, _machine_pack(CHEAT_BODY,
                                                 receiver=_receiver("ECX", (0x50, 0x60, 0x64))),
                             stubbed=True)
        self.assertEqual(self.fields(stubbed)["status"], "WARN")
        self.assertIn("lie outside the machine-derived receiver bounds", self.fields(stubbed)["detail"])
        live = self.judge(root, _machine_pack(CHEAT_BODY,
                                              receiver=_receiver("ECX", (0x50, 0x60, 0x64))))
        self.assertEqual(self.fields(live)["status"], "PASS", self.fields(live)["detail"])
        # No other check may move: the wire-in touches one key of one dict.
        for name, check in stubbed["static"]["checks"].items():
            if name == "FIELDS/OFFSETS":
                continue
            self.assertEqual(check, live["static"]["checks"][name], name)

    def test_a_pack_with_no_listing_is_untouched(self):
        root = self.build(_span("  return 0;"), _pack(), edges=OUT)
        report = self.judge(root, _pack())
        self.assertEqual(self.fields(report)["status"], "NOT_AVAILABLE")


# -- the corpus measurement -------------------------------------------------

RANK = {"PASS": 3, "WARN": 2, "NOT_AVAILABLE": 1, "UNKNOWN": 1, "FAIL": 0}


class CorpusBackCompat(unittest.TestCase):
    """Every committed pack, judged twice, with the module live and stubbed to ``None``.

    The whole committed corpus is measured, not a sample (418 reports when this was
    written, 586 after the corpus was regenerated): a full double-validate costs
    about 40 s on this repository (measured: 0.042 s per ``validate`` call after the
    index is warm), so there is nothing to trade away for speed here. Three assertions,
    and they are the three that matter for a drop-in:

    * only ``FIELDS/OFFSETS`` moves. The wire-in assigns one key of one dict, and a
      change anywhere else would mean it is reading something it should not.
    * it only ever moves toward a stronger verdict, judged on the validator's own
      severity ladder -- with ``FAIL`` ranked as the finding it is, so replacing a
      refutation this module can show was not warranted counts as a strengthening.
    * every target it moves carries a detail naming the concrete machine offsets that
      justified the move, because a status without the offsets behind it is not
      reviewable.
    """

    @classmethod
    def setUpClass(cls):
        cls.reports = []
        for path in sorted((REPO_ROOT / EVIDENCE_REL).glob("*/validation.json")):
            name = path.parent.name
            evidence = path.parent / "evidence.json"
            if not evidence.is_file():
                continue
            pack = json.loads(evidence.read_text(encoding="utf-8"))
            va = "0x00%s" % name if len(name) == 6 else "0x%s" % name
            # The baseline is the module switched *off*, reached by patching ``decide``
            # rather than by not calling it -- so this measurement reads the same whether
            # or not the orchestrator has already wired the module into ``validate``.
            with mock.patch.object(F, "decide", return_value=None):
                before = V.validate(root=REPO_ROOT, va=va, evidence=pack, write=False)
            after = _wired(REPO_ROOT, va, pack,
                           V.validate(root=REPO_ROOT, va=va, evidence=pack, write=False))
            cls.reports.append((va, before, after))
        if len(cls.reports) < 400:
            raise AssertionError("the corpus measurement needs the committed reports: found %d"
                                 % len(cls.reports))
        # Measured once, asserted three times: the movement, the direction, and the
        # evidence behind it. Collected here rather than in a test body so that no test
        # returns a value and the measurement is not repeated per assertion.
        cls.moved = []
        cls.downward = []
        cls.collateral = []
        for va, before, after in cls.reports:
            for name, check in after["static"]["checks"].items():
                if name != "FIELDS/OFFSETS" and check != before["static"]["checks"][name]:
                    cls.collateral.append((va, name))
            old = before["static"]["checks"]["FIELDS/OFFSETS"]
            new = after["static"]["checks"]["FIELDS/OFFSETS"]
            if old["status"] != new["status"]:
                cls.moved.append((va, old["status"], new["status"], new["detail"]))
            if RANK[new["status"]] < RANK[old["status"]]:
                cls.downward.append((va, old["status"], new["status"]))
        cls.counts = []
        for slot in (1, 2):
            counts = {}
            for row in cls.reports:
                status = row[slot]["static"]["checks"]["FIELDS/OFFSETS"]["status"]
                counts[status] = counts.get(status, 0) + 1
            cls.counts.append(counts)

    def test_only_the_fields_check_moves_and_only_upward(self):
        self.assertEqual(self.collateral, [], "a check other than FIELDS/OFFSETS moved")
        self.assertEqual(self.downward, [], "a verdict was weakened")
        self.assertTrue(self.moved, "the module changed nothing at all")
        for va, _old, _new, detail in self.moved:
            self.assertTrue(detail.strip(), va)
            self.assertRegex(detail, r"0x[0-9a-f]+", "%s moved without naming an offset" % va)

    def test_every_moved_target_rests_on_a_complete_listing_and_names_its_offsets(self):
        for va, _old, _new, detail in self.moved:
            categories = json.loads(
                (REPO_ROOT / EVIDENCE_REL / va[2:] / "evidence.json").read_text(encoding="utf-8"))["categories"]
            abi_outer, abi_inner = V._abi_envelope(categories)
            parse = V._machine_record(categories, abi_outer, abi_inner, "parse")
            listing = V._listing(categories)
            self.assertIsNotNone(listing, va)
            self.assertEqual(parse.get("degraded"), False, va)
            self.assertEqual(int(parse.get("unparsed") or 0), 0, va)
            self.assertEqual(parse.get("declared_count"), len(listing[1]), va)
            self.assertIn("consumed in full by the machine parse", detail, va)
            self.assertNotIn("degraded=true", detail, va)

    def test_the_counts_move_the_way_the_defect_analysis_says_they_should(self):
        before, after = self.counts
        # The corpus grew (586 packs against the 418 this test was first written
        # over), so the absolute per-status totals are deliberately not pinned
        # here: a pin on them is a pin on how much evidence happens to be
        # collected, which is not what this module decides. What is pinned is the
        # *shape* of the movement, and that is what the four assertions below say.
        # The set of statuses is the validator's own vocabulary, so a new one
        # appearing in either column is a change to the ladder, not a measurement.
        self.assertLessEqual(set(before), set(RANK), sorted(set(before)))
        self.assertLessEqual(set(after), set(RANK), sorted(set(after)))
        self.assertEqual(sum(before.values()), len(self.reports), before)
        self.assertEqual(sum(after.values()), len(self.reports), after)
        # Only the false contradictions move a status, and each becomes a pass.
        self.assertGreater(after.get("PASS", 0), before.get("PASS", 0))
        self.assertEqual(after.get("PASS", 0) - before.get("PASS", 0),
                         sum(1 for _va, old, _new, _detail in self.moved
                             if old == "WARN" and _new == "PASS"))
        # Every class of defect the analysis named is still represented: a body
        # whose declared offsets are all in the complete listing while the
        # `bounds_only` record omits one, and a body that copies its receiver
        # before reading through the copy. Below 9 the fix has stopped covering
        # the cases it was written for.
        self.assertGreaterEqual(
            sum(1 for _va, old, new, _detail in self.moved if old == "WARN" and new == "PASS"),
            9, "fewer WARN->PASS moves than the defect analysis found")
        # The targets that carry no complete listing or no receiver record are
        # missing evidence, not a contradiction, and nothing here moves them.
        self.assertEqual(after.get("NOT_AVAILABLE", 0), before.get("NOT_AVAILABLE", 0))
        print("\nFIELDS/OFFSETS over %d committed reports: before %s -> after %s; %d status move(s), "
              "%d detail repair(s), no verdict weakened"
              % (len(self.reports), before, after, len(self.moved),
                 sum(1 for _va, before_report, after_report in self.reports
                     if before_report["static"]["checks"]["FIELDS/OFFSETS"]
                     != after_report["static"]["checks"]["FIELDS/OFFSETS"]) - len(self.moved)))


def _wired(root, va, pack, report):
    """The orchestrator's wire-in, as a function.

    Written once, in the shape the orchestrator is asked to paste into ``validate.py``,
    and used by the corpus measurement so that what is measured is what will be shipped.
    """
    categories = pack["categories"]
    record = V._record(V._index(root), va)
    resolved = V._source(root, record)
    span = V._target_span(V._read_source(resolved["path"] if resolved else None), record)
    abi_outer, abi_inner = V._abi_envelope(categories)
    from tools.reconstruction_tooling.evidence_fields import decide as _fields_decide
    verdict = _fields_decide(record=record, categories=categories, abi_outer=abi_outer,
                             abi_inner=abi_inner, listing=V._listing(categories),
                             scoped_text=span.get("text", "") if span else "",
                             target_span=span, source_path=resolved["path"] if resolved else None)
    if verdict is None:
        return report
    # A new report rather than an edit in place: the corpus measurement holds the stubbed
    # verdict and the wired one side by side, and an in-place assignment would make them
    # the same object and the comparison vacuous.
    report = dict(report)
    report["checks"] = dict(report["checks"])
    report["static"] = dict(report["static"])
    report["static"]["checks"] = dict(report["static"]["checks"])
    report["static"]["checks"]["FIELDS/OFFSETS"] = verdict
    report["checks"]["FIELDS/OFFSETS"] = verdict
    return report


if __name__ == "__main__":
    unittest.main()
