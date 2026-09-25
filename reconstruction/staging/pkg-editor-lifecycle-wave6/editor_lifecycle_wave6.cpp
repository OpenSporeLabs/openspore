#include "editor_lifecycle_wave6.hpp"

#include <cmath>
#include <cstring>
#include <limits>

namespace openspore::reconstruction::pkg_editor_lifecycle_wave6 {

OpaqueGlobals g_editor_lifecycle_wave6_globals{};
NativePorts g_editor_lifecycle_wave6_ports{};

namespace {

template <typename Value>
Value load(const void* address) {
  Value value{};
  std::memcpy(&value, address, sizeof(value));
  return value;
}

template <typename Value>
void store(void* address, Value value) {
  std::memcpy(address, &value, sizeof(value));
}

std::byte* field(OpaqueEditor* editor, std::size_t offset) {
  return editor->bytes.data() + offset;
}

NativeResult invoke(OpaqueEditor* editor, NativeOp operation,
                    std::uint32_t address = 0, std::uint32_t slot = 0,
                    std::uint32_t first = 0, std::uint32_t second = 0,
                    std::uint32_t third = 0, std::uint32_t fourth = 0,
                    std::uint32_t fifth = 0, void* pointer = nullptr,
                    float first_scalar = 0.0F, float second_scalar = 0.0F) {
  NativeCall call{};
  call.operation = operation;
  call.editor = editor;
  call.address = address;
  call.slot = slot;
  call.first = first;
  call.second = second;
  call.third = third;
  call.fourth = fourth;
  call.fifth = fifth;
  call.pointer = pointer;
  call.first_scalar = first_scalar;
  call.second_scalar = second_scalar;
  if (g_editor_lifecycle_wave6_ports.call == nullptr) {
    return {};
  }
  return g_editor_lifecycle_wave6_ports.call(call);
}

void release_0098(OpaqueEditor* editor) {
  void* owner = load<void*>(field(editor, kOffsetExitModeArg));
  store(field(editor, kOffsetExitModeArg), static_cast<std::uint32_t>(0));
  if (owner == nullptr) {
    return;
  }
  auto* owner_bytes = static_cast<std::byte*>(owner);
  std::uint32_t count = load<std::uint32_t>(owner_bytes + 8);
  --count;
  store(owner_bytes + 8, count);
  if (count == 0) {
    store(owner_bytes + 8, static_cast<std::uint32_t>(1));
    invoke(editor, NativeOp::dispose_release_virtual, 0, 0, 1, 0, 0, 0, 0,
           owner);
  }
}

void release_004b9140(OpaqueEditor* editor, std::size_t offset) {
  void* owner = load<void*>(field(editor, offset));
  store(field(editor, offset), static_cast<std::uint32_t>(0));
  if (owner == nullptr) {
    return;
  }
  auto* owner_bytes = static_cast<std::byte*>(owner);
  std::uint32_t count = load<std::uint32_t>(owner_bytes + 8);
  --count;
  store(owner_bytes + 8, count);
  if (count == 0) {
    store(owner_bytes + 8, static_cast<std::uint32_t>(1));
    invoke(editor, NativeOp::dispose_release_virtual, 0, 0, 1, 0, 0, 0, 0,
           owner);
  }
}

void release_ref40(OpaqueEditor* editor, std::size_t offset) {
  void* object = load<void*>(field(editor, offset));
  store(field(editor, offset), static_cast<std::uint32_t>(0));
  if (object == nullptr) {
    return;
  }
  auto* object_bytes = static_cast<std::byte*>(object);
  std::uint32_t count = load<std::uint32_t>(object_bytes + 0x40);
  if (count > 1) {
    store(object_bytes + 0x40, count - 1);
    return;
  }
  store(object_bytes + 0x40, static_cast<std::uint32_t>(1));
  const std::uint32_t sign = load<std::uint32_t>(object_bytes + 4) >> 31;
  invoke(editor, NativeOp::dispose_release_object, 0, 0x170, sign, 0, 0, 0, 0,
         object);
}

void release_slot4(OpaqueEditor* editor, std::size_t offset) {
  void* object = load<void*>(field(editor, offset));
  store(field(editor, offset), static_cast<std::uint32_t>(0));
  if (object != nullptr) {
    invoke(editor, NativeOp::dispose_release_virtual, 0, 4, 0, 0, 0, 0, 0,
           object);
  }
}

void release_viewers(OpaqueEditor* editor) {
  constexpr std::size_t offsets[] = {0x3d0, 0x3d4, 0x3cc, 0x3d8, 0x3dc};
  for (const std::size_t offset : offsets) {
    if (load<std::uint32_t>(field(editor, offset)) == 0) {
      continue;
    }
    invoke(editor, NativeOp::dispose_viewer_prepare, 0x007c3ba0, 0, offset, 0,
           0, 0, 0, field(editor, offset));
    void* object = load<void*>(field(editor, offset));
    if (object != nullptr) {
      invoke(editor, NativeOp::dispose_viewer_reset, 0x007c4000, 0, 0, 0, 0, 0,
             0, object);
      invoke(editor, NativeOp::dispose_viewer_free, 0x00f47380, 0, 0, 0, 0, 0,
             0, object);
    }
    store(field(editor, offset), static_cast<std::uint32_t>(0));
  }
}

std::int32_t truncate_float(float value) {
  if (!std::isfinite(value) ||
      value >= static_cast<float>(std::numeric_limits<std::int32_t>::max()) ||
      value <= static_cast<float>(std::numeric_limits<std::int32_t>::min())) {
    return std::numeric_limits<std::int32_t>::min();
  }
  return static_cast<std::int32_t>(value);
}

NativeResult route_message(OpaqueEditor* editor, std::uint32_t message_id,
                           void* message) {
  return invoke(editor, NativeOp::message_route, 0x00591fa0, 0, message_id, 0,
                0, 0, 0, message);
}

void transition_after_message_flag(OpaqueEditor* editor) {
  const std::uint32_t state =
      load<std::uint32_t>(field(editor, kOffsetMessageState));
  if (state != 0 && state != 6) {
    store(field(editor, kOffsetMessageStateValue),
          static_cast<std::uint32_t>(3));
  } else {
    invoke(editor, NativeOp::message_route, 0x0067ddd0, 0x50, 0, 0, 0, 0, 0,
           nullptr);
  }
}

}

extern "C" bool __thiscall editor_dispose_00576c50(OpaqueEditor* editor) {
  if (load<std::uint8_t>(field(editor, kOffsetActive)) != 0) {
    invoke(editor, NativeOp::dispose_self_1c, 0x00576c50, 0x1c, 0, 0, 0, 0, 0,
           editor);
  }
  invoke(editor, NativeOp::dispose_remove_hash, 0x0067de20, 0x1c, 0x13f5688, 0,
         0, 0, 0, editor);
  invoke(editor, NativeOp::dispose_remove_hash, 0x0067de20, 0x1c, 0x13f5670, 0,
         0, 0, 0, editor);
  invoke(editor, NativeOp::dispose_remove_hash, 0x0067de20, 0x1c, 0x13f5660, 0,
         0, 0, 0, editor);
  store(field(editor, kOffsetManager), static_cast<std::uint32_t>(0));
  const NativeResult app =
      invoke(editor, NativeOp::dispose_acquire_app, 0x0067dcc0);
  if (app.pointer != nullptr) {
    if (load<std::uint32_t>(field(editor, kOffsetGlobalFlag5c0)) != 0) {
      const std::uint32_t fifth =
          load<std::uint32_t>(field(editor, kOffsetGlobalFlag5c0));
      store(field(editor, kOffsetGlobalFlag5c0), static_cast<std::uint32_t>(0));
      invoke(editor, NativeOp::dispose_helper, 0x00571db0, 0,
             load<std::uint32_t>(field(editor, 0x5c4)),
             load<std::uint32_t>(field(editor, 0x5c8)),
             load<std::uint32_t>(field(editor, 0x5cc)),
             load<std::uint32_t>(field(editor, 0x5d0)), fifth);
    }
    invoke(editor, NativeOp::dispose_render_2c, 0x00576c50, 0x2c, 0xffffd8f1,
           0x29d57f4, 0, 0, 0, field(editor, 0x10));
    invoke(editor, NativeOp::dispose_render_2c, 0x00576c50, 0x2c, 0xffffd8f1,
           0x3fc3f13, 0, 0, 0, field(editor, 0x10));
    invoke(editor, NativeOp::dispose_render_2c, 0x00576c50, 0x2c, 0xffffd8f1,
           0x62628f0, 0, 0, 0, field(editor, 0x10));
  }
  invoke(editor, NativeOp::dispose_helper, 0x00563de0);
  invoke(editor, NativeOp::dispose_helper, 0x00563de0);
  if (load<std::uint32_t>(field(editor, kOffsetExitModeArg)) != 0) {
    invoke(editor, NativeOp::dispose_release_prepare, 0x004ad330);
    release_0098(editor);
  }
  if (load<std::uint32_t>(field(editor, kOffsetExitModeArg2)) != 0) {
    invoke(editor, NativeOp::dispose_release_prepare, 0x004ad330);
    release_0098(editor);
  }
  release_ref40(editor, kOffsetObjectA0);
  release_ref40(editor, kOffsetObjectA8);
  release_ref40(editor, kOffsetObjectAc);
  release_slot4(editor, kOffsetObject84);
  release_slot4(editor, kOffsetObject8c);
  release_slot4(editor, kOffsetObject88);
  invoke(editor, NativeOp::dispose_shadow_0018, 0x0067dd80, 0x18, 0x0e4c6e4, 0,
         0, 0, 0, nullptr);
  invoke(editor, NativeOp::dispose_shadow_0018, 0x0067dd80, 0x18, 0x21b37d6, 0,
         0, 0, 0, nullptr);
  invoke(editor, NativeOp::dispose_shadow_0018, 0x0067dd80, 0x18, 0x05557b15, 0,
         0, 0, 0, nullptr);
  invoke(editor, NativeOp::dispose_world_0050, 0x0067ddd0, 0x50, 0x0e4c6e4, 0,
         0, 0, 0, nullptr);
  release_slot4(editor, kOffsetObject15c);
  release_004b9140(editor, kOffsetObject90);
  release_viewers(editor);
  invoke(editor, NativeOp::dispose_preferences, 0x00a206f0, 0x38, 0x0347536b,
         0x03475385, 0xb07c3bbf, 0x034753a0);
  invoke(editor, NativeOp::dispose_completion, 0x006b1f90, 0, 0, 0, 0, 0, 0,
         nullptr);
  invoke(editor, NativeOp::dispose_helper, 0x005a98f0);
  if (g_editor_lifecycle_wave6_globals.global_service_015eebec != nullptr) {
    void* service = *g_editor_lifecycle_wave6_globals.global_service_015eebec;
    if (service != nullptr) {
      *g_editor_lifecycle_wave6_globals.global_service_015eebec = nullptr;
      invoke(editor, NativeOp::dispose_release_virtual, 0, 8, 0, 0, 0, 0, 0,
             service);
    }
  }
  return true;
}

extern "C" bool __thiscall editor_initialize_00584300(OpaqueEditor* editor,
                                                      OpaqueManager* manager) {
  const std::uint32_t old_map_word =
      load<std::uint32_t>(field(editor, kOffsetMapCount));
  invoke(editor, NativeOp::initialize_map_prepare, 0x009a9600, 0, old_map_word,
         0, 0, 0, 0, field(editor, 0x454));
  auto* sentinel = field(editor, kOffsetMapSentinel);
  store(field(editor, kOffsetMapSentinel),
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(sentinel)));
  store(field(editor, kOffsetMapRight),
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(sentinel)));
  store(field(editor, kOffsetMapCount), static_cast<std::uint32_t>(0));
  store(field(editor, kOffsetMapBytes), static_cast<std::uint32_t>(0));
  store(field(editor, kOffsetMapTail), static_cast<std::uint32_t>(0));
  store(field(editor, kOffsetManager),
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(manager)));
  NativeResult manager_object =
      invoke(editor, NativeOp::initialize_manager_0050, 0x00584300, 0x50, 0, 0,
             0, 0, 0, manager);
  if (manager_object.pointer != nullptr) {
    invoke(editor, NativeOp::initialize_manager_0020, 0x00584300, 0x20,
           0x0fcc521, 0x05a4150, 0, 0, 0, manager_object.pointer);
  }
  manager_object = invoke(editor, NativeOp::initialize_manager_0050, 0x00584300,
                          0x50, 0, 0, 0, 0, 0, manager);
  if (manager_object.pointer != nullptr) {
    invoke(editor, NativeOp::initialize_manager_0020, 0x00584300, 0x20,
           0x03d437e3, 0x00627c70, 0, 0, 0, manager_object.pointer);
  }
  constexpr std::uint32_t hashes[] = {0x3615a30b, 0x465c50ba, 0xd817cd63,
                                      0x99f87089, 0x96b24187, 0x1c7eca95};
  for (const std::uint32_t hash : hashes) {
    invoke(editor, NativeOp::initialize_register_hash, 0x00643a40, 0, hash, 0,
           0, 0, 0, field(editor, 0x1b0));
  }
  invoke(editor, NativeOp::initialize_services, 0x00584300, 0, 0, 0, 0, 0, 0,
         nullptr);
  const NativeResult required =
      invoke(editor, NativeOp::initialize_required_008de1a0, 0x008de1a0);
  if (required.pointer == nullptr) {
    return false;
  }
  invoke(editor, NativeOp::initialize_late, 0x00584300, 0, 0, 0, 0, 0, 0,
         required.pointer);
  const float scalar =
      g_editor_lifecycle_wave6_globals.source_01465544 == nullptr
          ? 0.0F
          : *g_editor_lifecycle_wave6_globals.source_01465544;
  store(field(editor, kOffsetDefaultScalar), scalar);
  invoke(editor, NativeOp::initialize_manager_0050, 0x00584300, 0x50, 0, 0, 0,
         0, 0, editor);
  store(field(editor, 0x580), static_cast<std::uint32_t>(0));
  store<std::uint16_t>(field(editor, 0x584), static_cast<std::uint16_t>(0));
  constexpr std::uint32_t listeners[] = {0x13f5688, 0x13f5c94, 0x13f5670,
                                         0x13f5660};
  for (const std::uint32_t listener : listeners) {
    invoke(editor, NativeOp::initialize_listener, 0x0067de20, 0x18, listener, 0,
           0, 0, 0, editor);
  }
  return true;
}

extern "C" void __thiscall editor_on_exit_00587a20(OpaqueEditor* editor) {
  if (load<std::uint32_t>(field(editor, kOffsetExitObject94)) != 0) {
    invoke(editor, NativeOp::exit_slot_0034, 0x00587a20, 0x34, 0, 0, 0, 0, 0,
           field(editor, kOffsetExitObject94));
  }
  store(field(editor, kOffsetActive), static_cast<std::uint8_t>(0));
  invoke(editor, NativeOp::exit_property_int, 0x006a1880, 0,
         load<std::uint32_t>(field(editor, 0x450)), 11, 0, 0, 0, nullptr);
  invoke(editor, NativeOp::exit_phase, 0x00587a20, 0, 1, 0, 0, 0, 0, nullptr);
  if (load<std::uint32_t>(field(editor, kOffsetExitObjectE0)) != 0) {
    void* object = load<void*>(field(editor, kOffsetExitObjectE0));
    store(field(editor, kOffsetExitObjectE0), static_cast<std::uint32_t>(0));
    invoke(editor, NativeOp::exit_release_0008, 0x00587a20, 8, 0, 0, 0, 0, 0,
           object);
  }
  invoke(editor, NativeOp::exit_phase, 0x00587a20, 0, 2, 0, 0, 0, 0, nullptr);
  const NativeResult renderer = invoke(editor, NativeOp::exit_phase, 0x00587a20,
                                       0, 3, 0, 0, 0, 0, nullptr);
  if (renderer.boolean) {
    invoke(editor, NativeOp::exit_set_mode, 0x00587270, 0, 1, 0, 0, 0, 0,
           nullptr);
  }
  invoke(editor, NativeOp::exit_phase, 0x00587a20, 0, 4, 0, 0, 0, 0, nullptr);
  if (load<std::uint32_t>(field(editor, kOffsetExitRelease)) != 0) {
    const std::uint32_t first = load<std::uint32_t>(field(editor, 0x5d4));
    store(field(editor, kOffsetExitRelease), static_cast<std::uint32_t>(0));
    invoke(editor, NativeOp::exit_release_0004, 0x00571db0, 0, first,
           load<std::uint32_t>(field(editor, 0x5d8)),
           load<std::uint32_t>(field(editor, 0x5dc)),
           load<std::uint32_t>(field(editor, 0x5e0)),
           load<std::uint32_t>(field(editor, 0x5e4)));
  }
  const NativeResult clock =
      invoke(editor, NativeOp::exit_accumulate, 0x008130a0);
  const std::uint64_t start =
      load<std::uint64_t>(field(editor, kOffsetClockBase));
  const std::uint64_t accumulated =
      load<std::uint64_t>(field(editor, kOffsetClockAccumulator));
  store(field(editor, kOffsetClockAccumulator),
        static_cast<std::uint64_t>(accumulated + clock.qword - start));
  invoke(editor, NativeOp::exit_cleanup, 0x0067cab0);
  invoke(editor, NativeOp::exit_cleanup, 0x00801bb0);
  invoke(editor, NativeOp::exit_cleanup, 0x00777ae0);
  invoke(editor, NativeOp::exit_cleanup, 0x00777ae0);
  invoke(editor, NativeOp::exit_cleanup, 0x00421cf0);
}

extern "C" void __thiscall editor_update_0058be50(OpaqueEditor* editor,
                                                  float first_delta,
                                                  float second_delta) {
  static_cast<void>(first_delta);
  if (load<std::uint8_t>(field(editor, kOffsetActive)) == 0) {
    return;
  }
  const std::uint64_t timer =
      load<std::uint64_t>(field(editor, kOffsetTimerLow));
  if (timer != 0) {
    const NativeResult query =
        invoke(editor, NativeOp::update_clock_query, 0x0067de30);
    if (query.pointer != nullptr) {
      invoke(editor, NativeOp::update_clock_release, 0, 4, 0, 0, 0, 0, 0,
             query.pointer);
      const NativeResult parsed =
          invoke(editor, NativeOp::update_clock_query, 0x0067de30, 0,
                 0xb55619c2, 0x851d4139, 0, 0, 0, query.pointer);
      if (parsed.boolean) {
        invoke(editor, NativeOp::update_clock_expired, 0x00410370, 0,
               0x091756c5, 0, 0, 0, 0, query.pointer);
      }
      if (invoke(editor, NativeOp::update_clock_expired, 0x0093a5e0).boolean) {
        invoke(editor, NativeOp::update_clock_expired, 0x00575120);
        invoke(editor, NativeOp::update_clock_expired, 0x005dc580);
      }
      invoke(editor, NativeOp::update_clock_release, 0, 4, 0, 0, 0, 0, 0,
             query.pointer);
    }
  }
  if (load<std::uint8_t>(field(editor, kOffsetBlockedState)) != 0 &&
      load<std::uint32_t>(field(editor, kOffsetBlockedOwner)) != 0) {
    const NativeResult blocked =
        invoke(editor, NativeOp::update_blocking_10, 0, 0x10, 0, 0, 0, 0, 0,
               field(editor, kOffsetBlockedOwner));
    if (blocked.signed_word > 0) {
      return;
    }
  }
  const std::int32_t milliseconds = truncate_float(second_delta * 1000.0F);
  if (load<std::uint32_t>(field(editor, kOffsetMessagePending)) != 0) {
    const NativeResult gate =
        invoke(editor, NativeOp::update_timer_gate, 0, 0, 0, 0, 0, 0, 0,
               field(editor, kOffsetMessagePending));
    if (gate.boolean) {
      const float remaining =
          load<float>(field(editor, kOffsetMessageTimer)) - second_delta;
      store(field(editor, kOffsetMessageTimer), remaining);
      if (remaining >= 0.0F) {
        invoke(editor, NativeOp::update_timer_expire, 0x005cc0e0, 0, 0, 0, 0, 0,
               0, nullptr);
      }
    }
  }
  invoke(editor, NativeOp::update_main, 0x0058be50, 0,
         static_cast<std::uint32_t>(milliseconds), 0, 0, 0, 0, nullptr,
         second_delta, second_delta);
  const std::uint32_t mode = load<std::uint32_t>(field(editor, kOffsetMode));
  if (mode == 0) {
    invoke(editor, NativeOp::update_mode, 0x0058be50, 0, 0, 0, 0, 0, 0,
           nullptr);
  } else if (mode == 2) {
    invoke(editor, NativeOp::update_play, 0x00577e10, 0, 0, 0, 0, 0, 0,
           nullptr);
    invoke(editor, NativeOp::update_play, 0x0062c550, 0, 0, 0, 0, 0, 0,
           nullptr);
  }
  invoke(editor, NativeOp::update_finish, 0x0058be50, 0, 0, 0, 0, 0, 0,
         nullptr);
}

extern "C" bool __thiscall editor_handle_message_00591fa0(
    OpaqueEditor* editor, std::uint32_t message_id, void* message) {
  switch (message_id) {
    case 0x1c94703:
      store(field(editor, kOffsetMessageFlag384), static_cast<std::uint8_t>(1));
      invoke(editor, NativeOp::message_route, 0x00591fa0, 0, message_id, 0, 0,
             0, 0, message);
      return false;
    case 0x1c94708:
      store(field(editor, kOffsetMessageFlag385), static_cast<std::uint8_t>(1));
      invoke(editor, NativeOp::message_route, 0x00591fa0, 0, message_id, 0, 0,
             0, 0, message);
      return false;
    case 0x29d57f4:
      store(field(editor, kOffsetMessageFlag389), static_cast<std::uint8_t>(0));
      invoke(editor, NativeOp::message_route, 0x00591fa0, 0, message_id, 0, 0,
             0, 0, message);
      return true;
    case 0x462c656:
      store(field(editor, 0x190), static_cast<std::uint32_t>(0));
      invoke(editor, NativeOp::message_route, 0x00591fa0, 0, message_id, 0, 0,
             0, 0, message);
      return true;
    case 0x657abe5:
      store(static_cast<std::uint8_t*>(message) + 8,
            static_cast<std::uint32_t>(0));
      transition_after_message_flag(editor);
      return false;
    case 0x1ee1009: {
      auto* target =
          load<std::uint8_t*>(static_cast<std::uint8_t*>(message) + 8);
      store(target, static_cast<std::uint8_t>(0));
      transition_after_message_flag(editor);
      return false;
    }
    case 0x7aa519dc: {
      if (load<std::uint32_t>(message) !=
          load<std::uint32_t>(field(editor, kOffsetMessageKey))) {
        return false;
      }
      route_message(editor, message_id, message);
      store(field(editor, kOffsetMessageFlag4a4),
            static_cast<std::uint32_t>(1));
      if (load<std::uint32_t>(field(editor, 0x68)) != 0) {
        route_message(editor, message_id, message);
      }
      route_message(editor, message_id, message);
      return true;
    }
    case 0x14418c3f: {
      if (load<std::uint32_t>(message) !=
          load<std::uint32_t>(field(editor, kOffsetMessageKey))) {
        return false;
      }
      store(field(editor, kOffsetMessageFlag4a4),
            static_cast<std::uint32_t>(1));
      route_message(editor, message_id, message);
      return true;
    }
    case 0xd1511790: {
      if (load<std::uint32_t>(field(editor, 0x198)) == 1 ||
          load<std::uint8_t>(field(editor, 0x2a0)) == 0) {
        return false;
      }
      const std::uint32_t payload_key =
          load<std::uint32_t>(static_cast<std::uint8_t*>(message) + 0x14);
      if (payload_key != 0 && payload_key != load<std::uint32_t>(field(
                                                 editor, kOffsetMessageKey))) {
        return false;
      }
      const NativeResult accepted = route_message(editor, message_id, message);
      if (!accepted.boolean) {
        invoke(editor, NativeOp::message_commit, 0x00572620, 0, message_id, 0,
               0, 0, 0, message);
      }
      return true;
    }
    case 0xb2e18705: {
      const std::uint32_t request =
          load<std::uint32_t>(static_cast<std::uint8_t*>(message) + 0x20);
      if (request == 0) {
        return route_message(editor, message_id, message).boolean;
      }
      void* object = load<void*>(static_cast<std::uint8_t*>(message) + 0x20);
      const NativeResult value = invoke(editor, NativeOp::message_object_000c,
                                        0, 0xc, 0, 0, 0, 0, 0, object);
      return invoke(editor, NativeOp::message_route, 0x00591690, 0, value.word,
                    load<std::uint32_t>(static_cast<std::uint8_t*>(message) +
                                        0x10),
                    0, 0, 0, message)
          .boolean;
    }
    case 0x5132389:
      return route_message(editor, message_id, message).boolean;
    case 0xf1ff568b: {
      if (load<std::uint8_t>(static_cast<std::uint8_t*>(message) + 0xc) == 0) {
        return false;
      }
      if (invoke(editor, NativeOp::message_route, 0x004eb930).boolean) {
        store(static_cast<std::uint8_t*>(message) + 0x10,
              static_cast<std::uint32_t>(0xa6c97621));
        store(static_cast<std::uint8_t*>(message) + 0x14,
              static_cast<std::uint32_t>(0x00b1b104));
        store(static_cast<std::uint8_t*>(message) + 0x18,
              static_cast<std::uint32_t>(0x490f6945));
        store(static_cast<std::uint8_t*>(static_cast<std::uint8_t*>(message) +
                                         0xc),
              static_cast<std::uint8_t>(0));
      }
      return false;
    }
    case 0x7f18f481: {
      const std::uint32_t key = load<std::uint32_t>(message);
      if (key == load<std::uint32_t>(field(editor, kOffsetMessageKey2))) {
        route_message(editor, message_id, message);
      }
      if (key == load<std::uint32_t>(field(editor, kOffsetMessageKey4)) &&
          load<std::uint32_t>(field(editor, kOffsetMessageKey4)) != 0) {
        void* object = load<void*>(field(editor, kOffsetMessageKey4));
        store(field(editor, kOffsetMessageKey4), static_cast<std::uint32_t>(0));
        invoke(editor, NativeOp::message_release, 0, 8, 0, 0, 0, 0, 0, object);
      }
      if (key == load<std::uint32_t>(field(editor, kOffsetMessageKey3))) {
        route_message(editor, message_id, message);
      }
      return false;
    }
    case 0x90a03fdf:
      route_message(editor, message_id, message);
      if (load<std::uint32_t>(field(editor, kOffsetMessagePayloadOwner)) != 0) {
        void* owner = load<void*>(field(editor, kOffsetMessagePayloadOwner));
        if (load<std::uint8_t>(static_cast<std::uint8_t*>(owner) + 0x64) != 0) {
          route_message(editor, message_id, message);
        }
      }
      route_message(editor, message_id, message);
      return false;
    case 0xb03bc30c: {
      if (load<std::uint8_t>(field(editor, 0x300)) == 0) {
        store(field(editor, kOffsetMessageFlag1c0),
              static_cast<std::uint32_t>(0));
        store(field(editor, 0x1c4), static_cast<std::uint32_t>(0));
        store(field(editor, 0x1c8), static_cast<std::uint32_t>(0));
      } else {
        void* source = load<void*>(field(editor, kOffsetMessagePayloadOwner));
        store(field(editor, kOffsetMessageFlag1c0),
              load<std::uint32_t>(static_cast<std::uint8_t*>(source) + 0x10));
        store(field(editor, 0x1c4),
              load<std::uint32_t>(static_cast<std::uint8_t*>(source) + 0x14));
        store(field(editor, 0x1c8),
              load<std::uint32_t>(static_cast<std::uint8_t*>(source) + 0x18));
      }
      route_message(editor, message_id, message);
      const NativeResult clock =
          invoke(editor, NativeOp::message_route, 0x008130a0);
      store(field(editor, kOffsetMessageSnapshotClock), clock.qword);
      return false;
    }
    case 0xf058b0f2: {
      if (load<std::uint8_t>(field(editor, 0x300)) == 0) {
        store(field(editor, kOffsetMessageFlag1c0),
              static_cast<std::uint32_t>(0));
        store(field(editor, 0x1c4), static_cast<std::uint32_t>(0));
        store(field(editor, 0x1c8), static_cast<std::uint32_t>(0));
      } else {
        void* source = load<void*>(field(editor, kOffsetMessagePayloadOwner));
        store(field(editor, kOffsetMessageFlag1c0),
              load<std::uint32_t>(static_cast<std::uint8_t*>(source) + 0x10));
        store(field(editor, 0x1c4),
              load<std::uint32_t>(static_cast<std::uint8_t*>(source) + 0x14));
        store(field(editor, 0x1c8),
              load<std::uint32_t>(static_cast<std::uint8_t*>(source) + 0x18));
      }
      return false;
    }
    case 0x22d308b:
      route_message(editor, message_id, message);
      return true;
    case 0x52f180:
      route_message(editor, message_id, message);
      return true;
    case 0x48e5911:
      route_message(editor, message_id, message);
      return true;
    case 0x48e5912:
      route_message(editor, message_id, message);
      return true;
    case 0x24ce123:
    case 0x3fc3f13:
    case 0x44ef2b8:
    case 0x4519b5f:
    case 0x47d7cc6:
    case 0x4aca143:
    case 0x51cc0b8:
    case 0x56d39e9:
    case 0x5d02a72:
    case 0x60b3d03:
    case 0x62628f0:
    case 0x685309be:
    case 0x68cd252:
    case 0x90e08f60:
      route_message(editor, message_id, message);
      return false;
    default:
      return false;
  }
}

}
