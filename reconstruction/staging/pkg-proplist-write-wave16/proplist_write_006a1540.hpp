#pragma once

// PKG-PROLIST-WRITE-WAVE16 -- machine-derived call surface for VA 0x006a1540,
// App::PropertyList::Write
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22,
//  sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// Evidence for every displacement, constant and call site below is the
// 74-instruction listing of 0x006a1540..0x006a15f5 obtained live from the
// Ghidra bridge, plus the vtable words at 0x01408820 and the live decompilation
// of the two direct callees. Nothing here is named after an SDK field: the
// binary carries no MSVC RTTI and no published SDK structure for this class, so
// every member is identified by its machine displacement alone.
//
// Slot word: the triage record associates this target's class with the vtable
// at 0x01408820, and the word 0x006a1540 sits at 0x01408860, i.e. displacement
// +0x40 (the 17th four-byte slot) of that table. No slot semantics are claimed
// here. The neighbour at +0x3c holds 0x006a2f60 and the neighbour at +0x48
// holds 0x006a2a80; the terminator 0x00000000 is at 0x0140886c, so the table
// spans 0x01408820..0x0140886c inclusive.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-PROLIST-WRITE-WAVE16 requires an x86-32 target"
#endif

static_assert(sizeof(void *) == 4,
              "PKG-PROLIST-WRITE-WAVE16 requires 32-bit pointers");

namespace openspore::reconstruction::pkg_proplist_write_wave16 {

using Word = std::uint32_t;

// The IStream-shaped object handed in as the single stack dword. This body
// never dereferences it: it is only ever pushed as the first argument of the
// two direct calls (0x006a156a and 0x006a15b3 / 0x006a15cf), so the pointer
// value is all that is established.
struct OpaqueStream;

// One element of the range walked by this body.
//
// Established here:
//   +0x00  a 4-byte word read into the second stream call
//          (0x006a15a7, MOV EAX,dword ptr [EDI + EDX*0x1])
//   +0x04  the address handed to the third call
//          (0x006a15c4..0x006a15cb: MOV EAX,[ESI+0x18] / ADD EAX,EDI /
//           ADD EAX,0x4 / PUSH EAX)
//   size   0x18, from the loop stride 0x006a15e2 ADD EDI,0x18
//
// The remaining 0x14 bytes are never touched by this body. They are carried as
// opaque bytes on purpose; see unresolved_questions in the metadata sidecar for
// the 4-byte-versus-0x14-byte layout conflict, which this body cannot settle.
struct alignas(4) OpaquePropertyEntry {
  Word word_00;
  std::uint8_t opaque_04_17[0x14];
};

// The receiver.
//
// Established here:
//   +0x18  range begin, read three times (0x006a154d, 0x006a1577, 0x006a15a4)
//          and a fourth time at 0x006a15c4
//   +0x1c  range end,   read twice (0x006a154a, 0x006a1574)
//
// The extent past +0x1c is not established by this body, so the model stops at
// +0x20. Ghidra's live signature types the receiver as DirectPropertyList *;
// that conflicts with the demangled symbol App::PropertyList::Write and is
// recorded as an open question rather than resolved here.
struct alignas(4) OpaquePropertyList {
  std::uint8_t opaque_00_17[0x18];
  OpaquePropertyEntry *range_begin_018;
  OpaquePropertyEntry *range_end_01c;
};

static_assert(offsetof(OpaquePropertyEntry, word_00) == 0x00,
              "entry word_00 must sit at displacement 0x00");
static_assert(offsetof(OpaquePropertyEntry, opaque_04_17) == 0x04,
              "entry payload must sit at displacement 0x04");
static_assert(sizeof(OpaquePropertyEntry) == 0x18,
              "the loop stride at 0x006a15e2 is 0x18 bytes");
static_assert(offsetof(OpaquePropertyList, range_begin_018) == 0x18,
              "range begin must sit at displacement 0x18");
static_assert(offsetof(OpaquePropertyList, range_end_01c) == 0x1c,
              "range end must sit at displacement 0x1c");
static_assert(sizeof(OpaquePropertyList) == 0x20,
              "the model stops at +0x20; nothing past +0x1c is established");

// --- machine-observed callees, semantics unresolved ----------------------- //
//
// Both are declared through the port table rather than defined, because this
// package reconstructs 0x006a1540 only. Their observable calling surfaces are
// the four dwords each call site pushes, and that is exactly what the port
// signatures below encode.
//
//   0x0093aa70 -- 4 stack dwords per call, popped by the caller: the body pushes
//     0x0 / 0x1 / &word / stream (0x006a155a..0x006a156f) and 0x0 / 0x1 /
//     &word / stream (0x006a15aa..0x006a15b8), then ADD ESP,0x10 at 0x006a158d
//     and 0x006a15bd. 4 pushed plus 1 for the return address is 5 dwords, and
//     4 are removed, so the callee pops 0 and ends in a bare RET. Its live
//     decompilation reads the object it is handed as a vtable holder and
//     dispatches through the words at +0x10, +0x14 and +0x38 of that vtable,
//     byte-swapping each element when its fourth argument is not 1. Both call
//     sites here pass 0 as that fourth argument.
//
//   0x00693390 -- 3 stack dwords per call: the body pushes 0x0 / entry+0x4 /
//     stream (0x006a15c9..0x006a15d0) and then ADD ESP,0xc at 0x006a15d5, so
//     the callee pops 1 dword and ends in RET 0x4. Its live decompilation reads
//     a 16-bit word at +0x10 of the object it is handed and a 16-bit type tag
//     at +0x12 of the same object, and dispatches on the tag.
using NativeWriteWords = bool (*)(OpaqueStream *, const Word *, Word, Word);
using NativeWriteProperty = bool (*)(OpaqueStream *, std::uint8_t *, Word);

struct NativePorts {
  NativeWriteWords write_words_0093aa70;
  NativeWriteProperty write_property_00693390;
};

// The port table the reconstruction calls through. Tests replace both members.
NativePorts &proplist_write_native_ports();

#if defined(_MSC_VER)
#define PROPLIST_WRITE_THISCALL __thiscall
#else
#define PROPLIST_WRITE_THISCALL __attribute__((thiscall))
#endif

// The target. Machine ABI only: receiver in ECX, aliased into ESI at
// 0x006a1548 (MOV ESI,ECX); one ordinary stack dword at entry_ESP+0x4, read at
// 0x006a1543 (MOV EBP,dword ptr [ESP + 0x10] after three pushes, i.e.
// entry_ESP+0x4) and never written. Terminates RET 0x4 at 0x006a15f3, so the
// callee pops that dword: cdecl and fastcall are excluded by that terminator.
// The result is a bool in AL (0x006a15ef MOV AL,BL).
extern "C" bool PROPLIST_WRITE_THISCALL
write_006a1540(OpaquePropertyList *list, OpaqueStream *stream);

#undef PROPLIST_WRITE_THISCALL

// --- accessors, one per machine displacement ------------------------------ //

// 0x006a154a / 0x006a154d and 0x006a1574 / 0x006a1577:
// MOV ECX,[ESI+0x1c] / SUB ECX,[ESI+0x18] -- a 32-bit byte count, signed.
inline std::int32_t property_list_range_bytes(const OpaquePropertyList *list) {
  const auto *begin = reinterpret_cast<const std::uint8_t *>(list->range_begin_018);
  const auto *end = reinterpret_cast<const std::uint8_t *>(list->range_end_01c);
  return static_cast<std::int32_t>(end - begin);
}

// 0x006a1550..0x006a158d: the signed division by 0x18, spelled as
// IMUL 0x2AAAAAAB / SAR EDX,2 / SHR EAX,0x1f / ADD EAX,EDX. It is evaluated
// twice in the body, and the second evaluation is what bounds the loop.
inline std::int32_t property_list_entry_count(const OpaquePropertyList *list) {
  return property_list_range_bytes(list) / 0x18;
}

// 0x006a15a4 and 0x006a15c4: MOV EDX,[ESI+0x18] / MOV EAX,[ESI+0x18].
// The base is re-read from the receiver on every iteration, not hoisted.
inline OpaquePropertyEntry *
property_list_entry_at(OpaquePropertyList *list, std::int32_t offset) {
  return reinterpret_cast<OpaquePropertyEntry *>(
      reinterpret_cast<std::uint8_t *>(list->range_begin_018) + offset);
}

// 0x006a15c4..0x006a15cb: base + offset + 0x4, the second stack dword of the
// third call.
inline std::uint8_t *property_entry_payload(OpaquePropertyEntry *entry) {
  return reinterpret_cast<std::uint8_t *>(entry) + 0x4u;
}

} // namespace openspore::reconstruction::pkg_proplist_write_wave16
