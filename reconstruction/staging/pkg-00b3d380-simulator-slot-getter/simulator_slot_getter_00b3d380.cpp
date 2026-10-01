#include "simulator_slot_getter_00b3d380.hpp"

// 0x00b3d380 FUN_00b3d380 - a borrowed global-slot reader.
//
// Raw bytes 0x00b3d380..0x00b3d386:
//     a1 04 eb 67 01      MOV EAX,dword ptr ds:[0x0167eb04]
//     c3                  RET
//
// The body loads the single 4-byte word at 0x0167eb04 into EAX and returns.
// There is no branch, no call, no flag test, no register save, no loop and NO
// STORE anywhere in it, so:
//   * the read happens on every entry - there is no lazy, cached or
//     once-only path, and no publication check of any kind;
//   * the slot is not modified by this function;
//   * a bare RET means the callee pops nothing, so with 0 ordinary stack
//     arguments the caller owns the stack cleanup;
//   * ECX is never read in any form, so there is no register receiver.
//
// Return: the word's VALUE, moved to EAX, reinterpreted as the pointer that
// three sampled callers demonstrably dereference (0x01042450, 0x01017b70,
// 0x01017ce0 all read result+0x48). It is a load, not a LEA and not an
// immediate - both of those forms exist in the very same accessor block, at
// 0x00b3d220 (`MOV EAX,0x0167eac0`) for the table address, so the distinction
// is not hypothetical here.
//
// The pointee's class is UNKNOWN. The word is returned as a pointer only
// because the callers dereference it; the returned type is opaque, declares no
// member, and the one offset the evidence reaches (+0x48) is a caller-side
// observation that this translation unit does not itself use.
//
// What is deliberately NOT done here:
//   * no null check, no default, no fallback - the slot is returned as stored,
//     including a stored zero;
//   * no AddRef/Release - the header's call sites borrow, and the body has no
//     room for a reference call;
//   * no name for the slot or the object, because no SDK import or committed
//     research note names this one (see the header's evidence notes 6 and 7);
//   * no calling convention - a zero-parameter entry's encoding is identical
//     under all four candidates, and the derived ABI record abstains.

namespace openspore::reconstruction::pkg_00b3d380_simulator_slot_getter {

OpaqueSimulatorSingleton* simulator_slot_getter_00b3d380() {
  // 0x00b3d380 MOV EAX,dword ptr ds:[0x0167eb04]
  // 0x00b3d385 RET
  //
  // The one thing this body computes, transcribed as the machine has it: the
  // 32-bit word stored at the .data slot 0x0167eb04 is read and its value is
  // handed back. Nothing is written - not to the slot, not anywhere else.
  return reinterpret_cast<OpaqueSimulatorSingleton*>(
      static_cast<std::uintptr_t>(DAT_0167eb04));
}

}
