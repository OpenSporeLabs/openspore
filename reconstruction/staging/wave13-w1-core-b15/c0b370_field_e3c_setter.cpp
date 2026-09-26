// 0x00c0b370 — 0x00c0b370..0x00c0b37a, 3 instructions, 13 bytes.
//
//   0x00c0b370 MOV EAX,dword ptr [ESP + 0x4]
//   0x00c0b374 MOV dword ptr [ECX + 0xe3c],EAX
//   0x00c0b37a RET 0x4
//
// __thiscall, void return, receiver in ECX, one 4-byte stack argument at
// [ESP+4]. `RET 0x4` pops the return address AND the argument word, so the
// callee owns the cleanup. The body is a pure store: it reads nothing but the
// argument, writes nothing but the field, and touches no global.
//
// A byte-identical setter exists 20 bytes earlier at 0x00c0b35c
// (`8b 4c 24 04 / 89 81 3c 0e 00 00 / c2 04 00`), separated from this one by
// INT3 padding. Two out-of-line copies of the same store to the same offset.
//
// Field +0xe3c, established by a whole-image scan for the displacement 0xe3c
// which returns exactly five referencing instructions:
//
//   0x00c08218  MOV dword ptr [ESI + 0xe3c],0xffffffff   initialise to -1
//   0x00c0b374  MOV dword ptr [ECX + 0xe3c],EAX           this function
//   0x00c0c68c  MOV EAX,dword ptr [ESI + 0xe3c]           sole reader
//   0x00c1fbd2  MOV dword ptr [ESI + 0xe3c],EAX           bulk initialiser
//   0x00c1ff20  MOV dword ptr [ESI + 0xe3c],0xffffffff   reset to -1
//
// The sentinel is 0xffffffff, established at three independent sites: the
// initialiser at 0x00c08218, the reset at 0x00c1ff20 (both an immediate
// 0xffffffff store) and the reader at 0x00c0c692 (`CMP EAX,-0x1` /
// `JNZ 0x00c0c77e`) followed immediately by the shared epilogue that stores EAX
// through EBX, i.e. the stored value is handed straight back to the caller
// when it is not the sentinel.
//
// Observed written values, all from caller setup:
//   0x00c04363  PUSH 0x609ea52
//   0x00d62f1d  PUSH 0x341b7b33
//   0x00d62f97  PUSH 0xf4165aa3
//   0x00d630ff  PUSH 0x341b7b33
//   0x00d65242  PUSH -0x1
//   0x00d851a9  PUSH 0x337d8b6b
//   0x00cdf618  PUSH -0x1
//   0x00cdf70d  PUSH -0x1
//   0x00db96d7  not disassembled
//
// The domain is therefore "any 32-bit value the caller supplies, with -1
// meaning unset". Values such as 0x341b7b33 and 0x114242e6 (the constant the
// same region compares a virtual call's result against at 0x00c0c6cc) are the
// same family of opaque 32-bit tokens, but no token table was located, so the
// token is NOT named here.

#include "b15_opaque_types.hpp"

namespace openspore::wave13_w1_core_b15 {

void set_field_e3c_00c0b370(OpaqueSimState* self, std::int32_t value) noexcept {
    self->field_e3c = value;
}

}  // namespace openspore::wave13_w1_core_b15
