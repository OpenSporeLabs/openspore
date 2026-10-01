#include "editor_007c3ba0.hpp"

#include <cstddef>

#if defined(_MSC_VER)
#define PKG_EDITOR_007C3BA0_THISCALL __thiscall
#else
#define PKG_EDITOR_007C3BA0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_editor_007c3ba0 {

struct OpaqueEditorTeardown {
  std::uint8_t opaque_000[0x158];
  TargetWord field_158;
  std::uint8_t opaque_15c[0x14];
  TargetWord field_170;
};

static_assert(offsetof(OpaqueEditorTeardown, field_158) == 0x158,
              "receiver +0x158 word offset");
static_assert(offsetof(OpaqueEditorTeardown, field_170) == 0x170,
              "receiver +0x170 word offset");
static_assert(sizeof(OpaqueEditorTeardown) == 0x174,
              "receiver observed extent ends after +0x170");

namespace {

void inert_release_word(TargetWord) {}

EditorTeardownPorts g_editor_teardown_ports{inert_release_word,
                                            inert_release_word};

}

TargetWord g_editor_slot_007c3ba0_0 = 0;
TargetWord g_editor_slot_007c3ba0_1 = 0;
TargetWord g_editor_slot_007c3ba0_2 = 0;

EditorTeardownPorts& editor_teardown_ports() { return g_editor_teardown_ports; }

void editor_teardown_set_ports(const EditorTeardownPorts& ports) {
  g_editor_teardown_ports.release_field_158 =
      ports.release_field_158 == nullptr ? inert_release_word
                                         : ports.release_field_158;
  g_editor_teardown_ports.release_field_170 =
      ports.release_field_170 == nullptr ? inert_release_word
                                         : ports.release_field_170;
}

void editor_teardown_reset_ports() {
  g_editor_teardown_ports.release_field_158 = inert_release_word;
  g_editor_teardown_ports.release_field_170 = inert_release_word;
}

extern "C" std::uint8_t PKG_EDITOR_007C3BA0_THISCALL
editor_teardown_007c3ba0(OpaqueEditorTeardown* receiver) {
  const TargetWord field_158 = receiver->field_158;
  if (field_158 != 0u) {
    if (g_editor_slot_007c3ba0_0 == field_158) {
      g_editor_slot_007c3ba0_1 |= 0x2u;
      g_editor_slot_007c3ba0_2 |= 0x8u;
      g_editor_slot_007c3ba0_0 = 0u;
    }
    g_editor_teardown_ports.release_field_158(receiver->field_158);
    receiver->field_158 = 0u;
  }

  if (receiver->field_170 != 0u) {
    g_editor_teardown_ports.release_field_170(receiver->field_170);
    receiver->field_170 = 0u;
    return 1u;
  }
  return 0u;
}

}

#undef PKG_EDITOR_007C3BA0_THISCALL
