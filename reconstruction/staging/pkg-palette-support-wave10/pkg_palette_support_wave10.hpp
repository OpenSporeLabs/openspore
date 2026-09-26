#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-PALETTE-SUPPORT-WAVE10 requires an x86-32 target"
#endif

static_assert(sizeof(void *) == 4,
              "PKG-PALETTE-SUPPORT-WAVE10 target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4,
              "PKG-PALETTE-SUPPORT-WAVE10 target words are 32-bit");

#if defined(_MSC_VER)
#define PKG_PALETTE_SUPPORT_THISCALL __thiscall
#define PKG_PALETTE_SUPPORT_FASTCALL __fastcall
#define PKG_PALETTE_SUPPORT_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_PALETTE_SUPPORT_THISCALL __attribute__((thiscall))
#define PKG_PALETTE_SUPPORT_FASTCALL __attribute__((fastcall))
#define PKG_PALETTE_SUPPORT_CDECL __attribute__((cdecl))
#else
#error "PKG-PALETTE-SUPPORT-WAVE10 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_palette_support_wave10 {

struct alignas(4) OpaqueResourceEntry {
  std::uint32_t field00;
  std::uint32_t field04;
  std::uint32_t field08;
};

struct alignas(4) OpaqueResourceKey {
  std::uint32_t field00;
  std::uint32_t field04;
  std::uint32_t field08;
  std::uint8_t opaque0c[6];
  std::uint16_t field12;
};

struct alignas(4) OpaqueSlotVector {
  std::uint32_t *begin;
  std::uint32_t *end;
};

struct alignas(4) OpaqueVectorHost {
  void *vtable;
  std::uint8_t opaque04[8];
  OpaqueSlotVector field0c;
  std::uint8_t opaque14[0x48];
  std::uint32_t field5c;
  std::uint8_t opaque60[4];
  std::uint32_t field64;
  std::uint32_t field68;
  std::uint32_t field6c;
  OpaqueSlotVector field70;
};

struct alignas(4) OpaquePageA {
  OpaqueVectorHost host;
  std::uint8_t opaque78[0x0c];
};

struct alignas(4) OpaquePageB {
  OpaqueVectorHost host;
  std::uint8_t opaque78[0x18];
};

struct alignas(4) OpaqueEntryB {
  OpaqueVectorHost host;
  std::uint8_t opaque78[8];
};

struct alignas(4) OpaqueLeaf {
  void *vtable;
  std::uint8_t opaque04[8];
  OpaqueResourceEntry key;
  std::uint8_t opaque18[8];
};

struct alignas(4) OpaqueEntryA {
  void *vtable;
  std::uint8_t opaque04[8];
  OpaqueResourceEntry key;
  std::uint32_t field18;
  std::uint32_t field1c;
  std::uint32_t field20;
  std::uint32_t field24;
  std::uint8_t opaque28[0x20];
  std::uint32_t field48;
  std::uint8_t opaque4c[4];
};

struct alignas(4) OpaqueSupport {
  void *vtable;
  std::uint32_t field04;
  void *secondary;
  std::uint32_t field0c;
  std::uint32_t field10;
  std::uint32_t field14;
  std::uint8_t opaque18[8];
  std::uint32_t field20;
  std::uint32_t field24;
  std::uint32_t field28;
  std::uint32_t field2c;
  std::uint32_t field30;
  std::uint32_t field34;
  std::uint32_t field38;
  std::uint32_t field3c;
};

struct alignas(4) OpaqueFilterContext {
  std::uint32_t field00;
  std::uint32_t field04;
  std::uint32_t field08;
};

struct alignas(4) OpaqueFilterSlot {
  std::uint32_t field00;
  std::uint32_t field04;
  std::uint32_t field08;
  std::uint32_t field0c;
  std::uint32_t field10;
};

struct alignas(4) OpaqueFilterList {
  OpaqueResourceEntry *field00;
  OpaqueResourceEntry *field04;
  std::uint32_t field08;
  std::uint32_t field0c;
};

struct alignas(4) OpaqueFilterFrame {
  OpaqueFilterList list;
  std::uint32_t field10;
  std::uint32_t field14;
  OpaqueFilterSlot slot;
};

struct alignas(4) OpaqueNode;
struct alignas(4) OpaqueService;
struct alignas(4) OpaqueRegistry;
struct alignas(4) OpaqueProperty;

using NodeRetain04 = void(PKG_PALETTE_SUPPORT_THISCALL *)(OpaqueNode *);
using NodeRelease08 = void(PKG_PALETTE_SUPPORT_THISCALL *)(OpaqueNode *);

struct alignas(4) OpaqueNodeVtable {
  std::uintptr_t slots00;
  NodeRetain04 retain04;
  NodeRelease08 release08;
};

struct alignas(4) OpaqueNode {
  OpaqueNodeVtable *vtable;
};

using ServiceResolve2c = bool(PKG_PALETTE_SUPPORT_THISCALL *)(
    OpaqueService *, std::uint32_t, std::uint32_t, OpaqueProperty **);

struct alignas(4) OpaqueServiceVtable {
  std::uintptr_t slots00[11];
  ServiceResolve2c resolve2c;
};

struct alignas(4) OpaqueService {
  OpaqueServiceVtable *vtable;
};

using PropertyRelease04 =
    void(PKG_PALETTE_SUPPORT_THISCALL *)(OpaqueProperty *);
using PropertyQuery24 = bool(PKG_PALETTE_SUPPORT_THISCALL *)(
    OpaqueProperty *, OpaqueResourceKey *, std::uint32_t);

struct alignas(4) OpaquePropertyVtable {
  std::uintptr_t slots00;
  PropertyRelease04 release04;
  std::uintptr_t slots08[7];
  PropertyQuery24 query24;
};

struct alignas(4) OpaqueProperty {
  OpaquePropertyVtable *vtable;
};

using RegistryFilter38 = void(PKG_PALETTE_SUPPORT_THISCALL *)(
    OpaqueRegistry *, OpaqueFilterContext *, OpaqueFilterFrame *,
    std::uint32_t);

struct alignas(4) OpaqueRegistryVtable {
  std::uintptr_t slots00[14];
  RegistryFilter38 filter38;
};

struct alignas(4) OpaqueRegistry {
  OpaqueRegistryVtable *vtable;
};

static_assert(sizeof(OpaqueResourceEntry) == 0x0c,
              "packed resource entry is three words");
static_assert(offsetof(OpaqueResourceEntry, field04) == 0x04,
              "packed resource entry middle word offset");
static_assert(offsetof(OpaqueResourceKey, field08) == 0x08,
              "descriptor group word offset");
static_assert(offsetof(OpaqueResourceKey, field12) == 0x12,
              "descriptor half word offset");
static_assert(sizeof(OpaqueResourceKey) == 0x14, "descriptor size");
static_assert(sizeof(OpaqueSlotVector) == 8, "slot vector is a pointer pair");
static_assert(offsetof(OpaqueVectorHost, field0c) == 0x0c,
              "host leading slot vector offset");
static_assert(offsetof(OpaqueVectorHost, field5c) == 0x5c,
              "host element state offset");
static_assert(offsetof(OpaqueVectorHost, field64) == 0x64,
              "host entry instance offset");
static_assert(offsetof(OpaqueVectorHost, field68) == 0x68,
              "host entry type offset");
static_assert(offsetof(OpaqueVectorHost, field6c) == 0x6c,
              "host entry group offset");
static_assert(offsetof(OpaqueVectorHost, field70) == 0x70,
              "host trailing slot vector offset");
static_assert(sizeof(OpaqueVectorHost) == 0x78, "host size");
static_assert(sizeof(OpaquePageA) == 0x84, "page A allocation size");
static_assert(sizeof(OpaquePageB) == 0x90, "page B allocation size");
static_assert(offsetof(OpaquePageA, host) == 0x00, "page A host offset");
static_assert(offsetof(OpaquePageB, host) == 0x00, "page B host offset");
static_assert(offsetof(OpaqueEntryB, host) == 0x00, "entry B host offset");
static_assert(offsetof(OpaqueLeaf, key) == 0x0c, "leaf key offset");
static_assert(offsetof(OpaqueEntryA, key) == 0x0c, "entry A key offset");
static_assert(offsetof(OpaqueEntryA, field20) == 0x20,
              "entry A override offset");
static_assert(offsetof(OpaqueEntryA, field48) == 0x48, "entry A state offset");
static_assert(sizeof(OpaqueEntryA) == 0x50, "entry A size");
static_assert(offsetof(OpaqueSupport, field20) == 0x20,
              "support instance offset");
static_assert(offsetof(OpaqueSupport, field24) == 0x24,
              "support channel offset");
static_assert(offsetof(OpaqueSupport, field28) == 0x28,
              "support key word zero offset");
static_assert(offsetof(OpaqueSupport, field2c) == 0x2c,
              "support key word one offset");
static_assert(offsetof(OpaqueSupport, field30) == 0x30,
              "support key word two offset");
static_assert(offsetof(OpaqueSupport, field34) == 0x34,
              "support key word three offset");
static_assert(offsetof(OpaqueSupport, field38) == 0x38, "support flag offset");
static_assert(offsetof(OpaqueSupport, field3c) == 0x3c,
              "support back link offset");
static_assert(sizeof(OpaqueSupport) == 0x40, "support size");
static_assert(sizeof(OpaqueFilterSlot) == 0x14, "filter slot size");
static_assert(sizeof(OpaqueFilterList) == 0x10, "filter list size");
static_assert(offsetof(OpaqueFilterFrame, field10) == 0x10,
              "filter block token offset");
static_assert(offsetof(OpaqueFilterFrame, slot) == 0x18,
              "filter slot offset from the list base");
static_assert(sizeof(OpaqueFilterFrame) == 0x2c, "filter frame size");
static_assert(sizeof(decltype(OpaqueServiceVtable::resolve2c)) == 4,
              "service resolve slot is a single 32-bit pointer");
static_assert(sizeof(decltype(OpaquePropertyVtable::query24)) == 4,
              "property query slot is a single 32-bit pointer");
static_assert(sizeof(decltype(OpaqueRegistryVtable::filter38)) == 4,
              "registry filter slot is a single 32-bit pointer");
static_assert(offsetof(OpaqueServiceVtable, resolve2c) == 0x2c,
              "service resolve slot index");
static_assert(offsetof(OpaquePropertyVtable, query24) == 0x24,
              "property query slot index");
static_assert(offsetof(OpaqueRegistryVtable, filter38) == 0x38,
              "registry filter slot index");

extern void *g_table_015fd918;

extern "C" {

std::uint32_t PKG_PALETTE_SUPPORT_THISCALL unresolved_005c5cc0(OpaqueSupport *,
                                                               OpaquePageA *,
                                                               OpaquePageB *);

void PKG_PALETTE_SUPPORT_THISCALL unresolved_005c6010(OpaqueSupport *,
                                                      OpaqueResourceEntry *);

bool PKG_PALETTE_SUPPORT_THISCALL unresolved_005c6340(
    OpaqueSupport *, OpaqueResourceKey *, std::uint32_t, std::uint32_t,
    std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t);

void *PKG_PALETTE_SUPPORT_THISCALL unresolved_005c7f00(OpaqueVectorHost *,
                                                       std::uint32_t);

OpaqueEntryB *PKG_PALETTE_SUPPORT_THISCALL
unresolved_005c1ce0(OpaqueVectorHost *, std::uint32_t);

bool PKG_PALETTE_SUPPORT_THISCALL unresolved_005c6810(
    OpaqueEntryA *, const OpaqueResourceEntry *, std::int32_t, std::uint32_t);

std::int32_t PKG_PALETTE_SUPPORT_THISCALL unresolved_005c5c50(OpaqueSupport *,
                                                              OpaquePageA *,
                                                              std::uint32_t *);

OpaqueEntryB *PKG_PALETTE_SUPPORT_THISCALL
unresolved_005c5df0(OpaqueVectorHost *, std::uint32_t);

void PKG_PALETTE_SUPPORT_THISCALL unresolved_005c5f00(OpaqueProperty *,
                                                      OpaquePageB *);

bool PKG_PALETTE_SUPPORT_THISCALL unresolved_005c1d40(OpaquePageB *,
                                                      OpaquePageB *);

void PKG_PALETTE_SUPPORT_THISCALL unresolved_005c22b0(OpaquePageB *,
                                                      OpaquePageB *);

void PKG_PALETTE_SUPPORT_THISCALL unresolved_005c2390(OpaquePageB *,
                                                      OpaqueNode *);

bool PKG_PALETTE_SUPPORT_THISCALL
unresolved_005c8ad0(OpaquePageA *, OpaqueResourceEntry *, std::uint32_t,
                    std::uint32_t, std::uint32_t, std::uint32_t);

OpaquePageA *PKG_PALETTE_SUPPORT_THISCALL unresolved_005c7f50(OpaquePageA *);

OpaquePageB *PKG_PALETTE_SUPPORT_THISCALL unresolved_005c2020(OpaquePageB *);

void PKG_PALETTE_SUPPORT_THISCALL
unresolved_005c1e20(OpaquePageB *, const OpaqueResourceEntry *, std::uint32_t);

OpaqueService *PKG_PALETTE_SUPPORT_CDECL unresolved_0067de30();

OpaqueRegistry *PKG_PALETTE_SUPPORT_CDECL unresolved_008de1a0();

void *PKG_PALETTE_SUPPORT_CDECL
unresolved_00f473a0(std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t,
                    std::uint32_t, std::uint32_t);

void PKG_PALETTE_SUPPORT_CDECL unresolved_00f47380(void *);

const std::uint32_t *PKG_PALETTE_SUPPORT_FASTCALL
unresolved_0041e990(const OpaqueResourceKey *);

bool PKG_PALETTE_SUPPORT_CDECL unresolved_006a0ae0(OpaqueProperty *,
                                                   std::uint32_t,
                                                   std::int32_t *,
                                                   OpaqueResourceEntry *);

bool PKG_PALETTE_SUPPORT_CDECL unresolved_006a1250(OpaqueProperty *,
                                                   std::uint32_t,
                                                   OpaqueResourceEntry *);

bool PKG_PALETTE_SUPPORT_CDECL unresolved_006a12e0(OpaqueProperty *,
                                                   std::uint32_t,
                                                   std::uint32_t *);

bool PKG_PALETTE_SUPPORT_CDECL unresolved_006a12a0(OpaqueProperty *,
                                                   std::uint32_t,
                                                   std::uint32_t *);
}

}
