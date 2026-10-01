// PKG-DFW-00980510 -- VA 0x00980510
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22,
//  sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Reconstruction of the function the knowledge record names
// "UTFWin::PerspectiveEffect::GetProxyID". The class and the method name are
// the imported Spore-ModAPI spelling that the record carries; nothing below
// depends on that spelling, and the body models none of it. The reconstruction
// symbol is spelled with the VA token so an automated binder can attach this
// definition to the record's own last name component.
//
// The complete original body, 6 bytes, 2 instructions:
//
//   0x00980510  b8 02 02 00 00   MOV EAX,0x202
//   0x00980515  c3               RET
//
// Both instructions are below, each annotated with its address. There is no
// third instruction: the 0xcc bytes after the RET are inter-function padding
// and belong to no function body here.
//
// Mechanics, exhaustively:
//
//   transfers    none. The body calls nothing, jumps nowhere, and makes no
//                indirect transfer through a register or a memory operand.
//                The machine dispatch record agrees at indirect_calls = 0.
//   memory       no memory operand of any kind. No field is read, no field is
//                written, no global is named.
//   control flow none. There is no conditional branch, so the body is
//                straight-line and its single exit is the RET.
//   stack        the RET carries no immediate and no stack slot is ever read.
//                Zero ordinary stack arguments, zero bytes of callee cleanup,
//                the caller owns the stack.
//   return       EAX holds 0x00000202. The MOV is a full 32-bit immediate, so
//                the upper three bytes are defined rather than residual, which
//                is why the return is a 32-bit word and not a narrower one.
//
// ABI, and how much of it is inference:
//
//   __thiscall, receiver in ECX, is the persisted record's claim. The body
//   never reads ECX, so it cannot corroborate that claim, and the machine-
//   derived ABI record in the evidence pack abstained outright with verdict
//   ABI_UNKNOWN and the reason "no_discriminator: no stack-argument read and
//   no positive receiver evidence" -- because the body is byte-identical under
//   __cdecl, __stdcall, __thiscall and __fastcall. The reconstruction keeps the
//   receiver in the signature anyway, for one reason: the target's only
//   reference in the whole program is the DATA word at 0x014440e4, which is
//   slot +0x14 of a dispatch-table image based at 0x014440d0, and a virtual
//   member of an MSVC x86-32 class receives its receiver in ECX. That is the
//   whole basis for the convention -- a placement argument, not an observation.
//   It is reproduced here so the arity is right, and it is flagged so nobody
//   reads it back as a stronger claim than it is.
//
//   Concretely, the arity is the part that is machine-checkable. A thiscall
//   declaration with one ordinary stack argument compiles to a `ret $4`
//   terminator that pops a word the caller pushed. This body pushes nothing
//   and pops nothing, so the reconstruction declares the receiver and nothing
//   else, and the emitted terminator is the bare `ret` the listing shows.
//   (Verified with the compiler rather than assumed: `g++ -m32 -O2` on this
//   translation unit emits `b8 02 02 00 00 c3` for the symbol below -- the
//   original bytes, in order. The model-test command in the brief builds at
//   -O0, where a stack frame is emitted around the same two instructions; the
//   frame is a compiler artefact, not part of the reconstruction.)
//
// The immediate 0x202 is reproduced verbatim. Nothing in these two instructions
// says what it denotes, and the record carries that as an open question, so the
// comment above the return names the instruction rather than the value's
// meaning.

#include "dfw_00980510_types.hpp"

namespace openspore::reconstruction::pkg_dfw_00980510 {

extern "C" std::uint32_t PKG_DFW_00980510_THISCALL
dfw_get_proxy_id_00980510(void* self) {
  // The receiver is not read. The body has no memory operand, and the only
  // register it writes is the return register, so the receiver in ECX is
  // carried in the signature for the arity and dropped here. This is the
  // observable consequence of the ABI record's R2 inference ("ECX is never
  // read in any form, so there is no register receiver") and it is the reason
  // the function returns the same word for every receiver.
  (void)self;

  // 0x00980510  b8 02 02 00 00   MOV EAX,0x202
  //
  // The body's only instruction that does anything. One full 32-bit immediate
  // into the return register, unconditional, with no memory operand and no
  // dependence on anything. The next instruction is the RET below, so this is
  // also the only value the body ever produces.
  return 0x202u;

  // 0x00980515  c3   RET
  //
  // Reached by falling out of the return above. Bare RET, no immediate: no
  // callee stack cleanup, and the caller pops anything it pushed -- which, for
  // this body, is nothing. There is no third instruction and no other exit.
}

}  // namespace openspore::reconstruction::pkg_dfw_00980510
