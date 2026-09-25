#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <type_traits>
#include <vector>

#include "editor_lifecycle_wave6.hpp"

namespace openspore::reconstruction::pkg_editor_lifecycle_wave6 {

struct OpaqueManager {};

struct Fixture {
  OpaqueEditor editor{};
  OpaqueManager manager{};
  std::array<std::byte, 0x50> object{};
  std::array<std::byte, 0x20> service{};
  std::array<std::byte, 0x40> message{};
  void* global_service = nullptr;
  void* global_service_slot = nullptr;
  float source = 0.0F;
  bool app_available = false;
  bool required_available = false;
  bool renderer_available = false;
  bool message_result = false;
  bool clock_expired = false;
  std::uint64_t now = 0;
  std::vector<NativeCall> calls;
};

template <typename Value>
Value read(const void* address) {
  Value value{};
  std::memcpy(&value, address, sizeof(value));
  return value;
}

template <typename Value>
void write(void* address, Value value) {
  std::memcpy(address, &value, sizeof(value));
}

std::byte* at(OpaqueEditor& editor, std::size_t offset) {
  return editor.bytes.data() + offset;
}

std::uint32_t word(OpaqueEditor& editor, std::size_t offset) {
  return read<std::uint32_t>(at(editor, offset));
}

void set_word(OpaqueEditor& editor, std::size_t offset, std::uint32_t value) {
  write(at(editor, offset), value);
}

void set_byte(OpaqueEditor& editor, std::size_t offset, std::uint8_t value) {
  write(at(editor, offset), value);
}

void set_pointer(OpaqueEditor& editor, std::size_t offset, void* value) {
  write(at(editor, offset),
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(value)));
}

bool has(const Fixture& fixture, NativeOp operation) {
  for (const NativeCall& call : fixture.calls) {
    if (call.operation == operation) {
      return true;
    }
  }
  return false;
}

std::size_t count(const Fixture& fixture, NativeOp operation) {
  std::size_t result = 0;
  for (const NativeCall& call : fixture.calls) {
    if (call.operation == operation) {
      ++result;
    }
  }
  return result;
}

NativeResult invoke(const NativeCall& call) {
  Fixture* fixture = reinterpret_cast<Fixture*>(call.editor->bytes.data());
  fixture->calls.push_back(call);
  NativeResult result{};
  switch (call.operation) {
    case NativeOp::dispose_self_1c:
      set_byte(fixture->editor, kOffsetActive, 0);
      break;
    case NativeOp::dispose_acquire_app:
      result.pointer =
          fixture->app_available ? fixture->service.data() : nullptr;
      break;
    case NativeOp::initialize_manager_0050:
      result.pointer = fixture->service.data();
      break;
    case NativeOp::initialize_required_008de1a0:
      result.pointer =
          fixture->required_available ? fixture->service.data() : nullptr;
      break;
    case NativeOp::exit_phase:
      result.boolean = call.first == 3 && fixture->renderer_available;
      break;
    case NativeOp::exit_accumulate:
      result.qword = fixture->now;
      break;
    case NativeOp::update_clock_query:
      if (call.address == 0x0067de30 && call.first == 0) {
        result.pointer = fixture->service.data();
      }
      if (call.address == 0x0067de30 && call.first == 0xb55619c2) {
        result.boolean = true;
      }
      break;
    case NativeOp::update_clock_expired:
      result.boolean = call.address == 0x0093a5e0 && fixture->clock_expired;
      break;
    case NativeOp::update_timer_gate:
      result.boolean = true;
      break;
    case NativeOp::message_route:
      result.boolean = fixture->message_result;
      break;
    case NativeOp::message_object_000c:
      result.word = 0x12345678;
      break;
    default:
      break;
  }
  return result;
}

void initialize(Fixture& fixture) {
  fixture.calls.clear();
  fixture.app_available = false;
  fixture.required_available = false;
  fixture.renderer_available = false;
  fixture.message_result = false;
  fixture.clock_expired = false;
  fixture.now = 0;
  fixture.global_service = fixture.service.data();
  fixture.global_service_slot = &fixture.global_service;
  fixture.source = 0.0F;
  g_editor_lifecycle_wave6_globals = OpaqueGlobals{};
  g_editor_lifecycle_wave6_globals.source_01465544 = &fixture.source;
  g_editor_lifecycle_wave6_globals.global_service_015eebec =
      &fixture.global_service;
  g_editor_lifecycle_wave6_ports = NativePorts{};
  g_editor_lifecycle_wave6_ports.call = invoke;
}

void test_dispose() {
  Fixture fixture{};
  initialize(fixture);
  fixture.app_available = true;
  set_byte(fixture.editor, kOffsetActive, 1);
  set_word(fixture.editor, kOffsetGlobalFlag5c0, 9);
  set_pointer(fixture.editor, kOffsetObjectA0, fixture.object.data());
  write(fixture.object.data() + 0x40, static_cast<std::uint32_t>(1));
  assert(editor_dispose_00576c50(&fixture.editor));
  assert(word(fixture.editor, kOffsetActive) == 0);
  assert(word(fixture.editor, kOffsetGlobalFlag5c0) == 0);
  assert(word(fixture.editor, kOffsetObjectA0) == 0);
  assert(read<std::uint32_t>(fixture.object.data() + 0x40) == 1);
  assert(count(fixture, NativeOp::dispose_remove_hash) == 3);
  assert(count(fixture, NativeOp::dispose_render_2c) == 3);
  assert(fixture.global_service == nullptr);
}

void test_initialize() {
  Fixture fixture{};
  initialize(fixture);
  fixture.required_available = true;
  fixture.source = 1.25F;
  set_word(fixture.editor, kOffsetMapCount, 0x12345678);
  assert(editor_initialize_00584300(&fixture.editor, &fixture.manager));
  assert(word(fixture.editor, kOffsetManager) ==
         static_cast<std::uint32_t>(
             reinterpret_cast<std::uintptr_t>(&fixture.manager)));
  assert(word(fixture.editor, kOffsetMapSentinel) ==
         static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(
             fixture.editor.bytes.data() + kOffsetMapSentinel)));
  assert(word(fixture.editor, kOffsetMapRight) ==
         word(fixture.editor, kOffsetMapSentinel));
  assert(word(fixture.editor, kOffsetMapCount) == 0);
  assert(read<float>(at(fixture.editor, kOffsetDefaultScalar)) == 1.25F);
  assert(word(fixture.editor, 0x580) == 0);
  assert(read<std::uint16_t>(at(fixture.editor, 0x584)) == 0);
  assert(count(fixture, NativeOp::initialize_register_hash) == 6);
  assert(count(fixture, NativeOp::initialize_listener) == 4);

  Fixture failure{};
  initialize(failure);
  assert(!editor_initialize_00584300(&failure.editor, &failure.manager));
  assert(count(failure, NativeOp::initialize_listener) == 0);
}

void test_on_exit() {
  Fixture fixture{};
  initialize(fixture);
  fixture.renderer_available = true;
  fixture.now = 100;
  set_byte(fixture.editor, kOffsetActive, 1);
  set_word(fixture.editor, 0x450, 77);
  write(at(fixture.editor, kOffsetClockBase), static_cast<std::uint64_t>(40));
  write(at(fixture.editor, kOffsetClockAccumulator),
        static_cast<std::uint64_t>(7));
  editor_on_exit_00587a20(&fixture.editor);
  assert(word(fixture.editor, kOffsetActive) == 0);
  assert(has(fixture, NativeOp::exit_set_mode));
  assert(read<std::uint64_t>(at(fixture.editor, kOffsetClockAccumulator)) ==
         67);
  assert(count(fixture, NativeOp::exit_cleanup) == 5);
}

void test_update() {
  Fixture fixture{};
  initialize(fixture);
  set_byte(fixture.editor, kOffsetActive, 0);
  editor_update_0058be50(&fixture.editor, 9.0F, 0.25F);
  assert(fixture.calls.empty());

  initialize(fixture);
  set_byte(fixture.editor, kOffsetActive, 1);
  set_word(fixture.editor, kOffsetMode, 2);
  set_pointer(fixture.editor, kOffsetMessagePending, fixture.service.data());
  write(at(fixture.editor, kOffsetMessageTimer), 1.0F);
  editor_update_0058be50(&fixture.editor, 9.0F, 0.25F);
  assert(has(fixture, NativeOp::update_main));
  assert(has(fixture, NativeOp::update_play));
  assert(has(fixture, NativeOp::update_finish));
  for (const NativeCall& call : fixture.calls) {
    if (call.operation == NativeOp::update_main) {
      assert(call.first == 250);
      assert(call.first_scalar == 0.25F);
      assert(call.second_scalar == 0.25F);
    }
  }
  assert(read<float>(at(fixture.editor, kOffsetMessageTimer)) == 0.75F);
}

void test_message() {
  Fixture fixture{};
  initialize(fixture);
  std::uint8_t target = 1;
  write(fixture.message.data() + 8,
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&target)));
  assert(!editor_handle_message_00591fa0(&fixture.editor, 0x12345678,
                                         fixture.message.data()));
  assert(fixture.calls.empty());
  assert(editor_handle_message_00591fa0(&fixture.editor, 0x29d57f4,
                                        fixture.message.data()));
  assert(word(fixture.editor, kOffsetMessageFlag389) == 0);

  fixture.calls.clear();
  std::uint8_t enabled = 1;
  write(fixture.message.data() + 0xc, enabled);
  fixture.message_result = true;
  assert(!editor_handle_message_00591fa0(&fixture.editor, 0xf1ff568b,
                                         fixture.message.data()));
  assert(read<std::uint8_t>(fixture.message.data() + 0xc) == 0);
  assert(read<std::uint32_t>(fixture.message.data() + 0x10) == 0xa6c97621);

  fixture.calls.clear();
  set_word(fixture.editor, 0x198, 0);
  set_byte(fixture.editor, 0x2a0, 1);
  set_word(fixture.editor, kOffsetMessageKey, 7);
  write(fixture.message.data() + 0x14, static_cast<std::uint32_t>(7));
  fixture.message_result = true;
  assert(editor_handle_message_00591fa0(&fixture.editor, 0xd1511790,
                                        fixture.message.data()));
  assert(has(fixture, NativeOp::message_route));

  fixture.calls.clear();
  set_word(fixture.editor, kOffsetMessageState, 1);
  assert(!editor_handle_message_00591fa0(&fixture.editor, 0x1ee1009,
                                         fixture.message.data()));
  assert(target == 0);
  assert(word(fixture.editor, kOffsetMessageStateValue) == 3);
}

}

using namespace openspore::reconstruction::pkg_editor_lifecycle_wave6;

int main() {
  using Dispose = bool(__thiscall*)(OpaqueEditor*);
  using Initialize = bool(__thiscall*)(OpaqueEditor*, OpaqueManager*);
  using OnExit = void(__thiscall*)(OpaqueEditor*);
  using Update = void(__thiscall*)(OpaqueEditor*, float, float);
  using HandleMessage = bool(__thiscall*)(OpaqueEditor*, std::uint32_t, void*);
  static_assert(
      std::is_same<decltype(&editor_dispose_00576c50), Dispose>::value,
      "dispose ABI");
  static_assert(
      std::is_same<decltype(&editor_initialize_00584300), Initialize>::value,
      "initialize ABI");
  static_assert(std::is_same<decltype(&editor_on_exit_00587a20), OnExit>::value,
                "on-exit ABI");
  static_assert(std::is_same<decltype(&editor_update_0058be50), Update>::value,
                "update ABI");
  static_assert(std::is_same<decltype(&editor_handle_message_00591fa0),
                             HandleMessage>::value,
                "message ABI");
  test_dispose();
  test_initialize();
  test_on_exit();
  test_update();
  test_message();
  return 0;
}
