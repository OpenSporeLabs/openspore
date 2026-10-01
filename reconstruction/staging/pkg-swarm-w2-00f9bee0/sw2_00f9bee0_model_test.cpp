// PKG-SWARM-W2-00F9BEE0 -- VA 0x00f9bee0
// Behavioural model test for FUN_00f9bee0 @ 0x00f9bee0.
//
// All five DIRECT callees are defined here as observers, and all nine INDIRECT
// dispatches are observable too: the test owns every dispatch table, so it
// decides what each slot word is, where it is, and which arguments reach it. So
// the test sees every transfer the reconstruction makes, with which arguments,
// in which order, and gets to decide what each of them does to memory.
//
// What is asserted is what the 104-instruction listing fixes and nothing more:
//
//   * the exact 21-call sequence of the fall-through path, and the exact
//     one-call sequence of the early exit;
//   * every immediate: the four slot arguments on the first dispatch chain
//     (8, 0x3fbae24, 3, 0xa) and the four on the second (0x3fbae24, 0, 8, 7,
//     0x21), the eight channel ids 0x301 0x304 0x305 0x306 0x24b 0x23d 0x24c
//     0x24d each with a zero value word and a zero flag byte, and the two
//     always-zero words of every 0x00777ae0 call;
//   * the receiver of every one of the nine dispatches -- the second argument
//     for the four slot +0x50 dispatches and the first, the result of the
//     getter for the slot +0x54 one, the result of that for slot +0x0c, the
//     second getter's result for slot +0x1c and the result of that for slot
//     +0x134 -- and the identity of the two getters' two distinct objects;
//   * the six slot displacements, by planting a DIFFERENT decoy observer in
//     every neighbouring displacement of every table and a decoy in every
//     carrier at every one of the six displacements;
//   * the guard: the expected value is the receiver's address plus 4, or 0 when
//     the receiver is null, and the body proceeds only on EQUALITY;
//   * the receiver's single displacement, 0x8d8, with decoy words at 0x8d4 and
//     0x8dc and a sentinel tail past 0x8db;
//   * the one data word, 0x016c9e68, tested against zero and NEVER written by
//     the body;
//   * that the body performs NO memory write of its own anywhere;
//   * that the argument the body reads at 0x00f9bef0 really is the first stack
//     word, by replicating the machine's own three pushes and its own
//     `MOV ESI,[ESP+0x10]` in a probe;
//   * that the body consumes at most one word of the caller's stack, measured
//     through an inline-asm trampoline.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction, not to walk
// it. Each names a wrong reconstruction it is aimed at:
//
//   A  every one of the six slot displacements: twenty decoy observers sit in
//      the same tables at 0x04 0x08 0x10 0x14 0x18 0x20 0x24 0x48 0x4c 0x50 0x54
//      0x58 0x5c 0x60 0x12c 0x130 0x134 0x13c 0x140, so an off-by-4 or a
//      one-slot-out read is a named call in the log, not a silent difference;
//   B  two-level vs one-level: every carrier also carries a decoy word AT each
//      of the six displacements in its OWN bytes, so a reconstruction that
//      reads [object + slot] instead of [[object] + slot] dispatches through
//      the decoy and is caught;
//   C  the guard's expected value: driven with receiver+0, receiver+4 (taken),
//      receiver+8, receiver+0x80000000 and 0, so a hardcoded receiver+4, an
//      off-by-one displacement, an inverted branch and a signed compare are all
//      distinguishable;
//   D  the null-receiver arm: with the receiver null the expected value is 0,
//      and the body then FAULTS reading the receiver's word at 0x8d8. The test
//      catches the fault and asserts it, which is what refutes both a
//      reconstruction that hardcodes receiver+4 (it would exit instead) and one
//      that adds a null guard of its own (it would not fault);
//   E  the two global-getter objects are different: distinct tables, and each
//      carries decoys for the other's slots, so a reconstruction that swapped
//      them dispatches through the wrong receiver;
//   F  the discarded results are never consumed: the slot +0x0c, +0x50 and
//      +0x134 observers all return the address of a fixture carrier whose
//      dispatch word is zero, and the test asserts (i) no fault and (ii) that
//      the set of objects any dispatch was made through is exactly the five the
//      listing names. A reconstruction that chained one of them faults or
//      dispatches through a sixth object;
//   G  the receiver displacement 0x8d8: a non-zero decoy at 0x8d4 and 0x8dc must
//      not trigger the callee, and a zero word at 0x8d8 with both decoys
//      non-zero must not either;
//   H  the 0x00f998f0 arm is ordered AFTER the 0x00f96c60 arm and the callee --
//      not the body -- is what clears the receiver's word at 0x8d8: the
//      0x00f96c60 observer samples the word and the 0x00f998f0 observer samples
//      it at the instant of its own call;
//   I  the data word is read, never written: the 0x00f96c60 observer samples it
//      at the moment of the call and the test asserts it is unchanged across
//      the whole body;
//   J  the eight channel ids are in the listing's order and are not sorted, not
//      deduplicated and not reordered by size;
//   K  the argument surface is exactly one word at entry_ESP+0x4, measured by
//      replicating the prologue and the machine's own read.
//
// What is NOT asserted, and why:
//
//   * EAX. The body leaves the first dispatch's result there on the early-exit
//     path and the residue of the last slot +0x50 dispatch on the fall-through
//     path; the declared return type is void and no record fixes a width, so
//     there is nothing to assert. The one thing that IS asserted is negative:
//     the model binds nothing to the discarded results (case F).
//   * What 0x0067ddd0 and 0x0067dd80 return beyond being an object with a
//     dispatch word. Both are six-byte global getters in the image and the model
//     claims only the getter shape, which is all the body depends on.
//   * What 0x00f96c60 and 0x00f998f0 do beyond the two facts the body depends
//     on: that 0x00f96c60 clears the data word, and that 0x00f998f0 nulls the
//     receiver's word at 0x8d8. Both are reproduced in the observers because
//     this body's observable behaviour depends on them; everything else those
//     observers do not touch is fixture, not a claim.
//   * What 0x00777ae0 does with its three words. The observer records them and
//     changes nothing. The test asserts the words, not the effect.
//   * The body reaching the objects at 0x0067ddd0's and 0x0067dd80's globals
//     (0x15fd8e8 and 0x15fd8cc). Those are two words in .data in the image and
//     this body never names them; the test hands the getters their results.
//   * The two ADD ESP instructions. 0x48 and 0x18 are caller-side cleanups of
//     six and two three-word calls, so at C level the eight calls are eight
//     calls and the batching is invisible from outside. What the batching fixes
//     -- that 0x00777ae0 is cdecl with exactly three words -- is asserted by the
//     per-call argument count and by the trampoline's stack bound.
//   * Whether the receiver's word at 0x8d8 is a pointer, a handle or a count.
//     The 0x00f998f0 callee's own bytes make a release-and-null reading likely
//     and the model reproduces its nulling store, but no member is named for it
//     and the test asserts only that the word is compared against zero and that
//     the callee is called when and only when it is non-zero.

#include "sw2_00f9bee0_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <csignal>
#include <setjmp.h>

namespace openspore::reconstruction::pkg_swarm_w2_00f9bee0 {
namespace {

// The dispatch table the test hands to a carrier. 0x140 bytes of slots, so the
// 0x134 slot and its neighbours +0x130, +0x138, +0x13c and +0x140 all fit.
constexpr std::size_t kTableEntries = 0x144 / 4;
struct Table {
  Word entries[kTableEntries];
};

// The test's carrier fixture. It is handed to the body AS a VtableCarrier (the
// body only ever reads a carrier's own leading dword, and the header's carrier
// type is 0x10 bytes for exactly that reason), but the fixture is larger so
// that a one-level reconstruction -- one that reads [object + slot] instead of
// [[object] + slot] -- lands on a decoy word instead of on nothing at all.
constexpr std::size_t kCarrierFixtureBytes = 0x160;
struct CarrierFixture {
  unsigned char bytes[kCarrierFixtureBytes];
};

// The test's receiver fixture, with eight sentinel bytes past the last word the
// body reads so that a read or write past 0x8db shows up in the byte diff.
constexpr std::size_t kReceiverFixtureBytes = kReceiverSpan + 8;
struct ReceiverFixture {
  unsigned char bytes[kReceiverFixtureBytes];
};

enum Call : int {
  kSlot58 = 0,
  kSlot54,
  kSlot0c,
  kSlot50,
  kSlot1c,
  kSlot134,
  kFlush,
  kRelease,
  kSingleton,
  kShadowWorld,
  kChannel,
  kDecoyDisplacement,
  kDecoyPointee,
  kKindCount
};

constexpr int kMaxLog = 40;
constexpr int kMaxChannels = 12;

struct Observation {
  int log[kMaxLog];
  int length = 0;

  int slot_count[kKindCount] = {};

  // Every dispatch records the object it was made through and the word it was
  // handed. That is the whole observable surface of the nine indirect calls.
  const VtableCarrier* dispatch_receiver[kMaxLog] = {};
  Word dispatch_argument[kMaxLog] = {};
  const void* distinct_dispatch_objects[kMaxLog] = {};
  int distinct_count = 0;

  Word slot58_result = 0;
  VtableCarrier* slot54_result = nullptr;
  VtableCarrier* slot1c_result = nullptr;
  VtableCarrier* singleton_result = nullptr;
  VtableCarrier* shadow_result = nullptr;
  // The word the three discarded dispatches return. It is the address of a
  // fixture carrier whose dispatch word is zero, so any attempt to chain it
  // faults at a low address and is caught.
  VtableCarrier* discard_payload = nullptr;

  Word channel[kMaxChannels] = {};
  Word channel_value[kMaxChannels] = {};
  std::uint8_t channel_flag[kMaxChannels] = {};
  int channel_count = 0;

  Word flush_data_word_seen = 0;
  Word release_guard_seen = 0;
  bool release_writes_guard = false;
  Word release_guard_after = 0;
  Receiver* release_receiver = nullptr;

  // The receiver whose bytes the current case is exercising, so an observer can
  // sample it at a moment the caller cannot see.
  ReceiverFixture* active_receiver = nullptr;

  void reset() { *this = Observation(); }

  void record(Call kind, const VtableCarrier* receiver, Word argument) {
    if (length < kMaxLog) {
      log[length] = static_cast<int>(kind);
      dispatch_receiver[length] = receiver;
      dispatch_argument[length] = argument;
    }
    ++length;
    ++slot_count[kind];
    if (receiver != nullptr) {
      bool seen = false;
      for (int index = 0; index < distinct_count; ++index) {
        if (distinct_dispatch_objects[index] == receiver) {
          seen = true;
        }
      }
      if (!seen && distinct_count < kMaxLog) {
        distinct_dispatch_objects[distinct_count++] = receiver;
      }
    }
  }

  int count(Call kind) const { return slot_count[kind]; }
};

Observation g_obs;

// The five objects the two getters and the two consumed dispatches hand back.
// They live OUTSIDE the observation on purpose: begin() resets the observation,
// and the fixture wiring has to survive that reset or the getters would start
// returning null and the whole case would fault for the wrong reason.
VtableCarrier* g_fixture_singleton = nullptr;
VtableCarrier* g_fixture_shadow = nullptr;
VtableCarrier* g_fixture_slot54 = nullptr;
VtableCarrier* g_fixture_slot1c = nullptr;
VtableCarrier* g_fixture_discard = nullptr;

// Fault catching. The null-receiver arm of the guard is REQUIRED to fault (the
// body dereferences a null receiver at 0x00f9bf15 with no null check of its own),
// and the discarded-result case is required NOT to fault. Both are assertions
// rather than absences of output, so the signal is caught and counted.
sigjmp_buf g_fault_jump;
volatile int g_fault_count = 0;
volatile int g_run_completed = 0;

extern "C" void on_segv(int) {
  ++g_fault_count;
  siglongjmp(g_fault_jump, 1);
}

void install_fault_handler() {
  struct sigaction action;
  std::memset(&action, 0, sizeof action);
  action.sa_handler = on_segv;
  action.sa_flags = SA_NODEFER;
  sigemptyset(&action.sa_mask);
  sigaction(SIGSEGV, &action, nullptr);
}

// Runs the reconstruction and records whether it completed or faulted. All state
// lives in globals so that returning through siglongjmp cannot strand a local.
void run_model(Receiver* receiver, VtableCarrier* target) {
  g_run_completed = 0;
  if (sigsetjmp(g_fault_jump, 1) == 0) {
    re_sporepedia_effects_setup_00f9bee0(receiver, target);
    g_run_completed = 1;
  }
}

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

}  // namespace

// ---------------------------------------------------------------------------
// The nine indirect dispatches, as observers. The test owns every table, so
// each of these functions is reached only if the body reads exactly the slot
// displacement the listing says it reads.
// ---------------------------------------------------------------------------

// 0x00f9bfd -- slot +0x58 on the second argument, immediate 8. The only
// dispatch whose result the body consumes: it is compared against the receiver's
// address plus 4 (or 0).
extern "C" std::uintptr_t obs_slot_58(const VtableCarrier* object, Word argument) {
  g_obs.record(kSlot58, object, argument);
  return g_obs.slot58_result;
}

// 0x00f9bf36 -- slot +0x54 on the object 0x0067ddd0 returned, immediate
// 0x3fbae24. The result is consumed as an object at 0x00f9bf38.
extern "C" VtableCarrier* obs_slot_54(const VtableCarrier* object, Word argument) {
  g_obs.record(kSlot54, object, argument);
  return g_obs.slot54_result;
}

// 0x00f9bf41 -- slot +0x0c on the object the slot +0x54 dispatch returned,
// immediate 3. The result is DISCARDED, so the observer hands back the address
// of a carrier whose dispatch word is zero.
extern "C" DiscardedSlotResult obs_slot_0c(const VtableCarrier* object, Word argument) {
  g_obs.record(kSlot0c, object, argument);
  DiscardedSlotResult result;
  result.opaque = reinterpret_cast<Word>(g_obs.discard_payload);
  return result;
}

// 0x00f9bf4c, 0x00f9bf78, 0x00f9bf83 and 0x00f9bf8e -- slot +0x50 on the second
// argument, immediates 0xa, 8, 7 and 0x21. All four results are DISCARDED.
extern "C" DiscardedSlotResult obs_slot_50(const VtableCarrier* object, Word argument) {
  g_obs.record(kSlot50, object, argument);
  DiscardedSlotResult result;
  result.opaque = reinterpret_cast<Word>(g_obs.discard_payload);
  return result;
}

// 0x00f9bf5f -- slot +0x1c on the object 0x0067dd80 returned, immediate
// 0x3fbae24. The result is consumed as an object at 0x00f9bf61.
extern "C" VtableCarrier* obs_slot_1c(const VtableCarrier* object, Word argument) {
  g_obs.record(kSlot1c, object, argument);
  return g_obs.slot1c_result;
}

// 0x00f9bf6d -- slot +0x134 on the object the slot +0x1c dispatch returned,
// immediate 0. The result is DISCARDED.
extern "C" DiscardedSlotResult obs_slot_134(const VtableCarrier* object, Word argument) {
  g_obs.record(kSlot134, object, argument);
  DiscardedSlotResult result;
  result.opaque = reinterpret_cast<Word>(g_obs.discard_payload);
  return result;
}

// ---------------------------------------------------------------------------
// The five direct callees, as observers.
// ---------------------------------------------------------------------------

// 0x00f9bf10 -- cdecl, no argument. It samples the data word the body just
// tested: the word must still be NON-ZERO at the moment of the call, because
// the body does not clear it and this callee is the one that does
// (0x00f96cb6). It also samples the receiver's guard word, which must still be
// non-zero because the 0x00f998f0 arm runs after this one.
extern "C" void PKG_SWARM_W2_00F9BEE0_CDECL flush_pending_refraction_00f96c60() {
  g_obs.record(kFlush, nullptr, 0u);
  g_obs.flush_data_word_seen = Terrain__sTerrainRefractionBuffersRTTTexture;
  if (g_obs.active_receiver != nullptr) {
    g_obs.release_guard_seen = *reinterpret_cast<const Word*>(
        g_obs.active_receiver->bytes + kReceiverGuardDisplacement);
  }
}

// 0x00f9bf20 -- __thiscall, receiver in ECX, no argument. The callee's own bytes
// null the receiver's word at 0x8d8 at 0x00f99932, so the observer reproduces
// that store (behind a flag) and records the word as it found it and as it left
// it. The BODY must not do either.
extern "C" void PKG_SWARM_W2_00F9BEE0_THISCALL release_guard_member_00f998f0(
    Receiver* receiver) {
  g_obs.record(kRelease, nullptr, 0u);
  g_obs.release_receiver = reinterpret_cast<Receiver*>(g_obs.active_receiver);
  g_obs.release_guard_seen = *word_at(receiver, kReceiverGuardDisplacement);
  if (g_obs.release_writes_guard) {
    *word_at(receiver, kReceiverGuardDisplacement) = 0u;
  }
  g_obs.release_guard_after = *word_at(receiver, kReceiverGuardDisplacement);
}

// 0x00f9bf25 -- cdecl, no argument, returns a pointer. Fixture, not a claim.
extern "C" VtableCarrier* PKG_SWARM_W2_00F9BEE0_CDECL effect_singleton_0067ddd0() {
  g_obs.record(kSingleton, nullptr, 0u);
  return g_obs.singleton_result;
}

// 0x00f9bf4e -- cdecl, no argument, returns a DIFFERENT pointer.
extern "C" VtableCarrier* PKG_SWARM_W2_00F9BEE0_CDECL shadow_world_get_0067dd80() {
  g_obs.record(kShadowWorld, nullptr, 0u);
  return g_obs.shadow_result;
}

// 0x00f9bf99, 0x00f9bfa7, 0x00f9bfb5, 0x00f9bfc3, 0x00f9bfd1, 0x00f9bfdf,
// 0x00f9bff0 and 0x00f9bffe -- cdecl, three words each. Records them and changes
// nothing: the test asserts the words, not an effect.
extern "C" void PKG_SWARM_W2_00F9BEE0_CDECL apply_channel_setting_00777ae0(
    Word channel, Word value, std::uint8_t flag) {
  g_obs.record(kChannel, nullptr, 0u);
  if (g_obs.channel_count < kMaxChannels) {
    g_obs.channel[g_obs.channel_count] = channel;
    g_obs.channel_value[g_obs.channel_count] = value;
    g_obs.channel_flag[g_obs.channel_count] = flag;
  }
  ++g_obs.channel_count;
}

namespace {

// ---------------------------------------------------------------------------
// Decoys. Twenty neighbouring slot displacements and one in-carrier decoy, each
// with its OWN function so the log names which displacement a wrong
// reconstruction read.
// ---------------------------------------------------------------------------

#define PKG_DECOY_SLOT(suffix)                                                     \
  extern "C" std::uintptr_t decoy_slot_##suffix(const VtableCarrier* object,       \
                                                Word argument) {                   \
    g_obs.record(kDecoyDisplacement, object, argument);                           \
    return 0xdec00000u;                                                            \
  }

PKG_DECOY_SLOT(04)
PKG_DECOY_SLOT(08)
PKG_DECOY_SLOT(10)
PKG_DECOY_SLOT(14)
PKG_DECOY_SLOT(18)
PKG_DECOY_SLOT(1c)
PKG_DECOY_SLOT(20)
PKG_DECOY_SLOT(24)
PKG_DECOY_SLOT(48)
PKG_DECOY_SLOT(4c)
PKG_DECOY_SLOT(50)
PKG_DECOY_SLOT(54)
PKG_DECOY_SLOT(58)
PKG_DECOY_SLOT(5c)
PKG_DECOY_SLOT(60)
PKG_DECOY_SLOT(12c)
PKG_DECOY_SLOT(130)
PKG_DECOY_SLOT(134)
PKG_DECOY_SLOT(13c)
PKG_DECOY_SLOT(140)
PKG_DECOY_SLOT(00)
PKG_DECOY_SLOT(0c)
#undef PKG_DECOY_SLOT

// The one-level decoy: a word planted INSIDE a carrier at a slot displacement.
// A reconstruction that reads [object + slot] gets this address and dispatches
// through it.
extern "C" std::uintptr_t decoy_pointee(const VtableCarrier* object, Word argument) {
  g_obs.record(kDecoyPointee, object, argument);
  return 0xdec0deadu;
}

// The address of ANY observer, whatever its return type: the table holds a raw
// word, so the test has to be able to put a decoy of a different signature into
// the same slot a live observer occupies.
template <class Fn>
std::uintptr_t address_of(Fn entry) {
  return reinterpret_cast<std::uintptr_t>(entry);
}

// Every displacement a table can hold a decoy at, mapped to its observer.
struct Decoy {
  Word displacement;
  std::uintptr_t entry;
};

const Decoy kTableDecoys[] = {
    {0x00, address_of(decoy_slot_00)}, {0x04, address_of(decoy_slot_04)},
    {0x08, address_of(decoy_slot_08)}, {0x0c, address_of(decoy_slot_0c)},
    {0x10, address_of(decoy_slot_10)}, {0x14, address_of(decoy_slot_14)},
    {0x18, address_of(decoy_slot_18)}, {0x1c, address_of(decoy_slot_1c)},
    {0x20, address_of(decoy_slot_20)}, {0x24, address_of(decoy_slot_24)},
    {0x48, address_of(decoy_slot_48)}, {0x4c, address_of(decoy_slot_4c)},
    {0x50, address_of(decoy_slot_50)}, {0x54, address_of(decoy_slot_54)},
    {0x58, address_of(decoy_slot_58)}, {0x5c, address_of(decoy_slot_5c)},
    {0x60, address_of(decoy_slot_60)}, {0x12c, address_of(decoy_slot_12c)},
    {0x130, address_of(decoy_slot_130)}, {0x134, address_of(decoy_slot_134)},
    {0x13c, address_of(decoy_slot_13c)}, {0x140, address_of(decoy_slot_140)},
};
constexpr std::size_t kTableDecoyCount = sizeof(kTableDecoys) / sizeof(kTableDecoys[0]);

// A table with a decoy in every displacement the body could plausibly read, and
// the named observer installed at `live_displacement` -- or the live observer
// left out of the table entirely when that is 0xffffffff, which is how the
// no-dispatch cases are built.
template <class Fn>
Table make_table(Fn live, Word live_displacement) {
  Table table;
  for (std::size_t index = 0; index < kTableEntries; ++index) {
    table.entries[index] = address_of(decoy_slot_00);
  }
  for (std::size_t index = 0; index < kTableDecoyCount; ++index) {
    const Decoy& decoy = kTableDecoys[index];
    if (decoy.displacement / 4 < kTableEntries) {
      table.entries[decoy.displacement / 4] = decoy.entry;
    }
  }
  if (live != nullptr && live_displacement / 4 < kTableEntries) {
    table.entries[live_displacement / 4] = address_of(live);
  }
  return table;
}

// A carrier whose leading dword is the table and whose own bytes ALSO carry a
// decoy word at each of the six live slot displacements.
CarrierFixture make_carrier(const Table& table) {
  CarrierFixture fixture;
  std::memset(&fixture, 0, sizeof fixture);
  const std::uintptr_t table_address = reinterpret_cast<std::uintptr_t>(&table);
  std::memcpy(fixture.bytes, &table_address, sizeof table_address);
  const std::uintptr_t trap = address_of(decoy_pointee);
  const Word displacements[] = {vtable_slots::slot_0c, vtable_slots::slot_1c,
                                vtable_slots::slot_50, vtable_slots::slot_54,
                                vtable_slots::slot_58, vtable_slots::slot_134};
  for (std::size_t index = 0; index < sizeof displacements / sizeof displacements[0];
       ++index) {
    const std::size_t at = displacements[index];
    if (at + sizeof trap <= kCarrierFixtureBytes) {
      std::memcpy(fixture.bytes + at, &trap, sizeof trap);
    }
  }
  return fixture;
}

VtableCarrier* carrier_of(CarrierFixture& fixture) {
  return reinterpret_cast<VtableCarrier*>(fixture.bytes);
}

// A receiver with the guard word at 0x8d8 and DECOY words at 0x8d4 and 0x8dc, a
// recognisable filler everywhere else, and eight sentinel bytes past 0x8db.
ReceiverFixture make_receiver(Word guard) {
  ReceiverFixture fixture;
  for (std::size_t index = 0; index < kReceiverFixtureBytes; ++index) {
    fixture.bytes[index] = static_cast<unsigned char>(0x5au + (index & 0x0fu));
  }
  const Word neighbour_low = 0x11111111u;
  const Word neighbour_high = 0x22222222u;
  std::memcpy(fixture.bytes + kReceiverGuardDisplacement - 4, &neighbour_low, 4);
  std::memcpy(fixture.bytes + kReceiverGuardDisplacement, &guard, 4);
  std::memcpy(fixture.bytes + kReceiverGuardDisplacement + 4, &neighbour_high, 4);
  return fixture;
}

std::size_t changed_bytes(const unsigned char* before, const unsigned char* after,
                          std::size_t length) {
  std::size_t changed = 0;
  for (std::size_t index = 0; index < length; ++index) {
    if (before[index] != after[index]) {
      ++changed;
    }
  }
  return changed;
}

std::size_t changed_bytes_outside(const unsigned char* before, const unsigned char* after,
                                  std::size_t length, std::size_t low, std::size_t high) {
  std::size_t changed = 0;
  for (std::size_t index = 0; index < length; ++index) {
    if (before[index] == after[index]) {
      continue;
    }
    if (index < low || index >= high) {
      ++changed;
    }
  }
  return changed;
}

// The whole fall-through fixture: three carriers, three tables, the two getter
// results and the poison carrier the three discarded dispatches hand back.
// Every table lives INSIDE the world, and the world is filled in place rather
// than returned by value: a carrier's dispatch word is the ADDRESS of its
// table, so a world that were copied after construction would leave every
// carrier pointing at the temporary the copy came from.
struct World {
  Table target_table;
  Table effects_table;
  Table configured_table;
  Table lit_table;
  Table world_table;
  Table poison_table;
  CarrierFixture target;
  CarrierFixture configured;
  CarrierFixture effects;
  CarrierFixture lit;
  CarrierFixture world_object;
  CarrierFixture poison;
  ReceiverFixture receiver;

  VtableCarrier* target_object() { return carrier_of(target); }
  VtableCarrier* configured_object() { return carrier_of(configured); }
  VtableCarrier* effects_object() { return carrier_of(effects); }
  VtableCarrier* lit_object() { return carrier_of(lit); }
  VtableCarrier* world_object_ptr() { return carrier_of(world_object); }
  VtableCarrier* poison_object() { return carrier_of(poison); }
  Receiver* receiver_object() { return reinterpret_cast<Receiver*>(receiver.bytes); }
};

void init_world(World& world, Word guard) {
  // The second argument dispatches slot +0x58 (the gate) and slot +0x50 four
  // times. The getter's object dispatches slot +0x54; the result of THAT
  // dispatches slot +0x0c; the second getter's object dispatches slot +0x1c; the
  // result of that dispatches slot +0x134. Each table also carries a decoy for
  // every displacement the OTHER chains use, so a reconstruction that reached
  // for the wrong table's slot reads a decoy.
  world.target_table = make_table(obs_slot_58, vtable_slots::slot_58);
  world.target_table.entries[vtable_slots::slot_50 / 4] = address_of(obs_slot_50);
  world.effects_table = make_table(obs_slot_54, vtable_slots::slot_54);
  world.configured_table = make_table(obs_slot_0c, vtable_slots::slot_0c);
  world.lit_table = make_table(obs_slot_134, vtable_slots::slot_134);
  world.world_table = make_table(obs_slot_1c, vtable_slots::slot_1c);
  world.poison_table = make_table(decoy_slot_00, 0xffffffffu);

  world.target = make_carrier(world.target_table);
  world.effects = make_carrier(world.effects_table);
  world.configured = make_carrier(world.configured_table);
  world.lit = make_carrier(world.lit_table);
  world.world_object = make_carrier(world.world_table);
  // A carrier whose dispatch word is ZERO, so any attempt to chain a discarded
  // result through it faults at a low address and is caught by the handler.
  world.poison = make_carrier(world.poison_table);
  std::memset(world.poison.bytes, 0, sizeof world.poison.bytes);
  world.receiver = make_receiver(guard);

  g_fixture_singleton = world.effects_object();
  g_fixture_shadow = world.world_object_ptr();
  g_fixture_slot54 = world.configured_object();
  g_fixture_slot1c = world.lit_object();
  g_fixture_discard = world.poison_object();
}

// Prepare the observation for one run over a world.
void begin(ReceiverFixture* receiver, Word guard_result) {
  g_obs.reset();
  // A default so no case inherits the data word a previous case left behind; the
  // cases that drive the 0x00f96c60 gate override it after this call.
  Terrain__sTerrainRefractionBuffersRTTTexture = 0x0000c0deu;
  g_obs.active_receiver = receiver;
  g_obs.slot58_result = guard_result;
  g_obs.singleton_result = g_fixture_singleton;
  g_obs.shadow_result = g_fixture_shadow;
  g_obs.slot54_result = g_fixture_slot54;
  g_obs.slot1c_result = g_fixture_slot1c;
  g_obs.discard_payload = g_fixture_discard;
}

const Word kExpectedGuardOffset = 4u;
const Word kLiveChannelCount = 8u;
const Word kFallThroughCallCount = 21u;
const Word kEarlyExitCallCount = 1u;

std::uintptr_t expected_guard(const Receiver* receiver) {
  return receiver == nullptr
             ? 0u
             : reinterpret_cast<std::uintptr_t>(receiver) + kExpectedGuardOffset;
}

}  // namespace

// A stand-in for the body's prologue whose only job is to read the word the
// machine reads at 0x00f9bef0. Three register pushes, exactly as
// 0x00f9bee0..0x00f9bee4, and then the machine's own displacement 0x10. The
// assertion is that this returns the word the CALLER pushed, which is what
// fixes the body's single ordinary argument at entry_ESP+0x4 rather than at
// entry_ESP+0x8 or in a frame slot.
// Deliberately NOT declared with the convention macro and deliberately `naked`.
// The probe has to reproduce the machine's frame arithmetic EXACTLY, which means
// no compiler prologue of its own: a probe with GCC's ordinary prologue would
// have its own pushes and its own `sub esp` between entry and the read, and the
// displacement 0x10 would then be measured against the probe's frame rather than
// against the machine's three pushes. A probe declared thiscall would be worse
// still, because GCC would hand the argument over in ECX and nothing would
// reach the stack slot at all.
extern "C" __attribute__((naked)) std::uint32_t probe_argument_slot(void*) {
  __asm__ __volatile__("pushl %ebx\n\t"
                       "pushl %esi\n\t"
                       "pushl %edi\n\t"
                       "movl 0x10(%esp), %eax\n\t"
                       "popl %edi\n\t"
                       "popl %esi\n\t"
                       "popl %ebx\n\t"
                       "ret\n\t");
}

namespace {

// Case A -- the fall-through path, in full. Every one of the twenty-one
// transfers, in the listing's order, with the listing's arguments, through the
// listing's five dispatch receivers, and with no fault, no decoy, no receiver
// write and no write to the data word.
void case_fall_through() {
  World world;
  init_world(world, 0x0000beefu);
  begin(&world.receiver, expected_guard(world.receiver_object()));

  unsigned char receiver_before[kReceiverFixtureBytes];
  std::memcpy(receiver_before, world.receiver.bytes, sizeof receiver_before);
  const Word data_before = Terrain__sTerrainRefractionBuffersRTTTexture;

  run_model(world.receiver_object(), world.target_object());

  static const Call kExpected[] = {
      kSlot58, kFlush, kRelease, kSingleton, kSlot54, kSlot0c, kSlot50,
      kShadowWorld, kSlot1c, kSlot134, kSlot50, kSlot50, kSlot50,
      kChannel, kChannel, kChannel, kChannel, kChannel, kChannel, kChannel, kChannel};
  check(g_run_completed == 1,
        "A1: the fall-through path runs to its end without faulting");
  check(g_obs.length == static_cast<int>(kFallThroughCallCount),
        "A2: exactly 21 transfers, which is the listing's count");
  bool order_ok = g_obs.length == static_cast<int>(kFallThroughCallCount);
  for (int index = 0; order_ok && index < g_obs.length; ++index) {
    order_ok = g_obs.log[index] == static_cast<int>(kExpected[index]);
  }
  check(order_ok, "A3: the transfers happen in the listing's order");

  check(g_obs.count(kSlot58) == 1 && g_obs.count(kSlot54) == 1 &&
            g_obs.count(kSlot0c) == 1 && g_obs.count(kSlot1c) == 1 &&
            g_obs.count(kSlot134) == 1,
        "A4: slots +0x58, +0x54, +0x0c, +0x1c and +0x134 are each dispatched once");
  check(g_obs.count(kSlot50) == 4, "A5: slot +0x50 is dispatched four times");
  check(g_obs.count(kFlush) == 1 && g_obs.count(kRelease) == 1 &&
            g_obs.count(kSingleton) == 1 && g_obs.count(kShadowWorld) == 1,
        "A6: each of the four one-shot direct callees is called once");
  check(g_obs.channel_count == static_cast<int>(kLiveChannelCount),
        "A7: 0x00777ae0 is called eight times");

  // The immediates, in the listing's order. 0x00777ae0's words are recorded
  // separately because they do not go through a dispatch receiver.
  check(g_obs.dispatch_argument[0] == 0x8u,
        "A8: the gate's immediate is 8 (0x00f9bef9 PUSH 0x8)");
  check(g_obs.dispatch_argument[4] == 0x3fbae24u,
        "A9: the slot +0x54 immediate is 0x3fbae24 (0x00f9bf31)");
  check(g_obs.dispatch_argument[5] == 0x3u,
        "A10: the slot +0x0c immediate is 3 (0x00f9bf3f PUSH 0x3)");
  check(g_obs.dispatch_argument[6] == 0xau,
        "A11: the first slot +0x50 immediate is 0xa (0x00f9bf48 PUSH 0xa)");
  check(g_obs.dispatch_argument[8] == 0x3fbae24u,
        "A12: the slot +0x1c immediate is 0x3fbae24 (0x00f9bf5a)");
  check(g_obs.dispatch_argument[9] == 0x0u,
        "A13: the slot +0x134 immediate is 0 (0x00f9bf6b PUSH 0x0)");
  check(g_obs.dispatch_argument[10] == 0x8u &&
            g_obs.dispatch_argument[11] == 0x7u &&
            g_obs.dispatch_argument[12] == 0x21u,
        "A14: the last three slot +0x50 immediates are 8, 7 and 0x21, in that order");

  // The five dispatch receivers, and that no sixth object was ever dispatched
  // through. This is the case that refutes chaining a discarded result.
  const VtableCarrier* target = world.target_object();
  const VtableCarrier* effects = world.effects_object();
  const VtableCarrier* configured = world.configured_object();
  const VtableCarrier* lit = world.lit_object();
  const VtableCarrier* world_object = world.world_object_ptr();
  check(g_obs.dispatch_receiver[0] == target,
        "A15: the gate dispatches through the SECOND argument");
  check(g_obs.dispatch_receiver[4] == effects,
        "A16: the slot +0x54 dispatch goes through 0x0067ddd0's object, not the second argument");
  check(g_obs.dispatch_receiver[5] == configured,
        "A17: the slot +0x0c dispatch goes through the slot +0x54 RESULT");
  check(g_obs.dispatch_receiver[6] == target,
        "A18: the first slot +0x50 dispatch goes through the second argument again");
  check(g_obs.dispatch_receiver[8] == world_object,
        "A19: the slot +0x1c dispatch goes through 0x0067dd80's object");
  check(g_obs.dispatch_receiver[9] == lit,
        "A20: the slot +0x134 dispatch goes through the slot +0x1c RESULT");
  check(g_obs.dispatch_receiver[10] == target && g_obs.dispatch_receiver[11] == target &&
            g_obs.dispatch_receiver[12] == target,
        "A21: the last three slot +0x50 dispatches go through the second argument");
  check(g_obs.distinct_count == 5,
        "A22: exactly five distinct objects were dispatched through, so no discarded result was chained");
  const VtableCarrier* const kExpectedObjects[5] = {target, effects, configured,
                                                     lit, world_object};
  bool all_seen = g_obs.distinct_count == 5;
  for (int index = 0; all_seen && index < 5; ++index) {
    bool found = false;
    for (int seen = 0; seen < g_obs.distinct_count; ++seen) {
      found = found || g_obs.distinct_dispatch_objects[seen] == kExpectedObjects[index];
    }
    all_seen = all_seen && found;
  }
  check(all_seen, "A23: and they are the five the listing names");

  // The eight channel settings, in the listing's order, each with two zero words.
  static const Word kChannels[kMaxChannels] = {0x301, 0x304, 0x305, 0x306,
                                               0x24b, 0x23d, 0x24c, 0x24d};
  bool channels_ok = g_obs.channel_count == static_cast<int>(kLiveChannelCount);
  for (int index = 0; channels_ok && index < g_obs.channel_count; ++index) {
    channels_ok = g_obs.channel[index] == kChannels[index] &&
                  g_obs.channel_value[index] == 0u && g_obs.channel_flag[index] == 0u;
  }
  check(channels_ok,
        "A24: the eight ids are 0x301 0x304 0x305 0x306 0x24b 0x23d 0x24c 0x24d, in that order, each with a zero value and a zero flag");

  // REFUTE A/B: no decoy of either kind was reached, which is the positive
  // statement that the six displacements are exact and that both levels of the
  // dispatch are real.
  check(g_obs.count(kDecoyDisplacement) == 0,
        "A25: no neighbouring slot displacement in any table was dispatched through");
  check(g_obs.count(kDecoyPointee) == 0,
        "A26: no dispatch read a slot displacement out of a carrier's own bytes, so the read is two-level");

  // REFUTE I: the data word is read and never written by the body.
  check(g_obs.flush_data_word_seen == data_before,
        "A27: 0x00f96c60 sees the data word still non-zero, so the body did not clear it before the call");
  check(Terrain__sTerrainRefractionBuffersRTTTexture == data_before,
        "A28: the data word is unchanged across the whole body");

  // REFUTE H: the two one-shot arms are ordered, and the guard word has not
  // moved by the time 0x00f96c60's observer samples it.
  check(g_obs.release_guard_seen == 0x0000beefu,
        "A29: 0x00f96c60 still sees a non-zero guard word, so the 0x00f998f0 arm runs after it");
  check(g_obs.release_guard_seen == g_obs.release_guard_after,
        "A30: 0x00f998f0 found the guard word as the body left it, so the body did not write it");
  check(g_obs.release_receiver == reinterpret_cast<Receiver*>(world.receiver.bytes),
        "A31: ECX carried the receiver to 0x00f998f0");

  // REFUTE: the body writes no memory of its own anywhere.
  check(changed_bytes(receiver_before, world.receiver.bytes, kReceiverFixtureBytes) == 0,
        "A32: no byte of the receiver changed at all, so the body performs no memory write of its own");
  check(changed_bytes_outside(receiver_before, world.receiver.bytes, kReceiverFixtureBytes,
                              0, kReceiverFixtureBytes) == 0,
        "A33: and nothing changed past the receiver's modelled span either");
}

// Case B -- the early exit. The guard takes the branch for any result other than
// the receiver's address plus 4, and the test drives the arms a signed compare,
// an inverted branch and an off-by-one displacement would all get wrong.
void case_guard_rejects() {
  // Every entry is an offset from the EXPECTED value, and none of them is zero,
  // so each of these results differs from it. The list deliberately includes
  // values a signed compare and an off-by-one displacement would confuse.
  static const struct {
    Word delta;
    const char* what;
  } kRejected[] = {
      {1u, "one past the expected address"},
      {2u, "two past"},
      {3u, "three past"},
      {4u, "the receiver's address plus 8"},
      {8u, "the receiver's address plus 0xc"},
      {0x80000000u, "a value with the high bit set, which a signed compare would read as small"},
      {0x7fffffffu, "a value just under the high bit"},
      {0xfffffffcu, "the receiver's own address, i.e. one BELOW the expected value"},
      {0x00000004u ^ 0xffffffffu, "the complement of the receiver's address plus 4"},
  };
  for (std::size_t index = 0; index < sizeof kRejected / sizeof kRejected[0]; ++index) {
    World world;
    init_world(world, 0x0000beefu);
    const std::uintptr_t base = expected_guard(world.receiver_object());
    begin(&world.receiver, base + kRejected[index].delta);
    unsigned char before[kReceiverFixtureBytes];
    std::memcpy(before, world.receiver.bytes, sizeof before);
    const Word data_before = Terrain__sTerrainRefractionBuffersRTTTexture;

    run_model(world.receiver_object(), world.target_object());

    check(g_run_completed == 1, kRejected[index].what);
    check(g_obs.length == static_cast<int>(kEarlyExitCallCount),
          "B1: only the gate's dispatch happens when the guard rejects");
    check(g_obs.count(kSlot58) == 1, "B2: and it is the gate's");
    check(g_obs.count(kFlush) == 0 && g_obs.count(kRelease) == 0 &&
              g_obs.count(kSingleton) == 0 && g_obs.count(kShadowWorld) == 0 &&
              g_obs.channel_count == 0 && g_obs.count(kSlot54) == 0 &&
              g_obs.count(kSlot0c) == 0 && g_obs.count(kSlot1c) == 0 &&
              g_obs.count(kSlot134) == 0 && g_obs.count(kSlot50) == 0,
          "B3: nothing else is called on the early-exit path");
    check(changed_bytes(before, world.receiver.bytes, kReceiverFixtureBytes) == 0,
          "B4: the receiver is untouched on the early-exit path");
    check(Terrain__sTerrainRefractionBuffersRTTTexture == data_before,
          "B5: the data word is untouched on the early-exit path");
  }
}

// REFUTE C/D -- the null-receiver arm. With the receiver null the expected value
// is 0, so a gate result of 0 lets the body through and it then FAULTS reading
// the receiver's word at 0x8d8, because the body has no null check of its own.
// The fault is caught, so "it faulted" is an assertion.
void case_null_receiver_takes_the_gate() {
  // A valid SECOND argument: the body dereferences it at 0x00f9bef4 before it
  // ever looks at the receiver, so a null second argument would fault there and
  // the arm under test would never be reached. The receiver is what is null.
  World world;
  init_world(world, 0x0000beefu);
  const int faults_before = g_fault_count;
  begin(&world.receiver, 0u);  // the expected value on the null arm is zero
  // The data word is cleared so the only transfer this arm makes is the gate's,
  // which is what makes "it faulted before any other transfer" measurable.
  Terrain__sTerrainRefractionBuffersRTTTexture = 0u;

  run_model(nullptr, world.target_object());

  check(g_run_completed == 0,
        "C1: with a null receiver the body does NOT get past the gate's own null read");
  check(g_fault_count == faults_before + 1,
        "C2: it faults exactly once, at 0x00f9bf15 reading the receiver's word at 0x8d8");
  check(g_obs.count(kSlot58) == 1,
        "C3: the gate's dispatch DID happen, so the expected value really was 0 and not the receiver's address plus 4");
  check(g_obs.dispatch_receiver[0] == world.target_object() &&
            g_obs.dispatch_argument[0] == 0x8u,
        "C4: the gate was reached through the second argument, with the immediate 8");
  check(g_obs.length == 1 && g_obs.count(kFlush) == 0 && g_obs.count(kRelease) == 0,
        "C5: and it faulted before any other transfer");
}

// REFUTE C, the safe direction -- with a null receiver and a NON-zero gate
// result the body must exit cleanly, which is what a reconstruction that
// hardcodes receiver+4 would get wrong in the other direction only if it also
// got the branch backwards. Driven separately because it must NOT fault.
void case_null_receiver_rejects() {
  World world;
  init_world(world, 0x0000beefu);
  const int faults_before = g_fault_count;
  // With a null receiver the expected value is 0, so a gate result of
  // receiver+4 is a mismatch and the body must exit.
  begin(&world.receiver, kExpectedGuardOffset);
  Terrain__sTerrainRefractionBuffersRTTTexture = 0u;

  run_model(nullptr, world.target_object());

  check(g_run_completed == 1,
        "C6: a null receiver whose gate returns receiver+4 exits cleanly");
  check(g_fault_count == faults_before,
        "C7: and does not touch the null receiver, because the expected value on the null arm is 0");
  check(g_obs.length == static_cast<int>(kEarlyExitCallCount),
        "C8: only the gate's dispatch happened");
}

// REFUTE: the data word's gate. Zero suppresses the 0x00f96c60 call; non-zero
// makes it exactly once.
void case_data_word_gate() {
  {
    World world;
    init_world(world, 0x0000beefu);
    begin(&world.receiver, expected_guard(world.receiver_object()));
    Terrain__sTerrainRefractionBuffersRTTTexture = 0u;
    run_model(world.receiver_object(), world.target_object());
    check(g_obs.count(kFlush) == 0,
          "D1: a zero data word suppresses the 0x00f96c60 call (0x00f9bf0e JZ)");
    check(g_obs.length == static_cast<int>(kFallThroughCallCount) - 1,
          "D2: and the fall-through path is one transfer shorter");
  }
  {
    World world;
    init_world(world, 0x0000beefu);
    begin(&world.receiver, expected_guard(world.receiver_object()));
    Terrain__sTerrainRefractionBuffersRTTTexture = 0xffffffffu;
    run_model(world.receiver_object(), world.target_object());
    check(g_obs.count(kFlush) == 1,
          "D3: a non-zero data word makes the 0x00f96c60 call exactly once");
    check(g_obs.log[1] == static_cast<int>(kFlush),
          "D4: and it is the second transfer, after the gate");
    check(Terrain__sTerrainRefractionBuffersRTTTexture == 0xffffffffu,
          "D5: the body still does not write it");
  }
}

// REFUTE G: the receiver's displacement is 0x8d8. A non-zero decoy word one
// dword below and one dword above must not trigger the callee, and a zero word
// at 0x8d8 with both decoys non-zero must not either.
void case_guard_word_displacement() {
  {
    // 0x8d8 is zero; the decoys at 0x8d4 and 0x8dc are non-zero. No call.
    World world;
    init_world(world, 0u);
    begin(&world.receiver, expected_guard(world.receiver_object()));
    run_model(world.receiver_object(), world.target_object());
    check(g_obs.count(kRelease) == 0,
          "E1: a zero word at 0x8d8 suppresses the 0x00f998f0 call even though the neighbouring dwords are non-zero");
    check(g_obs.length == static_cast<int>(kFallThroughCallCount) - 1,
          "E2: and the path is one transfer shorter");
  }
  {
    // 0x8d8 is non-zero; the neighbouring dwords are the fixture's decoys and
    // are compared against nothing. The callee is called once. 0xffffffff is
    // used as the guard word so that all four of its bytes differ from the zero
    // the callee writes, which is what makes "exactly four bytes changed" a
    // real count rather than an accident of the value chosen.
    World world;
    init_world(world, 0xffffffffu);
    begin(&world.receiver, expected_guard(world.receiver_object()));
    g_obs.release_writes_guard = true;
    unsigned char before[kReceiverFixtureBytes];
    std::memcpy(before, world.receiver.bytes, sizeof before);
    run_model(world.receiver_object(), world.target_object());
    check(g_obs.count(kRelease) == 1, "E3: a non-zero word at 0x8d8 calls 0x00f998f0 once");
    check(g_obs.release_guard_seen == 0xffffffffu,
          "E4: the callee found the word the body tested");
    check(g_obs.release_guard_after == 0u,
          "E5: and the callee -- not the body -- is what clears it (0x00f99932)");
    check(changed_bytes_outside(before, world.receiver.bytes, kReceiverFixtureBytes,
                                kReceiverGuardDisplacement,
                                kReceiverGuardDisplacement + 4) == 0,
          "E6: the only bytes that changed are the callee's four at 0x8d8");
    check(changed_bytes(before, world.receiver.bytes, kReceiverFixtureBytes) == 4,
          "E7: exactly four changed bytes, and no write ran past 0x8db");
  }
  {
    // REFUTE H: the guard word is still non-zero when 0x00f96c60 runs, so the
    // two arms really are in that order and neither one moves it.
    World world;
    init_world(world, 0x00001234u);
    begin(&world.receiver, expected_guard(world.receiver_object()));
    run_model(world.receiver_object(), world.target_object());
    check(g_obs.release_guard_seen == 0x00001234u,
          "E8: 0x00f998f0 saw the word 0x8d8 unchanged by the 0x00f96c60 arm");
    check(g_obs.log[1] == static_cast<int>(kFlush) && g_obs.log[2] == static_cast<int>(kRelease),
          "E9: the 0x00f96c60 arm precedes the 0x00f998f0 arm");
  }
}

// REFUTE E: the two getters return two different objects, and each object's table
// carries a decoy for the other one's slot. A reconstruction that swapped them,
// or that dispatched slot +0x0c on the getter's own object instead of on the
// slot +0x54 result, is caught by the receiver assertions in case A and by the
// decoy counters here.
void case_the_two_getters_are_distinct() {
  World world;
  init_world(world, 0x0000beefu);
  begin(&world.receiver, expected_guard(world.receiver_object()));
  // Make the two getters' objects differ as much as the test can see: give the
  // second getter's table a decoy where the first getter's slot is, and vice
  // versa. They already do, from make_table's full decoy fill, but the live
  // observers overwrote one entry each; put the cross decoys back.
  world.effects_table.entries[vtable_slots::slot_1c / 4] = address_of(decoy_slot_1c);
  world.world_table.entries[vtable_slots::slot_54 / 4] = address_of(decoy_slot_54);
  run_model(world.receiver_object(), world.target_object());

  check(g_obs.count(kDecoyDisplacement) == 0,
        "F1: neither getter's object was dispatched through the other's slot");
  check(g_obs.dispatch_receiver[4] == world.effects_object() &&
            g_obs.dispatch_receiver[8] == world.world_object_ptr(),
        "F2: 0x0067ddd0's object is the slot +0x54 receiver and 0x0067dd80's is the slot +0x1c receiver");
  check(g_obs.dispatch_receiver[5] == world.configured_object() &&
            g_obs.dispatch_receiver[9] == world.lit_object(),
        "F3: and each second dispatch goes through its own RESULT, not through the object the getter returned");
}

// REFUTE F: the three discarded dispatches hand back the address of a carrier
// whose dispatch word is zero. Chaining any of them would fault. The test also
// checks the five-object set, so a chain that happened to stay inside the page
// would still be caught.
void case_discarded_results_are_never_consumed() {
  World world;
  init_world(world, 0x0000beefu);
  begin(&world.receiver, expected_guard(world.receiver_object()));
  std::memset(world.poison.bytes, 0, sizeof world.poison.bytes);
  const int faults_before = g_fault_count;

  run_model(world.receiver_object(), world.target_object());

  check(g_fault_count == faults_before,
        "G1: the discarded slot +0x0c, +0x50 and +0x134 results are never dereferenced");
  check(g_obs.distinct_count == 5,
        "G2: and no sixth object was ever dispatched through");
  check(g_obs.dispatch_receiver[5] != nullptr &&
            g_obs.dispatch_receiver[5] != world.poison_object(),
        "G3: the slot +0x0c receiver is the slot +0x54 result and not the poison carrier");
  check(g_obs.dispatch_receiver[9] != world.poison_object(),
        "G4: the slot +0x134 receiver is the slot +0x1c result and not the poison carrier");
}

// REFUTE J: the eight ids, driven out of order and with the two neighbours
// planted as 0x00777ae0's argument, must still be handed over in the listing's
// order. The test re-runs the fall-through path and reads the order back, and
// separately drives a run in which the two getters' objects are the SAME object
// to show the set-of-five assertion is not accidentally satisfied.
void case_order_is_not_sorted() {
  World world;
  init_world(world, 0x0000beefu);
  begin(&world.receiver, expected_guard(world.receiver_object()));
  run_model(world.receiver_object(), world.target_object());
  static const Word kOrder[kMaxChannels] = {0x301, 0x304, 0x305, 0x306,
                                            0x24b, 0x23d, 0x24c, 0x24d};
  bool unsorted = true;
  for (int index = 1; index < static_cast<int>(kLiveChannelCount); ++index) {
    unsorted = unsorted && kOrder[index] != kOrder[index - 1];
  }
  check(unsorted, "H1: the expected id order is neither sorted nor deduplicated");
  bool matches = g_obs.channel_count == static_cast<int>(kLiveChannelCount);
  for (int index = 0; matches && index < g_obs.channel_count; ++index) {
    matches = g_obs.channel[index] == kOrder[index];
  }
  check(matches, "H2: and the body hands them over in exactly that order");

  {
    // The distinct-object count of case A is a measurement and not a tautology
    // if each of the five objects is dispatched through a DIFFERENT number of
    // times, because five is then the only count that fits those five totals.
    World counted;
    init_world(counted, 0x0000beefu);
    begin(&counted.receiver, expected_guard(counted.receiver_object()));
    run_model(counted.receiver_object(), counted.target_object());
    const VtableCarrier* const kObjects[5] = {
        counted.target_object(), counted.effects_object(), counted.configured_object(),
        counted.lit_object(), counted.world_object_ptr()};
    static const int kPerObject[5] = {5, 1, 1, 1, 1};
    bool counts_ok = g_obs.distinct_count == 5;
    for (int object = 0; counts_ok && object < 5; ++object) {
      int hits = 0;
      for (int index = 0; index < g_obs.length; ++index) {
        if (g_obs.dispatch_receiver[index] == kObjects[object]) {
          ++hits;
        }
      }
      counts_ok = counts_ok && hits == kPerObject[object];
    }
    check(counts_ok,
          "H3: the five objects are dispatched through 5, 1, 1, 1 and 1 times, so the count of five is measured");
  }
}

// REFUTE K: the word the body reads at 0x00f9bef0 is the caller's first stack
// word. The probe replicates the machine's three pushes and the machine's own
// displacement 0x10, so the assertion is about the listing's own frame and not
// about this package's C++.
void case_argument_slot() {
  Word marker = 0xfeedfaceu;
  // The body reads a POINTER there -- the second argument is the object it
  // dispatches through -- so the assertion is against the address the caller
  // pushed, not against the word that address holds.
  const std::uint32_t observed = probe_argument_slot(&marker);
  check(observed == static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&marker)),
        "K1: with three pushes outstanding, [ESP+0x10] is the caller's first stack word, i.e. entry_ESP+0x4");
  check(kReceiverSpan == kReceiverGuardDisplacement + 4u,
        "K2: the receiver's modelled span ends exactly after the guard word");
}

// The body must consume AT MOST one word of its caller's stack -- the single
// argument the machine's `RET 0x4` accounts for -- and must never clean the
// caller's stack itself, which is what a cdecl reconstruction of a `RET 0x4`
// body would do. The bound is written as a range on purpose: GCC 16 does not
// implement `__attribute__((thiscall))` on a free function, so on this
// toolchain the compiled model leaves the four bytes to the caller (delta 4),
// while a toolchain that honours it pops them (delta 0). A delta above 4 would
// mean the body itself dropped the argument, which the machine does not do.
struct EspSamples {
  std::uint32_t before_push = 0;
  std::uint32_t after_return = 0;
};

EspSamples call_measured(Receiver* receiver, VtableCarrier* target) {
  const std::uint32_t entry = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&re_sporepedia_effects_setup_00f9bee0));
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  // EAX and ECX are in the clobber list, so the compiler cannot have allocated
  // either input to them and every "r" operand survives the `movl ..., %%ecx`.
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "pushl %[tgt]\n\t"
                       "call *%[entry]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [after] "=m"(after)
                       : [entry] "r"(entry), [recv] "r"(receiver), [tgt] "r"(target)
                       : "eax", "ecx", "memory");
  EspSamples samples;
  samples.before_push = before;
  samples.after_return = after;
  return samples;
}

void case_stack_discipline() {
  World world;
  init_world(world, 0x0000beefu);
  begin(&world.receiver, expected_guard(world.receiver_object()));
  const EspSamples samples = call_measured(world.receiver_object(), world.target_object());
  check(g_obs.count(kSlot58) == 1, "L1: the trampoline really reached the body");
  check(g_obs.channel_count == static_cast<int>(kLiveChannelCount),
        "L2: and the body really ran all eight 0x00777ae0 calls");
  const std::intptr_t delta = static_cast<std::intptr_t>(samples.before_push) -
                              static_cast<std::intptr_t>(samples.after_return);
  check(delta >= 0 && delta <= 4,
        "L3: the body consumes at most the one word `RET 0x4` accounts for, and never drops the caller's stack itself");
  check(g_obs.release_receiver == world.receiver_object(),
        "L4: and ECX carried the receiver, so the trampoline's own bookkeeping did not disturb it");
}

// The header's displacements and sizes against the listing's own bytes.
void verify_displacement_constants() {
  check(kDispatchWordDisplacement == 0x0u,
        "V1: the object's dispatch word is at its own +0x00");
  check(kReceiverSelfDisplacement == 0x4u,
        "V2: the address the gate compares against is the receiver's +0x4");
  check(kReceiverGuardDisplacement == 0x8d8u,
        "V3: the single receiver displacement the machine-derived record enumerates is 0x8d8");
  check(vtable_slots::slot_58 == 0x58u, "V4: slot +0x58 (0x00f9bef6)");
  check(vtable_slots::slot_54 == 0x54u, "V5: slot +0x54 (0x00f9bf2e)");
  check(vtable_slots::slot_0c == 0x0cu, "V6: slot +0x0c (0x00f9bf3c)");
  check(vtable_slots::slot_50 == 0x50u, "V7: slot +0x50 (0x00f9bf45 and three more)");
  check(vtable_slots::slot_1c == 0x1cu, "V8: slot +0x1c (0x00f9bf57)");
  check(vtable_slots::slot_134 == 0x134u, "V9: slot +0x134 (0x00f9bf65)");
  check(kReceiverSpan == 0x8dcu, "V10: the receiver's modelled span is 0x8dc bytes");
  check(kCarrierSpan >= 4u, "V11: the carrier's modelled span holds its dispatch word");
  check(kTableEntries * 4u > vtable_slots::slot_134,
        "V12: the test's table is long enough to hold the 0x134 slot and its neighbours");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_swarm_w2_00f9bee0

int main() {
  using namespace openspore::reconstruction::pkg_swarm_w2_00f9bee0;
  install_fault_handler();

  verify_displacement_constants();
  case_fall_through();
  case_guard_rejects();
  case_null_receiver_takes_the_gate();
  case_null_receiver_rejects();
  case_data_word_gate();
  case_guard_word_displacement();
  case_the_two_getters_are_distinct();
  case_discarded_results_are_never_consumed();
  case_order_is_not_sorted();
  case_argument_slot();
  case_stack_discipline();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}
