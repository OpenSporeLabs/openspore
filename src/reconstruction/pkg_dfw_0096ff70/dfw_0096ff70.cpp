// PKG-DFW-0096FF70 -- VA 0x0096ff70
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22,
//  binary sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Machine listing, 2 instructions, body 0x0096ff70..0x0096ff77 inclusive
// (bridge: body_start 0x0096ff70, body_end 0x0096ff77, body_span_bytes 8,
// instruction_count 2, classification "stub"). Re-derived read-only from the
// live bridge during this session rather than copied from the committed pack:
//
//   0096ff70  83 E9 0C          SUB  ECX,0x0C
//   0096ff73  E9 58 00 00 00    JMP  0x0096FFD0
//   0096ff78  CC CC ... CC      INT3 padding through 0x0096ff7f: alignment
//                               between this body and the next thunk at
//                               0x0096ff80, not part of this function
//
// Every line of the model below is annotated with the instruction it comes
// from. There are two instructions, so there are two annotated steps, and the
// header comment above carries the rest of what is known about the frame.
//
// What this body is, from the listing alone: eight bytes that rewrite the
// hidden receiver by a fixed amount and transfer control to a fixed address.
// It reads no memory, writes no memory, reads no stack slot, pushes nothing,
// pops nothing, calls nothing by CALL, and tests no flag. The single
// conditional-looking decision in the neighbourhood -- the TEST at 0x0096fff3
// on the low bit of the forwarded word -- is inside the tail target, not here.
//
// What this body is claimed *not* to be, and why:
//
//  * It is not a destructor. The persisted ABI record and the SDK method name
//    func88h put it in a destructor-adjacent slot, and the tail target has the
//    MSVC scalar-deleting shape, but no record for this target identifies the
//    vftable it lives in, and the only DATA reference the image holds is at
//    +0x08 of a pointer run that Ghidra never proved to be a vftable. The model
//    therefore names the callee by its address and nothing else.
//
//  * The receiver is not claimed to be a UTFWin::GlideEffect IBiStateEffect
//    subobject, even though the SDK places that subobject at offset 0x0C and
//    the adjustment is 0x0C. The identity of the subobject is an unresolved
//    question in the pack: the byte-for-byte identical shape at 0x0097e550
//    (UTFWin::InflateEffect::func88h) and the -0x04 shape at 0x0096ff80 make
//    the two-instruction form non-distinguishing, and the static image does not
//    settle which class the receiver belongs to. Both pointer types in the
//    header are left incomplete so that no such claim is smuggled in through a
//    struct.
//
//  * The calling convention is an inference, not a record. The machine-derived
//    ABI record abstains outright (verdict ABI_UNKNOWN, conventions
//    .calling_convention null, confidence UNKNOWN, abstained_because
//    "no_terminal_ret: the only exit observed is a tail jump"), and Ghidra's
//    decompilation of this body carries "WARNING: Unknown calling convention".
//    The model declares thiscall because the tail target's own listing pops
//    the one forwarded word itself (RET 0x4 at 0x00970006) and the hidden
//    receiver travels in ECX, which is callee-cleaned register-receiver
//    behaviour. The header states the same thing next to the macro.
//
// Source-shape approximation, stated once and in full: the machine transfers
// with JMP, not CALL. It pushes no return address, and this body contains no
// RET of its own -- its frame has no terminator at all. The model below
// therefore cannot express the transfer as a C++ tail jump without a non
// portable builtin, and it expresses it as an ordinary call whose result is
// discarded. Everything the machine does is still reproduced: the receiver is
// rewritten before the transfer, the stack word is forwarded bit for bit, no
// memory is touched, and the frame's net stack effect is the removal of the
// one word. The one RET 0x4 that ends this frame's lifetime belongs, in the
// machine, to the tail target; in the model it is the thunk's own thiscall
// epilogue, which is what keeps the caller's stack exactly where the machine
// leaves it. A test in the model file measures that balance directly.

#include "dfw_0096ff70_types.hpp"

namespace openspore::reconstruction::pkg_dfw_0096ff70 {

// 0x0096FF70 .. 0x0096FF77:
//
//   SUB ECX,0x0C
//   JMP 0x0096FFD0
//
// The only observable effects of this frame are the -0x0C rewrite of the
// hidden ECX receiver and the forwarding of the single stack word to the tail
// target, which consumes it with its own RET 0x4. The thunk writes no register
// other than ECX, reads no stack slot, and consults no flag, so nothing else
// can be attributed to this address.
extern "C" void PKG_DFW_0096FF70_THISCALL dfw_func88h_0096ff70(
    ThunkReceiver *self, Word deleting_flag) {
  // 0x0096ff70  SUB ECX,0x0C
  //
  // Arithmetic on the receiver register itself. The instruction reads no
  // memory operand, so nothing about the contents of the object the receiver
  // names is observed here -- not its size, not a vptr, not a count -- and it
  // writes no memory either, so the object is left exactly as the caller left
  // it. What the result means is not more than this: the address the tail
  // target goes on to operate on is 12 bytes below the address the thunk was
  // handed. That relationship is arithmetic, and the model reproduces it as
  // arithmetic on the pointer rather than as a cast between object types, so
  // that no layout claim rides along with it.
  TailTargetObject *const adjusted = reinterpret_cast<TailTargetObject *>(
      reinterpret_cast<unsigned char *>(self) - kReceiverAdjustmentBytes);

  // 0x0096ff73  JMP 0x0096FFD0
  //
  // The one transfer out of the body, and it is a jump: no return address is
  // pushed, nothing is popped, and control does not come back. Two things
  // travel with it and nothing else does. The adjusted receiver above, in the
  // register the jump leaves it in. And the one ordinary stack word, untouched:
  // the thunk neither reads nor rewrites it, and the tail target reads it at
  // [ESP+0x8] by TEST byte ptr [ESP+0x8],0x1 at 0x0096fff3 and pops it with
  // RET 0x4 at 0x00970006.
  //
  // The tail target's own listing ends with MOV EAX,ESI at 0x00970003, so it
  // returns the object pointer. That word is the callee's to make: the
  // persisted ABI record types this body void, the SDK method returns void, and
  // the two instructions above never write EAX, so this frame has no return
  // value of its own to propagate. It is discarded explicitly rather than left
  // to fall out of the call, so the reader can see the decision instead of
  // inferring it.
  static_cast<void>(
      dfw_tail_deleting_0096ffd0(adjusted, deleting_flag));
}

}  // namespace openspore::reconstruction::pkg_dfw_0096ff70
