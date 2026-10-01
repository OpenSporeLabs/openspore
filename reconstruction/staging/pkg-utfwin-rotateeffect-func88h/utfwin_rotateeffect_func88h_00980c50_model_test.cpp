#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "utfwin_rotateeffect_func88h_00980c50.hpp"

namespace openspore::reconstruction::pkg_utfwin_rotateeffect_func88h {
namespace {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

Opaque pointer_word(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

template <typename To, typename From>
Opaque function_word(From function) {
  static_assert(sizeof(To) == sizeof(From), "function pointer width mismatch");
  Opaque result{};
  std::memcpy(&result, &function, sizeof(result));
  return result;
}

template <typename To>
To function_from(Opaque word) {
  static_assert(sizeof(To) == sizeof(Opaque),
                "function pointer width mismatch");
  To result{};
  std::memcpy(&result, &word, sizeof(result));
  return result;
}

// The block at 0x00980c80 is not a claimed reconstruction, so the test supplies
// the oracle. It reproduces the four facts the constant-pairing argument
// rests on: the receiver is read from the stack, nothing is written unless the
// receiver and the word are both non-zero, the written value is exactly
// 0xCF2B2AD5, and the result is 1 whenever no store happened because the
// receiver was null.
extern "C" Opaque pkg_r8_re_00980c80(RotateEffectTokenWord* self,
                                     std::uint32_t word) {
  if (self != nullptr && word != 0u) {
    self->token_00 = kFunc88hToken;
  }
  return (self == nullptr) ? 0u : 1u;
}

// Pushes the three words the SDK method header declares and then removes them
// again, because 0x00980c50 ends in a bare RET and therefore cleans nothing.
// The three "arguments" are steered into EDX/ESI/EBX and the receiver into ECX
// so that the compiler cannot deduce the push count from the source.
Opaque call_three_argument(Opaque receiver, Opaque first, Opaque second,
                           Opaque third) {
  Opaque result = 0;
#if defined(__GNUC__) || defined(__clang__)
  __asm__ volatile(
      "pushl %[third]\n\t"
      "pushl %[second]\n\t"
      "pushl %[first]\n\t"
      "call func88h_00980c50\n\t"
      "movl %%eax, %[result]\n\t"
      "addl $12, %%esp\n\t"
      : [result] "=a"(result)
      : [receiver] "c"(receiver), [first] "D"(first), [second] "S"(second),
        [third] "b"(third)
      : "cc", "memory");
#else
  const TokenSlot slot = func88h_00980c50;
  result = slot(receiver, first, second, third);
#endif
  return result;
}

alignas(4) RotateEffectTokenWord receiver_storage{};

RotateEffectTokenWord* receiver() { return &receiver_storage; }

}  // namespace
}  // namespace openspore::reconstruction::pkg_utfwin_rotateeffect_func88h

using namespace openspore::reconstruction::pkg_utfwin_rotateeffect_func88h;

namespace {

void test_abi_record() {
  check(kFunc88hAbi.receiver_register == -1);
  check(kFunc88hAbi.ordinary_stack_words == 3);
  check(kFunc88hAbi.stack_cleanup_bytes == 0);
  check(std::strcmp(kFunc88hAbi.return_type, "std::uint32_t") == 0);
}

void test_constants_match_listing() {
  check(kFunc88hConstants.token == 0xcf2b2ad5u);
  check(kFunc88hConstants.token == kFunc88hToken);
  check(kFunc88hConstants.entry == 0x00980c50u);
  check(kFunc88hConstants.body_end_inclusive == 0x00980c55u);
  check(kFunc88hConstants.int3_pad_end == 0x00980c5fu);
  check(kFunc88hConstants.sole_data_xref == 0x01444364u);
  check(kFunc88hConstants.vtable_run_base == 0x01444364u);
  check(kFunc88hConstants.pairing_store_block == 0x00980c80u);
  check(kFunc88hConstants.pairing_store_end == 0x00980c9cu);
  check(kFunc88hConstants.adjustor_thunk_04 == 0x00980c60u);
  check(kFunc88hConstants.adjustor_thunk_0c == 0x00980c70u);
  check(kFunc88hConstants.adjustor_jump_target == 0x00980cb0u);
  check(kFunc88hConstants.vector_delete_entry == 0x0096ff20u);
  check(kFunc88hConstants.vector_delete_magic == 0xef2b293bu);
  check(kFunc88hConstants.objecttype_iperspective == 0xef2b293bu);
  // 0xCF2B2AD5 is not a member of the SDK ObjectTYPE family; the enum value
  // that does exist is 0xEF2B293B. The two must stay distinct.
  check(kFunc88hToken != kFunc88hConstants.vector_delete_magic);
  // The bare RET is what makes the caller, not the callee, pop the arguments.
  check(kFunc88hConstants.body_end_inclusive == kFunc88hConstants.entry + 5u);
}

// Slot +0x00 of the transcribed run is the sole reference to this target.
void test_vtable_run_holds_this_target() {
  check(kRotateEffectVTableRun.slot_00 == 0x00980c50u);
  check(kRotateEffectVTableRun.slot_00 == kFunc88hConstants.entry);
  check(offsetof(RotateEffectVTableRun, slot_00) == 0x00);
  check(kRotateEffectVTableRun.slot_04 == 0x00980320u);
  check(kRotateEffectVTableRun.slot_08 == 0x009800e0u);
  check(kRotateEffectVTableRun.slot_0c == 0x00980cb0u);
  check(kRotateEffectVTableRun.slot_10 == 0x0096ff20u);
  check(kRotateEffectVTableRun.slot_20 == 0x006f2f20u);
  check(kRotateEffectVTableRun.slot_2c == 0x006f2f20u);
}

// The slot is callable through a function pointer, and dispatching through the
// stored word yields the same constant as a direct call.
void test_dispatch_through_vtable_word() {
  RotateEffectVTableRun run{};
  run.slot_00 = function_word<TokenSlot>(func88h_00980c50);
  const TokenSlot slot = function_from<TokenSlot>(run.slot_00);
  check(slot == func88h_00980c50);
  check(call_three_argument(pointer_word(receiver()), 0u, 0u, 0u) ==
        kFunc88hToken);

  RotateEffectVTableRun minimal{};
  minimal.slot_00 = function_word<TokenGetSlot>(func88h_00980c50);
  const TokenGetSlot getter = function_from<TokenGetSlot>(minimal.slot_00);
  check(getter(pointer_word(receiver())) == kFunc88hToken);
}

// The return value is a fixed immediate: no argument and no receiver can
// change it. This is the core claim of the reconstruction.
void test_result_is_independent_of_every_input() {
  const Opaque receivers[] = {0u, 1u, 0xffffffffu, pointer_word(receiver())};
  const Opaque words[] = {0u, 1u, 0xef2b293bu, 0xffffffffu};
  for (const Opaque rcv : receivers) {
    for (const Opaque a : words) {
      for (const Opaque b : words) {
        for (const Opaque c : words) {
          check(call_three_argument(rcv, a, b, c) == kFunc88hToken);
        }
      }
    }
  }
}

// The frame performs no store: reaching it must leave the receiver untouched.
void test_frame_writes_no_memory() {
  receiver()->token_00 = 0x10203040u;
  check(call_three_argument(pointer_word(receiver()), 0x11111111u, 0u,
                            0xffffffffu) == kFunc88hToken);
  check(receiver()->token_00 == 0x10203040u);

  receiver()->token_00 = 0u;
  check(call_three_argument(0u, 0u, 0u, 0u) == kFunc88hToken);
  check(receiver()->token_00 == 0u);
}

// The strongest available corroboration that the immediate is meaningful:
// the block at 0x00980c80 stores exactly the value this target returns.
void test_constant_pairs_with_the_adjacent_store_block() {
  receiver()->token_00 = 0u;
  check(unresolved_contracts::pkg_r8_re_00980c80(receiver(), 1u) == 1u);
  check(receiver()->token_00 == kFunc88hToken);
  check(receiver()->token_00 == call_three_argument(0u, 0u, 0u, 0u));
}

// The store block refuses to write when its word argument is zero, which is
// the only thing that distinguishes it from an unconditional store.
void test_store_block_requires_a_non_zero_word() {
  receiver()->token_00 = 0x55667788u;
  check(unresolved_contracts::pkg_r8_re_00980c80(receiver(), 0u) == 1u);
  check(receiver()->token_00 == 0x55667788u);
  check(receiver()->token_00 != kFunc88hToken);

  check(unresolved_contracts::pkg_r8_re_00980c80(nullptr, 1u) == 0u);
  check(receiver()->token_00 == 0x55667788u);

  check(unresolved_contracts::pkg_r8_re_00980c80(receiver(), 0xffffffffu) ==
        1u);
  check(receiver()->token_00 == kFunc88hToken);
  receiver()->token_00 = 0u;
}

// The immediate is exactly 32 bits wide; the upper bytes of EAX are not part
// of the observed contract, so nothing may be claimed about them.
void test_constant_is_exactly_32_bits() {
  check(static_cast<std::uint64_t>(kFunc88hToken) == 0xcf2b2ad5ull);
  check(kFunc88hToken != 0u);
  check(sizeof(kFunc88hToken) == 4);
}

}  // namespace

int main() {
  test_abi_record();
  test_constants_match_listing();
  test_vtable_run_holds_this_target();
  test_dispatch_through_vtable_word();
  test_result_is_independent_of_every_input();
  test_frame_writes_no_memory();
  test_constant_pairs_with_the_adjacent_store_block();
  test_store_block_requires_a_non_zero_word();
  test_constant_is_exactly_32_bits();
  return 0;
}
