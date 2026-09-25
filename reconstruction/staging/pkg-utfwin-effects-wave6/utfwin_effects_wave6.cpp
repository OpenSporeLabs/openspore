#include "utfwin_effects_wave6.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_utfwin_effects_wave6 {
namespace {

using namespace openspore::reconstruction::pkg_utfwin_effects_wave6;

namespace unresolved_contracts {

extern "C" Opaque pkg18_re_009512c0();
extern "C" Opaque* pkg18_re_009512d0(Opaque size, Opaque alignment,
                                    const char* name, Opaque allocator);
extern "C" void PKG_UTFWIN_THISCALL pkg18_re_0096fe30(Opaque* object);
extern "C" Opaque* PKG_UTFWIN_THISCALL pkg18_re_0097e380(Opaque* object);
extern "C" Opaque PKG_UTFWIN_THISCALL pkg18_re_0097e4a0(Opaque object,
                                                       Opaque token);
extern "C" Opaque pkg18_re_007f5eb0(Opaque from, Opaque to, float amount);
extern "C" Opaque PKG_UTFWIN_THISCALL pkg18_re_00980490(
    Opaque object, std::uint8_t flags);

}

template <typename To, typename From>
To copy_function(From function) {
  static_assert(sizeof(To) == sizeof(From), "function pointer width mismatch");
  To result{};
  std::memcpy(&result, &function, sizeof(result));
  return result;
}

template <typename Constructor>
Opaque* create_factory_object(Opaque allocator_context, Opaque size,
                              Opaque alignment, Opaque name,
                              Constructor constructor) {
  Opaque context = allocator_context;
  if (context == 0) {
    context = unresolved_contracts::pkg18_re_009512c0();
  }
  const char* type_name = reinterpret_cast<const char*>(
      static_cast<std::uintptr_t>(name));
  Opaque* object = unresolved_contracts::pkg18_re_009512d0(
      size, alignment, type_name, context);
  if (object == nullptr) {
    return nullptr;
  }
  constructor(object);
  return object;
}

}

Opaque* PKG_UTFWIN_THISCALL utfwin_0096fec0(Opaque, Opaque unused,
                                           Opaque allocator_context) {
  static_cast<void>(unused);
  return create_factory_object(
      allocator_context, 0x60, 4, 0x014424f4u,
      unresolved_contracts::pkg18_re_0096fe30);
}

Opaque PKG_UTFWIN_THISCALL utfwin_0096ffc0(Opaque, Opaque unused) {
  static_cast<void>(unused);
  return 0x01442694u;
}

Opaque* PKG_UTFWIN_THISCALL utfwin_0097e440(Opaque, Opaque unused,
                                           Opaque allocator_context) {
  static_cast<void>(unused);
  return create_factory_object(
      allocator_context, 0x760, 4, 0x014433f8u,
      unresolved_contracts::pkg18_re_0097e380);
}

Opaque PKG_UTFWIN_THISCALL utfwin_0097e550(Opaque object, Opaque token) {
  return unresolved_contracts::pkg18_re_0097e4a0(object - 0x0cu, token);
}

Opaque PKG_UTFWIN_THISCALL utfwin_0097e890(Opaque, Opaque unused) {
  static_cast<void>(unused);
  return 0x01436b0u;
}

bool PKG_UTFWIN_THISCALL utfwin_0097e990(OpaqueLayout* layout,
                                        const FloatRect* source,
                                        FloatRect* destination) {
  if ((layout->flags & 0x08u) != 0) {
    destination->right =
        destination->right - (source->right - source->left);
  }
  if ((layout->flags & 0x04u) == 0) {
    destination->left =
        destination->left - (source->right - source->left);
  }
  if ((layout->flags & 0x02u) != 0) {
    destination->bottom =
        destination->bottom - (source->bottom - source->top);
  }
  if ((layout->flags & 0x01u) == 0) {
    destination->top =
        destination->top - (source->bottom - source->top);
  }
  return true;
}

void PKG_UTFWIN_THISCALL utfwin_0097ea50(OpaqueLayout* layout,
                                         const FloatRect* source) {
  layout->stored.left = source->left;
  layout->stored.top = source->top;
  layout->stored.right = source->right;
  layout->stored.bottom = source->bottom;
}

void PKG_UTFWIN_THISCALL utfwin_00980120(OpaqueModulateEffect* effect,
                                         OpaqueColorTarget* target,
                                         float amount) {
  const OpaqueColorVtable* vtable = target->vtable;
  using ColorSlot5C = void(PKG_UTFWIN_THISCALL*)(OpaqueColorTarget*, Opaque);
  const Opaque blended = unresolved_contracts::pkg18_re_007f5eb0(
      effect->color_64, effect->color_68, amount);
  const ColorSlot5C slot = copy_function<ColorSlot5C>(vtable->slot_5c);
  slot(target, blended);
}

Opaque PKG_UTFWIN_THISCALL utfwin_00980200(Opaque, Opaque unused) {
  static_cast<void>(unused);
  return 0x01443e4cu;
}

Opaque PKG_UTFWIN_THISCALL utfwin_00980470(Opaque object,
                                            std::uint8_t flags) {
  return unresolved_contracts::pkg18_re_00980490(object - 0x0cu, flags);
}

}
