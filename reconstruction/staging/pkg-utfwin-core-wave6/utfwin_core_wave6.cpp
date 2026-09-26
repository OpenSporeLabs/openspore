#include "utfwin_core_wave6.hpp"

namespace openspore::reconstruction::pkg_utfwin_core_wave6 {

OpaqueWord tooltip_sentinel_0164f328 = 0;

CursorRuntime& cursor_runtime() {
  static CursorRuntime runtime{};
  return runtime;
}

TooltipRuntime& tooltip_runtime() {
  static TooltipRuntime runtime{};
  return runtime;
}

namespace {

void reset_tooltip_state(TooltipCore* self) {
  self->vtable_00 = reinterpret_cast<TooltipCoreVTable*>(0x0141aec8);
  if (self->field_14 != nullptr) {
    self->field_14->vtable_00->release_04(self->field_14);
  }
  if (self->field_10 != nullptr) {
    self->field_10->vtable_00->release_04(self->field_10);
  }
  if (self->field_0c != nullptr) {
    self->field_0c->vtable_00->release_04(self->field_0c);
  }
  if (self->field_08 != nullptr) {
    self->field_08->vtable_00->destroy_08(self->field_08);
  }
  self->vtable_00 = reinterpret_cast<TooltipCoreVTable*>(0x013ec458);
  tooltip_sentinel_0164f328 = 0;
}

}

extern "C" OpaqueWord PKG_UTFWIN_CORE_THISCALL re_00575ea0(WindowCore* self) {
  return self->cursor_id_a4;
}

extern "C" std::uint8_t PKG_UTFWIN_CORE_THISCALL re_00801ac0(
    CursorManager* self, ResourceFactory* resource, DropIconObject** output,
    OpaqueWord forwarded_value, OpaqueWord compared_word) {
  if (compared_word != 0x02393756u) {
    return 0;
  }

  auto* icon = static_cast<DropIconObject*>(cursor_runtime().allocate(
      0x18u,
      reinterpret_cast<const char*>(static_cast<std::uintptr_t>(0x01416fbcu)),
      0u, 0u, 0u, 0u));
  if (icon != nullptr) {
    icon->vtable_00 = reinterpret_cast<DropIconObjectVTable*>(0x013ebcdc);
    icon->field_04 = 0;
    icon->field_08 = 0;
    icon->field_0c = 0;
    icon->field_10 = 0;
    icon->vtable_00 = reinterpret_cast<DropIconObjectVTable*>(0x01416fa8);
  }

  auto* resource_vtable = resource->vtable_00;
  OpaqueWord* data = resource_vtable->read_10(resource);
  icon->field_08 = data[0];
  icon->field_0c = data[1];
  icon->field_10 = data[2];

  const bool accepted = self->vtable_00->dispatch_24(
      self, resource, icon, forwarded_value, 0x02393756u);
  if (!accepted) {
    return 0;
  }

  *output = icon;
  cursor_runtime().icon_dispatch(icon);
  return 1;
}

extern "C" void* PKG_UTFWIN_CORE_THISCALL re_00835380(TooltipCore* self,
                                                      OpaqueWord flags) {
  reset_tooltip_state(self);
  if ((flags & 1u) != 0u) {
    tooltip_runtime().deallocate(self);
  }
  return self;
}

extern "C" void* PKG_UTFWIN_CORE_THISCALL re_00957510(ImageCore* self,
                                                      OpaqueWord type_id) {
  if (type_id == 0x01be8ca6u || type_id == 0xee3f516eu) {
    return self;
  }
  return nullptr;
}

extern "C" void* PKG_UTFWIN_CORE_THISCALL re_0095f960(WindowCore* self,
                                                      OpaqueWord type_id) {
  if (type_id == 0xeec58382u) {
    return nullptr;
  }
  if (type_id != 0xee3f516eu && type_id != 0xeeee8218u) {
    return nullptr;
  }
  if (self == nullptr) {
    return nullptr;
  }
  return static_cast<void*>(reinterpret_cast<std::uint8_t*>(self) + 4);
}

extern "C" std::int32_t PKG_UTFWIN_CORE_THISCALL re_0095f990(WindowCore* self) {
  const std::int32_t old =
      __atomic_fetch_add(&self->ref_count_28, 1, __ATOMIC_SEQ_CST);
  return old + 1;
}

extern "C" std::int32_t PKG_UTFWIN_CORE_THISCALL re_0095f9a0(WindowCore* self) {
  const std::int32_t old =
      __atomic_fetch_sub(&self->ref_count_28, 1, __ATOMIC_SEQ_CST);
  const std::int32_t result = old - 1;
  if (result == 0) {
    static_cast<void>(
        __atomic_fetch_add(&self->ref_count_28, 1, __ATOMIC_SEQ_CST));
    self->vtable_00->destroy_08(self, 1u);
  }
  return result;
}

extern "C" Drawable* PKG_UTFWIN_CORE_THISCALL re_00960050(WindowCore* self,
                                                          Drawable* drawable) {
  Drawable* old = self->drawable_1e4;
  if (drawable == old) {
    return old;
  }
  if (drawable != nullptr) {
    static_cast<void>(drawable->vtable_00->add_ref_00(drawable));
  }
  self->drawable_1e4 = drawable;
  if (old != nullptr) {
    static_cast<void>(old->vtable_00->release_04(old));
  }
  return self->vtable_00->get_drawable_90(self);
}

}

extern "C" PKG_UTFWIN_CORE_STDCALL void* re_00951220(
    openspore::reconstruction::pkg_utfwin_core_wave6::OpaqueWord,
    openspore::reconstruction::pkg_utfwin_core_wave6::OpaqueWord,
    openspore::reconstruction::pkg_utfwin_core_wave6::OpaqueWord,
    openspore::reconstruction::pkg_utfwin_core_wave6::OpaqueWord,
    openspore::reconstruction::pkg_utfwin_core_wave6::OpaqueWord) {
  return nullptr;
}

extern "C" PKG_UTFWIN_CORE_STDCALL void* re_00951230(
    openspore::reconstruction::pkg_utfwin_core_wave6::OpaqueWord,
    openspore::reconstruction::pkg_utfwin_core_wave6::OpaqueWord,
    openspore::reconstruction::pkg_utfwin_core_wave6::OpaqueWord) {
  return nullptr;
}
