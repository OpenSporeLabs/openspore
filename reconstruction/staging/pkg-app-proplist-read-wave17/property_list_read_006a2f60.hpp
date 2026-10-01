#pragma once

// Reconstruction of App::PropertyList::Read @ 0x006a2f60
// (DirectPropertyList member; vtable 0x01408820).
//
// Receiver layout is inherited verbatim from the sibling packages that already
// reconstructed this exact class from the same vtable:
//   reconstruction/staging/wave6-resources/property_list_access.hpp
//   reconstruction/metadata/wave6-resources/006a2470.json
// and is independently re-confirmed here by 0x006866f0, which lays a
// PropertyList out on the stack as {vftable, mnRefCount, mNameKey, ...} and
// heap-allocates it with FUN_00f473a0(0x38, ...) -- 0x38 == 56 bytes.

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "OpenSpore x86-32 reconstruction: 0x006a2f60 requires a 32-bit target"
#endif

namespace openspore::reconstruction::pkg_app_proplist_read_wave17 {

// ---------------------------------------------------------------------------
// Receiver layout (DirectPropertyList / App::PropertyList, 0x38 bytes)
// ---------------------------------------------------------------------------

// Receiver vtable, rooted at 0x01408820.  Only the slots this package actually
// observes are modelled; the class has more, and their extent is not claimed.
//   index 1 (+0x04) is a release entry point, invoked as
//   (**(code **)(*ptr + 4))() at 0x006a2fc8-0x006a2fcb.
struct PropertyListVtable {
  void* slot_00;
  void* release;  // +0x04, index 1
};

// PropertyMapEntry stride is 0x18, measured at 0x006a2ff9-0x006a3005
// (SUB ECX,[ESI+4] / SUB ECX,[ESI] / IMUL 0x2AAAAAAB / SAR 2) and again at
// 0x006a154d-0x006a1557 in App::PropertyList::Write.  The divisor is 0x18.
inline constexpr std::uint32_t kPropertyMapEntryStride = 0x18;

// Property occupies 0x14 bytes at entry+0x04, so 0x04 + 0x14 == 0x18.
// Offsets inside Property are re-derived from the per-record value reader
// 0x00694440, which is called with (entry + 0x04) as its second argument and
// touches param2+0x10 (ushort flags, masks 0x30 / 0x40 / 0xfff2) and
// param2+0x12 (ushort ObjectTYPE tag).  Those match the wave6-resources
// Property shape exactly.
struct Property {
  std::uint8_t opaque_prefix[0x10];  // 0x00..0x0f
  std::uint8_t flags;                // 0x10 (low 16 bits masked 0x30/0x40)
  std::uint8_t opaque_0x11;          // 0x11
  std::uint16_t type;                // 0x12 ObjectTYPE discriminant
};

struct PropertyMapEntry {
  std::uint32_t key;     // 0x00, one big-endian 32-bit word (see 0x006a15a7)
  Property property;     // 0x04
};

// std::vector-like record store.  0x006a2b80 reads entries_begin at +0x00 and
// entries_end at +0x04 and divides the byte span by 0x18, so this is the same
// object that PropertyList::HasProperty (0x006a2470) binary-searches.
struct PropertyMap {
  PropertyMapEntry* entries_begin;  // +0x18 on the receiver
  PropertyMapEntry* entries_end;    // +0x1c on the receiver
  std::uint8_t opaque_08_13[0x0c];
  std::uint8_t lookup_mode;  // +0x2c on the receiver
  std::uint8_t opaque_0d_0f[3];
};

struct DirectPropertyList {
  PropertyListVtable* vftable;  // 0x00
  std::uint32_t ref_count;      // 0x04
  std::uint8_t name_key[0x0c];  // 0x08 ResourceKey (typeID/groupID/instanceID)
  std::uint8_t final_release[4];// 0x14
  PropertyMap properties;       // 0x18
  DirectPropertyList* parent;   // 0x30
  std::uint32_t operations;     // 0x34
};

static_assert(sizeof(Property) == 0x14, "Property extent");
static_assert(offsetof(Property, flags) == 0x10, "Property flags offset");
static_assert(offsetof(Property, type) == 0x12, "Property type offset");
static_assert(sizeof(PropertyMapEntry) == 0x18, "entry stride");
static_assert(offsetof(PropertyMapEntry, property) == 0x04,
              "entry value offset");
static_assert(sizeof(PropertyMap) == 0x18, "map extent");
static_assert(sizeof(DirectPropertyList) == 0x38, "receiver extent");
static_assert(offsetof(DirectPropertyList, properties) == 0x18,
              "receiver map offset");
static_assert(offsetof(DirectPropertyList, parent) == 0x30,
              "receiver parent offset");

// ---------------------------------------------------------------------------
// Opaque runtime types
// ---------------------------------------------------------------------------

// COM-style stream.  0x0093a780 reaches slots +0x10 and +0x14 (both called
// with no arguments, +0x14 must return 0) and then slot +0x30 with
// (buffer, byte_count), which must return the full byte_count.
struct IStream {
  void* slot_00;
  void* slot_04;
  void* slot_08;
  void* slot_0c;
  void* lock;  // +0x10, index 4, invoked with no arguments
  std::uint32_t (*gate)();  // +0x14, index 5, must return 0
  void* slot_18;
  void* slot_1c;
  void* slot_20;
  void* slot_24;
  void* slot_28;
  // +0x30, index 12: (buffer, byte_count) -> bytes actually transferred.
  std::uint32_t (*read)(void* buffer, std::uint32_t byte_count);
};

// Global service pointer DAT_015fd8a8, returned by the trivial getter 0x0067de30.
// It is zero in the static image and filled at runtime, so its concrete type is
// NOT statically recoverable.  Only the used vtable slot is claimed: +0x2c.
// The receiver's slot +0x04 must NOT be assumed to mean the same thing here --
// the two vtables are unrelated and only the receiver's release slot was
// observed being called.
struct PropertyListService {
  void* slot_00;
  void* slot_04;
  void* slot_08;
  void* slot_0c;
  void* slot_10;
  void* slot_14;
  void* slot_18;
  void* slot_1c;
  void* slot_20;
  void* slot_24;
  void* slot_28;
  // +0x2c, index 11.  Called at 0x006a2fe3 as
  // (block[0], block[2], &receiver->parent).
  void (*resolve)(std::uint32_t, std::uint32_t, DirectPropertyList**);
};

// ---------------------------------------------------------------------------
// Helper ports.
//
// The four helpers 0x0093a780 / 0x0093a700 / 0x00694440 / 0x006a2b80 are
// reached by direct CALL rel32 in the original, so the staging model routes
// them through a bindable port table instead of re-declaring their bodies.
// ---------------------------------------------------------------------------

struct HelperPorts {
  // 0x0093a780(stream, dword_buffer, dword_count, swap_flag) -> bool in AL.
  // Observed: reads dword_count*4 bytes via IStream slot +0x30, requires the
  // full count, and (when swap_flag != 1) byte-swaps every dword, i.e. the
  // on-disk word order is big-endian.
  bool (*read_dwords_be)(IStream*, std::uint32_t* buffer, std::uint32_t count,
                         std::uint32_t swap_flag);

  // 0x0093a700(stream, word_buffer, element_count, flags) -> bool in AL.
  // Called with element_count == 1 on a 16-bit destination.  The 16-bit
  // sibling's internals are not asserted here.
  bool (*read_words_be)(IStream*, std::uint16_t* buffer,
                        std::uint32_t element_count, std::uint32_t flags);

  // 0x00694440(stream, entry + 0x04, flags) -> bool in AL.
  // Per-record value reader.  Its ObjectTYPE switch and array-dimension
  // handling are internal to that function and are not re-modelled here.
  bool (*read_property_value)(IStream*, Property*, std::uint32_t flags);

  // 0x006a2b80(&receiver->properties, n) -- exact-count resize.
  void (*resize_map)(PropertyMap*, std::uint32_t count);

  // 0x0067de30() -- the runtime-filled service singleton.
  PropertyListService* (*get_service)();
};

// ---------------------------------------------------------------------------
// Entry point
// ---------------------------------------------------------------------------

#if defined(_MSC_VER)
#define OPENSPORE_THISCALL __thiscall
#else
#define OPENSPORE_THISCALL __attribute__((thiscall))
#endif

extern HelperPorts g_helpers;

// App::PropertyList::Read @ 0x006a2f60.
// __thiscall: ECX = this, one stack argument, RET 0x4.
// Returns the accumulated success flag in AL (0x006a3064 MOV AL,BL).
bool OPENSPORE_THISCALL read_006a2f60(DirectPropertyList* list,
                                      IStream* pInputStream);

// OPENSPORE_THISCALL stays defined so the .cpp translation unit can redeclare
// the entry point with the same convention.

}  // namespace openspore::reconstruction::pkg_app_proplist_read_wave17
