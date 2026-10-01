// PKG-SW1-00A649A0 -- VA 0x00a649a0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000)
//
// The complete body. Four bytes, two instructions, no callees, one memory read
// and no memory write:
//
//   00a649a0  8B 41 6C   MOV EAX,DWORD PTR [ECX+0x6C]    ; 3 bytes
//   00a649a3  C3         RET                              ; 1 byte
//
// GhidraMCP /read_memory at 0x00a649a0 returns `8b416cc3cccccccccccccccccccc`
// for the first 16 bytes and /disassemble_function reports body_start 0x00a649a0,
// body_end 0x00a649a3, size 4, two instructions, classification "stub". The
// twelve 0xcc bytes that follow are the inter-function pad: the next body opens
// at 0x00a649a8 with 8B 49 70 (`MOV ECX,[ECX+0x70]`), so nothing in this file
// reaches past 0x00a649a3.
//
// A 4-byte body has exactly one place it can be wrong, so every line below is
// tied to a specific byte rather than to a plausible story:
//
//   8B      MOV r32, r/m32. A 32-bit load, four bytes of memory, one read, and
//           it sets no flag.
//   41      ModRM: mod = 01 so a single disp8 follows; reg = 000 so the
//           destination is EAX; r/m = 001 so the address register is ECX. There
//           is no SIB byte, no second register and no index.
//   6C      the disp8. +108, i.e. receiver + 0x6c. This is the only address the
//           function forms.
//   C3      RET, with no immediate byte behind it because the body ends here.
//           The callee therefore pops 0 bytes.
//
// FRAME. There is none, and the three facts that settle it are all visible in
// the 4 bytes plus the one call site:
//
//   * receiver. The address register is ECX and it is dereferenced immediately
//     (0x00a649a0), before anything is written to it, so ECX carries a receiver
//     and the receiver is READ, not written. The record agrees: receiver true,
//     receiver_register ECX, written_through 0, offsets [108].
//   * zero arguments. The body's only memory operand is [ECX+0x6c] -- it never
//     reads [ESP+...], [EBP+...], [EAX+...] or a push slot -- and its RET carries
//     no immediate. A call site agrees from the other side: 0x00a53d97 loads
//     ECX from [ESI+0x9c], 0x00a53da5 calls 0x00a649a0, and 0x00a53daa is
//     `FLD DOUBLE PTR [ESP+0x18]` with no ADD ESP,n in between, so no argument
//     was pushed and none is expected back. ghidra_function.parameter_count is 0
//     and its stored prototype is `undefined FUN_00a649a0(void)`.
//   * cleanup. 0 bytes, owner nominally the caller. For a zero-argument
//     __thiscall that is the same statement as "the RET has no immediate", so
//     the record's INFERRED cleanup and the observed C3 do not contradict each
//     other; the model test measures the stack effect across a thiscall shim
//     instead of trusting either (case Q).
//
// RETURN. EAX, and the value is the 32-bit word that was loaded: 0x00a649a0
// writes all of EAX from memory, so no bit of the previous EAX survives. The
// caller consumes it as a plain dword -- 0x00a53dc0 `MOV DWORD PTR [EDX],EAX`
// stores it as the first word of a three-word record whose other two words come
// from EDI (0x00a53dc2) and EBX (0x00a53dce) -- which is what rules out a
// sub-word return, a bool normalisation and a float in a numeric register: the
// result is stored as an integer word next to two other integer words and is
// never converted.
//
// VIRTUAL DISPATCH. None here: the body has no indirect call and no
// vtable-shaped load (abi_derived.dispatch: indirect_calls 0, call_offsets [],
// vtable_shaped_loads 0). This body is, however, itself installed as a vtable
// entry in seven places -- the data cross-references Ghidra records are
// 0x013ff6d0, 0x014627e0, 0x0147ca80, 0x0147cb48, 0x0147cc38, 0x01489118 and
// 0x01489438, and /read_memory re-read the dword at 0x013ff6d0, 0x01489118 and
// 0x0147ca80 for this package and each holds the little-endian `a0 49 a6 00` =
// 0x00a649a0. docs/analysis/vtables.json labels the run whose head is 0x013ff648
// "VTAB_013ff648_40slots" in namespace Sporepedia, so this entry sits 0x88 = 34
// dwords past that head. No slot number is declared, because whether the head
// dword counts as slot 0 is exactly the convention this target does not settle
// (see the types header). The tooling lists 14 vtable heads for this VA; seven
// of them contain a dword equal to the entry point and the other seven are the
// heads of the runs those seven sit inside or beside. Nothing is claimed about
// the other seven.
//
// NOT MODELLED, DELIBERATELY. There is no naming, no class, no slot and no
// pointee type for the returned word, because the machine evidence fixes none of
// them. abi_derived.return_semantics calls the value "pointer_like" with
// INFERRED confidence; that is a statement about the register, not a
// dereference, and turning it into a C++ pointer type would invent a second
// load the code does not perform. The receiver is likewise not named: this
// binary carries no MSVC RTTI and ghidra_function.sdk_name is null.

#include "sw1_00a649a0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_00a649a0 {

// The one displacement the body states, pinned to the instruction that states it.
// This is an assertion and not documentation: it fails the build if the header's
// value is ever edited away from the disp8 the listing carries.
static_assert(kFieldDisplacement == 0x6c,
              "MOV EAX,DWORD PTR [ECX+0x6C] at 0x00a649a0 -- the disp8 is 0x6c");

// 0x00a649a0  8B 41 6C   MOV EAX,DWORD PTR [ECX+0x6C]
// 0x00a649a3  C3         RET
//
// Written as the one memory read it is, at the displacement the ModRM and disp8
// encode. There is no branch, no arithmetic, no flag write, no call, no write to
// memory, and no stack traffic at all. The receiver is read exactly once, four
// bytes wide, and that dword is the return value.
extern "C" Word PKG_SW1_00A649A0_THISCALL re_00a649a0(Receiver* receiver) {
  // EAX = *(uint32_t *)(this + 0x6c). One level of indirection: the dword sits
  // at receiver+0x6c and its VALUE is returned, never a pointer to it.
  //
  // The receiver is an opaque byte run and the read goes through the
  // displacement-named accessor, because the machine-derived receiver record for
  // this target is `bounds_only` and carries nothing but the displacement itself.
  // A member name here would assert an identity for the word that the evidence
  // does not corroborate; the displacement does not need corroborance of that
  // kind, so it keeps the name and the word does not.
  const void* const self = receiver;
  return word_at(self, kFieldDisplacement);
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00a649a0
