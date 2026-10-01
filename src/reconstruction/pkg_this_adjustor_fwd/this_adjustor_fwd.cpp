// pkg-this-adjustor-fwd -- VA 0x00c372b0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// The complete body: 2 instructions, 0x00c372b0..0x00c372ba inclusive
// (ghidra_function.body_start 0x00c372b0, body_end 0x00c372ba, size_bytes 11).
//
//   00c372b0  ADD ECX,0x7b8        the receiver is adjusted by +0x7b8
//   00c372b6  JMP 0x00feba90        a single ESP-neutral direct jump
//
// THE ADJUSTMENT, AND WHY THE RECEIVER'S IDENTITY CHANGES. `ADD ECX,0x7b8`
// lifts the receiver 0x7b8 (1976) bytes above the incoming `this` before the
// jump, so the callee operates on a sub-object at a higher address. This is
// the shape of a this-adjustor thunk reaching a secondary base in a
// multiple-inheritance layout, and it is recorded as a distinct fact:
// abi_derived.receiver.adjustor_delta is 1976, and the header states the same
// as kReceiverAdjustorDelta. The receiver is NOT treated as unchanged.
//
// THE TRANSFER. The only exit is a direct JMP to a static target inside this
// image's code range (0x00feba90), the thunk pushes nothing and pops nothing,
// and the target is a function entry. That is the T1-FWD shape (S1..S7 all
// hold), so the convention and the cleanup FORWARD from the tail target:
// __thiscall, receiver in ECX, zero stack arguments, caller cleans. The
// derived record states it (conventions.calling_convention "__thiscall",
// confidence INFERRED, corroboration "forwarded_from_tail_target").
//
// THE TAIL TARGET, whose own listing is `MOV AL,byte ptr [ECX + 0x18] ; RET`:
//   00feba90  MOV AL,byte ptr [ECX + 0x18]
//   00feba93  RET
// Receiver in ECX (R-DIRECT at offset 0x18), no stack word read, bare RET, one
// byte written to the return register. Its return width is therefore one byte,
// and the thunk returns exactly that byte.
//
// FRAME. There is none. The thunk has no prologue, allocates no frame, pushes
// nothing, and saves no register; its two instructions are an in-place adjust
// and a jump. The stack word balance across the whole call is zero, which is
// the forwarded caller-cleanup fact and what the model test measures.
//
// GLOBALS: none. The two instructions name no data-segment address, and the
// xref export carries no data-reference edge type; the model declares none.
//
// VIRTUAL DISPATCH: none in this body's span. The transfer is a direct JMP to
// a static target, not an indirect call through a register or a memory
// operand. (The tail target 0x00feba90 is itself a slot of four vptr-backed
// vftables under predicate P -- 0x01416a68+0x18, 0x01453b48+0x10,
// 0x0145c164+0x10, 0x0145c2b8+0x14 -- but that is a fact about the callee,
// reached by a direct jump, not a dispatch this body performs.)
//
// CONTROL FLOW: none. The body is two straight-line instructions with no
// conditional branch and no loop; the only transfer is the unconditional
// tail jump.
//
// CONSTANTS. The body's only literals are the adjustor delta 0x7b8 and the
// tail target 0x00feba90, both stated in the machine listing. The delta is
// spelled through the header's named constant (kReceiverAdjustorDelta), tied to
// its instruction by a static_assert; the tail target is spelled through the
// callee symbol (re_00feba90), which embeds its VA.

#include "this_adjustor_fwd.hpp"

namespace openspore::reconstruction::pkg_this_adjustor_fwd {

// 00c372b0  ADD ECX,0x7b8
// 00c372b6  JMP 0x00feba90
//
// The whole body, literal. The receiver is adjusted by +0x7b8 and the adjusted
// receiver is what the callee receives; the callee's return value is returned
// unchanged. The machine reaches the callee with a JMP (a tail call); the C++
// expresses the same transfer and the same return value with a call whose
// result is returned. The observable behaviour is identical: the callee sees
// receiver + 0x7b8 in ECX, reads the byte at (receiver + 0x7b8) + 0x18, and the
// caller sees that byte come back with the stack balanced.
extern "C" std::uint8_t PKG_THIS_ADJUSTOR_FWD_THISCALL re_00c372b0(void* receiver) {
  return re_00feba90(static_cast<unsigned char*>(receiver) + kReceiverAdjustorDelta);
}

}  // namespace openspore::reconstruction::pkg_this_adjustor_fwd
