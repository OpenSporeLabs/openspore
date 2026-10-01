#include "shared_zero_result_00e31100.hpp"

// 0x00e31100 - shared "the result is zero" stub (ICF/COMDAT collapse).
//
// Raw bytes 0x00e31100..0x00e31102, read from the live Ghidra bridge:
//
//     0x00e31100  33 c0   XOR EAX,EAX
//     0x00e31102  c3      RET
//
// The whole body is two instructions. 33 c0 names the full 32-bit EAX, so every
// byte of the result register is written with zero and none of them is
// indeterminate at the RET; the RET is bare, so the callee pops nothing and the
// caller owns whatever cleanup there is (there is nothing: zero stack words).
// The receiver arrives in ECX per the V1-VFT derivation (slot of a vptr-backed
// vftable, callee pops nothing, no stack word read as an argument, EDX never
// read) and is never read in any form, so the parameter below is unnamed - the
// machine gives it no name and no use.
//
// Return: std::int32_t. The derived record states return_register EAX with
// return_semantics integral_in_EAX and register_class integral, and the operand
// of the XOR is the whole register, so the declared width is the 32 bits the
// machine actually writes. src/reconstruction/pkg08_cell_mode already consumes
// this call's EAX as a std::int32_t (its OpaqueIterator) and seeds a four-byte
// local cursor word with it.
//
// The body is straight-line: no branch, no call, no flag test, no register save,
// no loop, no memory operand of any kind. There is therefore nothing to
// transcribe but the single four-byte zero write, spelled in the C++ that means
// it.

namespace openspore::reconstruction::pkg_00e31100_shared_zero_result_stub {

std::int32_t PKG_00E31100_SHARED_ZERO_RESULT_THISCALL
shared_zero_result_00e31100(void*) {
  // 0x00e31100 XOR EAX,EAX   (33 c0: all four bytes of EAX, not AL alone)
  // 0x00e31102 RET           (c3: bare, callee pops nothing)
  return 0;
}

}