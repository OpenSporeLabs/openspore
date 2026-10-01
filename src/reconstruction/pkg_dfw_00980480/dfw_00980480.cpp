// PKG-DFW-00980480 -- VA 0x00980480
// UTFWin subsystem (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete machine body is two instructions, eight bytes, body span
// 0x00980480..0x00980487 (Ghidra body_start 0x00980480, body_end 0x00980487,
// body_span_bytes 8, size_bytes 8). Re-read from the binary through the live
// bridge this session; the raw bytes are 83 e9 04 e9 a8 fe ff ff.
//
//   00980480  83 e9 04        SUB ECX, 0x4
//   00980483  e9 a8 fe ff ff  JMP 0x00980330
//
// Every line of the model below is annotated with the instruction it comes from.
// There are only two, so the model is two statements, and everything that is
// *not* a statement here is an absence the listing fixes.
//
// What the two instructions do, and the only things they do:
//
//   00980480  SUB ECX, 0x4
//       Pointer arithmetic on the receiver's address, by four bytes, downward.
//       Three things the instruction does NOT do, each of which the model
//       therefore does not do either:
//         * it is not a field access -- the body contains no memory operand at
//           all, and the machine parse consumed all 2 instructions with
//           unparsed=0, so "no field access" is evidence rather than silence;
//         * it is not element arithmetic -- the unit is a byte, and the model
//           goes through a byte/uintptr view so a mis-scaled adjustment (0x10
//           instead of 0x4) cannot hide;
//         * it is not a null guard -- a null receiver wraps to 0xfffffffc, and
//           the model reproduces the wrap rather than inventing a guard.
//
//   00980483  JMP 0x00980330
//       A tail transfer: control leaves the body without a return of its own.
//       The listing contains no PUSH and no CALL, so:
//         * no return address is pushed -- the callee inherits this body's
//           caller, and the single stack word the caller pushed is at [ESP+0x4]
//           on entry to the callee;
//         * no stack word is pushed here either, so the word the callee finds is
//           the caller's own word, unchanged;
//         * no register other than ECX is touched, so EAX, EDX, the stack and
//           the flags reach the callee exactly as the caller left them. The
//           flags SET by the SUB are dead for every decision this body or its
//           callee can make. The callee's first instruction (0x00980330) loads a
//           stack word and writes no flag; its first read of any flag is the JZ
//           at 0x00980339, and that JZ is decided by the callee's own CMP at
//           0x00980334, not by anything the SUB left behind. So nothing in this
//           package models the flags.
//         * the callee treats the adjusted ECX as a pointer it must null-check
//           before using it (`TEST ECX,ECX` at 0x00980344 / `JZ` at 0x00980346),
//           and only then forms `receiver+0x0c` from it. That check is the
//           callee's own treatment of the word this body adjusted, and it is the
//           nearest machine corroboration available that ECX carries a pointer
//           this body is expected to adjust. It is recorded as an observation
//           about the callee's instructions; no class, no interface and no
//           meaning for 0xc is read out of it here.
//
// ABI, and the one honest difference between the machine and this source.
//
// The persisted ABI record for this target reads: "x86-32 thiscall with the
// receiver in ECX and one 4-byte stack word, popped by the tail callee",
// return_semantics "delegated result in EAX, forwarded verbatim from
// 0x00980330", stack_cleanup_bytes 4, stack_cleanup_owner "callee",
// termination "the body does not return; control leaves through the tail
// transfer at 0x00980483". All four facts are modelled, and the third is the
// reason the model looks the way it does:
//
//   * The C++ function below has a prologue and an epilogue that the machine body
//     does not have. In the binary there is no frame to set up, no frame to tear
//     down, and no RET of this body's own. A source function cannot omit its own
//     return and still be a source function, so the model returns the word the
//     tail callee produced -- which is precisely the record's return_semantics,
//     "forwarded verbatim". The generated epilogue is a source artifact, not a
//     claim about 0x00980480, and the record's own termination note is quoted
//     above so a reader is never left believing this body ends in a RET.
//   * Because thiscall is callee-cleaned and the machine body cleans nothing, the
//     single stack word in the declaration is the CALLER's word reaching the
//     callee, which the callee then reclaims. Declaring the word as a parameter
//     is how the model expresses that pass-through; the model neither pushes it
//     nor pops it.
//
// The receiver is opaque, and the one reason it is not `PerspectiveEffect *` is
// the arity conflict: the SDK and Ghidra name this symbol
// `bool HandleUIMessage(PerspectiveEffect *this, IWindow *pWindow, Message
// *message)`, but the tail callee pops exactly one stack word, so the body
// cannot be that two-argument virtual. The header states that conflict in full;
// it is not resolved here and nothing in this model depends on resolving it.
//
// What is deliberately NOT claimed, carried in the sidecar instead:
//
//   * The class. No record for this target establishes that 0x00980480 belongs
//     to PerspectiveEffect; the only class evidence is a transitive classifier
//     association with vtable:0x01443f2c, and the same record reports
//     vtable_reference_count 0 while the body contains no indirect transfer of
//     any kind, so nothing here dispatches through that table or any other.
//   * A slot offset. The address is stored as a dword at 0x01443f68, which is the
//     one xref the bridge reports, but no vtable start and no slot index has been
//     established, so no slot is declared and no slot offset is claimed.
//   * The meaning of the forwarded word, and the meaning of the returned word.
//     The callee compares the forwarded word against 0xef865d7e and answers with
//     receiver+0x0c or zero; that class id has no entry in the SDK ObjectTYPE
//     enum, and nothing here explains either the word or the answer.
//   * That 0x4 is "the ILayoutElement secondary base". That is a very plausible
//     reading of a cross-vtable adjustor thunk, and the sibling thunk at
//     0x00980470 is a second instance of the shape -- re-read from the live
//     listing this session it is `SUB ECX,0xc` / `JMP 0x00980490` -- but no
//     record for this target states what the four bytes are. They are modelled
//     as a machine displacement on the address and nothing more.

#include "dfw_00980480_types.hpp"

namespace openspore::reconstruction::pkg_dfw_00980480 {

extern "C" Opaque* PKG_DFW_00980480_THISCALL
handle_message_00980480(Opaque *entered_receiver, MessageWord forwarded_word) {
  // 0x00980480  SUB ECX, 0x4
  //
  // The adjusted receiver. The arithmetic goes through a uintptr_t view for two
  // reasons, both about matching the instruction and neither about making the
  // code tidier: the unit is a byte rather than a pointee-sized element, and
  // `0u - 4` on the integer wraps the way ECX wraps at a null receiver, which a
  // typed pointer subtraction leaves undefined. That wrap is observable and the
  // model keeps it -- see the null-receiver case in the model test.
  Opaque *const adjusted_receiver = reinterpret_cast<Opaque *>(
      reinterpret_cast<std::uintptr_t>(entered_receiver) - 0x4u);

  // 0x00980483  JMP 0x00980330
  //
  // The body's only transfer. It is a tail transfer, so the word the callee
  // leaves in EAX is this body's result, forwarded verbatim, which is the
  // record's own return_semantics; the forwarded stack word is handed over
  // untouched, because nothing between the two instructions touches it or the
  // stack.
  return tail_00980330(adjusted_receiver, forwarded_word);
}

}  // namespace openspore::reconstruction::pkg_dfw_00980480
