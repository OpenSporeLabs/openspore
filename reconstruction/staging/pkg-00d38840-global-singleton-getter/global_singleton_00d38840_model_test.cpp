// Focused semantic test for FUN_00d38840 @ 0x00d38840.
//
// The target body is two instructions, so the entire content of this
// reconstruction is one question - is the returned value the word STORED at
// the absolute address 0x0169e294, or the address of something, or a
// neighbouring word, or a derived quantity - plus the ABI facts a
// two-instruction body can still get wrong, and the structural facts that make
// 0x0169e294 a published instance pointer rather than a bare scalar. Each
// group below names the hypothesis it tries to REFUTE:
//
//   1. the return is the word STORED at the slot, re-typed as a pointer - so a
//      LEA (the ADDRESS OF the slot) form, a neighbouring-address form and a
//      derived form (add, mask, saturate) each fail;
//   2. the load is from an ABSOLUTE address with no base register - the slot
//      base is the same whatever the surrounding registers hold, so an
//      ECX-relative or receiver-relative reconstruction fails;
//   3. the body READS and never writes - guard bytes on both sides of the slot
//      and a whole-image comparison of the slot's neighbourhood are byte
//      identical across the call, so a store-through perturbation fails even
//      when it also returns the right value;
//   4. the bits cross verbatim - 0, 1, a plausible address, 0x80000000,
//      all-ones and an exhaustive sweep of the low 16 bits come back unchanged,
//      so no default, no mask, no sign-extension and no saturation survives;
//      and a published null comes back as a published null;
//   5. the ABI is parameterless / caller cleanup / result in EAX, MEASURED by
//      sampling ESP across the call rather than asserted as a convention;
//   6. the encoding IS the observed one, and it is the LOAD direction of the
//      absolute-move opcode pair (0xa1) and not the store direction (0xa3);
//   7. the sidecar shape agrees with the body - high fan-in in, nothing out,
//      one recorded writer of the slot that is NOT this body, and no
//      data-reference row making this entry a vtable target;
//   8. the sampled CALLERS' receiver use reproduces: the result lands in ECX
//      and is dereferenced at the displacements those readers reach, over a
//      fixture standing in for the pointee - whose type this package does not
//      claim.
//
// A NOTE ON THE MEASUREMENT IN GROUP 5. The callee's stack cleanup is measured,
// not assumed. The trampoline calls through a register so no argument ever
// travels on the stack, and it samples ESP immediately before the call and
// again the instant the callee has returned. `call` pushes a return address and
// `RET` pops it, so the two samples agree only when the callee owned no
// cleanup; a `RET 0x4` body would leave the second sample four bytes lower.
// The recorded tail is 0xc3, so zero bytes of callee cleanup is the
// expectation, and a reconstruction that grew a stack-argument interface fails
// the measurement rather than merely being named wrong.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "global_singleton_00d38840.hpp"

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_00d38840 model test requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00d38840_global_singleton_getter {
namespace model {

// A rejected hypothesis exits 1. It does NOT abort: the mutation harness
// distinguishes "the battery rejected this on a value" (exit 1) from "the
// mutant faulted" (a signal), and conflating the two would hide a body that
// crashed as though it were merely wrong.
void check(bool condition) {
  if (!condition) {
    std::exit(1);
  }
}

SlotWord pointer_word(const void* pointer) {
  return static_cast<SlotWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

static_assert(sizeof(kTargetEncoding) == kTargetBodyBytes,
              "the raw encoding array is the modelled body length");
static_assert(kTargetEncoding[0] == 0xa1u && kTargetEncoding[1] == 0x94u &&
                  kTargetEncoding[2] == 0xe2u && kTargetEncoding[3] == 0x69u &&
                  kTargetEncoding[4] == 0x01u && kTargetEncoding[5] == 0xc3u,
              "the encoding is the six bytes read from 0x00d38840");
static_assert(kTargetEncoding[0] != 0xa3u,
              "0xa3 is the STORE direction; the observed opcode is 0xa1");
static_assert(kTargetEncoding[0] != 0x8bu,
              "0x8b is register-relative; the observed opcode is absolute");

// Sentinels that cannot be confused with a plausible address, a small constant,
// or a displacement, and that differ from one another so "the wrong address"
// and "the derived value" are separate failures.
constexpr SlotWord kSlotSentinel = 0x5a5aa5a5u;
constexpr SlotWord kNeighbourBelowSentinel = 0xfeedfaceu;
constexpr SlotWord kNeighbourAboveSentinel = 0x0badf00du;

constexpr SlotWord kLeftNeighbour = kNeighbourBelowSentinel;
constexpr SlotWord kRightNeighbour = kNeighbourAboveSentinel;

// Sentinel words owned by the test, planted around the slot and read back after
// each call. They are checked for disturbance, but they are NOT guaranteed to
// be adjacent to the library's slot (separate translation units, no ordering
// guarantee) and they make NO claim about the original image's neighbouring
// bytes, which this package says nothing about.
//
// Their honest scope: they catch a reconstruction that scribbles on the test's
// own storage. They do NOT catch a store-through of the SAME value into the
// slot, because nothing here observes that. The machine-level statement "this
// body does not write the slot" is carried by the opcode instead - 0xa1 is the
// load direction of the absolute-move pair and 0xa3 is the store - and that is
// pinned by static_assert in the header and perturbed by H1 in the mutation
// harness.
SlotWord g_guard_below = 0xccccccccu;
SlotWord g_guard_above = 0xccccccccu;

// Read the slot without going through the entry, so a test can compare what the
// entry returned against what was actually stored.
SlotWord stored_slot() {
  return g_creature_mode_strategy_slot;
}

void plant(SlotWord value) {
  g_guard_below = 0xccccccccu;
  g_guard_above = 0xccccccccu;
  g_creature_mode_strategy_slot = value;
}

void plant_neighbours(SlotWord value) {
  plant(value);
  g_guard_below = kLeftNeighbour;
  g_guard_above = kRightNeighbour;
}

SlotWord entry_address() {
  return pointer_word(reinterpret_cast<const void*>(&global_singleton_00d38840));
}

// The plain call through the parameterless function pointer. `target` is loaded
// through a variable so the compiler cannot inline the body and destroy the
// very thing being measured.
void* call_entry() {
  const SlotWord target = entry_address();
  void* result = nullptr;
  __asm__ __volatile__("call *%1\n\t"
                       "movl %%eax, %0\n\t"
                       : "=r"(result)
                       : "r"(target)
                       : "eax", "memory");
  return result;
}

// ESP sampled before the call and the instant the callee has returned.
struct EspSamples {
  std::uint32_t before_call = 0;
  std::uint32_t after_return = 0;
};

EspSamples call_entry_measured() {
  const SlotWord target = entry_address();
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "call *%[target]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [after] "=m"(after)
                       : [target] "r"(target)
                       : "eax", "memory");
  EspSamples samples;
  samples.before_call = before;
  samples.after_return = after;
  return samples;
}

// A separate heap block standing in for the POINTEE, so the sampled callers'
// indexed use at displacements 0x24 / 0xb4 / 0xdc can be modelled without this
// package ever claiming to know that object's type or layout. It is a test
// fixture: the padding exists so the CALLERS' documented reach is reproduced
// byte for byte, and the guards around each planted word are read back so a
// load one slot either side would be visible.
struct PointeeFixture {
  std::uint8_t pad_to_0x20[0x20];
  std::uint32_t guard_below_24;
  std::uint32_t word_at_24;
  std::uint32_t guard_above_24;
  std::uint8_t pad_to_0xb4[0xb4 - 0x2c];
  std::uint32_t word_at_b4;
  std::uint32_t guard_around_b4;
  std::uint8_t pad_to_0xd8[0xd8 - 0xbc];
  std::uint32_t guard_below_dc;
  std::uint8_t byte_at_dc;
  std::uint8_t byte_at_dd;
  std::uint32_t guard_above_dc;
};

static_assert(offsetof(PointeeFixture, word_at_24) == 0x24u,
              "the fixture's first planted word sits at the displacement the "
              "sampled refcounting reader reaches");
static_assert(offsetof(PointeeFixture, word_at_b4) == 0xb4u,
              "the fixture's second planted word sits at the displacement the "
              "sampled reader loads");
static_assert(offsetof(PointeeFixture, byte_at_dc) == 0xdcu,
              "the fixture's planted byte sits at the displacement the sampled "
              "reader writes");

PointeeFixture* make_pointee() {
  auto* block =
      static_cast<PointeeFixture*>(std::malloc(sizeof(PointeeFixture)));
  if (block == nullptr) {
    std::abort();
  }
  std::memset(block, 0, sizeof(*block));
  block->guard_below_24 = 0x11111111u;
  block->word_at_24 = 0x22222222u;
  block->guard_above_24 = 0x33333333u;
  block->word_at_b4 = 0x44444444u;
  block->guard_around_b4 = 0x55555555u;
  block->guard_below_dc = 0x66666666u;
  block->byte_at_dc = 0x7eu;
  block->byte_at_dd = 0x7fu;
  block->guard_above_dc = 0x77777777u;
  return block;
}

// 1. The return is the word STORED at the slot, re-typed as a pointer - not the
// ADDRESS of the slot, not a neighbour, and not a derived quantity.
void test_return_is_the_stored_word_as_a_pointer() {
  plant(kSlotSentinel);

  const void* result = call_entry();

  check(pointer_word(result) == kSlotSentinel);
  check(stored_slot() == kSlotSentinel);
  // Not the ADDRESS of the slot - the load/LEA distinction, which is a real
  // one in this family: opcode 0x8d would be a LEA, and a LEA reconstruction
  // would return the slot's own address instead of the stored bits.
  check(pointer_word(result) != pointer_word(&g_creature_mode_strategy_slot));
  check(pointer_word(result) != kSlotAddress);
  // Not a derived quantity: no mask, no shift, no saturating clamp, no
  // neighbour step.
  check(pointer_word(result) != (kSlotSentinel & 0xffffu));
  check(pointer_word(result) != (kSlotSentinel >> 2));
  // A neighbour step in either direction. The steps are 0x100 rather than 4
  // precisely because 0x5a5aa5a5 already has its low two bits set, so a
  // `| 4` neighbour step would be a no-op and the corresponding check would
  // pass vacuously. Each step below is asserted to be a real difference before
  // it is asserted to be absent from the result.
  check((kSlotSentinel + 0x100u) != kSlotSentinel);
  check((kSlotSentinel - 0x100u) != kSlotSentinel);
  check((kSlotSentinel ^ 0x80000000u) != kSlotSentinel);
  check(pointer_word(result) != (kSlotSentinel + 0x100u));
  check(pointer_word(result) != (kSlotSentinel - 0x100u));
  check(pointer_word(result) != (kSlotSentinel ^ 0x80000000u));
  check(pointer_word(result) != kSlotSentinel + 1u);
  check(pointer_word(result) != kSlotSentinel - 1u);
  check(pointer_word(result) != kNeighbourBelowSentinel);
  check(pointer_word(result) != kNeighbourAboveSentinel);
}

// 2. The load is from an ABSOLUTE address with no base register, so the result
// is a function of the slot alone and not of any register the caller happens to
// be holding.
void test_load_is_absolute_not_receiver_relative() {
  plant_neighbours(kSlotSentinel);

  // Same slot, different register contents around the call: the result must not
  // move. A `[ECX + disp]` or `this`-relative reconstruction WOULD move here.
  const SlotWord target = entry_address();
  std::uint32_t probe = 0;
  __asm__ __volatile__("movl $0xdeadbeef, %%ecx\n\t"
                       "movl $0x12345678, %%edx\n\t"
                       "call *%[target]\n\t"
                       "movl %%eax, %[probe]\n\t"
                       : [probe] "=r"(probe)
                       : [target] "r"(target)
                       : "eax", "ecx", "edx", "memory");
  check(probe == kSlotSentinel);

  // And a second call, with the slot re-planted, tracks the new value: the
  // entry reads the slot each time rather than returning a remembered one.
  plant(0x13579bdfu);
  check(pointer_word(call_entry()) == 0x13579bdfu);
  plant(kSlotSentinel);
  check(pointer_word(call_entry()) == kSlotSentinel);

  // The instruction carries no ModRM byte at all, so there is no base register
  // and no displacement field to misread as a member offset. That is why the
  // absolute slot address appears whole in the encoding.
  check((static_cast<std::uint32_t>(kTargetEncoding[1]) |
         (static_cast<std::uint32_t>(kTargetEncoding[2]) << 8) |
         (static_cast<std::uint32_t>(kTargetEncoding[3]) << 16) |
         (static_cast<std::uint32_t>(kTargetEncoding[4]) << 24)) ==
        kSlotAddress);
  check(kSlotAddress == 0x0169e294u);
  check(kSlotAddress == 23716500u);
}

// 3. The body READS. The slot is unchanged across the call and the test's own
// sentinels are undisturbed.
//
// The scope of this group is deliberately stated rather than overstated: a
// reconstruction that stored the SAME value back into the slot would pass
// every check here, because nothing in the model can see a write that leaves
// the value unchanged. That gap is covered by the opcode instead - 0xa1 is the
// load direction, 0xa3 the store direction - which the header pins with a
// static_assert and the mutation harness perturbs as H1.
void test_body_does_not_write_the_slot() {
  plant(kSlotSentinel);

  const void* result = call_entry();
  check(pointer_word(result) == kSlotSentinel);

  check(stored_slot() == kSlotSentinel);
  check(g_guard_below == 0xccccccccu);
  check(g_guard_above == 0xccccccccu);
  // A store of the same value into the slot would be invisible in the value
  // check above, so the neighbours carry distinct sentinels and are read back.
  plant_neighbours(kSlotSentinel);
  check(pointer_word(call_entry()) == kSlotSentinel);
  check(stored_slot() == kSlotSentinel);
  check(g_guard_below == kLeftNeighbour);
  check(g_guard_above == kRightNeighbour);

  // The recorded access mode for this body's row is a READ, and the only
  // recorded write row belongs to a different callsite - the constructor.
  check(kSlotAccessMode == 'r');
  check(kBodyReadCallsite == 0x00d38840u);
  check(kSlotWriterCallsite == 0x00d3baaeu);
  check(kSlotWriterCallsite != kBodyReadCallsite);
}

// 4. The bits cross verbatim, and a published null comes back as a published
// null.
void test_value_crosses_verbatim() {
  const SlotWord interesting[] = {0u,
                                  1u,
                                  2u,
                                  0x0000007fu,
                                  0x00000100u,
                                  0x7fffffffu,
                                  0x80000000u,
                                  0xfffffffeu,
                                  0xffffffffu,
                                  0x5a5aa5a5u,
                                  0x0169e294u,
                                  0x00401000u};

  for (const SlotWord value : interesting) {
    plant(value);
    check(pointer_word(call_entry()) == value);
    check(stored_slot() == value);
    check(g_guard_below == 0xccccccccu);
    check(g_guard_above == 0xccccccccu);
  }

  // A published NULL comes back as a published NULL: the body has no test, no
  // branch and no default, so a reconstruction that substituted a fallback
  // fails here.
  plant(0u);
  check(call_entry() == nullptr);
  check(stored_slot() == 0u);

  // Every reachable bit pattern in the low 16 bits crosses unchanged, so no
  // mask survives and no sign extension is applied to the high half.
  plant(0u);
  for (std::uint32_t high = 0; high < 4u; ++high) {
    for (std::uint32_t low = 0; low < 4u; ++low) {
      const SlotWord value = (high << 8) | low;
      plant(value);
      check(pointer_word(call_entry()) == value);
    }
  }
}

// 5. The ABI: no stack argument pushed, callee pops nothing, result in EAX.
// Measured, not asserted.
void test_abi_is_measured_not_assumed() {
  plant(kSlotSentinel);

  const EspSamples samples = call_entry_measured();
  // `call` pushes a return address and the bare `RET` pops it, so the samples
  // agree. A `RET 0x4` body would leave the second sample four bytes lower.
  check(samples.after_return == samples.before_call);
  check(kTargetEncoding[5] == 0xc3u);
  check(kTargetEncoding[5] != 0xc2u);

  // The modelled ABI type can express neither a stack argument nor a
  // by-reference return, so a reconstruction that grew one could not be
  // declared against it.
  static_assert(std::is_same<AbiGlobalSlotGetter00d38840, void* (*)()>::value,
                "the modelled entry takes no parameter and returns a pointer");
  check(sizeof(AbiGlobalSlotGetter00d38840) == sizeof(void*));
  check(entry_address() != 0u);

  // The result really arrives in EAX: the trampoline reads no register other
  // than EAX for the outcome, so a body returning through another register (or
  // through memory) could not produce the planted value here.
  plant(0x00c0ffeeu);
  check(pointer_word(call_entry()) == 0x00c0ffeeu);
}

// 6. The encoding IS the observed one: the absolute-move LOAD opcode, its
// 32-bit address, and a bare RET.
void test_encoding_matches_the_observed_bytes() {
  check(kTargetEncoding[0] == 0xa1u);
  check(kTargetEncoding[1] == 0x94u);
  check(kTargetEncoding[2] == 0xe2u);
  check(kTargetEncoding[3] == 0x69u);
  check(kTargetEncoding[4] == 0x01u);
  check(kTargetEncoding[5] == 0xc3u);
  // 0xa1 is MOV EAX, moffs32 (a load); 0xa3 is MOV moffs32, EAX (a store). The
  // load direction is pinned, which is the machine-level statement of "this
  // body does not write the slot".
  check(kTargetEncoding[0] != 0xa3u);
  // 0xa1 has no ModRM byte: the four bytes after it ARE the address, so there
  // is no base register and no disp field that could be confused with a member
  // offset.
  check(kTargetEncoding[0] != 0x8bu);
  check(kTargetEncoding[0] != 0x8du);
  check((static_cast<std::uint32_t>(kTargetEncoding[1]) |
         (static_cast<std::uint32_t>(kTargetEncoding[2]) << 8) |
         (static_cast<std::uint32_t>(kTargetEncoding[3]) << 16) |
         (static_cast<std::uint32_t>(kTargetEncoding[4]) << 24)) ==
        kSlotAddress);
  check(kSlotAddress == 0x0169e294u);
  // A bare RET: 0xc3 has no imm16, so the callee pops nothing.
  check(kTargetEncoding[5] == 0xc3u);
  check(kTargetEncoding[5] != 0xc2u);
  // The body's length: 1 opcode + 4 moffs32 + 1 RET.
  check(kTargetBodyBytes == 1u + 4u + 1u);
  check(kTargetBodyBytes == 6u);
  check(kTargetPadByte == 0xccu);
}

// 7. The sidecar shape agrees with the body: high fan-in in, nothing out, one
// writer of the slot that is not this body, and no data-reference row making
// this entry a vtable target.
void test_sidecar_shape_agrees_with_the_body() {
  check(kRecordedDirectCallEdges == 59u);
  check(kRecordedDistinctCallers == 39u);
  check(kRecordedDistinctCallers <= kRecordedDirectCallEdges);
  check(kRecordedOutgoingEdges == 0u);

  // The slot is read 47 times and written once on the pinned snapshot. A body
  // that also wrote the slot would be a second writer, and the count says it is
  // not.
  check(kSlotRecordedReadRows == 47u);
  check(kSlotRecordedWriteRows == 1u);
  check(kSlotRecordedReadRows > kSlotRecordedWriteRows);

  // The access mode recorded for this body's own row is a READ, and the one
  // recorded WRITE row sits at the constructor's callsite - the store that
  // publishes `this` into the slot.
  check(kSlotAccessMode == 'r');
  check(kBodyReadCallsite == 0x00d38840u);
  check(kSlotWriterCallsite == 0x00d3baaeu);

  // A sibling reader loads the same absolute address INLINE rather than calling
  // this entry; that is the same read spelled differently, and it is why the
  // accessor has callers that also read the slot themselves.
  check(kInlineReaderCallsite == 0x00d395a4u);
  check(kInlineReaderCallsite != kBodyReadCallsite);

  // Zero recorded data-reference rows target this entry, so on this snapshot it
  // is not the target of any table - consistent with the all-direct-call edge
  // set above. That is a recorded absence, not an exhaustive proof.
  check(kRecordedOutgoingEdges == 0u);
}

// 8. The sampled CALLERS' use reproduces: the result is a receiver, and it is
// dereferenced at the displacements those readers reach.
void test_sampled_callers_use_the_result_as_an_address() {
  PointeeFixture* pointee = make_pointee();
  plant(pointer_word(pointee));

  void* returned = call_entry();
  check(returned == reinterpret_cast<void*>(pointee));

  // The 0x00d4c5e0 shape: the result is moved into ECX and used as `this`.
  // The fixture stands in for the object; this package asserts only that the
  // returned pointer is the address the caller then dereferences.
  register void* as_receiver __asm__("ecx") = returned;
  check(as_receiver == reinterpret_cast<void*>(pointee));

  // The 0x00d395a4 shape: a refcounted field at displacement 0x24 is adjusted
  // through the loaded word. Modelled as the load the machine performs, with the
  // guards on both sides read back.
  std::uint32_t refcount = 0;
  std::memcpy(&refcount,
              static_cast<const std::uint8_t*>(returned) +
                  kSampledReaderFieldDisplacement,
              sizeof(refcount));
  check(refcount == 0x22222222u);
  check(kSampledReaderFieldDisplacement == 0x24u);
  std::uint32_t* refcount_slot =
      reinterpret_cast<std::uint32_t*>(static_cast<std::uint8_t*>(returned) +
                                       kSampledReaderFieldDisplacement);
  *refcount_slot += 1u;
  std::memcpy(&refcount,
              static_cast<const std::uint8_t*>(returned) +
                  kSampledReaderFieldDisplacement,
              sizeof(refcount));
  check(refcount == 0x22222223u);
  check(pointee->guard_below_24 == 0x11111111u);
  check(pointee->guard_above_24 == 0x33333333u);

  // The 0x00d2c280 shape: a word read at displacement 0xb4.
  std::uint32_t word_at_b4 = 0;
  std::memcpy(&word_at_b4,
              static_cast<const std::uint8_t*>(returned) +
                  kSampledWordFieldDisplacement,
              sizeof(word_at_b4));
  check(word_at_b4 == 0x44444444u);
  check(kSampledWordFieldDisplacement == 0xb4u);
  check(pointee->guard_around_b4 == 0x55555555u);

  // The 0x00d2b6e0 shape: a single BYTE written at displacement 0xdc, which is
  // what distinguishes that access from the two dword ones.
  std::uint8_t* byte_slot = static_cast<std::uint8_t*>(returned) +
                            kSampledByteFieldDisplacement;
  *byte_slot = 0x2au;
  check(pointee->byte_at_dc == 0x2au);
  check(pointee->byte_at_dd == 0x7fu);
  check(kSampledByteFieldDisplacement == 0xdcu);
  check(pointee->guard_below_dc == 0x66666666u);
  check(pointee->guard_above_dc == 0x77777777u);

  // The recorded call and callee addresses of the sampled caller, which is what
  // makes the result a receiver rather than a value.
  check(kSampledCallerFirstCallsite == 0x00d4c624u);
  check(kSampledCallerSecondCallsite == 0x00d4c635u);
  check(kSampledCalleeExecuteAction == 0x00d39360u);
  check(kSampledCalleeSecond == 0x00d3cdc0u);

  // None of those displacements sizes anything in this package: the slot is a
  // bare word and the pointee is a fixture.
  check(kSampledReaderFieldDisplacement != kSlotAddress);
  check(sizeof(SlotWord) == 4u);

  std::free(pointee);
}

// 9. The entry's literal slot read and the header's kSlotAddress name one and
// the same address.
void test_entry_literal_and_header_address_agree() {
  const SlotWord declared = kSlotAddress;
  const SlotWord from_encoding =
      static_cast<std::uint32_t>(kTargetEncoding[1]) |
      (static_cast<std::uint32_t>(kTargetEncoding[2]) << 8) |
      (static_cast<std::uint32_t>(kTargetEncoding[3]) << 16) |
      (static_cast<std::uint32_t>(kTargetEncoding[4]) << 24);

  check(declared == from_encoding);
  check(declared == 0x0169e294u);
  check(declared == 23716500u);
  check((declared % sizeof(SlotWord)) == 0u);

  // And the entry agrees with both: plant the address itself and it comes back
  // unchanged, so nothing in the path rewrites the value.
  plant(declared);
  check(pointer_word(call_entry()) == declared);
  check(stored_slot() == declared);
}

}

}

namespace {

using namespace openspore::reconstruction::pkg_00d38840_global_singleton_getter;

int run_tests() {
  model::test_return_is_the_stored_word_as_a_pointer();
  model::test_load_is_absolute_not_receiver_relative();
  model::test_body_does_not_write_the_slot();
  model::test_value_crosses_verbatim();
  model::test_abi_is_measured_not_assumed();
  model::test_encoding_matches_the_observed_bytes();
  model::test_sidecar_shape_agrees_with_the_body();
  model::test_sampled_callers_use_the_result_as_an_address();
  model::test_entry_literal_and_header_address_agree();
  return 0;
}

}

int main() { return ::run_tests(); }