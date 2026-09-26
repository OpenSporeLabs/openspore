#include "utfwin_window_wave9.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_utfwin_window_wave9 {
namespace {

template <typename To>
To function_from(Opaque word) {
  static_assert(sizeof(To) == sizeof(Opaque),
                "UTFWin function pointer width mismatch");
  To result{};
  std::memcpy(&result, &word, sizeof(result));
  return result;
}

}

namespace unresolved_contracts {

extern "C" Opaque PKG_UTFWIN_WINDOW_WAVE9_THISCALL
pkg_utfwin_window_wave9_re_00950eb0(OpaqueEffect*, Opaque);
extern "C" void PKG_UTFWIN_WINDOW_WAVE9_THISCALL
pkg_utfwin_window_wave9_re_0096ffd0(OpaqueGlide*, Opaque);

}

Opaque PKG_UTFWIN_WINDOW_WAVE9_THISCALL
pkg_utfwin_window_wave9_0095fa30(OpaqueWindow* object, Opaque value) {
  object->field_80 = value;
  return value;
}

void PKG_UTFWIN_WINDOW_WAVE9_THISCALL
pkg_utfwin_window_wave9_0095fd60(OpaqueWindow* object, Opaque value) {
  const Opaque previous = object->field_a8;
  if (value == previous) {
    return;
  }
  object->field_a8 = value;
  OpaqueWindowMessage message;
  message.code_08 = 0x13u;
  message.new_state_0c = value;
  message.previous_state_10 = previous;
  const auto message_slot =
      function_from<WindowSlot114>(object->vtable_00->slot_114);
  message_slot(object, &message);
  if (object->field_1dc != 0) {
    const auto invalidate_slot =
        function_from<WindowSlot90>(object->vtable_00->slot_90);
    invalidate_slot(object);
  }
}

Opaque PKG_UTFWIN_WINDOW_WAVE9_THISCALL
pkg_utfwin_window_wave9_009672d0(OpaqueEffect* object, Opaque type_id) {
  if (type_id != 0x6f90a535u) {
    return unresolved_contracts::pkg_utfwin_window_wave9_re_00950eb0(object,
                                                                     type_id);
  }
  if (object == nullptr) {
    return 0;
  }
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(object) + 0x0cu);
}

void PKG_UTFWIN_WINDOW_WAVE9_THISCALL
pkg_utfwin_window_wave9_0096ff70(OpaqueGlide* object, Opaque flags) {
  const Opaque adjusted =
      static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(object) - 0x0cu);
  unresolved_contracts::pkg_utfwin_window_wave9_re_0096ffd0(
      reinterpret_cast<OpaqueGlide*>(static_cast<std::uintptr_t>(adjusted)),
      flags);
}

}
