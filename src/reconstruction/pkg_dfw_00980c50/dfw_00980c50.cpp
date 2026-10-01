// PKG-DFW-00980C50 -- VA 0x00980c50
// UTFWin::RotateEffect::func88h (SPORE/SporeBin/SporeApp.exe, 3.1.0.22,
// binary sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// The complete machine body is two instructions over six bytes, body
// 0x00980c50..0x00980c55 inclusive (ghidra_get_function_by_address:
// body_start 0x00980c50, body_end 0x00980c55, body_span_bytes 6, size_bytes 6;
// ghidra_disassemble_function: 2 instructions; ghidra_read_memory over 16
// bytes: b8 d5 2a 2b cf c3 cc cc cc cc cc cc cc cc cc cc, so the byte after
// the RET is INT3 padding and belongs to no function):
//
//   00980c50  B8 D5 2A 2B CF   MOV EAX,0xcf2b2ad5
//   00980c55  C3               RET
//
// Every line of the model below is annotated with the instruction it comes
// from. There are exactly two instructions and therefore exactly two
// statements.
//
// What the body does not do is most of what there is to say, and each absence
// below is a positive reading of the complete two-instruction listing, not a
// guess:
//
//   * It never reads ECX. The machine-derived ABI record states this itself
//     (inference R2, "ECX is never read in any form, so there is no register
//     receiver"; receiver.present false, receiver.register null,
//     receiver.offsets []), and the corroboration is direct: MOV EAX,imm has
//     no register operand at all. So the SDK method header's RotateEffect
//     receiver cannot influence the result and no subobject offset can be
//     recovered here. The receiver parameter is still declared, because the
//     record says ECX carries one, but the body ignores it.
//   * It never touches memory. The listing contains no memory operand, and the
//     ABI parse consumed both instructions with degraded=false and unparsed=0,
//     so "no memory access" is a statement about the whole body.
//   * It reads no stack word and writes none. Consequently the three `int`
//     parameters the SDK method header declares -- which the ABI record places
//     at ESP+0x08, ESP+0x0c and ESP+0x10 on entry, and each of which it marks
//     "never read" -- cannot influence the result either. The pack's own
//     unresolved questions call those three words most likely artefacts of the
//     SDK method-header generator, and this listing is the evidence for that.
//   * It consults no flag and branches nowhere. The body is straight-line, and
//     the pack lists no conditional branch and no jump. So there is no input
//     that selects one path over another, and no path to be taken.
//   * It transfers control nowhere. abi_derived.dispatch records
//     indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, and the two
//     instructions are a MOV and a RET, so this package declares no callee,
//     no extern, no slot boundary and no dispatch table of any kind.
//
// Terminator and stack discipline. 0x00980c55 is a bare RET: the opcode is C3
// with no immediate, confirmed in the byte dump above. A bare RET pops only the
// return address, so the frame removes no stack argument, and the ABI record
// agrees from its own side (cleanup.bytes 0, cleanup.side "caller",
// ret_form "bare RET at 0x00980c55; the caller pops"). Nothing is pushed
// inside the body either, so the frame's net effect on ESP is zero.
//
// The declaration therefore takes the receiver and no stack argument. Two
// things are being asserted and one is being declined, and the difference
// matters:
//
//   * Asserted: the receiver is in ECX, and the frame pops nothing.
//   * Declined: that a caller of the SDK's three-argument shape is obliged to
//     push three words. A body that reads no stack word cannot show whether
//     its caller pushed anything, and Ghidra's own storage for the receiver
//     (Stack[0x4]) is an artefact of Ghidra not knowing the convention rather
//     than a claim that anything was pushed. The model test therefore drives
//     the reconstruction through the caller shape the ABI record describes --
//     three words pushed, receiver in ECX, `addl $12, %esp` after the call --
//     and asserts that the callee removed none of them, which is the property
//     the bare RET does fix. That is the boundary of what is provable here, and
//     it is stated rather than papered over.
//
// Return register. The only write to EAX in the body is the immediate, so the
// word this function returns is that literal and nothing else can produce
// another. The machine record agrees (return.register EAX, RT1 "the return
// value is carried in EAX", confidence INFERRED).
//
// The SDK and the Ghidra import both spell this return type void, and the
// decompiled body is an empty `return;`. The record registers the disagreement
// as an open question -- "a void-returning SDK placeholder is equally
// consistent with the vtable generator's naming" -- and this model resolves it
// the way the instructions do: the MOV materialises a 32-bit value in EAX, so
// the span returns that word. The void reading is not refuted here, only not
// adopted; a reviewer with vftable context may prefer it.
//
// The model is C++ rather than a copy of the two opcodes. That is a
// deliberate choice for a clean-room reimplementation, and it has a stated
// cost: this translation unit is not claimed to be byte-identical to the
// image, and at -O0 the compiler surrounds the two operations with its own PIC
// sequence and a stack slot. The properties the listing fixes -- the returned
// word, the independence from every input, the absence of any write outside
// the return register, and the empty stack adjustment -- are what the model
// test asserts, and each of them is a property of the reconstructed behaviour
// rather than of the emitted bytes.

#include "dfw_00980c50_types.hpp"

namespace openspore::reconstruction::pkg_dfw_00980c50 {

// 0x00980c50 .. 0x00980c55. `receiver` is deliberately unnamed in this
// definition: the SDK method header gives it a name and a type, the ABI record
// gives it a register, and the listing then does nothing whatsoever with it.
// Naming it here would invite a reader to look for the use that is not there.
//
// The return type is spelled std::uint32_t rather than the Word alias, for the
// reason the header sets out: the validator reads this declaration's return
// type as text and compares it to the persisted record's "std::uint32_t", and
// "Word" would read as a rename.
extern "C" std::uint32_t PKG_DFW_00980C50_THISCALL dfw_00980c50_func88h(
    void *) {
  // 0x00980c50  MOV EAX,0xcf2b2ad5
  //
  // The whole body. An immediate into EAX, with no source register, no memory
  // operand, no flag written and no branch: whatever the receiver held in ECX
  // and whatever the three SDK-header words sat on the stack, neither is
  // consulted and neither is touched. The literal is repeated here rather than
  // referenced through kReturnedWord so that the statement a reader compares
  // against the listing carries the listing's own number; the header constant
  // exists for the test to assert against, and the two must stay equal.
  return 0xcf2b2ad5u;

  // 0x00980c55  RET
  //
  // Bare, with no immediate, and reached from the single statement above with
  // nothing on the stack that this frame had to place. The return falls out of
  // the end of the C++ body, so this instruction has no separate statement;
  // the empty stack adjustment it implies is what the model test measures
  // across a call made with three words pushed.
}

}  // namespace openspore::reconstruction::pkg_dfw_00980c50
