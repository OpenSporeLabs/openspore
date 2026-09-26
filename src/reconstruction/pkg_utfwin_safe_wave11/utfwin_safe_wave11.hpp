#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG utfwin safe wave11 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_UTFWIN_SAFE_WAVE11_THISCALL __thiscall
#else
#define PKG_UTFWIN_SAFE_WAVE11_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_utfwin_safe_wave11 {

using Opaque = std::uint32_t;

struct OpaqueVTable4 {
  Opaque slot_00;
  Opaque slot_04;
  Opaque slot_08;
  Opaque slot_0c;
};

struct OpaqueVTable15 {
  std::array<Opaque, 15> slots_00;
  Opaque terminator_3c;
};

struct OpaqueNameInput {
  Opaque vtable_00;
  std::uint8_t byte_04;
  std::uint8_t byte_05;
  std::uint8_t byte_06;
  std::uint8_t pad_07;
  float field_08;
  Opaque field_0c;
  Opaque field_10;
  Opaque vtable_14;
  Opaque field_18;
  Opaque field_1c;
  Opaque field_20;
  Opaque field_24;
  float field_28;
  float field_2c;
  float field_30;
  std::array<Opaque, 3> pad_34;
  float field_40;
  float field_44;
  Opaque field_48;
  std::array<Opaque, 2> pad_4c;
  float field_54;
  float field_58;
};

namespace addresses {

inline constexpr Opaque vtable_013eb384 = 0x013eb384u;
inline constexpr Opaque vtable_013eb394 = 0x013eb394u;
inline constexpr Opaque vtable_013eb938 = 0x013eb938u;
inline constexpr Opaque vtable_013ec458 = 0x013ec458u;
inline constexpr Opaque vtable_013f7214 = 0x013f7214u;
inline constexpr Opaque vtable_013f7224 = 0x013f7224u;
inline constexpr Opaque vtable_013f73e4 = 0x013f73e4u;
inline constexpr Opaque terminator_00800000 = 0x00800000u;
inline constexpr Opaque scalar_01485720 = 0x01485720u;

}

static_assert(sizeof(void*) == 4, "utfwin safe wave11 pointers are 32-bit");
static_assert(sizeof(Opaque) == 4,
              "utfwin safe wave11 opaque words are 32-bit");
static_assert(sizeof(OpaqueVTable4) == 0x10, "utfwin four-slot table extent");
static_assert(sizeof(OpaqueVTable15) == 0x40,
              "utfwin fifteen-slot table extent");
static_assert(offsetof(OpaqueVTable15, terminator_3c) == 0x3c,
              "utfwin fifteen-slot table terminator offset");
static_assert(offsetof(OpaqueNameInput, vtable_00) == 0x00,
              "utfwin name input primary vtable offset");
static_assert(offsetof(OpaqueNameInput, byte_04) == 0x04,
              "utfwin name input flag byte offset");
static_assert(offsetof(OpaqueNameInput, byte_05) == 0x05,
              "utfwin name input flag byte offset");
static_assert(offsetof(OpaqueNameInput, byte_06) == 0x06,
              "utfwin name input flag byte offset");
static_assert(offsetof(OpaqueNameInput, field_08) == 0x08,
              "utfwin name input base scalar offset");
static_assert(offsetof(OpaqueNameInput, field_0c) == 0x0c,
              "utfwin name input base word offset");
static_assert(offsetof(OpaqueNameInput, field_10) == 0x10,
              "utfwin name input base word offset");
static_assert(offsetof(OpaqueNameInput, vtable_14) == 0x14,
              "utfwin name input secondary vtable offset");
static_assert(offsetof(OpaqueNameInput, field_18) == 0x18,
              "utfwin name input observer offset");
static_assert(offsetof(OpaqueNameInput, field_1c) == 0x1c,
              "utfwin name input observer offset");
static_assert(offsetof(OpaqueNameInput, field_20) == 0x20,
              "utfwin name input observer offset");
static_assert(offsetof(OpaqueNameInput, field_24) == 0x24,
              "utfwin name input counter offset");
static_assert(offsetof(OpaqueNameInput, field_28) == 0x28,
              "utfwin name input scalar offset");
static_assert(offsetof(OpaqueNameInput, field_2c) == 0x2c,
              "utfwin name input scalar offset");
static_assert(offsetof(OpaqueNameInput, field_30) == 0x30,
              "utfwin name input scalar offset");
static_assert(offsetof(OpaqueNameInput, pad_34) == 0x34,
              "utfwin name input reserved span offset");
static_assert(offsetof(OpaqueNameInput, field_40) == 0x40,
              "utfwin name input scalar offset");
static_assert(offsetof(OpaqueNameInput, field_44) == 0x44,
              "utfwin name input scalar offset");
static_assert(offsetof(OpaqueNameInput, field_48) == 0x48,
              "utfwin name input word offset");
static_assert(offsetof(OpaqueNameInput, pad_4c) == 0x4c,
              "utfwin name input reserved span offset");
static_assert(offsetof(OpaqueNameInput, field_54) == 0x54,
              "utfwin name input scalar offset");
static_assert(offsetof(OpaqueNameInput, field_58) == 0x58,
              "utfwin name input scalar offset");
static_assert(sizeof(OpaqueNameInput) == 0x5c, "utfwin name input extent");
static_assert(sizeof(OpaqueNameInput*) == 4, "utfwin name input pointer width");

// 0x005c00e0 is not promoted by this batch: it carries the SDK symbol
// UI_EditorNamePanel_ctor and therefore belongs to the SDK-boundary path
// rather than the residual-unknown path. Its two port seams, the base
// destructor 0x005c0070 and the release 0x00f47380, are dropped with it.
extern "C" void PKG_UTFWIN_SAFE_WAVE11_THISCALL
utfwin_safe_wave11_base_construct_005b0f80(OpaqueNameInput*);

extern "C" Opaque utfwin_safe_wave11_scale_01485720;

extern "C" OpaqueNameInput* PKG_UTFWIN_SAFE_WAVE11_THISCALL
utfwin_safe_wave11_005ac9f0(OpaqueNameInput*);

}
