#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-orchestrate-dogfood-0095fa30 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_0095FA30_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_0095FA30_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_0095FA30_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_0095FA30_CDECL __attribute__((cdecl))
#else
#error \
    "pkg-orchestrate-dogfood-0095fa30 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_0095fa30 {

using OpaqueWord = std::uint32_t;

// The live decompilation types the receiver, the stack argument and the written
// slot as IWindow. No concrete class identity is claimed, so the type stays
// opaque and is only used through pointers.
struct OpaqueWindow;

// Receiver of the target function. Offset 0x80 is the only field the body
// touches, and it is written unconditionally. The 0x84 byte extent is a
// modeling bound, not a recovered allocation size.
struct alignas(4) OpaqueWindowLayout {
  std::uint8_t opaque_00[0x80]{};
  OpaqueWindow* opaque_0080 = nullptr;
};

// x86-32 thiscall with the receiver in ECX, one 4-byte stack word at [ESP+4],
// callee cleanup of that word through RET 0x4, and a void return.
using Abi0095fa30 = void(PKG_ORCHESTRATE_DOGFOOD_0095FA30_THISCALL*)(
    OpaqueWindowLayout*, OpaqueWindow*);

struct TargetPorts {
  // The 0x0095fa30 body contains no call instruction, so no port slot is
  // provable from the evidence; the table carries none and stays default null.
};

extern TargetPorts g_dogfood_0095fa30_ports;

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueWord) == 4, "target words are 32-bit");
static_assert(offsetof(OpaqueWindowLayout, opaque_0080) == 0x80,
              "written receiver slot offset from 0x0095fa34");
static_assert(sizeof(OpaqueWindowLayout) == 0x84,
              "modeled window extent through the written slot");
static_assert(sizeof(Abi0095fa30) == 4, "modeled entry slot width");
static_assert(sizeof(TargetPorts) == 1,
              "the proven body installs no port slot");
static_assert(
    std::is_same<Abi0095fa30, void(PKG_ORCHESTRATE_DOGFOOD_0095FA30_THISCALL*)(
                                  OpaqueWindowLayout*, OpaqueWindow*)>::value,
    "modeled entry carries the ECX receiver plus one stack word");

// The SDK parameter name is pChildWindow; the body copies the raw stack word
// into receiver+0x80 without dereferencing it, so the model keeps the argument
// name neutral and claims no child-window semantics.
extern "C" void PKG_ORCHESTRATE_DOGFOOD_0095FA30_THISCALL
utfwin_window_is_ancestor_of_0095fa30(OpaqueWindowLayout* window,
                                      OpaqueWindow* argument);

}

#undef PKG_ORCHESTRATE_DOGFOOD_0095FA30_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_0095FA30_THISCALL
