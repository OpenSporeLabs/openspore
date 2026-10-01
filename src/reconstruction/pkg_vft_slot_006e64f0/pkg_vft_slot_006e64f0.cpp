// PKG-VFT-SLOT-006E64F0 -- VA 0x006e64f0
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22,
//  sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Reconstruction of the function the knowledge record names
// "FUN_006e64f0". The record carries no class and no SDK name for this
// address, and none is invented here: the reconstruction symbol is spelled
// with the VA token so an automated binder can attach this definition to
// the record's own last name component.
//
// The complete original body, 4 bytes, 2 instructions:
//
//   0x006e64f0  8d 41 04   LEA EAX,[ECX + 0x4]
//   0x006e64f3  c3         RET
//
// Both instructions are below, each annotated with its address. There is
// no third instruction: the 0xcc bytes after the RET are inter-function
// padding and belong to no function body here.
//
// Mechanics, exhaustively:
//
//   transfers    none. The body calls nothing, jumps nowhere, and makes no
//                indirect transfer through a register or a memory operand.
//                The machine dispatch record agrees at indirect_calls = 0.
//   memory       no memory access of any kind. LEA computes an address; it
//                does not read or write the bytes at it. No field is read,
//                no field is written, no global is named.
//   control flow none. There is no conditional branch, so the body is
//                straight-line and its single exit is the RET.
//   stack        the RET carries no immediate and no stack slot is ever
//                read. Zero ordinary stack arguments, zero bytes of callee
//                cleanup, the caller owns the stack.
//   return       EAX holds the receiver's address plus 0x4. The LEA is a
//                full 32-bit address computation, so the return register
//                word is exactly ECX + 0x4 for every receiver.
//
// ABI, and how much of it is inference:
//
//   __thiscall, receiver in ECX, is the derived record's claim under rule
//   V1-VFT: 0x006e64f0 is the value of a slot in 66 vptr-backed vftables
//   (predicate P, measured on this image), the callee pops nothing, no
//   stack word is read as an argument, and no incoming EDX read exists --
//   so the receiver is in a register, and ECX is the only one that carries
//   one. The body itself never dereferences ECX, so it cannot corroborate
//   that claim; the listing-derived receiver evidence is
//   "ecx_address_taken_without_memory_access". The reconstruction keeps
//   the receiver in the signature anyway, for one reason: the convention
//   is a fact about the call sites that reach this slot, and the arity is
//   the part that is machine-checkable. A thiscall declaration with one
//   ordinary stack argument compiles to a `ret $4` terminator that pops
//   a word the caller pushed; this body pushes nothing and pops nothing,
//   so the reconstruction declares the receiver and nothing else, and the
//   emitted terminator is the bare `ret` the listing shows.
//
// The displacement 0x4 is reproduced verbatim through the header's named
// constant. Nothing in these two instructions says what the computed
// address denotes, so the comment above the return names the instruction
// rather than the value's meaning.

#include "pkg_vft_slot_006e64f0_types.hpp"

namespace openspore::reconstruction::pkg_vft_slot_006e64f0 {

extern "C" void* PKG_VFT_SLOT_006E64F0_THISCALL re_006e64f0(void* self) {
  // 0x006e64f0  8d 41 04   LEA EAX,[ECX + 0x4]
  //
  // The body's only instruction that does anything. The receiver's address
  // plus the displacement the instruction states, computed unconditionally
  // with no memory operand and no dependence on anything but the receiver.
  // The next instruction is the RET below, so this is also the only value
  // the body ever produces.
  auto* const bytes = reinterpret_cast<unsigned char*>(self);
  return bytes + kReceiverByteDisplacement;

  // 0x006e64f3  c3   RET
  //
  // Reached by falling out of the return above. Bare RET, no immediate: no
  // callee stack cleanup, and the caller pops anything it pushed -- which,
  // for this body, is nothing. There is no third instruction and no other
  // exit.
}

}  // namespace openspore::reconstruction::pkg_vft_slot_006e64f0
