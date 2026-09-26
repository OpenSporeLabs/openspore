#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "utfwin_window_wave9.hpp"

namespace openspore::reconstruction::pkg_utfwin_window_wave9 {
namespace model {

enum class Kind : std::uint8_t {
  message,
  invalidate,
  cast,
  destroy,
};

struct Event {
  Kind kind;
  Opaque object;
  Opaque code;
  Opaque new_state;
  Opaque previous_state;
};

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

Event events[8]{};
std::size_t event_count = 0;
Opaque cast_result = 0;
Opaque destroyed_object = 0;
Opaque destroyed_flags = 0;
Opaque invalidated_object = 0;
OpaqueWindowMessage message_copy{};
Opaque message_address = 0;

Opaque pointer_word(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

void add(Kind kind, Opaque object, Opaque code, Opaque new_state,
         Opaque previous_state) {
  check(event_count < 8);
  events[event_count++] = Event{kind, object, code, new_state, previous_state};
}

void reset() {
  event_count = 0;
  cast_result = 0;
  destroyed_object = 0;
  destroyed_flags = 0;
  invalidated_object = 0;
  message_copy = {};
  message_address = 0;
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

void PKG_UTFWIN_WINDOW_WAVE9_THISCALL
message_slot(OpaqueWindow* object, OpaqueWindowMessage* message) {
  add(Kind::message, pointer_word(object), message->code_08,
      message->new_state_0c, message->previous_state_10);
  check(reinterpret_cast<std::uintptr_t>(&message->stale_00) ==
            reinterpret_cast<std::uintptr_t>(message) &&
        reinterpret_cast<std::uintptr_t>(&message->stale_04) ==
            reinterpret_cast<std::uintptr_t>(message) + 4u);
  check(reinterpret_cast<std::uintptr_t>(&message->code_08) ==
        reinterpret_cast<std::uintptr_t>(message) + 8u);
  check(reinterpret_cast<std::uintptr_t>(&message->previous_state_10) ==
        reinterpret_cast<std::uintptr_t>(message) + 0x10u);
  message_copy = *message;
  message_address = pointer_word(message);
}

Opaque PKG_UTFWIN_WINDOW_WAVE9_THISCALL invalidate_slot(OpaqueWindow* object) {
  add(Kind::invalidate, pointer_word(object), 0, 0, 0);
  invalidated_object = pointer_word(object);
  return 0xfeedfaceu;
}

}

using namespace model;

extern "C" Opaque PKG_UTFWIN_WINDOW_WAVE9_THISCALL
pkg_utfwin_window_wave9_re_00950eb0(OpaqueEffect* object, Opaque type_id) {
  add(Kind::cast, pointer_word(object), type_id, 0, 0);
  return cast_result;
}

extern "C" void PKG_UTFWIN_WINDOW_WAVE9_THISCALL
pkg_utfwin_window_wave9_re_0096ffd0(OpaqueGlide* object, Opaque flags) {
  add(Kind::destroy, pointer_word(object), flags, 0, 0);
  destroyed_object = pointer_word(object);
  destroyed_flags = flags;
}

using SetWordSlot = Opaque(PKG_UTFWIN_WINDOW_WAVE9_THISCALL*)(OpaqueWindow*,
                                                              Opaque);
using StateSlot = void(PKG_UTFWIN_WINDOW_WAVE9_THISCALL*)(OpaqueWindow*,
                                                          Opaque);
using CastSlot = EffectCastSlot;
using DestroySlot = GlideDestroySlot;

void test_word_field_and_return_width() {
  OpaqueWindow window{};
  const SetWordSlot slot = function_from<SetWordSlot>(
      function_word(pkg_utfwin_window_wave9_0095fa30));
  check(slot(&window, 0) == 0);
  check(window.field_80 == 0);
  check(slot(&window, 0xdeadbeefu) == 0xdeadbeefu);
  check(window.field_80 == 0xdeadbeefu);
}

void test_state_message_and_invalidation_order() {
  OpaqueWindowVTable vtable{};
  vtable.slot_90 = function_word(invalidate_slot);
  vtable.slot_114 = function_word(message_slot);
  OpaqueWindow window{};
  window.vtable_00 = &vtable;
  window.field_a8 = 7;
  const StateSlot slot =
      function_from<StateSlot>(function_word(pkg_utfwin_window_wave9_0095fd60));

  reset();
  slot(&window, 7);
  check(event_count == 0);
  check(invalidated_object == 0);

  slot(&window, 9);
  check(event_count == 1);
  check(events[0].kind == Kind::message);
  check(events[0].object == pointer_word(&window));
  check(events[0].code == 0x13);
  check(events[0].new_state == 9);
  check(events[0].previous_state == 7);
  check(message_copy.code_08 == 0x13);
  check(message_copy.new_state_0c == 9);
  check(message_copy.previous_state_10 == 7);
  check(window.field_a8 == 9);
  check(invalidated_object == 0);
  const Opaque first_message_address = message_address;

  window.field_1dc = 1;
  reset();
  slot(&window, 10);
  check(event_count == 2);
  check(events[0].kind == Kind::message);
  check(events[1].kind == Kind::invalidate);
  check(events[1].object == pointer_word(&window));
  check(invalidated_object == pointer_word(&window));
  check(message_copy.code_08 == 0x13);
  check(message_copy.new_state_0c == 10);
  check(message_copy.previous_state_10 == 9);
  check(message_address == first_message_address);
}

void test_cast_sentinel_and_fallback() {
  std::uint8_t storage[0x40]{};
  auto* object = reinterpret_cast<OpaqueEffect*>(storage);
  const CastSlot slot =
      function_from<CastSlot>(function_word(pkg_utfwin_window_wave9_009672d0));

  reset();
  check(slot(object, 0x6f90a535u) == pointer_word(object) + 0x0cu);
  check(event_count == 0);
  check(slot(nullptr, 0x6f90a535u) == 0);
  check(event_count == 0);

  cast_result = 0x12345678u;
  check(slot(object, 0xeec58382u) == cast_result);
  check(event_count == 1);
  check(events[0].kind == Kind::cast);
  check(events[0].object == pointer_word(object));
  check(events[0].code == 0xeec58382u);

  cast_result = 0x87654321u;
  check(slot(nullptr, 0x12345678u) == cast_result);
  check(event_count == 2);
  check(events[1].object == 0);
  check(events[1].code == 0x12345678u);
}

void test_glide_adjustor_and_null_wrap() {
  std::uint8_t storage[0x40]{};
  auto* object = reinterpret_cast<OpaqueGlide*>(storage);
  const DestroySlot slot = function_from<DestroySlot>(
      function_word(pkg_utfwin_window_wave9_0096ff70));

  reset();
  slot(object, 0xa5u);
  check(event_count == 1);
  check(events[0].kind == Kind::destroy);
  check(events[0].object == pointer_word(object) - 0x0cu);
  check(events[0].code == 0xa5u);
  check(destroyed_object == pointer_word(object) - 0x0cu);
  check(destroyed_flags == 0xa5u);

  reset();
  slot(nullptr, 1);
  check(event_count == 1);
  check(events[0].kind == Kind::destroy);
  check(events[0].object == 0xfffffff4u);
  check(events[0].code == 1);
}

int run_tests() {
  test_word_field_and_return_width();
  test_state_message_and_invalidation_order();
  test_cast_sentinel_and_fallback();
  test_glide_adjustor_and_null_wrap();
  return 0;
}

}

int main() {
  return openspore::reconstruction::pkg_utfwin_window_wave9::run_tests();
}
