#include "simulator_receiver_slot_00bd81d0.hpp"

// 0x00bd81d0 FUN_00bd81d0 - a receiver-relative integer field accessor.
//
// Raw bytes 0x00bd81d0..0x00bd81d7:
//     8b 81 40 05 00 00   MOV EAX,dword ptr [ECX + 0x540]
//     c3                  RET
//
// The body reads the single 32-bit word at receiver+0x540 and returns it in
// EAX. There is no branch, no call, no flag test, no register save, no loop and
// NO STORE anywhere in it, so:
//   * the read happens on every entry - there is no lazy, cached or
//     once-only path, and no publication check of any kind;
//   * the field is not modified by this function;
//   * ECX is dereferenced once, directly, with no write through it, so it is a
//     receiver and not an ordinary first argument;
//   * a bare RET means the callee pops nothing, so the caller owns stack
//     cleanup. The enclosing accessor block does contain members that DO pop,
//     with `RET 4` at 0x00bd81c0 and 0x00bd81e0, so the distinction is one the
//     binary actually makes rather than a formality.
//
// Return: the word's VALUE, as a 32-bit integer. It is spelled `uint32_t`
// because the body performs no sign extension and moves the raw 32 bits; see
// the header's note 4 and 5 for why the ABI record's `pointer_like` label is
// not adopted, and why no enum type or enumerator name is claimed. Sampled
// callers compare the result against 0, 1, 2 and -1 and pass it straight
// through as an integer argument.
//
// What is deliberately NOT done here:
//   * no null or bounds check on the receiver - the body has no room for a
//     branch and performs none;
//   * no clamp, no default, no normalisation - the stored bit pattern is
//     returned verbatim, including 0 and 0xffffffff;
//   * no name for the receiver class or for the field, because no SDK import,
//     namespace or committed research note names either;
//   * no conversion to a signed or enumerated type, because that would be a
//     claim about a domain the evidence does not supply.

namespace openspore::reconstruction::pkg_00bd81d0_receiver_slot_getter {

// The declared return is spelled `uint32_t` rather than this package's
// `SlotWord` alias. The alias IS `std::uint32_t` and the header asserts its
// width; the validator measures the *declared* return's width from the
// spelling and an alias names no width, so the alias spelling made this
// dimension NOT_AVAILABLE on a body whose machine return width is proven.
// Same type, one token changed.
uint32_t simulator_receiver_slot_00bd81d0(
    const OpaqueSimulatorReceiver* receiver){
  // 0x00bd81d0 MOV EAX,dword ptr [ECX + 0x540]
  // 0x00bd81d6 RET
  //
  // The one thing this body computes, transcribed as the machine has it: the
  // 32-bit word stored at receiver+0x540 is read and its value is handed back.
  // Nothing is written - not to the field, not anywhere else.
  return *reinterpret_cast<const SlotWord*>(
      reinterpret_cast<const unsigned char*>(receiver) + kSlotOffset);
}

}
