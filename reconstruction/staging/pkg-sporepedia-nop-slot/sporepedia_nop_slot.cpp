// PKG-SPOREPEDIA-NOP-SLOT -- VA 0x00c2e4e0
// Sporepedia cluster (SPORE/SporeBin/SporeApp.exe, 3.1.0.22, x86-32)
//
// Machine listing, 1 instruction, body 0x00c2e4e0..0x00c2e4e0 inclusive
// (Ghidra body_end 0x00c2e4e0, body_span_bytes 1):
//
//   00c2e4e0  RET
//
// That single line is the whole of the body, and every fact below is read off
// it. There is no second instruction to annotate.
//
// ABI, machine-derived: __thiscall. Rule V1-VFT fired on this target: the
// address is the value of slot 12 of the vptr-backed vftable at 0x013f69b4
// (predicate P over the PE image: a maximal run of code pointers in .rdata
// stored into an object word by a constructor), so the function is a non-static
// virtual member of some class; the terminator is a bare RET, so the callee
// pops nothing; and no stack word is read as an argument. The only remaining
// place a receiver can arrive on x86-32 MSVC is a register, and of the two
// register-carrying conventions only ECX carries a receiver. The membership is
// established over 479 tables -- identical-code folding collapses every no-op
// virtual member onto this address -- so the class is deliberately not named:
// "a virtual member of some class" is the whole of what the evidence says.
//
// Return, machine-derived: void. The complete 1-instruction listing writes EAX
// on no path before the single reachable return, and the body makes no call
// that could clobber it, so the machine return state is VOID_PROVEN. The
// declaration states void, which is the width the machine proves and nothing
// more: whatever the caller left in EAX is not a value this body produces, and
// no record classifies it.
//
// The receiver arrives in ECX and is never read. The body performs no memory
// operand at all -- no displacement through ECX or any other register, no
// data-segment address, no immediate -- so the receiver parameter below is
// declared because the convention requires it and unused because the listing
// shows no use. No member name appears anywhere in this package: the
// machine-derived receiver record is bounds_only with an empty offset set,
// which states where a body was seen reaching, and this body was seen reaching
// nowhere.
//
// Transfers: none. The body names no callee, direct or indirect, and the xref
// export records no outgoing call edge for this address. Control flow: none.
// The single RET is unconditional and the body is straight-line. Constants:
// none -- the listing carries no hexadecimal literal, and this source span
// states none, so there is no displacement constant to pin and no static_assert
// in this package ties a constant to an instruction address: there is no
// constant in the body to tie.
//
// The empty body below is the literal model of the listing. A bare RET does
// nothing and returns; an empty body does nothing and returns. Nothing here
// is invented to fill the space the single instruction leaves.

#include "sporepedia_nop_slot.hpp"

namespace openspore::reconstruction::pkg_sporepedia_nop_slot {

extern "C" void PKG_SPOREPEDIA_NOP_SLOT_THISCALL sporepedia_nop_slot_FUN_00c2e4e0([[maybe_unused]] void *receiver) {
}

}  // namespace openspore::reconstruction::pkg_sporepedia_nop_slot
