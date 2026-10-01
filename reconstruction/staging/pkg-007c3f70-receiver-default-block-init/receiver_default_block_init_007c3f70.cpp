#include "receiver_default_block_init_007c3f70.hpp"

// The header undefines its convention macro, so it is respelled here; this is
// the same thiscall the entry declares and the derived ABI record names.
#if defined(_MSC_VER)
#define PKG_007C3F70_THISCALL __thiscall
#else
#define PKG_007C3F70_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_007c3f70_receiver_default_block_init {

// The host-supplied stand-in for the five absolute addresses the body loads
// from. Named without the target VA on purpose: only the reconstructed entry may
// carry the 8-hex address in this package.
OpaqueGlobalSource g_global_source;

// The slot-to-address table. It is a function rather than an inline array so the
// table cannot become a second symbol carrying the target VA.
//
// The first four addresses are consecutive and the fifth is not: the artifact
// places the first four in a writable segment and the fifth in a read-only one.
std::uint32_t global_slot_address(std::size_t slot) {
  switch (slot) {
    case kSlotFirstWord:
      return kGlobalFirstWordAddress;
    case kSlotSecondWord:
      return kGlobalSecondWordAddress;
    case kSlotThirdWord:
      return kGlobalThirdWordAddress;
    case kSlotFourthWord:
      return kGlobalFourthWordAddress;
    case kSlotSharedReadOnly:
      return kGlobalSharedReadOnlyAddress;
    default:
      break;
  }
  // Unreachable from the entry: every slot it reads is named above. The body
  // states five load sites and this table states five addresses, so a slot
  // outside them is a caller-side error, not a machine behaviour.
  return kGlobalFirstWordAddress;
}

Float read_global_float(std::size_t slot) {
  return g_global_source.words[slot];
}

// 0x007c3f70 -- the reconstructed entry.
//
// Thirteen receiver writes, five global reads, no branch, no call, no stack
// slot, no register save. Each comment below names the instruction it
// transcribes and its address.
void PKG_007C3F70_THISCALL receiver_default_block_init_007c3f70(OpaqueReceiver* receiver) {
  // 0x007c3f70  MOVSS XMM0,dword ptr [0x01635db8]
  // The FIRST load happens BEFORE the receiver is copied out of ECX. Ordering is
  // preserved deliberately: the machine performs this read while the receiver is
  // still only in ECX, and a reconstruction that copied first would be a
  // different body even though the two agree on the final bytes.
  const Float first = read_global_float(kSlotFirstWord);

  // 0x007c3f78  MOV EAX,ECX
  // The receiver's single read. EAX -- not ECX -- is the base register for all
  // thirteen stores, which is why the body can afford to destroy ECX at
  // 0x007c3fba. `receiver` stands in for that EAX copy from here on.

  // 0x007c3f7a  MOVSS dword ptr [EAX+0x140],XMM0
  store_float(receiver, kFieldFirstLoadedFloat, first);

  // 0x007c3f82  MOVSS XMM0,dword ptr [0x01635dbc]
  // 0x007c3f8a  MOVSS dword ptr [EAX+0x144],XMM0
  const Float second = read_global_float(kSlotSecondWord);
  store_float(receiver, kFieldSecondLoadedFloat, second);

  // 0x007c3f92  MOVSS XMM0,dword ptr [0x01635dc0]
  // 0x007c3f9a  MOVSS dword ptr [EAX+0x148],XMM0
  const Float third = read_global_float(kSlotThirdWord);
  store_float(receiver, kFieldThirdLoadedFloat, third);

  // 0x007c3fa2  MOVSS XMM0,dword ptr [0x01635dc4]
  // 0x007c3faa  MOVSS dword ptr [EAX+0x14c],XMM0
  const Float fourth = read_global_float(kSlotFourthWord);
  store_float(receiver, kFieldFourthLoadedFloat, fourth);

  // 0x007c3fb2  MOVSS XMM0,dword ptr [0x013f0620]
  // The FIFTH load, and the only one whose value is used more than once. It is
  // read ONCE. A body that re-loaded the global between the four stores below
  // would be a different machine body, and the model test's decoys exist to kill
  // exactly that shape.
  const Float shared = read_global_float(kSlotSharedReadOnly);

  // 0x007c3fba  XOR ECX,ECX
  // The receiver register is destroyed here and never re-read as a pointer. The
  // zero this produces is the immediate source of the next three stores AND of
  // the word eleven instructions below; `self` above is what keeps the receiver
  // address alive across this point, which is what `MOV EAX,ECX` does in the
  // machine -- `receiver` is that copy, so it stays usable after the zeroing.

  // 0x007c3fbc  MOV dword ptr [EAX+0x150],ECX
  store_word(receiver, kFieldFirstZeroWord, 0);
  // 0x007c3fc2  MOV dword ptr [EAX+0x154],ECX
  store_word(receiver, kFieldSecondZeroWord, 0);
  // 0x007c3fc8  MOV dword ptr [EAX+0x158],ECX
  store_word(receiver, kFieldThirdZeroWord, 0);

  // 0x007c3fce  MOVSS dword ptr [EAX+0x15c],XMM0
  store_float(receiver, kFieldFirstSharedFloat, shared);
  // 0x007c3fd6  MOVSS dword ptr [EAX+0x160],XMM0
  store_float(receiver, kFieldSecondSharedFloat, shared);
  // 0x007c3fde  MOVSS dword ptr [EAX+0x164],XMM0
  store_float(receiver, kFieldThirdSharedFloat, shared);
  // 0x007c3fe6  MOVSS dword ptr [EAX+0x168],XMM0
  store_float(receiver, kFieldFourthSharedFloat, shared);

  // 0x007c3fee  MOV byte ptr [EAX+0x16c],0x1
  // One byte, immediate 0x1. Written as a byte store and not as a word: the
  // word at 0x16c is never touched, and the following byte is not clobbered.
  store_byte(receiver, kFieldFlagByte, kFlagByteImmediate);

  // 0x007c3ff5  MOV dword ptr [EAX+0x170],ECX
  // The trailing zeroed word. The same ECX=0 produced at 0x007c3fba reaches this
  // store too; nothing overwrites it in between.
  store_word(receiver, kFieldTrailingZeroWord, 0);

  // 0x007c3ffb  RET
  // Bare, no immediate: the callee pops nothing and the caller owns the stack.
  //
  // Nothing is returned. Every XMM0 write in the body is consumed by a store into
  // the receiver, and the last instruction that defines any register at all is
  // the byte immediate above. XMM0 does still hold the shared word at this
  // RET -- nothing writes it after 0x007c3fb2 -- but whether any call site reads
  // it was not established, so it is documented and not returned.
}

}

#undef PKG_007C3F70_THISCALL