#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "UTFWin effects wave 6 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_utfwin_effects_wave6 {

using Opaque = std::uint32_t;

#if defined(_MSC_VER)
#define PKG_UTFWIN_THISCALL __thiscall
#define PKG_UTFWIN_CDECL __cdecl
#else
#define PKG_UTFWIN_THISCALL __attribute__((thiscall))
#define PKG_UTFWIN_CDECL __attribute__((cdecl))
#endif

struct FloatRect {
  float left;
  float top;
  float right;
  float bottom;
};

struct OpaqueLayout {
  Opaque vtable;
  std::uint8_t flags;
  std::array<std::uint8_t, 0x0b> opaque;
  FloatRect stored;
};

struct OpaqueColorVtable {
  std::array<Opaque, 0x17> prefix;
  Opaque slot_5c;
};

struct OpaqueColorTarget {
  OpaqueColorVtable* vtable;
  std::array<std::uint8_t, 0x5c> opaque;
};

struct OpaqueModulateEffect {
  Opaque vtable;
  std::array<std::uint8_t, 0x60> opaque;
  Opaque color_64;
  Opaque color_68;
};

using FactorySlot = Opaque*(PKG_UTFWIN_THISCALL*)(Opaque, Opaque, Opaque);
using ConstantSlot = Opaque(PKG_UTFWIN_THISCALL*)(Opaque, Opaque);
using AdjustSlot = Opaque(PKG_UTFWIN_THISCALL*)(Opaque, Opaque);
using RectTransformSlot = bool(PKG_UTFWIN_THISCALL*)(OpaqueLayout*,
                                                     const FloatRect*,
                                                     FloatRect*);
using RectStoreSlot = void(PKG_UTFWIN_THISCALL*)(OpaqueLayout*,
                                                 const FloatRect*);
using ModulateSlot = void(PKG_UTFWIN_THISCALL*)(OpaqueModulateEffect*,
                                                OpaqueColorTarget*, float);

static_assert(sizeof(Opaque) == 4, "UTFWin opaque words are 32-bit");
static_assert(sizeof(void*) == 4, "UTFWin pointers are 32-bit");
static_assert(sizeof(FloatRect) == 16, "UTFWin rectangles are 16 bytes");
static_assert(offsetof(FloatRect, left) == 0x00, "rectangle left offset");
static_assert(offsetof(FloatRect, top) == 0x04, "rectangle top offset");
static_assert(offsetof(FloatRect, right) == 0x08, "rectangle right offset");
static_assert(offsetof(FloatRect, bottom) == 0x0c, "rectangle bottom offset");
static_assert(offsetof(OpaqueLayout, flags) == 0x04, "layout flags offset");
static_assert(offsetof(OpaqueLayout, stored) == 0x10, "layout storage offset");
static_assert(sizeof(OpaqueLayout) == 0x20, "opaque layout extent");
static_assert(offsetof(OpaqueColorVtable, slot_5c) == 0x5c,
              "color virtual slot offset");
static_assert(sizeof(OpaqueColorVtable) == 0x60, "opaque color vtable extent");
static_assert(offsetof(OpaqueModulateEffect, color_64) == 0x64,
              "modulate color 0 offset");
static_assert(offsetof(OpaqueModulateEffect, color_68) == 0x68,
              "modulate color 1 offset");
static_assert(sizeof(OpaqueModulateEffect) == 0x6c, "modulate effect extent");

Opaque* PKG_UTFWIN_THISCALL utfwin_0096fec0(Opaque, Opaque unused,
                                            Opaque allocator_context);
Opaque PKG_UTFWIN_THISCALL utfwin_0096ffc0(Opaque, Opaque unused);
Opaque* PKG_UTFWIN_THISCALL utfwin_0097e440(Opaque, Opaque unused,
                                            Opaque allocator_context);
Opaque PKG_UTFWIN_THISCALL utfwin_0097e550(Opaque object, Opaque token);
Opaque PKG_UTFWIN_THISCALL utfwin_0097e890(Opaque, Opaque unused);
bool PKG_UTFWIN_THISCALL utfwin_0097e990(OpaqueLayout* layout,
                                         const FloatRect* source,
                                         FloatRect* destination);
void PKG_UTFWIN_THISCALL utfwin_0097ea50(OpaqueLayout* layout,
                                         const FloatRect* source);
void PKG_UTFWIN_THISCALL utfwin_00980120(OpaqueModulateEffect* effect,
                                         OpaqueColorTarget* target,
                                         float amount);
Opaque PKG_UTFWIN_THISCALL utfwin_00980200(Opaque, Opaque unused);
Opaque PKG_UTFWIN_THISCALL utfwin_00980470(Opaque object, std::uint8_t flags);

}
