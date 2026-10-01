#include "word_getter_0xb20_00c0bbd0.hpp"

// The header undefines its convention macro, so it is respelled here; this is
// the same thiscall the entry declares.
#if defined(_MSC_VER)
#define PKG_00C0BBD0_THISCALL __thiscall
#else
#define PKG_00C0BBD0_THISCALL __attribute__((thiscall))
#endif

// 0x00c0bbd0 FUN_00c0bbd0 - a non-virtual, single-word member getter.
//
// Raw bytes 0x00c0bbd0..0x00c0bbd6:
//     8b 81 20 0b 00 00      MOV EAX,dword ptr [ECX + 0xb20]
//     c3                     RET
//
// ECX is the receiver. The body loads one 32-bit word from displacement 0xb20
// of that receiver into EAX and returns. There is no branch, no call, no flag
// test, no register save, no loop and NO STORE anywhere in the body, so the
// read happens on every entry and the receiver is not modified. The bare RET
// means the callee pops nothing, so the caller owns the stack cleanup. With 0
// ordinary stack arguments, the receiver is in ECX and the convention is
// __thiscall.
//
// Return: the model declares std::uint32_t. The body performs a 32-bit memory
// LOAD, so the returned EAX holds the word's VALUE, not an address computed
// from the receiver. That is what separates this body from the LEA-form
// getters in the same cluster (0x00c0bc00, for instance, loads the same word
// and then ADDs a displacement to it before returning) and it is the single
// behavioural claim the model test attacks hardest.
//
// The ABI record's return_semantics reads pointer_like_in_EAX, but that is a
// register CLASS in the derived layer's vocabulary, not a C type, and it is not
// evidence about this word. Four sampled callers (0x00c4fc00, 0x00aca360,
// 0x00c02eb0, 0x00c08350) consume the result only in equality comparisons
// against other words or other getters' results, and in one bitmask - none of
// them dereferences it. So the honest return type is the width-computable
// builtin the load states, and the word's identity is left unclaimed.
//
// The displacement is spelled literally as a value, NOT as `receiver->member`.
// The disassembly establishes the displacement (0xb20), the width (32-bit) and
// the base (ECX); it establishes nothing about which member of any type
// occupies that word, and the receiver record says so itself
// (`register=ECX offsets=[0xb20] bounds_only`). A member name here would be a
// field-identity assertion with nothing behind it, so the displacement is
// spelled literally instead and the identity claim is left out.

namespace openspore::reconstruction::pkg_00c0bbd0_word_getter_0xb20 {

// The declared return is spelled `uint32_t` rather than this package's
// `Word` alias. The alias IS `std::uint32_t` and the header asserts its
// width; the validator measures the *declared* return's width from the
// spelling and an alias names no width, so the alias spelling made this
// dimension NOT_AVAILABLE on a body whose machine return width is proven.
// Same type, one token changed.
uint32_t PKG_00C0BBD0_THISCALL word_getter_0xb20_00c0bbd0(OpaqueReceiver* receiver){
  // 0x00c0bbd0 MOV EAX,dword ptr [ECX + 0xb20]
  // 0x00c0bbd6 RET
  //
  // The one computation this body makes, transcribed as the machine has it:
  // the 32-bit word at receiver+0xb20 is read and its value is returned in
  // EAX. The write is through the RETURN REGISTER, not through the receiver -
  // nothing at receiver+0xb20..receiver+0xb23 is modified.
  //
  // The read is written as a displacement into the opaque receiver, NOT as
  // `receiver->member`. The disassembly establishes the displacement (0xb20),
  // the width (32-bit) and the base (ECX); it establishes nothing about which
  // member of any type occupies that word, and the receiver record says so
  // itself (`register=ECX offsets=[0xb20] bounds_only`). A member name here
  // would be a field-identity assertion with nothing behind it, so the
  // displacement is spelled literally instead.
  return *word_at(receiver, kWordDisplacement);
}

}

#undef PKG_00C0BBD0_THISCALL
