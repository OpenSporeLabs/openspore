#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-orchestrate-dogfood-00841290 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_00841290_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_00841290_CDECL __attribute__((cdecl))
#else
#error "pkg-orchestrate-dogfood-00841290 needs MSVC or GCC CC macros"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_00841290 {

using OpaqueWord = std::uint32_t;

struct OpaqueFormatParserVtable;

struct alignas(4) OpaqueFormatParser {
  OpaqueFormatParserVtable* vtable;
};

using FormatParserReleaseSlot3c =
    OpaqueWord(PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL*)(OpaqueFormatParser*,
                                                           OpaqueWord);

struct alignas(4) OpaqueFormatParserVtable {
  std::uintptr_t slots_00[15]{};
  FormatParserReleaseSlot3c release_3c = nullptr;
};

struct OpaqueReleasePorts {
  FormatParserReleaseSlot3c release_3c = nullptr;
};

static constexpr OpaqueWord vtable_0141c930 = 0x0141c930u;
static constexpr OpaqueWord vtable_0141c97c = 0x0141c97cu;

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueWord) == 4, "target words are 32-bit");
static_assert(offsetof(OpaqueFormatParser, vtable) == 0x00,
              "receiver vtable word offset");
static_assert(sizeof(OpaqueFormatParser) == 4,
              "only the vtable word at +0x00 is read by the body");
static_assert(offsetof(OpaqueFormatParserVtable, release_3c) == 0x3c,
              "indirect dispatch slot offset");
static_assert(sizeof(OpaqueFormatParserVtable) == 0x40,
              "modeled vtable prefix extent ends after the +0x3c slot");
static_assert(0x3c / sizeof(std::uintptr_t) == 15u,
              "dispatch slot is vtable index 15");
static_assert(sizeof(FormatParserReleaseSlot3c) == 4,
              "vtable slot width is one 32-bit pointer");
static_assert(sizeof(OpaqueReleasePorts) == 4, "single default-null port");
static_assert(
    std::is_same<FormatParserReleaseSlot3c,
                 OpaqueWord(PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL*)(
                     OpaqueFormatParser*, OpaqueWord)>::value,
    "release slot keeps this in ECX and one four-byte stack word");

extern OpaqueReleasePorts g_dogfood_00841290_ports;

extern "C" bool PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL
argscript_formatparser_release_00841290(OpaqueFormatParser* parser,
                                        OpaqueWord argument_08);

}

#undef PKG_ORCHESTRATE_DOGFOOD_00841290_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_00841290_THISCALL
