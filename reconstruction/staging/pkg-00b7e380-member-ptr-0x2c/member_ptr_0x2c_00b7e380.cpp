#include "member_ptr_0x2c_00b7e380.hpp"

// The header undefines its convention macro, so it is respelled here; this is
// the same thiscall the entry declares.
#if defined(_MSC_VER)
#define PKG_00B7E380_THISCALL __thiscall
#else
#define PKG_00B7E380_THISCALL __attribute__((thiscall))
#endif

// 0x00b7e380 FUN_00b7e380 - a virtual member getter.
//
// Raw bytes 0x00b7e380..0x00b7e384:
//     8d 41 2c               LEA  EAX,dword ptr [ECX + 0x2c]
//     c3                     RET
//
// ECX is the receiver. The body computes EAX = ECX + 0x2c and returns. There
// is no branch, no call, no flag test, no register save and no loop in the
// body. The bare RET means the callee pops nothing, so the caller owns the
// stack cleanup. With 0 ordinary stack arguments, the receiver is in ECX and
// the convention is __thiscall.
//
// Return: the model declares void*. The body computes a 32-bit pointer in EAX
// (ECX + 0x2c) and returns it. The member's type is not established - the
// receiver is bounds_only, so member names are unverifiable - so the return
// type is the most honest pointer: void*.
//
// The displacement is spelled literally as a value, NOT as `receiver->member`.
// The disassembly establishes the displacement (0x2c), the width (32-bit) and
// the base (ECX); it establishes nothing about which member of any type
// occupies that word, and the receiver record says so itself
// (`register=ECX offsets=[0x2c] bounds_only`). A member name here would be a
// field-identity assertion with nothing behind it, so the displacement is
// spelled literally instead and the identity claim is left out.

namespace openspore::reconstruction::pkg_00b7e380_member_ptr_0x2c {

void* PKG_00B7E380_THISCALL member_ptr_0x2c_00b7e380(OpaqueReceiver* receiver) {
  // 0x00b7e380 LEA EAX,dword ptr [ECX + 0x2c]
  // 0x00b7e383 RET
  //
  // The one computation this body makes, transcribed as the machine has it:
  // the 32-bit word at receiver+0x2c is computed as an address and returned in
  // EAX. There is no branch, no call, no flag test, no register save and no
  // loop, so the computation happens on every entry.
  //
  // The computation is written as a displacement into the opaque receiver,
  // NOT as `receiver->member`. The disassembly establishes the displacement
  // (0x2c), the width (32-bit) and the base (ECX); it establishes nothing
  // about which member of any type occupies that word, and the receiver
  // record says so itself (`register=ECX offsets=[0x2c] bounds_only`). A
  // member name here would be a field-identity assertion with nothing behind
  // it, so the displacement is spelled literally instead and the identity
  // claim is left out - which is also the only way the reconstruction stays
  // true to a body that computes a raw address.
  return reinterpret_cast<void*>(
      reinterpret_cast<std::uintptr_t>(receiver) + 0x2c);
}

}

#undef PKG_00B7E380_THISCALL
