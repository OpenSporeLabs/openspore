#include "misc_engine.hpp"

#include <cstring>

namespace openspore::reconstruction::wave6_misc_engine {

namespace {

template <typename Value>
Value load_word(const void* object, std::size_t offset) {
  Value value{};
  std::memcpy(&value, static_cast<const unsigned char*>(object) + offset,
              sizeof(value));
  return value;
}

template <typename Value>
void store_word(void* object, std::size_t offset, Value value) {
  std::memcpy(static_cast<unsigned char*>(object) + offset, &value,
              sizeof(value));
}

template <typename Pointer>
Pointer target_pointer(TargetWord word) {
  return reinterpret_cast<Pointer>(static_cast<std::uintptr_t>(word));
}

OpaqueMessageService* service_from_manager(OpaqueMessageManager* manager) {
  return reinterpret_cast<OpaqueMessageService*>(
      reinterpret_cast<unsigned char*>(manager) - 0x208U);
}

}

TargetWord g_game_time_manager_0167eb3c = 0;
MessageQueuePorts g_message_queue_ports{};
DeletingDestructorPorts g_deleting_destructor_ports{};

OpaqueGameTimeManager* WAVE6_CDECL game_time_manager_get_00b3d480() {
  return target_pointer<OpaqueGameTimeManager*>(g_game_time_manager_0167eb3c);
}

TargetWord WAVE6_THISCALL message_manager_get_queue_0098f4d0(
    OpaqueMessageManager* manager, TargetWord queue_index, void* queue) {
  if (queue_index <= 3U) {
    store_word(
        manager, 0xacU + queue_index * sizeof(TargetWord),
        static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(queue)));
  }

  OpaqueMessageService* service = service_from_manager(manager);
  g_message_queue_ports.prepare_7c(service, 8U, 1U);
  return g_message_queue_ports.query_90(service);
}

OpaqueDestructible* WAVE6_THISCALL destructible_lifecycle_thunk_00b63980(
    OpaqueDestructible* receiver, TargetWord deleting_flag) {
  receiver->vtable = reinterpret_cast<OpaqueDestructibleVtable*>(0x01464450U);
  g_deleting_destructor_ports.base_destroy_005725a0(receiver);
  if ((deleting_flag & 1U) != 0U) {
    g_deleting_destructor_ports.global_delete_00f47380(receiver);
  }
  return receiver;
}

}
