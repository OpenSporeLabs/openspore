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
  std::array<std::byte, 0x50> object98{};
  std::array<std::byte, 0x20> object90{};
  std::array<std::byte, 0x20> object94{};
  std::array<std::byte, 0x20> service{};
  std::array<std::byte, 0x20> asset_view_manager{};
  std::array<std::byte, 0x40> message{};
  void* global_service = nullptr;
  void* global_service_slot = nullptr;
  float source = 0.0F;
  bool app_available = false;
  bool required_available = false;
  bool renderer_available = false;
  bool release_prepare_sets_exit_mode_arg = false;
  bool asset_view_available = false;
  bool first_gate = false;
  bool second_gate = false;
  bool property_gate = false;
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

bool has_address(const Fixture& fixture, std::uint32_t address) {
  for (const NativeCall& call : fixture.calls) {
    if (call.address == address) {
      return true;
    }
  }
  return false;
}

NativeResult invoke(const NativeCall& call) {
  Fixture* fixture = reinterpret_cast<Fixture*>(call.editor->bytes.data());
  fixture->calls.push_back(call);
  NativeResult result{};
  switch (call.operation) {
    case NativeOp::dispose_self_1c:
      set_byte(fixture->editor, kOffsetActive, 0);
      break;
    case NativeOp::dispose_release_prepare:
      if (fixture->release_prepare_sets_exit_mode_arg) {
        set_pointer(fixture->editor, kOffsetExitModeArg,
                    fixture->object98.data());
      }
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
    case NativeOp::message_service:
      if (call.address == 0x00401030) {
        result.pointer = fixture->asset_view_available
                             ? fixture->asset_view_manager.data()
                             : nullptr;
      } else if (call.address == 0x005dc2e0) {
        result.boolean = fixture->first_gate;
      } else if (call.address == 0x005dc2f0) {
        result.boolean = fixture->second_gate;
      } else if (call.address == 0x006a25a0) {
        result.boolean = fixture->property_gate;
      } else {
        result.boolean = fixture->message_result;
      }
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
  fixture.release_prepare_sets_exit_mode_arg = false;
  fixture.asset_view_available = false;
  fixture.first_gate = false;
  fixture.second_gate = false;
  fixture.property_gate = false;
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
  set_pointer(fixture.editor, kOffsetExitModeArg, fixture.object.data());
  set_pointer(fixture.editor, kOffsetObject90, fixture.object90.data());
  set_pointer(fixture.editor, kOffsetExitObject94, fixture.object94.data());
  set_pointer(fixture.editor, 0x3d0, fixture.object.data());
  write(fixture.object.data() + 0x40, static_cast<std::uint32_t>(1));
  write(fixture.object.data() + 8, static_cast<std::uint32_t>(1));
  write(fixture.object90.data() + 4, static_cast<std::uint32_t>(1));
  assert(editor_dispose_00576c50(&fixture.editor));
  assert(word(fixture.editor, kOffsetActive) == 0);
  assert(word(fixture.editor, kOffsetGlobalFlag5c0) == 0);
  assert(word(fixture.editor, kOffsetObjectA0) == 0);
  assert(word(fixture.editor, kOffsetExitModeArg) == 0);
  assert(word(fixture.editor, kOffsetObject90) == 0);
  assert(word(fixture.editor, kOffsetExitObject94) == 0);
  assert(read<std::uint32_t>(fixture.object.data() + 0x40) == 1);
  assert(read<std::uint32_t>(fixture.object.data() + 8) == 1);
  assert(read<std::uint32_t>(fixture.object90.data() + 4) == 1);
  assert(count(fixture, NativeOp::dispose_remove_hash) == 3);
  assert(count(fixture, NativeOp::dispose_render_2c) == 3);
  bool viewer_reset_object = false;
  bool object90_released = false;
  bool object94_released = false;
  for (const NativeCall& call : fixture.calls) {
    if (call.operation == NativeOp::dispose_viewer_reset &&
        call.pointer == fixture.object.data()) {
      viewer_reset_object = true;
    }
    if (call.operation == NativeOp::dispose_release_virtual &&
        call.pointer == fixture.object90.data()) {
      object90_released = true;
    }
    if (call.operation == NativeOp::dispose_release_virtual &&
        call.pointer == fixture.object94.data()) {
      object94_released = true;
    }
  }
  assert(viewer_reset_object);
  assert(object90_released);
  assert(object94_released);
  static_cast<void>(viewer_reset_object);
  static_cast<void>(object90_released);
  static_cast<void>(object94_released);
  assert(fixture.global_service == nullptr);
}

void test_dispose_second_release() {
  Fixture fixture{};
  initialize(fixture);
  fixture.release_prepare_sets_exit_mode_arg = true;
  set_pointer(fixture.editor, kOffsetExitModeArg2, fixture.object.data());
  write(fixture.object98.data() + 8, static_cast<std::uint32_t>(1));
  assert(editor_dispose_00576c50(&fixture.editor));
  assert(word(fixture.editor, kOffsetExitModeArg) == 0);
  assert(word(fixture.editor, kOffsetExitModeArg2) ==
         static_cast<std::uint32_t>(
             reinterpret_cast<std::uintptr_t>(fixture.object.data())));
  assert(read<std::uint32_t>(fixture.object98.data() + 8) == 1);
  assert(count(fixture, NativeOp::dispose_release_prepare) == 1);
  bool released = false;
  for (const NativeCall& call : fixture.calls) {
    if (call.operation == NativeOp::dispose_release_virtual &&
        call.pointer == fixture.object98.data() + 4) {
      released = true;
    }
  }
  assert(released);
  static_cast<void>(released);
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
  assert(word(fixture.editor, kOffsetDefaultScalar) == 0x43fa0000u);
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
  editor_update_0058be50(&fixture.editor, 0.25F, 9.0F);
  assert(has(fixture, NativeOp::update_main));
  assert(has(fixture, NativeOp::update_play));
  assert(has(fixture, NativeOp::update_finish));
  for (const NativeCall& call : fixture.calls) {
    if (call.operation == NativeOp::update_main) {
      assert(call.first == 250);
      assert(call.first_scalar == 0.25F);
      assert(call.second_scalar == 9.0F);
    }
  }
  assert(read<float>(at(fixture.editor, kOffsetMessageTimer)) == 0.75F);
  assert(count(fixture, NativeOp::update_timer_expire) == 0);

  Fixture expiry{};
  initialize(expiry);
  set_byte(expiry.editor, kOffsetActive, 1);
  set_pointer(expiry.editor, kOffsetMessagePending, expiry.service.data());
  write(at(expiry.editor, kOffsetMessageTimer), 0.25F);
  editor_update_0058be50(&expiry.editor, 0.25F, 9.0F);
  assert(read<float>(at(expiry.editor, kOffsetMessageTimer)) == 0.0F);
  assert(count(expiry, NativeOp::update_timer_expire) == 1);
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
  assert(fixture.calls.empty());

  fixture.calls.clear();
  assert(!editor_handle_message_00591fa0(&fixture.editor, 0x1c94708,
                                         fixture.message.data()));
  assert(read<std::uint8_t>(at(fixture.editor, kOffsetMessageFlag385)) == 1);
  assert(fixture.calls.empty());

  fixture.calls.clear();
  set_pointer(fixture.editor, 0x14, fixture.service.data());
  write(fixture.message.data(),
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(fixture.object.data())));
  fixture.message_result = true;
  assert(!editor_handle_message_00591fa0(&fixture.editor, 0xf058b0f2,
                                         fixture.message.data()));
  assert(has_address(fixture, 0x0040cf10));
  assert(!has_address(fixture, 0x00591fa0));

  fixture.calls.clear();
  assert(editor_handle_message_00591fa0(&fixture.editor, 0x3fc3f13,
                                        fixture.message.data()));
  assert(has_address(fixture, 0x006b1f90));
  assert(has_address(fixture, 0x004ae000));
  assert(!has_address(fixture, 0x00591fa0));

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
  assert(has(fixture, NativeOp::message_service));

  fixture.calls.clear();
  set_word(fixture.editor, kOffsetMessageState, 1);
  assert(!editor_handle_message_00591fa0(&fixture.editor, 0x1ee1009,
                                         fixture.message.data()));
  assert(target == 0);
  assert(word(fixture.editor, kOffsetMessageStateValue) == 3);
}

void test_message_5132389() {
  Fixture fixture{};
  initialize(fixture);
  set_byte(fixture.editor, 0x2a0, 1);
  assert(!editor_handle_message_00591fa0(&fixture.editor, 0x5132389,
                                         fixture.message.data()));
  assert(fixture.calls.empty());

  write(fixture.message.data(), static_cast<std::uint32_t>(1));
  fixture.first_gate = true;
  set_word(fixture.editor, 0x30c, 2);
  assert(editor_handle_message_00591fa0(&fixture.editor, 0x5132389,
                                        fixture.message.data()));
  assert(has_address(fixture, 0x00401030));
  assert(has_address(fixture, 0x005dc2e0));
  assert(!has_address(fixture, 0x005dc2f0));
  assert(!has_address(fixture, 0x006a25a0));
  assert(has_address(fixture, 0x00628910));

  initialize(fixture);
  set_byte(fixture.editor, 0x2a0, 1);
  write(fixture.message.data(), static_cast<std::uint32_t>(1));
  fixture.second_gate = true;
  set_word(fixture.editor, 0x30c, 2);
  assert(editor_handle_message_00591fa0(&fixture.editor, 0x5132389,
                                        fixture.message.data()));
  assert(has_address(fixture, 0x005dc2e0));
  assert(has_address(fixture, 0x005dc2f0));
  assert(!has_address(fixture, 0x006a25a0));

  initialize(fixture);
  set_byte(fixture.editor, 0x2a0, 1);
  write(fixture.message.data(), static_cast<std::uint32_t>(1));
  fixture.property_gate = true;
  set_word(fixture.editor, 0x30c, 2);
  assert(editor_handle_message_00591fa0(&fixture.editor, 0x5132389,
                                        fixture.message.data()));
  assert(has_address(fixture, 0x005dc2e0));
  assert(has_address(fixture, 0x005dc2f0));
  assert(has_address(fixture, 0x006a25a0));

  initialize(fixture);
  set_byte(fixture.editor, 0x2a0, 1);
  write(fixture.message.data(), static_cast<std::uint32_t>(1));
  assert(!editor_handle_message_00591fa0(&fixture.editor, 0x5132389,
                                         fixture.message.data()));
  assert(has_address(fixture, 0x005dc2e0));
  assert(has_address(fixture, 0x005dc2f0));
  assert(has_address(fixture, 0x006a25a0));
  assert(!has_address(fixture, 0x00628910));

  initialize(fixture);
  set_byte(fixture.editor, 0x2a0, 1);
  write(fixture.message.data(), static_cast<std::uint32_t>(1));
  write(fixture.asset_view_manager.data() + 0x1c, static_cast<std::uint8_t>(1));
  fixture.asset_view_available = true;
  fixture.property_gate = true;
  set_word(fixture.editor, 0x30c, 2);
  assert(!editor_handle_message_00591fa0(&fixture.editor, 0x5132389,
                                         fixture.message.data()));
  assert(has_address(fixture, 0x00401030));
  assert(has_address(fixture, 0x005dc2e0));
  assert(has_address(fixture, 0x005dc2f0));
  assert(has_address(fixture, 0x006a25a0));
  assert(!has_address(fixture, 0x00628910));

  initialize(fixture);
  set_byte(fixture.editor, 0x2a0, 1);
  write(fixture.message.data(), static_cast<std::uint32_t>(1));
  fixture.first_gate = true;
  fixture.message_result = true;
  set_word(fixture.editor, 0x30c, 1);
  assert(!editor_handle_message_00591fa0(&fixture.editor, 0x5132389,
                                         fixture.message.data()));
  assert(has_address(fixture, 0x005dc450));
  assert(has_address(fixture, 0x0067caa0));
  assert(has_address(fixture, 0x005df8f0));
  assert(!has_address(fixture, 0x00628910));
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
  test_dispose_second_release();
  test_initialize();
  test_on_exit();
  test_update();
  test_message();
  test_message_5132389();
  return 0;
}
