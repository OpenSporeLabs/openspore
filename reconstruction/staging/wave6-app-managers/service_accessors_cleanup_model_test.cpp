#include "service_accessors_cleanup.hpp"

using namespace openspore::reconstruction::wave6_app_managers;

#include <cassert>
#include <cstdint>
#include <vector>

namespace {

std::vector<void*> released;
OpaqueMessageCleanupWindow* root_to_clear = nullptr;

#if defined(_MSC_VER)
#define TEST_CDECL __cdecl
#else
#define TEST_CDECL __attribute__((cdecl))
#endif

void release_callback(void* value) {
  released.push_back(value);
  if (root_to_clear != nullptr) {
    OpaqueMessageCleanupWindow* receiver = root_to_clear;
    root_to_clear = nullptr;
    receiver->root_storage_00 = nullptr;
  }
}

void test_service_roots_are_distinct() {
  g_wave6_service_roots.state_manager_015fd898 = 0x11111111u;
  g_wave6_service_roots.prop_manager_015fd8f0 = 0x22222222u;
  assert(reinterpret_cast<std::uintptr_t>(App_IStateManager_Get_0067dce0()) ==
         0x11111111u);
  assert(reinterpret_cast<std::uintptr_t>(App_IPropManager_Get_0067ddf0()) ==
         0x22222222u);
  g_wave6_service_roots.state_manager_015fd898 = 0;
  g_wave6_service_roots.prop_manager_015fd8f0 = 0;
  assert(App_IStateManager_Get_0067dce0() == nullptr);
  assert(App_IPropManager_Get_0067ddf0() == nullptr);
}

void test_cleanup_walker_order_and_null_item() {
  released.clear();
  message_cleanup_ports().release_00f47380 = &release_callback;
  std::uint32_t links[3]{0x1000u, 0x2000u, 0u};
  OpaqueMessageManager manager{};
  OpaqueMessageCleanupWindow* receiver = &manager.cleanup_08;
  receiver->root_storage_00 = receiver;
  receiver->link_14 = reinterpret_cast<std::uint8_t*>(links);
  receiver->array_end_24 = reinterpret_cast<std::uint8_t*>(links + 2);
  receiver->cursor_08 = nullptr;
  receiver->limit_10 = nullptr;
  receiver->end_18 = nullptr;
  receiver->cleanup_storage_walker();
  assert(released.size() == 3u);
  assert(released[0] == reinterpret_cast<void*>(0x1000u));
  assert(released[1] == reinterpret_cast<void*>(0x2000u));
  assert(released[2] == receiver);
  message_cleanup_ports().release_00f47380 = nullptr;
}

void test_cleanup_walker_rereads_root_storage() {
  released.clear();
  message_cleanup_ports().release_00f47380 = &release_callback;
  std::uint32_t links[2]{0x3000u, 0u};
  OpaqueMessageManager manager{};
  OpaqueMessageCleanupWindow* receiver = &manager.cleanup_08;
  receiver->root_storage_00 = receiver;
  receiver->link_14 = reinterpret_cast<std::uint8_t*>(links);
  receiver->array_end_24 = reinterpret_cast<std::uint8_t*>(links + 1);
  receiver->cursor_08 = nullptr;
  receiver->limit_10 = nullptr;
  receiver->end_18 = nullptr;
  root_to_clear = receiver;
  receiver->cleanup_storage_walker();
  assert(released.size() == 1u);
  assert(released[0] == reinterpret_cast<void*>(0x3000u));
  assert(receiver->root_storage_00 == nullptr);
  root_to_clear = nullptr;
  message_cleanup_ports().release_00f47380 = nullptr;
}

void test_cleanup_walker_null_root_skips_array() {
  released.clear();
  message_cleanup_ports().release_00f47380 = &release_callback;
  std::uint32_t links[2]{0x4000u, 0u};
  OpaqueMessageManager manager{};
  OpaqueMessageCleanupWindow* receiver = &manager.cleanup_08;
  receiver->link_14 = reinterpret_cast<std::uint8_t*>(links);
  receiver->array_end_24 = reinterpret_cast<std::uint8_t*>(links + 1);
  receiver->cursor_08 = nullptr;
  receiver->limit_10 = nullptr;
  receiver->end_18 = nullptr;
  receiver->cleanup_storage_walker();
  assert(released.empty());
  message_cleanup_ports().release_00f47380 = nullptr;
}

void test_cleanup_walker_block_limit_handoff() {
  released.clear();
  message_cleanup_ports().release_00f47380 = &release_callback;
  alignas(std::uint8_t) std::uint8_t records[0x20]{};
  std::uint32_t links[2]{0u, 0u};
  links[1] = reinterpret_cast<std::uint32_t>(records + 0x18);
  OpaqueMessageManager manager{};
  OpaqueMessageCleanupWindow* receiver = &manager.cleanup_08;
  receiver->cursor_08 = records;
  receiver->limit_10 = records + 0x18;
  receiver->link_14 = reinterpret_cast<std::uint8_t*>(links);
  receiver->end_18 = records + 0x18;
  receiver->cleanup_storage_walker();
  assert(released.empty());
  assert(links[1] == reinterpret_cast<std::uint32_t>(records + 0x18));
  message_cleanup_ports().release_00f47380 = nullptr;
}

}

int main() {
  test_service_roots_are_distinct();
  test_cleanup_walker_order_and_null_item();
  test_cleanup_walker_rereads_root_storage();
  test_cleanup_walker_null_root_skips_array();
  test_cleanup_walker_block_limit_handoff();
  return 0;
}

#undef TEST_CDECL
