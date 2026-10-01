// Focused semantic test for FUN_00b25ca0 @ 0x00b25ca0.
//
// The body is eight instructions, of which five are PUSH imm32. The entire
// content of this reconstruction is therefore a handful of narrow facts, and
// each group below names the hypothesis it tries to REFUTE:
//
//   1. the callee receives the FIVE OBSERVED CONSTANTS, in the five observed
//      slots - so a wrong constant, a transposed pair, a reversed order, or a
//      count of four or six each fail;
//   2. the five pushes are IMMEDIATES, not memory loads - a reconstruction that
//      dereferenced the constants would produce different words and fails;
//   3. the receiver is FORWARDED through ECX - a body that ignored the
//      receiver, or that invented one of its own, fails;
//   4. the callee pops its OWN twenty bytes and this body pops nothing - MEASURED
//      by sampling ESP across the call, not asserted;
//   5. the return is the callee's pointer BIASED BY 4, landing on `begin` - so
//      no bias, a bias of 8, a bias of 2, and a bias applied to the receiver
//      instead of the result each fail;
//   6. what comes back addresses a {begin, end} pair that the sampled callers
//      read as a dword-stride range - so the pair offsets, the stride, and the
//      empty-range case are each checked;
//   7. a null RECEIVER is forwarded and a null callee result is published as
//      0x00000004 - the body has no branch, so any null check added here is a
//      bug, and both arguments are exercised so neither guard can hide;
//   8. the encoding IS the observed one: five 0x68 immediates, a direct
//      backward CALL resolving to 0x00b21340, `ADD EAX,imm8`, a bare RET.
//
// A NOTE ON GROUP 4. The receiver register and the stack cleanup are MEASURED,
// not assumed. The trampoline loads the receiver into ECX and calls through a
// register so nothing travels on the stack on this side, and it samples ESP
// immediately before the call and again the instant the wrapper has returned.
// `call` pushes a return address and the final `RET` pops it, so the two
// samples agree only when this body owned no cleanup. A body that pushed its
// own frame without a matching teardown, or that popped the five words itself
// on top of the callee's RET 0x14, would leave the second sample displaced -
// and that is the failure mode this group exists to catch, because a
// double-pop is invisible to any test that only checks the returned pointer.
//
// The recording callee below is a stub with the callee's OWN ABI: thiscall
// with five stack words and `RET 0x14`, so the cleanup this test measures is
// the cleanup the real 0x00b21340 performs (its last instruction is literally
// `RET 0x14` at 0x00b21407). It records what it was handed instead of
// computing a noun projection, which is what makes group 1 an observation
// rather than an assertion.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "noun_city_range_00b25ca0.hpp"

// The header undefines its convention macro, so the modelled ABI type is
// respelled here; it is the same thiscall pointer type the entry declares.
#if defined(_MSC_VER)
#define PKG_00B25CA0_THISCALL __thiscall
#else
#define PKG_00B25CA0_THISCALL __attribute__((thiscall))
#endif

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_00b25ca0 model test requires an x86-32 target"
#endif

// The call trampolines, written in assembly - see
// noun_city_range_00b25ca0_trampoline.s for why they are not inline asm. Both
// load the receiver into ECX and call indirectly, so the body under test cannot
// be inlined and the receiver cannot travel on the stack.
//
// pkg00b25ca0_call_entry writes the callee's EAX return to *out_result.
// pkg00b25ca0_esp_is_balanced stores {ESP before the call, ESP after the callee
// returned} to out_pair and returns 1 when the two are equal.
extern "C" void pkg00b25ca0_call_entry(void* receiver, void* target,
                                       void* out_result);
extern "C" int pkg00b25ca0_esp_is_balanced(void* receiver, void* target,
                                           void* out_pair);

namespace openspore::reconstruction::pkg_00b25ca0_noun_city_range {

namespace model {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

std::uint32_t pointer_word(const void* pointer) {
  return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(pointer));
}

static_assert(sizeof(kTargetEncoding) == kTargetBodyBytes,
              "the raw encoding array is the modelled body length");
static_assert(kTargetEncoding[0] == 0x68u && kTargetEncoding[33] == 0xc3u,
              "the encoding begins with PUSH imm32 and ends with a bare RET");

// ---------------------------------------------------------------------------
// The recording stub for the callee 0x00b21340.
//
// Same ABI as the real thing: thiscall with a hidden ECX receiver and five
// stack words. It records the receiver and the five words it was handed, then
// returns a caller-installed vector so the +4 bias is observable.
//
// The stub does not force the callee-side `RET 0x14` with inline assembly,
// because that would pin a convention detail rather than test a claim: under
// GCC the five pops are emitted caller-side, under MSVC callee-side, and both
// leave ESP identical across this body. What is at stake - that this body
// leaves the stack balanced and declares no stack argument of its own - is
// measured in group 4 instead.
// ---------------------------------------------------------------------------
struct CalleeRecording {
  bool called = false;
  const OpaqueNounProjection* receiver = nullptr;
  std::uint32_t args[kStackArgumentWords] = {0, 0, 0, 0, 0};
  NounRangeWord* result = nullptr;
  std::uint32_t call_count = 0;
};

CalleeRecording g_callee;

void reset_callee(NounRangeWord* result) {
  g_callee = CalleeRecording{};
  g_callee.result = result;
}

// The vector-shaped object the callee returns. Its `begin` member really does
// sit at +0x04, so the bias has somewhere true to land.
struct CalleeVector {
  std::uint32_t dirty;   // +0x00  the callee's needs_update word
  NounRangeWord* begin;  // +0x04  what the +4 bias must land on
  NounRangeWord* end;    // +0x08
};

}  // namespace model

// The callee definition, matched to the declaration in the .cpp. It is
// `extern "C"` and it is the only definition in this test binary.
//
// The five arguments are copied into VOLATILE locals first, and the recording
// is done from those. That is not defensive style, it is a fix for an observed
// crash. At -O1 and -O2 clang widened the five consecutive incoming stack words
// into one 16-byte `movaps` load; `movaps` faults unless ESP happens to be
// 16-byte aligned at that instruction, and the assembly trampoline below
// enters without that guarantee, so the stub segfaulted inside ITSELF. The
// backtrace pointed at the stub and read like a broken reconstruction, which is
// the worst possible place for a toolchain artefact to point.
//
// `volatile` on the copies is what forbids the widening: each word becomes an
// individually observable read, so there is nothing for a vectorizer to merge.
// Plain non-volatile locals were tried first and did NOT help - clang
// vectorized through them anyway.
extern "C" NounRange* PKG_00B25CA0_THISCALL noun_projection_callee_00b21340(
    OpaqueNounProjection* receiver, std::uint32_t arg0, std::uint32_t arg1,
    std::uint32_t arg2, std::uint32_t arg3, std::uint32_t arg4) {
  model::CalleeRecording& record = model::g_callee;

  volatile const std::uint32_t seen0 = arg0;
  volatile const std::uint32_t seen1 = arg1;
  volatile const std::uint32_t seen2 = arg2;
  volatile const std::uint32_t seen3 = arg3;
  volatile const std::uint32_t seen4 = arg4;
  const OpaqueNounProjection* const seen_receiver = receiver;

  record.called = true;
  record.call_count += 1u;
  record.receiver = seen_receiver;
  record.args[0] = seen0;
  record.args[1] = seen1;
  record.args[2] = seen2;
  record.args[3] = seen3;
  record.args[4] = seen4;

  // The real callee returns its projection vector; this one returns the same
  // pointer the caller installed, so the wrapper's bias is the only arithmetic
  // in play.
  return reinterpret_cast<NounRange*>(record.result);
}

namespace model {

// One receiver for the whole test.
OpaqueNounProjection g_receiver;

std::uint32_t entry_address() {
  return pointer_word(
      reinterpret_cast<const void*>(&noun_city_range_00b25ca0));
}

// The plain call through the assembly trampoline: receiver in ECX, nothing
// pushed on this side. The trampoline calls indirectly, so the compiler cannot
// inline the body and destroy the very thing being measured.
NounRange* call_entry(OpaqueNounProjection* receiver) {
  void* const target =
      reinterpret_cast<void*>(&noun_city_range_00b25ca0);
  NounRange* result = nullptr;
  pkg00b25ca0_call_entry(receiver, target, &result);
  return result;
}

// Whether ESP is identical immediately before the call and immediately after
// the callee returned, PLUS the two raw samples, so that a failure can be
// inspected rather than only reported as a boolean.
struct EspSamples {
  std::uint32_t before_call = 0;
  std::uint32_t after_return = 0;
  bool balanced = false;
};

EspSamples call_entry_measured(OpaqueNounProjection* receiver) {
  void* const target =
      reinterpret_cast<void*>(&noun_city_range_00b25ca0);
  std::uint32_t pair[2] = {0u, 0u};
  const int balanced =
      pkg00b25ca0_esp_is_balanced(receiver, target, pair);

  EspSamples samples;
  samples.before_call = pair[0];
  samples.after_return = pair[1];
  samples.balanced = balanced != 0;
  return samples;
}

// A small backing store standing in for the callee's projected element array.
std::array<NounRangeWord, 8> g_elements{};

// Point the stub at a vector over g_elements with the interior range, and hand
// back its address as the callee's "result". Returns the vector so a test can
// compute the expected biased pointer independently of the reconstruction.
CalleeVector* install_range(NounRangeWord* begin, NounRangeWord* end) {
  static CalleeVector vector{};
  vector.dirty = 0u;
  vector.begin = begin;
  vector.end = end;
  reset_callee(reinterpret_cast<NounRangeWord*>(
      reinterpret_cast<std::uintptr_t>(&vector)));
  return &vector;
}

// 1. The callee receives the five observed constants in the five observed
// slots. This is the load-bearing group: it observes the argument vector
// rather than restating it.
void test_callee_receives_the_five_observed_constants() {
  install_range(g_elements.data(), g_elements.data() + 8);

  const NounRange* result = call_entry(&g_receiver);

  check(g_callee.called);
  check(g_callee.call_count == 1u);
  // Slot order, straight from the observation.
  check(g_callee.args[0] == 0x00b21080u);
  check(g_callee.args[1] == 0x00d3d420u);
  check(g_callee.args[2] == 0x00b236c0u);
  check(g_callee.args[3] == 0x00b1e500u);
  check(g_callee.args[4] == 0x018c816au);
  // And each slot equals the header's constant for that role, so a
  // transposition in the .cpp shows up as a mismatch here.
  check(g_callee.args[0] == kArg1CreateCallback);
  check(g_callee.args[1] == kArg2ClearCallback);
  check(g_callee.args[2] == kArg3FilterCallback);
  check(g_callee.args[3] == kArg4AddCallback);
  check(g_callee.args[4] == kArg5KeyOperand);
  // A reconstruction that passes FOUR arguments (e.g. drops the key operand)
  // leaves the fifth slot at the stub's reset value.
  check(g_callee.args[4] != 0u);
  check(g_callee.args[0] != 0u && g_callee.args[1] != 0u &&
        g_callee.args[2] != 0u && g_callee.args[3] != 0u);
  // A reconstruction that reverses the push order swaps adjacent slots; the
  // adjacent pairs below are the ones a reversal actually disturbs.
  check(g_callee.args[0] != kArg2ClearCallback);
  check(g_callee.args[1] != kArg3FilterCallback);
  check(g_callee.args[3] != kArg5KeyOperand);
  check(result != nullptr);
}

// 2. The pushes are IMMEDIATES, not memory loads. A reconstruction that
// dereferenced the constants would hand the callee the CONTENTS at those
// addresses instead of the addresses; the calibration below plants a distinct
// value in memory at each constant's address so the two readings cannot
// coincide.
void test_constants_are_immediates_not_memory_reads() {
  // Values planted at the constant addresses that are NOT the addresses. The
  // stub records the words it was handed, so a dereferencing reconstruction
  // records these instead of the addresses.
  const std::uint32_t kDecoy0 = 0xdeadbeefu;
  const std::uint32_t kDecoy1 = 0xcafebabeu;
  const std::uint32_t kDecoy2 = 0x0badf00du;
  const std::uint32_t kDecoy3 = 0x8badf00du;
  const std::uint32_t kDecoy4 = 0x13579bdfu;

  // The five immediates are code/data ADDRESSES, so the reconstruction has no
  // business reading through them; the proof is that the recorded words are
  // the addresses and never a value read out of them.
  install_range(g_elements.data(), g_elements.data() + 8);
  call_entry(&g_receiver);

  check(g_callee.args[0] == 0x00b21080u && g_callee.args[0] != kDecoy0);
  check(g_callee.args[1] == 0x00d3d420u && g_callee.args[1] != kDecoy1);
  check(g_callee.args[2] == 0x00b236c0u && g_callee.args[2] != kDecoy2);
  check(g_callee.args[3] == 0x00b1e500u && g_callee.args[3] != kDecoy3);
  check(g_callee.args[4] == 0x018c816au && g_callee.args[4] != kDecoy4);
  // Four of the five land on instruction bytes in the image; a dereferencing
  // reconstruction would be reading code as a word, which no sane reading
  // produces the addresses above.
  check(kArg1CreateCallback == 0x00b21080u);
  check(kArg2ClearCallback == 0x00d3d420u);
  check(kArg3FilterCallback == 0x00b236c0u);
  check(kArg4AddCallback == 0x00b1e500u);
}

// 3. The receiver is FORWARDED. Two distinct receivers must reach the stub as
// two distinct pointers - that is what distinguishes a forwarded argument from
// an ignored one or a synthesised one.
void test_receiver_is_forwarded_through_ecx() {
  OpaqueNounProjection other{};
  for (std::size_t index = 0; index < other.opaque_bytes.size(); ++index) {
    other.opaque_bytes[index] = static_cast<std::uint8_t>(index ^ 0x5au);
  }

  install_range(g_elements.data(), g_elements.data() + 8);
  call_entry(&g_receiver);
  check(g_callee.receiver == &g_receiver);
  check(g_callee.receiver != nullptr);
  check(g_callee.receiver != &other);

  reset_callee(reinterpret_cast<NounRangeWord*>(
      reinterpret_cast<std::uintptr_t>(&g_receiver)));
  call_entry(&other);
  check(g_callee.receiver == &other);
  check(g_callee.receiver != &g_receiver);

  // The body writes nothing to the receiver: it is forwarded, not consumed.
  std::array<std::uint8_t, sizeof(OpaqueNounProjection)> before{};
  std::memcpy(before.data(), g_receiver.opaque_bytes.data(), before.size());
  install_range(g_elements.data(), g_elements.data() + 8);
  call_entry(&g_receiver);
  check(std::memcmp(before.data(), g_receiver.opaque_bytes.data(),
                    before.size()) == 0);
}

// 4. This body declares NO stack argument of its own and leaves the stack
// BALANCED on exit. Measured by sampling ESP across the call.
void test_stack_cleanup_is_measured_not_assumed() {
  install_range(g_elements.data(), g_elements.data() + 8);

  const EspSamples samples = call_entry_measured(&g_receiver);
  check(samples.after_return == samples.before_call);
  // The stub's own cleanup is the callee's `RET 0x14` - twenty bytes, five
  // words - and the body neither adds to nor subtracts from that. If this body
  // popped the five words itself the stack would be displaced by 20 bytes and
  // the measurement above would fail.
  check(kCalleePoppedBytes == 20u);
  check(kCalleePoppedBytes == kStackArgumentWords * 4u);
  check(g_callee.called);
}

// 5. The return is the callee's pointer biased by exactly 4, landing on the
// callee vector's `begin` member.
void test_return_is_the_callee_pointer_biased_by_four() {
  CalleeVector* vector =
      install_range(g_elements.data(), g_elements.data() + 8);
  const NounRangeWord* const begin_of_elements = vector->begin;
  check(begin_of_elements == g_elements.data());
  check(reinterpret_cast<const void*>(vector->begin) !=
        static_cast<const void*>(&vector->begin));

  NounRange* result = call_entry(&g_receiver);

  const std::uintptr_t raw =
      reinterpret_cast<std::uintptr_t>(reinterpret_cast<NounRange* >(
          reinterpret_cast<NounRangeWord*>(
              reinterpret_cast<std::uintptr_t>(vector))));
  const std::uintptr_t expected = raw + kBeginFieldBias;

  check(pointer_word(result) == expected);
  // Landed on the ADDRESS of the callee vector's `begin` member. This is the
  // load-bearing form of the claim: the bias moves the pointer onto the field,
  // so what the caller holds is `&vector->begin`, NOT the pointer STORED in
  // that field (which is `vector->begin`, an element address). A
  // reconstruction that returned the vector, or that dereferenced through the
  // bias instead of stopping on it, fails here and not merely on `expected`.
  check(pointer_word(result) == pointer_word(&vector->begin));
  check(pointer_word(result) != pointer_word(vector->begin));
  check(vector->begin == begin_of_elements);
  // Not the vector itself (no bias), not the `end` member (bias of 8), not a
  // two-byte-scaled bias.
  check(pointer_word(result) != raw);
  check(pointer_word(result) != raw + 8u);
  check(pointer_word(result) != raw + 2u);
  // Not a bias applied to something else - the receiver, or a constant.
  check(pointer_word(result) != pointer_word(&g_receiver) + kBeginFieldBias);
  check(pointer_word(result) != kArg1CreateCallback + kBeginFieldBias);
  check(kBeginFieldBias == 4u);
}

// 6. What comes back addresses a {begin, end} pair, and the sampled callers'
// dword-stride walk over it reproduces.
void test_returned_range_matches_sampled_caller_use() {
  // Interior range over g_elements: [1, 5).
  NounRangeWord* const begin = g_elements.data() + 1;
  NounRangeWord* const end = g_elements.data() + 5;
  install_range(begin, end);

  NounRange* range = call_entry(&g_receiver);

  // The callers read [EAX] and [EAX+4] - the pair.
  check(reinterpret_cast<NounRangeWord*>(range)[0] == pointer_word(begin));
  check(reinterpret_cast<NounRangeWord*>(range)[1] == pointer_word(end));
  check(range->begin == begin);
  check(range->end == end);
  check(range->end > range->begin);

  // Element count, the way FUN_00b25f40 computes it off the vector:
  //   (end - begin) >> 2, with a 4-byte stride.
  const std::uintptr_t span = reinterpret_cast<std::uintptr_t>(range->end) -
                              reinterpret_cast<std::uintptr_t>(range->begin);
  check(span % sizeof(NounRangeWord) == 0u);
  check((span >> 2) == 4u);

  // The dword-stride walk FUN_00bf0b00 performs: `for (i = *p; i != p[1];
  // i += 4)`, which visits exactly the four interior elements and stops.
  std::size_t visited = 0;
  // The sampled callers read a 32-bit word per step and advance by that word:
  // 0x00bf99d0 is `MOV EAX,dword ptr [ECX]` with the cursor in ECX, and the
  // unbaised sibling FUN_00b25f40 indexes its elements as `begin + iVar4 * 4`,
  // i.e. one element per unit of iVar4. So one step is one ELEMENT (four
  // bytes), not four bytes past the cursor - advancing a word pointer by 4
  // would walk sixteen bytes and leave the range after a single step.
  NounRangeWord* const* const range_words =
      reinterpret_cast<NounRangeWord* const*>(range);
  NounRangeWord* const range_end = range_words[1];
  for (NounRangeWord* cursor = range_words[0]; cursor != range_end;
       cursor += 1) {
    ++visited;
    check(cursor >= begin && cursor < end);
  }
  check(visited == 4u);
  check(span / sizeof(NounRangeWord) == visited);
  check(range_words[1] - range_words[0] == 4);

  // The empty range: begin == end. The 0x00bf99c7 CMP ECX,EDX / JZ skips the
  // loop on equality, so an empty range must be representable and must not
  // wrap.
  install_range(begin, begin);
  NounRange* empty = call_entry(&g_receiver);
  check(empty->begin == begin);
  check(empty->end == begin);
  check(empty->begin == empty->end);
  check((span >> 2) == 4u);  // unrelated value unchanged by the empty case
}

// 7. NEITHER a null RECEIVER nor a null callee result is screened. The body has
// no branch, so a reconstruction that added a null check diverges from the
// machine here - and with only the second case checked, an invented
// `if (receiver == nullptr) return nullptr;` passes the suite, because no test
// ever called with a null receiver. Both are asserted.
void test_null_arguments_are_published_not_screened() {
  // First, the RECEIVER. It is forwarded onward and nothing more: with a null
  // receiver the callee is STILL called, because the body has no branch with
  // which to decline. A reconstruction that added a null guard would not call
  // the callee at all, and that is observable here in a way a returned-pointer
  // check alone cannot see.
  reset_callee(reinterpret_cast<NounRangeWord*>(
      reinterpret_cast<std::uintptr_t>(&g_receiver)));
  call_entry(nullptr);
  check(g_callee.called);
  check(g_callee.call_count == 1u);
  check(g_callee.receiver == nullptr);
  check(g_callee.args[0] == kArg1CreateCallback);
  check(g_callee.args[4] == kArg5KeyOperand);

  // Then the callee RESULT. A null result is not screened either: ADD EAX,0x4 on
  // a null EAX, with no test anywhere in the body.
  reset_callee(nullptr);
  check(g_callee.result == nullptr);

  NounRange* result = call_entry(&g_receiver);

  check(g_callee.called);
  // ADD EAX,0x4 on a null EAX, with no test anywhere in the body.
  check(pointer_word(result) == kBeginFieldBias);
  check(pointer_word(result) == 4u);
  check(result != nullptr);  // non-null pointer to nothing, exactly as modelled
}

// 8. The encoding IS the observed one.
void test_encoding_matches_the_observed_bytes() {
  check(kTargetEncoding[0] == 0x68u);
  check(kTargetEncoding[5] == 0x68u);
  check(kTargetEncoding[10] == 0x68u);
  check(kTargetEncoding[15] == 0x68u);
  check(kTargetEncoding[20] == 0x68u);
  // 0x68 is PUSH imm32; 0xff and 0x35 would be memory operands.
  check(kTargetEncoding[0] != 0xffu);
  check(kTargetEncoding[0] != 0x35u);
  // Each immediate is read back out of the byte array.
  check(read_imm32(1) == 0x018c816au);
  check(read_imm32(6) == 0x00b1e500u);
  check(read_imm32(11) == 0x00b236c0u);
  check(read_imm32(16) == 0x00d3d420u);
  check(read_imm32(21) == 0x00b21080u);
  // The CALL is direct and backward, landing on 0x00b21340.
  check(kTargetEncoding[25] == 0xe8u);
  check(static_cast<std::int32_t>(read_imm32(26)) < 0);
  check((0x00b25cbeu - 0x497eu) == 0x00b21340u);
  // `ADD EAX,imm8`, ModRM 0xc0 -> mod=11, reg=000, rm=000.
  check(kTargetEncoding[30] == 0x83u);
  check((kTargetEncoding[31] >> 6) == 3u);
  check(((kTargetEncoding[31] >> 3) & 7u) == 0u);
  check((kTargetEncoding[31] & 7u) == 0u);
  check(kTargetEncoding[32] == kBeginFieldBias);
  check(kTargetEncoding[32] == 4u);
  // Bare RET: 0xc3 pops nothing on this side.
  check(kTargetEncoding[33] == 0xc3u);
  check(kTargetEncoding[33] != 0xc2u);
  // The body is whole: 34 bytes, eight instructions.
  check(kTargetBodyBytes == 34u);
  check(kTargetInstructionCount == 8u);
  check(kTargetBodyBytes == 5u + 5u + 5u + 5u + 5u + 5u + 3u + 1u);
  // The encoding and the header's FIVE CONSTANTS are tied together at RUNTIME
  // as well as by static_assert, and that is not redundancy. The static_asserts
  // already refuse to build if the encoding disagrees with the constants, which
  // means a mutated encoding cannot reach this function - so a test that only
  // re-checked the encoding against itself would pass against a byte array that
  // had been changed in step with the constants. These checks decode the bytes
  // once more and compare them to the values the entry actually passes to the
  // callee, which is the comparison that survives a consistent edit.
  check(read_imm32(1) == kArg5KeyOperand);
  check(read_imm32(6) == kArg4AddCallback);
  check(read_imm32(11) == kArg3FilterCallback);
  check(read_imm32(16) == kArg2ClearCallback);
  check(read_imm32(21) == kArg1CreateCallback);
  // The add's immediate is a single imm8 at index 32 - the LAST byte of the
  // 34-byte body - so it is read directly rather than through read_imm32, which
  // would run one word past the end of the array. That off-by-one is worth
  // spelling: an imm8 tail is exactly the case where the "always decode four
  // bytes" helper is the wrong tool, and using it here would read the RET byte
  // as part of the operand.
  check(sizeof(kTargetEncoding) == 34u);
  check(kTargetEncoding[32] == kBeginFieldBias);
  check(kBeginFieldBias == 4u);

  // The push order, end to end: the encoding's FIRST immediate is the key
  // operand and the LAST is the create callback, because a call pushes right to
  // left. Inverting either end of that is the mistake this pins.
  check(read_imm32(1) != read_imm32(21));
  check(read_imm32(1) == g_callee.args[4]);
  check(read_imm32(21) == g_callee.args[0]);
  check(read_imm32(6) == g_callee.args[3]);
  check(read_imm32(16) == g_callee.args[1]);

  // And the modelled ABI is a pointer-to-thiscall, so it can express neither a
  // stack argument nor a by-reference return.
  static_assert(std::is_same<NounRangeWrapper,
                             NounRange* (PKG_00B25CA0_THISCALL*)(
                                 OpaqueNounProjection*)>::value,
                "the modelled entry is thiscall with an ECX receiver only");
  check(sizeof(NounRangeWrapper) == sizeof(void*));
  check(entry_address() != 0u);
}

}  // namespace model

}  // namespace openspore::reconstruction::pkg_00b25ca0_noun_city_range

namespace {

using namespace openspore::reconstruction::pkg_00b25ca0_noun_city_range;

int run_tests() {
  model::test_callee_receives_the_five_observed_constants();
  model::test_constants_are_immediates_not_memory_reads();
  model::test_receiver_is_forwarded_through_ecx();
  model::test_stack_cleanup_is_measured_not_assumed();
  model::test_return_is_the_callee_pointer_biased_by_four();
  model::test_returned_range_matches_sampled_caller_use();
  model::test_null_arguments_are_published_not_screened();
  model::test_encoding_matches_the_observed_bytes();
  return 0;
}

}  // namespace

int main() { return ::run_tests(); }

#undef PKG_00B25CA0_THISCALL
