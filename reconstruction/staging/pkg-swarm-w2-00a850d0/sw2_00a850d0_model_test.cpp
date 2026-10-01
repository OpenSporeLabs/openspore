// PKG-SWARM-W2-00A850D0 -- VA 0x00a850d0
// Behavioural model test for FUN_00a850d0 @ 0x00a850d0.
//
// The body has NO DIRECT CALLEE. All four of its transfers are register indirect
// (`CALL EDX` at 00a850fc, 00a8512e, 00a8515a and 00a851b0), so the observers ARE
// the slot targets. Every word the model can possibly fetch is planted with the
// address of an observer, and every observer logs which slot it was, which object
// it was handed as its register argument, what its two stack arguments were, and
// what the receiver's own bytes held at the instant it was entered. The test
// therefore sees every transfer, with which argument, in which order, and decides
// what each callee leaves in EAX.
//
// WHAT IS ASSERTED, and it is only what the 81-instruction listing fixes:
//
//   * the guard byte at receiver displacement 0x14 is tested against ZERO, not
//     against one, and a non-zero value returns without a single write;
//   * the guard byte is raised to one before the null test, so a null dispatch
//     object still leaves the receiver guarded;
//   * the null dispatch object skips every transfer AND leaves receiver
//     displacement 0x68 untouched, because the store of all ones is at 00a85133,
//     past the branch;
//   * which single flag bit produces which transfer, and that the other three bit
//     positions (0, 3, 5, 7) produce nothing at all;
//   * the four slot displacements 0x18, 0x1c, 0x0c and 0x10, and that every
//     neighbouring slot of the real table is a decoy that must never be called;
//   * that the register argument of all four transfers is the object at receiver
//     displacement 0x10, and never the receiver, never the carrier, never the
//     carrier's flag word and never the table;
//   * the argument ORDER, which is the reverse of the push order: the halfword
//     from carrier displacement 0xa8 is the FIRST stack argument of the 0x1c call,
//     the receiver's own address at displacement 0x28 (or a literal zero) is its
//     second, and the carrier's words at 0xa0 and 0xa4 are the first and second
//     stack arguments of the 0x0c and 0x10 calls respectively;
//   * that the carrier's word at displacement 0xa8 is read as a SIXTEEN bit value;
//   * the DIVSS operand order: the .rdata word is the dividend, so the value
//     stored at receiver displacement 0x18 is unit/scale;
//   * that the value RETURNED is the carrier's float and not its reciprocal;
//   * the COMISS polarity at both 00a85174 and 00a85198, including the UNORDERED
//     case, so a NaN takes the branch in both places;
//   * that the .rdata words are READS, not baked-in constants, by overwriting both
//     of them and observing the outcome change;
//   * the SIGNED comparison at 00a851b7, by driving both halves of the 32-bit
//     range including 0x7fffffff and 0x80000000;
//   * the WRITE ORDERING, by having each observer read the receiver at the moment
//     it is entered: all ones at displacement 0x68 precedes the 0x0c and 0x10
//     transfers and the result store follows the 0x10 transfer;
//   * THAT THE RECEIVER'S WORD AT 0x0c IS READ FOUR TIMES. This is the case the
//     package is built around: each observer is given the power to replace the
//     receiver's word at displacement 0x0c, the test installs a second carrier
//     from inside the 0x18 callee and a third from inside the 0x10 callee, and
//     every later flag word, halfword, stack argument, guard float and the final
//     reciprocal must come from the carrier that was installed last. A model that
//     reads the pointer once produces a different, shorter call sequence.
//   * THAT THE RECEIVER'S WORD AT 0x10 IS READ FOUR TIMES TOO, by installing a
//     second dispatch object from inside a callee and requiring the later
//     transfers to go through the replacement's table.
//   * that nothing on the carrier or on the dispatch object is written, by
//     comparing both byte for byte;
//   * that the single popped stack word is never read, by running a whole case
//     with three different values for it, including a pointer to a poisoned block;
//   * an exhaustive sweep of the low nibble of the flag word against a sequence
//     predicted from the four bit tests and the two comparisons.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction, not to walk
// it. Each names the wrong reconstruction it is aimed at:
//
//   A  wrong receiver / wrong pointer level: decoy tables are planted on the
//      receiver itself, on the dispatch object, on the carrier and at the table's
//      own lead word, each carrying a live decoy observer in EVERY slot, so a
//      model that used any of the wrong objects would CALL something rather than
//      crash, and the decoy counter would catch it.
//   B  wrong slot displacement: every slot of the real table other than the four
//      the machine fetches carries a decoy, so an off-by-one-slot read of 0x14,
//      0x20, 0x08 or 0x04 is a call the test can see.
//   C  wrong bit index: the flag word is driven one bit at a time for all eight
//      positions, so shifting by one in either direction is caught.
//   D  wrong branch polarity: each of the three conditional arms is driven both
//      ways, and COMISS is driven with +0.0f, -0.0f, a negative, a NaN, a
//      denormal, a finite positive and +infinity.
//   E  signed against unsigned at 00a851b7: 0x00000000, 0x00000001, 0x7fffffff,
//      0x40000000, 0x80000000 and 0xffffffff.
//   F  wrong argument order and wrong width: the two pushed values are given
//      distinct patterns, and the carrier's word at displacement 0xa8 is poisoned
//      in its high half so a dword read is distinguishable from a halfword read.
//   G  wrong DIVSS operand order: the scale is driven to four, so unit/scale and
//      scale/unit differ by a factor of sixteen, and the RETURN value is checked
//      against the scale so a model that returned the reciprocal fails.
//   H  wrong write ordering, and the 00a85133 placement: the observers read the
//      receiver at the moment they are entered.
//   I  the four separate reads of receiver displacement 0x0c, and the four
//      separate reads of receiver displacement 0x10.
//   J  a hard-coded .rdata value: both words are overwritten by the test and the
//      outcome must follow.
//
// WHAT IS NOT ASSERTED, AND WHY:
//
//   * What the four callees DO. Their memory effects are test fixtures, not
//     claims; the only thing the body takes from a callee is the EAX of the 0x10
//     site, and the test drives that directly.
//   * Whether the four table words are VTABLE SLOTS or plain callback words. The
//     listing fixes that they are four-byte words at four displacements of a
//     table reached through the dispatch object's lead dword. It does not fix who
//     owns that table, and the same instructions would be produced by a callback
//     array. The test pins the addresses, the order and the argument order, and
//     says nothing about the classification.
//   * The stack-argument cleanup. The body never adjusts ESP after the three
//     two-argument transfers, so callee-owned cleanup is an INFERENCE from an
//     absence; this model implements it, and no case here could refute a
//     caller-cleanup reading because the body would then be self-inconsistent.
//   * Whether the real callees preserve EAX or XMM0. Nothing in this body can
//     show that. In particular the value XMM0 carries out of the 00a851b7
//     early-return path is the pre-call value UNLESS the transfer at 00a851b0
//     overwrote it, and on x86-32 that is the callee's signature, which this
//     listing does not show. The test asserts the pre-call value -- which is what
//     this reconstruction claims -- and the clobber case is named in the sidecar
//     as an open question rather than asserted either way.
//   * Any C++ type, class name or SDK symbol for the receiver, the carrier, the
//     dispatch object or the table. Nothing in this package names them, so the
//     model spells them as opaque byte runs and the test never asserts what they
//     are.
//   * That the single popped stack word is a pointer, an integer or anything
//     else. It is declared, never named, and case K requires only that the body
//     not read it.

#include "sw2_00a850d0_types.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <limits>

namespace openspore::reconstruction::pkg_swarm_w2_00a850d0 {
namespace {

// The listing's displacements, restated here as literals so that a mutation of
// either file is caught by the other. Same values as the header's constants.
constexpr std::size_t kRecvCarrier = 0x0cu;
constexpr std::size_t kRecvDispatch = 0x10u;
constexpr std::size_t kRecvFlag = 0x14u;
constexpr std::size_t kRecvScaleResult = 0x18u;
constexpr std::size_t kRecvZero1 = 0x1cu;
constexpr std::size_t kRecvZero2 = 0x20u;
constexpr std::size_t kRecvAddressArg = 0x28u;
constexpr std::size_t kRecvResult = 0x68u;
constexpr std::size_t kCarFlags = 0x08u;
constexpr std::size_t kCarScale = 0x10u;
constexpr std::size_t kCarArg0 = 0xa0u;
constexpr std::size_t kCarArg1 = 0xa4u;
constexpr std::size_t kCarHalf = 0xa8u;
constexpr std::size_t kReceiverExtent = 0x6cu;
constexpr std::size_t kCarrierExtent = 0xaau;

static_assert(kReceiverCarrierPointer == kRecvCarrier, "00a850e9");
static_assert(kReceiverDispatchPointer == kRecvDispatch, "00a850dd");
static_assert(kReceiverFlagByte == kRecvFlag, "00a850d3");
static_assert(kReceiverScaleResult == kRecvScaleResult, "00a85182");
static_assert(kReceiverFirstZeroFloat == kRecvZero1, "00a85162");
static_assert(kReceiverSecondZeroFloat == kRecvZero2, "00a85167");
static_assert(kReceiverAddressArgument == kRecvAddressArg, "00a85125");
static_assert(kReceiverResultWord == kRecvResult, "00a85133");
static_assert(kCarrierFlagWord == kCarFlags, "00a850ec");
static_assert(kCarrierScale == kCarScale, "00a8516c");
static_assert(kCarrierFirstStackArgument == kCarArg0, "00a8514f");
static_assert(kCarrierSecondStackArgument == kCarArg1, "00a85144");
static_assert(kCarrierHalfWord == kCarHalf, "00a8510e");
static_assert(kReceiverExtent == sizeof(Receiver), "the dword store at 0x68");
static_assert(kCarrierExtent == sizeof(Carrier), "the 16-bit read at 0xa8");
static_assert(kSlotBit2 == 0x18u, "00a850f9");
static_assert(kSlotBit4 == 0x1cu, "00a85120");
static_assert(kSlotBit1Set == 0x0cu, "00a85155");
static_assert(kSlotBit1Clear == 0x10u, "00a851ab");
static_assert(kResultInitialValue == 0xffffffffu, "00a85133");
static_assert(kBitIndexBit1 == 1u && kBitIndexBit2 == 2u && kBitIndexBit4 == 4u &&
                  kBitIndexBit6 == 6u,
              "the four shift immediates");

// -- the fixture --------------------------------------------------------------
// One contiguous block, so a stray read cannot wander into a neighbouring
// object's bytes and quietly look plausible. A decoy table is planted at every
// wrong level, so a wrong base CALLS a decoy instead of reading garbage.
struct Fixture {
  alignas(4) std::array<std::uint8_t, kReceiverExtent> receiver{};
  alignas(4) std::array<std::uint8_t, kCarrierExtent> carrier{};
  alignas(4) std::array<std::uint8_t, kCarrierExtent> carrier_alt{};
  alignas(4) std::array<std::uint8_t, kCarrierExtent> carrier_third{};
  alignas(4) std::array<std::uint8_t, 0x40> dispatch{};
  alignas(4) std::array<std::uint8_t, 0x40> dispatch_alt{};
  alignas(4) std::array<std::uint8_t, 0x30> table{};
  alignas(4) std::array<std::uint8_t, 0x30> table_alt{};
  alignas(4) std::array<std::uint8_t, 0x30> decoy_table{};
};

Fixture g_fixture;

// Distinct carrier payloads, so "which carrier did that read use" is decidable.
constexpr Word kCarrierOneFlags = 0x00000004u;    // bit 2 only
constexpr Word kCarrierAltFlags = 0x00000050u;    // bit 4 and bit 6
constexpr Word kCarrierThirdFlags = 0x00000000u;  // nothing
constexpr Float kCarrierOneScale = 8.0f;
constexpr Float kCarrierAltScale = 4.0f;
constexpr Float kCarrierThirdScale = 2.0f;
constexpr Word kCarrierOneArg0 = 0x11111111u;
constexpr Word kCarrierOneArg1 = 0x11111112u;
constexpr Word kCarrierOneHalf = 0x00001111u;
constexpr Word kCarrierAltArg0 = 0x22222222u;
constexpr Word kCarrierAltArg1 = 0x22222223u;
constexpr Word kCarrierAltHalf = 0x00002222u;
constexpr Word kCarrierThirdArg0 = 0x33333333u;
constexpr Word kCarrierThirdArg1 = 0x33333334u;
constexpr Word kCarrierThirdHalf = 0x00004444u;
// The high half of the carrier's word at displacement 0xa8 is poisoned so that a
// dword read there is distinguishable from the halfword read the machine makes.
constexpr Word kHalfHighPoison = 0xdead0000u;

// The value every receiver word the body does not read starts at. It is also the
// value the observers require to still be present at the receiver words the body
// writes only later, which is what makes the write ordering decidable.
constexpr Word kGuardPoison = 0xa5a5a5a5u;
constexpr std::uint8_t kGuardPoisonByte = 0xa5u;
constexpr Word kSentinel = 0xdeadbeefu;

// -- the log ------------------------------------------------------------------
constexpr int kMaxCalls = 32;
constexpr int kSlotDecoy = -1;

struct CallRecord {
  int slot;          // the slot displacement, or kSlotDecoy
  Word receiver;     // the object handed in the register argument
  Word first;        // the first stack argument
  Word second;       // the second stack argument
  Word result_at_68; // receiver displacement 0x68, sampled on entry
  Word scale_at_18;  // receiver displacement 0x18, sampled on entry
  Word zero_at_1c;
  Word zero_at_20;
  Word flag_at_14;
  Word xmm0;         // XMM0, sampled on entry
};

std::array<CallRecord, kMaxCalls> g_calls{};
int g_call_count = 0;
int g_decoy_count = 0;

// Mid-run writes. The body offers no other opportunity to be caught reading a
// cached value, so the test manufactures one: each armed slot names a callee site
// and a value to write into the receiver at the moment that callee is entered. A
// null pointer means disarmed.
const void* g_replace_carrier_after_18 = nullptr;
const void* g_replace_carrier_after_10 = nullptr;
const void* g_replace_dispatch_after_18 = nullptr;
const void* g_replace_dispatch_after_1c = nullptr;

std::uint8_t* g_receiver_bytes = nullptr;

// What the 0x10 observer leaves in EAX. The body is the only thing that reads it.
Word g_return_from_site10 = 0u;

void set_word(std::uint8_t* base, std::size_t offset, Word value) {
  std::memcpy(base + offset, &value, sizeof(value));
}

Word get_word(const std::uint8_t* base, std::size_t offset) {
  Word value = 0;
  std::memcpy(&value, base + offset, sizeof(value));
  return value;
}

void set_float(std::uint8_t* base, std::size_t offset, Float value) {
  std::memcpy(base + offset, &value, sizeof(value));
}

Float get_float(const std::uint8_t* base, std::size_t offset) {
  Float value = 0.0f;
  std::memcpy(&value, base + offset, sizeof(value));
  return value;
}

void set_byte(std::uint8_t* base, std::size_t offset, std::uint8_t value) {
  base[offset] = value;
}

Word address_of(const void* base, std::size_t offset) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(base) + offset);
}

// The address of an observer, as the four-byte word the machine would have read
// out of a table. A function pointer is not a `void*` in C++, so the conversion
// is spelled once here rather than at every planting site.
template <typename Callee>
Word code_address(Callee observer) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(observer));
}

void arm_hooks() {
  if (g_receiver_bytes == nullptr) {
    return;
  }
  if (g_replace_carrier_after_18 != nullptr) {
    set_word(g_receiver_bytes, kRecvCarrier,
             address_of(g_replace_carrier_after_18, 0));
  }
  if (g_replace_dispatch_after_18 != nullptr) {
    set_word(g_receiver_bytes, kRecvDispatch,
             address_of(g_replace_dispatch_after_18, 0));
  }
}

void arm_hooks_after_1c() {
  if (g_receiver_bytes == nullptr) {
    return;
  }
  if (g_replace_dispatch_after_1c != nullptr) {
    set_word(g_receiver_bytes, kRecvDispatch,
             address_of(g_replace_dispatch_after_1c, 0));
  }
}

void arm_hooks_after_10() {
  if (g_receiver_bytes == nullptr) {
    return;
  }
  if (g_replace_carrier_after_10 != nullptr) {
    set_word(g_receiver_bytes, kRecvCarrier,
             address_of(g_replace_carrier_after_10, 0));
  }
}

// The observer body, shared by all four real sites, the four alt sites and every
// decoy.
void record(int slot, void* receiver, Word first, Word second) {
  if (slot == kSlotDecoy) {
    ++g_decoy_count;
  }
  if (g_call_count >= kMaxCalls) {
    return;
  }
  CallRecord& entry = g_calls[static_cast<std::size_t>(g_call_count)];
  entry.slot = slot;
  entry.receiver = static_cast<Word>(reinterpret_cast<std::uintptr_t>(receiver));
  entry.first = first;
  entry.second = second;
  if (g_receiver_bytes != nullptr) {
    entry.result_at_68 = get_word(g_receiver_bytes, kRecvResult);
    entry.scale_at_18 = get_word(g_receiver_bytes, kRecvScaleResult);
    entry.zero_at_1c = get_word(g_receiver_bytes, kRecvZero1);
    entry.zero_at_20 = get_word(g_receiver_bytes, kRecvZero2);
    entry.flag_at_14 = g_receiver_bytes[kRecvFlag];
  }
  entry.xmm0 = xmm0_bits();
  ++g_call_count;
}

// Every observer is declared with the body's own convention, because the model
// calls through a thiscall-typed pointer and a plain cdecl function is not
// convertible to one. Two stack arguments is the widest shape; the decoys are
// declared the same way so a mis-dispatched call still balances the model's stack.
Word PKG_SW2_00A850D0_THISCALL observe_site18(void* receiver) {
  record(0x18, receiver, 0u, 0u);
  arm_hooks();
  return 0u;
}

Word PKG_SW2_00A850D0_THISCALL observe_site1c(void* receiver, Word first, Word second) {
  record(0x1c, receiver, first, second);
  arm_hooks_after_1c();
  return 0u;
}

Word PKG_SW2_00A850D0_THISCALL observe_site0c(void* receiver, Word first, Word second) {
  record(0x0c, receiver, first, second);
  return 0u;
}

Word PKG_SW2_00A850D0_THISCALL observe_site10(void* receiver, Word first, Word second) {
  record(0x10, receiver, first, second);
  arm_hooks_after_10();
  return g_return_from_site10;
}

Word PKG_SW2_00A850D0_THISCALL observe_decoy(void* receiver, Word first, Word second) {
  record(kSlotDecoy, receiver, first, second);
  return 0u;
}

// The alt table's four real slots, used only by case I to prove the separate reads
// of the receiver's word at displacement 0x10. Their slot is recorded NEGATED, so
// they are distinguishable from a transfer through the original table and are not
// counted as decoys.
Word PKG_SW2_00A850D0_THISCALL observe_alt18(void* receiver) {
  record(-0x18, receiver, 0u, 0u);
  arm_hooks();
  return 0u;
}

Word PKG_SW2_00A850D0_THISCALL observe_alt1c(void* receiver, Word first, Word second) {
  record(-0x1c, receiver, first, second);
  arm_hooks_after_1c();
  return 0u;
}

Word PKG_SW2_00A850D0_THISCALL observe_alt0c(void* receiver, Word first, Word second) {
  record(-0x0c, receiver, first, second);
  return 0u;
}

Word PKG_SW2_00A850D0_THISCALL observe_alt10(void* receiver, Word first, Word second) {
  record(-0x10, receiver, first, second);
  arm_hooks_after_10();
  return g_return_from_site10;
}

// -- fixture construction -----------------------------------------------------

void reset_log() {
  g_calls = std::array<CallRecord, kMaxCalls>{};
  g_call_count = 0;
  g_decoy_count = 0;
  g_replace_carrier_after_18 = nullptr;
  g_replace_carrier_after_10 = nullptr;
  g_replace_dispatch_after_18 = nullptr;
  g_replace_dispatch_after_1c = nullptr;
  g_receiver_bytes = nullptr;
  g_return_from_site10 = 0u;
}

void plant_table(std::array<std::uint8_t, 0x30>& table_bytes) {
  table_bytes.fill(0u);
  // Every slot starts as a decoy, so an off-by-one-slot read is a call the test
  // can see rather than a null target.
  for (std::size_t slot_index = 0; slot_index * 4u < 0x30u; ++slot_index) {
    set_word(table_bytes.data(), slot_index * 4u, code_address(&observe_decoy));
  }
  // The four displacements the machine actually fetches, and only those.
  set_word(table_bytes.data(), 0x0cu, code_address(&observe_site0c));
  set_word(table_bytes.data(), 0x10u, code_address(&observe_site10));
  set_word(table_bytes.data(), 0x18u, code_address(&observe_site18));
  set_word(table_bytes.data(), 0x1cu, code_address(&observe_site1c));
}

void plant_alt_table(std::array<std::uint8_t, 0x30>& table_bytes) {
  plant_table(table_bytes);
  set_word(table_bytes.data(), 0x0cu, code_address(&observe_alt0c));
  set_word(table_bytes.data(), 0x10u, code_address(&observe_alt10));
  set_word(table_bytes.data(), 0x18u, code_address(&observe_alt18));
  set_word(table_bytes.data(), 0x1cu, code_address(&observe_alt1c));
}

void plant_carrier(std::array<std::uint8_t, kCarrierExtent>& bytes, Word flags,
                   Float scale, Word arg0, Word arg1, Word half) {
  bytes.fill(0u);
  set_word(bytes.data(), kCarFlags, flags);
  set_float(bytes.data(), kCarScale, scale);
  set_word(bytes.data(), kCarArg0, arg0);
  set_word(bytes.data(), kCarArg1, arg1);
  // The halfword is written at its own displacement last, and the high half is
  // poisoned, so a dword read of the same address is distinguishable.
  set_word(bytes.data(), kCarHalf, kHalfHighPoison | half);
  // Decoy table pointers all over the carrier, so a model that used the carrier as
  // a dispatch object or as a table calls a decoy instead of reading nonsense.
  const Word decoy = address_of(g_fixture.decoy_table.data(), 0);
  for (std::size_t offset = 0; offset + 4u <= bytes.size(); offset += 4u) {
    const bool reserved = offset == kCarFlags || offset == kCarScale ||
                          (offset >= kCarArg0 && offset <= kCarHalf);
    if (!reserved) {
      set_word(bytes.data(), offset, decoy);
    }
  }
}

// Build the whole fixture: guard clear, one carrier installed, one dispatch object
// installed, and decoy table pointers in every slot the body does not read.
void build_fixture(Word flags, Float scale, Word dispatch_lead) {
  reset_log();
  plant_table(g_fixture.decoy_table);
  plant_carrier(g_fixture.carrier, flags, scale, kCarrierOneArg0, kCarrierOneArg1,
                kCarrierOneHalf);
  plant_carrier(g_fixture.carrier_alt, kCarrierAltFlags, kCarrierAltScale,
                kCarrierAltArg0, kCarrierAltArg1, kCarrierAltHalf);
  plant_carrier(g_fixture.carrier_third, kCarrierThirdFlags, kCarrierThirdScale,
                kCarrierThirdArg0, kCarrierThirdArg1, kCarrierThirdHalf);

  g_fixture.receiver.fill(kGuardPoisonByte);
  set_byte(g_fixture.receiver.data(), kRecvFlag, 0u);
  set_word(g_fixture.receiver.data(), kRecvCarrier,
           address_of(g_fixture.carrier.data(), 0));
  set_word(g_fixture.receiver.data(), kRecvDispatch,
           address_of(g_fixture.dispatch.data(), 0));
  for (std::size_t offset = 0; offset + 4u <= g_fixture.receiver.size(); offset += 4u) {
    if (offset == kRecvCarrier || offset == kRecvDispatch) {
      continue;
    }
    // The guard byte, the three float outputs, the address-taken word and the
    // result word are the receiver's own; everything else gets a decoy table.
    if (offset >= kRecvFlag && offset <= kRecvAddressArg) {
      continue;
    }
    if (offset == kRecvResult) {
      continue;
    }
    set_word(g_fixture.receiver.data(), offset,
             address_of(g_fixture.decoy_table.data(), 0));
  }

  g_fixture.dispatch.fill(0u);
  // Lead dword: the real table. Every other slot of the dispatch object is a decoy
  // table, so a model that used the dispatch object as the TABLE finds live decoys
  // at all four displacements instead of crashing.
  set_word(g_fixture.dispatch.data(), 0u, dispatch_lead);
  for (std::size_t offset = 4u; offset + 4u <= g_fixture.dispatch.size(); offset += 4u) {
    set_word(g_fixture.dispatch.data(), offset,
             address_of(g_fixture.decoy_table.data(), 0));
  }

  g_fixture.dispatch_alt.fill(0u);
  set_word(g_fixture.dispatch_alt.data(), 0u, address_of(g_fixture.table_alt.data(), 0));
  for (std::size_t offset = 4u; offset + 4u <= g_fixture.dispatch_alt.size();
       offset += 4u) {
    set_word(g_fixture.dispatch_alt.data(), offset,
             address_of(g_fixture.decoy_table.data(), 0));
  }

  plant_table(g_fixture.table);
  plant_alt_table(g_fixture.table_alt);
  g_receiver_bytes = g_fixture.receiver.data();
  set_xmm0_bits(0u);
  g_image_unit_scalar = 1.0f;
  g_image_zero_scalar = 0.0f;
}

// -- the harness --------------------------------------------------------------

int g_failures = 0;
int g_checks = 0;

void check(bool condition, const char* what) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    std::printf("  FAIL: %s\n", what);
  }
}

void check_equal_u32(Word actual, Word expected, const char* what) {
  ++g_checks;
  if (actual != expected) {
    ++g_failures;
    std::printf("  FAIL: %s (got 0x%08lx, want 0x%08lx)\n", what,
                static_cast<unsigned long>(actual),
                static_cast<unsigned long>(expected));
  }
}

void check_equal_f32(Float actual, Float expected, const char* what) {
  ++g_checks;
  if (float_bits(actual) != float_bits(expected)) {
    ++g_failures;
    std::printf("  FAIL: %s (got %.9g / 0x%08lx, want %.9g / 0x%08lx)\n", what,
                static_cast<double>(actual),
                static_cast<unsigned long>(float_bits(actual)),
                static_cast<double>(expected),
                static_cast<unsigned long>(float_bits(expected)));
  }
}

void check_no_decoy(const char* what) {
  ++g_checks;
  if (g_decoy_count != 0) {
    ++g_failures;
    std::printf("  FAIL: %s (%d decoy transfer(s) ran; a wrong object or a wrong "
                "slot displacement was used)\n",
                what, g_decoy_count);
  }
}

// The expected transfer sequence, as a list of slot displacements. A transfer
// through the alt table is recorded with its displacement negated, so the sequence
// says which table each transfer went through.
void check_sequence(const int* expected, std::size_t count, const char* what) {
  ++g_checks;
  bool same = (static_cast<std::size_t>(g_call_count) == count);
  if (same) {
    for (std::size_t index = 0; index < count; ++index) {
      if (g_calls[index].slot != expected[index]) {
        same = false;
        break;
      }
    }
  }
  if (!same) {
    ++g_failures;
    std::printf("  FAIL: %s -- got %d transfer(s):", what, g_call_count);
    for (int index = 0; index < g_call_count; ++index) {
      std::printf(" %d", g_calls[static_cast<std::size_t>(index)].slot);
    }
    std::printf(" -- want %d:", static_cast<int>(count));
    for (std::size_t index = 0; index < count; ++index) {
      std::printf(" %d", expected[index]);
    }
    std::printf("\n");
  }
}

Float run_model(Word stack_word) {
  return re_00a850d0(reinterpret_cast<Receiver*>(g_fixture.receiver.data()), stack_word);
}

// -- the cases ----------------------------------------------------------------

// A: the guard. 00a850d3 compares the byte at receiver+0x14 against ZERO, so any
// non-zero value exits, and the exit writes nothing at all -- including not
// balancing the POP EDI that the body would have pushed.
void case_a_guard_nonzero_returns_untouched() {
  std::printf("case A: a non-zero guard byte returns untouched\n");
  build_fixture(0xffffffffu, 4.0f, address_of(g_fixture.table.data(), 0));
  set_byte(g_fixture.receiver.data(), kRecvFlag, 0x5au);
  const std::array<std::uint8_t, kReceiverExtent> before = g_fixture.receiver;
  set_xmm0_bits(kSentinel);

  const Float returned = run_model(0u);

  check(g_call_count == 0, "A: no transfer happens");
  check_no_decoy("A: no decoy transfer");
  check(g_fixture.receiver == before,
        "A: the receiver is byte-for-byte unchanged, so the early exit writes "
        "nothing and does not even reach the POP EDI it never pushed");
  check_equal_u32(float_bits(returned), kSentinel,
                  "A: XMM0 was never written, so the caller's register contents "
                  "come back unchanged");

  // The converse: a zero guard is the only value that proceeds.
  reset_log();
  set_byte(g_fixture.receiver.data(), kRecvFlag, 0x00u);
  (void)run_model(0u);
  check(g_call_count > 0, "A: a zero guard byte does proceed to the transfers");
  check_no_decoy("A: no decoy transfer on the proceeding path");
}

// B: a null dispatch object. 00a850e7 branches to 0x00a8515c, which is PAST the
// store of all ones at 0x00a85133 -- so the receiver's displacement 0x68 must
// survive, and that is the only way to tell this branch from a fall-through.
void case_b_null_dispatch_pointer() {
  std::printf("case B: a null word at receiver+0x10 skips every transfer\n");
  build_fixture(0xffffffffu, 4.0f, address_of(g_fixture.table.data(), 0));
  set_word(g_fixture.receiver.data(), kRecvDispatch, 0u);
  (void)run_model(0u);

  check(g_call_count == 0, "B: no transfer happens");
  check_no_decoy("B: no decoy transfer");
  check_equal_u32(get_word(g_fixture.receiver.data(), kRecvResult), kGuardPoison,
                  "B: receiver+0x68 is NOT written, because the store of all ones "
                  "at 00a85133 lies past this branch");
  check_equal_u32(g_fixture.receiver[kRecvFlag], 1u,
                  "B: the guard byte is still raised, because 00a850e1 precedes "
                  "the null test");
  check_equal_f32(get_float(g_fixture.receiver.data(), kRecvScaleResult), 0.25f,
                  "B: the float tail still ran, so receiver+0x18 is 1/4");
}

// C: the four flag bits, one at a time, and the four positions that must do
// nothing. The carrier's float is driven NEGATIVE for the isolating cases, so the
// bit-1-CLEAR arm at 0x00a8518c cannot fire and each bit's own arm is the only
// thing that can produce a transfer. That matters: with a positive float the
// bit-1-CLEAR arm fires for every flag word whose bit 1 is clear, and the
// "untested bit" cases would stop being able to distinguish anything.
void case_c_flag_bit_indices() {
  std::printf("case C: each flag bit drives exactly one arm\n");
  const Word table_lead = address_of(g_fixture.table.data(), 0);
  const Word silent_bits[] = {0x00000001u, 0x00000008u, 0x00000020u, 0x00000080u};
  for (std::size_t index = 0; index < 4u; ++index) {
    build_fixture(silent_bits[index], -1.0f, table_lead);
    (void)run_model(0u);
    check(g_call_count == 0,
          "C: a bit position the body never tests produces no transfer at all");
    check_no_decoy("C: no decoy transfer");
  }

  build_fixture(0x00000002u, -1.0f, table_lead);
  (void)run_model(0u);
  {
    const int want[] = {0x0c};
    check_sequence(want, 1u,
                   "C: bit 1 SET dispatches at slot 0x0c, the arm 00a85142 guards");
  }
  check_no_decoy("C: bit 1 set");

  build_fixture(0x00000004u, -1.0f, table_lead);
  (void)run_model(0u);
  {
    const int want[] = {0x18};
    check_sequence(want, 1u, "C: bit 2 alone dispatches at slot 0x18");
  }
  check_no_decoy("C: bit 2 alone");

  build_fixture(0x00000010u, -1.0f, table_lead);
  (void)run_model(0u);
  {
    const int want[] = {0x1c};
    check_sequence(want, 1u, "C: bit 4 alone dispatches at slot 0x1c");
  }
  check_equal_u32(g_calls[0].first, kCarrierOneHalf,
                  "C: the 0x1c call's first stack argument is the carrier's HALFWORD "
                  "at displacement 0xa8");
  check_equal_u32(g_calls[0].second, 0u,
                  "C: with bit 6 clear the second stack argument is a literal zero");
  check_no_decoy("C: bit 4 alone");

  build_fixture(0x00000040u, -1.0f, table_lead);
  (void)run_model(0u);
  check(g_call_count == 0,
        "C: bit 6 alone produces no transfer: it modifies the bit-4 arm's second "
        "argument and is never an arm by itself");
  check_no_decoy("C: bit 6 alone");

  // The bit-1-CLEAR arm, isolated by a positive float and no other bit set.
  build_fixture(0u, 4.0f, table_lead);
  (void)run_model(0u);
  {
    const int want[] = {0x10};
    check_sequence(want, 1u,
                   "C: an all-zero flag word with a positive carrier float reaches "
                   "the bit-1-CLEAR arm and dispatches at slot 0x10");
  }
  check_no_decoy("C: the bit-1-CLEAR arm");

  // Everything set: the ordering is 0x18, then 0x1c, then 0x0c, because bit 1 is
  // set and so the bit-1-CLEAR arm at 0x00a8518c is not entered.
  build_fixture(0xffffffffu, 4.0f, table_lead);
  (void)run_model(0u);
  {
    const int want[] = {0x18, 0x1c, 0x0c};
    check_sequence(want, 3u, "C: all bits set dispatches 0x18, 0x1c, 0x0c in that "
                             "order, and NOT 0x10");
  }
  check_no_decoy("C: all bits set");

  // Two adjacent bits, so an off-by-one shift in EITHER direction is visible.
  build_fixture(0x00000006u, -1.0f, table_lead);
  (void)run_model(0u);
  {
    const int want[] = {0x18, 0x0c};
    check_sequence(want, 2u, "C: bits 1 and 2 together give 0x18 then 0x0c");
  }
  build_fixture(0x00000014u, -1.0f, table_lead);
  (void)run_model(0u);
  {
    const int want[] = {0x18, 0x1c};
    check_sequence(want, 2u, "C: bits 2 and 4 together give 0x18 then 0x1c");
  }
  build_fixture(0x00000012u, -1.0f, table_lead);
  (void)run_model(0u);
  {
    const int want[] = {0x1c, 0x0c};
    check_sequence(want, 2u, "C: bits 1 and 4 together give 0x1c then 0x0c");
  }
  check_no_decoy("C: the two-bit combinations");
}

// D: the argument order, the halfword width, the address argument's identity, the
// DIVSS operand order and the return register. The carrier's two pushed words are
// given distinct patterns and the scale is driven to four so 1/4 and 4 are far
// apart.
void case_d_argument_order_and_arithmetic() {
  std::printf("case D: argument order, halfword width, DIVSS order, return value\n");
  build_fixture(0x00000016u, 4.0f, address_of(g_fixture.table.data(), 0));  // bits 1,2,4
  (void)run_model(0u);

  const int want[] = {0x18, 0x1c, 0x0c};
  check_sequence(want, 3u, "D: bits 1, 2 and 4 give 0x18, 0x1c, 0x0c");
  check_no_decoy("D: no decoy transfer");

  check_equal_u32(g_calls[0].first, 0u,
                  "D: the 0x18 call pushes NOTHING, so its callee sees no stack "
                  "argument at all");
  check_equal_u32(g_calls[0].second, 0u,
                  "D: the 0x18 call pushes nothing, so there is no second "
                  "argument either");

  // REFUTE F: a swapped pair. 0x1c's first argument is the halfword and its second
  // is the address-or-zero, and the two are given different patterns.
  check_equal_u32(g_calls[1].first, kCarrierOneHalf,
                  "D: the 0x1c call's FIRST stack argument is the carrier's word "
                  "at 0xa8, not the address argument");
  check_equal_u32(g_calls[1].second, 0u,
                  "D: the 0x1c call's SECOND stack argument is the address-or-zero");
  // REFUTE F: a dword read instead of the halfword read.
  check(g_calls[1].first != (kHalfHighPoison | kCarrierOneHalf),
        "D: the 0x1c call's first argument is the 16-bit halfword and not the "
        "32-bit word, so the poisoned high half never reaches the callee");

  // REFUTE F again on the 0x0c arm, where the two pushed words are one dword apart
  // in the carrier and four bytes apart on the stack.
  check_equal_u32(g_calls[2].first, kCarrierOneArg0,
                  "D: the 0x0c call's FIRST stack argument is the carrier's word "
                  "at 0xa0");
  check_equal_u32(g_calls[2].second, kCarrierOneArg1,
                  "D: the 0x0c call's SECOND stack argument is the carrier's word "
                  "at 0xa4");
  check(g_calls[2].first != kCarrierOneArg1 && g_calls[2].second != kCarrierOneArg0,
        "D: the 0x0c call's two stack arguments are not exchanged");

  // REFUTE G: DIVSS XMM1,XMM0 makes the .rdata word the dividend.
  check_equal_f32(get_float(g_fixture.receiver.data(), kRecvScaleResult), 0.25f,
                  "D: receiver+0x18 is unit/scale (0.25), not scale/unit (4)");
  check_equal_f32(get_float(g_fixture.receiver.data(), kRecvZero1), 0.0f,
                  "D: receiver+0x1c is zeroed");
  check_equal_f32(get_float(g_fixture.receiver.data(), kRecvZero2), 0.0f,
                  "D: receiver+0x20 is zeroed");

  // With bit 6 set, the second argument is the receiver's own address. The float
  // is negative here so the bit-1-CLEAR arm cannot add a transfer of its own.
  build_fixture(0x00000050u, -1.0f, address_of(g_fixture.table.data(), 0));
  (void)run_model(0u);
  {
    const int want_bit4[] = {0x1c};
    check_sequence(want_bit4, 1u, "D: bit 4 alone still dispatches at 0x1c");
  }
  check_equal_u32(g_calls[0].second, address_of(g_fixture.receiver.data(), kRecvAddressArg),
                  "D: with bit 6 set the second stack argument is the receiver's "
                  "own address at displacement 0x28, pointer-identical");

  // And the RETURN value is the carrier's float, not its reciprocal.
  build_fixture(0u, 2.0f, address_of(g_fixture.table.data(), 0));
  set_xmm0_bits(0u);
  const Float returned = run_model(0u);
  check_equal_f32(get_float(g_fixture.receiver.data(), kRecvScaleResult), 0.5f,
                  "D: receiver+0x18 is 1/2");
  check_equal_f32(returned, 2.0f,
                  "D: the returned value is the carrier's float (2), NOT its "
                  "reciprocal (0.5): 00a8517e divides into XMM1 and XMM0 is "
                  "untouched");
}

// E: the COMISS polarity at both comparison sites, including the unordered case.
// JBE is CF-or-ZF, so a NaN takes the branch at BOTH 00a85174 and 00a85198.
void case_e_comparison_polarity() {
  std::printf("case E: COMISS polarity and the unordered case\n");
  const Float nan_value = std::numeric_limits<Float>::quiet_NaN();
  const Float denormal = std::numeric_limits<Float>::denorm_min();
  struct Sample {
    Float scale;
    bool arm_taken;       // the 00a85191 comparison let the 0x10 call through
    bool reciprocal_kept; // receiver+0x18 is 1/scale rather than positive zero
  };
  const Sample samples[] = {
      {4.0f, true, true},
      {1.0f, true, true},
      {0.5f, true, true},
      {denormal, true, true},  // positive, so the branch is not taken
      {0.0f, false, false},    // equal to zero: JBE is taken
      {-0.0f, false, false},   // -0.0f compares EQUAL to +0.0f: JBE is taken
      {-1.0f, false, false},   // negative: JBE is taken
      {nan_value, false, false},  // unordered: CF and ZF are both set
      {std::numeric_limits<Float>::infinity(), true, true},  // 1/inf is +0.0f
  };
  for (std::size_t index = 0; index < sizeof(samples) / sizeof(samples[0]); ++index) {
    build_fixture(0u, samples[index].scale, address_of(g_fixture.table.data(), 0));
    (void)run_model(0u);
    if (samples[index].arm_taken) {
      const int want_arm[] = {0x10};
      check_sequence(want_arm, 1u,
                     "E: the 00a85191 comparison let the 0x10 arm through");
    } else {
      check(g_call_count == 0,
            "E: the 00a85191 comparison sent control to 00a8515c and no transfer "
            "happened");
    }
    check_no_decoy("E: no decoy transfer");
    const Float stored = get_float(g_fixture.receiver.data(), kRecvScaleResult);
    if (samples[index].reciprocal_kept) {
      check_equal_f32(stored, 1.0f / samples[index].scale,
                      "E: receiver+0x18 is the reciprocal of a strictly positive "
                      "float");
    } else {
      check_equal_f32(stored, 0.0f,
                      "E: receiver+0x18 is POSITIVE zero, the XORPS result, when "
                      "the float is not strictly greater than zero");
      check(float_bits(stored) == 0u,
            "E: the stored zero is +0.0f (all bits clear), not -0.0f");
    }
  }

  // REFUTE J: both .rdata words are READS. Overwriting the threshold must change
  // which arm is taken, which a hard-coded zero could not do.
  build_fixture(0u, -50.0f, address_of(g_fixture.table.data(), 0));
  g_image_zero_scalar = -100.0f;
  (void)run_model(0u);
  {
    const int want[] = {0x10};
    check_sequence(want, 1u,
                   "E: the 00a85191 threshold is the .rdata word, not a hard-coded "
                   "zero: with the word at -100 a float of -50 takes the arm");
  }
  check_no_decoy("E: no decoy transfer");

  // And the dividend is read too.
  build_fixture(0u, 4.0f, address_of(g_fixture.table.data(), 0));
  g_image_unit_scalar = 3.0f;
  (void)run_model(0u);
  check_equal_f32(get_float(g_fixture.receiver.data(), kRecvScaleResult), 0.75f,
                  "E: receiver+0x18 is the .rdata word divided by the carrier's "
                  "float, so overwriting the word changed the result");
}

// F: the signed comparison at 00a851b7, and the early return that follows it. The
// two zeroed floats and the reciprocal are all on the far side of that branch, so
// a negative result must leave them exactly as they were.
void case_f_signed_result_comparison() {
  std::printf("case F: the signed comparison at 00a851b7 and the early return\n");
  const Word results[] = {0x00000000u, 0x00000001u, 0x7fffffffu, 0x40000000u,
                          0x80000000u, 0xffffffffu};
  for (std::size_t index = 0; index < sizeof(results) / sizeof(results[0]); ++index) {
    const bool negative = (results[index] & 0x80000000u) != 0u;
    build_fixture(0u, 4.0f, address_of(g_fixture.table.data(), 0));
    g_return_from_site10 = results[index];
    const Float returned = run_model(0u);

    check_equal_u32(get_word(g_fixture.receiver.data(), kRecvResult), results[index],
                    "F: receiver+0x68 holds the 0x10 callee's EAX whatever it is");
    if (negative) {
      // REFUTE E: an unsigned rewrite of JGE would take the tail for 0x80000000.
      check_equal_u32(g_fixture.receiver[kRecvFlag], 0u,
                      "F: a negative result released the guard byte, so JGE at "
                      "00a851b7 is the SIGNED comparison");
      check_equal_u32(get_word(g_fixture.receiver.data(), kRecvScaleResult), kGuardPoison,
                      "F: a negative result returned before the tail, so "
                      "receiver+0x18 was never written");
      check_equal_u32(get_word(g_fixture.receiver.data(), kRecvZero1), kGuardPoison,
                      "F: a negative result returned before the tail, so "
                      "receiver+0x1c was never written");
      check_equal_u32(get_word(g_fixture.receiver.data(), kRecvZero2), kGuardPoison,
                      "F: a negative result returned before the tail, so "
                      "receiver+0x20 was never written");
      // The returned value is XMM0 as 00a8518c left it, unless the transfer
      // clobbered it. The model claims the pre-call value and the sidecar names
      // the clobber as an open question, so only the pre-call value is asserted.
      check_equal_f32(returned, 4.0f,
                      "F: the early return carries the float 00a8518c loaded");
    } else {
      check_equal_u32(g_fixture.receiver[kRecvFlag], 1u,
                      "F: a non-negative result left the guard byte raised");
      check_equal_f32(get_float(g_fixture.receiver.data(), kRecvScaleResult), 0.25f,
                      "F: a non-negative result fell through to the tail");
      check_equal_f32(returned, 4.0f,
                      "F: the tail reloaded XMM0 from the fourth read of the "
                      "carrier pointer");
    }
  }
  check_no_decoy("F: no decoy transfer");
}

// G: write ordering, measured from inside each callee. Only a callee that samples
// the receiver at the moment it is entered can pin where 00a85133 sits.
void case_g_write_ordering() {
  std::printf("case G: the placement of the store of all ones, and of the result\n");
  build_fixture(0xffffffffu, 4.0f, address_of(g_fixture.table.data(), 0));
  (void)run_model(0u);
  const int want[] = {0x18, 0x1c, 0x0c};
  check_sequence(want, 3u, "G: all bits set");
  check_no_decoy("G: no decoy transfer");
  check_equal_u32(g_calls[0].result_at_68, kGuardPoison,
                  "G: receiver+0x68 is still the poison value inside the 0x18 "
                  "callee, so the store of all ones comes later");
  check_equal_u32(g_calls[1].result_at_68, kGuardPoison,
                  "G: receiver+0x68 is still the poison value inside the 0x1c "
                  "callee, so the store of all ones comes after the bit-4 arm");
  check_equal_u32(g_calls[2].result_at_68, kResultInitialValue,
                  "G: receiver+0x68 already holds all ones inside the 0x0c callee, "
                  "so 00a85133 precedes the bit-1-set arm");
  for (int index = 0; index < g_call_count; ++index) {
    check_equal_u32(g_calls[static_cast<std::size_t>(index)].flag_at_14, 1u,
                    "G: the guard byte is already raised inside every callee, so "
                    "00a850e1 precedes all three transfers");
    check_equal_u32(g_calls[static_cast<std::size_t>(index)].scale_at_18, kGuardPoison,
                    "G: receiver+0x18 is still poisoned inside every callee, so the "
                    "reciprocal store comes after all of them");
    check_equal_u32(g_calls[static_cast<std::size_t>(index)].zero_at_1c, kGuardPoison,
                    "G: receiver+0x1c is still poisoned inside every callee, so "
                    "the zeroing store comes after all of them");
  }

  // And the result store follows the 0x10 transfer.
  build_fixture(0u, 4.0f, address_of(g_fixture.table.data(), 0));
  g_return_from_site10 = 0x1234u;
  (void)run_model(0u);
  check_equal_u32(g_calls[0].result_at_68, kResultInitialValue,
                  "G: receiver+0x68 holds all ones, not the callee's result, inside "
                  "the 0x10 callee: 00a851b2 stores the result AFTER the transfer");
  check_equal_u32(get_word(g_fixture.receiver.data(), kRecvResult), 0x1234u,
                  "G: and the callee's result is in the receiver once it returns");
}

// H: the register argument of all four transfers. It is the object at receiver
// displacement 0x10 in every case -- never the receiver, never the carrier, never
// the table. The decoys planted on the other two objects make a mistake a CALL
// rather than a crash, so it cannot pass silently.
void case_h_register_argument_is_the_dispatch_object() {
  std::printf("case H: the register argument of every transfer\n");
  const Word dispatch_object = address_of(g_fixture.dispatch.data(), 0);
  const Word carrier_one = address_of(g_fixture.carrier.data(), 0);
  const Word receiver = address_of(g_fixture.receiver.data(), 0);
  const Word table = address_of(g_fixture.table.data(), 0);
  const Word decoy = address_of(g_fixture.decoy_table.data(), 0);

  build_fixture(0x00000016u, 4.0f, table);  // bits 1, 2 and 4
  (void)run_model(0u);
  const int want[] = {0x18, 0x1c, 0x0c};
  check_sequence(want, 3u, "H: three transfers");
  check_no_decoy("H: no decoy transfer");
  for (int index = 0; index < g_call_count; ++index) {
    const Word seen = g_calls[static_cast<std::size_t>(index)].receiver;
    check_equal_u32(seen, dispatch_object,
                    "H: the register argument is the object at receiver+0x10");
    check(seen != receiver, "H: the register argument is not the receiver itself");
    check(seen != carrier_one, "H: the register argument is not the carrier");
    check(seen != table, "H: the register argument is not the table");
    check(seen != decoy, "H: the register argument is not a decoy");
  }

  // The fourth site, and the fact that the 0x18 site is reached with the value
  // 00a850dd loaded rather than with a later read.
  build_fixture(0u, 4.0f, table);
  (void)run_model(0u);
  {
    const int want_alone[] = {0x10};
    check_sequence(want_alone, 1u, "H: the bit-1-CLEAR arm reaches the fourth site");
  }
  check_equal_u32(g_calls[0].receiver, dispatch_object,
                  "H: the fourth transfer's register argument is the object at "
                  "receiver+0x10");
  check_no_decoy("H: no decoy transfer on the fourth site");
}

// I: THE FOUR SEPARATE READS OF THE RECEIVER'S WORD AT DISPLACEMENT 0x0c. The body
// reads it at 00a850e9, 00a850fe, 00a85130 and 00a8515f, and it calls out between
// the reads, so a callee can replace the carrier. The test installs a second
// carrier from inside the 0x18 callee and a third from inside the 0x10 callee, and
// every later read must see the replacement.
void case_i_four_reads_of_the_carrier_pointer() {
  std::printf("case I: the receiver's word at 0x0c is read four times\n");
  build_fixture(kCarrierOneFlags, kCarrierOneScale, address_of(g_fixture.table.data(), 0));
  // READ #1 sees carrier_one, whose flag word is bit 2 only, so exactly one
  // transfer is scheduled -- and that transfer installs carrier_alt, whose flag
  // word is bits 4 and 6, so READ #2 and READ #3 see a different object.
  g_replace_carrier_after_18 = g_fixture.carrier_alt.data();
  // carrier_alt has bit 1 clear and a positive float, so the 0x10 transfer runs,
  // and that transfer installs carrier_third, whose float is 2.0. READ #4 -- the
  // tail's read at 00a8515f -- must therefore see carrier_third.
  g_replace_carrier_after_10 = g_fixture.carrier_third.data();
  g_return_from_site10 = 11u;
  (void)run_model(0u);

  const int want[] = {0x18, 0x1c, 0x10};
  check_sequence(want, 3u,
                 "I: after the 0x18 callee replaced the carrier, the bit-4 and "
                 "bit-1-CLEAR arms ran, which only a SECOND read of receiver+0x0c "
                 "can produce");
  check_no_decoy("I: no decoy transfer");
  check_equal_u32(g_calls[1].first, kCarrierAltHalf,
                  "I: the 0x1c call's halfword came from the REPLACEMENT carrier");
  check_equal_u32(g_calls[1].second, address_of(g_fixture.receiver.data(), kRecvAddressArg),
                  "I: the 0x1c call took its address argument, so bit 6 of the "
                  "REPLACEMENT carrier's flag word was the one tested");
  check_equal_u32(g_calls[2].first, kCarrierAltArg0,
                  "I: the 0x10 call's first argument came from the REPLACEMENT "
                  "carrier");
  check_equal_u32(g_calls[2].second, kCarrierAltArg1,
                  "I: the 0x10 call's second argument came from the REPLACEMENT "
                  "carrier");
  check(g_calls[1].first != kCarrierOneHalf,
        "I: the 0x1c call did NOT use the original carrier's halfword");
  check(g_calls[2].first != kCarrierOneArg0,
        "I: the 0x10 call did NOT use the original carrier's word at 0xa0");
  check_equal_f32(get_float(g_fixture.receiver.data(), kRecvScaleResult), 0.5f,
                  "I: the tail's FOURTH read of receiver+0x0c saw the carrier the "
                  "0x10 callee installed (1/2), not the one that call used (1/4)");
  check(float_bits(get_float(g_fixture.receiver.data(), kRecvScaleResult)) !=
            float_bits(1.0f / kCarrierAltScale),
        "I: the reciprocal is not the one the pre-swap carrier would have given");
  check_equal_u32(get_word(g_fixture.receiver.data(), kRecvResult), 11u,
                  "I: the 0x10 result reached receiver+0x68");
  check_equal_u32(g_fixture.receiver[kRecvFlag], 1u,
                  "I: 11 is non-negative, so the guard byte stayed raised");

  // The same case with no replacements at all, to show what the replaced run looked
  // like: the original carrier's flag word schedules one transfer and nothing else.
  build_fixture(kCarrierOneFlags, kCarrierOneScale, address_of(g_fixture.table.data(), 0));
  (void)run_model(0u);
  {
    const int want_plain[] = {0x18, 0x10};
    check_sequence(want_plain, 2u,
                   "I: without a replacement the original carrier's bit-2-only flag "
                   "word gives the bit-2 arm and then the bit-1-CLEAR arm, which is "
                   "what makes the replaced run's different three transfers "
                   "meaningful");
  }
  check_equal_f32(get_float(g_fixture.receiver.data(), kRecvScaleResult), 0.125f,
                  "I: and the tail's read then saw the original carrier (1/8)");
}

// J: the four separate reads of the receiver's word at displacement 0x10. The
// reloads at 00a8511b, 00a8514a and 00a851a0 are each inside the argument setup of
// a transfer, so a callee that replaces the word changes where the NEXT transfer
// goes. The replacement dispatch object's lead word names a table whose four slots
// carry distinguishable alt observers, so a cached pointer is visible.
void case_j_four_reads_of_the_dispatch_pointer() {
  std::printf("case J: the receiver's word at 0x10 is read four times\n");
  const Word original = address_of(g_fixture.dispatch.data(), 0);
  const Word replacement = address_of(g_fixture.dispatch_alt.data(), 0);

  // Bits 1, 2 and 4. The 0x18 transfer happens first and installs the replacement,
  // so the 0x1c and 0x0c transfers -- whose register arguments are reloaded at
  // 00a8511b and 00a8514a -- must go through the replacement's table.
  build_fixture(0x00000016u, 4.0f, address_of(g_fixture.table.data(), 0));
  g_replace_dispatch_after_18 = g_fixture.dispatch_alt.data();
  (void)run_model(0u);
  {
    const int want[] = {0x18, -0x1c, -0x0c};
    check_sequence(want, 3u,
                   "J: after the 0x18 callee replaced the dispatch object, the next "
                   "two transfers went through the REPLACEMENT's table");
  }
  check_no_decoy("J: no decoy transfer");
  check_equal_u32(g_calls[0].receiver, original,
                  "J: the first transfer's register argument is the dispatch object "
                  "00a850dd loaded, and 00a850f7 does not reload it");
  check_equal_u32(g_calls[1].receiver, replacement,
                  "J: the second transfer's register argument is the dispatch object "
                  "00a8511b reloaded");
  check_equal_u32(g_calls[2].receiver, replacement,
                  "J: the third transfer's register argument is the dispatch object "
                  "00a8514a reloaded");
  check(g_calls[1].receiver != g_calls[0].receiver,
        "J: the second transfer did NOT reuse the first transfer's pointer");

  // Bits 1 and 2, with the replacement installed from inside the 0x1c callee, so
  // the reload at 00a851a0 -- the fourth and last of them -- is the one observed.
  build_fixture(0x00000014u, 4.0f, address_of(g_fixture.table.data(), 0));
  g_replace_dispatch_after_1c = g_fixture.dispatch_alt.data();
  g_return_from_site10 = 0u;
  (void)run_model(0u);
  {
    const int want[] = {0x18, 0x1c, -0x10};
    check_sequence(want, 3u,
                   "J: the 0x1c transfer necessarily used the ORIGINAL table, "
                   "because the hook fires as that callee is entered, and the 0x10 "
                   "transfer then went through the REPLACEMENT's table");
  }
  check_no_decoy("J: no decoy transfer on the fourth reload");
  check_equal_u32(g_calls[2].receiver, replacement,
                  "J: the fourth transfer's register argument is the dispatch object "
                  "00a851a0 reloaded");
}

// K: nothing on the carrier or on the dispatch object is written, and the single
// popped stack word is never read. Each of the three runs starts from a freshly
// built fixture, so the three are comparable byte for byte.
void case_k_no_writes_and_unread_stack_word() {
  std::printf("case K: no write outside the receiver; the popped word is unread\n");
  std::array<std::uint8_t, 64> poisoned{};

  build_fixture(0xffffffffu, 4.0f, address_of(g_fixture.table.data(), 0));
  const std::array<std::uint8_t, kCarrierExtent> carrier_before = g_fixture.carrier;
  const std::array<std::uint8_t, 0x40> dispatch_before = g_fixture.dispatch;
  const std::array<std::uint8_t, kReceiverExtent> receiver_before = g_fixture.receiver;
  check(g_fixture.carrier == carrier_before, "K: the fixture starts in a known state");

  const Word stack_words[] = {
      0u, 0x5a5a5a5au,
      static_cast<Word>(reinterpret_cast<std::uintptr_t>(poisoned.data()))};
  std::array<std::uint8_t, kReceiverExtent> after_first{};
  for (std::size_t index = 0; index < 3u; ++index) {
    poisoned.fill(0xa5u);
    build_fixture(0xffffffffu, 4.0f, address_of(g_fixture.table.data(), 0));
    (void)run_model(stack_words[index]);
    if (index == 0u) {
      check(g_fixture.carrier == carrier_before,
            "K: not one byte of the carrier changed, so the body reads it and never "
            "writes it");
      check(g_fixture.dispatch == dispatch_before,
            "K: not one byte of the dispatch object changed, so the body reads it "
            "and never writes it");
      check(g_fixture.receiver != receiver_before,
            "K: the receiver did change, so the run was not a no-op");
    } else {
      check(g_fixture.receiver == after_first,
            "K: the popped stack word is never read: three different values give "
            "byte-identical receiver state");
      check(g_fixture.carrier == carrier_before,
            "K: the carrier is unchanged for every stack word value");
      check(g_fixture.dispatch == dispatch_before,
            "K: the dispatch object is unchanged for every stack word value");
    }
    if (index == 0u) {
      after_first = g_fixture.receiver;
    }
    bool untouched = true;
    for (std::size_t byte = 0; byte < poisoned.size(); ++byte) {
      if (poisoned[byte] != 0xa5u) {
        untouched = false;
      }
    }
    check(untouched,
          "K: a stack word pointing at a poisoned block leaves that block "
          "untouched, so it was never dereferenced");
  }
}

// L: a whole-run summary across the flag-word space, to catch a combination the
// hand-written cases miss. Every flag word in the low nibble is run against three
// carrier floats, and the exact transfer sequence is predicted from the four bit
// tests and the two comparisons.
void case_l_exhaustive_flag_words() {
  std::printf("case L: every flag word in the low nibble, predicted then measured\n");
  for (Word flags = 0u; flags < 0x10u; ++flags) {
    for (int scale_choice = 0; scale_choice < 3; ++scale_choice) {
      const Float scale = scale_choice == 0   ? 4.0f
                          : scale_choice == 1 ? 0.0f
                                              : -1.0f;
      build_fixture(flags, scale, address_of(g_fixture.table.data(), 0));
      (void)run_model(0u);

      int want[kMaxCalls];
      std::size_t want_count = 0u;
      if ((flags & 0x04u) != 0u) {
        want[want_count++] = 0x18;
      }
      if ((flags & 0x10u) != 0u) {
        want[want_count++] = 0x1c;
      }
      if ((flags & 0x02u) != 0u) {
        want[want_count++] = 0x0c;
      } else if (scale > 0.0f) {
        want[want_count++] = 0x10;
      }
      if (want_count != 0u) {
        check_sequence(want, want_count,
                       "L: the predicted transfer sequence for this flag word and "
                       "this carrier float");
      } else {
        check(g_call_count == 0, "L: no transfer was predicted and none happened");
      }
      check_no_decoy("L: no decoy transfer");

      // Whatever happened, the tail's outcome is the same shape every time.
      const Float stored = get_float(g_fixture.receiver.data(), kRecvScaleResult);
      if (scale > 0.0f) {
        check_equal_f32(stored, 1.0f / scale,
                        "L: a strictly positive float gives its reciprocal");
      } else {
        check_equal_f32(stored, 0.0f, "L: anything else gives positive zero");
      }
      check_equal_f32(get_float(g_fixture.receiver.data(), kRecvZero1), 0.0f,
                      "L: receiver+0x1c is zeroed on every path that reaches the "
                      "tail");
      check_equal_f32(get_float(g_fixture.receiver.data(), kRecvZero2), 0.0f,
                      "L: receiver+0x20 is zeroed on every path that reaches the "
                      "tail");
    }
  }
}

}  // namespace

int model_test() {
  std::printf("model test for re_00a850d0 (FUN_00a850d0 @ 0x00a850d0)\n");
  case_a_guard_nonzero_returns_untouched();
  case_b_null_dispatch_pointer();
  case_c_flag_bit_indices();
  case_d_argument_order_and_arithmetic();
  case_e_comparison_polarity();
  case_f_signed_result_comparison();
  case_g_write_ordering();
  case_h_register_argument_is_the_dispatch_object();
  case_i_four_reads_of_the_carrier_pointer();
  case_j_four_reads_of_the_dispatch_pointer();
  case_k_no_writes_and_unread_stack_word();
  case_l_exhaustive_flag_words();
  std::printf("%d check(s), %d failure(s)\n", g_checks, g_failures);
  return g_failures == 0 ? 0 : 1;
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00a850d0

int main() {
  return openspore::reconstruction::pkg_swarm_w2_00a850d0::model_test();
}
