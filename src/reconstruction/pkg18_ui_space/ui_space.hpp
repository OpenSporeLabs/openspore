#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-18 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG18_THISCALL __thiscall
#define PKG18_FASTCALL __fastcall
#else
#define PKG18_THISCALL __attribute__((thiscall))
#define PKG18_FASTCALL __attribute__((fastcall))
#endif

namespace openspore::reconstruction::pkg18_ui_space {

using Opaque = std::uintptr_t;

static_assert(sizeof(Opaque) == 4, "PKG-18 target words are 32-bit");
static_assert(sizeof(void*) == 4, "PKG-18 target pointers are 32-bit");
static_assert(sizeof(float) == 4, "PKG-18 target floats are 32-bit");

struct SpaceUiVtable;

struct SpaceUiObject {
  SpaceUiVtable* vtable;
  std::uint32_t refcount;
  std::array<std::uint8_t, 0x348> opaque;
};

struct SpaceUiVtable {
  using RawSlot = Opaque;
  std::array<RawSlot, 0x6a> slots;
};

static_assert(sizeof(SpaceUiVtable::RawSlot) == 4,
              "PKG-18 vtable slots are 32-bit raw target words");
static_assert(offsetof(SpaceUiObject, vtable) == 0,
              "PKG-18 object vtable offset");
static_assert(offsetof(SpaceUiObject, refcount) == 4,
              "PKG-18 object refcount offset");
static_assert(sizeof(SpaceUiObject) >= 0x20c,
              "PKG-18 object model covers the observed child offset");

struct TextZoomOwner {
  std::array<std::uint8_t, 0x78> bytes;
};

struct SpaceUiState {
  std::array<std::uint8_t, 0x6a8> bytes;
};

bool PKG18_THISCALL pkg18_text_zoom_rebind_00834fa0(
    TextZoomOwner* owner, SpaceUiObject* source, SpaceUiObject* target,
    Opaque mode, Opaque state, Opaque resource_key_0, Opaque resource_key_1,
    Opaque resource_key_2);

void PKG18_FASTCALL pkg18_space_ui_initialize_01073700(SpaceUiState* state);

}
