#include "scalar_field_194_00b8dab0.hpp"

// The header undefines its convention macro, so it is respelled here; this is
// the same thiscall the entry declares.
#if defined(_MSC_VER)
#define PKG_00B8DAB0_THISCALL __thiscall
#else
#define PKG_00B8DAB0_THISCALL __attribute__((thiscall))
#endif

// 0x00b8dab0 FUN_00b8dab0 - a receiver-field scalar getter.
//
// Raw bytes 0x00b8dab0..0x00b8dab8:
//     8b 81 94 01 00 00      MOV EAX,dword ptr [ECX + 0x194]
//     c3                     RET
//     cc                     INT3 pad (NOT part of the body)
//
// ECX is the receiver. The body reads the one 32-bit word the receiver holds
// at displacement 0x194 and returns it in EAX. There is no branch, no call, no
// flag test, no register save and no loop in the body, so:
//   * the read happens on every entry - no lazy, cached or once-only path;
//   * the word is not modified by this function;
//   * the bare RET means the callee pops nothing, so with 0 ordinary stack
//     arguments the caller owns stack cleanup, and the convention is
//     __thiscall.
//
// Return: a 32-bit scalar. The four sampled callers of header note 7 use it in
// signed ordered comparisons against small constants (cmp eax,0x5/jz, cmp
// eax,0x2/jl, cmp eax,[esp+0x10]/jle), and one reduces a running maximum with
// it. None dereferences it. That is the reason the return is spelled as a
// scalar and not as a pointer, even though the derived ABI record classified
// the EAX value `pointer_like` - see header note 8, where the disagreement is
// recorded rather than papered over.
//
// The displacement is spelled literally as a value, NOT as `receiver->field`.
// The disassembly establishes the displacement (0x194), the width (32-bit) and
// the base (ECX); it establishes nothing about which member of any type
// occupies that word, and the receiver record says so itself
// (`offsets: [404]`, `bounds_only: true`). A member name here would be a
// field-identity assertion with nothing behind it.
//
// What is deliberately NOT done here:
//   * no null check and no default - a receiver word of zero comes back as a
//     published zero, because the body has no branch with which to do
//     otherwise;
//   * no mask, sign-extension, saturation or range check of any kind;
//   * no name for the word at +0x194 or for the receiver's class;
//   * no calling convention beyond the __thiscall the derived record names.

namespace openspore::reconstruction::pkg_00b8dab0_field194_getter {

std::uint32_t PKG_00B8DAB0_THISCALL scalar_field_194_00b8dab0(
    OpaqueReceiver* receiver) {
  // 0x00b8dab0 MOV EAX,dword ptr [ECX + 0x194]
  // 0x00b8dab6 RET
  //
  // The one computation this body makes, transcribed as the machine has it:
  // the 32-bit word at receiver+0x194 is read and its value is handed back.
  // Nothing is written - not to that word, not to any neighbour.
  //
  // The read is written as a displacement into the opaque receiver, NOT as
  // `receiver->field`. The machine proves the displacement and the width; it
  // does not prove which member of any type occupies that word.
  //
  // The value is copied bit for bit. Sign or zero extension does not happen
  // here; any ordered reading of the result is a property of the CALLERS'
  // comparisons, not of this body.
  return *reinterpret_cast<const std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(receiver) + 0x194);
}

}

#undef PKG_00B8DAB0_THISCALL