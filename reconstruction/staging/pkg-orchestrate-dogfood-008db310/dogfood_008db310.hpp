#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-orchestrate-dogfood-008db310 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL __attribute__((cdecl))
#else
#error \
    "pkg-orchestrate-dogfood-008db310 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_008db310 {

using OpaqueWord = std::uint32_t;

struct alignas(4) OpaqueItemNode {
  std::uint8_t opaque_00_0b[0x0c]{};
  OpaqueWord record_begin_0c;
  OpaqueWord record_size_10;
  std::uint8_t opaque_14_1b[0x08]{};
  OpaqueItemNode* next_1c;
};

struct alignas(4) OpaqueWriteCarrier {
  std::uint8_t opaque_00_2b[0x2c]{};
  OpaqueItemNode* const* slots_2c;
  OpaqueWord end_slot_30;
  std::uint8_t opaque_34_4b[0x18]{};
};

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueWord) == 4, "target words are 32-bit");
static_assert(sizeof(OpaqueItemNode) == 0x20, "item node extent");
static_assert(offsetof(OpaqueItemNode, record_begin_0c) == 0x0c,
              "item node record begin offset");
static_assert(offsetof(OpaqueItemNode, record_size_10) == 0x10,
              "item node record size offset");
static_assert(offsetof(OpaqueItemNode, next_1c) == 0x1c,
              "item node chain offset");
static_assert(sizeof(OpaqueWriteCarrier) == 0x4c, "write carrier extent");
static_assert(offsetof(OpaqueWriteCarrier, slots_2c) == 0x2c,
              "write carrier slot array offset");
static_assert(offsetof(OpaqueWriteCarrier, end_slot_30) == 0x30,
              "write carrier end slot offset");

using DispatchSlot014368bc = bool(PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL*)(
    OpaqueWriteCarrier*, void*, OpaqueWord);

struct alignas(4) OpaquePorts {
  DispatchSlot014368bc dispatch_014368bc = nullptr;
};

static_assert(sizeof(DispatchSlot014368bc) == 4, "dispatch port width");
static_assert(sizeof(OpaquePorts) == 4, "port table extent");
static_assert(
    std::is_same<DispatchSlot014368bc,
                 bool(PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL*)(
                     OpaqueWriteCarrier*, void*, OpaqueWord)>::value,
    "dispatch entry takes the carrier and the two observed stack words");

extern OpaquePorts g_pf_index_write_008db310_ports;

extern "C" bool PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL
pf_index_write_bounds_008db310(OpaqueWriteCarrier* index, void* destination,
                               OpaqueWord destination_size);

}

#undef PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL
