#include "state_word_eq3_00c44c80.hpp"

// The header undefines its convention macro, so it is respelled here; this is the
// same thiscall the entry declares.
#if defined(_MSC_VER)
#define PKG_00C44C80_THISCALL __thiscall
#else
#define PKG_00C44C80_THISCALL __attribute__((thiscall))
#endif

// 0x00c44c80 FUN_00c44c80 - a one-word equality predicate.
//
// Raw bytes 0x00c44c80..0x00c44c8c:
//     33 c0                 XOR EAX,EAX
//     83 b9 84 00 00 00 03  CMP dword ptr [ECX + 0x84],0x3
//     0f 94 c0              SETZ AL
//     c3                    RET
//
// ECX is the receiver. The body is 4 instructions and 13 bytes, it is a single
// basic block, and it contains no branch, no call, no loop, no register save and
// no store. The terminator is a bare RET with no immediate and the body never
// reads the stack, so the callee pops nothing and the caller owns the stack
// cleanup; with no ordinary stack argument the receiver is in ECX and the
// convention is __thiscall.
//
// The single memory operand is a 32-bit read at 0x84 of the receiver. It is
// spelled as a displacement, NOT as `receiver->member`: the disassembly fixes a
// displacement, a width and a base register, and it fixes nothing about which
// member of any type occupies that word. The derived receiver record says so
// itself (`register=ECX`, `offsets=[0x84]`, `bounds_only=true`).
//
// The comparison value 0x3 is spelled as a constant, NOT as a member of a named
// enumeration. The `CMP` immediate is the whole of the evidence about it: nothing
// in this package enumerates the values the word at 0x84 can take, so naming one
// of them would invent the enumeration the body does not show.

namespace openspore::reconstruction::pkg_00c44c80_state_eq3 {

bool PKG_00C44C80_THISCALL state_word_eq3_00c44c80(OpaqueReceiver* receiver) {
  // 0x00c44c80 XOR EAX,EAX
  //
  // The return register is cleared in full before the comparison is made. This is
  // not a redundant prologue: it is what makes the single-byte `SETZ` below
  // sufficient, because only the low byte of EAX is written afterwards and the
  // three bytes above it would otherwise carry whatever the caller left there.
  // It is also the reason the value this body returns is 0 or 1 and never a
  // stale word in the upper three bytes.
  //
  // 0x00c44c82 CMP dword ptr [ECX + 0x84],0x3
  //
  // The only memory operand in the body: one 32-bit load at displacement 0x84 of
  // the receiver, compared against the immediate 0x3. `CMP` sets ZF from the
  // equality of the two and writes no register, so the load is the only thing
  // this body does to memory - it stores nothing.
  const std::uint32_t word =
      *reinterpret_cast<const std::uint32_t*>(reinterpret_cast<std::uintptr_t>(receiver) + 0x84);

  // 0x00c44c89 SETZ AL
  // 0x00c44c8c RET
  //
  // ZF is materialised into the low byte of the already-cleared EAX: the returned
  // value is 1 when the word equals 3 and 0 otherwise, and it is never anything
  // else - not the word itself, and not a truthy value of some other magnitude.
  // The comparison is on the full 32 bits, so a word of 0x103 is not 3 even
  // though its low byte is.
  return word == 0x3;
}

}

#undef PKG_00C44C80_THISCALL
