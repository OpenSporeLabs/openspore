#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "UTFWin CascadeEffect 0x009672d0 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_UTFWIN_CASCADE_THISCALL __thiscall
#else
#define PKG_UTFWIN_CASCADE_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_utfwin_cascade_009672d0 {

using Opaque = std::uintptr_t;

// ObjectTYPE words tested by the 0x009672d0 / 0x00950eb0 cross-cast pair.
// Every name and value below is taken verbatim from the SDK symbol table that
// the analysis project imports (SporeGhidra_march2017.xml, ENUM_ENTRY records):
//   0x6f90a535 -> "UTFWin::ICascadeEffect"
//   0x2f009dd0 -> "UTFWin::IWinProc"
//   0xee3f516e -> "Object"
//   0xeec58382 -> "UTFWin::ILayoutElement" (the same word also carries
//                 "UTFWin::Window", so the two labels are not separable here)
// Only these four words are declared: they are the only ones either function
// tests, and the SDK spells the rest of the enum in domains this package does
// not model.
inline constexpr Opaque kObjectTypeICascadeEffect = 0x6f90a535u;
inline constexpr Opaque kObjectTypeIWinProc = 0x2f009dd0u;
inline constexpr Opaque kObjectTypeObject = 0xee3f516eu;
inline constexpr Opaque kObjectTypeILayoutElement = 0xeec58382u;

// Receiver for both halves of the pair. The machine never dereferences it: it
// only tests it for null and adds 0x0, 0x4 or 0xc to it, so its size and its
// fields stay unresolved and only the address arithmetic is modelled.
struct CascadeEffectReceiver;

// The 0x009672d0 slot signature as an indirect-call projection. One explicit
// object word in ECX, one 4-byte stack word, caller cleanup of 4 bytes.
using Abi009672d0 = Opaque*(PKG_UTFWIN_CASCADE_THISCALL*)(Opaque, Opaque);

// Tail target reached by the JMP at 0x009672df, same shape and same cleanup.
using Abi00950eb0 = Opaque*(PKG_UTFWIN_CASCADE_THISCALL*)(Opaque, Opaque);

Opaque* PKG_UTFWIN_CASCADE_THISCALL handle_message_009672d0(Opaque object,
                                                            Opaque type);

}

#undef PKG_UTFWIN_CASCADE_THISCALL
