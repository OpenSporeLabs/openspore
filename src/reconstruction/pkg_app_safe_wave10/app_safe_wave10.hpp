#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG app safe wave10 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_APP_SAFE_WAVE10_CDECL __cdecl
#define PKG_APP_SAFE_WAVE10_THISCALL __thiscall
#else
#define PKG_APP_SAFE_WAVE10_CDECL __attribute__((cdecl))
#define PKG_APP_SAFE_WAVE10_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_app_safe_wave10 {

using TargetWord = std::uint32_t;
using TargetHalf = std::uint16_t;
using TargetByte = std::uint8_t;
using TargetFloat = float;

struct OpaqueVector3 {
  TargetFloat x;
  TargetFloat y;
  TargetFloat z;
};

struct OpaqueCursorElement {
  std::array<TargetByte, 0x18> opaque_00_17;
};

struct OpaqueCursorBuffer {
  TargetWord base;
  TargetWord cursor;
  TargetWord limit;
};

struct OpaquePropertySlot {
  TargetWord stored;
  std::array<TargetByte, 0x0c> opaque_04_0f;
  TargetHalf flags;
  TargetHalf kind;
};

using CopyElement_00511140 = OpaqueCursorElement*(
    PKG_APP_SAFE_WAVE10_THISCALL*)(OpaqueCursorElement * destination,
                                   const OpaqueCursorElement* source);

using GrowAndEmit_00424010 = void(PKG_APP_SAFE_WAVE10_THISCALL*)(
    OpaqueCursorBuffer* buffer, TargetWord cursor, TargetWord argument);

struct CursorRuntime {
  CopyElement_00511140 copy_element_00511140;
  GrowAndEmit_00424010 grow_and_emit_00424010;
};

CursorRuntime& cursor_runtime();

const TargetByte* property_sentinel_015d115d();

extern "C" OpaqueVector3* PKG_APP_SAFE_WAVE10_CDECL
vector3_add_0041dc10(OpaqueVector3* destination, const OpaqueVector3* left,
                     const OpaqueVector3* right);

extern "C" void PKG_APP_SAFE_WAVE10_THISCALL
cursor_buffer_emit_0041e8b0(OpaqueCursorBuffer* buffer, TargetWord argument);

extern "C" const TargetByte* PKG_APP_SAFE_WAVE10_THISCALL
property_value_resolve_0041e920(const OpaquePropertySlot* slot);

static_assert(sizeof(void*) == 4, "pkg-app-safe-wave10 needs 32-bit pointers");
static_assert(sizeof(TargetFloat) == 4,
              "pkg-app-safe-wave10 needs 32-bit floats");
static_assert(sizeof(TargetByte) == 1,
              "pkg-app-safe-wave10 needs one-byte slots");
static_assert(sizeof(OpaqueVector3) == 0x0c, "opaque vector size");
static_assert(sizeof(OpaqueCursorElement) == 0x18,
              "opaque cursor element size");
static_assert(sizeof(OpaqueCursorBuffer) == 0x0c, "opaque cursor buffer size");
static_assert(offsetof(OpaqueCursorBuffer, base) == 0x00,
              "opaque cursor buffer base offset");
static_assert(offsetof(OpaqueCursorBuffer, cursor) == 0x04,
              "opaque cursor buffer cursor offset");
static_assert(offsetof(OpaqueCursorBuffer, limit) == 0x08,
              "opaque cursor buffer limit offset");
static_assert(sizeof(OpaquePropertySlot) == 0x14, "opaque property slot size");
static_assert(offsetof(OpaquePropertySlot, stored) == 0x00,
              "opaque property slot stored offset");
static_assert(offsetof(OpaquePropertySlot, flags) == 0x10,
              "opaque property slot flags offset");
static_assert(offsetof(OpaquePropertySlot, kind) == 0x12,
              "opaque property slot kind offset");

}
