#include "storage_view_00c0bc00.hpp"

// The header undefines its convention macro, so it is respelled here; this is
// the same thiscall the entry declares.
#if defined(_MSC_VER)
#define PKG_00C0BC00_THISCALL __thiscall
#else
#define PKG_00C0BC00_THISCALL __attribute__((thiscall))
#endif

// 0x00c0bc00 FUN_00c0bc00 - a two-armed storage-view selector.
//
// Raw bytes 0x00c0bc00..0x00c0bc16 (23 bytes, 7 instructions):
//     00c0bc00  8b 81 20 0b 00 00   MOV EAX,dword ptr [ECX + 0xb20]
//     00c0bc06  85 c0               TEST EAX,EAX
//     00c0bc08  74 06               JZ 0x00c0bc10
//     00c0bc0a  05 04 05 00 00      ADD EAX,0x504
//     00c0bc0f  c3                  RET
//     00c0bc10  8d 81 28 0b 00 00   LEA EAX,dword ptr [ECX + 0xb28]
//     00c0bc16  c3                  RET
//
// ECX is the receiver, read at exactly one displacement. The body loads that
// word, tests it against zero, and returns one of two 32-bit values:
//
//   * word nonzero: the word's own value with 0x504 added to it, in 32-bit
//     arithmetic (EAX is the whole value, so the addition wraps).
//   * word zero:    the receiver's own address plus 0xb28.
//
// Both terminators are a bare RET with no immediate and no stack word is read,
// so the callee pops nothing and the caller owns the stack cleanup; with 0
// ordinary stack arguments and the receiver in ECX the convention is
// __thiscall. Neither arm writes memory: the body is a pure selector.
//
// Return: the model declares void*. The zero arm's value is unambiguously an
// address into the receiver (LEA of an interior displacement), and the nonzero
// arm is the loaded word with a byte displacement added to it, which is the
// same class of value. The evidence names no pointee type, so the pointee is
// `void` and the pointer is the most honest return type; the ABI sidecar's
// `return_semantics` (unclassified_in_EAX) is a register class and is NOT
// spelled here as a type.
//
// The displacements are written as header constants whose values are pinned by
// static_asserts to the instructions above, NOT as `receiver->member`. The
// receiver record is bounds_only (register=ECX, offsets=[0xb20]), so a member
// name would be a layout claim nothing corroborates, while a displacement is a
// local fact the listing states outright.

namespace openspore::reconstruction::pkg_00c0bc00_storage_view_00b28 {

void* PKG_00C0BC00_THISCALL storage_view_00c0bc00(OpaqueReceiver* receiver) {
  // 0x00c0bc00 MOV EAX,dword ptr [ECX + 0xb20]
  // The one load this body performs, at the one displacement it reaches through
  // the receiver. The word's identity is unclaimed; only its address is fixed.
  const Opaque storage_word = word_at(receiver, kStorageBaseDisplacement);

  // 0x00c0bc06 TEST EAX,EAX
  // 0x00c0bc08 JZ 0x00c0bc10
  // The branch is a test against zero, not a sign or parity test: TEST EAX,EAX
  // sets ZF from the whole register, so the arm taken depends only on whether
  // the loaded word is zero.
  if (storage_word != 0u) {
    // 0x00c0bc0a ADD EAX,0x504
    // 0x00c0bc0f RET
    //
    // The loaded word's value with the displacement added to it, computed in
    // 32-bit arithmetic because EAX is the whole of it and the addition is a
    // plain ADD on that register. Nothing from the receiver takes part on this
    // arm except the decision to be here.
    return reinterpret_cast<void*>(static_cast<std::uintptr_t>(storage_word) +
                                   kStorageDetour);
  }

  // 0x00c0bc10 LEA EAX,dword ptr [ECX + 0xb28]
  // 0x00c0bc16 RET
  //
  // The receiver's address at the second displacement. LEA forms the address;
  // it does not read the four bytes there, so this package claims nothing about
  // what they hold - only that their address is what comes back.
  return inline_storage_address(receiver);
}

}

#undef PKG_00C0BC00_THISCALL
