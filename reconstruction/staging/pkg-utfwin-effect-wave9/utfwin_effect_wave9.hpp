#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "UTFWin effect wave 9 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_utfwin_effect_wave9 {

using Opaque = std::uint32_t;

#if defined(_MSC_VER)
#define PKG_W9_THISCALL __thiscall
#define PKG_W9_NAKED __declspec(naked)
#else
#define PKG_W9_THISCALL __attribute__((thiscall))
#define PKG_W9_NAKED __attribute__((naked))
#endif

struct alignas(4) OpaqueVtableA {
  std::array<Opaque, 0x0f> prefix;
  Opaque slot_3c;
};

struct alignas(4) OpaqueVtableB {
  std::array<Opaque, 0x03> prefix;
  Opaque slot_0c;
  Opaque slot_10;
  Opaque slot_14;
};

struct alignas(4) OpaqueVtableC {
  std::array<Opaque, 0x14> prefix;
  Opaque slot_50;
};

struct alignas(4) OpaqueVtableD {
  std::array<Opaque, 0x09> prefix;
  Opaque slot_24;
};

struct alignas(4) OpaqueVtableE {
  std::array<Opaque, 0x22> prefix;
  Opaque slot_88;
};

using MessageSlot = Opaque(PKG_W9_THISCALL*)(Opaque, Opaque);
using TokenSlot = Opaque(PKG_W9_THISCALL*)(Opaque, Opaque);
using ProxySlot = Opaque(PKG_W9_THISCALL*)(Opaque);
using ThreeArgumentSlot = Opaque(PKG_W9_THISCALL*)(Opaque, Opaque, Opaque,
                                                   Opaque);
using ImageSlot = Opaque(PKG_W9_THISCALL*)(Opaque, Opaque);

static_assert(sizeof(void*) == 4,
              "UTFWin effect wave 9 target pointers are 32-bit");
static_assert(sizeof(Opaque) == 4,
              "UTFWin effect wave 9 opaque words are 32-bit");
static_assert(offsetof(OpaqueVtableA, slot_3c) == 0x3c,
              "opaque vtable A slot offset");
static_assert(sizeof(OpaqueVtableA) == 0x40, "opaque vtable A extent");
static_assert(offsetof(OpaqueVtableB, slot_0c) == 0x0c,
              "opaque vtable B first slot offset");
static_assert(offsetof(OpaqueVtableB, slot_14) == 0x14,
              "opaque vtable B third slot offset");
static_assert(sizeof(OpaqueVtableB) == 0x18, "opaque vtable B extent");
static_assert(offsetof(OpaqueVtableC, slot_50) == 0x50,
              "opaque vtable C slot offset");
static_assert(sizeof(OpaqueVtableC) == 0x54, "opaque vtable C extent");
static_assert(offsetof(OpaqueVtableD, slot_24) == 0x24,
              "opaque vtable D slot offset");
static_assert(sizeof(OpaqueVtableD) == 0x28, "opaque vtable D extent");
static_assert(offsetof(OpaqueVtableE, slot_88) == 0x88,
              "opaque vtable E slot offset");
static_assert(sizeof(OpaqueVtableE) == 0x8c, "opaque vtable E extent");

extern "C" Opaque PKG_W9_THISCALL utfwin_wave9_00980480(Opaque, Opaque);
extern "C" Opaque PKG_W9_THISCALL utfwin_wave9_009804e0(Opaque, Opaque);
extern "C" Opaque PKG_W9_THISCALL utfwin_wave9_00980510(Opaque);
extern "C" PKG_W9_NAKED PKG_W9_THISCALL Opaque utfwin_wave9_00980c50(Opaque,
                                                                     Opaque,
                                                                     Opaque,
                                                                     Opaque);
extern "C" Opaque PKG_W9_THISCALL utfwin_wave9_009817c0(Opaque, Opaque);

}
