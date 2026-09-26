#include "utfwin_wave11.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_utfwin_wave11 {

namespace unresolved_contracts {

extern "C" void PKG_UTFWIN_WAVE11_THISCALL
pkg_utfwin_wave11_re_005b0f80(OpaqueNameInput *);
extern "C" void PKG_UTFWIN_WAVE11_THISCALL
pkg_utfwin_wave11_re_005c0070(OpaqueNamePanel *);
extern "C" void pkg_utfwin_wave11_re_00f47380(Opaque *);
extern "C" Opaque pkg_utfwin_wave11_g_word_01485720;

}

OpaqueNameInput *PKG_UTFWIN_WAVE11_THISCALL
pkg_utfwin_wave11_005ac9f0(OpaqueNameInput *object) {
  unresolved_contracts::pkg_utfwin_wave11_re_005b0f80(object);

  float scale = 0.0f;
  std::memcpy(&scale, &unresolved_contracts::pkg_utfwin_wave11_g_word_01485720,
              sizeof(scale));

  object->vtable_14 = addresses::vtable_013ec458;
  object->field_18 = 0;
  object->vtable_00 = addresses::vtable_013f7224;
  object->vtable_14 = addresses::vtable_013f7214;
  object->field_1c = 0;
  object->field_20 = 0;
  object->field_24 = 0;
  object->field_28 = 0.0f;
  object->field_2c = 0.0f;
  object->field_30 = 0.0f;
  object->field_48 = 0;
  object->byte_04 = 0;
  object->field_40 = 0.0f;
  object->field_44 = 0.0f;
  object->field_54 = scale;
  object->field_58 = 0.0f;

  return object;
}

OpaqueNamePanel *PKG_UTFWIN_WAVE11_THISCALL
pkg_utfwin_wave11_005c00e0(OpaqueNamePanel *object, Opaque flags) {
  unresolved_contracts::pkg_utfwin_wave11_re_005c0070(object);

  if ((flags & 0x1u) != 0u) {
    unresolved_contracts::pkg_utfwin_wave11_re_00f47380(
        reinterpret_cast<Opaque *>(object));
  }

  return object;
}

}
