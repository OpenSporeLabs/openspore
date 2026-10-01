#pragma once

// PKG-APP-PROLIST-COPYALL-WAVE16 -- opaque layout and machine-observed call
// surface for VA 0x006a14d0, App::PropertyList::CopyAllPropertiesFrom
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22,
//  sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// Every displacement in this header is read off the 25-instruction listing of
// 0x006a14d0..0x006a1506 (body_end 0x006a1508) and off the two raw vtable
// images at 0x01408820 and 0x01408870, and nothing else. The binary carries no
// MSVC RTTI, so no member is named after an SDK field: each word is identified
// by its machine displacement, and where the Ghidra record supplies an SDK name
// for a word the comment says so explicitly and marks it as decompiler-derived.
//
// SCOPE OF THE RECEIVER RECORD. The body of 0x006a14d0 addresses exactly two
// displacements on its receiver: 0x00 (the vtable word, read three times) and
// 0x30 (read once, then written with zero). The other displacements declared
// below -- 0x04, 0x18, 0x1c, 0x34, 0x38, 0x3c -- are NOT established by this
// body. They are carried because this target's own vtable slots point at code
// that touches them (0x006a2a80 / 0x006a2b20 / 0x006a2f10 / 0x006a1510) and
// because the sibling reconstruction in pkg-app-proplist-wave13 read 0x18, 0x1c
// and 0x34. Each is attributed below to the record that observed it. A
// displacement nobody observed is opaque filler, not a claimed field.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-APP-PROLIST-COPYALL-WAVE16 requires an x86-32 target"
#endif

static_assert(sizeof(void *) == 4,
              "PKG-APP-PROLIST-COPYALL-WAVE16 requires 32-bit pointers");

#if defined(_MSC_VER)
#define PKG_APP_PROPLIST_COPYALL_WAVE16_THISCALL __thiscall
#else
// x86-32 thiscall is a free-function convention here, because the machine ABI
// is modelled at the C level (extern "C") rather than as C++ member functions.
// GCC accepts the attribute but warns that it is "used for non-class method",
// which is exactly the intended use; the warning is suppressed rather than the
// convention weakened, so the package builds clean under both clang++ (the
// gate the repository uses) and g++.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#define PKG_APP_PROPLIST_COPYALL_WAVE16_THISCALL __attribute__((thiscall))
#endif

namespace openspore {
namespace reconstruction {
namespace pkg_app_proplist_copyall_wave16 {
struct alignas(4) OpaquePropertyList;

// --- vtable slots this body dispatches through --------------------------- //
// Three indirect transfers leave this body, all of the form
// MOV EDX,[EAX + slot] / CALL EDX, and each is named for the target the two
// vtable images place in that slot. The slot displacement, not the semantic
// name, is what the listing fixes; the name comes from the Ghidra record for
// the slot target.
//
//   slot +0x04  called on the PARENT, not on the receiver, with no stack
//               argument. 0x00432b50 in BOTH vtable images. Ghidra names that
//               address FUN_00432b50. Its own body reads and decrements the
//               dword at param+0x04 under LOCK/UNLOCK, so the slot is a
//               reference-count release; the -2 and the 0x3/param[5] branch in
//               that body are described in the mechanics notes, not asserted
//               here as a field layout of this class.
//   slot +0x48  called on the RECEIVER with no stack argument. This is the
//               polymorphic heart of the body and the two vtable images
//               DISAGREE: 0x006a2a80 in vtable:0x01408820 (Ghidra name
//               App::PropertyList::Clear) and 0x006a2b20 in vtable:0x01408870
//               (Ghidra name App::DirectPropertyList::Clear). Both images were
//               read live and both slot targets were decompiled live.
//   slot +0x38  called on the RECEIVER with one pushed dword. 0x006a1510 in
//               BOTH vtable images. Ghidra name for that address:
//               App::PropertyList::AddAllPropertiesFrom, confirmed by a live
//               decompilation of 0x006a1510.

using ReleaseSlot04 = void(PKG_APP_PROPLIST_COPYALL_WAVE16_THISCALL*)(
    OpaquePropertyList *);
using ClearSlot48 = void(PKG_APP_PROPLIST_COPYALL_WAVE16_THISCALL*)(
    OpaquePropertyList *);
using AddAllPropertiesFromSlot38 = void(
    PKG_APP_PROPLIST_COPYALL_WAVE16_THISCALL *)(OpaquePropertyList *,
                                               OpaquePropertyList *);

struct alignas(4) OpaquePropertyListVtable {
  // 0x00. Ghidra record for 0x006a14d0 itself calls the receiver's first word
  // a vtable pointer, and the body reads it three times. The image value is
  // 0x00432be0 in both vtables.
  void *slot_00;
  // 0x04. 0x00432b50 in both images. Dispatched on the parent only.
  ReleaseSlot04 release_04;
  // 0x08, 0x0c, 0x10, 0x14. 0x006a1c80 / 0x006abe20 / 0x00432940 / 0x006a2e20
  // in vtable:0x01408820 and 0x006a1d60 / 0x006abe20 / 0x00432940 / 0x006a30c0
  // in vtable:0x01408870. Not dispatched by this body; opaque here.
  void *slot_08;
  void *slot_0c;
  void *slot_10;
  void *slot_14;
  // 0x18, 0x1c. 0x006a2ef0 in both images. Not dispatched by this body.
  void *slot_18;
  void *slot_1c;
  // 0x20, 0x24, 0x28. 0x006a1de0 / 0x006a2530 / 0x006a24d0 in
  // vtable:0x01408820 and 0x006a1e50 / 0x006a28c0 / 0x006a2800 in
  // vtable:0x01408870. Not dispatched by this body.
  void *slot_20;
  void *slot_24;
  void *slot_28;
  // 0x2c, 0x30. 0x006a2a40 / 0x006a2f10 in vtable:0x01408820 and 0x006a2ad0 /
  // 0x006a1600 in vtable:0x01408870. 0x30 is the slot pkg-app-proplist-wave13
  // reconstructed (App::PropertyList::AddPropertiesFrom) and 0x006a1510
  // dispatches to it; not dispatched by this body itself.
  void *slot_2c;
  void *slot_30;
  // 0x34. THIS BODY. The image value is 0x006a14d0 in BOTH vtables, which is
  // the machine fact that establishes the target as one function shared by two
  // classes rather than two same-named functions.
  void *slot_34_copy_all_properties_from;
  // 0x38. 0x006a1510 in both images. Dispatched by this body.
  AddAllPropertiesFromSlot38 add_all_properties_from_038;
  // 0x3c, 0x40, 0x44. 0x006a2f60 / 0x006a1540 / 0x006a3080 in
  // vtable:0x01408820 and 0x006a3170 / 0x006a1640 / 0x006a3180 in
  // vtable:0x01408870. Not dispatched by this body.
  void *slot_3c;
  void *slot_40;
  void *slot_44;
  // 0x48. THE OVERRIDDEN SLOT. 0x006a2a80 in vtable:0x01408820 and 0x006a2b20
  // in vtable:0x01408870. Dispatched by this body.
  ClearSlot48 clear_048;
};

// --- receiver ------------------------------------------------------------- //
//
// Displacement ledger, each row naming the record that observed it:
//
//   0x00  vtable word. THIS BODY: read at 0x006a14f1, 0x006a14fa (and at
//         0x006a14ea through the parent, not through the receiver).
//   0x04  read and written by the slot +0x04 target 0x00432b50, whose own body
//         does param_1+1 under LOCK. NOT observed by this body.
//   0x18  read by the slot +0x48 targets 0x006a2a80 (0x006a2a85) and 0x006a2b20
//         (0x006a2b34) and by slot +0x30 target 0x006a2f10 (reconstructed in
//         pkg-app-proplist-wave13). NOT observed by this body.
//   0x1c  same three records, as the range end.
//   0x30  THIS BODY: read at 0x006a14dc and written with zero at 0x006a14e3.
//         Ghidra names this word mpParent, which is an SDK-structure name from
//         the imported SporeGhidra_march2017 symbols, not an RTTI fact.
//   0x34  incremented by slot +0x48 target 0x006a2a80 (0x006a2ac6) and read by
//         slot +0x38 target 0x006a1510's sibling slot +0x30. NOT observed by
//         this body.
//   0x38  read by slot +0x48 target 0x006a2b20 at 0x006a2b24.
//   0x3c  read by slot +0x48 target 0x006a2b20 at 0x006a2b27.

struct alignas(4) OpaquePropertyList {
  // 0x00 -- vtable word, observed by this body at 0x006a14f1 and 0x006a14fa.
  OpaquePropertyListVtable *vtable;
  // 0x04 -- opaque to this body; the slot +0x04 target reads it. Ghidra's
  // imported structure calls it a reference count.
  std::uint32_t opaque_004;
  // 0x08..0x17 -- opaque. No record cited by this package reads these.
  std::uint8_t opaque_008[0x10];
  // 0x18, 0x1c -- property range begin/end, established by the slot +0x48 and
  // slot +0x30 targets, NOT by this body. Left opaque here so that nothing in
  // this package reads them.
  std::uint32_t opaque_018;
  std::uint32_t opaque_01c;
  // 0x20..0x2f -- opaque.
  std::uint8_t opaque_020[0x10];
  // 0x30 -- the parent word. This body's only field access. Read at
  // 0x006a14dc, zeroed at 0x006a14e3, and dispatched through at 0x006a14ea.
  OpaquePropertyList *parent_030;
  // 0x34..0x3c -- opaque to this body (see the ledger above).
  std::uint8_t opaque_034[0x0c];
};

static_assert(offsetof(OpaquePropertyList, vtable) == 0x00,
              "vtable word must sit at displacement 0x00");
static_assert(offsetof(OpaquePropertyList, opaque_004) == 0x04,
              "opaque_004 must sit at displacement 0x04");
static_assert(offsetof(OpaquePropertyList, opaque_018) == 0x18,
              "opaque_018 must sit at displacement 0x18");
static_assert(offsetof(OpaquePropertyList, opaque_01c) == 0x1c,
              "opaque_01c must sit at displacement 0x1c");
static_assert(offsetof(OpaquePropertyList, parent_030) == 0x30,
              "parent_030 must sit at displacement 0x30, the only field "
              "displacement this body addresses");
static_assert(sizeof(OpaquePropertyList) == 0x40,
              "the declared receiver must end after displacement 0x3c");

static_assert(offsetof(OpaquePropertyListVtable, release_04) == 0x04,
              "the release slot is read at [EAX + 0x4] by 0x006a14ec");
static_assert(offsetof(OpaquePropertyListVtable, slot_30) == 0x30,
              "slot +0x30 is the AddPropertiesFrom slot");
static_assert(offsetof(OpaquePropertyListVtable,
                       slot_34_copy_all_properties_from) == 0x34,
              "this body occupies vtable slot +0x34 in both vtable images");
static_assert(offsetof(OpaquePropertyListVtable,
                       add_all_properties_from_038) == 0x38,
              "the AddAllPropertiesFrom slot is read at [EAX + 0x38] by "
              "0x006a14fc");
static_assert(offsetof(OpaquePropertyListVtable, clear_048) == 0x48,
              "the Clear slot is read at [EAX + 0x48] by 0x006a14f3");
static_assert(sizeof(OpaquePropertyListVtable) == 0x4c,
              "the vtable image must be exactly 0x4c bytes wide");

// --- accessors, one per displacement this body actually uses -------------- //

// 0x006a14f1 and 0x006a14fa each read the receiver's first word. They are two
// separate reads, and the reconstruction preserves that: the slot +0x38 target
// is fetched from the vtable as it stands AFTER the slot +0x48 call has run.
inline OpaquePropertyListVtable *property_list_vtable_of(
    const OpaquePropertyList *list) {
  return list->vtable;
}

// 0x006a14dc -- the parent word, read once.
inline OpaquePropertyList *property_list_parent(
    const OpaquePropertyList *list) {
  return list->parent_030;
}

// 0x006a14e3 -- the same word written with zero, BEFORE the release call.
inline void property_list_detach_parent(OpaquePropertyList *list) {
  list->parent_030 = static_cast<OpaquePropertyList *>(nullptr);
}

extern "C" {

// The target itself, machine ABI only: receiver in ECX (aliased into ESI at
// 0x006a14d6), one ordinary stack dword at entry_ESP+0x4 read at 0x006a14d2 as
// [ESP + 0xc] after the two register pushes, callee-cleaned by RET 0x4 at
// 0x006a1506. Defined in all_copy_from_properties_006a14d0.cpp.
void PKG_APP_PROPLIST_COPYALL_WAVE16_THISCALL all_copy_from_properties_006a14d0(
    OpaquePropertyList *receiver, OpaquePropertyList *other);

} // extern "C"

}  // namespace pkg_app_proplist_copyall_wave16
}  // namespace reconstruction
}  // namespace openspore

#if !defined(_MSC_VER)
#pragma GCC diagnostic pop
#endif

#undef PKG_APP_PROPLIST_COPYALL_WAVE16_THISCALL
