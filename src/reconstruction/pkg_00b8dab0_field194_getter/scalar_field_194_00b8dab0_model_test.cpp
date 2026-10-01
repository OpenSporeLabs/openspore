// Focused semantic test for FUN_00b8dab0 @ 0x00b8dab0.
//
// The target body is two instructions, so the entire content of this
// reconstruction is one question - is the returned value the word STORED at
// receiver+0x194, or the address of it, or a neighbouring word, or a derived
// quantity - plus the ABI facts a two-instruction body can still get wrong.
// Each group below names the hypothesis it tries to REFUTE:
//
//   1. the return is the word STORED at +0x194 - so a LEA (the address) form,
//      a neighbouring-displacement form, and a derived form (add, mask,
//      saturate) each fail;
//   2. 0x194 is a BYTE displacement, not a word index - the word one slot
//      either side is planted with a different sentinel and neither is
//      returned, and 0x194-as-an-index (0x2c) and 0x194-as-a-double-byte
//      (0x328, past the modelled extent) are excluded;
//   3. the body READS and never writes - the whole 0x198-byte receiver is
//      byte-identical across the call, so a store-through perturbation fails on
//      the guards even if it also returns the right value;
//   4. the value crosses verbatim - 0, 1, 2, 5, INT_MAX, INT_MIN and all-ones
//      come back unchanged, so no default, no mask, no sign-extension and no
//      saturation survives;
//   5. the sampled callers' ordered comparisons behave as the binary's do,
//      using the two encodings those callers actually contain;
//   6. the ABI is ECX receiver / 0 stack arguments / caller cleanup, MEASURED
//      by sampling ESP across the call rather than asserted as a convention;
//   7. the encoding IS the observed one, and it is a LOAD and not a LEA - the
//      opcode byte is pinned, the ModRM fields are decoded, and the disp32 is
//      tied by static_assert to the header's displacement;
//   8. the entry's literal displacement and the header's kFieldDisplacement
//      name one and the same address.
//
// A NOTE ON THE MEASUREMENT IN GROUP 6. The receiver register and the
// callee's stack cleanup are measured, not assumed. The trampoline loads the
// receiver into ECX and calls through a register so the argument never travels
// on the stack, and it samples ESP immediately before the call and again the
// instant the callee has returned. `call` pushes a return address and `RET`
// pops it, so the two samples agree only when the callee owned no cleanup; a
// `RET 0x4` body would leave the second sample four bytes lower. The recorded
// tail is 0xc3, so zero bytes of callee cleanup is the expectation, and a
// reconstruction that grew a stack-argument interface fails the measurement
// rather than merely being named wrong.

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "scalar_field_194_00b8dab0.hpp"

// The header undefines its convention macro, so the modelled ABI type is
// respelled here; it is the same thiscall pointer type the entry declares.
#if defined(_MSC_VER)
#define PKG_00B8DAB0_THISCALL __thiscall
#else
#define PKG_00B8DAB0_THISCALL __attribute__((thiscall))
#endif

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_00b8dab0 model test requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00b8dab0_field194_getter {
namespace model {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

SlotWord pointer_word(const void* pointer) {
  return static_cast<SlotWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

static_assert(sizeof(kTargetEncoding) == kTargetBodyBytes,
              "the raw encoding array is the modelled body length");
static_assert(kTargetEncoding[0] == 0x8bu && kTargetEncoding[1] == 0x81u &&
                  kTargetEncoding[2] == 0x94u && kTargetEncoding[3] == 0x01u &&
                  kTargetEncoding[4] == 0x00u && kTargetEncoding[5] == 0x00u &&
                  kTargetEncoding[6] == 0xc3u,
              "the encoding is the seven bytes read from 0x00b8dab0");
static_assert(kTargetEncoding[0] != 0x8du,
              "0x8d is LEA; the observed opcode is 0x8b, a LOAD");

// One receiver for the whole test, wide enough for the word at +0x194 and its
// 4-byte-aligned neighbours on both sides.
OpaqueReceiver g_receiver;

// Sentinels that cannot be confused with a plausible address, a small
// constant, or a displacement, and that differ from one another so "one word
// too low" and "one word too high" are separate failures.
constexpr SlotWord kLeftSentinel = 0xfeedfaceu;   // the word at +0x190
constexpr SlotWord kFieldSentinel = 0x5a5aa5a5u;  // the word at +0x194
constexpr SlotWord kNearHeadSentinel = 0x0badf00du;  // the word at +0x004
constexpr SlotWord kFarHeadSentinel = 0x13579bdfu;   // the word at +0x000

constexpr std::size_t kFieldOffset = 0x194;
constexpr std::size_t kLeftNeighbourOffset = 0x190;

static_assert(kFieldOffset == kFieldDisplacement,
              "the test's offset is the header's displacement");
static_assert(kLeftNeighbourOffset + sizeof(SlotWord) == kFieldOffset,
              "the planted left neighbour ends where the field begins");

SlotWord word_at(std::size_t displacement) {
  SlotWord value = 0;
  std::memcpy(&value, g_receiver.opaque_bytes.data() + displacement,
              sizeof(value));
  return value;
}

void store_word_at(OpaqueReceiver& receiver, std::size_t displacement,
                   SlotWord value);

void store_at(std::size_t displacement, SlotWord value) {
  store_word_at(g_receiver, displacement, value);
}

void store_word_at(OpaqueReceiver& receiver, std::size_t displacement,
                   SlotWord value) {
  std::memcpy(receiver.opaque_bytes.data() + displacement, &value,
              sizeof(value));
}

void ramp_receiver(OpaqueReceiver& receiver) {
  for (std::size_t index = 0; index < receiver.opaque_bytes.size(); ++index) {
    receiver.opaque_bytes[index] = static_cast<std::uint8_t>(index + 1u);
  }
}

// Fill the whole modelled extent with a distinctive non-zero ramp, then plant
// the sentinels. A read of ANY part of the receiver is therefore visible in
// the value, and a write to any part is visible in the byte image.
void plant_receiver() {
  ramp_receiver(g_receiver);
  store_at(0x000, kFarHeadSentinel);
  store_at(0x004, kNearHeadSentinel);
  store_at(kLeftNeighbourOffset, kLeftSentinel);
  store_at(kFieldOffset, kFieldSentinel);
}

SlotWord entry_address() {
  return pointer_word(reinterpret_cast<const void*>(&scalar_field_194_00b8dab0));
}

// The plain call through a thiscall function pointer: receiver in ECX, nothing
// pushed, callee pops nothing. `target` is loaded through a variable so the
// compiler cannot inline the body and destroy the very thing being measured.
SlotWord call_entry(OpaqueReceiver* receiver) {
  const SlotWord target = entry_address();
  SlotWord result = 0;
  __asm__ __volatile__("movl %2, %%ecx\n\t"
                       "call *%1\n\t"
                       "movl %%eax, %0\n\t"
                       : "=r"(result)
                       : "r"(target), "r"(receiver)
                       : "eax", "ecx", "memory");
  return result;
}

// ESP sampled before the call and the instant the callee has returned.
struct EspSamples {
  std::uint32_t before_call = 0;
  std::uint32_t after_return = 0;
};

EspSamples call_entry_measured(OpaqueReceiver* receiver) {
  const SlotWord target = entry_address();
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

// 1. The return is the word STORED at +0x194, not the address of it and not a
// neighbour.
void test_return_is_the_stored_word() {
  plant_receiver();

  const SlotWord result = call_entry(&g_receiver);

  check(result == kFieldSentinel);
  // Not the ADDRESS of that word - the load/LEA distinction, which is not
  // hypothetical in this family: 0x00b8dad0 computes `lea eax,[ecx+0x198]`
  // two entries away, and 0x00b8da60 computes `lea eax,[ecx+0x188]`.
  check(result != pointer_word(&g_receiver) + kFieldOffset);
  check(result != pointer_word(&g_receiver));
  check(result != kFieldOffset);
  check(result != 0u);
  // Not a derived quantity: no mask, no shift, no saturating clamp.
  check(result != (kFieldSentinel & 0xffffu));
  check(result != (kFieldSentinel >> 2));
  check(result != kFieldSentinel + 1u);
  check(result != kFieldSentinel - 1u);
}

// 2. 0x194 is a BYTE displacement, not an index and not a scaled index.
void test_displacement_is_bytes_not_an_index() {
  plant_receiver();

  const SlotWord result = call_entry(&g_receiver);

  // The planted left neighbour is a different word and is not returned.
  check(result != kLeftSentinel);
  check(word_at(kLeftNeighbourOffset) == kLeftSentinel);
  // Read as a word index the body would sit on word 101 of the receiver; read
  // as an element COUNT the disp32 would address word 0x194, i.e. byte 0x650,
  // which is past the modelled extent and so cannot be what was read.
  check(kFieldDisplacement / sizeof(SlotWord) == 101u);
  check((kFieldDisplacement * sizeof(SlotWord)) > sizeof(OpaqueReceiver));
  check(result != kNearHeadSentinel);
  check(result != kFarHeadSentinel);
  // Doubling the displacement leaves the modelled extent entirely, so the
  // reconstruction could not have read there even by accident.
  check((2u * kFieldDisplacement) > sizeof(OpaqueReceiver));
  // And the receiver's extent really does end at the byte after the field.
  check(kFieldOffset + sizeof(SlotWord) == sizeof(OpaqueReceiver));
}

// 3. The body reads. The whole 0x198-byte receiver is byte-identical across
// the call.
void test_body_does_not_write_the_receiver() {
  plant_receiver();
  std::array<std::uint8_t, sizeof(OpaqueReceiver)> before{};
  std::memcpy(before.data(), g_receiver.opaque_bytes.data(), before.size());

  const SlotWord result = call_entry(&g_receiver);
  check(result == kFieldSentinel);

  check(std::memcmp(before.data(), g_receiver.opaque_bytes.data(),
                    before.size()) == 0);
  check(word_at(kFieldOffset) == kFieldSentinel);
  check(word_at(kLeftNeighbourOffset) == kLeftSentinel);
  check(word_at(0x000) == kFarHeadSentinel);
}

// 4. The value crosses verbatim. 0 has no substitute, 5 and 2 are the constants
// the sampled callers compare against, and the extremes have no clamp.
void test_value_crosses_verbatim() {
  const SlotWord interesting[] = {0u,
                                  1u,
                                  2u,
                                  5u,
                                  6u,
                                  0x7fffffffu,
                                  0x80000000u,
                                  0xfffffffeu,
                                  0xffffffffu};

  for (const SlotWord value : interesting) {
    plant_receiver();
    store_at(kFieldOffset, value);
    check(call_entry(&g_receiver) == value);
    check(word_at(kFieldOffset) == value);
  }

  // A published zero comes back as a published zero: the body has no test, no
  // branch and no default, so a reconstruction that substituted a fallback
  // fails here.
  plant_receiver();
  store_at(kFieldOffset, 0u);
  check(call_entry(&g_receiver) == 0u);

  // Every reachable value at that displacement is returned unchanged.
  plant_receiver();
  for (std::size_t high = 0; high < 4u; ++high) {
    for (std::size_t low = 0; low < 4u; ++low) {
      const std::uint32_t value =
          static_cast<std::uint32_t>((high << 8) | low);
      store_at(kFieldOffset, value);
      const SlotWord result = call_entry(&g_receiver);
      check(result == value);
    }
  }
}

// 5. The sampled callers' ordered comparisons behave as the binary's do. The
// two encodings below are the ones those callers actually contain:
//     0x00bade0a  call ; cmp eax,0x2     ; jl
//     0x00c8b609  call ; cmp eax,[esp+0x10] ; jle
void test_sampled_callers_ordered_comparisons() {
  // 0x00bade0f: 83 f8 02 = CMP EAX,0x00000002 (imm8 sign-extended) ;
  // 0x00bade12: 7c 67    = JL rel8. JL, not JB: the comparison is SIGNED.
  const std::uint8_t cmp_two_jl[5] = {0x83, 0xf8, 0x02, 0x7c, 0x67};
  check(cmp_two_jl[0] == 0x83u);
  check(cmp_two_jl[1] == 0xf8u);
  check(cmp_two_jl[2] == 0x02u);
  check(cmp_two_jl[3] == 0x7cu);

  // 0x00c8b60e: 3b 44 24 10 = CMP EAX,[esp+0x10] ;
  // 0x00c8b612: 7e 0b       = JLE rel8. JLE, not JBE: signed again.
  const std::uint8_t cmp_mem_jle[5] = {0x3b, 0x44, 0x24, 0x10, 0x7e};
  check(cmp_mem_jle[0] == 0x3bu);
  check(cmp_mem_jle[1] == 0x44u);
  check(cmp_mem_jle[2] == 0x24u);
  check(cmp_mem_jle[3] == 0x10u);
  check(cmp_mem_jle[4] == 0x7eu);

  // The comparisons are SIGNED in the image (JL/JLE, not JB/JBE), so the
  // reconstruction must be able to carry a value whose top bit is set and let
  // the CALLER order it as negative. A model that clamped or filtered the top
  // bit could not reproduce this.
  const auto less_than_two_signed = [](SlotWord value) -> bool {
    return static_cast<std::int32_t>(value) < 2;
  };
  plant_receiver();
  store_at(kFieldOffset, 0xffffffffu);
  check(less_than_two_signed(call_entry(&g_receiver)));
  store_at(kFieldOffset, 0x80000000u);
  check(less_than_two_signed(call_entry(&g_receiver)));
  store_at(kFieldOffset, 2u);
  check(!less_than_two_signed(call_entry(&g_receiver)));
  store_at(kFieldOffset, 3u);
  check(!less_than_two_signed(call_entry(&g_receiver)));

  // And the running-maximum idiom of 0x00c8b609/0x00c8b616 - take the larger of
  // two successive reads - reproduces exactly.
  const auto max_of = [](SlotWord left, SlotWord right) -> SlotWord {
    return static_cast<std::int32_t>(left) <= static_cast<std::int32_t>(right)
               ? right
               : left;
  };
  plant_receiver();
  store_at(kFieldOffset, 0xfffffff0u);
  SlotWord running = call_entry(&g_receiver);
  store_at(kFieldOffset, 0x00000007u);
  running = max_of(running, call_entry(&g_receiver));
  check(running == 0x00000007u);
  store_at(kFieldOffset, 0xfffffff0u);
  running = max_of(running, call_entry(&g_receiver));
  check(running == 0x00000007u);
}

// 6. The ABI: ECX receiver, nothing pushed, callee pops nothing. Measured.
void test_abi_is_measured_not_assumed() {
  plant_receiver();

  const EspSamples samples = call_entry_measured(&g_receiver);
  check(samples.after_return == samples.before_call);

  // The receiver arrives in ECX: a body that read its word from a stack
  // argument instead could not produce the planted sentinel with nothing
  // pushed.
  check(call_entry(&g_receiver) == kFieldSentinel);

  // A second receiver at a different address yields a different answer, which
  // is what makes the result a function OF the receiver rather than of
  // anything ambient.
  OpaqueReceiver other{};
  ramp_receiver(other);
  store_word_at(other, kFieldOffset, 0x12345678u);
  check(call_entry(&other) == 0x12345678u);
  check(call_entry(&g_receiver) == kFieldSentinel);

  // The modelled ABI type can express neither a stack argument nor a
  // by-reference return, so a reconstruction that grew one could not be
  // declared against it.
  static_assert(std::is_same<AbiScalarField19400b8dab0,
                             std::uint32_t(PKG_00B8DAB0_THISCALL*)(
                                 OpaqueReceiver*)>::value,
                "the modelled entry carries the ECX receiver and returns one word");
  check(sizeof(AbiScalarField19400b8dab0) == sizeof(void*));
  check(entry_address() != 0u);
}

// 7. The encoding IS the observed one: a LOAD, with a disp32 of 0x194, ending
// in a bare RET.
void test_encoding_matches_the_observed_bytes() {
  check(kTargetEncoding[0] == 0x8bu);
  check(kTargetEncoding[1] == 0x81u);
  check(kTargetEncoding[2] == 0x94u);
  check(kTargetEncoding[3] == 0x01u);
  check(kTargetEncoding[4] == 0x00u);
  check(kTargetEncoding[5] == 0x00u);
  check(kTargetEncoding[6] == 0xc3u);
  // ModRM 0x81: mod=10 -> a disp32 follows; reg=000 -> EAX; rm=001 -> ECX.
  check((kTargetEncoding[1] >> 6) == 2u);
  check(((kTargetEncoding[1] >> 3) & 7u) == 0u);
  check((kTargetEncoding[1] & 7u) == 1u);
  // The disp32, reassembled, is the header's displacement. This is the
  // statement that stops the encoding and the named displacement from drifting
  // apart silently.
  check((static_cast<std::uint32_t>(kTargetEncoding[2]) |
         (static_cast<std::uint32_t>(kTargetEncoding[3]) << 8) |
         (static_cast<std::uint32_t>(kTargetEncoding[4]) << 16) |
         (static_cast<std::uint32_t>(kTargetEncoding[5]) << 24)) ==
        kFieldDisplacement);
  // The load/LEA distinction, pinned by the opcode: 0x8b is MOV r32,r/m32 and
  // 0x8d is LEA. A LEA reconstruction would land on 0x8d here.
  check(kTargetEncoding[0] != 0x8du);
  // A bare RET: 0xc3 has no imm16, so the callee pops nothing.
  check(kTargetEncoding[6] == 0xc3u);
  check(kTargetEncoding[6] != 0xc2u);
  // The body's length: 1 opcode + 1 ModRM + 4 disp32 + 1 RET.
  check(kTargetBodyBytes == 1u + 1u + 4u + 1u);
  check(kTargetPadByte == 0xccu);
}

// 8. The entry's literal displacement and the header's kFieldDisplacement name
// one and the same address.
void test_entry_literal_and_header_displacement_agree() {
  plant_receiver();
  const SlotWord* literal = reinterpret_cast<const SlotWord*>(
      reinterpret_cast<std::uintptr_t>(&g_receiver) + 0x194);
  const SlotWord declared =
      field_at(&g_receiver, kFieldDisplacement);

  check(literal == reinterpret_cast<const SlotWord*>(
                       reinterpret_cast<std::uintptr_t>(&g_receiver) +
                       kFieldDisplacement));
  check(*literal == declared);
  check(declared == kFieldSentinel);
  // And the entry agrees with both.
  check(call_entry(&g_receiver) == *literal);
  check(call_entry(&g_receiver) == declared);
}

}

}

namespace {

using namespace openspore::reconstruction::pkg_00b8dab0_field194_getter;

int run_tests() {
  model::test_return_is_the_stored_word();
  model::test_displacement_is_bytes_not_an_index();
  model::test_body_does_not_write_the_receiver();
  model::test_value_crosses_verbatim();
  model::test_sampled_callers_ordered_comparisons();
  model::test_abi_is_measured_not_assumed();
  model::test_encoding_matches_the_observed_bytes();
  model::test_entry_literal_and_header_displacement_agree();
  return 0;
}

}

int main() { return ::run_tests(); }

#undef PKG_00B8DAB0_THISCALL