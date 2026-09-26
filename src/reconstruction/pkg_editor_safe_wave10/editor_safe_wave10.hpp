#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-editor-safe-wave10 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_EDITOR_SAFE_THISCALL __thiscall
#else
#define PKG_EDITOR_SAFE_THISCALL __attribute__((thiscall))
#endif

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif

namespace openspore::reconstruction::pkg_editor_safe_wave10 {

using Word = std::uint32_t;
using Real = float;

static_assert(sizeof(void*) == 4, "x86-32 pointers are four bytes");
static_assert(sizeof(Word) == 4, "target words are four bytes");
static_assert(sizeof(Real) == 4, "target row components are 32-bit floats");

struct OpaqueRowPublisher {
  std::uint8_t opaque_00_73[0x74]{};
  Real row_prev_74 = 0.0f;
  Real row_prev_78 = 0.0f;
  Real row_prev_7c = 0.0f;
  Real row_next_80 = 0.0f;
  Real row_next_84 = 0.0f;
  Real row_next_88 = 0.0f;
};

static_assert(offsetof(OpaqueRowPublisher, opaque_00_73) == 0x00,
              "opaque prefix starts at +0x00");
static_assert(offsetof(OpaqueRowPublisher, row_prev_74) == 0x74,
              "mirrored row first component at +0x74");
static_assert(offsetof(OpaqueRowPublisher, row_prev_78) == 0x78,
              "mirrored row second component at +0x78");
static_assert(offsetof(OpaqueRowPublisher, row_prev_7c) == 0x7c,
              "mirrored row third component at +0x7c");
static_assert(offsetof(OpaqueRowPublisher, row_next_80) == 0x80,
              "primary row first component at +0x80");
static_assert(offsetof(OpaqueRowPublisher, row_next_84) == 0x84,
              "primary row second component at +0x84");
static_assert(offsetof(OpaqueRowPublisher, row_next_88) == 0x88,
              "primary row third component at +0x88");
static_assert(sizeof(OpaqueRowPublisher) == 0x8c,
              "publisher observed extent ends after +0x88");

void PKG_EDITOR_SAFE_THISCALL
editor_row_publish_005a2010(OpaqueRowPublisher* self, Real row_x, Real row_y,
                            Real row_z, Word also_previous);

}

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif

#undef PKG_EDITOR_SAFE_THISCALL
