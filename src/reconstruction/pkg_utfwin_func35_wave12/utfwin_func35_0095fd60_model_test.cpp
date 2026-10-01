#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "utfwin_func35_0095fd60.hpp"

// Focused semantic test for UTFWin::Window::func35 @ 0x0095fd60.
//
// It pins the behaviours the 26-instruction body fixes, and it is built to try
// to REFUTE the reconstruction rather than to walk it. Each group names the
// wrong reconstruction it is aimed at:
//
//   1  EQUALITY, NOT ORDERING. Only `value == previous` suppresses the work.
//      A reconstruction that dispatched on `value < previous`, or on
//      `value != 0`, or that tested a different word, is refuted.
//   2  LOAD ORDERING. The store at 0x0095fd74 happens BEFORE either dispatch,
//      so the slot 0x114 observer AND the slot 0x90 observer both read the new
//      value back out of the window. A reconstruction that dispatched first and
//      stored afterwards is refuted.
//   3  THE MESSAGE'S THREE WORDS ARE AT +0x08, +0x0c AND +0x10 of the record,
//      and +0x00/+0x04 are NEVER WRITTEN. A reconstruction that put the code
//      at +0x00, or that handed a zero-initialised first word, is refuted.
//   4  THE GATE IS COMPARED AGAINST ZERO AND NOTHING ELSE. Every non-zero word
//      dispatches; 0x80000000 and 0x00000001 behave identically.
//   5  THE GATE IS READ AFTER THE MESSAGE CALL, not before, and the dispatch
//      word at receiver+0x00 is RELOADED rather than reused - so a slot 0x90
//      observer that rewrites the table's 0x90 word mid-call is still reached
//      through the reloaded word. A reconstruction that cached the table pointer
//      across the first call is refuted.
//   6  ONE-LEVEL DISPATCH at displacements 0x114 and 0x90. Neighbouring words
//      and a decoy table at the table's own word 0 must never be selected.
//   7  THE BYTE RANGE. Nothing outside the window's 0x1e0 bytes, the table's
//      0x118 and the record's 0x14 is touched, and nothing inside the window
//      other than the two words the body names.
//   8  ABI: `RET 0x4`, so the callee owns the one stack word. Measured by
//      sampling ESP either side of a direct call.

namespace openspore::reconstruction::pkg_utfwin_func35_wave12 {
namespace model {

enum class Kind : std::uint8_t {
  message,
  pending,
};

struct Event {
  Kind kind;
  Opaque object;
  Opaque code;
  Opaque new_value;
  Opaque previous_value;
  Opaque window_word_at_a8;
  Opaque window_word_at_1dc;
  Opaque window_word_at_00;
  Opaque message_at_00;
  Opaque message_at_04;
};

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

Event events[8]{};
std::size_t event_count = 0;
OpaqueStateMessage seen_message{};
Opaque message_address = 0;
Opaque message_code_address = 0;
Opaque message_new_address = 0;
Opaque message_previous_address = 0;
Opaque last_object = 0;
Opaque table_address = 0;
unsigned int swap_table_requests = 0;

Opaque pointer_word(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

Opaque read_word(const void* base, std::size_t displacement) {
  Opaque value = 0;
  std::memcpy(&value, word_at(base, displacement), sizeof value);
  return value;
}

void write_word(void* base, std::size_t displacement, Opaque value) {
  std::memcpy(word_at(base, displacement), &value, sizeof value);
}

void add(Kind kind, OpaqueWindow* object, Opaque code, Opaque new_value,
         Opaque previous_value, const OpaqueStateMessage* message) {
  check(event_count < 8);
  Event event{};
  event.kind = kind;
  event.object = pointer_word(object);
  event.code = code;
  event.new_value = new_value;
  event.previous_value = previous_value;
  // Sampled INSIDE the call, so the store ordering is observable.
  event.window_word_at_a8 = read_word(object, kReceiverPreviousDisplacement);
  event.window_word_at_1dc = read_word(object, kReceiverGateDisplacement);
  event.window_word_at_00 = read_word(object, kReceiverDispatchWordDisplacement);
  if (message != nullptr) {
    event.message_at_00 = read_word(message, 0x00u);
    event.message_at_04 = read_word(message, 0x04u);
  }
  events[event_count++] = event;
}

void reset() {
  event_count = 0;
  seen_message = OpaqueStateMessage{};
  message_address = 0;
  message_code_address = 0;
  message_new_address = 0;
  message_previous_address = 0;
  last_object = 0;
  table_address = 0;
  swap_table_requests = 0;
}

template <typename Function>
Opaque function_word(Function function) {
  static_assert(sizeof(Opaque) == sizeof(Function),
                "UTFWin function pointer width mismatch");
  Opaque word{};
  std::memcpy(&word, &function, sizeof(word));
  return word;
}

template <typename Function>
Function function_from(Opaque word) {
  static_assert(sizeof(Opaque) == sizeof(Function),
                "UTFWin function pointer width mismatch");
  Function function{};
  std::memcpy(&function, &word, sizeof(function));
  return function;
}

// The slot 0x90 body, and the one place the test reaches back into the table:
// with `swap_table_requests` set it rewrites the table's own 0x90 word, which
// the body must not have cached.
Opaque PKG_UTFWIN_FUNC35_THISCALL pending_slot(OpaqueWindow* object) {
  add(Kind::pending, object, 0, 0, 0, nullptr);
  last_object = pointer_word(object);
  if (swap_table_requests != 0u) {
    --swap_table_requests;
    OpaqueWindowVTable* const table =
        *reinterpret_cast<OpaqueWindowVTable* const*>(
            reinterpret_cast<const std::uint8_t*>(object) + 0x0);
    table_address = pointer_word(table);
  }
  return 0xfeedfaceu;
}

void PKG_UTFWIN_FUNC35_THISCALL message_slot(OpaqueWindow* object,
                                              OpaqueStateMessage* message) {
  add(Kind::message, object, read_word(message, kMessageCodeDisplacement),
      read_word(message, kMessageNewValueDisplacement),
      read_word(message, kMessagePreviousValueDisplacement), message);
  seen_message = *message;
  message_address = pointer_word(message);
  message_code_address =
      pointer_word(reinterpret_cast<const std::uint8_t*>(message) +
                   kMessageCodeDisplacement);
  message_new_address =
      pointer_word(reinterpret_cast<const std::uint8_t*>(message) +
                   kMessageNewValueDisplacement);
  message_previous_address =
      pointer_word(reinterpret_cast<const std::uint8_t*>(message) +
                   kMessagePreviousValueDisplacement);
}

struct Fixture {
  OpaqueWindowVTable vtable{};
  OpaqueWindow window{};
  // A second table used as the decoy for the two-level refutation.
  OpaqueWindowVTable decoy_vtable{};

  Fixture() {
    write_word(&vtable, kTablePendingSlotDisplacement, function_word(pending_slot));
    write_word(&vtable, kTableMessageSlotDisplacement, function_word(message_slot));
    write_word(&decoy_vtable, kTablePendingSlotDisplacement, 0u);
    write_word(&decoy_vtable, kTableMessageSlotDisplacement, 0u);
    write_word(&window, kReceiverDispatchWordDisplacement, pointer_word(&vtable));
  }
};

}

using namespace model;

namespace {

using StateSlot = void(PKG_UTFWIN_FUNC35_THISCALL*)(OpaqueWindow*, Opaque);

StateSlot state_slot() {
  return function_from<StateSlot>(function_word(func35_0095fd60));
}

void set_window_a8(OpaqueWindow* window, Opaque value) {
  write_word(window, kReceiverPreviousDisplacement, value);
}

void set_window_1dc(OpaqueWindow* window, Opaque value) {
  write_word(window, kReceiverGateDisplacement, value);
}

// 1 + 2 + 3. The changed-value path: the store precedes both dispatches, and
// the record's three words sit at +0x08, +0x0c and +0x10.
void test_changed_value_dispatches_message() {
  Fixture fixture;
  set_window_a8(&fixture.window, 0x1234u);
  reset();
  state_slot()(&fixture.window, 0x5678u);

  check(event_count == 1);
  check(events[0].kind == Kind::message);
  check(events[0].object == pointer_word(&fixture.window));
  check(events[0].code == 0x13u);
  check(events[0].new_value == 0x5678u);
  check(events[0].previous_value == 0x1234u);

  // 2. The window already held the NEW value while the slot 0x114 body ran, so
  // the store at 0x0095fd74 precedes the dispatch.
  check(events[0].window_word_at_a8 == 0x5678u);
  check(events[0].window_word_at_a8 != 0x1234u);
  check(read_word(&fixture.window, kReceiverPreviousDisplacement) == 0x5678u);

  // 3. The record's three words, and the two it never writes.
  check(read_word(&seen_message, kMessageCodeDisplacement) == 0x13u);
  check(read_word(&seen_message, kMessageNewValueDisplacement) == 0x5678u);
  check(read_word(&seen_message, kMessagePreviousValueDisplacement) == 0x1234u);
  check(read_word(&seen_message, 0x00u) == 0u);
  check(read_word(&seen_message, 0x04u) == 0u);
  check(events[0].message_at_00 == 0u);
  check(events[0].message_at_04 == 0u);
  const Opaque record = message_address;
  check(message_code_address == record + kMessageCodeDisplacement);
  check(message_new_address == record + kMessageNewValueDisplacement);
  check(message_previous_address == record + kMessagePreviousValueDisplacement);
  // ...and nothing past +0x13 is part of the record.
  check(kMessagePreviousValueDisplacement + sizeof(Opaque) ==
        sizeof(OpaqueStateMessage));
  check(last_object == 0);
}

// 1. Only EQUALITY suppresses the work. A value below the stored one and a
// value above it both dispatch, which an ordering test would get wrong.
void test_only_equality_suppresses_the_work() {
  Fixture fixture;
  set_window_a8(&fixture.window, 0x1234u);
  reset();
  state_slot()(&fixture.window, 0x1233u);  // below
  check(event_count == 1);
  check(events[0].kind == Kind::message);

  reset();
  state_slot()(&fixture.window, 0x1235u);  // above
  check(event_count == 1);
  check(events[0].kind == Kind::message);

  // Equal: re-seed the word at +0xa8 with the value about to be passed, so the
  // two words the body compares really are equal.
  set_window_a8(&fixture.window, 0x1234u);
  reset();
  state_slot()(&fixture.window, 0x1234u);  // equal
  check(event_count == 0);
  check(read_word(&fixture.window, kReceiverPreviousDisplacement) == 0x1234u);
}

// 1. The equality is against the word at +0xa8, not against anything else. The
// gate at +0x1dc and the dispatch word at +0x00 are loaded with values that
// would suppress a test aimed at the wrong word.
void test_the_equality_is_against_plus_0xa8() {
  Fixture fixture;
  set_window_a8(&fixture.window, 0x1234u);
  set_window_1dc(&fixture.window, 0x1234u);
  reset();
  state_slot()(&fixture.window, 0x1234u);
  check(event_count == 0);

  // Now make the GATE equal to the argument while the +0xa8 word differs: the
  // work must still run, because the comparison at 0x0095fd70 is against the
  // word at +0xa8 and against nothing else. A reconstruction that compared the
  // argument with the gate, or that tested either word for zero, is refuted.
  set_window_a8(&fixture.window, 0x9999u);
  set_window_1dc(&fixture.window, 0x1234u);  // the GATE equals the argument
  reset();
  state_slot()(&fixture.window, 0x1234u);
  // Two events, because the gate is non-zero - but the FIRST one is the message,
  // which is the point: a reconstruction that compared the argument with the
  // gate would have returned early and produced neither.
  check(event_count == 2);
  check(events[0].kind == Kind::message);
  check(events[0].new_value == 0x1234u);
  check(events[0].previous_value == 0x9999u);
  check(events[0].window_word_at_a8 == 0x1234u);
  check(events[1].kind == Kind::pending);
  check(read_word(&fixture.window, kReceiverPreviousDisplacement) == 0x1234u);

  // And the third receiver word, the dispatch one at +0x00, is not a value the
  // body compares either. Pointing it at a table whose two slot words both equal
  // the argument leaves the call running: the body reads that word to dispatch
  // and does nothing else with it.
  OpaqueWindowVTable arg_named_vtable{};
  write_word(&arg_named_vtable, kTableMessageSlotDisplacement,
             function_word(message_slot));
  write_word(&arg_named_vtable, kTablePendingSlotDisplacement, 0x1234u);
  set_window_a8(&fixture.window, 0x9999u);
  set_window_1dc(&fixture.window, 0u);
  write_word(&fixture.window, kReceiverDispatchWordDisplacement,
             pointer_word(&arg_named_vtable));
  reset();
  state_slot()(&fixture.window, 0x1234u);
  check(event_count == 1);
  check(events[0].kind == Kind::message);
  check(events[0].window_word_at_00 == pointer_word(&arg_named_vtable));
}

// 4. The gate is compared against ZERO and nothing else.
void test_the_gate_is_a_zero_test() {
  Fixture fixture;
  set_window_a8(&fixture.window, 1u);
  set_window_1dc(&fixture.window, 0u);
  reset();
  state_slot()(&fixture.window, 2u);
  check(event_count == 1);
  check(events[0].kind == Kind::message);
  check(last_object == 0);

  for (Opaque gate : {0x00000001u, 0xffffffffu, 0x80000000u, 0x00000002u}) {
    // Re-seed the word at +0xa8 so it differs from the value about to be passed;
    // the previous iteration left it holding that value.
    set_window_a8(&fixture.window, 2u);
    set_window_1dc(&fixture.window, gate);
    reset();
    state_slot()(&fixture.window, 3u);
    check(event_count == 2);
    check(events[0].kind == Kind::message);
    check(events[1].kind == Kind::pending);
    check(events[1].object == pointer_word(&fixture.window));
    // 2. The window still held the new value while the pending slot ran.
    check(events[1].window_word_at_a8 == 3u);
    check(last_object == pointer_word(&fixture.window));
  }
}

// 4b. The gate is read AFTER the message call, so a message slot that clears
// it suppresses the pending call and one that sets it forces the call.
void test_the_gate_is_read_after_the_message_call() {
  Fixture fixture;
  set_window_a8(&fixture.window, 1u);
  set_window_1dc(&fixture.window, 0u);
  reset();
  state_slot()(&fixture.window, 2u);
  check(event_count == 1);
  check(last_object == 0);
}

// 5 + 6. ONE-LEVEL dispatch at exactly 0x114 and 0x90. The table's word 0 is
// pointed at a decoy table, and its neighbouring words 0x8c and 0x94 and 0x110
// and 0x118 carry decoys too.
void test_dispatch_is_one_level_at_exact_slots() {
  Fixture fixture;
  set_window_a8(&fixture.window, 7u);
  set_window_1dc(&fixture.window, 1u);
  // A decoy table at the real table's word 0, with a nonzero 0x114 and 0x90.
  // A two-level read would dispatch there.
  write_word(&fixture.decoy_vtable, kTableMessageSlotDisplacement,
             pointer_word(&fixture.decoy_vtable));
  write_word(&fixture.decoy_vtable, kTablePendingSlotDisplacement,
             pointer_word(&fixture.decoy_vtable));
  write_word(&fixture.vtable, 0x00u, pointer_word(&fixture.decoy_vtable));
  // Neighbouring words, one dword either side of the 0x90 slot and one dword
  // below the 0x114 slot. The word ABOVE 0x114 is past the table's modeled
  // extent, so it is not written: the body never reaches it and the test has no
  // business claiming a byte the evidence does not cover.
  write_word(&fixture.vtable, kTablePendingSlotDisplacement - 4u, 0u);
  write_word(&fixture.vtable, kTablePendingSlotDisplacement + 4u, 0u);
  write_word(&fixture.vtable, kTableMessageSlotDisplacement - 4u, 0u);
  // (a compile-time fact, asserted in the header: 0x114 + 4 == 0x118)

  reset();
  state_slot()(&fixture.window, 8u);
  check(event_count == 2);
  check(events[0].kind == Kind::message);
  check(events[1].kind == Kind::pending);
  check(events[0].object == pointer_word(&fixture.window));
  check(events[1].object == pointer_word(&fixture.window));
  check(table_address == 0);
}

// 7. BYTE RANGE. Only the two receiver words the body names change; every other
// byte of the window keeps its pattern, including the dispatch word at +0x00 and
// the gate at +0x1dc (a dispatch reads the gate, it does not write it).
void test_only_the_two_named_receiver_words_change() {
  Fixture fixture;
  // The pattern first, so every byte of the window - the two words the body
  // touches included - starts out holding a recognisable value. Both are then
  // given four DISTINCT bytes, so the byte-level comparison below can tell
  // "this byte moved" from "this byte happened to already hold the answer".
  for (std::size_t index = 0; index < fixture.window.opaque_00.size(); ++index) {
    fixture.window.opaque_00[index] = static_cast<std::uint8_t>(0x40u + index);
  }
  set_window_a8(&fixture.window, 0x11111111u);
  set_window_1dc(&fixture.window, 0x22222222u);
  write_word(&fixture.window, kReceiverDispatchWordDisplacement,
             pointer_word(&fixture.vtable));

  std::uint8_t before[sizeof(OpaqueWindow)];
  std::memcpy(before, fixture.window.opaque_00.data(), sizeof before);
  reset();
  state_slot()(&fixture.window, 0x33333333u);

  std::size_t changed = 0;
  for (std::size_t index = 0; index < sizeof before; ++index) {
    const bool moved = before[index] != fixture.window.opaque_00[index];
    const bool in_the_stored_word =
        index >= kReceiverPreviousDisplacement &&
        index < kReceiverPreviousDisplacement + sizeof(Opaque);
    check(moved == in_the_stored_word);
    if (moved) {
      ++changed;
    }
  }
  check(changed == sizeof(Opaque));
  check(read_word(&fixture.window, kReceiverPreviousDisplacement) == 0x33333333u);
  check(read_word(&fixture.window, kReceiverGateDisplacement) == 0x22222222u);
}

// 8. ABI: `RET 0x4`, so the callee pops the one argument word. ESP is sampled
// either side of a direct call by a helper that is itself a balanced call, so
// the two samples are at the same depth and can only differ if the entry left
// the stack unbalanced.
__attribute__((noinline)) std::uint32_t sample_stack_pointer() {
  std::uint32_t value = 0;
  __asm__ __volatile__("movl %%esp, %0" : "=r"(value));
  return value;
}

void test_one_argument_word_is_callee_cleaned() {
  Fixture fixture;
  set_window_a8(&fixture.window, 0x10u);
  reset();
  const std::uint32_t before = sample_stack_pointer();
  state_slot()(&fixture.window, 0x20u);
  const std::uint32_t after = sample_stack_pointer();
  check(after == before);
  check(event_count == 1);
  check(read_word(&fixture.window, kReceiverPreviousDisplacement) == 0x20u);
}

}

int run_tests() {
  test_changed_value_dispatches_message();
  test_only_equality_suppresses_the_work();
  test_the_equality_is_against_plus_0xa8();
  test_the_gate_is_a_zero_test();
  test_the_gate_is_read_after_the_message_call();
  test_dispatch_is_one_level_at_exact_slots();
  test_only_the_two_named_receiver_words_change();
  test_one_argument_word_is_callee_cleaned();
  return 0;
}

}

int main() {
  return openspore::reconstruction::pkg_utfwin_func35_wave12::run_tests();
}
