#!/usr/bin/env python3
"""Sound vptr-backed vftable membership over a PE image (predicate ``P``).

What this is for
----------------
The ABI inference engine is handed one function's instruction stream and nothing
else; it has no image, so it cannot know whether the function it is looking at
is *a member of a class*. Two facts a caller can supply and this module proves
from the bytes are exactly that: which addresses are vptr-backed vftable bases,
and, for a queried function, which (table, slot index) pairs hold its address.

The predicate
-------------
``P(T)`` -- ``T`` is a vptr-backed vftable base **iff** all three clauses hold:

1. ``T`` lies in a data section of the image and is the **base of a maximal run**
   of ``>= 2`` consecutive dwords, each holding a code-section address;
2. some code instruction is ``MOV dword ptr [R + d], T`` where ``R`` is a
   general-purpose register **other than ESP or EBP**, the destination is **not**
   an absolute address and is not a SIB form, and ``0 <= d <= 0x40``;
3. no other ``T'`` satisfying clause 2 has ``T`` among its own slots -- the slot
   index is well-founded, so an address cannot be a table base and a member of
   another table at the same time.

``R3`` -- the bounded clause-1 relaxation
----------------------------------------
Clause 1's "base of a maximal run" is the only thing it ever checks, and a run has
exactly one base. So a real table that sits *interior* to a longer code-pointer
run is invisible to the predicate, and if nobody happens to vptr-store *that one
address* the entire region is invisible. On the real image the 520-slot run at
``0x0149b358`` is exactly that case: its base is vptr-stored by nobody, its first
108 slots precede the first vptr-stored address inside it, and it holds **23**
independently vptr-stored addresses. Not one table in that region is recognised,
and ``0x01053db0`` / ``0x01053e00`` have zero memberships.

That those 23 are 23 independent tables and not 23 slots is machine evidence, not
a reading: ``0x01054c29: C7 00 D8 B7 49 01  mov dword ptr [eax],0x149b7d8`` and
``0x01054c2f: C7 40 04 D8 BA 49 01  mov dword ptr [eax+0x4],0x149bad8`` install two
vptrs of *one* object at ``+0`` and ``+4``, which is the ``__thiscall``
multiple-inheritance layout: a primary table, then a secondary table for the next
base, laid down adjacently. This image has **zero** RTTI (no
``RTTICompleteObjectLocator`` anywhere), so there is no COL dword between them and
nothing but the vptr store distinguishes the two tables from each other's slots.

``R3`` therefore reads the run as a **sequence of adjacent tables**:

* partition ``R = [r0, e)`` at every address ``B`` in ``R`` satisfying clause 2;
* the cell ``[B, next-partition-or-e)`` is a table when ``B`` is vptr-backed and
  the cell length is ``>= MIN_SLOTS``;
* **bounding condition: a run whose own base ``r0`` satisfies clause 2 keeps
  exactly the pre-R3 behaviour** -- one table spanning the whole run. ``R3`` is
  therefore strictly additive: it fills regions where clause 1 currently proves
  *nothing*, and cannot alter, shorten or renumber a single existing membership.

Three properties of that wording are load-bearing:

* the cell **starts** at the marked address, so the slots before the first mark
  belong to no table -- ``R3`` never slides a cell backwards onto a run base;
* the cell **stops** at the next mark. This is what makes the bound a *lower* bound
  on the true table and never an over-claim: the next mark is a second,
  independently vptr-stored address, and clause 3 forbids it from being a slot of
  ``B``'s table, so ``B``'s table ends at or before it. Under-claiming loses
  evidence, which is an absence; over-claiming would be a false fact.
* **clause 3 runs on the pre-R3 candidate set, not on the cells.** A cell base is
  by construction at or before the end of the cell below it, so feeding cells to
  ``_well_founded`` would make every cell but the last reject itself. Clause 3 is
  vacuous under clause 1 (maximal runs of code pointers are disjoint and hold code
  addresses, while a clause-2 address is a data address) and becomes non-vacuous the
  moment clause 1 is relaxed -- the case this module's clause-3 docstring already
  anticipates. The partition supplies what clause 3 supplied: cells are disjoint, so
  a cell base is never a member of another cell.

A relaxation that was measured and **rejected**: admitting the
displacement-absolute store form (``mod == 0 && rm == 5``, ``C7 05 <abs32> <imm32>``)
to clause 2. It looks necessary -- the 520-slot run's base is vptr-stored *only* by
``0x01055902: C7 05 E8 1A 6E 01 58 B3 49 01``. It is not a vptr install. The store
sits in a class-registration sequence -- ``push 0x0`` / construct a global /
``push 0x13cadb0`` / ``call 0x11e07ef`` / test / destruct -- that assigns a table
address to a global variable; a ``[this + 0]`` install would have to be preceded by
the constructor that already set the vptr. Clause 2's exclusion of the absolute
form is load-bearing and stays. ``R3`` does not need it: the partition above reaches
``0x01053db0`` and ``0x01053e00`` through clause 2 unchanged.

**A clause-3 wording problem, stated here because the code depends on it.** The
proposal writes clause 3 as "no other ``T'`` satisfying (2) lies in
``(T, T + 4i]``", i.e. *no other vptr-stored address may lie inside ``T``'s own
run*. Read that way the clause is **not** vacuous on the real image: it rejects
**290 of the 1007** candidates -- e.g. the 37-slot run at ``0x013eb308`` holds
the vptr-stored ``0x013eb384`` and ``0x013eb394`` -- leaving 717, which
contradicts the 1007 the same proposal records and the reference scan produces.
The reading implemented here is the one that makes the clause's own stated
purpose true (a base may not be a slot of another base), and it is *provably*
vacuous under clause 1, so 1007 is preserved. The alternative is reported, not
silently chosen: 290 sound tables, and with them part of the V1 firing set,
depend on this decision.

Clause 1 is what makes a member function *virtual*: a virtual function is never
``static``, so it has a receiver and therefore a class. Clause 2 is what makes
the receiver **not** live in the callee-popped stack area: the code that installs
the vptr writes it at a small non-negative offset from a non-frame register,
i.e. at the head of the object, which is where ``__thiscall`` keeps ``this``.
Clause 3 keeps the slot index unambiguous.

What clause 2 excludes, and why each exclusion is load-bearing
--------------------------------------------------------------
* ``mod == 0 && rm == 5`` is a **displacement-absolute** destination
  (``MOV [0x0143e9b4], 0x013eb428``), a global table, not an object field.
  Confirmed on the real image: ``0x009feb54`` writes
  ``MOV [ESP+0x10], 0x013eb428`` and ``0x00404036`` writes
  ``MOV [EBP-0x2c], 0x013eb428`` -- both are frame-local callback tables, and
  both are excluded because ``rm == 4`` (SIB over ESP) and ``rm == 5`` (EBP).
* ``rm == 4`` is the SIB form; its base may be ESP or anything else, and the
  encoding of the displacement is a second byte, so the operand cannot be
  classified by the register test alone.
* ``mod == 3`` is the **register** form ``MOV r32, imm32`` -- a constant load,
  not a store to memory. It is excluded. Measured, it is also *free* on this
  image: including it leaves the store and base counts unchanged, so the
  exclusion costs nothing and removes a class of unsound candidate.

Section selection is derived from the PE section **characteristics**, not from a
name list: code = ``CNT_CODE`` or ``MEM_EXECUTE``; data = a section that
carries ``CNT_INITIALIZED_DATA``/``CNT_UNINITIALIZED_DATA`` and is neither code
nor executable, discardable (``CNT_DISCARDABLE``, the base-relocation table) nor
the resource section (located through data-directory entry 2). On the real image
that selects ``.rdata``, ``.data``, ``.tls`` and ``CONST`` and rejects ``.rsrc``
and ``.reloc`` by their flags, and it reproduces the reference's sound-table set
exactly (1007 tables, identical addresses). A toolchain that names its sections
differently is therefore handled, at the cost of a few small extra ranges, which
can only add candidates to a filter that still has to satisfy clauses 1-3.

Purity and determinism
----------------------
The whole module is a pure function of the image bytes and an optional
``image_base`` override: no clock, no network, no environment, no mutable module
state. ``scan_bytes(same_bytes) == scan_bytes(same_bytes)`` byte for byte, and
every map in the result is emitted in sorted order. The *only* impure part is
:meth:`scan_file`, which reads a file and may read or write a cache; it exists
so a 20 MB scan is not repeated per target, and it is keyed by the image's
SHA-256 so its result can never be attributed to a different binary.

Cache
-----
``scan_file`` caches the finished scan at
``<cache_dir>/vftables-<sha256-of-image>.json``, where ``cache_dir`` defaults to
``.spore-analysis/cache/`` under the repository root (a git-ignored directory --
nothing here is a committed artifact). The file name *is* the invalidation key:
a different binary is a different name, and a payload that does not re-state the
same ``sha256`` and ``cache_version``, or that is not readable JSON, is
discarded and recomputed. Nothing is ever served from a cache whose key does not
match the bytes in hand.

Measured, and how to reproduce
-----------------------------
On ``SPORE/SporeBin/SporeApp.exe`` (sha256 ``25d42a7a5c4d...``) this module
reports, in ``stats``:

===========================  =======  ==============
quantity                     this     R3 (`R3Tables`)
===========================  =======  ==============
``vptr_stores``              12,601   12,601
``vptr_bases``                4,168    4,168
``code_pointer_runs``         6,232    6,232
``sound_tables``              1,494 -> 1,882  (1,494 + 388 ``r3_tables``)
``r3_tables``                     --        388
===========================  =======  ==============

The three counts R3 does not touch are unchanged by construction. The table count
rises by exactly the number of cells inside runs whose own base is not vptr-stored;
nothing is removed and no existing table is resized.

The earlier measured table in this docstring reported 6,911 / 2,839 / 1,007 against
a 7,238 run count, attributed to two defects in the *reference* scan (a data range
mapped as one contiguous file blob that runs 1.3 MB past ``.data``, and an
immediate read at a fixed offset that drops every store carrying a displacement).
The corrected counts are the ones above, and they are what
``tests/test_vftable_membership.py`` pins.

Reproduce with:

    python3 -c "import sys; sys.path.insert(0,'.'); \
      from tools.reconstruction_tooling import vftables; \
      print(vftables.scan_file('SPORE/SporeBin/SporeApp.exe')['stats'])"

Specification: ``docs/tooling/abi-inference-vftable-extension.md`` §2.3.
Consumer: ``tools/reconstruction_tooling/abi_infer.py`` rules ``V1-VFT``/``T1-FWD``.
"""

import os

from bisect import bisect_left as _bisect_left

from .models import ROOT, canonical_json, sha256_bytes, write_json_atomic

SCHEMA = "openspore-vftable-scan-1"
#: Bumped whenever a clause of ``P``, the section-selection rule or the encoder
#: reading them changes, so a cache written by an older predicate can never be
#: served to a newer one. It is 2 because version 1 read the immediate of a
#: ``MOV r/m32, imm32`` at a fixed offset and so dropped every store carrying a
#: displacement; the digest alone does not catch that, because the *image* did
#: not change -- only the reading of it. It is 3 because ``R3`` changed clause 1's
#: consequence -- which addresses may be a table base -- while leaving the image
#: and clause 2 untouched. Same reason, same fix: a committed pre-R3 cache file
#: would otherwise be served to a post-R3 engine under a name whose key still
#: matches.
CACHE_VERSION = 3

# PE section characteristics (winnt.h). Only the bits this module reads.
SCN_CNT_CODE = 0x00000020
SCN_CNT_INITIALIZED_DATA = 0x00000040
SCN_CNT_UNINITIALIZED_DATA = 0x00000080
SCN_MEM_DISCARDABLE = 0x02000000
SCN_MEM_EXECUTE = 0x20000000

#: Default cache directory, relative to the repository root. Git-ignored.
CACHE_DIRNAME = os.path.join(".spore-analysis", "cache")

#: Clause 1: a run must be at least this many dwords to be a table.
MIN_SLOTS = 2
#: Clause 2: the vptr offset window, ``0 <= d <= 0x40``.
MAX_VPTR_OFFSET = 0x40
#: Clause 2: a table needs at least this many vptr-shaped stores naming it, or
#: clause 3 would be vacuous for a single-store candidate. Kept at 1 because the
#: clause text is an existential, and a single ``MOV [ECX], T`` in a constructor
#: is a real vptr install.
MIN_STORES = 1

_DWORD = 4
_MODRM_REG = 0x38
_MODRM_MOD = 0xC0
_MODRM_RM = 0x07
_OPCODE_MOV_RM32_IMM32 = 0xC7
_REG_ESP = 4
_REG_EBP = 5
_MOD_INDIRECT = 0
_MOD_DISP8 = 1
_MOD_DISP32 = 2


def default_cache_dir(root=ROOT):
    """The cache directory, created on demand by the writer only."""
    return os.path.join(str(root), CACHE_DIRNAME)


def cache_path(cache_dir, sha256):
    # type: (object, str) -> str
    """Cache file for one image digest. The name is the invalidation key."""
    return os.path.join(str(cache_dir), "vftables-%s.json" % str(sha256))


def _u16(blob, offset):
    if offset < 0 or offset + 2 > len(blob):
        raise ValueError("truncated PE header at %d" % offset)
    return blob[offset] | (blob[offset + 1] << 8)


def _u32(blob, offset):
    if offset < 0 or offset + 4 > len(blob):
        raise ValueError("truncated PE header at %d" % offset)
    return (blob[offset] | (blob[offset + 1] << 8)
            | (blob[offset + 2] << 16) | (blob[offset + 3] << 24))


def _i8(blob, offset):
    value = _u8(blob, offset)
    return value - 256 if value >= 128 else value


def _i32(blob, offset):
    value = _u32(blob, offset)
    return value - (1 << 32) if value >= 0x80000000 else value


def _u8(blob, offset):
    if offset < 0 or offset >= len(blob):
        raise ValueError("truncated PE header at %d" % offset)
    return blob[offset]


class Image(object):
    """A parsed, read-only PE image held entirely in memory.

    Pure over its ``data``: parsing touches no file, no clock and no
    environment. Every range is expressed in VAs derived from the optional
    header's ``ImageBase`` unless the caller overrides it.
    """

    __slots__ = ("data", "image_base", "sections", "code_ranges", "data_ranges",
                 "resource_range")

    def __init__(self, data, image_base=None):
        if not isinstance(data, (bytes, bytearray)):
            raise ValueError("image must be bytes")
        self.data = bytes(data)
        self.sections = ()
        self.code_ranges = ()
        self.data_ranges = ()
        self.resource_range = None
        self.image_base = self._parse(image_base)

    # -- parsing ---------------------------------------------------------
    def _parse(self, image_base):
        blob = self.data
        if len(blob) < 0x40 or blob[0:2] != b"MZ":
            raise ValueError("not a PE image: no MZ signature")
        pe = _u32(blob, 0x3C)
        if blob[pe:pe + 4] != b"PE\0\0":
            raise ValueError("not a PE image: no PE signature at 0x%x" % pe)
        coff = pe + 4
        section_count = _u16(blob, coff + 2)
        optional_size = _u16(blob, coff + 16)
        optional = coff + 20
        magic = _u16(blob, optional)
        if magic != 0x10B:
            # PE32+ has a different ImageBase width and a different section
            # layout for the data directories; the predicate is defined for the
            # 32-bit image this project reconstructs, and guessing here would
            # silently mis-place every address.
            raise ValueError("only PE32 images are supported (magic 0x%03x)" % magic)
        header_base = _u32(blob, optional + 28)
        directory_count = _u32(blob, optional + 92)
        resource = None
        if directory_count > 2:
            rva, size = struct_unpack_dir(blob, optional + 96 + 2 * 8)
            if size:
                resource = (rva, rva + size)
        self.resource_range = resource
        table = optional + optional_size
        sections = []
        code = []
        data = []
        for index in range(section_count):
            base = table + 40 * index
            if base + 40 > len(blob):
                raise ValueError("truncated section table at entry %d" % index)
            raw_name = blob[base:base + 8]
            name = raw_name.split(b"\0", 1)[0].decode("latin-1")
            vsize = _u32(blob, base + 8)
            vaddr = _u32(blob, base + 12)
            raw_size = _u32(blob, base + 16)
            raw_offset = _u32(blob, base + 20)
            characteristics = _u32(blob, base + 36)
            sections.append({
                "name": name,
                "vaddr": vaddr,
                "vsize": vsize,
                "raw_size": raw_size,
                "raw_offset": raw_offset,
                "characteristics": characteristics,
            })
        base = image_base if image_base is None else int(image_base)
        if not isinstance(base, int) or base < 0 or base > 0xFFFFFFFF:
            base = header_base
        self.image_base = base
        for entry in sections:
            lo = base + entry["vaddr"]
            hi = lo + entry["vsize"]
            backed = min(entry["vsize"], entry["raw_size"])
            entry["va"] = lo
            entry["end_va"] = hi
            entry["backed_bytes"] = backed
            entry["code"] = bool(entry["characteristics"] & (SCN_CNT_CODE | SCN_MEM_EXECUTE))
            entry["data"] = (bool(entry["characteristics"]
                                  & (SCN_CNT_INITIALIZED_DATA | SCN_CNT_UNINITIALIZED_DATA))
                             and not entry["code"]
                             and not entry["characteristics"] & SCN_MEM_DISCARDABLE
                             and not self._is_resource(entry["vaddr"], entry["vsize"]))
            if entry["code"]:
                code.append((lo, hi))
            if entry["data"]:
                data.append((lo, hi))
        self.sections = tuple(sections)
        self.code_ranges = tuple(sorted(code))
        self.data_ranges = tuple(sorted(data))
        return base

    def _is_resource(self, vaddr, vsize):
        span = self.resource_range
        if not span or not vsize:
            return False
        lo, hi = span
        return vaddr < hi and lo < vaddr + vsize

    # -- queries ---------------------------------------------------------
    def is_code(self, va):
        # type: (int) -> bool
        for lo, hi in self.code_ranges:
            if lo <= va < hi:
                return True
        return False

    def is_data(self, va):
        # type: (int) -> bool
        for lo, hi in self.data_ranges:
            if lo <= va < hi:
                return True
        return False

    def section_of(self, va):
        # type: (int) -> object
        for entry in self.sections:
            if entry["va"] <= va < entry["end_va"]:
                return entry
        return None

    def backed_bytes(self, section):
        # type: (object) -> bytes
        """The file-backed prefix of a section, which is all memory can hold."""
        offset = section["raw_offset"]
        return self.data[offset:offset + section["backed_bytes"]]


def struct_unpack_dir(blob, offset):
    """``(rva, size)`` of one data directory entry, or ``(0, 0)``."""
    try:
        return _u32(blob, offset), _u32(blob, offset + 4)
    except ValueError:
        return 0, 0


def _code_pointer_runs(image):
    """Clause 1, part 1: maximal runs of ``>= 2`` code pointers in data.

    Returns ``{base_va: (slot_count, section_index, byte_offset)}`` in ascending
    base order. A run never spans two sections: between them the image has an
    alignment gap that is not part of either section, so a dword sequence that
    crosses the boundary is not contiguous memory and cannot be a table.
    """
    runs = {}
    for index, section in enumerate(image.sections):
        if not section["data"]:
            continue
        buffer = image.backed_bytes(section)
        limit = len(buffer) - _DWORD
        if limit < 0:
            continue
        position = 0
        while position <= limit:
            value = _u32(buffer, position)
            if not image.is_code(value):
                position += _DWORD
                continue
            run_end = position
            while run_end + _DWORD <= len(buffer) \
                    and image.is_code(_u32(buffer, run_end)):
                run_end += _DWORD
            slots = (run_end - position) // _DWORD
            if slots >= MIN_SLOTS:
                runs[section["va"] + position] = (slots, index, position)
            position = run_end
    return runs


def _decode_store(buffer, position, image):
    # type: (bytes, int, object) -> object
    """One candidate ``MOV r/m32, imm32`` at ``position``, or ``None``.

    ``None`` is every rejection in one place, so the admissibility rules of
    clause 2 are readable as a list rather than as nesting: the opcode extension
    must be ``/0``; ``rm == 4`` (SIB) and ``rm == 5`` (EBP, or a displacement-
    absolute address when ``mod == 0``) are out, which is also what keeps ESP out
    of the eligible bases; ``mod == 3`` is the register form, a constant load
    rather than a store; and the immediate must be a data-section address.
    """
    if position + 6 > len(buffer):
        return None
    modrm = buffer[position + 1]
    mod = (modrm & _MODRM_MOD) >> 6
    extension = (modrm >> 3) & 0x7
    rm = modrm & _MODRM_RM
    if extension != 0 or rm in (_REG_ESP, _REG_EBP) or mod == 3:
        return None
    # The immediate *follows* the displacement, so where it is read depends on
    # `mod`. Reading it at a fixed offset (the reference scan's shortcut)
    # silently drops every store that carries a displacement -- 5,690 of the
    # 6,901 the reference accepts are `d == 0` alone -- and with them the whole
    # `0 <= d <= 0x40` window this clause is about.
    displacement = 0
    immediate = position + 2
    if mod == _MOD_DISP8:
        displacement = _i8(buffer, position + 2)
        immediate = position + 3
    elif mod == _MOD_DISP32:
        displacement = _i32(buffer, position + 2)
        immediate = position + 6
    if immediate + _DWORD > len(buffer):
        return None
    target = _u32(buffer, immediate)
    if not image.is_data(target):
        return None
    return (target, rm, displacement)


def _vptr_stores(image):
    """Clause 2, part 1: every ``MOV dword ptr [R + d], T`` with ``T`` in data.

    Returns ``[(va, target_va, base_register, displacement)]`` in ascending
    address order. See the module docstring for the three encodings excluded.
    """
    stores = []
    opcode = bytes([_OPCODE_MOV_RM32_IMM32])
    for section in image.sections:
        if not section["code"]:
            continue
        buffer = image.backed_bytes(section)
        position = buffer.find(opcode)
        while position >= 0:
            decoded = _decode_store(buffer, position, image)
            if decoded is not None:
                target, base_register, displacement = decoded
                stores.append((section["va"] + position, target, base_register,
                               displacement))
            position = buffer.find(opcode, position + 1)
    return stores


def _well_founded(candidates):
    """Clause 3: a candidate base may not also be a slot of another candidate.

    ``T`` is rejected when some other vptr-stored candidate ``T'`` satisfies
    ``T' < T <= T' + 4 * slots(T')`` -- ``T`` sits at or after a slot of ``T'``
    and no later than the end of that run, so it is that table's member rather
    than a table of its own, and its own "slot index" would have two answers.

    Measured on the real image this rejects **0 of 1007** candidates, and the
    reason is structural rather than lucky: clause 1 already requires ``T`` to
    be the base of a *maximal* run of code pointers, maximal runs of code
    pointers are disjoint, and every dword of such a run holds a code address
    while a clause-2 address is a data address. So a data address can never lie
    inside a code-pointer run and the clause is vacuously satisfied. It is kept
    because it is what makes the slot index well-founded, and because a future
    relaxation of clause 1 would make it bite.

    See the module docstring: the clause's text, read in the *other* direction
    (no other clause-2 address may lie inside ``T``'s own run), is not vacuous
    -- it rejects 290 of the 1007 candidates on this very image. That reading is
    reported, not implemented, because it discards sound tables and contradicts
    the measured 1007 the capability is specified against.
    """
    ordered = sorted(candidates)
    rejected = set()
    for index, table in enumerate(ordered):
        span = table + 4 * candidates[table][0]
        for other in ordered[index + 1:]:
            if other > span:
                break
            rejected.add(other)
    return set(table for table in ordered if table not in rejected)


def _r3_cells(runs, bases):
    """``R3``: partition each unclaimed run at every address clause 2 vptr-stores.

    ``runs`` is :func:`_code_pointer_runs`'s output and ``bases`` the set of
    addresses a clause-2 store names. Returns ``{cell_base: (slots, section_index,
    byte_offset)}``, ascending in base order, with the same tuple shape the
    candidate set carries, so the two are one dict downstream.

    **Bounding condition.** A run whose own base is in ``bases`` is skipped
    entirely. It already produced a table under clause 1, that table spans the whole
    run, and ``R3`` does not resize, split or renumber anything that clause 1
    already proved. This is what makes ``R3`` strictly additive.

    The head of a run is never claimed: a cell *starts* at a marked address, so the
    slots before the first mark belong to no table. Sliding a cell backwards onto
    the run base would be the unsound reading -- the run base is exactly the address
    nobody vptr-stored.

    A cell stops at the next marked address or at the end of the run, whichever
    comes first, and is a table only when it is at least ``MIN_SLOTS`` long. The
    bound is a lower bound on the true table: the next mark is a second,
    independently vptr-stored address, and clause 3 forbids it from being a slot of
    this table, so the table ends at or before it.
    """
    ordered = sorted(bases)
    cells = {}
    for table in sorted(runs):
        if table in bases:
            continue
        slots, section_index, offset = runs[table]
        end = table + 4 * slots
        first = _bisect_left(ordered, table)
        stop = _bisect_left(ordered, end)
        for index in range(first, stop):
            mark = ordered[index]
            following = ordered[index + 1] if index + 1 < stop else end
            width = (following - mark) // _DWORD
            if width >= MIN_SLOTS:
                cells[mark] = (width, section_index,
                               offset + (mark - table))
    return cells


def scan_bytes(data, image_base=None, sha256=None):
    # type: (bytes, object, object) -> dict
    """Run ``P`` (and ``R3``) over an image held in memory. Pure; no file, no cache.

    The result is JSON-shaped and deterministically ordered, so two calls with the
    same bytes are byte-identical.
    """
    image = Image(data, image_base)
    runs = _code_pointer_runs(image)
    stores = _vptr_stores(image)
    bases = {}
    for _va, target, _base_register, displacement in stores:
        if 0 <= displacement <= MAX_VPTR_OFFSET:
            bases.setdefault(target, []).append((_va, displacement))
    candidates = {table: runs[table] for table in sorted(bases)
                  if table in runs and len(bases[table]) >= MIN_STORES}
    # Clause 3 runs on the pre-R3 candidate set, never on the cells: see the module
    # docstring. A cell base sits at or before the end of the cell below it, so
    # feeding cells to `_well_founded` would make every cell but the last reject
    # itself.
    sound = _well_founded(candidates)
    r3 = _r3_cells(runs, {table for table in bases
                          if len(bases[table]) >= MIN_STORES})
    table_extents = {}
    for table in sorted(sound):
        table_extents[table] = candidates[table]
    for table in sorted(r3):
        table_extents[table] = r3[table]
    tables = {}
    memberships = {}
    for table in sorted(table_extents):
        width, index, offset = table_extents[table]
        tables[fmt(table)] = width
        section = image.sections[index]
        buffer = image.backed_bytes(section)
        for slot in range(width):
            value = _u32(buffer, offset + _DWORD * slot)
            memberships.setdefault(fmt(value), []).append([fmt(table), slot])
    for entries in memberships.values():
        entries.sort()
    return {
        "schema": SCHEMA,
        "cache_version": CACHE_VERSION,
        "binary_sha256": sha256,
        "image_base": fmt(image.image_base),
        "sections": [{
            "name": entry["name"],
            "va": fmt(entry["va"]),
            "end_va": fmt(entry["end_va"]),
            "backed_bytes": entry["backed_bytes"],
            "characteristics": fmt(entry["characteristics"]),
            "code": entry["code"],
            "data": entry["data"],
        } for entry in image.sections],
        "code_ranges": [[fmt(lo), fmt(hi)] for lo, hi in image.code_ranges],
        "data_ranges": [[fmt(lo), fmt(hi)] for lo, hi in image.data_ranges],
        "stats": {
            "code_pointer_runs": len(runs),
            "vptr_stores": len(stores),
            "vptr_bases": len(bases),
            "sound_tables": len(tables),
            "r3_tables": len(r3),
        },
        "tables": tables,
        "memberships": memberships,
    }


def fmt(value):
    # type: (int) -> str
    """The record-wide address spelling, ``0x%08x``."""
    return "0x%08x" % int(value)


def _valid_scan(value, sha256):
    """A cache payload is usable only if it is this schema, this version, and
    describes the very bytes in hand."""
    return (isinstance(value, dict)
            and value.get("schema") == SCHEMA
            and value.get("cache_version") == CACHE_VERSION
            and value.get("binary_sha256") == sha256
            and isinstance(value.get("stats"), dict)
            and isinstance(value.get("tables"), dict)
            and isinstance(value.get("memberships"), dict))


def read_cache(cache_dir, sha256):
    # type: (object, str) -> object
    """The cached scan for one digest, or ``None``. Never raises."""
    import json
    path = cache_path(cache_dir, sha256)
    try:
        with open(path, "r", encoding="utf-8") as handle:
            value = json.load(handle)
    except (OSError, ValueError):
        return None
    return value if _valid_scan(value, sha256) else None


def scan_file(path, image_base=None, cache_dir=None, use_cache=True):
    # type: (object, object, object, bool) -> object
    """Scan a PE file, through the SHA-256 cache. Never raises; ``None`` on
    anything unreadable or not a PE32 image.

    This is the only impure entry point in the module, and the only reason a
    file is named here at all: a 20 MB image is scanned once per digest, not
    once per target.
    """
    try:
        with open(str(path), "rb") as handle:
            data = handle.read()
    except OSError:
        return None
    sha = sha256_bytes(data)
    directory = default_cache_dir() if cache_dir is None else str(cache_dir)
    if use_cache:
        cached = read_cache(directory, sha)
        if cached is not None:
            return cached
    try:
        value = scan_bytes(data, image_base=image_base, sha256=sha)
    except ValueError:
        return None
    if use_cache and directory:
        try:
            if not os.path.isdir(directory):
                os.makedirs(directory)
            write_json_atomic(cache_path(directory, sha), value)
        except OSError:
            pass
    return value


def slots_of(scan, va):
    # type: (object, object) -> tuple
    """``(table_va, slot_index)`` memberships of one function, sorted.

    The function address is a **value stored in** a table, not an address into
    one, so this is a lookup in the membership index the scan built -- never an
    offset lookup. Unknown addresses return an empty tuple, which is the
    "membership not proven" answer every consumer must treat as an absence of
    evidence rather than as a negative fact.
    """
    if not isinstance(scan, dict):
        return ()
    memberships = scan.get("memberships")
    if not isinstance(memberships, dict):
        return ()
    entries = memberships.get(fmt(int(va)))
    if not isinstance(entries, list):
        return ()
    out = []
    for entry in entries:
        if isinstance(entry, list) and len(entry) == 2:
            out.append((int(entry[0], 16), entry[1]))
    out.sort()
    return tuple(out)


def is_code_address(scan, va):
    # type: (object, object) -> bool
    """Whether an address lies in a code range of the scanned image."""
    if not isinstance(scan, dict):
        return False
    needle = fmt(int(va))
    for entry in scan.get("code_ranges") or ():
        if isinstance(entry, list) and len(entry) == 2 and entry[0] <= needle < entry[1]:
            return True
    return False


def digest_of(scan):
    # type: (object) -> object
    """The image digest a scan was computed against, or ``None``."""
    return scan.get("binary_sha256") if isinstance(scan, dict) else None


def canonical(scan):
    # type: (object) -> str
    """The scan's canonical JSON, the exact bytes a cache file holds."""
    return canonical_json(scan)
