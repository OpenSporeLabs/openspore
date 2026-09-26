#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "UTFWin window wave 9 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_UTFWIN_WINDOW_WAVE9_THISCALL __thiscall
#else
#define PKG_UTFWIN_WINDOW_WAVE9_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_utfwin_window_wave9 {

using Opaque = std::uint32_t;

struct OpaqueEffect;
struct OpaqueGlide;
struct OpaqueWindowMessage;

struct OpaqueWindowVTable {
  std::array<Opaque, 0x24> slots_00{};
  Opaque slot_90 = 0;
  std::array<Opaque, 0x20> slots_94{};
  Opaque slot_114 = 0;
};

struct OpaqueWindow {
  OpaqueWindowVTable* vtable_00 = nullptr;
  std::array<std::uint8_t, 0x7c> opaque_04{};
  Opaque field_80 = 0;
  std::array<std::uint8_t, 0x24> opaque_84{};
  Opaque field_a8 = 0;
  std::array<std::uint8_t, 0x130> opaque_ac{};
  Opaque field_1dc = 0;
};

struct OpaqueWindowMessage {
  Opaque stale_00;
  Opaque stale_04;
  Opaque code_08;
  Opaque new_state_0c;
  Opaque previous_state_10;
};

using WindowSlot90 = Opaque(PKG_UTFWIN_WINDOW_WAVE9_THISCALL*)(OpaqueWindow*);
using WindowSlot114 = void(PKG_UTFWIN_WINDOW_WAVE9_THISCALL*)(
    OpaqueWindow*, OpaqueWindowMessage*);
using EffectCastSlot = Opaque(PKG_UTFWIN_WINDOW_WAVE9_THISCALL*)(OpaqueEffect*,
                                                                 Opaque);
using GlideDestroySlot = void(PKG_UTFWIN_WINDOW_WAVE9_THISCALL*)(OpaqueGlide*,
                                                                 Opaque);

static_assert(sizeof(void*) == 4, "UTFWin pointers are 32-bit");
static_assert(sizeof(Opaque) == 4, "UTFWin opaque words are 32-bit");
static_assert(sizeof(OpaqueWindowMessage) == 0x14, "UTFWin message state size");
static_assert(offsetof(OpaqueWindowMessage, stale_00) == 0x00,
              "UTFWin message stale head offset");
static_assert(offsetof(OpaqueWindowMessage, stale_04) == 0x04,
              "UTFWin message stale head offset");
static_assert(offsetof(OpaqueWindowMessage, code_08) == 0x08,
              "UTFWin message code offset");
static_assert(offsetof(OpaqueWindowMessage, new_state_0c) == 0x0c,
              "UTFWin message new-state offset");
static_assert(offsetof(OpaqueWindowMessage, previous_state_10) == 0x10,
              "UTFWin message previous-state offset");
static_assert(offsetof(OpaqueWindowVTable, slot_90) == 0x90,
              "UTFWin invalidation slot offset");
static_assert(offsetof(OpaqueWindowVTable, slot_114) == 0x114,
              "UTFWin message slot offset");
static_assert(sizeof(OpaqueWindowVTable) == 0x118,
              "UTFWin window vtable extent");
static_assert(offsetof(OpaqueWindow, field_80) == 0x80,
              "UTFWin word field offset");
static_assert(offsetof(OpaqueWindow, field_a8) == 0xa8,
              "UTFWin state field offset");
static_assert(offsetof(OpaqueWindow, field_1dc) == 0x1dc,
              "UTFWin invalidation flag offset");
static_assert(sizeof(OpaqueWindow) == 0x1e0, "UTFWin window extent");

Opaque PKG_UTFWIN_WINDOW_WAVE9_THISCALL
pkg_utfwin_window_wave9_0095fa30(OpaqueWindow*, Opaque);
void PKG_UTFWIN_WINDOW_WAVE9_THISCALL
pkg_utfwin_window_wave9_0095fd60(OpaqueWindow*, Opaque);
Opaque PKG_UTFWIN_WINDOW_WAVE9_THISCALL
pkg_utfwin_window_wave9_009672d0(OpaqueEffect*, Opaque);
void PKG_UTFWIN_WINDOW_WAVE9_THISCALL
pkg_utfwin_window_wave9_0096ff70(OpaqueGlide*, Opaque);

}
