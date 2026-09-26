#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-orchestrate-dogfood-006a1de0 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_006A1DE0_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_006A1DE0_CDECL __attribute__((cdecl))
#else
#error \
    "pkg-orchestrate-dogfood-006a1de0 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_006a1de0 {

using OpaqueWord = std::uint32_t;

struct OpaqueProperty;
struct alignas(4) OpaquePropertyEntry;

// Receiver of the entry point. 0x006a1de0 reads exactly four receiver
// offsets: +0x18, +0x1c, +0x2c and +0x30. The vtable word at +0x00 is not
// read by this body, but the object reached through +0x30 is dereferenced as
// [dword 0] then [dword 0 + 0x20], and the in-repo analogue
// reconstruction/staging/pkg-property-list-wave6 reads the same class word as
// `vtable`, so the leading word is modelled as the vtable pointer.
// The trailing extent 0x34 is a modeling bound, not a recovered size.
struct alignas(4) OpaquePropertyList;

// Live table read at 0x01408820 (128 bytes) from SporeApp.exe places
// 0x006a1de0 at displacement 0x20, index 8 counting from the table start.
// The word at displacement 0x1c is 0x006a2470, which Ghidra names
// App::PropertyList::HasProperty and which the analogue record
// reconstruction/metadata/wave6-resources/006a2470.json dispatches through
// the same +0x30 object with one pushed id word and a 4-byte callee cleanup.
using OpaquePropertyListHasProperty1c =
    bool(PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL*)(OpaquePropertyList*,
                                                     OpaqueWord);
using OpaquePropertyListGetPropertyAlt20 = bool(
    PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL*)(OpaquePropertyList*, OpaqueWord,
                                                OpaqueProperty**);

// Entry signature. ECX carries the receiver, ESP+0x04 carries the id word and
// ESP+0x08 carries the out pointer; all three return sites are `RET 0x8`, so
// the callee reclaims both stack words. The result is AL only: 0x1 on the hit
// path, the forwarded AL of the +0x20 virtual call on the parent path, and
// zero when there is no parent.
using OpaquePropertyListGetPropertyAltEntry = bool(
    PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL*)(OpaquePropertyList*, OpaqueWord,
                                                OpaqueProperty**);

// The only direct callee, 0x00612db0. Push order at 0x006a1def-0x006a1df5 is
// the key byte from +0x2c, the address of the caller's own id stack slot, the
// +0x1c word and the +0x18 word, so the callee signature is
// (entries_begin, entries_end, id pointer, lookup mode). Its own 33-instruction
// body reads only ESP+0x04, ESP+0x08 and ESP+0x10 of its own frame and returns
// with a plain RET, which fixes the convention as cdecl and proves the fourth
// pushed word is dead at the callee. It never writes through the id pointer;
// it only reads the key from it.
using OpaquePropertyListLowerBound00612db0 = OpaquePropertyEntry*(
    PKG_ORCHESTRATE_DOGFOOD_006A1DE0_CDECL*)(void*, void*, const OpaqueWord*,
                                             std::uint8_t);

struct alignas(4) OpaquePropertyListVtable {
  std::uintptr_t slot_words_00[7]{};
  OpaquePropertyListHasProperty1c operation_1c;
  OpaquePropertyListGetPropertyAlt20 operation_20;
};

// Sorted entry span element. The stride 0x18 is fixed by
// `LEA ECX,[EAX+0x18]` at 0x006a1e0a and by the 0x00612db0 index step. The
// dword at +0x00 is the key the body compares against with `CMP EDX,[EAX]` and
// the caller-side comparison inside 0x00612db0. The dword at +0x04 is only
// observed by address: the body forms node+4 and stores that address, not the
// value stored there, so the pointee type stays unresolved.
struct alignas(4) OpaquePropertyEntry {
  OpaqueWord key_00;
  OpaqueProperty* property_slot_04;
  std::uint8_t opaque_08[0x10]{};
};

struct alignas(4) OpaquePropertyList {
  OpaquePropertyListVtable* vtable;
  std::uint8_t opaque_04[0x14]{};
  OpaquePropertyEntry* entries_begin_18;
  OpaquePropertyEntry* entries_end_1c;
  std::uint8_t opaque_20[0x0c]{};
  std::uint8_t lookup_mode_2c;
  std::uint8_t opaque_2d[0x03]{};
  OpaquePropertyList* parent_30;
};

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueWord) == 4, "target words are 32-bit");
static_assert(sizeof(OpaquePropertyListLowerBound00612db0) == 4,
              "lower bound port width");
static_assert(sizeof(OpaquePropertyListGetPropertyAlt20) == 4,
              "virtual slot width");
static_assert(offsetof(OpaquePropertyListVtable, operation_1c) == 0x1c,
              "property list vtable slot offset");
static_assert(offsetof(OpaquePropertyListVtable, operation_20) == 0x20,
              "property list vtable slot offset");
static_assert(sizeof(OpaquePropertyListVtable) == 0x24,
              "property list vtable modeled window extent");
static_assert(sizeof(OpaquePropertyEntry) == 0x18,
              "property entry stride from the 0x00612db0 index step");
static_assert(offsetof(OpaquePropertyEntry, key_00) == 0x00,
              "property entry key offset");
static_assert(offsetof(OpaquePropertyEntry, property_slot_04) == 0x04,
              "property entry property word offset");
static_assert(offsetof(OpaquePropertyList, vtable) == 0x00,
              "property list vtable pointer offset");
static_assert(offsetof(OpaquePropertyList, entries_begin_18) == 0x18,
              "property list entries begin offset");
static_assert(offsetof(OpaquePropertyList, entries_end_1c) == 0x1c,
              "property list entries end offset");
static_assert(offsetof(OpaquePropertyList, lookup_mode_2c) == 0x2c,
              "property list lookup mode offset");
static_assert(offsetof(OpaquePropertyList, parent_30) == 0x30,
              "property list parent word offset");
static_assert(sizeof(OpaquePropertyList) == 0x34,
              "property list modeled prefix extent");
static_assert(
    std::is_same<
        OpaquePropertyListLowerBound00612db0,
        OpaquePropertyEntry*(
            PKG_ORCHESTRATE_DOGFOOD_006A1DE0_CDECL*)(void*, void*,
                                                     const OpaqueWord*,
                                                     std::uint8_t)>::value,
    "0x00612db0 keeps cdecl and takes the dead mode word as its fourth "
    "argument");
static_assert(std::is_same<OpaquePropertyListGetPropertyAltEntry,
                           OpaquePropertyListGetPropertyAlt20>::value,
              "the +0x20 dispatch shape equals the entry point shape");

struct GetPropertyAltPorts {
  OpaquePropertyListLowerBound00612db0 lower_bound_00612db0 = nullptr;
};

extern GetPropertyAltPorts g_dogfood_006a1de0_ports;

extern "C" bool PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL
property_list_get_property_alt_006a1de0(OpaquePropertyList* list,
                                        OpaqueWord property_id,
                                        OpaqueProperty** result);

}

#undef PKG_ORCHESTRATE_DOGFOOD_006A1DE0_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL
