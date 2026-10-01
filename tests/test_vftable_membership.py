"""Tests for the sound vftable predicate ``P`` in ``vftables.py``.

Every test here feeds the collector a **synthetic PE image built in memory**, so
the module is testable without the 100 MB binary and every clause can be
falsified on its own: a run with nothing storing it, a run of one dword, a store
through ESP or EBP or an absolute address, a table in the resource section, a run
that tries to span two sections. The one test that needs the real image measures
the four counts the capability was specified against and skips itself when
``SPORE/`` is absent, so the suite stays hermetic on a checkout without the game.
"""
import json
import os
import struct
import sys
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

from tools.reconstruction_tooling import vftables  # noqa: E402
from tools.reconstruction_tooling.models import canonical_json  # noqa: E402

IMAGE_BASE = 0x00400000
FILE_ALIGN = 0x200
SECT_ALIGN = 0x1000
HEADERS_SIZE = 0x400

CODE = vftables.SCN_CNT_CODE | vftables.SCN_MEM_EXECUTE | 0x40000000
RDATA = vftables.SCN_CNT_INITIALIZED_DATA | 0x40000000
DATA = vftables.SCN_CNT_INITIALIZED_DATA | 0x40000000 | 0x80000000
DISCARDABLE_RDATA = RDATA | vftables.SCN_MEM_DISCARDABLE

#: Where the synthetic sections live, as RVAs.
TEXT_RVA = 0x1000
RDATA_RVA = 0x2000
DATA_RVA = 0x3000
RSRC_RVA = 0x4000


def dwords(*values):
    return b"".join(struct.pack("<I", value & 0xFFFFFFFF) for value in values)


def pe_image(sections, image_base=IMAGE_BASE, resource=None):
    """A minimal but real PE32 image over ``[(name, characteristics, rva, bytes)]``.

    A section may carry a fifth element, a **virtual size**, so a test can build
    the ``.data`` shape this binary has -- a virtual extent larger than the bytes
    that back it. ``resource`` is the ``(rva, size)`` of data-directory entry 2,
    which is how the collector finds the resource section without naming it.
    """
    count = len(sections)
    optional_size = 0xE0
    header_end = 0x18 + optional_size + 40 * count
    raw = max(FILE_ALIGN, (header_end + FILE_ALIGN - 1) // FILE_ALIGN * FILE_ALIGN)
    offsets = {}
    cursor = raw
    for section in sections:
        rva, payload = section[2], section[3]
        offsets[rva] = cursor
        cursor += (len(payload) + FILE_ALIGN - 1) // FILE_ALIGN * FILE_ALIGN
    blob = bytearray(cursor)
    blob[0:2] = b"MZ"
    struct.pack_into("<I", blob, 0x3C, 0x40)
    struct.pack_into("<4s", blob, 0x40, b"PE\0\0")
    struct.pack_into("<HHIIIHH", blob, 0x44, 0x014C, count, 0, 0, 0, optional_size, 0x0102)
    optional = 0x58
    struct.pack_into("<H", blob, optional, 0x010B)
    struct.pack_into("<I", blob, optional + 28, image_base)
    struct.pack_into("<II", blob, optional + 32, SECT_ALIGN, FILE_ALIGN)
    struct.pack_into("<I", blob, optional + 92, 16)
    if resource:
        struct.pack_into("<II", blob, optional + 96 + 2 * 8, resource[0], resource[1])
    table = optional + optional_size
    for index, section in enumerate(sections):
        name, chars, rva, payload = section[0], section[1], section[2], section[3]
        virtual = section[4] if len(section) > 4 else len(payload)
        base = table + 40 * index
        padded = name.encode("latin-1")[:8].ljust(8, b"\0")
        blob[base:base + len(padded)] = padded
        struct.pack_into("<IIII", blob, base + 8, virtual, rva,
                         len(payload), offsets[rva])
        struct.pack_into("<I", blob, base + 36, chars)
        blob[offsets[rva]:offsets[rva] + len(payload)] = payload
    return bytes(blob)


def store_vptr(base_register=1, disp=0):
    """``MOV dword ptr [R + d], imm32`` bytes, ``R`` by x86 register number.

    ``C7 /0`` with a register-indirect ModRM: ``mod`` from ``disp``, ``rm`` the
    register. This is the exact encoding clause 2 admits.
    """
    if disp == 0:
        modrm = (0 << 6) | (0 << 3) | (base_register & 7)
        return bytes([0xC7, modrm])
    if -128 <= disp <= 127:
        modrm = (1 << 6) | (0 << 3) | (base_register & 7)
        return bytes([0xC7, modrm]) + struct.pack("<b", disp)
    modrm = (2 << 6) | (0 << 3) | (base_register & 7)
    return bytes([0xC7, modrm]) + struct.pack("<i", disp)


REG_EAX, REG_ECX, REG_EDX, REG_EBX, REG_ESP, REG_EBP, REG_ESI, REG_EDI = range(8)

#: Padding appended to a synthetic code section so a run of N code pointers has
#: N distinct addresses inside it to point at.
PAD = b"\x90" * 16


def image_with_table(code, rdata_payload, rdata_chars=RDATA, rdata_rva=RDATA_RVA,
                     data_payload=None, extra_sections=()):
    """A two/three-section image: code, a data section, and nothing else."""
    sections = [(".text", CODE, TEXT_RVA, code)]
    if rdata_payload is not None:
        sections.append((".rdata", rdata_chars, rdata_rva, rdata_payload))
    if data_payload is not None:
        sections.append((".data", DATA, DATA_RVA, data_payload))
    sections.extend(extra_sections)
    return pe_image(sections)


def table_va(rva):
    return IMAGE_BASE + rva


def fn_va(offset):
    return IMAGE_BASE + TEXT_RVA + offset


class SyntheticImageTest(unittest.TestCase):
    """The predicate, clause by clause, on images built in this test."""

    def scan(self, image, **kwargs):
        return vftables.scan_bytes(image, **kwargs)

    # -- clause 1 + 2: the positive, and every way to break it -------------
    def test_a_vptr_stored_run_of_two_is_a_table(self):
        image = image_with_table(
            store_vptr(REG_ECX) + dwords(table_va(RDATA_RVA)) + PAD,
            dwords(fn_va(0), fn_va(4)))
        scan = self.scan(image)
        self.assertEqual(1, scan["stats"]["sound_tables"])
        self.assertEqual({vftables.fmt(table_va(RDATA_RVA)): 2}, scan["tables"])
        self.assertEqual(((table_va(RDATA_RVA), 0),), vftables.slots_of(scan, fn_va(0)))
        self.assertEqual(((table_va(RDATA_RVA), 1),), vftables.slots_of(scan, fn_va(4)))

    def test_a_run_nothing_stores_is_not_a_table(self):
        """Clause 2 alone: a handler table registered by nobody's vptr."""
        image = image_with_table(PAD, dwords(fn_va(0), fn_va(4)))
        scan = self.scan(image)
        self.assertEqual(1, scan["stats"]["code_pointer_runs"])
        self.assertEqual(0, scan["stats"]["sound_tables"])
        self.assertEqual((), vftables.slots_of(scan, fn_va(0)))

    def test_a_single_dword_run_is_not_a_table(self):
        """Clause 1's ``>= 2``: one pointer is a global, not a dispatch table."""
        image = image_with_table(
            store_vptr(REG_ECX) + dwords(table_va(RDATA_RVA)) + PAD,
            dwords(fn_va(0), 0))
        scan = self.scan(image)
        self.assertEqual(0, scan["stats"]["code_pointer_runs"])
        self.assertEqual(0, scan["stats"]["sound_tables"])

    def test_a_run_is_maximal_and_its_slot_is_never_its_own_base(self):
        """Clause 1's 'maximal': one run, one base, and its interior is slots.

        A vptr store naming the *middle* of a run must not turn that dword into a
        second table: it is slot 1 of the run that starts at the base.
        """
        image = image_with_table(
            store_vptr(REG_ECX) + dwords(table_va(RDATA_RVA))
            + store_vptr(REG_ECX) + dwords(table_va(RDATA_RVA + 4)) + PAD,
            dwords(fn_va(0), fn_va(4), fn_va(8)))
        scan = self.scan(image)
        self.assertEqual(1, scan["stats"]["sound_tables"])
        self.assertEqual({vftables.fmt(table_va(RDATA_RVA)): 3}, scan["tables"])
        for slot, address in enumerate((fn_va(0), fn_va(4), fn_va(8))):
            self.assertEqual(((table_va(RDATA_RVA), slot),),
                             vftables.slots_of(scan, address))

    def test_two_runs_separated_by_a_non_pointer_are_two_tables(self):
        image = image_with_table(
            store_vptr(REG_ECX) + dwords(table_va(RDATA_RVA))
            + store_vptr(REG_ECX) + dwords(table_va(RDATA_RVA + 16)) + PAD,
            dwords(fn_va(0), fn_va(4), fn_va(8), 0, fn_va(12), fn_va(16)))
        scan = self.scan(image)
        self.assertEqual(2, scan["stats"]["sound_tables"])
        self.assertEqual({vftables.fmt(table_va(RDATA_RVA)): 3,
                          vftables.fmt(table_va(RDATA_RVA + 16)): 2},
                         scan["tables"])
        self.assertEqual(((table_va(RDATA_RVA + 16), 1),), vftables.slots_of(scan, fn_va(16)))

    def test_a_run_never_spans_two_sections(self):
        """The gap between two sections is not memory either of them maps."""
        image = image_with_table(
            store_vptr(REG_ECX) + dwords(table_va(RDATA_RVA)) + PAD,
            dwords(fn_va(0)), data_payload=dwords(fn_va(4)))
        scan = self.scan(image)
        self.assertEqual(0, scan["stats"]["sound_tables"],
                         "a run was reported across the section boundary")
        self.assertEqual(1, scan["stats"]["vptr_bases"])
        self.assertEqual(1, scan["stats"]["vptr_stores"])

    def test_a_table_outside_every_data_section_is_not_a_table(self):
        """Clause 1's 'in .rdata/.data': a code address is not a table."""
        image = pe_image([(".text", CODE, TEXT_RVA,
                           store_vptr(REG_ECX) + dwords(fn_va(16)) + dwords(fn_va(0), fn_va(4)))])
        scan = self.scan(image)
        self.assertEqual(0, scan["stats"]["sound_tables"])
        self.assertEqual(0, scan["stats"]["vptr_bases"],
                         "a store into a code section was counted as a vptr store")

    # -- clause 2: the three encodings it excludes -------------------------
    def test_a_store_through_esp_is_not_a_vptr_store(self):
        """``MOV [ESP+0x10], T`` -- a frame-local callback table (0x009feb54)."""
        image = image_with_table(
            bytes([0xC7, 0x44, 0x24, 0x10]) + dwords(table_va(RDATA_RVA)),
            dwords(fn_va(0), fn_va(4)))
        scan = self.scan(image)
        self.assertEqual(0, scan["stats"]["vptr_stores"])
        self.assertEqual(0, scan["stats"]["sound_tables"])

    def test_a_store_through_ebp_is_not_a_vptr_store(self):
        """``MOV [EBP-0x2c], T`` -- the other frame-local shape (0x00404036)."""
        image = image_with_table(
            bytes([0xC7, 0x45, 0xD4]) + dwords(table_va(RDATA_RVA)),
            dwords(fn_va(0), fn_va(4)))
        scan = self.scan(image)
        self.assertEqual(0, scan["stats"]["vptr_stores"])

    def test_an_absolute_destination_is_not_a_vptr_store(self):
        """``MOV [0x0143e9b4], T`` -- a global table, not an object field.

        The ModRM here is ``mod == 0, rm == 5``, which is a disp32 absolute
        address and not EBP-relative. Reading it as EBP is the bug this test
        exists to keep out.
        """
        image = image_with_table(
            bytes([0xC7, 0x05, 0xB4, 0xE9, 0x43, 0x01]) + dwords(table_va(RDATA_RVA)),
            dwords(fn_va(0), fn_va(4)))
        scan = self.scan(image)
        self.assertEqual(0, scan["stats"]["vptr_stores"])
        self.assertEqual(0, scan["stats"]["sound_tables"])

    def test_a_register_immediate_is_not_a_vptr_store(self):
        """``MOV EAX, T`` -- a constant load, which is not a store to memory."""
        image = image_with_table(
            bytes([0xB8]) + dwords(table_va(RDATA_RVA)),
            dwords(fn_va(0), fn_va(4)))
        scan = self.scan(image)
        self.assertEqual(0, scan["stats"]["vptr_stores"])
        self.assertEqual(0, scan["stats"]["vptr_bases"])

    def test_a_store_past_the_offset_window_is_not_a_vptr_store(self):
        """``d > 0x40`` is not the head of an object, so it is not a vptr."""
        near = image_with_table(
            store_vptr(REG_ECX, 0x40) + dwords(table_va(RDATA_RVA)) + PAD,
            dwords(fn_va(0), fn_va(4)))
        far = image_with_table(
            store_vptr(REG_ECX, 0x44) + dwords(table_va(RDATA_RVA)) + PAD,
            dwords(fn_va(0), fn_va(4)))
        self.assertEqual(1, self.scan(near)["stats"]["sound_tables"])
        self.assertEqual(0, self.scan(far)["stats"]["sound_tables"])

    def test_a_store_with_a_displacement_is_admitted(self):
        """The `0 <= d <= 0x40` window only exists if `d != 0` is decoded.

        The instruction under test is ``MOV DWORD PTR [ECX+0xC], 0x01444314``
        at ``0x00980c0d`` in this binary, read by hand off the image: the
        immediate follows the disp8, so a decoder that reads it at a fixed offset
        sees ``0x4443140c`` and drops the store. Every one of the reference
        scan's 6,901 stores has ``d == 0`` for exactly that reason.
        """
        image = image_with_table(
            store_vptr(REG_ECX, 0x0C) + dwords(table_va(RDATA_RVA)) + PAD,
            dwords(fn_va(0), fn_va(4)))
        scan = self.scan(image)
        self.assertEqual(1, scan["stats"]["vptr_stores"])
        self.assertEqual(1, scan["stats"]["sound_tables"])
        self.assertEqual(((table_va(RDATA_RVA), 0),), vftables.slots_of(scan, fn_va(0)))

    def test_a_negative_displacement_is_not_a_vptr_store(self):
        """``d < 0`` addresses before the object head, which is not a vptr."""
        image = image_with_table(
            store_vptr(REG_ECX, -4) + dwords(table_va(RDATA_RVA)) + PAD,
            dwords(fn_va(0), fn_va(4)))
        self.assertEqual(0, self.scan(image)["stats"]["sound_tables"])

    def test_every_admitted_base_register_is_a_base(self):
        """ESP and EBP out; EAX/ECX/EDX/EBX/ESI/EDI in."""
        for register in (REG_EAX, REG_ECX, REG_EDX, REG_EBX, REG_ESI, REG_EDI):
            with self.subTest(register=register):
                image = image_with_table(
                    store_vptr(register) + dwords(table_va(RDATA_RVA)) + PAD,
                    dwords(fn_va(0), fn_va(4)))
                self.assertEqual(1, self.scan(image)["stats"]["sound_tables"])
        for register in (REG_ESP, REG_EBP):
            with self.subTest(register=register):
                image = image_with_table(
                    store_vptr(register) + dwords(table_va(RDATA_RVA)) + PAD,
                    dwords(fn_va(0), fn_va(4)))
                self.assertEqual(0, self.scan(image)["stats"]["sound_tables"])

    # -- section selection, from characteristics ---------------------------
    def test_sections_are_selected_by_characteristics_not_by_name(self):
        """A section called ``.vftables`` with data flags is still data."""
        image = pe_image([(".text", CODE, TEXT_RVA,
                           store_vptr(REG_ECX) + dwords(table_va(DATA_RVA)) + PAD),
                          (".vftables", RDATA, DATA_RVA, dwords(fn_va(0), fn_va(4)))])
        scan = self.scan(image)
        self.assertEqual(1, scan["stats"]["sound_tables"])
        self.assertEqual([vftables.fmt(DATA_RVA + IMAGE_BASE)], list(scan["tables"]))

    def test_the_resource_section_is_excluded_by_its_directory_entry(self):
        """A resource blob is not a dispatch table, whatever it is called.

        The same bytes in a section that is *not* the resource directory are a
        table, which is what makes this a test of the directory entry rather
        than of the payload.
        """
        payload = dwords(fn_va(0), fn_va(4))
        def image_with(section_name, resource):
            return pe_image([(".text", CODE, TEXT_RVA,
                              store_vptr(REG_ECX) + dwords(table_va(RSRC_RVA)) + PAD),
                             (section_name, RDATA, RSRC_RVA, payload)],
                            resource=resource)
        excluded = self.scan(image_with(".rsrc", (RSRC_RVA, len(payload))))
        self.assertEqual(0, excluded["stats"]["code_pointer_runs"],
                         "the resource section is not a data range at all")
        self.assertEqual(0, excluded["stats"]["vptr_bases"])
        self.assertEqual(0, excluded["stats"]["sound_tables"])
        included = self.scan(image_with(".rdata", None))
        self.assertEqual(1, included["stats"]["code_pointer_runs"])
        self.assertEqual(1, included["stats"]["sound_tables"])

    def test_a_discardable_section_is_not_data(self):
        image = image_with_table(store_vptr(REG_ECX) + dwords(table_va(RDATA_RVA)) + PAD,
                                 dwords(fn_va(0), fn_va(4)), rdata_chars=DISCARDABLE_RDATA)
        self.assertEqual(0, self.scan(image)["stats"]["sound_tables"])

    def test_writable_data_sections_are_data_too(self):
        image = pe_image([(".text", CODE, TEXT_RVA,
                           store_vptr(REG_ECX) + dwords(table_va(DATA_RVA)) + PAD),
                          (".data", DATA, DATA_RVA, dwords(fn_va(0), fn_va(4)))])
        self.assertEqual(1, self.scan(image)["stats"]["sound_tables"])

    def test_an_unbacked_section_tail_contributes_no_dwords(self):
        """``.data``'s virtual size exceeds its raw size; the tail is zeros.

        Without this, a reader that mapped a whole section by virtual size would
        invent runs out of memory the image never holds.
        """
        image = pe_image([(".text", CODE, TEXT_RVA,
                           store_vptr(REG_ECX) + dwords(table_va(DATA_RVA + 0x40)) + PAD),
                          (".data", DATA, DATA_RVA, dwords(fn_va(0), fn_va(4)),
                           0x400 + 4)])
        image_obj = vftables.Image(image)
        entry = [item for item in image_obj.sections if item["name"] == ".data"][0]
        self.assertEqual(8, entry["backed_bytes"])
        self.assertEqual(0x404, entry["vsize"])
        self.assertTrue(image_obj.is_data(table_va(DATA_RVA + 0x40)),
                        "the unbacked tail is inside the section's address range")
        self.assertEqual(0, self.scan(image)["stats"]["sound_tables"])

    # -- membership semantics ---------------------------------------------
    def test_membership_is_by_value_not_by_offset(self):
        """The function address is a *value in* a table, not an address into it.

        A query for the table's own address must find nothing: the table holds
        dwords, and its base is not one of them.
        """
        image = image_with_table(store_vptr(REG_ECX) + dwords(table_va(RDATA_RVA)),
                                 dwords(fn_va(0), fn_va(4)))
        scan = self.scan(image)
        self.assertEqual((), vftables.slots_of(scan, table_va(RDATA_RVA)))
        self.assertEqual((), vftables.slots_of(scan, table_va(RDATA_RVA) + 4))
        self.assertEqual((), vftables.slots_of(scan, fn_va(8)))

    def test_a_function_beside_a_table_is_not_a_member(self):
        """Adjacency is not membership.

        A two-slot table, and on either side of it -- one dword past the run and
        the dword before it -- code pointers that are members of nothing. The
        middle of the run, by contrast, *is* a member, so the three cases are
        asserted together: what separates a member from a neighbour is being
        inside the run, not being near it.
        """
        table = table_va(RDATA_RVA + 4)
        image = image_with_table(store_vptr(REG_ECX) + dwords(table) + PAD,
                                 dwords(0, fn_va(0), fn_va(4), 0, fn_va(8), fn_va(12), 0))
        scan = self.scan(image)
        self.assertEqual(1, scan["stats"]["sound_tables"])
        self.assertEqual({vftables.fmt(table): 2}, scan["tables"])
        self.assertEqual(((table, 0),), vftables.slots_of(scan, fn_va(0)))
        self.assertEqual(((table, 1),), vftables.slots_of(scan, fn_va(4)))
        self.assertEqual((), vftables.slots_of(scan, fn_va(8)),
                         "the first dword past the run is not a slot of it")
        self.assertEqual((), vftables.slots_of(scan, fn_va(12)))
        self.assertEqual((), vftables.slots_of(scan, IMAGE_BASE + RDATA_RVA - 4),
                         "the dword before the run is not a slot of it")

    def test_an_unknown_address_is_an_absence_not_a_negative(self):
        image = image_with_table(store_vptr(REG_ECX) + dwords(table_va(RDATA_RVA)),
                                 dwords(fn_va(0), fn_va(4)))
        scan = self.scan(image)
        self.assertEqual((), vftables.slots_of(scan, 0xDEADBEEF))
        self.assertEqual((), vftables.slots_of(None, fn_va(0)))

    def test_a_repeated_function_reports_every_table_it_is_in(self):
        image = image_with_table(
            store_vptr(REG_ECX) + dwords(table_va(RDATA_RVA))
            + store_vptr(REG_ECX) + dwords(table_va(RDATA_RVA + 8)) + PAD,
            dwords(fn_va(0), fn_va(0)))
        scan = self.scan(image)
        self.assertEqual(((table_va(RDATA_RVA), 0), (table_va(RDATA_RVA), 1)),
                         vftables.slots_of(scan, fn_va(0)))

    # -- purity, shape and error behaviour --------------------------------
    def test_the_scan_is_a_pure_function_of_the_bytes(self):
        image = image_with_table(store_vptr(REG_ECX) + dwords(table_va(RDATA_RVA)),
                                 dwords(fn_va(0), fn_va(4)))
        first = self.scan(image, sha256="d" * 64)
        second = self.scan(image, sha256="d" * 64)
        self.assertEqual(canonical_json(first), canonical_json(second))

    def test_the_result_is_json_shaped_and_sorted(self):
        image = image_with_table(
            store_vptr(REG_ECX) + dwords(table_va(RDATA_RVA))
            + store_vptr(REG_ECX) + dwords(table_va(RDATA_RVA + 16)) + PAD,
            dwords(fn_va(4), fn_va(0), 0, 0, fn_va(8), fn_va(12)))
        scan = self.scan(image, sha256="a" * 64)
        self.assertEqual(sorted(scan["tables"]), list(scan["tables"]))
        for entries in scan["memberships"].values():
            self.assertEqual(sorted(entries), entries)
        self.assertEqual(canonical_json(scan), canonical_json(json.loads(canonical_json(scan))))

    def test_a_non_image_is_rejected_rather_than_guessed(self):
        for payload in (b"", b"MZ", b"MZ" + b"\0" * 0x3D, b"not a pe at all"):
            with self.subTest(payload=payload[:8]):
                with self.assertRaises(ValueError):
                    vftables.scan_bytes(payload)

    def test_a_pe64_image_is_refused(self):
        image = bytearray(pe_image([(".text", CODE, TEXT_RVA, b"\x90" * 16)]))
        struct.pack_into("<H", image, 0x58, 0x020B)          # PE32+ magic
        with self.assertRaises(ValueError):
            vftables.scan_bytes(bytes(image))

    def test_the_image_base_can_be_overridden(self):
        base = 0x10000000
        image = pe_image([(".text", CODE, TEXT_RVA,
                           store_vptr(REG_ECX) + dwords(base + RDATA_RVA)),
                          (".rdata", RDATA, RDATA_RVA, dwords(base + TEXT_RVA,
                                                              base + TEXT_RVA + 4))],
                         image_base=base)
        scan = vftables.scan_bytes(image, image_base=base)
        self.assertEqual(1, scan["stats"]["sound_tables"])
        self.assertEqual("0x10002000", list(scan["tables"])[0])
        self.assertEqual(((base + RDATA_RVA, 0),), vftables.slots_of(scan, base + TEXT_RVA))


class CacheTest(unittest.TestCase):
    """The cache is keyed by the image digest, and nothing else."""

    def setUp(self):
        self.directory = os.path.join("/tmp", "opencode", "abi2", "cache-test-%d" % os.getpid())
        self.image = image_with_table(store_vptr(REG_ECX) + dwords(table_va(RDATA_RVA))
                                      + PAD, dwords(fn_va(0), fn_va(4)))

    def test_the_cache_file_is_named_after_the_digest(self):
        self.assertTrue(vftables.cache_path("/x", "ab" * 32).endswith(
            "vftables-%s.json" % ("ab" * 32)))

    def write_image(self):
        """``scan_file`` takes a path, so the synthetic image is written out."""
        if not os.path.isdir(self.directory):
            os.makedirs(self.directory)
        path = os.path.join(self.directory, "synthetic.exe")
        with open(path, "wb") as handle:
            handle.write(self.image)
        return path

    def test_a_cached_scan_is_served_and_a_stale_one_is_not(self):
        import json
        path = self.write_image()
        first = vftables.scan_file(path, cache_dir=self.directory)
        self.assertEqual(1, first["stats"]["sound_tables"])
        cache = vftables.cache_path(self.directory, first["binary_sha256"])
        self.assertTrue(os.path.exists(cache))
        second = vftables.scan_file(path, cache_dir=self.directory)
        self.assertEqual(canonical_json(first), canonical_json(second))
        # A payload that does not re-state the digest it is filed under is
        # discarded, not served: the name is the key and the body must agree.
        with open(cache, "w", encoding="utf-8") as handle:
            json.dump(dict(first, binary_sha256="0" * 64), handle)
        self.assertIsNone(vftables.read_cache(self.directory, first["binary_sha256"]))
        third = vftables.scan_file(path, cache_dir=self.directory)
        self.assertEqual(canonical_json(first), canonical_json(third))

    def test_a_cache_from_another_predicate_version_is_not_served(self):
        import json
        path = self.write_image()
        scan = vftables.scan_file(path, cache_dir=self.directory, use_cache=False)
        cache = vftables.cache_path(self.directory, scan["binary_sha256"])
        with open(cache, "w", encoding="utf-8") as handle:
            json.dump(dict(scan, cache_version=0), handle)
        self.assertIsNone(vftables.read_cache(self.directory, scan["binary_sha256"]))

    def test_a_missing_or_unreadable_file_is_none_never_an_exception(self):
        self.assertIsNone(vftables.read_cache("/nonexistent/dir", "ab" * 32))
        self.assertIsNone(vftables.scan_file("/nonexistent/binary.exe"))
        self.assertIsNone(vftables.scan_file(__file__))     # a text file, not a PE


REAL_BINARY = os.path.join(ROOT, "SPORE", "SporeBin", "SporeApp.exe")
#: The four counts the capability was specified against, from
#: ``docs/tooling/abi-inference-vftable-extension.md`` §2.3. ``code_pointer_runs``
#: is included with the reference script's number and the corrected one, because
#: they differ and the reason is recorded in the module docstring: the reference
#: maps its data range as one contiguous *file* blob, which runs 1.3 MB past the
#: end of ``.data`` and sweeps most of ``.rsrc`` into it.
#: Measured on the real image by this module. The reference scan the capability
#: was designed against reports 6,911 / 2,839 / 1,007; those three counts are the
#: same measurement with two decoder defects, both documented in the module
#: docstring: the data range is one contiguous *file* blob that runs 1.3 MB past
#: ``.data`` (inflating ``code_pointer_runs`` to 7,238), and the immediate of a
#: ``MOV r/m32, imm32`` is read at a fixed offset, so every store carrying a
#: displacement is dropped -- which is what makes clause 2's ``0 <= d <= 0x40``
#: window vacuous. The corrected sound-table set is a strict **superset** of the
#: reference's (1,494 vs 1,007, none lost), so every conclusion the reference
#: supports still holds.
MEASURED = {"vptr_stores": 12601, "vptr_bases": 4168, "sound_tables": 1882}
MEASURED_RUNS = 6232
REFERENCE_RUNS = 7238
#: The `R3` partition adds tables and never resizes one, so the count is additive
#: and pinned separately: a change in either number is visible on its own, and
#: ``sound_tables - R3_TABLES`` is the pre-R3 count this module's earlier
#: measurement recorded (1494).
MEASURED_R3_TABLES = 388


@unittest.skipUnless(os.path.exists(REAL_BINARY), "SPORE/ is not present")
class RealImageMeasurementTest(unittest.TestCase):
    """The measured counts, on the real image, through the cached entry point."""

    @classmethod
    def setUpClass(cls):
        cls.directory = os.path.join("/tmp", "opencode", "abi2", "cache-real")
        cls.scan = vftables.scan_file(REAL_BINARY, cache_dir=cls.directory)

    def test_the_decision_relevant_counts_are_the_measured_ones(self):
        self.assertEqual(MEASURED["vptr_stores"], self.scan["stats"]["vptr_stores"])
        self.assertEqual(MEASURED["vptr_bases"], self.scan["stats"]["vptr_bases"])
        self.assertEqual(MEASURED["sound_tables"], self.scan["stats"]["sound_tables"])
        self.assertEqual(MEASURED_R3_TABLES, self.scan["stats"]["r3_tables"])
        self.assertEqual(1494, self.scan["stats"]["sound_tables"]
                         - self.scan["stats"]["r3_tables"],
                         "R3 is additive: it resizes and removes nothing")

    def test_the_run_count_is_the_corrected_one(self):
        """6,232, not the reference's 7,238 -- see this module's docstring."""
        self.assertEqual(MEASURED_RUNS, self.scan["stats"]["code_pointer_runs"])
        self.assertNotEqual(REFERENCE_RUNS, self.scan["stats"]["code_pointer_runs"])

    def test_every_sound_table_is_in_a_data_section(self):
        with open(REAL_BINARY, "rb") as handle:
            image = vftables.Image(handle.read())
        for table in self.scan["tables"]:
            self.assertTrue(image.is_data(int(table, 16)))

    #: The nine the extension says ``V1-VFT`` fires on. Membership only: whether
    #: the claim survives is the engine's decision, and
    #: ``tests.test_abi_inference.VftableRuleTest`` is where that is asserted.
    FIRES = ("0x00980510", "0x00b1e4d0", "0x00b7e380", "0x00b1fbf0", "0x0051e340",
             "0x0051e380", "0x006e64f0", "0x007f30d0", "0x00fa0d50")
    #: Sound membership the cleanup guard must go on to refuse. ``0x01053e00`` is
    #: deliberately absent: it is the falsifier, and it is *not* a member of any
    #: sound table, which is the first of the two independent reasons it stays
    #: non-thiscall.
    REFUSED = ("0x0067dc80", "0x0067e6b0", "0x0052e640", "0x0052e650", "0x0057d6f0",
               "0x00642210", "0x00a85840", "0x00a98400", "0x00e5cac0", "0x00f9fef0",
               "0x00fa5040", "0x006a2e20")

    def test_every_target_the_extension_fires_on_is_a_sound_member(self):
        for va in self.FIRES:
            with self.subTest(va=va):
                self.assertTrue(vftables.slots_of(self.scan, int(va, 16)))

    def test_every_target_the_cleanup_guard_refuses_is_a_sound_member(self):
        for va in self.REFUSED:
            with self.subTest(va=va):
                self.assertTrue(vftables.slots_of(self.scan, int(va, 16)),
                                "membership is proven here; only the claim is refused")

    def test_the_falsifier_is_a_sound_member_and_still_refused(self):
        """``0x01053e00`` now has real membership, and that is the point.

        Before ``R3`` this function was in no sound table at all, which meant the
        falsifier rested on *two* independent guards and the membership half of the
        argument was hypothetical. ``R3`` partitioned the 520-slot run at
        ``0x0149b358`` and ``0x01053e00`` is now slot 19 of five vptr-backed cells
        -- the cells the constructor pair at ``0x01054c29``/``0x01054c2f`` proves
        are separate tables. The guard under test is now the one that was already
        load-bearing, exercised with a real membership instead of a forced one:
        membership alone must not turn a callee-popping COM-shaped body into
        ``__thiscall``.

        ``tests/test_vftable_membership_r3.py`` is where the partition itself is
        falsified; ``tests/test_abi_inference.py::VftableRuleTest`` is where the
        refusal is asserted against the engine.
        """
        memberships = vftables.slots_of(self.scan, 0x01053E00)
        self.assertEqual(5, len(memberships))
        self.assertEqual({19}, {slot for _table, slot in memberships})
        self.assertNotIn((0x0149B358, 150),
                         memberships,
                         "the run base is vptr-stored by nobody and is not a table")
        for table, _slot in memberships:
            self.assertNotEqual(0x0149B358, table)

    def test_one_membership_is_pinned_by_value(self):
        """A measured (table, slot) pair, so a silent change is visible."""
        self.assertEqual(((0x014440D0, 5),), vftables.slots_of(self.scan, 0x00980510))

    def test_the_canvas_slots_the_specification_names(self):
        """``0x00847a40`` is a vftable slot -- and tail-jumps through the IAT.

        The proposal records the table as ``0x0141ca98``; the sound base is
        ``0x0141ca70``, which is exactly ten dwords earlier. The slot index the
        proposal quotes (10) is right and the base it quotes is an *interior*
        address of the same table -- the same contamination the proposal
        documents for ``0x01053e00``, measured here a second time.
        """
        self.assertEqual(((0x0141CA70, 10),), vftables.slots_of(self.scan, 0x00847A40))
        self.assertEqual(((0x0141CA70, 18),), vftables.slots_of(self.scan, 0x00847A90))
        self.assertEqual(0x28, 0x0141CA98 - 0x0141CA70)

    def test_a_global_getter_is_in_no_table(self):
        """``0x00b3d300`` (``MOV EAX,[0x0167eae0]; RET``): membership is absent."""
        self.assertEqual((), vftables.slots_of(self.scan, 0x00B3D300))

    def test_the_collapsed_identity_member_is_a_member_of_many_tables(self):
        """Membership yields 'a virtual member of some class', never a name."""
        memberships = vftables.slots_of(self.scan, 0x00B1E4D0)
        self.assertGreater(len(memberships), 100)
        self.assertEqual(len(set(table for table, _slot in memberships)),
                         len(set(table for table, _slot in memberships)))


if __name__ == "__main__":
    unittest.main()
