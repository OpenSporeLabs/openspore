#include "utfwin_effects_wave6.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_utfwin_effects_wave6 {
namespace {

using namespace openspore::reconstruction::pkg_utfwin_effects_wave6;

namespace unresolved_contracts {

extern "C" Opaque PKG_UTFWIN_CDECL pkg18_re_009512c0();
extern "C" Opaque* PKG_UTFWIN_CDECL pkg18_re_009512d0(Opaque size,
                                                      Opaque alignment,
                                                      const char* name,
                                                      Opaque allocator);
extern "C" void PKG_UTFWIN_THISCALL pkg18_re_0096fe30(Opaque* object);
extern "C" Opaque* PKG_UTFWIN_THISCALL pkg18_re_0097e380(Opaque* object);
extern "C" Opaque PKG_UTFWIN_THISCALL pkg18_re_0097e4a0(Opaque object,
                                                        Opaque token);
extern "C" Opaque PKG_UTFWIN_CDECL pkg18_re_007f5eb0(Opaque from, Opaque to,
                                                     float amount);
extern "C" Opaque PKG_UTFWIN_THISCALL pkg18_re_00980490(Opaque object,
                                                        std::uint8_t flags);

}

template <typename To, typename From>
To copy_function(From function) {
  static_assert(sizeof(To) == sizeof(From), "function pointer width mismatch");
  To result{};
  std::memcpy(&result, &function, sizeof(result));
  return result;
}

float load_float(const FloatRect* rectangle, std::size_t offset) {
  const auto* field = reinterpret_cast<const volatile float*>(
      reinterpret_cast<const unsigned char*>(rectangle) + offset);
  return *field;
}

void store_float(FloatRect* rectangle, std::size_t offset, float value) {
  auto* field = reinterpret_cast<volatile float*>(
      reinterpret_cast<unsigned char*>(rectangle) + offset);
  *field = value;
}

template <typename Constructor>
Opaque* create_factory_object(Opaque allocator_context, Opaque size,
                              Opaque alignment, Opaque name,
                              Constructor constructor) {
  Opaque context = allocator_context;
  if (context == 0) {
    context = unresolved_contracts::pkg18_re_009512c0();
  }
  const char* type_name =
      reinterpret_cast<const char*>(static_cast<std::uintptr_t>(name));
  Opaque* object = unresolved_contracts::pkg18_re_009512d0(size, alignment,
                                                           type_name, context);
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
  return create_factory_object(allocator_context, 0x60, 4, 0x014424f4u,
                               unresolved_contracts::pkg18_re_0096fe30);
}

Opaque PKG_UTFWIN_THISCALL utfwin_0096ffc0(Opaque, Opaque unused) {
  static_cast<void>(unused);
  return 0x01442694u;
}

Opaque* PKG_UTFWIN_THISCALL utfwin_0097e440(Opaque, Opaque unused,
                                            Opaque allocator_context) {
  static_cast<void>(unused);
  return create_factory_object(allocator_context, 0x760, 4, 0x014433f8u,
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
    const float delta = load_float(source, 0x08) - load_float(source, 0x00);
    store_float(destination, 0x08, load_float(destination, 0x08) - delta);
  }
  if ((layout->flags & 0x04u) == 0) {
    const float delta = load_float(source, 0x08) - load_float(source, 0x00);
    store_float(destination, 0x00, load_float(destination, 0x00) - delta);
  }
  if ((layout->flags & 0x02u) != 0) {
    const float delta = load_float(source, 0x0c) - load_float(source, 0x04);
    store_float(destination, 0x0c, load_float(destination, 0x0c) - delta);
  }
  if ((layout->flags & 0x01u) == 0) {
    const float delta = load_float(source, 0x0c) - load_float(source, 0x04);
    store_float(destination, 0x04, load_float(destination, 0x04) - delta);
  }
  return true;
}

void PKG_UTFWIN_THISCALL utfwin_0097ea50(OpaqueLayout* layout,
                                         const FloatRect* source) {
  const float left = load_float(source, 0x00);
  store_float(&layout->stored, 0x00, left);
  const float top = load_float(source, 0x04);
  store_float(&layout->stored, 0x04, top);
  const float right = load_float(source, 0x08);
  store_float(&layout->stored, 0x08, right);
  const float bottom = load_float(source, 0x0c);
  store_float(&layout->stored, 0x0c, bottom);
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

Opaque PKG_UTFWIN_THISCALL utfwin_00980470(Opaque object, std::uint8_t flags) {
  return unresolved_contracts::pkg18_re_00980490(object - 0x0cu, flags);
}

}
