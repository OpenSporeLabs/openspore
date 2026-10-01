#include "slot_1e8_00970b30.hpp"

// The header undefines its convention macro, so it is respelled here; this is
// the same thiscall the entry declares.
#if defined(_MSC_VER)
#define PKG_00970B30_THISCALL __thiscall
#else
#define PKG_00970B30_THISCALL __attribute__((thiscall))
#endif

// 0x00970b30 FUN_00970b30 - a receiver-slot getter returning a POINTER.
//
// Raw bytes 0x00970b30..0x00970b38:
//     8b 81 e8 01 00 00      MOV EAX,dword ptr [ECX + 0x1e8]
//     c3                     RET
//     cc                     INT3 pad (NOT part of the body)
//
// ECX is the receiver. The body reads the one 32-bit word the receiver holds
// at displacement 0x1e8 and hands it back in EAX. There is no branch, no call,
// no flag test, no register save and no loop in the body, so:
//   * the read happens on every entry - no lazy, cached or once-only path;
//   * the word is not modified by this function, and nothing else is;
//   * the bare RET means the callee pops nothing, so with 0 ordinary stack
//     arguments the caller owns stack cleanup, and the convention is
//     __thiscall.
//
// Return: a POINTER, and that is a claim the CALLERS make rather than one the
// body makes. Three sampled callers decompiled live all use the result as an
// address: 0x00c4b250 and 0x00c4c090 each load through it at displacement
// 0x13c, and 0x00c61070 tests it against 0 before loading through it. So the
// return type is `void*` - the weakest C type that states the observed use.
// It names no pointee type: the pointee's layout is unknown to this package and
// is deliberately not modelled. Note that the derived ABI record's own
// `register_class: pointer_like` is NOT the reason for this type; that
// heuristic is INFERRED with `corroboration: not_available` and cannot
// distinguish a loaded word from a computed address. The callers are.
//
// The immediately preceding entry in the image, at 0x00970b10, is this slot's
// SETTER: `mov edx,[esp+4] ; mov eax,1 ; mov [ecx+0x9c],eax ;
// mov [ecx+0x1e8],edx ; ret 0x4`. Same receiver, same displacement, one stack
// argument. That is what makes 0x1e8 a real read/write slot rather than a
// displacement this body happens to compute, and it is pinned in the test. That
// neighbouring code carries no function record in the program database, so it
// is cited as decoded adjacent code and not as a reconstructed function.
//
// The displacement is spelled literally as a value, NOT as `receiver->slot`.
// The disassembly establishes the displacement (0x1e8), the width (32-bit) and
// the base (ECX); it establishes nothing about which member of any type
// occupies that word, and the receiver record says so itself
// (`offsets: [488]`, `bounds_only: true`). A member name here would be a
// field-identity assertion with nothing behind it.
//
// What is deliberately NOT done here:
//   * no null check and no default - a stored null comes back as a published
//     null, because the body has no branch with which to do otherwise;
//   * no mask, sign-extension, saturation or range check of any kind;
//   * no name for the slot at +0x1e8, for the receiver's class, or for the
//     pointee;
//   * no calling convention beyond the __thiscall the derived record names.

namespace openspore::reconstruction::pkg_00970b30_slot_1e8_getter {

void* PKG_00970B30_THISCALL slot_1e8_00970b30(OpaqueReceiver* receiver) {
  // 0x00970b30 MOV EAX,dword ptr [ECX + 0x1e8]
  // 0x00970b36 RET
  //
  // The one computation this body makes, transcribed as the machine has it:
  // the 32-bit word at receiver+0x1e8 is read and its bits are reinterpreted
  // as an address, which is what the sampled callers then dereference.
  // Nothing is written - not to that word, not to any neighbour.
  //
  // The read is written as a displacement into the opaque receiver, NOT as
  // `receiver->slot`. The machine proves the displacement and the width; it
  // does not prove which member of any type occupies that word.
  //
  // The bits are copied verbatim. The reinterpretation to a pointer is the only
  // transformation, and it is a re-typing of the same 32 bits - no arithmetic,
  // no masking, no sign extension.
  return reinterpret_cast<void*>(static_cast<std::uintptr_t>(
      field_at(receiver, kFieldDisplacement)));
}

}

#undef PKG_00970B30_THISCALL