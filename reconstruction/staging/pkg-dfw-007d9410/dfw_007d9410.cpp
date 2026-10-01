// PKG-DFW-007D9410 -- VA 0x007d9410
// Spore input/camera key handling (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// Machine listing, 2 instructions, body 0x007d9410..0x007d9417 inclusive
// (ghidra_function: body_start 0x007d9410, body_end 0x007d9417, body_span_bytes 8,
// size_bytes 8; disassembly count 2; re-read read-only from the live bridge at
// http://127.0.0.1:8089/disassemble_function?address=0x007d9410 during this
// session). Every line of the model below is annotated with the instruction it
// comes from:
//
//   007d9410  SUB ECX,0x4
//   007d9413  JMP 0x007d9bb0
//
// That is the whole body. There is no prologue, no frame, no saved register, no
// memory operand of any kind, no conditional branch, no comparison, no
// arithmetic other than the four subtracted from the entry register, and no
// second transfer. Four facts follow, and the model asserts exactly these four
// and nothing else:
//
//   1. the entry register's value is reduced by four, unconditionally, before
//      anything else happens;
//   2. control then leaves for 0x007d9bb0 by an unconditional direct jump;
//   3. the stack is not touched: this body has no PUSH, no POP, no ADD ESP and
//      no SUB ESP, so the argument word the caller pushed is still where the
//      caller left it when the target runs, and the target's own terminator is
//      what returns to this frame's caller;
//   4. the word the target leaves in the return register is the word this body
//      returns, because there is no instruction after the jump to change it.
//
// On the transfer and this body not returning itself: the jump is a tail
// transfer (abi_derived.tail_call = {present: true, form: "jmp", target:
// "0x007d9bb0", after_frame_setup: false}), so 0x007d9410 has no terminator of
// its own -- which is why the same derived record abstains from the whole ABI
// with verdict ABI_UNKNOWN and the reason "no_terminal_ret: the only exit
// observed is a tail jump", and why its return.register is null. C++ cannot
// spell a tail transfer, so the line below is an ordinary call whose result is
// returned. The source therefore cannot distinguish a tail jump from a call
// followed by a return, and no claim is made about which one the compiler emits;
// the four facts above are what the listing fixes and what the model carries. The
// one consequence that IS visible at this level -- an argument word crossing the
// transfer without this body re-pushing it -- is modelled as a plain pass-through
// of the caller's word.
//
// On the entry register: the persisted ABI record calls it a hidden receiver in
// ECX ("ECX holds a pointer to the subobject that carries the OnKeyDown virtual;
// the entry rewinds it to the cMouseCamera start"), and the SDK/Ghidra prototype
// stored on the symbol types it `cMouseCamera *`. The derived record disagrees in
// a way the pack records and does not resolve: abi_derived.conclusions R2 reads
// "ECX is never read in any form, so there is no register receiver" at confidence
// OBSERVED, receiver.present is false, receiver.offsets is empty, and the
// envelope's conflicts array carries an unresolved inferred_vs_persisted entry on
// calling_convention. This listing cannot settle that, and it does not have to:
// 0x007d9410 never dereferences the register, so the model only ever does
// four-byte address arithmetic on it. The pointer types stay opaque and
// incomplete; no class, member, size or layout is named anywhere in this package.
//
// The four subtracted are written in decimal below, for the same reason the
// reference package writes 0x80 in decimal: the value is a machine displacement
// on a base that no record names, and spelling it as a hex literal in code would
// read as a claim about a memory operand that this body never forms.

#include "dfw_007d9410_types.hpp"

#include <cstdint>

namespace openspore::reconstruction::pkg_dfw_007d9410 {
namespace {

// 007d9410  SUB ECX,0x4
//
// The instruction's whole content: the entry register's value less four. It is
// spelled as integer arithmetic on the pointer's own numeric value rather than as
// C++ pointer arithmetic, because subtracting four from a pointer that may sit
// anywhere in the address space is undefined behaviour in the source language
// while SUB on a 32-bit register is not, and because the model has to reproduce
// the machine's wraparound for a receiver near zero: 0x00000002 - 4 is
// 0xFFFFFFFE on the machine, and this is the spelling that says so.
//
// The two pointer types are kept apart here and joined only by this cast, which
// is the same place the machine joins them: nothing between the entry and the
// jump gives either value a type, a size or a meaning.
OpaqueReceiver* rewind_entered_receiver(OpaqueEnteredReceiver* entered_receiver) {
  const std::uintptr_t raw = reinterpret_cast<std::uintptr_t>(entered_receiver);
  return reinterpret_cast<OpaqueReceiver*>(raw - 4u);
}

}  // namespace

extern "C" unclassified_in_EAX PKG_DFW_007D9410_THISCALL
mouse_camera_on_key_down_007d9410(OpaqueEnteredReceiver* entered_receiver,
                                  Word argument_word) {
  // 007d9410  SUB ECX,0x4
  //
  // First and only arithmetic in the body. There is no test around it: the
  // listing holds no conditional branch, so a null or near-zero entry register is
  // rewound like any other value and the transfer still happens. That is the one
  // place where a plausible-looking reconstruction goes wrong, so the model test
  // drives the null case explicitly and asserts that the transfer still occurs
  // and that the target receives 0xFFFFFFFC.
  OpaqueReceiver* const receiver = rewind_entered_receiver(entered_receiver);

  // 007d9413  JMP 0x007d9bb0
  //
  // The one transfer, direct, unconditional, and the last instruction in the
  // body. No stack word is pushed here and none is dropped afterwards, so the
  // argument word the caller of 0x007d9410 pushed is the word the target sees --
  // it is forwarded below exactly as it arrived, untouched and in the same slot.
  //
  // The target is not part of this package and nothing about it is asserted
  // beyond the contract the jump itself fixes; the model test supplies it as an
  // observer and decides what it returns, which is how the test can show that
  // this body forwards that word without reinterpreting it.
  return tail_transfer_target_007d9bb0(receiver, argument_word);
}

}  // namespace openspore::reconstruction::pkg_dfw_007d9410
