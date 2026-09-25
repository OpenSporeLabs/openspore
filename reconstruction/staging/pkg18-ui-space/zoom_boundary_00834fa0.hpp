#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-18 UI Space staging requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG18_THISCALL __thiscall
#define PKG18_VTABLECALL __thiscall
#else
#define PKG18_THISCALL __attribute__((thiscall))
#define PKG18_VTABLECALL __attribute__((fastcall))
#endif

namespace openspore::reconstruction::pkg18_ui_space {

using Opaque = std::uintptr_t;

static_assert(sizeof(Opaque) == 4, "PKG-18 target words are 32-bit");
static_assert(sizeof(void*) == 4, "PKG-18 target pointers are 32-bit");

struct ZoomVtable;

struct ZoomObject {
  ZoomVtable* vtable;
  std::uint32_t field_04;
  std::array<std::uint8_t, 0x344> opaque;
};

struct ZoomVtable {
  using RawSlot = Opaque;
  std::array<RawSlot, 0x6a> slots;
};

struct ZoomOwner {
  std::array<std::uint8_t, 0x78> bytes;
};

static_assert(sizeof(ZoomVtable::RawSlot) == 4,
              "PKG-18 vtable slots are 32-bit raw words");
static_assert(sizeof(ZoomObject) >= 0x20c,
              "PKG-18 object covers the observed child offset");
static_assert(sizeof(ZoomOwner) == 0x78,
              "PKG-18 zoom owner covers the observed fields");

bool PKG18_THISCALL pkg18_text_zoom_rebind_00834fa0(
    ZoomOwner* owner, ZoomObject* source, ZoomObject* target, Opaque mode,
    Opaque state, Opaque resource_key_0, Opaque resource_key_1,
    Opaque resource_key_2);

}
