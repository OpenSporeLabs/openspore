// 0x00980480 -- UTFWin::PerspectiveEffect::HandleUIMessage
//
// Complete machine body at 0x00980480, two instructions, eight bytes, no
// branch, no memory reference (ghidra_disassemble_function 0x00980480):
//
//   00980480  83 e9 04        SUB ECX, 0x4
//   00980483  e9 a8 fe ff ff  JMP 0x00980330
//
// That is a cross-vtable `this`-adjusting thunk. The receiver arrives in ECX
// pointing at a secondary base of the most-derived object; SUB ECX, 0x4 undoes
// the multiple-inheritance offset so ECX becomes the primary object pointer,
// and the following JMP transfers control without touching EAX, EDX, the flags
// or the stack, so the callee sees the same single stack word and the same
// register state the caller set up.
//
// Why the adjustment is 0x4 and not 0x0c: the SDK symbol table lays
// UTFWin::PerspectiveEffect out as SIZE 0x14 with its two secondary interface
// sub-objects at +0x04 (ILayoutElement) and +0x0c (IPerspectiveEffect), and the
// sibling thunk at 0x00980470 -- reconstructed in PKG-UTFWIN-EFFECTS-WAVE6 --
// subtracts 0x0c, the other secondary base. The two thunks are the same
// virtual reached through two different base sub-objects, which is what the two
// independently located uses of this address in .rdata are consistent with.
//
// Tail callee 0x00980330, complete body, eleven instructions:
// the incoming stack word is compared against 0xef865d7e; on a match it returns
// the primary receiver plus 0x0c (or 0 when the receiver is null), and on any
// other value it forwards the unchanged receiver and stack word to 0x00950eb0.
// Both constants and both returns are recorded in the test model, not guessed:
// 0xef865d7e has no entry in the SDK ObjectTYPE enum, while 0x00950eb0's three
// immediates do (0x2f009dd0 = UTFWin::IWinProc, 0xee3f516e = Object,
// 0xeec58382 = UTFWin::ILayoutElement) and it returns the primary receiver plus
// 0x04 for the latter two. The SDK enum is not injective -- 0xeec58382 is also
// published for UTFWin::Window and 0xef2b293b for IGlideEffect,
// IPerspectiveEffect and IRotateEffect alike -- so those three names are an
// observation about the constant family, not a proven identification.
//
// Two ABI facts are deliberately NOT claimed here and are recorded in the
// sidecar and in unresolved_questions instead. The SDK documents this virtual as
// `bool HandleUIMessage(IWindow *pWindow, Message *message)`, but the tail callee
// pops a single stack word (`RET 0x4` at both 0x0098034b and 0x00980350), so the
// modelled arity follows the machine, not the documentation. And the machine
// materialises a pointer or null in EAX (`LEA EAX,[ECX+0x0c]`, `XOR EAX,EAX`)
// and never a normalised byte, so the entry point is modelled as returning a
// pointer while the SDK label says bool.

#ifndef PKG_PERSPECTIVE_THISCALL
#if defined(_MSC_VER)
#define PKG_PERSPECTIVE_THISCALL __thiscall
#else
#define PKG_PERSPECTIVE_THISCALL __attribute__((thiscall))
#endif
#endif

#include "utfwin_perspective_wave12.hpp"

namespace openspore::reconstruction::pkg_utfwin_perspective_wave12 {

// 0x00980330 is the tail-transfer target of this package's entry point. It is a
// different target VA and is not claimed here: only its contract is declared,
// and the focused test supplies the stand-in that lets the forwarding behaviour
// be exercised.
namespace unresolved_contracts {

extern "C" Opaque* PKG_PERSPECTIVE_THISCALL dispatch_00980330(
    Opaque* primary_object, Opaque message_word);

}

Opaque* PKG_PERSPECTIVE_THISCALL handle_message_00980480(
    Opaque* layout_element_subobject, Opaque message_word) {
  // SUB ECX, 0x4 is byte arithmetic on the address, not element arithmetic on
  // the pointed-to word, so the adjustment is done through a byte view. Getting
  // this wrong silently moves the receiver by 0x10 instead of 0x4.
  Opaque* primary_object = reinterpret_cast<Opaque*>(
      reinterpret_cast<unsigned char*>(layout_element_subobject) - 0x4);
  return unresolved_contracts::dispatch_00980330(primary_object, message_word);
}

}
