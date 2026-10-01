// Model test for pkg_prop_resource_safe_wave9.
//
// It exists to try to FALSIFY the two reconstructions, not to walk them. Every
// test below names the riskiest way the listing could be misread and asserts the
// observation that would show the source wrong. A test that only produces a
// plausible answer is evidence of nothing here.
//
// Evidence, both listings complete and untruncated:
//   006a3300  MOV AL,byte ptr [ESP + 0x4] / MOV byte ptr [ECX + 0x15],AL /
//             RET 0x4
//   006c0550  30 instructions; the displacements and the dispatch sites they
//             produce are quoted inline at the test that pins each one.

#include <sys/wait.h>
#include <unistd.h>

#include <csignal>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <string>
#include <type_traits>
#include <vector>

#include "prop_resource_safe_wave9.hpp"

#if defined(_MSC_VER)
#define PKG_PROP_SAFE_TEST_CDECL __cdecl
#define PKG_PROP_SAFE_TEST_THISCALL __thiscall
#else
#define PKG_PROP_SAFE_TEST_CDECL __attribute__((cdecl))
#define PKG_PROP_SAFE_TEST_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_prop_resource_safe_wave9 {
namespace {

// -- what the two reconstructions declare ----------------------------------
//
// 006a3300 is entered with this plus one four-byte stack word, and the body
// ends in `RET 0x4`, so the callee pops it. 006c0550 is entered with this plus
// two four-byte stack words; it ends in `RET 0x8` on the path that returns
// through its own frame and restores the frame before jumping on the other, so
// the callee it reaches pops them. Both are measured further down rather than
// assumed from these types.
using SetDevModeSignature =
    void(PKG_PROP_SAFE_TEST_THISCALL*)(OpaquePropManagerReceiver*, std::uint8_t);
using FlushSignature =
    std::uint8_t(PKG_PROP_SAFE_TEST_THISCALL*)(void*, Word, Word);
using AccessPortSignature = Word(PKG_PROP_SAFE_TEST_THISCALL*)(void*);
using WritePortSignature =
    std::int32_t(PKG_PROP_SAFE_TEST_THISCALL*)(void*, Word, Word);

static_assert(std::is_same<decltype(&prop_manager_set_dev_mode_006a3300),
                           SetDevModeSignature>::value,
              "006a3300 takes this plus one explicit stack word popped by RET 0x4");
static_assert(
    std::is_same<decltype(&record_write_flush_006c0550), FlushSignature>::value,
    "006c0550 takes this plus two explicit stack words popped by RET 8");
static_assert(std::is_same<AccessPort, AccessPortSignature>::value,
              "the +0x10 port is dispatched with this and no stack word");
static_assert(std::is_same<WritePort, WritePortSignature>::value,
              "the +0x38 port is dispatched with this and two stack words");
static_assert(sizeof(std::uint8_t) == 1 && sizeof(Word) == 4 &&
                  sizeof(std::size_t) == 4 && sizeof(void*) == 4,
              "a one-byte store, four-byte slot words, four-byte code pointers");

// Constants are compared by VALUE here, never by spelling: each is written in
// two spellings, and the test would stop compiling if the header ever drifted
// away from the displacement the listing prints.
static_assert(kPropManagerSlotDisplacement == 0x15,
              "006a3304 stores at displacement 21");
static_assert(kPropManagerSlotDisplacement == 21,
              "the same displacement, read as a decimal value");
static_assert(kPropManagerObservedExtent == 0x16,
              "the body was seen reaching byte 21, so the object is 22 bytes");
static_assert(kRecordGateDisplacement == -4,
              "006c0555 reads one whole word below the receiver");
static_assert(kRecordGateDisplacement == -0x04,
              "the same displacement, in the other spelling");
static_assert(kRecordFirstObjectDisplacement == 40,
              "006c055b and 006c0562 name receiver+0x28");
static_assert(kRecordFirstObjectDisplacement != 8 &&
                  kRecordFirstObjectDisplacement != 0x2c,
              "the first object is neither receiver+0x8 nor receiver+0x2c");
static_assert(kRecordSecondObjectDisplacement == 4,
              "006c0585 and 006c058b name receiver+0x4");
static_assert(kRecordSecondObjectDisplacement != 0x24 &&
                  kRecordSecondObjectDisplacement != 0x14,
              "the second object is neither receiver+0x24 nor receiver+0x14");
static_assert(kRecordFirstObjectDisplacement != kRecordSecondObjectDisplacement,
              "the two object locations are different displacements");
static_assert(kRecordGateDisplacement != kRecordSecondObjectDisplacement,
              "the gate is below the receiver, not one of its words");
static_assert(kAccessPortSlot == 16, "006c055e reads table+0x10");
static_assert(kWritePortSlot == 56, "006c0577 and 006c0588 read table+0x38");
static_assert(kAccessPortSlot != kWritePortSlot,
              "the access slot and the write slot are different words");
static_assert(kObservedTableExtent == 0x3c,
              "the highest word the body reads in a table ends at +0x3c");

std::vector<std::string> events;

void check(bool condition) {
  if (condition) {
    return;
  }
  std::fputs("check failed", stderr);
  for (const std::string& event : events) {
    std::fprintf(stderr, " %s", event.c_str());
  }
  std::fputc('\n', stderr);
  std::abort();
}

// The event log is the order-of-operations oracle: a port that fires when it
// must not, or in the wrong order, shows up here before any value does.
void expect(std::initializer_list<const char*> expected) {
  check(events.size() == expected.size());
  std::size_t index = 0;
  for (const char* value : expected) {
    check(events[index] == value);
    ++index;
  }
}

// -- fixtures ---------------------------------------------------------------
//
// A slot table is a byte array with ports written into it at displacements. It
// has no named members: the listing shows two words of a table being read and
// names neither, so the test writes a port into every other slot it can think of
// and a source that reads the wrong one fails loudly instead of plausibly.
struct SlotTable {
  std::uint8_t bytes[kObservedTableExtent]{};

  template <typename Port>
  void install(std::ptrdiff_t slot, Port port) {
    static_assert(sizeof(port) == sizeof(Word),
                  "an x86-32 code pointer is four bytes wide, so a slot holds one");
    check(slot >= 0);
    check(static_cast<std::size_t>(slot) + sizeof(Word) <= kObservedTableExtent);
    std::memcpy(slot_at(bytes, slot), &port, sizeof(port));
  }
};

template <typename Port>
Port port_at(void* table, std::ptrdiff_t slot) {
  Port port = nullptr;
  std::memcpy(&port, slot_at(table, slot), sizeof(port));
  return port;
}

// Four bytes lead the receiver because the body reads one whole word *below* it
// (006c0555). Where the receiver sits inside the enclosing record is not
// something this listing shows -- the machine proves receiver-relative
// displacements and nothing at all about an object containing them -- so the
// fixture puts the receiver at its own base and reserves only the words the body
// actually reaches, instead of inventing a record layout around it.
//
// The tables those words point at are the test's own objects and live outside
// the arena. They cannot be embedded in it: the two of them are 0x24 apart and a
// table is 0x3c wide, so laying them out in one buffer would overlap, and picking
// non-overlapping placements would be inventing a layout the listing does not
// support.
constexpr std::size_t kArenaLead = 4;
constexpr std::size_t kArenaExtent = kArenaLead + 0x30;

static_assert(kReceiverObservedExtent == 0x2c,
              "the first object location plus the four bytes read there");
static_assert(kArenaExtent >= kArenaLead + kReceiverObservedExtent,
              "the arena holds every word the body was seen reaching, and more");

struct FlushFixture {
  std::uint8_t arena[kArenaExtent]{};

  void* receiver() { return arena + kArenaLead; }
  void* gate() { return arena; }
  void* first_object() { return slot_at(receiver(), 0x28); }
  void* second_object() { return slot_at(receiver(), 0x04); }
  void* at(std::ptrdiff_t receiver_relative) {
    return slot_at(receiver(), receiver_relative);
  }
  void set_gate(Word value) { std::memcpy(gate(), &value, sizeof(value)); }
  // The body copies a *pointer* out of each object location and reads the slot
  // through it (006c055b then 006c055e), so the fixture stores a pointer word
  // there and not a copy of a table.
  void publish(void* object, SlotTable& table) {
    void* const table_address = table.bytes;
    std::memcpy(object, &table_address, sizeof(table_address));
  }
  void poison(std::uint8_t value) { std::memset(arena, value, sizeof(arena)); }
};

struct PortState {
  Word access_result = 0;
  std::int32_t write_result = 0;
  void* expected_access_object = nullptr;
  void* expected_write_object = nullptr;
  Word expected_first_argument = 0;
  Word expected_second_argument = 0;
  void* observed_access_object = nullptr;
  void* observed_write_object = nullptr;
  std::uint32_t access_calls = 0;
  std::uint32_t write_calls = 0;
  // When set, the access port replaces the table words of both objects and the
  // reconstruction must read the replacements: 006c0571 and 006c0585 re-load
  // after the call rather than reusing the values 006c055b and 006c0562 read.
  bool replace_table_under_access = false;
  void* replacement_first_table = nullptr;
  void* replacement_second_table = nullptr;
  void* first_object = nullptr;
  void* second_object = nullptr;
};

PortState state;
SlotTable first_table;
SlotTable first_replacement_table;
SlotTable second_table;
SlotTable second_replacement_table;
SlotTable decoy_table;
FlushFixture fixture;

[[noreturn]] void fail(const char* what) {
  std::fprintf(stderr, "unexpected dispatch: %s", what);
  for (const std::string& event : events) {
    std::fprintf(stderr, " %s", event.c_str());
  }
  std::fputc('\n', stderr);
  std::abort();
}

// Neither decoy shape is in the listing, so neither may ever be reached: firing
// is the failure, and it is reported with the log of what did fire.
Word PKG_PROP_SAFE_TEST_THISCALL decoy_access_port(void* object) {
  static_cast<void>(object);
  fail("a table slot the listing never reads");
}

std::int32_t PKG_PROP_SAFE_TEST_THISCALL decoy_write_port(void* object, Word a, Word b) {
  static_cast<void>(object);
  static_cast<void>(a);
  static_cast<void>(b);
  fail("a table slot the listing never reads");
}

// The access port: one argument, the object, and nothing else -- 006c0567 has
// no PUSH before it.
Word PKG_PROP_SAFE_TEST_THISCALL access_port(void* object) {
  events.emplace_back("access");
  ++state.access_calls;
  // Pointer vs pointee, and the depth of the dispatch: 006c0565 sets ECX to the
  // object 006c0562 formed, not to the table word 006c055b loaded. A one-level
  // reconstruction, or one that passed the table, is caught right here.
  check(object == state.expected_access_object);
  state.observed_access_object = object;
  if (state.replace_table_under_access) {
    std::memcpy(state.first_object, &state.replacement_first_table, sizeof(void*));
    std::memcpy(state.second_object, &state.replacement_second_table, sizeof(void*));
  }
  return state.access_result;
}

std::int32_t PKG_PROP_SAFE_TEST_THISCALL write_first_primary(void* object, Word a,
                                                             Word b) {
  events.emplace_back("write-first");
  ++state.write_calls;
  check(object == state.expected_write_object);
  check(a == state.expected_first_argument);
  check(b == state.expected_second_argument);
  state.observed_write_object = object;
  return state.write_result;
}

std::int32_t PKG_PROP_SAFE_TEST_THISCALL write_first_replacement(void* object,
                                                                 Word a, Word b) {
  events.emplace_back("write-first-replacement");
  ++state.write_calls;
  check(object == state.expected_write_object);
  check(a == state.expected_first_argument);
  check(b == state.expected_second_argument);
  state.observed_write_object = object;
  return state.write_result;
}

std::int32_t PKG_PROP_SAFE_TEST_THISCALL write_second_primary(void* object, Word a,
                                                              Word b) {
  events.emplace_back("write-second");
  ++state.write_calls;
  check(object == state.expected_write_object);
  check(a == state.expected_first_argument);
  check(b == state.expected_second_argument);
  state.observed_write_object = object;
  return state.write_result;
}

std::int32_t PKG_PROP_SAFE_TEST_THISCALL write_second_replacement(void* object,
                                                                  Word a, Word b) {
  events.emplace_back("write-second-replacement");
  ++state.write_calls;
  check(object == state.expected_write_object);
  check(a == state.expected_first_argument);
  check(b == state.expected_second_argument);
  state.observed_write_object = object;
  return state.write_result;
}

// Every slot the listing does not read carries a decoy. Around +0x10 they are
// 0x00, 0x04, 0x08, 0x0c and 0x14 -- so a read of the access slot at 0, at 4
// (which is what a read of 0x2c instead of 0x28 in the receiver would land on),
// or anywhere near it, aborts. Around +0x38 they are 0x20, 0x24, 0x2c, 0x30 and
// 0x34 -- so a read of the write slot at 0x30 aborts, and 0x20 is what a read of
// receiver+0x48 instead of receiver+0x28 would land on.
void fill_decoys(SlotTable& table) {
  const std::ptrdiff_t access_decoys[] = {0x00, 0x04, 0x08, 0x0c, 0x14};
  for (const std::ptrdiff_t slot : access_decoys) {
    table.install(slot, decoy_access_port);
  }
  const std::ptrdiff_t write_decoys[] = {0x20, 0x24, 0x2c, 0x30, 0x34};
  for (const std::ptrdiff_t slot : write_decoys) {
    table.install(slot, decoy_write_port);
  }
}

// The table the receiver's *other* words point at. Every word of it is a trap,
// including the two the body would read, so a reconstruction that took an object
// location the listing does not name aborts with a message instead of jumping
// into whatever the fixture had left there. The upper half carries the write
// shape and the lower half the access shape, so a misread lands on the trap whose
// argument list matches the read it came from.
void fill_every_slot_with_a_trap(SlotTable& table) {
  for (std::size_t offset = 0; offset < kObservedTableExtent; offset += sizeof(Word)) {
    const std::ptrdiff_t slot = static_cast<std::ptrdiff_t>(offset);
    if (offset < kWritePortSlot - kAccessPortSlot) {
      table.install(slot, decoy_access_port);
    } else {
      table.install(slot, decoy_write_port);
    }
  }
}

void reset_fixture(Word gate_value, Word access_result) {
  events.clear();
  state = PortState{};
  state.access_result = access_result;
  state.first_object = fixture.first_object();
  state.second_object = fixture.second_object();
  state.expected_access_object = fixture.first_object();

  first_table = SlotTable{};
  first_replacement_table = SlotTable{};
  second_table = SlotTable{};
  second_replacement_table = SlotTable{};
  decoy_table = SlotTable{};
  fill_decoys(first_table);
  fill_decoys(first_replacement_table);
  fill_decoys(second_table);
  fill_decoys(second_replacement_table);
  fill_every_slot_with_a_trap(decoy_table);
  first_table.install(kAccessPortSlot, access_port);
  first_table.install(kWritePortSlot, write_first_primary);
  first_replacement_table.install(kAccessPortSlot, access_port);
  first_replacement_table.install(kWritePortSlot, write_first_replacement);
  second_table.install(kAccessPortSlot, access_port);
  second_table.install(kWritePortSlot, write_second_primary);
  second_replacement_table.install(kAccessPortSlot, access_port);
  second_replacement_table.install(kWritePortSlot, write_second_replacement);

  fixture.poison(0xa5);
  fixture.set_gate(gate_value);
  // The two locations the listing dispatches through, and then a table pointer
  // into the all-decoy table at every other word of the receiver the body does
  // not read -- +0x00, +0x08, +0x0c. A reconstruction that took the first object
  // at receiver+0x00, +0x08 or +0x0c, or the second at +0x14 or +0x24, would
  // dispatch into a decoy and abort. A displacement is an offset: 0x28 is not
  // 0x08, and treating it as an index into a word array would land elsewhere and
  // find one of these.
  fixture.publish(fixture.at(0x00), decoy_table);
  fixture.publish(fixture.at(0x08), decoy_table);
  fixture.publish(fixture.at(0x0c), decoy_table);
  fixture.publish(fixture.second_object(), second_table);
  fixture.publish(fixture.first_object(), first_table);
  // The pointers a port installs are table *addresses*, which is what the body
  // reads out of an object location: the array, not the struct wrapping it.
  state.replacement_first_table = first_replacement_table.bytes;
  state.replacement_second_table = second_replacement_table.bytes;
}

// The two forwarded words, named for the slot each arrives in rather than for a
// role the body never assigns them, and given values that are not
// interchangeable so a transposition cannot pass by accident.
constexpr Word kEsp4Word = 0xaaaa0001u;
constexpr Word kEsp8Word = 0xbbbb0002u;

// 006c057a pushes the ESP+0x8 word and 006c057b the ESP+0x4 word, so the port
// reached by CALL sees the ESP+0x8 word first. 006c058e and 006c058f restore
// the frame and 006c0590 JMP EDX, so the port reached by the jump inherits the
// caller's own two words in the caller's own order: ESP+0x4 first.
void expect_called_order(Word first, Word second) {
  state.expected_first_argument = first;
  state.expected_second_argument = second;
}

void expect_jumped_order(Word first, Word second) {
  state.expected_first_argument = first;
  state.expected_second_argument = second;
}

// The flush under test, entered with the two forwarded words, returning the byte
// it produced so the caller can compare it against a table of expectations.
std::uint8_t flush_checked() {
  return record_write_flush_006c0550(fixture.receiver(), kEsp4Word, kEsp8Word);
}

// ===========================================================================
// 0x006a3300
// ===========================================================================

// A receiver with guard bytes on both sides, so "the store did not run past the
// object" and "the store did not run before it" are both observable without
// reading outside the object the reconstruction was given.
struct DevModeSandbox {
  std::uint8_t before[4]{};
  OpaquePropManagerReceiver receiver{};
  std::uint8_t after[4]{};

  std::uint8_t* bytes() { return reinterpret_cast<std::uint8_t*>(&receiver); }
};

// Displacement is an offset, not an index and not a word count. The store lands
// on byte 21 of a 22-byte object and on no other byte, and not on either guard.
void test_dev_mode_lands_on_displacement_0x15() {
  DevModeSandbox sandbox{};
  std::memset(sandbox.bytes(), 0xee, sizeof(sandbox.receiver.bytes));
  std::memset(sandbox.before, 0x11, sizeof(sandbox.before));
  std::memset(sandbox.after, 0x22, sizeof(sandbox.after));
  check(sizeof(sandbox.receiver.bytes) == 0x16);
  check(kPropManagerSlotDisplacement == 21);

  prop_manager_set_dev_mode_006a3300(&sandbox.receiver, 0x5c);
  check(sandbox.bytes()[21] == 0x5c);
  // Compared whole: a word-wide store, a scaled index, or an off-by-one each
  // leave a different byte wrong, and nothing here assumes what the neighbours
  // should be beyond "unchanged".
  for (std::size_t index = 0; index < sizeof(sandbox.receiver.bytes); ++index) {
    if (index == 21) {
      continue;
    }
    check(sandbox.bytes()[index] == 0xee);
  }
  for (std::size_t index = 0; index < sizeof(sandbox.before); ++index) {
    check(sandbox.before[index] == 0x11);
  }
  for (std::size_t index = 0; index < sizeof(sandbox.after); ++index) {
    check(sandbox.after[index] == 0x22);
  }

  // The neighbouring bytes, named, because these are the displacements a
  // mutated source would most plausibly reach for. The byte after the object is
  // the guard, so a store that ran past the end is caught rather than tolerated.
  prop_manager_set_dev_mode_006a3300(&sandbox.receiver, 0x33);
  check(sandbox.bytes()[20] == 0xee);
  check(sandbox.bytes()[21] == 0x33);
  check(sandbox.after[0] == 0x22);
  check(sandbox.before[0] == 0x11);
  prop_manager_set_dev_mode_006a3300(&sandbox.receiver, 0x44);
  check(sandbox.bytes()[0x15] == 0x44);
  check(sandbox.bytes()[0x08] == 0xee);
  check(sandbox.bytes()[0x0f] == 0xee);
  check(sandbox.bytes()[0x00] == 0xee);
  // The same number read the other way, which is the same displacement and not a
  // different one: 0x15 and 0x15*4 are not interchangeable, and only the first
  // is what 006a3304 prints.
  static_assert(0x15 != 0x15 * 4, "a scaled index is not the displacement");
  check(sandbox.bytes()[kPropManagerSlotDisplacement] == 0x44);
}

// The width is one byte, because the storing instruction is a byte store, and
// the value is the byte the caller wrote, because the loading instruction reads
// one byte. All 256 values round-trip, which is the whole of that claim; a
// source that masked, shifted, or coerced the value fails the sweep.
void test_dev_mode_stores_the_caller_byte_only() {
  DevModeSandbox sandbox{};
  for (unsigned value = 0; value < 0x100u; ++value) {
    prop_manager_set_dev_mode_006a3300(&sandbox.receiver,
                                       static_cast<std::uint8_t>(value));
    check(sandbox.bytes()[21] == static_cast<std::uint8_t>(value));
    for (std::size_t index = 0; index < 21; ++index) {
      check(sandbox.bytes()[index] == 0x00);
    }
  }
  // The byte the body does not read is not written either, so a store of the
  // caller's whole argument word would show up as a run of non-zero bytes
  // above the slot. The signature fixes the argument's width at one byte and the
  // slot at four (measured below), which is why the sweep is over bytes.
  prop_manager_set_dev_mode_006a3300(&sandbox.receiver, 0x00);
  check(sandbox.bytes()[21] == 0x00);
}

// The ABI, measured. The argument slot is four bytes wide and the body ends in
// `RET 0x4`, so the callee pops all four even though the declared parameter is
// a single byte: a cdecl caller's own words must survive the call intact.
std::uint32_t dev_mode_probe_result = 0;

void PKG_PROP_SAFE_TEST_CDECL dev_mode_stack_probe(OpaquePropManagerReceiver* manager,
                                                   std::uint8_t value, Word guard_low,
                                                   Word guard_high) {
  std::uint32_t* const canary =
      static_cast<std::uint32_t*>(__builtin_alloca(2 * sizeof(std::uint32_t)));
  canary[0] = 0xc0dec0deu;
  canary[1] = 0xfeedfaceu;
  const SetDevModeSignature entry = &prop_manager_set_dev_mode_006a3300;
  entry(manager, value);
  check(canary[0] == 0xc0dec0deu);
  check(canary[1] == 0xfeedfaceu);
  check(guard_low == 0x11223344u);
  check(guard_high == 0x55667788u);
  check(reinterpret_cast<const std::uint8_t*>(manager)[21] == value);
  dev_mode_probe_result = canary[0] ^ canary[1] ^ guard_low ^ guard_high;
}

void test_dev_mode_callee_pops_one_word() {
  DevModeSandbox sandbox{};
  std::memset(sandbox.bytes(), 0x5a, sizeof(sandbox.receiver.bytes));
  dev_mode_stack_probe(&sandbox.receiver, 0x7e, 0x11223344u, 0x55667788u);
  check(dev_mode_probe_result ==
        (0xc0dec0deu ^ 0xfeedfaceu ^ 0x11223344u ^ 0x55667788u));
  check(sandbox.bytes()[21] == 0x7e);
  check(sandbox.bytes()[20] == 0x5a);
  check(sandbox.bytes()[0] == 0x5a);
}

// ===========================================================================
// 0x006c0550
// ===========================================================================

// The gate is a whole word one displacement *below* the receiver, and it is the
// only condition in the body. Any non-zero value of any width dispatches; only
// zero short-circuits, and then nothing at all is consulted.
void test_flush_gate_is_a_whole_word_below_the_receiver() {
  const Word nonzero[] = {0x00000001u, 0x00000100u, 0x01000000u, 0x00010000u,
                          0x80000000u, 0x7f7f7f7fu, 0xffffffffu};
  for (const Word value : nonzero) {
    reset_fixture(value, 0xffffffffu);
    expect_called_order(kEsp8Word, kEsp4Word);
    state.expected_write_object = fixture.first_object();
    state.write_result = 0x5b;
    flush_checked();
    expect({"access", "write-first"});
  }

  reset_fixture(0, 0xffffffffu);
  expect_called_order(kEsp8Word, kEsp4Word);
  state.write_result = 0x5b;
  check(record_write_flush_006c0550(fixture.receiver(), kEsp4Word, kEsp8Word) == 0);
  expect({});
  check(state.access_calls == 0);
  check(state.write_calls == 0);
}

// The gate is a word below the receiver, not a word of it. The receiver's own
// leading word is a table pointer the body never dispatches through, and the
// four bytes the gate occupies are the four below the receiver, not the four
// above the gate.
void test_flush_gate_is_not_a_receiver_word() {
  reset_fixture(0, 0xffffffffu);
  check(fixture.receiver() == fixture.arena + 4);
  check(fixture.gate() == fixture.arena);
  check(load_word(fixture.gate()) == 0);
  check(load_word(fixture.at(0x00)) != 0);
  check(record_write_flush_006c0550(fixture.receiver(), kEsp4Word, kEsp8Word) == 0);
  expect({});

  // A non-zero gate with a receiver whose leading word is a garbage non-pointer
  // behaves identically: the gate test does not read that word.
  reset_fixture(0x1234u, 0xffffffffu);
  const Word garbage = 0xdeadbeefu;
  std::memcpy(fixture.at(0x00), &garbage, sizeof(garbage));
  expect_called_order(kEsp8Word, kEsp4Word);
  state.expected_write_object = fixture.first_object();
  state.write_result = 0x2b;
  check(record_write_flush_006c0550(fixture.receiver(), kEsp4Word, kEsp8Word) == 0x2b);
  expect({"access", "write-first"});
}

// Two levels, in the right order: the word at receiver+0x28 is a pointer, and the
// port is a word of the object that pointer names -- not the word itself, and not
// a word of the receiver. The `this` handed to both ports is the object, which
// is a different address from both the table and the receiver.
void test_flush_dispatches_through_a_table_of_another_object() {
  reset_fixture(1, 0xffffffffu);
  expect_called_order(kEsp8Word, kEsp4Word);
  state.expected_write_object = fixture.first_object();
  state.write_result = 0x71;
  flush_checked();
  expect({"access", "write-first"});
  check(state.observed_access_object == fixture.first_object());
  check(state.observed_write_object == fixture.first_object());
  check(load_slot_table(fixture.first_object()) == first_table.bytes);
  check(state.observed_access_object != load_slot_table(fixture.first_object()));
  check(state.observed_access_object != fixture.receiver());

  reset_fixture(1, 0u);
  expect_jumped_order(kEsp4Word, kEsp8Word);
  state.expected_write_object = fixture.second_object();
  state.write_result = 0x72;
  flush_checked();
  expect({"access", "write-second"});
  check(state.observed_write_object == fixture.second_object());
  check(state.observed_write_object != load_slot_table(fixture.second_object()));
  check(state.observed_write_object != fixture.receiver());
  check(state.observed_write_object != state.observed_access_object);
}

// The exact slot displacements. Every other slot of both tables is a decoy, so
// reading 0x0c instead of 0x10 or 0x30 instead of 0x38 aborts rather than
// producing a plausible answer, and the ports really do sit at the two
// displacements the listing prints.
void test_flush_uses_the_shown_slot_displacements() {
  reset_fixture(1, 0xffffffffu);
  expect_called_order(kEsp8Word, kEsp4Word);
  state.expected_write_object = fixture.first_object();
  flush_checked();
  expect({"access", "write-first"});
  void* const table = load_slot_table(fixture.first_object());
  check(port_at<AccessPort>(table, 0x10) == access_port);
  check(port_at<WritePort>(table, 0x38) == write_first_primary);
  check(port_at<AccessPort>(table, 0x0c) == decoy_access_port);
  check(port_at<WritePort>(table, 0x30) == decoy_write_port);
  check(port_at<AccessPort>(table, 0x04) == decoy_access_port);
  check(port_at<WritePort>(table, 0x34) == decoy_write_port);
  check(port_at<WritePort>(table, 0x20) == decoy_write_port);

  reset_fixture(1, 0u);
  expect_jumped_order(kEsp4Word, kEsp8Word);
  state.expected_write_object = fixture.second_object();
  flush_checked();
  expect({"access", "write-second"});
  void* const second = load_slot_table(fixture.second_object());
  check(port_at<WritePort>(second, 0x38) == write_second_primary);
  check(port_at<WritePort>(second, 0x34) == decoy_write_port);
  check(port_at<AccessPort>(second, 0x10) == access_port);
}

// Load ordering. 006c0571 re-reads the first table word after the access port
// has run, and 006c0585 re-reads the second one, so a port that replaces either
// table is what the body then dispatches through. A reconstruction that kept the
// value it loaded before the call calls the replaced port and this fails.
void test_flush_reloads_the_table_word_after_the_access_port() {
  reset_fixture(1, 0xffffffffu);
  state.replace_table_under_access = true;
  expect_called_order(kEsp8Word, kEsp4Word);
  state.expected_write_object = fixture.first_object();
  state.write_result = 0x33;
  flush_checked();
  expect({"access", "write-first-replacement"});
  check(load_slot_table(fixture.first_object()) == first_replacement_table.bytes);
  check(state.write_calls == 1);

  reset_fixture(1, 0u);
  state.replace_table_under_access = true;
  expect_jumped_order(kEsp4Word, kEsp8Word);
  state.expected_write_object = fixture.second_object();
  state.write_result = 0x44;
  flush_checked();
  expect({"access", "write-second-replacement"});
  check(load_slot_table(fixture.second_object()) == second_replacement_table.bytes);

  // Replacing only the first table cannot change the second path: that path
  // never dispatches through the first object.
  reset_fixture(1, 0u);
  state.replace_table_under_access = true;
  expect_jumped_order(kEsp4Word, kEsp8Word);
  state.expected_write_object = fixture.second_object();
  state.write_result = 0x45;
  flush_checked();
  expect({"access", "write-second-replacement"});
}

// The two ports receive the two words in opposite orders, and the listing says
// which is which. A reconstruction that normalised them to one order fails
// exactly one of these two runs, in the port, before any value is compared.
void test_flush_two_ports_receive_the_words_in_opposite_orders() {
  check(kEsp4Word != kEsp8Word);
  check(kEsp4Word != 0 && kEsp8Word != 0);

  reset_fixture(1, 0xffffffffu);
  expect_called_order(kEsp8Word, kEsp4Word);
  state.expected_write_object = fixture.first_object();
  state.write_result = 0x01;
  check(record_write_flush_006c0550(fixture.receiver(), kEsp4Word, kEsp8Word) == 0x01);
  expect({"access", "write-first"});

  reset_fixture(1, 0u);
  expect_jumped_order(kEsp4Word, kEsp8Word);
  state.expected_write_object = fixture.second_object();
  state.write_result = 0x02;
  check(record_write_flush_006c0550(fixture.receiver(), kEsp4Word, kEsp8Word) == 0x02);
  expect({"access", "write-second"});

  // Each run pins the order in the port itself, so the checks above did not pass
  // because both words were interchangeable: they are not, by construction.
  check(state.expected_first_argument != state.expected_second_argument);
}

// The access port is handed the object and no stack word: 006c0567 has no PUSH
// before it, so a reconstruction that pushed an argument, or that passed the
// receiver instead of the object, is observable.
void test_flush_access_port_receives_no_stack_argument() {
  reset_fixture(1, 0xffffffffu);
  expect_called_order(kEsp8Word, kEsp4Word);
  state.expected_write_object = fixture.first_object();
  const std::uint8_t* const receiver_bytes =
      static_cast<const std::uint8_t*>(fixture.receiver());
  flush_checked();
  expect({"access", "write-first"});
  check(state.observed_access_object == fixture.first_object());
  check(state.observed_access_object != fixture.receiver());
  check(static_cast<const std::uint8_t*>(state.observed_access_object) -
            receiver_bytes ==
        kRecordFirstObjectDisplacement);
}

// The return is one byte of a 32-bit result on the two dispatch paths, and the
// zero 006c0553 writes on the short-circuit. The three bytes above are dropped,
// which is the width claim the source makes: a source that widened its return,
// returned the access port's result, or returned a pointer instead of the result
// fails the sweep.
void test_flush_returns_the_low_byte_of_the_write_result() {
  struct Case {
    std::int32_t port_result;
    std::uint8_t expected;
  };
  const Case cases[] = {
      {0, 0x00},
      {1, 0x01},
      {0x7f, 0x7f},
      {0xff, 0xff},
      {0x100, 0x00},
      {0x1234, 0x34},
      {0x00ff00, 0x00},
      {0x00000101, 0x01},
      {-1, 0xff},
      {-256, 0x00},
      {0x0000ffff, 0xff},
      {static_cast<std::int32_t>(0xffffff00u), 0x00},
  };
  for (const Case& item : cases) {
    reset_fixture(1, 0xffffffffu);
    expect_called_order(kEsp8Word, kEsp4Word);
    state.expected_write_object = fixture.first_object();
    state.write_result = item.port_result;
    check(record_write_flush_006c0550(fixture.receiver(), kEsp4Word, kEsp8Word) ==
          item.expected);
    expect({"access", "write-first"});

    reset_fixture(1, 0u);
    expect_jumped_order(kEsp4Word, kEsp8Word);
    state.expected_write_object = fixture.second_object();
    state.write_result = item.port_result;
    check(record_write_flush_006c0550(fixture.receiver(), kEsp4Word, kEsp8Word) ==
          item.expected);
    expect({"access", "write-second"});
  }

  // The access port's own result chooses the path and is not this body's
  // result: 006c0569 TEST EAX,EAX is a branch on it, and the byte that comes back
  // is the one the write port produced. A reconstruction that returned the
  // access port's result, or that tested it the other way round, fails both of
  // these.
  reset_fixture(1, 0u);
  expect_jumped_order(kEsp4Word, kEsp8Word);
  state.expected_write_object = fixture.second_object();
  state.access_result = 0u;
  state.write_result = 0xefu;
  check(record_write_flush_006c0550(fixture.receiver(), kEsp4Word, kEsp8Word) == 0xef);
  expect({"access", "write-second"});

  // The other direction: a non-zero access result takes the first path, and the
  // byte returned is that path's write port's, even though the other object's
  // port is installed and would have produced something else.
  reset_fixture(1, 0xffffffffu);
  expect_called_order(kEsp8Word, kEsp4Word);
  state.expected_write_object = fixture.first_object();
  state.access_result = 0x00000001u;
  state.write_result = 0x1eu;
  check(record_write_flush_006c0550(fixture.receiver(), kEsp4Word, kEsp8Word) == 0x1e);
  expect({"access", "write-first"});
}

// The body writes nothing: every write in it belongs to a port. A
// reconstruction that cached the table word back into the receiver, or that
// cleared the gate, changes the fixture and fails here.
void test_flush_leaves_the_receiver_byte_identical() {
  reset_fixture(0x0fu, 0xffffffffu);
  const FlushFixture before = fixture;
  expect_called_order(kEsp8Word, kEsp4Word);
  state.expected_write_object = fixture.first_object();
  state.write_result = 0x5au;
  flush_checked();
  expect({"access", "write-first"});
  check(std::memcmp(&fixture, &before, sizeof(fixture)) == 0);

  expect_jumped_order(kEsp4Word, kEsp8Word);
  state.expected_write_object = fixture.second_object();
  state.access_result = 0u;
  flush_checked();
  expect({"access", "write-first", "access", "write-second"});
  check(std::memcmp(&fixture, &before, sizeof(fixture)) == 0);
}

// The stack, measured. Both paths leave through a `RET 0x8` or through a tail
// jump the port completes, so a cdecl caller's own words survive and exactly two
// words are gone.
std::uint32_t flush_probe_result = 0;

void PKG_PROP_SAFE_TEST_CDECL flush_stack_probe(void* receiver, Word argument_at_esp4,
                                                Word argument_at_esp8, Word guard_low,
                                                Word guard_high) {
  std::uint32_t* const canary =
      static_cast<std::uint32_t*>(__builtin_alloca(2 * sizeof(std::uint32_t)));
  canary[0] = 0xc0dec0deu;
  canary[1] = 0xfeedfaceu;
  const FlushSignature entry = &record_write_flush_006c0550;
  const std::uint8_t produced = entry(receiver, argument_at_esp4, argument_at_esp8);
  check(canary[0] == 0xc0dec0deu);
  check(canary[1] == 0xfeedfaceu);
  check(guard_low == 0x11223344u);
  check(guard_high == 0x55667788u);
  check(produced == 0x5au);
  flush_probe_result = canary[0] ^ canary[1] ^ guard_low ^ guard_high;
}

void test_flush_callee_pops_two_words() {
  reset_fixture(1, 0xffffffffu);
  expect_called_order(kEsp8Word, kEsp4Word);
  state.expected_write_object = fixture.first_object();
  state.write_result = 0x5au;
  flush_stack_probe(fixture.receiver(), kEsp4Word, kEsp8Word, 0x11223344u, 0x55667788u);
  check(flush_probe_result ==
        (0xc0dec0deu ^ 0xfeedfaceu ^ 0x11223344u ^ 0x55667788u));
  expect({"access", "write-first"});

  // The same through the tail-jump path, where the port rather than the body
  // completes the return, and where the frame is restored first.
  reset_fixture(1, 0u);
  expect_jumped_order(kEsp4Word, kEsp8Word);
  state.expected_write_object = fixture.second_object();
  state.write_result = 0x5au;
  flush_stack_probe(fixture.receiver(), kEsp4Word, kEsp8Word, 0x11223344u, 0x55667788u);
  check(flush_probe_result ==
        (0xc0dec0deu ^ 0xfeedfaceu ^ 0x11223344u ^ 0x55667788u));
  expect({"access", "write-second"});
}

// No null test exists in the body: 006c055b/0x585 load the table word and read
// the slot through it with nothing tested in between, so a null table word
// faults. Asserting the fault is asserting the absence of a guard, and a
// reconstruction that added one would stop faulting and fail here.
void expect_faults(void* expected_object) {
  check(expected_object != nullptr);
  const pid_t child = fork();
  check(child >= 0);
  if (child == 0) {
    static_cast<void>(
        record_write_flush_006c0550(fixture.receiver(), kEsp4Word, kEsp8Word));
    _exit(0);
  }
  int status = 0;
  check(waitpid(child, &status, 0) == child);
  check(WIFSIGNALED(status));
  check(WTERMSIG(status) == SIGSEGV);
}

void test_flush_dispatches_without_a_null_test() {
  void* const null_table = nullptr;

  reset_fixture(1, 0xffffffffu);
  std::memcpy(fixture.first_object(), &null_table, sizeof(null_table));
  expect_faults(fixture.first_object());

  reset_fixture(1, 0u);
  std::memcpy(fixture.second_object(), &null_table, sizeof(null_table));
  expect_faults(fixture.second_object());
}

}

}

int main() {
  using namespace openspore::reconstruction::pkg_prop_resource_safe_wave9;
  test_dev_mode_lands_on_displacement_0x15();
  test_dev_mode_stores_the_caller_byte_only();
  test_dev_mode_callee_pops_one_word();
  test_flush_gate_is_a_whole_word_below_the_receiver();
  test_flush_gate_is_not_a_receiver_word();
  test_flush_dispatches_through_a_table_of_another_object();
  test_flush_uses_the_shown_slot_displacements();
  test_flush_reloads_the_table_word_after_the_access_port();
  test_flush_two_ports_receive_the_words_in_opposite_orders();
  test_flush_access_port_receives_no_stack_argument();
  test_flush_returns_the_low_byte_of_the_write_result();
  test_flush_leaves_the_receiver_byte_identical();
  test_flush_callee_pops_two_words();
  test_flush_dispatches_without_a_null_test();
  return 0;
}

#undef PKG_PROP_SAFE_TEST_CDECL
#undef PKG_PROP_SAFE_TEST_THISCALL
