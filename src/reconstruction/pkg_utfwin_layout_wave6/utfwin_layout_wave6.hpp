#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "UTFWin layout wave 6 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_UTFWIN_LAYOUT_THISCALL __thiscall
#define PKG_UTFWIN_LAYOUT_CDECL __cdecl
#else
#define PKG_UTFWIN_LAYOUT_THISCALL __attribute__((thiscall))
#define PKG_UTFWIN_LAYOUT_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_utfwin_layout_wave6 {

using Opaque = std::uintptr_t;

struct OpaqueCastObject;

using CastSlotD0 = Opaque**(PKG_UTFWIN_LAYOUT_THISCALL*)(OpaqueCastObject*,
                                                         Opaque**);

struct OpaqueCastVtable {
  std::array<Opaque, 52> prefix{};
  CastSlotD0 slot_d0 = nullptr;
};

struct OpaqueCastObject {
  OpaqueCastVtable* vtable = nullptr;
  std::array<std::uint8_t, 0x34> opaque_04{};
  Opaque value_38 = 0;
};

struct IntrusiveNode {
  IntrusiveNode* next = nullptr;
  IntrusiveNode* previous = nullptr;
};

struct LayoutWindow;

using ParentSlot10 = LayoutWindow*(PKG_UTFWIN_LAYOUT_THISCALL*)(LayoutWindow*);

struct LayoutWindowVtable {
  std::array<Opaque, 4> prefix{};
  ParentSlot10 slot_10 = nullptr;
};

struct LayoutManager {
  std::array<std::uint8_t, 0x18> opaque_00{};
  IntrusiveNode queue_18;
  std::uint32_t opaque_20 = 0;
  std::uint8_t opaque_24 = 0;
  std::uint8_t state_25 = 0;
};

struct LayoutWindow {
  LayoutWindowVtable* vtable = nullptr;
  IntrusiveNode sibling_04;
  std::array<std::uint8_t, 0x1c> opaque_0c{};
  std::uint32_t flags_28 = 0;
  std::uint32_t opaque_2c = 0;
  LayoutManager* manager_30 = nullptr;
  std::uint32_t opaque_34 = 0;
  IntrusiveNode children_38;
};

struct OpaqueIndexCarrier {
  std::array<std::uint8_t, 0x14> opaque_00{};
  std::array<Opaque*, 6> values_14{};
};

struct OpaqueImageCarrier {
  std::array<std::uint8_t, 0x2c> opaque_00{};
  Opaque* value_2c = nullptr;
  std::uint32_t opaque_30 = 0;
};

struct OpaqueTailVtable {
  std::array<Opaque, 35> prefix{};
  Opaque(PKG_UTFWIN_LAYOUT_THISCALL* slot_8c)(Opaque*, Opaque) = nullptr;
};

using Abi009601e0 = void(PKG_UTFWIN_LAYOUT_THISCALL*)(OpaqueCastObject*,
                                                      Opaque*, Opaque*&);
using Abi00961260 = void(PKG_UTFWIN_LAYOUT_THISCALL*)(OpaqueCastObject*,
                                                      Opaque*);
using Abi00961300 = void(PKG_UTFWIN_LAYOUT_THISCALL*)(LayoutWindow*,
                                                      LayoutWindow*);
using Abi00962830 = Opaque*(PKG_UTFWIN_LAYOUT_THISCALL*)(Opaque*, Opaque);
using Abi009646d0 = Opaque*(PKG_UTFWIN_LAYOUT_THISCALL*)(Opaque, Opaque);
using Abi00967e20 = void(PKG_UTFWIN_LAYOUT_THISCALL*)(OpaqueIndexCarrier*,
                                                      Opaque, Opaque*);
using Abi00967e60 = Opaque*(PKG_UTFWIN_LAYOUT_THISCALL*)(OpaqueImageCarrier*,
                                                         Opaque*);
using Abi00967e80 = Opaque(PKG_UTFWIN_LAYOUT_THISCALL*)(Opaque*, Opaque);
using Abi0096feb0 = Opaque*(PKG_UTFWIN_LAYOUT_THISCALL*)(Opaque*, Opaque);

static_assert(sizeof(void*) == 4);
static_assert(sizeof(Opaque) == 4);
static_assert(offsetof(OpaqueCastVtable, slot_d0) == 0xd0);
static_assert(sizeof(OpaqueCastVtable) == 0xd4);
static_assert(offsetof(OpaqueCastObject, value_38) == 0x38);
static_assert(sizeof(OpaqueCastObject) == 0x3c);
static_assert(offsetof(LayoutWindowVtable, slot_10) == 0x10);
static_assert(offsetof(LayoutWindow, sibling_04) == 0x04);
static_assert(offsetof(LayoutWindow, flags_28) == 0x28);
static_assert(offsetof(LayoutWindow, manager_30) == 0x30);
static_assert(offsetof(LayoutWindow, children_38) == 0x38);
static_assert(sizeof(LayoutWindow) == 0x40);
static_assert(offsetof(LayoutManager, queue_18) == 0x18);
static_assert(offsetof(LayoutManager, state_25) == 0x25);
static_assert(offsetof(OpaqueIndexCarrier, values_14) == 0x14);
static_assert(sizeof(OpaqueIndexCarrier) == 0x2c);
static_assert(offsetof(OpaqueImageCarrier, value_2c) == 0x2c);
static_assert(sizeof(OpaqueImageCarrier) == 0x34);
static_assert(offsetof(OpaqueTailVtable, slot_8c) == 0x8c);
static_assert(sizeof(OpaqueTailVtable) == 0x90);

void PKG_UTFWIN_LAYOUT_THISCALL
pkg_utfwin_layout_wave6_009601e0(OpaqueCastObject*, Opaque*, Opaque*&);
void PKG_UTFWIN_LAYOUT_THISCALL
pkg_utfwin_layout_wave6_00961260(OpaqueCastObject*, Opaque*);
void PKG_UTFWIN_LAYOUT_THISCALL pkg_utfwin_layout_wave6_00961300(LayoutWindow*,
                                                                 LayoutWindow*);
Opaque* PKG_UTFWIN_LAYOUT_THISCALL pkg_utfwin_layout_wave6_00962830(Opaque*,
                                                                    Opaque);
Opaque* PKG_UTFWIN_LAYOUT_THISCALL pkg_utfwin_layout_wave6_009646d0(Opaque,
                                                                    Opaque);
void PKG_UTFWIN_LAYOUT_THISCALL
pkg_utfwin_layout_wave6_00967e20(OpaqueIndexCarrier*, Opaque, Opaque*);
Opaque* PKG_UTFWIN_LAYOUT_THISCALL
pkg_utfwin_layout_wave6_00967e60(OpaqueImageCarrier*, Opaque*);
Opaque PKG_UTFWIN_LAYOUT_THISCALL pkg_utfwin_layout_wave6_00967e80(Opaque*,
                                                                   Opaque);
Opaque* PKG_UTFWIN_LAYOUT_THISCALL pkg_utfwin_layout_wave6_0096feb0(Opaque*,
                                                                    Opaque);

}

#undef PKG_UTFWIN_LAYOUT_CDECL
#undef PKG_UTFWIN_LAYOUT_THISCALL
