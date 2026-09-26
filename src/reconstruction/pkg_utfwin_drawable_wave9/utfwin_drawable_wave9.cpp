#include "utfwin_drawable_wave9.hpp"

namespace openspore::reconstruction::pkg_utfwin_drawable_wave9 {
namespace {

OpaqueWord pointer_value(const void* pointer) {
  return static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

}

extern "C" void PKG_UTFWIN_DRAWABLE_THISCALL
re_009849a0(OpaqueObject* self, OpaqueDrawableWire* target) {
  target->field_04 = pointer_value(self) - 4u;
  target->field_00 = 0x1444c24u;
  target->field_08 = 1u;
  const OpaqueWord derived_vtable = self->vtable_00->slot_14(self);
  target->field_0c = derived_vtable;
}

extern "C" OpaqueWord PKG_UTFWIN_DRAWABLE_THISCALL
re_00985ce0(OpaqueObject* self) {
  static_cast<void>(self);
  return 0x4f063bb3u;
}

extern "C" void PKG_UTFWIN_DRAWABLE_THISCALL
re_00987ae0(OpaqueObject* self, OpaqueDrawableWire* target) {
  target->field_04 = pointer_value(self) - 4u;
  target->field_00 = 0x14451c4u;
  target->field_08 = 1u;
  const OpaqueWord derived_vtable = self->vtable_00->slot_14(self);
  target->field_0c = derived_vtable;
}

extern "C" OpaqueWord PKG_UTFWIN_DRAWABLE_THISCALL
re_00b267d0(OpaqueObject* self, OpaqueWord selector) {
  const OpaqueWord self_value = pointer_value(self);
  return selector == 0x037e958bu ? self_value : 0u;
}

}
