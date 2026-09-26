#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "UTFWin wave 11 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_UTFWIN_WAVE11_THISCALL __thiscall
#else
#define PKG_UTFWIN_WAVE11_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_utfwin_wave11 {

using Opaque = std::uint32_t;

struct OpaqueVTable4 {
  Opaque slot_00;
  Opaque slot_04;
  Opaque slot_08;
  Opaque slot_0c;
};

struct OpaqueVTable8 {
  std::array<Opaque, 8> slots_00;
  Opaque terminator_20;
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

struct OpaqueNamePanel {
  Opaque vtable_00;
  Opaque vtable_04;
  Opaque vtable_08;
  Opaque refcount_0c;
  std::uint8_t byte_10;
  std::uint8_t byte_11;
  std::array<std::uint8_t, 2> pad_12;
  Opaque field_14;
  Opaque field_18;
  Opaque field_1c;
  Opaque field_20;
  Opaque buffer_24;
  Opaque buffer_28;
  Opaque buffer_2c;
  Opaque field_30;
  Opaque field_34;
};

namespace addresses {

inline constexpr Opaque vtable_013eb384 = 0x013eb384u;
inline constexpr Opaque vtable_013eb394 = 0x013eb394u;
inline constexpr Opaque vtable_013eb938 = 0x013eb938u;
inline constexpr Opaque vtable_013ec458 = 0x013ec458u;
inline constexpr Opaque vtable_013f7214 = 0x013f7214u;
inline constexpr Opaque vtable_013f7224 = 0x013f7224u;
inline constexpr Opaque vtable_013f73e4 = 0x013f73e4u;
inline constexpr Opaque vtable_013f7b70 = 0x013f7b70u;
inline constexpr Opaque vtable_013f7b80 = 0x013f7b80u;
inline constexpr Opaque vtable_013f7b90 = 0x013f7b90u;
inline constexpr Opaque terminator_00800000 = 0x00800000u;
inline constexpr Opaque scalar_01485720 = 0x01485720u;

inline constexpr Opaque slot_005ac9f0_panel_00 = 0x00u;
inline constexpr Opaque slot_005c00e0_panel_08 = 0x02u;
inline constexpr Opaque slot_005c00e0_panel_04 = 0x00u;
inline constexpr Opaque slot_005c00e0_panel_08_00 = 0x00u;
inline constexpr Opaque adjust_005c0050 = 0x04u;
inline constexpr Opaque adjust_005c0060 = 0x08u;

}

using NameInputPanelDestroySlot =
    OpaqueNamePanel *(PKG_UTFWIN_WAVE11_THISCALL *)(OpaqueNamePanel *, Opaque);
using NameInputPanelRefAddSlot =
    void(PKG_UTFWIN_WAVE11_THISCALL *)(OpaqueNamePanel *);
using NameInputPanelRefReleaseSlot =
    Opaque(PKG_UTFWIN_WAVE11_THISCALL *)(OpaqueNamePanel *);

static_assert(sizeof(void *) == 4, "UTFWin pointers are 32-bit");
static_assert(sizeof(Opaque) == 4, "UTFWin opaque words are 32-bit");
static_assert(sizeof(OpaqueVTable4) == 0x10, "UTFWin four-slot table extent");
static_assert(sizeof(OpaqueVTable8) == 0x24, "UTFWin eight-slot table extent");
static_assert(sizeof(OpaqueVTable15) == 0x40,
              "UTFWin fifteen-slot table extent");
static_assert(offsetof(OpaqueVTable8, terminator_20) == 0x20,
              "UTFWin eight-slot table terminator offset");
static_assert(offsetof(OpaqueVTable15, terminator_3c) == 0x3c,
              "UTFWin fifteen-slot table terminator offset");
static_assert(offsetof(OpaqueNameInput, vtable_00) == 0x00,
              "UTFWin name input primary vtable offset");
static_assert(offsetof(OpaqueNameInput, byte_04) == 0x04,
              "UTFWin name input flag byte offset");
static_assert(offsetof(OpaqueNameInput, byte_05) == 0x05,
              "UTFWin name input flag byte offset");
static_assert(offsetof(OpaqueNameInput, byte_06) == 0x06,
              "UTFWin name input flag byte offset");
static_assert(offsetof(OpaqueNameInput, field_08) == 0x08,
              "UTFWin name input base scalar offset");
static_assert(offsetof(OpaqueNameInput, field_0c) == 0x0c,
              "UTFWin name input base word offset");
static_assert(offsetof(OpaqueNameInput, field_10) == 0x10,
              "UTFWin name input base word offset");
static_assert(offsetof(OpaqueNameInput, vtable_14) == 0x14,
              "UTFWin name input secondary vtable offset");
static_assert(offsetof(OpaqueNameInput, field_18) == 0x18,
              "UTFWin name input observer offset");
static_assert(offsetof(OpaqueNameInput, field_1c) == 0x1c,
              "UTFWin name input observer offset");
static_assert(offsetof(OpaqueNameInput, field_20) == 0x20,
              "UTFWin name input observer offset");
static_assert(offsetof(OpaqueNameInput, field_24) == 0x24,
              "UTFWin name input counter offset");
static_assert(offsetof(OpaqueNameInput, field_28) == 0x28,
              "UTFWin name input scalar offset");
static_assert(offsetof(OpaqueNameInput, field_2c) == 0x2c,
              "UTFWin name input scalar offset");
static_assert(offsetof(OpaqueNameInput, field_30) == 0x30,
              "UTFWin name input scalar offset");
static_assert(offsetof(OpaqueNameInput, pad_34) == 0x34,
              "UTFWin name input reserved span offset");
static_assert(offsetof(OpaqueNameInput, field_40) == 0x40,
              "UTFWin name input scalar offset");
static_assert(offsetof(OpaqueNameInput, field_44) == 0x44,
              "UTFWin name input scalar offset");
static_assert(offsetof(OpaqueNameInput, field_48) == 0x48,
              "UTFWin name input word offset");
static_assert(offsetof(OpaqueNameInput, pad_4c) == 0x4c,
              "UTFWin name input reserved span offset");
static_assert(offsetof(OpaqueNameInput, field_54) == 0x54,
              "UTFWin name input scalar offset");
static_assert(offsetof(OpaqueNameInput, field_58) == 0x58,
              "UTFWin name input scalar offset");
static_assert(sizeof(OpaqueNameInput) == 0x5c, "UTFWin name input extent");
static_assert(offsetof(OpaqueNamePanel, vtable_00) == 0x00,
              "UTFWin name panel primary vtable offset");
static_assert(offsetof(OpaqueNamePanel, vtable_04) == 0x04,
              "UTFWin name panel secondary vtable offset");
static_assert(offsetof(OpaqueNamePanel, vtable_08) == 0x08,
              "UTFWin name panel tertiary vtable offset");
static_assert(offsetof(OpaqueNamePanel, refcount_0c) == 0x0c,
              "UTFWin name panel reference count offset");
static_assert(offsetof(OpaqueNamePanel, byte_10) == 0x10,
              "UTFWin name panel state byte offset");
static_assert(offsetof(OpaqueNamePanel, byte_11) == 0x11,
              "UTFWin name panel state byte offset");
static_assert(offsetof(OpaqueNamePanel, field_14) == 0x14,
              "UTFWin name panel observer offset");
static_assert(offsetof(OpaqueNamePanel, field_18) == 0x18,
              "UTFWin name panel observer offset");
static_assert(offsetof(OpaqueNamePanel, field_1c) == 0x1c,
              "UTFWin name panel observer offset");
static_assert(offsetof(OpaqueNamePanel, field_20) == 0x20,
              "UTFWin name panel observer offset");
static_assert(offsetof(OpaqueNamePanel, buffer_24) == 0x24,
              "UTFWin name panel inline buffer begin offset");
static_assert(offsetof(OpaqueNamePanel, buffer_28) == 0x28,
              "UTFWin name panel inline buffer cursor offset");
static_assert(offsetof(OpaqueNamePanel, buffer_2c) == 0x2c,
              "UTFWin name panel inline buffer end offset");
static_assert(offsetof(OpaqueNamePanel, field_30) == 0x30,
              "UTFWin name panel word offset");
static_assert(offsetof(OpaqueNamePanel, field_34) == 0x34,
              "UTFWin name panel word offset");
static_assert(sizeof(OpaqueNamePanel) == 0x38, "UTFWin name panel extent");
static_assert(sizeof(OpaqueNameInput *) == 4,
              "UTFWin name input pointer width");
static_assert(sizeof(OpaqueNamePanel *) == 4,
              "UTFWin name panel pointer width");

OpaqueNameInput *PKG_UTFWIN_WAVE11_THISCALL
pkg_utfwin_wave11_005ac9f0(OpaqueNameInput *);
OpaqueNamePanel *PKG_UTFWIN_WAVE11_THISCALL
pkg_utfwin_wave11_005c00e0(OpaqueNamePanel *, Opaque);

}
