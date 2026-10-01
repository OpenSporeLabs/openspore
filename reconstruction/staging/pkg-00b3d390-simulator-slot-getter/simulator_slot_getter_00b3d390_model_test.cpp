// Focused semantic test for FUN_00b3d390 @ 0x00b3d390.
//
// The target body is two instructions, so the whole content of this
// reconstruction is one question - is the returned word the VALUE stored in the
// .data slot at 0x0167eb08, or something else - plus the ABI facts a
// two-instruction body can still get wrong. Each test below names the hypothesis
// it tries to REFUTE:
//
//   1. the entry returns the slot's stored VALUE, not the slot's own ADDRESS
//      (the LEA form), not a constant it could have materialised, and not zero;
//   2. the returned word is the object POINTER the sampled callers use: it is
//      exactly the planted fixture's address, which an address-of-the-slot
//      answer could not produce. NO field offset is checked here, because no
//      sampled caller of this target reaches one - see the header's note 8;
//   3. the address is THIS slot: the two neighbouring words carry distinct
//      sentinels, neither is returned, and neither is disturbed;
//   4. the body READS and never writes - the whole window is byte-identical
//      before and after, and so is the pointee it hands back, so a
//      store-through perturbation fails on the guards even if it also returns
//      the right value;
//   5. the entry is a pure function of the slot - no caching, no lazy
//      publication check, no default, no refresh, and a published null comes
//      back as a published null;
//   6. there is NO register receiver and NO stack argument, argued from the
//      ENCODING rather than sampled at run time (see the note below);
//   7. the callee pops nothing, argued from the encoding's RET form;
//   8. the encoding IS the observed one: kTargetEncoding is the six bytes read
//      from 0x00b3d390, and its disp32 is tied by static_assert to the header's
//      kSlotVa, so the two statements cannot drift apart;
//   9. the "no static writer" claim has a structural basis: 0x0167eb08 lies
//      past .data's SizeOfRawData, so the slot is in the zero-filled tail and
//      its load-time value is zero. That is why a null-returning test above is
//      not a contrived state;
//  10. the slot-table arithmetic: this slot is word 18 of a CONTIGUOUS
//      43-word block at table offset 0x48, and the 0x48 here is a table offset
//      that must not be confused with any object offset.
//
// A NOTE ON WHY THE ABI CLAIMS ARE ENCODING ARGUMENTS AND NOT MEASUREMENTS.
// An earlier family of these tests sampled ESP around the call and re-called
// from a deeper frame, using constrained inline asm. Every version of that
// measurement was unreliable and the failures were silent: the compiler
// allocated a callee-saved register that the harness's own matching `pop` then
// overwrote, folded a variable alloca into one fixed frame so both depths were
// the same point, and allocated the register a constrained `call *%reg` was
// about to use as the operand being poisoned.
//
// For THIS body the encoding argument is strictly stronger than a sample.
// 0x00b3d390 is `a1 <disp32>`, and 0xa1 is MOV EAX, moffs32: the instruction has
// no ModRM byte, therefore no r/m operand, therefore no register operand of any
// kind - so ECX is not merely unused, it is unreadable by construction, and no
// receiver can exist. The same instruction has one memory operand and it is
// the absolute disp32, so there is no ESP-relative memory operand either: no
// stack argument is read. The trailing byte is 0xc3, RET with no imm16, so the
// callee pops nothing. Those three facts are read off six bytes of machine code
// that the package states twice, and they hold identically at every
// optimisation level and on every compiler, which is exactly the property a
// run-time sample could not offer here.

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "simulator_slot_getter_00b3d390.hpp"

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_00b3d390 model test requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00b3d390_simulator_slot_getter {
namespace model {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

std::uint32_t pointer_word(const void* pointer) {
  return static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(pointer));
}

// The slot window. The entry under test reads index kSlotIndex and nothing
// else, so the neighbours are planted with values distinguishable from every
// other candidate answer (an address, a small constant, a displacement).
constexpr std::size_t kWindowWords = 5;
constexpr std::size_t kSlotIndex = 2;
constexpr std::size_t kLeftNeighbourIndex = kSlotIndex - 1;
constexpr std::size_t kRightNeighbourIndex = kSlotIndex + 1;

static_assert(kSlotIndex > 0 && kSlotIndex + 1 < kWindowWords,
              "the slot needs a planted word on each side");

// Sentinels that cannot be confused with a plausible address, a small constant,
// or a displacement. They differ from each other so "one word too low" and "one
// word too high" are separate failures. The left sentinel is deliberately the
// value 0x0167eb04 - the neighbouring slot's own VA - so that an
// off-by-one-word answer in the SLOT TABLE's direction produces a value the
// test can name and reject rather than an anonymous miss.
constexpr std::uint32_t kLeftSentinel = 0x0167eb04u;
constexpr std::uint32_t kRightSentinel = 0x0badf00du;
constexpr std::uint32_t kFarGuard = 0x5a5a1234u;

SlotWord g_slot_window[kWindowWords];

// The fixture the slot is pointed at. Its address is the value planted in the
// slot, so the entry must hand that exact address back. The struct models NO
// extent (header note 8), so this is a single opaque byte: there is no
// observed field to plant, and inventing one would be the exact error this
// package exists to avoid.
alignas(4) OpaqueSimulatorSingleton g_fixture;

std::uint32_t slot_address() {
  return pointer_word(&g_slot_window[kSlotIndex]);
}

std::uint32_t entry_address() {
  return pointer_word(
      reinterpret_cast<const void*>(&simulator_slot_getter_00b3d390));
}

// The plain call. No arguments in or out except EAX, so the call site is
// identical under cdecl, stdcall, thiscall and fastcall - which is why no
// trampoline is needed here and why the derived ABI record abstains from naming
// a convention.
OpaqueSimulatorSingleton* call_entry() {
  return simulator_slot_getter_00b3d390();
}

// Fill the window with a non-zero pattern, then plant the pointer and the
// sentinels, so a write anywhere is visible afterwards.
void plant_window() {
  for (std::size_t index = 0; index < kWindowWords; ++index) {
    g_slot_window[index] = kFarGuard + static_cast<std::uint32_t>(index);
  }
  g_slot_window[0] = kFarGuard;
  g_slot_window[kWindowWords - 1] = kFarGuard + 0x10u;
  g_slot_window[kLeftNeighbourIndex] = kLeftSentinel;
  g_slot_window[kRightNeighbourIndex] = kRightSentinel;

  // The opaque byte is non-zero so "the pointer is the planted address" is a
  // real observation about an address rather than about an all-zero object.
  g_fixture.opaque_byte = 0xc3u;

  g_slot_window[kSlotIndex] = pointer_word(&g_fixture);
}

// 1. The return is the VALUE stored in the slot.
void test_return_is_the_stored_value() {
  plant_window();
  const std::uint32_t planted = g_slot_window[kSlotIndex];

  OpaqueSimulatorSingleton* result = call_entry();

  check(pointer_word(result) == planted);
  // Not the address of the slot: this is the load/LEA distinction, and it is
  // not hypothetical in this family - 0x00b3d220 in the same block returns a
  // table address as an immediate, and 0x00b3d230 dereferences it. A LEA-form
  // answer cannot also equal `planted`.
  check(pointer_word(result) != slot_address());
  // Not the slot's own VA as a literal, not the table base plus the table
  // offset (which is the same number), not the table offset, not zero.
  check(pointer_word(result) != kSlotVa);
  check(pointer_word(result) != kSlotTableBaseVa + kSlotTableOffset);
  check(pointer_word(result) != kSlotTableOffset);
  check(pointer_word(result) != kSlotBlockLastVa);
  check(pointer_word(result) != 0u);
  // And the value really was read out of the slot, word for word.
  check(g_slot_window[kSlotIndex] == planted);
}

// 2. The returned word is the object pointer the sampled callers use. Both
// sampled sites (0x00bf6f72 `mov ecx,eax` then a call; 0x00b5feeb `push eax`)
// hand the value on as a pointer, so pointer identity is the whole claim. No
// field offset is checked, because none is observed for this target.
void test_returned_word_is_a_pointer_to_the_planted_fixture() {
  plant_window();

  OpaqueSimulatorSingleton* result = call_entry();

  check(result == &g_fixture);
  // The fixture's single opaque byte is reachable through the returned pointer,
  // which is what "usable as a pointer" means here.
  check(result->opaque_byte == 0xc3u);
  // And the identity is exact, in both directions - not an offset, not a
  // truncated value, not a tagged one.
  check(pointer_word(result) - pointer_word(&g_fixture) == 0u);
  check(pointer_word(&g_fixture) - pointer_word(result) == 0u);
}

// 3. The address is THIS slot, not a neighbour.
void test_slot_is_exactly_0x0167eb08() {
  plant_window();

  OpaqueSimulatorSingleton* result = call_entry();

  check(pointer_word(result) == pointer_word(&g_fixture));
  check(pointer_word(result) != g_slot_window[kLeftNeighbourIndex]);
  check(pointer_word(result) != g_slot_window[kRightNeighbourIndex]);
  check(g_slot_window[kLeftNeighbourIndex] == kLeftSentinel);
  check(g_slot_window[kRightNeighbourIndex] == kRightSentinel);
  // The sentinels must not be able to masquerade as the right answer, or the
  // two neighbour checks above would be vacuous.
  check(kLeftSentinel != pointer_word(&g_fixture));
  check(kRightSentinel != pointer_word(&g_fixture));
  check(kLeftSentinel != kRightSentinel);
  // The left sentinel IS the neighbouring slot's VA, so a reconstruction that
  // read 0x0167eb04 (sibling 0x00b3d380's slot) instead of 0x0167eb08 would
  // land on exactly this value and be rejected by the checks above.
  check(kLeftSentinel == 0x0167eb04u);
  check(kSlotVa == kLeftSentinel + 4u);
  // The slot's arithmetic is the one the header states: 0x0167eac0 + 0x48.
  check(kSlotVa == kSlotTableBaseVa + kSlotTableOffset);
}

// 4. The body reads. The whole window and the pointee it hands back are
// byte-identical across the call.
void test_body_does_not_write_the_slot_window() {
  plant_window();
  SlotWord before[kWindowWords];
  std::memcpy(before, g_slot_window, sizeof(before));
  const std::uint8_t fixture_before = g_fixture.opaque_byte;

  OpaqueSimulatorSingleton* result = call_entry();
  check(result == &g_fixture);
  check(result->opaque_byte == 0xc3u);

  for (std::size_t index = 0; index < kWindowWords; ++index) {
    check(g_slot_window[index] == before[index]);
  }
  // The slot is a read view and so is the pointer it names: the entry must not
  // store through the value it returns either.
  check(g_fixture.opaque_byte == fixture_before);
}

// 5. Pure function of the slot: repeats, and tracks every change, including the
// two values a defaulting or refreshing body would mishandle.
void test_pure_function_of_the_slot() {
  plant_window();
  check(call_entry() == &g_fixture);
  check(call_entry() == &g_fixture);
  check(call_entry() == &g_fixture);

  // A published null must come back as a published null: the body has no test,
  // no branch and no default, so a reconstruction that substituted a fallback
  // for zero fails here. (And per test 9, zero is this slot's LOAD-TIME value,
  // so this is the state the entry is actually reached in before publication.)
  g_slot_window[kSlotIndex] = 0u;
  check(call_entry() == nullptr);
  check(g_slot_window[kSlotIndex] == 0u);

  // All-ones and a small odd constant are returned verbatim.
  g_slot_window[kSlotIndex] = 0xffffffffu;
  check(pointer_word(call_entry()) == 0xffffffffu);
  g_slot_window[kSlotIndex] = 0x00000011u;
  check(pointer_word(call_entry()) == 0x00000011u);

  plant_window();
  check(call_entry() == &g_fixture);
}

// 6. No register receiver and no stack argument, read off the encoding.
// 0x00b3d390 is `a1 <disp32>`: MOV EAX, moffs32. That opcode carries its
// operand in the trailing four bytes, so the instruction has no ModRM byte and
// therefore no r/m and no register operand at all - ECX cannot be read by this
// body, so no receiver can exist. Its single memory operand is the absolute
// disp32, so there is no ESP-relative operand either and no stack argument is
// read. The bytes that would change either conclusion are named, so a
// substitution of a ModRM-carrying form is caught here rather than assumed away.
void test_encoding_admits_no_receiver_and_no_stack_argument() {
  // 0xa0..0xa7 are the eight MOV moffs forms (MOV moffs8/32 to and from
  // AL/eAX/r/m). Every one of them takes its address in the four bytes that
  // follow the opcode, so none of them has a ModRM byte and none of them can
  // name a register operand. 0x00b3d390 is the moffs32-to-EAX direction, 0xa1.
  check(kTargetEncoding[0] == 0xa1u);
  // The instruction is exactly six bytes: a one-byte opcode plus a four-byte
  // disp32. There is no room for a ModRM byte AND a disp32, let alone for an
  // SIB byte or an ESP-relative displacement.
  check(kTargetBodyBytes == 1u + 4u + 1u);
  check(sizeof(kTargetEncoding) == kTargetBodyBytes);
  // And the modelled ABI type can express neither a receiver nor an argument,
  // so a reconstruction that grew one could not even be declared against it.
  static_assert(std::is_same<AbiSlotGetter00b3d390,
                             OpaqueSimulatorSingleton* (*)()>::value,
                "the modelled entry takes nothing and returns one pointer");
  check(sizeof(AbiSlotGetter00b3d390) == sizeof(void*));
  check(entry_address() != 0u);
}

// 7. The callee pops nothing. The trailing byte is RET with no imm16, so there
// is no callee-side cleanup, and with 0 ordinary stack arguments the caller's
// cleanup is 0 bytes. The byte that WOULD encode a cleanup is named, so a
// RET 0x4 answer cannot slip through as "a bare ret".
void test_bare_ret_implies_zero_callee_cleanup() {
  check(kTargetEncoding[5] == 0xc3u);
  // 0xc2 is RET imm16 and is the only other single-byte RET on x86-32; 0xc3
  // is RET with no immediate. A callee that popped n bytes would end in 0xc2
  // followed by the little-endian imm16, which is a two-byte tail this body
  // does not have.
  check(kTargetEncoding[5] != 0xc2u);
  check(sizeof(kTargetEncoding) == 6u);
}

// 8. The encoding IS the observed one, and its disp32 is the header's slot.
void test_encoding_matches_the_observed_bytes() {
  check(kTargetEncoding[0] == 0xa1u);
  check(kTargetEncoding[1] == 0x08u);
  check(kTargetEncoding[2] == 0xebu);
  check(kTargetEncoding[3] == 0x67u);
  check(kTargetEncoding[4] == 0x01u);
  check(kTargetEncoding[5] == 0xc3u);
  // The disp32 bytes, reassembled, must be the header's slot VA. This is the
  // statement that stops the encoding and the named slot from drifting apart
  // silently.
  check((static_cast<std::uint32_t>(kTargetEncoding[1]) |
         (static_cast<std::uint32_t>(kTargetEncoding[2]) << 8) |
         (static_cast<std::uint32_t>(kTargetEncoding[3]) << 16) |
         (static_cast<std::uint32_t>(kTargetEncoding[4]) << 24)) == kSlotVa);
  check(kSlotVa == 0x0167eb08u);
  check(kSlotTableBaseVa == 0x0167eac0u);
  check(kSlotTableOffset == 0x48u);
  check(kSlotVa == kSlotTableBaseVa + kSlotTableOffset);
  // The byte after the body is INT3 pad, not part of it, and is not modelled.
  check(kTargetBodyBytes == 6u);
  check(pointer_word(&g_slot_window[kSlotIndex]) == slot_address());
}

// 9. The slot is uninitialised at load, so the committed sidecar's "one reader,
// zero writers" is a property of the image and not of a search that missed
// something. Checked from the pinned PE section table's own numbers, which the
// header carries as constants.
void test_slot_lies_in_the_uninitialised_data_tail() {
  check(kDataSectionVa == 0x0110c000u);
  check(kDataSizeOfRawData == 0x000c4c00u);
  // Section offset of the slot inside .data:
  const std::uint32_t section_offset = kSlotVa - kDataSectionVa;
  check(section_offset == 0x00572b08u);
  // Past SizeOfRawData, so the file carries no initialiser for it and the
  // loader supplies zero - which is why "a published null comes back as a
  // published null" in test 5 is the entry's load-time state, not a contrivance.
  check(section_offset > kDataSizeOfRawData);
  // The whole accessor block's slot range is in the same tail.
  check((kSlotTableBaseVa - kDataSectionVa) > kDataSizeOfRawData);
  check((kSlotBlockLastVa - kDataSectionVa) > kDataSizeOfRawData);
  // And the slot is 4-byte aligned, so a 32-bit load at that address is in
  // bounds and aligned.
  check((kSlotVa & 3u) == 0u);
}

// 10. Slot-table arithmetic. This slot is table offset 0x48 = word 18 of a
// CONTIGUOUS 43-word block. The 0x48 here is a TABLE offset and is named as
// such so it cannot be silently promoted into an object field offset (which is
// exactly the trap the header's note 8 warns about).
void test_slot_table_arithmetic() {
  check(kSlotTableOffset == 0x48u);
  check(kSlotTableOffset == 72u);
  check(kSlotVa - kSlotTableBaseVa == kSlotTableOffset);
  check(kSlotBlockLastVa == 0x0167eb68u);
  check(kSlotBlockLastVa - kSlotTableBaseVa == 168u);
  check(kSlotBlockSpanBytes == 168u);
  check(kSlotBlockAccessorCount == 43u);
  // Contiguous: 43 four-byte words fill 168 bytes plus the final step, so the
  // bijection from accessor to slot leaves no gap and no duplicate.
  check(kSlotBlockAccessorCount * 4u == kSlotBlockSpanBytes + 4u);
  check(kSlotBlockWordIndex == 18u);
  check(kSlotTableOffset / 4u == kSlotBlockWordIndex);
  // 18 words in, so 19th word counting from one, and 24 words remain after it.
  check(kSlotBlockAccessorCount - kSlotBlockWordIndex == 25u);
  check(kSlotTableBaseVa <= kSlotVa);
  check(kSlotVa < kSlotBlockLastVa);
  // This slot is not either immediate table neighbour - the neighbours belong
  // to 0x00b3d380 (unnamed) and 0x00b3d3a0 (Simulator::cStarManager::Get), and
  // adjacency carries no identity.
  check(kSlotVa - 4u == 0x0167eb04u);
  check(kSlotVa + 4u == 0x0167eb0cu);
}

}

// The published slot word. The real image supplies the uninitialised .data word
// at 0x0167eb08; here the model supplies its own definition, bound to a window
// the tests can plant neighbours and guard bands into.
extern "C" {
SlotWord& DAT_0167eb08 = model::g_slot_window[model::kSlotIndex];
}

}

namespace {

using namespace openspore::reconstruction::pkg_00b3d390_simulator_slot_getter;
using model::call_entry;
using model::check;
using model::entry_address;
using model::g_fixture;
using model::g_slot_window;
using model::kFarGuard;
using model::kLeftSentinel;
using model::kRightSentinel;
using model::kWindowWords;
using model::plant_window;
using model::pointer_word;
using model::slot_address;

int run_tests() {
  model::test_return_is_the_stored_value();
  model::test_returned_word_is_a_pointer_to_the_planted_fixture();
  model::test_slot_is_exactly_0x0167eb08();
  model::test_body_does_not_write_the_slot_window();
  model::test_pure_function_of_the_slot();
  model::test_encoding_admits_no_receiver_and_no_stack_argument();
  model::test_bare_ret_implies_zero_callee_cleanup();
  model::test_encoding_matches_the_observed_bytes();
  model::test_slot_lies_in_the_uninitialised_data_tail();
  model::test_slot_table_arithmetic();
  return 0;
}

int run_all() { return ::run_tests(); }
}

int main() { return ::run_all(); }
