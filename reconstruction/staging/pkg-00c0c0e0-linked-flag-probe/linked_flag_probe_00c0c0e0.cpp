#include "linked_flag_probe_00c0c0e0.hpp"

// The header undefines its convention macro, so it is respelled here; this is the
// same thiscall the entry declares.
#if defined(_MSC_VER)
#define PKG_00C0C0E0_THISCALL __thiscall
#else
#define PKG_00C0C0E0_THISCALL __attribute__((thiscall))
#endif

// 0x00c0c0e0 FUN_00c0c0e0 - a two-level guarded byte probe.
//
// Raw bytes 0x00c0c0e0..0x00c0c0fc:
//     8b 81 84 0e 00 00     MOV EAX,dword ptr [ECX + 0xe84]
//     85 c0                 TEST EAX,EAX
//     74 0f                 JZ 0x00c0c0f9
//     80 b8 88 03 00 00 00  CMP byte ptr [EAX + 0x388],0x0
//     74 06                 JZ 0x00c0c0f9
//     b8 01 00 00 00        MOV EAX,0x1
//     c3                    RET
//     33 c0                 XOR EAX,EAX
//     c3                    RET
//
// ECX is the receiver. The body is 9 instructions, 28 bytes, one basic block
// plus one shared zero-return block, and it contains no call, no loop, no
// register save and no store. Both terminators are a bare RET with no immediate
// and the body never reads the stack, so the callee pops nothing and the caller
// owns the stack cleanup; with no ordinary stack argument the receiver is in ECX
// and the convention is __thiscall.
//
// The two displacements are spelled as values, NOT as `receiver->member` and NOT
// as `linked->member`. The disassembly fixes a displacement, a width and a base
// register; it fixes nothing about which member of any type occupies that word,
// and the derived receiver record says so itself (`register=ECX`,
// `bounds_only=true`). The 0x388 read is additionally reached through EAX and
// not through ECX, so it is not a receiver access at all: it is a second object,
// and it is modelled as one.
//
// The link word is spelled as an opaque `std::uint32_t` rather than as a typed
// pointer, because the machine only ever tests it against zero and uses it as an
// address. Casting it to `OpaqueLinkedObject*` is what the body does; asserting
// what it points at is a claim the listing does not make.

namespace openspore::reconstruction::pkg_00c0c0e0_linked_flag_probe {

std::uint32_t PKG_00C0C0E0_THISCALL linked_flag_probe_00c0c0e0(OpaqueReceiver* receiver) {
  // 0x00c0c0e0 MOV EAX,dword ptr [ECX + 0xe84]
  // The one receiver access: a 32-bit load at 0xe84. The body has no other
  // operand naming ECX.
  const std::uint32_t link =
      *reinterpret_cast<const std::uint32_t*>(reinterpret_cast<std::uintptr_t>(receiver) + 0xe84);

  // 0x00c0c0e6 TEST EAX,EAX
  // 0x00c0c0e8 JZ 0x00c0c0f9
  // The guard. It is a real branch in the machine, not a defensive addition: the
  // second load is only reached when the word is non-zero, so a zero link word
  // must return without ever forming the second address. Both conditional
  // branches in the body target this same 0x00c0c0f9 block, so the two tests
  // share one zero-return exit.
  if (link == 0) {
    // 0x00c0c0f9 XOR EAX,EAX
    // 0x00c0c0fb RET
    return 0;
  }

  // 0x00c0c0ea CMP byte ptr [EAX + 0x388],0x0
  // The second access, on the object the first one produced. EAX holds the link
  // word at this point, so 0x388 is a displacement on THAT base, not on ECX. The
  // read is a single byte, and the body compares it against zero without
  // sign-extending it anywhere.
  const std::uint8_t flag =
      *reinterpret_cast<const std::uint8_t*>(reinterpret_cast<std::uintptr_t>(link) + 0x388);

  // 0x00c0c0f1 JZ 0x00c0c0f9
  if (flag == 0) {
    // 0x00c0c0f9 XOR EAX,EAX
    // 0x00c0c0fb RET
    return 0;
  }

  // 0x00c0c0f3 MOV EAX,0x1
  // 0x00c0c0f8 RET
  //
  // The one-return arm writes a full 32-bit 1 into EAX. The value returned is
  // the constant 1 and not the flag byte: a flag byte of 0x2a still returns 1,
  // which is what distinguishes this body from one that forwards the byte.
  return 1;
}

}

#undef PKG_00C0C0E0_THISCALL
