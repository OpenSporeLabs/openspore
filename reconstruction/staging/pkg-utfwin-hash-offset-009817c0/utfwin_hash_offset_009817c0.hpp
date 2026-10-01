#pragma once

#include <cstddef>
#include <cstdint>

// 0x009817c0 reads ECX before any write and terminates with "RET 0x4", so the
// callee pops exactly one 4-byte stack word. That is __thiscall
// receiver-in-ECX with callee-owned cleanup of a single stack word: cdecl and
// fastcall are both excluded by the RET 0x4 immediate, and stdcall is excluded
// by the receiver register.
#if defined(_MSC_VER)
#define PKG_UTFWIN_HASH_OFFSET_THISCALL __thiscall
#else
#define PKG_UTFWIN_HASH_OFFSET_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_utfwin_hash_offset_009817c0 {

// The observed body only ever performs TEST on the receiver and LEA on it. It
// never dereferences a typed field, so the receiver stays an opaque address and
// no field type is asserted anywhere in this package.
using OpaqueReceiver = void*;

// The second input is compared against four 32-bit magic values and is never
// masked, widened, or used as an index. It is a 32-bit comparison key.
using HashWord = std::uint32_t;

// Hash keys proven by CMP immediates in the observed bodies. These are raw
// comparison constants read out of the instruction stream, not derived values.
inline constexpr HashWord kHash_6ec581fd = 0x6ec581fdu;
inline constexpr HashWord kHash_ee3f516e = 0xee3f516eu;
inline constexpr HashWord kHash_eec58382 = 0xeec58382u;
inline constexpr HashWord kHash_eef3af8cu = 0xeef3af8cu;

// Member byte offsets proven by the LEA displacements of the observed bodies.
inline constexpr std::ptrdiff_t kOffset_00 = 0x00;
inline constexpr std::ptrdiff_t kOffset_04 = 0x04;
inline constexpr std::ptrdiff_t kOffset_0c = 0x0c;

// 0x00951240, the tail-call target of 0x009817c0. Modelled because the JMP at
// 0x009817d6 reaches it with the receiver in ECX and the hash still in the
// incoming stack slot, so the reachable behaviour of this target depends on it.
extern "C" void* PKG_UTFWIN_HASH_OFFSET_THISCALL
sibling_hash_offset_00951240(OpaqueReceiver self, HashWord hash);

// 0x009817c0, 52 bytes, body 0x009817c0..0x009817f3 inclusive.
//
// NOTE ON THE NAME. "set_image_009817c0" is the binding label required by the
// reconstruction queue record, whose target name is
// "UTFWin::ScrollbarDrawable::SetImage". The observed body is NOT a setter and
// does NOT take an image pointer: it returns a pointer, takes a single 32-bit
// comparison key, and never writes to the receiver. The SDK label is recorded
// as a contradiction in the metadata sidecar; the behaviour modelled here is
// the behaviour the machine actually has.
extern "C" void* PKG_UTFWIN_HASH_OFFSET_THISCALL
set_image_009817c0(OpaqueReceiver self, HashWord hash);

}  // namespace openspore::reconstruction::pkg_utfwin_hash_offset_009817c0
