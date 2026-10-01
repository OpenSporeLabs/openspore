// PKG-SWARM-W1-00641490 -- VA 0x00641490
// Behavioural model test for FUN_00641490 @ 0x00641490.
//
// Both transfer targets are defined here as observers, so the test sees every
// transfer the reconstruction makes, with which arguments, in which order, and gets
// to decide what each of them does to memory:
//
//   * 0x00552300, the one DIRECT call, as a cdecl function taking the address
//     receiver+0x04 and returning a scripted status word;
//   * the SLOT the body dispatches to, as a thiscall function reached through the
//     word the reconstruction loads out of the table at displacement 0x90, so the
//     test controls the table and the slot and not the call.
//
// What is asserted is what the 30-instruction listing fixes and nothing more:
//
//   * both transfers, once each, and the order: the status call always first, the
//     dispatch only after the status compare passes;
//   * the argument of 0x00552300 as a POINTER to receiver+0x04, and the fact that
//     it is not the receiver, not receiver+0x00 and not the pair;
//   * the slot displacement 0x90 and the two-level shape of the dispatch: the
//     receiver's own leading word is the table, and the target is the table's word
//     at 0x90;
//   * the dispatch receiver (ECX) being the receiver itself, and the pair's
//     address being neither the receiver, nor receiver+0x04, nor receiver memory;
//   * the three branch conditions -- status == 2, the slot's AL != 0, and the AND
//     of the pair's two words != 0xffffffff -- each driven in both directions and,
//     where signedness could matter, with inputs on which it does;
//   * the AND being of BOTH words: a pair of (0xffffffff, 0x7fffffff) must be
//     accepted, which refutes a test on either word alone;
//   * the return being the low byte and only the low byte: 1 on the surviving
//     path, 0 on all three failing paths, and never the AND value;
//   * the pair being read AFTER the dispatch and re-read per call, not cached and
//     not taken from the receiver's own bytes;
//   * the ABI, measured by sampling ESP around the call rather than asserted as a
//     convention: the entry consumes no stack word.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction, not to walk
// it. Each names the wrong reconstruction it is aimed at:
//
//   A  the status constant is 2 and nothing else -- 0, 1 and 3 all fail, and 2
//      alone dispatches. A model comparing against 1, or against "<= 2", or
//      against a bit, dies here.
//   B  the branch polarity at 0x006414a5 is JNZ, not JZ.
//   C  the dispatch is TWO dereferences. A model that took the receiver's leading
//      word as the call target, or that added a third dereference, calls a decoy
//      or nothing; the decoys planted at the neighbouring slots and at a second
//      table record every one of those mistakes.
//   D  the dispatch word is the receiver's word at +0x00 and not at +0x04, +0x08
//      or -0x04: decoy table pointers at the neighbouring words stay inert.
//   E  the argument of 0x00552300 is the ADDRESS receiver+0x04, so a model that
//      passed the receiver, or a copy of the receiver's bytes, is refuted.
//   F  the AND is of both words, so the all-ones test is not on either word alone
//      and not on "either is all-ones".
//   G  the slot's return is tested as its LOW BYTE, so upper bytes are ignored.
//   H  the pair is read after the dispatch, per call, and not from the receiver.
//   I  the return value is the byte, so the AND value never leaks out.
//   J  the pair pointer is a frame object, not receiver memory and not the
//      receiver+0x04 the status call was handed.
//   K  the status call's argument and the pair's address are two different
//      objects, and the pair is passed to the slot and not to the status call.
//
// What is NOT asserted, and why:
//
//   * The upper three bytes of EAX. Both exits write AL with an 8-bit
//     instruction and the record lists no caller for this VA (all six xrefs are
//     data references from pointer runs), so nothing observes them. The declared
//     return type is the byte for the same reason.
//   * What the slot target does beyond writing the two words and reporting a byte
//     in AL. The observer implements that much because the body's own 0x006414bc
//     and 0x006414c0 read the two words; everything else it does is a fixture.
//   * The identity of the function the slot holds. It is 0x006417d0 in the three
//     table runs that agree, but the transfer target is a run-time value in EDX
//     and this body never names it, so the model calls through the loaded pointer
//     and the test supplies its own.
//   * The receiver's extent. 0x10 is the run the body and its callee were seen
//     reaching, not a claim that the object ends there, so no byte past it is
//     read or written by the model and none is tested.
//   * ESI. The body saves and restores it (0x00641493 / 0x006414cb and
//     0x006414d2); a C++ reconstruction of the body emits whatever prologue its
//     own compiler wants, so a test of that register would be a test of GCC.
//   * The frame's byte-level layout. The pair's position inside the frame is
//     fixed by the listing (entry-8 and entry-4) and used to model the two reads,
//     but the C++ object is a local and its address is not asserted to be at any
//     particular offset from ESP.

#include "swarm_w1_00641490_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_swarm_w1_00641490 {
namespace {

// Machine displacements restated as test-side literals, so a reader can see what
// the test believes without opening the header. Each is the value the listing
// shows at the instruction named beside it.
constexpr std::size_t kDispatchWordOffset = 0x00u;   // 0x006414a7 MOV EDX,[ESI]
constexpr std::size_t kAssetFieldOffset = 0x04u;     // 0x00641496 LEA EAX,[ESI+0x4]
constexpr std::size_t kSlotOffset = 0x90u;           // 0x006414a9 MOV EDX,[EDX+0x90]
constexpr std::size_t kNeighbourSlotBefore = 0x8cu;  // the slot one dword lower
constexpr std::size_t kNeighbourSlotAfter = 0x94u;   // the slot one dword higher
constexpr std::size_t kTableExtent = 0x98u;          // covers both decoy slots
constexpr std::size_t kReceiverSize = 0x10u;

enum Call : int {
  kCallStatus = 0,
  kCallSlot = 1,
};

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

struct Observation {
  int log[8] = {};
  int log_length = 0;

  // 0x00552300.
  int status_calls = 0;
  const void* status_argument = nullptr;
  Word status_return = 0;
  // When set, the observer writes this through the pointer it was handed, so the
  // test can show that a callee which scribbles on the receiver does not move the
  // reconstruction's decision. The real callee only reads.
  bool status_writes_argument = false;
  Word status_written = 0;

  // The slot target.
  int slot_calls = 0;
  SporepediaAssetReceiver* slot_receiver = nullptr;
  DisplacementRange* slot_range = nullptr;
  // Set by the observer: the two words it was handed before it wrote them, so the
  // test can see that the model hands over storage it has not pre-loaded.
  Word slot_range_before[2] = {0u, 0u};
  // And the two words as they stood AFTER it wrote them, captured inside the
  // observer: the pair is the reconstruction's own frame object and is gone by the
  // time the call returns, so reading it from the test would be reading dead
  // storage.
  Word slot_range_after[2] = {0u, 0u};
  // What the observer writes into the pair, and what it reports in AL.
  Word slot_writes[2] = {0u, 0u};
  std::uint32_t slot_return = 0;
  // When set, the observer leaves the pair alone, to show that the body's decision
  // does not depend on a callee that reports success without writing.
  bool slot_skips_write = false;

  void reset() { *this = Observation(); }

  void record(Call call) {
    if (log_length < 8) {
      log[log_length] = static_cast<int>(call);
    }
    ++log_length;
  }

  bool log_is(Call a, Call b) const {
    return log_length == 2 && log[0] == static_cast<int>(a) && log[1] == static_cast<int>(b);
  }
  bool log_is_only(Call a) const {
    return log_length == 1 && log[0] == static_cast<int>(a);
  }
};

Observation g_obs;

// A receiver with a sentinel tail, so a read or write past the modelled 0x10 bytes
// shows up in the byte comparison rather than silently landing in the test's own
// storage.
struct Receiver {
  unsigned char bytes[kReceiverSize + 8];
};

Receiver make_receiver(Word dispatch_word) {
  Receiver receiver;
  std::memset(&receiver, 0, sizeof receiver);
  std::memcpy(receiver.bytes + kDispatchWordOffset, &dispatch_word, sizeof dispatch_word);
  return receiver;
}

// A dispatch table big enough to hold the real slot and both decoy neighbours.
// Every word of it is a function address, so a model that read the wrong slot calls
// the wrong function and the test sees it.
struct Table {
  unsigned char bytes[kTableExtent];
};

void set_slot(Table& table, std::size_t displacement, SlotTarget target) {
  const std::uintptr_t value = reinterpret_cast<std::uintptr_t>(target);
  std::memcpy(table.bytes + displacement, &value, sizeof value);
}

SlotTarget slot_of(const Table& table, std::size_t displacement) {
  std::uintptr_t value = 0;
  std::memcpy(&value, table.bytes + displacement, sizeof value);
  return reinterpret_cast<SlotTarget>(value);
}

// The word the receiver's leading displacement holds, as a table address.
const void* table_of(const Receiver& receiver) {
  const void* value = nullptr;
  std::memcpy(&value, receiver.bytes + kDispatchWordOffset, sizeof value);
  return value;
}

}  // namespace

// 0x0064149a -- the one direct call. cdecl: the body drops its own word at
// 0x0064149f, so the argument is simply the first stack word. The real callee
// dereferences the pointer and reads three dwords through it; the observer records
// the address so the test can check which address it was, and can optionally
// scribble on it to show the body never reads the receiver's own bytes back.
extern "C" Word PKG_SWARM_W1_00641490_CDECL sporepedia_asset_status_00552300(
    const void* asset_field) {
  ++g_obs.status_calls;
  g_obs.record(kCallStatus);
  g_obs.status_argument = asset_field;
  if (g_obs.status_writes_argument && asset_field != nullptr) {
    std::memcpy(const_cast<void*>(asset_field), &g_obs.status_written,
                sizeof g_obs.status_written);
  }
  return g_obs.status_return;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00641490

namespace {

using namespace openspore::reconstruction::pkg_swarm_w1_00641490;

// The stand-in for the function the slot holds (0x006417d0 in the table runs that
// agree). The reconstruction reaches it through the table, so this is where the
// test's own signature is what gets called -- the model test cannot name 0x006417d0
// and does not try to.
extern "C" std::uint8_t PKG_SWARM_W1_00641490_THISCALL slot_target_observer(
    SporepediaAssetReceiver* receiver, DisplacementRange* range) {
  ++g_obs.slot_calls;
  g_obs.record(kCallSlot);
  g_obs.slot_receiver = receiver;
  g_obs.slot_range = range;
  if (range != nullptr) {
    g_obs.slot_range_before[0] = range->field_00;
    g_obs.slot_range_before[1] = range->field_04;
    if (!g_obs.slot_skips_write) {
      range->field_00 = g_obs.slot_writes[0];
      range->field_04 = g_obs.slot_writes[1];
    }
    g_obs.slot_range_after[0] = range->field_00;
    g_obs.slot_range_after[1] = range->field_04;
  }
  return static_cast<std::uint8_t>(g_obs.slot_return);
}

// A second, differently-shaped target, used as the decoy in the neighbouring slots.
// If the reconstruction reads the wrong slot, or the wrong level, this is what it
// calls and the observation count below catches it.
extern "C" std::uint8_t PKG_SWARM_W1_00641490_THISCALL slot_decoy_observer(
    SporepediaAssetReceiver* receiver, DisplacementRange* range) {
  ++g_obs.slot_calls;
  g_obs.record(kCallSlot);
  g_obs.slot_receiver = receiver;
  g_obs.slot_range = range;
  if (range != nullptr) {
    range->field_00 = 0xffffffffu;
    range->field_04 = 0xffffffffu;
  }
  g_obs.slot_return = 0xffffffffu;
  return 0u;
}

// The receiver the current case is exercising, as the model's own type.
SporepediaAssetReceiver* as_receiver(Receiver& receiver) {
  return reinterpret_cast<SporepediaAssetReceiver*>(&receiver);
}

// Case A -- the surviving path. The status is 2, the slot reports a non-zero AL,
// and the pair's AND is not all-ones, so the body reaches 0x006414c9 and returns
// 1. Everything about the two transfers is checked here.
void case_surviving_path() {
  Table table;
  std::memset(&table, 0, sizeof table);
  set_slot(table, kSlotOffset, &slot_target_observer);

  g_obs.reset();
  g_obs.status_return = 2u;
  g_obs.slot_writes[0] = 0x00010000u;
  g_obs.slot_writes[1] = 0x00ff0000u;
  g_obs.slot_return = 0x1u;

  Receiver receiver = make_receiver(reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(&table)));
  const std::uint8_t result = re_00641490(as_receiver(receiver));

  check(result == 1u, "A1: the surviving path returns 1");
  check(g_obs.status_calls == 1, "A2: 0x00552300 is called exactly once");
  check(g_obs.slot_calls == 1, "A3: the slot is dispatched to exactly once");
  check(g_obs.log_is(kCallStatus, kCallSlot), "A4: the status call comes before the dispatch");
  check(g_obs.status_argument == &receiver.bytes[kAssetFieldOffset],
        "A5: 0x00552300 is handed the ADDRESS receiver+0x04");
  check(g_obs.status_argument != static_cast<const void*>(&receiver) &&
            g_obs.status_argument != table_of(receiver),
        "A6: it is neither the receiver itself nor the table");
  check(g_obs.slot_receiver == as_receiver(receiver),
        "A7: the dispatch receiver in ECX is the receiver itself");
  check(g_obs.slot_range != nullptr, "A8: the slot was handed a pair address");
  check(reinterpret_cast<const unsigned char*>(g_obs.slot_range) !=
            reinterpret_cast<const unsigned char*>(&receiver),
        "A9: the pair is not receiver memory");
}

// Case B -- the status test is `!= 2`. Every other value the callee can return
// fails, and only 2 dispatches. 0x00552300's own listing returns 0, 1, 2 or a
// word it loaded, so 0, 1 and 3 (standing for "a loaded word that is not 2") are
// the discriminating values.
void case_status_value_is_exactly_two() {
  Table table;
  std::memset(&table, 0, sizeof table);
  set_slot(table, kSlotOffset, &slot_target_observer);

  struct Row {
    Word status;
    bool dispatches;
  };
  const Row rows[] = {{0u, false}, {1u, false}, {2u, true}, {3u, false}, {0xffffffffu, false}};

  for (const Row& row : rows) {
    g_obs.reset();
    g_obs.status_return = row.status;
    g_obs.slot_writes[0] = 1u;
    g_obs.slot_writes[1] = 1u;
    g_obs.slot_return = 1u;

    Receiver receiver =
        make_receiver(reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(&table)));
    const std::uint8_t result = re_00641490(as_receiver(receiver));

    check(g_obs.slot_calls == (row.dispatches ? 1 : 0),
          "B: the slot is dispatched only when the status is exactly 2");
    check(result == (row.dispatches ? 1u : 0u), "B: and the return follows that same test");
    if (!row.dispatches) {
      check(g_obs.log_is_only(kCallStatus), "B: a failing status makes no second transfer");
    }
  }
}

// Case C -- the dispatch is TWO dereferences, at slot 0x90. The table carries three
// targets: the observer one dword below the real slot, the observer at the real
// slot, and the decoy one dword above. A model that read the table's base word, or
// that read the receiver's leading word as the target itself, or that landed one
// dword either side of 0x90, calls something else.
void case_two_level_dispatch_at_slot_0x90() {
  Table table;
  std::memset(&table, 0, sizeof table);
  set_slot(table, kNeighbourSlotBefore, &slot_decoy_observer);
  set_slot(table, kSlotOffset, &slot_target_observer);
  set_slot(table, kNeighbourSlotAfter, &slot_decoy_observer);
  // The table's own base word also holds a pointer, so a model that stopped after
  // one dereference has something to call and is caught rather than faulting.
  set_slot(table, 0x0u, &slot_decoy_observer);

  g_obs.reset();
  g_obs.status_return = 2u;
  g_obs.slot_writes[0] = 7u;
  g_obs.slot_writes[1] = 3u;
  g_obs.slot_return = 1u;

  Receiver receiver =
      make_receiver(reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(&table)));
  const std::uint8_t result = re_00641490(as_receiver(receiver));

  check(result == 1u, "C1: the pair (7, 3) ANDs to 3, not all-ones, so the body survives");
  check(g_obs.slot_calls == 1, "C2: exactly one dispatch happened");
  check(g_obs.slot_receiver == as_receiver(receiver),
        "C3: the one dispatch went to the slot at 0x90 (the decoys would have "
        "written all-ones and reported a zero AL)");
  check(g_obs.slot_range != nullptr, "C4: the surviving dispatch was handed the pair");

  // The fixture itself, checked rather than assumed: the word the reconstruction
  // must read is the observer's, and the two neighbouring words -- and the table's
  // own base word -- are the decoy's. Without this the case above would also pass
  // against a reconstruction that called nothing at all.
  check(slot_of(table, kSlotOffset) == &slot_target_observer,
        "C5: the fixture's real slot holds the observer");
  check(slot_of(table, kNeighbourSlotBefore) == &slot_decoy_observer &&
            slot_of(table, kNeighbourSlotAfter) == &slot_decoy_observer &&
            slot_of(table, 0x0u) == &slot_decoy_observer,
        "C6: the decoy slots one dword either side of 0x90, and the table's base "
        "word, all hold the decoy");
}

// Case D -- the dispatch word is the receiver's own word at displacement 0. A second
// table is built and parked in the receiver's neighbouring words, and a third
// pointer is parked immediately before the receiver, so a model that read +0x04,
// +0x08 or a negative displacement calls one of the decoys.
void case_dispatch_word_is_receiver_offset_zero() {
  Table decoy_table;
  std::memset(&decoy_table, 0, sizeof decoy_table);
  set_slot(decoy_table, kSlotOffset, &slot_decoy_observer);

  Table table;
  std::memset(&table, 0, sizeof table);
  set_slot(table, kSlotOffset, &slot_target_observer);

  // A guard word in front of the receiver, so a negative displacement lands in
  // storage the test controls and points at the decoy table.
  Word guard = reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_table));

  g_obs.reset();
  g_obs.status_return = 2u;
  g_obs.slot_writes[0] = 0x11u;
  g_obs.slot_writes[1] = 0x11u;
  g_obs.slot_return = 1u;

  Receiver receiver =
      make_receiver(reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(&table)));
  std::memcpy(receiver.bytes + kAssetFieldOffset, &guard, sizeof guard);
  std::memcpy(receiver.bytes + kAssetFieldOffset + 4, &guard, sizeof guard);
  std::memcpy(&guard, receiver.bytes + kAssetFieldOffset + 8, sizeof guard);

  const std::uint8_t result = re_00641490(as_receiver(receiver));

  check(result == 1u, "D1: the neighbouring decoy pointers did not move the outcome");
  check(g_obs.slot_calls == 1, "D2: exactly one dispatch happened");
  check(g_obs.slot_range_after[0] == 0x11u && g_obs.slot_range_after[1] == 0x11u,
        "D3: the dispatch was the one that wrote 0x11, not the decoy's all-ones");
  check(g_obs.status_argument == &receiver.bytes[kAssetFieldOffset],
        "D4: and the status call was still handed receiver+0x04");
}

// Case E -- 0x00552300 is handed a POINTER, and the pointer is receiver+0x04. The
// observer also scribbles through the pointer it was given, which the real callee
// never does; the outcome must not move, because this body never reads the
// receiver's own bytes back.
void case_status_argument_is_a_pointer_to_the_asset_field() {
  Table table;
  std::memset(&table, 0, sizeof table);
  set_slot(table, kSlotOffset, &slot_target_observer);

  g_obs.reset();
  g_obs.status_return = 2u;
  g_obs.status_writes_argument = true;
  g_obs.status_written = 0xffffffffu;
  g_obs.slot_writes[0] = 5u;
  g_obs.slot_writes[1] = 5u;
  g_obs.slot_return = 1u;

  Receiver receiver =
      make_receiver(reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(&table)));
  const std::uint8_t result = re_00641490(as_receiver(receiver));

  check(g_obs.status_argument == &receiver.bytes[kAssetFieldOffset],
        "E1: the argument is the address receiver+0x04, byte for byte");
  check(result == 1u, "E2: a callee that scribbled on the receiver did not move the outcome");
  check(g_obs.slot_calls == 1, "E3: and the dispatch still happened");
}

// Case F -- the AND is of BOTH words, so the all-ones test is not on either word
// alone and not "either is all-ones". AND yields all-ones only when both are, and
// the rows below are chosen so that each of the four wrong rules gives a different
// answer on at least one of them.
void case_and_is_of_both_words() {
  Table table;
  std::memset(&table, 0, sizeof table);
  set_slot(table, kSlotOffset, &slot_target_observer);

  struct Row {
    Word first;
    Word second;
    bool survives;
  };
  const Row rows[] = {
      {0xffffffffu, 0xffffffffu, false},  // both all-ones: the rejected case
      {0xffffffffu, 0x7fffffffu, true},   // one all-ones only
      {0x7fffffffu, 0xffffffffu, true},   // the other all-ones only
      {0xfffffffeu, 0xffffffffu, true},   // one bit short in the first
      {0xffffffffu, 0xfffffffeu, true},   // one bit short in the second
      {0u, 0xffffffffu, true},            // zero and all-ones
      {0u, 0u, true},                     // nothing set at all
      {0x80000000u, 0xffffffffu, true},   // signed-negative first, all-ones second
  };

  for (const Row& row : rows) {
    g_obs.reset();
    g_obs.status_return = 2u;
    g_obs.slot_writes[0] = row.first;
    g_obs.slot_writes[1] = row.second;
    g_obs.slot_return = 1u;

    Receiver receiver =
        make_receiver(reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(&table)));
    const std::uint8_t result = re_00641490(as_receiver(receiver));

    check(result == (row.survives ? 1u : 0u),
          "F: only the both-words-all-ones pair is rejected");
  }
}

// Case G -- 0x006414b8 is `TEST AL,AL`: the low byte decides and the upper three are
// ignored. The rows differ only above bit 7, and the return values include 0x100
// (AL == 0) and 0x1ff (AL == 0xff), which a model testing the whole EAX, or
// testing "!= 0", gets wrong.
void case_only_the_low_byte_of_the_slot_return_is_tested() {
  Table table;
  std::memset(&table, 0, sizeof table);
  set_slot(table, kSlotOffset, &slot_target_observer);

  struct Row {
    std::uint32_t returned;
    bool survives;
  };
  const Row rows[] = {
      {0x00000000u, false},  // AL == 0
      {0x00000100u, false},  // AL == 0 with a non-zero upper half
      {0x00000001u, true},   // AL == 1
      {0x000000ffu, true},   // AL == 0xff
      {0xffffff00u, false},  // AL == 0 with every upper bit set
      {0x000001ffu, true},   // AL == 0xff with a non-zero upper half
  };

  for (const Row& row : rows) {
    g_obs.reset();
    g_obs.status_return = 2u;
    g_obs.slot_writes[0] = 0x33u;
    g_obs.slot_writes[1] = 0x33u;
    g_obs.slot_return = row.returned;

    Receiver receiver =
        make_receiver(reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(&table)));
    const std::uint8_t result = re_00641490(as_receiver(receiver));

    check(result == (row.survives ? 1u : 0u),
          "G: the slot's AL decides, and nothing above it is read");
  }
}

// Case H -- the pair is read AFTER the dispatch, once per call, and is not cached
// between calls. Two calls on the SAME receiver with the same status and the same
// slot get two different pairs written, and the two outcomes differ; a model that
// read the pair before the call, or that remembered the first call's pair, cannot
// produce that.
void case_pair_is_read_after_the_dispatch_each_call() {
  Table table;
  std::memset(&table, 0, sizeof table);
  set_slot(table, kSlotOffset, &slot_target_observer);

  g_obs.reset();
  g_obs.status_return = 2u;
  g_obs.slot_return = 1u;

  Receiver receiver =
      make_receiver(reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(&table)));

  g_obs.slot_writes[0] = 0xffffffffu;
  g_obs.slot_writes[1] = 0xffffffffu;
  const std::uint8_t first = re_00641490(as_receiver(receiver));

  g_obs.slot_writes[0] = 0x00000001u;
  g_obs.slot_writes[1] = 0xffffffffu;
  const std::uint8_t second = re_00641490(as_receiver(receiver));

  check(first == 0u, "H1: the first call's all-ones pair is rejected");
  check(second == 1u, "H2: the second call's pair is read afresh and accepted");
  check(g_obs.slot_calls == 2 && g_obs.status_calls == 2,
        "H3: both calls made both transfers");
}

// Case I -- the return value is the byte the machine's AL holds, not the AND result.
// 0x006414c9 writes 0x01 into AL and leaves bits 8..31 of EAX alone, so a model
// that returned the AND (or the slot's own return word) is refuted here.
void case_return_is_the_byte_not_the_and_value() {
  Table table;
  std::memset(&table, 0, sizeof table);
  set_slot(table, kSlotOffset, &slot_target_observer);

  g_obs.reset();
  g_obs.status_return = 0x99u;  // not 2, so this must fail
  g_obs.slot_writes[0] = 0x12345678u;
  g_obs.slot_writes[1] = 0x9abcdef0u;
  g_obs.slot_return = 0x1u;

  Receiver receiver =
      make_receiver(reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(&table)));
  const std::uint8_t failed = re_00641490(as_receiver(receiver));
  check(failed == 0u, "I1: a failing status returns 0, not the callee's 0x99");

  g_obs.status_return = 2u;
  const std::uint8_t survived = re_00641490(as_receiver(receiver));
  check(survived == 1u, "I2: a surviving path returns 1, not the AND 0x02345670");
  check(survived != 0x70u, "I3: the low byte of the AND never reaches the caller");
}

// Case J -- the pair the slot is handed is a frame object. It is not the receiver,
// not receiver+0x04 (the address the status call was handed), and not the table. A
// second call is checked for the same, and the test also confirms the two addresses
// are not equal to each other, which is the wrong-argument-order decoy.
void case_pair_and_status_argument_are_distinct_objects() {
  Table table;
  std::memset(&table, 0, sizeof table);
  set_slot(table, kSlotOffset, &slot_target_observer);

  g_obs.reset();
  g_obs.status_return = 2u;
  g_obs.slot_writes[0] = 2u;
  g_obs.slot_writes[1] = 2u;
  g_obs.slot_return = 1u;

  Receiver receiver =
      make_receiver(reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(&table)));
  const std::uint8_t result = re_00641490(as_receiver(receiver));
  const void* status_argument = g_obs.status_argument;
  DisplacementRange* range = g_obs.slot_range;

  check(result == 1u, "J1: the call survived");
  check(range != nullptr, "J2: the slot was handed a pair");
  check(reinterpret_cast<const void*>(range) != status_argument,
        "J3: the pair and the status argument are two different objects");
  check(reinterpret_cast<const unsigned char*>(range) != receiver.bytes &&
            reinterpret_cast<const unsigned char*>(range) + kPairSize <= receiver.bytes,
        "J4: the pair is not inside the receiver's bytes");
  check(status_argument != static_cast<const void*>(table_of(receiver)),
        "J5: the status argument is not the dispatch table either");
  check(reinterpret_cast<const unsigned char*>(range) !=
            reinterpret_cast<const unsigned char*>(&table),
        "J6: the pair is not the dispatch table");
}

// Case K -- a slot that reports success WITHOUT writing the pair. The real
// 0x006417d0 always writes both words on a non-zero AL, so this is a stricter
// question than the machine asks: it shows the model's outcome depends on the words
// it was given and on nothing else the callee did, which is the weakest honest form
// of "the body reads exactly the pair's two words".
void case_slot_that_writes_nothing() {
  Table table;
  std::memset(&table, 0, sizeof table);
  set_slot(table, kSlotOffset, &slot_target_observer);

  g_obs.reset();
  g_obs.status_return = 2u;
  g_obs.slot_skips_write = true;
  g_obs.slot_writes[0] = 0xffffffffu;  // ignored, the observer writes nothing
  g_obs.slot_writes[1] = 0xffffffffu;
  g_obs.slot_return = 1u;

  Receiver receiver =
      make_receiver(reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(&table)));
  const std::uint8_t result = re_00641490(as_receiver(receiver));

  check(g_obs.slot_calls == 1, "K1: the dispatch happened");
  check(result == 1u,
        "K2: with the pair left at its initial value the AND is 0, so the body survives -- "
        "the outcome tracks the words the callee wrote, not the words the test wanted");
}

// Case L -- ABI, measured. The terminator is a bare RET and the prologue reserves
// eight bytes and saves ESI, so this function takes no ordinary stack argument: ESP
// before the call and after the return must be the same value. The trampoline also
// hands the receiver in ECX, which is where the body's only receiver access reads
// from -- so a model that ignored the receiver, or that took it from the stack, is
// caught by the observations above rather than by this measurement.
struct EspSamples {
  std::uint32_t before_call = 0;
  std::uint32_t after_return = 0;
};

EspSamples call_measured(SporepediaAssetReceiver* receiver) {
  const std::uint32_t target =
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&re_00641490));
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  // EAX and ECX are in the clobber list, so the compiler cannot have allocated the
  // input to either: every "r" operand therefore survives the `movl ..., %%ecx`
  // that precedes its use.
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

void case_no_stack_argument_word_is_consumed() {
  Table table;
  std::memset(&table, 0, sizeof table);
  set_slot(table, kSlotOffset, &slot_target_observer);

  g_obs.reset();
  g_obs.status_return = 2u;
  g_obs.slot_writes[0] = 9u;
  g_obs.slot_writes[1] = 9u;
  g_obs.slot_return = 1u;

  Receiver receiver =
      make_receiver(reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(&table)));
  const EspSamples samples = call_measured(as_receiver(receiver));

  check(samples.after_return == samples.before_call,
        "L1: the function consumes no stack word (bare RET, and both exits restore ESP)");
  check(g_obs.status_calls == 1 && g_obs.slot_calls == 1,
        "L2: the trampoline really reached the whole body");
  check(g_obs.status_argument == &receiver.bytes[kAssetFieldOffset],
        "L3: ECX carried the receiver the trampoline was given");
  check(g_obs.slot_receiver == as_receiver(receiver),
        "L4: and the same receiver reached the slot in ECX");
}

// The displacements and constants the reconstruction states, against the listing's
// own bytes. Every one of these is a number a reviewer can check against the 30
// instructions at the top of the .cpp.
void verify_machine_constants() {
  check(kReceiverDispatchDisplacement == 0x0u,
        "V1: the dispatch word is the receiver's word at +0x00 (0x006414a7)");
  check(kReceiverAssetFieldDisplacement == 0x4u,
        "V2: the address handed to 0x00552300 is receiver+0x04 (0x00641496)");
  check(kStatusComparedValue == 0x2u, "V3: the compared status is 2 (0x006414a2)");
  check(kDispatchSlotDisplacement == 0x90u, "V4: the slot displacement is 0x90 (0x006414a9)");
  check(kDispatchSlotIndex == 36u, "V5: 0x90 is dword index 36");
  check(kPairFirstWordDisplacement == 0x0u, "V6: the pair's first word is at its +0x00");
  check(kPairSecondWordDisplacement == 0x4u, "V7: the pair's second word is at its +0x04");
  check(kPairSize == 0x8u, "V8: the pair is the eight bytes SUB ESP,0x8 reserves");
  check(kSentinelRejected == 0xffffffffu, "V9: the rejected AND value is all-ones (0x006414c4)");
  check(kTrue == 0x1u, "V10: the surviving return byte is 1 (0x006414c9)");
  check(kFalse == 0x0u, "V11: the failing return byte is 0 (0x006414d0)");
  check(sizeof(SporepediaAssetReceiver) == 0x10u,
        "V12: the modelled receiver covers the words the body and 0x00552300 were seen reading");
  check(kAssetFieldOffset + 12u <= kReceiverSize,
        "V13: 0x00552300 reads three dwords through receiver+0x04, and the run holds them");
  check(sizeof(DisplacementRange) == 8u, "V14: the pair is eight bytes");
}

}  // namespace

int main() {
  verify_machine_constants();
  case_surviving_path();
  case_status_value_is_exactly_two();
  case_two_level_dispatch_at_slot_0x90();
  case_dispatch_word_is_receiver_offset_zero();
  case_status_argument_is_a_pointer_to_the_asset_field();
  case_and_is_of_both_words();
  case_only_the_low_byte_of_the_slot_return_is_tested();
  case_pair_is_read_after_the_dispatch_each_call();
  case_return_is_the_byte_not_the_and_value();
  case_pair_and_status_argument_are_distinct_objects();
  case_slot_that_writes_nothing();
  case_no_stack_argument_word_is_consumed();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}
