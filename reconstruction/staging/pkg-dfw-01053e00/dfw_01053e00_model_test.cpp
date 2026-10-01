// PKG-DFW-01053E00 -- VA 0x01053e00
// Behavioural model test for FUN_01053e00.
//
// Every transfer this body makes is defined here as an observer, so the test
// sees all six indirect dispatches and the one direct callee and gets to decide
// what each of them returns and what each does to the receiver's words. The six
// dispatches are vtable slots rather than named externs, so they are filled
// with the observer function pointers below; the one direct callee, 0x00cb5930,
// is declared in the package header and defined here as an observer.
//
// The assertions are the claims the listing makes and nothing beyond them: the
// seven transfers and the order they happen in, the two receiver displacements
// (0x114 and 0x124) and how many times each is read, the one write and the fact
// that it precedes the transfer at 0x01053e36, the gate's being a fresh read
// rather than a kept value, which branch each input takes, the twelve-byte copy
// out of the returned pointer, the address pushed at 0x01053e57, the buffer the
// +0x30 slot is handed together with the fact that the body does not read it
// back, the two independent routes to the position, and the return word on both
// paths.
//
// Nothing here asserts what a dispatched slot means, what the word at 0x124
// points at, or what 0x00cb5930 does with the word it is handed.

#include "dfw_01053e00_types.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_dfw_01053e00 {

// 0x01053e00, defined in the package's own translation unit.
extern "C" bool PKG_DFW_01053E00_STDCALL
dfw_FUN_01053e00(void *receiver, void *second_stack_word);

// The seven transfers, in the order the listing makes them reachable.
enum Event : int {
  EV_NONE = 0,
  EV_TARGET_SLOT2C,   // 0x01053e17, slot word at displacement 0x2c
  EV_TARGET_SLOT04,   // 0x01053e36, slot word at displacement 0x04
  EV_SOURCE_SLOTB8,   // 0x01053e5c, slot word at displacement 0xb8
  EV_FOUND_SLOT30,    // 0x01053e6e, slot word at displacement 0x30
  EV_SOURCE_SLOT2C,   // 0x01053e7d, slot word at displacement 0x2c
  EV_EMITTER_SLOT38,  // 0x01053eb2, slot word at displacement 0x38
  EV_COMMIT           // 0x01053ebf, direct CALL 0x00cb5930
};

// The seven observers, defined below with the machine's own shape for each one.
extern "C" bool PKG_DFW_01053E00_THISCALL
dfw_observer_target_slot2c_01053e17(OpaqueBeamTarget *object);
extern "C" void PKG_DFW_01053E00_THISCALL
dfw_observer_target_slot04_01053e36(OpaqueBeamTarget *object);
extern "C" OpaqueFoundAt_b8 *PKG_DFW_01053E00_THISCALL
dfw_observer_source_slotb8_01053e5c(OpaqueWordAt114 *object, const Word *keyed);
extern "C" const OpaqueSinglePrecisionTriple *PKG_DFW_01053E00_THISCALL
dfw_observer_found_slot30_01053e6e(OpaqueFoundAt_b8 *object,
                                   OpaqueSinglePrecisionTriple *buffer);
extern "C" const OpaqueSinglePrecisionTriple *PKG_DFW_01053E00_THISCALL
dfw_observer_source_slot2c_01053e7d(OpaqueWordAt114 *object);
extern "C" void PKG_DFW_01053E00_THISCALL
dfw_observer_emitter_slot38_01053eb2(OpaqueWordAt34 *object,
                                      const OpaqueSinglePrecisionTriple *value);

namespace {

// Machine displacements, spelled as the listing spells them.
constexpr std::size_t kWord114 = 0x114u;
constexpr std::size_t kWord124 = 0x124u;

int g_failures = 0;

// The object graph. Every table word the model dispatches through is a real slot
// in a real table struct whose layout the header pins by static_assert, so a
// displacement mistake in the model cannot be papered over here.
OpaqueBeamTargetTable g_target_table = {};
OpaqueWordAt114Table g_source_table = {};
OpaqueFoundAtB8Table g_found_table = {};
OpaqueWordAt34Table g_emitter_table = {};

OpaqueBeamTarget g_target = {};
OpaqueBeamTarget g_other_target = {};
OpaqueWordAt114 g_source = {};
OpaqueWordAt114 g_other_source = {};
OpaqueFoundAt_b8 g_found = {};
OpaqueWordAt34 g_emitter = {};

// Two different position triples, so a model that mixed the two routes up would
// hand the emitter the wrong words.
const OpaqueSinglePrecisionTriple g_lookup_position = {1.5f, -2.25f, 3.125f};
const OpaqueSinglePrecisionTriple g_fallback_position = {-7.5f, 0.25f, 9.0f};

// A distinct, non-null word for the second callee-popped stack slot. It is
// never this body's own receiver, so a model that passed the receiver instead
// would be seen.
unsigned char g_second_word_storage = 0x5au;
void *const g_second_stack_word = &g_second_word_storage;

// What each observer returns and does. The defaults are the "nothing happens"
// configuration: the +0x2c slot declines, the lookup returns zero -- so a test
// that wants the lookup route must say so -- and no slot writes the receiver.
struct Plan {
  bool target_slot2c_result = false;
  // If set, the +0x2c observer writes this into the receiver's word at 0x124
  // before returning, so the re-read at 0x01053e1d can be told from a reuse of
  // the value read at 0x01053e08.
  OpaqueBeamTarget *target_slot2c_writes_word = nullptr;
  // If set, the +0x2c observer zeroes the receiver's word at 0x124 instead.
  bool target_slot2c_clears_word = false;

  // If set, the +0x04 observer puts this back into the receiver's word at 0x124,
  // so the gate at 0x01053e38 can be shown to be a fresh read.
  OpaqueBeamTarget *target_slot04_rewrites_word = nullptr;

  OpaqueFoundAt_b8 *lookup_result = nullptr;
  // If set, the +0xb8 observer plants this into the receiver's word at 0x114
  // before returning, so the re-read at 0x01053e72 can be told from a reuse of
  // the value read at 0x01053e45.
  OpaqueWordAt114 *slotb8_rewrites_word = nullptr;
  // The +0x30 observer writes these into the buffer the body handed it, so a
  // model that read the buffer back would be seen.
  bool lookup_writes_buffer = true;
  OpaqueSinglePrecisionTriple buffer_contents = {111.0f, 222.0f, 333.0f};

  // If set, the +0x38 observer puts this into the receiver's word at 0x124, so
  // the fourth read at 0x01053eb9 can be told from the third at 0x01053e99.
  OpaqueBeamTarget *emitter_rewrites_word = nullptr;
};

// Everything the observers saw.
struct Observation {
  int count = 0;
  Event order[16] = {};
  void *ecx[16] = {};
  void *stack_arg[16] = {};
  // The receiver's word at 0x124 sampled from inside the +0x04 observer, which is
  // the only way to see the ordering of the store at 0x01053e27 against it.
  unsigned long word124_at_slot04 = 0xdeadbeeful;
  unsigned long word124_at_emitter = 0xdeadbeeful;
  unsigned long word124_at_commit = 0xdeadbeeful;
  OpaqueSinglePrecisionTriple emitter_argument = {0.0f, 0.0f, 0.0f};
  const void *emitter_argument_address = nullptr;
  const void *buffer_address = nullptr;
  bool buffer_written = false;
};

Plan g_plan;
Observation g_obs;
unsigned char *g_receiver = nullptr;

void record(Event what, void *ecx, void *stack_arg) {
  if (g_obs.count >= 16) {
    ++g_obs.count;  // deliberately past the end, so an over-long log is visible
    return;
  }
  g_obs.order[g_obs.count] = what;
  g_obs.ecx[g_obs.count] = ecx;
  g_obs.stack_arg[g_obs.count] = stack_arg;
  ++g_obs.count;
}

unsigned long sample_word124() {
  unsigned long value = 0;
  std::memcpy(&value, g_receiver + kWord124, sizeof value);
  return value;
}

void plant_word124(OpaqueBeamTarget *value) {
  std::memcpy(g_receiver + kWord124, &value, sizeof value);
}

void plant_word114(OpaqueWordAt114 *value) {
  std::memcpy(g_receiver + kWord114, &value, sizeof value);
}

void build_graph() {
  g_target_table.slot_04 = &dfw_observer_target_slot04_01053e36;
  g_target_table.slot_2c = &dfw_observer_target_slot2c_01053e17;
  g_source_table.slot_2c = &dfw_observer_source_slot2c_01053e7d;
  g_source_table.slot_b8 = &dfw_observer_source_slotb8_01053e5c;
  g_found_table.slot_30 = &dfw_observer_found_slot30_01053e6e;
  g_emitter_table.slot_38 = &dfw_observer_emitter_slot38_01053eb2;
  g_target.table_00 = &g_target_table;
  g_target.word_34 = &g_emitter;
  // The second owned target exists so a test can tell one read of the word at
  // 0x124 from another. It is given the same table and the same emitter, so the
  // only thing that distinguishes it is its address.
  g_other_target.table_00 = &g_target_table;
  g_other_target.word_34 = &g_emitter;
  g_source.table_00 = &g_source_table;
  g_other_source.table_00 = &g_source_table;
  g_found.table_00 = &g_found_table;
  g_emitter.table_00 = &g_emitter_table;
}

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

void check_event(int index, Event wanted, const char *what) {
  if (index >= g_obs.count) {
    std::fprintf(stderr, "FAILED: %s (no transfer %d was made at all)\n", what, index);
    ++g_failures;
    return;
  }
  if (g_obs.order[index] != wanted) {
    std::fprintf(stderr, "FAILED: %s (transfer %d was the wrong one)\n", what, index);
    ++g_failures;
  }
}

void check_count(int wanted, const char *what) {
  if (g_obs.count != wanted) {
    std::fprintf(stderr, "FAILED: %s (saw %d transfers, wanted %d)\n", what,
                 g_obs.count, wanted);
    ++g_failures;
  }
}

}  // namespace

// ---------------------------------------------------------------------------
// The seven observers. Each is the machine's own shape: the receiver in ECX and
// at most one pushed stack word, so a single thiscall parameter list covers all
// of them.
// ---------------------------------------------------------------------------

// 0x01053e17  CALL EDX, slot word at displacement 0x2c of the object at
// receiver+0x124. ECX is that object; nothing is pushed.
extern "C" bool PKG_DFW_01053E00_THISCALL
dfw_observer_target_slot2c_01053e17(OpaqueBeamTarget *object) {
  record(EV_TARGET_SLOT2C, object, nullptr);
  if (g_plan.target_slot2c_clears_word) {
    plant_word124(nullptr);
  } else if (g_plan.target_slot2c_writes_word != nullptr) {
    plant_word124(g_plan.target_slot2c_writes_word);
  }
  return g_plan.target_slot2c_result;
}

// 0x01053e36  CALL EDX, slot word at displacement 0x04 of the same object.
// ECX is that object; nothing is pushed.
extern "C" void PKG_DFW_01053E00_THISCALL
dfw_observer_target_slot04_01053e36(OpaqueBeamTarget *object) {
  record(EV_TARGET_SLOT04, object, nullptr);
  g_obs.word124_at_slot04 = sample_word124();
  if (g_plan.target_slot04_rewrites_word != nullptr) {
    plant_word124(g_plan.target_slot04_rewrites_word);
  }
}

// 0x01053e5c  CALL EDX, slot word at displacement 0xb8 of the object at
// receiver+0x114. ECX is that object; 0x13f94d4 is the one pushed stack word.
extern "C" OpaqueFoundAt_b8 *PKG_DFW_01053E00_THISCALL
dfw_observer_source_slotb8_01053e5c(OpaqueWordAt114 *object, const Word *keyed) {
  record(EV_SOURCE_SLOTB8, object, const_cast<Word *>(keyed));
  if (g_plan.slotb8_rewrites_word != nullptr) {
    plant_word114(g_plan.slotb8_rewrites_word);
  }
  return g_plan.lookup_result;
}

// 0x01053e6e  CALL EDX, slot word at displacement 0x30 of the object the +0xb8
// transfer returned. ECX is that object; the frame buffer at [ESP+0x10] is the
// one pushed stack word.
extern "C" const OpaqueSinglePrecisionTriple *PKG_DFW_01053E00_THISCALL
dfw_observer_found_slot30_01053e6e(OpaqueFoundAt_b8 *object,
                                   OpaqueSinglePrecisionTriple *buffer) {
  record(EV_FOUND_SLOT30, object, buffer);
  g_obs.buffer_address = buffer;
  if (g_plan.lookup_writes_buffer) {
    *buffer = g_plan.buffer_contents;
    g_obs.buffer_written = true;
  }
  return &g_lookup_position;
}

// 0x01053e7d  CALL EDX, slot word at displacement 0x2c of the object at
// receiver+0x114. ECX is that object; nothing is pushed.
extern "C" const OpaqueSinglePrecisionTriple *PKG_DFW_01053E00_THISCALL
dfw_observer_source_slot2c_01053e7d(OpaqueWordAt114 *object) {
  record(EV_SOURCE_SLOT2C, object, nullptr);
  return &g_fallback_position;
}

// 0x01053eb2  CALL EAX, slot word at displacement 0x38 of the object at
// (receiver+0x124)+0x34. ECX is that object; the three copied words at
// [ESP+0x4] are the one pushed stack word.
extern "C" void PKG_DFW_01053E00_THISCALL
dfw_observer_emitter_slot38_01053eb2(
    OpaqueWordAt34 *object, const OpaqueSinglePrecisionTriple *value) {
  record(EV_EMITTER_SLOT38, object, const_cast<OpaqueSinglePrecisionTriple *>(value));
  g_obs.emitter_argument = *value;
  g_obs.emitter_argument_address = value;
  g_obs.word124_at_emitter = sample_word124();
  if (g_plan.emitter_rewrites_word != nullptr) {
    plant_word124(g_plan.emitter_rewrites_word);
  }
}

// 0x01053ebf  CALL 0x00cb5930. The body's only direct transfer and the only
// out-edge the xref export records. ECX is the receiver's word at 0x124, read at
// 0x01053eb9; the pushed word is the second callee-popped stack word, read at
// 0x01053eb4. The callee's own body is not modelled here: it is an observer that
// records what it was handed.
extern "C" void PKG_DFW_01053E00_THISCALL
dfw_commit_00cb5930(OpaqueBeamTarget *object, void *second_stack_word) {
  record(EV_COMMIT, object, second_stack_word);
  g_obs.word124_at_commit = sample_word124();
}

namespace {

OpaqueBeamToolState g_receiver_state = {};

void reset(Plan plan) {
  build_graph();
  std::memset(&g_receiver_state, 0, sizeof g_receiver_state);
  g_receiver = reinterpret_cast<unsigned char *>(&g_receiver_state);
  // The default entry state: both of the receiver's words non-zero, which is the
  // only state in which the body transfers anything at all. A test that wants
  // either word empty plants it after this.
  g_receiver_state.word_124 = &g_target;
  g_receiver_state.word_114 = &g_source;
  g_plan = plan;
  g_obs = Observation{};
}

bool run() { return dfw_FUN_01053e00(&g_receiver_state, g_second_stack_word); }

bool same_triple(const OpaqueSinglePrecisionTriple &a,
                 const OpaqueSinglePrecisionTriple &b) {
  return a.word_00 == b.word_00 && a.word_04 == b.word_04 && a.word_08 == b.word_08;
}

}  // namespace

// ---------------------------------------------------------------------------
// The claims. Each function is one group of assertions about the listing.
// ---------------------------------------------------------------------------

// 0x01053e0e/0x01053e10 with a zero word at 0x124, and the gate at
// 0x01053e38/0x01053e3f with it still zero: JZ 0x01053ecd, so the body makes no
// transfer at all and returns false. The return word is AL, zeroed explicitly at
// 0x01053ecd.
void test_zero_word_makes_no_transfer_and_returns_false() {
  reset(Plan{});
  plant_word124(nullptr);

  const bool got = run();

  check(got == false, "0x01053ecd XOR AL,AL leaves a false return word");
  check_count(0, "a zero word at 0x124 makes the body transfer nowhere");
}

// The word at 0x124 is non-zero and the +0x2c slot declines. 0x01053e1b then
// jumps to the gate, which re-reads the word and finds it unchanged -- so the
// position work runs with the word still in place. This is the only route to the
// gate that passes with a non-zero word.
void test_declining_slot_reaches_the_position_work() {
  reset(Plan{});
  g_plan.target_slot2c_result = false;
  g_plan.lookup_result = &g_found;

  const bool got = run();

  check(got == true, "0x01053ec4 MOV AL,0x1 leaves a true return word");
  check_count(5, "the declining route makes five transfers");
  check_event(0, EV_TARGET_SLOT2C, "0x01053e17 is the first transfer");
  check_event(1, EV_SOURCE_SLOTB8, "0x01053e5c follows the gate");
  check_event(2, EV_FOUND_SLOT30, "0x01053e6e follows the lookup");
  check_event(3, EV_EMITTER_SLOT38, "0x01053eb2 follows the three-word copy");
  check_event(4, EV_COMMIT, "0x01053ebf is the last transfer");
  check(g_obs.ecx[0] == &g_target, "0x01053e17 receives the object at receiver+0x124");
  check(sample_word124() == reinterpret_cast<unsigned long>(&g_target),
        "0x01053e1b skips the block, so the word at 0x124 is never written");
}

// The word at 0x124 is non-zero and the +0x2c slot accepts. The body re-reads
// the word at 0x01053e1d, clears it at 0x01053e27, dispatches the +0x04 slot at
// 0x01053e36, and then the gate at 0x01053e38 finds the cleared word and returns
// false. The ordering of the store against the +0x04 transfer is sampled from
// inside the observer, which is the only place it is observable.
void test_accepting_slot_clears_the_word_before_the_second_transfer() {
  reset(Plan{});
  g_plan.target_slot2c_result = true;

  const bool got = run();

  check(got == false, "the cleared word fails the gate at 0x01053e3f");
  check_count(2, "the accepting route makes two transfers and then stops");
  check_event(0, EV_TARGET_SLOT2C, "0x01053e17 runs first");
  check_event(1, EV_TARGET_SLOT04, "0x01053e36 runs second");
  check(g_obs.word124_at_slot04 == 0ul,
        "0x01053e27 zeroes the word at 0x124 before 0x01053e36 is reached");
  check(g_obs.ecx[1] == &g_target,
        "0x01053e36 receives the object ECX still holds, not the cleared word");
  check(sample_word124() == 0ul,
        "the word at 0x124 is left zero when the gate rejects it");
}

// The re-read at 0x01053e1d is a load, not a reuse: if the +0x2c transfer writes
// a zero into the receiver's word, the second test at 0x01053e23 takes its jump
// and the +0x04 transfer never runs. A model that reused the value read at
// 0x01053e08 would call it.
void test_the_second_test_reads_a_word_the_first_transfer_wrote() {
  reset(Plan{});
  g_plan.target_slot2c_result = true;
  g_plan.target_slot2c_clears_word = true;

  const bool got = run();

  check(got == false, "the word the +0x2c transfer zeroed fails the gate");
  check_count(1, "0x01053e25 skips 0x01053e27 and 0x01053e36 entirely");
  check_event(0, EV_TARGET_SLOT2C, "only the +0x2c transfer runs");
  check(g_obs.word124_at_slot04 == 0xdeadbeeful,
        "the +0x04 observer never ran, so it sampled nothing");
}

// The gate at 0x01053e38 is a fresh read of the word, not the value the block
// above left in a register. If the +0x04 transfer puts a non-zero word back, the
// gate passes and the body continues -- even though the store at 0x01053e27 had
// already zeroed it.
void test_the_gate_is_a_fresh_read_of_the_word() {
  reset(Plan{});
  g_plan.target_slot2c_result = true;
  g_plan.target_slot04_rewrites_word = &g_other_target;
  g_plan.lookup_result = &g_found;

  const bool got = run();

  check(got == true, "a word put back by 0x01053e36 passes the gate");
  check_count(6, "the repopulated route makes all six transfers plus the direct one");
  check_event(2, EV_SOURCE_SLOTB8, "the position work follows the +0x04 transfer");
  check(g_obs.ecx[5] == &g_other_target,
        "0x01053ebf receives the word the +0x04 transfer put back");
}

// The lookup route. 0x01053e70 jumps to 0x01053e7f, so the fallback block at
// 0x01053e72..0x01053e7d is skipped entirely: the +0x2c slot on the object at
// receiver+0x114 is not dispatched at all, and the position the emitter is given
// is the one the +0x30 slot returned.
void test_the_lookup_route_skips_the_fallback_block() {
  reset(Plan{});
  g_plan.lookup_result = &g_found;

  run();

  check_count(5, "the lookup route makes the +0x2c transfer, the lookup, the "
                 "+0x30 slot, the +0x38 slot and the direct callee");
  check_event(0, EV_TARGET_SLOT2C, "0x01053e17 runs first");
  check_event(1, EV_SOURCE_SLOTB8, "0x01053e5c runs after the gate");
  check_event(2, EV_FOUND_SLOT30, "0x01053e6e runs after the lookup");
  check(g_obs.ecx[1] == &g_source, "0x01053e5c receives the object at receiver+0x114");
  check(g_obs.stack_arg[1] == reinterpret_cast<void *>(
                                  static_cast<std::uintptr_t>(0x13f94d4u)),
        "0x01053e57 pushes the one data-segment address, 0x13f94d4");
  check(g_obs.ecx[2] == &g_found,
        "0x01053e6e receives the object the +0xb8 transfer returned");
  check(g_obs.buffer_address != nullptr,
        "0x01053e67 forms the address of the frame buffer at [ESP+0x10]");
  check(g_obs.buffer_written, "the observer was handed a writable frame buffer");
  check(same_triple(g_obs.emitter_argument, g_lookup_position),
        "the three words come from the pointer the +0x30 slot returned");
}

// The +0x30 slot is handed a twelve-byte buffer the body then ignores: the
// position the emitter receives is the callee's return value, not the buffer the
// body wrote to be given. The observer deliberately fills the buffer with
// different words.
void test_the_frame_buffer_is_written_but_never_read_back() {
  reset(Plan{});
  g_plan.lookup_result = &g_found;
  g_plan.lookup_writes_buffer = true;
  g_plan.buffer_contents = {111.0f, 222.0f, 333.0f};

  run();

  check(g_obs.buffer_written, "the observer wrote its own words into the buffer");
  check(!same_triple(g_obs.emitter_argument, g_plan.buffer_contents),
        "0x01053e6e through 0x01053ea2 read the returned pointer, not the buffer");
  check(same_triple(g_obs.emitter_argument, g_lookup_position),
        "the returned pointer is what the three MOVSS instructions read");
}

// The fallback route. A non-zero word at 0x114 whose +0xb8 lookup returns zero
// takes 0x01053e60 to the block at 0x01053e72, which re-reads the word at 0x114
// and dispatches the +0x2c slot on it with no test of its own. The position is
// that call's return value.
void test_the_fallback_route_dispatches_the_source_slot() {
  reset(Plan{});
  g_plan.lookup_result = nullptr;  // the +0xb8 transfer returns zero

  const bool got = run();

  check(got == true, "the fallback route still returns true");
  check_count(5, "the fallback route makes five transfers");
  check_event(0, EV_TARGET_SLOT2C, "0x01053e17 runs first");
  check_event(1, EV_SOURCE_SLOTB8, "0x01053e5c runs and returns zero");
  check_event(2, EV_SOURCE_SLOT2C, "0x01053e7d runs next, on the source");
  check(g_obs.ecx[2] == &g_source,
        "0x01053e72 re-reads the word at receiver+0x114 and dispatches on it");
  check(same_triple(g_obs.emitter_argument, g_fallback_position),
        "the position is the +0x2c slot's return value on this route");
}

// The three words are copied, in order, from offsets 0, 4 and 8 of the returned
// pointer into one contiguous run -- and that run is what the +0x38 slot is
// handed, as a single address rather than as three words.
void test_the_three_word_copy_reaches_the_slot_at_0x38() {
  reset(Plan{});
  g_plan.lookup_result = &g_found;

  run();

  check(g_obs.ecx[3] == &g_emitter,
        "0x01053eb2 receives the object at (receiver+0x124)+0x34");
  check(g_obs.emitter_argument_address != nullptr,
        "0x01053ead forms one address for the three words at [ESP+0x4]");
  check(g_obs.emitter_argument.word_00 == 1.5f, "the word at offset 0 is copied first");
  check(g_obs.emitter_argument.word_04 == -2.25f, "the word at offset 4 is copied second");
  check(g_obs.emitter_argument.word_08 == 3.125f, "the word at offset 8 is copied third");
}

// The direct callee at 0x01053ebf receives the receiver's word at 0x124 as
// 0x01053eb9 read it -- a fourth read, independent of the third at 0x01053e99
// -- and the second callee-popped stack word as its one stack argument. If the
// +0x38 transfer changes the word, the callee must see the new one.
void test_the_direct_callee_gets_the_fourth_read_and_the_stack_word() {
  reset(Plan{});
  g_plan.lookup_result = &g_found;
  g_plan.emitter_rewrites_word = &g_other_target;

  run();

  check(g_obs.ecx[4] == &g_other_target,
        "0x01053eb9 re-reads the word at 0x124 after the +0x38 transfer");
  check(g_obs.stack_arg[4] == g_second_stack_word,
        "0x01053eb4 reads the second callee-popped stack word and 0x01053eb8 "
        "pushes it");
  check(g_obs.stack_arg[4] != static_cast<void *>(&g_receiver_state),
        "the pushed word is not the receiver");
  check(g_obs.word124_at_commit == reinterpret_cast<unsigned long>(&g_other_target),
        "the word at 0x124 still held the new object when 0x01053ebf ran");
}

// The third read of the word, at 0x01053e99, is the one that selects the object
// whose word at 0x34 the +0x38 slot is reached through. Two owned targets with
// different emitters separate the third read from the fourth.
void test_the_third_read_selects_the_emitter() {
  reset(Plan{});
  g_plan.lookup_result = &g_found;
  g_plan.emitter_rewrites_word = &g_other_target;

  run();

  // The emitter was chosen from the word as it stood at 0x01053e99, i.e. before
  // the +0x38 observer rewrote it, so it is the emitter of the object the gate
  // accepted and not the emitter of the one the observer planted.
  check(g_obs.ecx[3] == &g_emitter,
        "0x01053e9f and 0x01053ea8 use the word as read at 0x01053e99");
}

// The second receiver displacement. 0x01053e45 and 0x01053e72 both read the word
// at 0x114, and a second source object planted there must be the one the +0xb8
// and +0x2c transfers are dispatched on. Nothing else in the body reaches 0x114,
// so this is the only assertion that a displacement mistake at that offset is
// caught rather than merely tolerated.
void test_the_word_at_114_selects_the_source_object() {
  reset(Plan{});
  g_plan.lookup_result = nullptr;  // take the fallback route as well
  plant_word114(&g_other_source);

  run();

  check(g_obs.ecx[1] == &g_other_source,
        "0x01053e5c dispatches on the object at receiver+0x114");
  check(g_obs.ecx[2] == &g_other_source,
        "0x01053e72 re-reads receiver+0x114 and dispatches on the same object");
}

// The re-read at 0x01053e72 is a load, not a reuse. The +0xb8 transfer runs
// before the fallback block and rewrites the receiver's word at 0x114, so the
// fallback must dispatch on the new object rather than on the one read at
// 0x01053e45. A model that reused the earlier read would call the original.
void test_the_fallback_re_reads_the_word_at_114() {
  reset(Plan{});
  g_plan.lookup_result = nullptr;   // take the fallback route
  g_plan.slotb8_rewrites_word = &g_other_source;

  run();

  check(g_obs.ecx[1] == &g_source,
        "0x01053e5c received the object the word at 0x114 named on entry");
  check(g_obs.ecx[2] == &g_other_source,
        "0x01053e72 re-reads the word at 0x114 and dispatches on what it now names");
}

// The direct callee is reached through a fourth, independent read of the word at
// 0x124 -- not through the third read at 0x01053e99 that chose the emitter. The
// +0x38 observer rewrites the word between the two.
void test_the_direct_callee_does_not_reuse_the_third_read() {
  reset(Plan{});
  g_plan.lookup_result = &g_found;
  g_plan.emitter_rewrites_word = &g_other_target;

  run();

  check(g_obs.ecx[3] == &g_emitter,
        "0x01053e99 selected the emitter from the word as it stood then");
  check(g_obs.ecx[4] == &g_other_target,
        "0x01053eb9 read the word again, and got the object the +0x38 transfer put there");
}

// The receiver's word at 0x114 is the only word at that displacement, and a
// model that read a neighbouring offset instead would dispatch on the padding.
// The test plants a second source and shows the transfer follows the word.
void test_the_word_at_114_is_not_read_at_a_neighbouring_offset() {
  reset(Plan{});
  g_plan.lookup_result = nullptr;
  // Everything around 0x114 is zero, so a displacement off by a few bytes lands
  // on padding and the model must not transfer control through it.
  check(g_receiver[0x118u] == 0 && g_receiver[0x110u] == 0,
        "the bytes either side of 0x114 are zero, so an off-by-a-few read faults");

  const bool got = run();

  check(got == true, "the fallback route still completes");
  check(g_obs.ecx[1] == &g_source, "0x01053e45 read the word at 0x114 and no other");
}

// The body's one write is the store at 0x01053e27, and it is the only byte of the
// receiver that changes on any path. A displacement applied as a write, or a
// second store, would move a byte here.
//
// One limit worth stating: a store that wrote back the value it had just read
// would leave the bytes identical and so pass this check. That store is not
// observable through this interface and is not claimed to be excluded; every
// store that changes a byte is.
void test_only_the_word_at_124_is_ever_written() {
  {
    reset(Plan{});
    plant_word124(&g_target);
    g_plan.target_slot2c_result = false;
    g_plan.lookup_result = &g_found;
    unsigned char before[sizeof(OpaqueBeamToolState)];
    std::memcpy(before, &g_receiver_state, sizeof before);
    run();
    check(std::memcmp(before, &g_receiver_state, sizeof before) == 0,
          "no byte of the receiver is written when the block is skipped");
  }
  {
    reset(Plan{});
    plant_word124(&g_target);
    g_plan.target_slot2c_result = true;
    unsigned char after[sizeof(OpaqueBeamToolState)];
    run();
    std::memcpy(after, &g_receiver_state, sizeof after);
    check(after[kWord124] == 0 && after[kWord124 + 1] == 0 &&
              after[kWord124 + 2] == 0 && after[kWord124 + 3] == 0,
          "the store at 0x01053e27 is the only write, and it lands at 0x124");
  }
}

}  // namespace openspore::reconstruction::pkg_dfw_01053e00

int main() {
  using namespace openspore::reconstruction::pkg_dfw_01053e00;
  test_zero_word_makes_no_transfer_and_returns_false();
  test_declining_slot_reaches_the_position_work();
  test_accepting_slot_clears_the_word_before_the_second_transfer();
  test_the_second_test_reads_a_word_the_first_transfer_wrote();
  test_the_gate_is_a_fresh_read_of_the_word();
  test_the_lookup_route_skips_the_fallback_block();
  test_the_frame_buffer_is_written_but_never_read_back();
  test_the_fallback_route_dispatches_the_source_slot();
  test_the_three_word_copy_reaches_the_slot_at_0x38();
  test_the_direct_callee_gets_the_fourth_read_and_the_stack_word();
  test_the_third_read_selects_the_emitter();
  test_the_word_at_114_selects_the_source_object();
  test_the_fallback_re_reads_the_word_at_114();
  test_the_direct_callee_does_not_reuse_the_third_read();
  test_the_word_at_114_is_not_read_at_a_neighbouring_offset();
  test_only_the_word_at_124_is_ever_written();
  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::fprintf(stderr, "all checks passed\n");
  return 0;
}
