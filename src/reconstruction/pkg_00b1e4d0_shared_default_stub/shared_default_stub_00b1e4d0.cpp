#include "shared_default_stub_00b1e4d0.hpp"

// 0x00b1e4d0 - shared "return false" default stub (ICF/COMDAT collapse).
//
// Raw bytes 0x00b1e4d0..0x00b1e4d2, read from the live Ghidra bridge:
//
//     0x00b1e4d0  30 c0   XOR AL,AL
//     0x00b1e4d2  c3      RET
//
// The whole body is two instructions. XOR AL,AL writes the low byte of EAX
// with zero and touches nothing else; the RET is bare, so the callee pops
// nothing and the caller owns whatever cleanup there is (there is nothing:
// zero stack words). The receiver arrives in ECX per the V1-VFT derivation
// (slot of a vptr-backed vftable, callee pops nothing, no stack word read as
// an argument, EDX never read) and is never read in any form, so the
// parameter below is unnamed - the machine gives it no name and no use.
//
// Return: bool. The machine writes exactly one byte (AL := 0) and the upper
// 24 bits of EAX are indeterminate at the RET; bool is the one-byte spelling
// of that fact and the spelling of "false". Nothing here reads the upper
// bytes, and no wider return type is declared: the return-semantics evidence
// is WIDTH_1_IN_EAX, and a wider declaration would contradict the listing.
//
// The body is straight-line: no branch, no call, no flag test, no register
// save, no loop, no memory operand of any kind. There is therefore nothing to
// transcribe but the single one-byte write, spelled in the C++ that means it.

namespace openspore::reconstruction::pkg_00b1e4d0_shared_default_stub {

bool PKG_00B1E4D0_SHARED_DEFAULT_STUB_THISCALL shared_default_stub_00b1e4d0(void*) {
  // 0x00b1e4d0 XOR AL,AL
  // 0x00b1e4d2 RET
  return false;
}

}
