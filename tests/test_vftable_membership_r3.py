"""R3 -- the bounded clause-1 relaxation, falsified on synthetic images.

The bug R3 repairs
------------------
``vftables.P`` clause 1 admits a data-section address only when it is the **base of
a maximal run** of ``>= 2`` consecutive code pointers. "Maximal run base" is the
only thing clause 1 ever checks, and it annihilates every real table that sits
*interior* to a longer code-pointer run: the run has exactly one base, the base is
one address, and if nobody happens to vptr-store *that* address the whole region is
invisible to the predicate. Measured on ``SPORE/SporeBin/SporeApp.exe``
(sha256 ``25d42a7a...``): the 520-slot run at ``0x0149b358`` has no vptr-stored base
at all, its first 108 slots precede the first vptr-stored address inside it, and it
holds **23** independently vptr-stored addresses (``0x0149b508``, ``0x0149b550``,
... ``0x0149bb30``). Not one table in that region is recognised today, and
``0x01053db0`` / ``0x01053e00`` have zero memberships.

Machine proof that those 23 are 23 independent tables and not 23 slots: two vptrs
of *one* object at ``+0`` and ``+4`` -- ``0x01054c29: C7 00 D8 B7 49 01  mov dword
ptr [eax],0x149b7d8`` and ``0x01054c2f: C7 40 04 D8 BA 49 01  mov dword ptr
[eax+0x4],0x149bad8`` -- which is two vptr installs on one object, i.e. two
adjacent tables under the ``__thiscall`` multiple-inheritance layout.

The predicate under test
------------------------
**R3 (bounded clause-1 relaxation).** A maximal code-pointer run ``R = [r0, e)`` in
a data section is partitioned at **every** address ``B`` in ``R`` that satisfies
clause 2 (``B`` is vptr-stored with a register base and ``0 <= d <= 0x40``). Each
partition cell ``[B, next-partition-or-e)`` is a table when ``B`` is vptr-backed and
the cell length is ``>= MIN_SLOTS`` (= 2). **Bounding condition: R3 is applied only
to a run whose own base ``r0`` does *not* satisfy clause 2.** A run whose base is
already clause-2-backed keeps exactly today's behaviour -- one table spanning the
whole run -- so R3 is strictly additive and cannot alter an existing membership.

Two properties of that wording are worth stating up front, because most of the
falsifiers below are about them:

* the cell **starts** at the marked address, so the slots *before* the first mark
  (the 108 slots of the real run) belong to no table. R3 does not slide a cell
  backwards to a run base;
* a cell **stops** at the next mark, so a cell can never swallow the following
  table's first slots. ``test_17`` is exactly that bound.

One requirement the wording implies and does not spell out, because it is a
consequence rather than a clause: **clause 3 must be applied to the pre-R3
candidate set, not to the cells.** ``_well_founded`` rejects a candidate ``T`` when
some other candidate ``T'`` satisfies ``T' < T <= T' + 4 * slots(T')`` -- and a
cell base is, by construction, at or before the end of the cell below it, so
running clause 3 over the partition makes every cell but the last reject itself.
That is vacuous under clause 1 (maximal runs of code pointers are disjoint and hold
code addresses, while a clause-2 address is a data address) and non-vacuous the
moment clause 1 is relaxed, which is the case the module docstring anticipates when
it keeps the clause. The partition supplies what clause 3 was there to supply --
cells are disjoint, so a cell base is never a member of another cell -- and
``test_20`` checks that clause 3 is in fact rejecting nothing on these images.

The asymmetry this file is built to show
----------------------------------------
Before R3 lands, the five R3-dependent cases in ``R3PositivesTest`` **fail** and
every case in ``R3FalsifierTest`` **passes**, and with them the four
``R3CorpusGuardTest`` cases. That is the point: a negative that fails before the
implementation proves nothing, and a positive that passes before it proves nothing
either. The remaining three positives -- the status-quo run-base table, determinism,
purity -- are *not* R3-dependent and are expected to pass on both sides; they are the
positive half of "R3 changes nothing else", and ``R3PositivesTest``'s docstring
names them. The falsifiers that are intrinsically about R3 cells (03, 06, 15, 16, 17,
18, 19) are written as *bounds and non-memberships* -- statements that are vacuously
true while R3 is absent and load-bearing the moment it lands -- with their exact
expectation behind an ``if the engine reported a table`` guard, and each paired with
a **status-quo control** (a vptr-backed run base) that fires before and after alike.
The whole battery has been run against a working R3 as well as against the
unrelaxed engine, and passes 33/33 in both configurations.

The synthetic images
--------------------
``r3_image`` builds a minimal PE32 over ``tests/test_vftable_membership.py``'s
already-proven builder (``pe_image`` / ``store_vptr`` / ``dwords``) rather than a
second one: ``.text`` at RVA ``0x1000`` carrying the clause-2 stores, ``.rdata`` at
RVA ``0x2000`` carrying one maximal run of distinct code pointers, optionally
``.data`` at RVA ``0x3000``, and a fifth section element wherever a virtual size
larger than the raw size is needed. Slot ``i`` of a run always holds the code address
``IMAGE_BASE + 0x1000 + 4 * i``, so the dword values inside a run are distinct by
construction and a slot index is checkable by value. The image base is
``0x00400000``. No clock, no randomness, no filesystem, no network: every synthetic
image is built in memory and every scan goes through ``scan_bytes``, the pure entry
point.

Spec: ``docs/tooling/abi-inference-vftable-extension.md`` §2.3, as extended by R3.
Consumer: ``tools/reconstruction_tooling/abi_infer.py`` rules ``V1-VFT``/``T1-FWD``.
"""
import json
import os
import struct
import sys
import unittest
from unittest import mock

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

from tests import test_vftable_membership as synth  # noqa: E402
from tests import vftable_corpus as corpus  # noqa: E402
from tools.reconstruction_tooling import vftables  # noqa: E402
from tools.reconstruction_tooling.models import canonical_json  # noqa: E402

RUN_RVA = synth.RDATA_RVA
REG_ECX = synth.REG_ECX
NOP = 0x90

REAL_BINARY = os.path.join(ROOT, "SPORE", "SporeBin", "SporeApp.exe")

#: The real region R3 is measured against, named so a failure says which one moved.
#: The run's length, its head length and the set of vptr-stored addresses inside it
#: are all read off the image by the tests that use them, never transcribed here.
REAL_RUN = 0x0149B358
REAL_RUN_SLOTS = 520


# ---------------------------------------------------------------------------
# synthetic images
# ---------------------------------------------------------------------------
def store_naming(target_va, register=REG_ECX, disp=0):
    """``MOV dword ptr [R + d], target_va`` -- the encoding clause 2 admits."""
    return synth.store_vptr(register, disp) + synth.dwords(target_va)


def run_va(slot, rdata_rva=RUN_RVA):
    """The address of slot ``slot`` of the run at ``rdata_rva``."""
    return synth.table_va(rdata_rva + 4 * slot)


def slot_fn(slot):
    """The code address stored in slot ``slot`` of a run built by :func:`r3_image`."""
    return synth.fn_va(4 * slot)


def code_pointers(count, first=0):
    """``count`` distinct code-section dwords: the payload of one maximal run."""
    return synth.dwords(*[slot_fn(first + index) for index in range(count)])


def r3_image(marks=(), run_slots=8, base_marked=False, register=REG_ECX, disp=0,
             rdata=None, rdata_rva=RUN_RVA, rdata_virtual=None,
             data_payload=None, data_virtual=None):
    """``.text`` with the clause-2 stores, ``.rdata`` with one maximal code run.

    ``marks`` holds one entry per clause-2 store. An ``int`` is a slot index of the
    run and gets the default ``MOV [R + d], imm32`` encoding; a ``bytes`` object is
    placed verbatim, which is how the encodings clause 2 *rejects* are built. The
    stores come first and the run's distinct code addresses follow, so slot ``i``
    always points at ``IMAGE_BASE + 0x1000 + 4 * i``.

    ``base_marked`` adds a store naming the run's own base, which is what makes R3's
    bounding condition observable: a run whose base is vptr-stored is not
    repartitioned at all.
    """
    stores = [store_naming(run_va(index, rdata_rva), register, disp)
              if isinstance(index, int) else bytes(index) for index in marks]
    if base_marked:
        stores.append(store_naming(run_va(0, rdata_rva), register, disp))
    code = b"".join(stores) + bytes([NOP]) * (4 * run_slots)
    sections = [(".text", synth.CODE, synth.TEXT_RVA, code)]
    entry = [".rdata", synth.RDATA, rdata_rva,
             code_pointers(run_slots) if rdata is None else rdata]
    if rdata_virtual is not None:
        entry.append(rdata_virtual)
    sections.append(tuple(entry))
    if data_payload is not None:
        data_entry = [".data", synth.DATA, synth.DATA_RVA, data_payload]
        if data_virtual is not None:
            data_entry.append(data_virtual)
        sections.append(tuple(data_entry))
    return synth.pe_image(sections)


def tables_of(scan):
    """``scan["tables"]`` keyed by integer address."""
    return {int(table, 16): slots for table, slots in scan["tables"].items()}


def tables_as(expected):
    """An integer-keyed table map in the spelling the scan uses."""
    return {vftables.fmt(table): slots for table, slots in expected.items()}


def u32(buffer, offset):
    return struct.unpack_from("<I", buffer, offset)[0]


# -- stand-ins for the two section-mapping guards ----------------------------
def runs_over_one_blob(image):
    """Stand-in for ``_code_pointer_runs``: one contiguous blob of every data
    section. This is the reference scanner's recorded defect, and it is what lets a
    run cross a section boundary.
    """
    data_sections = [(index, section) for index, section in enumerate(image.sections)
                     if section["data"]]
    if not data_sections:
        return {}
    blob = b"".join(image.backed_bytes(section) for _index, section in data_sections)
    first_index, first = data_sections[0]
    runs = {}
    position = 0
    while position + 4 <= len(blob):
        if not image.is_code(u32(blob, position)):
            position += 4
            continue
        end = position
        while end + 4 <= len(blob) and image.is_code(u32(blob, end)):
            end += 4
        slots = (end - position) // 4
        if slots >= vftables.MIN_SLOTS:
            runs[first["va"] + position] = (slots, first_index, position)
        position = end
    return runs


def runs_over_virtual_windows(image):
    """Stand-in for ``_code_pointer_runs``: read each data section's *virtual*
    window out of the file, ignoring ``SizeOfRawData``, so an unbacked tail
    contributes the dwords the image never holds.
    """
    runs = {}
    for index, section in enumerate(image.sections):
        if not section["data"]:
            continue
        offset = section["raw_offset"]
        buffer = image.data[offset:offset + section["vsize"]]
        position = 0
        while position + 4 <= len(buffer):
            if not image.is_code(u32(buffer, position)):
                position += 4
                continue
            end = position
            while end + 4 <= len(buffer) and image.is_code(u32(buffer, end)):
                end += 4
            slots = (end - position) // 4
            if slots >= vftables.MIN_SLOTS:
                runs[section["va"] + position] = (slots, index, position)
            position = end
    return runs


def decode_any_encoding(buffer, position, image):
    """Stand-in for ``_decode_store``: accept every ``C7 /0`` memory form.

    It keeps only the two things clause 2's *decoder* needs -- ``mod != 3`` and the
    mod-dependent offset of the immediate -- and drops every admissibility rule:
    the ``/0`` extension test, the ``rm`` exclusions (SIB, EBP, and the
    ``mod == 0, rm == 5`` displacement-absolute form) and the data-section test on
    the immediate.
    """
    if position + 2 > len(buffer):
        return None
    modrm = buffer[position + 1]
    mod = (modrm & 0xC0) >> 6
    rm = modrm & 0x07
    if mod == 3:
        return None
    displacement = 0
    immediate = position + 2
    if mod == 1:
        displacement = struct.unpack_from("<b", buffer, position + 2)[0]
        immediate = position + 3
    elif mod == 2:
        displacement = struct.unpack_from("<i", buffer, position + 2)[0]
        immediate = position + 6
    if immediate + 4 > len(buffer):
        return None
    return (u32(buffer, immediate), rm, displacement)


def decode_any_target(buffer, position, image):
    """Stand-in for ``_decode_store``: every encoding clause 2 admits, but the
    immediate is not required to be a data-section address.
    """
    if position + 6 > len(buffer):
        return None
    modrm = buffer[position + 1]
    mod = (modrm & 0xC0) >> 6
    extension = (modrm >> 3) & 0x7
    rm = modrm & 0x07
    if extension != 0 or rm in (4, 5) or mod == 3:
        return None
    immediate = position + 2
    displacement = 0
    if mod == 1:
        displacement = struct.unpack_from("<b", buffer, position + 2)[0]
        immediate = position + 3
    elif mod == 2:
        displacement = struct.unpack_from("<i", buffer, position + 2)[0]
        immediate = position + 6
    if immediate + 4 > len(buffer):
        return None
    return (u32(buffer, immediate), rm, displacement)


# -- the real image, read once, and only when it is there -------------------
_REAL = {}


def real_image_bytes():
    """The real image's bytes, or ``None`` when ``SPORE/`` is absent.

    Read once per process and handed straight to ``scan_bytes``, so nothing in this
    file writes a cache file and nothing depends on one.
    """
    if "bytes" not in _REAL:
        _REAL["bytes"] = None
        if os.path.exists(REAL_BINARY):
            with open(REAL_BINARY, "rb") as handle:
                _REAL["bytes"] = handle.read()
    return _REAL["bytes"]


def r3_free_tables(image_bytes):
    """The pre-R3 predicate on its own, with no partitioning step at all.

    This is how the corpus guard states additivity without a second engine: the
    three clause helpers are the ones R3 does not touch, so what they produce is by
    construction what ``P`` reported before R3 existed. Returns
    ``(runs, tables, backed)`` -- the maximal runs, the sound table bases among
    them, and every vptr-stored address (the set R3 partitions at).
    """
    image = vftables.Image(image_bytes)
    runs = vftables._code_pointer_runs(image)
    bases = {}
    for _va, target, _register, displacement in vftables._vptr_stores(image):
        if 0 <= displacement <= vftables.MAX_VPTR_OFFSET:
            bases.setdefault(target, []).append(displacement)
    candidates = {table: runs[table] for table in sorted(bases)
                  if table in runs and len(bases[table]) >= vftables.MIN_STORES}
    return runs, vftables._well_founded(candidates), set(bases)


def dword_at(image_bytes, va):
    """The dword stored at ``va`` in a scanned image, by section mapping."""
    image = vftables.Image(image_bytes)
    section = image.section_of(va)
    if section is None:
        raise AssertionError("0x%08x is in no section" % va)
    buffer = image.backed_bytes(section)
    offset = va - section["va"]
    if offset + 4 > len(buffer):
        raise AssertionError("0x%08x is not backed by the image" % va)
    return u32(buffer, offset)


# =========================================================================== #
# R3 -- the positives
# =========================================================================== #
class R3PositivesTest(unittest.TestCase):
    """The shapes R3 exists to recognise, on the real predicate's own terms.

    Every synthetic case here fails while R3 is absent, with three deliberate
    exceptions that are *not* R3-dependent and must not: the status-quo run-base
    table (``test_a_run_base_table_is_unchanged_by_r3``) and the purity/determinism
    properties, which are properties of ``scan_bytes`` rather than of the relaxation.
    They are in this class because they are the positive half of "R3 changes nothing
    else".

    ``test_the_real_run_at_0x0149b358_is_repartitioned`` runs the same assertion
    against the image the bug was measured on, and skips itself when ``SPORE/`` is
    absent exactly as the rest of the suite does.
    """

    def scan(self, image, **kwargs):
        return vftables.scan_bytes(image, **kwargs)

    # -- the shapes -------------------------------------------------------
    def test_two_adjacent_interior_vptr_backed_bases_both_become_tables(self):
        """The R3 case itself: two marked bases, neither of them the run base.

        The real shape in miniature -- ``0x0149b508`` and ``0x0149b550`` of the
        520-slot run, with the run's own base vptr-stored by nobody. The run base
        is deliberately not marked, because that is the only situation R3 applies
        to; with the base marked the run keeps today's single table
        (``test_01`` in the falsifiers).
        """
        scan = self.scan(r3_image(marks=(2, 5), run_slots=8))
        self.assertEqual(1, scan["stats"]["code_pointer_runs"], "one maximal run")
        self.assertEqual(2, scan["stats"]["vptr_bases"], "two vptr-stored addresses")
        self.assertEqual(tables_as({run_va(2): 3, run_va(5): 3}), scan["tables"])
        self.assertNotIn(vftables.fmt(run_va(0)), scan["tables"])
        for slot in range(8):
            tables = [table for table, _slot in vftables.slots_of(scan, slot_fn(slot))]
            expected = {0: [], 1: [], 2: [run_va(2)], 3: [run_va(2)], 4: [run_va(2)],
                        5: [run_va(5)], 6: [run_va(5)], 7: [run_va(5)]}[slot]
            self.assertEqual(expected, tables)
        self.assertEqual(((run_va(2), 0),), vftables.slots_of(scan, slot_fn(2)))
        self.assertEqual(((run_va(2), 2),), vftables.slots_of(scan, slot_fn(4)))
        self.assertEqual(((run_va(5), 0),), vftables.slots_of(scan, slot_fn(5)))
        self.assertEqual(((run_va(5), 2),), vftables.slots_of(scan, slot_fn(7)))

    def test_slot_indices_are_exact_from_the_cell_base(self):
        """A value at ``B + 0``, ``B + 4``, ``B + 8`` is slot 0, 1, 2.

        The slot index is counted from the **cell base**, not from the run base and
        not from the first slot of the run, so this is the assertion that pins
        where the cell starts.
        """
        scan = self.scan(r3_image(marks=(3,), run_slots=6))
        base = run_va(3)
        self.assertEqual({vftables.fmt(base): 3}, scan["tables"])
        for slot, index in ((3, 0), (4, 1), (5, 2)):
            self.assertEqual(((base, index),),
                             vftables.slots_of(scan, slot_fn(slot)),
                             "slot index is counted from the cell base")
        self.assertEqual((), vftables.slots_of(scan, slot_fn(2)),
                         "the dword before the cell base is not its slot 0")
        self.assertTrue(vftables.is_code_address(scan, slot_fn(5)))

    def test_the_last_cell_of_a_run_reaches_the_end_of_the_run(self):
        """The final cell is bounded by the run's end, not by the run's length.

        Three cells, so the last one has no next partition to stop at: it must
        consume every dword left in the run, which is the difference between "a
        maximal run" and "a maximal run minus its tail".
        """
        scan = self.scan(r3_image(marks=(2, 6, 10), run_slots=14))
        self.assertEqual(tables_as({run_va(2): 4, run_va(6): 4, run_va(10): 4}),
                         scan["tables"])
        self.assertEqual(((run_va(10), 3),), vftables.slots_of(scan, slot_fn(13)))
        self.assertEqual((), vftables.slots_of(scan, slot_fn(1)))

    def test_the_cells_of_a_partitioned_run_tile_the_run_exactly(self):
        """Coverage: every dword from the first mark to the end is claimed once,
        and the head before the first mark is claimed by nobody.

        This is the positive form of the partition invariant; ``test_15`` states
        the same invariant as a falsifier (no address claimed twice, no gap in the
        middle).
        """
        marks = (3, 7)
        scan = self.scan(r3_image(marks=marks, run_slots=12))
        self.assertEqual(tables_as({run_va(3): 4, run_va(7): 5}), scan["tables"])
        claimed = []
        for slot in range(12):
            memberships = vftables.slots_of(scan, slot_fn(slot))
            if slot < 3:
                self.assertEqual((), memberships,
                                 "the head of the run belongs to no table")
            else:
                self.assertEqual(1, len(memberships), "claimed exactly once")
                claimed.append(slot)
        self.assertEqual(list(range(3, 12)), claimed)

    def test_a_run_base_table_is_unchanged_by_r3(self):
        """The status quo, asserted on both sides of the relaxation.

        A run whose base is vptr-stored is one table spanning the whole run, and
        R3 leaves it exactly there. This passes before R3 and must keep passing
        after it -- it is the additive half of the bounding condition, and the
        corpus guard is its statement over the real image.
        """
        scan = self.scan(r3_image(marks=(), run_slots=8, base_marked=True))
        self.assertEqual(1, scan["stats"]["code_pointer_runs"])
        self.assertEqual(1, scan["stats"]["vptr_bases"])
        self.assertEqual(tables_as({run_va(0): 8}), scan["tables"])
        for slot in range(8):
            self.assertEqual(((run_va(0), slot),),
                             vftables.slots_of(scan, slot_fn(slot)))
        self.assertEqual((), vftables.slots_of(scan, run_va(0)),
                         "a table's own base is not one of its slots")

    # -- the real region --------------------------------------------------
    def test_the_real_run_at_0x0149b358_is_repartitioned(self):
        """The measured case, on the real image: 23 interior bases, 23 tables.

        The expected decomposition is derived from the image (the run's own length
        and the vptr-stored addresses the clause-2 decoder finds inside it) rather
        than transcribed, so the assertion is about the *relationship* between the
        marks and the cells -- and the two measured facts that make the case
        legible at all, 23 marks and a 108-slot head, are pinned so a change in
        either is visible.
        """
        payload = real_image_bytes()
        if payload is None:
            self.skipTest("the binary is not present")
        scan = self.scan(payload)
        runs, _pre, _backed = r3_free_tables(payload)
        self.assertIn(REAL_RUN, runs, "the measured run moved")
        slots, _index, _offset = runs[REAL_RUN]
        self.assertEqual(REAL_RUN_SLOTS, slots)
        end = REAL_RUN + 4 * slots
        image = vftables.Image(payload)
        marks = sorted({target for _va, target, _register, displacement
                        in vftables._vptr_stores(image)
                        if 0 <= displacement <= vftables.MAX_VPTR_OFFSET
                        and REAL_RUN < target < end})
        self.assertEqual(23, len(marks), "the measured mark count moved")
        self.assertEqual(0x1B0, marks[0] - REAL_RUN, "the measured head moved")
        self.assertNotIn(vftables.fmt(REAL_RUN), scan["tables"],
                         "the run base is vptr-stored by nobody and is not a table")
        expected = {}
        for index, mark in enumerate(marks):
            stop = marks[index + 1] if index + 1 < len(marks) else end
            expected[mark] = (stop - mark) // 4
        tables = tables_of(scan)
        for mark, cell in expected.items():
            self.assertGreaterEqual(cell, vftables.MIN_SLOTS)
            self.assertEqual(cell, tables.get(mark),
                             "0x%08x is not the cell R3 says it is" % mark)
        for slot in range((marks[0] - REAL_RUN) // 4):
            value = dword_at(payload, REAL_RUN + 4 * slot)
            self.assertFalse([table for table, _index in vftables.slots_of(scan, value)
                              if table in expected],
                             "the head of the run belongs to no cell")
        first = dword_at(payload, marks[0])
        self.assertIn((marks[0], 0), vftables.slots_of(scan, first),
                      "the first cell's first slot is not slot 0 of that cell")

    # -- determinism and purity -------------------------------------------
    def test_the_scan_is_deterministic_and_json_stable(self):
        """Two calls, two identical results, in both spellings of equality.

        ``canonical_json`` is the byte-identity the module promises; the
        ``json.dumps(sort_keys=True)`` round trip is the weaker, external spelling
        of the same claim, and a third call from a re-parsed payload rules out the
        result depending on the identity of the bytes object it was handed.
        """
        image = r3_image(marks=(2, 5), run_slots=8)
        first = self.scan(image, sha256="a" * 64)
        second = self.scan(image, sha256="a" * 64)
        self.assertEqual(canonical_json(first), canonical_json(second))
        self.assertEqual(json.dumps(first, sort_keys=True),
                         json.dumps(second, sort_keys=True))
        self.assertEqual(sorted(first["tables"]), list(first["tables"]))
        for entries in first["memberships"].values():
            self.assertEqual(sorted(entries), entries)
            self.assertEqual(len(entries), len({tuple(entry) for entry in entries}),
                             "a membership is never reported twice")
        third = self.scan(bytearray(image), sha256="a" * 64)
        self.assertEqual(canonical_json(first), canonical_json(third))

    def test_scan_bytes_touches_neither_the_cache_nor_the_filesystem(self):
        """The pure entry point stays pure: no open, no stat, no cache read.

        Every one of the six is patched to raise, so a regression is an exception
        rather than a silent side effect, and the scan still has to produce the
        full result twice.
        """
        image = r3_image(marks=(2, 5), run_slots=8)
        with mock.patch("builtins.open", side_effect=AssertionError("opened a file")), \
             mock.patch("os.path.exists", side_effect=AssertionError("stat-ed")), \
             mock.patch("os.makedirs", side_effect=AssertionError("made a dir")), \
             mock.patch.object(vftables, "read_cache",
                               side_effect=AssertionError("read the cache")), \
             mock.patch.object(vftables, "write_json_atomic",
                               side_effect=AssertionError("wrote the cache")), \
             mock.patch.object(vftables, "cache_path",
                               side_effect=AssertionError("named a cache file")):
            first = vftables.scan_bytes(image)
            second = vftables.scan_bytes(image)
        self.assertEqual(canonical_json(first), canonical_json(second))
        self.assertEqual(vftables.SCHEMA, first["schema"])

    def test_the_constants_this_battery_stands_on(self):
        self.assertEqual(2, vftables.MIN_SLOTS)
        self.assertEqual(0x40, vftables.MAX_VPTR_OFFSET)
        self.assertIsInstance(vftables.SCHEMA, str)
        self.assertTrue(vftables.SCHEMA)


# =========================================================================== #
# R3 -- the falsifiers
# =========================================================================== #
class R3FalsifierTest(unittest.TestCase):
    """Twenty ways to make R3 over-claim, each asserted to stay silent.

    Every case is a mutation of a firing input. The firing control is always a
    **status-quo** shape -- a run whose own base is vptr-stored -- so the control
    fires both before and after the relaxation and the negative differs from it in
    exactly the guarded property. That is what keeps every case in this class
    passing while R3 is absent, which is the property that makes the battery
    load-bearing rather than decorative.

    The seven cases about R3 cells themselves (03, 06, 15, 16, 17, 18, 19) state
    their negative as a **bound or a non-membership** -- true vacuously while no
    cell exists, and decisive the moment one does -- with the exact expectation
    behind ``if scan["stats"]["sound_tables"]``. ``test_20`` closes the set by
    replacing each guard in turn and asserting the negative stops holding.
    """

    def scan(self, image, **kwargs):
        return vftables.scan_bytes(image, **kwargs)

    def assertSilent(self, scan, why, slots=8):
        """No table anywhere, and none of the run's slots claimed."""
        self.assertEqual(0, scan["stats"]["sound_tables"], why)
        self.assertEqual({}, scan["tables"], why)
        for slot in range(slots):
            self.assertEqual((), vftables.slots_of(scan, slot_fn(slot)), why)

    def assertStatusQuo(self, slots=8):
        """The control: a vptr-backed run base is one table over the whole run.

        Fires before and after R3, and every negative below differs from it in one
        property only.
        """
        scan = self.scan(r3_image(run_slots=slots, base_marked=True))
        self.assertEqual(tables_as({run_va(0): slots}), scan["tables"])
        for slot in range(slots):
            self.assertEqual(((run_va(0), slot),),
                             vftables.slots_of(scan, slot_fn(slot)))
        return scan

    # -- 1. the bounding condition ---------------------------------------
    def test_01_a_vptr_backed_run_base_is_not_repartitioned(self):
        """The regression guard: a backed run base keeps exactly today's table.

        Two vptr-stored addresses in one run, one of them the base. The base is the
        table, spanning all eight slots; the interior mark is a **vptr base** (the
        store is decoded and counted) and still not a table. An R3 that repartitions
        unconditionally loses eight memberships and gains three.
        """
        self.assertStatusQuo()
        scan = self.scan(r3_image(marks=(4,), run_slots=8, base_marked=True))
        self.assertEqual(1, scan["stats"]["code_pointer_runs"])
        self.assertEqual(2, scan["stats"]["vptr_bases"],
                         "both stores are clause-2 admissible")
        self.assertEqual(tables_as({run_va(0): 8}), scan["tables"])
        self.assertNotIn(vftables.fmt(run_va(4)), scan["tables"])
        for slot in range(8):
            self.assertEqual(((run_va(0), slot),),
                             vftables.slots_of(scan, slot_fn(slot)),
                             "a backed run base keeps its slots")
        relaxed = self.scan(r3_image(marks=(4,), run_slots=8))
        if relaxed["stats"]["sound_tables"]:
            self.assertEqual(tables_as({run_va(4): 4}), relaxed["tables"],
                             "the same run, unbacked base, is a cell")

    # -- 2. no cell before the first mark ---------------------------------
    def test_02_a_run_base_without_vptr_evidence_yields_no_first_cell(self):
        """The first cell starts at the first *mark*, not at the run base.

        The head of a run with no vptr-stored base is a real shape -- the 108
        leading slots of the measured ``0x0149b358`` run -- and R3 does not hand
        them to the first cell as its slots 0, 1, 2.
        """
        self.assertStatusQuo()
        scan = self.scan(r3_image(marks=(3,), run_slots=8))
        self.assertEqual(1, scan["stats"]["code_pointer_runs"])
        self.assertEqual(1, scan["stats"]["vptr_bases"],
                         "only slot 3 is vptr-stored; the run base is not")
        for slot in range(3):
            self.assertEqual((), vftables.slots_of(scan, slot_fn(slot)),
                             "the cell before the first vptr base is not a table")
        self.assertNotIn(vftables.fmt(run_va(0)), scan["tables"])
        self.assertNotIn(vftables.fmt(run_va(2)), scan["tables"])
        if scan["stats"]["sound_tables"]:
            self.assertEqual(tables_as({run_va(3): 5}), scan["tables"])

    # -- 3. MIN_SLOTS ------------------------------------------------------
    def test_03_a_single_slot_cell_is_not_a_table(self):
        """A one-dword cell is a global, not a dispatch table.

        Identical to ``test_02``'s shape with the run one dword shorter, so the
        cell is one slot. Clause 1's ``MIN_SLOTS`` is the only thing separating
        this from a table, and it has to keep separating it under R3.
        """
        self.assertStatusQuo()
        scan = self.scan(r3_image(marks=(3,), run_slots=4))
        self.assertEqual(1, scan["stats"]["vptr_bases"])
        self.assertEqual(0, scan["stats"]["sound_tables"],
                         "a one-dword cell is a global")
        self.assertEqual({}, scan["tables"])
        self.assertEqual((), vftables.slots_of(scan, slot_fn(3)))
        longer = self.scan(r3_image(marks=(3,), run_slots=5))
        if longer["stats"]["sound_tables"]:
            self.assertEqual(tables_as({run_va(3): 2}), longer["tables"],
                             "one more dword of run and the cell qualifies")

    # -- 4 and 5. code-pointer runs that nobody vptr-stores ---------------
    def test_04_an_unrelated_code_pointer_run_is_not_a_table(self):
        """A dispatch table's array with no vptr install anywhere.

        ``0x00980510``'s shape without its constructor: a run of function pointers
        that a handler table or an interpose list can produce, and that clause 2 is
        the only thing keeping out.
        """
        self.assertStatusQuo()
        scan = self.scan(r3_image(run_slots=8))
        self.assertEqual(1, scan["stats"]["code_pointer_runs"], "the run exists")
        self.assertEqual(0, scan["stats"]["vptr_stores"], "nothing stores a vptr")
        self.assertEqual(0, scan["stats"]["vptr_bases"])
        self.assertSilent(scan, "a run nobody vptr-stores is not a table")

    def test_05_an_adjacent_function_pointer_array_is_not_a_table(self):
        """Two arrays, and vptr evidence in the image that names neither.

        The shape that matters here is not the absence of clause 2 but its
        *misplacement*: the image has a decoded vptr store, and it names an address
        that is not the base of any run. An R3 that partitions at "any address some
        store names" rather than at a run base would cut both arrays in half.
        """
        payload = code_pointers(3) + synth.dwords(0) + code_pointers(3, first=8) \
            + synth.dwords(0)
        gap = 3
        scan = self.scan(r3_image(marks=(gap,), run_slots=12, rdata=payload))
        self.assertEqual(2, scan["stats"]["code_pointer_runs"], "two arrays")
        self.assertEqual(1, scan["stats"]["vptr_stores"], "one store, off both bases")
        self.assertEqual(1, scan["stats"]["vptr_bases"])
        self.assertEqual({}, scan["tables"], "neither array is a table")
        for index in (0, 1, 2, 8, 9, 10):
            self.assertEqual((), vftables.slots_of(scan, slot_fn(index)))
        self.assertStatusQuo()
        armed = self.scan(r3_image(marks=(0,), run_slots=12, rdata=payload))
        self.assertEqual(tables_as({run_va(0): 3}), armed["tables"])
        self.assertEqual({}, {table: slots for table, slots in armed["tables"].items()
                              if table != vftables.fmt(run_va(0))},
                         "the unmarked second array is still not a table")

    # -- 6. exactly one cell per marked base ------------------------------
    def test_06_a_fake_contiguous_run_with_one_vptr_base_gives_one_table(self):
        """One mark, one cell, and nothing before it.

        The over-claim in the other direction from ``test_15``: an R3 that reported
        a cell at *every* run base, or split the run at the mark and reported the
        remainder as a second table, would fail the bound below.
        """
        self.assertStatusQuo()
        scan = self.scan(r3_image(marks=(3,), run_slots=8))
        self.assertEqual(1, scan["stats"]["code_pointer_runs"])
        self.assertLessEqual(len(scan["tables"]), 1,
                             "one marked base yields at most one table")
        self.assertNotIn(vftables.fmt(run_va(0)), scan["tables"])
        for slot in range(3):
            self.assertEqual((), vftables.slots_of(scan, slot_fn(slot)))
        if scan["stats"]["sound_tables"]:
            self.assertEqual(tables_as({run_va(3): 5}), scan["tables"])
            self.assertEqual(((run_va(3), 0),), vftables.slots_of(scan, slot_fn(3)))
            self.assertEqual(((run_va(3), 4),), vftables.slots_of(scan, slot_fn(7)))
        two = self.scan(r3_image(marks=(2, 5), run_slots=8))
        self.assertLessEqual(len(two["tables"]), 2, "two marks, at most two tables")
        if two["stats"]["sound_tables"]:
            self.assertEqual(tables_as({run_va(2): 3, run_va(5): 3}), two["tables"])

    # -- 7. clause 2's data-section requirement ---------------------------
    def test_07_a_vptr_base_in_a_code_section_is_rejected(self):
        """``MOV [EAX], <code address>`` names a code address, not a table.

        The immediate is a code-section address, so clause 2's last test rejects the
        store outright; nothing in the image is a data-section table base, and the
        run in ``.rdata`` is therefore unbacked.
        """
        self.assertStatusQuo()
        scan = self.scan(r3_image(marks=(b"\xc7\x01" + synth.dwords(slot_fn(0)),),
                                  run_slots=8))
        self.assertEqual(0, scan["stats"]["vptr_stores"],
                         "a code-section immediate is not a vptr store")
        self.assertEqual(0, scan["stats"]["vptr_bases"])
        self.assertSilent(scan, "a store into code is not a vptr install")

    # -- 8, 9, 10. the three encodings clause 2 excludes -------------------
    def test_08_an_ebp_or_esp_based_store_is_rejected(self):
        """``MOV [ESP+0x10], T`` and ``MOV [EBP-0x2c], T``: frame-local tables.

        ``0x009feb54`` and ``0x00404036`` write exactly these two shapes for
        ``0x013eb428``. Under R3 the excluded store must not become a partition
        point, or the frame-local table's address would cut a real run in half.
        """
        self.assertStatusQuo()
        rejected = (
            b"\xc7\x44\x24\x10",                          # MOV [ESP+0x10], imm32
            b"\xc7\x04",                                  # the SIB form, no disp
            b"\xc7\x45\xe0",                              # MOV [EBP-0x20], imm32
            b"\xc7\x85\x00\xfc\xff\xff",                  # MOV [EBP-0x400], imm32
        )
        for prefix in rejected:
            with self.subTest(prefix=prefix.hex()):
                scan = self.scan(r3_image(
                    marks=(prefix + synth.dwords(run_va(3)),), run_slots=8))
                self.assertEqual(0, scan["stats"]["vptr_stores"],
                                 "a frame register is not an object head")
                self.assertSilent(scan, "a frame-local store is not a vptr install")
        # The same immediate, through the one encoding clause 2 admits, is a store.
        admitted = self.scan(r3_image(
            marks=(b"\xc7\x01" + synth.dwords(run_va(3)),), run_slots=8))
        self.assertEqual(1, admitted["stats"]["vptr_stores"])
        self.assertEqual(1, admitted["stats"]["vptr_bases"])

    def test_09_a_disp32_absolute_store_does_not_mark_a_base(self):
        """``C7 05 <abs32> <imm32>`` is a global assignment, not a vptr install.

        The measured-and-rejected D1 relaxation. On the real image
        ``0x01055902: C7 05 E8 1A 6E 01 58 B3 49 01  mov dword ptr ds:0x16e1ae8,
        0x149b358`` is a global assignment inside a class-registration sequence: the
        immediate names the **run base** of the measured 520-slot run, so admitting
        the absolute form would mark ``0x0149b358`` and hand R3's bounding condition
        nothing to relax there -- or, worse, mark an address clause 1 never
        considered. The ModRM is ``mod == 0, rm == 5``, which is a displacement-
        absolute destination and not EBP-relative.
        """
        self.assertStatusQuo()
        absolute = b"\xc7\x05" + synth.dwords(0x016E1AE8) + synth.dwords(run_va(3))
        scan = self.scan(r3_image(marks=(absolute,), run_slots=8))
        self.assertEqual(0, scan["stats"]["vptr_stores"],
                         "a global assignment is not a this-relative install")
        self.assertEqual(0, scan["stats"]["vptr_bases"])
        self.assertSilent(scan, "the absolute form must not mark a base")
        named = self.scan(r3_image(marks=(b"\xc7\x01" + synth.dwords(run_va(3)),),
                                   run_slots=8))
        self.assertEqual(1, named["stats"]["vptr_bases"],
                         "the same immediate through [ECX] is a vptr base")

    def test_10_a_sib_based_store_is_rejected(self):
        """Every SIB destination is out, whatever its base register.

        ``rm == 4`` is the SIB form: the base may be ESP or anything else, and the
        displacement is a second byte, so the operand cannot be classified by the
        register test alone. A SIB store that named an interior run address would be
        a partition point under a laxer decoder.
        """
        self.assertStatusQuo()
        rejected = (
            b"\xc7\x44\x24\x08",                          # [ESP+0x8]
            b"\xc7\x44\x85\x00",                          # [EBP+0x0]
            b"\xc7\x84\x00\x10\x00\x00\x00",              # [EAX+0x10]
            b"\xc7\x84\x2c\x20\x00\x00\x00",              # [ESP+EAX*4+0x20]
        )
        for prefix in rejected:
            with self.subTest(prefix=prefix.hex()):
                scan = self.scan(r3_image(
                    marks=(prefix + synth.dwords(run_va(3)),), run_slots=8))
                self.assertEqual(0, scan["stats"]["vptr_stores"], "SIB is out")
                self.assertSilent(scan, "a SIB store is not a vptr install")
        admitted = self.scan(r3_image(
            marks=(b"\xc7\x01" + synth.dwords(run_va(3)),), run_slots=8))
        self.assertEqual(1, admitted["stats"]["vptr_stores"])

    # -- 11, 12. the offset window ----------------------------------------
    def test_11_a_displacement_past_the_cap_does_not_mark_a_base(self):
        """``d > 0x40`` is not the head of an object, so it is not a partition.

        The run base is marked too, so the negative does not depend on R3: the
        whole image is unsound unless the store itself is refused. ``0x40`` is
        inside the window and is the control, which fires.
        """
        self.assertStatusQuo()
        over = self.scan(r3_image(marks=(3, 5), run_slots=8, disp=0x44,
                                  base_marked=True))
        self.assertEqual(0, over["stats"]["vptr_bases"], "0x44 is past the cap")
        self.assertEqual({}, over["tables"])
        self.assertSilent(over, "a store past 0x40 marks nothing")
        at_cap = self.scan(r3_image(marks=(3, 5), run_slots=8, disp=0x40,
                                    base_marked=True))
        self.assertEqual(3, at_cap["stats"]["vptr_bases"], "0x40 is inside the window")
        self.assertEqual(tables_as({run_va(0): 8}), at_cap["tables"])

    def test_12_a_negative_displacement_does_not_mark_a_base(self):
        """``d < 0`` addresses before the object head, which is not a vptr."""
        self.assertStatusQuo()
        scan = self.scan(r3_image(marks=(3, 5), run_slots=8, disp=-4,
                                  base_marked=True))
        self.assertEqual(0, scan["stats"]["vptr_bases"])
        self.assertSilent(scan, "a negative displacement marks nothing")
        at_zero = self.scan(r3_image(marks=(3, 5), run_slots=8, disp=0,
                                     base_marked=True))
        self.assertEqual(3, at_zero["stats"]["vptr_bases"])
        self.assertEqual(tables_as({run_va(0): 8}), at_zero["tables"])

    # -- 13, 14. how a run is allowed to be read --------------------------
    def test_13_a_truncated_run_crossing_a_section_boundary_is_not_a_table(self):
        """A run never spans two sections, and a cell never does either.

        Between ``.rdata`` and ``.data`` there is an alignment gap that belongs to
        neither section, so a dword sequence crossing the boundary is not
        contiguous memory and cannot be a table. One code pointer at the end of
        ``.rdata`` and one at the start of ``.data`` is not a two-slot run: each
        half is one dword, and the address the store names is the run's *whole*
        content, not a base.
        """
        self.assertStatusQuo()
        image = r3_image(marks=(0,), run_slots=1, rdata=code_pointers(1),
                         data_payload=code_pointers(1, first=1))
        scan = self.scan(image)
        self.assertEqual(0, scan["stats"]["code_pointer_runs"],
                         "one dword per section is not a run")
        self.assertEqual(1, scan["stats"]["vptr_stores"],
                         "the store is a real vptr store; the run is what is missing")
        self.assertEqual(1, scan["stats"]["vptr_bases"])
        self.assertEqual({}, scan["tables"])
        self.assertEqual((), vftables.slots_of(scan, slot_fn(0)))
        self.assertEqual((), vftables.slots_of(scan, slot_fn(1)))
        whole = self.scan(r3_image(marks=(0,), run_slots=2))
        self.assertEqual(1, whole["stats"]["code_pointer_runs"])
        self.assertEqual(tables_as({run_va(0): 2}), whole["tables"],
                         "the same two dwords inside one section are a table")

    def test_14_an_uninitialised_data_tail_contributes_no_dword(self):
        """``.data``'s virtual size exceeds its raw size; the tail holds no bytes.

        Without this, a reader that mapped a whole section by virtual size invents
        runs out of memory the image never holds. The tail address is inside the
        section's data range -- so clause 2's store naming it is a real vptr store --
        and it is still not a run base, because no dword of it is backed. The
        control is the same image with the store naming the backed ``.data`` run
        instead, which fires.
        """
        self.assertStatusQuo()
        tail = 0x200
        unbacked_image = dict(
            run_slots=8,
            rdata=synth.dwords(0) * (tail // 4),
            rdata_virtual=0x400,
            data_payload=code_pointers(4, first=4),
        )
        unbacked = self.scan(r3_image(
            marks=(b"\xc7\x01" + synth.dwords(synth.table_va(RUN_RVA + tail)),),
            **unbacked_image))
        self.assertEqual(1, unbacked["stats"]["vptr_stores"],
                         "the tail is inside the section's data range")
        self.assertEqual(1, unbacked["stats"]["vptr_bases"])
        self.assertEqual(1, unbacked["stats"]["code_pointer_runs"],
                         "only the backed .data run exists")
        self.assertEqual({}, unbacked["tables"],
                         "the unbacked tail is not a run base")
        for index in range(4, 8):
            self.assertEqual((), vftables.slots_of(unbacked, slot_fn(index)))
        control = self.scan(r3_image(
            marks=(b"\xc7\x01" + synth.dwords(synth.table_va(synth.DATA_RVA)),),
            **unbacked_image))
        self.assertEqual(1, control["stats"]["code_pointer_runs"])
        self.assertEqual(tables_as({synth.table_va(synth.DATA_RVA): 4}),
                         control["tables"],
                         "the backed run beside the tail is a table")

    # -- 15, 17, 19. the partition itself ---------------------------------
    def test_15_overlapping_cells_cannot_exist(self):
        """Cells partition a run: one claim per dword, no gap in the middle.

        A run of 12 with marks at 3 and 7 tiles as head(0-2), cell(3-6), cell(7-11).
        The invariant is stated over whatever the engine reports, so it holds
        vacuously while R3 is absent and bites as soon as a cell exists.
        """
        self.assertStatusQuo()
        scan = self.scan(r3_image(marks=(3, 7), run_slots=12))
        seen = {}
        for slot in range(12):
            for table, index in vftables.slots_of(scan, slot_fn(slot)):
                self.assertNotIn(slot, seen, "one claim per dword of the run")
                seen[slot] = (table, index)
        for table, slots in scan["tables"].items():
            self.assertEqual(slots, len(set(range(slots))),
                             "a table's own slots are distinct indices")
        for index in range(12):
            self.assertLessEqual(len(vftables.slots_of(scan, slot_fn(index))), 1,
                                 "no dword of a run is claimed twice")
        if scan["stats"]["sound_tables"]:
            self.assertEqual(tables_as({run_va(3): 4, run_va(7): 5}), scan["tables"])
            self.assertEqual(list(range(3, 12)), sorted(seen))
            self.assertEqual({run_va(3), run_va(7)},
                             {table for table, _index in seen.values()})

    def test_16_removing_the_partition_marks_removes_the_table(self):
        """The partition mark is the only thing that makes a cell a table.

        Both images are the same length and differ in exactly the six bytes of one
        clause-2 store, which the second replaces with NOPs. The armed image is R3's
        shape; the disarmed one has no mark at all and must be silent, including for
        the dwords the surviving cell would otherwise have absorbed.
        """
        self.assertStatusQuo()
        disarmed = self.scan(r3_image(marks=(2, bytes([NOP]) * 6), run_slots=8))
        self.assertEqual(1, disarmed["stats"]["vptr_stores"],
                         "exactly one of the two stores is gone")
        self.assertEqual(1, disarmed["stats"]["vptr_bases"])
        self.assertNotIn(vftables.fmt(run_va(5)), disarmed["tables"],
                         "the unmarked base is not a table")
        for entry in vftables.slots_of(disarmed, slot_fn(5)):
            self.assertNotEqual(run_va(5), entry[0],
                                "no table exists at the unmarked base")
        if disarmed["stats"]["sound_tables"]:
            self.assertEqual(tables_as({run_va(2): 6}), disarmed["tables"],
                             "the surviving cell absorbs the unmarked dwords")
        armed = self.scan(r3_image(marks=(2, 5), run_slots=8))
        self.assertEqual(2, armed["stats"]["vptr_bases"])
        if armed["stats"]["sound_tables"]:
            self.assertEqual(tables_as({run_va(2): 3, run_va(5): 3}), armed["tables"],
                             "with both marks present each base is its own cell")

    def test_17_a_cell_never_extends_past_the_next_vptr_base(self):
        """The exact bound: a cell stops at the next marked address.

        The control is the same run with only the first mark, which is where the
        \"extends past\" behaviour is *real* -- the cell reaches the end of the run
        and the second marked address's dword is its slot 3. The bound is what stops
        that from happening once the second mark exists.
        """
        self.assertStatusQuo()
        scan = self.scan(r3_image(marks=(2, 5), run_slots=8))
        tables = tables_of(scan)
        self.assertLessEqual(tables.get(run_va(2), 0), 3,
                             "a cell may not reach past the next marked base")
        first_cell = [entry for entry in vftables.slots_of(scan, slot_fn(5))
                      if entry[0] == run_va(2)]
        self.assertEqual([], first_cell,
                         "the next marked address is never a slot of the cell below it")
        self.assertEqual((), vftables.slots_of(scan, run_va(5)),
                         "a table's own base is not one of its slots")
        single = self.scan(r3_image(marks=(2,), run_slots=8, base_marked=True))
        self.assertEqual(((run_va(0), 5),), vftables.slots_of(single, slot_fn(5)),
                         "with one mark the cell does reach the end of the run")
        if scan["stats"]["sound_tables"]:
            self.assertEqual(tables_as({run_va(2): 3, run_va(5): 3}), scan["tables"])
        absorbing = self.scan(r3_image(marks=(2,), run_slots=8))
        if absorbing["stats"]["sound_tables"]:
            self.assertEqual(tables_as({run_va(2): 6}), absorbing["tables"])
            self.assertEqual(((run_va(2), 3),),
                             vftables.slots_of(absorbing, slot_fn(5)))

    def test_18_slots_of_reports_the_r3_cell_not_the_run_base(self):
        """A membership names a cell, and a cell is always a vptr-stored address.

        The check is made against the stores this image actually contains, so it is
        independent of how the engine finds them: every table it reports is an
        address some ``MOV [R + d], imm32`` names, and in the unbacked-base image
        that set excludes the run base.
        """
        self.assertStatusQuo()
        marked = {run_va(2), run_va(5)}
        scan = self.scan(r3_image(marks=(2, 5), run_slots=8))
        for table in scan["tables"]:
            self.assertIn(int(table, 16), marked,
                          "a table base is a vptr-stored address")
        for slot in range(8):
            for table, _index in vftables.slots_of(scan, slot_fn(slot)):
                self.assertIn(table, marked, "a membership names a cell, not a run base")
                self.assertNotIn(table, (run_va(0),))
        self.assertEqual((), vftables.slots_of(scan, run_va(0)))
        if scan["stats"]["sound_tables"]:
            self.assertEqual(tables_as({run_va(2): 3, run_va(5): 3}), scan["tables"])
        backed = self.scan(r3_image(marks=(2, 5), run_slots=8, base_marked=True))
        self.assertEqual({run_va(0)}, {int(table, 16) for table in backed["tables"]},
                         "with a backed base the run base is the only table")
        self.assertTrue(vftables.is_code_address(scan, slot_fn(0)))
        self.assertFalse(vftables.is_code_address(scan, run_va(0)))

    def test_19_a_non_vptr_partition_point_is_ignored(self):
        """An address no admissible store names does not split a cell.

        The image carries a real ``[EAX]`` store naming slot 4 -- it is decoded,
        it is a data-section immediate, only its ``d == 0x40`` window position and
        the ``mod == 0, rm == 5`` absolute form keep it out -- and a cell at slot 2
        must still run to the end of the run rather than stopping at it.
        """
        self.assertStatusQuo()
        rejected = b"\xc7\x05" + synth.dwords(0x016B3C0C) + synth.dwords(run_va(4))
        scan = self.scan(r3_image(marks=(2, rejected), run_slots=8))
        self.assertEqual(1, scan["stats"]["vptr_stores"],
                         "only the register-based store is a vptr store")
        self.assertEqual(1, scan["stats"]["vptr_bases"])
        self.assertIn(run_va(4), (run_va(0), run_va(2), run_va(4)))
        tables = tables_of(scan)
        self.assertIn(tables.get(run_va(2), 0), (0, 6),
                      "the cell is whole or absent, never split at the unmarked dword")
        self.assertNotIn(vftables.fmt(run_va(4)), scan["tables"])
        if scan["stats"]["sound_tables"]:
            self.assertEqual(tables_as({run_va(2): 6}), scan["tables"])
        split = self.scan(r3_image(marks=(2, 4), run_slots=8))
        if split["stats"]["sound_tables"]:
            self.assertEqual(tables_as({run_va(2): 2, run_va(4): 4}), split["tables"],
                             "a real second mark does split the cell")

    # -- 20. the guards are load-bearing, by mutation ---------------------
    def test_20_every_guard_replaced_by_a_stand_in_fires(self):
        """Each guard, replaced by a lax stand-in, and the negative stops holding.

        Six mutations, one per guard the engine implements outside R3 itself:
        ``MIN_SLOTS`` (cases 03 and 12's shape), ``MAX_VPTR_OFFSET`` (11),
        clause 2's encoding rules via a decoder that admits every ``C7`` memory
        form (07, 08, 09, 10), clause 2's data-section test via a decoder that does
        not apply it (07), and the two section-mapping rules via readers that
        concatenate the data sections (13) or map each by its virtual size (14).
        Clause 3 is checked last and in the opposite direction: it is vacuous under
        clause 1, so replacing it must change nothing at all -- which is the property
        that lets R3 add cells without re-examining them, and the reason an R3 that
        fed the cells to ``_well_founded`` would lose every cell but the last one of
        each run.

        The two section-mapping stand-ins are asserted at the *run* level rather than
        through ``scan_bytes``: a run that genuinely crosses a section boundary is
        not representable through the public entry point, because ``scan_bytes``
        reads a table's slots out of the base section's own backed bytes and would
        raise. That is itself the proof the real reader maps each section by its own
        ``VirtualAddress``/``PointerToRawData`` pair.
        """
        # -- MIN_SLOTS -> 1: a one-dword run becomes a table.
        original_min = vftables.MIN_SLOTS
        try:
            vftables.MIN_SLOTS = 1
            one = self.scan(r3_image(run_slots=1, base_marked=True))
            self.assertEqual(1, one["stats"]["code_pointer_runs"])
            self.assertEqual(tables_as({run_va(0): 1}), one["tables"],
                             "MIN_SLOTS no longer refuses a one-dword table")
        finally:
            vftables.MIN_SLOTS = original_min
        self.assertEqual({}, self.scan(r3_image(run_slots=1, base_marked=True))["tables"])

        # -- MAX_VPTR_OFFSET -> 0x10000: a store past 0x40 marks a base.
        original_cap = vftables.MAX_VPTR_OFFSET
        try:
            vftables.MAX_VPTR_OFFSET = 0x10000
            over = self.scan(r3_image(marks=(3, 5), run_slots=8, disp=0x44,
                                      base_marked=True))
            self.assertEqual(3, over["stats"]["vptr_bases"])
            self.assertEqual(tables_as({run_va(0): 8}), over["tables"],
                             "0x44 is now inside the window")
        finally:
            vftables.MAX_VPTR_OFFSET = original_cap
        self.assertEqual(0, self.scan(r3_image(marks=(3, 5), run_slots=8, disp=0x44,
                                              base_marked=True))["stats"]["vptr_bases"])

        # -- clause 2's encoding rules replaced: SIB, EBP, and the absolute form.
        original_decode = vftables._decode_store
        try:
            vftables._decode_store = decode_any_encoding
            for label, image in (
                    ("esp", b"\xc7\x44\x24\x10"),
                    ("sib", b"\xc7\x84\x00\x10\x00\x00\x00"),
                    ("ebp", b"\xc7\x45\xe0"),
                    ("absolute", b"\xc7\x05" + synth.dwords(0x016E1AE8))):
                with self.subTest(encoding=label):
                    scan = self.scan(r3_image(
                        marks=(image + synth.dwords(run_va(3)),), run_slots=8))
                    self.assertEqual(1, scan["stats"]["vptr_stores"],
                                     "the stand-in decoder admits this encoding")
        finally:
            vftables._decode_store = original_decode
        for label, prefix in (("esp", b"\xc7\x44\x24\x10"),
                             ("sib", b"\xc7\x84\x00\x10\x00\x00\x00"),
                             ("ebp", b"\xc7\x45\xe0"),
                             ("absolute", b"\xc7\x05" + synth.dwords(0x016E1AE8))):
            with self.subTest(encoding=label, restored=True):
                scan = self.scan(r3_image(marks=(prefix + synth.dwords(run_va(3)),),
                                          run_slots=8))
                self.assertEqual(0, scan["stats"]["vptr_stores"],
                                 "the guard is back")

        # -- clause 2's data-section test replaced: a code address is a base.
        try:
            vftables._decode_store = decode_any_target
            scan = self.scan(r3_image(marks=(b"\xc7\x01" + synth.dwords(slot_fn(0)),),
                                      run_slots=8))
            self.assertEqual(1, scan["stats"]["vptr_stores"],
                             "the stand-in accepts a code-section immediate")
        finally:
            vftables._decode_store = original_decode
        self.assertEqual(0, self.scan(r3_image(
            marks=(b"\xc7\x01" + synth.dwords(slot_fn(0)),), run_slots=8)
        )["stats"]["vptr_stores"])

        # -- the two section-mapping rules replaced, at the run level.
        boundary = r3_image(marks=(0,), run_slots=1, rdata=code_pointers(1),
                            data_payload=code_pointers(1))
        parsed = vftables.Image(boundary)
        self.assertEqual({}, vftables._code_pointer_runs(parsed),
                         "a run does not cross a section boundary")
        self.assertEqual(1, len(runs_over_one_blob(parsed)),
                         "without the per-section mapping it does")

        tail_store = (b"\xc7\x01" + synth.dwords(synth.table_va(RUN_RVA + 0x200)),)
        unbacked = r3_image(marks=tail_store, run_slots=8,
                            rdata=synth.dwords(0) * 0x80, rdata_virtual=0x400,
                            data_payload=code_pointers(4))
        self.assertEqual(1, len(vftables._code_pointer_runs(vftables.Image(unbacked))))
        self.assertEqual(2, len(runs_over_virtual_windows(vftables.Image(unbacked))),
                         "mapping by virtual size invents a run in the tail")

        # -- clause 3 replaced: vacuous under clause 1, so nothing may move.
        images = (r3_image(marks=(2, 5), run_slots=8),
                  r3_image(marks=(), run_slots=8, base_marked=True),
                  boundary, unbacked)
        before = [canonical_json(self.scan(image)) for image in images]
        original_founded = vftables._well_founded
        try:
            vftables._well_founded = lambda candidates: set(candidates)
            after = [canonical_json(self.scan(image)) for image in images]
        finally:
            vftables._well_founded = original_founded
        for index, image in enumerate(images):
            with self.subTest(image=index):
                self.assertEqual(before[index], after[index],
                                 "clause 3 rejected nothing, so removing it moves nothing")


# =========================================================================== #
# R3 -- the additivity guard over the committed corpus
# =========================================================================== #
class R3CorpusGuardTest(unittest.TestCase):
    """R3 is strictly additive: no membership the R3-free pipeline reports is lost.

    The bounding condition promises this and nothing in the battery above can
    measure it, because every synthetic image is a fresh construction. This class
    states it over the real image, where the promise is the one that matters: an
    existing sound table is a proven fact, and a relaxation that dropped one would
    retract a fact the ABI engine has already cited.

    The R3-free reference is built from the three clause helpers R3 does not touch
    (:func:`r3_free_tables`), so it is by construction what ``P`` reported before
    the relaxation existed, and the assertion is a set inclusion in both directions
    of the record: every pre-R3 **table** survives with its exact slot count, and
    every pre-R3 **membership** -- a ``(table, slot)`` pair for a function address
    -- is still reported by ``slots_of`` for every committed corpus capture.

    Every test here skips itself when ``SPORE/`` is absent, the same guard the rest
    of the suite uses, so a checkout without the game still runs clean.
    """

    @classmethod
    def setUpClass(cls):
        payload = real_image_bytes()
        if payload is None:
            raise unittest.SkipTest("the binary is not present")
        cls.payload = payload
        cls.scan = vftables.scan_bytes(payload)
        cls.runs, cls.pre, cls.backed = r3_free_tables(payload)
        cls.image = vftables.Image(payload)

    def pre_memberships(self):
        """``{function address: [(table, slot), ...]}`` as ``P`` reported it.

        Rebuilt from the R3-free table set rather than read off the engine under
        test, which is the whole point: it cannot inherit a regression from the very
        implementation it is checking.
        """
        memberships = {}
        for table in sorted(self.pre):
            _slots, index, offset = self.runs[table]
            buffer = self.image.backed_bytes(self.image.sections[index])
            for slot in range(self.slots_of_table(table)):
                value = u32(buffer, offset + 4 * slot)
                memberships.setdefault(value, []).append((table, slot))
        for entries in memberships.values():
            entries.sort()
        return memberships

    def slots_of_table(self, table):
        """The pre-R3 slot count of a sound table, read from the run it is a base of."""
        return self.runs[table][0]

    def test_every_pre_r3_table_survives_with_its_slot_count(self):
        tables = tables_of(self.scan)
        self.assertEqual(1494, len(self.pre), "the measured pre-R3 table count moved")
        self.assertGreaterEqual(len(tables), len(self.pre))
        missing = sorted(table for table in self.pre if table not in tables)
        self.assertEqual([], missing,
                         "R3 retracted a sound table (first: 0x%08x)"
                         % (missing[0] if missing else 0))
        for table in self.pre:
            self.assertEqual(self.slots_of_table(table), tables[table],
                             "0x%08x kept its base and changed its length" % table)

    def test_every_pre_r3_membership_is_still_reported(self):
        memberships = self.pre_memberships()
        self.assertGreater(len(memberships), 0)
        for value, entries in sorted(memberships.items()):
            reported = vftables.slots_of(self.scan, value)
            for entry in entries:
                self.assertIn(entry, reported,
                              "0x%08x lost its (%s, %d) membership"
                              % (value, vftables.fmt(entry[0]), entry[1]))

    def test_every_committed_corpus_capture_keeps_its_memberships(self):
        """The corpus's own targets, which is what the ABI engine consumes.

        ``tests/vftable_corpus.py`` is the committed capture set the ``V1-VFT`` and
        ``T1-FWD`` tests read; a target whose memberships shrank would silently
        change an ABI record. Targets with no pre-R3 membership are included and
        asserted to have none lost, which is the ``fires``/``stack_receiver``
        distinction the corpus exists to falsify.
        """
        memberships = self.pre_memberships()
        for entry in corpus.CORPUS:
            value = int(entry["va8"], 16)
            with self.subTest(va=entry["va8"], group=entry["group"]):
                reported = vftables.slots_of(self.scan, value)
                for membership in memberships.get(value, ()):
                    self.assertIn(membership, reported,
                                  "0x%s lost a membership" % entry["va8"])

    def test_r3_adds_memberships_and_removes_none(self):
        """The direction of the relaxation, stated over the whole scan.

        Strictly additive means the post-R3 table set is a **superset** of the
        pre-R3 one, and every table in the difference is a genuine R3 cell: a
        vptr-stored address that is not itself a run base, so the only thing that
        can have promoted it is the partition. A re-slotting of an existing table,
        a retraction, or a cell at an address no store names all fail here.
        """
        tables = tables_of(self.scan)
        added = set(tables) - set(self.pre)
        self.assertEqual(set(), set(self.pre) - set(tables),
                         "R3 retracted a sound table")
        for table in sorted(added):
            self.assertIn(table, self.backed,
                          "0x%08x is not vptr-stored" % table)
            self.assertNotIn(table, self.runs,
                             "0x%08x is a run base, so it is not an R3 cell" % table)
        for table in self.pre:
            self.assertEqual(self.slots_of_table(table), tables[table],
                             "0x%08x was re-slotted" % table)
        memberships = self.pre_memberships()
        for value, entries in sorted(memberships.items()):
            self.assertTrue(set(entries).issubset(vftables.slots_of(self.scan, value)),
                            "0x%08x lost a membership" % value)


if __name__ == "__main__":
    unittest.main()
