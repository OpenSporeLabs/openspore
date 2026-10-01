#include "root_slot_eae8_00b3d310.hpp"

// 0x00b3d310 FUN_00b3d310 -- an absolute global-slot accessor.
//
// Raw bytes 0x00b3d310..0x00b3d315, read from SporeApp.exe 3.1.0.22:
//     a1 e8 ea 67 01      MOV EAX, dword ptr [0x0167eae8]
//     c3                  RET
//
// Decoding the operand. `a1` is the MOV r32, moffs32 form: a one-byte opcode
// followed by a little-endian absolute address, with no ModRM byte and no
// register operand at all. The four bytes e8 ea 67 01 therefore ARE the address
// 0x0167eae8, and the access is through the segment-absolute slot DS:0167eae8
// -- not through any base or index register, and not through a pointer the
// caller supplies. `c3` is a bare RET with no immediate, so the callee pops
// nothing.
//
// What the body does, exhaustively, over its two instructions:
//   * one 32-bit LOAD from 0x0167eae8 into EAX. There is no LEA, no addend, no
//     masking, no sign extension and no arithmetic: EAX receives the word's own
//     VALUE, bit for bit, which is what separates this body from the LEA-form
//     and offset-adding getters elsewhere in the same accessor cluster.
//   * no store. The committed data-reference artifact records exactly one row
//   for
//     this body -- `00b3d310 0167eae8 read .data -wr` -- and Ghidra's reference
//     database holds exactly one reference to 0x0167eae8, that READ. So the
//     slot is provably unchanged across a call, and nothing here publishes it.
//   * no branch and no conditional, so the load happens on every entry with no
//     path that skips it.
//   * no call, and no jump out of the body.
//   * no register receiver. ECX is never read in any form, so there is nothing
//   for
//     a thiscall-style hidden parameter to carry, and there are zero ordinary
//     stack arguments because no stack slot is ever read.
//
// What the compiler emits for this body, measured (clang 22.1.8, -m32): under
// -fno-pic at -O1/-O2 it is exactly `a1 <disp32>` / `c3` -- the target's own
// opcode pair, with the absolute address arriving as a link-time relocation.
// Under the default -fpic the same one-word load of the same global is reached
// through a get_pc_thunk and `mov 0x0(%eax),%eax`. -O0 adds the ordinary frame.
// The semantic content is the same in every case and is what the model test
// measures; none of these shapes is asserted here.
//
// Calling convention. With zero stack arguments, a bare RET and no ECX read,
// the byte sequence is identical under __cdecl, __stdcall, __thiscall and
// __fastcall. The derived ABI record states this itself and abstains from
// choosing: `C10` ("the function is byte-identical under all four conventions",
// confidence UNKNOWN) and `abstained_because: ["no_discriminator: no
// stack-argument read and no positive receiver evidence"]`. __cdecl is declared
// below because it is the only one of the four that asserts nothing about a
// callee-cleanup this body does not perform -- it is a source-side choice among
// byte-identical options, not a recovered fact, and the model test measures the
// cleanup instead of trusting the spelling.
//
// Return value. The machine fixes the WIDTH of what crosses EAX at four bytes.
// That the word is used as an object address is corroborated outside this body:
// the ABI record's `return` sub-record classifies EAX as `pointer_like`, and
// two independently read callers dereference the returned word at displacement
// +0x20 on the instruction right after the call (0x00acd13a `CMP dword ptr [EAX
// + 0x20], 0x1` following `CALL 0x00b3d310` at 0x00acd135, and 0x00b82985 `CMP
// dword ptr [EAX + 0x20], EBX` following `CALL 0x00b3d310` at 0x00b8297e). So
// the return is modelled as a pointer to an INCOMPLETE type. That type is never
// defined, sized or given a member here: this body reaches no displacement at
// all, so a member name would be an identity claim nothing in this package
// corroborates, and 0x20 is left entirely to the callers.
//
// The slot's identity is NOT claimed. Adjacent accessors in this cluster read
// neighbouring slots, and 0x0167eae8 sits between two of them, but adjacency
// proves nothing: nothing in this body, in its data-reference row, or in its
// single xref says what the slot holds or which class owns it. No writer of
// 0x0167eae8 exists in the current analysis state, so its publication and
// teardown, and whether it ever equals any neighbouring slot, are all unclaimed
// here. kSlotAddress is spelled as the absolute address the operand bytes
// carry, which is what the instruction states; it is not an offset into
// anything.

#if defined(_MSC_VER)
#define PKG_00B3D310_CDECL __cdecl
#else
#define PKG_00B3D310_CDECL __attribute__((cdecl))
#endif

// The modelled slot itself: one 32-bit word at absolute address 0x0167eae8. It
// is DEFINED here with C language linkage so the entry and the model test share
// one object; a C-linkage name is defined at global scope, never inside a
// namespace, which is why this definition sits outside the package namespace
// below.
extern "C" {
std::uint32_t g_0167eae8 = 0u;
}

namespace openspore {
namespace reconstruction {
namespace pkg_00b3d310_root_slot_eae8 {

OpaqueRootSlotTarget* PKG_00B3D310_CDECL simulator_root_slot_eae8_00b3d310() {
  // 0x00b3d310 MOV EAX, dword ptr [0x0167eae8]
  // 0x00b3d315 RET
  //
  // The whole computation: read the 32-bit word at absolute address 0x0167eae8
  // and hand its VALUE back in EAX. The load is a read, so nothing at
  // 0x0167eae8..0x0167eae8+sizeof(Word) is modified. There is no branch here,
  // so the read is unconditional, and no receiver is consulted, so the result
  // depends on nothing but the slot's current contents.
  return reinterpret_cast<OpaqueRootSlotTarget*>(
      static_cast<std::uintptr_t>(g_0167eae8));
}

}  // namespace pkg_00b3d310_root_slot_eae8
}  // namespace reconstruction
}  // namespace openspore

#undef PKG_00B3D310_CDECL