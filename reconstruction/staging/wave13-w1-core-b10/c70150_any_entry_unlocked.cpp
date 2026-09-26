#include "c70150_any_entry_unlocked.hpp"

namespace openspore::reconstruction::wave13_w1_core_b10 {

namespace {

// 0x0167a60c, read at 0x00c70205 and written at 0x00c70233. The live dword is
// 0x00000000. 0x00ae5c30 writes this same slot from inside its own constructor
// (param_1 -> DAT_0167a60c), so the store at 0x00c70233 is a second,
// redundant publication of the same pointer.
OpaqueSimSingleton** const kSimSingletonSlot =
    reinterpret_cast<OpaqueSimSingleton**>(0x0167a60cUL);

}  // namespace

std::uint8_t B10_CDECL SimOwner_AnyEntryUnlocked_00c70150(
    OpaqueSimTokenOwner* owner, void* key_or_context,
    OpaqueSimKeySource* key_source, std::uint8_t strict_flag) {
  (void)key_or_context;

  // 0x00c70158: MOV ECX,ESI ; CALL 0x00b8dab0 -> *(owner + 0x194)
  // 0x00c7015d: CMP EAX,0x5 ; JZ 0x00c70167
  // 0x00c70162: XOR AL,AL -> the only exit before the loop
  if (Port_00b8dab0_GetKind(owner) != 5u) {
    return 0;
  }

  // 0x00c70168..0x00c70177: count = (mListEnd - mListBegin) >> 2, computed
  // with SUB and a signed SAR by 2, not a DIV.
  const std::int32_t count = static_cast<std::int32_t>(
      (owner->mListEnd - owner->mListBegin) >> 2);

  // 0x00c70194: the base is loaded from the frame, then indexed as a dword
  // array, so the array starts at offset 0 of the key source.
  const auto* const key_entries =
      reinterpret_cast<const std::uint32_t*>(key_source);

  for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(count); ++i) {
    OpaqueSimChild* child =
        reinterpret_cast<OpaqueSimChild*>(const_cast<std::uint32_t*>(
            key_entries)[i]);

    // 0x00c701a1: MOV EDI,dword ptr [ECX + 0x84] of the key source
    // 0x00c701ae: CMP EAX,EDI ; JNZ 0x00c701f3
    if (Port_00ff0420_GetChildKey(child) != key_source->mKey84) {
      continue;
    }

    // 0x00c701b4 CALL 0x005c65e0 then 0x00c701bb MOV ESI,[EBP + 0x4] and
    // 0x00c701be SUB ESI,[EBP]: the pair read is the element's own +0x3c and
    // +0x40 dwords, and 0x00c701c3 shifts the difference right by 2.
    OpaqueSimChild* const list = Port_005c65e0_GetChildVectorBase(child);
    const std::int32_t inner = static_cast<std::int32_t>(
        (list->mListEnd40 - list->mListBegin3c) >> 2);

    for (std::uint32_t j = 0; j < static_cast<std::uint32_t>(inner); ++j) {
      // 0x00c701d0: CMP byte ptr [ESP + 0x20],0x0 ; JZ 0x00c70243
      // The flag inverts the loop: a zero flag accepts the first candidate
      // unconditionally, a non-zero flag demands the remaining-count test.
      if (strict_flag == 0u) {
        return 1;
      }

      OpaqueSimChild* element =
          reinterpret_cast<OpaqueSimChild*>(list->mListBegin3c +
                                            j * sizeof(std::uint32_t));

      // 0x00c701e5: CMP EAX,0x1 ; JG 0x00c70243
      if (Port_00ff0870_GetRemaining(element) > 1) {
        return 1;
      }
    }
  }

  // 0x00c701fc: CALL 0x01021080 -> *(Simulator::sSpacePlayerData + 0x10)
  // 0x00c70203: JNZ 0x00c7024b, i.e. a non-zero answer ends in "no match"
  // rather than falling through to the singleton.
  if (Port_01021080_GetSpacePlayerFlag() == 0u) {
    OpaqueSimSingleton* singleton = *kSimSingletonSlot;
    if (singleton == nullptr) {
      // 0x00c70212: PUSH 0x145f924 -> the ASCII string
      // "Simulator/SimSingleton"; 0x00c70217: PUSH 0xc8 -> size 200.
      void* created = Port_00f473a0_Allocate(
          0xc8u, "Simulator/SimSingleton", nullptr, nullptr, nullptr,
          nullptr);
      // 0x00c70231: the allocation-failure path stores 0 explicitly.
      singleton = created != nullptr
                      ? Port_00ae5c30_ConstructSimSingleton(created)
                      : nullptr;
      *kSimSingletonSlot = singleton;
    }

    // 0x00c7023a: CALL 0x00ae3740 -> byte ( *(this + 0x28) != this + 0x28 )
    // 0x00c70241: JZ 0x00c7024b
    if (Port_00ae3740_HasQueueEntries(singleton) != 0u) {
      return 1;
    }
  }

  return 0;
}

}  // namespace openspore::reconstruction::wave13_w1_core_b10
