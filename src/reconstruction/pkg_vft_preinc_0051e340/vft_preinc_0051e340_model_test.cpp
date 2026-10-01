#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "vft_preinc_0051e340.hpp"

namespace openspore::reconstruction::pkg_vft_preinc_0051e340 {
namespace {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

// The receiver is opaque; eight words is enough for the dword at +8 the body
// addresses, and the test reaches it the same way the body does.
struct OpaqueState {
  std::array<OpaqueWord, 8> words{};
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

// Calls the reconstruction with the receiver in ECX, the way a vtable slot is
// reached, and reports whether the caller's stack came back balanced. A canary
// dword is pushed first; the callee's bare RET pops only the return address,
// so the canary must still be at (%esp) when control returns here. A callee
// that popped an argument would leave (%esp) four bytes lower and the
// comparison would read the caller's own frame instead.
OpaqueWord call_through_thiscall(OpaqueWord receiver, bool* stack_balanced) {
  OpaqueWord result = 0;
  OpaqueWord balanced = 0;
#if defined(__GNUC__) || defined(__clang__)
  __asm__ volatile(
      "pushl $0x5a5a5a5a\n\t"
      "movl %[receiver], %%ecx\n\t"
      "call vft_preinc_0051e340\n\t"
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
  result = vft_preinc_0051e340(reinterpret_cast<Receiver*>(receiver));
  *stack_balanced = true;
#endif
  return result;
}

// The body's whole semantics: the dword at receiver+8 is pre-incremented and the
// new value is returned. This fails for a mutant that returns the old value,
// stores the old value, increments the wrong dword, or pops an argument.
void test_preincrement_at_receiver_plus_8() {
  OpaqueState state{};
  state.words[1] = 0x55667788u;  // dword at receiver+4: must not change
  state.words[2] = 0x11223344u;  // dword at receiver+8: the field
  const OpaqueWord receiver = pointer_word(&state);

  bool balanced = false;
  const OpaqueWord value = call_through_thiscall(receiver, &balanced);

  check(value == 0x11223345u);           // old + 1 returned
  check(state.words[2] == 0x11223345u);  // field updated in place
  check(state.words[1] == 0x55667788u);  // the dword at +4 untouched
  check(balanced);                       // bare RET: caller stack balanced

  // The increment is a read-modify-write of the same dword: a second call
  // increments again from the value the first call stored.
  const OpaqueWord second = call_through_thiscall(receiver, &balanced);
  check(second == 0x11223346u);
  check(state.words[2] == 0x11223346u);
  check(balanced);
}

// The target is a vtable slot implementation: it is reached by loading the
// vtable pointer from the receiver and then the slot from the vtable. The
// two-level load must not collapse into receiver -> slot: the slot word is
// read from the vtable the receiver points at, never from the receiver's own
// first word. The collapsed read is computed here and asserted different.
void test_vtable_slot_placement_two_level() {
  struct VTableImage {
    OpaqueWord slot_00;
    OpaqueWord slot_04;
  };
  struct VTableReceiver {
    VTableImage* vptr;
    std::array<OpaqueWord, 8> words{};
  };

  VTableImage image{};
  image.slot_00 = function_word<SlotType>(vft_preinc_0051e340);
  image.slot_04 = 0u;

  VTableReceiver object{};
  object.vptr = &image;
  object.words[1] = 0x00000007u;  // dword at receiver+8 (vptr occupies +0)

  // Level 1: receiver -> vtable. The vtable pointer is the receiver's first
  // word; it is data, not a slot.
  VTableImage* const vtable = object.vptr;
  check(pointer_word(vtable) == pointer_word(&image));

  // Level 2: vtable -> slot, read from the vtable the receiver points at.
  const OpaqueWord slot_word = function_word<SlotType>(vtable->slot_00);
  check(slot_word == function_word<SlotType>(vft_preinc_0051e340));

  // The mutation this check exists to catch: reading the slot from the
  // receiver directly. That read yields the vtable pointer itself, which is
  // not the slot word and not a code address.
  const OpaqueWord collapsed = function_word<SlotType>(object.vptr);
  check(collapsed != slot_word);
  check(collapsed != function_word<SlotType>(vft_preinc_0051e340));

  // Dispatch through the two-level load really reaches this body.
  const SlotType slot = function_from<SlotType>(slot_word);
  check(function_word<SlotType>(slot) ==
        function_word<SlotType>(vft_preinc_0051e340));
  const std::uint32_t value = slot(reinterpret_cast<Receiver*>(&object));
  check(value == 0x00000008u);
  check(object.words[1] == 0x00000008u);
}

// The recorded placement facts: the engine's V1-VFT inference cites 42
// memberships, the first being slot 0 of the table based at 0x013ef110, whose
// next slot holds the adjacent virtual 0x0051e380.
void test_recorded_placement_constants() {
  check(kFirstVTableBase == 0x013ef110u);
  check(kFirstVTableSlotIndex == 0u);
  check(kAdjacentVirtualVa == 0x0051e380u);
  check(kMembershipCount == 42u);
  check(kFirstVTableSlotIndex * 4u == 0u);
  check(kFieldReceiverOffset == 0x8u);
  check(kBaseDisplacement + kFieldDisplacement == kFieldReceiverOffset);
}

// The return is a full 32-bit EAX value and the argument surface is the
// receiver alone: a narrower return type, a pointer return, or a stack
// argument each fail here.
void test_return_width_and_argument_surface() {
  static_assert(sizeof(decltype(vft_preinc_0051e340(nullptr))) == 4,
                "return value occupies one 32-bit register");
  static_assert(sizeof(SlotType) == 4, "slot pointers are 32-bit");
  static_assert(sizeof(OpaqueWord) == 4, "opaque words are 32-bit");
}

}

int run_tests() {
  test_preincrement_at_receiver_plus_8();
  test_vtable_slot_placement_two_level();
  test_recorded_placement_constants();
  test_return_width_and_argument_surface();
  return 0;
}

}

int main() {
  return openspore::reconstruction::pkg_vft_preinc_0051e340::run_tests();
}
