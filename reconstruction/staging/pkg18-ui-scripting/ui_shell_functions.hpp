#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-18 UI scripting requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg18_ui_scripting {

using Opaque = std::uint32_t;

struct OpaqueUiVtable;

struct OpaqueUiObject {
  OpaqueUiVtable* vtable;
  std::array<std::uint8_t, 0x34> opaque;
};

struct OpaqueUiShell {
  OpaqueUiVtable* vtable;
  std::array<std::uint8_t, 0x34> opaque;
};

struct OpaqueUiMessage {
  std::array<std::uint8_t, 0x20> opaque;
};

struct OpaqueUiVtable {
  using Slot = Opaque (*)(Opaque, ...);
  std::array<Slot, 0x6a> slots;
};

static_assert(sizeof(Opaque) == 4, "PKG-18 UI scripting words are 32-bit");
static_assert(sizeof(void*) == 4, "PKG-18 UI scripting pointers are 32-bit");
static_assert(sizeof(OpaqueUiObject) == 0x38, "opaque UI service extent");
static_assert(sizeof(OpaqueUiShell) == 0x38, "opaque UI shell extent");
static_assert(sizeof(OpaqueUiMessage) == 0x20, "opaque UI message extent");
static_assert(sizeof(OpaqueUiVtable::Slot) == 4, "UI vtable slot width");

#if defined(_MSC_VER)
#define PKG18_THISCALL __thiscall
#else
#define PKG18_THISCALL __attribute__((thiscall))
#endif

bool PKG18_THISCALL pkg18_ui_shell_dispatch_005bf9d0(OpaqueUiShell* shell,
                                                     Opaque message_id,
                                                     OpaqueUiMessage* message);

void PKG18_THISCALL pkg18_ui_shell_set_enabled_005c0380(OpaqueUiShell* shell,
                                                        std::uint8_t enabled);

bool PKG18_THISCALL pkg18_ui_shell_handle_message_005c0100(
    OpaqueUiShell* shell, Opaque unused, OpaqueUiMessage* message);

}
