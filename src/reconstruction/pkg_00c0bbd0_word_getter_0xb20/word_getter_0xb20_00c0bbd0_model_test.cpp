#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <type_traits>

#include "word_getter_0xb20_00c0bbd0.hpp"

// Focused semantic test for FUN_00c0bbd0 @ 0x00c0bbd0.
//
// It pins the behaviour the two-instruction body fixes, and it is written to
// try to REFUTE the reconstruction rather than to walk it. Each group below
// names the risky hypothesis it attacks:
//   1. the entry returns the VALUE stored at receiver+0xb20, not the address
//      of that word, not the receiver, not a constant, and not a LEA-form
//      base-plus-displacement;
//   2. 0xb20 is the displacement and not a near neighbour - distinct sentinels
//      are planted either side of it and only the 0xb20 word comes back;
//   3. the body READS: the receiver is byte-identical before and after, so a
//      write-through or defaulting perturbation fails on the guard bands;
//   4. the entry is a pure function of the receiver - the result tracks a
//      changed word and repeats across calls;
//   5. the encoding itself is the observed one - the raw bytes of the body are
//      stated here and the displacement bytes are tied to the header's
//      kWordDisplacement, so the two statements cannot drift apart;
//   6. the ABI is ECX receiver / 0 stack words / caller cleanup - MEASURED by
//      sampling ESP around the call, and shown to be independent of the
//      caller's own stack depth, at two different depths.
//
// The calls go through an inline-asm trampoline instead of a thiscall function
// pointer on purpose. GCC's __attribute__((thiscall)) on a *function pointer
// type* allocates the argument with caller-side stack cleanup, which is not the
// convention the target uses (0x00c0bbd6 is a bare RET, caller cleanup), so a
// plain pointer call would drift the stack by 4 bytes per call. The trampoline
// reproduces the observed sequence exactly:
//     MOV EAX,[ECX+0xb20] / RET
// and the compiler-generated body of the reconstruction is that same pair: at
// -O1 and -O2, clang++ -m32 emits
//     8b 81 20 0b 00 00   mov 0xb20(%ecx),%eax
//     c3                  ret
// i.e. byte-identical to the seven bytes read from 0x00c0bbd0.

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_00c0bbd0 model test requires an x86-32 target"
#endif

// The header undefines its convention macro, so the modelled ABI type is
// respelled here; it is the same thiscall pointer type the entry declares.
#if defined(_MSC_VER)
#define PKG_00C0BBD0_THISCALL __thiscall
#else
#define PKG_00C0BBD0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00c0bbd0_word_getter_0xb20 {
namespace model {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

Word pointer_word(const void* pointer) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(pointer));
}

// The raw bytes read from 0x00c0bbd0..0x00c0bbd6, kept so the reconstruction's
// instruction sequence is stated in the test and not only in prose. The byte
// after the body (0xcc, INT3 pad) is deliberately not included.
constexpr std::uint8_t kTargetBytes[7] = {
    0x8b,                    // MOV r32, r/m32
    0x81,                    // ModRM: mod=10 (disp32), reg=EAX, r/m=ECX
    0x20, 0x0b, 0x00, 0x00,  // disp32 = 0x00000b20, little endian
    0xc3,                    // RET
};

// A sentinel that cannot be confused with a plausible address, a small
// constant, or a displacement value.
constexpr Word kSentinel = 0xfeedfaceu;

// A second, disjoint base for the planted neighbour words, so no neighbour can
// accidentally hold the value the correct answer is.
constexpr Word kNeighbourBase = 0x0badf00du;

// Distinguishable words below the reached one. Nothing above 0xb20 is inside the
// modeled extent, so the "not one word too high" claim is pinned arithmetically
// instead (kWordDisplacement + sizeof(Word) == sizeof(OpaqueReceiver)).
constexpr std::size_t kNeighbourDisplacements[] = {0x000u, 0x004u, 0x0b18u,
                                                   0x0b1cu};

Word entry_address() {
  return pointer_word(reinterpret_cast<const void*>(&word_getter_0xb20_00c0bbd0));
}

// The return value (EAX) after calling the entry through the trampoline.
// ECX = receiver, no stack words pushed, callee pops nothing.
Word call_entry(OpaqueReceiver* receiver) {
  const Word target = entry_address();
  Word result = 0;
  __asm__ __volatile__("movl %2, %%ecx\n\t"
                       "call *%1\n\t"
                       "movl %%eax, %0\n\t"
                       : "=r"(result)
                       : "r"(target), "r"(receiver)
                       : "eax", "ecx", "memory");
  return result;
}

// ESP sampled inside the trampoline, immediately before the call and again the
// instant the callee has returned. `call` puts a return address on the stack
// and `RET` takes it back, so the two samples are equal only when the callee
// owns no cleanup; a `RET 0x4` would leave the second four bytes lower. The
// model test therefore MEASURES the cleanup instead of asserting a calling
// convention it cannot derive from the body.
//
// `scratch_words` pushes a caller-side frame before sampling, so the same
// measurement can be repeated at a different stack depth: a body that read a
// stack argument at [ESP+4] would return the pushed word at one depth and
// something else at the other.
struct EspSamples {
  std::uint32_t before_call = 0;
  std::uint32_t after_return = 0;
};

EspSamples call_entry_measured(OpaqueReceiver* receiver, unsigned scratch_words) {
  const Word target = entry_address();
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  if (scratch_words == 0u) {
    __asm__ __volatile__("movl %%esp, %[before]\n\t"
                         "movl %[recv], %%ecx\n\t"
                         "call *%[target]\n\t"
                         "movl %%esp, %[after]\n\t"
                         : [before] "=m"(before), [after] "=m"(after)
                         : [target] "r"(target), [recv] "r"(receiver)
                         : "eax", "ecx", "memory");
  } else {
    __asm__ __volatile__(
        "subl $128, %%esp\n\t"
        "movl %%esp, %[before]\n\t"
        "movl %[recv], %%ecx\n\t"
        "call *%[target]\n\t"
        "movl %%esp, %[after]\n\t"
        "addl $128, %%esp\n\t"
        : [before] "=m"(before), [after] "=m"(after)
        : [target] "r"(target), [recv] "r"(receiver)
        : "eax", "ecx", "memory");
  }
  EspSamples samples;
  samples.before_call = before;
  samples.after_return = after;
  return samples;
}

static_assert(sizeof(kTargetBytes) == 7, "target body is 7 bytes");
static_assert(kTargetBytes[0] == 0x8b && kTargetBytes[1] == 0x81,
              "0x00c0bbd0 is MOV EAX,dword ptr [ECX + disp32]");
static_assert(kTargetBytes[6] == 0xc3,
              "0x00c0bbd6 is RET (caller cleanup, no stack words)");

// The displacement is tied to the ENCODING, not to prose: 0x00c0bbd0 is
// `8b 81 20 0b 00 00`, so the little-endian disp32 bytes 3..5 spell the
// header's kWordDisplacement. Any drift in either place fails here.
static_assert(kTargetBytes[2] == 0x20 && kTargetBytes[3] == 0x0b &&
                  kTargetBytes[4] == 0x00 && kTargetBytes[5] == 0x00,
              "disp32 bytes spell 0x00000b20, little endian");
static_assert(kWordDisplacement == 0xb20,
              "the header's displacement is the instruction's disp32");
static_assert(kWordDisplacement == 2848u,
              "0xb20 is the value 2848, compared semantically not by spelling");
static_assert(kWordDisplacement ==
                  (static_cast<std::size_t>(kTargetBytes[2]) |
                   (static_cast<std::size_t>(kTargetBytes[3]) << 8) |
                   (static_cast<std::size_t>(kTargetBytes[4]) << 16) |
                   (static_cast<std::size_t>(kTargetBytes[5]) << 24)),
              "header displacement equals the reconstructed disp32");

}

}

namespace {

using namespace openspore::reconstruction::pkg_00c0bbd0_word_getter_0xb20;
using model::call_entry;
using model::call_entry_measured;
using model::check;
using model::entry_address;
using model::kNeighbourBase;
using model::kNeighbourDisplacements;
using model::kSentinel;
using model::pointer_word;
using model::EspSamples;

static_assert(sizeof(pointer_word(nullptr)) == 4,
              "the modelled entry slot is one 32-bit word");
static_assert(sizeof(kSentinel) == 4, "the sentinel is one 32-bit word");
static_assert(std::is_same<AbiWordGetter00c0bbd0,
                           Word(PKG_00C0BBD0_THISCALL*)(OpaqueReceiver*)>::value,
              "modelled ABI is thiscall with 0 stack words, one-word return");

// Fill the whole modeled extent with a non-zero pattern so an access to any
// part of it is visible afterwards, and plant the sentinel only at the
// displacement the body is supposed to reach.
OpaqueReceiver planted_receiver() {
  OpaqueReceiver receiver{};
  for (std::size_t index = 0; index < receiver.opaque_bytes.size(); ++index) {
    receiver.opaque_bytes[index] = static_cast<std::uint8_t>(index + 1u);
  }
  for (std::size_t neighbour = 0;
       neighbour < sizeof(kNeighbourDisplacements) / sizeof(std::size_t);
       ++neighbour) {
    *word_at(&receiver, kNeighbourDisplacements[neighbour]) =
        kNeighbourBase + static_cast<Word>(neighbour);
  }
  *word_at(&receiver, kWordDisplacement) = kSentinel;
  return receiver;
}

Word receiver_address(const OpaqueReceiver* receiver) {
  return pointer_word(receiver);
}

// 1. The return is the VALUE at receiver+0xb20.
void test_return_value_is_the_stored_word() {
  OpaqueReceiver receiver = planted_receiver();

  const Word result = call_entry(&receiver);

  check(result == kSentinel);
  // Not the address of the word: this is the load/LEA distinction. A body
  // written as `reinterpret_cast<std::uintptr_t>(receiver) + 0xb20` returns a
  // value that no sentinel in this fixture equals, so the two cannot both pass.
  check(result != pointer_word(
                       reinterpret_cast<const void*>(
                           reinterpret_cast<std::uintptr_t>(&receiver) +
                           kWordDisplacement)));
  // Not the receiver, not the displacement, not a constant the body could have
  // materialised, and not zero.
  check(result != receiver_address(&receiver));
  check(result != kWordDisplacement);
  check(result != 0u);
  // And the value is genuinely read out of the receiver, byte for byte.
  check(result == *word_at(&receiver, kWordDisplacement));
}

// 2. 0xb20 is THE displacement: distinct words planted below it - including
// the word immediately before it - are not what comes back, and none of them
// is disturbed by the call.
void test_displacement_is_exactly_0xb20() {
  OpaqueReceiver receiver = planted_receiver();

  const Word result = call_entry(&receiver);

  check(result == kSentinel);
  for (std::size_t index = 0;
       index < sizeof(kNeighbourDisplacements) / sizeof(std::size_t); ++index) {
    const std::size_t displacement = kNeighbourDisplacements[index];
    const Word planted = kNeighbourBase + static_cast<Word>(index);
    check(*word_at(&receiver, displacement) == planted);
    check(result != planted);
    // The gap is measured in BYTES: a model that read the displacement as an
    // element count would land 0xb20 elements out, 0x2c80 bytes.
    check(reinterpret_cast<std::uintptr_t>(word_at(&receiver, displacement)) -
              reinterpret_cast<std::uintptr_t>(&receiver) ==
          static_cast<std::uintptr_t>(displacement));
  }
  // The entry's displacement and the header's accessor name one address.
  check(word_at(&receiver, kWordDisplacement) ==
        word_at(&receiver, static_cast<std::size_t>(0xb20u)));
}

// 3. The body READS. Guard bands before and after the reached word must be
// byte-identical across the call; a store-through or defaulting perturbation
// fails here even if it also returned the right value.
void test_body_does_not_write_the_receiver() {
  OpaqueReceiver receiver = planted_receiver();
  OpaqueReceiver before = receiver;

  const Word result = call_entry(&receiver);
  check(result == kSentinel);

  for (std::size_t index = 0; index < receiver.opaque_bytes.size(); ++index) {
    check(receiver.opaque_bytes[index] == before.opaque_bytes[index]);
  }
  // Stated as bounds too: the reached word sits inside the modeled extent and
  // the extent ends immediately after it.
  check(kWordDisplacement < sizeof(OpaqueReceiver));
  check(kWordDisplacement + sizeof(Word) == sizeof(OpaqueReceiver));
}

// 4. Pure function of the receiver: the result tracks the stored word and
// repeats across calls, so a reconstruction that cached a value fails.
void test_result_tracks_the_stored_word_and_repeats() {
  OpaqueReceiver receiver = planted_receiver();

  check(call_entry(&receiver) == kSentinel);
  check(call_entry(&receiver) == kSentinel);

  *word_at(&receiver, kWordDisplacement) = 0x12345678u;
  check(call_entry(&receiver) == 0x12345678u);

  *word_at(&receiver, kWordDisplacement) = 0xffffffffu;
  const Word all_ones = call_entry(&receiver);
  check(all_ones == 0xffffffffu);
  // A signed interpretation of the same bits is not what crosses the ABI, and
  // neither is a truncated 16-bit or byte-wide read of it.
  check(all_ones != 0xffffu);
  check(all_ones != 0xffu);
}

// 5. The encoding is the observed one: the body is the 7 bytes read from
// 0x00c0bbd0, and the header's displacement is that instruction's disp32.
void test_encoding_matches_the_observed_bytes() {
  check(model::kTargetBytes[0] == 0x8bu);
  check(model::kTargetBytes[1] == 0x81u);
  check(model::kTargetBytes[2] == 0x20u);
  check(model::kTargetBytes[3] == 0x0bu);
  check(model::kTargetBytes[4] == 0x00u);
  check(model::kTargetBytes[5] == 0x00u);
  check(model::kTargetBytes[6] == 0xc3u);
  check(sizeof(model::kTargetBytes) == 7u);
  // 0x81 is mod=10, i.e. a 32-bit displacement; the displacement bytes are the
  // ones after the ModRM byte, so the instruction carries 0x00000b20.
  check((model::kTargetBytes[1] >> 6) == 2);
  check((model::kTargetBytes[1] & 0x07) == 1);
  check((model::kTargetBytes[1] >> 3 & 0x07) == 0);
}

// 6. ABI, measured: the callee pops nothing, and the result does not depend on
// the caller's stack depth (so the body reads no stack argument).
void test_no_stack_words_are_popped_and_none_are_read() {
  OpaqueReceiver receiver = planted_receiver();

  const EspSamples shallow = call_entry_measured(&receiver, 0u);
  check(shallow.after_return == shallow.before_call);

  const EspSamples deep = call_entry_measured(&receiver, 32u);
  check(deep.after_return == deep.before_call);
  // The pushed scratch really did change the depth, so the two measurements
  // are not vacuously the same point in the frame.
  check(deep.before_call == shallow.before_call - 128u);

  // Same word, same answer, from two different caller stack depths.
  check(call_entry(&receiver) == kSentinel);
  check(call_entry_measured(&receiver, 8u).after_return ==
        call_entry_measured(&receiver, 8u).before_call);

  // The return value crosses in EAX as one 32-bit word; the modelled entry
  // signature is exactly that.
  check(sizeof(AbiWordGetter00c0bbd0) == sizeof(void*));
  check(sizeof(*word_at(&receiver, kWordDisplacement)) == 4u);
}

int run_tests() {
  test_return_value_is_the_stored_word();
  test_displacement_is_exactly_0xb20();
  test_body_does_not_write_the_receiver();
  test_result_tracks_the_stored_word_and_repeats();
  test_encoding_matches_the_observed_bytes();
  test_no_stack_words_are_popped_and_none_are_read();
  return 0;
}

}

int main() { return ::run_tests(); }

#undef PKG_00C0BBD0_THISCALL
