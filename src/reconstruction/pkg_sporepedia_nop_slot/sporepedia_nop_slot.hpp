// PKG-SPOREPEDIA-NOP-SLOT -- VA 0x00c2e4e0
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22, x86-32)
//
// Declaration for the reconstruction of FUN_00c2e4e0.
//
// The machine body is a single instruction, a bare RET at 0x00c2e4e0. The
// ABI is __thiscall, derived by rule V1-VFT: 0x00c2e4e0 is the value of slot
// 12 of the vptr-backed vftable at 0x013f69b4, the callee pops nothing, and
// no stack word is read as an argument, so the receiver arrives in ECX and
// the caller owns the stack. The membership is established over 479 tables:
// identical-code folding collapses every no-op virtual member in this image
// onto this one address, so "a virtual member of some class" is all the
// evidence supports and no class name is claimed here.
//
// The return is void. The complete 1-instruction listing writes EAX on no
// path before the single reachable return and no call can clobber it, so the
// machine return state is VOID_PROVEN and the declaration below states
// exactly that: the body produces no value.
//
// The receiver is declared and named because the convention puts it in ECX;
// the body never reads it, which the definition states by never using it.

#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-sporepedia-nop-slot requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_SPOREPEDIA_NOP_SLOT_THISCALL __thiscall
#else
#define PKG_SPOREPEDIA_NOP_SLOT_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_sporepedia_nop_slot {

extern "C" void PKG_SPOREPEDIA_NOP_SLOT_THISCALL sporepedia_nop_slot_FUN_00c2e4e0(void *receiver);

}  // namespace openspore::reconstruction::pkg_sporepedia_nop_slot
