#include "game_mode_wave7.hpp"

#if defined(_MSC_VER)
#define PKG_GAME_MODE_WAVE7_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_GAME_MODE_WAVE7_THISCALL __attribute__((thiscall))
#else
#error "PKG-GAME-MODE-WAVE7 requires an MSVC or GCC thiscall convention"
#endif

#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace openspore::reconstruction::pkg_game_mode_wave7 {

AppModePorts g_app_mode_ports{};
BridgeGlobals g_bridge_globals{};
BridgePorts g_app_simulator_bridge_ports{};
CellModePorts g_cell_mode_ports{};

namespace {

std::size_t app_mode_count(const AppModeRegistry* registry) {
  return static_cast<std::size_t>(registry->entries_end -
                                  registry->entries_begin);
}

bool equal_mode_name(const char* left, const char* right) {
  const unsigned char* first = reinterpret_cast<const unsigned char*>(left);
  const unsigned char* second = reinterpret_cast<const unsigned char*>(right);
  while (*first != 0U && *second != 0U) {
    if (std::tolower(*first) != std::tolower(*second)) {
      return false;
    }
    ++first;
    ++second;
  }
  return *first == *second;
}

std::uint8_t load_u8(const void* address, std::size_t offset) {
  std::uint8_t value{};
  std::memcpy(&value, static_cast<const std::uint8_t*>(address) + offset,
              sizeof(value));
  return value;
}

std::uint32_t load_u32(const void* address, std::size_t offset) {
  std::uint32_t value{};
  std::memcpy(&value, static_cast<const std::uint8_t*>(address) + offset,
              sizeof(value));
  return value;
}

void store_u8(void* address, std::size_t offset, std::uint8_t value) {
  std::memcpy(static_cast<std::uint8_t*>(address) + offset, &value,
              sizeof(value));
}

void store_u32(void* address, std::size_t offset, std::uint32_t value) {
  std::memcpy(static_cast<std::uint8_t*>(address) + offset, &value,
              sizeof(value));
}

void* address_of(std::uintptr_t value) {
  return reinterpret_cast<void*>(value);
}

}

extern "C" bool PKG_GAME_MODE_WAVE7_THISCALL app_mode_activate_index_007d8c80(
    AppModeRegistry* registry, std::int32_t index) {
  if (index < 0 ||
      static_cast<std::size_t>(index) >= app_mode_count(registry)) {
    return false;
  }
  app_mode_activate_007d85b0(registry, index);
  return true;
}

extern "C" void PKG_GAME_MODE_WAVE7_THISCALL
app_mode_activate_007d85b0(AppModeRegistry* registry, std::int32_t index) {
  const std::int32_t old_index =
      static_cast<std::int32_t>(registry->active_index);
  if (old_index == index) {
    return;
  }

  AppModeEntry* next_entry = registry->entries_begin + index;
  std::uint32_t old_notification_word = 0U;
  if (old_index >= 0 &&
      static_cast<std::size_t>(old_index) < app_mode_count(registry)) {
    OpaqueAppMode* old_mode = registry->entries_begin[old_index].mode;
    old_mode->vtable->on_exit(old_mode);
    old_notification_word =
        registry->entries_begin[old_index].notification_word;
  }

  registry->active_index = static_cast<std::uint32_t>(index);

  OpaqueNotificationManager* notification_manager =
      g_app_mode_ports.notifications.acquire();
  if (notification_manager != nullptr) {
    AppNotificationRecord record{0x212d3e7U, old_notification_word, 0U};
    notification_manager->vtable->dispatch(notification_manager, record.kind,
                                           &record);
    g_app_mode_ports.notifications.destroy(&record);
  }

  OpaqueAppMode* next_mode = next_entry->mode;
  next_mode->vtable->on_enter(next_mode);

  if (notification_manager != nullptr) {
    AppNotificationRecord record{0x22d1adcU, next_entry->notification_word, 1U};
    notification_manager->vtable->dispatch(notification_manager, record.kind,
                                           &record);
    g_app_mode_ports.notifications.destroy(&record);
  }
}

extern "C" bool PKG_GAME_MODE_WAVE7_THISCALL app_mode_activate_by_name_007d8360(
    AppModeRegistry* registry, const char* name) {
  const std::size_t count = app_mode_count(registry);
  for (std::size_t index = 0; index < count; ++index) {
    const AppModeEntry& entry = registry->entries_begin[index];
    if (entry.name_begin != entry.name_end &&
        equal_mode_name(entry.name_begin, name)) {
      return registry->vtable->activate_by_index(
          registry, static_cast<std::int32_t>(index));
    }
  }
  return false;
}

extern "C" bool PKG_GAME_MODE_WAVE7_THISCALL strategy_request_ready_00b5b840(
    StrategyState* strategy, std::uint32_t requested) {
  if (strategy->vtable->axis_a(strategy) != requested) {
    return false;
  }
  if (strategy->vtable->axis_b(strategy) != requested) {
    return false;
  }
  return strategy->pending == kNoPendingStrategyRequest;
}

extern "C" void PKG_GAME_MODE_WAVE7_THISCALL strategy_queue_primary_00b5b880(
    StrategyState* strategy, std::uint32_t requested) {
  strategy->request_kind = 1U;
  if (strategy->pending == kNoPendingStrategyRequest) {
    strategy->pending = requested;
  }
}

extern "C" void PKG_GAME_MODE_WAVE7_THISCALL strategy_queue_secondary_00b5b8a0(
    StrategyState* strategy, std::uint32_t requested) {
  strategy->request_kind = 2U;
  if (strategy->pending == kNoPendingStrategyRequest) {
    strategy->pending = requested;
  }
}

extern "C" void PKG_GAME_MODE_WAVE7_THISCALL
strategy_commit_primary_00b5b8c0(StrategyState* strategy) {
  strategy->committed_a = strategy->pending;
  strategy->pending = kNoPendingStrategyRequest;
  strategy->request_kind = 0U;
}

extern "C" void PKG_GAME_MODE_WAVE7_THISCALL
strategy_commit_secondary_00b5b8e0(StrategyState* strategy) {
  strategy->committed_b = strategy->pending;
  strategy->pending = kNoPendingStrategyRequest;
  strategy->request_kind = 0U;
}

extern "C" bool PKG_GAME_MODE_WAVE7_THISCALL app_simulator_mode_bridge_00b63510(
    OpaqueBridge* bridge, std::uint32_t message_id, void* payload) {
  BridgePorts& ports = g_app_simulator_bridge_ports;
  if (message_id <= 0x3e9a620U) {
    if (message_id == 0x3e9a620U) {
      g_bridge_globals.flag_01686af1 = 1U;
      return false;
    }
    if (message_id > 0x212d3e7U) {
      if (message_id == 0x22d1adcU) {
        const std::uint32_t first =
            ports.resolve_00b5c9d0(load_u32(payload, 0x10));
        const std::uint32_t second =
            ports.resolve_00b5c9d0(load_u32(payload, 0x08));
        if (first == second) {
          return true;
        }
        if (bridge->notification_enabled == 0U) {
          ports.ensure_00b60d80(bridge);
          if (bridge->notification_enabled == 0U) {
            return true;
          }
        }
        if (message_id == 0x212d3e7U) {
          ports.notify_212d3e7(bridge, first, second);
        } else {
          ports.notify_22d1adc(bridge, first, second);
        }
        return true;
      }
      if (message_id == 0x255abf5U) {
        if (load_u32(payload, 0x08) == 1U) {
          --bridge->counter_30;
        } else {
          ++bridge->counter_30;
        }
        return true;
      }
      return false;
    }
    if (message_id == 0x212d3e7U) {
      const std::uint32_t first =
          ports.resolve_00b5c9d0(load_u32(payload, 0x10));
      const std::uint32_t second =
          ports.resolve_00b5c9d0(load_u32(payload, 0x08));
      if (first == second) {
        return true;
      }
      if (bridge->notification_enabled == 0U) {
        ports.ensure_00b60d80(bridge);
        if (bridge->notification_enabled == 0U) {
          return true;
        }
      }
      if (message_id == 0x212d3e7U) {
        ports.notify_212d3e7(bridge, first, second);
      } else {
        ports.notify_22d1adc(bridge, first, second);
      }
      return true;
    }
    if (message_id == 0x0f62adeU) {
      const std::uint32_t first = load_u32(payload, 0x10);
      const std::uint32_t second = load_u32(payload, 0x18);
      if (first == 0x24a4f5aU) {
        OpaqueModeObject* current = ports.get_00b3d270();
        if (second == current->field_308) {
          ports.action_00b108b0(ports.get_00b3d270());
        }
      }
      OpaqueModeObject* target = ports.get_00b3d280();
      if (target == nullptr || first != 0x24a4f5aU ||
          second != target->field_308) {
        return false;
      }
      ports.action_00b108b0(ports.get_00b3d280());
      return false;
    }
    if (message_id == 0x0f62defU) {
      if (load_u32(payload, 0x18) == 0x39393837U) {
        OpaqueModeObject* mode = ports.get_00b3d320();
        if (mode != nullptr) {
          ports.dispatch_00b5e3f0(bridge, ports.get_00b5b800());
        }
      }
      return true;
    }
    return false;
  }

  if (message_id < 0x12a93f06U) {
    if (message_id == 0x12a93f05U) {
      if (load_u8(payload, 0) != 0U || !ports.query_00b5ca70()) {
        return false;
      }
      store_u8(payload, 0, 1U);
      return false;
    }
    if (message_id == 0x3e9a625U) {
      g_bridge_globals.flag_01686af1 = 0U;
      return false;
    }
    if (message_id != 0x4715068U) {
      return false;
    }
    if (ports.query_00e00ac0()) {
      OpaqueAppSystem* app_system = ports.app_system_get();
      ports.app_system_vtable_14(app_system, 0x64eb18eU, 0U, 0U);
    }
    if (ports.get_00b5b800() == address_of(0x01654c10U)) {
      OpaqueScenarioMode* scenario_mode = ports.get_scenario_mode();
      if (scenario_mode->mode_d0 == 2U) {
        ports.tree_node_vtable_2c(ports.get_00b3d320(),
                                  reinterpret_cast<const char*>(0x01654c05U));
      }
    }
    OpaqueModeObject* mode = ports.get_00b3d320();
    if (mode->flag_28 != 0U) {
      OpaqueAppSystem* app_system = ports.app_system_get();
      ports.app_system_vtable_18(app_system, 0x4715068U, 0U, 0U, 0U);
      return true;
    }
    if (ports.get_00b5b800() == address_of(0x01654c05U)) {
      if (!ports.query_01021080()) {
        void* root = ports.get_01002bd0();
        if (root != nullptr) {
          void* target = static_cast<std::uint8_t*>(root) + 0x20U;
          if (ports.query_00d09660(target)) {
            ports.action_00d100b0(target, 1U, 0U);
          }
        }
        void* reset_root = ports.get_00fd9c60();
        ports.action_00fde3e0(reset_root);
      }
    }
    OpaqueAppSystem* app_system = ports.app_system_get();
    ports.app_system_vtable_14(app_system, 0x689c9b9U, 0U, 0U);
    OpaqueGraphics* graphics = ports.graphics_get();
    ports.graphics_vtable_40(graphics);
    ports.get_00b3d320()->flag_28 = 1U;
    ports.get_00b3d320()->flag_29 = 1U;
    return true;
  }

  if (message_id == 0xf1ff568bU) {
    if (load_u8(payload, 0x0c) == 0U || ports.query_00b5cb20(payload)) {
      return false;
    }
    store_u32(payload, 0x10, 0xcdccb5aeU);
    store_u32(payload, 0x14, 0x00b1b104U);
    store_u32(payload, 0x18, 0x490f6945U);
    store_u8(payload, 0x0c, 0U);
    return false;
  }
  if (message_id == 0xf52feda1U) {
    void* summarizer = ports.create_00f473a0(
        8U, reinterpret_cast<const char*>(0x01463ef8U), 0U, 0U, 0U, 0U);
    if (summarizer != nullptr) {
      store_u32(summarizer, 0x04, 0U);
      store_u32(summarizer, 0x00, 0x01462690U);
    }
    void* service = ports.get_0067cb40();
    ports.register_summarizer(service, summarizer);
    return false;
  }
  return false;
}

extern "C" void cell_mode_constructor_00e616c0(CellModeOwner* owner) {
  CellModeObject* object =
      g_cell_mode_ports.factory(0x0cU, 0x013ebc58U, 0U, 0U, 0U, 0U);
  if (object != nullptr) {
    object->secondary_vtable = 0x013eb394U;
    object->primary_vtable = 0x01485558U;
    object->secondary_vtable = 0x01485550U;
  }
  owner->vtable->register_mode(owner, object,
                               reinterpret_cast<const char*>(0x01654c00U),
                               reinterpret_cast<const char*>(0x014856d8U));
}

}

#undef PKG_GAME_MODE_WAVE7_THISCALL
