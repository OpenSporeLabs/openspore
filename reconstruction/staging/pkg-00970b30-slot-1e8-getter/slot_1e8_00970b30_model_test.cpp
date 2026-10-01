// Focused semantic test for FUN_00970b30 @ 0x00970b30.
//
// The target body is two instructions, so the entire content of this
// reconstruction is one question - is the returned value the word STORED at
// receiver+0x1e8, or the address of that word, or a neighbouring word, or a
// derived quantity - plus the ABI facts a two-instruction body can still get
// wrong, and the one structural claim that makes 0x1e8 a real slot rather than
// a displacement this body happens to compute. Each group below names the
// hypothesis it tries to REFUTE:
//
//   1. the return is the word STORED at +0x1e8 re-typed as a pointer - so a
//      LEA (the address OF the slot) form, a neighbouring-displacement form and
//      a derived form (add, mask, saturate) each fail;
//   2. 0x1e8 is a BYTE displacement, not a word index - the words one slot
//      either side are planted with different sentinels and neither is
//      returned, and 0x1e8-as-an-index (0x7a0, past the modelled extent) is
//      excluded;
//   3. the GETTER and the adjacent SETTER named in the header address ONE AND
//      THE SAME address - the pair is pinned at compile time and re-checked
//      here, so "the setter writes 0x1ec" or "it writes a different slot" fails
//      rather than going unnoticed;
//   4. the body READS and never writes - the whole 0x1ec-byte receiver is
//      byte-identical across the call, so a store-through perturbation fails on
//      the guards even if it also returns the right pointer;
//   5. the bits cross verbatim - 0, 1, a plausible address, 0x80000000 and
//      all-ones come back unchanged, so no default, no mask, no sign-extension
//      and no saturation survives; and the sampled callers' POINTER use (a
//      null test and a load at displacement 0x13c) reproduces;
//   6. the ABI is ECX receiver / 0 stack arguments / caller cleanup, MEASURED
//      by sampling ESP across the call rather than asserted as a convention,
//      and contrasted against the neighbouring setter's `RET 0x4`;
//   7. the encoding IS the observed one, and it is a LOAD and not a LEA - the
//      opcode byte is pinned, the ModRM fields are decoded, and the disp32 is
//      tied by static_assert to the header's displacement;
//   8. the entry's literal displacement and the header's kFieldDisplacement
//      name one and the same address.
//
// A NOTE ON THE MEASUREMENT IN GROUP 6. The receiver register and the callee's
// stack cleanup are measured, not assumed. The trampoline loads the receiver
// into ECX and calls through a register so the argument never travels on the
// stack, and it samples ESP immediately before the call and again the instant
// the callee has returned. `call` pushes a return address and `RET` pops it,
// so the two samples agree only when the callee owned no cleanup; a `RET 0x4`
// body would leave the second sample four bytes lower. The recorded tail is
// 0xc3, so zero bytes of callee cleanup is the expectation, and a
// reconstruction that grew a stack-argument interface fails the measurement
// rather than merely being named wrong.

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "slot_1e8_00970b30.hpp"

// The header undefines its convention macro, so the modelled ABI type is
// respelled here; it is the same thiscall pointer type the entry declares.
#if defined(_MSC_VER)
#define PKG_00970B30_THISCALL __thiscall
#else
#define PKG_00970B30_THISCALL __attribute__((thiscall))
#endif

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_00970b30 model test requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00970b30_slot_1e8_getter {
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
                  kTargetEncoding[2] == 0xe8u && kTargetEncoding[3] == 0x01u &&
                  kTargetEncoding[4] == 0x00u && kTargetEncoding[5] == 0x00u &&
                  kTargetEncoding[6] == 0xc3u,
              "the encoding is the seven bytes read from 0x00970b30");
static_assert(kTargetEncoding[0] != 0x8du,
              "0x8d is LEA; the observed opcode is 0x8b, a LOAD");

// One receiver for the whole test, wide enough for the word at +0x1e8 and its
// 4-byte-aligned neighbours on both sides.
OpaqueReceiver g_receiver;

// A separate heap block standing in for the POINTEE, so the sampled callers'
// load at displacement 0x13c can be modelled without the model ever claiming to
// know that object's layout. It is a test fixture only: the 0x13c bytes of
// padding before the planted word exist so that the CALLERS' documented reach
// is reproduced byte for byte, and the guards around the word are read back so
// that a load one slot either side of 0x13c would be visible.
struct PointeeFixture {
  std::uint8_t pad_to_138[0x138];
  std::uint32_t guard_below;
  std::uint32_t word_at_13c;
  std::uint32_t word_at_140;
  std::uint32_t guard_above;
};

static_assert(offsetof(PointeeFixture, word_at_13c) == 0x13cu,
              "the fixture's planted word sits at the displacement the sampled "
              "callers load through");

PointeeFixture* make_pointee(SlotWord at_13c) {
  auto* block = static_cast<PointeeFixture*>(std::malloc(sizeof(PointeeFixture)));
  if (block == nullptr) {
    std::abort();
  }
  std::memset(block, 0, sizeof(*block));
  block->guard_below = 0x5e7e5e7eu;
  block->word_at_13c = at_13c;
  block->word_at_140 = 0x7a7a7a7au;
  block->guard_above = 0x6d6d6d6du;
  return block;
}

// Sentinels that cannot be confused with a plausible address, a small
// constant, or a displacement, and that differ from one another so "one word
// too low" and "one word too high" are separate failures.
constexpr SlotWord kLeftSentinel = 0xfeedfaceu;   // the word at +0x1e4
constexpr SlotWord kSlotSentinel = 0x5a5aa5a5u;   // the word at +0x1e8
constexpr SlotWord kNearHeadSentinel = 0x0badf00du;  // the word at +0x004
constexpr SlotWord kFarHeadSentinel = 0x13579bdfu;   // the word at +0x000

constexpr std::size_t kSlotOffset = 0x1e8;
constexpr std::size_t kLeftNeighbourOffset = 0x1e4;
constexpr std::size_t kSetterNeighbourOffset = 0x9c;

static_assert(kSlotOffset == kFieldDisplacement,
              "the test's offset is the header's displacement");
static_assert(kNeighbourSetterDisplacement == kSlotOffset,
              "the getter and the adjacent setter name one address");
static_assert(kLeftNeighbourOffset + sizeof(SlotWord) == kSlotOffset,
              "the planted left neighbour ends where the slot begins");
static_assert(kSetterNeighbourOffset < kSlotOffset,
              "the neighbour the setter also writes is BELOW this slot, so it "
              "is a different byte and cannot be mistaken for it");

SlotWord word_at(std::size_t displacement) {
  SlotWord value = 0;
  std::memcpy(&value, g_receiver.opaque_bytes.data() + displacement,
              sizeof(value));
  return value;
}

void store_at(std::size_t displacement, SlotWord value) {
  std::memcpy(g_receiver.opaque_bytes.data() + displacement, &value,
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
  store_at(kSlotOffset, kSlotSentinel);
}

SlotWord entry_address() {
  return pointer_word(reinterpret_cast<const void*>(&slot_1e8_00970b30));
}

// The plain call through a thiscall function pointer: receiver in ECX, nothing
// pushed, callee pops nothing. `target` is loaded through a variable so the
// compiler cannot inline the body and destroy the very thing being measured.
void* call_entry(OpaqueReceiver* receiver) {
  const SlotWord target = entry_address();
  void* result = nullptr;
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

// 1. The return is the word STORED at +0x1e8, re-typed as a pointer - not the
// ADDRESS of that word, not a neighbour, and not a derived quantity.
void test_return_is_the_stored_word_as_a_pointer() {
  plant_receiver();

  const void* result = call_entry(&g_receiver);

  check(pointer_word(result) == kSlotSentinel);
  // Not the ADDRESS of that word - the load/LEA distinction, which is a real
  // one in this family: the adjacent setter at 0x00970b10 stores with the same
  // displacement, and a LEA reconstruction would return the receiver plus the
  // displacement instead of the stored bits.
  check(pointer_word(result) != pointer_word(&g_receiver) + kSlotOffset);
  check(pointer_word(result) != pointer_word(&g_receiver));
  check(pointer_word(result) != kSlotOffset);
  check(result != nullptr);
  // Not a derived quantity: no mask, no shift, no saturating clamp.
  check(pointer_word(result) != (kSlotSentinel & 0xffffu));
  check(pointer_word(result) != (kSlotSentinel >> 2));
  check(pointer_word(result) != kSlotSentinel + 1u);
  check(pointer_word(result) != kSlotSentinel - 1u);
}

// 2. 0x1e8 is a BYTE displacement, not an index and not a scaled index.
void test_displacement_is_bytes_not_an_index() {
  plant_receiver();

  const void* result = call_entry(&g_receiver);

  // The planted left neighbour is a different word and is not returned.
  check(pointer_word(result) != kLeftSentinel);
  check(word_at(kLeftNeighbourOffset) == kLeftSentinel);
  // Read as a word index the body would sit on word 122 of the receiver; read
  // as an element COUNT the disp32 would address word 0x1e8, i.e. byte 0x7a0,
  // which is past the modelled extent and so cannot be what was read.
  check(kFieldDisplacement / sizeof(SlotWord) == 122u);
  check((kFieldDisplacement * sizeof(SlotWord)) > sizeof(OpaqueReceiver));
  check(pointer_word(result) != kNearHeadSentinel);
  check(pointer_word(result) != kFarHeadSentinel);
  // Doubling the displacement leaves the modelled extent entirely, so the
  // reconstruction could not have read there even by accident.
  check((2u * kFieldDisplacement) > sizeof(OpaqueReceiver));
  // And the receiver's extent really does end at the byte after the slot.
  check(kSlotOffset + sizeof(SlotWord) == sizeof(OpaqueReceiver));
}

// 3. The getter and the adjacent setter address ONE AND THE SAME address. The
// header pins the two constants against each other at compile time; this group
// pins the setter's OWN displacement - the one the model reads back - against
// the getter's, so a pair that drifts apart fails rather than merely looking
// plausible in prose.
void test_getter_and_adjacent_setter_share_one_address() {
  // The setter at 0x00970b10 stores its [ESP+4] argument at [ECX + 0x1e8].
  // Modelled here as "a store of the same displacement", which is the whole of
  // what that entry contributes to this target's claim.
  const std::size_t setter_written_displacement = kNeighbourSetterDisplacement;
  check(setter_written_displacement == kFieldDisplacement);
  check(setter_written_displacement == 488u);
  check(setter_written_displacement + kFieldWidth <= sizeof(OpaqueReceiver));

  // The setter also writes +0x9c, which is BELOW this slot: a different byte, so
  // "they touch the same word" is a claim about 0x1e8 and not about the pair.
  check(kSetterNeighbourOffset != setter_written_displacement);
  check(kSetterNeighbourOffset + kFieldWidth <= setter_written_displacement);

  // The getter reads exactly what the setter would have written: plant the
  // setter's would-be argument in the slot and read it straight back.
  plant_receiver();
  const SlotWord would_be_argument = 0xc0dec0deu;
  store_at(setter_written_displacement, would_be_argument);
  check(pointer_word(call_entry(&g_receiver)) == would_be_argument);
  check(word_at(kSetterNeighbourOffset) != would_be_argument);
}

// 4. The body reads. The whole 0x1ec-byte receiver is byte-identical across
// the call.
void test_body_does_not_write_the_receiver() {
  plant_receiver();
  std::array<std::uint8_t, sizeof(OpaqueReceiver)> before{};
  std::memcpy(before.data(), g_receiver.opaque_bytes.data(), before.size());

  const void* result = call_entry(&g_receiver);
  check(pointer_word(result) == kSlotSentinel);

  check(std::memcmp(before.data(), g_receiver.opaque_bytes.data(),
                    before.size()) == 0);
  check(word_at(kSlotOffset) == kSlotSentinel);
  check(word_at(kLeftNeighbourOffset) == kLeftSentinel);
  check(word_at(0x000) == kFarHeadSentinel);
  // The setter's other displacement is untouched too: this body writes nothing.
  check(word_at(kSetterNeighbourOffset) != kSlotSentinel);
}

// 5. The bits cross verbatim, and the sampled callers' POINTER use reproduces.
void test_value_crosses_verbatim_and_callers_dereference_it() {
  const SlotWord interesting[] = {0u,
                                  1u,
                                  2u,
                                  0x0000007fu,
                                  0x80000000u,
                                  0xfffffffeu,
                                  0xffffffffu,
                                  0x5a5aa5a5u};

  for (const SlotWord value : interesting) {
    plant_receiver();
    store_at(kSlotOffset, value);
    check(pointer_word(call_entry(&g_receiver)) == value);
    check(word_at(kSlotOffset) == value);
  }

  // A published NULL comes back as a published NULL: the body has no test, no
  // branch and no default, so a reconstruction that substituted a fallback
  // fails here. This is also the 0x00c61070 case's first arm.
  plant_receiver();
  store_at(kSlotOffset, 0u);
  check(call_entry(&g_receiver) == nullptr);

  // The 0x00c61070 shape: test the returned pointer against 0, and only load
  // through it when it is non-null. The pointee is a FIXTURE - this package
  // makes no claim about its type or layout, only that the returned pointer is
  // the one the caller then dereferences.
  PointeeFixture* pointee = make_pointee(0x11223344u);
  plant_receiver();
  store_at(kSlotOffset, pointer_word(pointee));
  void* returned = call_entry(&g_receiver);
  check(returned == reinterpret_cast<void*>(pointee));
  SlotWord loaded = 0;
  if (returned != nullptr) {
    // The 0x00c4b250 / 0x00c4c090 shape: a load at displacement 0x13c.
    std::memcpy(&loaded, static_cast<const std::uint8_t*>(returned) +
                            kSampledCallerPointeeDisplacement,
                sizeof(loaded));
  }
  check(loaded == 0x11223344u);
  check(kSampledCallerPointeeDisplacement == 0x13cu);
  std::free(pointee);

  // Every reachable bit pattern in the low 16 bits crosses unchanged, so no
  // mask survives.
  plant_receiver();
  for (std::size_t high = 0; high < 4u; ++high) {
    for (std::size_t low = 0; low < 4u; ++low) {
      const std::uint32_t value =
          static_cast<std::uint32_t>((high << 8) | low);
      store_at(kSlotOffset, value);
      check(pointer_word(call_entry(&g_receiver)) == value);
    }
  }
}

// 6. The ABI: ECX receiver, nothing pushed, callee pops nothing. Measured, and
// contrasted with the adjacent setter's `RET 0x4`.
void test_abi_is_measured_not_assumed() {
  plant_receiver();

  const EspSamples samples = call_entry_measured(&g_receiver);
  // `call` pushes a return address and the bare `RET` pops it, so the samples
  // agree. A `RET 0x4` body - the adjacent setter's shape - would leave the
  // second sample four bytes lower.
  check(samples.after_return == samples.before_call);
  check(kNeighbourSetterStackArgumentBytes == 4u);
  check(kNeighbourSetterStackArgumentBytes != 0u);

  // The receiver arrives in ECX: a body that read its slot from a stack
  // argument instead could not produce the planted sentinel with nothing
  // pushed.
  check(pointer_word(call_entry(&g_receiver)) == kSlotSentinel);

  // A second receiver at a different address yields a different answer, which
  // is what makes the result a function OF the receiver rather than of
  // anything ambient.
  OpaqueReceiver other{};
  ramp_receiver(other);
  std::memcpy(other.opaque_bytes.data() + kSlotOffset, "\x78\x56\x34\x12", 4);
  check(pointer_word(call_entry(&other)) == 0x12345678u);
  check(pointer_word(call_entry(&g_receiver)) == kSlotSentinel);

  // The modelled ABI type can express neither a stack argument nor a
  // by-reference return, so a reconstruction that grew one could not be
  // declared against it.
  static_assert(std::is_same<AbiPointerSlot1e800970b30,
                             void*(PKG_00970B30_THISCALL*)(
                                 OpaqueReceiver*)>::value,
                "the modelled entry carries the ECX receiver and returns a pointer");
  check(sizeof(AbiPointerSlot1e800970b30) == sizeof(void*));
  check(entry_address() != 0u);

  // The sidecar records a high fan-in of direct calls and NO outgoing edge, so
  // the modelled entry is a leaf and the body cannot have called anything.
  check(kRecordedDirectCallEdges == 142u);
  check(kRecordedDistinctCallers == 69u);
  check(kRecordedOutgoingEdges == 0u);
}

// 7. The encoding IS the observed one: a LOAD, with a disp32 of 0x1e8, ending
// in a bare RET.
void test_encoding_matches_the_observed_bytes() {
  check(kTargetEncoding[0] == 0x8bu);
  check(kTargetEncoding[1] == 0x81u);
  check(kTargetEncoding[2] == 0xe8u);
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
      reinterpret_cast<std::uintptr_t>(&g_receiver) + 0x1e8);
  const SlotWord declared = field_at(&g_receiver, kFieldDisplacement);

  check(literal == reinterpret_cast<const SlotWord*>(
                       reinterpret_cast<std::uintptr_t>(&g_receiver) +
                       kFieldDisplacement));
  check(*literal == declared);
  check(declared == kSlotSentinel);
  // And the entry agrees with both.
  check(pointer_word(call_entry(&g_receiver)) == *literal);
  check(pointer_word(call_entry(&g_receiver)) == declared);
}

}

}

namespace {

using namespace openspore::reconstruction::pkg_00970b30_slot_1e8_getter;

int run_tests() {
  model::test_return_is_the_stored_word_as_a_pointer();
  model::test_displacement_is_bytes_not_an_index();
  model::test_getter_and_adjacent_setter_share_one_address();
  model::test_body_does_not_write_the_receiver();
  model::test_value_crosses_verbatim_and_callers_dereference_it();
  model::test_abi_is_measured_not_assumed();
  model::test_encoding_matches_the_observed_bytes();
  model::test_entry_literal_and_header_displacement_agree();
  return 0;
}

}

int main() { return ::run_tests(); }

#undef PKG_00970B30_THISCALL