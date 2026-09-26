#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-ui-safe-wave10 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_UI_SAFE_CDECL __cdecl
#define PKG_UI_SAFE_THISCALL __thiscall
#else
#define PKG_UI_SAFE_CDECL __attribute__((cdecl))
#define PKG_UI_SAFE_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_ui_safe_wave10 {

using TargetWord = std::uint32_t;

inline constexpr TargetWord kDerivedPrimaryVtable = 0x013fe728u;
inline constexpr TargetWord kDerivedSecondaryVtable = 0x013fe718u;
inline constexpr TargetWord kBaseSecondaryVtable = 0x013ec458u;
inline constexpr TargetWord kBasePrimaryVtable = 0x013eb938u;

struct OpaqueService24 {
  void* vtable_00 = nullptr;
  TargetWord field_04 = 0;
  TargetWord field_08 = 0;
  TargetWord field_0c = 0;
  TargetWord field_10 = 0;
  void* slot_14 = nullptr;
};

struct OpaqueSlot;

using SlotReleasePort = void(PKG_UI_SAFE_THISCALL*)(OpaqueSlot*);
using ServiceDestroyPort = void(PKG_UI_SAFE_THISCALL*)(OpaqueService24*);
using DeallocatePort = void(PKG_UI_SAFE_CDECL*)(void*);

struct OpaqueSlotVtablePort {
  void* slot_00 = nullptr;
  SlotReleasePort release_04 = nullptr;
};

struct OpaqueSlot {
  OpaqueSlotVtablePort* vtable = nullptr;
};

struct OpaqueImageArchive {
  void* vtable_00 = nullptr;
  void* vtable_04 = nullptr;
  TargetWord refcount_08 = 0;
  std::uint8_t opaque_0c[8]{};
  OpaqueService24 service_14{};
  OpaqueService24 service_2c{};
  std::uint8_t byte_44 = 0;
  std::uint8_t byte_45 = 0;
  std::uint8_t opaque_46[2]{};
  TargetWord field_48 = 0;
  std::uint8_t opaque_4c[0x18]{};
  OpaqueSlot* slot_64 = nullptr;
  OpaqueSlot* slot_68 = nullptr;
};

struct ImageArchivePorts {
  ServiceDestroyPort service_destroy;
  DeallocatePort deallocate;
};

static_assert(sizeof(void*) == 4, "x86-32 pointers are four bytes");
static_assert(sizeof(TargetWord) == 4, "target words are four bytes");

static_assert(sizeof(OpaqueService24) == 0x18, "service subobject size");
static_assert(offsetof(OpaqueService24, vtable_00) == 0x00,
              "service vtable at +0x00");
static_assert(offsetof(OpaqueService24, field_04) == 0x04,
              "service field at +0x04");
static_assert(offsetof(OpaqueService24, field_08) == 0x08,
              "service field at +0x08");
static_assert(offsetof(OpaqueService24, field_0c) == 0x0c,
              "service field at +0x0c");
static_assert(offsetof(OpaqueService24, field_10) == 0x10,
              "service field at +0x10");
static_assert(offsetof(OpaqueService24, slot_14) == 0x14,
              "service slot at +0x14");

static_assert(sizeof(OpaqueSlotVtablePort) == 0x08, "slot vtable size");
static_assert(offsetof(OpaqueSlotVtablePort, slot_00) == 0x00,
              "slot vtable head at +0x00");
static_assert(offsetof(OpaqueSlotVtablePort, release_04) == 0x04,
              "release port at slot vtable +0x04");
static_assert(sizeof(OpaqueSlot) == 0x04, "slot head is one pointer");

static_assert(sizeof(OpaqueImageArchive) == 0x6c, "image archive size");
static_assert(offsetof(OpaqueImageArchive, vtable_00) == 0x00,
              "image archive primary vtable at +0x00");
static_assert(offsetof(OpaqueImageArchive, vtable_04) == 0x04,
              "image archive secondary vtable at +0x04");
static_assert(offsetof(OpaqueImageArchive, refcount_08) == 0x08,
              "image archive refcount at +0x08");
static_assert(offsetof(OpaqueImageArchive, opaque_0c) == 0x0c,
              "image archive opaque body at +0x0c");
static_assert(offsetof(OpaqueImageArchive, service_14) == 0x14,
              "image archive first service at +0x14");
static_assert(offsetof(OpaqueImageArchive, service_2c) == 0x2c,
              "image archive second service at +0x2c");
static_assert(offsetof(OpaqueImageArchive, byte_44) == 0x44,
              "image archive byte at +0x44");
static_assert(offsetof(OpaqueImageArchive, byte_45) == 0x45,
              "image archive byte at +0x45");
static_assert(offsetof(OpaqueImageArchive, opaque_46) == 0x46,
              "image archive opaque body at +0x46");
static_assert(offsetof(OpaqueImageArchive, field_48) == 0x48,
              "image archive field at +0x48");
static_assert(offsetof(OpaqueImageArchive, opaque_4c) == 0x4c,
              "image archive opaque body at +0x4c");
static_assert(offsetof(OpaqueImageArchive, slot_64) == 0x64,
              "image archive early handle at +0x64");
static_assert(offsetof(OpaqueImageArchive, slot_68) == 0x68,
              "image archive late handle at +0x68");

ImageArchivePorts& image_archive_ports();
void image_archive_set_ports(const ImageArchivePorts& ports);
void image_archive_reset_ports();

OpaqueImageArchive* PKG_UI_SAFE_THISCALL
image_archive_scalar_deleting_destructor_00635700(OpaqueImageArchive* archive,
                                                  TargetWord deleting);

}

#undef PKG_UI_SAFE_CDECL
#undef PKG_UI_SAFE_THISCALL
