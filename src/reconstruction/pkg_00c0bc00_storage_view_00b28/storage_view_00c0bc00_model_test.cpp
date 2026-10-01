#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "storage_view_00c0bc00.hpp"

// Focused semantic test for FUN_00c0bc00 @ 0x00c0bc00.
//
// It pins the behaviours the seven-instruction body fixes, and it is written to
// try to REFUTE the reconstruction rather than to walk it. Each group below
// names the risky hypothesis it attacks:
//
//   1. ARM AGREEMENT (1a..1e) - the decisive one. A hand-transcribed oracle in
//      assembly reproduces the target's seven instructions verbatim, and every
//      configuration is required to agree with it. This kills, in one place,
//      an inverted branch, a wrong detour, a wrong receiver displacement, a
//      wrong loaded displacement, and a reconstruction that returned the loaded
//      word unchanged. Nothing else in this test could catch all five at once.
//   2. the zero arm returns the receiver's address at displacement 2856 and not
//      the receiver itself, nor the loaded word, nor any neighbouring address;
//   3. the nonzero arm adds exactly 1284 to the loaded word and not 0, not 4,
//      and not to the receiver;
//   4. the branch is a ZERO test and not a sign test - a negative-valued word
//      must take the same arm a positive one does;
//   5. the addition is 32-bit and wraps, which a wider intermediate would not;
//   6. the body writes NO memory - the whole modelled extent is compared byte
//      for byte before and after every configuration;
//   7. the ABI is ECX receiver / 0 stack arguments / caller cleanup, MEASURED by
//      sampling ESP across the call rather than asserted as a convention;
//   8. the entry's literals and the header's constants name one and the same
//      numbers, so the two statements of each displacement cannot drift apart.
//
// The reconstruction itself is called through an inline-asm trampoline rather
// than through a thiscall function pointer on purpose. A __attribute__((thiscall))
// pointer TYPE makes the CALLER responsible for popping the argument word, which
// is not the convention the target uses (both terminators are a bare RET), so a
// plain pointer call would drift the stack by four bytes per call. The
// trampoline reproduces the observed calling sequence exactly:
//     ECX = receiver; CALL; EAX = result      (no push, callee pops nothing)

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_00c0bc00 model test requires an x86-32 target"
#endif

// The header undefines its convention macro, so the modelled ABI type is
// respelled here; it is the same thiscall pointer type the entry declares.
#if defined(_MSC_VER)
#define PKG_00C0BC00_THISCALL __thiscall
#else
#define PKG_00C0BC00_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00c0bc00_storage_view_00b28 {
namespace model {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

Opaque pointer_word(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

// The oracle: the target's seven instructions, transcribed. Displacements and
// the detour are written here straight from the encoding, independently of the
// header's named constants, so the oracle and the reconstruction are two
// separate statements of the same body and agreement between them is evidence.
//
//   8b 81 20 0b 00 00   movl 0xb20(%ecx),%eax   MOV EAX,[ECX+0xb20]
//   85 c0               testl %eax,%eax           TEST EAX,EAX
//   74 06               jz <zero arm>             JZ 0x00c0bc10
//   05 04 05 00 00      addl $0x504,%eax          ADD EAX,0x504
//   c3                  ret
//   8d 81 28 0b 00 00   leal 0xb28(%ecx),%eax     LEA EAX,[ECX+0xb28]
//   c3                  ret
//
// There is no argument-fetch prologue, because the target has none: the body
// reads ECX on its first instruction and never touches the stack. The oracle is
// therefore entered exactly as the target is - receiver in ECX, nothing pushed -
// and must only be called through the trampolines below. Anything else would be
// reading a different register than the machine reads. The parameter is left
// unnamed because the body never reads it from the stack - naming it would only
// invite g++'s -Wunused-parameter, which the promotion gate treats as fatal.
__attribute__((naked)) Opaque storage_view_oracle(const OpaqueReceiver*) {
  __asm__ __volatile__("movl 0xb20(%ecx), %eax\n\t"
                       "testl %eax, %eax\n\t"
                       "jz 1f\n\t"
                       "addl $0x504, %eax\n\t"
                       "ret\n\t"
                       "1:\n\t"
                       "leal 0xb28(%ecx), %eax\n\t"
                       "ret\n\t");
}

Opaque entry_address() {
  return pointer_word(reinterpret_cast<const void*>(&storage_view_00c0bc00));
}

// EAX after calling the reconstruction through the trampoline.
Opaque call_entry(const OpaqueReceiver* receiver) {
  const Opaque target = entry_address();
  Opaque result = 0;
  __asm__ __volatile__("movl %2, %%ecx\n\t"
                       "call *%1\n\t"
                       "movl %%eax, %0\n\t"
                       : "=r"(result)
                       : "r"(target), "r"(receiver)
                       : "eax", "ecx", "memory");
  return result;
}

// EAX after calling the oracle through the same trampoline.
Opaque call_oracle(const OpaqueReceiver* receiver) {
  const Opaque target = pointer_word(
      reinterpret_cast<const void*>(&storage_view_oracle));
  Opaque result = 0;
  __asm__ __volatile__("movl %2, %%ecx\n\t"
                       "call *%1\n\t"
                       "movl %%eax, %0\n\t"
                       : "=r"(result)
                       : "r"(target), "r"(receiver)
                       : "eax", "ecx", "memory");
  return result;
}

// ESP sampled immediately before the call and the instant the callee has
// returned. `call` pushes a return address and `ret` takes it back, so the two
// samples are equal only when the callee owns no cleanup; a RET with an
// immediate would leave the second sample four bytes lower. The test therefore
// MEASURES the cleanup rather than asserting a convention it cannot derive.
struct EspSamples {
  std::uint32_t before_call = 0;
  std::uint32_t after_return = 0;
};

EspSamples call_entry_measured(const OpaqueReceiver* receiver) {
  const Opaque target = entry_address();
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%[target]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [after] "=m"(after)
                       : [target] "r"(target), [recv] "r"(receiver)
                       : "eax", "ecx", "memory");
  EspSamples samples;
  samples.before_call = before;
  samples.after_return = after;
  return samples;
}

// The loaded word is written through the SAME displacement accessor the
// reconstruction reads it through, so the test never names a member either.
void set_storage_word(OpaqueReceiver* receiver, Opaque value) {
  *reinterpret_cast<Opaque*>(
      reinterpret_cast<std::uintptr_t>(receiver) + kStorageBaseDisplacement) = value;
}

// A byte-comparison of the whole modelled extent, so any store the body
// performed would be visible.
void expect_extent_unchanged(const OpaqueReceiver& before,
                             const OpaqueReceiver& after,
                             const char* what) {
  check(before.opaque_bytes.size() == after.opaque_bytes.size());
  check(std::memcmp(before.opaque_bytes.data(), after.opaque_bytes.data(),
                    before.opaque_bytes.size()) == 0);
  (void)what;
}

static_assert(sizeof(kStorageBaseDisplacement) == sizeof(std::size_t),
              "displacements are host-size values");
static_assert(kStorageBaseDisplacement == 2848,
              "the loaded word sits at displacement 2848 (MOV at 0x00c0bc00)");
static_assert(kStorageDetour == 1284,
              "the nonzero arm adds 1284 (ADD at 0x00c0bc0a)");
static_assert(kInlineStorageDisplacement == 2856,
              "the zero arm forms the receiver address at 2856 (LEA at 0x00c0bc10)");
static_assert(std::is_same<AbiStorageView00c0bc00,
                          void*(PKG_00C0BC00_THISCALL*)(OpaqueReceiver*)>::value,
              "modelled ABI is thiscall with 0 stack words");

}
}

namespace {

using namespace openspore::reconstruction::pkg_00c0bc00_storage_view_00b28;
using model::call_entry;
using model::call_entry_measured;
using model::call_oracle;
using model::check;
using model::entry_address;
using model::expect_extent_unchanged;
using model::pointer_word;
using model::set_storage_word;
using model::storage_view_oracle;
using model::EspSamples;

// A receiver whose every byte is non-zero and distinct from its neighbours, so
// a word read from the wrong displacement is never accidentally right.
OpaqueReceiver patterned_receiver() {
  OpaqueReceiver receiver{};
  for (std::size_t index = 0; index < receiver.opaque_bytes.size(); ++index) {
    receiver.opaque_bytes[index] = static_cast<std::uint8_t>((index * 7u) + 3u);
  }
  return receiver;
}

// 1a. Both arms agree with the oracle, word zero.
void test_zero_arm_agrees_with_the_oracle() {
  OpaqueReceiver receiver = patterned_receiver();
  set_storage_word(&receiver, 0u);

  check(call_entry(&receiver) == call_oracle(&receiver));
  check(call_entry(&receiver) == pointer_word(inline_storage_address(&receiver)));
}

// 1b. Both arms agree with the oracle, word nonzero: the words below are chosen
// so the two arms return DIFFERENT addresses for the same receiver, so a
// reconstruction with the arms swapped cannot agree on both.
void test_nonzero_arm_agrees_with_the_oracle() {
  const Opaque words[] = {1u, 2u, 4u, 0x1000u, 0x12345000u, 0x7fff0000u};
  for (std::size_t index = 0; index < sizeof(words) / sizeof(words[0]); ++index) {
    OpaqueReceiver receiver = patterned_receiver();
    set_storage_word(&receiver, words[index]);

    check(call_entry(&receiver) == call_oracle(&receiver));
    // The two arms must not be interchangeable: the oracle's answer on this
    // arm is neither the receiver's own displaced address nor the other arm's.
    check(call_entry(&receiver) != pointer_word(inline_storage_address(&receiver)));
  }
}

// 1c. The oracle itself is not degenerate: for every word it must return
// something specific, so "always returns the receiver" or "always returns the
// loaded word" is refuted on the oracle side as well as the reconstruction side.
void test_oracle_is_not_a_constant_function() {
  OpaqueReceiver receiver = patterned_receiver();
  set_storage_word(&receiver, 0u);
  const Opaque zero_case = call_oracle(&receiver);
  set_storage_word(&receiver, 0x2000u);
  const Opaque nonzero_case = call_oracle(&receiver);
  check(zero_case != nonzero_case);
  check(nonzero_case != pointer_word(static_cast<const void*>(&receiver)));
}

// 1d. Every reachable word value in a small sweep agrees, including the words
// either side of zero and the wrap point.
void test_sweep_agrees_with_the_oracle() {
  for (Opaque word = 0u; word < 6u; ++word) {
    OpaqueReceiver receiver = patterned_receiver();
    set_storage_word(&receiver, word);
    check(call_entry(&receiver) == call_oracle(&receiver));
  }
  const Opaque interesting[] = {0x80000000u, 0xfffff000u, 0xfffffff0u, 0xffffffffu};
  for (std::size_t index = 0; index < sizeof(interesting) / sizeof(interesting[0]);
       ++index) {
    OpaqueReceiver receiver = patterned_receiver();
    set_storage_word(&receiver, interesting[index]);
    check(call_entry(&receiver) == call_oracle(&receiver));
  }
}

// 1e. The call shape itself is not what makes the agreement: a receiver at a
// different address must still agree, so nothing in the comparison depends on
// the receiver sitting at one address.
void test_agreement_holds_for_a_second_receiver() {
  OpaqueReceiver first = patterned_receiver();
  OpaqueReceiver second = patterned_receiver();
  second.opaque_bytes[kStorageBaseDisplacement] = 0x11u;
  set_storage_word(&first, 0u);
  set_storage_word(&second, 0x11u);

  check(call_entry(&first) == call_oracle(&first));
  check(call_entry(&second) == call_oracle(&second));
  check(pointer_word(&first) != pointer_word(&second));
}

// 2. The zero arm's answer is the receiver at displacement 2856, not the
// receiver, not the loaded word's slot, not the intervening word's slot.
void test_zero_arm_is_receiver_at_the_inline_displacement() {
  OpaqueReceiver receiver = patterned_receiver();
  set_storage_word(&receiver, 0u);

  const Opaque result = call_entry(&receiver);
  const Opaque base = pointer_word(static_cast<const void*>(&receiver));

  check(result == base + 2856u);
  check(result != base);
  check(result != base + 2848u);  // the loaded word's own slot
  check(result != base + 2852u);  // the one word the body never reaches
  check(result != base + 2860u);
}

// 3. The nonzero arm adds exactly 1284 to the loaded word.
void test_nonzero_arm_adds_exactly_the_detour_to_the_loaded_word() {
  const Opaque words[] = {1u, 3u, 0x1000u, 0x00b20000u, 0xfffffff0u};
  for (std::size_t index = 0; index < sizeof(words) / sizeof(words[0]); ++index) {
    OpaqueReceiver receiver = patterned_receiver();
    const Opaque word = words[index];
    set_storage_word(&receiver, word);

    const Opaque result = call_entry(&receiver);
    check(result == word + 1284u);
    check(result != word);
    check(result != word + 4u);
    check(result != word - 1284u);
    // The receiver takes no part in this arm's arithmetic.
    check(result != pointer_word(static_cast<const void*>(&receiver)) + 1284u);
  }
}

// 4. The branch is a ZERO test. A word with the sign bit set takes the same arm
// as a small positive one, which a JNS/JE confusion would not.
void test_branch_is_a_zero_test_not_a_sign_test() {
  OpaqueReceiver negative = patterned_receiver();
  set_storage_word(&negative, 0x80000000u);
  OpaqueReceiver positive = patterned_receiver();
  set_storage_word(&positive, 0x00000010u);

  check(call_entry(&negative) == 0x80000000u + 1284u);
  check(call_entry(&positive) == 0x00000010u + 1284u);
  check(call_entry(&negative) != pointer_word(inline_storage_address(&negative)));
}

// 5. The addition is 32-bit and wraps. 0xfffffff0 + 1284 is 0x1000004f4, which
// truncates to 0x4f4; a 64-bit intermediate would return 0x1000004f4.
void test_addition_wraps_at_32_bits() {
  OpaqueReceiver receiver = patterned_receiver();
  set_storage_word(&receiver, 0xfffffff0u);

  check(call_entry(&receiver) == 0x4f4u);
  check(call_entry(&receiver) == call_oracle(&receiver));
}

// 6. The body writes nothing: the whole modelled extent is identical before and
// after, on both arms.
void test_body_writes_no_memory() {
  const Opaque words[] = {0u, 1u, 0x1000u, 0x80000000u};
  for (std::size_t index = 0; index < sizeof(words) / sizeof(words[0]); ++index) {
    OpaqueReceiver receiver = patterned_receiver();
    set_storage_word(&receiver, words[index]);
    const OpaqueReceiver snapshot = receiver;

    const Opaque result = call_entry(&receiver);

    expect_extent_unchanged(snapshot, receiver, "after one call");
    check(call_entry(&receiver) == result);  // idempotent: no state was made
  }
}

// 7. Caller cleanup, measured.
void test_no_stack_words_are_popped_by_the_callee() {
  OpaqueReceiver receiver = patterned_receiver();
  set_storage_word(&receiver, 0u);

  const EspSamples samples = call_entry_measured(&receiver);
  check(samples.after_return == samples.before_call);

  set_storage_word(&receiver, 7u);
  const EspSamples nonzero_samples = call_entry_measured(&receiver);
  check(nonzero_samples.after_return == nonzero_samples.before_call);

  check(sizeof(AbiStorageView00c0bc00) == sizeof(void*));
}

// 8. The entry's literals and the header's constants name one and the same
// numbers, so the two statements of each displacement cannot drift apart.
void test_entry_literals_and_header_constants_agree() {
  OpaqueReceiver receiver = patterned_receiver();
  set_storage_word(&receiver, 0u);

  const Opaque inline_result = call_entry(&receiver);
  check(inline_result ==
        pointer_word(address_at(&receiver, kInlineStorageDisplacement)));

  set_storage_word(&receiver, 0x1000u);
  const Opaque nonzero_result = call_entry(&receiver);
  check(nonzero_result ==
        static_cast<std::uintptr_t>(0x1000u) + kStorageDetour);

  // The three numbers are the listing's, and they are three DIFFERENT numbers:
  // the detour is not the receiver displacement, and the two receiver
  // displacements are not the same displacement.
  check(kStorageDetour != kStorageBaseDisplacement);
  check(kStorageDetour != kInlineStorageDisplacement);
  check(kStorageBaseDisplacement != kInlineStorageDisplacement);
  check(kStorageDetour != 0u);
}

int run_tests() {
  test_zero_arm_agrees_with_the_oracle();
  test_nonzero_arm_agrees_with_the_oracle();
  test_oracle_is_not_a_constant_function();
  test_sweep_agrees_with_the_oracle();
  test_agreement_holds_for_a_second_receiver();
  test_zero_arm_is_receiver_at_the_inline_displacement();
  test_nonzero_arm_adds_exactly_the_detour_to_the_loaded_word();
  test_branch_is_a_zero_test_not_a_sign_test();
  test_addition_wraps_at_32_bits();
  test_body_writes_no_memory();
  test_no_stack_words_are_popped_by_the_callee();
  test_entry_literals_and_header_constants_agree();
  return 0;
}

}

int main() { return ::run_tests(); }

#undef PKG_00C0BC00_THISCALL
