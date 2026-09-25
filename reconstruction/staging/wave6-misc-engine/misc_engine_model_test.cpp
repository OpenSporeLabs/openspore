#include <cstdlib>

#include "misc_engine.hpp"

namespace {

using openspore::reconstruction::wave6_misc_engine::DeletingDestructorPorts;
using openspore::reconstruction::wave6_misc_engine::g_app_system_015fd890;
using openspore::reconstruction::wave6_misc_engine::g_deleting_destructor_ports;
using openspore::reconstruction::wave6_misc_engine::
    g_game_time_manager_0167eb3c;
using openspore::reconstruction::wave6_misc_engine::g_message_queue_ports;
using openspore::reconstruction::wave6_misc_engine::
    message_manager_get_queue_0098f4d0;
using openspore::reconstruction::wave6_misc_engine::MessageQueuePorts;
using openspore::reconstruction::wave6_misc_engine::OpaqueDestructible;
using openspore::reconstruction::wave6_misc_engine::OpaqueIAppSystem;
using openspore::reconstruction::wave6_misc_engine::OpaqueMessageManager;
using openspore::reconstruction::wave6_misc_engine::OpaqueMessageService;
using openspore::reconstruction::wave6_misc_engine::TargetWord;
using openspore::reconstruction::wave6_misc_engine::
    time_start_frame_deleting_destructor_00b63980;

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

unsigned char byte_at(std::byte value) {
  return std::to_integer<unsigned char>(value);
}

struct MessageFixture {
  std::array<std::byte, 0x208> service_prefix;
  OpaqueMessageManager manager;
};

OpaqueMessageService* prepared_service = nullptr;
TargetWord prepared_first = 0;
TargetWord prepared_second = 0;
unsigned prepare_calls = 0;
unsigned query_calls = 0;
TargetWord query_result = 0;
OpaqueDestructible* destroyed_receiver = nullptr;
unsigned base_destroy_calls = 0;
unsigned global_delete_calls = 0;

void prepare_queue(OpaqueMessageService* service, TargetWord first,
                   TargetWord second) {
  prepared_service = service;
  prepared_first = first;
  prepared_second = second;
  ++prepare_calls;
}

TargetWord query_queue(OpaqueMessageService* service) {
  check(service == prepared_service);
  ++query_calls;
  return query_result;
}

void destroy_base(OpaqueDestructible* receiver) {
  check(receiver == destroyed_receiver);
  check(receiver->vtable ==
        reinterpret_cast<decltype(receiver->vtable)>(0x01464450U));
  receiver->vtable = reinterpret_cast<decltype(receiver->vtable)>(0x013ec458U);
  ++base_destroy_calls;
}

void delete_globally(OpaqueDestructible* receiver) {
  check(receiver == destroyed_receiver);
  ++global_delete_calls;
}

MessageQueuePorts make_message_ports() {
  MessageQueuePorts ports{};
  ports.prepare_7c = prepare_queue;
  ports.query_90 = query_queue;
  return ports;
}

DeletingDestructorPorts make_destructor_ports() {
  DeletingDestructorPorts ports{};
  ports.base_destroy_005725a0 = destroy_base;
  ports.global_delete_00f47380 = delete_globally;
  return ports;
}

void test_service_and_time_accessors() {
  OpaqueIAppSystem app_system{};
  OpaqueIAppSystem* app_system_result = nullptr;
  openspore::reconstruction::wave6_misc_engine::OpaqueGameTimeManager
      time_manager{};
  openspore::reconstruction::wave6_misc_engine::OpaqueGameTimeManager*
      time_result = nullptr;

  g_app_system_015fd890 =
      static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(&app_system));
  g_game_time_manager_0167eb3c =
      static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(&time_manager));

  app_system_result = openspore::reconstruction::wave6_misc_engine::
      app_iapp_system_get_0067dcc0();
  time_result = openspore::reconstruction::wave6_misc_engine::
      game_time_manager_get_00b3d480();

  check(app_system_result == &app_system);
  check(time_result == &time_manager);

  g_app_system_015fd890 = 0;
  g_game_time_manager_0167eb3c = 0;
  check(openspore::reconstruction::wave6_misc_engine::
            app_iapp_system_get_0067dcc0() == nullptr);
  check(openspore::reconstruction::wave6_misc_engine::
            game_time_manager_get_00b3d480() == nullptr);
}

void test_message_queue_switch_and_callback_order() {
  MessageFixture fixture{};
  g_message_queue_ports = make_message_ports();
  prepare_calls = 0;
  query_calls = 0;
  prepared_service = nullptr;
  prepared_first = 0;
  prepared_second = 0;
  query_result = 0x89abcdefU;

  void* queue = reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x1111U));
  TargetWord result =
      message_manager_get_queue_0098f4d0(&fixture.manager, 0U, queue);
  check(result == query_result);
  check(prepare_calls == 1U);
  check(query_calls == 1U);
  check(prepared_service ==
        reinterpret_cast<OpaqueMessageService*>(fixture.service_prefix.data()));
  check(prepared_first == 8U);
  check(prepared_second == 1U);
  check(byte_at(fixture.manager.opaque[0xac]) == 0x11U);
  check(byte_at(fixture.manager.opaque[0xad]) == 0x11U);
  check(byte_at(fixture.manager.opaque[0xae]) == 0U);
  check(byte_at(fixture.manager.opaque[0xaf]) == 0U);

  for (TargetWord index = 0; index < 4U; ++index) {
    void* value =
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x2000U + index));
    message_manager_get_queue_0098f4d0(&fixture.manager, index, value);
  }
  check(byte_at(fixture.manager.opaque[0xac]) == 0x00U);
  check(byte_at(fixture.manager.opaque[0xad]) == 0x20U);
  check(byte_at(fixture.manager.opaque[0xb0]) == 0x01U);
  check(byte_at(fixture.manager.opaque[0xb1]) == 0x20U);
  check(byte_at(fixture.manager.opaque[0xb4]) == 0x02U);
  check(byte_at(fixture.manager.opaque[0xb5]) == 0x20U);
  check(byte_at(fixture.manager.opaque[0xb8]) == 0x03U);
  check(byte_at(fixture.manager.opaque[0xb9]) == 0x20U);

  message_manager_get_queue_0098f4d0(
      &fixture.manager, 4U,
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x3000U)));
  check(prepare_calls == 6U);
  check(query_calls == 6U);
  check(byte_at(fixture.manager.opaque[0xac]) == 0x00U);
  check(byte_at(fixture.manager.opaque[0xad]) == 0x20U);
  check(byte_at(fixture.manager.opaque[0xb0]) == 0x01U);
  check(byte_at(fixture.manager.opaque[0xb1]) == 0x20U);
  check(byte_at(fixture.manager.opaque[0xb4]) == 0x02U);
  check(byte_at(fixture.manager.opaque[0xb5]) == 0x20U);
  check(byte_at(fixture.manager.opaque[0xb8]) == 0x03U);
  check(byte_at(fixture.manager.opaque[0xb9]) == 0x20U);
}

void test_deleting_destructor_flag_and_order() {
  OpaqueDestructible receiver{};
  g_deleting_destructor_ports = make_destructor_ports();
  destroyed_receiver = &receiver;
  base_destroy_calls = 0;
  global_delete_calls = 0;
  receiver.vtable = reinterpret_cast<decltype(receiver.vtable)>(0x11111111U);

  OpaqueDestructible* result =
      time_start_frame_deleting_destructor_00b63980(&receiver, 0U);
  check(result == &receiver);
  check(base_destroy_calls == 1U);
  check(global_delete_calls == 0U);
  check(receiver.vtable ==
        reinterpret_cast<decltype(receiver.vtable)>(0x013ec458U));

  result = time_start_frame_deleting_destructor_00b63980(&receiver, 1U);
  check(result == &receiver);
  check(base_destroy_calls == 2U);
  check(global_delete_calls == 1U);

  result = time_start_frame_deleting_destructor_00b63980(&receiver, 2U);
  check(result == &receiver);
  check(base_destroy_calls == 3U);
  check(global_delete_calls == 1U);

  result =
      time_start_frame_deleting_destructor_00b63980(&receiver, 0xffffffffU);
  check(result == &receiver);
  check(base_destroy_calls == 4U);
  check(global_delete_calls == 2U);
}

}

int main() {
  test_service_and_time_accessors();
  test_message_queue_switch_and_callback_order();
  test_deleting_destructor_flag_and_order();
  return 0;
}
