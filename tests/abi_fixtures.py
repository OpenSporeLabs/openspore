"""Shared fixture corpus + helpers for the ABI-inference test suite.

Not named ``test_*`` on purpose: unittest discovery must not collect this
module (house pattern, same as ``tests/orchestration_fixture.py``). The engine
under test is ``tools/reconstruction_tooling/abi_infer.py``; everything here is
data and pure helpers, no Ghidra, no network, no clock, no unseeded random.

Two fixture families
--------------------
* **Hermetic** (``tests/fixtures/abi/<nn>_<slug>.asm``): hand-written
  instruction streams in Intel syntax, one per requirement. Their canonical
  text lives in :data:`FIXTURES` so ``tests/fixtures/gen_abi_fixtures.py`` can
  regenerate the files and FATAL on byte drift; the *tests* read the bytes from
  disk, so a hand-edited ``.asm`` is genuinely what gets analysed.
* **Live** (``tests/fixtures/abi/live/<va8>_<slug>.json``): verbatim
  ``/disassemble_function`` response bodies captured from the GhidraMCP headless
  bridge by ``tests/capture_abi_golden.py --record``. Committed, so the CI suite
  needs no bridge at all.

Documented divergences from ``docs/tooling/abi-inference-tests.md``
---------------------------------------------------------------
The test plan and ``docs/tooling/abi-inference-spec.md`` were written against an
*earlier* record schema (``O1``/``I1`` ids, a ``PASS``/``SUPPORTED``/``WEAK``
confidence ladder, a ``shape`` field, ``verdict`` holding the convention name).
The landed engine deliberately emits a different, stricter document: ids are
``obs-0001``, the confidence ladder is the canonical 7-level
``knowledgegraph/scale.py`` vocabulary, ``completeness`` replaces ``shape``, and
``verdict`` is ``ABI_INFERRED``/``ABI_UNKNOWN`` while the convention itself
lives in ``conventions.calling_convention``.

Every divergence below is now encoded as an ordinary *passing* test of the
engine's current behaviour. The seven genuine engine defects that used to carry
``@unittest.expectedFailure`` (fixtures 21 and 23 plus the five D-series
corrections) have been **fixed in the engine**: those tests now pass
undecorated, and an unexpected success is no longer available as a fix alarm --
the engine's behaviour is pinned directly instead, so a regression fails the
suite. ``LIVE_TARGETS`` reflects the same corrected engine: a target the engine
now legitimately refuses carries ``None`` in its convention column, and the
reason it must abstain is in that row's note.
"""
import json
import os
import random
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FIXTURE_DIR = os.path.join(ROOT, "tests", "fixtures", "abi")
LIVE_DIR = os.path.join(FIXTURE_DIR, "live")
EXPECT_DIR = os.path.join(ROOT, "tests", "expected", "abi")
LIVE_EXPECT_DIR = os.path.join(EXPECT_DIR, "live")

# --------------------------------------------------------------------------
# Layout-invariance exclusion set.
#
# The engine's module docstring promises invariance "for every field except the
# provenance keys: the verbatim ``raw`` text, the ``at`` address and the
# ``index``-derived fields". These are exactly those, plus the three
# target/parse fields that exist only because an address column was supplied
# (``target.va``, ``target.syntax``, ``target.address_available``) and
# ``parse.declared_count``, which the engine only emits for the
# ``{"instructions": [...]}`` dict shape.
#
# ``parse.flow_complete`` is deliberately NOT in this set: it is an inference,
# not provenance, and it legitimately changes when an address column becomes
# available (a branch target absent from the listing can only be noticed then).
# ``test_layout_invariance_*`` therefore uses a straight-line body, and
# ``test_flow_complete_depends_on_address_availability`` pins the dependency
# explicitly rather than hiding it inside an exclusion.
# --------------------------------------------------------------------------
PROVENANCE_PATHS = (
    "$.content_sha256",
    "$.observations[].at",
    "$.observations[].raw",
    "$.observations[].index",
    "$.observations[].first_use",
    "$.observations[].first_write_index",
    "$.observations[].push_ebp_at",
    "$.observations[].mov_ebp_esp_at",
    "$.parse.layout",
    "$.parse.declared_count",
    "$.parse.frame.push_ebp_at",
    "$.parse.frame.mov_ebp_esp_at",
    "$.target.va",
    "$.target.syntax",
    "$.target.address_available",
)

# The engine's fixed claim order, read off the emission order in
# ``abi_infer._infer_rules``: cleanup (C1..C5) -> stack arguments (A1, A1-IMM,
# A2) -> receiver (R1, R0, R2) -> EDX register evidence (C8-E) -> variadic/SEH
# (V2) -> convention (C6, C6B, C7, C8, C9, C10, C11, C12) -> hidden return (S1,
# S2, S3) -> tail transfer (T1, T2) -> return (RT1..RT4) -> dispatch (D1).
# A repeated rule gets a ``#2`` suffix, so ids are compared on the base name.
CLAIM_ORDER = (
    "C1", "C2", "C3", "C4", "C5",
    "A1", "A1-IMM", "A2",
    "R1", "R0", "R2",
    "C8-E",
    "V1", "V2",
    "C6", "C6B", "C7", "C8", "C9", "C10", "C11", "C12",
    "S1", "S2", "S3",
    "T1", "T2",
    # RT4 (the bulk-write demotion) is emitted inside `_return_block` *before*
    # the RT1/RT2 pair it constrains, so it comes first here too.
    "RT4", "RT1", "RT2", "RT3",
    "D1",
)

# The Ghidra CodeBrowser rendering of fixture 01, used by the layout-invariance
# test as the third of four encodings of the same stream. The header rows and
# the byte column are what ``parse_listing`` must split off; the branch target
# 0x00401024 is deliberately *absent* from the listing, which is the real
# CodeBrowser shape.
CODEBROWSER_01 = """Listing  Address  Instruction  Bytes
-------  -------  -----------  -----
00401000  55             PUSH EBP
00401001  8bec           MOV EBP,ESP
00401003  83ec10         SUB ESP,0x10
00401006  8b4108         MOV EAX,dword ptr [ECX + 0x8]
0040100a  89410c         MOV dword ptr [ECX + 0xc],EAX
0040100d  8b4110         MOV EAX,dword ptr [ECX + 0x10]
00401011  83c004         ADD EAX,0x4
00401014  894114         MOV dword ptr [ECX + 0x14],EAX
00401018  8b4508         MOV EAX,dword ptr [EBP + 0x8]
0040101c  85c0           TEST EAX,EAX
0040101e  7404           JZ 0x00401024
00401020  8b4108         MOV EAX,dword ptr [ECX + 0x8]
00401023  89450c         MOV dword ptr [EBP + 0xc],EAX
00401026  89ec           MOV ESP,EBP
00401028  5d             POP EBP
00401029  c3             RET"""

# Address column for the JSON encoding of fixture 01. Deliberately non-uniform
# gaps, exactly like a real collector: the listing is a set of basic blocks
# emitted in address order, not one contiguous path.
JSON_ADDRESSES_01 = (
    "00401000", "00401001", "00401003", "00401006", "0040100a", "0040100d",
    "00401011", "00401014", "00401018", "0040101c", "0040101e", "00401020",
    "00401023", "00401026", "00401028", "00401029",
)

# FUZZ_SEED is asserted by the suite: the repo forbids unseeded randomness, and
# a corpus that is not reproducible cannot fail reproducibly.
FUZZ_SEED = 1234
GARBAGE_ALPHABET = "MOV PUSH RET CALL JMP 0x1EBPECXEDXESP[]+-, \n\t\r\x00\ufffd"


class Fixture(object):
    """One hermetic fixture: a stable id, the canonical bytes, and a note."""

    __slots__ = ("name", "blob", "note")

    def __init__(self, name, blob, note=""):
        self.name = name
        self.blob = blob if isinstance(blob, bytes) else blob.encode("utf-8")
        self.note = note

    @property
    def stem(self):
        return self.name[:-4] if self.name.endswith(".asm") else self.name

    @property
    def asm_path(self):
        return os.path.join(FIXTURE_DIR, self.stem + ".asm")

    @property
    def expected_path(self):
        return os.path.join(EXPECT_DIR, self.stem + ".json")

    def text(self):
        """The fixture as the engine will see it.

        ``.asm`` files are byte artefacts (fixture 15c is NUL and 0xFF bytes),
        so the decode is lossy-by-design and must be *stable*: the same bytes
        always decode to the same string, which is what makes the golden
        reproducible. ``surrogateescape`` is not used because the golden JSON
        would then hold un-encodable lone surrogates.
        """
        return self.blob.decode("utf-8", "replace")


def _asm(name, text, note=""):
    return Fixture(name, text, note)


# The 25 hermetic inputs. Numbering follows docs/tooling/abi-inference-tests.md
# §2.2 where a fixture exists there; 12b/22/23/24 are additions that the
# research pass's list did not need but the divergence tests do.
FIXTURES = (
    # --- requirement 1: the canonical __thiscall member -------------------- #
    _asm("01_thiscall_member.asm", """PUSH EBP
MOV EBP,ESP
SUB ESP,0x10
MOV EAX,dword ptr [ECX + 0x8]
MOV dword ptr [ECX + 0xc],EAX
MOV EAX,dword ptr [ECX + 0x10]
ADD EAX,0x4
MOV dword ptr [ECX + 0x14],EAX
MOV EAX,dword ptr [EBP + 0x8]
TEST EAX,EAX
JZ 0x00100050
MOV EAX,dword ptr [ECX + 0x8]
MOV dword ptr [EBP + 0xc],EAX
MOV ESP,EBP
POP EBP
RET
""", "spec §2.2 fixture 01; four ECX offsets, two of them written through"),

    # --- requirement 2: a hidden-sret CANDIDATE. sret.present is never True - #
    _asm("02_thiscall_sret_stack_buffer.asm", """PUSH EBP
MOV EBP,ESP
SUB ESP,0x20
MOV EAX,dword ptr [EBP + 0x8]
MOV dword ptr [EBP + -0x18],EAX
MOV EAX,dword ptr [ECX + 0x1c]
MOV dword ptr [EBP + -0x18],EAX
MOV EAX,dword ptr [ECX + 0x20]
MOV dword ptr [EBP + -0x1c],EAX
MOV EAX,dword ptr [EBP + 0xc]
MOV dword ptr [EBP + -0x18],EAX
MOV EAX,dword ptr [ECX + 0x24]
MOV dword ptr [EBP + -0x18],EAX
MOV EAX,dword ptr [EBP + 0x10]
MOV dword ptr [EBP + -0x1c],EAX
MOV EAX,dword ptr [ECX + 0x28]
MOV dword ptr [EBP + -0x1c],EAX
MOV ESP,EBP
POP EBP
RET 0xc
""", "three stack slots, a local buffer written from two of them, RET 0xc"),

    # --- requirement 3: __cdecl with 3 stack args -------------------------- #
    _asm("03_cdecl_three_stack_args.asm", """PUSH EBP
MOV EBP,ESP
SUB ESP,0x8
MOV EAX,dword ptr [EBP + 0x8]
MOV ECX,dword ptr [EBP + 0xc]
ADD EAX,ECX
MOV EDX,dword ptr [EBP + 0x10]
ADD EAX,EDX
MOV EAX,0x1
MOV ESP,EBP
POP EBP
RET
""", "ECX and EDX are *loaded from stack slots*, so neither is an incoming "
        "register argument; the trailing MOV EAX,1 makes the return integral"),

    # --- requirement 4: __stdcall, RET 0xc, slots from the immediate -------- #
    _asm("04_stdcall_ret_0xc.asm", """XOR AL,AL
RET 0xc
""", "no frame, no ECX; three words popped by the callee (real 0x00951230)"),

    # --- requirement 5: __fastcall, ECX and EDX both incoming --------------- #
    _asm("05_fastcall_ecx_edx.asm", """PUSH EBP
MOV EBP,ESP
MOV EAX,dword ptr [ECX + 0x4]
MOV EDX,dword ptr [EDX + 0x8]
ADD EAX,EDX
MOV dword ptr [ECX + 0x8],EAX
MOV EAX,dword ptr [ECX + 0xc]
ADD EAX,dword ptr [EDX + 0x10]
MOV ESP,EBP
POP EBP
RET
""", "the ONLY fixture in the corpus that may be claimed __fastcall"),

    # --- requirement 6: ECX read, never dereferenced (plan: MUST ABSTAIN) --- #
    _asm("06_ecx_read_never_dereferenced.asm", """PUSH EBP
MOV EBP,ESP
SUB ESP,0x8
MOV EAX,ECX
MOV dword ptr [EBP + -0x4],EAX
MOV EAX,dword ptr [EBP + 0x8]
TEST EAX,EAX
JZ 0x00200040
XOR EAX,EAX
MOV ESP,EBP
POP EBP
RET
""", "DIVERGENCE: plan R5 says ABI_UNKNOWN, engine says __cdecl"),

    # --- requirement 7: one implausible offset (plan: MUST ABSTAIN) --------- #
    _asm("07_ecx_single_implausible_offset.asm", """PUSH EBP
MOV EBP,ESP
MOV EAX,dword ptr [ECX + 0x4000]
RET
""", "DIVERGENCE: the engine applies NO plausibility window; see the "
         "PlausibilityWindowDivergence test class"),

    # --- requirement 8: frameless leaf (MUST ABSTAIN) ---------------------- #
    _asm("08_leaf_no_frame.asm", """MOV EAX,0x2a
RET
""", "observable, unclassifiable"),

    # --- requirement 9: naked JMP thunk (MUST ABSTAIN) --------------------- #
    _asm("09_naked_thunk.asm", """JMP 0x00929bd0
""", "real 0x007e6080 verbatim"),

    # --- requirement 10: two exits, DIFFERENT ret immediates ---------------- #
    _asm("10_contradictory_ret_immediates.asm", """PUSH EBP
MOV EBP,ESP
CMP dword ptr [EBP + 0x8],0x0
JNE 0x00300060
MOV EAX,dword ptr [ECX + 0x4]
MOV ESP,EBP
POP EBP
RET 0x4
JNE 0x00300090
MOV EAX,dword ptr [ECX + 0x8]
MOV ESP,EBP
POP EBP
RET 0x8
""", "DIVERGENCE from the plan on the vocabulary: the engine reports "
         "side CONFLICT / ret_immediates_disagree, which is what the spec's own "
         "F12 fragment says"),

    # --- requirement 11: a vtable-slot call ------------------------------- #
    _asm("11_vtable_slot_call.asm", """PUSH EBP
MOV EBP,ESP
MOV ECX,dword ptr [ECX + 0x20]
MOV EAX,dword ptr [ECX]
MOV EDX,dword ptr [EAX + 0x50]
CALL EDX
MOV EDX,dword ptr [EAX]
MOV ECX,EAX
MOV EAX,dword ptr [EDX + 0x38]
CALL EAX
XOR EAX,EAX
RET
""", "two-level dispatch, two indirect calls, no resolvable callee"),

    # --- requirement 12: variadic/alloca-looking (plan: MUST ABSTAIN) ------ #
    _asm("12_varargs_prologue.asm", """PUSH EBP
MOV EBP,ESP
SUB ESP,0x20
MOV dword ptr [EBP + -0x4],0x0
MOV EAX,dword ptr [EBP + 0x8]
TEST EAX,EAX
JNE 0x00400070
MOV dword ptr [EBP + -0x8],0x0
PUSH dword ptr [EBP + -0x8]
PUSH EAX
MOV ECX,dword ptr [ECX + 0x4]
CALL 0x00903400
ADD ESP,0x8
MOV dword ptr [EBP + -0x4],0x1
MOV EAX,dword ptr [EBP + 0xc]
RET
""", "DIVERGENCE: two zero-initialised locals before a call. Neither the spec "
         "nor the engine has a marker for this shape; 12b is the shape that "
         "does fire the real gate"),

    _asm("12b_variadic_huge_frame.asm", """PUSH EBP
MOV EBP,ESP
SUB ESP,0x2000
MOV EAX,dword ptr [ECX + 0x8]
MOV EAX,dword ptr [ECX + 0xc]
MOV EAX,dword ptr [EBP + 0x8]
MOV EDX,dword ptr [EBP + 0xc]
PUSH EDX
PUSH EAX
CALL 0x00903400
ADD ESP,0x8
MOV ESP,EBP
POP EBP
RET
""", "POSITIVE CONTROL: spec §3.6 marker 2 (sub esp,>0x1000 immediately before "
         "a call). Proves the variadic gate is live, which is what makes the 12 "
         "divergence a missing marker rather than a missing feature"),

    # --- requirement 13: pointer-like return ------------------------------- #
    _asm("13_pointer_return.asm", """PUSH EBP
MOV EBP,ESP
MOV EAX,dword ptr [EBP + 0x8]
RET
""", "one stack slot read into EAX, no frame write, no other use"),

    # --- requirement 14: integral return (plan: 'same path as 13') --------- #
    _asm("14_integral_return.asm", """PUSH EBP
MOV EBP,ESP
MOV EAX,0x1
RET
""", "DIVERGENCE: reads no argument at all, so the plan's 'same convention "
         "path as 13' is unsatisfiable; the engine abstains with "
         "no_discriminator"),

    # --- requirement 15: graceful abstention, five degenerate inputs -------- #
    Fixture("15a_empty.asm", b"", "zero bytes"),
    Fixture("15b_whitespace.asm", "   \n\n\t\n", "whitespace only"),
    Fixture("15c_binary_noise.asm",
            b"\x00\x00\xff\xfe\x01\x7f" + "�".encode("utf-8"),
            "NUL bytes, a lone 0xFF, a DEL and a UTF-8 replacement character"),
    _asm("15d_truncated.asm", """PUSH EBP
MOV EBP,ESP
SUB ESP,0x4
""", "a prefix of a longer function: no terminal return"),
    _asm("15e_prose.asm", """The function reads a member and writes it back.
This paragraph is English prose, not an assembly listing at all.
It mentions EAX, ECX and RET only as words, never as instructions.
""", "prose, not code"),

    # --- requirement 16: the AT&T twin of fixture 01 ----------------------- #
    Fixture("16_thiscall_member.att", """push %ebp
mov %esp,%ebp
sub $0x10,%esp
mov 0x8(%ecx),%eax
mov %eax,0xc(%ecx)
mov 0x10(%ecx),%eax
add $0x4,%eax
mov %eax,0x14(%ecx)
mov 0x8(%ebp),%eax
test %eax,%eax
je 0x00401024
mov 0x8(%ecx),%eax
mov %eax,0xc(%ebp)
mov %ebp,%esp
pop %ebp
ret
""", "the same stream as 01, AT&T encoding"),

    # --- Part B: a non-dword ret immediate --------------------------------- #
    _asm("17_stdcall_ret_6.asm", """PUSH EBP
MOV EBP,ESP
MOV EAX,dword ptr [EBP + 0x8]
MOV ESP,EBP
POP EBP
RET 0x6
""", "DIVERGENCE: the plan's R4 and invariant 11 demand a contradiction and no "
         "cleanup; the engine reports callee/6 and derives __stdcall"),

    # --- an argless x87 return (real 0x00d2e350) -------------------------- #
    _asm("18_argless_x87_return.asm", """FLD float ptr [0x0169e398]
RET
""", "return register ST0 recognised, convention still refused"),

    # --- a receiver recovered through its own spill slot (0x004bdc00) ------ #
    _asm("19_receiver_spilled_to_frame_slot.asm", """PUSH EBP
MOV EBP,ESP
SUB ESP,0x8
MOV dword ptr [EBP + -0x8],ECX
MOV EAX,dword ptr [0x016f2618]
MOV ECX,dword ptr FS:[0x2c]
MOV EDX,dword ptr [ECX + EAX*0x4]
MOV EAX,dword ptr [EBP + -0x8]
MOV dword ptr [EDX + 0x4],EAX
MOV ECX,dword ptr [EBP + 0x8]
PUSH ECX
MOV EDX,dword ptr [EBP + -0x8]
MOV EAX,dword ptr [EDX + 0x3a9c]
PUSH EAX
CALL 0x00903400
ADD ESP,0x8
MOV dword ptr [EBP + -0x4],EAX
MOV ESP,EBP
POP EBP
RET 0x4
""", "offset 0x3a9c = 15004; a receiver reached through a spill slot must not "
         "be windowed even if a window existed"),

    # --- ECX loaded from a stack slot (0x005291f0 trap) ------------------- #
    _asm("20_ecx_loaded_from_stack_slot.asm", """MOV EAX,dword ptr [ESP + 0x8]
MOV ECX,dword ptr [ESP + 0xc]
MOV EDX,dword ptr [ESP + 0x10]
MOV dword ptr [ECX],EAX
MOV EAX,dword ptr [ESP + 0x4]
MOV dword ptr [EDX],EAX
RET
""", "both ECX and EDX are STORE BASES; the most important negative control"),

    # --- sret-vs-fastcall ambiguity ---------------------------------------- #
    _asm("21_sret_ecx_or_fastcall_ambiguous.asm", """PUSH EBP
MOV EBP,ESP
SUB ESP,0x24
MOV dword ptr [EBP + -0x18],ECX
MOV EAX,dword ptr [EDX + 0x4]
MOV dword ptr [ECX],EAX
MOV EAX,dword ptr [EBP + 0x8]
MOV dword ptr [ECX + 0x4],EAX
MOV EAX,dword ptr [ECX + 0x8]
MOV ESP,EBP
POP EBP
RET 0x4
""", "DEFECT D2, corrected: EDX is dereferenced before any write (fastcall "
         "evidence) while callee cleanup selects C6B. The engine now holds both "
         "exclusive claims at UNKNOWN, names the ambiguity and abstains instead "
         "of resolving it in favour of one side"),

    # --- data, not code --------------------------------------------------- #
    _asm("22_data_bytes_no_mnemonic.asm", """00401000  8b01 0043 0a05 0000 00
00401008  c3             RET
""", "one data row then a real RET; the byte column is left-padded exactly as "
         "CodeBrowser prints it, so the RET is still recognised"),

    # --- spec §3.6 marker 3, which the engine cannot detect ---------------- #
    _asm("23_small_count_before_call.asm", """PUSH EBP
MOV EBP,ESP
SUB ESP,0x20
MOV EAX,0x4
CALL 0x00903400
ADD ESP,0x8
MOV EAX,dword ptr [ECX + 0x8]
MOV EAX,dword ptr [ECX + 0xc]
MOV EAX,dword ptr [EBP + 0x8]
MOV ESP,EBP
POP EBP
RET 0x8
""", "spec §3.6 marker 3 is a `mov r, imm` with a small count before a call; "
         "the engine now detects it (it was a real gap, now closed) and C6B is "
         "outranked by the variadic cap, so the record abstains"),

    # --- spec §3.6 marker 1, the real MSVC va_list shape -------------------- #
    _asm("24_va_list_setup_shape.asm", """PUSH EBP
MOV EBP,ESP
SUB ESP,0x20
MOV EAX,dword ptr [ECX + 0x8]
MOV EAX,dword ptr [ECX + 0xc]
XOR EAX,EAX
MOV ECX,0x4
REP STOSD
LEA EAX,[EBP + -0x4]
PUSH EAX
CALL 0x00903400
ADD ESP,0x8
MOV ESP,EBP
POP EBP
RET
""", "marker 1 fires: variadic is SUSPECTED and C12 forces the convention to "
         "null. The two ECX loads come first because the REP count necessarily "
         "reassigns ECX, which would otherwise destroy the receiver evidence"),
)

FIXTURES_BY_NAME = {fixture.stem: fixture for fixture in FIXTURES}

# The AT&T twin shares fixture 01's expected record modulo the provenance keys.
ATT_TWIN_OF = "16_thiscall_member.att"
ATT_TWIN_TARGET = "01_thiscall_member"


# --------------------------------------------------------------------------
# Real SporeApp.exe targets. The disassembly is NOT transcribed here: the
# committed tests/fixtures/abi/live/<va8>_<slug>.json files are the verbatim
# bridge responses, and the suite replays those. Expectations below are the
# ones the research pass established; the actual engine readings were
# re-measured against the live bridge and are recorded in each test.
# --------------------------------------------------------------------------
LIVE_TARGETS = (
    # (va8, slug, expected convention, expected cleanup side, expected bytes, note)
    ("0040ccb0", "thiscall_spilled_receiver", "__thiscall", "callee", 4,
     "receiver spilled to [EBP-0x48] and reloaded; five member offsets"),
    ("005291f0", "graphics_set_transform", None, "caller", 0,
     "MUST ABSTAIN: AND ESP,0xfffffff0 is alignment, and ECX is loaded from a "
     "frame slot, so the receiver is *undetermined* rather than proven absent -- "
     "an undetermined receiver must not yield a convention (defect D1, fixed)"),
    ("00951230", "stdcall_stub_ret0c", "__stdcall", "callee", 12,
     "two-instruction stub; the three slots come from the immediate"),
    ("00ce6950", "thiscall_member_0x184", "__thiscall", "caller", 0,
     "frameless single load [ECX+0x184]"),
    ("004bdc00", "seh_spilled_receiver", "__thiscall", "callee", 4,
     "SEH via FS:[0x2c]; receiver recovered through its own spill slot"),
    ("008db310", "thiscall_big_ret8", "__thiscall", "callee", 8,
     "no sub esp at all; LEA EBP,[EBX+EAX*0x1] is not a frame op; both exits "
     "are RET 0x8 so they agree"),
    ("00e5b790", "abstain_esp_delta", None, "caller", 0,
     "MUST ABSTAIN: FLD float ptr [ESP+0x40] resolves to key 0, the return "
     "address, so no incoming stack argument is read"),
    ("005c65e0", "lea_from_ecx", None, "caller", 0,
     "MUST ABSTAIN: LEA EAX,[ECX+0x3c] is address arithmetic, not a load"),
    ("00de9fc0", "untrusted_frame", None, "caller", 0,
     "MUST ABSTAIN: MOV EBP,ECX with no MOV EBP,ESP"),
    ("00aea250", "thiscall_contradicts_fastcall", "__thiscall", "caller", 0,
     "the index persists __fastcall; ECX is dereferenced at 32 offsets and EDX "
     "is only ever written"),
    ("00d2e350", "x87_argless", None, "caller", 0,
     "MUST ABSTAIN: argless x87 return"),
    ("007e6080", "naked_thunk", None, None, None,
     "MUST ABSTAIN: the whole function is JMP 0x00929bd0"),
)

#: The index's persisted label for 0x00aea250, which the engine contradicts.
PERSISTED_FASTCALL = "__fastcall"


def live_path(va8, slug):
    return os.path.join(LIVE_DIR, "%s_%s.json" % (va8, slug))


def live_expected_path(va8, slug):
    return os.path.join(LIVE_EXPECT_DIR, "%s_%s.json" % (va8, slug))


def live_va8s():
    return [entry[0] for entry in LIVE_TARGETS]


# --------------------------------------------------------------------------
# Reading helpers
# --------------------------------------------------------------------------
def read_blob(path):
    with open(path, "rb") as handle:
        return handle.read()


def read_text(path):
    return read_blob(path).decode("utf-8", "replace")


def read_json(path):
    with open(path, "r", encoding="utf-8") as handle:
        return json.load(handle)


def load_fixture(name):
    """Read one ``.asm``/``.att`` fixture from disk, by stem or by file name."""
    stem = name[:-4] if name.endswith((".asm", ".att")) else name
    for extension in (".asm", ".att"):
        path = os.path.join(FIXTURE_DIR, stem + extension)
        if os.path.isfile(path):
            return read_text(path)
    raise IOError("no committed fixture for %r under %s" % (name, FIXTURE_DIR))


def load_expected(name):
    stem = name[:-4] if name.endswith((".asm", ".att")) else name
    return read_json(os.path.join(EXPECT_DIR, stem + ".json"))


def iter_fixture_names():
    return [fixture.stem for fixture in FIXTURES]


def hermetic_inputs():
    """``(label, input)`` for every committed hermetic fixture.

    Inputs are read from disk, so a hand-edited ``.asm`` is exactly what gets
    analysed; the generator's byte-drift guard is what keeps that safe.
    """
    out = []
    for fixture in FIXTURES:
        if fixture.stem == ATT_TWIN_OF:
            continue  # consumed by the layout-invariance test, not standalone
        out.append((fixture.stem, load_fixture(fixture.stem)))
    return out


def live_inputs():
    """``(label, input)`` for every committed live capture."""
    out = []
    for va8, slug in [(entry[0], entry[1]) for entry in LIVE_TARGETS]:
        out.append((va8, read_json(live_path(va8, slug))))
    return out


# --------------------------------------------------------------------------
# Encoding the same stream four ways, for the layout-invariance test
# --------------------------------------------------------------------------
def encodings_of_01():
    """Four legal encodings of fixture 01's instruction stream.

    ``plain_text``, ``gcodebrowser_text`` (header + address + byte columns),
    ``att_text`` and ``json_instruction_list``. All four must yield the same
    record modulo :data:`PROVENANCE_PATHS`.
    """
    # CODEBROWSER_01 opens with two header rows ("Listing ..." and the "---"
    # ruler), so the body starts at line 2, not 3.
    intel = [line.split(None, 2)[2] for line in CODEBROWSER_01.splitlines()[2:]]
    assert len(intel) == len(JSON_ADDRESSES_01), (
        "the CodeBrowser body and the JSON address column must line up")
    json_list = [{"address": address, "instruction": instruction}
                 for address, instruction in zip(JSON_ADDRESSES_01, intel)]
    return {
        "plain_text": "\n".join(intel) + "\n",
        "gcodebrowser_text": CODEBROWSER_01,
        "att_text": load_fixture(ATT_TWIN_OF),
        "json_instruction_list": json_list,
        "json_instruction_dict": {"instructions": json_list, "count": len(json_list)},
    }


# --------------------------------------------------------------------------
# Property corpus
# --------------------------------------------------------------------------
def fuzz_inputs(count=400, seed=None):
    """Deterministic adversarial corpus. No wall clock, no unseeded randomness.

    The first eight entries are the hand-written adversarial strings from
    docs/tooling/abi-inference-tests.md §3; the rest is a seeded generator, so
    two runs of the suite produce byte-identical corpora.
    """
    rng = random.Random(FUZZ_SEED if seed is None else seed)
    yield ""
    yield "   \n\n\t\r\n"
    yield "\x00\xff\xfe" * 64
    yield "A" * 1048576
    yield "RET 0xFFFFFFFF\n" * 32
    yield "PUSH EBP\n" * 10000
    yield "\r\n".join("MOV EAX,dword ptr [EBP + 0x%x]" % i for i in range(1000))
    for _ in range(count):
        yield "".join(rng.choice(GARBAGE_ALPHABET)
                      for _ in range(rng.randint(0, 400)))


# --------------------------------------------------------------------------
# semantic_diff, the golden-comparison pattern from tests/diff_real.py
# --------------------------------------------------------------------------
def semantic_diff(expected, actual, path="$"):
    """Human-readable differences between two JSON documents.

    Copied in spirit from ``tests/diff_real.py::semantic_diff`` so a golden
    mismatch reads the same everywhere in this repo. Extended to walk lists of
    dicts element-wise, because an inference list is compared positionally and
    "expected 3 items, got 2" is useless on its own.
    """
    lines = []
    if isinstance(expected, dict) and isinstance(actual, dict):
        for key in sorted(set(expected) | set(actual), key=str):
            child = "%s.%s" % (path, key)
            if key not in actual:
                lines.append("%s: missing in actual (expected %r)" % (child, expected[key]))
            elif key not in expected:
                lines.append("%s: unexpected in actual %r" % (child, actual[key]))
            elif expected[key] != actual[key]:
                lines.extend(semantic_diff(expected[key], actual[key], child))
    elif isinstance(expected, list) and isinstance(actual, list):
        if len(expected) != len(actual):
            lines.append("%s: length %d expected, %d in actual" % (
                path, len(expected), len(actual)))
        for index, (want, got) in enumerate(zip(expected, actual)):
            lines.extend(semantic_diff(want, got, "%s[%d]" % (path, index)))
    elif expected != actual:
        lines.append("%s: expected %r got %r" % (path, expected, actual))
    return lines


_INDEXED_RE = re.compile(r"^(.*)\[\d+\]$")


def diffing_paths(expected, actual, path="$"):
    """Every dotted path at which two documents differ.

    ``list`` of ``dict`` is walked positionally and reported as ``path[]``;
    every other value is compared whole. This is what the layout-invariance
    test needs: it wants the *set* of differing paths so it can assert that the
    set is a subset of the documented provenance set.
    """
    out = set()
    if isinstance(expected, dict) and isinstance(actual, dict):
        for key in sorted(set(expected) | set(actual), key=str):
            child = "%s.%s" % (path, key)
            if key not in expected or key not in actual:
                out.add(child)
            else:
                out |= diffing_paths(expected[key], actual[key], child)
    elif isinstance(expected, list) and isinstance(actual, list):
        if len(expected) != len(actual):
            out.add(path)
            return out
        for want, got in zip(expected, actual):
            if isinstance(want, dict) and isinstance(got, dict):
                out |= diffing_paths(want, got, path + "[]")
            elif want != got:
                out.add(path)
    elif expected != actual:
        out.add(path)
    return out


def strip_provenance(record):
    """A record with the documented provenance keys removed.

    Removes ``content_sha256`` and, from every observation, the verbatim text
    and the address/index-derived keys, plus the target/parse keys that only
    exist because an address column was supplied. What is left must be equal
    across all four encodings of one instruction stream.
    """
    stripped = {key: value for key, value in record.items() if key != "content_sha256"}
    stripped["observations"] = [
        {key: value for key, value in observation.items()
         if key not in ("at", "raw", "index", "first_use", "first_write_index",
                        "push_ebp_at", "mov_ebp_esp_at")}
        for observation in record["observations"]
    ]
    stripped["parse"] = {key: value for key, value in record["parse"].items()
                         if key not in ("layout", "declared_count")}
    frame = stripped["parse"].get("frame")
    if isinstance(frame, dict):
        stripped["parse"]["frame"] = {
            key: value for key, value in frame.items()
            if key not in ("push_ebp_at", "mov_ebp_esp_at")}
    stripped["target"] = {key: value for key, value in record["target"].items()
                          if key not in ("va", "syntax", "address_available")}
    return stripped


def convention_of(record):
    return record["conventions"]["calling_convention"]


def inference_ids(record):
    return [entry["id"] for entry in record["inferences"]]


def base_rule(inference_id):
    """``C6B#2`` -> ``C6B``; the engine suffixes a repeated rule id."""
    return inference_id.split("#", 1)[0]


def abstention_codes(record):
    return [entry.split(":", 1)[0] for entry in record["abstained_because"]]
