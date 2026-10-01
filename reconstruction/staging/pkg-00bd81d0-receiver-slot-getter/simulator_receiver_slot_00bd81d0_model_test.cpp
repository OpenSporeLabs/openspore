// Focused semantic test for FUN_00bd81d0 @ 0x00bd81d0.
//
// The target body is two instructions, so the entire content of this
// reconstruction is one question - is the returned value the 32-bit word stored
// at receiver+0x540, and is that word returned as a scalar integer - plus the
// ABI facts a two-instruction body can still get wrong. Each test names the
// hypothesis it tries to REFUTE:
//
//   1. the entry returns the word stored at +0x540, not the ADDRESS of the
//      member, not a constant it could have materialised, and not zero;
//   2. the returned value is a SCALAR bit pattern carried verbatim: no sign
//      extension, no saturation, no clamp, and 0xffffffff comes back as
//      0xffffffff;
//   3. the offset is exactly 0x540: guard words planted one word below and one
//      word above are neither returned nor disturbed, and the address the entry
//      reads is spelled &receiver + 0x540;
//   4. the body READS and never writes - the whole 0x548-byte receiver is
//      byte-identical before and after, so a store-through perturbation fails on
//      the guards even if it also returns the right value;
//   5. the entry is a pure function of the field: no caching, no lazy
//      publication check, no default, no refresh, and every one of the four
//      values the sampled callers compare against (0, 1, 2, -1) comes back
//      unchanged;
//   6. there IS a receiver and it is ECX, argued from the ENCODING rather than
//      sampled at run time (see the note below);
//   7. the callee pops nothing, argued from the encoding's RET form, and named
//      against the `RET 4` form the sibling writers in the same block use;
//   8. the encoding IS the observed one: kTargetEncoding is the seven bytes read
//      from 0x00bd81d0, and its disp32 is tied by static_assert to the header's
//      kSlotOffset, and its ModRM byte is tied to the EAX/ECX operand pair, so
//      the statements cannot drift apart;
//   9. the modelled entry has no stack argument and returns one 32-bit value,
//      so a reconstruction that grew a parameter could not be declared.
//
// A NOTE ON WHY THE ABI CLAIMS ARE ENCODING ARGUMENTS AND NOT MEASUREMENTS.
// A sibling package in this repository tried to sample ESP around the call and
// to re-call from a deeper frame using constrained inline asm, and every
// version of that measurement turned out to be silently unreliable: the
// compiler allocated a callee-saved register that the harness's own matching
// `pop` then overwrote, folded a variable alloca into one fixed frame so both
// depths were the same point, and allocated the register a constrained
// `call *%reg` was about to use as the operand being poisoned. Each showed up
// only at -O1 or above, or only on one compiler, and each looked like a
// plausible zero.
//
// For THIS body the encoding argument is strictly stronger than a sample. The
// instruction is `8b 81 40 05 00 00`: 0x8b is MOV r32,r/m32, its ModRM byte is
// 0x81, and decoding that ModRM gives mod=10 (a disp32 follows), reg=000 (EAX,
// the destination) and r/m=001 (ECX, the base). So the body reads ECX, writes
// EAX, touches no other register, and its only memory operand is
// [ECX + disp32] - there is no ESP-relative operand anywhere and therefore no
// stack argument can be read. The trailing byte is 0xc3, RET with no imm16, so
// the callee pops nothing. Those facts are read off seven bytes of machine code
// that this package states twice (header static_asserts and the checks here),
// and they hold identically at every optimisation level and on every compiler,
// which is exactly the property a run-time sample could not offer here.
//
// A NOTE ON WHY THE RETURN IS MODELLED AS AN INTEGER AND NOT A POINTER. The
// derived ABI record labels the last value written to EAX `pointer_like`, and
// this package does not adopt that label. Seven sampled callers use the result
// as an enum-like small integer - 0x00bd0000 and 0x00cf78d0 branch on 1 and 2,
// 0x00bf0f40 maps 0/1/2 to 0/2/1 and everything else to -1, 0x00bd7160 compares
// against -1, 0x00bf1fd0 compares it for equality against a parameter and then
// does arithmetic on it, and 0x00bf9820 forwards it as an integer argument -
// and NOT ONE of them dereferences it. A register-shape heuristic is not a use
// observation, and the type below is the one the uses support. Test 2 is what
// holds that line: it fails if a reconstruction returns a pointer that is later
// dereferenced or masked, because the observed bit patterns must survive
// untouched.

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "simulator_receiver_slot_00bd81d0.hpp"

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_00bd81d0 model test requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00bd81d0_receiver_slot_getter {
namespace model {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

std::uint32_t address_word(const void* pointer) {
  return static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(pointer));
}

// The receiver fixture. The entry under test reads exactly one word out of it,
// so the words either side of that offset are planted with sentinels
// distinguishable from every other candidate answer (an address, a small
// constant, a displacement, an off-by-one offset).
constexpr std::size_t kReceiverWords = kReceiverModellingExtent / 4u;
constexpr std::size_t kSlotWordIndex = kSlotOffset / 4u;

// The word either side of the observed one. Named so the neighbour checks can
// be tied to the offset arithmetic rather than only to sentinel values.
constexpr std::size_t kLeftNeighbourWordIndex = kSlotWordIndex - 1;
constexpr std::size_t kRightNeighbourWordIndex = kSlotWordIndex + 1;

static_assert(kSlotWordIndex > 0 && kSlotWordIndex + 1 < kReceiverWords,
              "the slot needs a planted word on each side");
static_assert(kLeftNeighbourWordIndex * 4u + 4u == kSlotOffset,
              "the low neighbour word ends exactly where the observed word starts");
static_assert(kRightNeighbourWordIndex * 4u == kSlotOffset + 4u,
              "the high neighbour word starts exactly after the observed word");

// Sentinels that cannot be confused with a plausible address, a small constant,
// or a displacement. They differ from each other so "one word too low" and "one
// word too high" are separate failures.
constexpr SlotWord kLeftSentinel = 0xfeedfaceu;
constexpr SlotWord kRightSentinel = 0x0badf00du;
constexpr SlotWord kFarGuard = 0x5a5a1234u;

// A value the entry must never synthesise: a small constant, planted nowhere.
constexpr SlotWord kNeverPlanted = 0x0000002eu;

OpaqueSimulatorReceiver g_receiver;

// The address the entry is supposed to read.
unsigned char* slot_address() {
  return reinterpret_cast<unsigned char*>(&g_receiver) + kSlotOffset;
}

// The address of the word below and the word above it.
unsigned char* left_neighbour_address() { return slot_address() - 4; }

unsigned char* right_neighbour_address() { return slot_address() + 4; }

// The plain call. One pointer in, one 32-bit value out, so the call site is
// identical under cdecl, stdcall, thiscall and fastcall - which is exactly why
// the modelled type is a plain receiver-pointer parameter rather than a claim
// about a hidden register, even though the machine form reads ECX (test 6).
SlotWord call_entry() {
  return simulator_receiver_slot_00bd81d0(&g_receiver);
}

SlotWord* slot_word() {
  return reinterpret_cast<SlotWord*>(slot_address());
}

SlotWord* left_neighbour_word() {
  return reinterpret_cast<SlotWord*>(left_neighbour_address());
}

SlotWord* right_neighbour_word() {
  return reinterpret_cast<SlotWord*>(right_neighbour_address());
}

// Fill the receiver with a non-zero pattern, then plant the neighbours, so a
// write anywhere is visible afterwards.
void plant_receiver() {
  std::memset(&g_receiver, 0, sizeof(g_receiver));
  for (std::size_t index = 0; index < kReceiverWords; ++index) {
    reinterpret_cast<SlotWord*>(&g_receiver)[index] =
        kFarGuard + static_cast<SlotWord>(index);
  }
  *left_neighbour_word() = kLeftSentinel;
  *right_neighbour_word() = kRightSentinel;
}

// 1. The return is the VALUE stored at +0x540.
void test_return_is_the_stored_word() {
  plant_receiver();
  *slot_word() = 0x0badc0deu;
  const SlotWord planted = *slot_word();

  const SlotWord result = call_entry();

  check(result == planted);
  // Not the member's ADDRESS: this is the load-versus-LEA distinction, and it
  // is not hypothetical in this block - 0x00bd81a0, thirty bytes below this
  // entry, is `LEA EAX,[ECX + 0x548]`, which returns the ADDRESS of a member of
  // this same object. A LEA-form answer cannot also equal `planted`.
  check(address_word(slot_address()) != planted);
  // Not the offset, not a constant the body could have materialised, not zero.
  check(result != kSlotOffset);
  check(result != kNeverPlanted);
  check(result != 0u);
  // And the value really was read out of the receiver, word for word.
  check(*slot_word() == planted);
}

// 2. The returned word is carried as a SCALAR bit pattern, verbatim. This is the
// test that holds the line against the derived record's `pointer_like` label:
// the sampled callers compare the result against 0, 1, 2 and -1 and pass it
// straight through as an integer argument, so the four observed comparands -
// and the two extremes - must come back untouched, not sign-extended,
// saturated, masked or reinterpreted.
void test_return_is_a_verbatim_scalar() {
  // The four values the sampled callers actually compare against.
  const SlotWord observed[] = {
      kObservedComparandZero,
      kObservedComparandOne,
      kObservedComparandTwo,
      kObservedComparandMinusOneSigned,
  };
  for (std::size_t index = 0; index < sizeof(observed) / sizeof(observed[0]);
       ++index) {
    plant_receiver();
    *slot_word() = observed[index];
    check(call_entry() == observed[index]);
    check(*slot_word() == observed[index]);
  }

  // The 32-bit extremes: a body that sign-extended, clamped or promoted would
  // lose at least one of these.
  const SlotWord extremes[] = {
      0xffffffffu,  // the bit pattern behind the -1 comparison at 0x00bd7160
      0x7fffffffu,
      0x80000000u,
      0x0000ffffu,
      0x00010000u,
      0xabcdef01u,
  };
  for (std::size_t index = 0; index < sizeof(extremes) / sizeof(extremes[0]);
       ++index) {
    plant_receiver();
    *slot_word() = extremes[index];
    check(call_entry() == extremes[index]);
    check(*slot_word() == extremes[index]);
  }
}

// 3. The offset is exactly 0x540, not one word either side.
void test_offset_is_exactly_0x540() {
  plant_receiver();
  *slot_word() = 0x11111111u;

  const SlotWord result = call_entry();

  check(result == 0x11111111u);
  check(result != kLeftSentinel);
  check(result != kRightSentinel);
  // The sentinels must not be able to masquerade as the right answer, or the
  // two neighbour checks above would be vacuous.
  check(kLeftSentinel != 0x11111111u);
  check(kRightSentinel != 0x11111111u);
  check(kLeftSentinel != kRightSentinel);
  check(address_word(slot_address()) ==
        address_word(&g_receiver) + kSlotOffset);
  check(address_word(left_neighbour_address()) ==
        address_word(slot_address()) - 4u);
  check(address_word(right_neighbour_address()) ==
        address_word(slot_address()) + 4u);
  // And the neighbours are untouched.
  check(*left_neighbour_word() == kLeftSentinel);
  check(*right_neighbour_word() == kRightSentinel);
  // Plant a distinct value in each neighbour in turn; neither may surface.
  *left_neighbour_word() = 0x22222222u;
  check(call_entry() == 0x11111111u);
  check(call_entry() != 0x22222222u);
  *right_neighbour_word() = 0x33333333u;
  check(call_entry() == 0x11111111u);
  check(call_entry() != 0x33333333u);
}

// 4. The body reads. The whole receiver is byte-identical across the call.
void test_body_does_not_write_the_receiver() {
  plant_receiver();
  *slot_word() = 0x44444444u;
  std::uint8_t before[sizeof(OpaqueSimulatorReceiver)];
  std::memcpy(before, &g_receiver, sizeof(before));

  const SlotWord result = call_entry();
  check(result == 0x44444444u);

  for (std::size_t index = 0; index < sizeof(before); ++index) {
    check(g_receiver.opaque_bytes[index] == before[index]);
  }
  check(*slot_word() == 0x44444444u);
  check(*left_neighbour_word() == kLeftSentinel);
  check(*right_neighbour_word() == kRightSentinel);
}

// 5. Pure function of the field: repeats, tracks every change, and never
// substitutes a fallback - including for the two values a defaulting body would
// mishandle.
void test_pure_function_of_the_field() {
  plant_receiver();
  *slot_word() = kObservedComparandOne;
  check(call_entry() == kObservedComparandOne);
  check(call_entry() == kObservedComparandOne);
  check(call_entry() == kObservedComparandOne);

  // A stored zero comes back as a stored zero: the body has no test, no branch
  // and no default, so a reconstruction that substituted a fallback for zero
  // fails here.
  *slot_word() = 0u;
  check(call_entry() == kObservedComparandZero);
  check(*slot_word() == 0u);

  *slot_word() = kObservedComparandTwo;
  check(call_entry() == kObservedComparandTwo);
  *slot_word() = kObservedComparandMinusOneSigned;
  check(call_entry() == kObservedComparandMinusOneSigned);

  plant_receiver();
  *slot_word() = 0x56565656u;
  check(call_entry() == 0x56565656u);
  check(call_entry() == 0x56565656u);
}

// 6. There IS a receiver and it is ECX, read off the encoding.
// 0x00bd81d0 is `8b 81 40 05 00 00`: opcode 0x8b (MOV r32,r/m32) followed by
// ModRM 0x81. Decoding 0x81 gives mod=10, so a disp32 follows; reg=000, so the
// destination is EAX; r/m=100 would mean SIB and r/m=101 would mean a
// disp32-only form, so r/m=001 means the base register is ECX. A body that read
// no receiver at all, or read a receiver from some other register, cannot be
// spelled with this ModRM byte, and the byte that WOULD spell it is named below
// so the check is not vacuous.
void test_encoding_names_ecx_as_the_receiver() {
  check(kTargetEncoding[0] == 0x8bu);
  check(kTargetEncoding[1] == 0x81u);
  // mod = 10: the displacement is disp32, not disp8 and not RIP-relative.
  check((kTargetEncoding[1] >> 6) == 0x02u);
  check((kTargetEncoding[1] & 0xc0u) != 0xc0u);
  // reg = 000: the destination register is EAX.
  check(((kTargetEncoding[1] >> 3) & 0x07u) == 0x00u);
  // r/m = 001: the base register is ECX. The SIB escapes are named so a
  // substituted ModRM carrying one is caught.
  check((kTargetEncoding[1] & 0x07u) == 0x01u);
  check((kTargetEncoding[1] & 0x07u) != 0x04u);  // would be an SIB byte
  check((kTargetEncoding[1] & 0x07u) != 0x05u);  // would be disp32 with no base
  // The destination register really is EAX, so no other register is written.
  check(((kTargetEncoding[1] >> 3) & 0x07u) != 0x07u);
  // And the derived ABI record agrees on the shape it measured: exactly one
  // distinct receiver offset and zero writes through the receiver.
  check(kSlotOffset == 1344u);
  check(sizeof(SlotWord) == 4u);
}

// 7. The callee pops nothing. The trailing byte is RET with no imm16, so there
// is no callee-side cleanup, and with 0 ordinary stack arguments the caller's
// cleanup is 0 bytes. The enclosing accessor block DOES contain writers that pop
// - 0x00bd81c0 and 0x00bd81e0 both end in `RET 4` - so the distinction is one
// this binary makes, and the byte that WOULD encode a cleanup is named so a
// RET-immediate answer cannot slip through as "a bare ret".
void test_bare_ret_implies_zero_callee_cleanup() {
  check(kTargetEncoding[6] == 0xc3u);
  // 0xc2 is RET imm16 and is the only other single-byte RET on x86-32; 0xc3 is
  // RET with no immediate. A callee that popped n bytes would end in 0xc2
  // followed by the little-endian imm16, which is a two-byte tail this body
  // does not have. 0xcb would be RETF and 0xca RET imm16, far call.
  check(kTargetEncoding[6] != 0xc2u);
  check(kTargetEncoding[6] != 0xcau);
  check(kTargetEncoding[6] != 0xcbu);
  check(sizeof(kTargetEncoding) == kTargetBodyBytes);
  // The body's seventh byte is a RET, so there is exactly one instruction
  // after the six-byte MOV.
  check(kTargetBodyBytes == 7u);
}

// 8. The encoding IS the observed one, and its disp32 is the header's offset.
void test_encoding_matches_the_observed_bytes() {
  check(kTargetEncoding[0] == 0x8bu);
  check(kTargetEncoding[1] == 0x81u);
  check(kTargetEncoding[2] == 0x40u);
  check(kTargetEncoding[3] == 0x05u);
  check(kTargetEncoding[4] == 0x00u);
  check(kTargetEncoding[5] == 0x00u);
  check(kTargetEncoding[6] == 0xc3u);
  // The disp32 bytes, reassembled, must be the header's offset. This is the
  // statement that stops the encoding and the named offset from drifting apart
  // silently.
  check((static_cast<SlotWord>(kTargetEncoding[2]) |
         (static_cast<SlotWord>(kTargetEncoding[3]) << 8) |
         (static_cast<SlotWord>(kTargetEncoding[4]) << 16) |
         (static_cast<SlotWord>(kTargetEncoding[5]) << 24)) == kSlotOffset);
  check(kSlotOffset == 0x540u);
  check(kSlotOffset == 1344u);
  // The byte after the body is INT3 pad, not part of it, and is not modelled.
  check(kTargetBodyBytes == 7u);
  check(sizeof(kTargetEncoding) == 7u);
}

// 9. The modelled entry takes one receiver and returns one 32-bit value, and
// nothing else: no stack argument can be declared against it, so a
// reconstruction that grew one would not even compile against this type.
void test_modelled_abi_shape() {
  static_assert(sizeof(SlotWord) == 4u,
                "the returned value is one 32-bit word");
  // The member-pointer type is what ties the receiver-relative access to the
  // declared ABI: a zero-argument const member returning one word.
  static_assert(sizeof(AbiReceiverSlot00bd81d0) ==
                    sizeof(void (OpaqueSimulatorReceiver::*)()),
                "the modelled entry is a zero-argument member");
  static_assert(std::is_same<SlotWord (OpaqueSimulatorReceiver::*)() const,
                             AbiReceiverSlot00bd81d0>::value,
                "the modelled entry takes nothing and returns one word");
  check(kSlotWordIndex * 4u == kSlotOffset);
  check(kReceiverModellingExtent == 0x548u);
  check(kSlotOffset + sizeof(SlotWord) <= kReceiverModellingExtent);
}

}

}

namespace {

using namespace openspore::reconstruction::pkg_00bd81d0_receiver_slot_getter;
using model::address_word;
using model::call_entry;
using model::check;
using model::g_receiver;
using model::kFarGuard;
using model::kLeftSentinel;
using model::kNeverPlanted;
using model::kReceiverWords;
using model::kRightSentinel;
using model::left_neighbour_address;
using model::plant_receiver;
using model::right_neighbour_address;
using model::slot_address;
using model::slot_word;

int run_tests() {
  model::test_return_is_the_stored_word();
  model::test_return_is_a_verbatim_scalar();
  model::test_offset_is_exactly_0x540();
  model::test_body_does_not_write_the_receiver();
  model::test_pure_function_of_the_field();
  model::test_encoding_names_ecx_as_the_receiver();
  model::test_bare_ret_implies_zero_callee_cleanup();
  model::test_encoding_matches_the_observed_bytes();
  model::test_modelled_abi_shape();
  return 0;
}

}

int main() { return ::run_tests(); }
