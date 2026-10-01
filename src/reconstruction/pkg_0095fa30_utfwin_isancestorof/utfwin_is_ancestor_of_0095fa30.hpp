#pragma once

// Reconstruction of UTFWin::Window::IsAncestorOf @ 0x0095fa30 (SporeApp.exe
// 3.1.0.22, binary sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// Evidence basis (all from the live Ghidra bridge on SporeApp.exe, and all
// re-read for this package):
//   * disassembly 0x0095fa30..0x0095fa3c - exactly three instructions:
//       0x0095fa30  8b 44 24 04            MOV EAX,dword ptr [ESP + 0x4]
//       0x0095fa34  89 81 80 00 00 00      MOV dword ptr [ECX + 0x80],EAX
//       0x0095fa3a  c2 04 00               RET 0x4
//     raw bytes 0x0095fa30: 8b 44 24 04 89 81 80 00 00 00 c2 04 00
//   * decompilation UTFWin__Window__IsAncestorOf.c, which carries the SDK
//     signature `bool UTFWin__Window__IsAncestorOf(IWindow *this,
//     IWindow *pChildWindow)` and renders the single store as
//     `*(IWindow **)(in_ECX + 0x80) = this` (Ghidra binds the wrong formal to
//     the store because the convention is unknown to it; the disassembly is
//     authoritative about which register holds which value).
//   * 33 references to 0x0095fa30, every one a DATA pointer and never a CALL
//     site: this method is only ever reached through virtual dispatch. At each
//     reference address R the four consecutive vtable words read
//     [R]=0x0095fa30, [R+4]=0x0095fd60 (SDK label UTFWin::Window::func35),
//     [R+8]=0x0095fdc0, [R+0xc]=0x0095fe40 - verified by reading memory at
//     0x013fdb6c, 0x01414c14, 0x014195dc, 0x01479314 and 0x0144324c.
//
// The only receiver displacement this body touches is +0x80, and it is written
// unconditionally. Nothing outside the disassembly is asserted: the receiver's
// own vtable pointer is never read here, so the window extent below stops at
// the written slot.
//
// WHAT THE EVIDENCE DOES AND DOES NOT CARRY ABOUT THAT SLOT: the machine proves
// a width (4 bytes, `dword`) and a displacement (0x80, under ECX) and a mode
// (write, unconditional, the value copied verbatim from [ESP+4]). It does not
// prove which member of any type occupies that word, and nothing in this
// package's evidence pack names one. So `OpaqueWindow` below declares no member
// at all - not `field_80`, not a pointer, not a parent pointer - and the
// receiver is reached only through the `word_at` displacement accessor. The
// SDK decompilation renders the same store as `*(IWindow **)(in_ECX + 0x80)`;
// that is a decompiler's cast over an opaque base, and importing its member
// story would be importing a claim the disassembly does not make.

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "UTFWin IsAncestorOf 0x0095fa30 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_0095FA30_THISCALL __thiscall
#else
#define PKG_0095FA30_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_0095fa30_utfwin_isancestorof {

using Opaque = std::uint32_t;

struct OpaqueWindow;

// The vtable image this method was observed in, described as a standalone
// table and NOT embedded in OpaqueWindow: the 0x0095fa30 body never reads
// [ECX+0x00], so no vtable pointer field is claimed on the receiver. Slot
// displacements are relative to the reference address R (the image base this
// package verified by reading memory), and the four slot words are the values
// read out of the image.
struct OpaqueWindowVTable {
  Opaque slot_00_is_ancestor_of = 0x0095fa30u;  // R + 0x00, this method
  Opaque slot_04_func35 = 0x0095fd60u;          // R + 0x04, SDK label func35
  Opaque slot_08 = 0x0095fdc0u;                // R + 0x08
  Opaque slot_0c = 0x0095fe40u;                // R + 0x0c
};

// Receiver of the target function, modelled at exactly the width the machine
// read and no more: 0x84 bytes, 4-byte aligned, i.e. the prefix through the one
// word the body writes. 0x00..0x7f is never read or written by the body, and
// 0x80..0x83 is the word 0x0095fa34 overwrites. No member is declared, because
// no evidence in this package names one; the extent is a modelling bound, not a
// recovered allocation size.
struct alignas(4) OpaqueWindow {
  std::array<std::uint8_t, 0x84> opaque_bytes{};  // 0x00..0x83
};

// The displacement the body was observed reaching on the receiver, from
// `MOV dword ptr [ECX + 0x80],EAX` at 0x0095fa34. It is a value, not a member:
// the record enumerates displacements and cannot say which member is which.
constexpr std::size_t kSlotDisplacement = 0x80;

// The only way this package touches the receiver: a 4-byte word at a stated
// displacement. Naming a member instead would assert an identity the receiver
// record (offsets=[0x80], bounds_only) cannot corroborate.
inline Opaque* word_at(OpaqueWindow* window, std::size_t displacement) {
  return reinterpret_cast<Opaque*>(reinterpret_cast<std::uintptr_t>(window) +
                                   displacement);
}

inline Opaque word_at(const OpaqueWindow* window, std::size_t displacement) {
  return *reinterpret_cast<const Opaque*>(
      reinterpret_cast<std::uintptr_t>(window) + displacement);
}

inline Opaque as_word(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

// x86-32 thiscall: receiver in ECX, one ordinary 4-byte stack word at [ESP+4]
// read once and never dereferenced, callee cleanup of that word through
// RET 0x4, and a void return (see return_type_rationale in the sidecar: the
// machine writes no result into EAX after the load).
using AbiIsAncestorOf0095fa30 = void(PKG_0095FA30_THISCALL*)(OpaqueWindow*,
                                                             OpaqueWindow*);

static_assert(sizeof(void*) == 4, "UTFWin pointers are 32-bit");
static_assert(sizeof(Opaque) == 4, "UTFWin opaque words are 32-bit");
static_assert(sizeof(OpaqueWindow) == 0x84,
              "modeled window extent through the written slot");
static_assert(offsetof(OpaqueWindow, opaque_bytes) == 0,
              "the receiver's first byte is its base");
static_assert(kSlotDisplacement + sizeof(Opaque) == sizeof(OpaqueWindow),
              "the only displacement the body reaches ends the modeled extent");
static_assert(sizeof(OpaqueWindowVTable) == 0x10,
              "four consecutive vtable words were read at the reference");
static_assert(
    std::is_same<AbiIsAncestorOf0095fa30,
                 void(PKG_0095FA30_THISCALL*)(OpaqueWindow*,
                                              OpaqueWindow*)>::value,
    "modeled entry carries the ECX receiver plus one stack word");

// Entry point under reconstruction. The name carries the record's last `::`
// component (IsAncestorOf -> is, ancestor, of) plus the 8-hex target VA so the
// validator can bind this span to 0x0095fa30.
void PKG_0095FA30_THISCALL is_ancestor_of_0095fa30(OpaqueWindow* window,
                                                   OpaqueWindow* argument);

}

#undef PKG_0095FA30_THISCALL
