#pragma once

#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg editor 007c3ba0 reconstruction requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_EDITOR_007C3BA0_THISCALL __thiscall
#else
#define PKG_EDITOR_007C3BA0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_editor_007c3ba0 {

using TargetWord = std::uint32_t;

struct OpaqueEditorTeardown;

using ReleaseWordPort = void (*)(TargetWord);

struct EditorTeardownPorts {
  ReleaseWordPort release_field_158;
  ReleaseWordPort release_field_170;
};

static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(std::is_integral<std::uint8_t>::value,
              "the observed return width is a single byte");

extern TargetWord g_editor_slot_007c3ba0_0;
extern TargetWord g_editor_slot_007c3ba0_1;
extern TargetWord g_editor_slot_007c3ba0_2;

EditorTeardownPorts& editor_teardown_ports();
void editor_teardown_set_ports(const EditorTeardownPorts& ports);
void editor_teardown_reset_ports();

extern "C" std::uint8_t PKG_EDITOR_007C3BA0_THISCALL
editor_teardown_007c3ba0(OpaqueEditorTeardown* receiver);

}

#undef PKG_EDITOR_007C3BA0_THISCALL
