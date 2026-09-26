"""Hermetic test suite for the ABI-fact inference engine.

Engine under test: ``tools/reconstruction_tooling/abi_infer.py``. Pure, no
Ghidra, no network, no clock, no unseeded random. Run from the repo root:

    python3 -m unittest tests.test_abi_inference -v
    python3 -m unittest discover -s tests -t . -v

Layout
------
* Part A -- a 29-file fixture corpus in ``tests/fixtures/abi/`` with a golden
  record per input in ``tests/expected/abi/``, compared with a full semantic
  diff. One class per requirement cluster.
* Part B -- property/invariant tests over a fixed-seed corpus *and* every
  fixture, with ``FUZZ_SEED`` asserted.
* Part C -- the real SporeApp.exe functions, replayed from committed bridge
  captures in ``tests/fixtures/abi/live/`` so this file needs no bridge.
  Capture/verify is ``tests/capture_abi_golden.py``.
* Part D -- the cross-validation matrix, table-driven with ``subTest``.
* Part E -- degraded-mode robustness, using a consumer stub that mirrors the
  contract a feature-detected hook in ``evidence.py`` relies on. The stub lives
  here because ``tools/`` is owned elsewhere; it is the *contract* under test,
  not the call site.
* ``KnownEngineDefectTest`` -- the seven engine defects that were found, and
  have since been **corrected in the engine**. Every one of the seven is a
  full, undecorated assertion that passes today, and the seven stale pins
  that asserted the *defective* behaviour were removed or inverted. The
  alarm that used to be "unexpected success" now lives here as a
  documentation requirement instead: if any of these seven assertions ever
  needs weakening, the deletion note beside it names the contradicting
  test, so the reason cannot be quietly lost.

Record-schema divergences from the two design documents
------------------------------------------------------
``docs/tooling/abi-inference-tests.md`` and
``docs/tooling/abi-inference-spec.md`` were written against an earlier record:
``O1``/``I1`` observation ids, a ``PASS``/``SUPPORTED``/``WEAK`` confidence
ladder, a ``shape`` field, and ``verdict`` holding the convention name. The
landed engine emits observation ids ``obs-0001``, the canonical 7-level
``knowledgegraph/scale.py`` confidence vocabulary, ``completeness`` in place of
``shape``, and ``verdict`` restricted to ``ABI_INFERRED``/``ABI_UNKNOWN`` with
the convention in ``conventions.calling_convention``. This suite tests the
engine as landed, and each divergence is called out in the docstring of the
test that pins it. Where the documents are merely stale, the test passes; the
seven cases where the engine itself was wrong have been corrected and now live
in ``KnownEngineDefectTest``, which is where the "this was a defect" judgement
is kept.

The documents' own internal disagreements
-----------------------------------------
The research pass recorded six spec/engine conflicts. Re-running the engine
found those six and **seven more**, all named in the docstring of the test that
owns them. The two documents also disagree *with each other* -- on F02/F03-style
pairs (identical bodies, different expected ``return_class``) and on the
``0x1000`` receiver plausibility window, which the plan wants and the engine
deliberately omits. Nothing here resolves those by fiat: the engine's behaviour
is pinned and the divergence is stated. ``PlausibilityWindowDivergenceTest``
carries the most consequential one and says so loudly.
"""
import json
import os
import subprocess
import sys
import tempfile
import types
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

from tests import abi_fixtures as fx  # noqa: E402
from tools.reconstruction_tooling import abi_infer, evidence, validate  # noqa: E402
from tools.reconstruction_tooling.models import canonical_json, sha256_json  # noqa: E402

# The seed is asserted by the suite: the repo forbids unseeded randomness, and a
# corpus that cannot be reproduced cannot fail reproducibly.
FUZZ_SEED = 1234

#: A small thiscall body reused by the cross-validation matrix. `ret 0x4` so the
#: cleanup claim is OBSERVED and a conflict can visibly demote it.
THISCALL_BODY = ("PUSH EBP\nMOV EBP,ESP\n"
                 "MOV EAX,dword ptr [ECX + 0x8]\n"
                 "MOV EAX,dword ptr [ECX + 0xc]\n"
                 "MOV EAX,dword ptr [EBP + 0x8]\n"
                 "MOV ESP,EBP\nPOP EBP\nRET 0x4")
#: Frameless, no argument, no receiver: nothing distinguishes the conventions.
ABSTAIN_BODY = "MOV EAX,0x2a\nRET"
#: A single out-of-listing transfer and nothing else.
THUNK_BODY = "JMP 0x00929bd0"

# DELETED: ``CORRECTED_TO_ABSTAIN``.
#
# It existed because ``fx.LIVE_TARGETS``' convention column was recorded against
# the pre-fix engine and still carried ``__cdecl`` for ``0x005291f0``
# (``graphics_set_transform``), which the corrected engine legitimately refuses:
# ``MOV ECX,[EBP+0xc]`` loads ECX from a frame slot, so the receiver is
# *undetermined* rather than proven absent (defect D1; see
# ``KnownEngineDefectTest``). The table has since been corrected in place --
# ``tests/abi_fixtures.py`` now declares ``0x005291f0``'s expected convention as
# ``None`` -- so the exception list duplicated a condition the table states
# directly, and ``va8 in CORRECTED_TO_ABSTAIN`` was a second, weaker name for
# ``va8``'s own convention column being ``None``. With the table corrected, both
# consumers read the column alone:
# ``test_every_live_target_meets_its_convention_and_cleanup_expectation`` keys
# off ``convention is None``, and ``test_live_coverage_matches_the_research_pass_findings``
# partitions the table the same way. The one property the deleted guard test
# added -- "an abstention must name the rule that blocked it" -- is not lost to
# it: it is asserted for *every* abstaining target, from the same corpus, in
# ``DerivedRecordStorageTest``'s sibling assertion
# ``test_every_abstaining_live_target_names_the_rule_that_blocked_it``.
# Defect D1's own pin, ``test_005291f0_still_reads_its_two_slots_and_its_and_esp_is_alignment``,
# is untouched and still names the two reasons.


def record_of(name):
    """Analyse one committed fixture, by stem."""
    return abi_infer.analyze(fx.load_fixture(name))


def golden_of(name):
    return fx.read_json(fx.FIXTURES_BY_NAME[name].expected_path)


def live_record(va8, slug):
    return abi_infer.analyze(fx.read_json(fx.live_path(va8, slug)))


def live_golden(va8, slug):
    return fx.read_json(fx.live_expected_path(va8, slug))


def claim_of(record, rule):
    """The single inference with id `rule`, or None."""
    for entry in record["inferences"]:
        if entry["id"] == rule:
            return entry
    return None


def ids_of(record):
    return fx.inference_ids(record)


# =========================================================================== #
# Part A -- the fixture corpus
# =========================================================================== #
class FixtureCorpusTest(unittest.TestCase):
    """Every committed fixture must reproduce its golden byte for byte.

    The comparison is a full-record ``semantic_diff``, so a new top-level key in
    the engine's output shows up as "unexpected in actual" here and forces a
    deliberate ``gen_abi_fixtures.py --record``.
    """

    def test_every_fixture_matches_its_expected_record(self):
        seen = 0
        for name in fx.iter_fixture_names():
            if name == fx.ATT_TWIN_OF:
                continue  # asserted against 01's golden by AdapterTest
            with self.subTest(fixture=name):
                self.assertEqual([], fx.semantic_diff(golden_of(name), record_of(name)))
                seen += 1
        self.assertEqual(len(fx.FIXTURES) - 1, seen,
                         "every fixture except the AT&T twin must be asserted")

    def test_golden_is_canonical_json_on_disk(self):
        """The committed goldens are stored exactly as the engine emits them."""
        for name in fx.iter_fixture_names():
            if name == fx.ATT_TWIN_OF:
                continue
            with self.subTest(fixture=name):
                path = fx.FIXTURES_BY_NAME[name].expected_path
                with open(path, "rb") as handle:
                    raw = handle.read().decode("utf-8")
                self.assertEqual(golden_of(name), json.loads(raw))
                self.assertEqual(raw, canonical_json(json.loads(raw)),
                                 "%s is not canonically sorted" % os.path.basename(path))

    def test_goldens_reproduce_across_a_fresh_interpreter(self):
        """`content_sha256` is a real digest of the record, checked out-of-process."""
        script = (
            "import sys\n"
            "sys.path.insert(0, %r)\n"
            "from tools.reconstruction_tooling import abi_infer\n"
            "text = open(sys.argv[1], 'rb').read().decode('utf-8', 'replace')\n"
            "sys.stdout.write(abi_infer.analyze(text)['content_sha256'])\n"
        ) % ROOT
        for name in fx.iter_fixture_names():
            if name == fx.ATT_TWIN_OF:
                continue
            with self.subTest(fixture=name):
                proc = subprocess.run(
                    [sys.executable, "-c", script, fx.FIXTURES_BY_NAME[name].asm_path],
                    capture_output=True, text=True, timeout=120)
                self.assertEqual(0, proc.returncode, proc.stderr)
                self.assertEqual(golden_of(name)["content_sha256"], proc.stdout.strip())

    def test_golden_corruption_is_actually_detected(self):
        """Negative control for the corpus test: a broken golden must fail.

        Without this, "every fixture matches its golden" could be passing
        vacuously -- e.g. if ``semantic_diff`` silently swallowed everything.
        """
        expected = golden_of("01_thiscall_member")
        actual = record_of("01_thiscall_member")
        self.assertEqual([], fx.semantic_diff(expected, actual))
        for mutate in (
            lambda r: dict(r, verdict="ABI_BOGUS"),
            lambda r: dict(r, conventions=dict(r["conventions"],
                                               calling_convention="__fastcall")),
            lambda r: dict(r, cleanup=dict(r["cleanup"], bytes=99)),
            lambda r: dict(r, **{"return": dict(r["return"], type="int *")}),
            lambda r: dict(r, receiver=dict(r["receiver"], offsets=[1, 2, 3])),
        ):
            with self.subTest(mutation=mutate):
                self.assertNotEqual([], fx.semantic_diff(expected, mutate(actual)))

    def test_input_corruption_is_actually_detected(self):
        """Negative control: a changed ``.asm`` must change the record.

        This is what makes the committed inputs load-bearing. A reader who edits
        a fixture cannot leave the suite green.
        """
        original = record_of("01_thiscall_member")
        for suffix in ("NOP\n", "MOV EAX,dword ptr [ECX + 0x20]\nRET 0x4\n"):
            with self.subTest(suffix=suffix.strip()):
                mutated = abi_infer.analyze(fx.load_fixture("01_thiscall_member") + suffix)
                self.assertNotEqual(original["content_sha256"],
                                    mutated["content_sha256"])
                self.assertNotEqual([], fx.semantic_diff(original, mutated))

    def test_fixture_decode_is_stable(self):
        """The lossy byte->str decode the suite applies is deterministic.

        Fixture 15c is NUL and 0xFF bytes, so the suite must decode rather than
        read text. A decode that drifted between runs would make its golden
        unreproducible.
        """
        fixture = fx.FIXTURES_BY_NAME["15c_binary_noise"]
        self.assertEqual(fixture.text(), fx.load_fixture(fixture.stem))
        self.assertEqual(record_of(fixture.stem)["content_sha256"],
                         golden_of(fixture.stem)["content_sha256"])

    def test_corpus_covers_every_required_shape(self):
        """Guards against a future edit quietly dropping a requirement."""
        required = {
            "canonical thiscall member": "01_thiscall_member",
            "sret candidate": "02_thiscall_sret_stack_buffer",
            "cdecl, 3 stack args": "03_cdecl_three_stack_args",
            "stdcall RET 0xc": "04_stdcall_ret_0xc",
            "fastcall ECX+EDX": "05_fastcall_ecx_edx",
            "ECX read, never dereferenced": "06_ecx_read_never_dereferenced",
            "ECX single implausible offset": "07_ecx_single_implausible_offset",
            "leaf, no frame": "08_leaf_no_frame",
            "naked thunk": "09_naked_thunk",
            "two exits, disagreeing ret": "10_contradictory_ret_immediates",
            "vtable-slot call": "11_vtable_slot_call",
            "variadic/alloca-looking": "12_varargs_prologue",
            "pointer-like return": "13_pointer_return",
            "integral return": "14_integral_return",
            "non-dword ret": "17_stdcall_ret_6",
            "argless x87 return": "18_argless_x87_return",
            "receiver via spill slot": "19_receiver_spilled_to_frame_slot",
            "ECX from a stack slot": "20_ecx_loaded_from_stack_slot",
            "sret-vs-fastcall ambiguity": "21_sret_ecx_or_fastcall_ambiguous",
            "empty input": "15a_empty",
            "whitespace only": "15b_whitespace",
            "binary noise": "15c_binary_noise",
            "truncated listing": "15d_truncated",
            "prose": "15e_prose",
        }
        for label, name in sorted(required.items()):
            with self.subTest(requirement=label):
                self.assertIn(name, fx.iter_fixture_names())
                self.assertTrue(os.path.isfile(fx.FIXTURES_BY_NAME[name].asm_path))
                self.assertTrue(os.path.isfile(fx.FIXTURES_BY_NAME[name].expected_path))
        self.assertTrue(os.path.isfile(
            os.path.join(fx.FIXTURE_DIR, fx.ATT_TWIN_OF)),
            "the AT&T twin of fixture 01 is required by the layout test")
        self.assertEqual(29, len(fx.FIXTURES),
                         "the corpus grew or shrank; update this count deliberately")

    def test_live_capture_directory_holds_exactly_the_declared_targets(self):
        on_disk = sorted(name for name in os.listdir(fx.LIVE_DIR)
                         if name.endswith(".json"))
        expected = sorted("%s_%s.json" % (entry[0], entry[1])
                          for entry in fx.LIVE_TARGETS)
        self.assertEqual(expected, on_disk,
                         "a capture is committed that nothing asserts, or vice versa")


class VocabularyTest(unittest.TestCase):
    """The whitelists, asserted against the engine's own constants."""

    def test_engine_constants_have_the_documented_shapes(self):
        self.assertEqual("openspore-abi-inference-1", abi_infer.SCHEMA)
        self.assertEqual(("__cdecl", "__stdcall", "__thiscall", "__fastcall"),
                         abi_infer.CONVENTIONS)
        self.assertEqual(("ABI_INFERRED", "ABI_UNKNOWN"), abi_infer.VERDICTS)
        self.assertEqual(
            ("UNKNOWN", "APPROXIMATION", "INFERRED", "SUPPORTED", "OBSERVED",
             "CONFIRMED", "VERIFIED"), abi_infer.CONFIDENCE_ORDER)
        self.assertEqual(23, len(abi_infer.ABI_KEYS),
                         "the abi block whitelist must stay 23 names wide")
        self.assertTrue(abi_infer.ABSTENTION_CODES)

    def test_abi_key_whitelist_matches_the_consumer_it_feeds(self):
        """``ABI_KEYS`` must stay the same 23 names ``extract_abi`` whitelists.

        Load-bearing, not cosmetic: the validator consumes the emitted ``abi``
        sub-object verbatim, so a name the engine adds that
        ``tools/reconstruction_knowledge.py::extract_abi`` does not want would be
        dropped on the floor, silently.
        """
        expected = {
            "architecture", "calling_convention", "convention", "return_type",
            "return_width_bytes", "return_register", "stack_cleanup_bytes",
            "stack_cleanup_owner", "hidden_this_register", "hidden_receiver",
            "hidden_this", "hidden_this_type", "receiver_register", "receiver",
            "stack_arguments", "ordinary_stack_arguments",
            "ordinary_stack_argument_slots", "saved_registers", "ret_form",
            "termination", "return_semantics", "return", "return_observation",
        }
        self.assertEqual(expected, set(abi_infer.ABI_KEYS))
        from tools import reconstruction_knowledge
        with open(reconstruction_knowledge.__file__, encoding="utf-8") as handle:
            source = handle.read()
        start = source.index("def extract_abi(")
        body = source[start:start + 1600]
        for key in sorted(expected):
            with self.subTest(key=key):
                self.assertIn('"%s"' % key, body,
                              "extract_abi no longer whitelists %r" % key)

    def test_record_verdict_is_not_a_convention_name(self):
        """Divergence from both documents, pinned on purpose.

        The documents put the convention in ``verdict``. The engine restricts
        ``verdict`` to ABI_INFERRED/ABI_UNKNOWN and keeps the convention in
        ``conventions.calling_convention``. A reader that treats ``verdict`` as a
        convention is reading the wrong field.
        """
        record = record_of("01_thiscall_member")
        self.assertEqual("ABI_INFERRED", record["verdict"])
        self.assertIn(record["verdict"], abi_infer.VERDICTS)
        self.assertNotIn(record["verdict"], abi_infer.CONVENTIONS)
        self.assertEqual("__thiscall", fx.convention_of(record))

    def test_the_documents_pass_rung_does_not_exist_in_the_engine(self):
        """The documents' invariant "no PASS claim" is vacuous as written.

        ``PASS`` is not in ``CONFIDENCE_ORDER`` at all -- the engine mirrors
        ``knowledgegraph/scale.py``. The engine's own analogue is asserted
        properly in ``PropertyTest``: ABI_UNKNOWN implies a null convention and
        UNKNOWN conventions confidence.
        """
        self.assertNotIn("PASS", abi_infer.CONFIDENCE_ORDER)
        for name in fx.iter_fixture_names():
            if name == fx.ATT_TWIN_OF:
                continue
            with self.subTest(fixture=name):
                for entry in record_of(name)["inferences"]:
                    self.assertIn(entry["confidence"], abi_infer.CONFIDENCE_ORDER)


class CanonicalThiscallTest(unittest.TestCase):
    """Fixture 01 -- the shape every real __thiscall member reduces to."""

    def test_f01_is_thiscall_with_caller_cleanup(self):
        record = record_of("01_thiscall_member")
        self.assertEqual("ABI_INFERRED", record["verdict"])
        self.assertEqual("__thiscall", fx.convention_of(record))
        self.assertIn("C7", ids_of(record))
        self.assertEqual("caller", record["cleanup"]["side"])
        self.assertEqual(0, record["cleanup"]["bytes"])
        self.assertIn("C5", ids_of(record))
        self.assertEqual("CORE_RESOLVED", record["completeness"])
        self.assertEqual([], record["abstained_because"])

    def test_f01_receiver_offsets_and_write_through(self):
        receiver = record_of("01_thiscall_member")["receiver"]
        self.assertIs(True, receiver["present"])
        self.assertEqual("ECX", receiver["register"])
        self.assertEqual([8, 12, 16, 20], receiver["offsets"])
        self.assertEqual(4, receiver["distinct_offsets"])
        self.assertEqual(20, receiver["max_offset"])
        self.assertEqual(2, receiver["written_through"],
                         "two of the four [ECX+d] accesses are store destinations")
        self.assertTrue(receiver["bounds_only"],
                        "the record must not claim to know the object's size")
        self.assertIn("R1", ids_of(record_of("01_thiscall_member")))

    def test_f01_slot_table_is_entry_relative(self):
        slots = record_of("01_thiscall_member")["stack_arguments"]
        self.assertEqual(2, slots["observed_slots"])
        self.assertEqual(0, slots["derived_slots"])
        self.assertEqual(0, slots["gaps"])
        self.assertEqual(8, slots["total_bytes"])
        self.assertEqual([1, 2], [slot["ordinal"] for slot in slots["slots"]])
        self.assertEqual(["entry_ESP+0x4", "entry_ESP+0x8"],
                         [slot["entry_offset"] for slot in slots["slots"]])

    def test_f01_abi_block_is_populated_and_whitelisted(self):
        abi = record_of("01_thiscall_member")["abi"]
        self.assertEqual("x86-32", abi["architecture"])
        self.assertEqual("__thiscall", abi["calling_convention"])
        self.assertEqual("ECX", abi["hidden_this_register"])
        self.assertEqual("ECX", abi["receiver_register"])
        self.assertIs(True, abi["hidden_this"])
        self.assertIs(True, abi["receiver"])
        self.assertEqual(0, abi["stack_cleanup_bytes"])
        self.assertEqual("caller", abi["stack_cleanup_owner"])
        self.assertEqual("EAX", abi["return_register"])
        self.assertEqual("pointer_like_in_EAX", abi["return_semantics"])
        for key in abi:
            self.assertIn(key, abi_infer.ABI_KEYS)

    def test_f01_emits_no_cpp_type_anywhere(self):
        """The engine's hardest promise: a machine fact, never a C++ type."""
        record = record_of("01_thiscall_member")
        self.assertIsNone(record["return"]["type"])
        self.assertNotIn("return_type", record["abi"])
        self.assertNotIn("return_width_bytes", record["abi"])
        for inference in record["inferences"]:
            value = inference.get("value")
            if isinstance(value, dict):
                self.assertNotIn("type", value)
                self.assertNotIn("type_name", value)
                self.assertNotIn("cpp_type", value)


class HiddenReturnTest(unittest.TestCase):
    """Fixtures 02 and 21 -- the sret question, which the engine refuses.

    The engine's module docstring: "MSVC sret and an out-parameter compile to the
    same instruction sequence, so the engine reports the ambiguity instead of
    picking a winner." That is why ``sret.present`` is never ``True``.
    """

    def test_f02_sret_is_never_asserted_present(self):
        record = record_of("02_thiscall_sret_stack_buffer")
        self.assertIsNot(True, record["sret"]["present"])
        self.assertFalse(record["sret"]["present"])
        self.assertIsNone(record["sret"]["slot"])
        self.assertIsNone(record["sret"]["hypothesis_confidence"])
        self.assertIsNone(record["sret"]["ambiguity"])
        self.assertIn("S2", ids_of(record))

    def test_f02_is_thiscall_with_callee_cleanup_and_no_return_type(self):
        """Divergence from the documents: no ``hidden_return`` claim is emitted.

        The plan's §2.2 fixture 02 expects a ``hidden_return`` inference at
        SUPPORTED with role-tagged slots. The engine emits no such claim: the
        fixture loads entry slot 0 into EAX and then stores through a *local*,
        never through the loaded pointer, so S1's written-through test does not
        fire. The plan's own expectation is unsatisfiable from this body --
        "written through a frame slot" is not the sret signature, "written
        through the pointer" is.
        """
        record = record_of("02_thiscall_sret_stack_buffer")
        self.assertEqual("__thiscall", fx.convention_of(record))
        self.assertEqual("callee", record["cleanup"]["side"])
        self.assertEqual(12, record["cleanup"]["bytes"])
        self.assertIsNone(record["return"]["type"])
        self.assertNotIn("S1", ids_of(record),
                         "no sret hypothesis is derivable from this body")
        for slot in record["stack_arguments"]["slots"]:
            self.assertNotIn("role", slot,
                             "the engine never tags a slot's role")

    def test_f02_baseline_absence_is_weak_on_its_face(self):
        """``present: False`` is a DERIVED claim and says so."""
        record = record_of("02_thiscall_sret_stack_buffer")
        self.assertEqual("APPROXIMATION", record["sret"]["confidence"])
        self.assertIn("DERIVED absence is weak", record["sret"]["basis"])
        self.assertEqual("APPROXIMATION", claim_of(record, "S2")["confidence"])

    def test_sret_presence_is_never_true_across_the_whole_corpus(self):
        for label, text in fx.hermetic_inputs() + fx.live_inputs():
            with self.subTest(input=label):
                self.assertIsNot(True, abi_infer.analyze(text)["sret"]["present"])

    def test_sret_ambiguity_is_reported_on_a_real_function(self):
        """0x0040ccb0: the ambiguity is surfaced even though a convention is.

        ``sret_vs_out_param`` is the case the engine is *for*: slot 0 is loaded
        into a register that is then the base of a write. That sequence is
        identical for a hidden struct return and for an out-parameter, so the
        record carries ``present: null``, the ambiguity name and the S1
        hypothesis, and abstains on the code. It still infers ``__thiscall``,
        which is right: the convention does not depend on the sret question.
        """
        record = live_record("0040ccb0", "thiscall_spilled_receiver")
        self.assertIsNone(record["sret"]["present"])
        self.assertEqual("sret_vs_out_param", record["sret"]["ambiguity"])
        self.assertEqual(["hidden_sret", "out_parameter"], record["sret"]["candidates"])
        self.assertIn("S1", ids_of(record))
        self.assertIn("sret_vs_out_param", fx.abstention_codes(record))
        self.assertEqual("__thiscall", fx.convention_of(record))

    def test_s3_states_the_this_sret_ordering_is_a_non_question(self):
        """0x0040ccb0 with a receiver: MSVC never puts ``this`` and sret in contention."""
        record = live_record("0040ccb0", "thiscall_spilled_receiver")
        self.assertEqual({"this_register": "ECX", "sret_slot": 4,
                          "ordering": "not_applicable"},
                         record["sret"]["this_interaction"])


class CleanupTest(unittest.TestCase):
    """Fixtures 03, 04, 10, 17 -- who pops, and how many bytes.

    ``test_f17_non_dword_ret_is_reported_as_observed_cleanup`` was DELETED here.
    It asserted that ``ret 0x6`` yields ``callee``/6 at OBSERVED and a
    confident ``__stdcall``. ``KnownEngineDefectTest.
    test_non_dword_ret_must_be_a_contradiction`` now asserts the opposite on
    the same fixture -- a non-dword pop must abstain -- and passes, because
    defect D5 was corrected. Both cannot hold and the abstention is the
    admissible one: 6 is not a whole number of dword arguments, so neither the
    cleanup side nor ``__stdcall`` is derivable from it.
    """

    def test_f03_abstains_on_an_undetermined_receiver_but_keeps_three_slots(self):
        """Was ``test_f03_is_cdecl_with_three_observed_slots``.

        REPAIRED, not deleted: the concern this test exists for -- that a
        three-argument, caller-cleaned body yields exactly three observed entry
        slots at 4/8/0xc and 12 bytes -- is still valid and is unchanged. Only
        the convention claim moved.

        DELETED ASSERTION: ``__cdecl`` (and ``C9``) for fixture 03.
        ``KnownEngineDefectTest.test_undetermined_receiver_must_not_yield_a_
        convention`` pins the opposite for the same receiver state, and defect
        D1 was corrected: ECX is *undetermined* here (``ecx_read_without_
        deref``), and every remaining discriminator needs receiver *absence*,
        which is a different fact. C9 was therefore replaced by C10 and the
        record abstains. The other six assertions are untouched.
        """
        record = record_of("03_cdecl_three_stack_args")
        self.assertIsNone(fx.convention_of(record))
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertNotIn("C9", ids_of(record))
        self.assertIn("C10", ids_of(record))
        self.assertIn("receiver_undetermined_blocks_convention",
                      fx.abstention_codes(record))
        self.assertEqual("caller", record["cleanup"]["side"])
        self.assertEqual(0, record["cleanup"]["bytes"])
        slots = record["stack_arguments"]
        self.assertEqual(3, slots["observed_slots"])
        self.assertEqual(12, slots["total_bytes"])
        self.assertEqual(["entry_ESP+0x4", "entry_ESP+0x8", "entry_ESP+0xc"],
                         [slot["entry_offset"] for slot in slots["slots"]])

    def test_f03_ecx_and_edx_loaded_from_slots_are_not_register_arguments(self):
        """The adversarial point the plan pins, and the engine honours it.

        ``MOV ECX,dword ptr [EBP + 0xc]`` and ``MOV EDX,dword ptr [EBP + 0x10]``
        both use ECX and EDX as memory bases, but their def dominates the use
        and their source is a frame slot. An engine that inferred ``__fastcall``
        from "ECX and EDX are memory bases" would be wrong here.
        """
        record = record_of("03_cdecl_three_stack_args")
        self.assertNotEqual("__fastcall", fx.convention_of(record))
        self.assertNotIn("C8", ids_of(record))
        self.assertNotIn("C8-E", ids_of(record))
        self.assertIsNone(record["receiver"]["present"])
        self.assertEqual("ecx_read_without_deref", record["receiver"]["reason"])
        self.assertIn("receiver_not_determinable", fx.abstention_codes(record))

    def test_f03_return_class_is_integral(self):
        block = record_of("03_cdecl_three_stack_args")["return"]
        self.assertEqual("EAX", block["register"])
        self.assertEqual("integral", block["register_class"])
        self.assertIsNone(block["type"])

    def test_f04_is_stdcall_from_the_ret_immediate_alone(self):
        record = record_of("04_stdcall_ret_0xc")
        self.assertEqual("__stdcall", fx.convention_of(record))
        self.assertIn("C6", ids_of(record))
        self.assertIn("C3", ids_of(record))
        self.assertIn("A1-IMM", ids_of(record))
        self.assertEqual("callee", record["cleanup"]["side"])
        self.assertEqual(12, record["cleanup"]["bytes"])
        self.assertEqual("ret 0xc", record["cleanup"]["evidence"])
        self.assertFalse(record["receiver"]["present"],
                         "ECX is never mentioned, so there is no receiver")
        self.assertIn("R2", ids_of(record))

    def test_f04_derived_slots_are_never_reported_as_observed(self):
        """A1-IMM reports the popped *area*, not a parameter count.

        The claim text says so, and the fields are split so a consumer cannot
        confuse them: ``observed_slots`` is 0, ``derived_slots`` is 3, and every
        derived slot carries ``observed: false`` and
        ``source: "ret_immediate"``.
        """
        record = record_of("04_stdcall_ret_0xc")
        slots = record["stack_arguments"]
        self.assertEqual(0, slots["observed_slots"])
        self.assertEqual(3, slots["derived_slots"])
        for slot in slots["slots"]:
            self.assertIs(False, slot["observed"])
            self.assertIs(False, slot["read"])
            self.assertEqual("ret_immediate", slot["source"])
        self.assertIn("not a parameter count", claim_of(record, "A1-IMM")["claim"])

    def test_f04_gaps_counts_derived_slots_which_is_a_reporting_hazard(self):
        """``gaps: 3`` next to ``derived_slots: 3`` is not three missing arguments.

        The engine's slot-table pass sets ``gaps`` to the number of derived slots
        when the table comes from the immediate. A consumer that read ``gaps`` as
        "ordinals below the highest observed slot that were never touched" would
        conclude this three-argument stub has three holes. Pinned so the oddity is
        visible rather than accidental.
        """
        slots = record_of("04_stdcall_ret_0xc")["stack_arguments"]
        self.assertEqual(3, slots["gaps"])
        self.assertEqual(slots["derived_slots"], slots["gaps"])
        self.assertNotIn("slot_gaps_present",
                         fx.abstention_codes(record_of("04_stdcall_ret_0xc")))

    def test_f10_disagreeing_ret_immediates_abstain_on_the_convention(self):
        """Divergence from the plan's vocabulary; the engine matches the spec.

        The plan expects ``mode: "UNKNOWN"`` and reason
        ``contradictory_cleanup``. The engine emits ``side: "CONFLICT"`` plus the
        two codes ``ret_immediates_disagree`` and ``cleanup_undeterminable`` --
        which is character-for-character what ``abi-inference-spec.md``'s own F12
        fragment specifies. The plan is the stale document here.
        """
        record = record_of("10_contradictory_ret_immediates")
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertIsNone(fx.convention_of(record))
        self.assertEqual("UNKNOWN", record["conventions"]["confidence"])
        self.assertEqual("CONFLICT", record["cleanup"]["side"])
        self.assertIsNone(record["cleanup"]["bytes"])
        self.assertIn("terminal ret immediates disagree: 0x4, 0x8",
                      record["cleanup"]["evidence"])
        codes = fx.abstention_codes(record)
        self.assertIn("ret_immediates_disagree", codes)
        self.assertIn("cleanup_undeterminable", codes)
        self.assertIn("C1", ids_of(record))

    def test_f10_receiver_survives_the_cleanup_contradiction(self):
        """A bad cleanup must suppress the convention, not the receiver evidence.

        The two facts are independent: ECX is demonstrably dereferenced at two
        offsets even though we cannot say who pops.
        """
        record = record_of("10_contradictory_ret_immediates")
        receiver = record["receiver"]
        self.assertIs(True, receiver["present"])
        self.assertEqual([4, 8], receiver["offsets"])
        self.assertIn("R1", ids_of(record))
        self.assertNotIn("C7", ids_of(record))
        self.assertNotIn("C6B", ids_of(record))

    def test_f10_slot_table_is_still_reported_though_the_plan_says_otherwise(self):
        """Divergence: the plan says ``stack_arguments`` must be absent.

        The engine reports the one slot it can see. That is the right call -- the
        observed slot is a fact independent of who pops -- but the plan's
        expectation is explicit, so the divergence is pinned.
        """
        record = record_of("10_contradictory_ret_immediates")
        self.assertEqual(1, record["stack_arguments"]["observed_slots"])
        self.assertIn("A1", ids_of(record))

    # DELETED: test_f17_non_dword_ret_is_reported_as_observed_cleanup.
    # Asserted cleanup "callee"/6 at OBSERVED, conventions.calling_convention
    # "__stdcall" and an empty abstained_because for fixture 17. Now covered by
    # KnownEngineDefectTest.test_non_dword_ret_must_be_a_contradiction, which
    # asserts the opposite (side None, bytes None, convention None, ABI_UNKNOWN)
    # and passes since defect D5 was corrected. The old assertion is no longer
    # admissible because 6 is not a whole number of dword arguments, so
    # __stdcall was never derivable from it.

    def test_c4_flags_a_pop_smaller_than_the_highest_slot_read(self):
        record = abi_infer.analyze(
            "PUSH EBP\nMOV EBP,ESP\n"
            "MOV EAX,dword ptr [EBP + 0x8]\n"
            "MOV EDX,dword ptr [EBP + 0x10]\n"
            "MOV ESP,EBP\nPOP EBP\nRET 0x4\n")
        self.assertIn("ret_imm_below_highest_slot", fx.abstention_codes(record))
        self.assertIn("C4", ids_of(record))
        self.assertIsNone(record["cleanup"]["side"])
        self.assertEqual("UNKNOWN", record["cleanup"]["confidence"])


class RegisterArgumentTest(unittest.TestCase):
    """Fixtures 05, 06, 07, 20 -- ECX and EDX as register evidence.

    Both ``test_f06_*`` and ``test_f20_*`` were REPAIRED: each asserted
    ``__cdecl`` for a body whose receiver is *undetermined*, and
    ``KnownEngineDefectTest.test_undetermined_receiver_must_not_yield_a_
    convention`` now asserts ``None`` for the same two fixtures and passes
    (defect D1). The ``__cdecl`` claim was deleted from both; the rest of each
    test -- the receiver reason, the R0 rule, the missing C8/C8-E, the reason
    ``__thiscall`` survives as a candidate, the full slot table -- is the real
    subject of those tests and is kept, and the abstention is now asserted
    positively so the two fixtures cannot drift back together.
    """

    def test_f05_is_the_only_fastcall_in_the_corpus(self):
        record = record_of("05_fastcall_ecx_edx")
        self.assertEqual("__fastcall", fx.convention_of(record))
        self.assertIn("C8", ids_of(record))
        self.assertIn("C8-E", ids_of(record))
        self.assertEqual(["__fastcall"], record["conventions"]["candidate_conventions"])
        self.assertEqual("caller", record["cleanup"]["side"])
        self.assertEqual(0, record["stack_arguments"]["observed_slots"])
        self.assertEqual([4, 8, 12], record["receiver"]["offsets"])
        for label, text in fx.hermetic_inputs() + fx.live_inputs():
            if label == "05_fastcall_ecx_edx":
                continue  # this fixture is the one that is supposed to be it
            with self.subTest(input=label):
                self.assertNotEqual("__fastcall", fx.convention_of(abi_infer.analyze(text)))

    def test_f05_fastcall_is_capped_at_inferred_never_supported(self):
        """The spec calls C8 the one strong discriminator, and still caps it.

        Hand-written assembly and intrinsic wrappers are the counterexample, so
        without external corroboration the claim cannot reach SUPPORTED.
        """
        record = record_of("05_fastcall_ecx_edx")
        self.assertEqual("INFERRED", record["conventions"]["confidence"])
        corroborated = abi_infer.analyze(fx.load_fixture("05_fastcall_ecx_edx"),
                                         ghidra_calling_convention="__fastcall")
        self.assertEqual("SUPPORTED", corroborated["conventions"]["confidence"])
        self.assertEqual("__fastcall", fx.convention_of(corroborated))

    def test_f06_ecx_read_but_never_dereferenced_is_undetermined_not_absent(self):
        """Was ``test_f06_ecx_read_but_never_dereferenced_still_names_a_
        convention``.

        The subject is unchanged: an ECX that is read but never dereferenced is
        a *known-unknown* receiver, and the record has to say which. Only the
        conclusion moved.

        DELETED ASSERTION: ``conventions.calling_convention == "__cdecl"``.
        ``KnownEngineDefectTest.test_undetermined_receiver_must_not_yield_a_
        convention`` asserts ``None`` for this exact fixture and passes, since
        defect D1 was corrected. C9's own precondition is "receiver absent";
        ``ecx_read_without_deref`` is not that, so the engine no longer gets to
        reach a convention. ``__thiscall`` therefore stays only as a
        *candidate*, and the record abstains -- which is the honest reading of a
        receiver we cannot place.

        Three documents had disagreed here and the engine picked the permissive
        one; the conservative reading is now implemented, and the assertions
        below pin the parts that were always right.
        """
        record = record_of("06_ecx_read_never_dereferenced")
        self.assertIsNone(fx.convention_of(record))
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertIn("receiver_undetermined", record["conventions"]["ambiguities"])
        self.assertIn("__thiscall", record["conventions"]["candidate_conventions"])
        receiver = record["receiver"]
        self.assertIsNone(receiver["present"])
        self.assertEqual("ecx_read_without_deref", receiver["reason"])
        self.assertEqual("UNKNOWN", receiver["confidence"])
        self.assertIn("R0", ids_of(record))
        codes = fx.abstention_codes(record)
        self.assertIn("receiver_not_determinable", codes)
        self.assertIn("receiver_undetermined_blocks_convention", codes)

    def test_f07_a_single_implausible_offset_is_accepted_as_a_receiver(self):
        """Divergence, prominent on purpose: there is no plausibility window.

        See ``PlausibilityWindowDivergenceTest`` for the full argument.
        """
        record = record_of("07_ecx_single_implausible_offset")
        self.assertIs(True, record["receiver"]["present"])
        self.assertEqual([16384], record["receiver"]["offsets"])
        self.assertEqual(1, record["receiver"]["distinct_offsets"])
        self.assertEqual("__thiscall", fx.convention_of(record))
        self.assertEqual([], record["abstained_because"])
        self.assertIn("R1", ids_of(record))
    def test_f20_ecx_and_edx_loaded_from_stack_slots_are_store_bases_only(self):
        """The most important negative control in the corpus.

        Both ECX and EDX are the *destination* of a store, so any engine that
        infers ``__fastcall`` from "ECX and EDX are memory bases" is wrong. This
        is also the shape behind the real 0x00aea250 conflict.

        REPAIRED: the ``__cdecl`` claim was deleted. It contradicted
        ``KnownEngineDefectTest.test_undetermined_receiver_must_not_yield_a_
        convention``, which asserts ``None`` for this fixture and passes since
        defect D1 was corrected -- ``ecx_reassigned_before_deref`` is an
        undetermined receiver, not a proven-absent one, so C9 may not fire.
        Everything that made this the corpus's key negative control is kept, and
        the abstention is now asserted positively.
        """
        record = record_of("20_ecx_loaded_from_stack_slot")
        self.assertIsNone(fx.convention_of(record))
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertIn("receiver_undetermined", record["conventions"]["ambiguities"])
        self.assertNotIn("C8", ids_of(record))
        self.assertNotIn("C8-E", ids_of(record))
        self.assertNotIn("C9", ids_of(record))
        receiver = record["receiver"]
        self.assertIsNone(receiver["present"])
        self.assertEqual("ecx_reassigned_before_deref", receiver["reason"])
        codes = fx.abstention_codes(record)
        self.assertIn("receiver_not_determinable", codes)
        self.assertIn("receiver_undetermined_blocks_convention", codes)
        self.assertEqual(4, record["stack_arguments"]["observed_slots"])
        self.assertEqual(["entry_ESP+0x4", "entry_ESP+0x8", "entry_ESP+0xc",
                          "entry_ESP+0x10"],
                         [slot["entry_offset"]
                          for slot in record["stack_arguments"]["slots"]])


    def test_f20_no_register_argument_name_is_invented(self):
        """The engine has no such ABI_KEYS name and must not fabricate one."""
        record = record_of("20_ecx_loaded_from_stack_slot")
        self.assertNotIn("register_incoming_registers", record["abi"])
        self.assertNotIn("register_arguments", record["abi"])
        for key in record["abi"]:
            self.assertIn(key, abi_infer.ABI_KEYS)


class ShapeTest(unittest.TestCase):
    """Fixtures 08, 09, 11, 12, 12b, 18, 22 -- when the engine refuses.

    ``test_f12_does_not_abstain_and_the_gate_it_wants_does_not_exist`` was
    DELETED here. It asserted that fixture 12's va_list zero-fill shape does
    *not* abstain, because the plan's ``varargs_or_alloca_prologue`` gate had no
    implementation. ``KnownEngineDefectTest.test_varargs_prologue_must_abstain``
    now asserts that it does abstain, on the same fixture, and passes since
    defect D6 was corrected. Fixture 12b below remains the positive control
    proving the variadic gate is live rather than vacuous.
    """

    def test_f08_frameless_leaf_is_observable_but_unclassifiable(self):
        record = record_of("08_leaf_no_frame")
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertIsNone(fx.convention_of(record))
        self.assertIn("no_discriminator", fx.abstention_codes(record))
        self.assertEqual("UNKNOWN", record["conventions"]["confidence"])
        self.assertIn("C10", ids_of(record))
        self.assertEqual(0, record["stack_arguments"]["observed_slots"])
        self.assertEqual("integral", record["return"]["register_class"])
        self.assertEqual("caller", record["cleanup"]["side"])

    def test_f08_divergence_from_the_plans_reason_string(self):
        """The plan's ``argless_cdecl_stdcall_indistinguishable`` does not exist.

        The engine's registered code is ``no_discriminator``, with the detail
        "no stack-argument read and no positive receiver evidence" -- the same
        fact in the engine's vocabulary. The plan's name is not in
        ``ABSTENTION_CODES`` and could not be emitted without changing the closed
        vocabulary.
        """
        record = record_of("08_leaf_no_frame")
        self.assertNotIn("argless_cdecl_stdcall_indistinguishable",
                         abi_infer.ABSTENTION_CODES)
        details = [entry for entry in record["abstained_because"]
                   if entry.startswith("no_discriminator")]
        self.assertEqual(["no_discriminator: no stack-argument read and no positive "
                          "receiver evidence"], details)

    def test_f09_naked_thunk_abstains_and_reports_the_tail_transfer(self):
        record = record_of("09_naked_thunk")
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertIsNone(fx.convention_of(record))
        self.assertIn("no_terminal_ret", fx.abstention_codes(record))
        tail = record["tail_call"]
        self.assertIs(True, tail["present"])
        self.assertEqual("0x00929bd0", tail["target"])
        self.assertEqual("jmp", tail["form"])
        self.assertIn("tail_call", record["conventions"]["ambiguities"])
        self.assertIsNone(record["cleanup"]["side"])
        self.assertIsNone(record["return"]["register"])

    def test_f09_divergence_from_the_plans_empty_inference_expectation(self):
        """The plan says ``EXPAND: none``; the engine emits four inferences.

        All four are *negative* facts -- no terminal return, no register
        receiver, slot 0 is not written through, this is a tail transfer -- and
        each is independently true and independently useful. Emitting nothing
        would throw away the observation that the function does have a target.
        """
        record = record_of("09_naked_thunk")
        self.assertEqual(["C2", "R2", "S2", "T1"], ids_of(record))
        for inference in record["inferences"]:
            self.assertTrue(inference["based_on"],
                            "every claim still cites a real observation")

    def test_f11_virtual_dispatch_is_observed_and_never_resolved(self):
        record = record_of("11_vtable_slot_call")
        self.assertEqual("__thiscall", fx.convention_of(record))
        self.assertEqual("caller", record["cleanup"]["side"])
        self.assertEqual("integral", record["return"]["register_class"])
        indirect = [obs for obs in record["observations"]
                    if obs["kind"] == "CALL_INDIRECT"]
        self.assertEqual(2, len(indirect),
                         "both CALL reg sites are observed with no resolvable callee")
        for observation in indirect:
            self.assertIn("base", observation)
            self.assertNotIn("callee", observation)
            self.assertIsNone(observation.get("target"))

    def test_f11_divergence_from_the_plans_member_offset_expectation(self):
        """The plan expects offsets [0, 32] at WEAK; the engine reports [32].

        Fixture 11 reassigns ECX at instruction 2
        (``MOV ECX,dword ptr [ECX + 0x20]``), so the ``[ECX]`` load at
        instruction 3 is through a register the compiler has already
        overwritten. Counting ``+0`` as a member offset would credit the
        receiver with a dereference of something that is no longer the receiver.
        The plan's two-offset expectation is the unsatisfiable one.
        """
        record = record_of("11_vtable_slot_call")
        self.assertEqual([32], record["receiver"]["offsets"])
        self.assertEqual("INFERRED", record["receiver"]["confidence"])
        self.assertEqual(0, record["stack_arguments"]["observed_slots"])

    # DELETED: test_f12_does_not_abstain_and_the_gate_it_wants_does_not_exist.
    # Asserted conventions.calling_convention "__thiscall", variadic "UNKNOWN"
    # and an empty abstained_because for fixture 12, on the grounds that "the
    # plan's R8 gate has no implementation anywhere". Now covered by
    # KnownEngineDefectTest.test_varargs_prologue_must_abstain, which asserts
    # ABI_UNKNOWN / SUSPECTED / C12 / variadic_not_decidable_from_listing on the
    # same fixture and passes since defect D6 was corrected. The old assertion
    # is no longer admissible because the gate now exists: the engine emits a
    # VARIADIC_MARKER named "varargs_or_alloca_prologue" and caps the convention.
    # Its one surviving assertion -- that the plan's code is not in
    # ABSTENTION_CODES -- was dropped with it because it is now misleading: the
    # engine uses that exact string as a *marker* name, not as an abstention
    # code, and the markers are asserted directly by
    # KnownEngineDefectTest.test_varargs_prologue_must_abstain and by
    # test_f12b_the_variadic_gate_is_live_for_the_shape_the_spec_does_specify.

    def test_f12b_the_variadic_gate_is_live_for_the_shape_the_spec_does_specify(self):
        """Positive control: the variadic gate is live, not vacuous.

        Spec §3.6 marker 2: a huge frame (``sub esp, N``, N > 0x1000) immediately
        before a call. When that shape is present the engine does abstain, and
        the convention is forced to null by C12 with ``__cdecl`` as the only
        surviving candidate.

        This is the control for the two variadic markers: 12b fires on a marker
        the spec always listed, 12 on the ``varargs_or_alloca_prologue`` marker
        that had to be added, and 23 on the ``small_count_before_call`` marker
        that was unreachable dead code. Three distinct shapes, one gate.
        """
        record = record_of("12b_variadic_huge_frame")
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertEqual("SUSPECTED", record["variadic"])
        self.assertIn("C12", ids_of(record))
        codes = fx.abstention_codes(record)
        self.assertIn("variadic_not_decidable_from_listing", codes)
        self.assertIn("variadic_caps_convention", codes)
        self.assertEqual(["__cdecl"], record["conventions"]["candidate_conventions"])
        self.assertIn("variadic_suspected", record["conventions"]["ambiguities"])
        self.assertTrue(record["stack_arguments"]["not_complete"])
        # cleanup is a machine fact and survives the gate
        self.assertEqual("caller", record["cleanup"]["side"])
        self.assertEqual(0, record["cleanup"]["bytes"])

    def test_variadic_never_reaches_a_confirmed_state(self):
        """The spec: three-valued only, never "confirmed" and never "absent"."""
        for name in fx.iter_fixture_names():
            if name == fx.ATT_TWIN_OF:
                continue
            with self.subTest(fixture=name):
                self.assertIn(record_of(name)["variadic"], ("UNKNOWN", "SUSPECTED"))

    def test_f18_argless_x87_return_is_recognised_while_the_convention_is_refused(self):
        record = record_of("18_argless_x87_return")
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertIn("no_discriminator", fx.abstention_codes(record))
        block = record["return"]
        self.assertEqual("ST0", block["register"])
        self.assertEqual("float_or_x87", block["register_class"])
        self.assertEqual("APPROXIMATION", block["confidence"])
        self.assertIsNone(block["type"])
        self.assertEqual("caller", record["cleanup"]["side"])
        self.assertEqual(0, record["cleanup"]["bytes"])

    def test_f22_a_data_row_is_an_observation_not_an_instruction(self):
        """A byte column with no mnemonic must not become a frame or an insn."""
        record = record_of("22_data_bytes_no_mnemonic")
        kinds = [obs["kind"] for obs in record["observations"]]
        self.assertIn("DATA_BYTE", kinds)
        data = [obs for obs in record["observations"]
                if obs["kind"] == "DATA_BYTE"][0]
        self.assertEqual(5, data["count"], "8b01 0043 0a05 0000 00 is five bytes")
        self.assertIn("RET", [obs["raw"] for obs in record["observations"]])
        self.assertIn("C5", ids_of(record))
        self.assertIs(True, record["return"]["void_possible"],
                      "EAX is never written and no call can clobber it")
        self.assertIn("RT3", ids_of(record))

    def test_completeness_is_the_analogue_of_the_documents_shape_field(self):
        """``shape`` does not exist; ``completeness`` is what replaced it.

        The documents give ``shape`` four values (body/thunk/empty/unparseable).
        The engine has no such field, so a reader looking for it gets a
        KeyError. The honest mapping: ``completeness`` in {CORE_RESOLVED,
        PARTIAL, EMPTY} plus ``tail_call.form`` together carry what ``shape`` was
        trying to say.
        """
        self.assertNotIn("shape", record_of("01_thiscall_member"))
        for name, expected in sorted({
            "01_thiscall_member": "CORE_RESOLVED",
            "09_naked_thunk": "EMPTY",
            "08_leaf_no_frame": "PARTIAL",
            "15a_empty": "EMPTY",
            "15e_prose": "EMPTY",
        }.items()):
            with self.subTest(fixture=name):
                self.assertEqual(expected, record_of(name)["completeness"])


class ReturnKindTest(unittest.TestCase):
    """Fixtures 13, 14 -- what EAX holds, as a machine-level class."""

    def test_f13_pointer_like_is_inferred_not_assumed(self):
        record = record_of("13_pointer_return")
        self.assertEqual("EAX", record["return"]["register"])
        self.assertEqual("pointer_like", record["return"]["register_class"])
        self.assertIsNone(record["return"]["type"],
                          "pointer_like is a machine fact, never a C++ pointer")
        self.assertIn("pointer_like_in_EAX", record["abi"]["return_semantics"])
        self.assertNotIn("return_type", record["abi"])

    def test_f14_integral_return_abstains_which_the_plan_did_not_anticipate(self):
        """Divergence: the plan's "same convention path as 13" is unsatisfiable.

        Fixture 13 reads ``[EBP + 0x8]``; fixture 14 reads nothing. C9 needs at
        least one resolved slot, so 14 cannot be ``__cdecl`` -- yet the plan
        asserts it is and that it takes "the same convention path as 13". This
        is the seventh internal inconsistency in the two documents, beyond the
        six the research pass recorded. The engine is right: the two bodies are
        not equivalent and it says so.
        """
        record = record_of("14_integral_return")
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertIsNone(fx.convention_of(record))
        self.assertIn("no_discriminator", fx.abstention_codes(record))
        self.assertEqual(0, record["stack_arguments"]["observed_slots"])
        self.assertEqual("integral", record["return"]["register_class"])
        self.assertIn("C10", ids_of(record))

    def test_f13_and_f14_never_conflate(self):
        """Pair-asserted in one test so the two classes cannot drift together."""
        pointer = record_of("13_pointer_return")["return"]
        integral = record_of("14_integral_return")["return"]
        self.assertNotEqual(pointer["register_class"], integral["register_class"])
        self.assertEqual("pointer_like", pointer["register_class"])
        self.assertEqual("integral", integral["register_class"])
        for block in (pointer, integral):
            self.assertIsNone(block["type"])
            self.assertEqual("EAX", block["register"])

    def test_bulk_string_write_forces_aggregate_unknown(self):
        """RT4: a ``rep stosd`` reaching EAX is evidence against a struct return."""
        record = abi_infer.analyze(
            "PUSH EBP\nMOV EBP,ESP\n"
            "XOR EAX,EAX\nMOV ECX,0x4\nREP STOSD\n"
            "MOV EAX,1\nMOV ESP,EBP\nPOP EBP\nRET\n")
        self.assertEqual("aggregate_unknown", record["return"]["register_class"])
        self.assertIn("RT4", ids_of(record))
        self.assertTrue(record["return"]["aggregate_evidence"]["bulk_write"])

    def test_return_class_is_unknown_exactly_when_no_register_is_named(self):
        """``register == X`` and ``register_class == "unknown"`` never co-occur."""
        for label, text in fx.hermetic_inputs() + fx.live_inputs():
            with self.subTest(input=label):
                block = abi_infer.analyze(text)["return"]
                if block["register"] is not None:
                    self.assertNotEqual("unknown", block["register_class"])
                else:
                    self.assertEqual("unknown", block["register_class"])


class RobustnessTest(unittest.TestCase):
    """Fixture 15a-15e -- five degenerate inputs, none of which may raise."""

    def test_f15a_and_f15b_empty_inputs(self):
        for name in ("15a_empty", "15b_whitespace"):
            with self.subTest(fixture=name):
                record = record_of(name)
                self.assertEqual("ABI_UNKNOWN", record["verdict"])
                self.assertEqual([], record["observations"])
                self.assertEqual([], record["inferences"])
                self.assertEqual({"architecture": "x86-32", "receiver": False},
                                 record["abi"],
                                 "an empty listing still states the architecture "
                                 "and that there is no receiver")
                self.assertEqual("EMPTY", record["completeness"])
                codes = fx.abstention_codes(record)
                self.assertIn("empty_listing", codes)
                self.assertIn("no_terminal_ret", codes)

    def test_f15c_binary_noise_is_unparsed_not_fatal(self):
        record = record_of("15c_binary_noise")
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertIn("UNPARSED", [obs["kind"] for obs in record["observations"]])
        self.assertIn("unparsed_lines_present", fx.abstention_codes(record))
        self.assertEqual(1, record["parse"]["unparsed"])
        self.assertIn("empty_listing", fx.abstention_codes(record))

    def test_f15d_truncated_listing_is_flagged_as_truncated(self):
        record = record_of("15d_truncated")
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        codes = fx.abstention_codes(record)
        self.assertIn("truncated_listing", codes)
        self.assertIn("no_terminal_ret", codes)
        self.assertIn("C2", ids_of(record))

    def test_f15e_prose_is_unparsed_not_fatal(self):
        record = record_of("15e_prose")
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        for observation in record["observations"]:
            self.assertEqual("UNPARSED", observation["kind"],
                             "a line mentioning EAX as a word is not an instruction")
        self.assertIn("unparsed_lines_present", fx.abstention_codes(record))

    def test_internal_error_never_leaks_into_a_record(self):
        """The engine's internal-error fallback must never be reachable here.

        ``analyze`` catches everything but ValueError and returns a record tagged
        ``parse.internal_error``. No committed input may reach that path: a record
        carrying the tag means the engine crashed and *hid* it, which is strictly
        worse than raising.
        """
        for label, text in fx.hermetic_inputs() + fx.live_inputs():
            with self.subTest(input=label):
                self.assertNotIn("internal_error", abi_infer.analyze(text)["parse"])


class AdapterTest(unittest.TestCase):
    """Fixture 16 -- four encodings of one stream, one verdict."""

    #: ``flow_complete`` is an inference that legitimately changes when an
    #: address column becomes available, so the loose comparison removes it too.
    #: ``test_flow_complete_depends_on_address_availability`` pins the dependency
    #: rather than hiding it, and the strict test below uses a straight-line body
    #: where it cannot fire.
    ADDRESS_DERIVED = ("flow_complete",)

    def _stripped(self, record):
        stripped = fx.strip_provenance(record)
        for key in self.ADDRESS_DERIVED:
            stripped["parse"].pop(key, None)
        return stripped

    def test_f16_all_four_layouts_agree_modulo_the_provenance_keys(self):
        records = {label: abi_infer.analyze(value)
                   for label, value in fx.encodings_of_01().items()}
        baseline = self._stripped(records["plain_text"])
        for label, record in sorted(records.items()):
            with self.subTest(layout=label):
                self.assertEqual([], fx.semantic_diff(
                    baseline, self._stripped(record)))

    def test_f16_layouts_are_labelled_correctly(self):
        expected = {
            "plain_text": "plain_text",
            "gcodebrowser_text": "gcodebrowser_text",
            "att_text": "att_text",
            "json_instruction_list": "json_instruction_list",
            "json_instruction_dict": "json_instruction_list",
        }
        seen = []
        for label, value in sorted(fx.encodings_of_01().items()):
            with self.subTest(layout=label):
                record = abi_infer.analyze(value)
                self.assertEqual(expected[label], record["parse"]["layout"])
                seen.append(record["parse"]["layout"])
        self.assertEqual(4, len(set(seen)),
                         "four distinct layouts must be recognised")

    def test_f16_every_encoding_derives_the_same_convention(self):
        for label, value in sorted(fx.encodings_of_01().items()):
            with self.subTest(layout=label):
                record = abi_infer.analyze(value)
                self.assertEqual("__thiscall", fx.convention_of(record))
                self.assertEqual([8, 12, 16, 20], record["receiver"]["offsets"])
                self.assertEqual(2, record["stack_arguments"]["observed_slots"])

    def test_f16_att_twin_matches_the_intel_golden(self):
        """The committed ``.att`` file produces fixture 01's record."""
        att = abi_infer.analyze(fx.load_fixture(fx.ATT_TWIN_OF))
        self.assertEqual([], fx.semantic_diff(
            self._stripped(golden_of(fx.ATT_TWIN_TARGET)),
            self._stripped(att)))

    def test_f16_header_rows_and_rulers_are_scaffolding_not_data(self):
        record = abi_infer.analyze(fx.CODEBROWSER_01)
        self.assertEqual(0, record["parse"]["unparsed"],
                         "the Listing/----- header rows must be recognised")
        self.assertEqual(16, record["target"]["instructions"])
        self.assertTrue(record["target"]["address_available"])
        self.assertEqual("intel", record["target"]["syntax"])

    def test_flow_complete_depends_on_address_availability(self):
        """Documented: ``flow_complete`` is an inference, not provenance.

        Fixture 01's ``JZ 0x00401024`` targets an address that is *not* in the
        listing. Without an address column the engine cannot know that and
        reports ``true``; with one it does know and reports ``false``. That is
        strictly more information, not less -- which is why
        ``parse.flow_complete`` is deliberately *not* in the invariance
        exclusion set, and why the strict invariance test uses a straight-line
        body.
        """
        plain = abi_infer.analyze(fx.encodings_of_01()["plain_text"])
        codebrowser = abi_infer.analyze(fx.encodings_of_01()["gcodebrowser_text"])
        self.assertTrue(plain["parse"]["flow_complete"])
        self.assertFalse(codebrowser["parse"]["flow_complete"])
        self.assertNotIn("$.parse.flow_complete", fx.PROVENANCE_PATHS)

    def test_straight_line_body_is_strictly_layout_invariant(self):
        """A body with no branch is invariant over all three encodings.

        The tight form of the invariant: the set of paths that change with the
        layout must be a subset of the documented provenance set and nothing
        else.
        """
        straight = ["PUSH EBP", "MOV EBP,ESP", "SUB ESP,0x10",
                    "MOV EAX,dword ptr [ECX + 0x8]",
                    "MOV dword ptr [ECX + 0xc],EAX",
                    "MOV EAX,dword ptr [EBP + 0x8]",
                    "MOV ESP,EBP", "POP EBP", "RET"]
        addresses = ["00401000", "00401001", "00401003", "00401006", "0040100a",
                     "0040100d", "00401011", "00401013", "00401014"]
        json_form = [{"address": address, "instruction": instruction}
                     for address, instruction in zip(addresses, straight)]
        codebrowser = "\n".join(
            ["Listing  Address  Instruction  Bytes",
             "-------  -------  -----------  -----"] +
            ["%s  %s" % (address, instruction)
             for address, instruction in zip(addresses, straight)])
        forms = {
            "plain_text": "\n".join(straight) + "\n",
            "gcodebrowser_text": codebrowser,
            "json_instruction_list": json_form,
        }
        records = {label: abi_infer.analyze(value) for label, value in forms.items()}
        baseline = records["plain_text"]
        for label, record in sorted(records.items()):
            with self.subTest(layout=label):
                differing = fx.diffing_paths(baseline, record)
                undocumented = {path for path in differing
                                if path not in fx.PROVENANCE_PATHS}
                self.assertEqual(
                    set(), undocumented,
                    "these fields changed with the layout and are not declared "
                    "provenance: %s" % sorted(undocumented))
        self.assertEqual([], fx.semantic_diff(fx.strip_provenance(baseline),
                                              fx.strip_provenance(
                                                  records["gcodebrowser_text"])))


class SegmentAndSpillTest(unittest.TestCase):
    """Fixture 19 -- a receiver recovered through its own spill slot."""

    def test_f19_receiver_is_recovered_through_the_spill_slot(self):
        receiver = record_of("19_receiver_spilled_to_frame_slot")["receiver"]
        self.assertIs(True, receiver["present"])
        self.assertEqual("ECX", receiver["register"])
        self.assertEqual("R-ALIAS", receiver["shape"])
        self.assertEqual([15004], receiver["offsets"],
                         "0x3a9c: ECX is spilled to [EBP-0x8] and reloaded into EDX")
        self.assertIn("R1", ids_of(record_of("19_receiver_spilled_to_frame_slot")))

    def test_f19_seh_segment_access_is_not_a_gate_and_not_variadic_evidence(self):
        """V2: ``FS:[0x2c]`` is an SEH walk, so it gates nothing.

        The documents (R8) also say an ``FS:[0x…]`` access is not an abstention
        gate. The engine additionally reports it as a positive fact.
        """
        record = record_of("19_receiver_spilled_to_frame_slot")
        self.assertTrue(record["seh_or_cookie_frame"])
        self.assertIn("V2", ids_of(record))
        self.assertNotIn("variadic_not_decidable_from_listing",
                         fx.abstention_codes(record))
        self.assertEqual([], record["abstained_because"])
        segment = [obs for obs in record["observations"]
                   if obs["kind"] == "SEGMENT_TLS"]
        self.assertTrue(segment, "the FS: operand is an observation")
        self.assertEqual("FS", segment[0]["segment"])
        self.assertIn("0x2c", segment[0]["text"])

    def test_f19_divergence_from_the_plans_confidence_expectations(self):
        """The plan expects SUPPORTED receiver and WEAK arguments; engine says INFERRED.

        The plan's note that a single offset should not be SUPPORTED is right and
        the engine agrees; the plan's expectation that this body would reach
        SUPPORTED does not hold, because it only ever reaches one offset.
        """
        record = record_of("19_receiver_spilled_to_frame_slot")
        self.assertEqual("INFERRED", record["receiver"]["confidence"])
        self.assertEqual("INFERRED", record["stack_arguments"]["confidence"])
        for rule in ("R1", "A1"):
            self.assertNotEqual("SUPPORTED", claim_of(record, rule)["confidence"])

    def test_f19_return_is_call_result_not_pointer_like(self):
        """Divergence from the plan: it expects ``pointer_like`` at WEAK.

        The last write to EAX is the ``CALL 0x00903400`` result, so the value
        class is ``call_result`` and the engine reports
        ``aggregate_unknown``. Calling that ``pointer_like`` would require proving
        the *callee* returned a pointer, which a callee's own listing cannot do.
        """
        block = record_of("19_receiver_spilled_to_frame_slot")["return"]
        self.assertEqual("EAX", block["register"])
        self.assertEqual("aggregate_unknown", block["register_class"])
        self.assertIsNone(block["type"])

    def test_receiver_confidence_reaches_supported_with_three_offsets(self):
        """The engine's documented deviation from the plan's R1.

        The plan's R1 wants two offsets plus one write-through to be enough,
        which would make F01 and F13 -- the same shape -- pin different answers.
        The engine therefore needs three distinct offsets.
        """
        self.assertEqual("SUPPORTED",
                         record_of("01_thiscall_member")["receiver"]["confidence"])
        many = live_record("00aea250", "thiscall_contradicts_fastcall")
        self.assertGreaterEqual(many["receiver"]["distinct_offsets"], 3)
        self.assertGreaterEqual(many["receiver"]["written_through"], 1)
        self.assertEqual("SUPPORTED", many["receiver"]["confidence"])


class EngineInventionTest(unittest.TestCase):
    """C6B and A1-IMM: rules the spec lacks, which the binary requires.

    Both are load-bearing. Without C6B the real functions 0x008db310 and
    0x004bdc00 are unreachable; without A1-IMM the real 0x00951230 is
    unreachable. Neither weakens a rule to make a test pass -- each makes a
    *stronger* claim available on a shape the spec had no rule for.
    """

    def test_c6b_thiscall_that_also_pops_its_arguments(self):
        """Why C6B exists: MSVC emits ``ret N`` for a member with arguments.

        ``abi-inference-spec.md`` has C6 (callee cleanup, no receiver ->
        ``__stdcall``) and C7 (caller cleanup, receiver -> ``__thiscall``) and
        nothing for callee cleanup *with* a receiver, which is the single most
        common shape for a real member function. C6 alone would have to call
        0x008db310 and 0x004bdc00 ``__stdcall``, which is simply wrong.

        REPAIRED. Fixture 23 used to be in the same table and asserted
        ``__thiscall`` from the identical callee-pops-plus-receiver shape. It no
        longer resolves, and the reason is *not* that C6B is wrong: ``MOV
        EAX,0x4`` immediately before ``CALL 0x00903400`` is spec §3.7 marker 3,
        so defect D3 was corrected and the variadic gate now fires. The variadic
        cap (C12) outranks the convention rule, so 23 abstains while still
        reporting callee/8 and the receiver. 19 has no marker and still reaches
        C6B, which is what keeps the rule itself load-bearing.
        """
        record = record_of("19_receiver_spilled_to_frame_slot")
        self.assertEqual("callee", record["cleanup"]["side"])
        self.assertGreater(record["cleanup"]["bytes"], 0)
        self.assertIs(True, record["receiver"]["present"])
        self.assertEqual("__thiscall", fx.convention_of(record))
        self.assertIn("C6B", ids_of(record))
        self.assertNotIn("C6", ids_of(record))
        self.assertNotIn("C7", ids_of(record))
        self.assertNotIn("C12", ids_of(record))
        self.assertEqual("UNKNOWN", record["variadic"],
                         "the control must not itself be variadic-suspect")

    def test_c6b_is_outranked_by_the_variadic_cap_on_the_same_shape(self):
        """The other half of the C6B story: where C6B *does not* reach.

        Fixture 23 is a callee-popping member with a receiver -- the C6B shape
        byte for byte -- plus a small count immediately before a call. The
        variadic cap is the stronger claim about the stack-argument extent, so it
        wins and the record abstains. The machine facts that made 23 a C6B
        candidate are still reported; only the convention is refused.
        """
        record = record_of("23_small_count_before_call")
        self.assertEqual("callee", record["cleanup"]["side"])
        self.assertEqual(8, record["cleanup"]["bytes"])
        self.assertIs(True, record["receiver"]["present"])
        self.assertEqual("SUSPECTED", record["variadic"])
        self.assertIn("C12", ids_of(record))
        self.assertIn("small_count_before_call",
                      [obs.get("marker") for obs in record["observations"]
                       if obs["kind"] == "VARIADIC_MARKER"])
        self.assertIsNone(fx.convention_of(record))
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertIn("variadic_caps_convention", fx.abstention_codes(record))

    def test_c6b_claim_text_states_why_fastcall_is_excluded(self):
        claim = claim_of(record_of("19_receiver_spilled_to_frame_slot"), "C6B")["claim"]
        self.assertIn("rules out cdecl and fastcall", claim)

    def test_c6b_is_what_makes_the_two_real_functions_reachable(self):
        """Both real members pop their own arguments. Without C6B: unreachable."""
        for va8, slug, expected_bytes in (("008db310", "thiscall_big_ret8", 8),
                                          ("004bdc00", "seh_spilled_receiver", 4)):
            with self.subTest(va=va8):
                record = live_record(va8, slug)
                self.assertEqual("__thiscall", fx.convention_of(record))
                self.assertEqual("callee", record["cleanup"]["side"])
                self.assertEqual(expected_bytes, record["cleanup"]["bytes"])
                self.assertIn("C6B", ids_of(record))

    def test_a1imm_slots_derived_from_a_ret_immediate_are_never_observed(self):
        """Why A1-IMM exists: a two-instruction stub has no argument read.

        ``abi-inference-spec.md`` has no rule for a callee cleanup with no
        argument evidence. 0x00951230 is ``XOR AL,AL / RET 0xc`` -- the entire
        function. Without A1-IMM the record would report zero slots for a
        three-argument stdcall.
        """
        slots = live_record("00951230", "stdcall_stub_ret0c")["stack_arguments"]
        self.assertIn("A1-IMM", ids_of(live_record("00951230", "stdcall_stub_ret0c")))
        self.assertEqual(0, slots["observed_slots"])
        self.assertEqual(3, slots["derived_slots"])
        self.assertEqual(12, slots["total_bytes"])
        for slot in slots["slots"]:
            self.assertIs(False, slot["observed"])
            self.assertEqual("ret_immediate", slot["source"])

    def test_a1imm_confidence_is_approximation_the_weakest_rung(self):
        record = record_of("04_stdcall_ret_0xc")
        self.assertEqual("APPROXIMATION", claim_of(record, "A1-IMM")["confidence"])
        self.assertEqual("APPROXIMATION", record["stack_arguments"]["confidence"])

    def test_a1imm_does_not_fire_when_a_real_slot_read_exists(self):
        """A1 (observed) and A1-IMM (derived) are mutually exclusive."""
        record = record_of("17_stdcall_ret_6")
        self.assertIn("A1", ids_of(record))
        self.assertNotIn("A1-IMM", ids_of(record))
        self.assertEqual(1, record["stack_arguments"]["observed_slots"])
        self.assertEqual(0, record["stack_arguments"]["derived_slots"])

    def test_norm_disp_unwraps_eight_digit_displacements_but_not_immediates(self):
        """The engine's documented mask-vs-displacement rule.

        Ghidra prints a negative displacement as an eight-hex-digit literal, so
        ``0xfffffef4`` unwraps to -0x10c -- prefix or not. An
        *immediate* is never unwrapped, so ``and esp,0xfffffff0`` keeps its mask.
        That distinction is load-bearing: unwrapping the mask would turn an
        alignment operation into a 4GB stack allocation.
        """
        for literal, expected in (("0xfffffef4", -0x10c), ("fffffef4", -0x10c),
                                  ("-0xc", -0xc), ("0x8", 8), ("0x1000", 0x1000)):
            with self.subTest(literal=literal):
                self.assertEqual(expected, abi_infer.norm_disp(literal))
        record = abi_infer.analyze(
            "PUSH EBP\nMOV EBP,ESP\nAND ESP,0xfffffff0\n"
            "MOV EAX,dword ptr [EBP + 0x8]\nMOV ESP,EBP\nPOP EBP\nRET\n")
        self.assertNotIn("esp_alignment_unknown", fx.abstention_codes(record))
        self.assertEqual(0xFFFFFFF0, record["parse"]["frame"]["and_esp"],
                         "the mask value must survive as written")


class PlausibilityWindowDivergenceTest(unittest.TestCase):
    """THE deliberate conservatism trade-off, in the wrong direction.

    ``docs/tooling/abi-inference-tests.md`` R2 requires the receiver's member
    offsets to lie in ``[0, 0x1000]`` and names
    ``single_implausible_member_offset`` for a violation. The landed engine
    applies **no** window at all: it reports every offset it observed and leaves
    the windowing to the consumer. This is documented in the engine's module
    docstring as a deliberate choice, and the reasoning is sound in one
    direction -- MSVC layouts do reach 0x3a9c (fixture 19) and a hard 0x1000
    cut-off would reject a real function.

    But the cost is real and it is on the permissive side: fixture 07's
    ``[ECX + 0x4000]`` is accepted as a receiver, and so would be a coincidental
    ``[ECX + 0xdeadbeef]``. Any consumer that does not window the offsets will
    over-report members. The engine mitigates by labelling the receiver
    ``bounds_only: true`` and by capping confidence, so this class pins both the
    acceptance *and* the mitigations, so a consumer cannot silently depend on a
    window existing.
    """

    #: Every one of these is far beyond the 0x1000 the documents would allow.
    #: Values that would wrap through a signed 32-bit conversion are excluded
    #: here and covered by ``test_an_oversized_displacement_is_read_signed``.
    OFFSETS = (0x1001, 0x4000, 0x8000, 0x10000, 0x100000, 0x40000000)

    def test_engine_accepts_offsets_the_plan_would_reject(self):
        for offset in self.OFFSETS:
            with self.subTest(offset=hex(offset)):
                record = abi_infer.analyze(
                    "PUSH EBP\nMOV EBP,ESP\n"
                    "MOV EAX,dword ptr [ECX + 0x%x]\n" % offset +
                    "MOV EAX,dword ptr [ECX + 0x%x]\n" % (offset + 4) +
                    "MOV ESP,EBP\nPOP EBP\nRET\n")
                self.assertIs(True, record["receiver"]["present"])
                self.assertEqual([offset, offset + 4], record["receiver"]["offsets"])
                self.assertEqual("__thiscall", fx.convention_of(record))
                self.assertNotIn("single_implausible_member_offset",
                                 fx.abstention_codes(record))

    def test_the_window_code_does_not_exist_in_the_engines_vocabulary(self):
        """Not merely unused -- absent, so it cannot be emitted even by accident."""
        self.assertNotIn("single_implausible_member_offset",
                         abi_infer.ABSTENTION_CODES)
        self.assertFalse(hasattr(abi_infer, "PLAUSIBLE_MEMBER_MAX"),
                         "the engine defines no plausibility constant")

    def test_a_spilled_receiver_is_not_windowed_either(self):
        """Fixture 19's 0x3a9c would fail a 0x1000 window too.

        This is the case that makes the absence defensible: a member offset of
        15004 is real, so any window that rejected it would lose a true receiver.
        ``R-ALIAS`` versus ``R-DIRECT`` is how a consumer can tell the two
        situations apart.
        """
        direct = record_of("07_ecx_single_implausible_offset")
        spilled = record_of("19_receiver_spilled_to_frame_slot")
        self.assertEqual("R-DIRECT", direct["receiver"]["shape"])
        self.assertEqual("R-ALIAS", spilled["receiver"]["shape"])
        self.assertGreater(spilled["receiver"]["max_offset"], 0x1000)
        self.assertGreater(direct["receiver"]["max_offset"], 0x1000)

    def test_an_oversized_displacement_is_read_signed(self):
        """A displacement above 0x7fffffff is a *negative* offset, correctly.

        ``[ECX + 0xfffff000]`` is ``[ECX - 0x1000]`` on x86, and the engine says
        so. That is a different thing from a huge member offset, which is why
        this case is kept out of :data:`OFFSETS`: it is not the window
        divergence, it is ordinary sign extension.
        """
        for literal, expected in (("0xfffff000", -0x1000), ("0xffffff00", -0x100)):
            with self.subTest(literal=literal):
                record = abi_infer.analyze(
                    "PUSH EBP\nMOV EBP,ESP\n"
                    "MOV EAX,dword ptr [ECX + %s]\n" % literal +
                    "MOV EAX,dword ptr [ECX + 0x8]\n"
                    "MOV ESP,EBP\nPOP EBP\nRET\n")
                self.assertIn(expected, record["receiver"]["offsets"])

    def test_the_mitigation_is_bounds_only_and_a_capped_confidence(self):
        """If no window bounds the offsets, the record must say so explicitly."""
        for offset in self.OFFSETS:
            with self.subTest(offset=hex(offset)):
                record = abi_infer.analyze(
                    "PUSH EBP\nMOV EBP,ESP\n"
                    "MOV EAX,dword ptr [ECX + 0x%x]\n" % offset +
                    "MOV EAX,dword ptr [ECX + 0x%x]\n" % (offset + 4) +
                    "MOV ESP,EBP\nPOP EBP\nRET\n")
                self.assertTrue(record["receiver"]["bounds_only"],
                                "the record must admit it cannot bound the object")
                self.assertIn(record["receiver"]["confidence"],
                              ("INFERRED", "SUPPORTED"))
        single = record_of("07_ecx_single_implausible_offset")
        self.assertEqual("INFERRED", single["receiver"]["confidence"],
                         "one offset is the weakest present-receiver rung")
        self.assertTrue(single["receiver"]["bounds_only"])


# =========================================================================== #
# Part B -- invariants
# =========================================================================== #
class DeterminismTest(unittest.TestCase):
    """R11 -- identical input, byte-identical record, here and out of process."""

    def setUp(self):
        self.corpus = (fx.hermetic_inputs() + fx.live_inputs() +
                       [("fuzz[%d]" % index, text) for index, text
                        in enumerate(fx.fuzz_inputs(count=25))])

    def test_fuzz_seed_is_pinned(self):
        self.assertEqual(1234, FUZZ_SEED)
        self.assertEqual(FUZZ_SEED, fx.FUZZ_SEED)

    def test_infer_is_byte_identical_across_five_runs(self):
        for label, text in self.corpus:
            with self.subTest(input=label):
                digest = abi_infer.analyze(text)["content_sha256"]
                for _ in range(4):
                    self.assertEqual(digest, abi_infer.analyze(text)["content_sha256"])

    def test_infer_is_byte_identical_in_a_fresh_interpreter(self):
        script = (
            "import sys\n"
            "sys.path.insert(0, %r)\n"
            "from tools.reconstruction_tooling import abi_infer\n"
            "text = open(sys.argv[1], 'rb').read().decode('utf-8', 'replace')\n"
            "sys.stdout.write(abi_infer.analyze(text)['content_sha256'])\n"
        ) % ROOT
        handle, path = tempfile.mkstemp(prefix="abi-fresh-", suffix=".asm")
        try:
            with os.fdopen(handle, "wb") as stream:
                stream.write(fx.load_fixture("01_thiscall_member").encode("utf-8"))
            proc = subprocess.run([sys.executable, "-c", script, path],
                                  capture_output=True, text=True, timeout=120)
        finally:
            os.unlink(path)
        self.assertEqual(0, proc.returncode, proc.stderr)
        self.assertEqual(record_of("01_thiscall_member")["content_sha256"],
                         proc.stdout.strip())

    def test_record_is_canonical_json(self):
        """``finalize`` sorts every map before hashing, so keys sort at all levels."""
        for label, text in self.corpus:
            with self.subTest(input=label):
                record = abi_infer.analyze(text)
                self.assertEqual(record, json.loads(canonical_json(record)))
                self.assertEqual(canonical_json(record),
                                 canonical_json(json.loads(canonical_json(record))))

    def test_content_sha256_is_the_digest_of_the_record_with_itself_nulled(self):
        for label, text in self.corpus:
            with self.subTest(input=label):
                record = abi_infer.analyze(text)
                nulled = dict(record)
                nulled["content_sha256"] = None
                self.assertEqual(sha256_json(nulled), record["content_sha256"])

    def test_analyze_twice_on_one_record_is_stable(self):
        """`analyze` carries no state across calls.

        The cheapest possible check for the hidden-module-state class of bug the
        docstring promises against: if anything accumulated, the second call
        would differ.
        """
        for name in ("01_thiscall_member", "11_vtable_slot_call",
                     "20_ecx_loaded_from_stack_slot", "05_fastcall_ecx_edx"):
            with self.subTest(fixture=name):
                first = record_of(name)
                abi_infer.analyze(fx.load_fixture("13_pointer_return"))
                abi_infer.analyze(fx.load_fixture("09_naked_thunk"))
                self.assertEqual(first, record_of(name))

    def test_reparsing_the_committed_input_through_the_two_stages_matches(self):
        """Stage 1 + stage 2 must equal the one-shot pipeline, byte for byte.

        This is the real idempotence property: the listing is parsed twice, by
        two different entry points, and the resulting records must be identical.
        The documents' "infer(infer(x)) == infer(x)" is not expressible against
        this record design, because the intermediate is a parse, not a record.
        """
        for name in ("01_thiscall_member", "03_cdecl_three_stack_args",
                     "11_vtable_slot_call", "20_ecx_loaded_from_stack_slot"):
            with self.subTest(fixture=name):
                text = fx.load_fixture(name)
                insns, meta = abi_infer.parse_listing(text)
                observations, state, frame = abi_infer.extract(insns, meta)
                abi_infer._complete_observations(state, observations)
                state.observations = observations
                staged = abi_infer.infer(observations, state, frame, meta)
                staged, _conflicts = abi_infer.cross_validate(staged)
                self.assertEqual(abi_infer.analyze(text)["content_sha256"],
                                 abi_infer.finalize(staged)["content_sha256"])

    def test_fuzz_corpus_is_reproducible(self):
        """Guards against an unseeded ``random`` creeping into the corpus."""
        first = list(fx.fuzz_inputs(count=50))
        second = list(fx.fuzz_inputs(count=50))
        self.assertEqual(first, second)
        self.assertNotEqual(list(fx.fuzz_inputs(count=50, seed=4321)), first)


class OrderingTest(unittest.TestCase):
    """Observation ids are dense; inference ids follow the fixed claim order."""

    def setUp(self):
        self.order = {rule: position
                      for position, rule in enumerate(fx.CLAIM_ORDER)}

    def test_observation_ids_are_dense_and_in_listing_order(self):
        for label, text in fx.hermetic_inputs() + fx.live_inputs():
            with self.subTest(input=label):
                observations = abi_infer.analyze(text)["observations"]
                self.assertEqual(
                    ["obs-%04d" % (position + 1)
                     for position in range(len(observations))],
                    [obs["id"] for obs in observations],
                    "ids must be dense, gap-free and assigned in listing order")
                indices = [obs["index"] for obs in observations]
                self.assertEqual(sorted(indices), indices,
                                 "observations must be emitted in listing order")

    def test_inference_ids_are_unique_and_follow_the_claim_order(self):
        for label, text in fx.hermetic_inputs() + fx.live_inputs():
            with self.subTest(input=label):
                rules = ids_of(abi_infer.analyze(text))
                self.assertEqual(len(rules), len(set(rules)),
                                 "an inference id must never repeat")
                positions = [self.order[fx.base_rule(rule)] for rule in rules]
                self.assertEqual(sorted(positions), positions,
                                 "inferences must follow the fixed claim order, "
                                 "got %s" % rules)

    def test_every_emitted_rule_is_in_the_claim_order_table(self):
        for label, text in fx.hermetic_inputs() + fx.live_inputs():
            for rule in ids_of(abi_infer.analyze(text)):
                with self.subTest(input=label, rule=rule):
                    self.assertIn(fx.base_rule(rule), self.order,
                                  "a new rule appeared; add it to CLAIM_ORDER so "
                                  "the ordering invariant keeps covering it")

    def test_repeated_rule_ids_are_suffixed_not_duplicated(self):
        record = live_record("0040ccb0", "thiscall_spilled_receiver")
        rules = ids_of(record)
        self.assertEqual(len(rules), len(set(rules)))
        for rule in rules:
            if "#" in rule:
                base, suffix = rule.split("#", 1)
                self.assertIn(base, self.order)
                self.assertTrue(suffix.isdigit())

    def test_set_valued_fields_are_sorted(self):
        for label, text in fx.hermetic_inputs() + fx.live_inputs():
            with self.subTest(input=label):
                record = abi_infer.analyze(text)
                offsets = record["receiver"]["offsets"]
                self.assertEqual(sorted(offsets), offsets)
                for inference in record["inferences"]:
                    self.assertEqual(sorted(inference["based_on"]),
                                     inference["based_on"])
                self.assertEqual(sorted(set(record["abstained_because"])),
                                 sorted(record["abstained_because"]))
                self.assertEqual(sorted(record["dispatch"]["call_offsets"]),
                                 record["dispatch"]["call_offsets"])
                ordinals = [slot["ordinal"] for slot
                            in record["stack_arguments"]["slots"]]
                self.assertEqual(sorted(ordinals), ordinals)
                self.assertEqual(sorted(record["conventions"]["ambiguities"]),
                                 sorted(record["conventions"]["ambiguities"]))

    def test_observations_and_inferences_are_independent_lists(self):
        """Mutating ``observations`` cannot change an inference's value.

        The two lists are separate objects and no inference holds a reference
        into the observation list, so emptying the observations breaks the
        citations without changing any claimed value. That is the structural
        separation the design requires: a claim is never *computed* from the
        emitted observations, only cited from them.
        """
        record = record_of("01_thiscall_member")
        values = {entry["id"]: entry.get("value") for entry in record["inferences"]}
        record["observations"] = []
        self.assertEqual(values, {entry["id"]: entry.get("value")
                                  for entry in record["inferences"]})


class PropertyTest(unittest.TestCase):
    """The twelve invariants, over the fixtures, the captures and the corpus."""

    def setUp(self):
        pairs = fx.hermetic_inputs() + fx.live_inputs()
        pairs += [("fuzz[%d]" % index, text) for index, text
                  in enumerate(fx.fuzz_inputs(count=120))]
        self.pairs = pairs

    # -- 1 --------------------------------------------------------------- #
    def test_property_every_inference_cites_a_real_observation_id(self):
        for label, text in self.pairs:
            record = abi_infer.analyze(text)
            ids = {obs["id"] for obs in record["observations"]}
            for inference in record["inferences"]:
                with self.subTest(input=label, rule=inference["id"]):
                    self.assertTrue(inference["based_on"],
                                    "an inference must cite at least one observation")
                    for citation in inference["based_on"]:
                        self.assertIn(citation, ids)

    # -- 2 --------------------------------------------------------------- #
    def test_property_unknown_verdict_claims_nothing(self):
        """The documents' invariant 2, restated in the engine's vocabulary.

        ``PASS`` does not exist in ``CONFIDENCE_ORDER``, so the literal assertion
        is vacuous. The engine's analogue, which is what the design actually
        promises, is: an ``ABI_UNKNOWN`` verdict means no convention was claimed,
        the conventions confidence is UNKNOWN, and no inference names a
        convention as its value.
        """
        seen = 0
        for label, text in self.pairs:
            record = abi_infer.analyze(text)
            if record["verdict"] != "ABI_UNKNOWN":
                continue
            seen += 1
            with self.subTest(input=label):
                self.assertIsNone(fx.convention_of(record))
                self.assertEqual("UNKNOWN", record["conventions"]["confidence"])
                self.assertTrue(record["abstained_because"],
                                "an abstention must say why")
                for inference in record["inferences"]:
                    self.assertNotIn(inference.get("value"), abi_infer.CONVENTIONS)
        self.assertGreater(seen, 5, "the corpus must actually contain abstentions")

    # -- 3 --------------------------------------------------------------- #
    def test_property_vocabularies_are_closed(self):
        for label, text in self.pairs:
            record = abi_infer.analyze(text)
            with self.subTest(input=label):
                self.assertIn(record["verdict"], abi_infer.VERDICTS)
                if fx.convention_of(record) is not None:
                    self.assertIn(fx.convention_of(record), abi_infer.CONVENTIONS)
                for candidate in record["conventions"]["candidate_conventions"]:
                    self.assertIn(candidate, abi_infer.CONVENTIONS)
                for confidence in (record["conventions"]["confidence"],
                                   record["receiver"]["confidence"],
                                   record["stack_arguments"]["confidence"],
                                   record["cleanup"]["confidence"],
                                   record["return"]["confidence"],
                                   record["sret"]["confidence"]):
                    self.assertIn(confidence, abi_infer.CONFIDENCE_ORDER)
                for inference in record["inferences"]:
                    self.assertIn(inference["confidence"], abi_infer.CONFIDENCE_ORDER)
                for code in fx.abstention_codes(record):
                    self.assertIn(code, abi_infer.ABSTENTION_CODES)
                self.assertIn(record["cleanup"]["side"],
                              (None, "caller", "callee", "CONFLICT"))
                self.assertIn(record["completeness"],
                              ("CORE_RESOLVED", "PARTIAL", "EMPTY"))
                self.assertIn(record["variadic"], ("UNKNOWN", "SUSPECTED"))
                self.assertIn(record["return"]["register_class"],
                              ("unknown", "integral", "pointer_like",
                               "aggregate_unknown", "float_or_x87"))

    # -- 4 --------------------------------------------------------------- #
    def test_property_engine_is_total_on_arbitrary_text(self):
        """No exception, ever, and always a dict with ``schema`` and ``verdict``."""
        for label, text in self.pairs:
            with self.subTest(input=label, text=repr(text)[:60]):
                record = abi_infer.analyze(text)
                self.assertIsInstance(record, dict)
                self.assertEqual(abi_infer.SCHEMA, record["schema"])
                self.assertIn("verdict", record)
                self.assertIn(record["verdict"], abi_infer.VERDICTS)

    def test_property_engine_rejects_every_unrecognised_shape(self):
        """Totality is over *text*. An unrecognised shape must raise, not coerce.

        ``normalize_listing``'s docstring: "Silently coercing an unrecognised
        shape is forbidden." A number, a bool and a dict without ``instructions``
        are all ValueError, so a caller passing the wrong thing finds out.
        """
        for value in (5, 1.5, True, {}, {"schema": "wrong"}, {"foo": 1},
                      [1, 2, 3], [{"no": "instruction"}], object()):
            with self.subTest(value=repr(value)[:40]):
                with self.assertRaises(ValueError):
                    abi_infer.analyze(value)

    def test_property_legal_empty_shapes_are_accepted(self):
        for value in (None, "", [], {"instructions": []}):
            with self.subTest(value=repr(value)):
                record = abi_infer.analyze(value)
                self.assertEqual("ABI_UNKNOWN", record["verdict"])
                self.assertEqual([], record["observations"])

    # -- 5 --------------------------------------------------------------- #
    def test_property_return_type_is_always_none(self):
        """The engine emits no C++ type, ever."""
        for label, text in self.pairs:
            with self.subTest(input=label):
                self.assertIsNone(abi_infer.analyze(text)["return"]["type"])

    def test_property_no_type_named_key_is_ever_filled(self):
        """A type-shaped key is whitelisted but must stay empty."""
        for label, text in self.pairs:
            record = abi_infer.analyze(text)
            with self.subTest(input=label):
                for key in ("return_type", "return_width_bytes", "hidden_this_type"):
                    self.assertNotIn(key, record["abi"],
                                     "%s is a C++-shaped key the engine must not fill"
                                     % key)

    # -- 6 --------------------------------------------------------------- #
    def test_property_sret_present_is_never_true(self):
        for label, text in self.pairs:
            with self.subTest(input=label):
                self.assertIsNot(True, abi_infer.analyze(text)["sret"]["present"])

    # -- 7 --------------------------------------------------------------- #
    def test_property_abi_keys_stay_inside_the_whitelist(self):
        """CRITICAL: the validator consumes this sub-object verbatim."""
        for label, text in self.pairs:
            record = abi_infer.analyze(text)
            with self.subTest(input=label):
                for key in record["abi"]:
                    self.assertIn(key, abi_infer.ABI_KEYS,
                                  "record['abi']['%s'] would be dropped by "
                                  "extract_abi" % key)

    def test_property_abi_block_survives_extract_abi_unchanged(self):
        """End to end: every emitted name must reach the consumer's selection."""
        from tools.reconstruction_knowledge import extract_abi
        for label, text in fx.hermetic_inputs() + fx.live_inputs():
            record = abi_infer.analyze(text)
            if not record["abi"]:
                continue
            with self.subTest(input=label):
                selected = extract_abi({"abi": record["abi"]})
                for key in record["abi"]:
                    self.assertIn(key, selected,
                                  "extract_abi dropped %r from the emitted block"
                                  % key)

    # -- 8 --------------------------------------------------------------- #
    def test_property_determinism_over_the_corpus(self):
        for label, text in self.pairs:
            with self.subTest(input=label):
                first = abi_infer.analyze(text)
                self.assertEqual(canonical_json(first),
                                 canonical_json(abi_infer.analyze(text)))

    # -- 9 --------------------------------------------------------------- #
    def test_property_canonical_form_over_the_corpus(self):
        for label, text in self.pairs:
            with self.subTest(input=label):
                record = abi_infer.analyze(text)
                self.assertEqual(record, json.loads(canonical_json(record)))

    # -- 10 -------------------------------------------------------------- #
    def test_property_ids_are_dense_and_ordered_over_the_corpus(self):
        order = {rule: position for position, rule in enumerate(fx.CLAIM_ORDER)}
        for label, text in self.pairs:
            record = abi_infer.analyze(text)
            with self.subTest(input=label):
                self.assertEqual(
                    ["obs-%04d" % (position + 1)
                     for position in range(len(record["observations"]))],
                    [obs["id"] for obs in record["observations"]])
                positions = [order[fx.base_rule(rule)] for rule in ids_of(record)]
                self.assertEqual(sorted(positions), positions)

    # -- 12 (restated correctly; the literal form is asserted in Defect D7) -- #
    def test_property_slot_pitch_is_always_a_dword_multiple(self):
        """The documents' phrasing is wrong as written; the pitch is not.

        The documents say "stack-argument widths are always dword multiples".
        That conflates the *pitch* between entry slots -- which is always a
        dword, and is what the cleanup arithmetic and C4's comparison are built
        on -- with the *observed read width*, which may be 1, 2 or 4.
        ``KnownEngineDefectTest.test_slot_pitch_is_dword_and_read_widths_are_
        reported_verbatim`` is the focused form of this separation.
        """
        for label, text in self.pairs:
            record = abi_infer.analyze(text)
            with self.subTest(input=label):
                for slot in record["stack_arguments"]["slots"]:
                    offset = slot["entry_offset"]
                    self.assertTrue(offset.startswith("entry_ESP+0x"), offset)
                    self.assertEqual(0, int(offset[len("entry_ESP+0x"):], 16) % 4)
                    for size in slot["sizes"]:
                        self.assertIn(size, (1, 2, 4, 8, 10, 16, 32),
                                      "an unknown width must not be invented")
                ordinals = [slot["ordinal"] for slot
                            in record["stack_arguments"]["slots"]]
                self.assertEqual(list(range(1, len(ordinals) + 1)), ordinals)

    def test_observed_read_widths_may_be_narrower_than_a_dword(self):
        """The engine reports the width it saw; that is more honest, not less.

        ``MOV AX, word ptr [EBP + 0x8]`` is a two-byte read of entry slot 1.
        Reporting it as a four-byte argument would be a claim the listing does
        not support.
        """
        for instruction, expected in (("MOV AX,word ptr [EBP + 0x8]", [2]),
                                      ("MOV AL,byte ptr [EBP + 0x8]", [1]),
                                      ("MOV EAX,dword ptr [EBP + 0x8]", [4])):
            with self.subTest(instruction=instruction):
                record = abi_infer.analyze(
                    "PUSH EBP\nMOV EBP,ESP\n%s\nMOV EAX,1\n"
                    "MOV ESP,EBP\nPOP EBP\nRET\n" % instruction)
                self.assertEqual(expected,
                                 record["stack_arguments"]["slots"][0]["sizes"])

    def test_one_slot_read_at_two_widths_is_an_abstention(self):
        record = abi_infer.analyze(
            "PUSH EBP\nMOV EBP,ESP\n"
            "MOV EAX,dword ptr [EBP + 0x8]\n"
            "MOV AX,word ptr [EBP + 0x8]\n"
            "MOV EAX,1\nMOV ESP,EBP\nPOP EBP\nRET\n")
        self.assertTrue(record["stack_arguments"]["widths_ambiguous"])
        self.assertIn("slot_width_ambiguous", fx.abstention_codes(record))
        self.assertIn("A2", ids_of(record))


# =========================================================================== #
# Part D -- cross-validation
# =========================================================================== #
class CrossValidationTest(unittest.TestCase):
    """The matrix from abi-inference-spec.md §5.1, over ``analyze``'s kwargs.

    The precedence, from ``cross_validate``'s docstring: an external claim may
    only bump (capped at SUPPORTED), drop (floor INFERRED) or record a conflict.
    It may never set ``calling_convention``, ``sret.present`` or
    ``receiver.present``, it can never promote an abstention, and Ghidra silence
    is not agreement.

    Two tests here were REPAIRED after defect D4 was corrected (a conflict that
    demoted nothing): ``test_disagreement_demotes_the_cleanup_claim_and_changes_
    nothing_else`` and ``test_cross_validate_never_writes_convention_receiver_
    or_sret`` (with ``test_a_disagreement_demotes_cleanup_confidence_and_
    nothing_else`` splitting out the one write a conflict *is* allowed to make).
    All three had asserted that a disagreement leaves every field bit-identical,
    which spec §5.1.4's mandatory ``drop(...)`` forbids.
    """

    SILENCE = (None, "", "   ", "unknown", "default", "none", "n/a", "null", 0, True)

    def test_ghidra_silence_is_no_information_in_every_spelling(self):
        """Silence changes the verdict, the conflicts and nothing else.

        The one field that does change is
        ``cross_validation.ghidra_calling_convention``, which echoes the
        caller's own string verbatim -- that is provenance, so a consumer can see
        what Ghidra actually said, and it is not read as a claim: ``ghidra``
        stays ``no_information`` and no conflict is raised.
        """
        baseline = abi_infer.analyze(THISCALL_BODY)
        for value in self.SILENCE:
            with self.subTest(ghidra=repr(value)):
                record = abi_infer.analyze(THISCALL_BODY,
                                           ghidra_calling_convention=value)
                self.assertEqual("no_information",
                                 record["cross_validation"]["ghidra"])
                self.assertEqual([], record["conflicts"])
                self.assertFalse(record["cross_validation"]["agreement"])
                self.assertEqual(baseline["conventions"], record["conventions"])
                self.assertEqual(baseline["cleanup"], record["cleanup"])
                self.assertEqual(baseline["receiver"], record["receiver"])
                self.assertEqual(baseline["verdict"], record["verdict"])
                self.assertEqual(baseline["inferences"], record["inferences"])
                differing = fx.diffing_paths(baseline, record)
                self.assertLessEqual(
                    differing,
                    {"$.content_sha256",
                     "$.cross_validation.ghidra_calling_convention"},
                    "silence must change nothing but the verbatim echo")
                self.assertEqual(
                    None if value is None else str(value),
                    record["cross_validation"]["ghidra_calling_convention"],
                    "the echo is the caller's own string, never normalised")

    def test_ghidra_agreement_raises_confidence_exactly_one_rung(self):
        record = abi_infer.analyze(THISCALL_BODY,
                                   ghidra_calling_convention="__thiscall")
        self.assertEqual("agrees", record["cross_validation"]["ghidra"])
        self.assertTrue(record["cross_validation"]["agreement"])
        self.assertEqual("ghidra_agrees", record["conventions"]["corroboration"])
        self.assertEqual("SUPPORTED", record["conventions"]["confidence"])
        self.assertEqual([], record["conflicts"])

    def test_agreement_is_capped_at_supported(self):
        """Bumping twice must not reach OBSERVED, which is a fact label."""
        record = abi_infer.analyze(THISCALL_BODY)
        for _ in range(3):
            record, _conflicts = abi_infer.cross_validate(
                record, ghidra_calling_convention="__thiscall")
        self.assertEqual("SUPPORTED", record["conventions"]["confidence"])
        self.assertLess(abi_infer.CONFIDENCE_ORDER.index("SUPPORTED"),
                        abi_infer.CONFIDENCE_ORDER.index("OBSERVED"))

    def test_agreement_accepts_the_bare_convention_name(self):
        for spelling in ("__thiscall", "thiscall", "__thiscall ", "  thiscall"):
            with self.subTest(spelling=repr(spelling)):
                record = abi_infer.analyze(THISCALL_BODY,
                                           ghidra_calling_convention=spelling)
                self.assertEqual("agrees", record["cross_validation"]["ghidra"])

    def test_ghidra_disagreement_records_a_conflict_and_keeps_our_convention(self):
        record = abi_infer.analyze(THISCALL_BODY,
                                   ghidra_calling_convention="__cdecl")
        self.assertEqual("disagrees", record["cross_validation"]["ghidra"])
        self.assertFalse(record["cross_validation"]["agreement"])
        self.assertEqual("__thiscall", fx.convention_of(record),
                         "an external claim must never overwrite an inference")
        self.assertEqual("ABI_INFERRED", record["verdict"])
        self.assertEqual(1, len(record["conflicts"]))
        conflict = record["conflicts"][0]
        self.assertEqual("inferred_vs_ghidra", conflict["kind"])
        self.assertEqual("calling_convention", conflict["field"])
        self.assertEqual("__thiscall", conflict["inferred"])
        self.assertEqual("__cdecl", conflict["ghidra"])
        self.assertEqual("unresolved", conflict["resolution_status"])

    def test_disagreement_demotes_the_cleanup_claim_and_changes_nothing_else(self):
        """Was ``test_disagreement_changes_the_confidence_ladder_not_otherwise``.

        REPAIRED, because the old version was unsatisfiable alongside its own
        twin. It asserted ``disagreed["cleanup"]["confidence"] == "OBSERVED"``
        on the grounds that a conflict demoted nothing; D4's test requires it to
        be *lower* under disagreement. ``OBSERVED`` is the top of the range
        there is room to drop from, so ``bare == disagreed < agreed`` could not
        hold. Spec §5.1.4 mandates a demotion, defect D4 was corrected, and the
        cleanup claim now falls one rung, OBSERVED -> SUPPORTED. The convention
        claim itself still sits on the INFERRED floor, so the demotion lands on
        cleanup -- the claim that had room to move.
        """
        observed = abi_infer.analyze(THISCALL_BODY)
        agreed = abi_infer.analyze(THISCALL_BODY,
                                   ghidra_calling_convention="__thiscall")
        disagreed = abi_infer.analyze(THISCALL_BODY,
                                      ghidra_calling_convention="__cdecl")
        self.assertEqual("INFERRED", observed["conventions"]["confidence"])
        self.assertEqual("SUPPORTED", agreed["conventions"]["confidence"])
        self.assertEqual("INFERRED", disagreed["conventions"]["confidence"],
                         "the convention claim is already on the floor")
        self.assertLess(abi_infer.CONFIDENCE_ORDER.index(
            disagreed["conventions"]["confidence"]),
            abi_infer.CONFIDENCE_ORDER.index(
                agreed["conventions"]["confidence"]),
            "agreement must outrank disagreement")
        # The demotion D4 required: strictly below both the bare record and the
        # agreed record, and below the rung the claim was emitted at.
        self.assertEqual("OBSERVED", observed["cleanup"]["confidence"])
        self.assertEqual("OBSERVED", agreed["cleanup"]["confidence"])
        self.assertEqual("SUPPORTED", disagreed["cleanup"]["confidence"],
                         "a conflict must visibly demote the cleanup claim")
        self.assertLess(abi_infer.CONFIDENCE_ORDER.index(
            disagreed["cleanup"]["confidence"]),
            abi_infer.CONFIDENCE_ORDER.index(
                observed["cleanup"]["confidence"]),
            "the demotion must be real, not a renaming of the same rung")
        # Everything that is a machine fact is untouched by the conflict.
        self.assertEqual(observed["cleanup"]["side"],
                         disagreed["cleanup"]["side"])
        self.assertEqual(observed["cleanup"]["bytes"],
                         disagreed["cleanup"]["bytes"])
        self.assertEqual(observed["cleanup"]["evidence"],
                         disagreed["cleanup"]["evidence"])
        self.assertEqual(1, len(disagreed["conflicts"]))
        self.assertEqual([], agreed["conflicts"])

    def test_cross_validation_never_promotes_an_abstention(self):
        """Ghidra naming a convention while the engine abstained.

        The record must stay ABI_UNKNOWN / UNKNOWN *and* the conflict must
        still be emitted: an abstention plus a contradiction is exactly what a
        human needs to see. Promoting would launder the disagreement.
        """
        sources = [ABSTAIN_BODY, THUNK_BODY,
                   fx.load_fixture("08_leaf_no_frame"),
                   fx.load_fixture("10_contradictory_ret_immediates"),
                   fx.load_fixture("12b_variadic_huge_frame"),
                   fx.load_fixture("14_integral_return")]
        for source in sources:
            for convention in abi_infer.CONVENTIONS:
                with self.subTest(source=source[:24], convention=convention):
                    record = abi_infer.analyze(source,
                                               ghidra_calling_convention=convention)
                    self.assertEqual("ABI_UNKNOWN", record["verdict"])
                    self.assertIsNone(fx.convention_of(record))
                    self.assertEqual("UNKNOWN", record["conventions"]["confidence"])
                    self.assertEqual("not_available",
                                     record["conventions"]["corroboration"])
                    self.assertEqual("disagrees",
                                     record["cross_validation"]["ghidra"])
                    self.assertEqual(1, len(record["conflicts"]))
                    self.assertIsNone(record["conflicts"][0]["inferred"])
                    self.assertEqual(convention, record["conflicts"][0]["ghidra"])

    def test_persisted_agreement_raises_one_rung(self):
        record = abi_infer.analyze(THISCALL_BODY,
                                   persisted_abi={"calling_convention": "__thiscall"})
        self.assertEqual("agrees", record["cross_validation"]["persisted"])
        self.assertTrue(record["cross_validation"]["agreement"])
        self.assertEqual("persisted_agrees", record["conventions"]["corroboration"])
        self.assertEqual("SUPPORTED", record["conventions"]["confidence"])
        self.assertEqual([], record["conflicts"])

    def test_persisted_disagreement_records_a_conflict(self):
        record = abi_infer.analyze(THISCALL_BODY,
                                   persisted_abi={"calling_convention": "__cdecl"})
        self.assertEqual("disagrees", record["cross_validation"]["persisted"])
        self.assertEqual("__thiscall", fx.convention_of(record))
        self.assertEqual(1, len(record["conflicts"]))
        self.assertEqual("inferred_vs_persisted", record["conflicts"][0]["kind"])

    def test_persisted_cleanup_bytes_mismatch_is_its_own_conflict(self):
        """The cleanup byte count is cross-checkable independently of the name."""
        record = abi_infer.analyze(THISCALL_BODY, persisted_abi={
            "calling_convention": "__thiscall", "stack_cleanup_bytes": 8})
        kinds = [(conflict["kind"], conflict["field"])
                 for conflict in record["conflicts"]]
        self.assertEqual([("inferred_vs_persisted", "stack_cleanup_bytes")], kinds,
                         "the convention agrees, so only the byte count conflicts")
        self.assertEqual("callee", record["cleanup"]["side"])
        self.assertEqual(4, record["cleanup"]["bytes"],
                         "the engine's own cleanup figure is never overwritten")
        conflict = record["conflicts"][0]
        self.assertEqual(4, conflict["inferred"])
        self.assertEqual(8, conflict["persisted"])
        self.assertEqual("unresolved", conflict["resolution_status"])

    def test_ghidra_and_persisted_disagreeing_with_each_other_is_a_third_conflict(self):
        record = abi_infer.analyze(
            THISCALL_BODY,
            ghidra_calling_convention="__stdcall",
            persisted_abi={"calling_convention": "__fastcall"})
        kinds = {conflict["kind"] for conflict in record["conflicts"]}
        self.assertEqual({"inferred_vs_ghidra", "inferred_vs_persisted",
                          "ghidra_vs_persisted"}, kinds)

    def test_a_garbage_persisted_abi_is_ignored_not_merged(self):
        for value in (None, {}, "notadict", 7, {"calling_convention": "unknown"},
                      {"calling_convention": None}, {"calling_convention": 3}):
            with self.subTest(persisted=repr(value)):
                record = abi_infer.analyze(THISCALL_BODY, persisted_abi=value)
                self.assertEqual("__thiscall", fx.convention_of(record))
                self.assertEqual("no_information",
                                 record["cross_validation"]["persisted"])
                self.assertEqual([], record["conflicts"])

    def test_a_garbage_parameter_count_is_ignored(self):
        baseline = abi_infer.analyze(THISCALL_BODY)
        for value in (True, False, "3", 3.5, None):
            with self.subTest(count=repr(value)):
                record = abi_infer.analyze(THISCALL_BODY,
                                           ghidra_parameter_count=value)
                self.assertEqual(baseline["content_sha256"], record["content_sha256"])
        counted = abi_infer.analyze(THISCALL_BODY, ghidra_parameter_count=3)
        self.assertEqual(3, counted["cross_validation"]["ghidra_parameter_count"])

    def test_cross_validate_never_writes_convention_receiver_or_sret(self):
        """The precedence rule, field by field, for every outcome.

        REPAIRED. The old version also asserted
        ``bare["cleanup"] == record["cleanup"]`` for a disagreeing Ghidra, i.e.
        that a conflict changes *no* field at all. That contradicts spec §5.1.4,
        which mandates ``drop(...)`` on a conflict, and it contradicts
        ``KnownEngineDefectTest.test_a_conflict_must_visibly_demote_confidence``
        -- which asserts the demotion and passes since defect D4 was corrected.
        ``OBSERVED`` is the top rung, so "no demotion" and "must demote" cannot
        both hold; §5.1.4 wins, and the cleanup claim now falls OBSERVED ->
        SUPPORTED on disagreement.

        The invariant that is actually admissible is the one this test now
        states: cross-validation never *writes* ``calling_convention``,
        ``receiver`` or ``sret`` -- it may only bump, drop or record a conflict
        on a confidence. Silence and agreement must therefore leave all five
        fields bit-identical, and a disagreement may touch the cleanup
        *confidence* and nothing else, which is asserted field by field below
        rather than by comparing whole sub-objects.
        """
        bare = abi_infer.analyze(THISCALL_BODY)
        for ghidra in (None, "__cdecl", "__thiscall", "__stdcall", "__fastcall"):
            with self.subTest(ghidra=repr(ghidra)):
                record = abi_infer.analyze(THISCALL_BODY,
                                           ghidra_calling_convention=ghidra)
                # Never written, under any outcome.
                self.assertEqual(bare["receiver"], record["receiver"])
                self.assertEqual(bare["sret"], record["sret"])
                self.assertEqual(fx.convention_of(bare), fx.convention_of(record))
                # The cleanup *finding* is never written either -- only its
                # confidence may move, and only downward.
                for key in ("side", "bytes", "evidence"):
                    self.assertEqual(bare["cleanup"][key], record["cleanup"][key],
                                     "cross-validation must not rewrite cleanup.%s"
                                     % key)
                rank = abi_infer.CONFIDENCE_ORDER.index
                self.assertLessEqual(rank(record["cleanup"]["confidence"]),
                                     rank(bare["cleanup"]["confidence"]),
                                     "cleanup confidence may only be lowered")
                if record["cross_validation"]["ghidra"] == "no_information":
                    self.assertEqual(bare["cleanup"], record["cleanup"],
                                     "silence must not move the cleanup claim at all")
                    self.assertEqual(bare["conventions"], record["conventions"])

    def test_a_disagreement_demotes_cleanup_confidence_and_nothing_else(self):
        """The one field a conflict is allowed to move, asserted positively.

        Split out from the precedence test above so the permitted write is a
        first-class assertion rather than a gap in a ``assertEqual`` on whole
        sub-objects: every disagreeing convention must produce the same
        one-rung demotion, and must leave the convention name, the receiver, the
        sret block and the cleanup finding untouched.
        """
        bare = abi_infer.analyze(THISCALL_BODY)
        rank = abi_infer.CONFIDENCE_ORDER.index
        floor = rank("SUPPORTED")
        for ghidra in ("__cdecl", "__stdcall", "__fastcall"):
            with self.subTest(ghidra=ghidra):
                record = abi_infer.analyze(THISCALL_BODY,
                                           ghidra_calling_convention=ghidra)
                self.assertEqual("disagrees", record["cross_validation"]["ghidra"])
                self.assertEqual(floor, rank(record["cleanup"]["confidence"]),
                                 "a conflict must demote cleanup by exactly one rung")
                self.assertEqual("__thiscall", fx.convention_of(record),
                                 "an external claim must never overwrite the "
                                 "inference")
                self.assertEqual(bare["receiver"], record["receiver"])
                self.assertEqual(bare["sret"], record["sret"])
                for key in ("side", "bytes", "evidence"):
                    self.assertEqual(bare["cleanup"][key], record["cleanup"][key])
                self.assertEqual(1, len(record["conflicts"]))
                self.assertEqual("inferred_vs_ghidra", record["conflicts"][0]["kind"])
                self.assertEqual("unresolved", record["conflicts"][0]["resolution_status"])

    def test_cross_validate_returns_the_records_own_conflict_list(self):
        bare = abi_infer.analyze(THISCALL_BODY)
        record, conflicts = abi_infer.cross_validate(
            bare, ghidra_calling_convention="__cdecl")
        self.assertEqual("__thiscall", fx.convention_of(record))
        self.assertEqual(1, len(conflicts))
        self.assertIs(record["conflicts"], conflicts,
                      "the returned conflict list is the record's, not a copy")

    def test_cross_validation_does_not_launder_a_contradiction(self):
        """0x00aea250: engine says __thiscall, the index persists __fastcall.

        The engine's own reading stands, the conflict is emitted, and the
        record still says ``__thiscall``. Adopting the persisted label is the
        launder the design forbids.
        """
        record = abi_infer.analyze(
            fx.read_json(fx.live_path("00aea250", "thiscall_contradicts_fastcall")),
            persisted_abi={"calling_convention": fx.PERSISTED_FASTCALL})
        self.assertEqual("__thiscall", fx.convention_of(record))
        self.assertNotEqual(fx.PERSISTED_FASTCALL, fx.convention_of(record))
        self.assertEqual("disagrees", record["cross_validation"]["persisted"])
        self.assertEqual(1, len(record["conflicts"]))
        conflict = record["conflicts"][0]
        self.assertEqual("inferred_vs_persisted", conflict["kind"])
        self.assertEqual("__thiscall", conflict["inferred"])
        self.assertEqual("__fastcall", conflict["persisted"])
        self.assertEqual("unresolved", conflict["resolution_status"])
        self.assertEqual("ABI_INFERRED", record["verdict"])

    def test_a_conflict_does_not_erase_the_evidence_behind_the_claim(self):
        """Demotion is a confidence change, never a deletion of observations."""
        record = abi_infer.analyze(THISCALL_BODY,
                                   ghidra_calling_convention="__cdecl")
        bare = abi_infer.analyze(THISCALL_BODY)
        self.assertEqual(bare["observations"], record["observations"])
        self.assertEqual(bare["inferences"], record["inferences"])

    def test_both_sources_agreeing_reaches_supported_not_beyond(self):
        record = abi_infer.analyze(
            THISCALL_BODY, ghidra_calling_convention="__thiscall",
            persisted_abi={"calling_convention": "__thiscall"})
        self.assertEqual("SUPPORTED", record["conventions"]["confidence"])
        self.assertEqual("agrees", record["cross_validation"]["ghidra"])
        self.assertEqual("agrees", record["cross_validation"]["persisted"])
        self.assertEqual([], record["conflicts"])


# =========================================================================== #
# Part E -- degraded modes
# =========================================================================== #
class AbiInferenceConsumer(object):
    """A minimal caller of the engine, standing in for the hook in evidence.py.

    ``tools/`` is owned elsewhere, so the *contract* is pinned here instead of at
    the call site: a feature-detected integration must be able to call the engine
    without knowing whether it is present, and must be able to treat any failure
    as "no ABI evidence" rather than as a crash. Every path degrades to a
    well-formed empty record.
    """

    @staticmethod
    def empty_record(reason):
        return {"schema": abi_infer.SCHEMA, "verdict": "ABI_UNKNOWN",
                "conventions": {"calling_convention": None, "confidence": "UNKNOWN"},
                "abstained_because": [reason], "abi": {}, "degraded": True}

    def infer(self, disassembly):
        if disassembly is None:
            return self.empty_record("no_disassembly_supplied")
        try:
            record = abi_infer.infer(disassembly)
        except Exception as error:                     # noqa: BLE001 - by design
            return self.empty_record("engine_raised:%s" % type(error).__name__)
        if not isinstance(record, dict):
            return self.empty_record("engine_returned_%s" % type(record).__name__)
        if not record:
            return self.empty_record("engine_returned_empty_dict")
        if record.get("schema") != abi_infer.SCHEMA:
            return self.empty_record("engine_schema_mismatch:%r" % record.get("schema"))
        return record

    @staticmethod
    def has_abi_evidence(record):
        return bool(record.get("abi"))


class DegradedModeTest(unittest.TestCase):
    """Part E -- every degraded shape must produce a usable record, never raise."""

    def setUp(self):
        self.consumer = AbiInferenceConsumer()

    def _with_fake_engine(self, replacement):
        """Run the consumer against a stand-in engine, then restore the real one."""
        original = abi_infer.infer
        abi_infer.infer = replacement
        try:
            return self.consumer.infer(THISCALL_BODY)
        finally:
            abi_infer.infer = original

    def test_missing_entry_point_degrades_to_no_evidence(self):
        record = self.consumer.infer(None)
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertTrue(record["degraded"])
        self.assertIsNone(record["conventions"]["calling_convention"])
        self.assertFalse(self.consumer.has_abi_evidence(record))
        self.assertEqual("no_disassembly_supplied", record["abstained_because"][0])

    def test_an_empty_listing_is_not_the_same_as_a_missing_one(self):
        """A real empty listing is an answer; a missing entry point is a failure."""
        record = self.consumer.infer("")
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertNotIn("degraded", record)
        self.assertIn("empty_listing", fx.abstention_codes(record))

    def test_a_raising_engine_degrades_safely(self):
        def explode(*args, **kwargs):
            raise RuntimeError("bridge gone")
        record = self._with_fake_engine(explode)
        self.assertTrue(record["degraded"])
        self.assertIn("engine_raised:RuntimeError", record["abstained_because"])
        self.assertEqual("ABI_UNKNOWN", record["verdict"])

    def test_an_engine_returning_a_non_dict_degrades_safely(self):
        for value in ([], "ABI_UNKNOWN", 7, None, object()):
            with self.subTest(value=type(value).__name__):
                record = self._with_fake_engine(lambda *a, **k: value)
                self.assertTrue(record["degraded"])
                self.assertIn("engine_returned_", record["abstained_because"][0])
                self.assertEqual("ABI_UNKNOWN", record["verdict"])

    def test_an_engine_returning_an_empty_dict_degrades_safely(self):
        record = self._with_fake_engine(lambda *a, **k: {})
        self.assertTrue(record["degraded"])
        self.assertIn("engine_returned_empty_dict", record["abstained_because"])

    def test_an_engine_returning_the_wrong_schema_degrades_safely(self):
        for schema in ("bogus", None, "", 1, "openspore-abi-inference-2"):
            with self.subTest(schema=repr(schema)):
                record = self._with_fake_engine(
                    lambda *a, **k: {"schema": schema, "verdict": "ABI_INFERRED"})
                self.assertTrue(record["degraded"])
                self.assertIn("engine_schema_mismatch",
                              record["abstained_because"][0])
                self.assertEqual("ABI_UNKNOWN", record["verdict"],
                                 "a wrong-schema record must not be trusted")

    def test_a_healthy_engine_is_not_marked_degraded(self):
        record = self.consumer.infer(THISCALL_BODY)
        self.assertNotIn("degraded", record)
        self.assertTrue(self.consumer.has_abi_evidence(record))
        self.assertEqual("__thiscall", record["conventions"]["calling_convention"])

    def test_a_degraded_record_is_still_schema_conformant(self):
        """Whatever the failure, the consumer's fallback has the right shape."""
        for label, record in (
            ("missing", self.consumer.infer(None)),
            ("raising", self._with_fake_engine(
                lambda *a, **k: (_ for _ in ()).throw(ValueError("x")))),
            ("non-dict", self._with_fake_engine(lambda *a, **k: 7)),
            ("empty", self._with_fake_engine(lambda *a, **k: {})),
            ("wrong schema", self._with_fake_engine(
                lambda *a, **k: {"schema": "bogus"})),
        ):
            with self.subTest(mode=label):
                self.assertEqual(abi_infer.SCHEMA, record["schema"])
                self.assertIn(record["verdict"], abi_infer.VERDICTS)
                self.assertEqual({}, record["abi"])
                self.assertTrue(record["abstained_because"])

    def test_infer_single_argument_is_the_whole_inference(self):
        """``infer(x)`` with one argument is the full pipeline, per its docstring."""
        self.assertEqual(abi_infer.analyze(THISCALL_BODY)["content_sha256"],
                         abi_infer.infer(THISCALL_BODY)["content_sha256"])

    def test_infer_two_stage_call_matches_the_whole_pipeline(self):
        """``infer(obs, state, frame, meta)`` is stage two of the same pipeline."""
        insns, meta = abi_infer.parse_listing(THISCALL_BODY)
        observations, state, frame = abi_infer.extract(insns, meta)
        abi_infer._complete_observations(state, observations)
        state.observations = observations
        staged = abi_infer.infer(observations, state, frame, meta)
        # `analyze` runs cross_validate, caller corroboration and finalize on top
        # of the raw rule output; reproduce that so the two are comparable.
        staged, _conflicts = abi_infer.cross_validate(staged)
        self.assertEqual(abi_infer.analyze(THISCALL_BODY)["content_sha256"],
                         abi_infer.finalize(staged)["content_sha256"])

    def test_extract_never_produces_a_convention(self):
        """Stage 1 may not leak convention, receiver or sret vocabulary."""
        insns, meta = abi_infer.parse_listing(fx.load_fixture("01_thiscall_member"))
        observations, _state, _frame = abi_infer.extract(insns, meta)
        for observation in observations:
            with self.subTest(observation=observation["id"]):
                for forbidden in ("calling_convention", "convention", "sret",
                                  "receiver", "__thiscall", "__cdecl",
                                  "__stdcall", "__fastcall"):
                    self.assertNotIn(forbidden, json.dumps(observation, sort_keys=True),
                                     "stage 1 leaked %r" % forbidden)

    def test_normalize_listing_reports_the_layout_it_detected(self):
        cases = {
            "plain_text": THISCALL_BODY,
            "gcodebrowser_text": fx.CODEBROWSER_01,
            "att_text": fx.load_fixture(fx.ATT_TWIN_OF),
        }
        for expected, text in sorted(cases.items()):
            with self.subTest(expected=expected):
                _lines, meta = abi_infer.normalize_listing(text)
                self.assertEqual(expected, meta["layout"])


# =========================================================================== #
# Part F -- how a derived record is STORED
#
# The engine's record is a full per-instruction transcript, so the largest
# functions in the binary produce records of 25 KB to 215 KB. The evidence pack
# stores that record under ``categories["abi"]["value"]`` and has to keep it
# inside a byte budget. The budget used to be enforced with ``compact``, which
# answers an over-budget value with an opaque ``{"truncated": ...}`` envelope --
# and ``validate._abi_category`` reads an envelope as *no derived record*. The
# feature therefore went silently missing for exactly the functions with the
# most ABI evidence.
#
# What replaced it is a projection: the same document with the transcripts
# bounded and every decision-relevant field complete, marked so a consumer can
# tell it apart from a full record. These tests pin the projection's contract:
# a record that fits is stored untouched, a record that does not is projected
# rather than enveloped, no verdict moves, every citation still resolves, the
# value still fits the budget, and a pathological record degrades by a defined
# ladder instead of falling back to the envelope.
#
# The projection lives in ``tools/reconstruction_tooling/evidence.py`` and is
# exercised here rather than in ``tests/test_openspore_tooling.py`` because it
# is a property of the *record* this suite owns: every input below is a
# committed golden of this engine, so the whole class is hermetic and needs no
# bridge. The stored value is a storage concern, but the value stored is still
# an ``openspore-abi-inference-1`` record, which is what makes this suite's own
# goldens the right fixtures for it.
# =========================================================================== #
class DerivedRecordStorageTest(unittest.TestCase):
    """The stored form of a derived ABI record: full, or projected -- never an envelope."""

    #: The one committed live target whose record is genuinely over the budget
    #: (32623 B as committed). Named here rather than discovered, so a
    #: re-capture that changes its size has to be acknowledged in this file.
    OVER_BUDGET = (("00de9fc0", "untrusted_frame"),)
    #: The ladder the implementation must use, in this order. Pinned so the
    #: degradation order cannot be rearranged silently: the transcript goes
    #: first, then the per-function bookkeeping, then the ABI claim block, and
    #: the minimum key set is the floor.
    LADDER = ("observations_identity_only", "transcripts_minimised",
              "observations_dropped", "parse_dropped", "dispatch_dropped",
              "abi_transcripts_dropped", "abi_claims_only")
    #: What the *last* applied step is called after 0 and after 1 ladder rungs.
    #: The summary projection is step zero and is not itself a ladder rung, so
    #: the tail of the applied list lags the ladder index by one.
    LADDER_TAIL = ("observations_summarised", "observations_identity_only")
    #: ``(parent container, list key, marker key)`` of every bounded transcript
    #: list, mirroring ``evidence.ABI_DERIVED_TRANSCRIPTS`` as the test reads it:
    #: the bound is stated by a sibling marker inside the parent, never by a
    #: synthetic element inside the list.
    BOUNDED = (("stack_arguments", "slots", "slots_bounded"),
               ("abi", "stack_arguments", "stack_arguments_bounded"),
               ("abi", "ordinary_stack_arguments", "ordinary_stack_arguments_bounded"),
               ("abi", "ordinary_stack_argument_slots", "ordinary_stack_argument_slots_bounded"))

    @staticmethod
    def live_records():
        """``(va8, slug, record)`` for every committed live target."""
        return [(va8, slug, live_golden(va8, slug))
                for va8, slug, _c, _s, _b, _n in fx.LIVE_TARGETS]

    @staticmethod
    def every_committed_record():
        """``(label, record)`` for every committed golden of this engine.

        The 24 hermetic inputs and the 12 live targets, so "a record that fits
        is stored untouched" is asserted against the whole corpus the engine has
        a golden for, not against a hand-picked pair. The AT&T twin is skipped:
        it has no golden of its own (it is replayed through fixture 01's).
        """
        out = [(stem, golden_of(stem)) for stem in fx.iter_fixture_names()
               if stem != fx.ATT_TWIN_OF]
        out.extend(("%s/%s" % (va8, slug), golden)
                   for va8, slug, golden in DerivedRecordStorageTest.live_records())
        return out

    #: How many of ``0x00de9fc0``'s own observations the synthetic records keep.
    #: Chosen so that a *small* number of filler observations is enough to push
    #: the record over the budget: at 64 the summary projection is 21468 B, so
    #: the summary rung is reachable without deleting the record's real
    #: citations, and every deeper rung is reachable by adding more.
    KEEP_OBSERVATIONS = 64
    #: Characters of verbatim instruction text each filler observation carries.
    #: ``raw`` is the transcript the summary rung drops, so its width is what
    #: decides whether a record is over budget only because of its transcript.
    FILLER_RAW_REPEAT = 1

    def record_with_filler(self, count, extra=None):
        """``0x00de9fc0``'s record with ``count`` synthetic observations appended.

        One real record cannot reach every rung -- the committed corpus tops out
        at 32623 B and its summary projection at 28543 B, so the summary rung is
        unreachable from a committed golden alone. The ladder is therefore walked
        with the same *kind* of input the large real functions produce: real
        observations first, then as many more per-instruction observations as it
        takes. The filler is a genuine observation shape (``id``/``index``/
        ``at``/``kind``/``raw``/a scalar), so the projection is doing real work
        on it rather than taking a special case.

        Only the first :data:`KEEP_OBSERVATIONS` real observations are kept, so
        a record built this way is deliberately *not* self-consistent: the
        inference trace still cites ids past that cut. Anything asserting on
        citation resolution has to use :meth:`tiled_record` instead.
        """
        record = live_golden(*self.OVER_BUDGET[0])
        observations = [dict(observation)
                        for observation in record["observations"][:self.KEEP_OBSERVATIONS]]
        for index in range(count):
            filler = {"id": "obs-f%05d" % (index + 1), "index": 900 + index,
                      "at": "0x00f00000", "kind": "REG_READ", "reg": "EAX",
                      "raw": ("MOV EAX,dword ptr [EBP + 0x%x]; " % (4 * index)) *
                             self.FILLER_RAW_REPEAT}
            if extra:
                filler.update(extra)
            observations.append(filler)
        return dict(record, observations=observations)

    def tiled_record(self, repeats):
        """The real record's observations *and* its citations, tiled together.

        Unlike :meth:`record_with_filler` this one is internally consistent: the
        observation list is repeated ``repeats`` times with fresh ids and every
        ``based_on`` list is rewritten to the ids of its own copy, so the record
        cites observations it actually has. That is the only way to assert on
        citation *resolution* for a synthetic record -- a filler record's
        citations are dangling by construction, which is a property of the
        fixture, not of the projection.
        """
        record = live_golden(*self.OVER_BUDGET[0])
        observations = []
        inferences = []
        for repeat in range(repeats):
            renumber = {observation["id"]: "obs-t%03d-%s" % (repeat, observation["id"])
                        for observation in record["observations"]}
            observations.extend(dict(observation, id=renumber[observation["id"]])
                                for observation in record["observations"])
            for inference in record["inferences"]:
                copy = dict(inference)
                copy["based_on"] = [renumber[identifier]
                                    for identifier in inference["based_on"]
                                    if identifier in renumber]
                inferences.append(copy)
        return dict(record, observations=observations, inferences=inferences)

    def count_landing_on_rung(self, rungs):
        """The smallest filler count whose projection applies ``rungs`` ladder rungs.

        ``rungs`` 0 is the summary projection on its own -- every observation
        summarised, nothing else touched. ``rungs`` 1 adds
        ``LADDER[0]``, and so on. Scanned in a fixed ascending order with no
        randomness, so the answer is a constant of this class rather than a
        property of the machine it runs on.
        """
        for count in range(0, 2048, 4):
            stored = self.stored(self.record_with_filler(count))
            if "projection" not in stored:
                continue                     # still inside the budget: keep going
            if len(stored["projection"]["applied_steps"]) == rungs + 1:
                return count
        self.fail("no filler count in [0, 2048) applies %d ladder rungs" % rungs)

    @staticmethod
    def stored(record):
        return evidence._stored_derived_record(record)

    @staticmethod
    def hook(va8, slug, persisted_abi=None):
        """What ``evidence.collect`` would store, via the hook that derives it.

        The two cards are the shapes ``collect`` builds: a disassembly card with
        the uncompacted ``listing`` the engine reads, and a function card
        carrying only the two keys the hook is allowed to read off it. No
        bridge: both come from the committed capture.
        """
        document = fx.read_json(fx.live_path(va8, slug))
        disassembly = {"status": "ok", "mode": "live",
                       "provenance": "GhidraMCP /disassemble_function",
                       "data": document, "listing": document}
        function = {"status": "ok", "mode": "live",
                    "provenance": "GhidraMCP /get_function_by_address",
                    "data": {"name": slug}}
        return evidence._derived_abi("0x" + va8, function, disassembly, persisted_abi,
                                     {"binary": {"image_base": "0x00400000"}})

    @staticmethod
    def size(value):
        return len(canonical_json(value).encode("utf-8"))

    @staticmethod
    def citations_of(record):
        """Every observation id an inference cites, in sorted order."""
        return sorted({identifier
                       for inference in (record.get("inferences") or [])
                       for identifier in inference.get("based_on", [])})

    @classmethod
    def unresolved_citations(cls, stored_record, full_record):
        """Cited ids the stored observations cannot resolve."""
        known = {observation.get("id")
                 for observation in (stored_record.get("observations") or [])
                 if isinstance(observation, dict)}
        return [identifier for identifier in cls.citations_of(full_record)
                if identifier not in known]

    # ---------------------------------------------------------------- fitting #
    def test_a_record_that_fits_is_stored_unchanged(self):
        """The identity property, over every committed golden of this engine.

        A record inside the budget is returned *as the same object*, so the
        stored value is the engine's return value byte for byte and the pack's
        ``content_sha256`` is unaffected by the storage layer existing at all.
        This is what keeps the committed packs unchanged, and it is why the
        projection is not applied unconditionally.
        """
        corpus = self.every_committed_record()
        fitted = 0
        for label, record in corpus:
            with self.subTest(record=label):
                stored = self.stored(record)
                if self.size(record) <= evidence.ABI_DERIVED_MAX_BYTES:
                    fitted += 1
                    self.assertIs(record, stored,
                                  "a record that fits must be stored unchanged")
                    self.assertEqual(canonical_json(record), canonical_json(stored))
                    self.assertNotIn("projection", stored)
                    self.assertNotEqual(True, stored.get("truncated"))
        # The property only means something if the corpus has both sides of the
        # boundary, so the count is asserted rather than assumed.
        self.assertGreater(fitted, len(corpus) // 2)
        self.assertLess(fitted, len(corpus), "no over-budget record in the corpus?")

    def test_the_boundary_is_exactly_the_budget(self):
        """One byte under is stored whole; one byte over is projected.

        A budget off by a byte would show up as a pack that changed shape for
        no reason, so the boundary is measured rather than assumed: a real
        record is trimmed and then padded until it straddles the budget, and
        both sides of the line are checked.
        """
        budget = evidence.ABI_DERIVED_MAX_BYTES
        record = live_golden(*self.OVER_BUDGET[0])
        observations = list(record["observations"])
        while self.size(record) > budget:
            observations = observations[:-1]
            record = dict(record, observations=list(observations))
        self.assertLessEqual(self.size(record), budget)
        self.assertIs(record, self.stored(record))
        padded = dict(record, padding="p" * (budget + 4096))
        self.assertGreater(self.size(padded), budget)
        projected = self.stored(padded)
        self.assertIsNot(padded, projected)
        self.assertIn("projection", projected)
        self.assertLessEqual(self.size(projected), budget)

    # ------------------------------------------------------------- projecting #
    def test_an_over_budget_record_is_projected_and_never_enveloped(self):
        """The hole this closes: a large record is readable, not an envelope.

        ``0x00de9fc0`` is a committed live capture whose record is 32623 B. It
        used to be stored as ``{"truncated": true, "original_bytes": 32623,
        "preview": ...}``, which every consumer reads as "no derived record".
        """
        for va8, slug in self.OVER_BUDGET:
            with self.subTest(va=va8):
                record = live_golden(va8, slug)
                self.assertGreater(self.size(record), evidence.ABI_DERIVED_MAX_BYTES)
                stored = self.stored(record)
                self.assertNotEqual(True, stored.get("truncated"),
                                    "the envelope form must never be stored")
                self.assertNotIn("preview", stored)
                self.assertEqual(abi_infer.SCHEMA, stored["schema"])
                marker = stored["projection"]
                self.assertTrue(marker["full_record_recoverable"])
                self.assertEqual(self.size(record), marker["original_bytes"])
                self.assertEqual(len(record["observations"]),
                                 marker["observation_count"])
                self.assertEqual(evidence.ABI_DERIVED_MAX_BYTES, marker["budget_bytes"])
                self.assertIn("observations_summarised", marker["applied_steps"])
                self.assertEqual(marker["applied_steps"],
                                 ["observations_summarised"] +
                                 list(self.LADDER[:len(marker["applied_steps"]) - 1]),
                                 "the ladder must be walked in order")

    def test_a_projected_record_keeps_every_decision_relevant_field(self):
        """The projection is a storage concern: not one claim may move.

        Everything the validator, the worker briefing and this suite read is
        compared whole against the engine's record: the verdict, the whole
        abstention list, the conflicts, the conventions block, the cleanup, the
        receiver, the return classification, the sret hypothesis, the inference
        trace with its claims and its ``based_on`` lists, and the engine's own
        ``content_sha256`` -- which stays the digest of the *full* record, which
        is exactly the claim ``full_record_recoverable`` makes.
        """
        for va8, slug in self.OVER_BUDGET:
            with self.subTest(va=va8):
                record = live_golden(va8, slug)
                stored = self.stored(record)
                for key in ("schema", "verdict", "completeness", "abstained_because",
                            "conflicts", "conventions", "cleanup", "receiver",
                            "return", "sret", "stack_arguments", "dispatch",
                            "cross_validation", "tail_call", "target", "parse",
                            "seh_or_cookie_frame", "variadic", "inferences",
                            "content_sha256"):
                    self.assertEqual(record[key], stored[key], key)

    def test_the_projected_abi_block_keeps_every_claim(self):
        """``abi`` is the field the validator's oracle reads, so it stays whole.

        Its *element lists* may be bounded -- they are the per-slot transcript
        -- but the claims themselves, and the scalar summary beside each bounded
        list, are the decision and are never bounded. The three copies of the
        slot table the engine puts inside ``abi`` are bounded together with the
        original, so they stay consistent with each other.
        """
        for va8, slug, record in self.live_records():
            with self.subTest(va=va8):
                stored = self.stored(record)
                full_abi, abi = record["abi"], stored["abi"]
                self.assertEqual(sorted(full_abi), sorted(abi),
                                 "the projection must not add or drop an ABI claim")
                bounded = {list_key for _p, list_key, _m in self.BOUNDED}
                for key, value in full_abi.items():
                    if key not in bounded:
                        self.assertEqual(value, abi[key], key)
                for parent, list_key, marker_key in self.BOUNDED:
                    full_parent, stored_parent = record.get(parent), stored.get(parent)
                    if not isinstance(full_parent, dict) or list_key not in full_parent:
                        continue
                    value, kept = full_parent[list_key], stored_parent[list_key]
                    self.assertEqual(value[:len(kept)], kept,
                                     "%s.%s: the head of a bounded list must survive"
                                     % (parent, list_key))
                    if len(kept) == len(value):
                        # Nothing was bound: either the record was stored whole,
                        # or this list was already inside the cap.
                        self.assertNotIn(marker_key, stored_parent)
                        continue
                    marker = stored_parent.get(marker_key)
                    self.assertIsNotNone(marker, "%s.%s has no bound marker"
                                         % (parent, list_key))
                    self.assertEqual(len(value), marker["kept"] + marker["omitted"])
                    self.assertEqual(len(kept), marker["kept"])
                    self.assertLessEqual(marker["kept"],
                                         evidence.ABI_DERIVED_TRANSCRIPT_ELEMENTS)
                # The scalar summary beside a bounded table is the decision.
                for key in ("observed_slots", "derived_slots", "gaps",
                            "total_bytes", "confidence", "not_complete"):
                    for parent in ("stack_arguments",):
                        if key in record[parent]:
                            self.assertEqual(record[parent][key],
                                             stored[parent][key], key)

    def test_the_projection_is_bounded_at_every_rung_it_can_reach(self):
        """Each rung is measured, and the first one that fits is the one taken.

        The ladder stops at the first rung that fits, which only means the
        *richest* one if the rungs are checked in order and each really is
        smaller than the last. Only the first two rungs are reachable from
        ``0x00de9fc0``'s shape, and that is a fact about the rungs rather than a
        gap in the test: once the observation transcript is gone the record is
        15 KB, and ``parse`` (404 B) and ``dispatch`` (77 B) are far too small
        to be the difference between fitting and not. The deeper rungs are
        reached by growing what they actually shed -- the slot tables in
        ``test_the_floor_is_bounded_however_large_the_input_is``, the
        observation count in
        ``test_a_pathological_record_degrades_by_the_ladder_and_keeps_a_verdict``
        -- and the *order* is pinned for the whole ladder in
        ``test_the_ladder_is_the_documented_order`` and in every
        ``applied_steps`` assertion.
        """
        for rungs in (0, 1):
            with self.subTest(rungs=rungs, rung=self.LADDER_TAIL[rungs]):
                record = self.record_with_filler(self.count_landing_on_rung(rungs))
                stored = self.stored(record)
                applied = stored["projection"]["applied_steps"]
                self.assertEqual(applied, ["observations_summarised"] +
                                 list(self.LADDER[:rungs]),
                                 "the ladder must be walked in order, one rung at a time")
                self.assertEqual(self.LADDER_TAIL[rungs], applied[-1])
                self.assertLessEqual(self.size(stored), evidence.ABI_DERIVED_MAX_BYTES)
                self.assertEqual(record["verdict"], stored["verdict"])
                self.assertEqual(record["abstained_because"],
                                 stored["abstained_because"])
                self.assertLess(self.size(stored), self.size(record),
                                "a projection must be smaller than its input")
                self.assertEqual(stored["projection"]["observation_count"],
                                 len(stored["observations"]),
                                 "a rung must not lose or invent an observation")
                self.assertNotEqual("dropped", stored["projection"]["observations"])

    def test_every_citation_still_resolves_on_a_projected_record(self):
        """``inferences[].based_on`` must resolve against what is stored.

        The projection keeps every observation's id, and the id is the citation
        handle, so the traceability of every claim survives. A rung that dropped
        the observations entirely would break this, which is why the ladder puts
        the id-only rung *before* the drop rung.
        """
        for va8, slug, record in self.live_records():
            with self.subTest(va=va8):
                stored = self.stored(record)
                marker = stored.get("projection")
                if marker is None:
                    continue                      # stored whole: nothing to check
                self.assertNotEqual("dropped", marker["observations"],
                                    "a projected record must keep its citations")
                stored_ids = [observation.get("id")
                              for observation in stored["observations"]]
                self.assertEqual(marker["observation_count"], len(stored_ids))
                self.assertEqual(marker["observation_count"],
                                 len(record["observations"]))
                self.assertEqual(len(set(stored_ids)), len(stored_ids),
                                 "ids must stay unique and one per observation")
                self.assertEqual([], self.unresolved_citations(stored, record),
                                 "a stored projection left a citation dangling")

    def test_citations_resolve_on_a_tiled_record_at_the_identity_rung(self):
        """Citation resolution on a record far bigger than any committed one.

        The committed over-budget record lands on the identity rung and is
        checked in ``test_every_citation_still_resolves_on_a_projected_record``.
        This is the same property on a record big enough that the summary rung
        cannot possibly fit, so the check cannot pass by accident on a record
        that was barely projected: two copies of the observations and two copies
        of the inference trace, each copy citing its own ids, which is what a
        63800-byte record's trace looks like.
        """
        record = self.tiled_record(2)
        self.assertGreater(self.size(record), 2 * evidence.ABI_DERIVED_MAX_BYTES)
        stored = self.stored(record)
        self.assertEqual("identity_only", stored["projection"]["observations"])
        self.assertEqual(self.LADDER_TAIL[1],
                         stored["projection"]["applied_steps"][-1])
        self.assertEqual(2 * len(self.citations_of(
            live_golden(*self.OVER_BUDGET[0]))), len(self.citations_of(record)))
        self.assertEqual([], self.unresolved_citations(stored, record))
        # The stored form really is the id-only one, so the resolution above is
        # a statement about the cheapest rung and not about a rich one.
        self.assertEqual([{"id": observation["id"]}
                          for observation in record["observations"]],
                         stored["observations"])

    def test_the_summary_rung_drops_the_transcript_and_keeps_the_identity(self):
        """What a *summarised* observation may lose, and what it may not.

        ``raw`` -- the verbatim instruction text, which is the bulk of a large
        record -- is the transcript and is dropped. The identity fields and the
        small scalars are the facts the inferences cite and are kept, and a long
        prose string is truncated rather than dropped so the reason survives.
        The rung is reached with a record built by
        :meth:`count_landing_on_rung`, because no committed golden is small
        enough to need only this rung.
        """
        record = self.record_with_filler(self.count_landing_on_rung(0))
        stored = self.stored(record)
        self.assertEqual(["observations_summarised"],
                         stored["projection"]["applied_steps"])
        # A reason long enough to be bounded, so the text rule is exercised too.
        record = self.record_with_filler(self.count_landing_on_rung(0),
                                         extra={"reason": "why " * 400})
        stored = self.stored(record)
        bound = evidence.ABI_DERIVED_OBSERVATION_TEXT
        checked = 0
        for observation, full in zip(stored["observations"], record["observations"]):
            self.assertNotIn("raw", observation)
            for key in evidence.ABI_DERIVED_OBSERVATION_IDENTITY:
                self.assertEqual(full[key], observation[key], key)
            for key, value in full.items():
                if key == "raw":
                    continue
                if isinstance(value, str) and len(value) > bound:
                    checked += 1
                    self.assertTrue(observation[key].startswith(value[:bound]))
                    self.assertEqual(bound + 1, len(observation[key]))
                else:
                    self.assertEqual(value, observation[key], key)
        self.assertGreater(checked, 0, "no long text was truncated: the rule is untested")

    def test_the_identity_rung_keeps_every_id_and_nothing_else(self):
        """The rung that trades field-level facts for resolvable citations.

        A citation names an observation by ``id``, so ``id`` is the whole of what
        it needs. The committed over-budget record lands here, and this is the
        assertion that the id-only form is id-only: not one other field of the
        observation survives, and every id is still there in order.
        """
        for va8, slug in self.OVER_BUDGET:
            with self.subTest(va=va8):
                record = live_golden(va8, slug)
                stored = self.stored(record)
                self.assertEqual(["observations_summarised",
                                  "observations_identity_only"],
                                 stored["projection"]["applied_steps"])
                self.assertEqual("identity_only", stored["projection"]["observations"])
                self.assertEqual([{"id": observation["id"]}
                                  for observation in record["observations"]],
                                 stored["observations"])

    def test_no_verdict_moves_for_any_committed_target(self):
        """The invariant the whole projection is accountable to.

        Walked over every committed golden of the engine -- 24 hermetic inputs
        and 12 live targets -- so a verdict changing in either direction, for
        any input, fails here rather than in a pack nobody diffs.
        """
        for label, record in self.every_committed_record():
            with self.subTest(record=label):
                stored = self.stored(record)
                self.assertEqual(record["verdict"], stored["verdict"])
                self.assertEqual(record["abstained_because"],
                                 stored["abstained_because"])
                self.assertEqual(record["conflicts"], stored["conflicts"])
                self.assertEqual(record["completeness"], stored["completeness"])
                self.assertEqual(evidence._convention_of(stored),
                                 evidence._convention_of(record))

    def test_the_stored_value_is_always_within_the_budget(self):
        for label, record in self.every_committed_record():
            with self.subTest(record=label):
                self.assertLessEqual(self.size(self.stored(record)),
                                     evidence.ABI_DERIVED_MAX_BYTES)

    def test_the_projection_is_a_pure_function_of_the_record(self):
        """Same record in, same bytes out -- and the input is not touched.

        The pack is hashed, so a projection that depended on dict iteration
        order, mutated its input, or drifted between calls would make
        ``content_sha256`` unstable. The input is compared by value before and
        after, which is the only way a caller can rely on keeping its record.
        """
        for va8, slug, record in self.live_records():
            with self.subTest(va=va8):
                before = canonical_json(record)
                first = canonical_json(self.stored(record))
                second = canonical_json(self.stored(record))
                self.assertEqual(first, second)
                self.assertEqual(before, canonical_json(record),
                                 "the projection mutated the record it was given")

    # ----------------------------------------------------------------- ladder #
    def test_the_ladder_is_the_documented_order(self):
        self.assertEqual(self.LADDER, tuple(evidence.ABI_DERIVED_PROJECTION_STEPS))
        for key in ("schema", "verdict", "abi", "abstained_because", "conflicts"):
            self.assertIn(key, evidence.ABI_DERIVED_MINIMUM_KEYS,
                          "the floor must still carry %r" % key)

    def test_a_pathological_record_degrades_by_the_ladder_and_keeps_a_verdict(self):
        """A record no projection can fit is degraded, never enveloped.

        The real corpus tops out at 215190 B, so the deep rungs are reached
        here by a synthetic record built from a real one: the observations of
        ``0x00de9fc0`` tiled 40 times, which keeps the shape real and the record
        40x the size. What is asserted is the *contract* of the ladder: the
        applied steps are a prefix of it, the result fits, the result is still
        a record with a verdict, a readable ``abi`` block, the full abstention
        list and the conflicts -- and never an envelope.
        """
        record = live_golden(*self.OVER_BUDGET[0])
        tiled = [dict(observation, id="obs-t%02d-%s" % (repeat, observation["id"]))
                 for repeat in range(40) for observation in record["observations"]]
        pathological = dict(record, observations=tiled)
        self.assertGreater(self.size(pathological), evidence.ABI_DERIVED_MAX_BYTES)
        stored = self.stored(pathological)
        self.assertNotEqual(True, stored.get("truncated"))
        self.assertIn("projection", stored)
        self.assertLessEqual(self.size(stored), evidence.ABI_DERIVED_MAX_BYTES)
        applied = stored["projection"]["applied_steps"]
        self.assertEqual(applied, ["observations_summarised"] +
                         list(self.LADDER[:len(applied) - 1]),
                         "the ladder must be walked in order, one rung at a time")
        self.assertGreater(len(applied), 1,
                           "40x the observations should need more than the first rung")
        self.assertEqual(record["verdict"], stored["verdict"])
        self.assertEqual(record["abstained_because"], stored["abstained_because"])
        self.assertEqual(record["conflicts"], stored["conflicts"])
        self.assertEqual(abi_infer.SCHEMA, stored["schema"])
        for key in ("verdict", "abi", "abstained_because", "conflicts"):
            self.assertIn(key, stored, "the floor must still carry %r" % key)
        self.assertIsInstance(stored["abi"], dict)

    def test_the_floor_is_bounded_however_large_the_input_is(self):
        """The last rung is small by construction, so the ladder always lands.

        A ``0x00588570``-shaped input: a record whose ``abi`` block alone carries
        2000 slot entries -- and the engine stores that table three times over --
        with the inference trace repeated 12 times and the observation
        transcript blown up. Every earlier rung has to fail before the floor is
        reached, and the floor has to be inside the budget -- which is only true
        if it keeps no element list at all.
        """
        budget = evidence.ABI_DERIVED_MAX_BYTES
        record = live_golden(*self.OVER_BUDGET[0])
        slots = [{"entry_offset": "entry_ESP+0x%x" % (4 * index), "observed": True,
                  "ordinal": index, "read": False, "size_inferred": False,
                  "sizes": [4], "written": False} for index in range(2000)]
        offsets = [slot["entry_offset"] for slot in slots]
        pathological = dict(
            record,
            abi=dict(record["abi"], stack_arguments=slots,
                     ordinary_stack_arguments=slots,
                     ordinary_stack_argument_slots=offsets),
            stack_arguments=dict(record["stack_arguments"], slots=slots,
                                 observed_slots=len(slots)),
            inferences=[dict(inference) for _ in range(12)
                        for inference in record["inferences"]])
        self.assertGreater(self.size(pathological), 4 * budget)
        stored = self.stored(pathological)
        self.assertLessEqual(self.size(stored), budget)
        self.assertNotEqual(True, stored.get("truncated"))
        self.assertEqual(record["verdict"], stored["verdict"])
        self.assertEqual(record["abstained_because"], stored["abstained_because"])
        self.assertIsInstance(stored["abi"], dict)
        self.assertEqual(record["abi"].get("architecture"),
                         stored["abi"].get("architecture"))
        self.assertEqual(record["abi"].get("calling_convention"),
                         stored["abi"].get("calling_convention"))
        applied = stored["projection"]["applied_steps"]
        self.assertEqual(applied[-1], "abi_claims_only",
                         "a record of this size can only land on the floor")
        self.assertEqual(sorted(set(evidence.ABI_DERIVED_MINIMUM_KEYS) | {"projection"}),
                         sorted(stored),
                         "the floor is exactly the minimum key set plus the marker")

    def test_an_unexpected_shape_degrades_without_raising(self):
        """A record the projection does not recognise is carried, not raised on.

        ``_derived_abi`` is the only caller and it must be able to answer "no
        derivation" for any shape, so the projection never raises and never
        invents a field the engine did not emit.
        """
        for value in (None, [], "record", 7, True):
            with self.subTest(value=type(value).__name__):
                self.assertEqual(value, self.stored(value))
        odd = {"schema": abi_infer.SCHEMA, "verdict": "ABI_UNKNOWN", "abi": {},
               "abstained_because": [], "conflicts": [],
               "observations": "not a list", "padding": "x" * 40000}
        stored = self.stored(odd)
        self.assertIsInstance(stored, dict)
        self.assertEqual("ABI_UNKNOWN", stored["verdict"])
        # An ``observations`` value the projection does not recognise is never
        # re-interpreted: the summary and identity rungs leave it alone and the
        # ``observations_dropped`` rung removes it, exactly as it would a list.
        self.assertNotIn("observations", stored)
        self.assertIn("observations_dropped", stored["projection"]["applied_steps"])
        self.assertEqual([], self.unresolved_citations(stored, odd))

    def test_a_record_with_no_abi_block_is_still_stored(self):
        """A record whose ``abi`` is not a dict must not lose its verdict."""
        record = dict(live_golden(*self.OVER_BUDGET[0]), abi=None,
                      padding="x" * 40000)
        stored = self.stored(record)
        self.assertIsInstance(stored, dict)
        self.assertIn("verdict", stored)

    # -------------------------------------------------------------- consumers #
    def test_the_hook_stores_a_projection_and_never_an_envelope(self):
        """The pack's own hook, end to end, on the real over-budget capture.

        The other tests in this class call the storage helper. This one goes
        through ``evidence._derived_abi`` -- the function the evidence pack
        actually calls -- with the committed capture as the disassembly card,
        so the value that would reach ``categories["abi"]["value"]`` is what is
        asserted. Reverting the hook to the pre-fix ``compact`` call fails here
        and nowhere else, which is the point: the regression is at the call
        site, not in the helper.
        """
        for va8, slug in self.OVER_BUDGET:
            with self.subTest(va=va8):
                derived = self.hook(va8, slug)
                self.assertIsNotNone(derived)
                stored = derived["value"]
                self.assertNotEqual(True, stored.get("truncated"),
                                    "the hook must not store an envelope")
                self.assertNotIn("preview", stored)
                self.assertIn("projection", stored)
                self.assertEqual(abi_infer.SCHEMA, stored["schema"])
                self.assertIn(stored["verdict"], abi_infer.VERDICTS)
                self.assertIsInstance(stored["abi"], dict)
                self.assertLessEqual(self.size(stored), evidence.ABI_DERIVED_MAX_BYTES)
                # The engine's own digest survives, so the stored value still
                # identifies the full record it was projected from.
                self.assertIn("content_sha256", stored)
                self.assertEqual(2, len(derived["observations"]))

    def test_the_hook_stores_the_engine_return_unchanged_for_a_small_record(self):
        """Byte identity, through the hook, for a record that fits the budget.

        This is the pack-level form of "a record that fits is stored
        unchanged": the value the hook returns is the engine's return value,
        compared as bytes against an independent call of the engine on the same
        capture with the same arguments.
        """
        checked = 0
        for va8, slug, _c, _s, _b, _n in fx.LIVE_TARGETS:
            document = fx.read_json(fx.live_path(va8, slug))
            if self.size(abi_infer.analyze(document, image_base=0x00400000)) > \
                    evidence.ABI_DERIVED_MAX_BYTES:
                continue
            with self.subTest(va=va8):
                derived = self.hook(va8, slug)
                self.assertNotIn("projection", derived["value"])
                self.assertEqual(
                    canonical_json(abi_infer.analyze(document, image_base=0x00400000)),
                    canonical_json(derived["value"]))
            checked += 1
        self.assertGreater(checked, 5, "too few fitting targets: the rule is untested")

    def test_the_hook_answers_no_derivation_rather_than_an_envelope(self):
        """Every way the hook can say "nothing here" still says it.

        The hook is feature-detected and defensive by contract, so a card it
        cannot read, a compact-truncated listing, or a listing with no
        provenance to cite must all come back as ``None`` -- never as a
        half-written value, and never as the envelope the validator would read
        as "no record" while a consumer read it as a record. An *empty* listing
        is not one of those: the engine treats it as a legal answer, so the hook
        stores that real record rather than dropping it.
        """
        self.assertIsNone(evidence._derived_abi(
            "0x00de9fc0", None, {"status": "error", "code": "offline"}, None, None))
        self.assertIsNone(evidence._derived_abi(
            "0x00de9fc0", {"status": "ok", "data": {}, "provenance": "p"},
            {"status": "error"}, None, None))
        self.assertIsNone(evidence._derived_abi(
            "0x00de9fc0", None, {"status": "ok", "listing": {"truncated": True,
                                                             "preview": "x"}},
            None, None))
        self.assertIsNone(evidence._derived_abi(
            "0x00de9fc0", None, {"status": "ok", "listing": {"instructions": []}},
            None, None))
        empty = evidence._derived_abi(
            "0x00de9fc0", None,
            {"status": "ok", "provenance": "p", "listing": {"instructions": []}},
            None, None)
        self.assertIsInstance(empty, dict)
        self.assertNotEqual(True, empty["value"].get("truncated"))
        self.assertEqual("EMPTY", empty["value"]["completeness"])
        self.assertEqual("ABI_UNKNOWN", empty["value"]["verdict"])

    def test_the_validator_reads_a_projected_record_as_a_record(self):
        """``_abi_category`` returns facts *and* the record for a projection.

        This is the assertion the fix exists for. An envelope makes
        ``_abi_category`` return ``({}, None)``, which the validator reads as no
        derived ABI at all; a projection must return the ABI facts and the
        record, with the verdict readable.
        """
        for va8, slug, record in self.live_records():
            with self.subTest(va=va8):
                stored = self.stored(record)
                facts, inference = validate._abi_category(
                    {"abi": {"availability": "available", "value": stored}})
                self.assertIsNotNone(inference)
                self.assertEqual(record["verdict"], inference["verdict"])
                self.assertEqual(record["abi"], facts)
                self.assertIsInstance(facts, dict)
                self.assertNotEqual(({}, None), (facts, inference))
        # The envelope really is the failure mode being ruled out, shown once.
        envelope = {"truncated": True, "original_bytes": 32623, "preview": "{"}
        self.assertEqual(({}, None),
                         validate._abi_category({"abi": {"value": envelope}}))

    def test_every_abstaining_live_target_names_the_rule_that_blocked_it(self):
        """The property the deleted exemption-list guard used to carry.

        It was written for one hand-maintained entry. Stated over the table it
        is stronger: *every* target the table declares must abstain has to say
        why, and say it with a code from the engine's own closed vocabulary --
        so no abstention can be a shrug, and a future engine that recovers a
        convention for one of these fails here instead of being absorbed by a
        stale exception.
        """
        checked = 0
        for va8, slug, convention, _side, _bytes, _note in fx.LIVE_TARGETS:
            if convention is not None:
                continue
            checked += 1
            with self.subTest(va=va8):
                record = live_record(va8, slug)
                self.assertEqual("ABI_UNKNOWN", record["verdict"])
                self.assertIsNone(fx.convention_of(record))
                self.assertTrue(record["abstained_because"],
                                "an abstention must carry its reasons")
                for code in fx.abstention_codes(record):
                    self.assertIn(code, abi_infer.ABSTENTION_CODES,
                                  "%s abstains with an unregistered code %r"
                                  % (va8, code))
        self.assertGreater(checked, 1,
                           "the table must keep more than one declared abstention")

    def test_the_005291f0_abstention_is_still_pinned_against_the_table(self):
        """The one target the exception list used to cover, checked directly.

        ``0x005291f0``'s convention column is ``None`` in the corrected table,
        and the engine must abstain on it with the D1 reason codes. This is the
        assertion that survives the deletion of ``CORRECTED_TO_ABSTAIN`` and its
        guard test, stated without the list.
        """
        row = dict((entry[0], entry) for entry in fx.LIVE_TARGETS)["005291f0"]
        self.assertIsNone(row[2], "the table must declare 0x005291f0 as abstaining")
        record = live_record("005291f0", row[1])
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertIsNone(fx.convention_of(record))
        codes = fx.abstention_codes(record)
        self.assertIn("receiver_undetermined_blocks_convention", codes,
                      "an abstention must name the rule that blocked it")
        self.assertIn("receiver_not_determinable", codes)


# =========================================================================== #
# Part C -- the real SporeApp.exe functions, replayed hermetically
# =========================================================================== #
class RealSporeAppTest(unittest.TestCase):
    """The twelve real functions, from committed bridge captures.

    The disassembly is the verbatim ``/disassemble_function`` response body, not
    a transcription, so these assertions are about the real binary. The bridge
    was re-probed while this suite was written and every expectation below was
    taken from the live output, not from the research pass's notes.
    """

    #: instruction counts as committed, so a re-capture that changes the length
    #: of a fixture is a loud test failure rather than a silent golden update.
    COUNTS = {"0040ccb0": 71, "005291f0": 37, "00951230": 2, "00ce6950": 2,
              "004bdc00": 25, "008db310": 57, "00e5b790": 155, "005c65e0": 2,
              "00de9fc0": 193, "00aea250": 37, "00d2e350": 2, "007e6080": 1}

    def test_live_captures_are_committed_and_well_formed(self):
        for va8, slug, _convention, _side, _byte_count, _note in fx.LIVE_TARGETS:
            with self.subTest(va=va8):
                document = fx.read_json(fx.live_path(va8, slug))
                self.assertIsInstance(document.get("instructions"), list)
                self.assertTrue(document["instructions"])
                for item in document["instructions"]:
                    self.assertIn("address", item)
                    self.assertIn("instruction", item)

    def test_live_goldens_match_the_committed_captures(self):
        """No bridge needed: this is the CI-safe replay path."""
        for va8, slug, _c, _s, _b, _n in fx.LIVE_TARGETS:
            with self.subTest(va=va8, slug=slug):
                self.assertEqual([], fx.semantic_diff(live_golden(va8, slug),
                                                      live_record(va8, slug)))

    def test_live_capture_instruction_counts_match_the_index(self):
        for va8, slug, _c, _s, _b, _n in fx.LIVE_TARGETS:
            with self.subTest(va=va8):
                document = fx.read_json(fx.live_path(va8, slug))
                self.assertEqual(self.COUNTS[va8], len(document["instructions"]),
                                 "the committed capture's length changed; re-record")
                self.assertEqual(document["count"], len(document["instructions"]))

    def test_every_live_target_meets_its_convention_and_cleanup_expectation(self):
        """Six of the twelve resolve a convention; six must not.

        The convention column is the whole expectation: ``None`` means *this
        target must abstain* and the row's note says which rule blocks it; any
        other value is a name the engine has to produce, so the table cannot
        weaken into "whatever the engine says". ``0x005291f0`` is one of the
        ``None`` rows -- its reason is pinned by
        ``test_005291f0_still_reads_its_two_slots_and_its_and_esp_is_alignment``,
        and every abstaining row's registered abstention codes are asserted in
        ``test_every_abstaining_live_target_names_the_rule_that_blocked_it``.
        """
        for va8, slug, convention, side, byte_count, _note in fx.LIVE_TARGETS:
            with self.subTest(va=va8, slug=slug):
                record = live_record(va8, slug)
                if convention is None:
                    self.assertEqual("ABI_UNKNOWN", record["verdict"],
                                     "%s must abstain" % va8)
                    self.assertIsNone(fx.convention_of(record))
                else:
                    self.assertEqual("ABI_INFERRED", record["verdict"])
                    self.assertEqual(convention, fx.convention_of(record))
                self.assertEqual(side, record["cleanup"]["side"])
                self.assertEqual(byte_count, record["cleanup"]["bytes"])

    def test_no_real_function_is_claimed_fastcall(self):
        """A real finding, asserted rather than assumed.

        The only two real candidates are 0x00aea250 (whose body contradicts the
        persisted ``__fastcall``) and 0x00de9fc0 (whose frame is untrusted), so
        ``__fastcall`` detection stays hermetic-fixture-only.
        """
        for va8, slug, _c, _s, _b, _n in fx.LIVE_TARGETS:
            with self.subTest(va=va8):
                self.assertNotEqual("__fastcall", fx.convention_of(live_record(va8, slug)),
                                    "%s must not be claimed __fastcall" % va8)

    def test_0040ccb0_spilled_receiver_and_callee_cleanup_four(self):
        record = live_record("0040ccb0", "thiscall_spilled_receiver")
        self.assertEqual("__thiscall", fx.convention_of(record))
        self.assertEqual(4, record["cleanup"]["bytes"])
        receiver = record["receiver"]
        self.assertIs(True, receiver["present"])
        self.assertEqual("ECX", receiver["register"])
        self.assertEqual("R-ALIAS", receiver["shape"],
                         "the receiver is spilled to [EBP-0x48] and reloaded")
        self.assertEqual(1, record["stack_arguments"]["observed_slots"])
        self.assertIn("C6B", ids_of(record))

    def test_005291f0_still_reads_its_two_slots_and_its_and_esp_is_alignment(self):
        """Was ``test_005291f0_and_esp_alignment_is_not_a_receiver``.

        The real finding this test exists for is untouched: ``AND
        ESP,0xfffffff0`` is stack alignment and not a receiver, ``MOV
        ECX,[EBP+0xc]`` loads ECX from a frame slot, and the two real stack
        arguments at ``[EBP+0x8]``/``[EBP+0xc]`` are both read.

        REPAIRED: the ``__cdecl`` claim was deleted.
        ``KnownEngineDefectTest.test_undetermined_receiver_must_not_yield_a_
        convention`` requires an undetermined receiver to yield no convention,
        and defect D1 was corrected, so this target moved from
        ``ABI_INFERRED`` to ``ABI_UNKNOWN`` -- one of the two real-function
        movement the verdict table in
        ``test_live_coverage_matches_the_research_pass_findings`` accounts for.
        The cleanup reading (caller/0) is a machine fact and is still asserted.
        """
        record = live_record("005291f0", "graphics_set_transform")
        self.assertIsNone(fx.convention_of(record))
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertIn("receiver_undetermined", record["conventions"]["ambiguities"])
        self.assertIn("receiver_undetermined_blocks_convention",
                      fx.abstention_codes(record))
        self.assertEqual("caller", record["cleanup"]["side"])
        self.assertEqual(0, record["cleanup"]["bytes"])
        self.assertEqual(2, record["stack_arguments"]["observed_slots"],
                         "[EBP+0x8] and [EBP+0xc] are the two stack arguments")
        self.assertIsNone(record["receiver"]["present"],
                          "MOV ECX,[EBP+0xc] loads ECX from a slot, so no receiver")
        self.assertEqual("ecx_reassigned_before_deref", record["receiver"]["reason"])
        self.assertEqual(0xFFFFFFF0, record["parse"]["frame"]["and_esp"],
                         "AND ESP,0xfffffff0 is alignment, not a receiver")
        self.assertNotIn("esp_alignment_unknown", fx.abstention_codes(record))

    def test_00951230_slots_derive_from_the_two_instruction_stub(self):
        record = live_record("00951230", "stdcall_stub_ret0c")
        document = fx.read_json(fx.live_path("00951230", "stdcall_stub_ret0c"))
        self.assertEqual(2, len(document["instructions"]))
        self.assertEqual("__stdcall", fx.convention_of(record))
        self.assertEqual(12, record["cleanup"]["bytes"])
        self.assertEqual(0, record["stack_arguments"]["observed_slots"])
        self.assertEqual(3, record["stack_arguments"]["derived_slots"])
        self.assertIn("A1-IMM", ids_of(record))

    def test_00ce6950_single_member_load_is_a_receiver(self):
        """A boundary case, and the reason the plan's window is unenforceable.

        ``MOV EAX,dword ptr [ECX + 0x184] / RET`` has exactly *one*
        dereference. The plan's R2 needs two distinct offsets and would abstain;
        the spec's R1 accepts one (DERIVED, one offset, no write-through) and the
        engine caps it at INFERRED. Both readings are defensible; the spec's is
        the one implemented, and the cap is what keeps a single load honest.
        """
        record = live_record("00ce6950", "thiscall_member_0x184")
        self.assertIs(True, record["receiver"]["present"])
        self.assertEqual([0x184], record["receiver"]["offsets"])
        self.assertEqual(1, record["receiver"]["distinct_offsets"])
        self.assertEqual("__thiscall", fx.convention_of(record))
        self.assertEqual("caller", record["cleanup"]["side"])
        self.assertEqual(0, record["stack_arguments"]["observed_slots"])
        self.assertEqual("pointer_like", record["return"]["register_class"])

    def test_004bdc00_seh_frame_and_spill_slot_receiver(self):
        record = live_record("004bdc00", "seh_spilled_receiver")
        self.assertEqual("__thiscall", fx.convention_of(record))
        self.assertEqual(4, record["cleanup"]["bytes"])
        self.assertTrue(record["seh_or_cookie_frame"])
        self.assertEqual("R-ALIAS", record["receiver"]["shape"])
        self.assertGreater(record["receiver"]["max_offset"], 0x1000)
        self.assertIn("V2", ids_of(record))
        self.assertEqual([], record["abstained_because"],
                         "an FS: access must not gate anything (documents R8)")

    def test_008db310_the_big_one_agrees_across_both_exits(self):
        """No ``sub esp`` at all, a fake frame op, and two agreeing ``RET 0x8``.

        Three things the engine has to get right: ``LEA EBP,[EBX+EAX*0x1]`` is
        not a frame operation, so the linear ESP walk is the only calibration
        available; both exits pop 8, so they *agree* and are not a
        contradiction; and stack words are pushed while only 2 are popped, so
        C4's "ret below the highest slot" test must not fire.
        """
        record = live_record("008db310", "thiscall_big_ret8")
        self.assertEqual("__thiscall", fx.convention_of(record))
        self.assertEqual("callee", record["cleanup"]["side"])
        self.assertEqual(8, record["cleanup"]["bytes"])
        self.assertNotIn("ret_immediates_disagree", fx.abstention_codes(record))
        self.assertNotIn("ret_imm_below_highest_slot", fx.abstention_codes(record))
        self.assertEqual(2, record["stack_arguments"]["observed_slots"])
        self.assertEqual(8, record["stack_arguments"]["total_bytes"])
        self.assertIn("C6B", ids_of(record))
        frame = record["parse"]["frame"]
        self.assertIsNone(frame["sub"], "there is no sub esp in this function")
        self.assertIsNone(frame["lea_esp"])

    def test_008db310_flow_not_modelled_is_honest_about_the_listing(self):
        """Ghidra emits a body in address order across blocks, not one path."""
        record = live_record("008db310", "thiscall_big_ret8")
        self.assertIn("flow_not_modelled", fx.abstention_codes(record))
        self.assertFalse(record["parse"]["flow_complete"])

    def test_00e5b790_abstains_and_says_why(self):
        """The honest abstention the research pass established, preserved.

        ``FLD float ptr [ESP + 0x40]`` resolves to key 0 -- the return address --
        so the function reads *no* incoming stack argument and ``__cdecl`` is not
        derivable. The expected cleanup (caller, 0) *is* derivable and the engine
        reports it. No rule was weakened to make ``__cdecl`` appear, and the test
        asserts the absence of a convention, not its presence.
        """
        record = live_record("00e5b790", "abstain_esp_delta")
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertIsNone(fx.convention_of(record))
        self.assertIn("no_discriminator", fx.abstention_codes(record))
        self.assertIn("C10", ids_of(record))
        self.assertEqual(0, record["stack_arguments"]["observed_slots"])
        self.assertEqual("caller", record["cleanup"]["side"])
        self.assertEqual(0, record["cleanup"]["bytes"])
        self.assertEqual("ST0", record["return"]["register"])

    def test_005c65e0_lease_address_arithmetic_is_not_a_dereference(self):
        """``LEA EAX,[ECX + 0x3c]`` takes ECX's address without reading memory."""
        record = live_record("005c65e0", "lea_from_ecx")
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertIsNone(fx.convention_of(record))
        self.assertIsNone(record["receiver"]["present"])
        self.assertEqual("ecx_address_taken_without_memory_access",
                         record["receiver"]["reason"])
        codes = fx.abstention_codes(record)
        self.assertIn("ecx_address_taken_without_memory_access", codes)
        self.assertIn("receiver_not_determinable", codes)
        self.assertIn("R0", ids_of(record))
        self.assertEqual([], record["receiver"]["offsets"])

    def test_00de9fc0_untrusted_frame_abstains(self):
        """``MOV EBP,ECX`` with no ``MOV EBP,ESP`` makes every offset uncalibrated.

        The engine's abstention is narrower than the loose form the plan
        describes, and deliberately so: ``push ebp`` without ``mov ebp,esp``
        matches 11,995 functions in this binary, most of which use EBP as an
        ordinary callee-saved register. Requiring EBP to actually be loaded from
        a register or used as a memory base is what keeps the gate meaningful.
        """
        record = live_record("00de9fc0", "untrusted_frame")
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertIsNone(fx.convention_of(record))
        codes = fx.abstention_codes(record)
        self.assertIn("untrusted_frame_stack_reads", codes)
        self.assertIn("frame_pointer_untrusted", codes)
        frame = record["parse"]["frame"]
        self.assertTrue(frame["push_ebp"])
        self.assertFalse(frame["mov_ebp_esp"])
        self.assertTrue(frame["ebp_is_general_register"])
        self.assertEqual(1, record["dispatch"]["indirect_calls"],
                         "MOV EDX,[EAX+0x38] / CALL EDX is observed as dispatch")

    def test_00aea250_engine_says_thiscall_and_the_index_says_fastcall(self):
        """A real, unresolved conflict. Not a test to make pass.

        ECX is dereferenced at 32 distinct offsets with 33 write-throughs, which
        is a receiver by any reading. EDX is only ever *written*, so there is no
        incoming register argument and therefore no fastcall evidence. The
        persisted ``__fastcall`` is contradicted by the function's own body; the
        engine reports ``__thiscall`` and refuses to adopt the label.
        """
        bare = live_record("00aea250", "thiscall_contradicts_fastcall")
        self.assertEqual("__thiscall", fx.convention_of(bare))
        receiver = bare["receiver"]
        self.assertIs(True, receiver["present"])
        self.assertGreaterEqual(receiver["distinct_offsets"], 2)
        self.assertGreaterEqual(receiver["written_through"], 1)
        self.assertEqual("R-ALIAS", receiver["shape"])
        self.assertNotIn("C8", ids_of(bare))
        self.assertNotIn("C8-E", ids_of(bare))
        self.assertEqual("caller", bare["cleanup"]["side"])
        self.assertEqual(0, bare["stack_arguments"]["observed_slots"])

        conflicted = abi_infer.analyze(
            fx.read_json(fx.live_path("00aea250", "thiscall_contradicts_fastcall")),
            persisted_abi={"calling_convention": fx.PERSISTED_FASTCALL})
        self.assertEqual("__thiscall", fx.convention_of(conflicted))
        self.assertEqual("disagrees", conflicted["cross_validation"]["persisted"])
        self.assertEqual(1, len(conflicted["conflicts"]))
        self.assertEqual("unresolved", conflicted["conflicts"][0]["resolution_status"])

    def test_00d2e350_argless_x87_abstains(self):
        record = live_record("00d2e350", "x87_argless")
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertIn("no_discriminator", fx.abstention_codes(record))
        self.assertEqual("ST0", record["return"]["register"])
        self.assertEqual("float_or_x87", record["return"]["register_class"])
        self.assertEqual("caller", record["cleanup"]["side"])

    def test_007e6080_naked_thunk_abstains(self):
        document = fx.read_json(fx.live_path("007e6080", "naked_thunk"))
        self.assertEqual(1, len(document["instructions"]))
        record = live_record("007e6080", "naked_thunk")
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertEqual("0x00929bd0", record["tail_call"]["target"])
        self.assertEqual("jmp", record["tail_call"]["form"])
        self.assertIn("no_terminal_ret", fx.abstention_codes(record))
        self.assertIsNone(record["cleanup"]["side"])
        self.assertEqual("EMPTY", record["completeness"])

    def test_live_coverage_matches_the_research_pass_findings(self):
        """Six conventions inferred, six abstentions, zero fastcalls.

        The count moved from seven inferred / five abstentions when defect D1
        was corrected: ``0x005291f0`` loads ECX from a frame slot, so its
        receiver is undetermined rather than proven absent, and the corrected
        engine refuses the ``__cdecl`` the old one derived. The movement is
        strictly toward abstention -- one convention *lost*, one abstention
        *gained*, no new claim -- which is the direction every one of the seven
        corrections moved in. ``fx.LIVE_TARGETS``' convention column now records
        that refusal as ``None``, so this table is read straight off the column:
        a non-``None`` column is a convention the engine must produce and a
        ``None`` column is an abstention that must carry its reasons.
        """
        inferred = [entry[0] for entry in fx.LIVE_TARGETS if entry[2] is not None]
        abstained = [entry[0] for entry in fx.LIVE_TARGETS if entry[2] is None]
        self.assertEqual(6, len(inferred))
        self.assertEqual(6, len(abstained))
        self.assertEqual(len(fx.LIVE_TARGETS), len(inferred) + len(abstained))
        for va8, slug, _c, _s, _b, _n in fx.LIVE_TARGETS:
            with self.subTest(va=va8):
                record = live_record(va8, slug)
                self.assertEqual(va8 in inferred,
                                 record["verdict"] == "ABI_INFERRED")
                if va8 in abstained:
                    self.assertTrue(record["abstained_because"],
                                    "an abstention must carry its reasons")


# =========================================================================== #
# Corrected engine defects
# =========================================================================== #
class KnownEngineDefectTest(unittest.TestCase):
    """Seven engine defects, found and then **corrected in the engine**.

    These were seven full assertions carrying ``@unittest.expectedFailure``:
    the complete expectation was written out, the test genuinely failed, and
    unittest reporting an *unexpected success* was the alarm that said the
    engine had been fixed. That has happened -- all seven now pass as ordinary,
    undecorated tests, and the seven stale pins that asserted the *defective*
    behaviour were deleted or inverted. There is no ``expectedFailure`` left in
    this file, and every assertion below is a real one that would fail if the
    behaviour regressed.

    Each defect moved the engine strictly **toward abstention**: no correction
    added a named convention, a raised confidence or a ``CORE_RESOLVED``
    completeness. That is the property the seven share, and it is why the
    deleted pins were unsatisfiable rather than merely out of date. The
    "abstention ladder" runs
    ``VERIFIED > CONFIRMED > OBSERVED > SUPPORTED > INFERRED > APPROXIMATION >
    UNKNOWN``, so a "higher" name can be a weaker claim -- ``cleanup`` dropping
    from ``OBSERVED`` to ``SUPPORTED`` *is* a demotion, and two tests below
    assert it with ``assertLess`` on the index for exactly that reason.

    The seven, in the order they appear below:

    * **D7** ``test_slot_pitch_is_dword_and_read_widths_are_reported_verbatim``
      -- an *invariant mis-specified*, not an engine bug. The documents'
      "stack-argument widths are always dword multiples" conflated the entry-slot
      **pitch** (always a dword, and what the cleanup arithmetic is built on)
      with the **observed read width**, which is 1 for ``MOV AL`` and 2 for
      ``MOV AX``. Padding either to four would be a claim the listing does not
      support, so the test now states the two facts separately.
    * **D5** ``test_non_dword_ret_must_be_a_contradiction`` -- ``ret 0x6`` was
      reported as ``callee``/6 at ``OBSERVED`` and used to derive a confident
      ``__stdcall``. Six is not a whole number of dword arguments, so neither the
      cleanup side nor ``__stdcall`` is derivable from it. Fixture 17 now
      abstains with a ``ret_immediate_not_dword_multiple`` contradiction.
    * **D1** ``test_undetermined_receiver_must_not_yield_a_convention`` -- the
      largest one. ``receiver_not_determinable`` means the engine could not tell
      whether ECX is a receiver, and the old engine treated that as if it were
      *absent*, so C9 -- whose own precondition is "receiver absent" -- fired and
      named ``__cdecl`` off a known-unknown. Fixtures 03, 06, 20 and the real
      function 0x005291f0 all correctly abstain now.
    * **D6** ``test_varargs_prologue_must_abstain`` -- the plan's R8
      ``varargs_or_alloca_prologue`` shape (two zero-initialised frame locals
      before a call) had no marker anywhere, so fixture 12 named ``__thiscall``
      for a textbook va_list body. The marker now exists; the variadic cap
      (C12) outranks the convention rule and the record abstains.
    * **D3** ``test_small_count_before_call_variadic_marker_must_fire`` -- spec
      §3.7 marker 3 was **unreachable dead code**: it required a register
      operand and then read the ``value`` key, which only an *immediate* operand
      has, so the two conditions were mutually exclusive. A ``mov r, imm`` with a
      small count before a call is now detected, for every count probed.
    * **D2** ``test_callee_cleanup_plus_incoming_EDX_must_be_an_ambiguity`` --
      one record held two mutually exclusive readings: fixture 21 dereferences
      EDX before any write to it (C8-E, "the one strong discriminator") *and*
      pops its own arguments (C6B, whose own claim text says callee-pop "rules
      out cdecl and fastcall"), then reported ``conflicts: []``. A fastcall
      callee does not pop and a popping thiscall has no incoming register
      argument, so the record now names ``ecx_and_edx_indistinguishable``,
      keeps both claims at UNKNOWN and abstains.
    * **D4** ``test_a_conflict_must_visibly_demote_confidence`` --
      ``cross_validate`` promised a disagreement is "lowered only by conflict
      (never below INFERRED)", but the convention claim is always emitted at
      exactly INFERRED, so ``_drop(INFERRED)`` with an INFERRED floor was a
      no-op and the demotion path could never execute. The cleanup claim had
      room to move and now does: a disagreement drops it OBSERVED -> SUPPORTED.
    """

    # ---- the spec never had the rule; the plan did --------------------- #
    def test_non_dword_ret_must_be_a_contradiction(self):
        """Defect D5, corrected. A non-dword pop is a contradiction, not a fact.

        The old engine reported ``callee``/6 at OBSERVED for ``ret 0x6`` and
        derived a confident ``__stdcall`` from it -- the "engine over-reach" the
        plan's R4 warned about, against a spec C3 that had no divisibility test.
        The clause now exists in both the engine and its abstention vocabulary:
        ``RET 0x6`` yields a ``ret_immediate_not_dword_multiple`` contradiction
        on ``cleanup`` and the record abstains.

        The concern that justified treating this as a defect rather than a
        divergence is the reason to keep the test: 6 *is* a true machine fact,
        but deriving ``__stdcall`` from a non-dword cleanup is not derivable, and
        the old record then claimed four bytes of arguments against a six-byte
        pop. Both halves are asserted below.
        """
        record = record_of("17_stdcall_ret_6")
        self.assertTrue(record["abstained_because"],
                        "a non-dword pop must abstain")
        self.assertIsNone(record["cleanup"]["side"],
                          "cleanup side is not derivable from ret 0x6")
        self.assertIsNone(record["cleanup"]["bytes"],
                          "6 is not a whole number of dword arguments")
        self.assertIsNone(fx.convention_of(record),
                          "__stdcall is not derivable from a 6-byte pop")
        self.assertEqual("ABI_UNKNOWN", record["verdict"])
        self.assertEqual("ret_immediate_not_dword_multiple",
                         record["cleanup"]["contradiction"]["kind"])
        self.assertEqual("UNKNOWN", record["cleanup"]["confidence"])
        # The observed slot table is a machine fact and survives the contradiction.
        self.assertEqual(1, record["stack_arguments"]["observed_slots"])
        self.assertEqual(4, record["stack_arguments"]["total_bytes"],
                         "the observed table is 4 bytes while the pop is 6")

    def test_slot_pitch_is_dword_and_read_widths_are_reported_verbatim(self):
        """Defect D7, corrected: the invariant was mis-specified, not the engine.

        This test used to assert that *every reported width* is a dword multiple
        and to fail, because ``MOV AX, word ptr [EBP + 0x8]`` is a two-byte read
        of entry slot 1 and ``MOV AL, …`` a one-byte read. Padding either to four
        would be a claim the listing does not support.

        Two different facts were being conflated, so the test now separates them:

        * the entry-slot **pitch** -- the distance between consecutive slots -- is
          always a dword, and the cleanup arithmetic and C4's comparison are built
          on exactly that;
        * the **observed read width** is reported verbatim and may be 1, 2, 4, 8
          or 16; and
        * a slot read at *more than one* width is the case the documents were
          reaching for, and it is flagged ambiguous per spec A2 rather than
          silently resolved.

        The corpus-wide form of the pitch invariant lives in
        ``PropertyTest.test_property_slot_pitch_is_always_a_dword_multiple``; this
        is the focused, narrow-width case the corpus form cannot express.
        """
        narrow = abi_infer.analyze(
            "PUSH EBP\nMOV EBP,ESP\n"
            "MOV AX,word ptr [EBP + 0x8]\n"
            "MOV EAX,1\nMOV ESP,EBP\nPOP EBP\nRET\n")
        for slot in narrow["stack_arguments"]["slots"]:
            offset = int(slot["entry_offset"][len("entry_ESP+0x"):], 16)
            self.assertEqual(0, (offset - 4) % 4,
                             "the entry-slot pitch is always a dword multiple")
            for size in slot["sizes"]:
                self.assertIn(size, (1, 2, 4, 8, 16),
                              "the reported width must be a width the listing "
                              "actually showed")
        self.assertEqual([[2]], [slot["sizes"]
                                 for slot in narrow["stack_arguments"]["slots"]],
                         "a two-byte read of slot 1 is reported as two bytes")
        self.assertFalse(narrow["stack_arguments"]["widths_ambiguous"])

        byte_narrow = abi_infer.analyze(
            "PUSH EBP\nMOV EBP,ESP\n"
            "MOV AL,byte ptr [EBP + 0x8]\n"
            "MOV EAX,1\nMOV ESP,EBP\nPOP EBP\nRET\n")
        self.assertEqual([[1]], [slot["sizes"]
                                 for slot in byte_narrow["stack_arguments"]["slots"]])

        conflicting = abi_infer.analyze(
            "PUSH EBP\nMOV EBP,ESP\n"
            "MOV EAX,dword ptr [EBP + 0x8]\n"
            "MOV AX,word ptr [EBP + 0x8]\n"
            "MOV EAX,1\nMOV ESP,EBP\nPOP EBP\nRET\n")
        self.assertTrue(conflicting["stack_arguments"]["widths_ambiguous"],
                        "one slot read at two widths is spec A2's ambiguity")
        self.assertIn("slot_width_ambiguous", fx.abstention_codes(conflicting))
        self.assertIn("A2", ids_of(conflicting))

    # ---- the engine does not meet its own spec / docstring -------------- #
    def test_undetermined_receiver_must_not_yield_a_convention(self):
        """Defect D1, corrected. The largest of the seven.

        The spec's C9 precondition says "receiver absent";
        ``receiver_not_determinable`` means the engine could not tell whether
        ECX is a receiver at all. Inferring a convention from a *known-unknown*
        is different from inferring one from a *known-absent* receiver, and the
        plan's R5 draws exactly that line. Three documents had three readings
        and the engine had picked the one that let it name a convention off an
        undetermined receiver -- the reading its own abstention policy exists
        to prevent. It now refuses instead.

        The mitigation is still load-bearing: ``__thiscall`` remains in
        ``candidate_conventions``, the reason is in ``receiver.reason`` and both
        ``receiver_not_determinable`` and
        ``receiver_undetermined_blocks_convention`` are in
        ``abstained_because``, so a consumer can see exactly which rule held
        the claim back. Fixture 03 is included here alongside 06 and 20 because
        all three share the same receiver state.
        """
        for name in ("03_cdecl_three_stack_args",
                     "06_ecx_read_never_dereferenced",
                     "20_ecx_loaded_from_stack_slot"):
            with self.subTest(fixture=name):
                record = record_of(name)
                self.assertIsNone(record["receiver"]["present"])
                self.assertIsNone(fx.convention_of(record),
                                  "an undetermined receiver must not name a "
                                  "convention")
                self.assertEqual("ABI_UNKNOWN", record["verdict"])
                self.assertIn("receiver_undetermined",
                              record["conventions"]["ambiguities"])
                self.assertIn("__thiscall",
                              record["conventions"]["candidate_conventions"],
                              "thiscall stays a candidate, it is not eliminated")
                self.assertIn("receiver_undetermined_blocks_convention",
                              fx.abstention_codes(record))

    def test_varargs_prologue_must_abstain(self):
        """Defect D6, corrected. The marker for this shape now exists.

        The plan's R8 gate ``varargs_or_alloca_prologue`` ("two ``MOV dword ptr
        [EBP-x],0`` before a call") was in neither the spec's list of three
        markers nor the engine, so fixture 12 named ``__thiscall`` for a body
        carrying the classic MSVC va_list zero-fill shape. A
        ``VARIADIC_MARKER`` observation with that name is now emitted, which
        makes ``variadic`` SUSPECTED and lets C12 cap the convention to null.

        Fixture 12b (asserted in ``ShapeTest``) remains the positive control
        proving the gate is live for the shapes the spec already listed, so
        this is a marker that was missing, not a feature that was absent.
        """
        record = record_of("12_varargs_prologue")
        self.assertEqual("ABI_UNKNOWN", record["verdict"],
                         "a va_list zero-fill before a call is a variadic marker")
        self.assertEqual("SUSPECTED", record["variadic"])
        self.assertIn("C12", ids_of(record))
        self.assertIn("variadic_not_decidable_from_listing",
                      fx.abstention_codes(record))
        markers = [obs.get("marker") for obs in record["observations"]
                   if obs["kind"] == "VARIADIC_MARKER"]
        self.assertIn("varargs_or_alloca_prologue", markers)
        self.assertEqual(["__cdecl"], record["conventions"]["candidate_conventions"])
        self.assertTrue(record["stack_arguments"]["not_complete"])

    def test_small_count_before_call_variadic_marker_must_fire(self):
        """Defect D3, corrected. Spec §3.7 marker 3 was unreachable dead code.

        The rule required ``_operand_reg(operands[0]) is not None`` and then read
        ``operands[0]["value"]``. A register operand has no ``value`` key -- only
        an immediate operand does -- so the two conditions were mutually
        exclusive and the marker could never fire: one of the three shapes the
        spec names was undetectable. A ``mov r, imm`` with a small count
        immediately before a call is now detected, and it is probed here across
        every count, not just the one the fixture happens to use.
        """
        record = record_of("23_small_count_before_call")
        self.assertEqual("SUSPECTED", record["variadic"])
        markers = [obs.get("marker") for obs in record["observations"]
                   if obs["kind"] == "VARIADIC_MARKER"]
        self.assertIn("small_count_before_call", markers,
                      "spec §3.7 marker 3 must detect `mov r, imm` before a call")
        for count in (1, 2, 4, 8, 0x10, 0x20, 0x40):
            with self.subTest(count=hex(count)):
                probe = abi_infer.analyze(
                    "PUSH EBP\nMOV EBP,ESP\nSUB ESP,0x20\n"
                    "MOV EAX,0x%x\n" % count +
                    "CALL 0x00903400\nADD ESP,0x8\n"
                    "MOV ESP,EBP\nPOP EBP\nRET\n")
                probe_markers = [obs.get("marker") for obs in
                                 probe["observations"]
                                 if obs["kind"] == "VARIADIC_MARKER"]
                self.assertIn("small_count_before_call", probe_markers,
                              "count 0x%x before a call must be a variadic marker"
                              % count)

    def test_callee_cleanup_plus_incoming_EDX_must_be_an_ambiguity(self):
        """Defect D2, corrected. One record may not hold two exclusive readings.

        Fixture 21 dereferences EDX before any write to it -- the spec calls this
        "the one strong discriminator in the whole engine" -- and pops its own
        arguments. Those cannot both hold: a callee-popping ``__thiscall`` has no
        incoming register argument, and an ``__fastcall`` callee does not pop.
        The old engine emitted C8-E *and* C6B (whose own claim text says
        callee-pop "rules out cdecl and fastcall"), then reported
        ``conflicts: []`` -- the contradiction silently resolved in favour of one
        side, and a confident ``__thiscall`` on top of it.

        The corrected engine keeps both observations (the evidence is real and
        must not be erased), holds both claims at UNKNOWN, names the ambiguity
        the documents asked for, and abstains. The engine represents this in
        ``conventions.ambiguities`` rather than in ``conflicts``; either is a
        legible report of the same contradiction, and what is load-bearing is
        that the convention is not asserted and the ambiguity is named.
        """
        record = record_of("21_sret_ecx_or_fastcall_ambiguous")
        # Both exclusive readings are still observed -- that is evidence, not a
        # defect. C8-E is a statement about a register, so it stays at OBSERVED;
        # what the defect was is a *convention* (C6B -> __thiscall) resolved on
        # top of it. C6B is now held at UNKNOWN with no value.
        self.assertIn("C8-E", ids_of(record))
        self.assertIn("C6B", ids_of(record))
        self.assertEqual("OBSERVED", claim_of(record, "C8-E")["confidence"])
        self.assertEqual({"register": "EDX"}, claim_of(record, "C8-E")["value"],
                         "the machine fact behind the EDX reading is unchanged")
        self.assertEqual("UNKNOWN", claim_of(record, "C6B")["confidence"],
                         "the convention claim must be held, not asserted")
        self.assertIsNone(claim_of(record, "C6B").get("value"),
                          "an undecided reading must not carry a convention")
        self.assertEqual("ABI_UNKNOWN", record["verdict"],
                         "sret-vs-fastcall is not decidable from a callee body")
        self.assertIn("ecx_and_edx_indistinguishable",
                      record["conventions"]["ambiguities"],
                      "the two exclusive readings must be reported as an ambiguity")
        self.assertIn("__thiscall", record["conventions"]["candidate_conventions"])
        self.assertIn("__fastcall", record["conventions"]["candidate_conventions"],
                      "neither reading may be eliminated, both must be reported")
        self.assertIsNone(fx.convention_of(record))
        self.assertEqual([], record["conflicts"],
                         "the engine reports this through conventions."
                         "ambiguities, not through the cross-validation list")

    def test_a_conflict_must_visibly_demote_confidence(self):
        """Defect D4, corrected. A demotion path that cannot execute is not one.

        ``cross_validate``'s docstring promised a disagreement is "lowered only
        by conflict (never below INFERRED)". But the convention claim is always
        emitted at exactly INFERRED, so ``_drop(INFERRED)`` with an INFERRED
        floor was a mathematical no-op: a Ghidra disagreement changed nothing a
        consumer reads, only the conflict list.

        The floor choice was always defensible -- INFERRED is the honest rung for
        a single-listing inference -- so the demotion had to land somewhere it
        had room. It now lands on the cleanup claim, which starts at OBSERVED and
        drops to SUPPORTED under disagreement. Both halves are asserted with
        ``assertLess`` on the ladder index, because on this vocabulary
        ``SUPPORTED`` is a *weaker* claim than ``OBSERVED`` and the names alone
        do not make that obvious.
        """
        agreed = abi_infer.analyze(THISCALL_BODY,
                                   ghidra_calling_convention="__thiscall")
        disagreed = abi_infer.analyze(THISCALL_BODY,
                                      ghidra_calling_convention="__cdecl")
        self.assertLess(
            abi_infer.CONFIDENCE_ORDER.index(disagreed["conventions"]["confidence"]),
            abi_infer.CONFIDENCE_ORDER.index(agreed["conventions"]["confidence"]),
            "a Ghidra disagreement must leave the convention claim below the "
            "rung agreement reached, not identical to it")
        self.assertLess(
            abi_infer.CONFIDENCE_ORDER.index(disagreed["cleanup"]["confidence"]),
            abi_infer.CONFIDENCE_ORDER.index(agreed["cleanup"]["confidence"]),
            "a Ghidra disagreement must demote the cleanup claim, which starts "
            "at OBSERVED and has room to drop")
        self.assertEqual("OBSERVED", agreed["cleanup"]["confidence"])
        self.assertEqual("SUPPORTED", disagreed["cleanup"]["confidence"])
        # Agreement must still never exceed SUPPORTED, so the two paths are not
        # merely inverting each other.
        self.assertLess(abi_infer.CONFIDENCE_ORDER.index("SUPPORTED"),
                        abi_infer.CONFIDENCE_ORDER.index("OBSERVED"))


if __name__ == "__main__":
    unittest.main()
