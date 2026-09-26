#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-argscript-wave9 requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "target words are 32-bit");

#if defined(_MSC_VER)
#define PKG_ARGSCRIPT_WAVE9_THIS_CALL __thiscall
#else
#define PKG_ARGSCRIPT_WAVE9_THIS_CALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_argscript_wave9 {

struct OpaqueString {
  char* begin = nullptr;
  char* end = nullptr;
  char* capacity = nullptr;
  void* allocator = nullptr;
};

struct OpaqueLine {
  std::array<std::uint8_t, 0x44> bytes{};
};

struct OpaqueFormatParser {
  std::array<std::uint8_t, 0x130> field_000{};
  OpaqueString field_130{};
  std::array<std::uint8_t, 0x14> field_140{};
  OpaqueString field_154{};
  std::uint8_t field_164 = 0;
  std::array<std::uint8_t, 3> field_165{};
  std::uint32_t field_168 = 0;
  OpaqueLine field_16c{};
  OpaqueString field_1b0{};
};

static_assert(sizeof(OpaqueString) == 0x10, "opaque string width");
static_assert(sizeof(OpaqueLine) == 0x44, "opaque line width");
static_assert(sizeof(OpaqueFormatParser) == 0x1c0, "opaque parser width");
static_assert(offsetof(OpaqueFormatParser, field_130) == 0x130,
              "scope field offset");
static_assert(offsetof(OpaqueFormatParser, field_140) == 0x140,
              "scope tail offset");
static_assert(offsetof(OpaqueFormatParser, field_154) == 0x154,
              "secondary string offset");
static_assert(offsetof(OpaqueFormatParser, field_164) == 0x164,
              "state byte offset");
static_assert(offsetof(OpaqueFormatParser, field_168) == 0x168,
              "state word offset");
static_assert(offsetof(OpaqueFormatParser, field_16c) == 0x16c, "line offset");
static_assert(offsetof(OpaqueFormatParser, field_1b0) == 0x1b0,
              "tail string offset");

char* PKG_ARGSCRIPT_WAVE9_THIS_CALL
pkg_argscript_get_current_scope_00d1dcd0(OpaqueFormatParser* parser);

}

#undef PKG_ARGSCRIPT_WAVE9_THIS_CALL
