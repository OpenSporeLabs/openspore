#include "global_singleton_00d38840.hpp"

// 0x00d38840 FUN_00d38840 - a global-instance accessor returning a POINTER.
//
// Raw bytes 0x00d38840..0x00d38849:
//     a1 94 e2 69 01      MOV EAX,dword ptr [0x0169e294]
//     c3                  RET
//     cc cc cc cc         INT3 pad (NOT part of the body)
//
// Opcode 0xa1 is the absolute form: it takes a 32-bit address as its only
// operand and has NO ModRM byte and NO base register. That single fact fixes
// three things at once, and they are the whole content of this
// reconstruction:
//
//   * the base of the access is a fixed global, not a receiver - which is why
//     there is no __thiscall here and why the ABI record's receiver is absent
//     (`present: false`, `distinct_offsets: 0`, `register: null`);
//   * the access is a plain dword load - there is no index, no scale and no
//     displacement to be confused with a member offset, so the "is this
//     displacement a byte offset or an element index" hazard that a
//     `[ECX + disp]` family has simply does not arise here;
//   * the access is a READ - opcode 0xa1 is the load direction; the store
//     direction is 0xa3, and no store appears in the body.
//
// Because there is no branch, no call, no flag test, no register save and no
// loop, the load happens on every entry and nothing else does: no lazy path,
// no cache, no publication check, no default, no refresh. A slot holding null
// comes back as a slot holding null.
//
// Return: a POINTER, and that is a claim the WRITER and the CALLERS make rather
// than one the body makes. The single recorded writer of the slot, the function
// at 0x00d3b9b0, is a constructor-shaped body that stores its own incoming
// object pointer into the slot at 0x00d3baae (`MOV [0x0169e294], ESI`) and then
// returns that same pointer - so the slot is published as an object address.
// On the reading side, the caller at 0x00d4c5e0 calls this entry twice and each
// time moves the result into ECX before calling a member function
// (0x00d39360, whose live signature names its first parameter
// `cCreatureModeStrategy *this`), which is receiver use; and readers at
// 0x00d395a4, 0x00d2b6e0 and 0x00d2c280 index through the loaded word at
// displacements 0x24, 0xdc and 0xb4.
//
// The declared type is `void*`, NOT `cCreatureModeStrategy*`, and that is
// deliberate. The Ghidra label on the slot is `App::sCreatureModeStrategy` while
// the callee names a TYPE `App::cCreatureModeStrategy`; this binary carries no
// RTTI, so nothing machine-derived ties the slot to that class, and the derived
// ABI record's own `pointer_like` classification is INFERRED with
// `corroboration: not_available`. `void*` is the weakest C type that states the
// observed use. It names no pointee type, no pointee layout and no pointee
// size; the displacements other functions reach are not used to bound anything.
//
// What is deliberately NOT done here:
//   * no null check, no default and no fallback - the body has no branch with
//     which to do either;
//   * no name for the class of the object the slot points at;
//   * no calling convention macro at all: the body is byte-identical under
//     __cdecl, __stdcall, __thiscall and __fastcall, because it takes no
//     parameter and pops nothing, so picking one would be an invention;
//   * no assumption that the slot is initialised. The .data bytes at
//     0x0169e294 read as zero in the uninitialised image, which says nothing
//     about the running process.

namespace openspore::reconstruction::pkg_00d38840_global_singleton_getter {

// Definition of the modelled slot. Zero-initialised, exactly as the four bytes
// of `.data` at 0x0169e294 read in the uninitialised image; the test overwrites
// it before every call and its plant is the only thing that makes a
// load-versus-store distinction visible.
SlotWord g_creature_mode_strategy_slot = 0u;

void* global_singleton_00d38840() {
  // 0x00d38840 MOV EAX,dword ptr [0x0169e294]
  // 0x00d38845 RET
  //
  // The one computation this body makes, transcribed as the machine has it: the
  // 32-bit word the absolute address names is read, and its bits are handed
  // back in EAX re-typed as an address.
  //
  // The bits are copied verbatim. The re-typing to a pointer is the only
  // transformation - no arithmetic, no masking, no sign extension, no
  // saturation, no comparison and no branch. The read is NOT written as a
  // dereference of anything this package owns, because 0x0169e294 is an address
  // in the ORIGINAL image: the model stands the slot up as the object
  // g_creature_mode_strategy_slot and reads that, which is the same read with
  // the original's data section made addressable.
  //
  // Nothing is written - not to the slot, not to any neighbour, and there is no
  // reference call, no addref and no release in the body.
  return reinterpret_cast<void*>(
      static_cast<std::uintptr_t>(g_creature_mode_strategy_slot));
}

}