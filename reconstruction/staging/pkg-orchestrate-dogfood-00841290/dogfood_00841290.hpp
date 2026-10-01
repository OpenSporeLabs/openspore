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

// The receiver, as the body actually reaches it. `dispatch_00` is a
// displacement label, not a field name: the machine-derived receiver record for
// 0x00841290 enumerates the two displacements the body was seen using (0x00 and
// 0x3c) with `bounds_only` set, and a set of displacements says where the body
// reached, never which member occupies an offset. The reconstruction body in the
// .cpp therefore addresses the receiver by displacement alone; this struct
// exists so the model test can build a receiver and read it back.
//
// The word at +0x00 is nonetheless known to be a table pointer, and that is a
// machine fact rather than a name: 0x008412a9 loads it, 0x008412ae indexes it at
// +0x3c, and 0x008412bf calls what comes back, so a one-level reading of the
// receiver is refuted by the listing itself and the test below refutes it again.
struct alignas(4) OpaqueFormatParser {
  OpaqueFormatParserVtable* dispatch_00;
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
static_assert(offsetof(OpaqueFormatParser, dispatch_00) == 0x00,
              "receiver dispatch word offset, read at 0x008412a9");
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
