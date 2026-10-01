#include "simulator_slot_getter_00b3d390.hpp"

// 0x00b3d390 FUN_00b3d390 - a borrowed global-slot reader.
//
// Raw bytes 0x00b3d390..0x00b3d396:
//     a1 08 eb 67 01      MOV EAX,dword ptr ds:[0x0167eb08]
//     c3                  RET
//
// The body loads the single 4-byte word at 0x0167eb08 into EAX and returns.
// There is no branch, no call, no flag test, no register save, no loop and NO
// STORE anywhere in it, so:
//   * the read happens on every entry - there is no lazy, cached or
//     once-only path, and no publication check of any kind;
//   * the slot is not modified by this function;
//   * a bare RET means the callee pops nothing, so with 0 ordinary stack
//     arguments the caller owns the stack cleanup;
//   * ECX is never read in any form, so there is no register receiver.
//
// Return: the word's VALUE, moved to EAX, reinterpreted as the object pointer
// that sampled callers demonstrably use as such - 0x00bf6f72 moves it straight
// into ECX as the receiver of a call, and 0x00b5feeb pushes it straight as a
// stack argument. It is a load, not a LEA and not an immediate - both of those
// forms exist in the very same accessor block, at 0x00b3d220
// (`MOV EAX,0x0167eac0`) for the table address.
//
// The pointee's class is UNKNOWN and NO field offset on it is claimed. The SDK
// import names this slot's neighbours but leaves 0x0167eb08 unnamed, and the
// two canonical manager slots that Phase 0 did name live in the same table
// without making any of the 43 slots a manager. The returned type is opaque,
// declares no member, and models no size.
//
// What is deliberately NOT done here:
//   * no null check, no default, no fallback - the slot is returned as stored,
//     including a stored zero, which is its load-time value;
//   * no AddRef/Release - the sampled uses borrow, and the body has no room for
//     a reference call;
//   * no name for the slot or the object, because no SDK import or committed
//     research note names this one;
//   * no calling convention - a zero-parameter entry's encoding is identical
//     under all four candidates, and the derived ABI record abstains.

namespace openspore::reconstruction::pkg_00b3d390_simulator_slot_getter {

OpaqueSimulatorSingleton* simulator_slot_getter_00b3d390() {
  // 0x00b3d390 MOV EAX,dword ptr ds:[0x0167eb08]
  // 0x00b3d395 RET
  //
  // The one thing this body computes, transcribed as the machine has it: the
  // 32-bit word stored in the uninitialised .data slot 0x0167eb08 is read and
  // its value is handed back. Nothing is written - not to the slot, not
  // anywhere else.
  return reinterpret_cast<OpaqueSimulatorSingleton*>(
      static_cast<std::uintptr_t>(DAT_0167eb08));
}

}
