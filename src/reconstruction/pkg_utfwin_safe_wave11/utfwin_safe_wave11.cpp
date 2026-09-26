#include "utfwin_safe_wave11.hpp"

#include <cstring>

#if defined(_MSC_VER)
#define PKG_UTFWIN_SAFE_WAVE11_THISCALL __thiscall
#else
#define PKG_UTFWIN_SAFE_WAVE11_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_utfwin_safe_wave11 {

Opaque utfwin_safe_wave11_scale_01485720 = 0x3f800000u;

OpaqueNameInput* PKG_UTFWIN_SAFE_WAVE11_THISCALL
utfwin_safe_wave11_005ac9f0(OpaqueNameInput* object) {
  utfwin_safe_wave11_base_construct_005b0f80(object);

  float scale = 0.0f;
  std::memcpy(&scale, &utfwin_safe_wave11_scale_01485720, sizeof(scale));

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

}
