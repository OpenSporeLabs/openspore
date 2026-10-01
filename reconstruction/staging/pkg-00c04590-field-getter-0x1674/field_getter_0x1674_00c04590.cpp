#include "field_getter_0x1674_00c04590.hpp"

// The header undefines its convention macro, so it is respelled here; this is
// the same thiscall the entry declares.
#if defined(_MSC_VER)
#define PKG_00C04590_THISCALL __thiscall
#else
#define PKG_00C04590_THISCALL __attribute__((thiscall))
#endif

// 0x00c04590 FUN_00c04590 - a non-virtual, single-word member getter, the read
// side of the refcounted-pointer swap at 0x00c045a0.
//
// Raw bytes 0x00c04590..0x00c04596:
//     8b 81 74 16 00 00      MOV EAX,dword ptr [ECX + 0x1674]
//     c3                     RET
//
// ECX is the receiver. The body loads one 32-bit word from displacement 0x1674
// of that receiver into EAX and returns. There is no branch, no call, no flag
// test, no register save, no loop and NO STORE anywhere in the body, so the
// read happens on every entry and the receiver is not modified. The bare RET
// means the callee pops nothing, so the caller owns the stack cleanup. With 0
// ordinary stack arguments, the receiver is in ECX and the convention is
// __thiscall.
//
// Return: the model declares std::uint32_t. The body performs a 32-bit memory
// LOAD, so the returned EAX holds the word's VALUE, not an address computed
// from the receiver.
//
// THE POINT OF THIS FUNCTION, given its neighbour. 0x00c045a0, ten bytes
// further on, stores through the SAME displacement 0x1674 and is visibly a
// retain-new / store / release-old swap on a refcounted object pointer: it
// null-tests the incoming value, calls the pointer's own vtable slot +0x0
// (0x00c045c7..0x00c045cd) before storing, then calls slot +0x4 on the outgoing
// value (0x00c045d9..0x00c045e0) after storing. This body does NONE of that.
// There is no call and no write, so it is a RAW read: it neither acquires nor
// releases a reference, and the sampled callers that go on to use the result
// (0x00b6b4c0 reads `*(int *)(result + 0x15c)`; 0x00accf80 calls through
// `**(code **)result`) are doing that dereference themselves, in the caller.
// Claiming a retaining accessor here would be the single most plausible wrong
// reconstruction, so the model test attacks it head-on with a counted fake
// object whose vtable slots are instrumented.
//
// The ABI record's return_semantics reads pointer_like_in_EAX, and the
// neighbour plus those callers make it plausible that the word is an object
// pointer. But that is a register CLASS in the derived layer's vocabulary and a
// corroborating inference, not a C type the machine states; the model returns
// the width-computable builtin and asserts no pointee type.
//
// The displacement is spelled literally as a value, NOT as `receiver->member`.
// The disassembly establishes the displacement (0x1674), the width (32-bit) and
// the base (ECX); it establishes nothing about which member of any type
// occupies that word, and the receiver record says so itself
// (`register=ECX offsets=[0x1674] bounds_only`). A member name here would be a
// field-identity assertion with nothing behind it, so the displacement is
// spelled literally instead and the identity claim is left out.

namespace openspore::reconstruction::pkg_00c04590_field_getter_0x1674 {

// The declared return is spelled `uint32_t` rather than this package's
// `Word` alias. The alias IS `std::uint32_t` and the header asserts its
// width; the validator measures the *declared* return's width from the
// spelling and an alias names no width, so the alias spelling made this
// dimension NOT_AVAILABLE on a body whose machine return width is proven.
// Same type, one token changed.
uint32_t PKG_00C04590_THISCALL field_getter_0x1674_00c04590(
    OpaqueReceiver* receiver){
  // 0x00c04590 MOV EAX,dword ptr [ECX + 0x1674]
  // 0x00c04596 RET
  //
  // The one computation this body makes, transcribed as the machine has it:
  // the 32-bit word at receiver+0x1674 is read and its value is returned in
  // EAX. The write is through the RETURN REGISTER, not through the receiver -
  // nothing at receiver+0x1674..receiver+0x1677 is modified, and no reference
  // count, flag or field anywhere is touched.
  //
  // The read is written as a displacement into the opaque receiver, NOT as
  // `receiver->member`. The disassembly establishes the displacement (0x1674),
  // the width (32-bit) and the base (ECX); it establishes nothing about which
  // member of any type occupies that word, and the receiver record says so
  // itself (`register=ECX offsets=[0x1674] bounds_only`).
  return *word_at(receiver, kWordDisplacement);
}

}

#undef PKG_00C04590_THISCALL
