#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "get_proxy_id_00980510.hpp"

namespace openspore::reconstruction::pkg_utfwin_perspective_proxyid_00980510 {
namespace {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

struct OpaqueState {
  std::array<OpaqueWord, 12> words{};
};

OpaqueWord pointer_word(const void* pointer) {
  return static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

template <typename To, typename From>
OpaqueWord function_word(From function) {
  static_assert(sizeof(To) == sizeof(From), "function pointer width mismatch");
  OpaqueWord result{};
  std::memcpy(&result, &function, sizeof(result));
  return result;
}

template <typename To>
To function_from(OpaqueWord word) {
  static_assert(sizeof(To) == sizeof(OpaqueWord),
                "function pointer width mismatch");
  To result{};
  std::memcpy(&result, &word, sizeof(result));
  return result;
}

// Calls the reconstruction with the receiver in ECX, the way the vtable slot at
// +0x14 is reached, and reports whether the caller's stack came back balanced.
// A canary dword is pushed first; the callee's bare RET pops only the return
// address, so the canary must still be at (%esp) when control returns here. A
// callee that popped an argument would leave (%esp) four bytes lower and the
// comparison would read the caller's own frame instead.
OpaqueWord call_through_thiscall(OpaqueWord receiver, bool* stack_balanced) {
  OpaqueWord result = 0;
  OpaqueWord balanced = 0;
#if defined(__GNUC__) || defined(__clang__)
  __asm__ volatile(
      "pushl $0x5a5a5a5a\n\t"
      "movl %[receiver], %%ecx\n\t"
      "call get_proxy_id_00980510\n\t"
      "movl %%eax, %%edx\n\t"
      "cmpl $0x5a5a5a5a, (%%esp)\n\t"
      "sete %%cl\n\t"
      "movl %%edx, %%eax\n\t"
      "movzbl %%cl, %%edx\n\t"
      "addl $4, %%esp\n\t"
      : [result] "=&a"(result), [balanced] "=d"(balanced)
      : [receiver] "r"(receiver)
      : "ecx", "cc", "memory");
  *stack_balanced = balanced != 0u;
#else
  const ProxyIdSlot slot = get_proxy_id_00980510;
  result = slot(reinterpret_cast<PerspectiveEffect*>(receiver));
  *stack_balanced = true;
#endif
  return result;
}

// The one constant the body owns: a full 32-bit immediate, not a narrowed or
// sign-extended store.
void test_constant_is_0x202() {
  check(kPerspectiveEffectProxyId == 0x202u);
  check(kPerspectiveEffectProxyId == 514u);
  check((kPerspectiveEffectProxyId & 0xffff0000u) == 0u);
}

// The body is a constant function: it must ignore whatever the caller left in
// ECX, must not touch the receiver object, and must return the same 32-bit
// value for every receiver.
void test_receiver_independence() {
  OpaqueState state{};
  const OpaqueWord receiver = pointer_word(&state);
  const std::array<OpaqueWord, 12> before = state.words;

  const OpaqueWord receivers[] = {
      0u,
      0xffffffffu,
      0x00000001u,
      0xdeadbeefu,
      receiver,
      receiver + 0x10u,
  };

  bool balanced = false;
  for (const OpaqueWord candidate : receivers) {
    const OpaqueWord value = call_through_thiscall(candidate, &balanced);
    check(value == kPerspectiveEffectProxyId);
    check(value == 0x202u);
    check((value & 0xffff0000u) == 0u);
    check(balanced);
  }

  check(state.words == before);
}

// Slot +0x14 of the recorded vtable image holds this body, and the offset is
// fixed by the single reference word that reaches it.
void test_vtable_slot_placement() {
  PerspectiveEffectVTable vtable{};

  for (std::size_t index = 0; index < kPerspectiveEffectVTableSlotCount;
       ++index) {
    vtable.slot_00 = kPerspectiveEffectVTableImage[index];
  }

  check(kGetProxyIdSlotIndex == 5u);
  check(kGetProxyIdSlotOffset == 0x14u);
  check(kGetProxyIdSlotIndex * 4u == kGetProxyIdSlotOffset);
  check(kPerspectiveEffectVTableBase == 0x014440d0u);
  check(kPerspectiveEffectVTableBase + kGetProxyIdSlotOffset ==
        kGetProxyIdReferenceWord);
  check(kGetProxyIdReferenceWord == 0x014440e4u);
  check(kPerspectiveEffectVTablePredecessorTerminator == 0x00000000u);
  check(kPerspectiveEffectVTableImage[kGetProxyIdSlotIndex] == kGetProxyIdVa);
  check(kGetProxyIdVa == 0x00980510u);

  // The immediate neighbours of the target's slot, as recorded.
  check(kPerspectiveEffectVTableImage[4] == 0x00e31100u);
  check(kPerspectiveEffectVTableImage[6] == 0x00980520u);
  check(kPerspectiveEffectVTableImage[7] == 0x006f2f20u);

  // The function really is a slot-shaped callee: it converts to the slot type
  // and round-trips through a vtable word.
  const ProxyIdSlot from_code = get_proxy_id_00980510;
  check(function_word<ProxyIdSlot>(from_code) ==
        function_word<ProxyIdSlot>(get_proxy_id_00980510));
  vtable.slot_14 = function_word<ProxyIdSlot>(get_proxy_id_00980510);
  const ProxyIdSlot dispatched = function_from<ProxyIdSlot>(vtable.slot_14);

  OpaqueState state{};
  const OpaqueWord receiver = pointer_word(&state);
  const std::array<OpaqueWord, 12> before = state.words;
  check(dispatched(reinterpret_cast<PerspectiveEffect*>(receiver)) == 0x202u);
  check(dispatched(reinterpret_cast<PerspectiveEffect*>(0u)) == 0x202u);
  check(state.words == before);
}

// Zero stack words and zero callee cleanup: the return value is a plain 4-byte
// register result and the declared argument surface is the receiver alone.
void test_return_width_and_argument_surface() {
  static_assert(sizeof(decltype(get_proxy_id_00980510(nullptr))) == 4,
                "return value occupies one 32-bit register");
  check(sizeof(PerspectiveEffectVTable) == 0x60u);
  check(kPerspectiveEffectVTableSlotCount * 4u ==
        sizeof(PerspectiveEffectVTable));
}

}

int run_tests() {
  test_constant_is_0x202();
  test_receiver_independence();
  test_vtable_slot_placement();
  test_return_width_and_argument_surface();
  return 0;
}

}

int main() {
  return openspore::reconstruction::pkg_utfwin_perspective_proxyid_00980510::
      run_tests();
}
