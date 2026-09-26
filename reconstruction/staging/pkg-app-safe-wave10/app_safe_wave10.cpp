#include "app_safe_wave10.hpp"

namespace openspore::reconstruction::pkg_app_safe_wave10 {
namespace {

constexpr TargetWord kElementStride = 0x18u;
constexpr TargetHalf kPropertyStorageMask = 0x0030u;
constexpr TargetHalf kPropertyKindBool = 0x0001u;
constexpr TargetHalf kPropertyKindVoid = 0x0010u;
constexpr std::uintptr_t kPropertySentinel = 0x015d115du;

OpaqueCursorElement *PKG_APP_SAFE_WAVE10_THISCALL default_copy_element_00511140(
    OpaqueCursorElement *, const OpaqueCursorElement *) {
  return nullptr;
}

void PKG_APP_SAFE_WAVE10_THISCALL
default_grow_and_emit_00424010(OpaqueCursorBuffer *, TargetWord, TargetWord) {
}

}

CursorRuntime &cursor_runtime() {
  static CursorRuntime runtime{default_copy_element_00511140,
                               default_grow_and_emit_00424010};
  return runtime;
}

const TargetByte *property_sentinel_015d115d() {
  return reinterpret_cast<const TargetByte *>(kPropertySentinel);
}

OpaqueVector3 *vector3_add_0041dc10(OpaqueVector3 *destination,
                                    const OpaqueVector3 *left,
                                    const OpaqueVector3 *right) {
  const TargetFloat sum_x = left->x + right->x;
  const TargetFloat sum_y = left->y + right->y;
  const TargetFloat sum_z = left->z + right->z;
  destination->x = sum_x;
  destination->y = sum_y;
  destination->z = sum_z;
  return destination;
}

void cursor_buffer_emit_0041e8b0(OpaqueCursorBuffer *buffer,
                                 TargetWord argument) {
  if (buffer->cursor < buffer->limit) {
    const TargetWord saved = buffer->cursor;
    buffer->cursor = saved + kElementStride;
    if (saved != 0u) {
      auto *const destination = reinterpret_cast<OpaqueCursorElement *>(
          static_cast<std::uintptr_t>(saved));
      auto *const source = reinterpret_cast<const OpaqueCursorElement *>(
          static_cast<std::uintptr_t>(argument));
      cursor_runtime().copy_element_00511140(destination, source);
    }
  } else {
    cursor_runtime().grow_and_emit_00424010(buffer, buffer->cursor, argument);
  }
}

const TargetByte *property_value_resolve_0041e920(
    const OpaquePropertySlot *slot) {
  const TargetHalf kind = slot->kind;
  if (kind != kPropertyKindBool && kind != kPropertyKindVoid) {
    return property_sentinel_015d115d();
  }
  if ((slot->flags & kPropertyStorageMask) != 0u) {
    return reinterpret_cast<const TargetByte *>(
        static_cast<std::uintptr_t>(slot->stored));
  }
  if (kind != 0u) {
    return reinterpret_cast<const TargetByte *>(
        reinterpret_cast<std::uintptr_t>(slot));
  }
  return nullptr;
}

}
